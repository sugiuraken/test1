#if !defined(AFX_MIGHTYCASLFRAME_H__C0B76CA9_B658_11D3_AB2D_006067202C95__INCLUDED_)
#define AFX_MIGHTYCASLFRAME_H__C0B76CA9_B658_11D3_AB2D_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MightyCaslFrame.h : ヘッダー ファイル
//
#include "ChildFrm.h"
#include "HorzSplitterWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslFrame フレーム

class CMightyCaslFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CMightyCaslFrame)
protected:
	CMightyCaslFrame();           // 動的生成に使用されるプロテクト コンストラクタ。

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します

	//{{AFX_VIRTUAL(CMightyCaslFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	void ExchangeWorkView(CRuntimeClass* pNewViewClass);
	virtual ~CMightyCaslFrame();
	void BackupWindowPos();
	void RestoreWindowPos();

	CSplitterWnd m_wndSplitterHorz;
	CSplitterWnd m_wndSplitterVert;
	CSplitterWnd m_wndSplitterLeft;
	CSplitterWnd m_wndSplitterRight;
//	CHorzSplitterWnd m_wndSplitterShelf;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMightyCaslFrame)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnDestroy();
	afx_msg void OnBreakpointAllclear();
	afx_msg void OnRegisterSet();
	afx_msg void OnExecuteGo();
	afx_msg void OnExecuteTrace();
	afx_msg void OnExecutePass();
	afx_msg void OnExecuteReload();
	afx_msg void OnUpdateWorkviewDump(CCmdUI* pCmdUI);
	afx_msg void OnWorkviewDump();
	afx_msg void OnUpdateWorkviewOutput(CCmdUI* pCmdUI);
	afx_msg void OnWorkviewOutput();
	afx_msg void OnUpdateWorkviewWatch(CCmdUI* pCmdUI);
	afx_msg void OnWorkviewWatch();
	afx_msg void OnUpdateWatchNew(CCmdUI* pCmdUI);
	afx_msg void OnWatchNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MIGHTYCASLFRAME_H__C0B76CA9_B658_11D3_AB2D_006067202C95__INCLUDED_)
