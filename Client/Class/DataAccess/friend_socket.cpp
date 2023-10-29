#include "friend_socket.h"

#include "Class/Common/common.h"

Friend_Socket::Friend_Socket(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->socket = socket;
    connect(socket, &Socket::s_friends, this, &Friend_Socket::readyRead);
}


void Friend_Socket::myFriends()
{
    this->myWrite("MYFRIENDS","");
}


void Friend_Socket::setNickname(const QString &no, const QString &nickName)
{
    QString text = "";
    text = text + no + "splitA" + nickName;
    this->myWrite("SETNICKNAME",text);
}


void Friend_Socket::makeFriends(const QString &no, const QString &mail)
{
    QString text = "";
    text = text + no + "splitA" + mail;
    this->myWrite("MAKEFRIENDS",text);
}


void Friend_Socket::unFriend(const QString &no)
{
    QString text = "";
    text = text + no;
    this->myWrite("UNFRIEND",text);
}


void Friend_Socket::respond(const QString &no, bool accapt)
{
    QString text = "";
    text = text + no + "splitA" + QString::number(accapt);
    this->myWrite("RESPOND",text);
}


void Friend_Socket::myWrite(const QString &title, const QString &text)
{
    QString str ="";
    str = str + title + "splitZ" + text;
    socket->write("FRIENDS",str);
}


void Friend_Socket::readyRead(const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYFRIENDS"){
        this->f_myFriends(back);
    }else if(front == "MAKEFRIENDS"){
        emit s_makeFriends(back.toInt());
    }else if(front == "NEWFRIEND"){
        this->f_newFriend(back);
    }else if(front == "UNFRIEND"){
        emit s_unFriend(back);
    }
}


void Friend_Socket::f_myFriends(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    QVector<Friend> friends;
    for(int i=0; i<splitA.size(); i++){
        QVector<QString> splitB = splitA.at(i).split("splitB");
        if(splitB.size() != 5){
            continue;
        }

        Friend ffriend;
        ffriend.setNo(splitB.at(0));
        ffriend.setName(splitB.at(1));
        ffriend.setSignature(splitB.at(2));
        ffriend.setNickname(splitB.at(3));
        ffriend.setHead(Common().strToPix(splitB.at(4)));
        friends.push_back(ffriend);
    }

    emit s_myFriends(friends);
}


void Friend_Socket::f_newFriend(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 5){
        return;
    }

    Friend ffriend;
    ffriend.setNo(splitA.at(0));
    ffriend.setName(splitA.at(1));
    ffriend.setSignature(splitA.at(2));
    ffriend.setNickname(splitA.at(3));
    ffriend.setHead(Common().strToPix(splitA.at(4)));

    emit s_newFriend(ffriend);
}

