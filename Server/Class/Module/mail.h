#ifndef MAIL_H
#define MAIL_H

#include <QObject>
#include <QTcpSocket>

class Mail : public QObject
{
    Q_OBJECT
public:
    explicit Mail(QObject *parent);
    void processInfo(QTcpSocket *socket, const QString &text);

private:
    void myWrite(QTcpSocket *socket, const QString &title, const QString &text);

private slots:
    void f_myMails(QTcpSocket *socket);
    void f_removeMail(QTcpSocket *socket, const QString &text);

signals:
    void s_write(QTcpSocket *socket, const QString &title, const QString &text);
};

#endif // MAIL_H
