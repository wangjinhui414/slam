#include "widgetctrl.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QShortcut>

WidgetCtrl::WidgetCtrl(QWidget *parent) : QWidget(parent)
{
/**************************控件布局*************************************/
    m_comvehicle = new QComboBox;
    m_comstart = new QComboBox;
    m_comend = new QComboBox;
    m_compath = new QComboBox;
    m_lablistpath = new QLabel(QStringLiteral("固定路径:"));
    m_lablestart = new QLabel(QStringLiteral("起始站点:"));
    m_lableend = new QLabel(QStringLiteral("目标站点:"));
    m_buttonss = new QPushButton(QStringLiteral("站点执行"));
    m_buttonconpath = new QPushButton(QStringLiteral("路径执行"));
    m_buttonsc = new QPushButton(QStringLiteral("停止任务"));
    m_buttonup = new QPushButton(QStringLiteral("↑"));
    m_buttonleft = new QPushButton(QStringLiteral("←"));
    m_buttonright = new QPushButton(QStringLiteral("→"));
    m_buttondown = new QPushButton(QStringLiteral("↓"));
    m_buttonstop = new QPushButton(QStringLiteral("||"));
    m_buttonsetpos = new QPushButton(QStringLiteral("测试按钮"));
    m_btneditstd = new QPushButton(QStringLiteral("站点编辑"));
    m_buttonvedio = new QPushButton(QStringLiteral("视频监控"));
    m_btleftlight = new QPushButton(QStringLiteral("左闪开"));
    m_btrightlight = new QPushButton(QStringLiteral("右闪开"));
    m_bdoublelight = new QPushButton(QStringLiteral("双闪开"));
    m_btgreenlight = new QPushButton(QStringLiteral("绿灯开"));
    m_btyellowlight = new QPushButton(QStringLiteral("黄灯开"));
    m_btbluelight = new QPushButton(QStringLiteral("蓝灯开"));
    m_btsetvolt = new QPushButton(QStringLiteral("设置电压伐值"));
    m_comlock= new QComboBox;
    m_btunlock = new QPushButton(QStringLiteral("开锁"));
    m_comjdq = new QComboBox;
    m_btjdqon = new QPushButton(QStringLiteral("开"));
    m_btjdqoff = new QPushButton(QStringLiteral("断"));

    QGridLayout *pLayout = new QGridLayout();
    pLayout->setGeometry(rect());
    pLayout->addWidget(m_comvehicle,0,0,1,3);
    pLayout->addWidget(m_lablistpath,1,0,1,1);
    pLayout->addWidget(m_compath,1,1,1,2);

    pLayout->addWidget(m_lablestart,2,0,1,1);
    pLayout->addWidget(m_comstart,2,1,1,2);
    pLayout->addWidget(m_lableend,3,0,1,1);
    pLayout->addWidget(m_comend,3,1,1,2);
    pLayout->addWidget(m_buttonss,4,0,1,1);
    pLayout->addWidget(m_buttonconpath,4,1,1,1);
    pLayout->addWidget(m_buttonsc,4,2,1,1);
    pLayout->addWidget(NULL,5,0,1,3);

    pLayout->addWidget(m_buttonsetpos,6,0,1,1);
    pLayout->addWidget(m_btneditstd,6,1,1,1);
    pLayout->addWidget(m_buttonvedio,6,2,1,1);
    pLayout->addWidget(m_buttonup,7,1,1,1);
    pLayout->addWidget(m_buttonstop,7,2,1,1);
    pLayout->addWidget(m_buttonleft,8,0,1,1);
    pLayout->addWidget(m_buttondown,8,1,1,1);
    pLayout->addWidget(m_buttonright,8,2,1,1);

    pLayout->addWidget(m_btleftlight,9,0,1,1);
    pLayout->addWidget(m_btrightlight,9,1,1,1);
    pLayout->addWidget(m_bdoublelight,9,2,1,1);
    pLayout->addWidget(m_btgreenlight,10,0,1,1);
    pLayout->addWidget(m_btyellowlight,10,1,1,1);
    pLayout->addWidget(m_btbluelight,10,2,1,1);
    pLayout->addWidget(m_comjdq,11,0,1,1);
    pLayout->addWidget(m_btjdqon,11,1,1,1);
    pLayout->addWidget(m_btjdqoff,11,2,1,1);

    pLayout->addWidget(m_comlock,12,0,1,1);
    pLayout->addWidget(m_btunlock,12,1,1,1);
    pLayout->addWidget(m_btsetvolt,12,2,1,1);


    // 设置水平间距
    pLayout->setHorizontalSpacing(5);
    // 设置垂直间距
    pLayout->setVerticalSpacing(5);
    // 设置外间距
    pLayout->setContentsMargins(5, 5, 5, 5);
    pLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    pLayout->setColumnMinimumWidth(0,15);
    pLayout->setColumnMinimumWidth(1,15);
    pLayout->setColumnMinimumWidth(2,15);
    setLayout(pLayout);
/**************************信号事件绑定*************************************/
    connect(m_comvehicle,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(commVehicleChange(const QString &)));
    connect(m_buttonss,SIGNAL(clicked()),this,SLOT(startTask()));
    connect(m_buttonsc,SIGNAL(clicked()),this,SLOT(stopTask()));
    connect(m_buttonup,SIGNAL(clicked()),this,SLOT(up()));
    connect(m_buttonstop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(m_buttondown,SIGNAL(clicked()),this,SLOT(down()));
    connect(m_buttonleft,SIGNAL(clicked()),this,SLOT(left()));
    connect(m_buttonright,SIGNAL(clicked()),this,SLOT(right()));
    connect(m_buttonsetpos,SIGNAL(clicked()),this,SLOT(setvehiclepos()));
    connect(m_btneditstd,SIGNAL(clicked()),this,SLOT(editstd()));
    connect(m_buttonconpath,SIGNAL(clicked()),this,SLOT(pathrun()));
    connect(m_buttonvedio,SIGNAL(clicked()),this,SLOT(dlgvedio()));

    connect(m_btleftlight,SIGNAL(clicked()),this,SLOT(btleftlight()));
    connect(m_btrightlight,SIGNAL(clicked()),this,SLOT(btrightlight()));
    connect(m_bdoublelight,SIGNAL(clicked()),this,SLOT(btdoublelight()));
    connect(m_btgreenlight,SIGNAL(clicked()),this,SLOT(btgreenlight()));
    connect(m_btyellowlight,SIGNAL(clicked()),this,SLOT(btyellowlight()));
    connect(m_btbluelight,SIGNAL(clicked()),this,SLOT(btbluelight()));
    connect(m_btjdqon,SIGNAL(clicked()),this,SLOT(btjdqon()));
    connect(m_btjdqoff,SIGNAL(clicked()),this,SLOT(btjdqoff()));
    connect(m_btsetvolt,SIGNAL(clicked()),this,SLOT(btsetvlot()));
    connect(m_btunlock,SIGNAL(clicked()),this,SLOT(btunlock()));
/**************************控件初始化*************************************/
    //载入在线小车
    QVector<QString> qvstr = g_comser.GetVehicleList();
    for(QVector<QString>::iterator it = qvstr.begin();it!=qvstr.end();++it)
    {
        m_comvehicle->addItem(*it);
    }
    g_comser.SetOperateVehicle(m_comvehicle->currentText());
    //载入可选站点
    m_flgstd = false;
    if(g_database.GetNodesTab(&m_nodes))
    {
        QMap<int,DatabaseData::TYPE_NODES>::const_iterator it;
        for(it = m_nodes.constBegin();it!=m_nodes.constEnd();++it)
        {
            DatabaseData::TYPE_NODES ntemp = it.value();
            m_comstart->addItem(QString::number(ntemp.id) + "-" + ntemp.name);
            m_comend->addItem(QString::number(ntemp.id) + "-" + ntemp.name);
        }
    }

    //获取固定路径
    QVector<QString> qvpath = g_comser.GetVehicleConstPathList();
    QVector<QString>::const_iterator it;
    for(it = qvpath.constBegin();it!=qvpath.constEnd();++it)
    {
        m_compath->addItem(*it);
    }

    for(int i=1;i!=17;i++)
    {
        m_comjdq->addItem(/*QStringLiteral("继电器")+*/QString::number(i));
    }
    m_comjdq->addItem(QStringLiteral("全部"));
    for(int i=1;i!=7;i++)
    {
        m_comlock->addItem(/*QStringLiteral("继电器")+*/QString::number(i));
    }
    m_timevent = startTimer(1000);

    QShortcut *keyu = new QShortcut(QKeySequence(Qt::Key_Up),this);
    QShortcut *keyd = new QShortcut(QKeySequence(Qt::Key_Down),this);
    QShortcut *keyl = new QShortcut(QKeySequence(Qt::Key_Left),this);
    QShortcut *keyr = new QShortcut(QKeySequence(Qt::Key_Right),this);
    QShortcut *keys = new QShortcut(QKeySequence(Qt::Key_S),this);
    connect(keyu, SIGNAL(activated()), m_buttonup, SLOT(click()));
    connect(keyd, SIGNAL(activated()), m_buttondown, SLOT(click()));
    connect(keyl, SIGNAL(activated()), m_buttonleft, SLOT(click()));
    connect(keyr, SIGNAL(activated()), m_buttonright, SLOT(click()));
    connect(keys, SIGNAL(activated()), m_buttonstop, SLOT(click()));
}
WidgetCtrl::~WidgetCtrl()
{
    if(m_timevent)
        QObject::killTimer(m_timevent);
}

void WidgetCtrl::timerEvent(QTimerEvent *event)
{
     event = event;
     QVector<QString> qvstr = g_comser.GetVehicleList();
     if(qvstr.size()!=m_comvehicle->count())
     {
         m_comvehicle->clear();
         for(QVector<QString>::iterator it = qvstr.begin();it!=qvstr.end();++it)
         {
             m_comvehicle->addItem(*it);
         }
     }
     QVector<QString> qvpath = g_comser.GetVehicleConstPathList();
     if(qvpath.size()!=m_compath->count())
     {
         m_compath->clear();
         QVector<QString>::const_iterator it;
         for(it = qvpath.constBegin();it!=qvpath.constEnd();++it)
         {
             m_compath->addItem(*it);
         }
     }


}


void WidgetCtrl::commVehicleChange(const QString &vehicle)
{
    g_comser.SetOperateVehicle(vehicle);
}
void msleep(int time)
{
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.msecsTo(now)<=time);
}
void WidgetCtrl::startTask()
{
//    comserver::TYPE_ROBOT_STATUS status;
//    g_comser.GetVehicleStatus(&status);
//    if(status.run_status>0)
//    {
//        QMessageBox::warning(this,QStringLiteral("警告！"),QStringLiteral("车辆正在执行其他任务！"),QMessageBox::Ok);
//    }
//    else
//    {
//        QString strs = m_comstart->currentText();
//        QString stre = m_comend->currentText();
//        int istart = strs.split("-").takeFirst().toInt();
//        int iend = stre.split("-").takeFirst().toInt();
//        QVector<QString> allpath = g_comser.GetVehicleConstPathList();
//        for(QVector<QString>::iterator it = allpath.begin();it!=allpath.end();++it)
//        {
//            QString spath = *it;
//            QStringList sltmp = spath.split("-");
//            if(sltmp.takeFirst() == strs && sltmp.takeLast() == stre)
//            {
//                g_comser.RunPath(spath);
//                return;
//            }
//        }
//        if(g_comser.CreatePath(istart,iend))
//        {
//            startTask();
//        }
//        else
//        {
//            QMessageBox::warning(this,QStringLiteral("警告！"),QStringLiteral("生成路径失败！"),QMessageBox::Ok);
//        }
//    }
    QString strs = m_comstart->currentText();
    QString stre = m_comend->currentText();
    int istart = strs.split("-").takeFirst().toInt();
    int iend = stre.split("-").takeFirst().toInt();
    g_comser.CreatePath(istart,iend);
    msleep(500);
    QVector<QString> qvpath = g_comser.GetVehicleConstPathList();
    QVector<QString>::const_iterator it;
    for(it = qvpath.constBegin();it!=qvpath.constEnd();++it)
    {
        m_compath->addItem(*it);
    }
}

