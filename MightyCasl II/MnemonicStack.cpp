// MnemonicStack.cpp: CMnemonicPUSH クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MnemonicStack.h"
#include "CometCore.h"
#include "MightyCaslDoc.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicPUSH::CMnemonicPUSH(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicPUSH::~CMnemonicPUSH()
{

}

BOOL CMnemonicPUSH::Assemble()
{
	m_code[0] = COMET_PUSH;
	return AnalyzeOperand_adrXR();
}

BOOL CMnemonicPUSH::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	WORD value; 
	EvalOperand_adrXRImm(pRegister, pMemory, value);
	
	WORD regSP = pRegister->GetValue(REG_SP);
	regSP--;
	regSP &= 0xffff;

	pMemory->SetMemory(regSP, value);
	pRegister->SetValue(REG_SP, regSP);
	return TRUE;
}


CMnemonicPOP::CMnemonicPOP(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 1;
}


CMnemonicPOP::~CMnemonicPOP()
{

}

BOOL CMnemonicPOP::Assemble()
{
	m_code[0] = COMET_POP;
	return AnalyzeOperand_GR();
}

BOOL CMnemonicPOP::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	WORD regSP = pRegister->GetValue(REG_SP);
	WORD value = pMemory->GetMemory(regSP);
	StoreOperand_GR(pRegister, value);
	pRegister->SetValue(REG_SP, (regSP + 1) & 0xffff);
	return TRUE;
}


CMnemonicCALL::CMnemonicCALL(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicCALL::~CMnemonicCALL()
{

}

BOOL CMnemonicCALL::Assemble()
{
	m_code[0] = COMET_CALL;
	return AnalyzeOperand_adrXR();
}

void CMnemonicCALL::SetPassBreakPoint(CCometCore* pCometCore)
{
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize);
}

void CMnemonicCALL::SetTraceBreakPoint(CCometCore* pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(addr);
}

BOOL CMnemonicCALL::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	EvalOperand_adrXRImm(pRegister, pMemory, m_callAddress);
	WORD regSP = pRegister->GetValue(REG_SP);
	regSP--;
	regSP &= 0xffff;
	pMemory->SetMemory(regSP, m_address + 2);
	pRegister->SetValue(REG_SP, regSP);

	return TRUE;
}


CMnemonicRET::CMnemonicRET(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 1;
}

CMnemonicRET::~CMnemonicRET()
{

}

BOOL CMnemonicRET::Assemble()
{
	m_code[0] = COMET_RET;
	return AnalyzeOperand_NULL();
}

void CMnemonicRET::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD regSP = pCometCore->m_register.GetValue(REG_SP);
	WORD retAddr = pCometCore->m_memory.GetMemory(regSP);
	pCometCore->SetTemporaryBreakPoint(retAddr);
}

BOOL CMnemonicRET::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	WORD regSP = pRegister->GetValue(REG_SP);
	m_retAddress = pMemory->GetMemory(regSP);
	pRegister->SetValue(REG_SP, regSP + 1);
	
	return TRUE;
}


CMnemonicSVC::CMnemonicSVC(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicSVC::~CMnemonicSVC()
{

}

BOOL CMnemonicSVC::Assemble()
{
	m_code[0] = COMET_SVC;
	return AnalyzeOperand_adrXR();
}

BOOL CMnemonicSVC::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	EvalOperand_adrXRImm(pRegister, pMemory, m_SVCParam);

	CString strTemp;
	strTemp.Format("ｽｰﾊﾞｰﾊﾞｲｻﾞｺｰﾙ %d", m_SVCParam);
	pDocument->OutputDevice(strTemp);

	// FRは不定になる
	pRegister->SetValue(REG_FR, m_SVCParam % 7);

	return TRUE;
}

CMnemonicNOP::CMnemonicNOP(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 1;
}

CMnemonicNOP::~CMnemonicNOP()
{

}

BOOL CMnemonicNOP::Assemble()
{
	m_code[0] = COMET_NOP;
	return AnalyzeOperand_NULL();
}

BOOL CMnemonicNOP::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	return TRUE;
}
