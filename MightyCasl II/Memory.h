// Memory.h: CMemory クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORY_H__3DFD17F7_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_)
#define AFX_MEMORY_H__3DFD17F7_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MEMORY_SIZE			0x10000

#define MEMORY_ATTR_NULL	0x00
#define MEMORY_ATTR_CODE	0x01
#define MEMORY_ATTR_CONST	0x02
#define MEMORY_ATTR_WORK	0x03

class CMemory  
{
protected:
	WORD m_mem[MEMORY_SIZE];
	BYTE m_attr[MEMORY_SIZE];
public:
	void Init();
	void SetMemory(WORD address, WORD data);
	WORD GetMemory(WORD address);
	void GetMemoryRange(WORD address, WORD* buffer, WORD len);
	CMemory();
	virtual ~CMemory();

};

#endif // !defined(AFX_MEMORY_H__3DFD17F7_D9E7_11D3_BD8C_0000E8647D2D__INCLUDED_)
