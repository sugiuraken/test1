// DumpView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "DumpView.h"

#include "Memory.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int c_leftMargin		= 8;
const int c_maxMemory		= MEMORY_SIZE;

const int c_lenAddrArea		= 7;
const int c_lenHexArea		= (5 * 8);
const int c_lenDelimArea	= 3;
const int c_lenCharArea		= 8;

/////////////////////////////////////////////////////////////////////////////
// CDumpView

IMPLEMENT_DYNCREATE(CDumpView, CView)

CDumpView::CDumpView()
{
	m_topLineAddress = 0x000000;
}

CDumpView::~CDumpView()
{
}

UINT CDumpView::TestDumpHit(CPoint pt)
{
	pt.x -= c_leftMargin;
	if (pt.x < m_fontSize.cx * c_lenAddrArea)
		return MAKELONG(HP_PREHEX, 0);

	pt.x -= m_fontSize.cx * c_lenAddrArea;
	if (pt.x < m_fontSize.cx * c_lenHexArea)
		return MAKELONG(HP_HEX0 + (pt.x % (m_fontSize.cx * 5)) / m_fontSize.cx, pt.x / (m_fontSize.cx * 5));

	pt.x -= m_fontSize.cx * c_lenHexArea;
	if (pt.x < m_fontSize.cx * c_lenDelimArea)
		return MAKELONG(HP_PRECHR, 0);

	pt.x -= m_fontSize.cx * c_lenDelimArea;
	if (pt.x < m_fontSize.cx * c_lenCharArea)
		return MAKELONG(HP_CHR, pt.x / m_fontSize.cx);
	
	pt.x -= m_fontSize.cx * c_lenCharArea;
	if (pt.x < m_fontSize.cx)
		return MAKELONG(HP_CHRSPACE, 0);

	return MAKELONG(HP_POSTCHR, 0);
}

void CDumpView::SetCaretPosSmart(CPoint point)
{
	if (point.y < m_fontSize.cy) 
	{
		if (m_topLineAddress == 0x000000)
			return;							// そんな上にカレットは移動できない
		// 一行スクロールして、画面の上方外へ出そうなカレットを止める
		m_topLineAddress -= 8;
		InvalidateRect(NULL, FALSE);
		point += CSize(0, m_fontSize.cy);
	}
	else 
	{
		// そこはもうアドレスが大きすぎるところ
		if (m_topLineAddress + ((point.y - m_fontSize.cy) / m_fontSize.cy) * 8 >= c_maxMemory)
			return;
		
		CRect rcClient;
		GetClientRect(rcClient);
		if (rcClient.Height() > m_fontSize.cy && point.y + m_fontSize.cy >= rcClient.bottom) 
		{
			// １行以上の表示高があって、ウィンドウの下にすこし出ている行にカレットが移動するので、
			// １行分スクロールします。
			m_topLineAddress += 8;
			InvalidateRect(NULL, FALSE);
			point -= CSize(0, m_fontSize.cy);
		}
	}
	SetCaretPos(point);
}

void CDumpView::AdjustOverCaret()
{
	// スクロールによりメモリ末尾より後ろの空白をさしてしまったかもしれないカレットを補正する

	CPoint point = GetCaretPos();
	// そこはまだメモリのあるところ
	if (m_topLineAddress + ((point.y - m_fontSize.cy) / m_fontSize.cy) * 8 < c_maxMemory)
		return;

	point.y = ((c_maxMemory - 0x08) - m_topLineAddress) / 8 * m_fontSize.cy + m_fontSize.cy;
	SetCaretPos(point);

}


BEGIN_MESSAGE_MAP(CDumpView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDumpView)
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpView 描画

