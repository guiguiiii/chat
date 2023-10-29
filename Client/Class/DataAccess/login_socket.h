#ifndef LOGIN_SOCKET_H
#define LOGIN_SOCKET_H

#include <QObject>
#include "Class/socket.h"

class Login_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Login_Socket(QObject *parent, Socket *socket);

    void login(const QString &no, const QString &pwd);
    void Register(const QString &no, const QString &pwd, const QString &name);

private:
    Socket *socket;
    void myWrite(const QString &title, const QString &text);

private slots:
    void readyRead(const QString &text);

signals:
    void s_login(int state);
    void s_register(int state);
};

#endif // LOGIN_SOCKET_H
