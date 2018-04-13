#ifndef MEMDATA_H
#define MEMDATA_H

#include "comserver.h"
#include "databasedata.h"

#define   MAP_PATH          "map.bmp"
#define DEF_SERVER_IP       "127.0.0.1"
#define DEF_SERVER_PORT     6000
//#define DEF_MYSQL_IP        "127.0.0.1"
#define DEF_MYSQL_IP        "172.16.14.118"
#define DEF_MYSQL_PORT      3306
#define DEF_MYSQL_DATA      "slam"
#define DEF_MYSQL_USER      "root"
#define DEF_MYSQL_PWD       "thunder865"

extern comserver g_comser;
extern DatabaseData g_database;
















#endif // MEMDATA_H
