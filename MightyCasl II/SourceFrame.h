#if !defined(AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_)
#define AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceFrame.h : ヘッダー ファイル
//
#include "ChildFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CSourceFrame フレーム

class CSourceFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CSourceFrame)
protected:
	CSourceFrame();           // 動的生成に使用されるプロテクト コンストラクタ。

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します

	//{{AFX_VIRTUAL(CSourceFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CSplitterWnd m_wndSplitter;
	virtual ~CSourceFrame();

	void BackupWindowPos();
	void RestoreWindowPos();
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSourceFrame)
	afx_msg void OnToolAsm();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_)
