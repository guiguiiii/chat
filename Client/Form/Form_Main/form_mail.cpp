#include "form_mail.h"
#include "ui_form_mail.h"

#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QTextBrowser>
#include "Form/Common/widget_tips.h"
#include "Form/Common/widget_choose.h"

Form_Mail::Form_Mail(QWidget *parent, Socket *socket, Friends_Service *friends) :
    QWidget(parent),
    ui(new Ui::Form_Mail)
{
    ui->setupUi(this);
    this->friends = friends;
    this->myMail = new Mail_Socket(this,socket);
    connect(myMail, &Mail_Socket::s_myMails, this, &Form_Mail::f_myMails);
    connect(myMail, &Mail_Socket::s_newMail, this, &Form_Mail::f_newMail);
    myMail->myMails();
}


Form_Mail::~Form_Mail()
{
    delete ui;
}


void Form_Mail::f_myMails(const QVector<Mail> &mails)
{
    for(int i=0; i<mails.size(); i++){
        this->f_newMail(mails.at(i));
    }
}


void Form_Mail::f_newMail(const Mail &mail)
{
    QWidget *widget = new QWidget(ui->sawc);
    widget->setFixedSize(201,70);
    widget->setStyleSheet(".QWidget{ border: none; }");

    QLabel *time = new QLabel(widget);
    time->setFixedSize(201,20);
    time->setText(mail.date().mid(5));
    time->setStyleSheet("Font: 17pt;");
    time->setAlignment(Qt::AlignCenter);

    QPushButton *btn = new QPushButton(widget);
    btn->setFixedSize(201,50);
    btn->move(0,20);
    btn->setText(mail.title());
    if(mail.title().size() >= 5){
        btn->setStyleSheet("border-radius: 20px; font: 20pt;");
    }else{
        btn->setStyleSheet("border-radius: 20px;");
    }
    connect(btn, &QPushButton::clicked, this, [=](){ this->mailSelected(mail); });

    ui->sawc->layout()->addWidget(widget);
    ui->sawc->layout()->removeItem(ui->spacer);
    ui->sawc->layout()->addItem(ui->spacer);

    connect(this, &Form_Mail::s_removeMail, this, [=](int no){
        if(mail.no() == no){
            widget->deleteLater();
        }
    });
}


void Form_Mail::f_makeFriends(const Mail &mail)
{
    QPushButton *btn_accept = new QPushButton(ui->Group_Text);
    btn_accept->setFixedSize(120,50);
    btn_accept->move(180,420);
    btn_accept->setText("接受");
    btn_accept->setStyleSheet("border-radius: 20px;");

    QPushButton *btn_reject = new QPushButton(ui->Group_Text);
    btn_reject->setFixedSize(120,50);
    btn_reject->move(30,420);
    btn_reject->setText("拒绝");
    btn_reject->setStyleSheet("border-radius: 20px;");

    connect(this, &Form_Mail::clearWidgets, btn_accept, &QPushButton::deleteLater);
    connect(this, &Form_Mail::clearWidgets, btn_reject, &QPushButton::deleteLater);
    connect(btn_accept, &QPushButton::clicked, this, [=](){
        Widget_Tips *widget_tips = new Widget_Tips(this,"回复成功");
        connect(widget_tips, &Widget_Tips::destroyed, this, [=](){
            emit clearWidgets();
            myMail->removeMail(mail.no());
            emit s_removeMail(mail.no());
        });
        widget_tips->setVisible(1);
        friends->respond(mail.sender(),1);
    });
    connect(btn_reject, &QPushButton::clicked, this, [=](){
        Widget_Tips *widget_tips = new Widget_Tips(this,"已拒绝申请");
        connect(widget_tips, &Widget_Tips::destroyed, this, [=](){
            emit clearWidgets();
            myMail->removeMail(mail.no());
            emit s_removeMail(mail.no());
        });
        widget_tips->setVisible(1);
        friends->respond(mail.sender(),0);
    });

    btn_accept->setVisible(1);
    btn_reject->setVisible(1);
}


void Form_Mail::mailSelected(const Mail &mail)
{
    emit clearWidgets();
    QLabel *title = new QLabel(ui->Group_Text);
    title->setFixedSize(441,40);
    title->move(20,20);
    title->setText(mail.title());
    title->setStyleSheet("Font: 32pt;");
    title->setVisible(1);

    QLabel *sender = new QLabel(ui->Group_Text);
    sender->setFixedSize(441,30);
    sender->move(20,65);
    sender->setText("来自： " + mail.sender());
    sender->setStyleSheet("Font: 23pt;");
    sender->setVisible(1);

    QLabel *time = new QLabel(ui->Group_Text);
    time->setFixedSize(441,20);
    time->move(20,105);
    time->setText("时间： " + mail.date());
    time->setStyleSheet("Font: 17pt;");
    time->setVisible(1);

    QLabel *line = new QLabel(ui->Group_Text);
    line->setFixedSize(401,1);
    line->move(20,130);
    line->setStyleSheet("border: 1px solid black");
    line->setVisible(1);

    QLabel *lb_text = new QLabel(ui->Group_Text);
    lb_text->setFixedSize(100,50);
    lb_text->move(20,140);
    lb_text->setText("正文：");
    lb_text->setStyleSheet("Font: 30pt;");
    lb_text->setVisible(1);

    QTextBrowser *textBrowser = new QTextBrowser(ui->Group_Text);
    textBrowser->setFixedSize(401,250);
    textBrowser->move(20,190);
    textBrowser->setText(mail.text());
    textBrowser->setStyleSheet("border: 1px solid black; border-radius: 8px; background-color: transparent;");
    textBrowser->setVisible(1);

    QPushButton *btn_remove = new QPushButton(ui->Group_Text);
    btn_remove->setFixedSize(100,50);
    btn_remove->move(320,20);
    btn_remove->setText("删除");
    btn_remove->setStyleSheet("color: rgb(210,0,0); border-radius: 20px;");
    btn_remove->setVisible(1);

    connect(this, &Form_Mail::clearWidgets, title, &QLabel::deleteLater);
    connect(this, &Form_Mail::clearWidgets, sender, &QLabel::deleteLater);
    connect(this, &Form_Mail::clearWidgets, time, &QLabel::deleteLater);
    connect(this, &Form_Mail::clearWidgets, line, &QLabel::deleteLater);
    connect(this, &Form_Mail::clearWidgets, lb_text, &QLabel::deleteLater);
    connect(this, &Form_Mail::clearWidgets, textBrowser, &QTextBrowser::deleteLater);
    connect(this, &Form_Mail::clearWidgets, btn_remove, &QPushButton::deleteLater);
    connect(btn_remove, &QPushButton::clicked, this, [=](){ this->removeMail(mail.no()); });

    if(mail.type() == "好友申请"){
        textBrowser->setFixedSize(401,220);
        this->f_makeFriends(mail);
    }
}


void Form_Mail::removeMail(int no)
{
    Widget_Choose *widget_choose = new Widget_Choose(this,"邮件","是否删除该邮件？");
    connect(widget_choose, &Widget_Choose::confirm, this, [=](){
        emit clearWidgets();
        myMail->removeMail(no);
        emit s_removeMail(no);
    });
    widget_choose->setVisible(1);
}


void Form_Mail::on_btn_close_clicked()
{
    this->deleteLater();
}

