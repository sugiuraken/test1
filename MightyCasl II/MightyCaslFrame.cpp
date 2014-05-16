// MightyCaslFrame.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "MightyCaslFrame.h"

#include "SimulateView.h"
#include "RegisterView.h"
#include "StackView.h"
#include "SymbolView.h"
#include "DumpView.h"
#include "DeviceView.h"
#include "WatchView.h"

#include "RegisterDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslFrame

IMPLEMENT_DYNCREATE(CMightyCaslFrame, CChildFrame)

CMightyCaslFrame::CMightyCaslFrame()
{
}

CMightyCaslFrame::~CMightyCaslFrame()
{
}


BEGIN_MESSAGE_MAP(CMightyCaslFrame, CChildFrame)
	//{{AFX_MSG_MAP(CMightyCaslFrame)
	ON_WM_MDIACTIVATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_BREAKPOINT_ALLCLEAR, OnBreakpointAllclear)
	ON_COMMAND(ID_REGISTER_SET, OnRegisterSet)
	ON_COMMAND(ID_EXECUTE_GO, OnExecuteGo)
	ON_COMMAND(ID_EXECUTE_TRACE, OnExecuteTrace)
	ON_COMMAND(ID_EXECUTE_PASS, OnExecutePass)
	ON_COMMAND(ID_EXECUTE_RELOAD, OnExecuteReload)
	ON_UPDATE_COMMAND_UI(ID_WORKVIEW_DUMP, OnUpdateWorkviewDump)
	ON_COMMAND(ID_WORKVIEW_DUMP, OnWorkviewDump)
	ON_UPDATE_COMMAND_UI(ID_WORKVIEW_OUTPUT, OnUpdateWorkviewOutput)
	ON_COMMAND(ID_WORKVIEW_OUTPUT, OnWorkviewOutput)
	ON_UPDATE_COMMAND_UI(ID_WORKVIEW_WATCH, OnUpdateWorkviewWatch)
	ON_COMMAND(ID_WORKVIEW_WATCH, OnWorkviewWatch)
	ON_UPDATE_COMMAND_UI(ID_WATCH_NEW, OnUpdateWatchNew)
	ON_COMMAND(ID_WATCH_NEW, OnWatchNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslFrame メッセージ ハンドラ
void CMightyCaslFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	if (bActivate)
	{
		CDocument* pDocument = GetActiveDocument();
		pDocument->SetTitle("Simulator");
		SetWindowText("Simulator");
	}
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}


BOOL CMightyCaslFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~FWS_ADDTOTITLE;
	return CChildFrame::PreCreateWindow(cs);
}

BOOL CMightyCaslFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CMightyCaslApp* pApp = (CMightyCaslApp*)AfxGetApp();
	int defaultWorkView = pApp->m_environment.m_defaultWorkView;
	CRuntimeClass* pWorkView = (defaultWorkView == ENV_WORKVIEW_DUMP) ? RUNTIME_CLASS(CDumpView) :
							   (defaultWorkView == ENV_WORKVIEW_WATCH) ? RUNTIME_CLASS(CWatchView) :
																		RUNTIME_CLASS(CDeviceView);


	if (!m_wndSplitterHorz.CreateStatic(this, 2, 1) || 
			!m_wndSplitterVert.CreateStatic(&m_wndSplitterHorz, 1, 2, WS_CHILD | WS_VISIBLE, 
																	m_wndSplitterHorz.IdFromRowCol(0, 0)) ||

						!m_wndSplitterLeft.CreateStatic(&m_wndSplitterVert, 2, 1, WS_CHILD | WS_VISIBLE, 
																	m_wndSplitterVert.IdFromRowCol(0, 0)) ||

						!m_wndSplitterLeft.CreateView(0, 0, RUNTIME_CLASS(CSimulateView), CSize(0, 0), pContext) ||
						!m_wndSplitterLeft.CreateView(1, 0, RUNTIME_CLASS(CRegisterView), CSize(0, 0), pContext) ||


					!m_wndSplitterRight.CreateStatic(&m_wndSplitterVert, 2, 1, WS_CHILD | WS_VISIBLE, 
																	m_wndSplitterVert.IdFromRowCol(0, 1)) ||

						!m_wndSplitterRight.CreateView(0, 0, RUNTIME_CLASS(CStackView), CSize(0, 0), pContext) ||
						!m_wndSplitterRight.CreateView(1, 0, RUNTIME_CLASS(CSymbolView), CSize(0, 0), pContext) ||
			!m_wndSplitterHorz.CreateView(1, 0, pWorkView, CSize(0, 0), pContext))
		return FALSE;

	
	CRect rcFrameWindow;
	GetWindowRect(&rcFrameWindow);

	int heighSimulate = rcFrameWindow.Height() * 75 / 100;
	int widthSimulate = rcFrameWindow.Width() * 80 / 100;

	m_wndSplitterHorz.SetRowInfo(0, heighSimulate, 0);				// 75%
	m_wndSplitterVert.SetColumnInfo(0, widthSimulate, 0);			// 80%

	m_wndSplitterLeft.SetRowInfo(0, heighSimulate * 50 / 100, 0);		// 50%
	m_wndSplitterRight.SetRowInfo(0, heighSimulate * 30 / 100, 0);		// 30%

	RestoreWindowPos();

	return TRUE;
}

