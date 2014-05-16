#if !defined(AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg �_�C�A���O

class CWatchDlg : public CDialog
{
// �R���X�g���N�V����
public:
	void SetDialogTitle(LPCSTR title);
	CWatchDlg(CLabelBank* pLabelBank, CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CWatchDlg)
	enum { IDD = IDD_WATCH };
	CSpinButtonCtrl	m_ctrlSpin;
	int		m_fmt;
	UINT	m_length;
	CString	m_target;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CWatchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CLabelBank* m_pLabelBank;
	static int maxLen[5];
	void SetSpinRange(int fmtType);
	CString m_title;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_WATCHDLG_H__4FA4C1C0_DE94_11D3_AB2F_006067202C95__INCLUDED_)
