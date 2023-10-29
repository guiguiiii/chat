#ifndef PERSONAL_H
#define PERSONAL_H

#include <QObject>
#include <QTcpSocket>

class Personal : public QObject
{
    Q_OBJECT
public:
    explicit Personal(QObject *parent);
    void processInfo(QTcpSocket *socket, const QString &text);

private:
    void myWrite(QTcpSocket *socket, const QString &title, const QString &text);

private slots:
    void f_myInfo(QTcpSocket *socket);
    void f_setMyInfo(QTcpSocket *socket, const QString &text);

signals:
    void s_write(QTcpSocket *socket, const QString &title, const QString &text);
};

#endif // PERSONAL_H
