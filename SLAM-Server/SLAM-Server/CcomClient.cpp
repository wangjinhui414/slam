#include "stdafx.h"
#include "CcomClien.h"


extern CMyDatabase mydatabse;
bool CcomClient::InitCcom(TYPE_USER_INFO *userinfo )
{
	if (userinfo == NULL)	return false;
	m_userinfo = userinfo;
	m_vehicleinfo =NULL;
	return true;
}


void CcomClient::TCPSendToClient(string sendstr)
{
	int ret = send(m_userinfo->sockConn, (char*)sendstr.c_str(), sendstr.length(), 0);
	if (ret > 0)
	{
		cout << "send:" << sendstr.c_str() << endl;
	}
	else
	{
		m_err = -1;
	}

}
string CcomClient::TCPRecvFromClient()
{
	//DWORD timeout = 0;
	char buf[8192] = "";
	//setsockopt(m_userinfo->sockConn, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(DWORD));
	int ret = recv(m_userinfo->sockConn, buf, 8192, 0);
	if (ret > 0)
	{
		cout << "recv:" << buf << endl;
	}
	else
	{
		m_err = -1;
	}
	return string(buf);
}
bool CcomClient::WaitVehicleResponse(DWORD time)
{
	DWORD timeout = 0;
	MYTOOLS::StartTimeCount(timeout);
	while (m_vehicleinfo->cmdflag != TYPE_VEHICLE_INFO::E_INVALID)
	{
		if (MYTOOLS::EndTimeCount(timeout) > time)
		{
			return false;
		}
	}
	return true;
}

int CcomClient::TransSendToVehicle(string strfun,string strpar)
{
	if (m_vehicleinfo == NULL)
	{
		Json::Value value;
		value["status"] = false;
		Json::Value strerr;
		strerr["reason"] = "please select robot!";
		value["data"] = strerr;
		TCPSendToClient(value.toStyledString());
		return 1;
	}
	while (m_vehicleinfo->cmdflag != TYPE_VEHICLE_INFO::E_RELASE)
	{
		Sleep(500);
	}
	if (strfun == "SetVehiclePos")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETROBOTPOS;
	}
	else if (strfun == "GetVehiclePos")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETROBOTPOS;
	}
	else if (strfun == "GetPathList")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SELECTFIXPATH;
	}
	else if (strfun == "GetMapList")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETMAPLIST;
	}
	else if (strfun == "GetRecordMapList")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETRECODEMAPS;
	}
	else if (strfun == "GetVehicleStatus")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETSTATUS;
	}
	else if (strfun == "StartRobot")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::STARTROBOT;
	}
	else if (strfun == "StopRobot")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::STOPROBOT;
	}
	else if (strfun == "SetAmclMap")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETAMCLMAP;
	}
	else if (strfun == "SetNaviMap")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETNAVIMAP;
	}
	else if (strfun == "Pause")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::PAUSE;
	}
	else if (strfun == "Continue")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::CONTINUE;
	}
	else if (strfun == "Reboot")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::REBOOT;
	}
	else if (strfun == "RunPath")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::RUNPATH;
	}
	else if (strfun == "RecordPath")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::RECODEPATH;
	}
	else if (strfun == "SavePath")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SAVEPATH;
	}
	else if (strfun == "MakeMaping")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::MAPPING;
	}
	else if (strfun == "StartRecordMap")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::RECODEMAP;
	}
	else if (strfun == "RobotForwardRecode")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ROBOTFORWARDRECODE;
	}
	else if (strfun == "RobotPauseRecode")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ROBOTPAUSERECODE;
	}
	else if (strfun == "RobotTurnLeftRecode")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ROBOTTURNLEFTRECODE;
	}
	else if (strfun == "RobotTurnRightRecode")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ROBOTTURNRIGHTRECODE;
	}
	else if (strfun == "RobotBackWardRecode")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ROBOTBACKWARDCODE;
	}
	else if (strfun == "SaveRecordMap")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::STOPRECODEMAP;
	}
	else if (strfun == "SetPathFileState")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETPATHFILESTATE;
	}
	else if (strfun == "SetRobotLaserFileState")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETROBOTLASERFILESTATE;
	}
	else if (strfun == "GetLaserData")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETLASER;
	}
	else if (strfun == "GetGlobalPath")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GETGLOBALPATH;
	}
	else if (strfun == "ReadSOC")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::READSOC;
	}
	else if (strfun == "SetVolt")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::SETVOLTE;
	}
	else if (strfun == "ReadLockStatus")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::READLOCKSTATUS;
	}
	else if (strfun == "Unlock")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::UNLOCK;
	}
	else if (strfun == "LeftTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::LEFTTW;
	}
	else if (strfun == "RightTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::RIGHTTW;
	}
	else if (strfun == "LeftRightTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::LEFTRIGHTTW;
	}
	else if (strfun == "GreenTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::GREENTW;
	}
	else if (strfun == "YellowTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::YELLOWTW;
	}
	else if (strfun == "BlueTW")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::BLUETW;
	}
	else if (strfun == "OneRelayOnOff")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ONERELAYONOFF;
	}
	else if (strfun == "AllRelayOn")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ALLRELAYON;
	}
	else if (strfun == "AllRelayOff")
	{
		m_vehicleinfo->cmd = TYPE_VEHICLE_INFO::ALLRELAYOFF;
	}


	memset(m_vehicleinfo->cmdbuf, 0, MAX_CMDBUF_SIZE);
	strcpy(m_vehicleinfo->cmdbuf, strpar.c_str());
	m_vehicleinfo->cmdflag = TYPE_VEHICLE_INFO::E_VELID;
	bool ret = WaitVehicleResponse(1000000);
	if (ret == true)//正常返回
	{
		return 0;
	}
	//else//超时
	//{
	//	Json::Value value;
	//	value["status"] = false;
	//	Json::Value strerr;
	//	strerr["reason"] = "robot return timeout!";
	//	value["data"] = strerr;
	//	TCPSendToClient(value.toStyledString());
	//	return 2;
	//}

}


