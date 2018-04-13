#include "stdafx.h"
#include "mytypedef.h"
#include<vector>


void MYTOOLS::CalStringToArray(char* str, char*restr, CGroup<int> &varry)
{
	char *cbuf = new char[strlen(str) + 1];
	char *pde = cbuf;
	strcpy_s(cbuf, strlen(str) + 1, str);
	char *ptmp;
	while ((ptmp = strstr(cbuf, restr)) != NULL)
	{
		*ptmp = 0;
		varry.push_back(atoi(cbuf));
		cbuf = ptmp+1;
	}
	if (strlen(cbuf) > 0)
	{
		varry.push_back(atoi(cbuf));
	}
	delete[]pde;
}

CGroup<string>  MYTOOLS::CalString(char* str, const char* ch)
{
	CGroup<string> cgret;
	char *cbuf = new char[strlen(str) + 1];
	char *pde = cbuf;
	strcpy_s(cbuf, strlen(str) + 1, str);
	char *ptmp;
	while ((ptmp = strstr(cbuf, ch)) != NULL)
	{
		*ptmp = 0;
		cgret.push_back(cbuf);
		cbuf = ptmp + 1;
	}
	if (strlen(cbuf) > 0)
	{
		cgret.push_back(cbuf);
	}
	delete[]pde;
	return cgret;
}



void MYTOOLS::StartTimeCount(DWORD &timer)
{
	timer = ::GetTickCount();
}
DWORD MYTOOLS::EndTimeCount(DWORD timer)
{
	return ::GetTickCount() - timer;
}
string  MYTOOLS::inttostring(int iin)
{
	char ch[50] = "";
	_itoa_s(iin, ch, 10);
	return string(ch);
}
int  MYTOOLS::stringtoint(string str)
{
	return atoi(str.c_str());
}
double  MYTOOLS::stringtodouble(string str)
{
	return atof(str.c_str());
}
