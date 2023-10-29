#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message();
    Message(const QString &sender, const QString &receiver,
            const QString &date, const QString &text);

    const QString &sender() const;
    void setSender(const QString &newSender);

    const QString &receiver() const;
    void setReceiver(const QString &newReceiver);

    const QString &date() const;
    void setDate(const QString &newDate);

    const QString &text() const;
    void setText(const QString &newText);

private:
    QString m_sender;
    QString m_receiver;
    QString m_date;
    QString m_text;
};

#endif // MESSAGE_H
