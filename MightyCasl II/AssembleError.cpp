// AssembleError.cpp: CAssembleError クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "AssembleError.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAssembleError::CAssembleError(int lineNumber, LPCSTR sourceLine, LPCSTR errorMessage)
: m_sourceLine(sourceLine), m_errorMessage(errorMessage)
{
	m_lineNumber = lineNumber;
}

CAssembleError::CAssembleError(int lineNumber, LPCSTR sourceLine, int nErrorId)
: m_sourceLine(sourceLine)
{
	m_lineNumber = lineNumber;
	m_errorMessage.LoadString(nErrorId);
}

CAssembleError::~CAssembleError()
{

}

//////////////////////////////////////////////////////////////////////
// CAssembleErrorArray クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAssembleErrorArray::CAssembleErrorArray()
{

}

CAssembleErrorArray::~CAssembleErrorArray()
{

}

void CAssembleErrorArray::DeleteAll()
{
	for (int i = 0; i < GetSize(); i++)
	{
		CAssembleError* pError = (CAssembleError*)GetAt(i);
		delete pError;
	}
	RemoveAll();
}

CString CAssembleError::GetErrorMessage()
{
	CString msg;
	if (m_lineNumber != -1)
		msg.Format("ERROR #%d: %s", m_lineNumber, m_errorMessage);
	else
		msg.Format("ERROR : %s", m_errorMessage);
	return msg;
}

int CAssembleError::GetLineNumber()
{
	return m_lineNumber;
}

void CAssembleError::SetLineNumber(int lineNumber)
{
	m_lineNumber = lineNumber;
}
