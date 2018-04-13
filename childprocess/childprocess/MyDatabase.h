#ifndef  _MY_DATABASE_H_
#define  _MY_DATABASE_H_

#pragma once
#include "stdafx.h"
#include "mytypedef.h"
using namespace std;

/**************************************************���ݿ��ṹ****************************************************/
//�û���
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
//С����
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
//վ���
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

/**************************************************Start���ݿ������****************************************************/

class CMyDatabase
{
public:
	CMyDatabase(void);
	~CMyDatabase(void);

	static BOOL ComInit(void){ if (S_OK == ::CoInitialize(NULL)) return TRUE; else return FALSE; };//��ʼ��COM���
	static void ComUninit(void){ ::CoUninitialize(); };//ж��COM���
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
/************************************************End���ݿ������************************************************************/




/***********************************************Start���������㷨��************************************************************/
#define INFF  10000000//���������
class CFloyd
{
public:
	CFloyd(){ m_distmap.clear(); m_path.clear(); };
	~CFloyd(){ vector<vector<int>>().swap(m_distmap); vector<vector<int>>().swap(m_path); };

	virtual void LoadDatabaseRecord(CGroup<TAB_NODE> myrecorde);//���붨���¼��
	vector<int> FindShortestPaht(int istart,int iend);//�������·��
	void PrintFloyd(void);//������
protected:
	void Floyd(vector<vector<int> > &distmap, vector<vector<int> > &path);//���������㷨 
private:
	vector<vector<int>> m_distmap;
	vector<vector<int>> m_path;
};


/***********************************************End���������㷨��**************************************************************/



#endif