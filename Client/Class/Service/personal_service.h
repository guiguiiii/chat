#ifndef PERSONAL_SERVICE_H
#define PERSONAL_SERVICE_H

#include <QObject>
#include "Class/DataAccess/personal_socket.h"

class Personal_Service : public QObject
{
    Q_OBJECT
public:
    explicit Personal_Service(QObject *parent, Socket *socket);

    void initInfo();
    const Info &myInfo();
    void setMyInfo(const Info &info);

private:
    Personal_Socket *personal_socket;
    Info info;
    Info tmpInfo;

private slots:
    void f_myInfo(const Info &info);
    void f_setMyInfo(int state);

signals:
    void s_initSuccess();
    void s_infoChanged();
    void s_setMyInfo(int state);
};

#endif // PERSONAL_SERVICE_H