void CcomClient::RunClientCcom()
{
	//与客户端通讯内容
	while (1)
	{
		string stmp = TCPRecvFromClient();
		if (m_err == -1)	return;
		Json::Reader reader;
		Json::Value value;
		string sfun = "";
		string spara = "";
		if (reader.parse(stmp, value))
		{
			sfun = value["function"].asString();
			spara = value["parameter"].asString();
		}
		else
		{
			continue;
		}
	    //无需与车辆交互的指令
		if (sfun == "GetVehicleList")
		{
			ResponseGetVehicleList(); continue;
		}
		else if (sfun == "SetOperateVehicle")
		{
			ResponseSetOperatVehicle(spara); continue;
		}
		else if (sfun == "GetOperateVehicle")
		{
			ResponseGetOperatVehicle(); continue;
		}
		//数据库
		else if (sfun == "GetUserRecord")
		{
			ResponseGetUserRecord(); continue;
		}
		else if (sfun == "GetVehicleRecord")
		{
			ResponseGetVehicleRecord(); continue;
		}
		else if (sfun == "GetNodeRecord")
		{
			ResponseGetNodeRecord(); continue;
		}
		else if (sfun == "UpdataUserRecord")
		{
			ResponseUpdataUserRecord(stmp); continue;
		}
		else if (sfun == "UpdataVehicleRecord")
		{
			ResponseUpdataVehicleRecord(stmp); continue;
		}
		else if (sfun == "UpdataNodeRecord")
		{
			ResponseUpdataNodeRecord(stmp); continue;
		}

		else if (sfun == "DeleteUserRecord")
		{
			ResponseDeleteUserRecord(stmp); continue;
		}
		else if (sfun == "DeleteVehicleRecord")
		{
			ResponseDeleteVehicleRecord(stmp); continue;
		}
		else if (sfun == "DeleteNodeRecord")
		{
			ResponseDeleteNodeRecord(stmp); continue;
		}
		else if (sfun == "CreatePath1")
		{
			ResponseCreatePath1(stmp); continue;
		}
		else if (sfun == "CreatePath2")
		{
			ResponseCreatePath2(stmp); continue;
		}
		else if (sfun == "Exit")//客户端退出
		{
			return;
		}
		//需要与车辆交互的指令
		if (TransSendToVehicle(sfun, spara) != 0)	
			continue;;
		switch (m_vehicleinfo->cmd)
		{
		case TYPE_VEHICLE_INFO::SETROBOTPOS:            ResponseSetVehiclePos(); break;
		case TYPE_VEHICLE_INFO::GETROBOTPOS:            ResponseGetVehiclePos(); break;
		case TYPE_VEHICLE_INFO::SELECTFIXPATH:          ResponseGetVehicleConstPathList(); break;
		case TYPE_VEHICLE_INFO::RUNPATH:                ResponseRunPath(); break;
		case TYPE_VEHICLE_INFO::GETLASER:               ResponseGetLaserData(); break;
		case TYPE_VEHICLE_INFO::GETGLOBALPATH:          ResponseGetGlobalPath(); break;
		case TYPE_VEHICLE_INFO::GETSTATUS:              ResponseGetVehicleStatus(); break;
		case TYPE_VEHICLE_INFO::GETMAPLIST:             ResponseGetVehicleMapList(); break;
		case TYPE_VEHICLE_INFO::GETRECODEMAPS:          ResponseGetVehicleRecordMapList(); break;
		case TYPE_VEHICLE_INFO::MAPPING:                ResponseMakeMaping(); break;
		case TYPE_VEHICLE_INFO::PAUSE:                  ResponsePause(); break;
		case TYPE_VEHICLE_INFO::CONTINUE:                  ResponseContinue(); break;
		case TYPE_VEHICLE_INFO::REBOOT:                 ResponseRebootVehicle(); break;
		case TYPE_VEHICLE_INFO::RECODEMAP:              ResponseMakeMaping(); break;
		case TYPE_VEHICLE_INFO::RECODEPATH:             ResponseStartRecordPath(); break;
		case TYPE_VEHICLE_INFO::ROBOTFORWARDRECODE:     ResponseRobotForwardRecode(); break;
		case TYPE_VEHICLE_INFO::ROBOTPAUSERECODE:       ResponseRobotPauseRecode(); break;
		case TYPE_VEHICLE_INFO::ROBOTTURNLEFTRECODE:    ResponseRobotTurnLeftRecode(); break;
		case TYPE_VEHICLE_INFO::ROBOTTURNRIGHTRECODE:   ResponseRobotTurnRightRecode(); break;
		case TYPE_VEHICLE_INFO::ROBOTBACKWARDCODE:		ResponseRobotBackWardRecode(); break;
		case TYPE_VEHICLE_INFO::SAVEPATH:               ResponseSavePath(); break;
		case TYPE_VEHICLE_INFO::SETAMCLMAP:             ResponseSetAmclMap(); break;
		case TYPE_VEHICLE_INFO::SETNAVIMAP:             ResponseSetNaviMap(); break;
		case TYPE_VEHICLE_INFO::SETPATHFILESTATE:       ResponseSetPahtFileState(); break;
		case TYPE_VEHICLE_INFO::SETROBOTLASERFILESTATE: ResponseSetRobotLaserState(); break;
		case TYPE_VEHICLE_INFO::STARTROBOT:             ResponseStartRobot(); break;
		case TYPE_VEHICLE_INFO::STOPRECODEMAP:          ResponseSaveRecordMap(); break;
		case TYPE_VEHICLE_INFO::STOPROBOT:              ResponseStopRobot(); break;          
		//8800
		case TYPE_VEHICLE_INFO::READSOC:				
		case TYPE_VEHICLE_INFO::SETVOLTE:				
		case TYPE_VEHICLE_INFO::READLOCKSTATUS:			
		case TYPE_VEHICLE_INFO::UNLOCK:					
		case TYPE_VEHICLE_INFO::LEFTTW:					
		case TYPE_VEHICLE_INFO::RIGHTTW:				
		case TYPE_VEHICLE_INFO::LEFTRIGHTTW:			
		case TYPE_VEHICLE_INFO::GREENTW:				
		case TYPE_VEHICLE_INFO::YELLOWTW:				
		case TYPE_VEHICLE_INFO::BLUETW:					
		case TYPE_VEHICLE_INFO::ONERELAYONOFF:						
		case TYPE_VEHICLE_INFO::ALLRELAYON:				
		case TYPE_VEHICLE_INFO::ALLRELAYOFF:			 ComReponse(); break;
		default:break;
		}
		m_vehicleinfo->cmdflag = TYPE_VEHICLE_INFO::E_RELASE;
	}
}

