#include "comserver.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTime>
#include "memdata.h"

comserver::comserver(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket();
    m_buf.resize(40960);
}

void comserver::TCPSendToServer(QByteArray sarray)
{
    m_netmutex.lock();
    m_socket->write(sarray);
    if (m_socket->waitForBytesWritten())
    {
        qDebug() << "send:" << sarray << endl;
    }
    else
    {

    }
    m_netmutex.unlock();
}

QByteArray comserver::TCPRecvFromServer(int longdata)
{
    m_buf.clear();
    if(longdata == 0)
    {
        if(m_socket->waitForReadyRead())
        {
            m_buf = m_socket->readAll();
            qDebug()<< "recv:"<<m_buf<<endl;

        }
        return m_buf;
    }
    else
    {
        while(m_socket->waitForReadyRead(300))
        {
            m_buf.append(m_socket->readAll());
        }
        qDebug()<< "recv:"<<m_buf<<endl;
        return m_buf;
    }

}

int comserver::Login(QString uname,QString pwd)
{
    m_socket->connectToHost(DEF_SERVER_IP,DEF_SERVER_PORT);
    if(!m_socket->waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        return false;
    }
    qDebug() << "Connection successful!";
    QJsonObject jsonobj;
    jsonobj["type"] = 1;
    jsonobj["user"] = uname;
    jsonobj["pwd"] = pwd;
    QJsonDocument jsonDoc(jsonobj);
    TCPSendToServer(jsonDoc.toJson());
    QByteArray recvb=TCPRecvFromServer();
    QJsonDocument doc = QJsonDocument::fromJson(recvb);
    QJsonObject rjobj = doc.object();

    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        if(rjobj.take("status").toBool())
            return 1;
        else
            return -1;
    }
    return 0;
}


void comserver::Logout()
{
    m_socket->disconnectFromHost();
}


QVector<QString> comserver::GetVehicleList()
{
    QVector<QString> cgret;
    TCPSendToServer("{\"function\":\"GetVehicleList\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status") && rjobj.take("status").toBool()==true)
    {
        QJsonArray jarray = rjobj.take("data").toArray();

        for (int i = 0; i != jarray.size(); i++)
        {
            QString str = jarray.at(i).toObject().take("robot").toString();
            cgret.push_back(str);
        }
    }
    return cgret;

}

bool comserver::SetOperateVehicle(QString vehicle)
{
    QString scmd = "{\"function\":\"SetOperateVehicle\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", vehicle);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;

}

QString comserver::GetOperateVehicle()
{
    QString scmd = "{\"function\":\"GetOperateVehicle\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status") && rjobj.take("status").toBool()==true)
    {
        return rjobj.take("data").toObject().take("robot").toString();
    }
    return "";
}


QVector<QString> comserver::GetVehicleConstPathList()//获取小车固定路径列表
{
    QVector<QString> cgret;
    TCPSendToServer("{\"function\":\"GetPathList\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        QJsonArray jarray = rjobj.take("data").toArray();

        for (int i = 0; i != jarray.size(); i++)
        {
            QString str = jarray.at(i).toObject().take("path").toString();
            cgret.push_back(str);
        }
    }
    return cgret;
}

QVector<QString> comserver::GetVehicleMapList()
{
    QVector<QString> cgret;
    TCPSendToServer("{\"function\":\"GetMapList\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        QJsonArray jarray = rjobj.take("data").toArray();

        for (int i = 0; i != jarray.size(); i++)
        {
            QString str = jarray.at(i).toObject().take("map_name").toString();
            cgret.push_back(str);
        }
    }
    return cgret;
}

QVector<QString> comserver::GetVehicleRecordMapList()
{
    QVector<QString> cgret;
    TCPSendToServer("{\"function\":\"GetRecordMapList\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        QJsonArray jarray = rjobj.take("data").toArray();

        for (int i = 0; i != jarray.size(); i++)
        {
            QString str = jarray.at(i).toObject().take("map_name").toString();
            cgret.push_back(str);
        }
    }
    return cgret;
}


