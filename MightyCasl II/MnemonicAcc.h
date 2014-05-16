// MnemonicAcc.h: CMnemonicADD クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICACC_H__BDBBD9E4_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICACC_H__BDBBD9E4_D917_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicADDA : public CMnemonic  
{
public:
	CMnemonicADDA(WORD ADDAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicADDA();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
};

class CMnemonicADDL : public CMnemonic  
{
public:
	CMnemonicADDL(WORD ADDLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicADDL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
};

class CMnemonicSUBA : public CMnemonic  
{
public:
	CMnemonicSUBA(WORD SUBAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSUBA();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

class CMnemonicSUBL : public CMnemonic  
{
public:
	CMnemonicSUBL(WORD SUBLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicSUBL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

class CMnemonicAND : public CMnemonic  
{
public:
	CMnemonicAND(WORD ANDress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicAND();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

class CMnemonicOR : public CMnemonic  
{
public:
	CMnemonicOR(WORD ORress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicOR();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};

class CMnemonicXOR : public CMnemonic  
{
public:
	CMnemonicXOR(WORD XORress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicXOR();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

};


#endif // !defined(AFX_MNEMONICACC_H__BDBBD9E4_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
