// InputDeviceDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "mightycasl.h"
#include "InputDeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDeviceDlg �_�C�A���O


CInputDeviceDlg::CInputDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDeviceDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void CInputDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDeviceDlg)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDeviceDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDeviceDlg ���b�Z�[�W �n���h��
