#if !defined(AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_)
#define AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// COutputView ビュー

class COutputView : public CEditView
{
protected:
	COutputView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(COutputView)

// アトリビュート
public:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(COutputView)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~COutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	void AdjustErrorLineNumber(int nLine, int deltaLine);
	CFont m_font;
	CAssembleErrorArray* m_pErrors;
	void DisplayErrors();
	//{{AFX_MSG(COutputView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MightyCaslView.cpp ファイルがデバッグ環境の時使用されます。
inline CMightyCaslDoc* COutputView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_)
