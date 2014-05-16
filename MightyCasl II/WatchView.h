#if !defined(AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchView.h : ヘッダー ファイル
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CWatchView ビュー

class CWatchView : public CListViewEx
{
protected:
	CWatchView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CWatchView)

// アトリビュート
public:
protected:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:
	void AddWatch(LPCSTR szTarget = NULL);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CWatchView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CFont m_font;
	CSize m_fontSize;
	COleDropTarget m_dropTarget;
	DROPEFFECT m_dropEffect;

	virtual ~CWatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CLabelBank* GetLabelBank();
	CWatchList* GetWatchList();
	CRegister* GetRegister();
	CMemory* GetMemory();

	// 生成されたメッセージ マップ関数
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	void ModifyWatch();
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	void InsertWatchItem(CWatchInfo* pInfo);
	//{{AFX_MSG(CWatchView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateWatchModify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWatchClear(CCmdUI* pCmdUI);
	afx_msg void OnWatchClear();
	afx_msg void OnWatchModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CWatchView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
