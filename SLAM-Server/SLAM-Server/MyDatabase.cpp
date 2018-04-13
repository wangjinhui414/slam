#include "StdAfx.h"
#include "MyDatabase.h"
#include <fstream>

CMyDatabase::CMyDatabase(void)
{
	
}


CMyDatabase::~CMyDatabase(void)
{
}

BOOL CMyDatabase::ConnectDatabase(char* server, char*database, char* uid, char* pwd)
{
	char szConnectStr[1024];
	//sprintf_s(szConnectStr, "driver={SQL Server}; Server=%s;Database=%s;UID=%s;PWD=%s", server, database, uid, pwd);
	//sprintf_s(szConnectStr, "driver={MySQL ODBC 5.7 Driver}; Server=%s;Database=%s;UID=%s;PWD=%s", server, database, uid, pwd);
	sprintf_s(szConnectStr, "DSN=MySQL;server=%s;database=%s;", server, database);
	m_pConnection.CreateInstance(__uuidof(Connection));
	HRESULT ret = m_pConnection->Open(szConnectStr, uid, pwd, adModeUnknown);
	if (ret == S_OK)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CGroup<TAB_USER> CMyDatabase::QueryRecordeUser(void)
{
	CGroup<TAB_USER> cgret;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "select *  from  staff_user;";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			TAB_USER tmpuser;
			var = m_pRecordset->GetCollect("USER_NAME");
			if (var.vt != VT_NULL)
				tmpuser.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("USER_PASS");
			if (var.vt != VT_NULL)
				tmpuser.pwd = (char*)(_bstr_t)var;
			var.Clear();
// 			var = m_pRecordset->GetCollect("Role");
// 			if (var.vt != VT_NULL)
// 				tmpuser.role = var.lVal;
// 			var.Clear();
// 			var = m_pRecordset->GetCollect("Del");
// 			if (var.vt != VT_NULL)
// 				tmpuser.del = var.lVal;
// 			var.Clear();
			cgret.push(tmpuser);
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}

CGroup<TAB_USER> CMyDatabase::QueryRecordeUserWithKey(const char *value)
{
	CGroup<TAB_USER> cgret;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "SELECT * FROM staff_user WHERE USER_NAME ='" + string(value) + "';";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			TAB_USER tmpuser;
			var = m_pRecordset->GetCollect("USER_NAME");
			if (var.vt != VT_NULL)
				tmpuser.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("USER_PASS");
			if (var.vt != VT_NULL)
				tmpuser.pwd = (char*)(_bstr_t)var;
			var.Clear();
// 			var = m_pRecordset->GetCollect("Role");
// 			if (var.vt != VT_NULL)
// 				tmpuser.role = var.lVal;
// 			var.Clear();
// 			var = m_pRecordset->GetCollect("Del");
// 			if (var.vt != VT_NULL)
// 				tmpuser.del = var.lVal;
// 			var.Clear();
			cgret.push(tmpuser);
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}


CGroup<TAB_VEHICLE> CMyDatabase::QueryRecordeVehicle()
{
	CGroup<TAB_VEHICLE> cgret;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "select *  from  Vehicle;";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			TAB_VEHICLE tmpvehicle;
			//var = m_pRecordset->GetCollect("ID");
			//if (var.vt != VT_NULL)
			//	tmpvehicle.id = var.lVal;
			//var.Clear();
			var = m_pRecordset->GetCollect("Name");
			if (var.vt != VT_NULL)
				tmpvehicle.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Password");
			if (var.vt != VT_NULL)
				tmpvehicle.pwd = (char*)(_bstr_t)var;
			var.Clear();
			//var = m_pRecordset->GetCollect("Port");
			//if (var.vt != VT_NULL)
			//	tmpvehicle.port = var.lVal;
			//var.Clear();
			var = m_pRecordset->GetCollect("State");
			if (var.vt != VT_NULL)
				tmpvehicle.state = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("StartNode");
			if (var.vt != VT_NULL)
				tmpvehicle.startnode = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("EndNode");
			if (var.vt != VT_NULL)
				tmpvehicle.endnode = var.lVal;
			var.Clear();
			cgret.push(tmpvehicle);
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}
CGroup<TAB_VEHICLE> CMyDatabase::QueryRecordeVehicleWithKey(const char* value)
{
	CGroup<TAB_VEHICLE> cgret;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "SELECT * FROM Vehicle WHERE Name ='" + string(value) + "';";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			TAB_VEHICLE tmpvehicle;
			//var = m_pRecordset->GetCollect("ID");
			//if (var.vt != VT_NULL)
			//	tmpvehicle.id = var.lVal;
			//var.Clear();
			var = m_pRecordset->GetCollect("Name");
			if (var.vt != VT_NULL)
				tmpvehicle.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Password");
			if (var.vt != VT_NULL)
				tmpvehicle.pwd = (char*)(_bstr_t)var;
			var.Clear();
			//var = m_pRecordset->GetCollect("Port");
			//if (var.vt != VT_NULL)
			//	tmpvehicle.port = var.lVal;
			//var.Clear();
			var = m_pRecordset->GetCollect("State");
			if (var.vt != VT_NULL)
				tmpvehicle.state = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("StartNode");
			if (var.vt != VT_NULL)
				tmpvehicle.startnode = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("EndNode");
			if (var.vt != VT_NULL)
				tmpvehicle.endnode = var.lVal;
			var.Clear();
			cgret.push(tmpvehicle);
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}


CGroup<TAB_NODE> CMyDatabase::QueryRecordeNode()
{
	CGroup<TAB_NODE> cgret;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "select *  from  Nodes;";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			TAB_NODE tmpnodes;
			var = m_pRecordset->GetCollect("ID");
			if (var.vt != VT_NULL)
				tmpnodes.id = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("NAME");
			if (var.vt != VT_NULL)
				tmpnodes.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("X");
			if (var.vt != VT_NULL)
				tmpnodes.x = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Y");
			if (var.vt != VT_NULL)
				tmpnodes.y = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("F");
			if (var.vt != VT_NULL)
				tmpnodes.f = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("TYPE");
			if (var.vt != VT_NULL)
				tmpnodes.type = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentNode");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var, tmpnodes.AdjNodeos);
			}
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentDis");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var, tmpnodes.AdjDis);
			}
			var.Clear();
			cgret.push(tmpnodes);
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}

