// Label.cpp: CLabel クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Label.h"
#include "Register.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CLabel::CLabel(LPCSTR name, WORD value)
: m_name(name)
{
	m_value = value;
}

CLabel::~CLabel()
{

}

//////////////////////////////////////////////////////////////////////
// CMapLabels クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CLabelBank::CLabelBank()
{
	m_lastErrorId = 0;
}

CLabelBank::~CLabelBank()
{
	DeleteAll();
}

void CLabelBank::DeleteAll()
{
	CString key;
	CLabel* pLabel;
	POSITION pos = GetStartPosition();
	while (pos)
	{
		 GetNextAssoc(pos, key, pLabel);
		 delete pLabel;
	}
	RemoveAll();
}

UINT CLabelBank::GetLastError()
{
	return m_lastErrorId;
}

BOOL CLabelBank::RegistLiteralLabel(WORD address, WORD value)
{
	CString literalLabel;
	literalLabel.Format("__%04X__", address);

	CLabel* pLabel;
	if (Lookup(literalLabel, pLabel))	// ラベルの二重定義
	{
		m_lastErrorId = IDS_ASMERR_LABEL_MULTIDEF;
		return FALSE;
	}

	SetAt(literalLabel, new CLabel(literalLabel, value));
	return TRUE;
}

BOOL CLabelBank::Regist(LPCSTR name, WORD value)
{
	int nLeng = strlen(name);
	if (nLeng == 0)
		return TRUE;

	m_lastErrorId = CLabel::CheckLabelFormat(name);
	if (m_lastErrorId)
		return FALSE;

	// 汎用レジスタ名 "GRx" はラベルに使えない
	int nRegID = CRegister::GetRegisterId(name);
	if (nRegID >= COMET_GR0 && nRegID <= COMET_GR7)
	{
		m_lastErrorId = IDS_ASMERR_LABEL_GRX;
		return FALSE;
	}

	CLabel* pLabel;
	if (Lookup(name, pLabel))	// ラベルの二重定義
	{
		m_lastErrorId = IDS_ASMERR_LABEL_MULTIDEF;
		return FALSE;
	}


	SetAt(name, new CLabel(name, value));
	return TRUE;
}

UINT CLabel::CheckLabelFormat(LPCSTR name)
{
	int nLeng = strlen(name);
	ASSERT(nLeng);

	if (nLeng > 8)		// ラベル名が長すぎる
		return IDS_ASMERR_LABEL_TOOLONG;

	if (name[0] < 'A' || name[0] > 'Z')	// 先頭文字は英大文字でなければならない
		return IDS_ASMERR_LABEL_BADFIRSTCHAR;

	for (int i = 1; i < nLeng; i++)	// 続く文字は英大文字or数字でなければならない
	{
		if (!(isdigit(name[i]) || (name[i] >= 'A' && name[i] <= 'Z')))
			return IDS_ASMERR_LABEL_BADCHAR;
	}
	return 0L;
}
