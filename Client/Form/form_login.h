#ifndef FORM_LOGIN_H
#define FORM_LOGIN_H

#include <QWidget>
#include "Class/socket.h"
#include "Class/DataAccess/login_socket.h"

namespace Ui {
class Form_Login;
}

class Form_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Login(QWidget *parent, Socket *socket);
    ~Form_Login();

private:
    Ui::Form_Login *ui;
    Socket *socket;
    Login_Socket *login;

private slots:
    void f_login(int state);

signals:
    void closeWaitWidget();

private slots:
    void on_btn_exit_clicked();
    void on_btn_login_clicked();
    void on_le_no_returnPressed();
    void on_le_pwd_returnPressed();
    void on_btn_register_clicked();
};

#endif // FORM_LOGIN_H
