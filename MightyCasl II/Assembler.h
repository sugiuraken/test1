// Assembler.h: CAssembler �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSEMBLER_H__1D4D57C4_CECA_11D3_AB2E_006067202C95__INCLUDED_)
#define AFX_ASSEMBLER_H__1D4D57C4_CECA_11D3_AB2E_006067202C95__INCLUDED_

#include "Label.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Literal.h"
#include "AssembleError.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Mnemonic.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define USER_PROGRAM_BEGIN_ADDRESS	0x0100

class CAssembler  
{
public:
	BOOL HaveError();
	CLabelBank m_labelBank;
	CLiteralBank m_literalBank;

	int m_nPass;
	WORD m_startAddress;
	int m_nEnd;
	int m_nStart;
	CAssembleErrorArray m_errors;

	CAssembler();
	virtual ~CAssembler();
	void DoAssemble(LPCSTR line);
	void Initialize(int nPass);

	CMnemonicArray* GetMnemonics() {return &m_mnemonics;}
	void OutputCode(CMemory* pMemory);
protected:
	WORD m_address;
	int m_nLine;

	CMnemonic* CreateMnemonic(LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine);
	CMnemonicArray m_mnemonics;
	void OmitComment(CString& line);
};

#endif // !defined(AFX_ASSEMBLER_H__1D4D57C4_CECA_11D3_AB2E_006067202C95__INCLUDED_)
