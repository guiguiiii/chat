#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Class/socket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_close_clicked();
    void on_btn_minSize_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    bool leftBtnPressed;
    QPoint startPos;

    Socket *socket;
};
#endif // MAINWINDOW_H
