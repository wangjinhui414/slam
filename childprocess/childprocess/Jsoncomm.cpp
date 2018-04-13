#include "stdafx.h"
#include "Jsoncomm.h"



CJsonComm::CJsonComm(TYPE_VEHICLE_INFO* psharememory, SOCKET socket7700, SOCKET socket8800)
{
	m_psharememo = psharememory;
	m_sockclient7700 = socket7700;
	m_sockclient8800 = socket8800;
}

CJsonComm::~CJsonComm()
{


}

void CJsonComm::CloseJsoncom()
{
	closesocket(m_sockclient7700);
	m_psharememo->isonline = false;
	//m_psharememo->socket_vehicle = NULL;
}

void CJsonComm::RunmComVehicle()
{
	DWORD time_getpos = 0;
	while (1)
	{
		
		if (m_psharememo->cmdflag == TYPE_VEHICLE_INFO::E_VELID)
		{
			cout << m_psharememo->cmd << endl;
			switch (m_psharememo->cmd)
			{
		    //7700
			case TYPE_VEHICLE_INFO::REFRESH:                ReFreshVehicleData(); break;
			case TYPE_VEHICLE_INFO::SETROBOTPOS:            SetRobotPos(); break;
			case TYPE_VEHICLE_INFO::GETROBOTPOS:            GetRobotPos(); break;
			case TYPE_VEHICLE_INFO::SELECTFIXPATH:          SelectFixPath(); break;
			case TYPE_VEHICLE_INFO::RUNPATH:                RunPath(); break;
			case TYPE_VEHICLE_INFO::GETLASER:               GetLaserData(); break;
			case TYPE_VEHICLE_INFO::GETGLOBALPATH:          GetGlobalPath(); break;
			case TYPE_VEHICLE_INFO::GETSTATUS:              GetStatus(); break;
			case TYPE_VEHICLE_INFO::GETMAPLIST:             GetMapList(); break;
			case TYPE_VEHICLE_INFO::GETRECODEMAPS:          GetRecordMap(); break;
			case TYPE_VEHICLE_INFO::MAPPING:                Mapping(); break;
			case TYPE_VEHICLE_INFO::PAUSE:                  Pause(); break;
			case TYPE_VEHICLE_INFO::CONTINUE:                  Continue(); break;
			case TYPE_VEHICLE_INFO::REBOOT:                 Reboot(); break;
			case TYPE_VEHICLE_INFO::RECODEMAP:              RecodeMap(); break;
			case TYPE_VEHICLE_INFO::RECODEPATH:             RecordPath(); break;
			case TYPE_VEHICLE_INFO::ROBOTFORWARDRECODE:     RobotForwardRecode(); break;
			case TYPE_VEHICLE_INFO::ROBOTPAUSERECODE:       RobotPauseRecode(); break;
			case TYPE_VEHICLE_INFO::ROBOTTURNLEFTRECODE:    RobotTurnLeftRecode(); break;
			case TYPE_VEHICLE_INFO::ROBOTTURNRIGHTRECODE:   RobotTurnRightRecode(); break;
			case TYPE_VEHICLE_INFO::ROBOTBACKWARDCODE:		RobotBackwardRecode(); break;
			case TYPE_VEHICLE_INFO::SAVEPATH:               SavePath(); break;
			case TYPE_VEHICLE_INFO::SETAMCLMAP:             SetAmclMap(); break;
			case TYPE_VEHICLE_INFO::SETNAVIMAP:             SetNaviMap(); break;
			case TYPE_VEHICLE_INFO::SETPATHFILESTATE:       SetPathFileState(); break;
			case TYPE_VEHICLE_INFO::SETROBOTLASERFILESTATE: SetRobotLaserFileState(); break;
			case TYPE_VEHICLE_INFO::STARTROBOT:             StartRobot(); break;
			case TYPE_VEHICLE_INFO::STOPRECODEMAP:          StopRecodeMap(); break;
			case TYPE_VEHICLE_INFO::STOPROBOT:              StopRobot(); break;
			//8800
			case TYPE_VEHICLE_INFO::READSOC:				ReadSoc(); break;
			case TYPE_VEHICLE_INFO::SETVOLTE:				SetVolteF(); break;
			case TYPE_VEHICLE_INFO::READLOCKSTATUS:			GetLockStatus(); break;
			case TYPE_VEHICLE_INFO::UNLOCK:					OneUnlock(); break;
			case TYPE_VEHICLE_INFO::LEFTTW:					LeftTW(); break;
			case TYPE_VEHICLE_INFO::RIGHTTW:				RightTW(); break;
			case TYPE_VEHICLE_INFO::LEFTRIGHTTW:			LeftRightTW(); break;
			case TYPE_VEHICLE_INFO::GREENTW:				GreenTW(); break;
			case TYPE_VEHICLE_INFO::YELLOWTW:				YellowTW(); break;
			case TYPE_VEHICLE_INFO::BLUETW:					BlueTW(); break;
			case TYPE_VEHICLE_INFO::ONERELAYONOFF:				OneRelayONOFF(); break;
			case TYPE_VEHICLE_INFO::ALLRELAYON:				AllRelayON(); break;
			case TYPE_VEHICLE_INFO::ALLRELAYOFF:			ALLRelayOFF(); break;
			default:break;
			}
			cout << m_psharememo->cmd << endl;
			m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		
		}
		//if (MYTOOLS::EndTimeCount(time_getpos) > 1000)
		//{
		//	GetRobotPos();
		//	GetStatus();
		//	MYTOOLS::StartTimeCount(time_getpos);
		//}
	}
}

