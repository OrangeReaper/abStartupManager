#include "mailer.h"
#include <QDebug>
#include <QSettings>
#include <QHostInfo>

mailer::mailer(QStringList message)
{
    m_message = message;
    QSettings settings;
    smtpServer = settings.value("smtpServer").toString();
    smtpUser = settings.value("smtpUser").toString();
    smtpPassword = settings.value("smtpPassword").toString();
    recipientEmail = settings.value("recipientEmail").toString();
    recipientName = settings.value("recipientName").toString();
    smtp = new SmtpClient(smtpServer, 465, SmtpClient::SslConnection);
}
mailer::~mailer(){
    smtp->deleteLater();
}
void mailer::run(){
    QString t_message="Some servers disconnected or failed to connect.\n";
    if (m_message.length() > 0){
        for (auto str : m_message){
            t_message=t_message + "\n" + str;
        }

        smtp->setUser(smtpUser);
        smtp->setPassword(smtpPassword);

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        QString sender = "abStartupManager@" + QHostInfo::localHostName();
        message.setSender(new EmailAddress(smtpUser, sender));
        message.addRecipient(new EmailAddress(recipientEmail, recipientName));
        message.setSubject("VPN Server Event Report");

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText(t_message);

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp->connectToHost();
        smtp->login();
        smtp->sendMail(message);
        smtp->quit();
    }
}

