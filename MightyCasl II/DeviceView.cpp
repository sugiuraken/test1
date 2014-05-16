// DeviceView.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "mightycasl.h"
#include "DeviceView.h"
#include "MightyCaslDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceView

IMPLEMENT_DYNCREATE(CDeviceView, CEditView)

CDeviceView::CDeviceView()
{
}

CDeviceView::~CDeviceView()
{
}


BEGIN_MESSAGE_MAP(CDeviceView, CEditView)
	//{{AFX_MSG_MAP(CDeviceView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceView �`��

void CDeviceView::OnDraw(CDC* pDC)
{
	CMightyCaslDoc* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
}

/////////////////////////////////////////////////////////////////////////////
// CDeviceView �f�f

#ifdef _DEBUG
void CDeviceView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDeviceView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMightyCaslDoc* CDeviceView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDeviceView ���b�Z�[�W �n���h��

BOOL CDeviceView::PreCreateWindow(CREATESTRUCT& cs) 
{
	BOOL result = CEditView::PreCreateWindow(cs);
	cs.style |= ES_READONLY;
	return result;
}

int CDeviceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CDeviceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CHintUpdateView* pHintUpdate = (CHintUpdateView*)pHint;
	switch (lHint)
	{
	case UPDATEHINT_DEVICE_ACCESS:
		AppendString(pHintUpdate->m_string);
		break;
	}
}

void CDeviceView::AppendString(LPCSTR text)
{
	CEdit& rEditCtrl = GetEditCtrl();
	int nLine = rEditCtrl.GetLineCount();
	if (nLine > 1000)
	{
		int nChar = rEditCtrl.LineIndex(1);
		rEditCtrl.SetSel(0, nChar, TRUE);
		rEditCtrl.ReplaceSel("");
	}
	
	LPCSTR p = LockBuffer();
	int nLen = strlen(p);
	UnlockBuffer();


	CString strTemp;
	strTemp.Format("%s\r\n", text);
	rEditCtrl.SetSel(nLen, nLen);
	rEditCtrl.ReplaceSel(strTemp);
}

void CDeviceView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	CMightyCaslDoc* pDocument = GetDocument();
	for (int i = 0; i < pDocument->m_strDeviceAccess.GetSize(); i++)
		AppendString(pDocument->m_strDeviceAccess[i]);
	
}
