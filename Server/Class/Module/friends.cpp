#include "friends.h"

#include <QSqlQuery>
#include <QDateTime>
#include "Common/common.h"

Friends::Friends(QObject *parent) :
    QObject{parent}
{

}


void Friends::processInfo(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYFRIENDS"){
        this->f_myFriends(socket);
    }else if(front == "SETNICKNAME"){
        this->f_setNickname(socket,back);
    }else if(front == "MAKEFRIENDS"){
        this->f_makeFriends(socket,back);
    }else if(front == "UNFRIEND"){
        this->f_unFriend(socket,back);
    }else if(front == "RESPOND"){
        this->f_respond(socket,back);
    }

    this->deleteLater();
}


void Friends::myWrite(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    emit s_write(socket,"FRIENDS",str);
}


void Friends::f_myFriends(QTcpSocket *socket)
{
    QString strBack = "";
    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
SELECT no2, name, signature, nickname1 FROM friends \
    LEFT JOIN users ON no2 = no \
        WHERE no1 = '%1' \
    UNION \
SELECT no1, name, signature, nickname2 FROM friends \
    LEFT JOIN users ON no1 = no \
        WHERE no2 = '%1' ;")
        .arg(no);
    query.exec(sqlStr);

    while(query.next()){
        strBack = strBack + query.value(0).toString() + "splitB";
        strBack = strBack + query.value(1).toString() + "splitB";
        strBack = strBack + query.value(2).toString() + "splitB";
        strBack = strBack + query.value(3).toString() + "splitB";
        strBack = strBack + Common().noGetHead(query.value(0).toString()) + "splitA";
    }

    strBack.resize(strBack.size() -6);
    this->myWrite(socket,"MYFRIENDS",strBack);
}


void Friends::f_setNickname(QTcpSocket *socket, const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 2){
        return;
    }

    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
UPDATE friends SET nickname1 = '%3' WHERE no1 = '%1' AND no2 = '%2' ; \
UPDATE friends SET nickname2 = '%3' WHERE no2 = '%1' AND no1 = '%2' ;")
        .arg(no,splitA.at(0),splitA.at(1));
    query.exec(sqlStr);
}


void Friends::f_makeFriends(QTcpSocket *socket, const QString &text)
{
    /*回复状态字
        1--申请成功，2--账号不存在，3--已为好友
      若申请成功，存储申请邮件
        若对方在线，发送一份申请邮件
      （ 若同对象同类型邮件存在，改为更新文本，时间 )、、、但是客户端没有更新接口 */
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 2){
        return;
    }

    QSqlQuery query;
    QString no = Common().socketToNo(socket);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm");

    //  查询是否存在该账号
    QString sqlStr = QString(" \
SELECT no FROM users WHERE no = '%1' ;")
        .arg(splitA.at(0));
    query.exec(sqlStr);
    if(query.next() == false){
        //  若账号不存在，回复状态字 2
        this->myWrite(socket,"MAKEFRIENDS","2");
        return;
    }

    //  查询是否已互为好友
    QString sqlStr_2 = QString(" \
SELECT no1 FROM friends WHERE no1 = '%1' AND no2 = '%2' \
    UNION \
SELECT no2 FROM friends WHERE no1 = '%2' AND no2 = '%1' ;")
        .arg(no,splitA.at(0));
    query.exec(sqlStr_2);
    if(query.next()){
        //  若已互为好友，回复状态字 3
        this->myWrite(socket,"MAKEFRIENDS","3");
        return;
    }

    //  若不为以上情况，即为申请成功，回复状态字 1
    this->myWrite(socket,"MAKEFRIENDS","1");

    //  查询同对象同类型邮件是否存在
    QString mailNo = "";
    QString sqlStr_3 = QString(" \
SELECT no FROM mails WHERE no1 = '%1' AND no2 = '%2' AND type = '好友申请' ;")
        .arg(no,splitA.at(0));
    query.exec(sqlStr_3);

    if(query.next()){
        //若存在，更新时间和文本
        mailNo = query.value(0).toString();
        QString sqlStr_4 = QString(" \
UPDATE mails SET m_date = '%1', text = '%2' WHERE no = '%3' ;")
            .arg(time,splitA.at(1),mailNo);
        query.exec(sqlStr_4);

    }else{
        //若不存在，存入一封新的申请邮件
        QString sqlStr_5 = QString(" \
INSERT INTO mails ( no1, no2, m_date, title, text, type ) \
    VALUES ( '%1', '%2', '%3', '%4', '%5', '%6' ) ;")
            .arg(no,splitA.at(0),time,"好友申请",splitA.at(1),"好友申请");
        query.exec(sqlStr_5);

        //  若对方在线，把邮件发过去
        QTcpSocket *socketTo = Common().noToSocket(splitA.at(0));
        if(socketTo != nullptr){
            this->sendNewMail(socketTo);
        }
    }
}


void Friends::f_unFriend(QTcpSocket *socket, const QString &text)
{
    QSqlQuery query;
    QString no = Common().socketToNo(socket);

    QString sqlStr = QString(" \
DELETE FROM friends WHERE no1 = '%1' AND no2 = '%2' ; \
DELETE FROM friends WHERE no1 = '%2' AND no2 = '%1' ;")
        .arg(no,text);
    query.exec(sqlStr);

    //  回应客户端
    this->myWrite(socket,"UNFRIEND",text);

    //  若对方在线，发送断开关系信息
    QTcpSocket *socketTo = Common().noToSocket(text);
    if(socketTo != nullptr){
        this->myWrite(socketTo,"UNFRIEND",no);
    }
}