void CMightyCaslFrame::RestoreWindowPos()
{
	CWinApp* pApp = AfxGetApp();
	CString strTemp;

	int cyHorzCur, cxVertCur, cyLeftCur, cyRightCur;
	strTemp = pApp->GetProfileString(REG_ENTRY_WINDOW, REG_KEY_SIMULATESPLIT);
	if (sscanf(strTemp, "%d %d %d %d", &cyHorzCur, &cxVertCur, &cyLeftCur, &cyRightCur) != 4)
		return;

	int cyCur, cxCur;
	int cyMin, cxMin;
	m_wndSplitterHorz.GetRowInfo(0, cyCur, cyMin);
	if (cyHorzCur != -1)
		m_wndSplitterHorz.SetRowInfo(0, cyHorzCur, cyMin);

	m_wndSplitterVert.GetColumnInfo(0, cxCur, cxMin);
	if (cxVertCur != -1)
		m_wndSplitterVert.SetColumnInfo(0, cxVertCur, cxMin);

	m_wndSplitterLeft.GetRowInfo(0, cyCur, cyMin);
	if (cyLeftCur != -1)
		m_wndSplitterLeft.SetRowInfo(0, cyLeftCur, cyMin);

	m_wndSplitterRight.GetRowInfo(0, cyCur, cyMin);
	if (cyRightCur != -1)
		m_wndSplitterRight.SetRowInfo(0, cyRightCur, cyMin);

	WINDOWPLACEMENT wp;
	memset(&wp, 0, sizeof(WINDOWPLACEMENT));
	wp.length = sizeof(WINDOWPLACEMENT);
	
	if (!GetWindowPlacement(&wp))
		return;

	BOOL showMaximaized;
	strTemp = pApp->GetProfileString(REG_ENTRY_WINDOW, REG_KEY_SIMULATEFRAME);
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

void CMightyCaslFrame::BackupWindowPos()
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
	pApp->WriteProfileString(REG_ENTRY_WINDOW, REG_KEY_SIMULATEFRAME, strTemp);

	int cyHorzCur, cxVertCur, cyLeftCur, cyRightCur;
	int cyMin, cxMin;

	m_wndSplitterHorz.GetRowInfo(0, cyHorzCur, cyMin);
	m_wndSplitterVert.GetColumnInfo(0, cxVertCur, cxMin);
	m_wndSplitterLeft.GetRowInfo(0, cyLeftCur, cyMin);
	m_wndSplitterRight.GetRowInfo(0, cyRightCur, cxMin);
	
	strTemp.Format("%d %d %d %d", cyHorzCur, cxVertCur, cyLeftCur, cyRightCur);
	pApp->WriteProfileString(REG_ENTRY_WINDOW, REG_KEY_SIMULATESPLIT, strTemp);
}

void CMightyCaslFrame::OnDestroy() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->CloseDeviceFiles();

	CChildFrame::OnDestroy();
	
	BackupWindowPos();	
}

void CMightyCaslFrame::OnBreakpointAllclear() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	CMnemonicArray* pMnemonics = pDocument->m_assembler.GetMnemonics();
	pMnemonics->ClearAllBreakPoint();
	pDocument->UpdateAllViews(NULL, UPDATEHINT_CHANGE_BREAKPOINT, NULL);
}

