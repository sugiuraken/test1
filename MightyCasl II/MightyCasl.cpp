// MightyCasl.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "MightyCasl.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MightyCaslDoc.h"
#include "MightyCaslView.h"
#include "SourceView.h"

#include "MightyCaslFrame.h"
#include "SourceFrame.h"
#include "EnvironmentDlg.h"
#include "LicenseDlg.h"

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT cf_SYMBOL = ::RegisterClipboardFormat("SYMBOLFORMAT");
const UINT cf_REGISTER = ::RegisterClipboardFormat("REGISTERFORMAT");

/////////////////////////////////////////////////////////////////////////////////
// グローバル関数

CString ConvertBinaryString(WORD value)
{
	CString text;
	for (int i = 0; i < 16; i++)
	{
		text += CString((value & (1 << (15 - i))) ? "1" : "0");
		if (i % 4 == 3)
			text += " ";
	}
	text = text.Left(16 + 3);
	return text;
}

BOOL ConvertStringToValue(WORD& resultValue, LPCSTR str, CLabelBank* pLabelBank)
{
	CString strTemp(str);
	if (strTemp.GetLength() == 0)
		return FALSE;

	char ch = strTemp[0];
	if (ch == '#')
	{
		strTemp = strTemp.Mid(1);
		if (strTemp.GetLength() == 0)
			return FALSE;

		char* endptr;
		resultValue = (WORD)strtoul((LPCSTR)strTemp, &endptr, 16);
		if (*endptr != '\0')
			return FALSE;
	}
	else if (ch == '%')
	{
		strTemp = strTemp.Mid(1);
		int nLen = strTemp.GetLength();
		if (nLen == 0)
			return FALSE;

		resultValue = 0;
		for (int i = 0; i < nLen; i++)
		{
			resultValue <<= 1;
			if (strTemp[i] == '0')
				;
			else if (strTemp[i] == '1')
				resultValue++;
			else
				return FALSE;
		}
	}
	else if (ch == '\'')
	{
		strTemp = strTemp.Mid(1);
		int nLen = strTemp.GetLength();
		if (nLen != 1)
			return FALSE;

		resultValue = strTemp[0];
	}
	else if ((ch >= 'A' && ch <= 'Z') || ch == '_')
	{
		if (pLabelBank == NULL)
			return FALSE;

		CLabel* pLabel;
		if (!pLabelBank->Lookup(strTemp, pLabel))
			return FALSE;
		resultValue = pLabel->m_value;
	}
	else
	{
		char* endptr;
		resultValue = (WORD)strtol((LPCSTR)strTemp, &endptr, 10);
		if (*endptr != '\0')
			return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslApp

BEGIN_MESSAGE_MAP(CMightyCaslApp, CWinApp)
	//{{AFX_MSG_MAP(CMightyCaslApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_TOOL_ENV, OnToolEnv)
	ON_COMMAND(ID_HELP_SUPPORT, OnHelpSupport)
	ON_COMMAND(ID_HELP_DOCUMNET, OnHelpDocumnet)
	ON_COMMAND(ID_TOOL_LISENCE, OnToolLisence)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslApp クラスの構築

CMightyCaslApp::CMightyCaslApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMightyCaslApp オブジェクト

CMightyCaslApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslApp クラスの初期化

BOOL CMightyCaslApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。
	// OLE ライブラリの初期化
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

	// 設定が保存される下のレジストリ キーを変更します。
	// TODO: この文字列を、会社名または所属など適切なものに
	// 変更してください。
	SetRegistryKey(_T("FREEWAY"));

	// インストール時刻を設定
	time_t serial = GetProfileInt(REG_ENTRY_ENV, REG_KEY_INSTALLDATE, 0);
	if (serial == 0)
	{
		CTime time = CTime::GetCurrentTime();
		WriteProfileInt(REG_ENTRY_ENV, REG_KEY_INSTALLDATE, time.GetTime());
	}


	m_environment.GetProfile(this);
	if (m_environment.m_defaultSourcePath)
	{
//		_chdir(m_environment.m_defaultSourcePath);
		SetCurrentDirectory(m_environment.m_defaultSourcePath);
	}

	
	LoadStdProfileSettings();  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MIGHTYTYPE,
		RUNTIME_CLASS(CMightyCaslDoc),
		RUNTIME_CLASS(CMightyCaslFrame), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CMightyCaslView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(
		IDR_SOURCETYPE,
		RUNTIME_CLASS(CMightyCaslDoc),
		RUNTIME_CLASS(CSourceFrame), // カスタム MDI 子フレーム
		RUNTIME_CLASS(CMightyCaslView));
	AddDocTemplate(pDocTemplate);

	// メイン MDI フレーム ウィンドウを作成
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンドラインでディスパッチ コマンドを指定します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	CString id = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_ID, NULL);
	CString key = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_KEY, NULL);
	if (!CLicenseDlg::CheckLicenseKey(id, key))
	{
		CTime curDate = CTime::GetCurrentTime();
		time_t serial = GetProfileInt(REG_ENTRY_ENV, REG_KEY_INSTALLDATE, 0);
		serial += 60 * 60 * 24 * 40;		// 40日の試用期間
		if (curDate > CTime(serial))
		{
			AfxMessageBox(IDS_MSG_OVERDATE, MB_OK | MB_ICONEXCLAMATION);
			OnToolLisence();
			id = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_ID, NULL);
			key = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_KEY, NULL);
			if (!CLicenseDlg::CheckLicenseKey(id, key))
			{
				AfxMessageBox(IDS_MSG_OVERDATE_EXIT, MB_OK | MB_ICONEXCLAMATION);
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox(IDS_MSG_TRIAL, MB_OK | MB_ICONINFORMATION);
		}
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_version;
	CString	m_submsg;
	//}}AFX_DATA

	// ClassWizard 仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_version = _T("");
	m_submsg = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_VERSION, m_version);
	DDX_Text(pDX, IDC_SUBMSG, m_submsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CMightyCaslApp::OnAppAbout()
{
	CAboutDlg aboutDlg;

	CString id = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_ID, NULL);
	CString key = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_KEY, NULL);
	BOOL bValidLicense = CLicenseDlg::CheckLicenseKey(id, key);

	time_t serial = GetProfileInt(REG_ENTRY_ENV, REG_KEY_INSTALLDATE, 0);
	serial += 60 * 60 * 24 * 40;		// 40日の試用期間

	CString version;
	GetVersion(version);

	aboutDlg.m_version = version;
	if (bValidLicense)
		aboutDlg.m_submsg.Format("ﾗｲｾﾝｽID : %s", id);
	else
	{
		CTime time(serial);
		aboutDlg.m_submsg.Format("お試し期限 : %04d年%02d月%02d日", 
									time.GetYear(), time.GetMonth(), time.GetDay());
	}
