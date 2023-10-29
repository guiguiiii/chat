#ifndef COMMON_H
#define COMMON_H

#include <QPixmap>

class Common
{
public:
    Common();
    QString pixToStr(const QPixmap &pixmap);
    QPixmap strToPix(const QString &str);
};

#endif // COMMON_H
