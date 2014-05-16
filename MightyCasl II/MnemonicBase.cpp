// MnemonicBase.cpp: CMnemonicLD クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicLD::CMnemonicLD(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicLD::~CMnemonicLD()
{

}

BOOL CMnemonicLD::Assemble()
{
	m_code[0] = COMET_LD;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicLD::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR2(pRegister, pMemory, value);		
	else
		EvalOperand_adrXR(pRegister, pMemory, value);

	StoreOperand_GR(pRegister, value);
	pRegister->UpdateFlagState((signed short)value);
	pRegister->ResetOverflowFlag();
	return TRUE;
}


CMnemonicST::CMnemonicST(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicST::~CMnemonicST()
{

}

BOOL CMnemonicST::Assemble()
{
	m_code[0] = COMET_ST;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicST::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value;
	EvalOperand_GR(pRegister, pMemory, value);
	StoreOperand_addrXR(pRegister, pMemory, value);

	return TRUE;
}


CMnemonicLAD::CMnemonicLAD(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicLAD::~CMnemonicLAD()
{

}

BOOL CMnemonicLAD::Assemble()
{
	m_code[0] = COMET_LAD;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicLAD::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value;
	EvalOperand_adrXRImm(pRegister, pMemory, value);
	StoreOperand_GR(pRegister, value);
//	pRegister->UpdateFlagState((signed short)value);

	return TRUE;
}