void WidgetCtrl::stopTask()
{
    g_comser.StopRobot();
}

void WidgetCtrl::up()
{
    g_comser.RobotForwardRecode();
}

void WidgetCtrl::stop()
{
     g_comser.RobotPauseRecode();
}

void WidgetCtrl::down()
{
    g_comser.RobotBackWardRecode();
}

void WidgetCtrl::left()
{
    g_comser.RobotTurnLeftRecode();
}

void WidgetCtrl::right()
{
    g_comser.RobotTurnRightRecode();
}
void WidgetCtrl::setvehiclepos()
{
    g_comser.GetLaserData(&m_laserdata);

    return;

//    QInputDialog dlg;
//    QString str = dlg.getText(this,QStringLiteral("输入坐标x1,y1,x2,y2"),QStringLiteral("位置"));
//    QStringList strlist = str.split(QStringLiteral(","));
//    if(strlist.size() == 4)
//    {
//        QString strx1 = strlist.takeAt(0);
//        QString stry1 = strlist.takeAt(0);
//        QString strx2 = strlist.takeAt(0);
//        QString stry2 = strlist.takeAt(0);
//        if(g_comser.SetVehiclePos(strx1.toDouble(),stry1.toDouble(),strx2.toDouble(),stry2.toDouble()))
//        {
//            QString strok = strx1+ "," + stry1 + "-" +
//                         strx2 + "," + stry2;
//            QMessageBox::information(this,QStringLiteral("设置成功"),strok);//,QMessageBox::Ok);
//        }
//        else
//        {
//            QString strok = strx1+ "," + stry1 + "-" +
//                         strx2 + "," + stry2;
//            QMessageBox::information(this,QStringLiteral("设置失败"),strok);//,QMessageBox::Ok);
//        }
//    }
}
void WidgetCtrl::editstd()
{
    if(m_btneditstd->text() == QStringLiteral("站点编辑"))
    {
        m_flgstd = true;
        m_btneditstd->setText(QStringLiteral("保存编辑"));
    }
    else if(m_btneditstd->text() == QStringLiteral("保存编辑"))
    {
        g_database.UpdateNodesTab(&m_nodes);
        m_flgstd = false;
        m_btneditstd->setText(QStringLiteral("站点编辑"));
        m_nodes.clear();
        if(g_database.GetNodesTab(&m_nodes))
        {
            m_comstart->clear();
            m_comend->clear();
            QMap<int,DatabaseData::TYPE_NODES>::const_iterator it;
            for(it = m_nodes.constBegin();it!=m_nodes.constEnd();++it)
            {
                DatabaseData::TYPE_NODES ntemp = it.value();
                m_comstart->addItem(QString::number(ntemp.id) + "-" + ntemp.name);
                m_comend->addItem(QString::number(ntemp.id) + "-" + ntemp.name);
            }
        }
    }
}
void WidgetCtrl::pathrun()
{
    g_comser.RunPath(m_compath->currentText());
}