TAB_NODE CMyDatabase::QueryRecordeNodeWithKey(DWORD id)
{
	TAB_NODE cgret;
	cgret.id = 0xFFFFFFFF;
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		string strSql = "select *  from  Nodes WHERE ID ='" + MYTOOLS::inttostring(id) + "';";
		m_pRecordset->Open(strSql.c_str(),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		_variant_t var;
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			cout << "ERROR: The data in the table is empty" << endl;
			return cgret;
		}
		while (!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("ID");
			if (var.vt != VT_NULL)
				cgret.id = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Name");
			if (var.vt != VT_NULL)
				cgret.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("X");
			if (var.vt != VT_NULL)
				cgret.x = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Y");
			if (var.vt != VT_NULL)
				cgret.y = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("F");
			if (var.vt != VT_NULL)
				cgret.f = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Type");
			if (var.vt != VT_NULL)
				cgret.type = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Type");
			if (var.vt != VT_NULL)
				cgret.type = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentNode");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var, cgret.AdjNodeos);
			}
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentDis");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var, cgret.AdjDis);
			}
			var.Clear();
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
		m_pRecordset = NULL;
	}
	m_pRecordset->Close();
	return cgret;
}


string CMyDatabase::QueryRecordeUserJson()
{
	CGroup<TAB_USER> cguser = QueryRecordeUser();
	Json::Value jret;
	Json::Value jdata;
	for (int i = 0;i!=cguser.GetSize();i++)
	{
		Json::Value juser;
		juser["name"] = cguser[i].name;
		juser["pwd"] = cguser[i].pwd;
		juser["del"] = (int)cguser[i].del;
		juser["role"] = (int)cguser[i].role;
		jdata.append(juser);
	}
	jret["data"] = jdata;
	if (cguser.size() != 0)
	{
		jret["status"] = true;
	}
	else
	{
		jret["status"] = false;
	}
	return jret.toStyledString();
}
string CMyDatabase::QueryRecordeVehicleJson()
{
	CGroup<TAB_VEHICLE> cgvehicle = QueryRecordeVehicle();
	Json::Value jret;
	Json::Value jdata;
	for (int i = 0; i != cgvehicle.GetSize(); i++)
	{
		Json::Value juser;
		juser["name"] = cgvehicle[i].name;
		juser["pwd"] = cgvehicle[i].pwd;
		juser["startnode"] = (int)cgvehicle[i].startnode;
		juser["endnode"] = (int)cgvehicle[i].endnode;
		jdata.append(juser);
	}
	jret["data"] = jdata;
	if (cgvehicle.size() != 0)
	{
		jret["status"] = true;
	}
	else
	{
		jret["status"] = false;
	}
	return jret.toStyledString();
}
string CMyDatabase::QueryRecordeNodeJson()
{
	CGroup<TAB_NODE> cgnodes = QueryRecordeNode();
	Json::Value jret;
	Json::Value jdata;
	for (int i = 0; i != cgnodes.GetSize(); i++)
	{
		Json::Value jnode;
		jnode["id"] = (int)cgnodes[i].id;
		jnode["name"] = cgnodes[i].name;
		jnode["type"] = (int)cgnodes[i].type;
		jnode["f"] = cgnodes[i].f;
		jnode["x"] = cgnodes[i].x;
		jnode["y"] = cgnodes[i].y;
		jnode["adjnodes"] = Json::nullValue;
		jnode["adjdiss"] = Json::nullValue;
		for (int j = 0; j != cgnodes[i].AdjNodeos.size();j++)
		{
			Json::Value jadjnode;
			jadjnode["node"] = cgnodes[i].AdjNodeos[j];
			jnode["adjnodes"].append(jadjnode);
		}
		for (int k = 0; k != cgnodes[k].AdjDis.size(); k++)
		{
			Json::Value jadjdis;
			jadjdis["distances"] = cgnodes[i].AdjDis[k];
			jnode["adjdiss"].append(jadjdis);
		}
		jdata.append(jnode);
	}
	jret["data"] = jdata;
	if (cgnodes.size() != 0)
	{
		jret["status"] = true;
	}
	else
	{
		jret["status"] = false;
	}
	return jret.toStyledString();
}
bool CMyDatabase::UpdataRecordUserJson(string jsuser)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jsuser, value))
	{
		string uname = value["record"]["name"].asString();
		string pwd = value["record"]["pwd"].asString();
		int del = value["record"]["del"].asInt();
		int role = value["record"]["role"].asInt();
		CGroup<TAB_USER> cgret = QueryRecordeUserWithKey(uname.c_str());
		if (cgret.GetSize() == 1)
		{
			char ch[200] = "";
			sprintf_s(ch, "UPDATE Users SET Password='%s',Role='%d',Del='%d' WHERE Name='%s';", pwd.c_str(), role, del, uname.c_str());
			try
			{
				m_pConnection->Execute(ch, NULL, adCmdText);
				return true;
			}
			catch (_com_error *e)
			{
				cout<<e->Description()<<endl;
				return false;
			}
		}
		else
		{
			m_pRecordset.CreateInstance(__uuidof(Recordset));
			m_pRecordset->Open("SELECT * FROM Users",                // 查询s表中所有字段
				m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
				adOpenDynamic,
				adLockOptimistic,
				adCmdText);
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("Name", _variant_t(uname.c_str()));
			m_pRecordset->PutCollect("Password", _variant_t(pwd.c_str()));
			m_pRecordset->PutCollect("Role", _variant_t(role));
			m_pRecordset->PutCollect("Del", _variant_t(del));
			m_pRecordset->Update();
			return true;
		}
	}
	return false;
}
bool CMyDatabase::UpdataRecordVehicleJson(string jsvehicle)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jsvehicle, value))
	{
		string uname = value["record"]["name"].asString();
		string pwd = value["record"]["pwd"].asString();
		int startnode = value["record"]["startnode"].asInt();
		int endnode = value["record"]["endnode"].asInt();
		int state = value["record"]["state"].asInt();
		CGroup<TAB_VEHICLE> cgret = QueryRecordeVehicleWithKey(uname.c_str());
		if (cgret.GetSize() == 1)
		{
			char ch[200] = "";
			sprintf_s(ch, "UPDATE Vehicle SET Password='%s',Startnode='%d',Endnode='%d',State='%d' WHERE Name='%s';", 
				pwd.c_str(), startnode, endnode, state , uname.c_str());
			try
			{
				m_pConnection->Execute(ch, NULL, adCmdText);
				return true;
			}
			catch (_com_error *e)
			{
				cout << e->Description() << endl;
				return false;
			}
		}
		else
		{
			m_pRecordset.CreateInstance(__uuidof(Recordset));
			m_pRecordset->Open("SELECT * FROM Vehicle",                // 查询s表中所有字段
				m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
				adOpenDynamic,
				adLockOptimistic,
				adCmdText);
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("Name", _variant_t(uname.c_str()));
			m_pRecordset->PutCollect("Password", _variant_t(pwd.c_str()));
			m_pRecordset->PutCollect("Startnode", _variant_t(startnode));
			m_pRecordset->PutCollect("Endnode", _variant_t(endnode));
			m_pRecordset->PutCollect("State", _variant_t(state));
			m_pRecordset->Update();
			return true;
		}
	}
	return false;
}
bool CMyDatabase::UpdataRecordNodeJson(string jsnode)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jsnode, value))
	{
		int id = value["record"]["id"].asInt();
		string name = value["record"]["name"].asString();
		int x = value["record"]["x"].asInt();
		int y = value["record"]["y"].asInt();
		int f = value["record"]["f"].asInt();
		int type = value["record"]["type"].asInt();
		string snodes = "";
		string sdiss = "";
		for (int i = 0; i != value["record"]["adjnodes"].size();i++)
		{
			char ch[50] = "";
			int tttm = value["record"]["adjnodes"][i]["node"].asInt();
			itoa(tttm, ch, 10);
			snodes += ch;
			if (i != value["record"]["adjnodes"].size() - 1)
				snodes += ",";
		}
		for (int i = 0; i != value["record"]["adjdiss"].size(); i++)
		{
			char ch[50] = "";
			int tttm = value["record"]["adjdiss"][i]["distances"].asInt();
			itoa(tttm, ch, 10);
			sdiss += ch;
			if (i != value["record"]["adjdiss"].size() - 1)
				sdiss += ",";
		}
		TAB_NODE  cgret = QueryRecordeNodeWithKey(id);
		if (cgret.id!=0xFFFFFFFF)
		{
			char ch[300] = "";
			sprintf_s(ch, "UPDATE Nodes SET Name='%s',X='%d',Y='%d',F='%d',Type='%d',AdjacentNode='%s',AdjacentDis='%s' WHERE ID='%d';", 
				name.c_str(), x, y, f, type, snodes.c_str(), sdiss.c_str(), id);
			try
			{
				m_pConnection->Execute(ch, NULL, adCmdText);
				return true;
			}
			catch (_com_error *e)
			{
				cout << e->Description() << endl;
				return false;
			}
		}
		else
		{
			m_pRecordset.CreateInstance(__uuidof(Recordset));
			m_pRecordset->Open("SELECT * FROM Nodes",                // 查询s表中所有字段
				m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
				adOpenDynamic,
				adLockOptimistic,
				adCmdText);
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("ID", _variant_t(id));
			m_pRecordset->PutCollect("Name", _variant_t(name.c_str()));
			m_pRecordset->PutCollect("X", _variant_t(x));
			m_pRecordset->PutCollect("Y", _variant_t(y));
			m_pRecordset->PutCollect("F", _variant_t(f));
			m_pRecordset->PutCollect("Type", _variant_t(type));
			m_pRecordset->PutCollect("AdjacentNode", _variant_t(snodes.c_str()));
			m_pRecordset->PutCollect("AdjacentDis", _variant_t(sdiss.c_str()));
			m_pRecordset->Update();
			return true;
		}
	}
	return false;
}

