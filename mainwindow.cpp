#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clsettings.h"
#include "dlgsettings.h"
#include "mailer.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QThreadPool>
#include <QFileInfo>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("abondServices");//(Strings::organisationName);
    QCoreApplication::setOrganizationDomain("abondservices.co.uk");//(Strings::organisationDomain);
    QCoreApplication::setApplicationName("abStartupManager");//(Strings::applicationName);

    clSettings::validate();                         //Initialise settings

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    int iconsize=settings.value("iconSize").toInt();
    pgmImage = new abUIImage(this, ":/images/red_shield_icon.png",iconsize,iconsize);
    resize(iconsize,iconsize);

    QAction * a_status = new QAction("Status", this);
    connect(a_status, SIGNAL(triggered()), this, SLOT(status()));
    pgmImage->menu()->addAction(a_status);

    QAction * a_settings = new QAction("Settings", this);
    connect(a_settings, SIGNAL(triggered()), this, SLOT(settings()));
    pgmImage->menu()->addAction(a_settings);

    QAction * a_quit = new QAction("Disconnect && Quit", this);
    connect(a_quit, SIGNAL(triggered()), this, SLOT(close()));
    pgmImage->menu()->addAction(a_quit);

    QAction * a_shutdown = new QAction("Shutdown", this);
    connect(a_shutdown, SIGNAL(triggered()), this, SLOT(shutdown()));
    pgmImage->menu()->addAction(a_shutdown);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pgmImage);

    setCentralWidget(new QWidget);
    this->centralWidget()->setStyleSheet("background-color: rgba(255, 0, 0, 0)"); //Transparency
    centralWidget()->setLayout(layout);

    vpnInterface = clVPNInterface::getInstance();   //Initialise VPN Interface Instance
    connect(vpnInterface, SIGNAL(vpnConnected(bool)), this, SLOT(vpnConnected(bool)));
    connect(vpnInterface, SIGNAL(vpnAlarm()), this, SLOT(vpnAlarm()));
    vpnInterface->forceNotify();
    startPollingVPNInterface();

    m_connectToVPN = connectToVPN::getInstance();
    connect(m_connectToVPN, SIGNAL(connectionLost()), vpnInterface, SLOT(forceNotify()));

}

MainWindow::~MainWindow()
{
    delete ui;
    VPNTimer->deleteLater();

    if (startUpProcess != nullptr) delete startUpProcess;
    if (shutdownProcess != nullptr) delete shutdownProcess;
    if (shutdownCmdProcess != nullptr) delete shutdownCmdProcess;
    if (m_shutdownCmdStatus != nullptr) delete m_shutdownCmdStatus;
}
void MainWindow::showEvent(QShowEvent *ev){
    QMainWindow::showEvent(ev);
    QTimer::singleShot(50, this, SLOT(windowVisible()));
}
void MainWindow::windowVisible(){
    return;
    if (!userIsRoot()){
        QMessageBox msgBox;
        msgBox.setText("Root Privileges are Required to run this Program");
        msgBox.exec();
        QCoreApplication::quit();
    }
}
bool MainWindow::userIsRoot(){
    QSettings settings;
    QFileInfo fi(settings.value("privilegedDir").toString());
    return (fi.isDir() && fi.isWritable());

}
void MainWindow::mousePressEvent(QMouseEvent *event){
    m_pos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - m_pos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
void MainWindow::closeEvent(QCloseEvent *event) {
    m_closing=true;
    m_connectToVPN = connectToVPN::getInstance();
    m_connectToVPN->disconnectVPN();

    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
void MainWindow::startPollingVPNInterface(){
    VPNTimer = new QTimer(this);
    connect(VPNTimer, SIGNAL(timeout()), vpnInterface, SLOT(pollVPN()) );

    QSettings settings;
    int pollPeriod = settings.value("pollVPNEvery").toInt();
    int vpnAlarm = (settings.value("vpnAlarmAfter").toInt() / (pollPeriod/1000) ) + 1;
    vpnInterface->setAlarm(vpnAlarm);
    VPNTimer->start(pollPeriod);
}

void MainWindow::doConnect(){
    QSettings settings;
    QString openVPNCmd = settings.value("openVPNCmd").toString();
    QString authFile = settings.value("authFile").toString();
    connect_vpn(openVPNCmd, nextConnection(), authFile);
}
QString MainWindow::nextConnection(){
    clSettingsHelper settingsHelper;// = new clSettingsHelper();
    QStringList m_list=settingsHelper.getList("Servers");
    if (m_list.size() == 0) return "";
    if (nextVPNConnection >= m_list.size()) nextVPNConnection=0;
    return m_list.at(nextVPNConnection++);
}
void MainWindow::connect_vpn(QString openVPNCmd, QString ovpnFile, QString authFile){
    if (!m_closing){
        m_connectToVPN = connectToVPN::getInstance();
        m_connectToVPN->connectVPN(this, openVPNCmd, ovpnFile, authFile);
    }

}
void MainWindow::vpnConnected(bool isConnected){
    //On Startup we should always arrive here and either
    //Connect (if not connected) or monitor (if Connected)
    if (isConnected){
        qDebug() << "VPN is Connected";
        //The first time we get here we run the startup applications
        if (!monitoring) runStartupApps();
        monitoring=true;
        pgmImage->loadImage(":/images/green_shield_icon.png");
        emailServerFailures();
    } else {
         qDebug() << "VPN is Disconnected... Attempting to connect to VPN";
         pgmImage->loadImage(":/images/red_shield_icon.png");
         if (monitoring) logDisconnection();
         doConnect();
    }
}
void MainWindow::emailServerFailures(){
    mailer mailFailures(m_connectionFailures);
    mailFailures.run();
}
void MainWindow::logDisconnection(){
    QString format = "d MMMM yy hh:mm:ss";
    QString logEntry=QDateTime::currentDateTime().toString(format) + " " + m_connectToVPN->currentConnection();
    m_connectionFailures.append(logEntry);
}
void MainWindow::vpnAlarm(){
    // Here if m_connectToVPN detects a disconnect or the VPNInterface Alarm goes off
    vpnConnected(false); // Force next connection when vpnDisconnected for too long
}

void MainWindow::runStartupApps(){
    QSettings settings;
    QString onFirstConnectRunDetached = settings.value("onFirstConnectRunDetached").toString();
    startUpProcess = new QProcess();
    runCmdDetached(startUpProcess, onFirstConnectRunDetached);

}
void MainWindow::runCmdDetached(QProcess * p, QString cmd){
    QFile file(cmd);
    p->startDetached(cmd);
}
void MainWindow::shutdown(){
    QSettings settings;
    QString beforeShutdownRunInWindow = settings.value("beforeShutdownRunInWindow").toString();

    QFile file(beforeShutdownRunInWindow);
    //if (file.exists()){
        shutdownProcess = new QProcess(this);
        connect(shutdownProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(runShutdownCmd()));
        m_shutdownCmdStatus = new dlgRunCLIApp(this, shutdownProcess, beforeShutdownRunInWindow, true, false);
        m_shutdownCmdStatus->show();
    //} else {
    //    runShutdownCmd();
    //}

}
void MainWindow::runShutdownCmd(){
    QSettings settings;
    QString shutdownCmd = settings.value("shutdownCmd").toString();
    shutdownCmdProcess = new QProcess();
    runCmdDetached(shutdownCmdProcess, shutdownCmd);
    close();
}
void MainWindow::settings(){
    dlgSettings dialog;
    dialog.exec();
}
void MainWindow::status(){
    m_connectToVPN->showStatus();
}

