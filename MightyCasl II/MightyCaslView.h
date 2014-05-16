// MightyCaslView.h : CMightyCaslView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGHTYCASLVIEW_H__788E89CE_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_MIGHTYCASLVIEW_H__788E89CE_F9E5_11D2_BECC_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMightyCaslView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CMightyCaslView();
	DECLARE_DYNCREATE(CMightyCaslView)

// アトリビュート
public:
	CMightyCaslDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMightyCaslView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMightyCaslView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMightyCaslView)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MightyCaslView.cpp ファイルがデバッグ環境の時使用されます。
inline CMightyCaslDoc* CMightyCaslView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MIGHTYCASLVIEW_H__788E89CE_F9E5_11D2_BECC_006067202C95__INCLUDED_)
