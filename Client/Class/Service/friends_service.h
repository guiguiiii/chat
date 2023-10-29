#ifndef FRIENDS_SERVICE_H
#define FRIENDS_SERVICE_H

#include <QObject>
#include "Class/Transfer/noaname.h"
#include "Class/DataAccess/friend_socket.h"

class Friends_Service : public QObject
{
    Q_OBJECT

public:
    explicit Friends_Service(QObject *parent, Socket *socket);

    void initFriends();
    Friend myFriend(const QString &no);
    void setNickname(const QString &no, const QString &nickName);
    void makeFriends(const QString &no, const QString &mail);
    void unFriend(const QString &no);
    void respond(const QString &no, bool accapt);
    QVector<NoAName> friendList();
    QVector<NoAName> chatList();

private:
    Friend_Socket *friend_socket;
    QVector<Friend> friends;

private slots:
    void f_myFriends(const QVector<Friend> &friends);
    void f_newFriend(const Friend &ffriend);
    void f_unFriend(const QString &no);

signals:
    void s_initSuccess();
    void s_makeFriends(int state);
    void s_newFriend(const NoAName &noAName);
    void s_unFriend(const QString &no);
};

#endif // FRIENDS_SERVICE_H
