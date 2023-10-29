#include "form_connect.h"
#include "ui_form_connect.h"

#include "form_login.h"
#include "Class/DataAccess/myfile.h"

Form_Connect::Form_Connect(QWidget *parent,Socket *socket) :
    QWidget(parent),
    ui(new Ui::Form_Connect)
{
    ui->setupUi(this);
    this->socket = socket;
    connect(socket, &Socket::connected, this, &Form_Connect::f_connected);
    this->init();
    this->on_btn_retry_clicked();
}


Form_Connect::~Form_Connect()
{
    delete ui;
}


void Form_Connect::on_btn_set_clicked()
{
    ui->lb_title->setVisible(0);
    ui->btn_set->setVisible(0);
    ui->btn_retry->setVisible(0);
    ui->Group_Set->setVisible(1);
}


void Form_Connect::on_btn_cancel_clicked()
{
    ui->Group_Set->setVisible(0);
    ui->lb_title->setVisible(1);
    ui->btn_set->setVisible(1);
    ui->btn_retry->setVisible(1);
}


void Form_Connect::on_btn_confirm_clicked()
{
    ui->Group_Set->setVisible(0);
    ui->lb_title->setVisible(1);
    ui->btn_set->setVisible(1);
    ui->btn_retry->setVisible(1);
}


void Form_Connect::on_btn_retry_clicked()
{
    QString addr = ui->le_addr->text();
    QString port = ui->le_port->text();
    socket->connectToHost(addr,port.toInt());
}


void Form_Connect::init()
{
    ui->Group_Set->setVisible(0);
    QVector<QString> ipPort = MyFile().ipPort().split('\n');
    ui->le_addr->setText(ipPort.front());
    ui->le_port->setText(ipPort.back());
}


void Form_Connect::f_connected()
{
    QString addr = ui->le_addr->text();
    QString port = ui->le_port->text();
    MyFile().setIpPort(addr,port);
    (new Form_Login(this,socket))->setVisible(1);
}

