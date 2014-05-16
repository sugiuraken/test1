#if !defined(AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_)
#define AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceFrame.h : �w�b�_�[ �t�@�C��
//
#include "ChildFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CSourceFrame �t���[��

class CSourceFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CSourceFrame)
protected:
	CSourceFrame();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^�B

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�

	//{{AFX_VIRTUAL(CSourceFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CSplitterWnd m_wndSplitter;
	virtual ~CSourceFrame();

	void BackupWindowPos();
	void RestoreWindowPos();
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSourceFrame)
	afx_msg void OnToolAsm();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SOURCEFRAME_H__C0B76CA8_B658_11D3_AB2D_006067202C95__INCLUDED_)
