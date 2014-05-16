// LicenseDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "LicenseDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg ダイアログ


CLicenseDlg::CLicenseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenseDlg)
	m_key = _T("");
	m_id = _T("");
	//}}AFX_DATA_INIT
}


void CLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseDlg)
	DDX_Text(pDX, IDC_KEY, m_key);
	DDX_Text(pDX, IDC_ID, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenseDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateOkBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg メッセージ ハンドラ
void CLicenseDlg::OnKickIdle()
{
	UpdateDialogControls(this, FALSE);
}

void CLicenseDlg::OnUpdateOkBtn(CCmdUI* pCmdUI)
{	
	CString strTemp1, strTemp2;
	GetDlgItemText(IDC_KEY, strTemp1);
	GetDlgItemText(IDC_ID, strTemp2);
	pCmdUI->Enable(strTemp1.IsEmpty() || strTemp2.IsEmpty() ? FALSE : TRUE);
}


void CLicenseDlg::OnOK() 
{
	UpdateData(TRUE);

	if (!CheckLicenseKey(m_id, m_key))
	{
		AfxMessageBox(IDS_ERR_LICENSEKEY, MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	CDialog::OnOK();
}

BOOL CLicenseDlg::CheckLicenseKey(LPCSTR id, LPCSTR key)
{
	int idNum = atoi(id);

	if (strlen(id) != 7 || idNum == 0)
		return FALSE;

	const char* hint = "FREEWAY";
	BYTE buf[7];
	for (int i = 0; i < 7; i++)
		buf[i] = id[i] ^ hint[i] + idNum * 13;


	const char* table[] = 
	{
		"ABCDEFGHIJKLMNOP",
		"qrstuvwxyz012345",
		"6789abcdefghijkl",
		"mnopQRSTUVWXYZ01",
	};

	CString keyString;
	for (i = 0; i < 7; i++)
	{
		int hi = (buf[i] & 0xf0) >> 4;
		int lo = (buf[i] & 0x0f);
		keyString += table[i % 4][hi];
		keyString += table[i % 4][lo];
	}

	if (keyString != key)
		return FALSE;

	return TRUE;	
}
