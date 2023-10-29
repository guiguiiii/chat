#include "socket.h"

Socket::Socket(QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Socket::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Socket::disconnected );
    connect(socket, &QTcpSocket::readyRead, this, &Socket::readyRead);
}


void Socket::connectToHost(const QString &addr, int port)
{
    socket->abort();
    socket->connectToHost(addr,port);
}


void Socket::write(const QString &title, const QString &text)
{
    QString end = "PACKAGE_END     ";
    QString title_16 = QString("%1").arg(title,16,QLatin1Char(' '));
    int length = text.size() + end.size();
    QString textSize_16 = QString("%1").arg(QString::number(length),16,'0');
    QString str = "PACKAGE_BEGIN   ";
    str = str + textSize_16 + title_16 + text + end;
    socket->write(str.toUtf8());
}


void Socket::sendSignal(const QString &title, const QString &text)
{

//debug
qDebug()<<"CLASS: "<<title<<"  TITLE"<<text.split("splitZ").front();
if(text.size() <= 300){
    qDebug()<<"TEXT: "<<text;
}

    if(title == "LOGIN"){
        emit s_login(text);
    }else if(title == "PERSONAL"){
        emit s_personal(text);
    }else if(title == "FRIENDS"){
        emit s_friends(text);
    }else if(title == "CHAT"){
        emit s_chat(text);
    }else if(title == "MAIL"){
        emit s_mail(text);
    }
}


void Socket::readyRead()
{
    //静态局部变量
    static QString text = "";
    static int size = -1;
    static int begin = -1;
    static QString title = "";
    text += socket->readAll();

    while(1){
        //若没有上次未读完的包体
        if(size == -1){
            if(text.size() < 48){
                return;
            }

            //寻找头串，若找到，给 size、title 赋值，
            //  否则 text（缓冲区）只保留最后 16 位，可以防止头串被分成两半。
            begin = text.indexOf("PACKAGE_BEGIN   ");
            if(begin >= 0){
                size = text.sliced(begin + 16,16).toInt();
                title = text.sliced(begin + 32,16).trimmed();
            }else{
                text = text.sliced(text.size() - 16,16);
                return;
            }
        }

        //若 text（缓冲区）中 在包头后面的数据的大小 >= 包体数据大小，
        //  则拆包成功，将数据分发，同时将 size、title 初始化。text（缓冲区）可以删掉该包体部分。
        //    且进入 while 第二层循环，处理第二包。
        if(text.size()-(begin+48) >= size){
            sendSignal(title,text.sliced(begin+48,size-16));
            text = text.sliced(begin + 48 + size);
            size = -1;
            begin = -1;
            title = "";
        }else{
            return;
        }
    }
}

