// MnemonicShift.h: CMnemonicSLA クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICSHIFT_H__BDBBD9E6_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICSHIFT_H__BDBBD9E6_D917_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicSLA : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicSLA(WORD SLAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSLA();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};

class CMnemonicSRA : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicSRA(WORD SRAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSRA();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};


class CMnemonicSLL : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicSLL(WORD SLLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSLL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};


class CMnemonicSRL : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicSRL(WORD SRLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSRL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};


#endif // !defined(AFX_MNEMONICSHIFT_H__BDBBD9E6_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
