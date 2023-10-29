#ifndef FRIEND_SOCKET_H
#define FRIEND_SOCKET_H

#include <QObject>
#include "Class/socket.h"
#include "Class/Data/friend.h"

class Friend_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Friend_Socket(QObject *parent, Socket *socket);

    void myFriends();
    void setNickname(const QString &no, const QString &nickName);
    void makeFriends(const QString &no, const QString &mail);
    void unFriend(const QString &no);
    void respond(const QString &no, bool accapt);

private:
    Socket *socket;
    void myWrite(const QString &title, const QString &text);

private slots:
    void readyRead(const QString &text);
    void f_myFriends(const QString &text);
    void f_newFriend(const QString &text);

signals:
    void s_myFriends(const QVector<Friend> &friends);
    void s_makeFriends(int state);
    void s_newFriend(const Friend &ffriend);
    void s_unFriend(const QString &no);
};

#endif // FRIEND_SOCKET_H
