#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent);

    void connectToHost(const QString &addr, int port);
    void write(const QString &title, const QString &text);

private:
    QTcpSocket *socket;
    void sendSignal(const QString &title, const QString &text);

private slots:
    void readyRead();

signals:
    void connected();
    void disconnected();
    void s_login(const QString &text);
    void s_personal(const QString &text);
    void s_friends(const QString &text);
    void s_chat(const QString &text);
    void s_mail(const QString &text);
};

#endif // SOCKET_H
