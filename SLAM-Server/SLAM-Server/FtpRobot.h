#pragma once
#include<afxinet.h>

class CFtpClient
{
public:
	CFtpClient();
	~CFtpClient();
public:
	CInternetSession *pInternetSession;
	CFtpConnection *pFtpConnection;
	// FTP��������ַ    
	CString m_strServerAddr;
	// ��¼�û���    
	CString m_strUserName;
	// ��¼����    
	CString m_strPassWord;

public:
	BOOL ConnectToServer();
	void Upload(CString strpath);
	void Download(CString strpath);
	void CloseConnection();
};

