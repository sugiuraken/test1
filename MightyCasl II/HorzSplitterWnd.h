#if !defined(AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_)
#define AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HorzSplitterWnd.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd �E�B���h�E

class CHorzSplitterWnd : public CSplitterWnd
{
// �R���X�g���N�V����
public:
	CHorzSplitterWnd();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CHorzSplitterWnd)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CHorzSplitterWnd();

protected:
	virtual void TrackRowSize(int y, int row);
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CHorzSplitterWnd)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HORZSPLITTERWND_H__2F7C1F61_B723_11D2_B671_0000010122DC__INCLUDED_)
