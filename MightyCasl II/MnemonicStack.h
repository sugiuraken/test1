// MnemonicStack.h: CMnemonicPUSH クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICSTACK_H__BC498C43_D936_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICSTACK_H__BC498C43_D936_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicPUSH : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicPUSH(WORD PUSHress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicPUSH();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};

class CMnemonicPOP : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicPOP(WORD POPress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicPOP();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};

class CMnemonicCALL : public CMnemonic  
{
protected:
	WORD m_callAddress;
	virtual WORD GetNextPCAddress() {return m_callAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicCALL(WORD CALLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicCALL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetPassBreakPoint(CCometCore* pCometCore);
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};

class CMnemonicRET : public CMnemonic  
{
protected:
	WORD m_retAddress;
	virtual WORD GetNextPCAddress() {return m_retAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicRET(WORD RETress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicRET();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);
};


class CMnemonicSVC : public CMnemonic  
{
protected:
	WORD m_SVCParam;
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicSVC(WORD SVCress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSVC();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
};

class CMnemonicNOP : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicNOP(WORD NOPress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicNOP();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
};



#endif // !defined(AFX_MNEMONICSTACK_H__BC498C43_D936_11D3_BD8B_0000E8647D2D__INCLUDED_)
