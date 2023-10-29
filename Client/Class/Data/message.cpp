#include "message.h"

Message::Message() :
    m_sender(""), m_receiver(""), m_date(""), m_text("")
{

}


Message::Message(const QString &sender, const QString &receiver,
                 const QString &date, const QString &text)
    : m_sender(sender), m_receiver(receiver), m_date(date), m_text(text)
{

}

const QString &Message::sender() const
{
    return m_sender;
}

void Message::setSender(const QString &newSender)
{
    m_sender = newSender;
}

const QString &Message::receiver() const
{
    return m_receiver;
}

void Message::setReceiver(const QString &newReceiver)
{
    m_receiver = newReceiver;
}

const QString &Message::date() const
{
    return m_date;
}

void Message::setDate(const QString &newDate)
{
    m_date = newDate;
}

const QString &Message::text() const
{
    return m_text;
}

void Message::setText(const QString &newText)
{
    m_text = newText;
}
