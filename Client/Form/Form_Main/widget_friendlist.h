#ifndef WIDGET_FRIENDLIST_H
#define WIDGET_FRIENDLIST_H

#include <QWidget>
#include <QPushButton>
#include "Class/Service/friends_service.h"
#include "Class/Service/chat_service.h"
#include "Class/Transfer/noaname.h"

namespace Ui {
class Widget_FriendList;
}

class Widget_FriendList : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_FriendList(QWidget *parent);
    ~Widget_FriendList();
    void setServiceFriends(Friends_Service *friends);
    void setServiceChat(Chat_Service *chat);

private:
    Ui::Widget_FriendList *ui;
    Friends_Service *friends;
    Chat_Service *chat;

private:
    void initBtns();
    QPushButton *newBtn(const QString &title);

private slots:
    void newFriend(const NoAName &myFriend);
};

#endif // WIDGET_FRIENDLIST_H
