// WatchInfo.h: CWatchInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATCHINFO_H__6AAC80A0_DEA0_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_WATCHINFO_H__6AAC80A0_DEA0_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WATCHFMT_HEX		0
#define WATCHFMT_SIGNED		1
#define WATCHFMT_UNSIGNED	2
#define WATCHFMT_BINARY		3
#define WATCHFMT_CHAR		4


class CWatchInfo  
{
public:
	CString m_target;
	int m_length;
	int m_fmt;
public:
	CWatchInfo(LPCSTR target, int length, int fmt);
	virtual ~CWatchInfo();
};

class CWatchList : public CList<CWatchInfo*, CWatchInfo*>
{
public:
	void DeleteAll();
	CWatchList();
	virtual ~CWatchList();
};

#endif // !defined(AFX_WATCHINFO_H__6AAC80A0_DEA0_11D3_AB2F_006067202C95__INCLUDED_)