bool CMyDatabase::DeleteRecordUserJson(string jstr)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jstr, value))
	{
		string name = value["record"]["name"].asString();
		string strsql = "DELETE FROM Users WHERE Name='";
		strsql += name;
		strsql += "';";
		m_pConnection->Execute(strsql.c_str(), NULL, adCmdText);
		return true;
	}
	return false;
}
bool CMyDatabase::DeleteRecordVehicleJson(string jstr)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jstr, value))
	{
		string name = value["record"]["name"].asString();
		string strsql = "DELETE FROM Vehicle WHERE Name='";
		strsql += name;
		strsql += "';";
		m_pConnection->Execute(strsql.c_str(), NULL, adCmdText);
		return true;
	}
	return false;
}
bool CMyDatabase::DeleteRecordNodeJson(string jstr)
{
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(jstr, value))
	{
		int id = value["record"]["id"].asInt();
		string strsql = "DELETE FROM Nodes WHERE ID='";
		strsql += MYTOOLS::inttostring(id);
		strsql += "';";
		m_pConnection->Execute(strsql.c_str(), NULL, adCmdText);
		return true;
	}
	return false;
}



















/************************************************************************/
/* 路径生成和上传 函数 暂时放database里面                               */
/************************************************************************/
#include "math.h"
#include "ftplib.h"
#pragma comment(lib,"./ftplib.lib") 
#define LENGHT_STEP      1//最小坐标距离间隔  
#define LENGTH_ADD       25//加速距离  一个像素点5厘米
#define LENGTH_DEC       25//减速距离
#define MIN_SPEED        0.35//最小速度
#define MAX_SPEED        0.6//最大速度
void CMyDatabase::OutPutAllPath()
{
	CGroup<TAB_NODE> allnode = QueryRecordeNode();

	for (int i = 0; i != allnode.GetSize(); i++)
	{
		for (int j = 0; j != allnode[i].AdjNodeos.GetSize(); j++)
		{
			int xx = allnode[i].AdjNodeos[j];
			TAB_NODE objnode = QueryRecordeNodeWithKey(allnode[i].AdjNodeos[j]);
			if (objnode.id == 0xFFFFFFFF)	continue;
			double start_x = allnode[i].x;//起始站点X坐标
			double start_y = allnode[i].y;//起始站点Y坐标
			double end_x = objnode.x;//目标站点X坐标
			double end_y = objnode.y;//目标站点Y坐标
			double arg = atan((end_y - start_y) / (end_x - start_x));//求出斜线与X坐标的夹角
			double length = sqrt(pow((end_y - start_y), 2) + pow((end_x - start_x), 2));//求出2点距离
			vector<string> sout;
			double culen = 0;
			double cux = start_x;//当前要生成的坐标点x
			double cuy = start_y;//当前要生成的坐标点y
			double cuspeed = MIN_SPEED;//当前要生成的坐标点速度
			while (culen < length)
			{
				char buf[200] = "";
				string str = "";
				double out_x = (cux - 4096)*0.05;
				double out_y = -(cuy - 4096)*0.05;
				sprintf_s(buf, "%f	%f	%f	%f	%f	%f", out_x, out_y, 0.0, cuspeed, 0.0, 0.0);
				sout.push_back(string(buf));

				if (culen>(length-LENGTH_DEC))//到达减速距离
				{
					cuspeed -= (MAX_SPEED - MIN_SPEED) / LENGTH_ADD;
				}
				if (culen < LENGTH_ADD)//加速阶段
				{
					cuspeed += (MAX_SPEED - MIN_SPEED) / LENGTH_ADD;
				}
				culen += LENGHT_STEP;
				cux += LENGHT_STEP*cos(arg);
				cuy += LENGHT_STEP*sin(arg);
			}
			char buf[200] = "";
			double out_end_x = (out_end_x - 4096)*0.05;
			double out_end_y= -(out_end_y - 4096)*0.05;
			sprintf_s(buf, "%f	%f	%f	%f	%f	%f", out_end_x, out_end_y, 0.0, MIN_SPEED, 0.0, 0.0);
			sout.push_back(string(buf));
			char fname[50] = "";
			sprintf_s(fname, ".\\path\\%d-%d.txt", allnode[i].id, allnode[i].AdjNodeos[j]);
			ofstream outfile(fname);
			
			for (vector<string>::iterator it = sout.begin(); it != sout.end();it++)
			{
				cout << string(*it).c_str() << endl;
				outfile << string(*it).c_str() << endl;
			}
			outfile.close();
		}
	}
}

