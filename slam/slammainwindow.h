#ifndef SLAMMAINWINDOW_H
#define SLAMMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtSql>
#include <QTextCodec>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <iostream>
#include <QtDebug>

#include "widgetctrl.h"
#include "widgetmaxmap.h"
#include "widgetminmap.h"
#include "memdata.h"

namespace Ui {
class SlamMainWindow;
}

class SlamMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlamMainWindow(QWidget *parent = 0);
    ~SlamMainWindow();

/***************************************************/
 public:
    QVector<QDockWidget*> m_showdock;//当前布局的dockwidget集合 用于释放
    WidgetMaxmap *m_pmaxmap;         //大地图centerwidget
    WidgetMinmap *m_pminmap;         //小地图widget
    WidgetCtrl   *m_pctrlpane;       //控制widget
    QLabel *m_statuslabel;           //状态栏
/***************************************************/

    void closeEvent(QCloseEvent *event);
signals:
    void sendsemquit();
private:
    Ui::SlamMainWindow *ui;

private slots:
    void trigerMenu(QAction* act);
    void setStatusText(QString);

};

#endif // SLAMMAINWINDOW_H
