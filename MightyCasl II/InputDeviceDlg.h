#if !defined(AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_)
#define AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDeviceDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CInputDeviceDlg ダイアログ

class CInputDeviceDlg : public CDialog
{
// コンストラクション
public:
	CInputDeviceDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputDeviceDlg)
	enum { IDD = IDD_INPUT_DEVICE };
	CString	m_edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CInputDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CInputDeviceDlg)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_)
