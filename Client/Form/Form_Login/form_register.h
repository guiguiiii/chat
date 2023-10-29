#ifndef FORM_REGISTER_H
#define FORM_REGISTER_H

#include <QWidget>
#include "Class/DataAccess/login_socket.h"

namespace Ui {
class Form_Register;
}

class Form_Register : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Register(QWidget *parent, Login_Socket *login);
    ~Form_Register();

private:
    Ui::Form_Register *ui;
    Login_Socket *login;

private slots:
    void f_register(int state);

signals:
    void cancel();
    void success(const QVector<QString> &noAPwd);
    void closeWaitWidget();

private slots:
    void on_btn_cancel_clicked();
    void on_btn_submit_clicked();
    void on_le_name_returnPressed();
};

#endif // FORM_REGISTER_H
