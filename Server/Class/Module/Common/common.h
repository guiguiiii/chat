#ifndef COMMON_H
#define COMMON_H

#include <QTcpSocket>
#include <QPixmap>

class Common
{
public:
    Common();
    QString socketToString(const QTcpSocket *socket);
    QString socketToNo(const QTcpSocket *socket);
    QTcpSocket *noToSocket(const QString &no);
    QString noGetHead(const QString &no);
    QPixmap strToPixmap(const QString &str);
};

#endif // COMMON_H
