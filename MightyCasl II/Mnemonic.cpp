// Mnemonic.cpp: CMnemonic クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Mnemonic.h"
#include "Label.h"
#include "Assembler.h"
#include "CometCore.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonic::CMnemonic(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: m_strMnemonic(strMnemonic), m_strOperand(strOperand), m_strNativeLine(strNativeLine)
{
	m_address = address;
	m_pAssembler = pAssembler;

	m_codeSize = 0;
	m_errorId = 0;
	m_bBreakOn = FALSE;
}

CMnemonic::~CMnemonic()
{
}

CString CMnemonic::GetSourceLine()
{
	CString text;
	int nStart = 0;
	int nPos = m_strNativeLine.Find('\t', nStart);
	while (nPos != -1)
	{
		text += m_strNativeLine.Mid(nStart, nPos - nStart);
		int len = text.GetLength();
		int spaceLen = 8 - (len % 8);
		text += CString("        ").Left(spaceLen);
		nStart = nPos + 1;
		nPos = m_strNativeLine.Find('\t', nStart);
	}
	text += m_strNativeLine.Mid(nStart);
	return text;
}

BOOL CMnemonic::Output(CMemory *pMemory)
{
	if (m_codeSize)
	{
		for (int i = 0; i < m_codeSize; i++)
			pMemory->SetMemory(m_address + i, m_code[i]);
	}
	return TRUE;
}

BOOL CMnemonic::CheckExecuteCode(CMemory* pMemory)
{
	if (m_codeSize)
	{
		for (int i = 0; i < m_codeSize; i++)
		{
			if (pMemory->GetMemory(m_address + i) != m_code[i])
				return FALSE;
		}
	}
	return TRUE;
}


BOOL CMnemonic::Assemble()
{
	return TRUE;
}

WORD CMnemonic::GetCodeSize()
{
	return m_codeSize;
}

UINT CMnemonic::GetError()
{
	return m_errorId;
}

BOOL CMnemonic::GetLabelValue(LPCSTR name, WORD &value)
{
	if (CLabel::CheckLabelFormat(name))
	{
		m_errorId = IDS_ASMERR_OPE_BADLABEL;
		return FALSE;
	}

	if (m_pAssembler->m_nPass == 1)
	{
		// １パス目は、常に 0x0000 として処理を進める。
		value = 0x0000;
		return TRUE;
	}

	CLabelBank& rLabelBank = m_pAssembler->m_labelBank;
	CLabel* pLabel;
	if (!rLabelBank.Lookup(name, pLabel))
	{
		m_errorId = IDS_ASMERR_OPE_UNDEF_LABEL;
		return FALSE;
	}
	value = pLabel->m_value;
	return TRUE;
}

BOOL CMnemonic::GetLiteralValue(LPCSTR literal, WORD &value)
{
	if (m_pAssembler->m_nPass == 1)
	{
		// １パス目は、常に 0x0000 として処理を進める。
		value = 0x0000;
		return TRUE;
	}

	CLiteralBank& rLiteralBank = m_pAssembler->m_literalBank;
	CLiteral* pLiteral = rLiteralBank.AppendLiteral(literal);
	if (pLiteral == NULL)
	{
		m_errorId = rLiteralBank.GetLastError();
		return FALSE;
	}
	value = pLiteral->GetAddress();

	// リテラルをラベルとして登録する
	CLabelBank& rLabelBank = m_pAssembler->m_labelBank;
	rLabelBank.RegistLiteralLabel(m_address, value);
	return TRUE;
}

