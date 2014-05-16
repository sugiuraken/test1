#if !defined(AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg ダイアログ

class CWatchDlg : public CDialog
{
// コンストラクション
public:
	void SetDialogTitle(LPCSTR title);
	CWatchDlg(CLabelBank* pLabelBank, CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CWatchDlg)
	enum { IDD = IDD_WATCH };
	CSpinButtonCtrl	m_ctrlSpin;
	int		m_fmt;
	UINT	m_length;
	CString	m_target;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CWatchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CLabelBank* m_pLabelBank;
	static int maxLen[5];
	void SetSpinRange(int fmtType);
	CString m_title;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CWatchDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnFmtClicked(UINT nID);
	afx_msg void OnKickIdle();
	afx_msg void OnUpdateOkBtn(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_)
