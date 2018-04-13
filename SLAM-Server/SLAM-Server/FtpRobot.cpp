#include "stdafx.h"
#include "FtpRobot.h"


CFtpClient::CFtpClient()
{

}


CFtpClient::~CFtpClient()
{
	CloseConnection();
}


// 连接到指定FTP服务器    
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
	if (pFtpConnection)    //连接成功
	{
		if (pFtpConnection->PutFile(str1, str2, false))
		{
			AfxMessageBox("文件上传完成\n");
			//printf("文件上传完成\n");
		}
		else
		{
			AfxMessageBox("文件上传失败！\n");
			//printf("文件上传失败\n");
		}
	}
}

void CFtpClient::Download(CString strpath)
{
	CString str1, str2;
	str1 = "./" + strpath;
	str2 = "recoder/" + strpath;
	if (pFtpConnection)    //连接成功
	{
		if (pFtpConnection->GetFile(str2, str1, false))
		{
			printf("文件下载完成\n");

		}
		else
		{
			printf("文件下载失败！\n");
		}
	}
}

// 关闭连接    
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