void WidgetCtrl::dlgvedio()
{
    QProcess *process;
    process = new QProcess();
    process->start("./VideoAudio/VideoAudio.exe myrobot");
}

void WidgetCtrl::btleftlight()
{
    if(m_btleftlight->text() == QStringLiteral("左闪开"))
    {
        g_comser.LeftTW("1");
        m_btleftlight->setText(QStringLiteral("左闪关"));
    }
    else if(m_btleftlight->text() == QStringLiteral("左闪关"))
    {
        g_comser.LeftTW("0");
        m_btleftlight->setText(QStringLiteral("左闪开"));
    }
}

void WidgetCtrl::btrightlight()
{
    if(m_btrightlight->text() == QStringLiteral("右闪开"))
    {
        g_comser.RightTW("1");
        m_btrightlight->setText(QStringLiteral("右闪关"));
    }
    else if(m_btrightlight->text() == QStringLiteral("右闪关"))
    {
        g_comser.RightTW("0");
        m_btrightlight->setText(QStringLiteral("右闪开"));
    }
}

void WidgetCtrl::btdoublelight()
{
    if(m_bdoublelight->text() == QStringLiteral("双闪开"))
    {
        g_comser.LeftRightTW("1");
        m_bdoublelight->setText(QStringLiteral("双闪关"));
    }
    else if(m_bdoublelight->text() == QStringLiteral("双闪关"))
    {
        g_comser.LeftRightTW("0");
        m_bdoublelight->setText(QStringLiteral("双闪开"));
    }
}