bool comserver::GetLaserData(QVector<comserver::TYPE_LASERDATA> *pcglaser)
{
    TCPSendToServer("{\"function\":\"GetLaserData\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer(1));
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        QJsonArray jarray = rjobj.take("data").toArray();
        for (int i = 0; i != jarray.size(); i++)
        {
            comserver::TYPE_LASERDATA one;
            one.angle = jarray.at(i).toObject().take("angle").toDouble();
            one.range = jarray.at(i).toObject().take("range").toDouble();
            pcglaser->push_back(one);
        }
        return true;
    }
    return false;
}
bool comserver::GetGlobalPath(QVector<comserver::TYPE_CURTASK_POINT> *pcurpoint)//获取当前路径坐标点
{
    TCPSendToServer("{\"function\":\"GetGlobalPath\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        QJsonArray jarray = rjobj.take("data").toArray();
        for (int i = 0; i != jarray.size(); i++)
        {
            comserver::TYPE_CURTASK_POINT one;
            one.dir = jarray.at(i).toObject().take("dir").toInt();
            one.x = jarray.at(i).toObject().take("x").toInt();
            one.y = jarray.at(i).toObject().take("y").toInt();
            pcurpoint->push_back(one);
        }
        return true;
    }
    return false;
}
bool comserver::GetVehicleStatus(comserver::TYPE_ROBOT_STATUS *pstatus)
{
   TCPSendToServer("{\"function\":\"GetVehicleStatus\",\"parameter\":null}");
   QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
   QJsonObject rjobj = doc.object();
   if(!rjobj.isEmpty() && rjobj.contains("data"))
   {
        pstatus->run_status = rjobj.take("data").toObject().take("status").toInt();
        pstatus->errcode = rjobj.take("data").toObject().take("errcode").toInt();
        return true;
    }
    return false;
}


