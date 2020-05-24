#include "connecttovpn.h"
#include "abfunctions.h"


#include <QNetworkConfigurationManager>

#include <QMessageBox>
#include <QTextStream>
#include <QSettings>
#include <QDebug>
#include <QThread>

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
    if (m_doPing) m_doPing->deleteLater();
}
void connectToVPN::connectVPN( QString openVPNCmd, QString ovpnFile, QString authFile){
    waitForNetwork();
    m_openVPNCmd = openVPNCmd;
    m_ovpnFile = ovpnFile;
    m_authFile = authFile;
    reconnect();
}
void connectToVPN::waitForNetwork(){
    QNetworkConfigurationManager networkConfigurationManager;
    while (!networkConfigurationManager.isOnline() ){
        emit logSomething("Waiting for Network to Connect");
        QThread::sleep(1000);
    }
}
void connectToVPN::reconnect(){
    killVPNConnections();

    //needs super user privileges!!!
    QString program = m_openVPNCmd + " --config " + m_ovpnFile + " --auth-user-pass " + m_authFile;

    if (p_connect) p_connect->deleteLater();
    p_connect = new QProcess(this);

    QSettings settings;
    QStringList abortOn=settings.value("abortIf").toString().split(",");
    m_openVPNStatus = new dlgRunCLIApp(0, p_connect, program, true, false, abortOn); //changed to runDetached
    // let monitor decide when to reconnect connect(m_openVPNStatus, SIGNAL(finished()), this, SLOT(reconnect()));
    m_currentConnection=m_ovpnFile.mid(m_ovpnFile.lastIndexOf("/"));

    startPing(30000); //30 seconds
}
void connectToVPN::startPing(int timeout){
    m_pingTimeout=timeout;
    m_startTime=QDateTime::currentDateTime();
    doPing();
}
void connectToVPN::doPing(){
    if (m_doPing) m_doPing->deleteLater();

    m_doPing=new ping();
    connect (m_doPing, SIGNAL(vpnConnectionState(bool)), this, SLOT(pingState(bool)));

    m_doPing->doPing();
}
void connectToVPN::pingState(bool connectionState){
    m_connected=connectionState;
    if (m_connected){
        pingComplete();
        qDebug() << "Ping Success";
        emit connected();        
    } else {
        if (m_startTime.msecsTo(QDateTime::currentDateTime()) > m_pingTimeout) {
            pingComplete();
           emit failedToConnect();

        } else {
            qDebug() << "Ping Failed";
            doPing();
        }
    }
}
void connectToVPN::pingComplete(){
    m_doPing->deleteLater();
    m_doPing=0;
}
void connectToVPN::killVPNConnections(){
    QProcess p;
    QString k = "sudo /usr/bin/killall -2 openvpn" ;
    p.start(k);
    p.waitForFinished();
    killWindow();
}
void connectToVPN::killWindow(){
    if (m_openVPNStatus != nullptr) {
        m_openVPNStatus->close();
        m_openVPNStatus->deleteLater();
        m_openVPNStatus=nullptr;
    }
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
