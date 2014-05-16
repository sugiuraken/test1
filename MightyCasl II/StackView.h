#if !defined(AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackView.h : ヘッダー ファイル
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CStackView ビュー

class CStackView : public CListViewEx
{
protected:
	CStackView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CStackView)

// アトリビュート
public:
protected:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CStackView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CStackView();
	CRegister* GetRegister();
	CMemory* GetMemory();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CFont m_font;
	CSize m_fontSize;
	CImageList m_imageIcon;

	// 生成されたメッセージ マップ関数
protected:
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	virtual void PreDrawItem(int nItem, LV_ITEM* pLVI);
	//{{AFX_MSG(CStackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CStackView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
