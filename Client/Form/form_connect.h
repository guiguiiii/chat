#ifndef FORM_CONNECT_H
#define FORM_CONNECT_H

#include <QWidget>
#include "Class/socket.h"

namespace Ui {
class Form_Connect;
}

class Form_Connect : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Connect(QWidget *parent,Socket *socket);
    ~Form_Connect();

private slots:
    void on_btn_set_clicked();
    void on_btn_cancel_clicked();
    void on_btn_confirm_clicked();
    void on_btn_retry_clicked();

private:
    Ui::Form_Connect *ui;
    Socket *socket;
    void init();

private slots:
    void f_connected();
};

#endif // FORM_CONNECT_H
