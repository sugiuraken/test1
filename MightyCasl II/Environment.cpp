// Environment.cpp: CEnvironment クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Environment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CEnvironment::CEnvironment()
{
	m_defaultSourcePath.Empty();
	m_defaultWorkView = ENV_WORKVIEW_DUMP;
	m_bSaveWatchElm = FALSE;
	m_inDeviceType = ENV_INDEVICE_CONSOLE;
	m_outDeviceType = ENV_OUTDEVICE_CONSOLE;
	m_inFileName = "";
	m_outFileName = "";
}

CEnvironment::~CEnvironment()
{

}

BOOL CEnvironment::GetProfile(CWinApp *pApp)
{
	m_defaultSourcePath = pApp->GetProfileString(REG_ENTRY_ENV, REG_KEY_SOURCEPATH);
	m_defaultWorkView = pApp->GetProfileInt(REG_ENTRY_ENV, REG_KEY_WORKVIEW, ENV_WORKVIEW_DUMP);
	m_bSaveWatchElm = pApp->GetProfileInt(REG_ENTRY_ENV, REG_KEY_SAVEWATCHFLAG, 0);
	m_inDeviceType = pApp->GetProfileInt(REG_ENTRY_ENV, REG_KEY_INDEVICETYPE, ENV_INDEVICE_CONSOLE);
	m_outDeviceType = pApp->GetProfileInt(REG_ENTRY_ENV, REG_KEY_OUTDEVICETYPE, ENV_OUTDEVICE_CONSOLE);
	m_inFileName = pApp->GetProfileString(REG_ENTRY_ENV, REG_KEY_INFILENAME);
	m_outFileName = pApp->GetProfileString(REG_ENTRY_ENV, REG_KEY_OUTFILENAME);
	return TRUE;
}

BOOL CEnvironment::WriteProfile(CWinApp *pApp)
{
	if (!pApp->WriteProfileString(REG_ENTRY_ENV, REG_KEY_SOURCEPATH, m_defaultSourcePath) ||
			!pApp->WriteProfileInt(REG_ENTRY_ENV, REG_KEY_WORKVIEW, m_defaultWorkView) ||
			!pApp->WriteProfileInt(REG_ENTRY_ENV, REG_KEY_INDEVICETYPE, m_inDeviceType) ||
			!pApp->WriteProfileInt(REG_ENTRY_ENV, REG_KEY_OUTDEVICETYPE, m_outDeviceType) ||
			!pApp->WriteProfileString(REG_ENTRY_ENV, REG_KEY_INFILENAME, m_inFileName) ||
			!pApp->WriteProfileString(REG_ENTRY_ENV, REG_KEY_OUTFILENAME, m_outFileName) ||
			!pApp->WriteProfileInt(REG_ENTRY_ENV, REG_KEY_SAVEWATCHFLAG, m_bSaveWatchElm))
		return FALSE;
	return TRUE;
}
