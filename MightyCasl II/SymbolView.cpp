// SymbolView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "SymbolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSymbolView

IMPLEMENT_DYNCREATE(CSymbolView, CListViewEx)

CSymbolView::CSymbolView()
{
	m_nSortColumn = 0;
	m_nSortOrder = 1;
}

CSymbolView::~CSymbolView()
{
}


BEGIN_MESSAGE_MAP(CSymbolView, CListViewEx)
	//{{AFX_MSG_MAP(CSymbolView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymbolView 描画

void CSymbolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CSymbolView 診断

#ifdef _DEBUG
void CSymbolView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CSymbolView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

CMightyCaslDoc* CSymbolView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSymbolView メッセージ ハンドラ

int CSymbolView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListViewEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
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

void CSymbolView::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	// ヘッダー幅の設定
	CListCtrl& rListCtrl = GetListCtrl();
	CRect rcClient;
	GetClientRect(rcClient);
	
	rListCtrl.InsertColumn(0, "LABEL", LVCFMT_LEFT);
	rListCtrl.SetColumnWidth(0, m_fontSize.cx * 10);

	rListCtrl.InsertColumn(1, "ADDR", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(1, m_fontSize.cx * 7);
	
	CLabelBank* pLabelBank = &GetDocument()->m_assembler.m_labelBank;

	int nIndex = 0;
	POSITION pos = pLabelBank->GetStartPosition();
	while (pos)
	{
		CString strLabel;
		CLabel* pLabel;
		pLabelBank->GetNextAssoc(pos, strLabel, pLabel);
		CString strValue;
		strValue.Format("%04X", pLabel->m_value);

		int nItem = rListCtrl.InsertItem(nIndex++, strLabel);
		rListCtrl.SetItemText(nItem, 1, strValue);
		rListCtrl.SetItemData(nItem, (LPARAM)pLabel);
	}
	rListCtrl.SortItems(CompareFunc, (DWORD)this);

}

int CSymbolView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSymbolView* pThis = (CSymbolView*)lParamSort;

	CLabel* pLabel1 = (CLabel*)lParam1;
	CLabel* pLabel2 = (CLabel*)lParam2;
	
	if ((pLabel1 == NULL) || (pLabel1 == NULL))
		return 0;

	int result = 0;
	switch (pThis->m_nSortColumn)
	{
	case 0:
		result = pLabel1->m_name.Compare(pLabel2->m_name);
		break;
	case 1:
		result = pLabel1->m_value - pLabel2->m_value;
		break;
	}
	return result * pThis->m_nSortOrder;
}

void CSymbolView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// 現在ソート中のカラムなら、ソートオーダーを変更、別のカラムなら昇順オーダー
	if (m_nSortColumn == pNMListView->iSubItem)
		m_nSortOrder = -m_nSortOrder;
	else
	{
		m_nSortColumn = pNMListView->iSubItem;
		m_nSortOrder = 1;
	}
	
	GetListCtrl().SortItems(CompareFunc, (DWORD)this);
	*pResult = 0;
}

void CSymbolView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	
	
}

BOOL CSymbolView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_SINGLESEL;	
	
	return CListViewEx::PreCreateWindow(cs);
}

void CSymbolView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CLabel* pLabel = (CLabel*)GetListCtrl().GetItemData(pNMListView->iItem);

	HGLOBAL hGlobal = ::GlobalAlloc(GHND | GMEM_SHARE, (DWORD)(sizeof(SYMBOLFORMAT)));
	if (hGlobal == NULL)
		return;

	SYMBOLFORMAT* pSymbolValue = (SYMBOLFORMAT*)::GlobalLock(hGlobal);
	pSymbolValue->value = pLabel->m_value;
	strcpy(pSymbolValue->name, pLabel->m_name);
	::GlobalUnlock(hGlobal);

	COleDataSource* pSource = new COleDataSource();
	pSource->CacheGlobalData(cf_SYMBOL, hGlobal);

	DROPEFFECT dropEffect = pSource->DoDragDrop(DROPEFFECT_COPY, NULL);
	delete pSource;

	*pResult = 0;
}