void Friends::f_respond(QTcpSocket *socket, const QString &text)
{
    /*若接受，好友关系存入数据库，发给自己一条新好友信息，
          一封成为好友邮件，邮件存入数据库。
        若对方在线，发给对方一条新好友信息，
          一封成为好友邮件，邮件存入数据库。
      若拒绝，若对方在线，
        发给对方一封拒绝成为好友邮件，邮件存入数据库。*/
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 2){
        return;
    }

    QString strTo = "";
    QString strBack = "";
    QSqlQuery query;
    QString no = Common().socketToNo(socket);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm");
    QTcpSocket *socketTo = Common().noToSocket(splitA.at(0));

    //  拒绝处理
    if(splitA.at(1) == '0'){
        //  对方的申请结果邮件存入数据库
        QString body = no + " 拒绝了您的好友申请";
        QString sqlStr = QString(" \
INSERT INTO MAILS ( no1, no2, m_date, title, text, type ) \
    VALUES ( '%1', '%2', '%3', '%4', '%5', '%6' ) ;")
            .arg(no,splitA.at(0),time,"好友申请结果",body,"信息");
        query.exec(sqlStr);

        //  若对方在线，把邮件发过去
        if(socketTo != nullptr){
            this->sendNewMail(socketTo);
        }

    //  接受处理
    }else{
        //  好友关系存入数据库
        QString sqlStr = QString(" \
INSERT INTO friends ( no1, no2 ) VALUES ( '%1', '%2' ) ;")
            .arg(splitA.at(0),no);
        query.exec(sqlStr);

        //  查询对方信息，给自己发送新好友信息
        QString sqlStr_2 = QString(" \
SELECT name, signature FROM users WHERE no = '%1' ;")
            .arg(splitA.at(0));
        query.exec(sqlStr_2);

        if(query.next()){
            strBack = strBack + splitA.at(0) + "splitA";
            strBack = strBack + query.value(0).toString() + "splitA";
            strBack = strBack + query.value(1).toString() + "splitA";
            strBack = strBack + "" + "splitA";
            strBack = strBack + Common().noGetHead(splitA.at(0));

            this->myWrite(socket,"NEWFRIEND",strBack);
        }

        //  存入我的成为好友邮件
        QString body = "我已成为你的好友";
        QString sqlStr_3 = QString(" \
INSERT INTO MAILS ( no1, no2, m_date, title, text, type ) \
    VALUES ( '%1', '%2', '%3', '%4', '%5', '%6' ) ;")
            .arg(splitA.at(0),no,time,"好友",body,"信息");
        query.exec(sqlStr_3);

        //  给自己发送成为好友邮件
        this->sendNewMail(socket);

        //  存入对方的成为好友邮件
        body = no + " 接受了您的好友申请";
        QString sqlStr_4 = QString(" \
INSERT INTO MAILS ( no1, no2, m_date, title, text, type ) \
    VALUES ( '%1', '%2', '%3', '%4', '%5', '%6' ) ;")
            .arg(no,splitA.at(0),time,"好友申请结果",body,"信息");
        query.exec(sqlStr_4);

        //  若对方在线，发送成为好友邮件，发送新好友信息
        if(socketTo != nullptr){
            //  给对方发送成为好友邮件
            this->sendNewMail(socketTo);

            //查询我的信息，给对方发送新好友信息
            QString sqlStr_5 = QString(" \
SELECT name, signature FROM users WHERE no = '%1' ;")
                .arg(no);
            query.exec(sqlStr_5);
            if(query.next()){
                strTo = "";
                strTo = strTo + no + "splitA";
                strTo = strTo + query.value(0).toString() + "splitA";
                strTo = strTo + query.value(1).toString() + "splitA";
                strTo = strTo + "" + "splitA";
                strTo = strTo + Common().noGetHead(no);

                this->myWrite(socketTo,"NEWFRIEND",strTo);
            }
        }
    }
}


void Friends::sendNewMail(QTcpSocket *socket, const QString &mailNo)
{
    QString strTo = "";
    QSqlQuery query;

    QString sqlStr = "";
    if(mailNo != "-1"){
        sqlStr = QString(" \
SELECT no, no1, m_date, title, text, type FROM mails WHERE no = '%1' ;")
            .arg(mailNo);
    }else{
        sqlStr = QString(" \
SELECT no, no1, m_date, title, text, type FROM mails WHERE no = LAST_INSERT_ID() ;");
    }
    query.exec(sqlStr);

    if(query.next()){
        strTo = strTo + query.value(0).toString() + "splitA";
        strTo = strTo + query.value(1).toString() + "splitA";
        strTo = strTo + query.value(2).toString() + "splitA";
        strTo = strTo + query.value(3).toString() + "splitA";
        strTo = strTo + query.value(4).toString() + "splitA";
        strTo = strTo + query.value(5).toString();
    }

    QString str = "";
    str = str + "NEWMAIL" + "splitZ" + strTo;
    emit s_write(socket,"MAIL",str);
}

