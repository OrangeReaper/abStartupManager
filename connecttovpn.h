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
    void startPing(int timeout);
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

    QDateTime m_startTime;
    int m_pingTimeout;
    void doPing();
    void pingComplete();

    void killWindow();
    void waitForNetwork();

    QProcess    * p_connect=0;
    ping        * m_doPing=0;

    QString m_currentConnection;
    QString m_openVPNCmd;
    QString m_ovpnFile;
    QString m_authFile;

    dlgRunCLIApp * m_openVPNStatus = nullptr;

    bool m_connected;

};

#endif // CONNECTTOVPN_H
