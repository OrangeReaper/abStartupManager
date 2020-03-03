#ifndef CLPINGTESTVPN_H
#define CLPINGTESTVPN_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QTimer>

class clpingtestvpn : public QObject
{
    Q_OBJECT
public:
    explicit clpingtestvpn(QObject *parent = nullptr);

    enum state {
        UNKNOWN,
        CONNECTED,
        DISCONNECTED
    };

signals:
    void vpnConnectionState(bool connected);
public slots:
    void monitorVPN();
    void pingCommandFinished(int exitCode);
    void doPing();

private:
    QTimer * m_pingEvery;
    QString m_doPing;
    QProcess * m_pingProcess;
    state m_state=UNKNOWN;
    static QString m_getVPNIPAddress(){ return "ip -4 addr show dev tun0"; }
    QString pingAddress="";
    void emitSignal(bool connected);

};

#endif // CLPINGTESTVPN_H
