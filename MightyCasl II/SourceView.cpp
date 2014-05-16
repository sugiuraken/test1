// SourceView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MightyCasl.h"
#include "MightyCaslDoc.h"
#include "SourceView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceView

IMPLEMENT_DYNCREATE(CSourceView, CEditView)

CSourceView::CSourceView()
{
}

CSourceView::~CSourceView()
{
}


BEGIN_MESSAGE_MAP(CSourceView, CEditView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CSourceView)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceView 描画

void CSourceView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CSourceView 診断

#ifdef _DEBUG
void CSourceView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSourceView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
CMightyCaslDoc* CSourceView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSourceView メッセージ ハンドラ

void CSourceView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	CMightyCaslDoc* pDocument = GetDocument();
	
}

int CSourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
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

	ReleaseDC(pDC);
	return 0;
}

void CSourceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHintUpdate = (CHintUpdateView*)pHint;
	switch (lHint)
	{
	case UPDATEHINT_GOTO_SRCLINE:
		GotoSourceLine(pHintUpdate->m_nLine - 1);
		break;
	}
}

void CSourceView::GotoSourceLine(int nLine)
{
	CEdit& rEdit = GetEditCtrl();

	int nChar = rEdit.LineIndex(nLine);
	rEdit.SetSel(nChar, nChar);
	SetFocus();
}

void CSourceView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEdit& rEdit = GetEditCtrl();
	m_beforeLineCount = rEdit.GetLineCount();
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSourceView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEditView::OnKeyUp(nChar, nRepCnt, nFlags);

	CEdit& rEdit = GetEditCtrl();
	int afterLineCount = rEdit.GetLineCount();
	if (m_beforeLineCount == afterLineCount)
		return;

	int nLine = rEdit.LineFromChar();		// 現在の行番号を得る

	// 行数が変わったので、エラー情報の行番号を補正する
	CHintUpdateView hint;
	hint.m_nLine = nLine + 1;
	hint.m_nDeltaLine = afterLineCount - m_beforeLineCount;
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_SRCLINE, &hint);
}

BOOL CSourceView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CEditView::PreCreateWindow(cs);
}



void CSourceView::GetCaretPosition(int &nLine, int &nCol)
{
    static int oldStart = -1, oldEnd = -1;
    static enum Direction { left, right } oldDir = right;

    CEdit& theEdit = GetEditCtrl();

    // テキストがマウスで選択された場合は、選択の方向を判別する必要がある。
    // 右にドラッグされている場合は、選択範囲の終点となる文字が重要であり、
    // 左にドラッグされている場合は、選択範囲の始点となる文字が重要である。
    // 現在の選択状態を判別するには、最後の選択位置を記憶させておく必要がある。
    // 文字がまったく選択されない場合は、newStartとnewEndが等しくなる。

    Direction newDir = right;
    int newStart, newEnd, nCurrent;
    theEdit.GetSel(newStart, newEnd);

    if ( (newEnd == oldEnd) && (newStart == oldStart))
            newDir = oldDir;
    else if (oldStart == newStart) 
            newDir = right;
    else if (oldEnd == newEnd)
            newDir = left;
    else if (oldStart == newEnd)
            newDir = left;
    else if (oldEnd == newStart)
            newDir = right;
        
    if (newDir == right)
            nCurrent = newEnd;
    else 
            nCurrent = newStart; 
        
    oldStart = newStart;
    oldEnd = newEnd;
    oldDir = newDir;

    // 選択範囲内の現在の文字に基づいて現在の行を判別する。
    // LineFromCharはゼロベースなので、1を追加しなければならない。
    nLine = theEdit.LineFromChar(nCurrent) + 1;
    
    // nLineIndexは、nLine行の最初の文字のゼロベースインデックスである。
    int nLineIndex = theEdit.LineIndex(nLine-1);
        
    // キャレットの列位置は、GetSelから取得された現在の位置から行インデックス
    // を引いたものである。
    nCol = nCurrent - nLineIndex + 1;

}

void CSourceView::OnContextMenu(CWnd*, CPoint point)
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_SOURCE_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}
