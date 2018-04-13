#ifndef  _MEM_DATA_ 
#define  _MEM_DATA_
#include "MyDatabase.h"

#define  MAX_CMDBUF_SIZE    40960

#define   MAX_PATH_NUM      50
#define   MAX_PATHNAME_LEN  40
#define   MAX_LASER_NUM     541
#define   MAX_CURTASK_POINT     200

#define   MAX_MAP_NUM      10
#define   MAX_MAPNAME_LEN  40

typedef struct TYPE_VEHICLE_INFO//在线车辆信息
{
	TYPE_VEHICLE_INFO()
	{
		memset(this, 0, sizeof(TYPE_VEHICLE_INFO));
	}
	//小车的 共享通讯Socket
	bool isonline;
	DWORD childprocessid;
	WSAPROTOCOL_INFO wasinfo7700;
	WSAPROTOCOL_INFO wasinfo8800;

	string vehicle_ip;
	DWORD vehicle_port;

	//小车数据库的记录集
	TAB_VEHICLE vehicletab;

	//SERVER to Child vehicle Cmd
	char cmdbuf[MAX_CMDBUF_SIZE];
	enum {
		REFRESH = 0X00, SETROBOTPOS = 0x01, GETROBOTPOS, SELECTFIXPATH, RUNPATH, GETLASER, GETGLOBALPATH, SETTARGETPOS,
		GETSTATUS, GETMAPLIST, GETRECODEMAPS, MAPPING, PAUSE, CONTINUE, REBOOT, RECODEMAP, RECODEPATH, ROBOTFORWARDRECODE,
		ROBOTPAUSERECODE, ROBOTTURNLEFTRECODE, ROBOTTURNRIGHTRECODE, ROBOTBACKWARDCODE, SAVEPATH, SETAMCLMAP, SETNAVIMAP,
		SETPATHFILESTATE, SETROBOTLASERFILESTATE, STARTROBOT, STOPRECODEMAP, STOPROBOT,
		READSOC, SETVOLTE, READLOCKSTATUS, UNLOCK, LEFTTW, RIGHTTW, LEFTRIGHTTW, GREENTW, YELLOWTW, BLUETW,
		ONERELAYONOFF, ALLRELAYON, ALLRELAYOFF,
	};
	DWORD cmd;
	enum { E_RELASE, E_VELID, E_INVALID };
	BYTE cmdflag;


	/***********子进程返回给服务器小车的当前状态************/
	//小车当前位置
	struct TYPE_VEHICLEPOS
	{
		double last_dx;
		double th;
		double x;
		double y;
	}vehicle_pos;
	//小车固定路径列表
	struct TYPE_PATHS_LIST
	{
		char paths[MAX_PATH_NUM][MAX_PATHNAME_LEN];
		int path_num;
	}vehicle_paths;
	//获取一组的激光数据
	struct TYPE_LASERDATA
	{
		double angle;
		double range;
	};
	TYPE_LASERDATA laserdatas[MAX_LASER_NUM];
	//当前任务路径坐标点
	struct TYPE_CURTASK_POINT
	{
		BYTE dir;
		int x;
		int y;
	};
	TYPE_CURTASK_POINT map_points[MAX_CURTASK_POINT];
	WORD map_pointsize;
	//小车当前运行状态
	struct TYPE_ROBOT_STATUS
	{
		int run_status;
		int errcode;
	}run_status;
	//小车地图列表
	struct TYPE_MAP_LIST
	{
		char maps[MAX_MAP_NUM][MAX_MAPNAME_LEN];
		int map_num;
	}vehicle_maps, vehicle_record_maps;;

}TYPE_VEHICLE_INFO, *pTYPE_VEHICLE_INFO;



#endif