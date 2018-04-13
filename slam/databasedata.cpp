#include "databasedata.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QMessageBox>
#include <Qt>
#include <QDebug>
#include "memdata.h"


DatabaseData::DatabaseData()
{

}

bool DatabaseData::Open()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(DEF_MYSQL_IP);//数据库地址，这个必须要替换成自己的数据库地址，可以使用远程IP地址
    m_db.setPort(DEF_MYSQL_PORT);//端口
    m_db.setDatabaseName(DEF_MYSQL_DATA);//数据库名
    m_db.setUserName(DEF_MYSQL_USER);//用户名
    m_db.setPassword(DEF_MYSQL_PWD);//密码
    return m_db.open();

}
//sudo /home/wangjinhui/Qt5.10.1/5.10.1/gcc_64/bin/qmake “INCLUDEPATH+=/usr/include/mysql” “LIBS+=-L/usr/lib/x86_64-linux-gnu/-lmysqlclient” mysql.pro
void DatabaseData::Close()
{
    m_db.close();
}


bool DatabaseData::GetNodesTab(QMap<int,DatabaseData::TYPE_NODES> *allnodes)
{
    QSqlQuery query(m_db);
    if(query.exec("SELECT * FROM nodes where ID >= 0"))
    {
        while(query.next())
        {
            DatabaseData::TYPE_NODES one;
            one.id = query.value(0).toInt();
            one.name = query.value(1).toString();
            one.x = query.value(2).toInt();
            one.y = query.value(3).toInt();
            one.f = query.value(4).toInt();
            one.type = query.value(5).toInt();
            QString str = query.value(6).toString();
            QStringList slist = str.split(",");
            if(slist.size()>0)
            {
                while(!slist.isEmpty())
                {
                    QString stmp = slist.takeFirst();
                    if(stmp.size()>0)
                        one.adjucentnode.push_back(stmp.toInt());
                }
            }

            QString str1 = query.value(7).toString();
            QStringList slist1 = str1.split(",");
            if(slist1.size()>0)
            {
                while(!slist1.isEmpty())
                {
                    QString stmp = slist1.takeFirst();
                    if(stmp.size()>0)
                        one.adjucentdis.push_back(stmp.toInt());
                }
            }
            allnodes->insert(one.id,one);
        }
        return true;
    }
    return false;
}

bool DatabaseData::UpdateNodesTab(QMap<int, DatabaseData::TYPE_NODES> *allnodes)
{
    bool success = true;
    QSqlQuery query(m_db);
   success = query.exec("DELETE FROM nodes where ID >=0");
    // 插入数据user
    for(QMap<int,DatabaseData::TYPE_NODES>::iterator it =allnodes->begin();
        it!=allnodes->end();++it)
    {
        DatabaseData::TYPE_NODES ntemp = it.value();
        QSqlQuery query(m_db);
        query.prepare("insert into nodes (ID,Name,X,Y,F,Type,AdjacentNode,AdjacentDis)""values(?,?,?,?,?,?,?,?)");
        query.bindValue(0,ntemp.id);
        query.bindValue(1,ntemp.name);
        query.bindValue(2,ntemp.x);
        query.bindValue(3,ntemp.y);
        query.bindValue(4,ntemp.f);
        query.bindValue(5,ntemp.type);
        QString strnode = "";
        QString strdis = "";
        QVector<quint32>::iterator at,bt;
        for(at = ntemp.adjucentnode.begin(),bt = ntemp.adjucentdis.begin()
            ;at!=ntemp.adjucentnode.end();++at,++bt)
        {
            strnode += QString::number(*at,10);
            strdis += QString::number(*bt,10);
            if((at+1)==ntemp.adjucentnode.end())
            {

            }
            else
            {
                strnode += ",";
                strdis += ",";
            }
        }
        query.bindValue(6,strnode);
        query.bindValue(7,strdis);
        success = query.exec();
    }
    return success;
}
