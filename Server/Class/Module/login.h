#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QTcpSocket>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent);
    void processInfo(QTcpSocket *socket, const QString &text);

private:
    void myWrite(QTcpSocket *socket, const QString &title, const QString &text);

private slots:
    void f_login(QTcpSocket *socket, const QString &text);
    void f_register(QTcpSocket *socket, const QString &text);

signals:
    void s_write(QTcpSocket *socket, const QString &title, const QString &text);
};

#endif // LOGIN_H
