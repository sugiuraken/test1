#if !defined(AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackView.h : �w�b�_�[ �t�@�C��
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CStackView �r���[

class CStackView : public CListViewEx
{
protected:
	CStackView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CStackView)

// �A�g���r���[�g
public:
protected:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CStackView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CStackView();
	CRegister* GetRegister();
	CMemory* GetMemory();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CFont m_font;
	CSize m_fontSize;
	CImageList m_imageIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	virtual void PreDrawItem(int nItem, LV_ITEM* pLVI);
	//{{AFX_MSG(CStackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CStackView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STACKVIEW_H__A7E61443_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
