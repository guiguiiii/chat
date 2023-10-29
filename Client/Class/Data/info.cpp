#include "info.h"

Info::Info() :
    m_no(""), m_pwd(""), m_name(""), m_signature(""), m_head(QPixmap())
{

}

Info::Info(const QString &no, const QString &pwd, const QString &name,
       const QString &signature, const QPixmap &head) :
    m_no(no), m_pwd(pwd), m_name(name), m_signature(signature), m_head(head)
{

}

const QString &Info::no() const
{
    return m_no;
}

void Info::setNo(const QString &newNo)
{
    m_no = newNo;
}

const QString &Info::pwd() const
{
    return m_pwd;
}

void Info::setPWD(const QString &newPwd)
{
    m_pwd = newPwd;
}

const QString &Info::name() const
{
    return m_name;
}

void Info::setName(const QString &newName)
{
    m_name = newName;
}

const QString &Info::signature() const
{
    return m_signature;
}

void Info::setSignature(const QString &newSignature)
{
    m_signature = newSignature;
}

const QPixmap &Info::head() const
{
    return m_head;
}

void Info::setHead(const QPixmap &newHead)
{
    m_head = newHead;
}
