#include "dlgruncliapp.h"
#include "abfunctions.h"
#include "ui_dlgruncliapp.h"
#include <QDebug>
#include <QSettings>
#include <QTextStream>
#include <QScreen>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>

dlgRunCLIApp::dlgRunCLIApp(QWidget *parent, QProcess *process, QString command, bool userCanAbort, bool runDetached, QStringList abort) :
    QDialog(parent),
    ui(new Ui::dlgRunCLIApp)
{
    ui->setupUi(this);
    ui->hideWindow->setVisible(true); // always
    ui->abortProcess->setVisible(userCanAbort);

    logSomething(command);

    if (userCanAbort){
        QStringList sl=command.split(" ");
        m_killCommand = sl[0];
        if (m_killCommand=="sudo") m_killCommand=sl[1];
        sl=m_killCommand.split("/");
        m_killCommand=sl[sl.size()-1];
        m_killCommand="sudo /usr/bin/killall -15 " + m_killCommand;
    }

    //Put window in centre of screen

    // Get current screen size
    QScreen *screen= QGuiApplication::screens().at(0);
    QSize rec =screen->availableSize();

    // Using base size of window
    QSize size = this->baseSize();

    // Set top left point
    QPoint topLeft = QPoint((rec.width() / 2) - (size.width() / 2), (rec.height() / 2) - (size.height() / 2));

    // set window position
    setGeometry(QRect(topLeft, size));
    m_abort=abort;
    m_process = process;
    connect(m_process,SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(m_process, SIGNAL(finished(int)), this, SLOT(saveLog()));
    if (runDetached){
        m_process->startDetached(command);
    } else {
        m_process->start(command);
    }
}

dlgRunCLIApp::~dlgRunCLIApp()
{
    delete ui;
}
void dlgRunCLIApp::closeEvent(QCloseEvent *event) {
    saveLog();
}
void dlgRunCLIApp::readyReadStandardOutput(){
    m_process->setReadChannel(QProcess::StandardOutput);
    QTextStream stream(m_process);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui->output->addItem(line);
        abortProcess(line);
    }
}
void dlgRunCLIApp::abortProcess(QString line){

    for (QString item : m_abort){
        if (line.contains(item, Qt::CaseInsensitive)){
            abortProcess();
            break;
        }
    }
}
void dlgRunCLIApp::abortProcess(){
    emit abort();
    ui->abortProcess->setEnabled(false);
    logSomething("Process terminated by user.. Wait");

    QProcess p;
    p.start(m_killCommand);
    p.waitForFinished();

    m_process->waitForFinished();

    saveLog();

}

void dlgRunCLIApp::saveLog(){
    if (!logSaved){
        logSaved=true;
        QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
        QString logDir = path + "/" + QCoreApplication::organizationName() + "/logs/abStartupManager";
        if (abFunctions::mkdir(path)){
            path = logDir + "/" + QDate::currentDate().toString("yyMMdd") + ".log";
            QFile f(path);
            if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
                QString txt = "...\n" ;
                f.write(txt.toUtf8());
                for(int i = 0; i < ui->output->count(); ++i)
                {
                    QListWidgetItem* item = ui->output->item(i);
                    txt = item->text() + "\n";
                    f.write(txt.toUtf8());
                }
                f.close();
                cleanup(logDir);
            }
        }
    }
    emit finished();
}
void dlgRunCLIApp::cleanup(QString logDir){
    //QDir(const QString & path, const QString & nameFilter, SortFlags sort = SortFlags( Name | IgnoreCase ), Filters filters = AllEntries);
    QDir dir(logDir,"*.log",( QDir::Name | QDir::IgnoreCase ));

    QSettings settings;
    int maxLogs = settings.value("maxLogs").toInt();

    while(dir.entryList().size() > maxLogs){
        if (!dir.remove(dir.entryList().first())) break;
    }
}

void dlgRunCLIApp::logSomething(QString text){
    QString format = "d MMMM yy hh:mm:ss";
    QString log=QDateTime::currentDateTime().toString(format) + " " + text;
    ui->output->addItem(log);
}


