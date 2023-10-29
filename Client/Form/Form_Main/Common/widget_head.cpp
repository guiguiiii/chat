#include "widget_head.h"
#include "ui_widget_head.h"

Widget_Head::Widget_Head(QWidget *parent, const QPixmap &head) :
    QWidget(parent),
    ui(new Ui::Widget_Head)
{
    ui->setupUi(this);
    ui->radius->setPixmap(head);
}


Widget_Head::~Widget_Head()
{
    delete ui;
}


void Widget_Head::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        this->deleteLater();
    }
}

