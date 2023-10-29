#ifndef CHAT_SOCKET_H
#define CHAT_SOCKET_H

#include <QObject>
#include "Class/socket.h"
#include "Class/Data/message.h"

class Chat_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Chat_Socket(QObject *parent, Socket *socket);

    void myMessages();
    void sendMessage(const Message &message);

private:
    Socket *socket;
    void myWrite(const QString &title, const QString &text);

private slots:
    void readyRead(const QString &text);
    void f_myMessages(const QString &text);
    void f_receiveMessage(const QString &text);

signals:
    void s_myMessages(const QVector<Message> &messages);
    void s_receiveMessage(const Message &message);
};

#endif // CHAT_SOCKET_H
