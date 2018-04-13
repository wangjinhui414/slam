#ifndef  _MY_DATABASE_H_
#define  _MY_DATABASE_H_

#pragma once
#include "stdafx.h"
#include "mytypedef.h"
using namespace std;

/**************************************************数据库表结构****************************************************/
//用户表
typedef struct TAB_USER
{
	//DWORD uid;
	string name;
	string pwd;
	DWORD role;
	DWORD del;
	TAB_USER()
	{
		memset(this, 0, sizeof(TAB_USER));
	}
}TAB_USER, *pTAB_USER;
//小车表
typedef struct TAB_VEHICLE
{
	string name;
	string pwd;
	int state;
	int startnode;
	int endnode;
	TAB_VEHICLE()
	{
		memset(this, 0, sizeof(TAB_VEHICLE));
	}

}TAB_VEHICLE, *pTAB_VEHICLE;
//站点表
typedef struct TAB_NODE
{
	DWORD id;
	string name;
	DWORD type;
	int x;
	int y;
	int f;
	CGroup<int> AdjNodeos;
	CGroup<int> AdjDis;
	TAB_NODE()
	{
		memset(this, 0, sizeof(TAB_NODE));
	}

}TAB_TAB_NODE, *pTAB_NODE;

/**************************************************Start数据库操作类****************************************************/

class CMyDatabase
{
public:
	CMyDatabase(void);
	~CMyDatabase(void);

	static BOOL ComInit(void){ if (S_OK == ::CoInitialize(NULL)) return TRUE; else return FALSE; };//初始化COM组件
	static void ComUninit(void){ ::CoUninitialize(); };//卸载COM组件
public:
	BOOL ConnectDatabase(char* server, char*database, char* uid, char* pwd);
	CGroup<TAB_USER> QueryRecordeUser(void);
	CGroup<TAB_USER> QueryRecordeUserWithKey(const char* value);
	CGroup<TAB_VEHICLE> QueryRecordeVehicle();
	CGroup<TAB_VEHICLE> QueryRecordeVehicleWithKey(const char* value);
	CGroup<TAB_NODE> QueryRecordeNode();
private:
	_ConnectionPtr  m_pConnection;
	_CommandPtr     m_pCommand;
	_RecordsetPtr   m_pRecordset;
};
/************************************************End数据库操作类************************************************************/




/***********************************************Start弗洛伊德算法类************************************************************/
#define INFF  10000000//无穷大设置
class CFloyd
{
public:
	CFloyd(){ m_distmap.clear(); m_path.clear(); };
	~CFloyd(){ vector<vector<int>>().swap(m_distmap); vector<vector<int>>().swap(m_path); };

	virtual void LoadDatabaseRecord(CGroup<TAB_NODE> myrecorde);//载入定点记录集
	vector<int> FindShortestPaht(int istart,int iend);//查找最短路径
	void PrintFloyd(void);//调试用
protected:
	void Floyd(vector<vector<int> > &distmap, vector<vector<int> > &path);//弗洛伊德算法 
private:
	vector<vector<int>> m_distmap;
	vector<vector<int>> m_path;
};


/***********************************************End弗洛伊德算法类**************************************************************/



#endif