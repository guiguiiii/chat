#include "widget_chat.h"
#include "ui_widget_chat.h"

#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
#include <QScrollArea>
#include <QWidget>
#include <QLayout>

Widget_Chat::Widget_Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Chat)
{
    ui->setupUi(this);
    ui->Chat_sawc->setFixedHeight(0);
}


Widget_Chat::~Widget_Chat()
{
    delete ui;
}


void Widget_Chat::setService(Chat_Service *chat)
{
    this->chat = chat;
    this->no = chat->myNo();
    connect(chat, &Chat_Service::s_setMessages, this, &Widget_Chat::f_setMessages);
    connect(chat, &Chat_Service::s_appendMessage, this, &Widget_Chat::f_appendMessage);
}


void Widget_Chat::f_setMessages(const QPixmap &myHead, const QPixmap &frdHead, const QVector<Message> &messages)
{
    ui->Chat_sawc->setFixedHeight(0);
    for(int i=0; i<messages.size(); i++){
        if(messages.at(i).sender() == no){
            this->f_appendMessage(myHead,messages.at(i));
        }else{
            this->f_appendMessage(frdHead,messages.at(i));
        }
    }
}


void Widget_Chat::f_appendMessage(const QPixmap &head, const Message &message)
{
    if(message.text().size() == 0){
        return;
    }

    int y = ui->Chat_sawc->height();
    QWidget *widget = new QWidget(ui->Chat_sawc);
    widget->setFixedWidth(521);
    widget->move(0,y);
    widget->setStyleSheet(".QWidget{ border: none; }");
    connect(chat, &Chat_Service::s_setMessages, widget, &QWidget::deleteLater);
    widget->setVisible(1);

    QLabel *lb_time = new QLabel(widget);
    lb_time->setFixedSize(521,40);
    lb_time->setText(message.date().mid(5));
    lb_time->setAlignment(Qt::AlignCenter);
    lb_time->setStyleSheet("border: none;");
    lb_time->setVisible(1);

    QLabel *lb_text = new QLabel(widget);
    lb_text->setFixedWidth(341);
    lb_text->move(90,40);
    lb_text->setText(message.text());
    lb_text->setStyleSheet("padding-left: 10px; padding-right: 10px; padding-top: 10px; padding-bottom: 10px;");
    lb_text->setWordWrap(1);
    lb_text->adjustSize();
    lb_text->setVisible(1);
    widget->setFixedSize(521,40 +lb_text->height());

    QLabel *lb_head = new QLabel(widget);
    lb_head->setFixedSize(60,60);
    lb_head->move(20,35);
    lb_head->setPixmap(head);
    lb_head->setScaledContents(1);
    lb_head->setStyleSheet("border: none;");
    lb_head->setVisible(1);

    QPushButton *btn_head = new QPushButton(widget);
    btn_head->setFixedSize(60,60);
    btn_head->move(20,35);
    btn_head->setStyleSheet("background-color: transparent;");
    connect(btn_head, &QPushButton::clicked, this, [=](){ emit s_showHead(lb_head->pixmap()); });
    btn_head->setVisible(1);

    if(message.sender() == no){
        lb_head->move(440,35);
        btn_head->move(440,35);
    }

    ui->Chat_sawc->setFixedHeight(y + widget->height());
    int value = ui->Chat_sa->verticalScrollBar()->maximumHeight();
    ui->Chat_sa->verticalScrollBar()->setValue(value);
}

