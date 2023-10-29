#ifndef FRIEND_H
#define FRIEND_H

#include <QPixmap>

class Friend
{
public:
    Friend();

    const QString &no() const;
    void setNo(const QString &newNo);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &signature() const;
    void setSignature(const QString &newSignature);

    const QString &nickname() const;
    void setNickname(const QString &newNickname);

    const QPixmap &head() const;
    void setHead(const QPixmap &newHead);

private:
    QString m_no;
    QString m_name;
    QString m_signature;
    QString m_nickname;
    QPixmap m_head;
};

#endif // FRIEND_H
