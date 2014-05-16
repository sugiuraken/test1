// WatchInfo.cpp: CWatchInfo �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "WatchInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CWatchInfo::CWatchInfo(LPCSTR target, int length, int fmt)
: m_target(target)
{
	m_length = length;
	m_fmt = fmt;
}

CWatchInfo::~CWatchInfo()
{

}


CWatchList::CWatchList()
{

}

CWatchList::~CWatchList()
{
	DeleteAll();
}

void CWatchList::DeleteAll()
{
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		CWatchInfo* pInfo = GetNext(pos);
		delete pInfo;
	}
	RemoveAll();
}
