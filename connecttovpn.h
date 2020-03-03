#ifndef CONNECTTOVPN_H
#define CONNECTTOVPN_H

#include <QString>
#include <QObject>
#include <QProcess>
#include "dlgruncliapp.h"


class connectToVPN : public QObject  {
    Q_OBJECT
public:    
    static connectToVPN *getInstance();
    ~connectToVPN();
    void connectVPN(QString openVPNCmd="", QString ovpnFile="", QString authFile="");
    void disconnectVPN();
    void showStatus();

    QString currentConnection(){ return m_currentConnection; }

public slots:
    void on_process_finished();
    void killVPNConnections();
signals:
private:
    connectToVPN(){} // Singleton Object
    static connectToVPN *s_instance;

    void killWindow();

    QProcess * p_connect=nullptr;
    QString m_currentConnection="";
    dlgRunCLIApp * m_openVPNStatus = nullptr;
};

#endif // CONNECTTOVPN_H
