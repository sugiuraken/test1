// MightyCaslDoc.cpp : CMightyCaslDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MightyCasl.h"

#include "MightyCaslDoc.h"
#include "SourceView.h"
#include "InputDeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslDoc

IMPLEMENT_DYNCREATE(CMightyCaslDoc, CDocument)

BEGIN_MESSAGE_MAP(CMightyCaslDoc, CDocument)
	//{{AFX_MSG_MAP(CMightyCaslDoc)
	ON_COMMAND(ID_EXEXUTE_STOP, OnExexuteStop)
	ON_UPDATE_COMMAND_UI(ID_EXEXUTE_STOP, OnUpdateExexuteStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslDoc クラスの構築/消滅

CMightyCaslDoc::CMightyCaslDoc()
{
	m_cometCore.m_pDocument = this;
	m_pOutputFile = NULL;
	m_pInputFile = NULL;
}

CMightyCaslDoc::~CMightyCaslDoc()
{
}

BOOL CMightyCaslDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_sourceFileName = "(無題)";
	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMightyCaslDoc シリアライゼーション

void CMightyCaslDoc::Serialize(CArchive& ar)
{
	CView* pView = NULL;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		CRuntimeClass* pRuntimeClass = pView->GetRuntimeClass();
		if (pRuntimeClass->m_lpszClassName == "CSourceView")
			break;
	}

	if (pView == NULL)
		return;

	CFile* pFile = ar.GetFile();
	CString strTemp;
	if (ar.IsStoring())
	{
		pView->GetWindowText(strTemp);
		pFile->Write(strTemp, strTemp.GetLength());
	}
	else
	{
		DWORD dwFileSize = pFile->GetLength();

		LPSTR p = strTemp.GetBuffer(dwFileSize + 1);
		pFile->Read(p, dwFileSize);
		strTemp.ReleaseBuffer(dwFileSize);

		pView->SetWindowText(strTemp);
	}
}

CView* CMightyCaslDoc::GetTargetView(LPCSTR className)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		CRuntimeClass* pRC = pView->GetRuntimeClass();
		if (!strcmp(pRC->m_lpszClassName, className))
			return pView;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslDoc クラスの診断

#ifdef _DEBUG
void CMightyCaslDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMightyCaslDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslDoc コマンド
BOOL CMightyCaslDoc::Assemble() 
{
	// 既にシミュレータフレームが開いていたらいったん閉じる
	CView* pSimulateView = GetTargetView("CSimulateView");
	if (pSimulateView)
	{
		CFrameWnd* pFrame = pSimulateView->GetParentFrame();
		if (pFrame)
			pFrame->SendMessage(WM_CLOSE);
	}

	// ソースビューからプログラムリストを取得する
	m_sourceLine.RemoveAll();

	CSourceView* pSourceView = (CSourceView*)GetTargetView("CSourceView");
	CString strTemp(pSourceView->LockBuffer());
	while (!strTemp.IsEmpty())
	{
		int nPos = strTemp.Find("\r\n");
		if (nPos == -1)
		{
			m_sourceLine.Add(strTemp);
			strTemp.Empty();
		}
		else
		{
			m_sourceLine.Add(strTemp.Left(nPos));
			strTemp = strTemp.Mid(nPos + 2);
		}
	}

	UpdateAllViews(NULL, UPDATEHINT_BEGIN_ASSEMBLE, NULL);

	for (int pass = 1; pass <= 2; pass++)
	{
		m_assembler.Initialize(pass);
		for (int i = 0; i < m_sourceLine.GetSize(); i++)
		{
			m_assembler.DoAssemble(m_sourceLine[i]);
//			if (m_assembler.m_bEnd)
//				break;				// END 命令なら終了
		}

		if (m_assembler.HaveError())
			break;
	}

	if (m_assembler.m_nStart == 0)
		m_assembler.m_errors.Add(new CAssembleError(-1, NULL, IDS_ASMERR_NOSTART));

	if (m_assembler.m_nStart != m_assembler.m_nEnd)
		m_assembler.m_errors.Add(new CAssembleError(-1, NULL, IDS_ASMERR_NOEND));

	if (m_assembler.HaveError())
	{
		CHintUpdateView hint;
		hint.m_pAssembler = &m_assembler;
		UpdateAllViews(NULL, UPDATEHINT_DISP_ASMERRORS, &hint);

		CString msg, fmt;

		fmt.LoadString(IDS_ERR_ASSEMBLE);
		msg.Format(fmt, m_assembler.m_errors.GetSize());
		AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	AfxMessageBox(IDS_MSG_ASMCOMPLETE, MB_OK | MB_ICONINFORMATION);

	ResetCore();

	CMightyCaslApp* pApp = (CMightyCaslApp*)AfxGetApp();
	CFrameWnd* pSimulatorFrame = pApp->OpenSimulatorFrame(this);
	if (pSimulatorFrame == NULL)
	{
		AfxMessageBox(IDS_ERR_OPENSIMULATORFRAME, MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;
}



BOOL CMightyCaslDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_sourceFileName = lpszPathName;
	return TRUE;
}

BOOL CMightyCaslDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_sourceFileName = lpszPathName;
	
	CView* pSoruceView = GetTargetView("CSourceView");
	if (pSoruceView)
	{
		CFrameWnd* pFrame = pSoruceView->GetParentFrame();
		if (pFrame)
		{
			CString strTemp;
			strTemp.Format("Source - %s", m_sourceFileName);
			pFrame->SetWindowText(strTemp);
		}
	}
	return CDocument::OnSaveDocument(lpszPathName);
}

void CMightyCaslDoc::CloseDeviceFiles()
{
	if (m_pInputFile)
	{
		TRY
		{
			m_pInputFile->Close();
		}
		CATCH (CFileException, fe) 
		{
			m_pInputFile->Abort();
		}
		END_CATCH
		delete m_pInputFile;
		m_pInputFile = NULL;
	}

	if (m_pOutputFile)
	{
		TRY
		{
			m_pOutputFile->Close();
		}
		CATCH (CFileException, fe) 
		{
			m_pOutputFile->Abort();
		}
		END_CATCH
		delete m_pOutputFile;
		m_pOutputFile = NULL;
	}

}

void CMightyCaslDoc::ResetCore()
{
	CloseDeviceFiles();
	m_cometCore.Init();

	// 開始アドレス設定
	m_cometCore.m_register.SetValue(REG_PC, m_assembler.m_startAddress);
	// スタックのシステムへの戻り番地 0x0000 を積む
	m_cometCore.m_memory.SetMemory(0xffff, 0x0000);
	m_cometCore.m_register.SetValue(REG_SP, 0xffff);


	m_assembler.OutputCode(&m_cometCore.m_memory);
	m_strDeviceAccess.RemoveAll();
}


void CMightyCaslDoc::ExecuteProgram(int mode, WORD breakAddr)
{

	CMnemonicArray* pMnemonics = m_assembler.GetMnemonics();
	m_cometCore.ExecuteGo(pMnemonics, mode, breakAddr);
	UpdateAllViews(NULL, UPDATEHINT_EXEC_BREAK, NULL);

}

void CMightyCaslDoc::OnExexuteStop() 
{
	m_cometCore.ExecuteStop();
}

void CMightyCaslDoc::OnUpdateExexuteStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);	
}

