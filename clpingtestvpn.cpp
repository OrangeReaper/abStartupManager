#include "clpingtestvpn.h"
#include <QTextStream>
#include <QDebug>
#include <QSettings>

clpingtestvpn::clpingtestvpn(QObject *parent) : ping(parent)
{
    m_pingEvery = new QTimer();
    QSettings settings;
    int pollPeriod = settings.value("pollVPNEvery").toInt();
    m_pingEvery->setInterval(pollPeriod);

    connect(m_pingEvery, SIGNAL(timeout()), this, SLOT(doPing()));

}
void clpingtestvpn::monitorVPN(){
    doPing();
    m_pingEvery->start();
}
void clpingtestvpn::stopMonitoring(){
    m_pingEvery->stop();
}

