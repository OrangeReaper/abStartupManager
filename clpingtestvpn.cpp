#include "clpingtestvpn.h"
#include <QTextStream>
#include <QDebug>
#include <QSettings>

clpingtestvpn::clpingtestvpn(QObject *parent) : QObject(parent)
{
    m_pingEvery = new QTimer();
    QSettings settings;
    int pollPeriod = settings.value("pollVPNEvery").toInt();
    m_pingEvery->setInterval(pollPeriod);
    connect(m_pingEvery, SIGNAL(timeout()), this, SLOT(doPing()));

    pingAddress=settings.value("pingAddr").toString();;
}
void clpingtestvpn::monitorVPN(){
    doPing();
    m_pingEvery->start();
}
void clpingtestvpn::doPing(){

    m_doPing="ping -c 1 -W 1 " + pingAddress;
    m_pingProcess = new QProcess(this);
    connect(m_pingProcess, SIGNAL(finished(int)), this, SLOT(pingCommandFinished(int)));
    m_pingProcess->start(m_doPing);

}
void clpingtestvpn::pingCommandFinished(int exitCode){
    if (exitCode==0) {
        // it's alive
        if (m_state != CONNECTED){
            m_state = CONNECTED;
            emitSignal(true);
        }
    } else {
        // it's dead
        if (m_state != DISCONNECTED){
            m_state = DISCONNECTED;
            emitSignal(false);
        }
    }
    m_pingProcess->deleteLater();
}
void clpingtestvpn::emitSignal(bool connected){
    emit vpnConnectionState(connected);
}
