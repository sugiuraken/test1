// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MightyCasl.h"
#include "MightyCaslDoc.h"
#include "SourceView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CARET, OnUpdateIndicatorCaret)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_PROGRESS,
	ID_INDICATOR_CARET,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	m_bProgramExecuting	= FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // 作成に失敗
	}

	// TODO: ツール バーをドッキング可能にしない場合は以下の３行を削除
	//       してください。
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	RestoreWindowPos();

	DragAcceptFiles();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ


void CMainFrame::OnDestroy() 
{
	CMDIFrameWnd::OnDestroy();
	
	BackupWindowPos();	
}


void CMainFrame::RestoreWindowPos()
{
	CWinApp* pApp = AfxGetApp();

	WINDOWPLACEMENT wp;
	memset(&wp, 0, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);
	
	if (!GetWindowPlacement(&wp))
		return;

	BOOL showMaximaized;
	CString strTemp;
	strTemp = pApp->GetProfileString(REG_ENTRY_WINDOW, REG_KEY_MAINFRAME);
	if (sscanf(strTemp, "%d %d %d %d %d",
						&wp.rcNormalPosition.left,
						&wp.rcNormalPosition.top,
						&wp.rcNormalPosition.right,
						&wp.rcNormalPosition.bottom,
						&showMaximaized) != 5)
		return;

//	if (showMaximaized)
//		wp.showCmd = SW_SHOWMAXIMIZED;
	SetWindowPlacement(&wp);
}

void CMainFrame::BackupWindowPos()
{
	BOOL showMaximaized = FALSE;
	if (IsZoomed())
		showMaximaized = TRUE;


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
	pApp->WriteProfileString(REG_ENTRY_WINDOW, REG_KEY_MAINFRAME, strTemp);

}

void CMainFrame::OnUpdateIndicatorCaret(CCmdUI* pCmdUI) 
{
	CSourceView* pSourceView = NULL;
	CFrameWnd* pChildFrame = GetActiveFrame();
	if (pChildFrame)
	{
		CMightyCaslDoc* pDocument = (CMightyCaslDoc*)pChildFrame->GetActiveDocument();
		if (pDocument)
			pSourceView = (CSourceView*)pDocument->GetTargetView("CSourceView");
	}
	if (pSourceView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		pCmdUI->Enable(TRUE);
		int nLine, nCol;
		pSourceView->GetCaretPosition(nLine, nCol);
		CString strTemp;
		strTemp.Format("%3d行 / %3d列", nLine, nCol);
		pCmdUI->SetText(strTemp);
	}
}

void CMainFrame::StepProgress()
{
	m_wndStatusBar.GetProgressCtrl().StepIt();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (m_bProgramExecuting == TRUE)
	{ 
		if (nID >= 0x8000 && nID <= 0xEFFF)
		{
			if (nCode == CN_UPDATE_COMMAND_UI) 
			{
				CCmdUI* pCmdUI = (CCmdUI*)pExtra;
				pCmdUI->Enable(nID == ID_EXEXUTE_STOP ? TRUE : FALSE);
				return TRUE;
			}
		}
	}	

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::PreProgramExecute()
{
	m_bProgramExecuting = TRUE;

	CWnd* pMDIClientWnd = CWnd::FromHandle(m_hWndMDIClient);
	CWnd* pChildWnd = pMDIClientWnd->GetWindow(GW_CHILD);
	if (pChildWnd)
	{
		CWnd* pWnd = pChildWnd->GetWindow(GW_HWNDFIRST);
		while (pWnd)
		{
			pWnd->EnableWindow(FALSE);
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	CMenu* pMenu = GetSystemMenu(FALSE);
	pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
}

void CMainFrame::PostProgramExecute()
{
	m_wndStatusBar.GetProgressCtrl().SetPos(0);

	CMenu* pMenu = GetSystemMenu(FALSE);
	pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);

	CWnd* pMDIClientWnd = CWnd::FromHandle(m_hWndMDIClient);
	CWnd* pChildWnd = pMDIClientWnd->GetWindow(GW_CHILD);
	if (pChildWnd)
	{
		CWnd* pWnd = pChildWnd->GetWindow(GW_HWNDFIRST);
		while (pWnd)
		{
			pWnd->EnableWindow(TRUE);
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
	}
	m_bProgramExecuting = FALSE;
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	//ドロップされたファイルの個数を取得
	UINT uiCount = DragQueryFile(hDropInfo, ~0lu, NULL, 0);

	CString strFileName;
	for (UINT i = 0; i < uiCount; i++)
	{
		//ファイル名の長さを取得
		UINT uiLen = DragQueryFile(hDropInfo, i, NULL, 0);

		//ファイル名を取得
		DragQueryFile(hDropInfo, i, strFileName.GetBuffer(uiLen + 1), uiLen + 1);
		strFileName.ReleaseBuffer();

		break;			// 1つだけ
	}
	if (!strFileName.IsEmpty())
		AfxGetApp()->OpenDocumentFile(strFileName);

	CMDIFrameWnd::OnDropFiles(hDropInfo);
}
