#ifndef COMSERVER_H
#define COMSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QList>
#include <QVector>
#include <QMutex>

class comserver : public QObject
{
    Q_OBJECT
public:
    explicit comserver(QObject *parent = nullptr);
    struct TYPE_VEHICLEPOS
    {
        TYPE_VEHICLEPOS(){
            last_dx = 0;
            th = 0;
            x = 0;
            y = 0;
        }
        double last_dx;
        double th;
        double x;
        double y;
    };
    struct TYPE_CURTASK_POINT
    {
        quint8 dir;
        int x;
        int y;
    };
    struct TYPE_ROBOT_STATUS
    {
        int run_status;
        int errcode;
    };
    struct TYPE_LASERDATA
    {
        double angle;
        double range;
    };
    //用户表
    typedef struct TAB_USER
    {
        QString name;
        QString pwd;
        quint32 role;
        quint32 del;
        TAB_USER()
        {
            memset(this, 0, sizeof(TAB_USER));
        }
    }TAB_USER, *pTAB_USER;
    //小车表
    typedef struct TAB_VEHICLE
    {
        QString name;
        QString pwd;
        int state;
        int startnode;
        int endnode;
        TAB_VEHICLE()
        {
            memset(this, 0, sizeof(TAB_VEHICLE));
        }

    }TAB_VEHICLE, *pTAB_VEHICLE;
    //站点表
    typedef struct TAB_NODE
    {
        quint32 id;
        QString name;
        quint32 type;
        int x;
        int y;
        int f;
        QVector<int> AdjNodeos;
        QVector<int> AdjDis;
        TAB_NODE()
        {
            memset(this, 0, sizeof(TAB_NODE));
        }

    }TAB_TAB_NODE, *pTAB_NODE;


    int Login(QString uname,QString pwd);//登陆
    void Logout();//登出
    void TCPSendToServer(QByteArray sarray);//网络发送
    QByteArray TCPRecvFromServer(int longdata = 0);//网络接收

    QVector<QString> GetVehicleList();/*获取在线车辆列表*/
    bool SetOperateVehicle(QString vehicle); /*选择操作小车*/
    QString GetOperateVehicle();/*获取当前操作的小车*/

    QVector<QString> GetVehicleConstPathList();//获取小车固定路径列表
    QVector<QString> GetVehicleMapList();//获取地图列表
    QVector<QString> GetVehicleRecordMapList();//获取记录地图列表
    bool GetLaserData(QVector<comserver::TYPE_LASERDATA> *pcglaser);//获取激光数据
    bool GetGlobalPath(QVector<comserver::TYPE_CURTASK_POINT> *pcurpoint);//获取当前路径坐标点
    bool GetVehicleStatus(comserver::TYPE_ROBOT_STATUS *pstatus);//获取小车的当前状态

    bool StartRobot();//开始运行机器人
    bool StopRobot();//停止运行机器人
    bool SetAmclMap(QString mapname);//设置定位地图
    bool SetNaviMap(QString mapname);//设置导航地图
    bool SetVehiclePos(double x_start,double y_start,double x_end,double y_end);//设置车辆位置
    bool GetVehiclePos(comserver::TYPE_VEHICLEPOS *vpos);//获取某个小车的定位

    bool Pause();//暂停下车
    bool RebootVehicle();//重启小车
    bool RunPath(QString pathname, int itype = 0);//执行路径运行
    bool StartRecordPath();//记录路径
    bool SavePath(QString savename);//保存路径

    bool MakeMaping();//执行制图任务
    bool StartRecordMap();//开始记录地图
    bool RobotForwardRecode();//记录地图时执行机器人运动
    bool RobotPauseRecode();//记录地图时执行机器人停止
    bool RobotTurnLeftRecode();//记录地图时执行机器人向左
    bool RobotTurnRightRecode();//记录地图时执行机器人向右
    bool RobotBackWardRecode();//记录地图时执行机器人向后
    bool SaveRecordMap(QString savename);//停止并保存记录地图
    bool SetPathFileState(int state);
    bool SetRobotLaserFileState(int state);
    bool CreatePath(int startnode, int endnode);
    bool CreatePath(QVector<int> nodes);

    QString ReadSOC();
    bool SetVolt(QString str);
    bool GetLockStatus(int *status);
    bool Unlock(QString num);
    bool LeftTW(QString onoff);
    bool RightTW(QString onoff);
    bool LeftRightTW(QString onoff);
    bool GreenTW(QString onoff);
    bool YellowTW(QString onoff);
    bool BlueTW(QString onoff);
    bool OneRelayOnoff(QString num,QString onoff);
    bool AllRelayOn();
    bool AllRelayOff();
signals:

public slots:

private:
    QTcpSocket *m_socket;
    QByteArray m_buf;
    QMutex m_netmutex;

};

#endif // COMSERVER_H
