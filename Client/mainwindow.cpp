#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include "Form/form_connect.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->socket = new Socket(this);
    (new Form_Connect(ui->GroupBox_Main,socket));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_close_clicked()
{
    this->deleteLater();
}


void MainWindow::on_btn_minSize_clicked()
{
    this->showMinimized();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        leftBtnPressed = 1;
        startPos.setX(event->globalPosition().x());
        startPos.setY(event->globalPosition().y());
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(leftBtnPressed == 1){
        this->move((this->geometry().topLeft() + event->globalPosition() - startPos).toPoint());
        startPos.setX(event->globalPosition().x());
        startPos.setY(event->globalPosition().y());
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        leftBtnPressed = 0;
    }
}

