#include "chat_socket.h"

Chat_Socket::Chat_Socket(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->socket = socket;
    connect(socket, &Socket::s_chat, this, &Chat_Socket::readyRead);
}


void Chat_Socket::myMessages()
{
    this->myWrite("MYMESSAGES","");
}


void Chat_Socket::sendMessage(const Message &message)
{
    QString str ="";
    str = str + message.sender() + "splitA";
    str = str + message.receiver() + "splitA";
    str = str + message.date() + "splitA";
    str = str + message.text();
    this->myWrite("SENDMESSAGE",str);
}


void Chat_Socket::myWrite(const QString &title, const QString &text)
{
    QString str ="";
    str = str + title + "splitZ" + text;
    socket->write("CHAT",str);
}


void Chat_Socket::readyRead(const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYMESSAGES"){
        this->f_myMessages(back);
    }else if(front == "RECEIVEMESSAGE"){
        this->f_receiveMessage(back);
    }
}


void Chat_Socket::f_myMessages(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    QVector<Message> messages;
    for(int i=0; i<splitA.size(); i++){
        QVector<QString> splitB = splitA.at(i).split("splitB");
        if(splitB.size() != 4){
            continue;
        }

        Message message;
        message.setSender(splitB.at(0));
        message.setReceiver(splitB.at(1));
        message.setDate(splitB.at(2));
        message.setText(splitB.at(3));
        messages.push_back(message);
    }

    emit s_myMessages(messages);
}


void Chat_Socket::f_receiveMessage(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 4){
        return;
    }

    Message message;
    message.setSender(splitA.at(0));
    message.setReceiver(splitA.at(1));
    message.setDate(splitA.at(2));
    message.setText(splitA.at(3));
    emit s_receiveMessage(message);
}

