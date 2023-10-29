#include "friends_service.h"

Friends_Service::Friends_Service(QObject *parent, Socket *socket)
    : QObject{parent}
{
    friend_socket = new Friend_Socket(this,socket);
    connect(friend_socket, &Friend_Socket::s_myFriends, this, &Friends_Service::f_myFriends);
    connect(friend_socket, &Friend_Socket::s_makeFriends, this, &Friends_Service::s_makeFriends);
    connect(friend_socket, &Friend_Socket::s_newFriend, this, &Friends_Service::f_newFriend);
    connect(friend_socket, &Friend_Socket::s_unFriend, this, &Friends_Service::f_unFriend);
}


void Friends_Service::initFriends()
{
    friend_socket->myFriends();
}


Friend Friends_Service::myFriend(const QString &no)
{
    for(int i=0; i<friends.size(); i++){
        if(friends.at(i).no() == no){
            return friends.at(i);
        }
    }
    return Friend();
}


void Friends_Service::setNickname(const QString &no, const QString &nickName)
{
    friend_socket->setNickname(no,nickName);
    for(int i=0; i<friends.size(); i++){
        if(friends.at(i).no() == no){
            friends[i].setNickname(nickName);
            break;
        }
    }
}


void Friends_Service::makeFriends(const QString &no, const QString &mail)
{
    friend_socket->makeFriends(no,mail);
}


void Friends_Service::unFriend(const QString &no)
{
    friend_socket->unFriend(no);
}


void Friends_Service::respond(const QString &no, bool accapt)
{
    friend_socket->respond(no,accapt);
}


QVector<NoAName> Friends_Service::friendList()
{
    QVector<NoAName> noANames;
    for(int i=0; i<friends.size(); i++){
        NoAName noAName;
        noAName.setNo(friends.at(i).no());
        noAName.setName(friends.at(i).name());
        noAName.setHead(friends.at(i).head());
        noANames.push_back(noAName);
    }

    return noANames;
}


QVector<NoAName> Friends_Service::chatList()
{
    QVector<NoAName> noANames;
    for(int i=0; i<friends.size(); i++){
        NoAName noAName;
        noAName.setNo(friends.at(i).no());
        noAName.setName(friends.at(i).name());
        noAName.setHead(friends.at(i).head());
        noANames.push_back(noAName);
    }

    return noANames;
}


void Friends_Service::f_myFriends(const QVector<Friend> &friends)
{
    this->friends = friends;
    emit s_initSuccess();
}


void Friends_Service::f_newFriend(const Friend &ffriend)
{
    friends.append(ffriend);
    NoAName noAName;
    noAName.setNo(ffriend.no());
    noAName.setName(ffriend.name());
    noAName.setHead(ffriend.head());
    emit s_newFriend(noAName);
}


void Friends_Service::f_unFriend(const QString &no)
{
    for(int i=0; i<friends.size(); i++){
        if(friends.at(i).no() == no){
            friends.removeAt(i);
            break;
        }
    }
    emit s_unFriend(no);
}

