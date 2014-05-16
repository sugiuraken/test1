// MnemonicMacro.cpp: CMnemonicIN クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicMacro.h"
#include "Assembler.h"
#include "MightyCaslDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicIN::CMnemonicIN(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 12;
}

CMnemonicIN::~CMnemonicIN()
{

}

BOOL CMnemonicIN::Assemble()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	if (params.GetSize() != 2)
	{
		m_errorId = IDS_ASMERR_OPE_NUMBER;
		return FALSE;
	}

	if (!GetLabelValue(params[0], m_bufferAddress))
		return FALSE;

	if (!GetLabelValue(params[1], m_lengthAddress))
		return FALSE;

	m_code[0] = COMET_PUSH | COMET_GR1;							// PUSH 0,GR1
	m_code[1] = 0x0000;
	m_code[2] = COMET_PUSH | COMET_GR2;							// PUSH 0,GR2
	m_code[3] = 0x0000;
	m_code[4] = COMET_LAD | (COMET_GR1 << 4) | COMET_GRNULL;	// LAD GR1,BUF
	m_code[5] = m_bufferAddress;
	m_code[6] = COMET_LAD | (COMET_GR2 << 4) | COMET_GRNULL;	// LAD GR2,LEN
	m_code[7] = m_lengthAddress;
	m_code[8] = COMET_SVC | COMET_GRNULL;						// SVC n
	m_code[9] = GetSvcParam();
	m_code[10] = COMET_POP | (COMET_GR2 << 4);					// POP GR2
	m_code[11] = COMET_POP | (COMET_GR1 << 4);					// POP GR1

	return TRUE;
}

BOOL CMnemonicIN::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	CString strTemp;
	BOOL result = pDocument->InputDevice(strTemp);
	if (result)
	{
		int leng = strTemp.GetLength();
		if (leng > 80)
		{
			strTemp = strTemp.Left(80);
			leng = 80;
		}
		pMemory->SetMemory(m_lengthAddress, leng);
		for (int i = 0; i < leng; i++)
		{
			WORD data = strTemp[i];
			pMemory->SetMemory(m_bufferAddress + i, data);
		}
	}
	else
		pMemory->SetMemory(m_lengthAddress, 0xFFFF);		// -1 を設定

	// FRは不定になる
	pRegister->SetValue(REG_FR, result % 7);
	return TRUE;
}


CMnemonicOUT::CMnemonicOUT(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonicIN(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{

}

CMnemonicOUT::~CMnemonicOUT()
{

}

BOOL CMnemonicOUT::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	CString strTemp;

	int leng = (int)pMemory->GetMemory(m_lengthAddress);
	if (leng > 256)
		leng = 256;			// 256文字までの制限

	for (int i = 0; i < leng; i++)
	{
		WORD data = pMemory->GetMemory(m_bufferAddress + i) & 0x00ff;
		int ch = data;
		if (isprint(ch))
			strTemp += ch;
		else
		{
			CString strControl;
			strControl.Format("\\%02X", ch);
			strTemp += strControl;
		}
	}

	pDocument->OutputDevice(strTemp);

	// FRは不定になる
	pRegister->SetValue(REG_FR, leng % 7);
	return TRUE;
}



CMnemonicRPUSH::CMnemonicRPUSH(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 14;
}

CMnemonicRPUSH::~CMnemonicRPUSH()
{

}

BOOL CMnemonicRPUSH::Assemble()
{
	m_code[0] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR1;	// PUSH 0,GR1
	m_code[1] = 0x0000;
	m_code[2] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR2;	// PUSH 0,GR2
	m_code[3] = 0x0000;
	m_code[4] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR3;	// PUSH 0,GR3
	m_code[5] = 0x0000;
	m_code[6] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR4;	// PUSH 0,GR4
	m_code[7] = 0x0000;
	m_code[8] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR5;	// PUSH 0,GR5
	m_code[9] = 0x0000;
	m_code[10] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR6;	// PUSH 0,GR6
	m_code[11] = 0x0000;
	m_code[12] = COMET_PUSH | (COMET_GRNULL << 4) | COMET_GR7;	// PUSH 0,GR7
	m_code[13] = 0x0000;

	return TRUE;
}

BOOL CMnemonicRPUSH::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	for (int nRegID = COMET_GR1; nRegID <= COMET_GR7; nRegID++)
	{
		WORD value = pRegister->GetValue(nRegID);
		WORD regSP = pRegister->GetValue(REG_SP);
		regSP--;
		regSP &= 0xffff;

		pMemory->SetMemory(regSP, value);
		pRegister->SetValue(REG_SP, regSP);
	}
	return TRUE;
}


CMnemonicRPOP::CMnemonicRPOP(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 7;
}

CMnemonicRPOP::~CMnemonicRPOP()
{

}

BOOL CMnemonicRPOP::Assemble()
{
	m_code[0] = COMET_POP | (COMET_GR7 << 4) | COMET_GRNULL;	// POP GR7
	m_code[1] = COMET_POP | (COMET_GR6 << 4) | COMET_GRNULL;	// POP GR6
	m_code[2] = COMET_POP | (COMET_GR5 << 4) | COMET_GRNULL;	// POP GR5
	m_code[3] = COMET_POP | (COMET_GR4 << 4) | COMET_GRNULL;	// POP GR4
	m_code[4] = COMET_POP | (COMET_GR3 << 4) | COMET_GRNULL;	// POP GR3
	m_code[5] = COMET_POP | (COMET_GR2 << 4) | COMET_GRNULL;	// POP GR2
	m_code[6] = COMET_POP | (COMET_GR1 << 4) | COMET_GRNULL;	// POP GR1

	return TRUE;
}

BOOL CMnemonicRPOP::ExecuteCode(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	for (int nRegID = COMET_GR7; nRegID >= COMET_GR1; nRegID--)
	{
		WORD regSP = pRegister->GetValue(REG_SP);
		WORD value = pMemory->GetMemory(regSP);

		pRegister->SetValue(nRegID, value);
		pRegister->SetValue(REG_SP, (regSP + 1) & 0xffff);
	}
	return TRUE;
}
