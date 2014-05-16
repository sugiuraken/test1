#if !defined(AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_)
#define AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenseDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg ダイアログ

class CLicenseDlg : public CDialog
{
// コンストラクション
public:
	static BOOL CheckLicenseKey(LPCSTR id, LPCSTR key);
	CLicenseDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLicenseDlg)
	enum { IDD = IDD_LICENSE };
	CString	m_key;
	CString	m_id;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLicenseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLicenseDlg)
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnKickIdle();
	afx_msg void OnUpdateOkBtn(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_)
