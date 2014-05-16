#if !defined(AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchView.h : �w�b�_�[ �t�@�C��
//
#include "ListVwEx.h"
#include "MightyCaslDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CWatchView �r���[

class CWatchView : public CListViewEx
{
protected:
	CWatchView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CWatchView)

// �A�g���r���[�g
public:
protected:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:
	void AddWatch(LPCSTR szTarget = NULL);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CWatchView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CFont m_font;
	CSize m_fontSize;
	COleDropTarget m_dropTarget;
	DROPEFFECT m_dropEffect;

	virtual ~CWatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CLabelBank* GetLabelBank();
	CWatchList* GetWatchList();
	CRegister* GetRegister();
	CMemory* GetMemory();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	void ModifyWatch();
	virtual void PreDrawSubItem(int nItem, int nColumn, LPSTR szBuff, int nLen);
	void InsertWatchItem(CWatchInfo* pInfo);
	//{{AFX_MSG(CWatchView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateWatchModify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWatchClear(CCmdUI* pCmdUI);
	afx_msg void OnWatchClear();
	afx_msg void OnWatchModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG
inline CMightyCaslDoc* CWatchView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_WATCHVIEW_H__A7E61445_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
