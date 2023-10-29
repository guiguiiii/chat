#include "mail.h"

Mail::Mail() :
    m_no(0), m_sender(""), m_date(""), m_title(""), m_text(""), m_type("")
{

}

Mail::Mail(int newNo, const QString &newSender, const QString &newDate,
           const QString &newTitle, const QString &newText, const QString &newType) :
    m_no(newNo), m_sender(newSender), m_date(newDate), m_title(newTitle), m_text(newText), m_type(newType)
{

}

int Mail::no() const
{
    return m_no;
}

void Mail::setNo(int newNo)
{
    m_no = newNo;
}

const QString &Mail::sender() const
{
    return m_sender;
}

void Mail::setSender(const QString &newSender)
{
    m_sender = newSender;
}

const QString &Mail::date() const
{
    return m_date;
}

void Mail::setDate(const QString &newDate)
{
    m_date = newDate;
}

const QString &Mail::title() const
{
    return m_title;
}

void Mail::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

const QString &Mail::text() const
{
    return m_text;
}

void Mail::setText(const QString &newText)
{
    m_text = newText;
}

const QString &Mail::type() const
{
    return m_type;
}

void Mail::setType(const QString &newType)
{
    m_type = newType;
}
