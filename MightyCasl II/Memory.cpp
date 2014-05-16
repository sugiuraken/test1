// Memory.cpp: CMemory クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMemory::CMemory()
{
	Init();
}

CMemory::~CMemory()
{

}

void CMemory::GetMemoryRange(WORD address, WORD *buffer, WORD len)
{
	if (len == 0)
		return;

	UINT tail = (UINT)address + len;
	if (tail <= MEMORY_SIZE)
		memcpy(buffer, m_mem + address, sizeof(WORD) * len);
	else
	{
		GetMemoryRange(address, buffer, MEMORY_SIZE - address);
		GetMemoryRange(address, buffer + MEMORY_SIZE - address, tail - MEMORY_SIZE);
	}
}

WORD CMemory::GetMemory(WORD address)
{
	return m_mem[address];
}

void CMemory::SetMemory(WORD address, WORD data)
{
	m_mem[address] = data;
}

void CMemory::Init()
{
	memset(m_mem, 0, sizeof(WORD) * MEMORY_SIZE);
	memset(m_attr, MEMORY_ATTR_NULL, sizeof(BYTE) * MEMORY_SIZE);

}
