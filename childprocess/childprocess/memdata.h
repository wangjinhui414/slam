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

typedef struct TYPE_VEHICLE_INFO//���߳�����Ϣ
{
	TYPE_VEHICLE_INFO()
	{
		memset(this, 0, sizeof(TYPE_VEHICLE_INFO));
	}
	//С���� ����ͨѶSocket
	bool isonline;
	DWORD childprocessid;
	WSAPROTOCOL_INFO wasinfo7700;
	WSAPROTOCOL_INFO wasinfo8800;

	string vehicle_ip;
	DWORD vehicle_port;

	//С�����ݿ�ļ�¼��
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


	/***********�ӽ��̷��ظ�������С���ĵ�ǰ״̬************/
	//С����ǰλ��
	struct TYPE_VEHICLEPOS
	{
		double last_dx;
		double th;
		double x;
		double y;
	}vehicle_pos;
	//С���̶�·���б�
	struct TYPE_PATHS_LIST
	{
		char paths[MAX_PATH_NUM][MAX_PATHNAME_LEN];
		int path_num;
	}vehicle_paths;
	//��ȡһ��ļ�������
	struct TYPE_LASERDATA
	{
		double angle;
		double range;
	};
	TYPE_LASERDATA laserdatas[MAX_LASER_NUM];
	//��ǰ����·�������
	struct TYPE_CURTASK_POINT
	{
		BYTE dir;
		int x;
		int y;
	};
	TYPE_CURTASK_POINT map_points[MAX_CURTASK_POINT];
	WORD map_pointsize;
	//С����ǰ����״̬
	struct TYPE_ROBOT_STATUS
	{
		int run_status;
		int errcode;
	}run_status;
	//С����ͼ�б�
	struct TYPE_MAP_LIST
	{
		char maps[MAX_MAP_NUM][MAX_MAPNAME_LEN];
		int map_num;
	}vehicle_maps, vehicle_record_maps;;

}TYPE_VEHICLE_INFO, *pTYPE_VEHICLE_INFO;



#endif