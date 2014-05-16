// MnemonicShift.cpp: CMnemonicSLA クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicShift.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicSLA::CMnemonicSLA(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicSLA::~CMnemonicSLA()
{

}

BOOL CMnemonicSLA::Assemble()
{
	m_code[0] = COMET_SLA;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSLA::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value, nBit;
	EvalOperand_GRadrXRImm(pRegister, pMemory, value, nBit);

	WORD flagBit = value & 0x8000;
	WORD value2 = value;
	value2 <<= nBit;
	value = (WORD)value2 & 0x7fff;
	value |= flagBit;
	
	StoreOperand_GR(pRegister, value);
	pRegister->UpdateFlagState((signed short)value);
	if (value2 & 0x8000)
		pRegister->SetOverflowFlag();
	else
		pRegister->ResetOverflowFlag();

	return TRUE;
}



CMnemonicSRA::CMnemonicSRA(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicSRA::~CMnemonicSRA()
{

}

BOOL CMnemonicSRA::Assemble()
{
	m_code[0] = COMET_SRA;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSRA::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value, nBit;
	EvalOperand_GRadrXRImm(pRegister, pMemory, value, nBit);

	WORD saveValue = value;
	value = (signed short)value >> nBit;
	
	StoreOperand_GR(pRegister, value);
	pRegister->UpdateFlagState((signed short)value);

	// オーバーフローフラグの更新
	if (nBit == 0)
		;
	else if (nBit <= 16)
	{
		if (saveValue & (1 << (nBit - 1)))
			pRegister->SetOverflowFlag();
		else
			pRegister->ResetOverflowFlag();
	}
	else
		pRegister->ResetOverflowFlag();

	return TRUE;
}



CMnemonicSLL::CMnemonicSLL(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicSLL::~CMnemonicSLL()
{

}

BOOL CMnemonicSLL::Assemble()
{
	m_code[0] = COMET_SLL;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSLL::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value, nBit;
	EvalOperand_GRadrXRImm(pRegister, pMemory, value, nBit);

	UINT unsignedValue = value;
	unsignedValue <<= nBit;
	
	StoreOperand_GR(pRegister, (WORD)unsignedValue);
	pRegister->UpdateFlagState((signed short)unsignedValue);

	if (unsignedValue & 0x10000)
		pRegister->SetOverflowFlag();
	else
		pRegister->ResetOverflowFlag();

	return TRUE;
}



CMnemonicSRL::CMnemonicSRL(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicSRL::~CMnemonicSRL()
{

}

BOOL CMnemonicSRL::Assemble()
{
	m_code[0] = COMET_SRL;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSRL::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value, nBit;
	EvalOperand_GRadrXRImm(pRegister, pMemory, value, nBit);

	WORD saveValue = value;
	value >>= nBit;
	
	StoreOperand_GR(pRegister, value);
	pRegister->UpdateFlagState((signed short)value);

	// オーバーフローフラグの更新
	if (nBit == 0)
		;
	else if (nBit <= 16)
	{
		if (saveValue & (1 << (nBit - 1)))
			pRegister->SetOverflowFlag();
		else
			pRegister->ResetOverflowFlag();
	}
	else
		pRegister->ResetOverflowFlag();
	return TRUE;
}
