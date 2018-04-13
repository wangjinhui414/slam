#ifndef WIDGETCTRL_H
#define WIDGETCTRL_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMap>
#include "memdata.h"

class WidgetCtrl : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetCtrl(QWidget *parent = nullptr);
    ~WidgetCtrl();
    void setStatusText(QString text){
        emit sendStatusText(text);
     }

public:
    QComboBox *m_comvehicle;
    QComboBox *m_comstart;
    QComboBox *m_comend;
    QComboBox *m_compath;
    QLabel *m_lablestart;
    QLabel *m_lableend;
    QLabel *m_lablistpath;

    QPushButton *m_buttonss;
    QPushButton *m_buttonconpath;
    QPushButton *m_buttonsc;

    QPushButton *m_buttonup;
    QPushButton *m_buttonleft;
    QPushButton *m_buttonright;
    QPushButton *m_buttondown;
    QPushButton *m_buttonstop;

    QPushButton *m_buttonsetpos;
    QPushButton *m_btneditstd;
    QPushButton *m_buttonvedio;

    QPushButton *m_btleftlight;
    QPushButton *m_btrightlight;
    QPushButton *m_bdoublelight;
    QPushButton *m_btgreenlight;
    QPushButton *m_btyellowlight;
    QPushButton *m_btbluelight;

    QComboBox *m_comlock;
    QPushButton *m_btunlock;
    QPushButton *m_btsetvolt;

    QComboBox *m_comjdq;
    QPushButton *m_btjdqon;
    QPushButton *m_btjdqoff;

    int m_timevent;
    bool m_flgstd;
    QMap<int,DatabaseData::TYPE_NODES> m_nodes;
    QVector<comserver::TYPE_LASERDATA> m_laserdata;

    void timerEvent(QTimerEvent *event);
signals:
    void sendStatusText(QString);
public slots:
    void commVehicleChange(const QString &vehicle);
    void startTask();
    void stopTask();
    void up();
    void stop();
    void down();
    void left();
    void right();
    void setvehiclepos();
    void editstd();
    void pathrun();
    void dlgvedio();
    void btunlock();
    void btleftlight();
    void btrightlight();
    void btdoublelight();
    void btgreenlight();
    void btyellowlight();
    void btbluelight();
    void btsetvlot();
    void btjdqon();
    void btjdqoff();
};

#endif // WIDGETCTRL_H
