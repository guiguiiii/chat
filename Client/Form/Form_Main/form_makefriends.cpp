#include "form_makefriends.h"
#include "ui_form_makefriends.h"

#include "Form/Common/widget_tips.h"

Form_MakeFriends::Form_MakeFriends(QWidget *parent, Friends_Service *friends) :
    QWidget(parent),
    ui(new Ui::Form_MakeFriends)
{
    ui->setupUi(this);
    this->friends = friends;
    connect(friends, &Friends_Service::s_makeFriends, this, &Form_MakeFriends::f_makeFriends);

    ui->le_no->setFocus();
}


Form_MakeFriends::~Form_MakeFriends()
{
    delete ui;
}


void Form_MakeFriends::f_makeFriends(int state)
{
    if(state == 1){
        QString text = "好友申请发送成功";
        Widget_Tips *widget_tips = new Widget_Tips(this,text);
        connect(widget_tips, &Widget_Tips::destroyed, this, &Form_MakeFriends::deleteLater);
        widget_tips->setVisible(1);
    }else if(state == 2){
        (new Widget_Tips(this,"该账号不存在"))->setVisible(1);
    }else if(state == 3){
        (new Widget_Tips(this,"已与对方互为好友"))->setVisible(1);
    }
}


void Form_MakeFriends::on_btn_close_clicked()
{
    this->deleteLater();
}


void Form_MakeFriends::on_btn_send_clicked()
{
    QString no = ui->le_no->text();
    QString mail = ui->te_mail->toPlainText();
    friends->makeFriends(no,mail);
}

