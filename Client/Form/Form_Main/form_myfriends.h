#ifndef FORM_MYFRIENDS_H
#define FORM_MYFRIENDS_H

#include <QWidget>
#include <QPushButton>
#include "Class/Service/friends_service.h"

namespace Ui {
class Form_MyFriends;
}

class Form_MyFriends : public QWidget
{
    Q_OBJECT

public:
    explicit Form_MyFriends(QWidget *parent, Friends_Service *friends);
    ~Form_MyFriends();

private slots:
    void on_btn_back_clicked();

private:
    Ui::Form_MyFriends *ui;
    Friends_Service *friends;

private:
    void initBtns();
    void newBtn(const NoAName &noAName);

private slots:
    void friend_clicked(const QString &no);
};

#endif // FORM_MYFRIENDS_H
