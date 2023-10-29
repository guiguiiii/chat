#include "mail_socket.h"

#include <QDateTime>

Mail_Socket::Mail_Socket(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->socket = socket;
    connect(socket, &Socket::s_mail, this, &Mail_Socket::readyRead);
}


void Mail_Socket::myMails()
{
    this->myWrite("MYMAILS","");
}


void Mail_Socket::removeMail(int no)
{
    this->myWrite("REMOVEMAIL",QString::number(no));
}


void Mail_Socket::myWrite(const QString &title, const QString &text)
{
    QString str ="";
    str = str + title + "splitZ" + text;
    socket->write("MAIL",str);
}


void Mail_Socket::readyRead(const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYMAILS"){
        this->f_myMails(back);
    }else if(front == "NEWMAIL"){
        this->f_newMail(back);
    }
}


void Mail_Socket::f_myMails(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    QVector<Mail> mails;
    for(int i=0; i<splitA.size(); i++){
        QVector<QString> splitB = splitA.at(i).split("splitB");
        if(splitB.size() != 6){
            continue;
        }

        Mail mail;
        mail.setNo(splitB.at(0).toInt());
        mail.setSender(splitB.at(1));
        mail.setDate(splitB.at(2));
        mail.setTitle(splitB.at(3));
        mail.setText(splitB.at(4));
        mail.setType(splitB.at(5));
        mails.push_back(mail);
    }

    emit s_myMails(mails);
}


void Mail_Socket::f_newMail(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 6){
        return;
    }

    Mail mail;
    mail.setNo(splitA.at(0).toInt());
    mail.setSender(splitA.at(1));
    mail.setDate(splitA.at(2));
    mail.setTitle(splitA.at(3));
    mail.setText(splitA.at(4));
    mail.setType(splitA.at(5));

    emit s_newMail(mail);
}


