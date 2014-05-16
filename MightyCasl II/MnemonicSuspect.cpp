// MnemonicSuspect.cpp: CMnemonicSTART クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MnemonicSuspect.h"
#include "Assembler.h"
#include "CometCore.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMnemonicSTART::CMnemonicSTART(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
	m_startAddress = m_address;
}

CMnemonicSTART::~CMnemonicSTART()
{

}

BOOL CMnemonicSTART::Assemble()
{
	if (m_pAssembler->m_nStart > m_pAssembler->m_nEnd)
	{
		m_errorId = IDS_ASMERR_MULTI_START;
		return FALSE;
	}

	if ((m_pAssembler->m_nStart == 0) && (m_address != USER_PROGRAM_BEGIN_ADDRESS))
	{
		m_errorId = IDS_ASMERR_ILLEGAL_START;
		return FALSE;
	}

	m_pAssembler->m_nStart++;

	if (!m_strOperand.IsEmpty())
	{
		if (!GetLabelValue(m_strOperand, m_startAddress))
			return FALSE;
	}

//	if (m_pAssembler->m_nStart == 1)
//		m_pAssembler->m_startAddress = m_startAddress;
	return TRUE;
}

void CMnemonicSTART::SetTraceBreakPoint(CCometCore* pCometCore)
{
	pCometCore->ClearTemporaryBreakPoint();
}


CMnemonicEND::CMnemonicEND(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicEND::~CMnemonicEND()
{

}

BOOL CMnemonicEND::Assemble()
{
	if (m_pAssembler->m_nStart <= m_pAssembler->m_nEnd)
	{
		m_errorId = IDS_ASMERR_MULTI_END;
		return FALSE;
	}

	m_pAssembler->m_nEnd++;

	if (!m_strOperand.IsEmpty())
	{
		m_errorId = IDS_ASMERR_OPE_SPACE;
		return FALSE;
	}

	return TRUE;
}

void CMnemonicEND::SetTraceBreakPoint(CCometCore* pCometCore)
{
	pCometCore->ClearTemporaryBreakPoint();
}

CMnemonicDC::CMnemonicDC(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicDC::~CMnemonicDC()
{

}

BOOL CMnemonicDC::Output(CMemory *pMemory)
{
	for (int i = 0; i < m_words.GetSize(); i++)
		pMemory->SetMemory(m_address + i, m_words[i]);
	return TRUE;
}

BOOL CMnemonicDC::Assemble()
{
	if (m_strOperand.IsEmpty())
	{
		m_errorId = IDS_ASMERR_OPE_NOTHING;
		return FALSE;
	}

	CStringArray params;
	SplitOperand(m_strOperand, params);

	for (int i = 0; i < params.GetSize(); i++)
	{
		CString strParam(params[i]);
		int nLeng = strParam.GetLength();
		if (nLeng == 0)
		{
			m_errorId = IDS_ASMERR_OPE_NOTHING;
			return FALSE;
		}

		char chFirst = strParam[0];
		if (chFirst == '\'')
		{
			// 文字定数
			int nPos = strParam.Find('\'', 1);
			if (nPos == -1 || nPos != nLeng - 1)
			{
				m_errorId = IDS_ASMERR_OPE_BADSTRFMT;
				return FALSE;
			}
			if (nLeng <= 2)
			{
				m_errorId = IDS_ASMERR_OPE_NULLSTR;
				return FALSE;
			}

			for (int i = 1; i <  nLeng - 1; i++)
				m_words.Add(strParam[i]);
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
				char ch = strParam[i];
				if (!(isdigit(ch) || (ch >= 'A' && ch <= 'F')))
				{
					m_errorId = IDS_ASMERR_OPE_BADHEXFMT;
					return FALSE;
				}
			}
			char* endptr;
			WORD value = (WORD)strtoul(((LPCSTR)strParam) + 1, &endptr, 16);
			m_words.Add(value);
		}
		else if (chFirst >= 'A' && chFirst <= 'Z')
		{
			// ラベル定数
			WORD value;
			if (!GetLabelValue(strParam, value))
				return FALSE;
			m_words.Add(value);
		}
		else
		{
			// 10進数定数
			LPCSTR nptr = strParam;
			char* endptr;
			WORD value = (WORD)strtol(nptr, &endptr, 10);
			if (endptr - nptr != nLeng)
			{
				m_errorId = IDS_ASMERR_OPE_BADDIGITFMT;
				return FALSE;
			}
			m_words.Add(value);
		}
	}
	return TRUE;
}

void CMnemonicDC::SetTraceBreakPoint(CCometCore* pCometCore)
{
	pCometCore->ClearTemporaryBreakPoint();
}

CMnemonicDS::CMnemonicDS(WORD address, LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine, CAssembler* pAssembler)
: CMnemonic(address, strMnemonic, strOperand, strNativeLine, pAssembler)
{
}

CMnemonicDS::~CMnemonicDS()
{

}

BOOL CMnemonicDS::Assemble()
{
	if (m_strOperand.IsEmpty())
	{
		m_errorId = IDS_ASMERR_OPE_NOTHING;
		return FALSE;
	}

	// 10進数定数（≧0)
	LPCSTR nptr = m_strOperand;
	char* endptr;
	LONG value = strtol(nptr, &endptr, 10);
	if (endptr - nptr != m_strOperand.GetLength())
	{
		m_errorId = IDS_ASMERR_OPE_BADDIGITFMT;
		return FALSE;
	}
	if (value < 0)
	{
		m_errorId = IDS_ASMERR_OPE_MUSTBEPLUS;
		return FALSE;
	}
	m_codeSize = (WORD)value;
	return TRUE;
}

void CMnemonicDS::SetTraceBreakPoint(CCometCore* pCometCore)
{
	pCometCore->ClearTemporaryBreakPoint();
}
