#include "login.h"

#include <QSqlQuery>
#include "Common/common.h"

Login::Login(QObject *parent) :
    QObject{parent}
{

}


void Login::processInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "LOGIN"){
        this->f_login(socket,back);
    }else if(front == "REGISTER"){
        this->f_register(socket,back);
    }

    this->deleteLater();
}


void Login::myWrite(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    emit s_write(socket,"LOGIN",str);
}


void Login::f_login(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 2){
        return;
    }

    QString strBack ="";
    QSqlQuery query;
    QString socketStr = Common().socketToString(socket);

    QString sqlStr = QString(" \
SELECT no FROM users WHERE no = '%1' AND pwd = '%2' ;")
        .arg(splitA.at(0),splitA.at(1));
    query.exec(sqlStr);

    //若查询到一个元组
    if(query.next()){
        //修改账号的 socket 值
        QString sqlStr_2 = QString(" \
UPDATE users SET socket = '%2' WHERE no = '%1' ;")
            .arg(splitA.at(0),socketStr);
        query.exec(sqlStr_2);

        //返回 state = 1
        strBack ='1';

    }else{
        //查看是 输入的账号不存在 还是 账号密码不匹配
        QString sqlStr_3 = QString(" \
SELECT no FROM users WHERE no = '%1' ;")
            .arg(splitA.at(0));
        query.exec(sqlStr_3);

        //返回 state = 2 或 state = 3
        if(query.next()){
            strBack ='2';
        }else{
            strBack ='3';
        }
    }

    this->myWrite(socket,"LOGIN",strBack);
}


void Login::f_register(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 3){
        return;
    }

    QString strBack = "";
    QSqlQuery query;

    QString sqlStr = QString(" \
INSERT INTO users ( no, pwd, name ) VALUES ( '%1', '%2', '%3' ) ;")
        .arg(splitA.at(0),splitA.at(1),splitA.at(2));

    if(query.exec(sqlStr)){
        strBack = '1';
    }else{
        strBack = '2';
    }

    this->myWrite(socket,"REGISTER",strBack);
}

