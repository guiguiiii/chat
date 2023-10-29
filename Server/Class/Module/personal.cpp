#include "personal.h"

#include <QSqlQuery>
#include "Common/common.h"

Personal::Personal(QObject *parent)
    : QObject{parent}
{

}


void Personal::processInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYINFO"){
        this->f_myInfo(socket);
    }else if(front == "SETMYINFO"){
        this->f_setMyInfo(socket,back);
    }

    this->deleteLater();
}


void Personal::myWrite(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    emit s_write(socket,"PERSONAL",str);
}


void Personal::f_myInfo(QTcpSocket *socket)
{
    QString strBack ="";
    QSqlQuery query;
    QString socketStr = Common().socketToString(socket);

    QString sqlStr = QString(" \
SELECT no, pwd, name, signature FROM users WHERE socket = '%1' ;")
        .arg(socketStr);
    query.exec(sqlStr);

    if(query.next()){
        strBack = strBack + query.value(0).toString() + "splitA";
        strBack = strBack + query.value(1).toString() + "splitA";
        strBack = strBack + query.value(2).toString() + "splitA";
        strBack = strBack + query.value(3).toString() + "splitA";
        strBack = strBack + Common().noGetHead(query.value(0).toString());
        this->myWrite(socket,"MYINFO",strBack);
    }
}


void Personal::f_setMyInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 5){
        return;
    }

    QString strBack ="";
    QString addr = Common().socketToString(socket);
    QSqlQuery query;

    QString sqlStr = QString(" \
UPDATE users \
    SET no = '%1', pwd = '%2', name = '%3', signature = '%4' \
        WHERE socket = '%5' ;")
        .arg(splitA.at(0),splitA.at(1),splitA.at(2),splitA.at(3),addr);

    //若修改成功，则把头像也改了。
    if(query.exec(sqlStr)){
        QString head = splitA.at(4);
        QPixmap pixmap(Common().strToPixmap(head));

        //若头像与默认头像不相同，则将头像以账号为名字保存。
        if(pixmap.cacheKey() != QPixmap("Data/Head/_.png").cacheKey()){
            QString name = QString("Data/Head/%1.png").arg(splitA.at(0));
            pixmap.save(name);
        }

        //返回 state = 1
        strBack ='1';
    }else{
        //返回 state = 2
        strBack ='2';
    }

    this->myWrite(socket,"SETMYINFO",strBack);
}

