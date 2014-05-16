#if !defined(AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_)
#define AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// COutputView �r���[

class COutputView : public CEditView
{
protected:
	COutputView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(COutputView)

// �A�g���r���[�g
public:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(COutputView)
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~COutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	void AdjustErrorLineNumber(int nLine, int deltaLine);
	CFont m_font;
	CAssembleErrorArray* m_pErrors;
	void DisplayErrors();
	//{{AFX_MSG(COutputView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MightyCaslView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CMightyCaslDoc* COutputView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OUTPUTVIEW_H__C0B76CAA_B658_11D3_AB2D_006067202C95__INCLUDED_)
