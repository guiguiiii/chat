#include "form_myinfo.h"
#include "ui_form_myinfo.h"

#include "Common/widget_head.h"
#include "Form_MyInfo/widget_sethead.h"
#include "Form/Common/widget_tips.h"

Form_MyInfo::Form_MyInfo(QWidget *parent, Personal_Service *personal) :
    QWidget(parent),
    ui(new Ui::Form_MyInfo)
{
    ui->setupUi(this);
    this->personal = personal;
    connect(personal, &Personal_Service::s_setMyInfo, this, &Form_MyInfo::f_setMyInfo);
    this->initForm();
}


Form_MyInfo::~Form_MyInfo()
{
    delete ui;
}


void Form_MyInfo::initForm()
{
    Info info = personal->myInfo();
    ui->le_no->setText(info.no());
    ui->le_pwd->setText(info.pwd());
    ui->le_name->setText(info.name());
    ui->te_signature->setText(info.signature());
    ui->lb_head->setPixmap(info.head());
}


void Form_MyInfo::f_setMyInfo(int state)
{
    if(state == 1){
        Widget_Tips *widget_tips = new Widget_Tips(this,"设置成功！");
        connect(widget_tips, &Widget_Tips::destroyed, this, &Form_MyInfo::deleteLater);
        widget_tips->setVisible(1);
    }else if(state == 2){
        (new Widget_Tips(this,"该账号已被使用"))->setVisible(1);
    }
}


void Form_MyInfo::on_btn_cancel_clicked()
{
    this->deleteLater();
}


void Form_MyInfo::on_btn_head_clicked()
{
    QPixmap head = ui->lb_head->pixmap();
    (new Widget_Head(this,head))->setVisible(1);
}


void Form_MyInfo::on_btn_setHead_clicked()
{
    Widget_SetHead *widget_setHead = new Widget_SetHead(this);
    connect(widget_setHead, &Widget_SetHead::setHead, this, [=](const QPixmap &head){
        ui->lb_head->setPixmap(head);
    });
    widget_setHead->setVisible(1);
}


void Form_MyInfo::on_btn_confirm_clicked()
{
    QString no = ui->le_no->text();
    QString pwd = ui->le_pwd->text();
    QString name = ui->le_name->text();
    QString signature = ui->te_signature->toPlainText();
    if(no.size() == 0){
        (new Widget_Tips(this,"账号不能为空"))->setVisible(1);
    }else if(pwd.size() == 0){
        (new Widget_Tips(this,"密码不能为空"))->setVisible(1);
    }else if(name.size() == 0){
        (new Widget_Tips(this,"名字不能为空"))->setVisible(1);
    }else if(no.size() > 12){
        (new Widget_Tips(this,"输入的账号过长"))->setVisible(1);
    }else if(pwd.size() > 18){
        (new Widget_Tips(this,"输入的密码过长"))->setVisible(1);
    }else if(name.size() > 10){
        (new Widget_Tips(this,"输入的名字过长"))->setVisible(1);
    }else if(signature.size() > 100){
        (new Widget_Tips(this,"输入的签名过长"))->setVisible(1);
    }else{
        Info info;
        info.setNo(no);
        info.setPWD(pwd);
        info.setName(name);
        info.setSignature(signature);
        info.setHead(ui->lb_head->pixmap());
        personal->setMyInfo(info);
    }
}

