#ifndef MAIL_H
#define MAIL_H

#include <QString>

class Mail
{
public:
    Mail();
    Mail(int newNo, const QString &newSender, const QString &newDate,
         const QString &newTitle, const QString &newText, const QString &newType);

    int no() const;
    void setNo(int newNo);

    const QString &sender() const;
    void setSender(const QString &newSender);

    const QString &date() const;
    void setDate(const QString &newDate);

    const QString &title() const;
    void setTitle(const QString &newTitle);

    const QString &text() const;
    void setText(const QString &newText);

    const QString &type() const;
    void setType(const QString &newType);

private:
    int m_no;
    QString m_sender;
    QString m_date;
    QString m_title;
    QString m_text;
    QString m_type;
};

#endif // MAIL_H
