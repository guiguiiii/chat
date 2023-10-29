#ifndef PERSONAL_SOCKET_H
#define PERSONAL_SOCKET_H

#include <QObject>
#include "Class/socket.h"
#include "Class/Data/info.h"

class Personal_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Personal_Socket(QObject *parent, Socket *socket);

    void myInfo();
    void setMyInfo(const Info &info);

private:
    Socket *socket;
    void myWrite(const QString &title, const QString &text);

private slots:
    void readyRead(const QString &text);
    void f_myInfo(const QString &text);

signals:
    void s_myInfo(const Info &info);
    void s_setMyInfo(int state);
};

#endif // PERSONAL_SOCKET_H
