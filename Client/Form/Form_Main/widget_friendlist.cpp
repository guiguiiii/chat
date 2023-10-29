#include "widget_friendlist.h"
#include "ui_widget_friendlist.h"

#include <QLayout>

Widget_FriendList::Widget_FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_FriendList)
{
    ui->setupUi(this);
}


Widget_FriendList::~Widget_FriendList()
{
    delete ui;
}


void Widget_FriendList::setServiceFriends(Friends_Service *friends)
{
    this->friends = friends;
    connect(friends, &Friends_Service::s_newFriend, this, &Widget_FriendList::newFriend);
    this->initBtns();
}


void Widget_FriendList::setServiceChat(Chat_Service *chat)
{
    this->chat = chat;
}


void Widget_FriendList::initBtns()
{
    QVector<NoAName> noANames(friends->chatList());
    for(int i=0; i<noANames.size(); i++){
        this->newFriend(noANames.at(i));
    }
}


void Widget_FriendList::newFriend(const NoAName &noAName)
{
    QPushButton *btn = newBtn(noAName.name());
    connect(btn, &QPushButton::clicked, this, [=](){
        chat->setCurrentFrd(noAName);
    });
    connect(friends, &Friends_Service::s_unFriend, this, [=](const QString &no){
        if(noAName.no() == no){
            btn->deleteLater();
        }
    });
}


QPushButton *Widget_FriendList::newBtn(const QString &title)
{
    QPushButton *btn = new QPushButton(ui->sawc);
    btn->setFixedSize(191,51);
    btn->setText(title);

    ui->sawc->layout()->addWidget(btn);
    ui->sawc->layout()->removeItem(ui->spacer);
    ui->sawc->layout()->addItem(ui->spacer);

    return btn;
}

