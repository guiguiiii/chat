#include "widget_choose.h"
#include "ui_widget_choose.h"

Widget_Choose::Widget_Choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Choose)
{
    ui->setupUi(this);
}


Widget_Choose::Widget_Choose(QWidget *parent,const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Choose)
{
    ui->setupUi(this);
    ui->lb_text->setText(text);
}


Widget_Choose::Widget_Choose(QWidget *parent,const QString &title,const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Choose)
{
    ui->setupUi(this);
    ui->lb_title->setText(title);
    ui->lb_text->setText(text);
}


Widget_Choose::~Widget_Choose()
{
    delete ui;
}


void Widget_Choose::setText(const QString &text)
{
    ui->lb_text->setText(text);
}


void Widget_Choose::setTitle(const QString &title)
{
    ui->lb_title->setText(title);
}


void Widget_Choose::setBtnCancel(const QString &text)
{
    ui->btn_cancel->setText(text);
}


void Widget_Choose::setBtnConfirm(const QString &text)
{
    ui->btn_confirm->setText(text);
}


void Widget_Choose::on_btn_cancel_clicked()
{
    emit cancel();
    this->deleteLater();
}


void Widget_Choose::on_btn_confirm_clicked()
{
    emit confirm();
    this->deleteLater();
}

