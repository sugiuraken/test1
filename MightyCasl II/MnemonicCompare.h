// MnemonicCompare.h: CMnemonicCPA クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICCOMPARE_H__BDBBD9E5_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICCOMPARE_H__BDBBD9E5_D917_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicCPA : public CMnemonic  
{
public:
	CMnemonicCPA(WORD CPAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicCPA();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

class CMnemonicCPL : public CMnemonic  
{
public:
	CMnemonicCPL(WORD CPLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicCPL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

#endif // !defined(AFX_MNEMONICCOMPARE_H__BDBBD9E5_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