bool CMyDatabase::OutPutAppointPath(vector<int> path)
{
	if (path.size() <= 1)	return false;
	string sstart = MYTOOLS::inttostring(path[0]);
	string ssend = MYTOOLS::inttostring(path[path.size()-1]);
	string spathname = sstart + "-" + ssend;
	vector<string> sout;//输出路径容器
	for (int i = 0; i != path.size() - 1;i++)
	{
		TAB_NODE startnode = QueryRecordeNodeWithKey(path[i]);
		if (startnode.id == 0xFFFFFFFF)	return false;
		bool flag = false;
		//测试路径是否能到达
		for (int j = 0; j != startnode.AdjNodeos.GetSize(); j++)
		{
			if (startnode.AdjNodeos[j] == path[i + 1])
			{
				flag = true; break;
			}
		}
		if (flag == true)//路径通路写入路径文件
		{
			TAB_NODE nextnode = QueryRecordeNodeWithKey(path[i+1]);//经过路径的下一节点
			if (nextnode.id == 0xFFFFFFFF)	return false;
			if (i == 0)//起始路径
			{
				double start_x = startnode.x;//起始站点X坐标
				double start_y = startnode.y;//起始站点Y坐标
				double end_x = nextnode.x;//目标站点X坐标
				double end_y = nextnode.y;//目标站点Y坐标

				char buff[100] = "";
				//sprintf_s(buff, "%f	,%f===========%f,%f", start_x, start_y, end_x, end_y);
				//sout.push_back(string(buff));

				double arg = atan(abs(end_y - start_y) / abs(end_x - start_x));//求出斜线与X坐标的夹角
				double length = sqrt(pow((end_y - start_y), 2) + pow((end_x - start_x), 2));//求出2点距离
				double culen = 0;
				double cux = start_x;//当前要生成的坐标点x
				double cuy = start_y;//当前要生成的坐标点y
				double cuspeed = MIN_SPEED;//当前要生成的坐标点速度
				while (culen < length)
				{
					char buf[200] = "";
					string str = "";
					double out_end_x = (cux - 4096)*0.05;
					double out_end_y = -(cuy - 4096)*0.05;
					sprintf_s(buf, "%.4f %.4f %.4f %.4f %.4f %.4f", out_end_x, out_end_y, 0.0, cuspeed, 0.0, 0.0);
					sout.push_back(string(buf));
					if (culen < LENGTH_ADD)//加速阶段
					{
						cuspeed += (MAX_SPEED - MIN_SPEED) / LENGTH_ADD*LENGHT_STEP;
					}
					culen += LENGHT_STEP;
					cux = cux + LENGHT_STEP*cos(arg)*(end_x>start_x ? 1 : -1);
					cuy += LENGHT_STEP*sin(arg)*(end_y>start_y ? 1 : -1);
				}
			}
			else if (i == (path.size() - 2))//结束路径
			{
				double start_x = startnode.x;//起始站点X坐标
				double start_y = startnode.y;//起始站点Y坐标
				double end_x = nextnode.x;//目标站点X坐标
				double end_y = nextnode.y;//目标站点Y坐标
				char buff[100] = "";
				//sprintf_s(buff, "%f	,%f===========%f,%f", start_x, start_y, end_x, end_y);
				//sout.push_back(string(buff));
				double arg = atan(abs(end_y - start_y) / abs(end_x - start_x));//求出斜线与X坐标的夹角
				double length = sqrt(pow((end_y - start_y), 2) + pow((end_x - start_x), 2));//求出2点距离
				double culen = 0;
				double cux = start_x;//当前要生成的坐标点x
				double cuy = start_y;//当前要生成的坐标点y
				double cuspeed = MAX_SPEED;//当前要生成的坐标点速度
				while (culen < length)
				{
					if (culen > (length - LENGTH_DEC))//到达减速距离
					{
						cuspeed -= (MAX_SPEED - MIN_SPEED) / LENGTH_ADD*LENGHT_STEP;
					}
					char buf[200] = "";
					string str = "";
					double out_end_x = (cux - 4096)*0.05;
					double out_end_y = -(cuy - 4096)*0.05;
					sprintf_s(buf, "%.4f %.4f %.4f %.4f %.4f %.4f", out_end_x, out_end_y, 0.0, cuspeed, 0.0, 0.0);
					sout.push_back(string(buf));
					culen += LENGHT_STEP;
					cux += LENGHT_STEP*cos(arg)*(end_x > start_x ? 1 : -1);
					cuy += LENGHT_STEP*sin(arg)*(end_y>start_y ? 1 : -1);
				}
				char buf[200] = "";
				double ou_end_x = (end_x - 4096)*0.05;
				double ou_end_y = -(end_y - 4096)*0.05;
				sprintf_s(buf, "%.4f %.4f %.4f %.4f %.4f %.4f", ou_end_x, ou_end_y, 0.0, MIN_SPEED, 0.0, 0.0);
				sout.push_back(string(buf));
			}
			else//经过路径
			{
				double start_x = startnode.x;//起始站点X坐标
				double start_y = startnode.y;//起始站点Y坐标
				double end_x = nextnode.x;//目标站点X坐标
				double end_y = nextnode.y;//目标站点Y坐标
				char buff[100] = "";
				//sprintf_s(buff, "%f	,%f===========%f,%f", start_x, start_y, end_x, end_y);
				//sout.push_back(string(buff));
				double arg = atan(abs(end_y - start_y) / abs(end_x - start_x));//求出斜线与X坐标的夹角
				double length = sqrt(pow((end_y - start_y), 2) + pow((end_x - start_x), 2));//求出2点距离
				double culen = 0;
				double cux = start_x;//当前要生成的坐标点x
				double cuy = start_y;//当前要生成的坐标点y
				double cuspeed = MAX_SPEED;//当前要生成的坐标点速度
				while (culen < length)
				{
					char buf[200] = "";
					string str = "";
					double out_end_x = (cux - 4096)*0.05;
					double out_end_y = -(cuy - 4096)*0.05;
					sprintf_s(buf, "%.4f %.4f %.4f %.4f %.4f %.4f", out_end_x, out_end_y, 0.0, cuspeed, 0.0, 0.0);
					sout.push_back(string(buf));
					culen += LENGHT_STEP;
					cux += LENGHT_STEP*cos(arg)*(end_x > start_x ? 1 : -1);
					cuy += LENGHT_STEP*sin(arg)*(end_y>start_y ? 1 : -1);
				}
			}
		}
		else
		{
			return false;//路径无法到达
		}
	}
	//生成路径
	char fname[100] = "";
	sprintf_s(fname, ".\\path\\%s.txt", spathname.c_str());
	ofstream outfile(fname);
	for (vector<string>::iterator it = sout.begin(); it != sout.end(); it++)
	{
		cout << string(*it).c_str() << endl;
		outfile << string(*it).c_str() << endl;
	}
	outfile.close();
	return true;
}


