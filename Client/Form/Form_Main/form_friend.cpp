#include "form_friend.h"
#include "ui_form_friend.h"

#include "Form/Common/widget_tips.h"
#include "Form/Common/widget_choose.h"
#include "Form/Common/widget_wait.h"

Form_Friend::Form_Friend(QWidget *parent, Friends_Service *friends, const QString &no) :
    QWidget(parent),
    ui(new Ui::Form_Friend)
{
    ui->setupUi(this);
    this->no = no;
    this->friends = friends;
    connect(friends, &Friends_Service::s_unFriend, this, &Form_Friend::f_unFriend);
    this->initForm();
}


Form_Friend::~Form_Friend()
{
    delete ui;
}


void Form_Friend::initForm()
{
    Friend myFriend(friends->myFriend(no));
    ui->no->setText(myFriend.no());
    ui->name->setText(myFriend.name());
    ui->signature->setText(myFriend.signature());
    ui->le_nickname->setText(myFriend.nickname());
}


void Form_Friend::f_unFriend(const QString &no)
{
    if(this->no == no){
        QString text = "与对方的好友关系已断开";
        Widget_Tips *widget_tips = new Widget_Tips(this,text);
        connect(widget_tips, &Widget_Tips::destroyed, this, &Form_Friend::deleteLater);
        widget_tips->setVisible(1);
        emit closeWaitWidget();
    }
}


void Form_Friend::on_btn_close_clicked()
{
    QString nickname2 = ui->le_nickname->text();
    if(nickname2 != nickname){
        friends->setNickname(no,nickname2);
    }
    this->deleteLater();
}


void Form_Friend::on_btn_unFriend_clicked()
{
    QString text = "是否删除该好友";
    Widget_Choose *widget_choose = new Widget_Choose(this,"好友",text);
    connect(widget_choose, &Widget_Choose::confirm, this, [=](){
        Widget_Wait *widget_wait = new Widget_Wait(this);
        connect(this, &Form_Friend::closeWaitWidget, widget_wait, &Widget_Wait::deleteLater);
        widget_wait->setVisible(1);
        friends->unFriend(no);
    });
    widget_choose->setVisible(1);
}