void CJsonComm::SendJsonString7700(string jstr)
{
	int ret = send(m_sockclient7700, (char*)jstr.c_str(), jstr.length(), 0);
	if (ret > 0)
	{
		cout << "send-->" << jstr.c_str() << endl;
	}
	else
	{
		m_err = -1;
	}
}
int findnum(char* src, char ch)
{
	char *psch = src;
	int ret = 0;
	while ((psch = strchr(psch, ch))!=NULL)
	{
		psch++;
		ret++;
	}
	return ret;
}
string CJsonComm::RecvJsonString7700()
{
	DWORD timeout = 2000;
	char buf[40960] = "";
	//setsockopt(m_sockclient7700, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	int len=0;
// 	int leftnum = 0, rightnum = 0;
// 	DWORD ztime=0;
// 	while (1)
// 	{
// 		int ret = 0;
// 		ret = recv(m_sockclient7700, &buf[len], 40960, 0);
// 		leftnum += findnum(&buf[len], '{');
// 		rightnum += findnum(&buf[len], '}');
// 		if (ret>0)
// 		{ 
// 			len += ret;
// 		}
// 		else
// 		{
// 			ztime++;
// 			if (ztime > 2)
// 			{
// 				break;
// 			}
// 		}
// 		if (leftnum == rightnum)
// 		{
// 			break;
// 		}
// 	}
	len = recv(m_sockclient7700, buf, 40960, 0);

	if (len > 0)
	{
		cout << "recv<--" << buf << endl;
	}
	else
	{
		m_err = -1;
	}
	return string(buf);
}

void CJsonComm::SendJsonString8800(string jstr)
{
	if (m_sockclient8800 == 0)
	{
		m_sockclient8800 = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, &(m_psharememo->wasinfo8800), 0, WSA_FLAG_OVERLAPPED);
	}
	int ret = send(m_sockclient8800, (char*)jstr.c_str(), jstr.length(), 0);
	if (ret > 0)
	{
		cout << "send-->" << jstr.c_str() << endl;
	}
	else
	{
		m_err = -1;
	}
}
string CJsonComm::RecvJsonString8800()
{
	DWORD timeout = 5000;
	static char buf[40960] = "";
	//setsockopt(*m_psockclient, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	int ret = recv(m_sockclient8800, buf, 40960, 0);
	if (ret > 0)
	{
		cout << "recv<--" << buf << endl;
	}
	else
	{
		m_err = -1;
	}
	return string(buf);
}
void CJsonComm::ReFreshVehicleData()
{
   //SetRobotPos();
	//GetRobotPos();
	//SelectFixPath();
	//RunPath();
	//GetLaserData();
	//GetGlobalPath();
	//GetStatus();
	//GetMapList();
	//GetRecordMap();
	//Mapping();
	//Pause();
	//Reboot();
	//RecodeMap();
	//RecordPath();
	//RobotForwardRecode();
	//RobotPauseRecode();
	//RobotTurnLeftRecode();
	//RobotTurnRightRecode();
	//SavePath();
	//SetAmclMap();
	//SetNaviMap();
	//SetPathFileState();
	//SetRobotLaserFileState();
	//StartRobot();
	//StopRecodeMap();
	//StopRobot();

}

