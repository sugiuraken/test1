// Register.h: CRegister クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTER_H__07F704F7_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
#define AFX_REGISTER_H__07F704F7_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comet.h"

#define REG_GR0		COMET_GR0
#define REG_GR1		COMET_GR1
#define REG_GR2		COMET_GR2
#define REG_GR3		COMET_GR3
#define REG_GR4		COMET_GR4
#define REG_GR5		COMET_GR5
#define REG_GR6		COMET_GR6
#define REG_GR7		COMET_GR7
#define REG_SP		8
#define REG_PC		9
#define REG_FR		10

#define REG_FR_ZFLG	0x01
#define REG_FR_SFLG 0x02
#define REG_FR_VFLG 0x04
#define REG_FR_ALL	(REG_FR_ZFLG | REG_FR_SFLG | REG_FR_VFLG)

#define SIZEOF_REG	(REG_FR + 1)

class CRegister  
{
protected:
	WORD m_reg[SIZEOF_REG];
public:
	static int GetRegisterId(LPCSTR regName);
	void Init();
	WORD GetValue(int nRegID){return m_reg[nRegID];}
	void SetValue(int nRegID, WORD value){m_reg[nRegID] = value;}

	static LPCSTR GetRegisterName(int nRegID);
	CRegister();
	virtual ~CRegister();
	void UpdateFlagState(int result);

	void ResetOverflowFlag() {m_reg[REG_FR] &= ~REG_FR_VFLG;}
	void SetOverflowFlag() {m_reg[REG_FR] |= REG_FR_VFLG;}
	void ResetZeroFlag() {m_reg[REG_FR] &= ~REG_FR_ZFLG;}
	void SetZeroFlag() {m_reg[REG_FR] |= REG_FR_ZFLG;}
	void ResetSignFlag() {m_reg[REG_FR] &= ~REG_FR_SFLG;}
	void SetSignFlag() {m_reg[REG_FR] |= REG_FR_SFLG;}

	void UpdateOverflowFlag(int result)
	{
		if (result >= -32768 && result <= 32767)
			m_reg[REG_FR] &= ~REG_FR_VFLG;
		else
			m_reg[REG_FR] |= REG_FR_VFLG;
	}
	void UpdateOverflowFlag(UINT result)
	{
		if (result >= 0 && result <= 65535)
			m_reg[REG_FR] &= ~REG_FR_VFLG;
		else
			m_reg[REG_FR] |= REG_FR_VFLG;
	}
	BOOL IsPlus() {return (!IsZero() && !IsMinus()) ? TRUE : FALSE;}
	BOOL IsPlusOrZero() {return !IsMinus();}
	BOOL IsMinus() {return (m_reg[REG_FR] & REG_FR_SFLG) ? TRUE : FALSE;}
	BOOL IsNonZero() {return !IsZero();}
	BOOL IsZero() {return (m_reg[REG_FR] & REG_FR_ZFLG) ? TRUE : FALSE;}
	BOOL IsOverflow() {return (m_reg[REG_FR] & REG_FR_VFLG) ? TRUE : FALSE;}

};

#endif // !defined(AFX_REGISTER_H__07F704F7_DAA7_11D3_BD8D_0000E8647D2D__INCLUDED_)