void CDumpView::OnDraw(CDC* pDC)
{
	CMemory* pMemory = GetMemory();

	CRect rcClient;
	GetClientRect(rcClient);

	pDC->SelectObject(&m_font);
	pDC->FillSolidRect(CRect(0, 0, rcClient.right, m_fontSize.cy), ::GetSysColor(COLOR_BTNFACE));
	pDC->TextOut(c_leftMargin, 0, CString("ADDR :  +0   +1   +2   +3   +4   +5   +6   +7   : CHARECTOR"));
	
	pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
	int nAddr = m_topLineAddress;
	for (int y = m_fontSize.cy; y < rcClient.Height(); y += m_fontSize.cy) 
	{
		if (nAddr >= c_maxMemory) 
		{
			rcClient.top = y;
			pDC->FillSolidRect(rcClient, pDC->GetBkColor());
			break;
		}
		CString textLine, textCharactor;
		textLine.Format("%04X", nAddr);
		pDC->TextOut(c_leftMargin, y, textLine);

		textLine = " : ";
		WORD code[8];
		pMemory->GetMemoryRange(nAddr, code, 8);
		for (int i = 0; i < 8; i++) 
		{
			CString text;
			text.Format("%04X ", code[i]);
			textLine += text;
			textCharactor += (code[i] < 0x100 && isprint(code[i] & 0xff)) ? (code[i] & 0xff) : '.';
		}
		textLine += " : " + textCharactor;
		pDC->TextOut(c_leftMargin + 4 * m_fontSize.cx, y, textLine);
		nAddr += 8;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDumpView 診断

#ifdef _DEBUG
void CDumpView::AssertValid() const
{
	CView::AssertValid();
}

void CDumpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMightyCaslDoc* CDumpView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumpView メッセージ ハンドラ
BOOL CDumpView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_VSCROLL;
	return CView::PreCreateWindow(cs);
}

int CDumpView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
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

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;

	si.nMin = 0;
	si.nMax = c_maxMemory / 0x08;
	si.nPage = 8;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, FALSE);

	return 0;
}

void CDumpView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	m_ptCaret = CPoint(c_leftMargin + m_fontSize.cx * c_lenAddrArea, m_fontSize.cy);
	m_topLineAddress = 0x000100;
	SetCaretPos(m_ptCaret);
	Invalidate(FALSE);
}


void CDumpView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHUV = (CHintUpdateView*)pHint;

	switch (lHint) 
	{
	case UPDATEHINT_UPDATE_MEMORY:
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		break;
	case UPDATEHINT_NEXT_DUMPVIEW:
		m_topLineAddress = GetNextPageLocationAddress();
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		break;
	case UPDATEHINT_UPDATE_DUMPVIEW:
		m_topLineAddress = pHUV->m_locationAddress & 0xFFF8;
		m_ptCaret = CPoint(c_leftMargin + m_fontSize.cx * (c_lenAddrArea + (pHUV->m_locationAddress & 0x0007) * 5), 
						   m_fontSize.cy);
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		break;
	case UPDATEHINT_EXEC_BREAK:
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		break;
	case UPDATEHINT_FILL_MEMORY:
		{
			CWaitCursor wCursor;
			CMemory* pMem = GetMemory();
			UINT* pParam = (UINT*)pHUV->m_pParam;
//			pMem->FillMemoryRange(pParam[0], pParam[1], pParam[2]);
			GetDocument()->UpdateAllViews(NULL, UPDATEHINT_UPDATE_MEMORY, NULL);
		}
		break;
	case UPDATEHINT_PATTERN_MEMORY:
		{
			CWaitCursor wCursor;
			CMemory* pMem = GetMemory();
			UINT* pParam = (UINT*)pHUV->m_pParam;
			WORD* pWordPattern = (WORD*)pParam[3];
			UINT nPattern = pParam[2];
			LPBYTE pPattern = new BYTE[nPattern];
			for (UINT i = 0; i < nPattern; i++)
				pPattern[i] = (BYTE)pWordPattern[i];
//			pMem->FillMemoryPattern(pParam[0], pParam[1], nPattern, pPattern);
			delete [] pPattern;
			GetDocument()->UpdateAllViews(NULL, UPDATEHINT_UPDATE_MEMORY, NULL);
		}
	case UPDATEHINT_COPY_MEMORY:
		{
			CWaitCursor wCursor;
			CMemory* pMem = GetMemory();
			UINT* pParam = (UINT*)pHUV->m_pParam;
//			pMem->CopyMemoryRange(pParam[0], pParam[1], pParam[2]);
			GetDocument()->UpdateAllViews(NULL, UPDATEHINT_UPDATE_MEMORY, NULL);
		}
		break;
	default:
		break;
	}
}


