#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include <QWidget>
#include "Class/socket.h"
#include "Class/Service/personal_service.h"
#include "Class/Service/friends_service.h"
#include "Class/Service/chat_service.h"

namespace Ui {
class Form_Main;
}

class Form_Main : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Main(QWidget *parent, Socket *socket);
    ~Form_Main();

private:
    Ui::Form_Main *ui;
    Socket *socket;
    Personal_Service *personal;
    Friends_Service *friends;
    Chat_Service *chat;

private slots:
    void initInfo();
    void initFriends();
    void initChat();
    void lockLineEdit(bool lock);

private slots:
    void on_btn_Info_clicked();
    void on_btn_myFriends_clicked();
    void on_btn_mail_clicked();
    void on_btn_makeFriends_clicked();
    void on_btn_send_clicked();
    void on_le_send_returnPressed();
};

#endif // FORM_MAIN_H
