#if !defined(AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_)
#define AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDeviceDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CInputDeviceDlg �_�C�A���O

class CInputDeviceDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CInputDeviceDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CInputDeviceDlg)
	enum { IDD = IDD_INPUT_DEVICE };
	CString	m_edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CInputDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CInputDeviceDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_INPUTDEVICEDLG_H__F4F31453_E446_11D3_BD98_0000E8647D2D__INCLUDED_)
