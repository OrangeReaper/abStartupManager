#include "mailer.h"
#include <QDebug>
#include <QSettings>

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
    QString t_message="The following servers disconnected or failed to connect.\n";
    if (m_message.length() > 0){
        qDebug() << t_message;
        for (auto str : m_message){
            qDebug() << str;
            t_message=t_message + "\n" + str;
        }

        smtp->setUser(smtpUser);
        smtp->setPassword(smtpPassword);

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        message.setSender(new EmailAddress(smtpUser, "abStartupManager"));
        message.addRecipient(new EmailAddress(recipientEmail, recipientName));
        message.setSubject("VPN Server Failure Report");

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText(t_message);

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        connect(smtp, SIGNAL(smtpError(SmtpClient::SmtpError e)), this, SLOT(smtpError(SmtpClient::SmtpError e)));

        qDebug() << "servers disconnected or failed to connect: Mailer Response";
        smtp->connectToHost();
        qDebug() << "Connect Response: " << smtp->getResponseText();
        smtp->login();
        qDebug() << "Login Response: " << smtp->getResponseText();
        smtp->sendMail(message);
        qDebug() << "After Send Response: " << smtp->getResponseText();
        smtp->quit();
        qDebug() << "After Quit Response: " << smtp->getResponseText();
    }
}
void mailer::smtpError(SmtpClient::SmtpError e){
    qDebug() << smtp->getResponseText();
}
