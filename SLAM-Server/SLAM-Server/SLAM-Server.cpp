// SLAM-Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyDatabase.h"
#include "memdata.h"
#include "ShareMemory.h"
#include "CcomClien.h"
using namespace std;


/********************************************************************************************
                                ClientThreadFun1
��������ͻ���ͨѶ�̣߳�һ���û�����һ���߳�
���ӽ���ͨѶЭ��ο� CJsonComm��
��ͻ���ͨѶ  �Զ���

********************************************************************************************/
CMyDatabase mydatabse;

DWORD WINAPI ClientThreadFun1(LPVOID lp)//��ͨ�û�����
{
	string username = string((char*)lp);//��ȡ�û����û���
	TYPE_USER_INFO userinfo = g_usersonline[username];//��ȡ�û���Ϣ�ṹ��
	//TYPE_VEHICLE_INFO *vehicleinfo = vehiclesonline[userinfo.dovehiclename.c_str()];//��ȡ������С����Ϣ
	CcomClient comclient;
	if (true == comclient.InitCcom(&userinfo))
	{
		comclient.RunClientCcom();
	}
	g_usersonline.erase(username);//��������û�
	return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{	
	if (FALSE == CMyDatabase::ComInit())
	{
		cout << "ERROR: cominit failed!" << endl;
		return 0;
	}

	
	//BOOL ret = mydatabse.ConnectDatabase("ROBOT-PC", "SLAM", "sa", "11111111");
	//BOOL ret = mydatabse.ConnectDatabase("localhost", "slam", "root", "thunder865");
	BOOL ret = mydatabse.ConnectDatabase("172.16.14.118", "slam", "root", "thunder865");
	if (ret == FALSE)
	{
		cout << "ERROR: Connect Database failed" << endl;
		CMyDatabase::ComUninit();
		return 0;
	}
	CGroup<TAB_USER> cgret = mydatabse.QueryRecordeUser();
	//CGroup<TAB_VEHICLE> cgret1 = mydatabse.QueryRecordeVehicle();
	CGroup<TAB_NODE> cgret2 = mydatabse.QueryRecordeNode();
	//mydatabse.OutPutAllPath();
	//CGroup<TAB_USER> rrecord = mydatabse.QueryRecordeUserWithKey("wangjinhui");

	//CMyDatabase::ComUninit();

	//CFloyd cfloyd;
	//cfloyd.LoadDatabaseRecord(cgret2);
	//cfloyd.PrintFloyd();
	//vector<int> rett = cfloyd.FindShortestPaht(0, 4);
	//mydatabse.OutPutAppointPath(rett);

	//return 0;
	//extern map<string, TYPE_VEHICLE_INFO*> vehiclesonline;
	//TYPE_VEHICLE_INFO *v1 = new TYPE_VEHICLE_INFO();
	//v1->isonline = true;
	//v1->run_status.errcode = 0;
	//v1->run_status.run_status = 1;
	//v1->vehicle_maps.map_num = 2;
	//memset(&v1->vehicle_maps.maps[0][0], 0, MAX_MAPNAME_LEN);
	//memcpy(&v1->vehicle_maps.maps[0][0], "map1", strlen("map1"));
	//memset(&v1->vehicle_maps.maps[1][0], 0, MAX_MAPNAME_LEN);
	//memcpy(&v1->vehicle_maps.maps[1][0], "map2", strlen("map2"));
	//v1->vehicle_paths.path_num = 2;
	//memset(&v1->vehicle_paths.paths[0][0], 0, MAX_MAPNAME_LEN);
	//memcpy(&v1->vehicle_paths.paths[0][0], "path1", strlen("path1"));
	//memset(&v1->vehicle_paths.paths[1][0], 0, MAX_MAPNAME_LEN);
	//memcpy(&v1->vehicle_paths.paths[1][0], "map2", strlen("map2"));

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
	//����Tcp������socket
	SOCKET sockSrv6000 = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET sockSrv7700 = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET sockSrv8800 = socket(AF_INET, SOCK_STREAM, 0);
	//��������ַ
	SOCKADDR_IN addrSrv6000;
	SOCKADDR_IN addrSrv7700;
	SOCKADDR_IN addrSrv8800;
	addrSrv6000.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv6000.sin_family = AF_INET;
	addrSrv6000.sin_port = htons(6000);
	addrSrv7700.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv7700.sin_family = AF_INET;
	addrSrv7700.sin_port = htons(7700);
	addrSrv8800.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv8800.sin_family = AF_INET;
	addrSrv8800.sin_port = htons(8800);
	//��socket���ַ����һ��
	bind(sockSrv6000, (SOCKADDR*)&addrSrv6000, sizeof(SOCKADDR));
	bind(sockSrv7700, (SOCKADDR*)&addrSrv7700, sizeof(SOCKADDR));
	bind(sockSrv8800, (SOCKADDR*)&addrSrv8800, sizeof(SOCKADDR));
	//��ʼ�����ͻ�������,���������Ϊ5
	listen(sockSrv6000, 50);
	listen(sockSrv7700, 50);
	listen(sockSrv8800, 50);
	while (1)
	{
		fd_set fdset_r;
		timeval tv = { 1, 0 };

		/**********************************************************************
			�ͻ���½socket����
			***********************************************************************/
		//���ڴ�ſͻ��˵�ַ
		SOCKADDR_IN addrClient6000;
		int len = sizeof(SOCKADDR_IN);
		//���Ͻ��տͻ��˷��͵�����
		SOCKET sockClient6000;
		//���յ��Ŀͻ�������socket
		FD_ZERO(&fdset_r);
		FD_SET(sockSrv6000, &fdset_r);
		if (select(0, &fdset_r, NULL, NULL, &tv) > 0)
		{
			sockClient6000 = accept(sockSrv6000, (SOCKADDR *)&addrClient6000, &len);
			if (sockClient6000 == NULL)
			{
			}
			else
			{
				struct sockaddr_in sa;
				int len = sizeof(sa);
				if (!getpeername(sockClient6000, (struct sockaddr *)&sa, &len))
				{
					printf("�ͻ���IP��%s ", inet_ntoa(sa.sin_addr));
					printf("�ͻ���PORT��%d \r\n", ntohs(sa.sin_port));
				}
				DWORD timeout = 30000;
				setsockopt(sockClient6000, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(DWORD));
				char tpbuf[4096] = "";
				memset(tpbuf, 0, 4096);
				int rlen = recv(sockClient6000, (char*)tpbuf, 4096, 0);
				int usertype = -1;
				string uname = "";
				string upwd = "";
				Json::Reader reader;
				Json::Value value;
				if (reader.parse(tpbuf, value))
				{
					usertype = value["type"].asInt();
					uname = value["user"].asString();
					upwd = value["pwd"].asString();
					cout << "user " << uname.c_str() << " login" << endl;
					CGroup<TAB_USER> rrecord = mydatabse.QueryRecordeUserWithKey(uname.c_str());
					if (rrecord.GetSize() >= 1 && rrecord.GetAt(0).pwd == upwd)//�û���������ȷ
					{
						TYPE_USER_INFO oneinfo;
						oneinfo.sockConn = sockClient6000;
						oneinfo.ip = addrClient6000.sin_addr.S_un.S_addr;
						oneinfo.port = addrClient6000.sin_port;
						oneinfo.usertab = rrecord.GetAt(0);
						g_usersonline[uname] = oneinfo;
						char*puname = new char[50];
						memcpy(puname, uname.c_str(), uname.length() + 1);
						HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientThreadFun1, puname, 0, 0);
						Json::Value jsret;
						jsret["status"] = true;
						send(sockClient6000, jsret.toStyledString().c_str(), jsret.toStyledString().length(), 0);
						timeout = 0;
						setsockopt(sockClient6000, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(DWORD));
					}
					else//�û������벻ƥ��
					{
						Json::Value jsret;
						jsret["status"] = false;
						send(sockClient6000, jsret.toStyledString().c_str(), jsret.toStyledString().length(), 0);
						closesocket(sockClient6000);
					}
				}
			}
		}

		//	/**********************************************************************
		//	���������7700socket����
		//	***********************************************************************/

		//���ڴ�ſͻ��˵�ַ
		SOCKADDR_IN addrClient7700;
		len = sizeof(SOCKADDR_IN);
		//���Ͻ��տͻ��˷��͵�����
		SOCKET sockClient7700;
		FD_ZERO(&fdset_r);
		FD_SET(sockSrv7700, &fdset_r);
		if (select(0, &fdset_r, NULL, NULL, &tv) > 0)
		{
			//���յ��Ŀͻ�������socket
			sockClient7700 = accept(sockSrv7700, (SOCKADDR *)&addrClient7700, &len);
			if (sockClient7700 == NULL)
			{
			}
			else //������С����½�����ӽ���
			{
				struct sockaddr_in sa;
				int len = sizeof(sa);
				string robotip = "";
				if (!getpeername(sockClient7700, (struct sockaddr *)&sa, &len))
				{
					robotip = inet_ntoa(sa.sin_addr);
					printf("7700���������IP��%s ", inet_ntoa(sa.sin_addr));
					printf("7700���������PORT��%d \r\n", ntohs(sa.sin_port));
				}
				CShareMemory *sharememory = NULL;
				if (g_vehiclesonline.count(robotip))
				{
					memset(g_vehiclesonline[robotip], 0, sizeof(TYPE_VEHICLE_INFO));
					g_vehiclesonline[robotip]->isonline = true;
					g_vehiclesonline[robotip]->cmdflag = TYPE_VEHICLE_INFO::E_RELASE;
				}
				else
				{
					sharememory = new CShareMemory((char *)robotip.c_str(), sizeof(TYPE_VEHICLE_INFO));
					TYPE_VEHICLE_INFO *vehicle_info = (TYPE_VEHICLE_INFO *)sharememory->m_pmem;
					vehicle_info->isonline = true;
					g_vehiclesonline[robotip] = vehicle_info;
					g_vehiclesonline[robotip]->cmdflag = TYPE_VEHICLE_INFO::E_RELASE;
				}

				TCHAR strcmd[1024] = _T("D:\\workspace\\childprocess\\Debug\\childprocess.exe  ");
				//_T("..\\..\\childprocess\\Debug\\childprocess.exe ");
				TCHAR vname[100] = {};
				MultiByteToWideChar(CP_ACP, 0, robotip.c_str(), -1, vname, 100);
				_tcscat_s(strcmd, vname);
				STARTUPINFO si;
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				si.wShowWindow = SW_HIDE;
				PROCESS_INFORMATION pi;
				ZeroMemory(&pi, sizeof(pi));

				BOOL bRet = CreateProcess(NULL, strcmd/*(LPTSTR)strpath.c_str()*/, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);//
				if (!bRet)
				{
					delete sharememory;
					g_vehiclesonline.erase(robotip);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					cout << "error:CreateProcess" << endl;
					continue;
				}
				TYPE_VEHICLE_INFO *vehicle_info = (TYPE_VEHICLE_INFO *)sharememory->m_pmem;
				vehicle_info->vehicle_ip = inet_ntoa(sa.sin_addr);
				vehicle_info->vehicle_port = ntohs(sa.sin_port);
				int ctime = 0;
				while (0 == vehicle_info->childprocessid)
				{
					ctime++;
					Sleep(100);
				}

				if (0 != vehicle_info->childprocessid)
				{
					WSADuplicateSocket(sockClient7700, vehicle_info->childprocessid, &(vehicle_info->wasinfo7700));
				}
				else
				{
					closesocket(sockClient7700);
					g_vehiclesonline.erase(robotip);
				}

			}
		}

		///**********************************************************************
		//���������8800socket����
		//***********************************************************************/
		//���ڴ�ſͻ��˵�ַ
		SOCKADDR_IN addrClient8800;
		len = sizeof(SOCKADDR_IN);
		//���Ͻ��տͻ��˷��͵�����
		SOCKET sockClient8800;
		FD_ZERO(&fdset_r);
		FD_SET(sockSrv8800, &fdset_r);
		if (select(0, &fdset_r, NULL, NULL, &tv) > 0)
		{
			//���յ��Ŀͻ�������socket
			sockClient8800 = accept(sockSrv8800, (SOCKADDR *)&addrClient8800, &len);
			if (sockClient8800 == NULL)
			{

			}
			else
			{
				struct sockaddr_in sa;
				int len = sizeof(sa);
				string strip;
				if (!getpeername(sockClient8800, (struct sockaddr *)&sa, &len))
				{
					strip = inet_ntoa(sa.sin_addr);
					printf("8800���������IP��%s ", inet_ntoa(sa.sin_addr));
					printf("8800���������PORT��%d \r\n", ntohs(sa.sin_port));
				}
				if (g_vehiclesonline.count(strip))//��������˹����ڴ��ҵ�7700�˿�С���ڴ�
				{
					TYPE_VEHICLE_INFO* vehicleinfo = g_vehiclesonline[strip];
					if (0 != vehicleinfo->childprocessid)
					{
						WSADuplicateSocket(sockClient8800, vehicleinfo->childprocessid, &(vehicleinfo->wasinfo8800));
					}
					else
					{
						closesocket(sockClient8800);
					}
				}
				else//���δ���乲���ڴ�ر�socket
				{
					closesocket(sockClient8800);
				}
				
			}
		}
		
	}

	//����socket��̻���
	WSACleanup();
	CMyDatabase::ComUninit();
	return 0;
}
