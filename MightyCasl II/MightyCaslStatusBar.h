#if !defined(AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_)
#define AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MightyCaslStatusBar.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslStatusBar �E�B���h�E

class CMightyCaslStatusBar : public CStatusBar
{
// �R���X�g���N�V����
public:
	CMightyCaslStatusBar();

// �A�g���r���[�g
public:
	CProgressCtrl& GetProgressCtrl() {return m_meter;}
// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CMightyCaslStatusBar)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CMightyCaslStatusBar();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	CProgressCtrl m_meter;
	//{{AFX_MSG(CMightyCaslStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MIGHTYCASLSTATUSBAR_H__776D2546_DDD0_11D3_BD8F_0000E8647D2D__INCLUDED_)
