#include "friend.h"

Friend::Friend() :
    m_no(""), m_name(""), m_signature(""), m_nickname(""), m_head(QPixmap())
{

}

const QString &Friend::no() const
{
    return m_no;
}

void Friend::setNo(const QString &newNo)
{
    m_no = newNo;
}

const QString &Friend::name() const
{
    return m_name;
}

void Friend::setName(const QString &newName)
{
    m_name = newName;
}

const QString &Friend::signature() const
{
    return m_signature;
}

void Friend::setSignature(const QString &newSignature)
{
    m_signature = newSignature;
}

const QString &Friend::nickname() const
{
    return m_nickname;
}

void Friend::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}

const QPixmap &Friend::head() const
{
    return m_head;
}

void Friend::setHead(const QPixmap &newHead)
{
    m_head = newHead;
}
