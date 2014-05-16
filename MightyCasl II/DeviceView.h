#if !defined(AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_)
#define AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceView.h : �w�b�_�[ �t�@�C��
//
class CMightyCaslDoc;
/////////////////////////////////////////////////////////////////////////////
// CDeviceView �r���[

class CDeviceView : public CEditView
{
protected:
	CDeviceView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CDeviceView)

// �A�g���r���[�g
public:
	CMightyCaslDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDeviceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CDeviceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	void AppendString(LPCSTR);
	CFont m_font;
	//{{AFX_MSG(CDeviceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // MightyCaslView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CMightyCaslDoc* CDeviceView::GetDocument()
   { return (CMightyCaslDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVICEVIEW_H__1F4BA356_DDF2_11D3_BD8F_0000E8647D2D__INCLUDED_)
