#include "noaname.h"

NoAName::NoAName() :
    m_no(""), m_name(""), m_head(QPixmap())
{

}

NoAName::NoAName(const QString &newNo, const QString &newName) :
    m_no(newNo), m_name(newName), m_head(QPixmap())
{

}

NoAName::NoAName(const QString &newNo, const QString &newName, const QPixmap &newHead) :
    m_no(newNo), m_name(newName), m_head(newHead)
{

}

const QString &NoAName::no() const
{
    return m_no;
}

void NoAName::setNo(const QString &newNo)
{
    m_no = newNo;
}

const QString &NoAName::name() const
{
    return m_name;
}

void NoAName::setName(const QString &newName)
{
    m_name = newName;
}

const QPixmap &NoAName::head() const
{
    return m_head;
}

void NoAName::setHead(const QPixmap &newHead)
{
    m_head = newHead;
}
