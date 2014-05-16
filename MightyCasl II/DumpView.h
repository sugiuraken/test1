#if !defined(AFX_DUMPVIEW_H__A7E61446_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
#define AFX_DUMPVIEW_H__A7E61446_D9C3_11D3_AB2F_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpView.h : �w�b�_�[ �t�@�C��
//

#include "MightyCaslDoc.h"

#define HP_PREHEX		1
#define HP_HEX0			2
#define HP_HEX1			3
#define HP_HEX2			4
#define HP_HEX3			5
#define HP_HEXSPACE		6
#define HP_POSTHEX		7
#define HP_PRECHR		HP_POSTHEX
#define HP_CHR			8
#define HP_CHRSPACE		9
#define HP_POSTCHR		10

/////////////////////////////////////////////////////////////////////////////
// CDumpView �r���[

class CDumpView : public CView
{
protected:
	CDumpView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CDumpView)

// �A�g���r���[�g
public:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDumpView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CDumpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CMemory* GetMemory();
	UINT GetNextPageLocationAddress();
	void ModifyMemoryChr(UINT nChar, CPoint ptCaret, WORD offset);
	void ModifyMemoryHex(UINT nChar, CPoint ptCaret, WORD hitPos, WORD offset);
	void MoveCaret(UINT nChar);
	void AdjustOverCaret();
	void SetCaretPosSmart(CPoint point);
	UINT TestDumpHit(CPoint pt);		// LOWORD(return) : HP_XXXXX, HIWORD(return) : index

	CFont m_font;
	CPoint m_ptCaret;
	UINT m_topLineAddress;
	CSize m_fontSize;
	COleDropTarget m_dropTarget;
	DROPEFFECT m_dropEffect;
	//{{AFX_MSG(CDumpView)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CMightyCaslDoc* CDumpView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DUMPVIEW_H__A7E61446_D9C3_11D3_AB2F_006067202C95__INCLUDED_)
