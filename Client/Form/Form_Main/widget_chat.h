#ifndef WIDGET_CHAT_H
#define WIDGET_CHAT_H

#include <QWidget>
#include "Class/Service/chat_service.h"

namespace Ui {
class Widget_Chat;
}

class Widget_Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Chat(QWidget *parent);
    ~Widget_Chat();
    void setService(Chat_Service *chat);

private:
    Ui::Widget_Chat *ui;
    Chat_Service *chat;
    QString no;

private:
    void newCommon(const Message &message);

private slots:
    void f_setMessages(const QPixmap &myHead, const QPixmap &frdHead, const QVector<Message> &messages);
    void f_appendMessage(const QPixmap &head, const Message &message);

signals:
    void s_showHead(const QPixmap &head);
};

#endif // WIDGET_CHAT_H
