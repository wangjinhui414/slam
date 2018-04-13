#include "stdafx.h"
#include "FtpRobot.h"


CFtpClient::CFtpClient()
{

}


CFtpClient::~CFtpClient()
{
	CloseConnection();
}


// ���ӵ�ָ��FTP������    
BOOL CFtpClient::ConnectToServer()
{
	try
	{
		//CloseConnection();
		pInternetSession = new CInternetSession(AfxGetAppName());
		m_strServerAddr = "192.168.33.99";
		m_strUserName = "root";
		m_strPassWord.Empty();
		pFtpConnection = (CFtpConnection*)pInternetSession->GetFtpConnection(m_strServerAddr, m_strUserName, m_strPassWord, FALSE);

		if (NULL != pFtpConnection)
			return TRUE;
	}
	catch (CInternetException *e)
	{
		e->Delete();
	}
	return FALSE;
}


void CFtpClient::Upload(CString strpath)
{
	CString str1,str2;
	str1 = "./" + strpath;
	str2 = "recoder/" + strpath;
	if (pFtpConnection)    //���ӳɹ�
	{
		if (pFtpConnection->PutFile(str1, str2, false))
		{
			AfxMessageBox("�ļ��ϴ����\n");
			//printf("�ļ��ϴ����\n");
		}
		else
		{
			AfxMessageBox("�ļ��ϴ�ʧ�ܣ�\n");
			//printf("�ļ��ϴ�ʧ��\n");
		}
	}
}

void CFtpClient::Download(CString strpath)
{
	CString str1, str2;
	str1 = "./" + strpath;
	str2 = "recoder/" + strpath;
	if (pFtpConnection)    //���ӳɹ�
	{
		if (pFtpConnection->GetFile(str2, str1, false))
		{
			printf("�ļ��������\n");

		}
		else
		{
			printf("�ļ�����ʧ�ܣ�\n");
		}
	}
}

// �ر�����    
void CFtpClient::CloseConnection()
{
	if (NULL != pFtpConnection)
	{
		pFtpConnection->Close();
		delete pFtpConnection;
		pFtpConnection = NULL;
	}
	if (NULL != pInternetSession)
	{
		delete pInternetSession;
		pInternetSession = NULL;
	}
}