void WidgetCtrl::btgreenlight()
{
    if(m_btgreenlight->text() == QStringLiteral("绿灯开"))
    {
        g_comser.GreenTW("1");
        m_btgreenlight->setText(QStringLiteral("绿灯关"));
    }
    else if(m_btgreenlight->text() == QStringLiteral("绿灯关"))
    {
        g_comser.GreenTW("0");
        m_btgreenlight->setText(QStringLiteral("绿灯开"));
    }
}

void WidgetCtrl::btyellowlight()
{
    if(m_btyellowlight->text() == QStringLiteral("黄灯开"))
    {
        g_comser.YellowTW("1");
        m_btyellowlight->setText(QStringLiteral("黄灯关"));
    }
    else if(m_btyellowlight->text() == QStringLiteral("黄灯关"))
    {
        g_comser.YellowTW("0");
        m_btyellowlight->setText(QStringLiteral("黄灯开"));
    }
}

void WidgetCtrl::btbluelight()
{
    if(m_btbluelight->text() == QStringLiteral("蓝灯开"))
    {
        g_comser.BlueTW("1");
        m_btbluelight->setText(QStringLiteral("蓝灯关"));
    }
    else if(m_btbluelight->text() == QStringLiteral("蓝灯关"))
    {
        g_comser.BlueTW("0");
        m_btbluelight->setText(QStringLiteral("蓝灯开"));
    }
}

void WidgetCtrl::btsetvlot()
{
    QInputDialog dlg;
    QString readvlot = g_comser.ReadSOC();
    double vlot = dlg.getDouble(this,QStringLiteral("当前电压:")+readvlot,QStringLiteral("电压阈值"));
    g_comser.SetVolt(QString("%1").arg(vlot));
}

void WidgetCtrl::btunlock()
{
    QString str = m_comlock->currentText();
    g_comser.Unlock(str);
}

void WidgetCtrl::btjdqon()
{
   QString str = m_comjdq->currentText();
   if(str == QStringLiteral("全部"))
   {
        g_comser.OneRelayOnoff(str,"1");
   }
   else
   {
        g_comser.AllRelayOn();
   }

}

void WidgetCtrl::btjdqoff()
{
    QString str = m_comjdq->currentText();
    if(str == QStringLiteral("全部"))
    {
         g_comser.OneRelayOnoff(str,"0");
    }
    else
    {
         g_comser.AllRelayOff();
    }
}