/*****************************************************服务函数******************************************************/
void CcomClient::ResponseGetVehicleList()
{
	string slist = "";
	Json::Value jret;
	jret["status"] = true;
	jret["data"] = Json::nullValue;
	
	for (map<string, TYPE_VEHICLE_INFO*>::iterator it = g_vehiclesonline.begin(); it != g_vehiclesonline.end(); it++)
	{
		Json::Value jrobot;
		jrobot["robot"] = it->first;
		jret["data"].append(jrobot);
	}

	TCPSendToClient(jret.toStyledString());

}

void CcomClient::ResponseSetOperatVehicle(string newvehicle)
{
	Json::Value jvalue;
	if (!g_vehiclesonline.count(newvehicle))
	{
		jvalue["status"] = false;
		jvalue["data"] = Json::nullValue;
		TCPSendToClient(jvalue.toStyledString());
		return;
	}
	m_userinfo->dovehiclename = newvehicle;//更改操作车辆
	m_vehicleinfo = g_vehiclesonline[m_userinfo->dovehiclename.c_str()];//获取操作的小车信息
	if (m_vehicleinfo != NULL)
	{
		jvalue["status"] = true;
		jvalue["data"] = Json::nullValue;
		TCPSendToClient(jvalue.toStyledString());
	}
	else
	{
		jvalue["status"] = false;
		jvalue["data"] = Json::nullValue;
		TCPSendToClient(jvalue.toStyledString());
	}
}

