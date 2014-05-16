// MnemonicMacro.h: CMnemonicIN クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MNEMONICMACRO_H__9D6B5020_D51D_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_MNEMONICMACRO_H__9D6B5020_D51D_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mnemonic.h"

class CMnemonicIN : public CMnemonic  
{
public:
	CMnemonicIN(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicIN();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

protected:
	virtual WORD GetSvcParam() {return COMET_SVC_IN;}
	WORD m_bufferAddress;
	WORD m_lengthAddress;

};

class CMnemonicOUT : public CMnemonicIN  
{
public:
	CMnemonicOUT(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicOUT();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);

protected:
	virtual WORD GetSvcParam() {return COMET_SVC_OUT;}
};


class CMnemonicRPUSH : public CMnemonic  
{
public:
	CMnemonicRPUSH(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicRPUSH();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
};

class CMnemonicRPOP : public CMnemonic  
{
public:
	CMnemonicRPOP(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler);
	virtual ~CMnemonicRPOP();
	virtual BOOL Assemble();
	virtual BOOL IsExecutable() {return TRUE;}
	virtual BOOL ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument);
};

#endif // !defined(AFX_MNEMONICMACRO_H__9D6B5020_D51D_11D3_AB2F_006067202C95__INCLUDED_)
