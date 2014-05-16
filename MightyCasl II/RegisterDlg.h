#if !defined(AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
#define AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterDlg.h : ヘッダー ファイル
//
#include "Register.h"

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg ダイアログ

class CRegisterDlg : public CDialog
{
// コンストラクション
public:
	CRegisterDlg(int nRegID, CRegister* pRegister, CLabelBank* pLabelBank, CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRegisterDlg)
	enum { IDD = IDD_REGISTER };
	BOOL	m_bOverflow;
	BOOL	m_bSign;
	BOOL	m_bZero;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CRegister* m_pRegister;
	CLabelBank* m_pLabelBank;
	int m_nRegID;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRegisterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
