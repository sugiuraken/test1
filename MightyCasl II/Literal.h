// Literal.h: CLiteral クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LITERAL_H__268DCF8C_6430_4DA4_A127_CB37CC3BB1FA__INCLUDED_)
#define AFX_LITERAL_H__268DCF8C_6430_4DA4_A127_CB37CC3BB1FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMemory;

class CLiteral  
{
protected:
	WORD m_address;
	CUIntArray m_words;
public:
	CLiteral(WORD address, CUIntArray& words);
	virtual ~CLiteral() {}
	WORD GetAddress() {return m_address;}

	void OutputCode(CMemory* pMemory);
};

class CLiteralBank : public CTypedPtrArray<CPtrArray, CLiteral*>
{
public:
	UINT GetLastError();
	void DeleteAll();

	CLiteralBank();
	virtual ~CLiteralBank();
	CLiteral* AppendLiteral(LPCSTR literal);
	void SetTopAddress(WORD address) {m_curAddress = address;}
	void OutputCode(CMemory* pMemory);
protected:
	UINT m_lastErrorId;
	WORD m_curAddress;
};


#endif // !defined(AFX_LITERAL_H__268DCF8C_6430_4DA4_A127_CB37CC3BB1FA__INCLUDED_)
