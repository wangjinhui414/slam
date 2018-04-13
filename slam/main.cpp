#include "slammainwindow.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include "logindialog.h"
#include <QSplashScreen>
#include <QJsonObject>
#include "comserver.h"
#include <QDebug>
#include "workthread.h"


void qsleep(int time)
{
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.msecsTo(now)<=time);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("qt_zh_CN.qm");
    a.installTranslator(&translator);


    /************************************用户授权*******************************/
    LoginDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        /*******************启动画面显示时 启动服务 连接数据库***********************/
        QPixmap pixmap("start1.png");
        QSplashScreen screen(pixmap);
        screen.show();
        screen.showMessage(QStringLiteral("正在读取配置信息..."), Qt::AlignBottom, Qt::black);
        a.processEvents();
        qsleep(1000);
        /*配置文件读取*/
        if(1)
        {
            screen.showMessage(QStringLiteral("读取配置信息成功..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);
        }
        else
        {
            screen.showMessage(QStringLiteral("读取配置信息失败..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);
            return 0;
        }
        /*数据库连接*/
        screen.showMessage(QStringLiteral("正在连接数据库..."), Qt::AlignBottom, Qt::black);
        a.processEvents();
        qsleep(1000);
        if(g_database.Open())
        {
            screen.showMessage(QStringLiteral("数据库连接成功..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);

        }
        else
        {
            screen.showMessage(QStringLiteral("数据库连接失败..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);
            return 0;
        }
        screen.close();
        /*启动通讯线程*/
        screen.showMessage(QStringLiteral("正在初始化通讯..."), Qt::AlignBottom, Qt::black);
        a.processEvents();
        qsleep(1000);
        if(1)
        {
            screen.showMessage(QStringLiteral("初始化通讯成功..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);
        }
        else
        {
            screen.showMessage(QStringLiteral("初始化通讯失败..."), Qt::AlignBottom, Qt::black);
            a.processEvents();
            qsleep(1000);
            return 0;
        }
        screen.close();

        /*主框架启动*/
        SlamMainWindow w;
        w.setWindowFlags(w.windowFlags());
        w.showMaximized();
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}

