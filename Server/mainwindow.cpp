#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Form/form_main.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->server = new Server(this);
    (new Form_Main(ui->Widget))->setVisible(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