bool CJsonComm::SetRobotPos()
{
	//参数格式m_psharememo->cmdbuf    例子"1.0,1.0,1.1,1.1,"
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setRobotPos\",\"data\":{\"robot_x\":${0},\"robot_y\":${1},\"end_x\":${2},\"end_y\":${3}}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	jstr = jstr.replace(jstr.find("${1}"), 4, cgspar.GetAt(1));
	jstr = jstr.replace(jstr.find("${2}"), 4, cgspar.GetAt(2));
	jstr = jstr.replace(jstr.find("${3}"), 4, cgspar.GetAt(3));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret, value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

//bool CJsonComm::SetRobotPos(string sx1,string sy1,string sx2,string sy2)
//{
//	//参数格式m_psharememo->cmdbuf    例子"1.0,1.0,1.1,1.1,"
//	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setRobotPos\",\"data\":{\"robot_x\":${0},\"robot_y\":${1},\"end_x\":${2},\"end_y\":${3}}}}}";
//	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
//	jstr = jstr.replace(jstr.find("${0}"), 4, sx1);
//	jstr = jstr.replace(jstr.find("${1}"), 4, sy1);
//	jstr = jstr.replace(jstr.find("${2}"), 4, sx2);
//	jstr = jstr.replace(jstr.find("${3}"), 4, sy2);
//	SendJsonString(jstr);
//	string sret = RecvJsonString();
//	Json::Reader reader;
//	Json::Value value;
//	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
//	if (reader.parse(sret, value))
//	{
//		return value["state"].asBool();
//	}
//	else
//	{
//		return false;
//	}
//}

bool CJsonComm::GetRobotPos()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getRobotPos\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
	strcpy(m_psharememo->cmdbuf, sret.c_str());
	Json::Reader reader;
	Json::Value value;
	
	if (reader.parse(sret.c_str(), value))
	{
		if (!value["data"].isNull())
		{
			Json::Value  js_data = value["data"];
			if (!js_data["laser_dx"].isNull())
			{
				m_psharememo->vehicle_pos.last_dx  = js_data["laser_dx"].asDouble();
			}
			if (!js_data["th"].isNull())
			{
				m_psharememo->vehicle_pos.th = js_data["th"].asDouble();
			}
			if (!js_data["x"].isNull())
			{
				m_psharememo->vehicle_pos.x = js_data["x"].asDouble();
			}
			if (!js_data["y"].isNull())
			{
				m_psharememo->vehicle_pos.y = js_data["y"].asDouble();
			}
		}
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return true;
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}

bool CJsonComm::SelectFixPath()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"selectFixPath\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
	strcpy(m_psharememo->cmdbuf, sret.c_str());
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
		int i = 0;
		for (i = 0; i != json_data.size(); i++)
		{
			m_psharememo->vehicle_paths.paths[i][0] = 0;
			strcpy(&m_psharememo->vehicle_paths.paths[i][0], json_data[i]["path"].asString().c_str());
		}
		m_psharememo->vehicle_paths.path_num = i;
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}

bool CJsonComm::RunPath()
{
	//参数格式m_psharememo->cmdbuf    例子"fix,A to B,"
	//fix为运行方式   A to B为路径名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"runPath\",\"data\":{\"method\":\"${0}\",\"path_name\":\"${1}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	jstr = jstr.replace(jstr.find("${1}"), 4, cgspar.GetAt(1));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}
bool CJsonComm::GetLaserData()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getLaser\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
// 		for (int i = 0; i != json_data.size();i++)
// 		{
// 			m_psharememo->laserdatas[i].angle = json_data[i]["angle"].asDouble();
// 			m_psharememo->laserdatas[i].range = json_data[i]["range"].asDouble();
// 		}
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		Json::Value jvalue;
		jvalue["state"] = false;
		jvalue["data"] = Json::nullValue;
		string strret = jvalue.toStyledString();
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		memcpy(m_psharememo->cmdbuf, strret.c_str(), strret.length());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
	}


bool CJsonComm::GetGlobalPath()
{

	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getGlobalPath\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
		WORD &i = m_psharememo->map_pointsize;
		for (i = 0; i != json_data.size(); i++)
		{
			m_psharememo->map_points[i].dir = json_data[i]["dir"].asInt();
			m_psharememo->map_points[i].x = json_data[i]["x"].asInt();
			m_psharememo->map_points[i].y = json_data[i]["y"].asInt();
		}
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}

bool CJsonComm::GetStatus()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getStatus\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
		m_psharememo->run_status.run_status = json_data["status"].asInt();
		m_psharememo->run_status.errcode = json_data["errcode"].asInt();
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}

