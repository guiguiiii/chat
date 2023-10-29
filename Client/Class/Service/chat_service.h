#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include <QObject>
#include "Class/DataAccess/chat_socket.h"
#include "Class/Service/friends_service.h"
#include "Class/Data/info.h"
#include "Class/Transfer/noaname.h"

class Chat_Service : public QObject
{
    Q_OBJECT
public:
    explicit Chat_Service(QObject *parent, Socket *socket);
    void setMyInfo(const Info &info);
    void setFriends(Friends_Service *friends);
    QString myNo();

    void sendMessage(const QString &text);
    void setCurrentFrd(const NoAName &NoAName);

private:
    Chat_Socket *chat_socket;
    Info info;
    NoAName currentFrd;

private slots:
    void f_myMessages(const QVector<Message> &messages);
    void f_receiveMessage(const Message &message);

signals:
    void s_initSuccess();
    void s_setMessages(const QPixmap &myHead, const QPixmap &frdHead, const QVector<Message> &messages);
    void s_appendMessage(const QPixmap &head, const Message &message);
    void s_lockLineEdit(bool lock);
};

#endif // CHAT_SERVICE_H
