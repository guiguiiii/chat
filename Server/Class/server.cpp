#include "server.h"

#include <QSqlQuery>
#include "Class/Module/login.h"
#include "Class/Module/personal.h"
#include "Class/Module/friends.h"
#include "Class/Module/chat.h"
#include "Class/Module/mail.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    this->initSQL();
    this->server = new QTcpServer(this);
    this->server->listen(QHostAddress::Any,HOST);
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}


void Server::initSQL()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("127.0.0.1");
    database.setPort(3306);
    database.setUserName("guigui");
    database.setPassword("123456");
    database.setDatabaseName("chat");
    database.open();
    if(!database.isOpen()){
        qDebug()<<"MYSQLNOTOPEN!";
        return;
    }
}


void Server::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, [=](){ this->disconnected(socket); });
    connect(socket, &QTcpSocket::readyRead, this, [=](){ this->readyRead(socket); });
}


void Server::disconnected(QTcpSocket *socket)
{
    //删除用户表中的 socket 值，删除套接字对象。
    QString addr = QString::number(reinterpret_cast<std::uintptr_t>(socket));
    QSqlQuery query;
    QString str = QString("UPDATE users SET socket = NULL WHERE socket = '%1' ;")
        .arg(addr);
    query.exec(str);
    socket->deleteLater();
}


void Server::readyRead(QTcpSocket *socket)
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
            sendSignal(socket,title,text.sliced(begin+48,size-16));
        	text = text.sliced(begin + 48 + size);
        	size = -1;
        	begin = -1;
        	title = "";
	    }else{
			return;
        }
    }
}


void Server::write(QTcpSocket *socket, const QString &title, const QString &text)
{
    QString end = "PACKAGE_END     ";
    QString title_16 = QString("%1").arg(title,16,QLatin1Char(' '));
    int length = text.size() + end.size();
    QString textSize_16 = QString("%1").arg(QString::number(length),16,'0');
    QString str = "PACKAGE_BEGIN   ";
    str = str + textSize_16 + title_16 + text + end;
    socket->write(str.toUtf8());
}


void Server::sendSignal(QTcpSocket *socket, const QString &title, const QString &text)
{

//debug
qDebug()<<"CLASS: "<<title<<"  TITLE"<<text.split("splitZ").front();
if(text.size() <= 300){
    qDebug()<<"TEXT: "<<text;
}

    if(title == "LOGIN"){
        Login *login = new Login(this);
        connect(login, &Login::s_write, this, &Server::write);
        login->processInfo(socket,text);

    }else if(title == "PERSONAL"){
        Personal *personal = new Personal(this);
        connect(personal, &Personal::s_write, this, &Server::write);
        personal->processInfo(socket,text);

    }else if(title == "FRIENDS"){
        Friends *friends = new Friends(this);
        connect(friends, &Friends::s_write, this, &Server::write);
        friends->processInfo(socket,text);

    }else if(title == "CHAT"){
        Chat *chat = new Chat(this);
        connect(chat, &Chat::s_write, this, &Server::write);
        chat->processInfo(socket,text);

    }else if(title == "MAIL"){
        Mail *mail = new Mail(this);
        connect(mail, &Mail::s_write, this, &Server::write);
        mail->processInfo(socket,text);

    }
}