bool CJsonComm::GetMapList()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getMapList\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
		unsigned int i = 0;
		for (i = 0; i < json_data.size(); i++)
		{
			m_psharememo->vehicle_maps.maps[i][0] = 0;
			strcpy(&m_psharememo->vehicle_maps.maps[i][0], json_data[i]["map_name"].asString().c_str());
			cout <<"===="<< i << endl;
		}
		m_psharememo->vehicle_maps.map_num = i;
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}

bool CJsonComm::GetRecordMap()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"getRecodeMaps\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		Json::Value json_data = value["data"];
		int i = 0;	
		for (i = 0; i != json_data.size(); i++)
		{
			m_psharememo->vehicle_record_maps.maps[i][0] = 0;
			strcpy(&m_psharememo->vehicle_record_maps.maps[i][0], json_data[i]["map_name"].asString().c_str());
		}
		m_psharememo->vehicle_record_maps.map_num = i;
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return true;
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
	return false;
}


bool CJsonComm::Mapping()
{
	//参数格式m_psharememo->cmdbuf    例子"mapname,"
	//一个参数 地图名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"mapping\",\"data\":{\"map_name\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::Pause()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"pause\",\"data\":{\"status\":\"pause\"}}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::Continue()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"pause\",\"data\":{\"status\":\"continue\"}}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}
bool CJsonComm::Reboot()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"reboot\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::RecodeMap()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"recodeMap\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::RecordPath()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"recodePath\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::RobotForwardRecode()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"robotForwardRecode\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::RobotPauseRecode()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"robotPauseRecode\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}


bool CJsonComm::RobotTurnLeftRecode()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"robotTurnLeftRecode\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}


bool CJsonComm::RobotTurnRightRecode()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"robotTurnRightRecode\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::RobotBackwardRecode()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"robotBackwardRecode\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}



