#if !defined(AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterView.h : �w�b�_�[ �t�@�C��
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

#define REG_COLUMN_REG		0
#define REG_COLUMN_HEX		1
#define REG_COLUMN_SIGNED	2
#define REG_COLUMN_UNSIGNED	3
#define REG_COLUMN_BINARY	4
#define REG_COLUMN_CHAR		5


/////////////////////////////////////////////////////////////////////////////
// CRegisterView �r���[

class CRegisterView : public CListViewEx
{
protected:
	CRegisterView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CRegisterView)

// �A�g���r���[�g
public:
protected:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CRegisterView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CFont m_font;
	CSize m_fontSize;
	virtual ~CRegisterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	void ModifyRegister();
	CRegister* GetRegister();
	CLabelBank* GetLabelBank();
	//{{AFX_MSG(CRegisterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CRegisterView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_REGISTERVIEW_H__A7E61442_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