void CMightyCaslFrame::OnRegisterSet() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	
	CRegisterDlg dlg(REG_GR0, 
					 &pDocument->m_cometCore.m_register, 
					 &pDocument->m_assembler.m_labelBank,
					 this);

	if (dlg.DoModal() == IDCANCEL)
		return;

	pDocument->UpdateAllViews(NULL, UPDATEHINT_CHANGE_REGISTER, NULL);
}

void CMightyCaslFrame::OnExecuteGo() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->ExecuteProgram(EXECUTEMODE_GO);
}

void CMightyCaslFrame::OnExecuteTrace() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->ExecuteProgram(EXECUTEMODE_TRACE);
}

void CMightyCaslFrame::OnExecutePass() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->ExecuteProgram(EXECUTEMODE_PASS);
}

void CMightyCaslFrame::OnExecuteReload() 
{
	CMightyCaslDoc* pDocument = (CMightyCaslDoc*)GetActiveDocument();
	pDocument->ResetCore();
	pDocument->UpdateAllViews(NULL, UPDATEHINT_EXEC_BREAK, NULL);
}

void CMightyCaslFrame::ExchangeWorkView(CRuntimeClass *pNewViewClass)
{
	CView* pActiveView = GetActiveView();
	CView* pOldView = (CView*)m_wndSplitterHorz.GetPane(1, 0);
	BOOL bActive = (pActiveView == pOldView);

//	pOldView->SendMessage(wm_DumpState, TRUE, (LPARAM)&m_dumpTopLineAddress);	// TRUE = save

	CCreateContext context;
	context.m_pCurrentFrame = NULL;
	context.m_pLastView = NULL;
	context.m_pCurrentDoc = pOldView->GetDocument();
	context.m_pNewDocTemplate = context.m_pCurrentDoc->GetDocTemplate();

	int cyCur, cyMin;
	int cxCur, cxMin;
	m_wndSplitterHorz.GetRowInfo(1, cyCur, cyMin);
	m_wndSplitterHorz.GetColumnInfo(0, cxCur, cxMin);

	m_wndSplitterHorz.DeleteView(1, 0);
	m_wndSplitterHorz.CreateView(1, 0, pNewViewClass, CSize(0, 0), &context);
	m_wndSplitterHorz.SetRowInfo(1, cyCur, cyMin);
	m_wndSplitterHorz.SetColumnInfo(0, cxCur, cxMin);
	m_wndSplitterHorz.RecalcLayout();

	CView* pNewView = (CView*)m_wndSplitterHorz.GetPane(1, 0);
	pNewView->SendMessage(WM_INITIALUPDATE);
	if (bActive)
		m_wndSplitterHorz.SetActivePane(1, 0, pNewView);
//	pNewView->SendMessage(wm_DumpState, FALSE, (LPARAM)&m_dumpTopLineAddress);	// FALSE = restore

}

void CMightyCaslFrame::OnUpdateWorkviewDump(CCmdUI* pCmdUI) 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	pCmdUI->SetCheck(!strcmp(className, "CDumpView") ? 1 : 0);
}

void CMightyCaslFrame::OnWorkviewDump() 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	if (strcmp(className, "CDumpView"))
		ExchangeWorkView(RUNTIME_CLASS(CDumpView));
}

void CMightyCaslFrame::OnUpdateWorkviewOutput(CCmdUI* pCmdUI) 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	pCmdUI->SetCheck(!strcmp(className, "CDeviceView") ? 1 : 0);
}

void CMightyCaslFrame::OnWorkviewOutput() 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	if (strcmp(className, "CDeviceView"))
		ExchangeWorkView(RUNTIME_CLASS(CDeviceView));
}

void CMightyCaslFrame::OnUpdateWorkviewWatch(CCmdUI* pCmdUI) 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	pCmdUI->SetCheck(!strcmp(className, "CWatchView") ? 1 : 0);
}

void CMightyCaslFrame::OnWorkviewWatch() 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	if (strcmp(className, "CWatchView"))
		ExchangeWorkView(RUNTIME_CLASS(CWatchView));
}

void CMightyCaslFrame::OnUpdateWatchNew(CCmdUI* pCmdUI) 
{
	LPCSTR className = m_wndSplitterHorz.GetPane(1, 0)->GetRuntimeClass()->m_lpszClassName;
	pCmdUI->Enable(!strcmp(className, "CWatchView") ? TRUE : FALSE);
}

void CMightyCaslFrame::OnWatchNew() 
{
	CWatchView* pView = (CWatchView*)m_wndSplitterHorz.GetPane(1, 0);
	pView->AddWatch();
}

	
