#ifndef FORM_MYINFO_H
#define FORM_MYINFO_H

#include <QWidget>
#include "Class/Service/personal_service.h"

namespace Ui {
class Form_MyInfo;
}

class Form_MyInfo : public QWidget
{
    Q_OBJECT

public:
    explicit Form_MyInfo(QWidget *parent, Personal_Service *personal);
    ~Form_MyInfo();

private:
    Ui::Form_MyInfo *ui;
    Personal_Service *personal;

private:
    void initForm();

private slots:
    void f_setMyInfo(int state);

private slots:
    void on_btn_cancel_clicked();
    void on_btn_head_clicked();
    void on_btn_setHead_clicked();
    void on_btn_confirm_clicked();
};

#endif // FORM_MYINFO_H
