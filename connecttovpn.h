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

    void connectVPN(QWidget *parent=0, QString openVPNCmd="", QString ovpnFile="", QString authFile="");
    void disconnectVPN();
    void showStatus();

    bool hasFailed()   { return m_failed; }

    QString currentConnection(){ return m_currentConnection; }

public slots:
    void on_process_finished();
signals:
    void connectionLost();
private:
    connectToVPN(){}
    static connectToVPN *s_instance;

    bool m_failed = false;

    void killVPNConnections();
    void killWindow();

    QProcess * p_connect=nullptr;

    QString m_currentConnection="";

    dlgRunCLIApp * m_openVPNStatus = nullptr;


};

#endif // CONNECTTOVPN_H