void CMnemonic::SplitOperand(LPCSTR operand, CStringArray &params)
{
	char buffer[1024];
	char* p = strcpy(buffer, operand);
	while (*p)
	{
		if (*p == '\'')
		{
			p++;
			while (*p && *p != '\'')
			{
				if (*p == ',')
					*p = '\t';
				p++;
			}
			if (*p)
				p++;
		}
		else
			p++;
	}

	
	CString strTemp(buffer);
	int nPos;
	while ((nPos = strTemp.Find(',')) != -1)
	{
		CString param = strTemp.Left(nPos);
		param.TrimLeft();
		param.TrimRight();
		param.Replace('\t', ',');
		params.Add(param);
		strTemp = strTemp.Mid(nPos + 1);
	}
	if (!strTemp.IsEmpty())
	{
		strTemp.TrimLeft();
		strTemp.TrimRight();
		strTemp.Replace('\t', ',');
		params.Add(strTemp);
	}
}

BOOL CMnemonic::AnalyzeOperand_GRadrXR()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	int nParam = params.GetSize();
	if (nParam != 2 && nParam != 3)
	{
		m_errorId = IDS_ASMERR_OPE_NUMBER;
		return FALSE;
	}

	WORD codeGR;
	if (!ParseGR(params[0], codeGR))
	{
		m_errorId = IDS_ASMERR_OPE_FORMAT1ERR;
		return FALSE;
	}

	WORD codeAddr;
	if (!ParseAddr(params[1], codeAddr))
	{
		switch (m_errorId)
		{
		case IDS_ASMERR_OPE_BADDIGITFMT:
			m_errorId = IDS_ASMERR_OPE_BADDIGITFMT2;
			break;
		case IDS_ASMERR_OPE_BADLABEL:
			m_errorId = IDS_ASMERR_OPE_BADLABEL2;
			break;
		case IDS_ASMERR_OPE_UNDEF_LABEL:
			m_errorId = IDS_ASMERR_OPE_UNDEF_LABEL2;
			break;
		default:
			m_errorId = IDS_ASMERR_OPE_FORMAT2ERR;
			break;
		}
		return FALSE;
	}

	WORD codeXR = COMET_GRNULL;
	if (nParam == 3)
	{
		if (!ParseXR(params[2], codeXR))
		{
			m_errorId = IDS_ASMERR_OPE_FORMAT3ERR;
			return FALSE;
		}
	}

	m_code[0] &= 0xff00;
	m_code[0] |= ((codeGR << 4) | codeXR);
	m_code[1] = codeAddr;

	return TRUE;
}

BOOL CMnemonic::ParseGR(LPCSTR param, WORD& code)
{
	CString strReg(param);
	if (strReg.GetLength() != 3)
		return FALSE;

	if (strReg.Left(2) != "GR")
		return FALSE;

	if (strReg[2] < '0' || strReg[2] > '7')
		return FALSE;

	code = strReg[2] - '0';
	return TRUE;

}

