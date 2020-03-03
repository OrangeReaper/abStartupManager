#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clsettings.h"
#include "dlgsettings.h"
#include "mailer.h"
#include "clsettingshelper.h"
#include "abqaction.h"
#include "abfunctions.h"

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

   setToolTip("v0.104.2");

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

    m_profile = new QMenu("Profile", this);
    pgmImage->menu()->addMenu(m_profile);
    populateProfileMenu();

    QAction * a_settings = new QAction("Settings", this);
    connect(a_settings, SIGNAL(triggered()), this, SLOT(settings()));
    pgmImage->menu()->addAction(a_settings);

    QAction * a_quit = new QAction("Quit", this);
    connect(a_quit, SIGNAL(triggered()), this, SLOT(userClose()));
    pgmImage->menu()->addAction(a_quit);

    QAction * a_shutdown = new QAction("Shutdown", this);
    connect(a_shutdown, SIGNAL(triggered()), this, SLOT(shutdown()));
    pgmImage->menu()->addAction(a_shutdown);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pgmImage);

    setCentralWidget(new QWidget);
    this->centralWidget()->setStyleSheet("background-color: rgba(255, 0, 0, 0)"); //Transparency
    centralWidget()->setLayout(layout);

    m_currentProfile=defaultProfile();


    m_connectToVPN = connectToVPN::getInstance();
    pingTestVPN = new clpingtestvpn(this);
    connect(pingTestVPN, SIGNAL(vpnConnectionState(bool)), this, SLOT(vpnConnected(bool)));
    pingTestVPN->monitorVPN(); // Start Monitoring
}

MainWindow::~MainWindow()
{
    delete ui;
    m_connectToVPN->deleteLater();
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
void MainWindow::populateProfileMenu(){
    //return;
    m_profile->clear();

    abQAction * action = new abQAction(defaultProfile(), this);
    connect(action, SIGNAL(triggered(QString)), this, SLOT(selectProfile(QString)));
    m_profile->addAction(action);

    clSettingsHelper m_settingsHelper;
    QStringList profiles=m_settingsHelper.getList("Profiles");
    for (QString profile : profiles){
        abQAction * newAction = new abQAction(profile, this);
        connect(newAction, SIGNAL(triggered(QString)), this, SLOT(selectProfile(QString)));
        m_profile->addAction(newAction);

    }

    m_profile->menuAction()->setVisible(profiles.count()>0);
}
void MainWindow::selectProfile(QString text){
    if (m_currentProfile != text){
        m_currentProfile=text;
        nextVPNConnection=0;
        switching=true;
        m_connectToVPN->disconnectVPN();
    }
}

void MainWindow::userClose(){
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(0, "Quit", "Do you want to Disconnect VPN?",
                                    QMessageBox::Yes|QMessageBox::No);
      //m_connectToVPN = connectToVPN::getInstance();
      if (reply == QMessageBox::Yes) {          
        m_connectToVPN->disconnectVPN();
      } else {
        m_connectToVPN->deleteLater();
      }
      close();
}
void MainWindow::closeEvent(QCloseEvent *event) {
    m_closing=true;
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::doConnect(){

    QSettings settings;
    QString openVPNCmd = settings.value("openVPNCmd").toString();
    QString authFile = settings.value("authFile").toString();
    connect_vpn(openVPNCmd, nextConnection(), authFile);
}
QString MainWindow::nextConnection(){
    clSettingsHelper settingsHelper;// = new clSettingsHelper();
    QStringList m_list=settingsHelper.getList(m_currentProfile);
    if (m_list.size() == 0) return "";
    if (nextVPNConnection >= m_list.size()) nextVPNConnection=0;
    return m_list.at(nextVPNConnection++);
}
void MainWindow::connect_vpn(QString openVPNCmd, QString ovpnFile, QString authFile){
    if (!m_closing && abFunctions::fileExists(ovpnFile) && abFunctions::fileExists(authFile) ){
        //m_connectToVPN = connectToVPN::getInstance();
        m_connectToVPN->connectVPN(openVPNCmd, ovpnFile, authFile);
    }
}
void MainWindow::vpnConnected(bool isConnected){
    //On Startup we should always arrive here and either
    //Connect (if not connected) or monitor (if Connected)
    if (isConnected){
        qDebug() << "VPN is Connected";
        QString logEntry= getConnectionName() + " Connected";
        logSomething(logEntry);
        //The first time we get here we run the startup applications
        if (!monitoring) runStartupApps();
        monitoring=true;
        pgmImage->loadImage(":/images/green_shield_icon.png");
        if (m_reportDisconnect) emailServerFailures();
    } else {
         qDebug() << "VPN is Disconnected... Attempting to connect to VPN";
         pgmImage->loadImage(":/images/red_shield_icon.png");
         if (monitoring && !switching) logDisconnection();
         switching=false;
         doConnect();
    }
}
QString MainWindow::getConnectionName(){
    QString result=m_connectToVPN->currentConnection();
    if (result == "") result = "Unknown Connection";
    return result;
}
void MainWindow::emailServerFailures(){
    mailer mailFailures(m_connectionLog);
    mailFailures.run();
}
void MainWindow::logDisconnection(){
    m_reportDisconnect=true;
    QString logEntry= getConnectionName() + " Disconnected";
    logSomething(logEntry);
}
void MainWindow::logSomething(QString logEntry){
    QString format = "d MMMM yy hh:mm:ss";
    QString log=QDateTime::currentDateTime().toString(format) + " " + logEntry;
    m_connectionLog.append(log);
}

void MainWindow::runStartupApps(){
    QSettings settings;
    QString onFirstConnectRunDetached = settings.value("onFirstConnectRunDetached").toString();
    startUpProcess = new QProcess(this);
    runCmdDetached(startUpProcess, onFirstConnectRunDetached);

}
void MainWindow::runCmdDetached(QProcess * p, QString cmd){
    if (abFunctions::fileExists(cmd)) p->startDetached(cmd);
}
void MainWindow::shutdown(){
    QSettings settings;
    QString beforeShutdownRunInWindow = settings.value("beforeShutdownRunInWindow").toString();

    if (abFunctions::fileExists(beforeShutdownRunInWindow)){

        shutdownProcess = new QProcess(this);
        connect(shutdownProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(runShutdownCmd()));
        m_shutdownCmdStatus = new dlgRunCLIApp(this, shutdownProcess, beforeShutdownRunInWindow, true, false);
        m_shutdownCmdStatus->show();

    } else runShutdownCmd();


}
void MainWindow::runShutdownCmd(){
    QSettings settings;
    QString shutdownCmd = settings.value("shutdownCmd").toString();
    shutdownCmdProcess = new QProcess(this);
    runCmdDetached(shutdownCmdProcess, shutdownCmd);
    close();
}
void MainWindow::settings(){
    dlgSettings dialog;
    connect(&dialog, SIGNAL(profilesChanged()), this, SLOT(populateProfileMenu()) );
    dialog.exec();
}
void MainWindow::status(){
    m_connectToVPN->showStatus();
}

