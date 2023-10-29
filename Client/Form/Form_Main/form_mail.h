#ifndef FORM_MAIL_H
#define FORM_MAIL_H

#include <QWidget>
#include "Class/DataAccess/mail_socket.h"
#include "Class/Service/friends_service.h"

namespace Ui {
class Form_Mail;
}

class Form_Mail : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Mail(QWidget *parent, Socket *socket, Friends_Service *friends);
    ~Form_Mail();

private:
    Ui::Form_Mail *ui;
    Mail_Socket *myMail;
    Friends_Service *friends;

private slots:
    void f_myMails(const QVector<Mail> &mails);
    void f_newMail(const Mail &mail);

private:
    void mailSelected(const Mail &mail);
    void removeMail(int no);

private:
    //特殊邮件的额外界面
    void f_makeFriends(const Mail &mail);

signals:
    void s_removeMail(int no);
    void clearWidgets();

private slots:
    void on_btn_close_clicked();
};

#endif // FORM_MAIL_H
