#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QTcpSocket>

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent);
    void processInfo(QTcpSocket *socket, const QString &text);

private:
    void myWrite(QTcpSocket *socket, const QString &title, const QString &text);

private slots:
    void f_myMessages(QTcpSocket *socket);
    void f_sendMessage(const QString &text);

signals:
    void s_write(QTcpSocket *socket, const QString &title, const QString &text);
};

#endif // CHAT_H
