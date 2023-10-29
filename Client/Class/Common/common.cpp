#include "common.h"

#include <QBuffer>

Common::Common()
{

}


QString Common::pixToStr(const QPixmap &pixmap)
{
    QBuffer buffer;
    pixmap.save(&buffer,"png");
    QByteArray byteArray;
    byteArray.append(buffer.data());
    return byteArray.toBase64();
}


QPixmap Common::strToPix(const QString &str){
    QString head(str);
    QByteArray byteArray(QByteArray::fromBase64(head.toLocal8Bit()));
    QImage image;
    image.loadFromData(byteArray);
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    return pixmap;
}

