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

signals:
    void vpnConnectionState(bool connected);
public slots:
    void monitorVPN();
    void processIPCommand();
    void ipCommandFinished();
    void pingCommandFinished(int exitCode);
    void doPing();

private:
    QTimer * m_pingEvery;
    QProcess * m_ipProcess;
    QString m_doPing;
    QProcess * m_pingProcess;
    static QString m_getVPNIPAddress(){ return "ip -4 addr show dev tun0"; }
    QString vpnIPAddress;
    void getIPAddr();
    void setIPAddress(QString line);

};

#endif // CLPINGTESTVPN_H
