#ifndef MAILER_H
#define MAILER_H

#include <QThread>
#include <QObject>
#include "SmtpClient/src/SmtpMime"

class mailer: public QThread
{
    Q_OBJECT

public:
    mailer(QStringList message=QStringList());
    ~mailer();
    void run();
private slots:

private:
    QStringList m_message;
    SmtpClient * smtp;

    QString smtpServer;
    QString smtpUser;
    QString smtpPassword;
    QString recipientEmail;
    QString recipientName;
};

#endif // MAILER_H
