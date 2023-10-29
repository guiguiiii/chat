#include "chat_service.h"

#include <QDateTime>
#include "Class/DataAccess/myfile.h"

Chat_Service::Chat_Service(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->chat_socket = new Chat_Socket(this,socket);
    connect(chat_socket, &Chat_Socket::s_myMessages, this, &Chat_Service::f_myMessages);
    connect(chat_socket, &Chat_Socket::s_receiveMessage, this, &Chat_Service::f_receiveMessage);
}


void Chat_Service::setMyInfo(const Info &info)
{
    this->info = info;
    MyFile().initMessageDir(info.no());
    chat_socket->myMessages();
}


void Chat_Service::setFriends(Friends_Service *friends)
{
    connect(friends, &Friends_Service::s_unFriend, this, [=](const QString &no){
        if(currentFrd.no() == no){
            emit s_lockLineEdit(1);
            emit s_setMessages(QPixmap(),QPixmap(),QVector<Message>());
        }
    });
}


QString Chat_Service::myNo()
{
    return info.no();
}


void Chat_Service::sendMessage(const QString &text)
{
    if(text == ""){
        return;
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm");
    Message message;
    message.setSender(info.no());
    message.setReceiver(currentFrd.no());
    message.setDate(time);
    message.setText(text);
    chat_socket->sendMessage(message);
    MyFile().appendMessage(info.no(),message);
    if(currentFrd.no() != ""){
        emit s_appendMessage(info.head(),message);
    }
}


void Chat_Service::setCurrentFrd(const NoAName &myFriend)
{
    this->currentFrd = myFriend;
    QVector<Message> messages = MyFile().getMessages(info.no(),currentFrd.no());
    emit s_setMessages(info.head(),currentFrd.head(),messages);
    emit s_lockLineEdit(0);
}


void Chat_Service::f_myMessages(const QVector<Message> &messages)
{
    for(int i=0; i<messages.size(); i++){
        MyFile().appendMessage(info.no(),messages.at(i));
    }
    emit s_initSuccess();
}


void Chat_Service::f_receiveMessage(const Message &message)
{
    MyFile().appendMessage(info.no(),message);
    if(currentFrd.no() == message.sender()){
        emit s_appendMessage(currentFrd.head(),message);
    }
}

