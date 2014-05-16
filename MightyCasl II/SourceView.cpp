// SourceView.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSourceView �`��

void CSourceView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
}

/////////////////////////////////////////////////////////////////////////////
// CSourceView �f�f

#ifdef _DEBUG
void CSourceView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSourceView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
CMightyCaslDoc* CSourceView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSourceView ���b�Z�[�W �n���h��

void CSourceView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	CMightyCaslDoc* pDocument = GetDocument();
	
}

int CSourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString strFontFace("�l�r �S�V�b�N");
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

	// �ҏW�t�H���g��ݒ肷��
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	
	lf.lfCharSet = SHIFTJIS_CHARSET; 
	lf.lfHeight = pointFont * 10;			// 1/10 pt�P��
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

	int nLine = rEdit.LineFromChar();		// ���݂̍s�ԍ��𓾂�

	// �s�����ς�����̂ŁA�G���[���̍s�ԍ���␳����
	CHintUpdateView hint;
	hint.m_nLine = nLine + 1;
	hint.m_nDeltaLine = afterLineCount - m_beforeLineCount;
	GetDocument()->UpdateAllViews(this, UPDATEHINT_CHANGE_SRCLINE, &hint);
}

BOOL CSourceView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	return CEditView::PreCreateWindow(cs);
}



void CSourceView::GetCaretPosition(int &nLine, int &nCol)
{
    static int oldStart = -1, oldEnd = -1;
    static enum Direction { left, right } oldDir = right;

    CEdit& theEdit = GetEditCtrl();

    // �e�L�X�g���}�E�X�őI�����ꂽ�ꍇ�́A�I���̕����𔻕ʂ���K�v������B
    // �E�Ƀh���b�O����Ă���ꍇ�́A�I��͈͂̏I�_�ƂȂ镶�����d�v�ł���A
    // ���Ƀh���b�O����Ă���ꍇ�́A�I��͈͂̎n�_�ƂȂ镶�����d�v�ł���B
    // ���݂̑I����Ԃ𔻕ʂ���ɂ́A�Ō�̑I���ʒu���L�������Ă����K�v������B
    // �������܂������I������Ȃ��ꍇ�́AnewStart��newEnd���������Ȃ�B

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

    // �I��͈͓��̌��݂̕����Ɋ�Â��Č��݂̍s�𔻕ʂ���B
    // LineFromChar�̓[���x�[�X�Ȃ̂ŁA1��ǉ����Ȃ���΂Ȃ�Ȃ��B
    nLine = theEdit.LineFromChar(nCurrent) + 1;
    
    // nLineIndex�́AnLine�s�̍ŏ��̕����̃[���x�[�X�C���f�b�N�X�ł���B
    int nLineIndex = theEdit.LineIndex(nLine-1);
        
    // �L�����b�g�̗�ʒu�́AGetSel����擾���ꂽ���݂̈ʒu����s�C���f�b�N�X
    // �����������̂ł���B
    nCol = nCurrent - nLineIndex + 1;

}

void CSourceView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: ���̃u���b�N�̓|�b�v�A�b�v ���j���[ �R���|�[�l���g�ɂ���Ēǉ�����܂���
	{
		if (point.x == -1 && point.y == -1){
			//�L�[�X�g���[�N�̔���
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
