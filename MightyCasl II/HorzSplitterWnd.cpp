// HorzSplitterWnd.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "mightycasl.h"
#include "HorzSplitterWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd

CHorzSplitterWnd::CHorzSplitterWnd()
{
}

CHorzSplitterWnd::~CHorzSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CHorzSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CHorzSplitterWnd)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHorzSplitterWnd::TrackRowSize(int y, int row)
{
	// �X�v���b�^���㉺�Ɉړ������Ƃ���
	int saveSize = m_pRowInfo[row].nIdealSize;
	CSplitterWnd::TrackRowSize(y, row);
	m_pRowInfo[row + 1].nIdealSize += saveSize - m_pRowInfo[row].nIdealSize;      // new size
}
/////////////////////////////////////////////////////////////////////////////
// CHorzSplitterWnd ���b�Z�[�W �n���h��
