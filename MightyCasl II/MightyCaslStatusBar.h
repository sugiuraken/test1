#if !defined(AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_)
#define AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MightyCaslStatusBar.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslStatusBar ウィンドウ

class CMightyCaslStatusBar : public CStatusBar
{
// コンストラクション
public:
	CMightyCaslStatusBar();

// アトリビュート
public:
	CProgressCtrl& GetProgressCtrl() {return m_meter;}
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CMightyCaslStatusBar)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMightyCaslStatusBar();

	// 生成されたメッセージ マップ関数
protected:
	CProgressCtrl m_meter;
	//{{AFX_MSG(CMightyCaslStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_)
