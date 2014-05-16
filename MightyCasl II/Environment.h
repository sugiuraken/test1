// Environment.h: CEnvironment クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENVIRONMENT_H__28A2ACC1_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_ENVIRONMENT_H__28A2ACC1_DF4A_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ENV_WORKVIEW_DUMP	0
#define ENV_WORKVIEW_WATCH	1
#define ENV_WORKVIEW_OUTPUT	2

#define ENV_INDEVICE_CONSOLE	0
#define ENV_INDEVICE_FILE		1

#define ENV_OUTDEVICE_CONSOLE	0
#define ENV_OUTDEVICE_FILE		1

class CEnvironment  
{
public:
	CString m_defaultSourcePath;
	int	m_defaultWorkView;
	BOOL m_bSaveWatchElm;
	int m_inDeviceType;
	int m_outDeviceType;
	CString m_inFileName;
	CString m_outFileName;
public:
	BOOL WriteProfile(CWinApp* pApp);
	BOOL GetProfile(CWinApp* pApp);
	CEnvironment();
	virtual ~CEnvironment();

};

#endif // !defined(AFX_ENVIRONMENT_H__28A2ACC1_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
