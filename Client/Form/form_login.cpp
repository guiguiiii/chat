#include "form_login.h"
#include "ui_form_login.h"

#include "form_main.h"
#include "Form_Login/form_register.h"
#include "Common/widget_tips.h"
#include "Common/widget_wait.h"

Form_Login::Form_Login(QWidget *parent,Socket *socket) :
    QWidget(parent),
    ui(new Ui::Form_Login)
{
    ui->setupUi(this);
    ui->le_no->setFocus();

    this->socket = socket;
    connect(socket, &Socket::disconnected, this, &Form_Login::deleteLater);

    this->login = new Login_Socket(this,socket);
    connect(login, &Login_Socket::s_login, this, &Form_Login::f_login);
}


Form_Login::~Form_Login()
{
    delete ui;
}


void Form_Login::f_login(int state)
{
    if(state == 1){
        (new Form_Main(this,socket))->setVisible(1);
    }else if(state == 2){
        (new Widget_Tips(this,"账号与密码不匹配"))->setVisible(1);
    }else if(state == 3){
        (new Widget_Tips(this,"账号不存在"))->setVisible(1);
    }
    emit closeWaitWidget();
}


void Form_Login::on_btn_exit_clicked()
{
    this->parent()->parent()->parent()->deleteLater();
}


void Form_Login::on_btn_login_clicked()
{
    QString no = ui->le_no->text();
    QString pwd = ui->le_pwd->text();
    if(no.size() == 0){
        (new Widget_Tips(this,"账号不能为空"))->setVisible(1);
    }else if(pwd.size() == 0){
        (new Widget_Tips(this,"密码不能为空"))->setVisible(1);
    }else if(no.size() > 12){
        (new Widget_Tips(this,"输入的账号过长"))->setVisible(1);
    }else if(pwd.size() > 18){
        (new Widget_Tips(this,"输入的密码过长"))->setVisible(1);
    }else{
        Widget_Wait *widget_wait = new Widget_Wait(this);
        connect(this, &Form_Login::closeWaitWidget, widget_wait, &Widget_Wait::deleteLater);
        widget_wait->setVisible(1);
        login->login(no,pwd);
    }
}


void Form_Login::on_le_no_returnPressed()
{
    ui->le_pwd->setFocus();
}


void Form_Login::on_le_pwd_returnPressed()
{
    this->on_btn_login_clicked();
}


void Form_Login::on_btn_register_clicked()
{
    Form_Register *form_register = new Form_Register(this,login);

    //注册取消后，焦点重新放在账号输入框上
    connect(form_register, &Form_Register::cancel, this, [=](){
        ui->le_no->setFocus();
    });

    //注册成功，输入框自动填写注册界面内的账号密码
    connect(form_register, &Form_Register::success, this, [=](const QVector<QString> &noAPwd){
        ui->le_no->setText(noAPwd.front());
        ui->le_pwd->setText(noAPwd.back());
    });

    form_register->setVisible(1);
}

