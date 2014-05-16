// MightyCaslDoc.h : CMightyCaslDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_)
#define AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_

#include "CometCore.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Assembler.h"
#include "WatchInfo.h"	// ClassView �ɂ���Ēǉ�����܂����B

class CMightyCaslDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CMightyCaslDoc();
	DECLARE_DYNCREATE(CMightyCaslDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMightyCaslDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void CloseDeviceFiles();
	BOOL OutputDevice(LPCSTR output);
	BOOL InputDevice(CString& input);
	CWatchList m_watchList;
	void ExecuteProgram(int mode, WORD breakAddr = 0x0000);
	CView* GetTargetView(LPCSTR className);
	void ResetCore();
	CAssembler m_assembler;
	CCometCore m_cometCore;
	CString m_sourceFileName;
	CStringArray m_strDeviceAccess;

	virtual ~CMightyCaslDoc();
	BOOL Assemble();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	CStdioFile* m_pOutputFile;
	CStdioFile* m_pInputFile;
	CStringArray m_sourceLine;
	//{{AFX_MSG(CMightyCaslDoc)
	afx_msg void OnExexuteStop();
	afx_msg void OnUpdateExexuteStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MIGHTYCASLDOC_H__788E89CC_F9E5_11D2_BECC_006067202C95__INCLUDED_)
