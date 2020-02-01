/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   clVPNInterface.h
 * Author: andy
 *
 * Created on 27 July 2017, 17:19
 */

#ifndef CLVPNINTERFACE_H
#define CLVPNINTERFACE_H

#include <string>
#include <QMutex>
#include <QString>
#include <QObject>
#include <QSettings>

class clVPNInterface : public QObject {
    Q_OBJECT
public:
    static clVPNInterface *getInstance(); //singleton

    QString getVPNAddress() { return lclVPNAddress; }
    bool vpnIsConnected();



    void setAlarm(int alarmCount){
        m_alarmAfter=alarmCount;
        m_alarmCountdown=alarmCount;
    }

public slots:
    void forceNotify();
    void pollVPN();

signals:
    void vpnConnected(bool state);
    void vpnAlarm();

private:
    clVPNInterface(){}
    static clVPNInterface *s_instance;

    QMutex mu;

    bool isVPNConnected();
    bool m_connected;

    void notify(bool status);
    void startTimer();
    void sendAlarm();

    QString lclVPNAddress="0:0:0:0";

    int m_alarmAfter = 18;
    int m_alarmCountdown = 18;

};

#endif /* CLVPNINTERFACE_H */