void CcomClient::ResponseGetOperatVehicle()
{
	Json::Value jvalue;
	Json::Value jrobot;
	jrobot["robot"] = string(m_userinfo->dovehiclename);
	jvalue["status"] = true;
	jvalue["data"] = jrobot;
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseGetVehicleConstPathList()
{
	Json::Value jvalue;
	jvalue["status"] = true;
	Json::Value jdata;
	for (int i = 0; i < m_vehicleinfo->vehicle_paths.path_num; i++)
	{
		Json::Value jpath;
		jpath["path"] = string(&m_vehicleinfo->vehicle_paths.paths[i][0]);
		jdata.append(jpath);
	}
	jvalue["data"] = jdata;
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseGetVehicleMapList()
{
	Json::Value jvalue;
	jvalue["status"] = true;
	Json::Value jdata;
	for (int i = 0; i != m_vehicleinfo->vehicle_maps.map_num; i++)
	{
		Json::Value jpath;
		jpath["map_name"] = string(&m_vehicleinfo->vehicle_maps.maps[i][0]);
		jdata.append(jpath);
	}
	jvalue["data"] = jdata;
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseGetVehicleRecordMapList()
{
	Json::Value jvalue;
	jvalue["status"] = true;
	Json::Value jdata;
	for (int i = 0; i != m_vehicleinfo->vehicle_record_maps.map_num; i++)
	{
		Json::Value jpath;
		jpath["map_name"] = string(&m_vehicleinfo->vehicle_record_maps.maps[i][0]);
		jdata.append(jpath);
	}
	jvalue["data"] = jdata;
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseGetVehicleStatus()
{
	Json::Value jvalue;
	jvalue["status"] = true;
	Json::Value jdata;
	jdata["errcode"] = m_vehicleinfo->run_status.errcode;
	jdata["status"] = m_vehicleinfo->run_status.run_status;
	jvalue["data"] = jdata;
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseStartRobot()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseStopRobot()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseSetAmclMap()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseSetNaviMap()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseSetVehiclePos()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseGetVehiclePos()
{
	Json::Value jvalue;
	jvalue["status"] = true;
	Json::Value jdata ;
	jdata["last_dx"] = m_vehicleinfo->vehicle_pos.last_dx;
	jdata["th"] = m_vehicleinfo->vehicle_pos.th;
	jdata["x"] = m_vehicleinfo->vehicle_pos.x;
	jdata["y"] = m_vehicleinfo->vehicle_pos.y;
	jvalue["data"] = jdata;
	TCPSendToClient(jvalue.toStyledString());
}
void CcomClient::ResponsePause()//暂停下车
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseContinue()//暂停下车
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

void CcomClient::ResponseRebootVehicle()//重启小车
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRunPath()//执行路径运行
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseStartRecordPath()//记录路径
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseSavePath()//保存路径
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseMakeMaping()//执行制图任务
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseStartRecordMap()//开始记录地图
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRobotForwardRecode()//记录地图时执行机器人运动
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRobotPauseRecode()//记录地图时执行机器人停止
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRobotTurnLeftRecode()//记录地图时执行机器人向左
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRobotTurnRightRecode()//记录地图时执行机器人向右
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseRobotBackWardRecode()//记录地图时执行机器人向右
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}
void CcomClient::ResponseSaveRecordMap()//停止并保存记录地图
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

void CcomClient::ResponseSetPahtFileState()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

void CcomClient::ResponseSetRobotLaserState()
{
	//Json::Value jvalue;
	//jvalue["status"] = true;
	//jvalue["data"] = Json::nullValue;
	//TCPSendToClient(jvalue.toStyledString());
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

void CcomClient::ResponseGetLaserData()
{
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

void CcomClient::ResponseGetGlobalPath()
{
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}

//数据库
void CcomClient::ResponseGetUserRecord()
{
	TCPSendToClient(mydatabse.QueryRecordeUserJson());
}
void CcomClient::ResponseGetVehicleRecord()
{
	TCPSendToClient(mydatabse.QueryRecordeVehicleJson());
}
void CcomClient::ResponseGetNodeRecord()
{
	TCPSendToClient(mydatabse.QueryRecordeNodeJson());
}
void CcomClient::ResponseUpdataUserRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.UpdataRecordUserJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}
void CcomClient::ResponseUpdataVehicleRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.UpdataRecordVehicleJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}
void CcomClient::ResponseUpdataNodeRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.UpdataRecordNodeJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseDeleteUserRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.DeleteRecordUserJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}
void CcomClient::ResponseDeleteVehicleRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.DeleteRecordVehicleJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}
void CcomClient::ResponseDeleteNodeRecord(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = mydatabse.DeleteRecordNodeJson(jstr);
	TCPSendToClient(jvalue.toStyledString());
}



void CcomClient::ResponseCreatePath1(string jstr)
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;

	Json::Reader reader;
	Json::Value jnodes;
	int istart = -1;
	int iend = -1;
	if (reader.parse(jstr, jnodes))
	{
		istart = jnodes["nodes"]["startnode"].asInt();
		iend = jnodes["nodes"]["endnode"].asInt();
		if (istart >= 0 && iend >= 0)
		{
			CGroup<TAB_NODE> cgret2 = mydatabse.QueryRecordeNode();
			CFloyd cfloyd;
			cfloyd.LoadDatabaseRecord(cgret2);
			//cfloyd.PrintFloyd();
			vector<int> rett = cfloyd.FindShortestPaht(istart, iend);
			bool ouret = mydatabse.OutPutAppointPath(rett);
			if (ouret == true)
			{
				string sstart = MYTOOLS::inttostring(istart);
				string ssend = MYTOOLS::inttostring(iend);
				string spathname = sstart + "-" + ssend + ".txt";
				if (mydatabse.FtpAppointPath(spathname, "192.168.33.99"))// m_vehicleinfo->vehicle_ip))
					jvalue["status"] = true;
				else
					jvalue["status"] = false;
			}
			else
			{
				jvalue["status"] = false;
			}

		}
	}
	TCPSendToClient(jvalue.toStyledString());
}

void CcomClient::ResponseCreatePath2(string jstr)
{
	Json::Value jret;
	jret["data"] = Json::nullValue;

	Json::Reader reader;
	Json::Value jvalue;
	if (reader.parse(jstr, jvalue))
	{
		vector<int> nodes;
		vector<int> allnodes;
		Json::Value jndoes = jvalue["nodes"]; 
		for (int i = 0; i != jndoes.size(); i++)
		{
			nodes.push_back(jndoes[i]["node"].asInt());
		}
		CGroup<TAB_NODE> cgret2 = mydatabse.QueryRecordeNode();
		CFloyd cfloyd;
		cfloyd.LoadDatabaseRecord(cgret2);
		
		for (vector<int>::iterator it = nodes.begin(); it != (nodes.end()-1);it++)
		{
			vector<int> rett = cfloyd.FindShortestPaht(*it, *(it+1));
			for (vector<int>::iterator jt = rett.begin(); jt != (rett.end() - 1); jt++)
			{
				allnodes.push_back(*jt);
			}
		}
		allnodes.push_back(nodes[nodes.size()-1]);
		bool ouret = mydatabse.OutPutAppointPath(allnodes);
		if (ouret == true)
		{
			string sstart = MYTOOLS::inttostring(allnodes[0]);
			string ssend = MYTOOLS::inttostring(allnodes[allnodes.size() - 1]);
			string spathname = sstart + "-" + ssend;
			if (mydatabse.FtpAppointPath(spathname, m_vehicleinfo->vehicle_ip))
				jret["status"] = true;
			else
				jret["status"] = false;
		}
		else
		{
			jvalue["status"] = false;
		}
	}
	TCPSendToClient(jret.toStyledString());
}


void CcomClient::ComReponse()
{
	TCPSendToClient(m_vehicleinfo->cmdbuf);
}


