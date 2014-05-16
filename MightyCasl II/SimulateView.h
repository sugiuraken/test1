#if !defined(AFX_SIMULATEVIEW_H__BC498C47_D936_11D3_BD8B_0000E8647D2D__INCLUDED_)
#define AFX_SIMULATEVIEW_H__BC498C47_D936_11D3_BD8B_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimulateView.h : ヘッダー ファイル
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

#define ICONOVERLAY_SIMULATE_PC	1

#define ICON_SIMULATE_NORMAL	2
#define ICON_SIMULATE_BREAK		3

/////////////////////////////////////////////////////////////////////////////
// CSimulateView ビュー

class CSimulateView : public CListViewEx
{
protected:
	CSimulateView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CSimulateView)

// アトリビュート
public:
protected:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSimulateView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	COleDropTarget m_dropTarget;
	DROPEFFECT m_dropEffect;
	CImageList m_imageIcon;
	CFont m_font;
	CSize m_fontSize;
	CRegister* GetRegister();
	CMemory* GetMemory();
	virtual ~CSimulateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	void SetPcAtLine();
	void EnsureVisibleAddress(WORD address);
	void EnsureVisibleCurPC();
	virtual void PreDrawItem(int nItem, LV_ITEM* pLVI);
	void InsertListItem();
	CMnemonicArray* GetMnemonics();
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CSimulateView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBreakpointSet();
	afx_msg void OnUpdateBreakpointSet(CCmdUI* pCmdUI);
	afx_msg void OnExecuteCome();
	afx_msg void OnUpdateExecuteCome(CCmdUI* pCmdUI);
	afx_msg void OnRegisterPc();
	afx_msg void OnUpdateRegisterPc(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CSimulateView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMULATEVIEW_H__BC498C47_D936_11D3_BD8B_0000E8647D2D__INCLUDED_)
