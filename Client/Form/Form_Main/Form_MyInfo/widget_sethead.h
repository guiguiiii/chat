#ifndef WIDGET_SETHEAD_H
#define WIDGET_SETHEAD_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPixmap>

namespace Ui {
class Widget_SetHead;
}

class Widget_SetHead : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_SetHead(QWidget *parent);
    ~Widget_SetHead();

private:
    Ui::Widget_SetHead *ui;
    QPixmap head;

private:
    QPixmap& pixmapToRound(QPixmap &pixmap,int radius);

signals:
    void setHead(const QPixmap &head);

private slots:
    void on_btn_cancel_clicked();
    void on_btn_confirm_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *ev);
    void dropEvent(QDropEvent *ev);
};

#endif // WIDGET_SETHEAD_H
