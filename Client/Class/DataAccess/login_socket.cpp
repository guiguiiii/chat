    #include "login_socket.h"

Login_Socket::Login_Socket(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->socket = socket;
    connect(socket, &Socket::s_login, this, &Login_Socket::readyRead);
}


void Login_Socket::login(const QString &no, const QString &pwd)
{
    QString text = "";
    text = text + no + "splitA" + pwd;
    this->myWrite("LOGIN",text);
}


void Login_Socket::Register(const QString &no, const QString &pwd, const QString &name)
{
    QString text = "";
    text = text + no + "splitA" + pwd + "splitA" + name;
    this->myWrite("REGISTER",text);
}


void Login_Socket::myWrite(const QString &title, const QString &text)
{
    QString str = "";
    str = str + title + "splitZ" + text;
    socket->write("LOGIN",str);
}


void Login_Socket::readyRead(const QString &text)
{
    QVector<QString> splitZ = text.split("splitZ");
    QString front = splitZ.front();
    QString back = splitZ.back();
    if(front == "LOGIN"){
        emit s_login(back.toInt());
    }else if(front == "REGISTER"){
        emit s_register(back.toInt());
    }
}