BOOL CMnemonic::ParseAddr(LPCSTR param, WORD &code)
{
	CString strAddr(param);
	int nLeng = strAddr.GetLength();
	if (nLeng == 0)
		return FALSE;

	char chFirst = strAddr[0];
	if (chFirst >= 'A' && chFirst <= 'Z')
	{
		// ラベル定数
		if (!GetLabelValue(strAddr, code))
			return FALSE;
	}
	else if (chFirst == '=')
	{
		// リテラル
		if (!GetLiteralValue((LPCSTR)strAddr + 1, code))
			return FALSE;
	}
	else if (chFirst == '#')
	{
		// 16進数定数
		if (nLeng != 5)
		{
			m_errorId = IDS_ASMERR_OPE_BADHEXFMT;
			return FALSE;
		}
		for (int i = 1; i < 5; i++)
		{
			char ch = strAddr[i];
			if (!(isdigit(ch) || (ch >= 'A' && ch <= 'F')))
			{
				m_errorId = IDS_ASMERR_OPE_BADHEXFMT;
				return FALSE;
			}
		}
		char* endptr;
		code = (WORD)strtoul(((LPCSTR)strAddr) + 1, &endptr, 16);
	}
	else
	{
		// 10進数定数
		LPCSTR nptr = strAddr;
		char* endptr;
		code = (WORD)strtol(nptr, &endptr, 10);
		if (endptr - nptr != nLeng)
		{
			m_errorId = IDS_ASMERR_OPE_BADDIGITFMT;
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CMnemonic::ParseXR(LPCSTR param, WORD &code)
{
	CString strReg(param);
	if (strReg.GetLength() != 3)
		return FALSE;

	if (strReg.Left(2) != "GR")
		return FALSE;

	if (strReg[2] < '1' || strReg[2] > '7')
		return FALSE;

	code = strReg[2] - '0';
	return TRUE;

}


BOOL CMnemonic::AnalyzeOperand_adrXR()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	int nParam = params.GetSize();
	if (nParam != 1 && nParam != 2)
	{
		m_errorId = IDS_ASMERR_OPE_NUMBER;
		return FALSE;
	}

	WORD codeAddr;
	if (!ParseAddr(params[0], codeAddr))
	{
		switch (m_errorId)
		{
		case IDS_ASMERR_OPE_BADDIGITFMT:
			m_errorId = IDS_ASMERR_OPE_BADDIGITFMT1;
			break;
		case IDS_ASMERR_OPE_BADLABEL:
			m_errorId = IDS_ASMERR_OPE_BADLABEL1;
			break;
		case IDS_ASMERR_OPE_UNDEF_LABEL:
			m_errorId = IDS_ASMERR_OPE_UNDEF_LABEL1;
			break;
		default:
			m_errorId = IDS_ASMERR_OPE_FORMAT1ERR;
			break;
		}
		return FALSE;
	}

	WORD codeXR = COMET_GRNULL;
	if (nParam == 2)
	{
		if (!ParseXR(params[1], codeXR))
		{
			m_errorId = IDS_ASMERR_OPE_FORMAT2ERR;
			return FALSE;
		}
	}

	m_code[0] &= 0xff00;
	m_code[0] |= ((COMET_GRNULL << 4) | codeXR);
	m_code[1] = codeAddr;

	return TRUE;
}

BOOL CMnemonic::AnalyzeOperand_GR()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	int nParam = params.GetSize();
	if (nParam != 1)
	{
		m_errorId = IDS_ASMERR_OPE_NUMBER;
		return FALSE;
	}

	WORD codeGR;
	if (!ParseGR(params[0], codeGR))
	{
		m_errorId = IDS_ASMERR_OPE_FORMATERR;
		return FALSE;
	}

	m_code[0] &= 0xff00;
	m_code[0] |= ((codeGR << 4) | COMET_GRNULL);
	m_code[1] = 0x0000;

	return TRUE;
}

BOOL CMnemonic::AnalyzeOperand_GRGR()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	int nParam = params.GetSize();
	if (nParam != 2)
		return FALSE;

	WORD codeGR[2];
	if (!ParseGR(params[0], codeGR[0]))
		return FALSE;
	if (!ParseGR(params[1], codeGR[1]))
		return FALSE;

	m_code[0] |= COMET_RR_BIT;		// r,r を表す
	m_code[0] |= ((codeGR[0] << 4) | codeGR[1]);

	return TRUE;

}


