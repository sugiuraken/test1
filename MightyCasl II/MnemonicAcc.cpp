// MnemonicAcc.cpp: CMnemonicADD クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicAcc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicADDA::CMnemonicADDA(WORD ADDAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(ADDAress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicADDA::~CMnemonicADDA()
{

}

BOOL CMnemonicADDA::Assemble()
{
	m_code[0] = COMET_ADDA;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicADDA::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	int singnedValue1 = (signed short)value1;
	int singnedValue2 = (signed short)value2;
	int resultValue = singnedValue1 + singnedValue2;

	StoreOperand_GR(pRegister, (WORD)resultValue);
	pRegister->UpdateFlagState((signed short)resultValue);
	pRegister->UpdateOverflowFlag(resultValue);

	return TRUE;
}

CMnemonicADDL::CMnemonicADDL(WORD ADDLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(ADDLress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicADDL::~CMnemonicADDL()
{

}

BOOL CMnemonicADDL::Assemble()
{
	m_code[0] = COMET_ADDL;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicADDL::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	UINT unsingnedValue1 = value1;
	UINT unsingnedValue2 = value2;
	UINT resultValue = unsingnedValue1 + unsingnedValue2;

	StoreOperand_GR(pRegister, (WORD)resultValue);
	pRegister->UpdateFlagState((signed short)resultValue);
	pRegister->UpdateOverflowFlag(resultValue);

	return TRUE;
}


CMnemonicSUBA::CMnemonicSUBA(WORD SUBAress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(SUBAress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicSUBA::~CMnemonicSUBA()
{

}

BOOL CMnemonicSUBA::Assemble()
{
	m_code[0] = COMET_SUBA;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSUBA::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	int singnedValue1 = (signed short)value1;
	int singnedValue2 = (signed short)value2;
	int resultValue = singnedValue1 - singnedValue2;

	StoreOperand_GR(pRegister, (WORD)resultValue);
	pRegister->UpdateFlagState((signed short)resultValue);
	pRegister->UpdateOverflowFlag(resultValue);

	return TRUE;
}

CMnemonicSUBL::CMnemonicSUBL(WORD SUBLress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(SUBLress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicSUBL::~CMnemonicSUBL()
{

}

BOOL CMnemonicSUBL::Assemble()
{
	m_code[0] = COMET_SUBL;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicSUBL::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);

	UINT unsingnedValue1 = value1;
	UINT unsingnedValue2 = value2;
	UINT resultValue = unsingnedValue1 - unsingnedValue2;

	StoreOperand_GR(pRegister, (WORD)resultValue);
	pRegister->UpdateFlagState((signed short)resultValue);
	pRegister->UpdateOverflowFlag(resultValue);

	return TRUE;
}



CMnemonicAND::CMnemonicAND(WORD ANDress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(ANDress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicAND::~CMnemonicAND()
{

}

BOOL CMnemonicAND::Assemble()
{
	m_code[0] = COMET_AND;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicAND::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);
	value1 &= value2;

	StoreOperand_GR(pRegister, value1);
	pRegister->UpdateFlagState((signed short)value1);
	pRegister->ResetOverflowFlag();

	return TRUE;
}


CMnemonicOR::CMnemonicOR(WORD ORress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(ORress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicOR::~CMnemonicOR()
{

}

BOOL CMnemonicOR::Assemble()
{
	m_code[0] = COMET_OR;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicOR::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);
	value1 |= value2;

	StoreOperand_GR(pRegister, value1);
	pRegister->UpdateFlagState((signed short)value1);
	pRegister->ResetOverflowFlag();


	return TRUE;
}


CMnemonicXOR::CMnemonicXOR(WORD XORress, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(XORress, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicXOR::~CMnemonicXOR()
{

}

BOOL CMnemonicXOR::Assemble()
{
	m_code[0] = COMET_XOR;
	if (AnalyzeOperand_GRGR())
	{
		m_codeSize = 1;
		return TRUE;
	}
	m_codeSize = 2;
	return AnalyzeOperand_GRadrXR();
}

BOOL CMnemonicXOR::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	WORD value1, value2;
	if (m_code[0]& COMET_RR_BIT)
		EvalOperand_GR1GR2(pRegister, pMemory, value1, value2);		
	else
		EvalOperand_GRadrXR(pRegister, pMemory, value1, value2);
	value1 ^= value2;

	StoreOperand_GR(pRegister, value1);
	pRegister->UpdateFlagState((signed short)value1);
	pRegister->ResetOverflowFlag();

	return TRUE;
}

