// EnvironmentDLg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mightycasl.h"
#include "EnvironmentDlg.h"
#include <shlobj.h>
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnvironmentDlg ダイアログ


CEnvironmentDlg::CEnvironmentDlg(CEnvironment* pEnvironment, CWnd* pParent /*=NULL*/)
	: CDialog(CEnvironmentDlg::IDD, pParent)
{
	m_pEnvironment = pEnvironment;
	//{{AFX_DATA_INIT(CEnvironmentDlg)
	//}}AFX_DATA_INIT
}


void CEnvironmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SOURCEPATH, m_pEnvironment->m_defaultSourcePath);
	DDX_Radio(pDX, IDC_WORKVIEW_DUMP, m_pEnvironment->m_defaultWorkView);
	DDX_Radio(pDX, IDC_IN_CONSOLE, m_pEnvironment->m_inDeviceType);
	DDX_Text(pDX, IDC_IN_FILENAME, m_pEnvironment->m_inFileName);
	DDX_Radio(pDX, IDC_OUT_CONSOLE, m_pEnvironment->m_outDeviceType);
	DDX_Text(pDX, IDC_OUT_FILENAME, m_pEnvironment->m_outFileName);
	DDX_Check(pDX, IDC_SAVE_WATCH, m_pEnvironment->m_bSaveWatchElm);
	//{{AFX_DATA_MAP(CEnvironmentDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnvironmentDlg, CDialog)
	//{{AFX_MSG_MAP(CEnvironmentDlg)
	ON_BN_CLICKED(IDC_REF_SOURCEPATH, OnRefSourcepath)
	ON_BN_CLICKED(IDC_REF_OUTFILE, OnRefOutfile)
	ON_BN_CLICKED(IDC_REF_INFILE, OnRefInfile)
	//}}AFX_MSG_MAP
	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_IN_FILENAME, OnUpdateInFile)
	ON_UPDATE_COMMAND_UI(IDC_REF_INFILE, OnUpdateInFile)
	ON_UPDATE_COMMAND_UI(IDC_OUT_FILENAME, OnUpdateOutFile)
	ON_UPDATE_COMMAND_UI(IDC_REF_OUTFILE, OnUpdateOutFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnvironmentDlg メッセージ ハンドラ
void CEnvironmentDlg::OnKickIdle()
{
	UpdateDialogControls(this, FALSE);
}

void CEnvironmentDlg::OnUpdateInFile(CCmdUI* pCmdUI)
{	
	CButton* pButton = (CButton*)GetDlgItem(IDC_IN_FILE);
	pCmdUI->Enable(pButton->GetCheck() ? TRUE : FALSE);
}

void CEnvironmentDlg::OnUpdateOutFile(CCmdUI* pCmdUI)
{	
	CButton* pButton = (CButton*)GetDlgItem(IDC_OUT_FILE);
	pCmdUI->Enable(pButton->GetCheck() ? TRUE : FALSE);
}

int CALLBACK CEnvironmentDlg::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED && lpData)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	return 0;
}

void CEnvironmentDlg::OnRefSourcepath() 
{
	CString strFolder;
	GetDlgItemText(IDC_SOURCEPATH, strFolder);

	BROWSEINFO lpbi;
	lpbi.hwndOwner = GetSafeHwnd();
	lpbi.pidlRoot = NULL;
	lpbi.pszDisplayName = NULL;
	lpbi.lpfn = BrowseCallbackProc;

	CString title;
	title.LoadString(IDS_SOURCEPATHREF_TITLE);
	lpbi.lpszTitle = title;
	lpbi.ulFlags = BIF_RETURNONLYFSDIRS;
	lpbi.lParam = (LPARAM)(LPCSTR)strFolder;

	LPITEMIDLIST list = ::SHBrowseForFolder(&lpbi);	// 選択アプリのポインタ
	if ( !list )
		return;
	
	::SHGetPathFromIDList(list, strFolder.GetBuffer(MAX_PATH));		//	pathをとる
	strFolder.ReleaseBuffer();
	SetDlgItemText(IDC_SOURCEPATH, strFolder);

	LPMALLOC pMalloc;
	::SHGetMalloc(&pMalloc);
	pMalloc->Free(list);
	pMalloc->Release();
}

void CEnvironmentDlg::OnRefOutfile() 
{
	CString strFilter;
	strFilter.LoadString(IDS_TEXTFILE_ACCESS_FILTER);
	CFileDialog dlg(FALSE, "txt", "*.txt", OFN_HIDEREADONLY, strFilter, this);

	CString strTemp;
	GetDlgItemText(IDC_OUT_FILENAME, strTemp);
	dlg.m_ofn.lpstrInitialDir = strTemp;
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_OUT_FILENAME, dlg.GetPathName());
}

void CEnvironmentDlg::OnRefInfile() 
{
	CString strFilter;
	strFilter.LoadString(IDS_TEXTFILE_ACCESS_FILTER);

	CString strTemp;
	CFileDialog dlg(TRUE, "txt", "*.txt", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, strFilter, this);
	GetDlgItemText(IDC_IN_FILENAME, strTemp);
	dlg.m_ofn.lpstrInitialDir = strTemp;
	if (dlg.DoModal() == IDOK) 
		SetDlgItemText(IDC_IN_FILENAME, dlg.GetPathName());
}
