#if !defined(AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SymbolView.h : ヘッダー ファイル
// ListVwEx.h : CListViewEx クラスのインターフェイス
//
// このクラスはレポート モードのリスト ビュー コントロールに対して
// 行全体の選択モードを提供します。
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// このソース コードは Microsoft Foundation Class リファレンスおよび、
// 関連するオンライン ドキュメントの補足のみを目的としています。
// Microsoft Foundation Class 製品に関する詳しい情報はこれらのドキュメント
// を参照してください。
//

class CListViewEx : public CListView
{
	DECLARE_DYNCREATE(CListViewEx)

// 構築
public:
	CListViewEx();

// アトリビュート
protected:
	BOOL m_bFullRowSel;

public:
	BOOL SetFullRowSel(BOOL bFillRowSel);
	BOOL GetFullRowSel();

	BOOL m_bClientWidthSel;

// オーバーライド
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CListViewEx)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CListViewEx();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void RepaintSelectedItems();

// インプリメンテーション - クライアント領域の幅
	int m_cxClient;

// インプリメンテーション - 状態表示のアイコンの幅
	int m_cxStateImageOffset;
	afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);

// インプリメンテーション - リスト ビューの色
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);

// 生成されたメッセージ マップ関数
protected:
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	virtual void PreDrawItem(int nItem, LV_ITEM* pLVI);
	//{{AFX_MSG(CListViewEx)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
