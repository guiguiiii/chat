#ifndef WIDGET_HEAD_H
#define WIDGET_HEAD_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Widget_Head;
}

class Widget_Head : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Head(QWidget *parent, const QPixmap &head);
    ~Widget_Head();

private:
    Ui::Widget_Head *ui;

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // WIDGET_HEAD_H
