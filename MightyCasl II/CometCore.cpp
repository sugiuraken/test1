// CometCore.cpp: CCometCore クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "CometCore.h"
#include "MightyCaslDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CCometCore::CCometCore()
{
	m_pDocument = NULL;
}

CCometCore::~CCometCore()
{

}


void CCometCore::Init()
{
	m_memory.Init();
	m_register.Init();
}

BOOL CCometCore::ExecuteGo(CMnemonicArray *pMnemonics, int mode, WORD breakAddr)
{
	m_bExecuteStop = FALSE;
	WORD curPC = m_register.GetValue(REG_PC);
	CMnemonic* pMnemoic = pMnemonics->FindExecutable(curPC);
	if (pMnemoic == NULL)
	{
		AfxMessageBox(IDS_RUNERR_NOEXECUTABLE, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (mode == EXECUTEMODE_TRACE)
		pMnemoic->SetTraceBreakPoint(this);
	else if (mode == EXECUTEMODE_PASS)
		pMnemoic->SetPassBreakPoint(this);
	else if (mode == EXECUTEMODE_COME)
		SetTemporaryBreakPoint(breakAddr);
	else
		ClearTemporaryBreakPoint();

	BOOL bResult = TRUE;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->PreProgramExecute();
	int nCount = 0;
	for (;;)
	{
		if (!pMnemoic->Execute(&m_register, &m_memory, m_pDocument))
		{
			bResult = FALSE;
			break;
		}

		// 命令実行後、PC が 0000 になったら終了
		WORD regPC = m_register.GetValue(REG_PC);
		if (regPC == 0x0000)
		{
			m_pDocument->CloseDeviceFiles();
			AfxMessageBox(IDS_MSG_EXECUTEXIT, MB_OK | MB_ICONINFORMATION);
			break;
		}

		// テンポラリブレークポイントをチェック
		curPC = m_register.GetValue(REG_PC);
		if (IsTemporaryBreakPoint(curPC))
			break;


		pMnemoic = pMnemonics->FindExecutable(curPC);
		if (pMnemoic == NULL)
		{
			AfxMessageBox(IDS_RUNERR_NOEXECUTABLE, MB_OK | MB_ICONEXCLAMATION);
			bResult = FALSE;
			break;
		}


		// ブレークポイントをチェック
		if (pMnemoic->IsBreakPoint())
			break;
	

		if (nCount++ == 100)
		{
			pMainFrame->StepProgress();
			nCount = 0;
			PumpMessages();

			if (m_bExecuteStop)
			{
				AfxMessageBox(IDS_MSG_USERSTOP, MB_OK | MB_ICONINFORMATION);
				break;
			}
		}
	}
	pMainFrame->PostProgramExecute();
	return bResult;
}

void CCometCore::PumpMessages()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);  
		AfxGetApp()->OnIdle(0);
	}
}

void CCometCore::SetTemporaryBreakPoint(WORD address)
{
	m_tempBreakPoint.RemoveAll();
	m_tempBreakPoint.Add(address);
}

void CCometCore::SetTemporaryBreakPoint(WORD address1, WORD address2)
{
	m_tempBreakPoint.RemoveAll();
	m_tempBreakPoint.Add(address1);
	m_tempBreakPoint.Add(address2);
}

BOOL CCometCore::IsTemporaryBreakPoint(WORD address)
{
	for (int i = 0; i < m_tempBreakPoint.GetSize(); i++)
	{
		if (m_tempBreakPoint[i] == address)
			return TRUE;
	}
	return FALSE;
}
