// WatchView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "WatchView.h"
#include "WatchDlg.h"
#include "WatchInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchView

IMPLEMENT_DYNCREATE(CWatchView, CListViewEx)

CWatchView::CWatchView()
{
}

CWatchView::~CWatchView()
{
}


BEGIN_MESSAGE_MAP(CWatchView, CListViewEx)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CWatchView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_UPDATE_COMMAND_UI(ID_WATCH_MODIFY, OnUpdateWatchModify)
	ON_UPDATE_COMMAND_UI(ID_WATCH_CLEAR, OnUpdateWatchClear)
	ON_COMMAND(ID_WATCH_CLEAR, OnWatchClear)
	ON_COMMAND(ID_WATCH_MODIFY, OnWatchModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchView 描画

void CWatchView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CWatchView 診断

#ifdef _DEBUG
void CWatchView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CWatchView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}


CMightyCaslDoc* CWatchView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWatchView メッセージ ハンドラ

int CWatchView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	
	return 0;
}

void CWatchView::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	// ヘッダー幅の設定
	CListCtrl& rListCtrl = GetListCtrl();
	CRect rcClient;
	GetClientRect(rcClient);
	
	rListCtrl.InsertColumn(0, "WATCH", LVCFMT_LEFT);
	rListCtrl.SetColumnWidth(0, m_fontSize.cx * 10);

	rListCtrl.InsertColumn(1, "VALUES", LVCFMT_LEFT);
	rListCtrl.SetColumnWidth(1, m_fontSize.cx * 80);
	

	CWatchList* pWatchList = GetWatchList();
	POSITION pos = pWatchList->GetHeadPosition();
	while (pos)
	{
		CWatchInfo* pInfo = pWatchList->GetNext(pos);
		InsertWatchItem(pInfo);
	}
}

void CWatchView::AddWatch(LPCSTR szTarget)
{
	CWatchDlg dlg(GetLabelBank(), this);
	dlg.SetDialogTitle("ｳｫｯﾁの新規追加");
	if (szTarget)
		dlg.m_target = szTarget;
	if (dlg.DoModal() == IDCANCEL)
		return;

	CWatchInfo* pInfo = new CWatchInfo(dlg.m_target, dlg.m_length, dlg.m_fmt);
	GetWatchList()->AddTail(pInfo);
	InsertWatchItem(pInfo);
}


CLabelBank* CWatchView::GetLabelBank()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_assembler.m_labelBank;
}

CWatchList* CWatchView::GetWatchList()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_watchList;
}

CRegister* CWatchView::GetRegister()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_register;
}

CMemory* CWatchView::GetMemory()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_memory;
}


void CWatchView::InsertWatchItem(CWatchInfo *pInfo)
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nIndex = rListCtrl.GetItemCount();

	int nItem = rListCtrl.InsertItem(nIndex++, pInfo->m_target);
	rListCtrl.SetItemData(nItem, (LPARAM)pInfo);
}

void CWatchView::PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen)
{
	strcpy(szBuff, "???");

	CListCtrl& rListCtrl = GetListCtrl();
	CWatchInfo* pInfo = (CWatchInfo*)rListCtrl.GetItemData(nItem);

	// ウォッチアドレスを求める
	WORD watchAddr;
	char ch = pInfo->m_target[0];
	if (ch == '$')
	{
		CRegister* pRegister = GetRegister();
		int regId = pRegister->GetRegisterId(pInfo->m_target.Mid(1));
		if (regId == -1 || regId >= REG_PC)
			return;

		watchAddr = pRegister->GetValue(regId);
	}
	else if (ch == '#' || (ch >= 'A' && ch <= 'Z') || ch == '_')
	{
		if (!ConvertStringToValue(watchAddr, pInfo->m_target, GetLabelBank()))
			return;
	}

	CMemory* pMemory = GetMemory();

	CString strTemp;
	CString strWatch;

	if (pInfo->m_fmt == WATCHFMT_CHAR)
		strWatch = "'";

	for (int i = 0; i < pInfo->m_length; i++)
	{
		if (i > 0 && pInfo->m_fmt != WATCHFMT_CHAR)
			strWatch += ", ";
		WORD value = pMemory->GetMemory(watchAddr + i);
		switch (pInfo->m_fmt)
		{
		case WATCHFMT_HEX:
			strTemp.Format("#%04hX", value);
			break;
		case WATCHFMT_SIGNED:
			strTemp.Format("%hd", value);
			break;
		case WATCHFMT_UNSIGNED:
			strTemp.Format("%hu", value);
			break;
		case WATCHFMT_BINARY:
			strTemp = CString("%") + ConvertBinaryString(value);
			break;
		case WATCHFMT_CHAR:
			strTemp = (value < 0x100 && isprint(value & 0xff)) ? (value & 0xff) : '.';
			break;
		}
		strWatch += strTemp;
	}

	if (pInfo->m_fmt == WATCHFMT_CHAR)
		strWatch += "'";

	strcpy(szBuff, strWatch);
}


void CWatchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHUV = (CHintUpdateView*)pHint;

	switch (lHint) 
	{
	case UPDATEHINT_EXEC_BREAK:
	case UPDATEHINT_UPDATE_MEMORY:
	case UPDATEHINT_FILL_MEMORY:
	case UPDATEHINT_PATTERN_MEMORY:
	case UPDATEHINT_COPY_MEMORY:
	case UPDATEHINT_CHANGE_MEMORY:
	case UPDATEHINT_CHANGE_REGISTER:
		InvalidateRect(NULL, TRUE);
		UpdateWindow();
	default:
		break;
	}
}

void CWatchView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	ModifyWatch();
	CListViewEx::OnLButtonDblClk(nFlags, point);
}

void CWatchView::OnUpdateWatchModify(CCmdUI* pCmdUI) 
{
	CListCtrl& rListCtrl = GetListCtrl();
	pCmdUI->Enable(rListCtrl.GetSelectedCount() == 1 ? TRUE : FALSE);
}

void CWatchView::OnWatchModify() 
{
	ModifyWatch();
}

void CWatchView::ModifyWatch()
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;
	
	CWatchInfo* pInfo = (CWatchInfo*)rListCtrl.GetItemData(nSelected);

	CWatchDlg dlg(GetLabelBank(), this);
	dlg.SetDialogTitle("ｳｫｯﾁの変更");
	dlg.m_target = pInfo->m_target;
	dlg.m_length = pInfo->m_length;
	dlg.m_fmt = pInfo->m_fmt;
	if (dlg.DoModal() == IDCANCEL)
		return;

	pInfo->m_target = dlg.m_target;
	pInfo->m_length = dlg.m_length;
	pInfo->m_fmt = dlg.m_fmt;

	rListCtrl.SetItemText(nSelected, 0, pInfo->m_target);
	rListCtrl.Update(nSelected);
}

DROPEFFECT CWatchView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	m_dropEffect = DROPEFFECT_NONE;
	if (pDataObject->IsDataAvailable(cf_SYMBOL) || pDataObject->IsDataAvailable(cf_REGISTER))
		m_dropEffect = DROPEFFECT_COPY;
	return m_dropEffect;
}

DROPEFFECT CWatchView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return m_dropEffect;
}

BOOL CWatchView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	CString strTarget;
	if (pDataObject->IsDataAvailable(cf_SYMBOL))
	{
		HGLOBAL hGlobal = pDataObject->GetGlobalData(cf_SYMBOL);
		SYMBOLFORMAT* pSymbolValue = (SYMBOLFORMAT*)::GlobalLock(hGlobal);

		strTarget = pSymbolValue->name;
		::GlobalUnlock(hGlobal);
	}
	else if (pDataObject->IsDataAvailable(cf_REGISTER))
	{
		HGLOBAL hGlobal = pDataObject->GetGlobalData(cf_REGISTER);
		REGISTERFORMAT* pRegisterValue = (REGISTERFORMAT*)::GlobalLock(hGlobal);

		strTarget.Format("$%s", pRegisterValue->name);
		::GlobalUnlock(hGlobal);
	}
	else
		return FALSE;

	AddWatch(strTarget);
	return TRUE;
}

void CWatchView::OnUpdateWatchClear(CCmdUI* pCmdUI) 
{
	CListCtrl& rListCtrl = GetListCtrl();
	pCmdUI->Enable(rListCtrl.GetSelectedCount() ? TRUE : FALSE);
}

void CWatchView::OnWatchClear() 
{
	CMightyCaslDoc* pDocument = GetDocument();
	CWatchList* pWatchList = &pDocument->m_watchList;

	CListCtrl& rListCtrl = GetListCtrl();
	int nSelected;
	while ((nSelected = rListCtrl.GetNextItem(-1, LVNI_SELECTED)) != -1)
	{
		CWatchInfo* pInfo = (CWatchInfo*)rListCtrl.GetItemData(nSelected);
		rListCtrl.DeleteItem(nSelected);
		POSITION pos = pWatchList->Find(pInfo);
		pWatchList->RemoveAt(pos);
		delete pInfo;
	}
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
}

void CWatchView::OnContextMenu(CWnd*, CPoint point)
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_WATCH_DLG));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

