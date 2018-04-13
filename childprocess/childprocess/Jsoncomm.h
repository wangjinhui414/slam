#ifndef _JSON_COMM_H_ 
#define _JSON_COMM_H_

#include "stdafx.h"
#if defined(__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
	#pragma warning(disable : 4996)
#endif

#include "memdata.h"
#include "MyDatabase.h"
#include "json/json.h"
#pragma comment(lib, "json_vc71_libmtd.lib")




class CJsonComm
{
public:
	CJsonComm(TYPE_VEHICLE_INFO* sharememory, SOCKET socket7700, SOCKET socket8800);
	~CJsonComm();
public:
	void RunmComVehicle();
	void SendJsonString7700(string jstr);
	string RecvJsonString7700();
	void SendJsonString8800(string jstr);
	string RecvJsonString8800();
	void ReFreshVehicleData();
	void CloseJsoncom();
//protected:
	bool SetRobotPos();
	bool GetRobotPos();
	bool SelectFixPath();
	bool RunPath();
	bool GetLaserData();
	bool GetGlobalPath();
	bool GetStatus();
	bool GetMapList();
	bool GetRecordMap();
	bool Mapping();
	bool Pause();
	bool Continue();
	bool Reboot();
	bool RecodeMap();
	bool RecordPath();
	bool RobotForwardRecode();
	bool RobotPauseRecode();
	bool RobotTurnLeftRecode();
	bool RobotTurnRightRecode();
	bool RobotBackwardRecode();
	bool SavePath();
	bool SetAmclMap();
	bool SetNaviMap();
	bool SetPathFileState();
	bool SetRobotLaserFileState();
	bool StartRobot();
	bool StopRecodeMap();
	bool StopRobot();

	//bool SetRobotPos(string sx1, string sy1, string sx2, string sy2);

	void ReadSoc();
	void SetVolteF();
	void GetLockStatus();
	void OneUnlock();
	void LeftTW();
	void RightTW();
	void LeftRightTW();
	void GreenTW();
	void YellowTW();
	void BlueTW();
	void OneRelayONOFF();
	void AllRelayON();
	void ALLRelayOFF();


//private:
public:
	TYPE_VEHICLE_INFO *m_psharememo;
	SOCKET m_sockclient7700;
	SOCKET m_sockclient8800;
	int m_err;
};




#endif