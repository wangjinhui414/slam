#include "widgetminmap.h"

WidgetMinmap::WidgetMinmap(QWidget *parent) : QWidget(parent)
{
    m_size = 250;
    m_timevent = startTimer(500);
}

WidgetMinmap::~WidgetMinmap()
{
    if(m_timevent)
        QObject::killTimer(m_timevent);
}

void WidgetMinmap::paintEvent(QPaintEvent *event)
{
    event = event;

    QPainter painter(this);
    QPixmap pix;
    pix.load(MAP_PATH);
    QRect rect(0,0,m_size,m_size);
    painter.drawPixmap(rect,pix);
    double kx = double(m_size)/m_mapsize.width();
    double ky = double(m_size)/m_mapsize.height();
    QRect rectmin(m_rect.x()*kx,m_rect.y()*ky,
                  m_rect.width()*kx,m_rect.height()*ky);
    painter.drawRect(rectmin);

    painter.setBrush(Qt::blue);
    QPoint potmp = QPoint(m_prelamap->m_point.x()*kx,m_prelamap->m_point.y()*ky);
    painter.drawEllipse(potmp,2,2);
}

void WidgetMinmap::updateShowarea(QRect rect,QSize mapsize)
{
    m_rect = rect;
    m_mapsize = mapsize;
    update();
}

void WidgetMinmap::mousePressEvent(QMouseEvent *event)
{
    double kx = double(m_size)/m_mapsize.width();
    double ky = double(m_size)/m_mapsize.height();
    QPoint rpoint(event->pos().x()/kx,event->pos().y()/ky);

    emit minclick(rpoint);

}
void WidgetMinmap::timerEvent(QTimerEvent *event)
{
    event = event;
    update();
}
