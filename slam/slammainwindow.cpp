#include "slammainwindow.h"
#include "ui_slammainwindow.h"
#include "slamconfig.h"
#include <QProcess>
#include <QDockWidget>
#include <QLayout>
#include <QLabel>

SlamMainWindow::SlamMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlamMainWindow)
{
    ui->setupUi(this);
    /******************************************************************/
//    m_pmaxmap = new WidgetMaxmap;         //大地图centerwidget
//    m_pminmap = new WidgetMinmap;         //小地图widget
//    m_pctrlpane = new WidgetCtrl;       //控制widget
    m_statuslabel = new QLabel();
    this->statusBar()->addWidget(m_statuslabel);

    /******************************************************************/
}


SlamMainWindow::~SlamMainWindow()
{
    delete ui;
}

void SlamMainWindow::trigerMenu(QAction* act)
{
    for(QVector<QDockWidget*>::iterator it = m_showdock.begin();it!=m_showdock.end();++it)
    {
        this->removeDockWidget(*it);
        delete *it;
        m_showdock.erase(it);
        --it;
    }
    m_statuslabel->setText("");


    if (act->text() == QStringLiteral("系统设置"))//"\347\263\273\347\273\237\350\256\276\347\275\256")
    {
        //系统设置菜单被按下
        QMessageBox msgBox;
        msgBox.setText(QStringLiteral("系统设置"));

        msgBox.exec();
    }
    else
    if (act->text() == QStringLiteral("数据库设置"))//"\346\225\260\346\215\256\345\272\223\350\256\276\347\275\256")
    {
        //数据库设置菜单被按下
        /*QMessageBox msgBox;
        msgBox.setText(QStringLiteral("数据库设置"));
        msgBox.exec();*/
        //lkmysql();//这是使用Connector.C++ 1.1连接mysql，下面的方法是使用QT5连接的。
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(DEF_MYSQL_IP);
        db.setPort(DEF_MYSQL_PORT);
        db.setDatabaseName(DEF_MYSQL_DATA);
        db.setUserName(DEF_MYSQL_USER);
        db.setPassword(DEF_MYSQL_PWD);
        if (db.open())
        {
            //qDebug() << "success!";
            QMessageBox msgBox;
            msgBox.setWindowTitle(QStringLiteral("数据库连接"));
            msgBox.setText(QStringLiteral("本地数据库连接成功，可以进行正常操作了。\n\n数据库操作代码由北京大基机器人有限公司提供！"));
            msgBox.exec();


        }
        else{
            //qDebug() << "failure";
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("本地数据库连接失败！"));
            msgBox.exec();
        }
    }
    else
        if (act->text() == QStringLiteral("机器人设置"))
        {

        }
        else

        if (act->text() == QStringLiteral("电梯设置"))
        {
            //电梯设置菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("电梯设置"));

            msgBox.exec();
        }
        else
        if (act->text() == QStringLiteral("站点设置"))
        {
            //站点设置菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("站点设置"));

            msgBox.exec();
        }
        else
        if (act->text() == QStringLiteral("用户管理"))
        {
            //用户管理菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("用户管理"));

            msgBox.exec();
        }
        else
        if (act->text() == QStringLiteral("自动升级"))
        {
            //用户管理菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("自动升级"));
            msgBox.exec();
        }
        else


        if (act->text() == QStringLiteral("路径规划"))//"\350\267\257\345\276\204\350\247\204\345\210\222")
        {
            //路径规划菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("路径规划"));
            msgBox.exec();
            QProcess *process;
            process = new QProcess();
            process->start("./PathEdit.exe");
        }
        else
        if (act->text() == QStringLiteral("任务派发"))
        {
            //任务派发菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("任务派发"));
            msgBox.exec();
            //设置主地图
             m_pmaxmap = new WidgetMaxmap;
             m_pminmap = new WidgetMinmap;         //小地图widget
             m_pctrlpane = new WidgetCtrl;       //控制widget
             //QRect rect = m_pmaxmap->geometry();
              int size = 250;//rect.width()/3;

            setCentralWidget(m_pmaxmap);
            QDockWidget *dock=new QDockWidget(QStringLiteral("控制面板"),this);
            dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
            dock->setWidget(m_pctrlpane);
//            dock->setMaximumSize(size,rect.height() - size);
//            dock->setFixedSize(size,rect.height() - size);
            addDockWidget(Qt::LeftDockWidgetArea,dock);
            m_showdock.append(dock);

            dock=new QDockWidget(QStringLiteral("小地图"),this);


            m_pminmap->m_size = size;
            m_pminmap->m_prelamap = m_pmaxmap;
            m_pmaxmap->m_widctrl = m_pctrlpane;

            dock->setWidget(m_pminmap);
            dock->setMaximumSize(size,size);
            dock->setFixedSize(size,size);
            dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
            addDockWidget(Qt::LeftDockWidgetArea,dock);
            m_showdock.append(dock);

            connect(m_pmaxmap,SIGNAL(showchange(QRect ,QSize )),m_pminmap,SLOT(updateShowarea(QRect ,QSize )));
            connect(m_pminmap,SIGNAL(minclick(QPoint)),m_pmaxmap,SLOT(recvminclick(QPoint)));
            connect(m_pctrlpane,SIGNAL(sendStatusText(QString)),this,SLOT(setStatusText(QString)));
            m_pctrlpane->setStatusText(QStringLiteral("任务派发"));
        }
        else

        if (act->text() == QStringLiteral("地图管理"))
        {
            //地图管理菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("地图管理"));

            msgBox.exec();
        }
        else
        if (act->text() == QStringLiteral("节点管理"))
        {
            //节点管理菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("节点管理"));

            msgBox.exec();
        }
        else

        if (act->text() == QStringLiteral("视频IP"))
        {
            //视频IP菜单被按下
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("视频IP"));

            msgBox.exec();
        }
        else
        if (act->text() == QStringLiteral("系统注册"))
        {
           //系统注册菜单被按下
            QMessageBox::about(this, QStringLiteral("系统注册"), QStringLiteral(" \n系统注册！\n\n                       2017年12月"));
        }

        if (act->text() == QStringLiteral("关于我们"))
        {
            //关于菜单被按下
            /*QMessageBox msgBox;
            msgBox.setWindowTitle(QStringLiteral("关于我们"));
            msgBox.setText(QStringLiteral(" \n本程序由北京大基机器人有限公司设计   版权所有  盗版必究！\n\n                       2017年12月"));

            msgBox.exec();*/
            QMessageBox::about(this, QStringLiteral("关于我们"), QStringLiteral(" \n本程序由北京大基机器人有限公司设计   版权所有  盗版必究！\n\n                       2017年12月"));
        }
}



void SlamMainWindow::setStatusText(QString text)
{
    m_statuslabel->setText(text);
    m_statuslabel->show();
}
void SlamMainWindow::closeEvent(QCloseEvent *event)
{
    event = event;
    emit sendsemquit();
}