BOOL CMightyCaslDoc::InputDevice(CString &input)
{
	CHintUpdateView hint;

	CMightyCaslApp* pApp = (CMightyCaslApp*)AfxGetApp();
	CEnvironment& environment = pApp->m_environment;
	if (environment.m_inDeviceType == ENV_INDEVICE_CONSOLE)
	{
		CInputDeviceDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			input = dlg.m_edit;

			hint.m_string.Format("INPUT  : %s", input);
			m_strDeviceAccess.Add(hint.m_string);
			UpdateAllViews(NULL, UPDATEHINT_DEVICE_ACCESS, &hint);

			return TRUE;
		}
	}
	else
	{
		CString msg;
		if (m_pInputFile == NULL)
		{
			m_pInputFile = new CStdioFile();
			if (!m_pInputFile->Open(environment.m_inFileName, 
								   CFile::modeRead | CFile::typeText | CFile::shareDenyWrite))
			{
				AfxFormatString1(msg, IDS_ERR_INFILE_OPEN, environment.m_inFileName);
				AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
				delete m_pInputFile;
				m_pInputFile = NULL;
			}
		}
		if (m_pInputFile)
		{
			TRY
			{
				if (m_pInputFile->ReadString(input))
				{
					hint.m_string.Format("INPUT  : %s", input);
					m_strDeviceAccess.Add(hint.m_string);
					UpdateAllViews(NULL, UPDATEHINT_DEVICE_ACCESS, &hint);
					return TRUE;
				}
			}
			CATCH (CFileException, fe) 
			{
				m_pInputFile->Abort();
				AfxFormatString1(msg, IDS_ERR_INFILE_READ, environment.m_inFileName);
				AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
				delete m_pInputFile;
				m_pInputFile = NULL;
			}
			END_CATCH
		}
	}

	hint.m_string = "INPUT  : <EOF>";
	m_strDeviceAccess.Add(hint.m_string);
	UpdateAllViews(NULL, UPDATEHINT_DEVICE_ACCESS, &hint);
	return FALSE;
}

BOOL CMightyCaslDoc::OutputDevice(LPCSTR output)
{
	CMightyCaslApp* pApp = (CMightyCaslApp*)AfxGetApp();
	CEnvironment& environment = pApp->m_environment;

	if (environment.m_outDeviceType == ENV_OUTDEVICE_FILE)
	{
		CString msg;
		if (m_pOutputFile == NULL)
		{
			m_pOutputFile = new CStdioFile();
			if (!m_pOutputFile->Open(environment.m_outFileName, 
								   CFile::modeCreate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite))
			{
				AfxFormatString1(msg, IDS_ERR_OUTFILE_CREATE, environment.m_outFileName);
				AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
				delete m_pOutputFile;
				m_pOutputFile = NULL;
			}
		}
		if (m_pOutputFile)
		{
			TRY
			{
				m_pOutputFile->WriteString(output);
				m_pOutputFile->WriteString("\n");
			}
			CATCH (CFileException, fe) 
			{
				m_pOutputFile->Abort();
				AfxFormatString1(msg, IDS_ERR_OUTFILE_WRITE, environment.m_outFileName);
				AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
				delete m_pOutputFile;
				m_pOutputFile = NULL;
			}
			END_CATCH
		}
	}
	
	CHintUpdateView hint;
	hint.m_string.Format("OUTPUT : %s", output);
	m_strDeviceAccess.Add(hint.m_string);
	UpdateAllViews(NULL, UPDATEHINT_DEVICE_ACCESS, &hint);
	return TRUE;
}