void CMyDatabase::FtpAllPath(string ip)
{
#ifdef WIN32
	vector<string> sallpath;
	WIN32_FIND_DATAA finddata;
	HANDLE herror;
	LPCSTR filepathname = "./path/*.txt";
	herror = FindFirstFileA(filepathname,&finddata);
	if(herror == INVALID_HANDLE_VALUE)
	{
		return ;
	}
	while (::FindNextFileA(herror, &finddata))
	{
		string sfn = finddata.cFileName;
		if (sfn == "." || sfn == "..")
		{
			continue;
		}
		cout << finddata.cFileName << endl;
		sallpath.push_back(sfn);
	}

	ftplib ftpclient;
	if (!ftpclient.Connect(ip.c_str()))	return;
	if (!ftpclient.Login("root", ""))	return;
	for (vector<string>::iterator it = sallpath.begin(); it != sallpath.end();it++)
	{
		string loacpath = "./path/" + *it;
		string servpath = "./record-wjh/"+ *it;
		ftpclient.Put(loacpath.c_str(), servpath.c_str(), ftplib::ascii);
	}
	
	ftpclient.Quit();
#else


#endif

}
/***********************************************
暂时只正对192.168.33.99
************************************************/

char* TCHAR2char(TCHAR* tchStr)
{
	int iLen = 2 * wcslen(tchStr);//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
	char* chRtn = new char[iLen + 1];
	wcstombs(chRtn, tchStr, iLen + 1);//转换成功返回为非负值 
	return chRtn;
}
bool CMyDatabase::FtpAppointPath(string pathname ,string ip)
{
#ifdef WIN32
// 	vector<string> sallpath;
// 	WIN32_FIND_DATA finddata;
// 	HANDLE herror;
// 	TCHAR filepathname[] = _T("./path/*.txt");
// 	herror = FindFirstFile(filepathname, &finddata);
// 	if (herror == INVALID_HANDLE_VALUE)
// 	{
// 		return false;
// 	}
// 	while (::FindNextFile(herror, &finddata))
// 	{
// 		char* cfname = TCHAR2char(finddata.cFileName);
// 		string sfn = cfname;
// 		delete []cfname;
// 		if (sfn == "." || sfn == "..")
// 		{
// 			continue;
// 		}
// 		if (sfn == pathname)
// 		{
			ftplib ftpclient;
			if (!ftpclient.Connect(ip.c_str()))	return false;
			if (!ftpclient.Login("root", ""))	return false;
			string loacpath = "./path/" + pathname;
			string servpath = "./recoder/" + pathname;
			ftpclient.Put(loacpath.c_str(), servpath.c_str(), ftplib::ascii);
			ftpclient.Quit();
			return true;
// 		}
// 	}
// 	return false;
	
#else

#endif
}















