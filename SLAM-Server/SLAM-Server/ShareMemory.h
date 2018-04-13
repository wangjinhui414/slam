#ifndef _SHARE_MEMORY_H_
#define _SHARE_MEMORY_H_
#include <iostream>
using namespace std;

class CShareMemory
{
public:
	CShareMemory(char *name,int size);
	CShareMemory(char*name);
	~CShareMemory();
public:
	void Create(char* name, int size);

	HANDLE m_pHandle;
	LPVOID m_pmem;
	bool m_icmode;
	string m_name;
};




#endif