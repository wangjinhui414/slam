#include "widgetmaxmap.h"
#include <QtMath>



WidgetMaxmap::WidgetMaxmap(QWidget *parent) : QWidget(parent)
{
    m_mapsize = QPixmap(MAP_PATH).size();
    m_flagmapmove = false;
    //初始化地图居中
    QRect rect = this->rect();
    m_showpos = QPoint(m_mapsize.width()/2 - rect.width() , m_mapsize.height()/2 - rect.height());
    m_timevent = startTimer(300);

    m_point.setX(4096);
    m_point.setY(4096);

    m_menu = new QMenu(this);
    m_addst = new QAction(QStringLiteral("新增站点"));
    m_delst = new QAction(QStringLiteral("删除站点"));
    m_linkst = new QAction(QStringLiteral("连接到"));
    m_editst = new QAction(QStringLiteral("编辑站点"));
    m_setpos = new QAction(QStringLiteral("定位设置"));

    connect(m_addst,SIGNAL(triggered(bool)),this,SLOT(recvaddst()));
    connect(m_delst,SIGNAL(triggered(bool)),this,SLOT(recvdelst()));
    connect(m_linkst,SIGNAL(triggered(bool)),this,SLOT(recvlinkst()));
    connect(m_editst,SIGNAL(triggered(bool)),this,SLOT(recveditst()));
    connect(m_setpos,SIGNAL(triggered(bool)),this,SLOT(recvsetpos()));
}

WidgetMaxmap::~WidgetMaxmap()
{
    if(m_timevent)
        QObject::killTimer(m_timevent);
}

//求箭头两点坐标
void WidgetMaxmap::calcVertexes(double start_x, double start_y, double end_x, double end_y, double& x1, double& y1, double& x2, double& y2)
{
    double arrow_lenght_ = 10;//箭头长度，一般固定
    double arrow_degrees_ = 0.5;//箭头角度，一般固定

    double angle = atan2(end_y - start_y, end_x - start_x) + 3.1415926;//

    x1 = end_x + arrow_lenght_ * cos(angle - arrow_degrees_);//求得箭头点1坐标
    y1 = end_y + arrow_lenght_ * sin(angle - arrow_degrees_);
    x2 = end_x + arrow_lenght_ * cos(angle + arrow_degrees_);//求得箭头点2坐标
    y2 = end_y + arrow_lenght_ * sin(angle + arrow_degrees_);
}
void WidgetMaxmap::paintEvent(QPaintEvent *event)
{
    event = event;
    //绘制地图图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(MAP_PATH);
    QRect rect = this->rect();
    painter.drawPixmap(rect,pix.copy(m_showpos.x(),m_showpos.y(),rect.width(),rect.height()));
    //绘制坐标信息
    QString str;
    QPoint curpos = mapFromGlobal(QCursor::pos());
    quint32 curx = m_showpos.x()+curpos.x();
    quint32 cury = m_showpos.y()+curpos.y();
    double slx = ((double)curx-4096)*0.05;
    double sly = ((double)cury-4096)*-0.05;
    str.sprintf("MAP:%d,%d|CUR:%d,%d|SL:%.4f,%.4f",m_showpos.x(),m_showpos.y(),curx,cury,slx,sly);
    painter.drawText(QRectF(0,0,300,50),str);
    //绘制站点信息
    if(m_widctrl->m_flgstd == true)
    {
        for(QMap<int,DatabaseData::TYPE_NODES>::const_iterator it = m_widctrl->m_nodes.constBegin();
            it!=m_widctrl->m_nodes.constEnd();++it)
        {
            DatabaseData::TYPE_NODES ntemp = it.value();
            painter.setBrush(Qt::red);
            QPoint dtxpos = QPoint(ntemp.x,ntemp.y)-m_showpos;
            painter.drawEllipse(dtxpos,5,5);
            painter.drawText(QRectF(dtxpos.x()+8,dtxpos.y()-10,100,50),QString::number(ntemp.id,10));
            for(QVector<quint32>::const_iterator jt = ntemp.adjucentnode.constBegin();jt != ntemp.adjucentnode.constEnd();++jt)
            {
                DatabaseData::TYPE_NODES lnode = m_widctrl->m_nodes[*jt];
                QPoint startpo = QPoint(ntemp.x,ntemp.y)-m_showpos;
                QPoint endpo = QPoint(lnode.x,lnode.y)-m_showpos;
                double x1,y1,x2,y2;
                calcVertexes(startpo.x(),startpo.y(),endpo.x(),endpo.y(),x1,y1,x2,y2);
                painter.drawLine(startpo,endpo);
                painter.drawLine((QPointF)endpo,QPointF(x1,y1));
                painter.drawLine((QPointF)endpo,QPointF(x2,y2));
            }

        }
    }
    else
    {

    }
    //绘制车辆位置点
    painter.setBrush(Qt::blue);
    //painter.drawEllipse(m_point-m_showpos,5,5);
    QRect rect_top = QRect(m_point-m_showpos-QPoint(5,5),m_point-m_showpos+QPoint(5,5));
    // 扇形起始角度
    int startAngle = (45+m_cdir) * 16;
    // 扇形覆盖范围（120度的）
    int spanAngle = 270 * 16;
    painter.drawPie(rect_top, startAngle, spanAngle);
    //绘制定位线
    if(m_startpot != QPoint(0,0))
    {
        QPoint curpos = mapFromGlobal(QCursor::pos());
        painter.drawLine(m_startpot-m_showpos,curpos);
    }
    //更新小视图
    minMapChange();
}

