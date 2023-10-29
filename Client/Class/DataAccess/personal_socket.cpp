#include "personal_socket.h"

#include "Class/Common/common.h"

Personal_Socket::Personal_Socket(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->socket = socket;
    connect(socket, &Socket::s_personal, this, &Personal_Socket::readyRead);
}

void Personal_Socket::myInfo()
{
    this->myWrite("MYINFO","");
}


void Personal_Socket::setMyInfo(const Info &info)
{
    QString text ="";
    text = text + info.no() + "splitA";
    text = text + info.pwd() + "splitA";
    text = text + info.name() + "splitA";
    text = text + info.signature() + "splitA";
    text = text + Common().pixToStr(info.head());
    this->myWrite("SETMYINFO",text);
}


void Personal_Socket::myWrite(const QString &title, const QString &text)
{
    QString str ="";
    str = str + title + "splitZ" + text;
    socket->write("PERSONAL",str);
}


void Personal_Socket::readyRead(const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "MYINFO"){
        this->f_myInfo(back);
    }else if(front == "SETMYINFO"){
        emit s_setMyInfo(back.toInt());
    }
}


void Personal_Socket::f_myInfo(const QString &text)
{
    QVector<QString> splitA = text.split("splitA");
    if(splitA.size() != 5){
        return;
    }

    Info info;
    info.setNo(splitA.at(0));
    info.setPWD(splitA.at(1));
    info.setName(splitA.at(2));
    info.setSignature(splitA.at(3));

    //QString to QPixmap
    QByteArray by = QByteArray::fromBase64(splitA.at(4).toLocal8Bit());
    QImage image;
    image.loadFromData(by);
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    info.setHead(pixmap);

    emit s_myInfo(info);
}