void CFloyd::LoadDatabaseRecord(CGroup<TAB_NODE> myrecorde)
{
	m_distmap.assign(myrecorde.GetSize(), vector<int>(myrecorde.GetSize(), INFF));
	for (int i = 0; i != m_distmap.size(); i++)
	{
		m_distmap[i][i] = 0;
	}
	for (int i = 0; i != myrecorde.GetSize(); i++)
	{
		for (int j = 0; j != myrecorde.GetAt(i).AdjNodeos.GetSize(); j++)
		{
			int col = myrecorde.GetAt(i).AdjNodeos.GetAt(j);
			m_distmap[i][col] = myrecorde.GetAt(i).AdjDis.GetAt(j);
		}
	}
	Floyd(m_distmap, m_path);
	PrintFloyd();
}

void CFloyd::Floyd(vector<vector<int> > &distmap, vector<vector<int> > &path)//路径上到达该点的中转点
//福利：这个函数没有用除INF外的任何全局量，可以直接复制！
{
	const int &NODE = distmap.size();//用邻接矩阵的大小传递顶点个数，减少参数传递
	path.assign(NODE, vector<int>(NODE, -1));//初始化路径数组 
	for (vector < vector<int>>::iterator it = path.begin(); it != path.end(); it++)
	{
		int k = 0;
		for (vector<int>::iterator iy = it->begin(); iy != it->end(); iy++)
		{
			*iy = k++;
		}
	}
	for (int k = 1; k != NODE; ++k)//对于每一个中转点
		for (int i = 0; i != NODE; ++i)//枚举源点
			for (int j = 0; j != NODE; ++j)//枚举终点
				if (distmap[i][j] > distmap[i][k] + distmap[k][j])//不满足三角不等式
				{
					distmap[i][j] = distmap[i][k] + distmap[k][j];//更新
					path[i][j] = path[i][k];//记录路径
				}
}