void WidgetMaxmap::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        m_flagmapmove = true;
    }
    m_stapoint = event->pos();

    //站点编辑连接
    if(m_flaglink == true)
    {
        QPoint snp = mapFromGlobal(QCursor::pos())+m_showpos;
        for(QMap<int,DatabaseData::TYPE_NODES>::iterator it = m_widctrl->m_nodes.begin();
            it!=m_widctrl->m_nodes.end();++it)
        {
            DatabaseData::TYPE_NODES ntemp = it.value();
            if(QRect(ntemp.x-3,ntemp.y-3,6,6).contains(snp))
            {
                m_widctrl->m_nodes[m_linksid].adjucentnode.push_back(it.value().id);
                quint32 twopdis = 10000000;
                quint32 x1 = m_widctrl->m_nodes[m_linksid].x;
                quint32 y1 = m_widctrl->m_nodes[m_linksid].y;
                quint32 x2 = it.value().x;
                quint32 y2 = it.value().y;
                twopdis = qSqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
                m_widctrl->m_nodes[m_linksid].adjucentdis.push_back(twopdis);
                break;
            }
        }
        setCursor(Qt::ArrowCursor);
        m_flaglink = false;
    }
    if(event->button() == Qt::LeftButton && m_startpot != QPoint(0,0))
    {
        QPoint curpos = mapFromGlobal(QCursor::pos());
        quint32 px = m_showpos.x()+curpos.x();
        quint32 py = m_showpos.y()+curpos.y();
        double slx1 = ((double)m_startpot.x()-4096)*0.05;
        double sly1 = ((double)m_startpot.y()-4096)*-0.05;
        double slx2 = ((double)px-4096)*0.05;
        double sly2 = ((double)py-4096)*-0.05;
        g_comser.SetVehiclePos(slx1,sly1,slx2,sly2);
        m_startpot = QPoint(0,0);
    }

}

void WidgetMaxmap::mouseReleaseEvent(QMouseEvent *event)
{
    event = event;
    if(event->button() == Qt::MidButton)
    {
        m_flagmapmove = false;
    }
}

void WidgetMaxmap::mouseDoubleClickEvent(QMouseEvent *event)
{
    event = event;

}

void WidgetMaxmap::mouseMoveEvent(QMouseEvent *event)
{
    m_curpos = event->pos();
    if(m_flagmapmove == true)
    {
        m_showpos = m_showpos - (event->pos() - m_stapoint);
        if(m_showpos.x() < 0)
            m_showpos.setX(0);
        if(m_showpos.y() < 0)
            m_showpos.setY(0);
        if(m_showpos.x() > (m_mapsize.width() - rect().width()))
            m_showpos.setX(m_mapsize.width() - rect().width());
        if(m_showpos.y() > (m_mapsize.height() - rect().height()))
            m_showpos.setY(m_mapsize.height() - rect().height());
        m_stapoint = event->pos();

    }
    update();
}

