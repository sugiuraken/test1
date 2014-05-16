// MnemonicSuspect.h: CMnemonicSTART クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICSUSPECT_H__896A79A7_D3AE_11D3_BD80_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICSUSPECT_H__896A79A7_D3AE_11D3_BD80_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicSTART : public CMnemonic  
{
public:
	CMnemonicSTART(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSTART();
	virtual BOOL Assemble();
	virtual BOOL Output(CMemory *pMemory) {return TRUE;}
	virtual BOOL CheckExecuteCode(CMemory* pMemory) {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

protected:
	WORD m_startAddress;
};

class CMnemonicEND : public CMnemonic  
{
public:
	CMnemonicEND(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicEND();
	virtual BOOL Assemble();
	virtual BOOL Output(CMemory *pMemory) {return TRUE;}
	virtual BOOL CheckExecuteCode(CMemory* pMemory) {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);
};

class CMnemonicDC : public CMnemonic  
{
public:
	CMnemonicDC(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicDC();
	virtual BOOL Assemble();
	virtual WORD GetCodeSize() {return m_words.GetSize();}
	virtual BOOL Output(CMemory *pMemory);
	virtual BOOL CheckExecuteCode(CMemory* pMemory) {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

	CUIntArray* GetConstant() {return &m_words;}
protected:
	CUIntArray m_words;
};

class CMnemonicDS : public CMnemonic  
{
public:
	CMnemonicDS(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicDS();
	virtual BOOL Assemble();
	virtual BOOL Output(CMemory *pMemory) {return TRUE;}
	virtual BOOL CheckExecuteCode(CMemory* pMemory) {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

protected:
};

#endif // !defined(AFX_MNEMONICSUSPECT_H__896A79A7_D3AE_11D3_BD80_0000E8647D2D__INCLUDED_)
