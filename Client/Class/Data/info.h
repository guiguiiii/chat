#ifndef INFO_H
#define INFO_H

#include <QPixmap>

class Info
{
public:
    Info();
    Info(const QString &no, const QString &pwd, const QString &name,
         const QString &signature, const QPixmap &head);

    const QString &no() const;
    void setNo(const QString &newNo);

    const QString &pwd() const;
    void setPWD(const QString &newPwd);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &signature() const;
    void setSignature(const QString &newSignature);

    const QPixmap &head() const;
    void setHead(const QPixmap &newHead);

private:
    QString m_no;
    QString m_pwd;
    QString m_name;
    QString m_signature;
    QPixmap m_head;
};

#endif // INFO_H
