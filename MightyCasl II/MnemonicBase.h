// MnemonicBase.h: CMnemonicLD クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICBASE_H__BDBBD9E1_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICBASE_H__BDBBD9E1_D917_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicLD : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicLD(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicLD();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
};

class CMnemonicST : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicST(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicST();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
};

class CMnemonicLAD : public CMnemonic  
{
protected:
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicLAD(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicLAD();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}

};


#endif // !defined(AFX_MNEMONICBASE_H__BDBBD9E1_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
