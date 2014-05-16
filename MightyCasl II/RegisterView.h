#if !defined(AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterView.h : ヘッダー ファイル
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

#define REG_COLUMN_REG		0
#define REG_COLUMN_HEX		1
#define REG_COLUMN_SIGNED	2
#define REG_COLUMN_UNSIGNED	3
#define REG_COLUMN_BINARY	4
#define REG_COLUMN_CHAR		5


/////////////////////////////////////////////////////////////////////////////
// CRegisterView ビュー

class CRegisterView : public CListViewEx
{
protected:
	CRegisterView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CRegisterView)

// アトリビュート
public:
protected:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CRegisterView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CFont m_font;
	CSize m_fontSize;
	virtual ~CRegisterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);

	// 生成されたメッセージ マップ関数
protected:
	void ModifyRegister();
	CRegister* GetRegister();
	CLabelBank* GetLabelBank();
	//{{AFX_MSG(CRegisterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CRegisterView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
