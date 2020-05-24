#include "ping.h"
#include <QApplication>
#include <QSettings>

ping::ping(QObject *parent) : QObject(parent)
{
    QSettings settings;
    m_pingAddress=settings.value("pingAddr").toString();

}
ping::~ping(){
    if (m_pingProcess) m_pingProcess->deleteLater();
}
void ping::doPing(){
    //count=1; deadline(w)=1 - exit after 1 second regardless... send 1 packet
    QString doPingProcess="ping -c 1 -W 1 " + m_pingAddress;

    m_pingProcess = new QProcess(this);
    connect(m_pingProcess, SIGNAL(finished(int)), this, SLOT(pingCommandFinished(int)));
    m_pingProcess->start(doPingProcess);
    QApplication::processEvents();
}
void ping::pingCommandFinished(int exitCode){
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
    m_pingProcess=0;
    //m_pingProcess->deleteLater();
}
void ping::emitSignal(bool connected){
    emit vpnConnectionState(connected);
}
