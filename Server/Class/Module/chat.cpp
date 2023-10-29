#include "chat.h"

#include <QSqlQuery>
#include "Common/common.h"

Chat::Chat(QObject *parent) :
    QObject{parent}
{

}

void Chat::processInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYMESSAGES"){
        this->f_myMessages(socket);
    }else if(front == "SENDMESSAGE"){
        this->f_sendMessage(back);
    }

    this->deleteLater();
}


void Chat::myWrite(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    emit s_write(socket,"CHAT",str);
}


void Chat::f_myMessages(QTcpSocket *socket)
{
    QString strBack ="";
    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
SELECT no1, no2, m_date, text FROM messages WHERE no2 = '%1' ;")
        .arg(no);
    query.exec(sqlStr);

    while(query.next()){
        strBack = strBack + query.value(0).toString() + "splitB";
        strBack = strBack + query.value(1).toString() + "splitB";
        strBack = strBack + query.value(2).toString() + "splitB";
        strBack = strBack + query.value(3).toString() + "splitA";
    }

    QString sqlStr_2 = QString(" \
DELETE FROM messages WHERE no2 = '%1' ;")
        .arg(no);
    query.exec(sqlStr_2);

    strBack.resize(strBack.size() -6);
    this->myWrite(socket,"MYMESSAGES",strBack);
}


void Chat::f_sendMessage(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 4){
        return;
    }

    QString strTo ="";
    QSqlQuery query;
    QTcpSocket *socketTo = Common().noToSocket(splitA.at(1));

    //若对方在线，则把信息发过去，否则存在数据库里。
    if(socketTo == nullptr){
        QString sqlStr = QString(" \
INSERT INTO messages VALUES ( '%1', '%2', '%3', '%4' ) ;")
            .arg(splitA.at(0),splitA.at(1),splitA.at(2),splitA.at(3));
        query.exec(sqlStr);

    }else{
        strTo = strTo + splitA.at(0) + "splitA";
        strTo = strTo + splitA.at(1) + "splitA";
        strTo = strTo + splitA.at(2) + "splitA";
        strTo = strTo + splitA.at(3);
        this->myWrite(socketTo,"RECEIVEMESSAGE",strTo);
    }
}

