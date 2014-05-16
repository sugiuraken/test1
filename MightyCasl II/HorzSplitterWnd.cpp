// HorzSplitterWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "HorzSplitterWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd

CHorzSplitterWnd::CHorzSplitterWnd()
{
}

CHorzSplitterWnd::~CHorzSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CHorzSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CHorzSplitterWnd)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHorzSplitterWnd::TrackRowSize(int y, int row)
{
	// スプリッタを上下に移動したときに
	int saveSize = m_pRowInfo[row].nIdealSize;
	CSplitterWnd::TrackRowSize(y, row);
	m_pRowInfo[row + 1].nIdealSize += saveSize - m_pRowInfo[row].nIdealSize;      // new size
}
/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd メッセージ ハンドラ
