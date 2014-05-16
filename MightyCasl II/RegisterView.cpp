// RegisterView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "RegisterView.h"
#include "Register.h"

#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterView

IMPLEMENT_DYNCREATE(CRegisterView, CListViewEx)

CRegisterView::CRegisterView()
{
}

CRegisterView::~CRegisterView()
{
}


BEGIN_MESSAGE_MAP(CRegisterView, CListViewEx)
	//{{AFX_MSG_MAP(CRegisterView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterView 描画

void CRegisterView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CRegisterView 診断

#ifdef _DEBUG
void CRegisterView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CRegisterView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

CMightyCaslDoc* CRegisterView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRegisterView メッセージ ハンドラ

int CRegisterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CRegisterView::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	// ヘッダー幅の設定
	CListCtrl& rListCtrl = GetListCtrl();
	CRect rcClient;
	GetClientRect(rcClient);
	
	rListCtrl.InsertColumn(REG_COLUMN_REG, "REG", LVCFMT_LEFT);
	rListCtrl.SetColumnWidth(REG_COLUMN_REG, m_fontSize.cx * 8);

	rListCtrl.InsertColumn(REG_COLUMN_HEX, "Hex", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(REG_COLUMN_HEX, m_fontSize.cx * 7);
	
	rListCtrl.InsertColumn(REG_COLUMN_SIGNED, "Signed", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(REG_COLUMN_SIGNED, m_fontSize.cx * 10);

	rListCtrl.InsertColumn(REG_COLUMN_UNSIGNED, "Unsigned", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(REG_COLUMN_UNSIGNED, m_fontSize.cx * 10);

	rListCtrl.InsertColumn(REG_COLUMN_BINARY, "Binary", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(REG_COLUMN_BINARY, m_fontSize.cx * 22);

	rListCtrl.InsertColumn(REG_COLUMN_CHAR, "Chr", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(REG_COLUMN_CHAR, m_fontSize.cx * 5);

	for (int i = 0; i < SIZEOF_REG; i++)
	{
		int nIndex = rListCtrl.InsertItem(i, CRegister::GetRegisterName(i));
		rListCtrl.SetItemData(nIndex, i);
	}
}

void CRegisterView::PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen)
{
	CRegister* pRegister = GetRegister();

	CListCtrl& rListCtrl = GetListCtrl();
	int nRegID = rListCtrl.GetItemData(nItem);

	CString strTemp = "";
	WORD value = pRegister->GetValue(nRegID);
	switch (nColumn)
	{
	case REG_COLUMN_HEX:
		if (nRegID <= REG_PC)
			strTemp.Format("%04hX", value);
		else if (nRegID == REG_FR)
		{
			WORD state = (value & REG_FR_ALL);
			strTemp.Empty();
			strTemp += (state & REG_FR_VFLG) ? "V" : "-";
			strTemp += (state & REG_FR_SFLG) ? "S" : "-";
			strTemp += (state & REG_FR_ZFLG) ? "Z" : "-";
		}
		break;
	case REG_COLUMN_SIGNED:
		if (nRegID <= REG_GR7)
			strTemp.Format("%hd", value);
		break;
	case REG_COLUMN_UNSIGNED:
		if (nRegID <= REG_GR7)
			strTemp.Format("%hu", value);
		break;
	case REG_COLUMN_BINARY:
		if (nRegID <= REG_GR7)
			strTemp = ConvertBinaryString(value);
		else if (nRegID == REG_FR)
		{
			WORD state = (value & 0x007);
			strTemp.Empty();
			strTemp += (state & REG_FR_VFLG) ? "1" : "0";
			strTemp += (state & REG_FR_SFLG) ? "1" : "0";
			strTemp += (state & REG_FR_ZFLG) ? "1" : "0";
		}
		break;
	case REG_COLUMN_CHAR:
		if (nRegID <= REG_GR7)
			strTemp.Format("'%c'", (value < 0x100 && isprint(value & 0xff)) ? (char)(value & 0xff) : '.');
		break;
	}
	strcpy(szBuff, strTemp);
}	


CRegister* CRegisterView::GetRegister()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_register;
}

CLabelBank* CRegisterView::GetLabelBank()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_assembler.m_labelBank;
}

BOOL CRegisterView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_SINGLESEL;	
	return CListViewEx::PreCreateWindow(cs);
}

void CRegisterView::ModifyRegister()
{
	CListCtrl& rListCtrl = GetListCtrl();
	int nItem = rListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nItem == -1)
		return;

	CRegisterDlg dlg(nItem, GetRegister(), GetLabelBank(), this);
	

	if (dlg.DoModal() == IDCANCEL)
		return;

	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_REGISTER, NULL);
}

void CRegisterView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	ModifyRegister();
	
	CListViewEx::OnLButtonDblClk(nFlags, point);
}

void CRegisterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint) 
	{
	case UPDATEHINT_EXEC_BREAK:
	case UPDATEHINT_CHANGE_REGISTER:
		InvalidateRect(NULL, TRUE);
		UpdateWindow();
		break;
	default:
		break;
	}
}

void CRegisterView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nRegId = pNMListView->iItem;
	if (nRegId == REG_SP || (nRegId >= REG_GR0 && nRegId <= REG_GR7))
	{
		HGLOBAL hGlobal = ::GlobalAlloc(GHND | GMEM_SHARE, (DWORD)(sizeof(REGISTERFORMAT)));
		if (hGlobal == NULL)
			return;

		REGISTERFORMAT* pRegisterValue = (REGISTERFORMAT*)::GlobalLock(hGlobal);
		pRegisterValue->value = GetRegister()->GetValue(nRegId);
		strcpy(pRegisterValue->name, CRegister::GetRegisterName(nRegId));
		::GlobalUnlock(hGlobal);

		COleDataSource* pSource = new COleDataSource();
		pSource->CacheGlobalData(cf_REGISTER, hGlobal);

		DROPEFFECT dropEffect = pSource->DoDragDrop(DROPEFFECT_COPY, NULL);
		delete pSource;
	}
	*pResult = 0;
}

