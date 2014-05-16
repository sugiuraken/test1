// Register.cpp: CRegister クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Register.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CRegister::CRegister()
{
	Init();
}

CRegister::~CRegister()
{

}

LPCSTR CRegister::GetRegisterName(int nRegID)
{
	static LPCSTR regName[SIZEOF_REG] =
	{
		"GR0", "GR1", "GR2", "GR3", "GR4", "GR5", "GR6", "GR7", "SP", "PR", "FR"
	};

	return regName[nRegID];
}

void CRegister::Init()
{
	for (int i = 0; i < SIZEOF_REG; i++)
		m_reg[i] = 0x0000;
}

void CRegister::UpdateFlagState(int result)
{
	WORD fr = GetValue(REG_FR);
	if (result == 0)
		fr |= REG_FR_ZFLG;
	else
		fr &= ~REG_FR_ZFLG;

	if (result < 0)
		fr |= REG_FR_SFLG;
	else
		fr &= ~REG_FR_SFLG;

	SetValue(REG_FR, fr);
}

int CRegister::GetRegisterId(LPCSTR name)
{
	static LPCSTR regName[] = 
	{
		"GR0", "GR1", "GR2", "GR3", "GR4", "GR5", "GR6", "GR7",
		"SP", "PR", "FR"
	};

	static int regID[] = 
	{
		REG_GR0, REG_GR1, REG_GR2, REG_GR3, REG_GR4, REG_GR5, REG_GR6, REG_GR7, 
		REG_SP, REG_PC, REG_FR
	};

	for (int i = 0; i < sizeof regName / sizeof(LPCSTR); i++)
	{
		if (!strcmp(regName[i], name))
			return regID[i];
	}
	return -1;
}
