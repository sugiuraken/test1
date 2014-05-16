// MnemonicJump.cpp: CMnemonicJPZ クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "MnemonicJump.h"
#include "CometCore.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicJPL::CMnemonicJPL(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJPL::~CMnemonicJPL()
{

}

BOOL CMnemonicJPL::Assemble()
{
	m_code[0] = COMET_JPL;
	return AnalyzeOperand_adrXR();
}

void CMnemonicJPL::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize, addr);
}

BOOL CMnemonicJPL::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	if (pRegister->IsPlus())
		EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	else
		m_jumpAddress = m_address + 2;
	return TRUE;
}




CMnemonicJMI::CMnemonicJMI(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJMI::~CMnemonicJMI()
{

}

BOOL CMnemonicJMI::Assemble()
{
	m_code[0] = COMET_JMI;
	return AnalyzeOperand_adrXR();
}

void CMnemonicJMI::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize, addr);
}

BOOL CMnemonicJMI::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	if (pRegister->IsMinus())
		EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	else
		m_jumpAddress = m_address + 2;
	return TRUE;
}


CMnemonicJNZ::CMnemonicJNZ(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJNZ::~CMnemonicJNZ()
{

}

BOOL CMnemonicJNZ::Assemble()
{
	m_code[0] = COMET_JNZ;
	return AnalyzeOperand_adrXR();
}

void CMnemonicJNZ::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize, addr);
}

BOOL CMnemonicJNZ::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	if (pRegister->IsNonZero())
		EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	else
		m_jumpAddress = m_address + 2;
	return TRUE;
}


CMnemonicJZE::CMnemonicJZE(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJZE::~CMnemonicJZE()
{

}

BOOL CMnemonicJZE::Assemble()
{
	m_code[0] = COMET_JZE;
	return AnalyzeOperand_adrXR();
}

void CMnemonicJZE::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize, addr);
}

BOOL CMnemonicJZE::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	if (pRegister->IsZero())
		EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	else
		m_jumpAddress = m_address + 2;
	return TRUE;
}


CMnemonicJOV::CMnemonicJOV(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJOV::~CMnemonicJOV()
{

}

BOOL CMnemonicJOV::Assemble()
{
	m_code[0] = COMET_JOV;
	return AnalyzeOperand_adrXR();
}

void CMnemonicJOV::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize, addr);
}

BOOL CMnemonicJOV::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	if (pRegister->IsOverflow())
		EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	else
		m_jumpAddress = m_address + 2;
	return TRUE;
}


CMnemonicJUMP::CMnemonicJUMP(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_codeSize = 2;
}

CMnemonicJUMP::~CMnemonicJUMP()
{

}

BOOL CMnemonicJUMP::Assemble()
{
	m_code[0] = COMET_JUMP;
	return AnalyzeOperand_adrXR();
}


void CMnemonicJUMP::SetTraceBreakPoint(CCometCore *pCometCore)
{
	WORD addr;
	EvalOperand_adrXRImm(&pCometCore->m_register, &pCometCore->m_memory, addr);
	pCometCore->SetTemporaryBreakPoint(addr);
}

BOOL CMnemonicJUMP::ExecuteCode(CRegister* pRegister, CMemory* pMemory, CMightyCaslDoc* pDocument)
{
	EvalOperand_adrXRImm(pRegister, pMemory, m_jumpAddress);
	return TRUE;
}
