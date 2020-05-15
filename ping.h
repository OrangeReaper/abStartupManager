#ifndef PING_H
#define PING_H

#include <QObject>
#include <QProcess>

class ping : public QObject
{
    Q_OBJECT
public:
    explicit ping(QObject *parent = nullptr);
    virtual ~ping();

    enum state {
        UNKNOWN=0,
        CONNECTED=1,
        DISCONNECTED=2
    };

    int pingState() { return m_state; }
    void setState(int state) { m_state=state; }
signals:
    void vpnConnectionState(bool connected);
public slots:
    void pingCommandFinished(int exitCode);
    void doPing();

private:
    void emitSignal(bool connected);

    QString m_pingAddress="";

    QProcess * m_pingProcess=0;

    int m_state=UNKNOWN;
};

#endif // PING_H
