#if !defined(AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnvironmentDLg.h : ヘッダー ファイル
//
#include "Environment.h"
/////////////////////////////////////////////////////////////////////////////
// CEnvironmentDlg ダイアログ

class CEnvironmentDlg : public CDialog
{
// コンストラクション
public:
	CEnvironmentDlg(CEnvironment* pEnvironment, CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CEnvironmentDlg)
	enum { IDD = IDD_ENVIRONMENT };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEnvironmentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	CEnvironment* m_pEnvironment;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEnvironmentDlg)
	afx_msg void OnRefSourcepath();
	afx_msg void OnRefOutfile();
	afx_msg void OnRefInfile();
	//}}AFX_MSG
	afx_msg void OnKickIdle();
	afx_msg void OnUpdateInFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutFile(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
