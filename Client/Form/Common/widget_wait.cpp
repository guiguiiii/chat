#include "widget_wait.h"
#include "ui_widget_wait.h"

Widget_Wait::Widget_Wait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Wait)
{
    ui->setupUi(this);
}

Widget_Wait::~Widget_Wait()
{
    delete ui;
}
