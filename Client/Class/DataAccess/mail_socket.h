#ifndef MAIL_SOCKET_H
#define MAIL_SOCKET_H

#include <QObject>
#include "Class/socket.h"
#include "Class/Data/mail.h"

class Mail_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Mail_Socket(QObject *parent, Socket *socket);

    void myMails();
    void removeMail(int no);

private:
    Socket *socket;
    void myWrite(const QString &title, const QString &text);

private slots:
    void readyRead(const QString &text);
    void f_myMails(const QString &text);
    void f_newMail(const QString &text);

signals:
    void s_myMails(const QVector<Mail> &mails);
    void s_newMail(const Mail &mail);
};

#endif // MAIL_SOCKET_H
