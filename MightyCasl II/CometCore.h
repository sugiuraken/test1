// CometCore.h: CCometCore クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMETCORE_H__3DFD17F6_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_)
#define AFX_COMETCORE_H__3DFD17F6_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_

#include "Memory.h"	// ClassView によって追加されました。
#include "Register.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Mnemonic.h"

#define EXECUTEMODE_GO		0
#define EXECUTEMODE_TRACE	1
#define EXECUTEMODE_PASS	2
#define EXECUTEMODE_COME	3


class CMightyCaslDoc;
class CCometCore  
{
protected:
	BOOL IsTemporaryBreakPoint(WORD address);
	BOOL m_bExecuteStop;
	void PumpMessages();
public:
	void ClearTemporaryBreakPoint(){m_tempBreakPoint.RemoveAll();}
	void SetTemporaryBreakPoint(WORD address1, WORD address2);
	void SetTemporaryBreakPoint(WORD address);
	CMightyCaslDoc* m_pDocument;
	CUIntArray m_tempBreakPoint;
	BOOL ExecuteGo(CMnemonicArray* pMnemonics, int mode, WORD breakAddr = 0x0000);
	void Init();
	CRegister m_register;
	CMemory m_memory;
	CCometCore();
	virtual ~CCometCore();
	void ExecuteStop() {m_bExecuteStop = TRUE;}
};

#endif // !defined(AFX_COMETCORE_H__3DFD17F6_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_)
