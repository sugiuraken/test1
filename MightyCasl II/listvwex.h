#if !defined(AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SymbolView.h : �w�b�_�[ �t�@�C��
// ListVwEx.h : CListViewEx �N���X�̃C���^�[�t�F�C�X
//
// ���̃N���X�̓��|�[�g ���[�h�̃��X�g �r���[ �R���g���[���ɑ΂���
// �s�S�̂̑I�����[�h��񋟂��܂��B
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// ���̃\�[�X �R�[�h�� Microsoft Foundation Class ���t�@�����X����сA
// �֘A����I�����C�� �h�L�������g�̕⑫�݂̂�ړI�Ƃ��Ă��܂��B
// Microsoft Foundation Class ���i�Ɋւ���ڂ������͂����̃h�L�������g
// ���Q�Ƃ��Ă��������B
//

class CListViewEx : public CListView
{
	DECLARE_DYNCREATE(CListViewEx)

// �\�z
public:
	CListViewEx();

// �A�g���r���[�g
protected:
	BOOL m_bFullRowSel;

public:
	BOOL SetFullRowSel(BOOL bFillRowSel);
	BOOL GetFullRowSel();

	BOOL m_bClientWidthSel;

// �I�[�o�[���C�h
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// ClassWizard �͉��z�֐��𐶐����I�[�o�[���C�h���܂��B
	//{{AFX_VIRTUAL(CListViewEx)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CListViewEx();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void RepaintSelectedItems();

// �C���v�������e�[�V���� - �N���C�A���g�̈�̕�
	int m_cxClient;

// �C���v�������e�[�V���� - ��ԕ\���̃A�C�R���̕�
	int m_cxStateImageOffset;
	afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);

// �C���v�������e�[�V���� - ���X�g �r���[�̐F
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	virtual void PreDrawItem(int nItem, LV_ITEM* pLVI);
	//{{AFX_MSG(CListViewEx)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_LISTVWEX_H__A7E61444_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
