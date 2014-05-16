// OutputView.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "mightycasl.h"
#include "MightyCaslDoc.h"
#include "OutputView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputView

IMPLEMENT_DYNCREATE(COutputView, CEditView)

COutputView::COutputView()
{
	m_pErrors = NULL;
}

COutputView::~COutputView()
{
}


BEGIN_MESSAGE_MAP(COutputView, CEditView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(COutputView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputView �`��

void COutputView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
}

/////////////////////////////////////////////////////////////////////////////
// COutputView �f�f

#ifdef _DEBUG
void COutputView::AssertValid() const
{
	CEditView::AssertValid();
}

void COutputView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMightyCaslDoc* COutputView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputView ���b�Z�[�W �n���h��

BOOL COutputView::PreCreateWindow(CREATESTRUCT& cs) 
{
	BOOL result = CEditView::PreCreateWindow(cs);
	cs.style |= ES_READONLY;
	return result;
}

void COutputView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHintUpdate = (CHintUpdateView*)pHint;
	switch (lHint)
	{
	case UPDATEHINT_BEGIN_ASSEMBLE:
		m_pErrors = NULL;
		DisplayErrors();
		break;
	case UPDATEHINT_DISP_ASMERRORS:
		m_pErrors = &pHintUpdate->m_pAssembler->m_errors;
		DisplayErrors();
		break;
	case UPDATEHINT_CHANGE_SRCLINE:
		AdjustErrorLineNumber(pHintUpdate->m_nLine, pHintUpdate->m_nDeltaLine);
		break;
	}
}

void COutputView::DisplayErrors()
{
	CString text;
	if (m_pErrors)
	{
		for (int i = 0; i < m_pErrors->GetSize(); i++)
		{
			CAssembleError* pError = m_pErrors->GetAt(i);
			text += pError->GetErrorMessage();
			text += "\r\n";
		}
	}
	SetWindowText(text);
}

void COutputView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (m_pErrors)
	{
		CEdit& rEdit = GetEditCtrl();
		int nLine = HIWORD(rEdit.CharFromPos(point));
		if (nLine < m_pErrors->GetSize())
		{
			CAssembleError* pError = m_pErrors->GetAt(nLine);
			int nSourceLine = pError->GetLineNumber();
			if (nSourceLine == -1)
				MessageBeep(MB_ICONEXCLAMATION);
			else
			{
				CHintUpdateView hint;
				hint.m_nLine = nSourceLine;
				GetDocument()->UpdateAllViews(this, UPDATEHINT_GOTO_SRCLINE, &hint);
			}
		}
	}	
//	CEditView::OnLButtonDblClk(nFlags, point);
}

int COutputView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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


void COutputView::AdjustErrorLineNumber(int nLine, int deltaLine)
{
	if (m_pErrors == NULL)
		return;

	if (deltaLine > 0)
	{
		for (int i = 0; i < m_pErrors->GetSize(); i++)
		{
			CAssembleError* pError = m_pErrors->GetAt(i);
			int nErrorNumber = pError->GetLineNumber();
			if (nErrorNumber >= nLine - deltaLine)
				pError->SetLineNumber(nErrorNumber + deltaLine);
		}
	}
	else
	{
		for (int i = 0; i < m_pErrors->GetSize(); i++)
		{
			CAssembleError* pError = m_pErrors->GetAt(i);
			int nErrorNumber = pError->GetLineNumber();
			if (nErrorNumber >= nLine)
			{
				if (nErrorNumber < nLine - deltaLine)
					pError->SetLineNumber(-1);
				else
					pError->SetLineNumber(nErrorNumber + deltaLine);
			}
		}
	}
}

HBRUSH COutputView::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: �e�n���h�����Ăяo�������Ȃ��ꍇ�͂����Ńu���V�̃n���h���Ƃ��� NULL �ȊO��Ԃ��悤�ɂ��Ă�������
	return NULL;
}

void COutputView::OnContextMenu(CWnd*, CPoint point)
{
/*
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_OUTPUT_VIEW));

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
