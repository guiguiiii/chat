#ifndef MYFILE_H
#define MYFILE_H

#include <QVector>
#include "Class/Data/message.h"

class MyFile
{
public:
    MyFile();
    QString ipPort();
    void setIpPort(const QString &ip, const QString &port);
    void initMessageDir(const QString &no);
//    void initMessFile(const QString &myNo, const QVector<NoAName> &noANames);
    void appendMessage(const QString &myNo, const Message &message);
    QVector<Message> getMessages(const QString &myNo, const QString &no);
};

#endif // MYFILE_H
