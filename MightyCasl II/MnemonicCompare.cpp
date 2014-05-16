// MnemonicCompare.cpp: CMnemonicLD クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicCompare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicCPA::CMnemonicCPA(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicCPA::~CMnemonicCPA()
{

}

BOOL CMnemonicCPA::Assemble()
{
	m_code[0] = COMET_CPA;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicCPA::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	int singnedValue1 = (signed short)value1;
	int singnedValue2 = (signed short)value2;
	int resultValue = singnedValue1 - singnedValue2;

//	pRegister->UpdateFlagState((signed short)resultValue);
	if (singnedValue1 == singnedValue2)
		pRegister->SetZeroFlag();
	else
		pRegister->ResetZeroFlag();

	if (singnedValue1 < singnedValue2)
		pRegister->SetSignFlag();
	else
		pRegister->ResetSignFlag();

	pRegister->ResetOverflowFlag();

	return TRUE;
}

CMnemonicCPL::CMnemonicCPL(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicCPL::~CMnemonicCPL()
{

}

BOOL CMnemonicCPL::Assemble()
{
	m_code[0] = COMET_CPL;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicCPL::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	UINT unsingnedValue1 = value1;
	UINT unsingnedValue2 = value2;
	UINT resultValue = unsingnedValue1 - unsingnedValue2;

//	pRegister->UpdateFlagState((signed short)resultValue);
	if (unsingnedValue1 == unsingnedValue2)
		pRegister->SetZeroFlag();
	else
		pRegister->ResetZeroFlag();

	if (unsingnedValue1 < unsingnedValue2)
		pRegister->SetSignFlag();
	else
		pRegister->ResetSignFlag();

	pRegister->ResetOverflowFlag();

	return TRUE;
}
