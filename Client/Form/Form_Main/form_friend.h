#ifndef FORM_FRIEND_H
#define FORM_FRIEND_H

#include <QWidget>
#include "Class/Service/friends_service.h"

namespace Ui {
class Form_Friend;
}

class Form_Friend : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Friend(QWidget *parent, Friends_Service *friends, const QString &no);
    ~Form_Friend();

private:
    Ui::Form_Friend *ui;
    Friends_Service *friends;
    QString no;
    QString nickname;

private:
    void initForm();

private slots:
    void f_unFriend(const QString &no);

signals:
    void closeWaitWidget();

private slots:
    void on_btn_close_clicked();
    void on_btn_unFriend_clicked();
};

#endif // FORM_FRIEND_H
