// StackView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "StackView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStackView

IMPLEMENT_DYNCREATE(CStackView, CListViewEx)

CStackView::CStackView()
{
}

CStackView::~CStackView()
{
}


BEGIN_MESSAGE_MAP(CStackView, CListViewEx)
	//{{AFX_MSG_MAP(CStackView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStackView 描画

void CStackView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CStackView 診断

#ifdef _DEBUG
void CStackView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CStackView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

CMightyCaslDoc* CStackView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStackView メッセージ ハンドラ

int CStackView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	// アイコンの設定
	if (!m_imageIcon.Create(IDB_ICON_STACK, 16, FALSE, RGB(0, 128, 0)))
		return -1;
	GetListCtrl().SetImageList(&m_imageIcon, LVSIL_SMALL);
	
	return 0;
}

void CStackView::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	// ヘッダー幅の設定
	CListCtrl& rListCtrl = GetListCtrl();
	CRect rcClient;
	GetClientRect(rcClient);
	
	rListCtrl.InsertColumn(0, "STACK", LVCFMT_LEFT);
	rListCtrl.SetColumnWidth(0, m_fontSize.cx * 12);

	rListCtrl.InsertColumn(1, "VALUE", LVCFMT_RIGHT);
	rListCtrl.SetColumnWidth(1, m_fontSize.cx * 7);

	
	// ダミーで10個登録
	for (int i = 0; i < 64; i++)
	{
		int nIndex = rListCtrl.InsertItem(i, "0000");
		rListCtrl.SetItemText(nIndex, 1, "0000");
	}

}

void CStackView::PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen)
{
	CRegister* pRegister = GetRegister();
	WORD sp = pRegister->GetValue(REG_SP);

	CMemory* pMemory = GetMemory();
	WORD value = pMemory->GetMemory(sp + nItem);
	CString strTemp;
	strTemp.Format("%04X", value);
	strcpy(szBuff, strTemp);
}

void CStackView::PreDrawItem(int nItem, LV_ITEM* pLVI)
{
	CRegister* pRegister = GetRegister();
	WORD sp = pRegister->GetValue(REG_SP);

	CString strTemp;
	strTemp.Format("%04X", (sp + nItem) & 0xffff);
	strcpy(pLVI->pszText, strTemp);

	pLVI->iImage = (nItem == 0) ? 1 : 0;
		
}

CRegister* CStackView::GetRegister()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_register;
}

CMemory* CStackView::GetMemory()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_memory;
}

void CStackView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
	default:
		break;
	}
}

BOOL CStackView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_SINGLESEL;	
	
	return CListViewEx::PreCreateWindow(cs);
}