void CFloyd::PrintFloyd(void)
{
	cout << "*************************CFloyd m_distmap***********************************" << endl;
	for (vector < vector<int>>::iterator it = m_distmap.begin(); it != m_distmap.end(); it++)
	{
		for (vector<int>::iterator iy = it->begin(); iy != it->end(); iy++)
		{
			if (*iy == INFF)
			{
				cout << "∞"<< '\t';
			}
			else
			{
				cout << *iy << '\t';
			}
		}
		cout << endl;
	}
	cout << "**************************CFloyd path**************************************" << endl;
	for (vector < vector<int>>::iterator it = m_path.begin(); it != m_path.end(); it++)
	{
		for (vector<int>::iterator iy = it->begin(); iy != it->end(); iy++)
		{
			cout << *iy << '\t';
		}
		cout << endl;
	}
}

vector<int> CFloyd::FindShortestPaht(int istart, int iend)
{
	vector<int> vret;
	vret.push_back(istart);
	int indx1 = istart;
	//int lastindex = -1;
	while (1)
	{
		int midv = m_path[indx1][iend];
		if (iend == midv)
		{
			//vret.insert(vret.begin(), midv);
			break;
		}
		else
		{
			vret.push_back(midv);
			indx1 = midv;
		}
		//lastindex = midv;
	}
	vret.push_back(iend);
	return vret;
}