bool CJsonComm::SavePath()
{
	//参数格式m_psharememo->cmdbuf    例子"A to B,"
	//A to B为保存的路径名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"savePath\",\"data\":{\"path_name\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}
bool CJsonComm::SetAmclMap()
{
	//参数格式m_psharememo->cmdbuf    例子"mapname,"
	//mapname 为地图名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setAmclMap\",\"data\":{\"map_name\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}
bool CJsonComm::SetNaviMap()
{
	//参数格式m_psharememo->cmdbuf    例子"mapname,"
	//mapname 为地图名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setNaviMap\",\"data\":{\"map_name\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::SetPathFileState()
{
	//参数格式m_psharememo->cmdbuf    例子"0,"
	//0 为路径状态
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setPathFileState\",\"data\":{\"state\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}
bool CJsonComm::SetRobotLaserFileState()
{
	//参数格式m_psharememo->cmdbuf    例子"0,"
	//0 为激光文件状态状态
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"setRobotLaserFileState\",\"data\":{\"state\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}


bool CJsonComm::StartRobot()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"startRobot\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::StopRecodeMap()
{
	//参数格式m_psharememo->cmdbuf    例子"map_name,"
	//map_name 为记录地图名称
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"stopRecodeMap\",\"data\":{\"map_name\":\"${0}\"}}}}";
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	jstr = jstr.replace(jstr.find("${0}"), 4, cgspar.GetAt(0));
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

bool CJsonComm::StopRobot()
{
	string jstr = "{\"Action\":{\"CallBackFunction\":{\"name\":\"stopRobot\"}}}";
	SendJsonString7700(jstr);
	string sret = RecvJsonString7700();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		strcpy(m_psharememo->cmdbuf, sret.c_str());
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return value["state"].asBool();
	}
	else
	{
		m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
		return false;
	}
}

void CJsonComm::ReadSoc()
{
	string jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"EE 03 06 00 00 00 03 88\",\"len\":8}}";
	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		memset(m_psharememo->cmdbuf, 0, MAX_CMDBUF_SIZE);
		string strhex = value["ActionDG"]["dataDG"].asString();
		CGroup<string> arrayhex = MYTOOLS::CalString((char*)strhex.c_str(), " ");
		if (arrayhex.GetSize() >= 8)
		{
			char rbuf[20];
			sprintf_s(rbuf, "%d%d.%d",MYTOOLS::stringtoint(arrayhex.GetAt(5)), MYTOOLS::stringtoint(arrayhex.GetAt(4)), MYTOOLS::stringtoint(arrayhex.GetAt(3)));
			Json::Value jvalue;
			jvalue["status"] = true;
			jvalue["data"] = rbuf;
			memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());		
		}
	}
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;

}
void CJsonComm::SetVolteF()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	double fvolot = MYTOOLS::stringtodouble(m_psharememo->cmdbuf);
	int x10 = int(fvolot / 10);
	int x1 = (int)fvolot % 10;
	int d1 = (int)(fvolot * 10) % 10;
	char buf[500];
	sprintf_s(buf, "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"EE 03 05 %02d %02d %02d 03 88\",\"len\":8}}"
		, d1, x1, x10);
	string jstr = buf;
	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt()==1?true:false;
	}
	else
	{
		jvalue["status"] = false;
		
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::GetLockStatus()
{
	Json::Value jvalue;
	jvalue["status"] = false;
	string jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"AA 0E 02 00 00 00 0C 55\",\"len\":8}}";
	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		string strhex = value["ActionDG"]["dataDG"].asString();
		CGroup<string> arrayhex = MYTOOLS::CalString((char*)strhex.c_str(), " ");
		if (arrayhex.GetSize() >= 8)
		{
			long   lTemp = strtol(arrayhex.GetAt(5).c_str(), NULL, 16);
			//Json::Value jdata;
			//jdata["lock1"] = lTemp & 0x01;
			//jdata["lock2"] = lTemp & 0x02;
			//jdata["lock3"] = lTemp & 0x04;
			//jdata["lock4"] = lTemp & 0x08;
			//jdata["lock5"] = lTemp & 0x10;
			//jdata["lock6"] = lTemp & 0x20;
			jvalue["data"] = lTemp;
			jvalue["status"] = true;
		}
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::OneUnlock()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int locknm = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	if (locknm <= 6 && locknm >= 1)
	{
		char str[300] = "";
		sprintf_s(str, "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"AA 0E 01 00 00 %02X %02X 55\",\"len\":8}}",
			locknm, 15 - locknm);
		SendJsonString8800(str);
		string sret = RecvJsonString8800();
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(sret.c_str(), value))
		{
			jvalue["status"] = value["status"].asInt() == 1 ? true : false;
		}
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::LeftTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 05 05 77\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 00 05 72\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::RightTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 05 06 78\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 00 06 73\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::LeftRightTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 07 06 05 00 30 98\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 07 06 00 00 00 63\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::GreenTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 05 09 7B\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 00 09 76\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::YellowTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 05 0A 7C\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 00 0A 77\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::BlueTW()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	int onoff = MYTOOLS::stringtoint(m_psharememo->cmdbuf);
	string jstr = "";
	if (onoff)
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 05 0B 7D\",\"len\":8}}";
	}
	else
	{
		jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 17 00 00 00 0B 78\",\"len\":8}}";
	}

	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::OneRelayONOFF()
{
	CGroup<string> cgspar = MYTOOLS::CalString(m_psharememo->cmdbuf, ",");
	BYTE jdq = MYTOOLS::stringtoint(cgspar.GetAt(0));
	BYTE onoff = MYTOOLS::stringtoint(cgspar.GetAt(1));
	BYTE buf[8] = { 0x55, 0x01, 0x11, 0x00, 0x00, 0x00, 0x01, 0x69 };
	buf[2] = onoff + 0x11;
	buf[6] = jdq;
	buf[7] = 0;
	for (int i = 0; i != 7;i++)
	{
		buf[7] += buf[i];
	}
	char str[300] = "";
	sprintf_s(str, "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"%02X %02X %02X %02X %02X %02X %02X %02X\",\"len\":8}}",
		buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);

	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	SendJsonString8800(str);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::AllRelayON()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	string jstr = "{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 15 00 00 FF FF 69\",\"len\":8}}";
	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		int ii = value["status"].asInt();
		jvalue["status"] = (value["status"].asInt() == 1 ? true : false);
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}
void CJsonComm::ALLRelayOFF()
{
	Json::Value jvalue;
	jvalue["data"] = Json::nullValue;
	jvalue["status"] = false;
	string jstr ="{\"ActionDG\":{\"name\":\"setChassisUp\",\"port\":\"1\",\"data\":\"55 01 14 00 00 FF FF 68\",\"len\":8}}";
	SendJsonString8800(jstr);
	string sret = RecvJsonString8800();
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(sret.c_str(), value))
	{
		jvalue["status"] = value["status"].asInt() == 1 ? true : false;
	}
	memcpy(m_psharememo->cmdbuf, jvalue.toStyledString().c_str(), jvalue.toStyledString().length());
	m_psharememo->cmdflag = TYPE_VEHICLE_INFO::E_INVALID;
}