#ifndef FORM_MAKEFRIENDS_H
#define FORM_MAKEFRIENDS_H

#include <QWidget>
#include "Class/Service/friends_service.h"

namespace Ui {
class Form_MakeFriends;
}

class Form_MakeFriends : public QWidget
{
    Q_OBJECT

public:
    explicit Form_MakeFriends(QWidget *parent, Friends_Service *friends);
    ~Form_MakeFriends();

private:
    Ui::Form_MakeFriends *ui;
    Friends_Service *friends;

private slots:
    void f_makeFriends(int state);

private slots:
    void on_btn_close_clicked();
    void on_btn_send_clicked();
};

#endif // FORM_MAKEFRIENDS_H
