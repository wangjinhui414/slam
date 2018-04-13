#include "StdAfx.h"
#include "MyDatabase.h"


CMyDatabase::CMyDatabase(void)
{
	
}


CMyDatabase::~CMyDatabase(void)
{
}

BOOL CMyDatabase::ConnectDatabase(char* server, char*database, char* uid, char* pwd)
{
	char szConnectStr[1024];
	sprintf_s(szConnectStr, "driver={SQL Server}; Server=%s;Database=%s;UID=%s;PWD=%s", server, database, uid, pwd);
	m_pConnection.CreateInstance(__uuidof(Connection));
	HRESULT ret = m_pConnection->Open(szConnectStr, "", "", adModeUnknown);
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
		string strSql = "select *  from  Users;";
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
			var = m_pRecordset->GetCollect("Name");
			if (var.vt != VT_NULL)
				tmpuser.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Password");
			if (var.vt != VT_NULL)
				tmpuser.pwd = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Role");
			if (var.vt != VT_NULL)
				tmpuser.role = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Del");
			if (var.vt != VT_NULL)
				tmpuser.del = var.lVal;
			var.Clear();
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
		string strSql = "SELECT * FROM Users WHERE Name ='" + string(value) + "';";
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
			var = m_pRecordset->GetCollect("Name");
			if (var.vt != VT_NULL)
				tmpuser.name = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Password");
			if (var.vt != VT_NULL)
				tmpuser.pwd = (char*)(_bstr_t)var;
			var.Clear();
			var = m_pRecordset->GetCollect("Role");
			if (var.vt != VT_NULL)
				tmpuser.role = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Del");
			if (var.vt != VT_NULL)
				tmpuser.del = var.lVal;
			var.Clear();
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

			var = m_pRecordset->GetCollect("Status");
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
			var = m_pRecordset->GetCollect("Status");
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
			var = m_pRecordset->GetCollect("Name");
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
			var = m_pRecordset->GetCollect("Type");
			if (var.vt != VT_NULL)
				tmpnodes.type = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("Type");
			if (var.vt != VT_NULL)
				tmpnodes.type = var.lVal;
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentNode");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var,",", tmpnodes.AdjNodeos);
			}
			var.Clear();
			var = m_pRecordset->GetCollect("AdjacentDis");
			if (var.vt != VT_NULL)
			{
				MYTOOLS::CalStringToArray((char*)(_bstr_t)var,",", tmpnodes.AdjDis);
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
					path[i][j] = k;//记录路径
				}
}

void CFloyd::PrintFloyd(void)
{
	cout << "*************************CFloyd m_distmap***********************************" << endl;
	for (vector < vector<int>>::iterator it = m_distmap.begin(); it != m_distmap.end(); it++)
	{
		for (vector<int>::iterator iy = it->begin(); iy != it->end(); iy++)
		{
			cout << *iy << '\t';
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
	vret.push_back(iend);
	int indx1 = iend;
	int lastindex = -1;
	while (1)
	{
		if (lastindex == m_path[istart][indx1])
		{
			vret.insert(vret.begin(), m_path[istart][indx1]);
			break;
		}
		else
		{
			vret.insert(vret.begin(), m_path[istart][indx1]);
			indx1 = m_path[istart][indx1];
		}
		lastindex = m_path[istart][indx1];
	}
	vret.insert(vret.begin(), istart);
	return vret;
}