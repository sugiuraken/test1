// MightyCasl.h : MIGHTYCASL アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_MIGHTYCASL_H__788E89C4_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_MIGHTYCASL_H__788E89C4_F9E5_11D2_BECC_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル
#include "Environment.h"	// ClassView によって追加されました。

class CLabelBank;
CString ConvertBinaryString(WORD value);
BOOL ConvertStringToValue(WORD& resultValue, LPCSTR str, CLabelBank* pLabelBank = NULL);

////////////////////////////////////////////////////////////////////
// レジストリ
//

#define REG_ENTRY_WINDOW		"Window"
#define REG_KEY_SOURCEFRAME		"SourceFrame"
#define REG_KEY_SOURCESPLIT		"SourceSplit"
#define REG_KEY_SIMULATEFRAME	"SimulateFrame"
#define REG_KEY_SIMULATESPLIT	"SimulateSplit"
#define REG_KEY_MAINFRAME		"MainFrame"

#define REG_ENTRY_ENV			"Env"
#define REG_KEY_SOURCEPATH		"SourcePath"
#define REG_KEY_WORKVIEW		"WorkView"
#define REG_KEY_SAVEWATCHFLAG	"SaveWatch"
#define REG_KEY_INDEVICETYPE	"InDeviceType"
#define REG_KEY_OUTDEVICETYPE	"OutDeviceType"
#define REG_KEY_INFILENAME		"InFileName"
#define REG_KEY_OUTFILENAME		"OutFileName"
#define REG_KEY_INSTALLDATE		"Serial"


#define REG_KEY_SOURCEFONT		"SourceFont"		// "Fontface:Point"

#define REG_ENTRY_WATCH			"Watch"
#define REG_KEY_NUMBER			"Number"
#define REG_KEY_ELM				"%d"

#define REG_ENTRY_LICENSE		"License"
#define REG_KEY_ID				"Id"
#define REG_KEY_KEY				"Key"




////////////////////////////////////////////////////////////////////
// UpdateView のヒント
//
#define UPDATEHINT_UPDATE_MEMORY		0x100
#define UPDATEHINT_NEXT_DUMPVIEW		0x101
#define UPDATEHINT_UPDATE_DUMPVIEW		0x102
#define UPDATEHINT_UPDATE_SIMVIEW		0x103

#define UPDATEHINT_FILL_MEMORY			0x110
#define UPDATEHINT_PATTERN_MEMORY		0x111
#define UPDATEHINT_COPY_MEMORY			0x112
#define UPDATEHINT_CHANGE_MEMORY		0x113


#define UPDATEHINT_CHANGE_REGISTER		0x120

#define UPDATEHINT_CHANGE_BREAKPOINT	0x130

#define UPDATEHINT_EXEC_BREAK			0x200

#define UPDATEHINT_DEVICE_ACCESS		0x300				// m_string

#define UPDATEHINT_CHANGE_SRCLINE		0x500				// m_nLine, m_nDeltaLine
#define UPDATEHINT_GOTO_SRCLINE			0x600				// m_nLine;
#define UPDATEHINT_BEGIN_ASSEMBLE		0x700				// NULL
#define UPDATEHINT_DISP_ASMERRORS		0x800				// m_pAssembler

class CAssembler;
class CHintUpdateView : public CObject
{
public:
	CAssembler* m_pAssembler;
	int m_nLine;
	int m_nDeltaLine;
	WORD m_locationAddress;
	void* m_pParam;
	CString m_string;
};


extern const UINT cf_SYMBOL;
extern const UINT cf_REGISTER;

struct SYMBOLFORMAT
{
	WORD value;
	char name[16];
};

struct REGISTERFORMAT
{
	WORD value;
	char name[16];
};


/////////////////////////////////////////////////////////////////////////////
// CMightyCaslApp:
// このクラスの動作の定義に関しては MightyCasl.cpp ファイルを参照してください。
//

class CMightyCaslApp : public CWinApp
{
protected:
	BOOL GetVersion(CString& version);
public:
	CEnvironment m_environment;
	CFrameWnd* OpenSimulatorFrame(CDocument* pDocument);
	CMightyCaslApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMightyCaslApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CMightyCaslApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnToolEnv();
	afx_msg void OnHelpSupport();
	afx_msg void OnHelpDocumnet();
	afx_msg void OnToolLisence();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MIGHTYCASL_H__788E89C4_F9E5_11D2_BECC_006067202C95__INCLUDED_)
