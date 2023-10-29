#ifndef WIDGET_WAIT_H
#define WIDGET_WAIT_H

#include <QWidget>

namespace Ui {
class Widget_Wait;
}

class Widget_Wait : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Wait(QWidget *parent = nullptr);
    ~Widget_Wait();

private:
    Ui::Widget_Wait *ui;
};

#endif // WIDGET_WAIT_H
