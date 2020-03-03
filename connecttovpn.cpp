#include "connecttovpn.h"
#include "abfunctions.h"

#include <QMessageBox>
#include <QTextStream>
#include <QSettings>
#include <QDebug>

connectToVPN* connectToVPN::s_instance = 0;

connectToVPN* connectToVPN::getInstance(){
    if(!s_instance) {
        s_instance = new connectToVPN();;
        // There is no instance so we created one.
        return s_instance;
    } else {
        //This is the same instance!
        return s_instance;
    }
}
connectToVPN::~connectToVPN()
{
    killWindow();
}
void connectToVPN::connectVPN( QString openVPNCmd, QString ovpnFile, QString authFile){

    disconnectVPN();
    //needs super user privileges!!!
    QString program = openVPNCmd + " --config " + ovpnFile + " --auth-user-pass " + authFile;

    p_connect = new QProcess(this);

    connect(p_connect, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(on_process_finished()));

    QSettings settings;
    QStringList abortOn=settings.value("abortIf").toString().split(",");
    m_openVPNStatus = new dlgRunCLIApp(0, p_connect, program, false, false, abortOn);
    connect(m_openVPNStatus, SIGNAL(abort()), this, SLOT(killVPNConnections()));

    m_currentConnection=ovpnFile.mid(ovpnFile.lastIndexOf("/"));
}

void connectToVPN::on_process_finished(){
    killWindow();
//    m_failed=true;
}

void connectToVPN::killWindow(){

    if (m_openVPNStatus != nullptr) {
        m_openVPNStatus->close();
        m_openVPNStatus->deleteLater();
        m_openVPNStatus=nullptr;
    }
}
void connectToVPN::disconnectVPN(){
    killVPNConnections();
}
void connectToVPN::killVPNConnections(){
    QProcess p;
    QString k = "sudo /usr/bin/killall -2 openvpn" ;
    p.start(k);
    p.waitForFinished();
    killWindow();
}
void connectToVPN::showStatus(){
   if (m_openVPNStatus != nullptr) {
       m_openVPNStatus->show();
   } else {
       QMessageBox msgBox;
       msgBox.setText("openVPN Not Running");
       msgBox.exec();
   }
}
