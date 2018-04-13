#include "stdafx.h"
#include "ShareMemory.h"
CShareMemory::CShareMemory(char *name,int size)
{
	Create(name, size);
	m_name = name;
	m_icmode = true;

}
CShareMemory::CShareMemory(char *name)
{
	m_pHandle = OpenFileMappingA(FILE_MAP_WRITE | FILE_MAP_READ, FALSE, name);
	if (m_pHandle == NULL)
	{
		//错误处理
		const char *msg = "OpenFileMapping() failed with error ";
		cout << msg << endl;
	}
	m_pmem = MapViewOfFile(m_pHandle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);

	if (m_pmem == NULL)
	{
		//错误处理
		const char *msg = "MapViewOfFile() failed with error ";
		cout << msg << endl;
	}
	m_name = name;
	m_icmode = false;

}
CShareMemory::~CShareMemory()
{
	::UnmapViewOfFile(m_pmem);
	::CloseHandle(m_pHandle);

}
void CShareMemory::Create(char* name, int size)
{
	m_pHandle = CreateFileMappingA((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, size, name);
	long bFileMappingAlreadyExist = GetLastError();
	bool bFileMappingAlreadyExists = (GetLastError() == ERROR_ALREADY_EXISTS);
	if (m_pHandle == NULL)
	{
		//错误处理
		const char  *msg = "CreateFileMapping() failed with error";
		cout << msg << endl;
	}
	m_pmem = MapViewOfFile(m_pHandle, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
	if (m_pmem == NULL)
	{
		//错误处理
		const char  *msg = "MapViewOfFile() failed with error";
		cout << msg << endl;
	}
}