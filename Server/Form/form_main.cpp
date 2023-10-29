#include "form_main.h"
#include "ui_form_main.h"

Form_Main::Form_Main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Main)
{
    ui->setupUi(this);
}


Form_Main::~Form_Main()
{
    delete ui;
}

