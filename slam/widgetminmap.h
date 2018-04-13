#ifndef WIDGETMINMAP_H
#define WIDGETMINMAP_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include "widgetmaxmap.h"


class WidgetMinmap : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMinmap(QWidget *parent = nullptr);
    ~WidgetMinmap();
    int m_size;
    WidgetMaxmap *m_prelamap;
    QRect m_rect;
    QSize m_mapsize;



    int m_timevent;
    void timerEvent(QTimerEvent *event);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void minclick(QPoint);
public slots:
    void updateShowarea(QRect ,QSize);
};

#endif // WIDGETMINMAP_H
