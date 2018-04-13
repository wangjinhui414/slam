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

	void ResponsePause();//��ͣ�³�
	void ResponseContinue();
	void ResponseRebootVehicle();//����С��
	void ResponseRunPath();//ִ��·������
	void ResponseStartRecordPath();//��¼·��
	void ResponseSavePath();//����·��

	void ResponseMakeMaping();//ִ����ͼ����
	void ResponseStartRecordMap();//��ʼ��¼��ͼ
	void ResponseRobotForwardRecode();//��¼��ͼʱִ�л������˶�
	void ResponseRobotPauseRecode();//��¼��ͼʱִ�л�����ֹͣ
	void ResponseRobotTurnLeftRecode();//��¼��ͼʱִ�л���������
	void ResponseRobotTurnRightRecode();//��¼��ͼʱִ�л���������
	void ResponseRobotBackWardRecode();//��¼��ͼʱִ�л��������
	void ResponseSaveRecordMap();//ֹͣ�������¼��ͼ

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