void CDumpView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	BOOL bRedraw = FALSE;
	switch (nSBCode) 
	{
	case SB_LINEDOWN:
		if (m_topLineAddress >= c_maxMemory - 0x08)
			break;
		m_topLineAddress += 8;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		AdjustOverCaret();
		bRedraw = TRUE;
		break;
	case SB_LINEUP:
		if (m_topLineAddress < 0x0008)
			break;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		m_topLineAddress -= 8;
		bRedraw = TRUE;
		break;
	case SB_PAGEDOWN:
		if ((m_topLineAddress >= c_maxMemory - 0x80) || (c_maxMemory < 0x80))
			m_topLineAddress = c_maxMemory - 0x08;
		else
			m_topLineAddress += 0x40;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		AdjustOverCaret();
		bRedraw = TRUE;
		break;
	case SB_PAGEUP:
		if (m_topLineAddress < 0x40)
			m_topLineAddress = 0;
		else
			m_topLineAddress -= 0x40;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		bRedraw = TRUE;
		break;
	case SB_BOTTOM:
		m_topLineAddress = c_maxMemory - 0x08;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		AdjustOverCaret();
		bRedraw = TRUE;
		break;
	case SB_TOP:
		m_topLineAddress = 0x0000;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		bRedraw = TRUE;
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		m_topLineAddress = nPos * 0x08;
		SetScrollPos(SB_VERT, m_topLineAddress / 0x08);
		bRedraw = TRUE;
		break;
	}
	if (bRedraw)
		InvalidateRect(NULL, FALSE);
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDumpView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar) 
	{
	case VK_DOWN:
	case VK_UP:
	case VK_RIGHT:
	case VK_LEFT:
	case VK_TAB:
		MoveCaret(nChar);
		break;
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN, 0, NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP, 0, NULL);
		break;
	case VK_END:
		OnVScroll(SB_BOTTOM, 0, NULL);
		break;
	case VK_HOME:
		OnVScroll(SB_TOP, 0, NULL);
		break;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDumpView::MoveCaret(UINT nChar)
{
	CPoint ptCaret = GetCaretPos();
	UINT hit = TestDumpHit(ptCaret);

	switch (nChar) 
	{
	case VK_TAB:
		switch (LOWORD(hit)) 
		{
		case HP_HEX0:
		case HP_HEX1:
		case HP_HEX2:
		case HP_HEX3:
		case HP_HEXSPACE:
			ptCaret.x = c_leftMargin + 
						m_fontSize.cx * (c_lenAddrArea + c_lenHexArea + c_lenDelimArea + HIWORD(hit));
			break;		
		case HP_POSTHEX:
			ptCaret.x = c_leftMargin + 
						m_fontSize.cx * (c_lenAddrArea + c_lenHexArea + c_lenDelimArea + c_lenCharArea);
			break;
		case HP_CHR:
			ptCaret.x = c_leftMargin + 
						m_fontSize.cx * (c_lenAddrArea + 5 * HIWORD(hit));
			break;
		case HP_CHRSPACE:
			ptCaret.x = c_leftMargin + 
						m_fontSize.cx * (c_lenAddrArea + c_lenHexArea);
			break;
		}
		break;
	case VK_DOWN:
		ptCaret += CSize(0, m_fontSize.cy);
		break;
	case VK_UP:
		ptCaret -= CSize(0, m_fontSize.cy);
		break;
	case VK_RIGHT:
		switch (LOWORD(hit)) 
		{
		case HP_POSTHEX:
			ptCaret = CPoint(c_leftMargin + m_fontSize.cx * c_lenAddrArea, 
							 ptCaret.y + m_fontSize.cy);
			break;
		case HP_CHRSPACE:
			ptCaret = CPoint(c_leftMargin + m_fontSize.cx * (c_lenAddrArea + c_lenHexArea + c_lenDelimArea), 
							 ptCaret.y + m_fontSize.cy);
			break;
		default:
			ptCaret += CSize(m_fontSize.cx, 0);
			break;
		}
		break;
	case VK_LEFT:
		if ((LOWORD(hit) == HP_HEX0) && (HIWORD(hit) == 0))
			ptCaret = CPoint(c_leftMargin + m_fontSize.cx * (c_lenAddrArea + c_lenHexArea), ptCaret.y - m_fontSize.cy);
		else if ((LOWORD(hit) == HP_CHR) && (HIWORD(hit) == 0))
			ptCaret = CPoint(c_leftMargin + m_fontSize.cx * (c_lenAddrArea + c_lenHexArea + c_lenDelimArea + c_lenCharArea), 
							 ptCaret.y - m_fontSize.cy);
		else 
			ptCaret -= CSize(m_fontSize.cx, 0);
		break;
	}
	SetCaretPosSmart(ptCaret);
}


