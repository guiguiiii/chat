#include "common.h"

#include <QSqlQuery>
#include <QBuffer>
#include <QFile>

Common::Common()
{

}


QString Common::socketToString(const QTcpSocket *socket)
{
    return QString::number(reinterpret_cast<std::uintptr_t>(socket));
}


QString Common::socketToNo(const QTcpSocket *socket)
{
    QString addr = QString::number(reinterpret_cast<std::uintptr_t>(socket));
    QString sqlStr = QString(" \
SELECT no FROM users WHERE socket = '%1' ;")
        .arg(addr);
    QSqlQuery query;
    query.exec(sqlStr);
    if(query.next()){
        return query.value(0).toString();
    }else{
        return "";
    }
}


QTcpSocket *Common::noToSocket(const QString &no)
{
    QString sqlStr = QString(" \
SELECT socket FROM users WHERE no = '%1' AND socket IS NOT NULL ;")
        .arg(no);
    QSqlQuery query;
    query.exec(sqlStr);
    if(query.next()){
        QTcpSocket *socket = (QTcpSocket *)query.value(0).toLongLong();
        return socket;
    }else{
        QTcpSocket *socket = nullptr;
        return socket;
    }
}


QString Common::noGetHead(const QString &no)
{
    QPixmap pixmap;
    QString defPath = "Data/Head/_.png";
    QString myPath = "Data/Head/";
    myPath = myPath + no + ".png";
    QFile file(myPath);
    if(file.exists()){
        pixmap.load(myPath);
    }else{
        pixmap.load(defPath);
    }

    QBuffer buffer;
    pixmap.save(&buffer,"png");
    QByteArray byteArray;
    byteArray.append(buffer.data());
    return byteArray.toBase64();
}


QPixmap Common::strToPixmap(const QString &str)
{
    QString head(str);
    QByteArray byteArray(QByteArray::fromBase64(head.toLocal8Bit()));
    QImage image;
    image.loadFromData(byteArray);
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    return pixmap;
}

