#include "dlgruncliapp.h"
#include "abfunctions.h"
#include "ui_dlgruncliapp.h"
#include <QDebug>
#include <QSettings>
#include <QTextStream>
#include <QScreen>

dlgRunCLIApp::dlgRunCLIApp(QWidget *parent, QProcess *process, QString command, bool userCanAbort, bool runDetached) :
    QDialog(parent),
    ui(new Ui::dlgRunCLIApp)
{
    ui->setupUi(this);
    ui->hideWindow->setVisible(!userCanAbort);
    ui->abortProcess->setVisible(userCanAbort);
    ui->output->addItem(command);

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

    m_process = process;
    connect(m_process,SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
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
void dlgRunCLIApp::readyReadStandardOutput(){
    m_process->setReadChannel(QProcess::StandardOutput);
    QTextStream stream(m_process);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui->output->addItem(line);
    }
}

void dlgRunCLIApp::abortProcess(){
    m_process->kill();
    m_process->waitForFinished();
    ui->output->addItem("Process terminated");
}
