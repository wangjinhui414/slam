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
	// FTP服务器地址    
	CString m_strServerAddr;
	// 登录用户名    
	CString m_strUserName;
	// 登录密码    
	CString m_strPassWord;

public:
	BOOL ConnectToServer();
	void Upload(CString strpath);
	void Download(CString strpath);
	void CloseConnection();
};

