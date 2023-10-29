#include "personal_service.h"
#include <QBuffer>

Personal_Service::Personal_Service(QObject *parent, Socket *socket)
    : QObject{parent}
{
    this->personal_socket = new Personal_Socket(this,socket);
    connect(personal_socket, &Personal_Socket::s_myInfo, this, &Personal_Service::f_myInfo);
    connect(personal_socket, &Personal_Socket::s_setMyInfo, this, &Personal_Service::f_setMyInfo);
}

void Personal_Service::initInfo()
{
    personal_socket->myInfo();
}

const Info &Personal_Service::myInfo()
{
    return info;
}

void Personal_Service::setMyInfo(const Info &info)
{
    this->tmpInfo = info;
    personal_socket->setMyInfo(info);
}

void Personal_Service::f_myInfo(const Info &info)
{
    this->info = info;
    emit s_initSuccess();
}

void Personal_Service::f_setMyInfo(int state)
{
    emit s_setMyInfo(state);
    if(state == 1){
        info = tmpInfo;
        tmpInfo = Info();
        emit s_infoChanged();
    }
}
