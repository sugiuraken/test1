// Mnemonic.h: CMnemonic クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONIC_H__E3260D21_CF88_11D3_AB2E_006067202C95__INCLUDED_)
#define AFX_MNEMONIC_H__E3260D21_CF88_11D3_AB2E_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comet.h"
#include "memory.h"
#include "register.h"

class CMightyCaslDoc;
class CAssembler;
class CCometCore;

class CMnemonic  
{
public:
	virtual void SetPassBreakPoint(CCometCore* pCometCore);
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);
	virtual BOOL Execute(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
	virtual BOOL IsExecutable() {return FALSE;}
	WORD GetAddress() {return m_address;}
	BOOL IsBreakPoint() {return m_bBreakOn;}
	void SetBreakPoint(BOOL bOn = TRUE) {m_bBreakOn = bOn;}
	UINT GetError();
	virtual WORD GetNextPCAddress() {return m_address + m_codeSize;}
	virtual WORD GetCodeSize();
	virtual BOOL Assemble();
	virtual BOOL Output(CMemory *pMemory);
	CMnemonic(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonic();

	CString GetSourceLine();
protected:
	BOOL AnalyzeOperand_GRGR();
	void StoreOperand_GR(CRegister* pRegister, WORD value);
	void StoreOperand_addrXR(CRegister *pRegister, CMemory* pMemory, WORD value);

	void EvalOperand_GR(CRegister* pRegister, CMemory* pMemory, WORD& value);
	void EvalOperand_GR2(CRegister* pRegister, CMemory* pMemory, WORD& value);
	void EvalOperand_GR1GR2(CRegister* pRegister, CMemory* pMemory, WORD& value1, WORD& value2);
	void EvalOperand_adrXR(CRegister* pRegister, CMemory* pMemory, WORD& value);
	void EvalOperand_adrXRImm(CRegister* pRegister, CMemory* pMemory, WORD& value);
	void EvalOperand_GRadrXR(CRegister* pRegister, CMemory* pMemory, WORD& value1, WORD& value2);
	void EvalOperand_GRadrXRImm(CRegister* pRegister, CMemory* pMemory, WORD& value1, WORD& value2);

	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument) {return TRUE;}
	virtual BOOL CheckExecuteCode(CMemory* pMemory);

	BOOL m_bBreakOn;
	BOOL ParseXR(LPCSTR param, WORD& code);
	BOOL ParseAddr(LPCSTR param, WORD& code);
	BOOL ParseGR(LPCSTR param, WORD& code);
	BOOL AnalyzeOperand_GRadrXR();
	BOOL AnalyzeOperand_adrXR();
	BOOL AnalyzeOperand_GR();
	BOOL AnalyzeOperand_NULL();
	static void SplitOperand(LPCSTR operand, CStringArray& params);
	BOOL GetLabelValue(LPCSTR name, WORD& value);
	BOOL GetLiteralValue(LPCSTR name, WORD& value);
	UINT m_errorId;
	CAssembler* m_pAssembler;
	CString m_strNativeLine;
	CString m_strOperand;
	CString m_strMnemonic;
	WORD m_address;
	WORD m_codeSize;
	WORD m_code[32];
};

class CMnemonicComment : public CMnemonic
{
public:
	CMnemonicComment(WORD address, LPCSTR strNativeLine, CAssembler* pAssembler)
		: CMnemonic(address, NULL, NULL, strNativeLine, pAssembler)
	{}
	virtual ~CMnemonicComment(){}
	virtual BOOL Output(CMemory *pMemory) {return TRUE;}
	virtual BOOL CheckExecuteCode(CMemory* pMemory) {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);
protected:
};

class CMnemonicArray : public CPtrArray  
{
public:
	CMnemonic* FindExecutable(WORD adddress);
	void OutputCode(CMemory* pMemory);
	void ClearAllBreakPoint();
	BOOL IsBreakpointAddress(WORD address);
	void DeleteAll();
	CMnemonicArray();
	virtual ~CMnemonicArray();

};

#endif // !defined(AFX_MNEMONIC_H__E3260D21_CF88_11D3_AB2E_006067202C95__INCLUDED_)
