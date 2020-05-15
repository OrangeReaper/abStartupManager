#ifndef CLPINGTESTVPN_H
#define CLPINGTESTVPN_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "ping.h"

class clpingtestvpn : public ping
{
    Q_OBJECT
public:
    explicit clpingtestvpn(QObject *parent = nullptr);

signals:

public slots:
    void monitorVPN();
    void stopMonitoring();

private:
    QTimer * m_pingEvery;
    //QString m_doPing;

    static QString m_getVPNIPAddress(){ return "ip -4 addr show dev tun0"; }

    //int m_alarmAfter;
    //int m_alarmCount=0;

};

#endif // CLPINGTESTVPN_H
