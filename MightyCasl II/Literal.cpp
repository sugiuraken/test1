// Literal.cpp: CLiteral クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "Literal.h"
#include "Memory.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CLiteral::CLiteral(WORD address, CUIntArray& words)
{
	m_address = address;
	for (int i = 0; i < words.GetSize(); i++)
		m_words.Add(words[i]);
}

void CLiteral::OutputCode(CMemory* pMemory)
{
	for (int i = 0; i < m_words.GetSize(); i++)
		pMemory->SetMemory(m_address + i, m_words[i]);
}



//////////////////////////////////////////////////////////////


CLiteralBank::CLiteralBank()
{
	m_lastErrorId = 0;
}

CLiteralBank::~CLiteralBank()
{
	DeleteAll();
}

void CLiteralBank::DeleteAll()
{
	for (int i = 0; i < GetSize(); i++)
		 delete GetAt(i);
	RemoveAll();
}

UINT CLiteralBank::GetLastError()
{
	return m_lastErrorId;
}

CLiteral* CLiteralBank::AppendLiteral(LPCSTR literal)
{
	CUIntArray words;
	CString strLiteral(literal);

	if (strLiteral.IsEmpty())
	{
		m_lastErrorId = IDS_ASMERR_LIT_NOTHING;
		return FALSE;
	}

	int nLeng = strLiteral.GetLength();
	char chFirst = strLiteral[0];
	if (chFirst == '\'')
	{
		// 文字定数
		int nPos = strLiteral.Find('\'', 1);
		if (nPos == -1 || nPos != nLeng - 1)
		{
			m_lastErrorId = IDS_ASMERR_LIT_BADSTRFMT;
			return FALSE;
		}
		if (nLeng <= 2)
		{
			m_lastErrorId = IDS_ASMERR_LIT_NULLSTR;
			return FALSE;
		}

		for (int i = 1; i <  nLeng - 1; i++)
			words.Add(strLiteral[i]);
	}
	else if (chFirst == '#')
	{
		// 16進数定数
		if (nLeng != 5)
		{
			m_lastErrorId = IDS_ASMERR_LIT_BADHEXFMT;
			return FALSE;
		}
		for (int i = 1; i < 5; i++)
		{
			char ch = strLiteral[i];
			if (!(isdigit(ch) || (ch >= 'A' && ch <= 'F')))
			{
				m_lastErrorId = IDS_ASMERR_LIT_BADHEXFMT;
				return FALSE;
			}
		}
		char* endptr;
		WORD value = (WORD)strtoul(((LPCSTR)strLiteral) + 1, &endptr, 16);
		words.Add(value);
	}
	else
	{
		// 10進数定数
		LPCSTR nptr = strLiteral;
		char* endptr;
		WORD value = (WORD)strtol(nptr, &endptr, 10);
		if (endptr - nptr != nLeng)
		{
			m_lastErrorId = IDS_ASMERR_LIT_BADDIGITFMT;
			return FALSE;
		}
		words.Add(value);
	}

	CLiteral* pLiteral = new CLiteral(m_curAddress, words);
	Add(pLiteral);
	m_curAddress += words.GetSize();

	return pLiteral;
}


void CLiteralBank::OutputCode(CMemory* pMemory)
{
	for (int i = 0; i < GetSize(); i++)
	{
		CLiteral* pLiteral = GetAt(i);
		pLiteral->OutputCode(pMemory);
	}
}