BOOL CMnemonic::AnalyzeOperand_NULL()
{
	CStringArray params;
	SplitOperand(m_strOperand, params);
	int nParam = params.GetSize();
	if (nParam)
	{
		m_errorId = IDS_ASMERR_OPE_NUMBER;
		return FALSE;
	}

	m_code[0] &= 0xff00;
	m_code[1] = 0x0000;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// CMnemonicArray クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicArray::CMnemonicArray()
{
}

CMnemonicArray::~CMnemonicArray()
{

}

void CMnemonicArray::DeleteAll()
{
	for (int i = 0; i < GetSize(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)GetAt(i);
		delete pMnemonic;
	}
	RemoveAll();
}

BOOL CMnemonicArray::IsBreakpointAddress(WORD address)
{
	for (int i = 0; i < GetSize(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)GetAt(i);
		if (pMnemonic->GetAddress() == address && pMnemonic->IsBreakPoint())
			return TRUE;
	}
	return FALSE;
}


void CMnemonicArray::ClearAllBreakPoint()
{
	for (int i = 0; i < GetSize(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)GetAt(i);
		pMnemonic->SetBreakPoint(FALSE);
	}
}

void CMnemonicArray::OutputCode(CMemory *pMemory)
{
	for (int i = 0; i < GetSize(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)GetAt(i);
		pMnemonic->Output(pMemory);
	}

}

CMnemonic* CMnemonicArray::FindExecutable(WORD adddress)
{
	for (int i = 0; i < GetSize(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)GetAt(i);
		if (pMnemonic->GetAddress() == adddress && pMnemonic->IsExecutable())
			return pMnemonic;
	}
	return FALSE;
}

BOOL CMnemonic::Execute(CRegister *pRegister, CMemory *pMemory, CMightyCaslDoc *pDocument)
{
	if (!CheckExecuteCode(pMemory))
	{
		AfxMessageBox(IDS_RUNERR_CODECHANGED, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!ExecuteCode(pRegister, pMemory, pDocument))
		return FALSE;

	pRegister->SetValue(REG_PC, GetNextPCAddress());
	return TRUE;
}

void CMnemonic::SetTraceBreakPoint(CCometCore *pCometCore)
{
	pCometCore->SetTemporaryBreakPoint(m_address + m_codeSize);
}

void CMnemonic::SetPassBreakPoint(CCometCore *pCometCore)
{
	SetTraceBreakPoint(pCometCore);
}


void CMnemonicComment::SetTraceBreakPoint(CCometCore* pCometCore)
{
	pCometCore->ClearTemporaryBreakPoint();
}

void CMnemonic::EvalOperand_GR(CRegister *pRegister, CMemory *pMemory, WORD &value)
{
	int gr = (m_code[0] & 0x00f0) >> 4;
	value = pRegister->GetValue(gr);
}

void CMnemonic::EvalOperand_GR2(CRegister *pRegister, CMemory *pMemory, WORD &value)
{
	int gr = m_code[0] & 0x000f;
	value = pRegister->GetValue(gr);
}

void CMnemonic::EvalOperand_GR1GR2(CRegister* pRegister, CMemory* pMemory, WORD& value1, WORD& value2)
{
	EvalOperand_GR(pRegister, pMemory, value1);
	EvalOperand_GR2(pRegister, pMemory, value2);
}

void CMnemonic::EvalOperand_adrXRImm(CRegister *pRegister, CMemory *pMemory, WORD &value)
{
	value = m_code[1];

	int xr = m_code[0] & 0x000f;
	if (xr != COMET_GRNULL)
		value += pRegister->GetValue(xr);
}

void CMnemonic::EvalOperand_adrXR(CRegister *pRegister, CMemory *pMemory, WORD &value)
{
	EvalOperand_adrXRImm(pRegister, pMemory, value);
	value = pMemory->GetMemory(value);
}

void CMnemonic::EvalOperand_GRadrXRImm(CRegister *pRegister, CMemory *pMemory, WORD &value1, WORD &value2)
{
	EvalOperand_GR(pRegister, pMemory, value1);
	EvalOperand_adrXRImm(pRegister, pMemory, value2);
}

void CMnemonic::EvalOperand_GRadrXR(CRegister *pRegister, CMemory *pMemory, WORD &value1, WORD &value2)
{
	EvalOperand_GR(pRegister, pMemory, value1);
	EvalOperand_adrXR(pRegister, pMemory, value2);
}


void CMnemonic::StoreOperand_GR(CRegister *pRegister, WORD value)
{
	int gr = (m_code[0] & 0x00f0) >> 4;
	pRegister->SetValue(gr, value);
}

void CMnemonic::StoreOperand_addrXR(CRegister *pRegister, CMemory* pMemory, WORD value)
{
	WORD addr;
	EvalOperand_adrXRImm(pRegister, pMemory, addr);
	pMemory->SetMemory(addr, value);

}

