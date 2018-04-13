#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QtSql>
#include <QTextCodec>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QMap>

class DatabaseData
{   
public:
    DatabaseData();
    bool Open();
    void Close();

/***************************站点表获取***************************/
    typedef struct TYPE_NODES
    {
        quint32 id;
        QString name;
        quint32 x;
        quint32 y;
        quint32 f;
        quint8 type;
        QVector<quint32> adjucentnode;
        QVector<quint32> adjucentdis;
    }TYPE_NODES;
    bool GetNodesTab(QMap<int,DatabaseData::TYPE_NODES> *allnodes);
    bool UpdateNodesTab(QMap<int,DatabaseData::TYPE_NODES> *allnodes);


private:
    QSqlDatabase m_db;
};



#endif // DATABASEDATA_H

