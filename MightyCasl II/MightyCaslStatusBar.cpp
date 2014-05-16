// MightyCaslStatusBar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "MightyCaslStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslStatusBar

CMightyCaslStatusBar::CMightyCaslStatusBar()
{
}

CMightyCaslStatusBar::~CMightyCaslStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMightyCaslStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CMightyCaslStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMightyCaslStatusBar メッセージ ハンドラ

int CMightyCaslStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_meter.Create(WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 101);
	m_meter.SetRange(0, 1000);
	m_meter.SetPos(0);
	m_meter.SetStep(1);
	
	return 0;
}

void CMightyCaslStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	
	int nIndex = CommandToIndex(ID_INDICATOR_PROGRESS);
    if (nIndex == -1)
		return;

	CRect rect;
	GetItemRect(nIndex, &rect);
	m_meter.MoveWindow(rect);
}
