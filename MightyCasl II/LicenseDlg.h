#if !defined(AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_)
#define AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenseDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg �_�C�A���O

class CLicenseDlg : public CDialog
{
// �R���X�g���N�V����
public:
	static BOOL CheckLicenseKey(LPCSTR id, LPCSTR key);
	CLicenseDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLicenseDlg)
	enum { IDD = IDD_LICENSE };
	CString	m_key;
	CString	m_id;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLicenseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLicenseDlg)
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnKickIdle();
	afx_msg void OnUpdateOkBtn(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LICENSEDLG_H__9711EB26_9F6A_4789_A0E0_04F741B72D07__INCLUDED_)
