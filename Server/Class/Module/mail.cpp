#include "mail.h"

#include <QSqlQuery>
#include "Common/common.h"

Mail::Mail(QObject *parent)
    : QObject{parent}
{

}

void Mail::processInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYMAILS"){
        this->f_myMails(socket);
    }else if(front == "REMOVEMAIL"){
        this->f_removeMail(socket,back);
    }

    this->deleteLater();
}


void Mail::myWrite(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    emit s_write(socket,"MAIL",str);
}


void Mail::f_myMails(QTcpSocket *socket)
{
    QString strBack ="";
    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
SELECT no, no1, m_date, title, text, type FROM mails WHERE no2 = '%1' ;")
        .arg(no);
    query.exec(sqlStr);

    while(query.next()){
        strBack = strBack + query.value(0).toString() + "splitB";
        strBack = strBack + query.value(1).toString() + "splitB";
        strBack = strBack + query.value(2).toString() + "splitB";
        strBack = strBack + query.value(3).toString() + "splitB";
        strBack = strBack + query.value(4).toString() + "splitB";
        strBack = strBack + query.value(5).toString() + "splitA";
    }

    strBack.resize(strBack.size() -6);
    this->myWrite(socket,"MYMAILS",strBack);
}


void Mail::f_removeMail(QTcpSocket *socket, const QString &text)
{
    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
DELETE FROM mails WHERE no = '%1' AND ( no1 = '%2' OR no2 = '%2' ) ;")
        .arg(text,no);
    query.exec(sqlStr);
}

