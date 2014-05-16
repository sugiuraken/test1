// SourceFrame.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "SourceFrame.h"
#include "MightyCaslDoc.h"
#include "SourceView.h"
#include "OutputView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceFrame

IMPLEMENT_DYNCREATE(CSourceFrame, CChildFrame)

CSourceFrame::CSourceFrame()
{
}

CSourceFrame::~CSourceFrame()
{
}


BEGIN_MESSAGE_MAP(CSourceFrame, CChildFrame)
	//{{AFX_MSG_MAP(CSourceFrame)
	ON_COMMAND(ID_TOOL_ASM, OnToolAsm)
	ON_WM_MDIACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceFrame メッセージ ハンドラ

BOOL CSourceFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_wndSplitter.CreateStatic(this, 2, 1)) 
	{
		TRACE0("Failed to create splitter wnd\n");
		return FALSE;      // 作成に失敗
	}
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSourceView), CSize(0, 0), pContext) || 
		!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(COutputView), CSize(0, 0), pContext)) 
	{
		TRACE0("Failed to create splitter view\n");
		return FALSE;      // 作成に失敗
	}

	CRect rcFrameWindow;
	GetWindowRect(rcFrameWindow);

	int heightSourceView = rcFrameWindow.Height() * 75 / 100;
	m_wndSplitter.SetRowInfo(0, heightSourceView, 0);


	RestoreWindowPos();
	m_wndSplitter.SetActivePane(0, 0);

	return TRUE;
}

void CSourceFrame::OnToolAsm() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->Assemble();		
}

void CSourceFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	if (bActivate)
	{
		CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
		pDocument->SetTitle("Source");

		CString strTemp;
		strTemp.Format("Source - %s", pDocument->m_sourceFileName);
		SetWindowText(strTemp);

	}
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}


BOOL CSourceFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~FWS_ADDTOTITLE;
	
	return CChildFrame::PreCreateWindow(cs);
}

void CSourceFrame::OnDestroy() 
{
	CChildFrame::OnDestroy();
	BackupWindowPos();	
}

void CSourceFrame::RestoreWindowPos()
{
	CWinApp* pApp = AfxGetApp();

	int cyCur, cyMin;
	m_wndSplitter.GetRowInfo(0, cyCur, cyMin);
	cyCur = pApp->GetProfileInt(REG_ENTRY_WINDOW, REG_KEY_SOURCESPLIT, -1);
	if (cyCur > 0)
		m_wndSplitter.SetRowInfo(0, cyCur, cyMin);

	WINDOWPLACEMENT wp;
	memset(&wp, 0, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);
	
	if (!GetWindowPlacement(&wp))
		return;

	BOOL showMaximaized;
	CString strTemp;
	strTemp = pApp->GetProfileString(REG_ENTRY_WINDOW, REG_KEY_SOURCEFRAME);
	if (sscanf(strTemp, "%d %d %d %d %d",
						&wp.rcNormalPosition.left,
						&wp.rcNormalPosition.top,
						&wp.rcNormalPosition.right,
						&wp.rcNormalPosition.bottom,
						&showMaximaized) != 5)
		return;

	SetWindowPlacement(&wp);
//	if (showMaximaized)
//		GetMDIFrame()->MDIMaximize(this);
}

void CSourceFrame::BackupWindowPos()
{
	BOOL showMaximaized = FALSE;
	if (IsZoomed())
	{
		ShowWindow(SW_RESTORE);
		showMaximaized = TRUE;
	}


	WINDOWPLACEMENT wp;
	memset(&wp, 0, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);

	if (!GetWindowPlacement(&wp))
		return;

	CString strTemp;
	strTemp.Format("%d %d %d %d %d", 
						wp.rcNormalPosition.left,
						wp.rcNormalPosition.top,
						wp.rcNormalPosition.right,
						wp.rcNormalPosition.bottom,
						showMaximaized);

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString(REG_ENTRY_WINDOW, REG_KEY_SOURCEFRAME, strTemp);

	int cyCur, cyMin;
	m_wndSplitter.GetRowInfo(0, cyCur, cyMin);
	pApp->WriteProfileInt(REG_ENTRY_WINDOW, REG_KEY_SOURCESPLIT, cyCur);
}

