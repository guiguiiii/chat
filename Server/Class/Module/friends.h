#ifndef FRIENDS_H
#define FRIENDS_H

#include <QObject>
#include <QTcpSocket>

class Friends : public QObject
{
    Q_OBJECT
public:
    explicit Friends(QObject *parent);
    void processInfo(QTcpSocket *socket, const QString &text);

private:
    void myWrite(QTcpSocket *socket, const QString &title, const QString &text);

private slots:
    void f_myFriends(QTcpSocket *socket);
    void f_setNickname(QTcpSocket *socket, const QString &text);
    void f_makeFriends(QTcpSocket *socket, const QString &text);
    void f_unFriend(QTcpSocket *socket, const QString &text);
    void f_respond(QTcpSocket *socket, const QString &text);

signals:
    void s_write(QTcpSocket *socket, const QString &title, const QString &text);

    //特殊函数，发送其他模块的信息
private:
    void sendNewMail(QTcpSocket *socket, const QString &mailNo = "-1");
};

#endif // FRIENDS_H
