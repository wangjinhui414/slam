// childprocess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "ShareMemory.h"
#include "MyDatabase.h"
#include "mytypedef.h"
#include "memdata.h"
#include "Jsoncomm.h"


using namespace std;
void DebugRobot(CJsonComm *jsoncomm, TYPE_VEHICLE_INFO* psharemem);


int _tmain(int argc, _TCHAR* argv[])
{
	char vname[1024];
	if (argc >= 2)
	{
		sprintf_s(vname, "%S", argv[1]);
		cout <<"子进程："<< vname << endl;
	}
	
	//获取共享内存
	CShareMemory csharemem = CShareMemory(vname);
	string stmp = csharemem.m_name;
	TYPE_VEHICLE_INFO* psharemem = (TYPE_VEHICLE_INFO*)csharemem.m_pmem;
	
	//连接数据库
	//if (FALSE == CMyDatabase::ComInit())
	//{
	//	cout << "ERROR: cominit failed!" << endl;
	//	return 0;
	//}
	//CMyDatabase mydatabse;
	//BOOL ret = mydatabse.ConnectDatabase("ROBOT-PC", "SLAM", "sa", "11111111");
	//
	//if (ret == FALSE)
	//{
	//	cout << "ERROR: Connect Database failed" << endl;
	//	CMyDatabase::ComUninit();
	//	return 0;
	//}
	//CGroup<TAB_USER> cgret = mydatabse.QueryRecordeUser();
	//CGroup<TAB_VEHICLE> cgret1 = mydatabse.QueryRecordeVehicle();
	//CGroup<TAB_NODE> cgret2 = mydatabse.QueryRecordeNode();
	//计算出路径矩阵图
	//CFloyd cfloyd;
	//cfloyd.LoadDatabaseRecord(cgret2);
	//cfloyd.PrintFloyd();
	//vector<int> rett = cfloyd.FindShortestPaht(1, 6);
	//建立TCP服务
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}
	psharemem->childprocessid = GetCurrentProcessId();
	Sleep(500);
	if (psharemem->isonline == true)
	{
		
		SOCKET s1 =0,s2=0;
		s1 = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &(psharemem->wasinfo7700), 0, WSA_FLAG_OVERLAPPED);
		CJsonComm jsoncomm = CJsonComm(psharemem,s1,s2);
		//jsoncomm.ReFreshVehicleData();
		jsoncomm.RunmComVehicle();
		//DebugRobot(&jsoncomm, psharemem);
	}

	return 0;
}

#define    PRINTRET(x)      cout<<(x==true?"OK":"FAULT")<<endl; 
void DebugRobot(CJsonComm *jsoncomm,TYPE_VEHICLE_INFO* psharemem)
{
	cout << "***********start debug**************" << endl;
	while (1)
	{
		if (jsoncomm->m_err == -1)
		{
			cout << "***********end debug***********" << endl;
			jsoncomm->CloseJsoncom();
			return;
		}
		char ch[200] = "";
		cout << "input:";
		cin >> ch;
		string stmp = ch;
		if (stmp == "quit")
		{
			break;
		}
		else if (stmp.find("SetRobotPos:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SetRobotPos();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("GetRobotPos") == 0)
		{
			jsoncomm->GetRobotPos();
			cout << "last_dx:"<<psharemem->vehicle_pos.last_dx << endl;
			cout <<"th:"<< psharemem->vehicle_pos.th << endl;
			cout << "x:"<<psharemem->vehicle_pos.x << endl;
			cout << "y:"<<psharemem->vehicle_pos.y << endl;
		}
		else if (stmp.find("GetPathList") == 0)
		{
			jsoncomm->SelectFixPath();
			for (int i = 0; i != psharemem->vehicle_paths.path_num;i++)
			{
				cout << "path" << i + 1 << ":" << &(psharemem->vehicle_paths.paths[i][0]) << endl;
			}
		}
		else if (stmp.find("RunPath:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->RunPath();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("GetLaserData") == 0)
		{
			jsoncomm->GetLaserData();
			for (int i = 0; i != MAX_LASER_NUM; i++)
			{
				cout << "angle" << i + 1 << ":" << psharemem->laserdatas[i].angle << endl;
				cout << "range" << i + 1 << ":" << psharemem->laserdatas[i].range << endl;
			}
		}
		else if (stmp.find("GetStatus") == 0)
		{
			jsoncomm->GetStatus();
			cout << "status:" << psharemem->run_status.run_status << endl;
			cout << "errcode:" << psharemem->run_status.errcode << endl;
		}
		else if (stmp.find("GetMapList") == 0)
		{
			jsoncomm->GetMapList();
			for (int i = 0; i != psharemem->vehicle_maps.map_num; i++)
			{
				cout << "map" << i + 1 << ":" << &(psharemem->vehicle_maps.maps[i][0]) << endl;
			}
		}
		else if (stmp.find("GetRecordMap") == 0)
		{
			jsoncomm->GetRecordMap();
			for (int i = 0; i != psharemem->vehicle_record_maps.map_num; i++)
			{
				cout << "map" << i + 1 << ":" << &(psharemem->vehicle_record_maps.maps[i][0]) << endl;
			}
		}
		else if (stmp.find("Mapping:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->Mapping();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("Pause") == 0)
		{
			bool ret = jsoncomm->Pause();
			PRINTRET(ret);
		}
		else if (stmp.find("Reboot") == 0)
		{
			bool ret = jsoncomm->Reboot();
			PRINTRET(ret);
		}
		else if (stmp.find("RecodeMap") == 0)
		{
			bool ret = jsoncomm->RecodeMap();
			PRINTRET(ret);
		}
		else if (stmp.find("RecordPath") == 0)
		{
			bool ret = jsoncomm->RecordPath();
			PRINTRET(ret);
		}
		else if (stmp.find("RobotForwardRecode") == 0)
		{
			bool ret = jsoncomm->RobotForwardRecode();
			PRINTRET(ret);
		}
		else if (stmp.find("RobotPauseRecode") == 0)
		{
			bool ret = jsoncomm->RobotPauseRecode();
			PRINTRET(ret);
		}
		else if (stmp.find("RobotTurnLeftRecode") == 0)
		{
			bool ret = jsoncomm->RobotTurnLeftRecode();
			PRINTRET(ret);
		}
		else if (stmp.find("RobotTurnRightRecode") == 0)
		{
			bool ret = jsoncomm->RobotTurnRightRecode();
			PRINTRET(ret);
		}
		else if (stmp.find("SavePath:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SavePath();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("SetAmclMap:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SetAmclMap();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("SetNaviMap:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SetNaviMap();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("SetPathFileState:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SetPathFileState();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("SetRobotLaserFileState:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->SetRobotLaserFileState();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("StopRecodeMap:") == 0)
		{
			char* par = strstr(ch, ":") + 1;
			if (par != NULL)
			{
				sprintf_s(psharemem->cmdbuf, par);
				bool ret = jsoncomm->StopRecodeMap();
				PRINTRET(ret);
			}
		}
		else if (stmp.find("StartRobot") == 0)
		{
			bool ret = jsoncomm->StartRobot();
			PRINTRET(ret);
		}
		else if (stmp.find("StopRobot") == 0)
		{
			bool ret = jsoncomm->StopRobot();
			PRINTRET(ret);
		}

	}
}


