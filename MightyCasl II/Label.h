// Label.h: CLabel クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABEL_H__E3260D23_CF88_11D3_AB2E_006067202C95__INCLUDED_)
#define AFX_LABEL_H__E3260D23_CF88_11D3_AB2E_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLabel  
{
public:
	static UINT CheckLabelFormat(LPCSTR name);
	WORD m_value;
	CString m_name;
	CLabel(LPCSTR name, WORD value);
	virtual ~CLabel();

};


class CLabelBank : public CTypedPtrMap<CMapStringToPtr, CString, CLabel*>
{
public:
	BOOL Regist(LPCSTR name, WORD value);
	BOOL RegistLiteralLabel(WORD address, WORD value);

	UINT GetLastError();
	void DeleteAll();
	CLabelBank();
	virtual ~CLabelBank();

protected:
	UINT m_lastErrorId;
};

#endif // !defined(AFX_LABEL_H__E3260D23_CF88_11D3_AB2E_006067202C95__INCLUDED_)