bool comserver::StartRobot()
{
    QString scmd = "{\"function\":\"StartRobot\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
         return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::StopRobot()//停止运行机器人
{
    QString scmd = "{\"function\":\"StopRobot\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
         return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::SetAmclMap(QString mapname)//设置定位地图
{
    QString scmd = "{\"function\":\"SetAmclMap\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", mapname);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
         return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::SetNaviMap(QString mapname)//设置导航地图
{
    QString scmd = "{\"function\":\"SetNaviMap\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", mapname);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::SetVehiclePos(double x_start, double y_start, double x_end, double y_end)//设置车辆位置
{
    QString scmd = "{\"function\":\"SetVehiclePos\",\"parameter\":\"${0}\"}";
    QString cpar = "";
    cpar.sprintf("%f,%f,%f,%f", x_start, y_start, x_end, y_end);
    scmd = scmd.replace("${0}", cpar);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::GetVehiclePos(comserver::TYPE_VEHICLEPOS *vpos)//获取某个小车的定位
{
    QString scmd = "{\"function\":\"GetVehiclePos\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status") && rjobj.take("status").toBool()==true)
    {
        QJsonObject qobjdata = rjobj.take("data").toObject();
        vpos->th = qobjdata.take("th").toDouble();
        vpos->x =  qobjdata.take("x").toDouble();
        vpos->y =  qobjdata.take("y").toDouble();
        vpos->last_dx = qobjdata.take("last_dx").toDouble();
        return rjobj.take("status").toBool();
    }
    return false;
}

//bool comserver::GetLaserData(QVector<comserver::TYPE_LASERDATA> *laserdata)
//{
//    QString scmd = "{\"function\":\"GetLaserData\",\"parameter\":null}";
//    TCPSendToServer(scmd.toLatin1());
//    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
//    QJsonObject rjobj = doc.object();
//    if(!rjobj.isEmpty() && rjobj.contains("status") && rjobj.take("status").toBool()==true)
//    {
//        QJsonObject jarray = rjobj.take("data").toArray();
//        for(int i=0;i!=jarray.size();i++)
//        {
//            comserver::TYPE_LASERDATA onelaser;
//            onelaser.angle = jarray.at(i).toObject().take("angle").toDouble();
//            onelaser.range = jarray.at(i).toObject().take("range").toDouble();
//            laserdata->push_back(onelaser);
//        }
//        return rjobj.take("status").toBool();
//    }
//    return false;
//}

bool comserver::Pause()
{
    QString scmd = "{\"function\":\"Pause\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::RebootVehicle()//重启小车
{
    QString scmd = "{\"function\":\"Reboot\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::RunPath(QString pathname, int itype)//执行路径运行
{
    QString scmd = "{\"function\":\"RunPath\",\"parameter\":\"${0}\"}";
    if (itype == 0)
        pathname = "fix," + pathname;
    else
        pathname = "free," + pathname;
    scmd = scmd.replace("${0}",pathname);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::StartRecordPath()//记录路径
{
    QString scmd = "{\"function\":\"RecordPath\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::SavePath(QString savename)//保存路径
{
    QString scmd = "{\"function\":\"SavePath\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", savename);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::MakeMaping()//执行制图任务
{
    QString scmd = "{\"function\":\"MakeMaping\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::StartRecordMap()//开始记录地图
{
    QString scmd = "{\"function\":\"StartRecordMap\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::RobotForwardRecode()//记录地图时执行机器人运动
{
    QString scmd = "{\"function\":\"RobotForwardRecode\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::RobotPauseRecode()//记录地图时执行机器人停止
{
    QString scmd = "{\"function\":\"RobotPauseRecode\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::RobotTurnLeftRecode()//记录地图时执行机器人向左
{
    QString scmd = "{\"function\":\"RobotTurnLeftRecode\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::RobotTurnRightRecode()//记录地图时执行机器人向右
{
    QString scmd = "{\"function\":\"RobotTurnRightRecode\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::RobotBackWardRecode()
{
    QString scmd = "{\"function\":\"RobotBackWardRecode\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::SaveRecordMap(QString savename)//停止并保存记录地图
{
    QString scmd = "{\"function\":\"SaveRecordMap\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", savename);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::SetPathFileState(int state)
{
    QString scmd = "{\"function\":\"SetPathFileState\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", QString::number(state, 10));
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
bool comserver::SetRobotLaserFileState(int state)
{
    QString scmd = "{\"function\":\"SetRobotLaserFileState\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}", QString::number(state, 10));
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::CreatePath(int startnode, int endnode)
{
    QJsonObject jdata;
    jdata.insert("function","CreatePath1");
    jdata.insert("parameter","");
    QJsonObject jpar;
    jpar.insert("startnode",startnode);
    jpar.insert("endnode",endnode);
    jdata.insert("nodes",jpar);

    TCPSendToServer(QJsonDocument(jdata).toJson());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::CreatePath(QVector<int> nodes)
{
    QJsonObject jdata;
    jdata.insert("function","CreatePath2");
    jdata.insert("parameter","");
    QJsonArray jpar;
    for (QVector<int>::iterator it = nodes.begin(); it != nodes.end();++it)
    {
        QJsonObject jvalue;
        jvalue.insert("node",*it);
        jpar.append(jvalue);
    }
    jdata.insert("nodes",jpar);

    TCPSendToServer(QJsonDocument(jdata).toJson());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

QString comserver::ReadSOC()
{
    TCPSendToServer("{\"function\":\"ReadSOC\",\"parameter\":null}");
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        return rjobj.take("data").toString();
    }
    return "";
}

bool comserver::SetVolt(QString str)
{
    QString scmd = "{\"function\":\"SetVolt\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",str);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::GetLockStatus(int *status)
{
    QString scmd = "{\"function\":\"ReadLockStatus\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("data"))
    {
        *status = rjobj.take("data").toInt();
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::Unlock(QString num)
{
    QString scmd = "{\"function\":\"Unlock\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",num);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::LeftTW(QString onoff)
{
    QString scmd = "{\"function\":\"LeftTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::RightTW(QString onoff)
{
    QString scmd = "{\"function\":\"RightTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::LeftRightTW(QString onoff)
{
    QString scmd = "{\"function\":\"LeftRightTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::GreenTW(QString onoff)
{
    QString scmd = "{\"function\":\"GreenTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::YellowTW(QString onoff)
{
    QString scmd = "{\"function\":\"YellowTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::BlueTW(QString onoff)
{
    QString scmd = "{\"function\":\"BlueTW\",\"parameter\":\"${0}\"}";
    scmd = scmd.replace("${0}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::OneRelayOnoff(QString num, QString onoff)
{
    QString scmd = "{\"function\":\"OneRelayOnOff\",\"parameter\":\"${0},${1}\"}";
    scmd = scmd.replace("${0}",num);
    scmd = scmd.replace("${1}",onoff);
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::AllRelayOn()
{
    QString scmd = "{\"function\":\"AllRelayOn\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}

bool comserver::AllRelayOff()
{
    QString scmd = "{\"function\":\"AllRelayOff\",\"parameter\":null}";
    TCPSendToServer(scmd.toLatin1());
    QJsonDocument doc = QJsonDocument::fromJson(TCPRecvFromServer());
    QJsonObject rjobj = doc.object();
    if(!rjobj.isEmpty() && rjobj.contains("status"))
    {
        return rjobj.take("status").toBool();
    }
    return false;
}
