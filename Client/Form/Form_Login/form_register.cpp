#include "form_register.h"
#include "ui_form_register.h"

#include "Form/Common/widget_tips.h"
#include "Form/Common/widget_wait.h"

Form_Register::Form_Register(QWidget *parent, Login_Socket *login) :
    QWidget(parent),
    ui(new Ui::Form_Register)
{
    ui->setupUi(this);
    ui->le_no->setFocus();

    this->login = login;
    connect(login, &Login_Socket::s_register, this, &Form_Register::f_register);
}


Form_Register::~Form_Register()
{
    delete ui;
}


void Form_Register::f_register(int state)
{
    if(state == 1){
        Widget_Tips *widget_tips = new Widget_Tips(this,"注册成功！");
        connect(widget_tips, &Widget_Tips::destroyed, this, &Form_Register::deleteLater);
        widget_tips->setVisible(1);
        QVector<QString> noAPwd;
        noAPwd.push_back(ui->le_no->text());
        noAPwd.push_back(ui->le_pwd->text());
        emit success(noAPwd);
    }else if(state == 2){
        (new Widget_Tips(this,"该账号被注册"))->setVisible(1);
    }
    emit closeWaitWidget();
}


void Form_Register::on_btn_cancel_clicked()
{
    emit cancel();
    this->deleteLater();
}


void Form_Register::on_btn_submit_clicked()
{
    QString no = ui->le_no->text();
    QString pwd = ui->le_pwd->text();
    QString pwd2 = ui->le_pwd2->text();
    QString name = ui->le_name->text();
    if(no.size() == 0){
        (new Widget_Tips(this,"账号不能为空"))->setVisible(1);
    }else if(pwd.size() == 0 or pwd2.size() == 0){
        (new Widget_Tips(this,"密码不能为空"))->setVisible(1);
    }else if(name.size() == 0){
        (new Widget_Tips(this,"名字不能为空"))->setVisible(1);
    }else if(pwd != pwd2){
        (new Widget_Tips(this,"两次输入的密码不一致"))->setVisible(1);
    }else if(no.size() > 12){
        (new Widget_Tips(this,"输入的账号过长"))->setVisible(1);
    }else if(pwd.size() > 18){
        (new Widget_Tips(this,"输入的密码过长"))->setVisible(1);
    }else if(name.size() > 10){
        (new Widget_Tips(this,"输入的名字过长"))->setVisible(1);
    }else{
        Widget_Wait *widget_wait = new Widget_Wait(this);
        connect(this, &Form_Register::closeWaitWidget, widget_wait, &Widget_Wait::deleteLater);
        widget_wait->setVisible(1);
        login->Register(no,pwd,name);
    }
}


void Form_Register::on_le_name_returnPressed()
{
    this->on_btn_submit_clicked();
}

