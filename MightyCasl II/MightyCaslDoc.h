// MightyCaslDoc.h : CMightyCaslDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_

#include "CometCore.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Assembler.h"
#include "WatchInfo.h"	// ClassView によって追加されました。

class CMightyCaslDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CMightyCaslDoc();
	DECLARE_DYNCREATE(CMightyCaslDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMightyCaslDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void CloseDeviceFiles();
	BOOL OutputDevice(LPCSTR output);
	BOOL InputDevice(CString& input);
	CWatchList m_watchList;
	void ExecuteProgram(int mode, WORD breakAddr = 0x0000);
	CView* GetTargetView(LPCSTR className);
	void ResetCore();
	CAssembler m_assembler;
	CCometCore m_cometCore;
	CString m_sourceFileName;
	CStringArray m_strDeviceAccess;

	virtual ~CMightyCaslDoc();
	BOOL Assemble();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	CStdioFile* m_pOutputFile;
	CStdioFile* m_pInputFile;
	CStringArray m_sourceLine;
	//{{AFX_MSG(CMightyCaslDoc)
	afx_msg void OnExexuteStop();
	afx_msg void OnUpdateExexuteStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_)