void WidgetMaxmap::contextMenuEvent(QContextMenuEvent *event)
{
    event = event;
    m_menu->clear();
    if(m_widctrl->m_flgstd == false)
    {
        m_menu->addAction(m_setpos);
    }
    else
    {
        m_menu->addAction(m_addst);
        m_menu->addAction(m_delst);
        m_menu->addAction(m_linkst);
        m_menu->addAction(m_editst);
    }
        m_menu->move(cursor().pos());
        m_menu->show();

}
void WidgetMaxmap::recvaddst()
{
    for (int i = 0; i != 1000; i++)
    {
        if(m_widctrl->m_nodes.count(i)<=0)
        {
            QString name = "";
            quint8 ntype = 0;
            DatabaseData::TYPE_NODES tab_node;
            tab_node.name = name;
            tab_node.x = m_showpos.x()+mapFromGlobal(m_menu->pos()).x();
            tab_node.y = m_showpos.y()+mapFromGlobal(m_menu->pos()).y();
            tab_node.type = ntype;
            tab_node.id = i;
            m_widctrl->m_nodes[i] = tab_node;
            break;
        }
    }
}

void WidgetMaxmap::recvdelst()
{
    QPoint snp = mapFromGlobal(m_menu->pos())+m_showpos;
    quint32 did = 0xFFFFFF;
    for(QMap<int,DatabaseData::TYPE_NODES>::iterator it = m_widctrl->m_nodes.begin();
        it!=m_widctrl->m_nodes.end();++it)
    {
        DatabaseData::TYPE_NODES ntemp = it.value();
        if(QRect(ntemp.x-3,ntemp.y-3,6,6).contains(snp))
        {
            did = it.value().id;
            m_widctrl->m_nodes.erase(it);
            break;
        }
    }
    //if(did>=0)
    {
        for(QMap<int,DatabaseData::TYPE_NODES>::iterator it = m_widctrl->m_nodes.begin();
            it!=m_widctrl->m_nodes.end();++it)
        {
            QVector<quint32>::iterator at,bt;
            for(at = it->adjucentnode.begin(),bt = it->adjucentdis.begin()
                ;at!=it->adjucentnode.end();++at,++bt)
            {
                if(*at == did)
                {
                    it->adjucentnode.erase(at);
                    it->adjucentdis.erase(bt);
                    at--;
                    bt--;
                }
            }
        }
    }
}

void WidgetMaxmap::recvlinkst()
{
    QPoint snp = mapFromGlobal(m_menu->pos())+m_showpos;
    for(QMap<int,DatabaseData::TYPE_NODES>::iterator it = m_widctrl->m_nodes.begin();
        it!=m_widctrl->m_nodes.end();++it)
    {
        DatabaseData::TYPE_NODES ntemp = it.value();
        if(QRect(ntemp.x-3,ntemp.y-3,6,6).contains(snp))
        {
            m_linksid = ntemp.id;
            m_flaglink = true;
            setCursor(Qt::CrossCursor);
            break;
        }
    }
}

void WidgetMaxmap::recveditst()
{

}

void WidgetMaxmap::recvsetpos()
{
   // QPoint curpos = mapFromGlobal(QCursor::pos());
//    quint32 curx = m_showpos.x()+mapFromGlobal(m_menu->pos()).x();
//    quint32 cury = m_showpos.y()+mapFromGlobal(m_menu->pos()).y();
//    double slx = ((double)curx-4096)*0.05;
//    double sly = ((double)cury-4096)*-0.05;
//    g_comser.SetVehiclePos(slx,sly,slx+0.01,sly+0.01);
 //   flaglaser = !flaglaser;

     quint32 curx = m_showpos.x()+mapFromGlobal(m_menu->pos()).x();
     quint32 cury = m_showpos.y()+mapFromGlobal(m_menu->pos()).y();
     m_startpot = QPoint(curx,cury);

}
void WidgetMaxmap::minMapChange()
{
    emit showchange(QRect(m_showpos.x(),m_showpos.y(),rect().width(),rect().height()),m_mapsize);
}

void WidgetMaxmap::recvminclick(QPoint point)
{
    m_showpos.setX(point.x()-rect().width()/2);
    m_showpos.setY(point.y()-rect().height()/2);
    update();
}

void WidgetMaxmap::recvSemVehiclePosChange(QVector<QPoint>)
{


}

void WidgetMaxmap::timerEvent(QTimerEvent *event)
{
    event = event;
    comserver::TYPE_VEHICLEPOS vpos;
    g_comser.GetVehiclePos(&vpos);
    vpos.x = vpos.x/0.05+4096;
    vpos.y = -vpos.y/0.05+4096;
    m_point.setX(vpos.x);
    m_point.setY(vpos.y);
    m_cdir = vpos.th>0 ? vpos.th : (2*3.1415+vpos.th);
    m_cdir = m_cdir*360/(2*3.1415);

    update();
}