//	aboutDlg.m_submsg = "ベータ版";
	aboutDlg.DoModal();
	// テスト
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslApp メッセージ ハンドラ

void CMightyCaslApp::OnFileNew() 
{
	POSITION pos = GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);
		CString fileNewName;
		pTemplate->GetDocString(fileNewName, CDocTemplate::fileNewName);
		if (fileNewName == "Editor")
		{
			POSITION pos = pTemplate->GetFirstDocPosition();
			if (pos)
			{
				CDocument* pDocument = pTemplate->GetNextDoc(pos);
				if (!pDocument->SaveModified())
					return;
				pDocument->OnCloseDocument();
			}
			pTemplate->OpenDocumentFile(NULL);
			break;
		}
	}
}

void CMightyCaslApp::OnFileOpen() 
{
	POSITION pos = GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);
		CString fileNewName;
		pTemplate->GetDocString(fileNewName, CDocTemplate::fileNewName);
		if (fileNewName == "Editor")
		{
			POSITION pos = pTemplate->GetFirstDocPosition();
			if (pos)
			{
				CDocument* pDocument = pTemplate->GetNextDoc(pos);
				if (!pDocument->SaveModified())
					return;
				pDocument->OnCloseDocument();
			}
			CWinApp::OnFileOpen();
			break;
		}
	}
