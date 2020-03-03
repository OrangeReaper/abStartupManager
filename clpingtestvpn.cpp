#include "clpingtestvpn.h"
#include <QTextStream>
#include <QDebug>

clpingtestvpn::clpingtestvpn(QObject *parent) : QObject(parent)
{
    m_pingEvery = new QTimer();
    m_pingEvery->setInterval(5000);
    connect(m_pingEvery, SIGNAL(timeout()), this, SLOT(doPing()));

    m_ipProcess = new QProcess();
    connect(m_ipProcess,SIGNAL(readyReadStandardOutput()), this, SLOT(processIPCommand()));
    connect(m_ipProcess, SIGNAL(finished(int)), this, SLOT(ipCommandFinished()));
}
void clpingtestvpn::monitorVPN(){
    m_pingEvery->stop();
    getIPAddr();
}
void clpingtestvpn::getIPAddr(){
    //Parse command: ip -4 addr show dev tun0
    vpnIPAddress="";
    m_ipProcess->start(m_getVPNIPAddress());
}
void clpingtestvpn::ipCommandFinished(){
    if (vpnIPAddress.length()==0) {
        emit vpnConnectionState(false);
    } else {
        m_pingEvery->start();
    }

}
void clpingtestvpn::processIPCommand(){
    m_ipProcess->setReadChannel(QProcess::StandardOutput);
    QTextStream stream(m_ipProcess);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.contains("inet")) setIPAddress(line);
    }
}
void clpingtestvpn::setIPAddress(QString line){
    QString s = "inet";
    QString e = "/";
    int start = line.indexOf(s, 0, Qt::CaseInsensitive)+s.length();
    int end = line.indexOf(e, start, Qt::CaseInsensitive);
    vpnIPAddress = line.mid(start, (end - (start))).trimmed();
}
void clpingtestvpn::doPing(){
    m_doPing="ping -c 1 -W 1 " + vpnIPAddress;
    m_pingProcess = new QProcess();
    connect(m_pingProcess, SIGNAL(finished(int)), this, SLOT(pingCommandFinished(int)));
    m_pingProcess->start(m_doPing);
}
void clpingtestvpn::pingCommandFinished(int exitCode){
    if (exitCode==0) {
        // it's alive
    } else {
        // it's dead
        emit vpnConnectionState(false);
        m_pingEvery->stop();
    }
    m_pingProcess->deleteLater();
}