void CDumpView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	CreateSolidCaret(1, m_fontSize.cy);
	SetCaretPos(m_ptCaret);
	ShowCaret();
}

void CDumpView::OnKillFocus(CWnd* pNewWnd) 
{
	m_ptCaret = GetCaretPos();
	HideCaret();
	::DestroyCaret();

	CView::OnKillFocus(pNewWnd);
}

void CDumpView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPoint ptCaret;
	UINT hit = TestDumpHit(point);
	switch (LOWORD(hit)) 
	{
	case HP_HEX0:
	case HP_HEX1:
	case HP_HEX2:
	case HP_HEX3:
	case HP_HEXSPACE:
		ptCaret.x = c_leftMargin + (HIWORD(hit) * 5 + (LOWORD(hit) - HP_HEX0) + c_lenAddrArea) * m_fontSize.cx;
		ptCaret.y = (point.y / m_fontSize.cy) * m_fontSize.cy;
		SetCaretPosSmart(ptCaret);
		break;
	case HP_CHRSPACE:
		hit = MAKELONG(HP_CHR, 8);		// fall throw
	case HP_CHR:
		ptCaret.x = c_leftMargin + (HIWORD(hit) + c_lenHexArea + c_lenDelimArea + c_lenAddrArea) * m_fontSize.cx;
		ptCaret.y = (point.y / m_fontSize.cy) * m_fontSize.cy;
		SetCaretPosSmart(ptCaret);
		break;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CDumpView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPoint ptCaret = GetCaretPos();
	UINT hit = TestDumpHit(ptCaret);
	WORD hitPos = LOWORD(hit);
	if (hitPos >= HP_HEX0 && hitPos <= HP_HEX3)
	{
		if (isxdigit(nChar))
			ModifyMemoryHex(nChar, ptCaret, hitPos, HIWORD(hit));
	}
	else if (hitPos == HP_CHR)
	{
		if (isprint(nChar))
			ModifyMemoryChr(nChar, ptCaret, HIWORD(hit));
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CDumpView::ModifyMemoryHex(UINT nChar, CPoint ptCaret, WORD hitPos, WORD offset)
{
	CString text((BYTE)nChar);

	HideCaret();
	CMemory* pMemory = GetMemory();

	CDC* pDC = GetDC();
	pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
	pDC->SelectObject(&m_font);
	// まず入力した文字をいったん表示する
	pDC->TextOut(ptCaret.x, ptCaret.y, text);
	
	// 入力した値をメモリに設定
	UINT address = m_topLineAddress + (ptCaret.y / m_fontSize.cy - 1) * 8 + offset;
	WORD w;
	switch (hitPos)
	{
	case HP_HEX0:
		w = pMemory->GetMemory(address) & 0x0fff;
		w |= strtoul(text, NULL, 16) << 12;
		break;
	case HP_HEX1:
		w = pMemory->GetMemory(address) & 0xf0ff;
		w |= strtoul(text, NULL, 16) << 8;
		break;
	case HP_HEX2:
		w = pMemory->GetMemory(address) & 0xff0f;
		w |= strtoul(text, NULL, 16) << 4;
		break;
	case HP_HEX3:
		w = pMemory->GetMemory(address) & 0xfff0;
		w |= strtoul(text, NULL, 16);
		break;
	}
	pMemory->SetMemory(address, w);

	// 設定後、再度メモリからデータを取り込んで再表示する
	w = pMemory->GetMemory(address);
	text.Format("%01X", ((hitPos == HP_HEX0) ? (w >> 12) : 
						 (hitPos == HP_HEX1) ? (w >>  8) : 
						 (hitPos == HP_HEX2) ? (w >>  4) : w) & 0x0f);

	pDC->TextOut(ptCaret.x, ptCaret.y, text);

	// CHR表示も更新する
	text = (w < 0x100 && isprint(w & 0xff)) ? (char)w : '.';
	pDC->TextOut(c_leftMargin + (c_lenAddrArea + c_lenHexArea+ c_lenDelimArea + offset) * m_fontSize.cx, 
				 ptCaret.y,
				 text);
	
	ReleaseDC(pDC);

	MoveCaret(VK_RIGHT);
	if (hitPos == HP_HEX3) 
	{
		MoveCaret(VK_RIGHT);
		if (offset == 7)
			MoveCaret(VK_RIGHT);
	}

	ShowCaret();			

	CHintUpdateView hint;
	hint.m_locationAddress = address;
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_MEMORY, &hint);
}

void CDumpView::ModifyMemoryChr(UINT nChar, CPoint ptCaret, WORD offset)
{
	CMemory* pMemory = GetMemory();

	HideCaret();

	CDC* pDC = GetDC();
	pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
	pDC->SelectObject(&m_font);
	// まず入力した文字をいったん表示する
	pDC->TextOut(ptCaret.x, ptCaret.y, CString((BYTE)nChar));
	
	// 入力した値をメモリに設定
	UINT address = m_topLineAddress + (ptCaret.y / m_fontSize.cy - 1) * 8 + offset;
	pMemory->SetMemory(address, nChar);

	// 設定後、再度メモリからデータを取り込んで再表示する
	BYTE b = (BYTE)pMemory->GetMemory(address);
	pDC->TextOut(ptCaret.x, ptCaret.y, CString(b));

	// HEX表示も更新する
	CString text;
	text.Format("%04X", b);
	pDC->TextOut(c_leftMargin + (c_lenAddrArea + offset * 5) * m_fontSize.cx, ptCaret.y, text);
	
	ReleaseDC(pDC);

	MoveCaret(VK_RIGHT);
	if (offset == 7)
		MoveCaret(VK_RIGHT);
	ShowCaret();			

	CHintUpdateView hint;
	hint.m_locationAddress = address;
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_MEMORY, &hint);
}

