#if !defined(AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnvironmentDLg.h : �w�b�_�[ �t�@�C��
//
#include "Environment.h"
/////////////////////////////////////////////////////////////////////////////
// CEnvironmentDlg �_�C�A���O

class CEnvironmentDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CEnvironmentDlg(CEnvironment* pEnvironment, CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CEnvironmentDlg)
	enum { IDD = IDD_ENVIRONMENT };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEnvironmentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	CEnvironment* m_pEnvironment;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ENVIRONMENTDLG_H__28A2ACC2_DF4A_11D3_AB2F_006067202C95__INCLUDED_)
