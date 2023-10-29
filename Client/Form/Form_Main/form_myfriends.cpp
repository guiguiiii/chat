#include "form_myfriends.h"
#include "ui_form_myfriends.h"

#include <QWidget>
#include <QLayout>
#include "Common/widget_head.h"
#include "form_friend.h"

Form_MyFriends::Form_MyFriends(QWidget *parent, Friends_Service *friends) :
    QWidget(parent),
    ui(new Ui::Form_MyFriends)
{
    ui->setupUi(this);
    this->friends = friends;
    connect(friends, &Friends_Service::s_newFriend, this, &Form_MyFriends::newBtn);
    this->initBtns();
}


Form_MyFriends::~Form_MyFriends()
{
    delete ui;
}


void Form_MyFriends::on_btn_back_clicked()
{
    this->deleteLater();
}


void Form_MyFriends::initBtns()
{
    QVector<NoAName> noANames(friends->friendList());
    for(int i=0; i<noANames.size(); i++){
        this->newBtn(noANames.at(i));
    }
}


void Form_MyFriends::newBtn(const NoAName &noAName)
{
    QWidget *widget = new QWidget(ui->Main_sawc);
    widget->setFixedSize(601,71);
    widget->setStyleSheet(".QWidget{ border: none; }");
    widget->setVisible(1);

    QPushButton *btn = new QPushButton(widget);
    btn->setFixedSize(601,71);
    connect(btn, &QPushButton::clicked, this, [=](){ this->friend_clicked(noAName.no()); });
    btn->setVisible(1);

    QLabel *name = new QLabel(widget);
    name->setFixedSize(251,51);
    name->move(85,10);
    name->setText(noAName.name());
    name->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    name->setVisible(1);

    QLabel *lb_head = new QLabel(widget);
    lb_head->setFixedSize(60,60);
    lb_head->move(10,5);
    lb_head->setScaledContents(1);
    lb_head->setPixmap(noAName.head());
    lb_head->setStyleSheet("border-radius: 30px;");
    lb_head->setVisible(1);

    QPushButton *btn_head = new QPushButton(widget);
    btn_head->setFixedSize(60,60);
    btn_head->move(10,5);
    btn_head->setStyleSheet("background-color: transparent; border-radius: 30px;");
    connect(btn_head, &QPushButton::clicked, this, [=](){ (new Widget_Head(this,noAName.head()))->setVisible(1); });
    btn_head->setVisible(1);

    ui->Main_sawc->layout()->addWidget(widget);
    ui->Main_sawc->layout()->removeItem(ui->spacer);
    ui->Main_sawc->layout()->addItem(ui->spacer);

    connect(friends, &Friends_Service::s_unFriend, this, [=](const QString &no){
        if(noAName.no() == no){
            widget->deleteLater();
        }
    });
}


void Form_MyFriends::friend_clicked(const QString &no)
{
    (new Form_Friend(this,friends,no))->setVisible(1);
}