BOOL CDumpView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (zDelta < 0) 
		OnVScroll(SB_LINEDOWN, 0, NULL);
	else if(zDelta > 0)
		OnVScroll(SB_LINEUP, 0, NULL);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CDumpView::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_CHAR)
	{
		if (pMsg->wParam == 0x07)		// Ctrl+G
		{
//			AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DUMP_GOTO, 0L);
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

UINT CDumpView::GetNextPageLocationAddress()
{
	CRect rcClient;
	GetClientRect(rcClient);

	int nLineCount = (rcClient.Height() - m_fontSize.cy) / m_fontSize.cy;
	if (nLineCount < 1)
		nLineCount = 1;

	int nAddr = m_topLineAddress + nLineCount * 0x08;
	if (nAddr > (c_maxMemory - 0x08))
		nAddr = (c_maxMemory - 0x08);
	return nAddr;
}

DROPEFFECT CDumpView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	m_dropEffect = DROPEFFECT_NONE;
	if (pDataObject->IsDataAvailable(cf_SYMBOL) || pDataObject->IsDataAvailable(cf_REGISTER))
		m_dropEffect = DROPEFFECT_COPY;
	return m_dropEffect;
}

DROPEFFECT CDumpView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return m_dropEffect;
}

BOOL CDumpView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	CHintUpdateView hint;
	if (pDataObject->IsDataAvailable(cf_SYMBOL))
	{
		HGLOBAL hGlobal = pDataObject->GetGlobalData(cf_SYMBOL);
		SYMBOLFORMAT* pSymbolValue = (SYMBOLFORMAT*)::GlobalLock(hGlobal);

		hint.m_locationAddress = pSymbolValue->value;
		::GlobalUnlock(hGlobal);
	}
	else if (pDataObject->IsDataAvailable(cf_REGISTER))
	{
		HGLOBAL hGlobal = pDataObject->GetGlobalData(cf_REGISTER);
		REGISTERFORMAT* pRegisterValue = (REGISTERFORMAT*)::GlobalLock(hGlobal);

		hint.m_locationAddress = pRegisterValue->value;
		::GlobalUnlock(hGlobal);
	}
	else
		return FALSE;

	GetDocument()->UpdateAllViews(NULL, UPDATEHINT_UPDATE_DUMPVIEW, &hint);
	SetFocus();
	return TRUE;
}



CMemory* CDumpView::GetMemory()
{
	CMightyCaslDoc* pDocument = GetDocument();
	return &pDocument->m_cometCore.m_memory;
}

void CDumpView::OnContextMenu(CWnd*, CPoint point)
{
/*
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_DUMP_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
*/
}
