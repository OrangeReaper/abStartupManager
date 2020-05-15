#ifndef CONNECTTOVPN_H
#define CONNECTTOVPN_H

#include <QString>
#include <QObject>
#include <QProcess>
#include <QDateTime>

#include "dlgruncliapp.h"
#include "ping.h"


class connectToVPN : public QObject  {
    Q_OBJECT
public:    
    static connectToVPN *getInstance();
    ~connectToVPN();
    QString currentConnection(){ return m_currentConnection; }
    void connectVPN(QString openVPNCmd="", QString ovpnFile="", QString authFile="");
    void showStatus();

public slots:
    void killVPNConnections();
    void reconnect();
    void pingState(bool connectionState);
signals:
    void failedToConnect();
    void connected();
    void logSomething(QString logEntry);
private:
    connectToVPN(){} // Singleton Object
    static connectToVPN *s_instance;

    void doPing();
    void killWindow();
    void waitForNetwork();

    QProcess    * p_connect=0;
    ping        * m_doPing=0;

    QString m_currentConnection;
    QString m_openVPNCmd;
    QString m_ovpnFile;
    QString m_authFile;

    dlgRunCLIApp * m_openVPNStatus = nullptr;

    //bool m_disabled=false;
    bool m_connected;

    QDateTime m_startTime;
};

#endif // CONNECTTOVPN_H
