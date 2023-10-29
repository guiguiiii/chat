#include "widget_sethead.h"
#include "ui_widget_sethead.h"

#include <QMimeData>
#include <QPainter>

Widget_SetHead::Widget_SetHead(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_SetHead)
{
    ui->setupUi(this);
    this->setAcceptDrops(1);
}


Widget_SetHead::~Widget_SetHead()
{
    delete ui;
}


QPixmap& Widget_SetHead::pixmapToRound(QPixmap &pixmap, int radius)
{
    if(pixmap.isNull()){
        return pixmap;
    }
    int diameter = 2 * radius;

    //裁剪成正方形
    int w = pixmap.width();
    int h = pixmap.height();
    if( w > h ){
        int x = ( w - h ) / 2;
        pixmap = pixmap.copy(x,0,h,h);
    }else if( w < h ){
        int y = ( h - w ) / 2;
        pixmap = pixmap.copy(0,y,w,w);
    }

    //等比例缩放
    pixmap = pixmap.scaled(diameter,diameter);

    //裁剪成圆形
    QBitmap mark(diameter,diameter);
    QPainter painter(&mark);
    painter.fillRect(0,0,diameter,diameter,Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawRoundedRect(0,0,diameter,diameter,radius,radius);
    pixmap.setMask(mark);
    return pixmap;
}


void Widget_SetHead::on_btn_cancel_clicked()
{
    this->deleteLater();
}


void Widget_SetHead::on_btn_confirm_clicked()
{
    if(head.cacheKey() != QPixmap().cacheKey()){
        emit setHead(head);
    }
    this->deleteLater();
}


void Widget_SetHead::dragEnterEvent(QDragEnterEvent *ev)
{
    if(ev->mimeData()->hasUrls()){
        ev->acceptProposedAction();
    }else{
        ev->ignore();
    }
}


void Widget_SetHead::dropEvent(QDropEvent *ev)
{
    const QMimeData *mimedata = ev->mimeData();
    if(mimedata->hasUrls()){
        int radius = ui->radius->width() / 2;
        QList<QUrl> urls = mimedata->urls();
        QString filename = urls.front().toLocalFile();
        QPixmap pixmap(filename);
        pixmap = pixmapToRound(pixmap,radius);
        ui->radius->setPixmap(pixmap);
        this->head = pixmap;
    }
}

