#ifndef WIDGET_CHOOSE_H
#define WIDGET_CHOOSE_H

#include <QWidget>

namespace Ui {
class Widget_Choose;
}

class Widget_Choose : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Choose(QWidget *parent);
    explicit Widget_Choose(QWidget *parent,const QString &text);
    explicit Widget_Choose(QWidget *parent,const QString &title,const QString &text);
    ~Widget_Choose();

    void setText(const QString &text);
    void setTitle(const QString &title);
    void setBtnCancel(const QString &text);
    void setBtnConfirm(const QString &text);

private:
    Ui::Widget_Choose *ui;

signals:
    void cancel();
    void confirm();

private slots:
    void on_btn_cancel_clicked();
    void on_btn_confirm_clicked();
};

#endif // WIDGET_CHOOSE_H
