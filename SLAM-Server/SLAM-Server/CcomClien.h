#ifndef  _CCOM_CLIENT_H_
#define  _CCOM_CLIENT_H_
#include "stdafx.h"
#include "memdata.h"
#include "MyDatabase.h"



class  CcomClient
{
public:
	CcomClient(){};
	~CcomClient(){};
public:
	bool InitCcom(TYPE_USER_INFO *userinfo);
	void RunClientCcom();
	void TCPSendToClient(string sendstr);
	string TCPRecvFromClient();
	bool WaitVehicleResponse(DWORD time = 6000);
	int TransSendToVehicle(string strfun, string strpar);
public:
	void ResponseGetVehicleList();
	void ResponseSetOperatVehicle(string newvehicle);
	void ResponseGetOperatVehicle();
	void ResponseGetVehicleConstPathList();
	void ResponseGetVehicleMapList();
	void ResponseGetVehicleRecordMapList();
	void ResponseGetVehicleStatus();


	void ResponseStartRobot();
	void ResponseStopRobot();
	void ResponseSetAmclMap();
	void ResponseSetNaviMap();
	void ResponseSetVehiclePos();
	void ResponseGetVehiclePos();
	void ResponseSetPahtFileState();
	void ResponseSetRobotLaserState();

	void ResponsePause();//暂停下车
	void ResponseContinue();
	void ResponseRebootVehicle();//重启小车
	void ResponseRunPath();//执行路径运行
	void ResponseStartRecordPath();//记录路径
	void ResponseSavePath();//保存路径

	void ResponseMakeMaping();//执行制图任务
	void ResponseStartRecordMap();//开始记录地图
	void ResponseRobotForwardRecode();//记录地图时执行机器人运动
	void ResponseRobotPauseRecode();//记录地图时执行机器人停止
	void ResponseRobotTurnLeftRecode();//记录地图时执行机器人向左
	void ResponseRobotTurnRightRecode();//记录地图时执行机器人向右
	void ResponseRobotBackWardRecode();//记录地图时执行机器人向后
	void ResponseSaveRecordMap();//停止并保存记录地图

	void ResponseGetLaserData();
	void ResponseGetGlobalPath();

	void ComReponse();

public:
	void ResponseGetUserRecord();
	void ResponseGetVehicleRecord();
	void ResponseGetNodeRecord();
	void ResponseUpdataUserRecord(string jsuser);
	void ResponseUpdataVehicleRecord(string jsvehicls);
	void ResponseUpdataNodeRecord(string jsnode);

	void ResponseDeleteUserRecord(string jstr);
	void ResponseDeleteVehicleRecord(string jstr);
	void ResponseDeleteNodeRecord(string jstr);

	void ResponseCreatePath1(string jstr);
	void ResponseCreatePath2(string jstr);
public:
	TYPE_VEHICLE_INFO *m_vehicleinfo;
	TYPE_USER_INFO *m_userinfo;
	DWORD m_err;
};


#endif