#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include <QWidget>

namespace Ui {
class Form_Main;
}

class Form_Main : public QWidget
{
    Q_OBJECT

public:
    Form_Main(QWidget *parent);
    ~Form_Main();

private:
    Ui::Form_Main *ui;
};

#endif // FORM_MAIN_H
