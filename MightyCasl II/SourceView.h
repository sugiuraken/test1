#if !defined(AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSourceView �r���[

class CSourceView : public CEditView
{
protected:
	CSourceView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CSourceView)

// �A�g���r���[�g
public:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:
	void GetCaretPosition(int& nLine, int& nCol);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSourceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CSourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	int m_beforeLineCount;
	void GotoSourceLine(int nLine);
	CFont m_font;
	//{{AFX_MSG(CSourceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MightyCaslView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CMightyCaslDoc* CSourceView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SOURCEVIEW_H__788E89D6_F9E5_11D2_BECC_006067202C95__INCLUDED_)
