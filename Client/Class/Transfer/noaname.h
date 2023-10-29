#ifndef NOANAME_H
#define NOANAME_H

#include <QPixmap>

class NoAName
{
public:
    NoAName();
    NoAName(const QString &newNo, const QString &newName);
    NoAName(const QString &newNo, const QString &newName, const QPixmap &newHead);

    const QString &no() const;
    void setNo(const QString &newNo);

    const QString &name() const;
    void setName(const QString &newName);

    const QPixmap &head() const;
    void setHead(const QPixmap &newHead);

private:
    QString m_no;
    QString m_name;
    QPixmap m_head;
};

#endif // NOANAME_H
