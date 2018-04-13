#ifndef WIDGETMAXMAP_H
#define WIDGETMAXMAP_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QMoveEvent>
#include <QMenu>
#include <QAction>
#include "widgetctrl.h"
#include "memdata.h"


class WidgetMaxmap : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMaxmap(QWidget *parent = nullptr);
    ~WidgetMaxmap();

    bool m_flagmapmove;//拖拽地图标志
    QPoint m_stapoint;//拖拽地图上个起始点
    QSize  m_mapsize;//地图的大小
    QPoint m_showpos;//地图显示的左上坐标位置
    QPoint m_curpos;//鼠标当前位置
    void minMapChange();

    WidgetCtrl *m_widctrl;

    QPoint m_point;//选定车辆坐标
    double m_cdir;//选定车辆方向
    int m_timevent;

    //站点编辑菜单
    QMenu *m_menu;
    QAction *m_addst;
    QAction *m_delst;
    QAction *m_linkst;
    QAction *m_editst;
    QAction *m_setpos;
    quint32 m_linksid;
    bool m_flaglink;
    //激光数据
    QVector<comserver::TYPE_LASERDATA> *m_laserdata;

    //定位数据
    QPoint m_startpot;

    void timerEvent(QTimerEvent *event);
protected:
    void calcVertexes(double start_x, double start_y, double end_x, double end_y, double& x1, double& y1, double& x2, double& y2);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void showchange(QRect ,QSize );
public slots:
    void recvminclick(QPoint);
    void recvSemVehiclePosChange(QVector<QPoint>);

    void recvaddst();
    void recvdelst();
    void recvlinkst();
    void recveditst();
    void recvsetpos();
};

#endif // WIDGETMAXMAP_H
