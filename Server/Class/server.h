#ifndef SERVER_H
#define SERVER_H

//端口号，以后改成图形化设置
#define HOST 10523

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent);

private:
    void initSQL();

private slots:
    void newConnection();
    void disconnected(QTcpSocket *socket);
    void readyRead(QTcpSocket *socket);

private:
    QTcpServer *server;
    void write(QTcpSocket *socket,const QString &title,const QString &text);
    void sendSignal(QTcpSocket *socket,const QString &title,const QString &text);
};

#endif // SERVER_H
