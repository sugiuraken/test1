// MnemonicJump.h: CMnemonicJPZ クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICJUMP_H__BDBBD9E7_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_MNEMONICJUMP_H__BDBBD9E7_D917_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicJPL : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJPL(WORD JPLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJPL();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};

class CMnemonicJMI : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJMI(WORD JMIress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJMI();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};

class CMnemonicJNZ : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJNZ(WORD JNZress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJNZ();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};

class CMnemonicJZE : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJZE(WORD JZEress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJZE();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};

class CMnemonicJOV : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJOV(WORD JOVress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJOV();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);

};


class CMnemonicJUMP : public CMnemonic  
{
protected:
	WORD m_jumpAddress;
	virtual WORD GetNextPCAddress() {return m_jumpAddress;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
public:
	CMnemonicJUMP(WORD JUMPress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicJUMP();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual void SetTraceBreakPoint(CCometCore* pCometCore);
};

#endif // !defined(AFX_MNEMONICJUMP_H__BDBBD9E7_D917_11D3_BD8B_0000E8647D2D__INCLUDED_)
