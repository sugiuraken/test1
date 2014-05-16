#if !defined(AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSourceView ビュー

class CSourceView : public CEditView
{
protected:
	CSourceView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CSourceView)

// アトリビュート
public:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:
	void GetCaretPosition(int& nLine, int& nCol);

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSourceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CSourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	int m_beforeLineCount;
	void GotoSourceLine(int nLine);
	CFont m_font;
	//{{AFX_MSG(CSourceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MightyCaslView.cpp ファイルがデバッグ環境の時使用されます。
inline CMightyCaslDoc* CSourceView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_)
