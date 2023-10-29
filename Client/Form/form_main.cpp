#include "form_main.h"
#include "ui_form_main.h"

#include <QMimeData>
#include "Form_Main/form_myinfo.h"
#include "Form_Main/form_mail.h"
#include "Form_Main/form_myfriends.h"
#include "Form_Main/form_makefriends.h"
#include "Form_Main/Common/widget_head.h"

Form_Main::Form_Main(QWidget *parent, Socket *socket) :
    QWidget(parent),
    ui(new Ui::Form_Main)
{
    ui->setupUi(this);
    this->setAcceptDrops(1);
    this->lockLineEdit(1);

    this->socket = socket;

    connect(ui->Group_Chat, &Widget_Chat::s_showHead, this, [=](const QPixmap &head){ (new Widget_Head(this,head))->setVisible(1); });

    chat = new Chat_Service(this,socket);
    connect(chat, &Chat_Service::s_initSuccess, this, &Form_Main::initChat);
    connect(chat, &Chat_Service::s_lockLineEdit, this, &Form_Main::lockLineEdit);

    personal = new Personal_Service(this,socket);
    connect(personal, &Personal_Service::s_initSuccess, this, &Form_Main::initInfo);
    connect(personal, &Personal_Service::s_infoChanged, this, &Form_Main::initInfo);
    personal->initInfo();

    friends = new Friends_Service(this,socket);
    connect(friends, &Friends_Service::s_initSuccess, this, &Form_Main::initFriends);
    friends->initFriends();
}


Form_Main::~Form_Main()
{
    delete ui;
}


void Form_Main::initInfo()
{
    Info info = personal->myInfo();
    ui->lb_head->setPixmap(info.head());
    ui->lb_name->setText(info.name());
    chat->setMyInfo(info);
    if(personal != nullptr and friends != nullptr and chat != nullptr){
        ui->widget->setVisible(0);
    }
}


void Form_Main::initFriends()
{
    chat->setFriends(friends);
    ui->Group_FriendList->setServiceFriends(friends);
    if(personal != nullptr and friends != nullptr and chat != nullptr){
        ui->widget->setVisible(0);
    }
}


void Form_Main::initChat()
{
    ui->Group_Chat->setService(chat);
    ui->Group_FriendList->setServiceChat(chat);
    if(personal != nullptr and friends != nullptr and chat != nullptr){
        ui->widget->setVisible(0);
    }
}


void Form_Main::lockLineEdit(bool lock)
{
    if(lock){
        ui->le_send->setReadOnly(1);
        ui->le_send->setText("  请选择一位好友以开启聊天");
    }else{
        ui->le_send->setReadOnly(0);
        ui->le_send->setText("");
        ui->le_send->setFocus();
    }
}


void Form_Main::on_btn_Info_clicked()
{
    (new Form_MyInfo(this,personal))->setVisible(1);
}


void Form_Main::on_btn_myFriends_clicked()
{
    (new Form_MyFriends(this,friends))->setVisible(1);
}


void Form_Main::on_btn_mail_clicked()
{
    (new Form_Mail(this,socket,friends))->setVisible(1);
}


void Form_Main::on_btn_makeFriends_clicked()
{
    (new Form_MakeFriends(this,friends))->setVisible(1);
}


void Form_Main::on_btn_send_clicked()
{
    if(ui->le_send->isReadOnly() == false){
        QString text = ui->le_send->text();
        ui->le_send->clear();
        ui->le_send->setFocus();
        chat->sendMessage(text);
    }
}


void Form_Main::on_le_send_returnPressed()
{
    this->on_btn_send_clicked();
}

