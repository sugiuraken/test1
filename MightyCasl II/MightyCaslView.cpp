// MightyCaslView.cpp : CMightyCaslView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "MightyCasl.h"

#include "MightyCaslDoc.h"
#include "MightyCaslView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView

IMPLEMENT_DYNCREATE(CMightyCaslView, CView)

BEGIN_MESSAGE_MAP(CMightyCaslView, CView)
	//{{AFX_MSG_MAP(CMightyCaslView)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView �N���X�̍\�z/����

CMightyCaslView::CMightyCaslView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMightyCaslView::~CMightyCaslView()
{
}

BOOL CMightyCaslView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView �N���X�̕`��

void CMightyCaslView::OnDraw(CDC* pDC)
{
	CMightyCaslDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView �N���X�̐f�f

#ifdef _DEBUG
void CMightyCaslView::AssertValid() const
{
	CView::AssertValid();
}

void CMightyCaslView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMightyCaslDoc* CMightyCaslView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView �N���X�̃��b�Z�[�W �n���h��

