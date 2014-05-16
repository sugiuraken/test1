// AssembleError.h: CAssembleError クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSEMBLEERROR_H__1D4D57C6_CECA_11D3_AB2E_006067202C95__INCLUDED_)
#define AFX_ASSEMBLEERROR_H__1D4D57C6_CECA_11D3_AB2E_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAssembleError  
{
public:
	void SetLineNumber(int lineNumber);
	int GetLineNumber();
	CString GetErrorMessage();
	CAssembleError(int lineNumber, LPCSTR sourceLine, LPCSTR errorMessage);
	CAssembleError(int lineNumber, LPCSTR sourceLine, int nErrorId);
	virtual ~CAssembleError();

protected:
	int m_lineNumber;
	CString m_errorMessage;
	CString m_sourceLine;
};




class CAssembleErrorArray : public CArray<CAssembleError*, CAssembleError*>
{
public:
	void DeleteAll();
	CAssembleErrorArray();
	virtual ~CAssembleErrorArray();

};

#endif // !defined(AFX_ASSEMBLEERROR_H__1D4D57C6_CECA_11D3_AB2E_006067202C95__INCLUDED_)