//	CWinApp::OnFileOpen();
}

CDocument* CMightyCaslApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	POSITION pos = GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);
		CString fileNewName;
		pTemplate->GetDocString(fileNewName, CDocTemplate::fileNewName);
		if (fileNewName == "Editor")
		{
			POSITION pos = pTemplate->GetFirstDocPosition();
			if (pos)
			{
				CDocument* pDocument = pTemplate->GetNextDoc(pos);
				if (!pDocument->SaveModified())
					return NULL;
				pDocument->OnCloseDocument();
			}
			return pTemplate->OpenDocumentFile(lpszFileName);
		}
	}
	return NULL;
}

CFrameWnd* CMightyCaslApp::OpenSimulatorFrame(CDocument* pDocument)
{
	POSITION pos = GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);
		CString fileNewName;
		pTemplate->GetDocString(fileNewName, CDocTemplate::fileNewName);
		if (fileNewName == "Simulator")
		{
			CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, NULL);
			if (pFrame == NULL)
				return NULL;
			pTemplate->InitialUpdateFrame(pFrame, pDocument);
			return pFrame;
		}
	}
	return NULL;
}


void CMightyCaslApp::OnToolEnv() 
{
	CEnvironmentDlg dlg(&m_environment);
	if (dlg.DoModal() == IDOK)
		m_environment.WriteProfile(this);
}

BOOL CMightyCaslApp::GetVersion(CString& version)
{
	TCHAR filename[_MAX_PATH];
	// モジュール名を得る
	DWORD len = GetModuleFileName(NULL, filename, sizeof(filename) / sizeof(filename[0]));
	if (len <= 0)
		return FALSE;

	DWORD dwDummyHandle;
	len = GetFileVersionInfoSize(filename, &dwDummyHandle);
	if (len <= 0)
		return FALSE;

	BOOL result = FALSE;
	LPBYTE pVersionInfo = new BYTE[len];
	if (::GetFileVersionInfo(filename, 0, len, pVersionInfo))
	{
		VS_FIXEDFILEINFO* lpvi;
		UINT iLen;
		if (VerQueryValue(pVersionInfo, _T("\\"), (LPVOID*)&lpvi, &iLen))
		{
			version.Format("%hd.%hd.%hd.%hd", 
								HIWORD(lpvi->dwProductVersionMS), LOWORD(lpvi->dwProductVersionMS),
								HIWORD(lpvi->dwProductVersionLS), LOWORD(lpvi->dwProductVersionLS));
			result = TRUE;
		}
	}
	delete [] pVersionInfo;
	return result;
}

void CMightyCaslApp::OnHelpSupport() 
{
	::ShellExecute(NULL, "open", "http://www2.tba.t-com.ne.jp/sken/", NULL, NULL, SW_SHOWNORMAL );	
}

void CMightyCaslApp::OnHelpDocumnet() 
{
	char path[MAX_PATH];
	::GetModuleFileName(NULL, path, MAX_PATH);
	char* cp = strrchr(path, '\\');
	*(cp + 1) = '\0';

	CString helpFile;
	helpFile.Format("%sHelp\\mightycasl.htm", path);

	::ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);	
		
}

void CMightyCaslApp::OnToolLisence() 
{
//	AfxMessageBox("ベータ版のためライセンス設定の必要はありません", MB_OK | MB_ICONINFORMATION);
//	return;

	CLicenseDlg dlg;
	
	dlg.m_id = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_ID, NULL);
	dlg.m_key = GetProfileString(REG_ENTRY_LICENSE, REG_KEY_KEY, NULL);

	if (dlg.DoModal() == IDCANCEL)
		return;

	WriteProfileString(REG_ENTRY_LICENSE, REG_KEY_ID, dlg.m_id);
	WriteProfileString(REG_ENTRY_LICENSE, REG_KEY_KEY, dlg.m_key);
}
