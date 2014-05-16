// RegisterDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg ダイアログ


CRegisterDlg::CRegisterDlg(int nRegID, CRegister* pRegister, CLabelBank* pLabelBank, CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{
	m_nRegID = nRegID;
	m_pRegister = pRegister;
	m_pLabelBank = pLabelBank;
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_bOverflow = FALSE;
	m_bSign = FALSE;
	m_bZero = FALSE;
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Check(pDX, IDC_FR_OVERFLOW, m_bOverflow);
	DDX_Check(pDX, IDC_FR_SIGN, m_bSign);
	DDX_Check(pDX, IDC_FR_ZERO, m_bZero);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg メッセージ ハンドラ

BOOL CRegisterDlg::OnInitDialog() 
{
	WORD regFR = m_pRegister->GetValue(REG_FR);
	m_bOverflow = (regFR & REG_FR_VFLG) ? TRUE : FALSE;
	m_bSign = (regFR & REG_FR_SFLG) ? TRUE : FALSE;
	m_bZero = (regFR & REG_FR_ZFLG) ? TRUE : FALSE;
		
	CDialog::OnInitDialog();
	
	CString strTemp;
	for (int i = 0; i < 10; i++)
	{
		strTemp.Format("#%04X", m_pRegister->GetValue(REG_GR0 + i));
		SetDlgItemText(IDC_GR0 + i, strTemp);
	}

	CWnd* pFirstFocusWnd = NULL;
	if (m_nRegID == REG_FR)
		pFirstFocusWnd = GetDlgItem(IDC_FR_OVERFLOW);
	else
		pFirstFocusWnd = GetDlgItem(IDC_GR0 + m_nRegID);

	GotoDlgCtrl(pFirstFocusWnd);
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CRegisterDlg::OnOK() 
{
	UpdateData(TRUE);

	CString strTemp;
	WORD value[10];
	for (int i = 0; i < 10; i++)
	{
		GetDlgItemText(IDC_GR0 + i, strTemp);

		if (!ConvertStringToValue(value[i], strTemp, m_pLabelBank))
		{
			AfxMessageBox(IDS_ERR_SETREGISTER, MB_OK | MB_ICONEXCLAMATION);
			GotoDlgCtrl(GetDlgItem(IDC_GR0 + i));
			return;
		}
	}

	for (i = 0; i < 10; i++)
		m_pRegister->SetValue(REG_GR0 + i, value[i]);

	WORD regFR = 0;
	if (m_bOverflow)
		regFR |= REG_FR_VFLG;
	if (m_bSign)
		regFR |= REG_FR_SFLG;
	if (m_bZero)
		regFR |= REG_FR_ZFLG;

	m_pRegister->SetValue(REG_FR, regFR);

	CDialog::OnOK();
}
