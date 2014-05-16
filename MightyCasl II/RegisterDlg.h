#if !defined(AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
#define AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterDlg.h : �w�b�_�[ �t�@�C��
//
#include "Register.h"

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg �_�C�A���O

class CRegisterDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CRegisterDlg(int nRegID, CRegister* pRegister, CLabelBank* pLabelBank, CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRegisterDlg)
	enum { IDD = IDD_REGISTER };
	BOOL	m_bOverflow;
	BOOL	m_bSign;
	BOOL	m_bZero;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CRegister* m_pRegister;
	CLabelBank* m_pLabelBank;
	int m_nRegID;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRegisterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_REGISTERDLG_H__07F704FA_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
