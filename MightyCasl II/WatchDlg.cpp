// WatchDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "WatchDlg.h"
#include "Register.h"

#include <afxpriv.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg ダイアログ


CWatchDlg::CWatchDlg(CLabelBank* pLabelBank, CWnd* pParent /*=NULL*/)
	: CDialog(CWatchDlg::IDD, pParent)
{
	m_pLabelBank = pLabelBank;
	//{{AFX_DATA_INIT(CWatchDlg)
	m_fmt = 0;
	m_length = 1;
	m_target = _T("");
	//}}AFX_DATA_INIT
}


void CWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWatchDlg)
	DDX_Control(pDX, IDC_SPIN_LENGTH, m_ctrlSpin);
	DDX_Radio(pDX, IDC_FMT_HEX, m_fmt);
	DDX_Text(pDX, IDC_LENGTH, m_length);
	DDX_Text(pDX, IDC_TARGET, m_target);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWatchDlg, CDialog)
	//{{AFX_MSG_MAP(CWatchDlg)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_FMT_HEX, IDC_FMT_CHAR, OnFmtClicked)
	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateOkBtn)
END_MESSAGE_MAP()


int CWatchDlg::maxLen[5] = {8, 8, 8, 4, 80};

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg メッセージ ハンドラ
void CWatchDlg::OnKickIdle()
{
	UpdateDialogControls(this, FALSE);
}

void CWatchDlg::OnUpdateOkBtn(CCmdUI* pCmdUI)
{	
	CString strTemp;
	GetDlgItemText(IDC_TARGET, strTemp);
	strTemp.TrimLeft();
	pCmdUI->Enable(strTemp.IsEmpty() ? FALSE : TRUE);
}


BOOL CWatchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	SetSpinRange(m_fmt);
	SetWindowText(m_title);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CWatchDlg::SetDialogTitle(LPCSTR title)
{
	m_title = title;
}

void CWatchDlg::SetSpinRange(int fmtType)
{
	m_ctrlSpin.SetRange(1, maxLen[fmtType]);
}

void CWatchDlg::OnFmtClicked(UINT nID)
{
	SetSpinRange(nID - IDC_FMT_HEX);
}

void CWatchDlg::OnOK() 
{
	UpdateData(TRUE);

	// 対象指定のチェック
	char ch = m_target[0];
	if (ch == '$')
	{
		int regId = CRegister::GetRegisterId(m_target.Mid(1));
		if (regId == -1 || regId >= REG_PC)
		{
			AfxMessageBox(IDS_ERR_BADWATCHTARGET_REG, MB_OK | MB_ICONEXCLAMATION);
			return;
		}
	}
	else if (ch == '#' || (ch >= 'A' && ch <= 'Z') || ch == '_')
	{
		WORD tempValue;
		if (!ConvertStringToValue(tempValue, m_target, m_pLabelBank))
		{
			AfxMessageBox(IDS_ERR_BADWATCHTARGET_NUM, MB_OK | MB_ICONEXCLAMATION);
			return;
		}
	}
	else
	{
		AfxMessageBox(IDS_ERR_BADWATCHTARGET, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	// 長さのチェック
	if (!(m_length > 0 && m_length <= (UINT)maxLen[m_fmt]))
	{
		CString strTemp;
		strTemp.Format("16進数形式表示 : 1～%d\n"
					   "符号付10進数形式表示 : 1～%d\n"
					   "符号無10進数形式表示 : 1～%d\n"
					   "2進数形式表示 : 1～%d\n"
					   "文字形式表示 : 1～%d",
					   maxLen[0], maxLen[1], maxLen[2], maxLen[3], maxLen[4]);

		CString msg;
		AfxFormatString1(msg, IDS_ERR_BADWATCHTARGET_LEN, strTemp);
		AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	EndDialog(IDOK);	
}

