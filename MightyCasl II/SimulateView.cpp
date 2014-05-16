// SimulateView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "SimulateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimulateView

IMPLEMENT_DYNCREATE(CSimulateView, CListViewEx)

CSimulateView::CSimulateView()
{
}

CSimulateView::~CSimulateView()
{
}


BEGIN_MESSAGE_MAP(CSimulateView, CListViewEx)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CSimulateView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BREAKPOINT_SET, OnBreakpointSet)
	ON_UPDATE_COMMAND_UI(ID_BREAKPOINT_SET, OnUpdateBreakpointSet)
	ON_COMMAND(ID_EXECUTE_COME, OnExecuteCome)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_COME, OnUpdateExecuteCome)
	ON_COMMAND(ID_REGISTER_PC, OnRegisterPc)
	ON_UPDATE_COMMAND_UI(ID_REGISTER_PC, OnUpdateRegisterPc)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulateView 描画

void CSimulateView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CSimulateView 診断

#ifdef _DEBUG
void CSimulateView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CSimulateView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

CMightyCaslDoc* CSimulateView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimulateView メッセージ ハンドラ
int CSimulateView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListViewEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_dropTarget.Register(this);
	CString strFontFace("ＭＳ ゴシック");
	int pointFont = 10;

	CWinApp* pApp = AfxGetApp();
	CString strTemp = pApp->GetProfileString(REG_ENTRY_ENV, REG_KEY_SOURCEFONT);
	int nPos = strTemp.Find(":");
	if (nPos > 0)
	{
		strFontFace = strTemp.Left(nPos);
		pointFont = atoi(strTemp.Mid(nPos + 1));
	}

	CDC* pDC = GetDC();

	// 編集フォントを設定する
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	
	lf.lfCharSet = SHIFTJIS_CHARSET; 
	lf.lfHeight = pointFont * 10;			// 1/10 pt単位
	lf.lfWidth = 0;
	lf.lfQuality = PROOF_QUALITY;
	strcpy(lf.lfFaceName, strFontFace);

	if (m_font.CreatePointFontIndirect(&lf, pDC))
		SetFont(&m_font);

	pDC->SelectObject(&m_font);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	m_fontSize.cx = tm.tmAveCharWidth;
	m_fontSize.cy = tm.tmHeight;

	ReleaseDC(pDC);

	// アイコンの設定
	if (!m_imageIcon.Create(IDB_ICON_SIMULATE, 16, FALSE, RGB(0, 128, 0)))
		return -1;
	m_imageIcon.SetOverlayImage(ICONOVERLAY_SIMULATE_PC,	ICONOVERLAY_SIMULATE_PC);
	GetListCtrl().SetImageList(&m_imageIcon, LVSIL_SMALL);

	CMightyCaslDoc* pDocument = GetDocument();
	CView* pSourceView = pDocument->GetTargetView("CSourceView");
	if (pSourceView)
	{
		CWnd* pParentFrame = pSourceView->GetParentFrame();
		if (pParentFrame)
		{
			CMenu* pMenu = pParentFrame->GetSystemMenu(FALSE);
			pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
		}
	}


	return 0;
}


void CSimulateView::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	// ヘッダー幅の設定
	CListCtrl& rListCtrl = GetListCtrl();
	
	rListCtrl.InsertColumn(0, "ADDR");
	rListCtrl.SetColumnWidth(0, m_fontSize.cx * 8);

	rListCtrl.InsertColumn(1, "Source Line");
	rListCtrl.SetColumnWidth(1,  m_fontSize.cx  * 60);

	InsertListItem();
}

void CSimulateView::InsertListItem()
{
	CListCtrl& rListCtrl = GetListCtrl();

	CMnemonicArray* pMnemonics = GetMnemonics();
	for (int i = 0; i < pMnemonics->GetSize(); i++)
	{
		CString strAddr;

		CMnemonic* pMnemonic = (CMnemonic*)pMnemonics->GetAt(i);
		strAddr.Format("%04X", pMnemonic->GetAddress());
		LV_ITEM lvi;
		lvi.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_TEXT | LVIF_STATE;
		lvi.pszText = (LPSTR)(LPCSTR)strAddr;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.iImage = ICON_SIMULATE_NORMAL;
		lvi.stateMask = LVIS_OVERLAYMASK;
		lvi.state = INDEXTOOVERLAYMASK(0);
		lvi.lParam = (LPARAM)pMnemonic;
		int nItem = rListCtrl.InsertItem(&lvi);

		CString line = pMnemonic->GetSourceLine();
		rListCtrl.SetItemText(nItem, 1, line);
	}
}

CMnemonicArray* CSimulateView::GetMnemonics()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return pDocument->m_assembler.GetMnemonics();	
}


void CSimulateView::PreDrawItem(int nItem, LV_ITEM* pLVI)
{
	CListCtrl& rListCtrl = GetListCtrl();

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nItem);
	pLVI->iImage = pMnemonic->IsBreakPoint() ? ICON_SIMULATE_BREAK : ICON_SIMULATE_NORMAL;

	CRegister* pRegister = GetRegister();
	WORD pc = pRegister->GetValue(REG_PC);

	int nOverlayImage = 0;
	if (pMnemonic->IsExecutable() && pMnemonic->GetAddress() == pc)
		nOverlayImage = ICONOVERLAY_SIMULATE_PC;
	pLVI->state &= ~ILD_OVERLAYMASK;
	pLVI->state |= INDEXTOOVERLAYMASK(nOverlayImage);
}

CRegister* CSimulateView::GetRegister()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_register;
}

