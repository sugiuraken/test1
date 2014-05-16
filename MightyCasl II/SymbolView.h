#if !defined(AFX_SYMBOLVIEW_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_SYMBOLVIEW_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SymbolView.h : ヘッダー ファイル
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CSymbolView ビュー

class CSymbolView : public CListViewEx
{
protected:
	CSymbolView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CSymbolView)

// アトリビュート
public:
protected:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSymbolView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CSymbolView();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CFont m_font;
	CSize m_fontSize;
	int	m_nSortColumn;
	int m_nSortOrder;
	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSymbolView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CSymbolView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SYMBOLVIEW_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
