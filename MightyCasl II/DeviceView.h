#if !defined(AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_)
#define AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceView.h : ヘッダー ファイル
//
class CMightyCaslDoc;
/////////////////////////////////////////////////////////////////////////////
// CDeviceView ビュー

class CDeviceView : public CEditView
{
protected:
	CDeviceView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CDeviceView)

// アトリビュート
public:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CDeviceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CDeviceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	void AppendString(LPCSTR);
	CFont m_font;
	//{{AFX_MSG(CDeviceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // MightyCaslView.cpp ファイルがデバッグ環境の時使用されます。
inline CMightyCaslDoc* CDeviceView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_)
