#if !defined(AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_)
#define AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HorzSplitterWnd.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd ウィンドウ

class CHorzSplitterWnd : public CSplitterWnd
{
// コンストラクション
public:
	CHorzSplitterWnd();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CHorzSplitterWnd)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CHorzSplitterWnd();

protected:
	virtual void TrackRowSize(int y, int row);
	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CHorzSplitterWnd)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_)