CMemory* CSimulateView::GetMemory()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_memory;
}

BOOL CSimulateView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_SINGLESEL;	
	
	return CListViewEx::PreCreateWindow(cs);
}

void CSimulateView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHUV = (CHintUpdateView*)pHint;

	switch (lHint) 
	{
	case UPDATEHINT_EXEC_BREAK:
		EnsureVisibleCurPC();
		break;
	case UPDATEHINT_CHANGE_REGISTER:
	case UPDATEHINT_CHANGE_BREAKPOINT:
		InvalidateRect(NULL, TRUE);
		UpdateWindow();
		break;
	case UPDATEHINT_UPDATE_SIMVIEW:
		EnsureVisibleAddress(pHUV->m_locationAddress);
		break;
	default:
		break;
	}
}

void CSimulateView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	SetPcAtLine();

	CListViewEx::OnLButtonDblClk(nFlags, point);
}

void CSimulateView::OnBreakpointSet() 
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nSelected);
	if (!pMnemonic->IsExecutable())
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	BOOL bBreakOn = pMnemonic->IsBreakPoint() ? FALSE : TRUE;
	pMnemonic->SetBreakPoint(bBreakOn);

	rListCtrl.Update(nSelected);
}

void CSimulateView::OnUpdateBreakpointSet(CCmdUI* pCmdUI) 
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nSelected);
	pCmdUI->Enable(pMnemonic->IsExecutable());
}

void CSimulateView::EnsureVisibleCurPC()
{
	CListCtrl& rListCtrl = GetListCtrl();

	CRegister* pRegister = GetRegister();
	WORD pc = pRegister->GetValue(REG_PC);

	for (int i = 0; i < rListCtrl.GetItemCount(); i++)
	{
		CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(i);
		if (pMnemonic->IsExecutable() && pMnemonic->GetAddress() == pc)
		{
			rListCtrl.EnsureVisible(i, FALSE);
			break;
		}
	}
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
}

void CSimulateView::EnsureVisibleAddress(WORD address)
{
	CListCtrl& rListCtrl = GetListCtrl();

	int nTargetItem = -1;
	for (int i = rListCtrl.GetItemCount() - 1; i >= 0; i--)
	{
		CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(i);
		if (pMnemonic->GetAddress() == address)
		{
			nTargetItem = i;
			break;
		}
	}

	if (nTargetItem == -1)
		return;

	for (i = 0; i < rListCtrl.GetItemCount(); i++)
	{
		UINT state = (i == nTargetItem) ? LVIS_FOCUSED | LVIS_SELECTED : 0;
		rListCtrl.SetItemState(i, state, LVIS_FOCUSED | LVIS_SELECTED);
	}
	rListCtrl.EnsureVisible(nTargetItem, FALSE);
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
}


void CSimulateView::OnExecuteCome() 
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nSelected);
	if (!pMnemonic->IsExecutable())
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	CMightyCaslDoc* pDocument = GetDocument();
	CMnemonicArray* pMnemonics = pDocument->m_assembler.GetMnemonics();
	pDocument->ExecuteProgram(EXECUTEMODE_COME, pMnemonic->GetAddress());
}

void CSimulateView::OnUpdateExecuteCome(CCmdUI* pCmdUI) 
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nSelected);
	pCmdUI->Enable(pMnemonic->IsExecutable());
}

DROPEFFECT CSimulateView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	m_dropEffect = DROPEFFECT_NONE;
	if (pDataObject->IsDataAvailable(cf_SYMBOL))
		m_dropEffect = DROPEFFECT_COPY;
	return m_dropEffect;
}

DROPEFFECT CSimulateView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return m_dropEffect;
}

BOOL CSimulateView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	HGLOBAL hGlobal = pDataObject->GetGlobalData(cf_SYMBOL);
	SYMBOLFORMAT* pSymbolValue = (SYMBOLFORMAT*)::GlobalLock(hGlobal);

	CHintUpdateView hint;
	hint.m_locationAddress = pSymbolValue->value;
	::GlobalUnlock(hGlobal);
	GetDocument()->UpdateAllViews(NULL, UPDATEHINT_UPDATE_SIMVIEW, &hint);

	SetFocus();
	return TRUE;
}


void CSimulateView::OnRegisterPc() 
{
	SetPcAtLine();
}

void CSimulateView::OnUpdateRegisterPc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount() ? TRUE : FALSE);	
}

void CSimulateView::SetPcAtLine()
{

	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;

	CMnemonic* pMnemonic = (CMnemonic*)rListCtrl.GetItemData(nSelected);
	if (!pMnemonic->IsExecutable())
	{
		MessageBeep(MB_ICONEXCLAMATION);
		return;
	}

	CRegister* pRegister = GetRegister();
	pRegister->SetValue(REG_PC, pMnemonic->GetAddress());
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_REGISTER, NULL);
}

void CSimulateView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: このブロックはポップアップ メニュー コンポーネントによって追加されました
	{
		if (point.x == -1 && point.y == -1){
			//キーストロークの発動
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_SIMULATE_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CSimulateView::OnDestroy() 
{
	CListViewEx::OnDestroy();
	
	CMightyCaslDoc* pDocument = GetDocument();
	CView* pSourceView = pDocument->GetTargetView("CSourceView");
	if (pSourceView)
	{
		CWnd* pParentFrame = pSourceView->GetParentFrame();
		if (pParentFrame)
		{
			CMenu* pMenu = pParentFrame->GetSystemMenu(FALSE);
			pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
		}
	}
}
