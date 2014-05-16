// Assembler.cpp: CAssembler クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mightycasl.h"
#include "Assembler.h"
#include "Comet.h"
#include "MnemonicSuspect.h"
#include "MnemonicMacro.h"
#include "MnemonicBase.h"
#include "MnemonicAcc.h"
#include "MnemonicShift.h"
#include "MnemonicCompare.h"
#include "MnemonicJump.h"
#include "MnemonicStack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAssembler::CAssembler()
{

}

CAssembler::~CAssembler()
{
	m_mnemonics.DeleteAll();
}

void CAssembler::Initialize(int nPass)
{
	m_nPass		= nPass;
	m_nEnd		= 0;
	m_nStart	= 0;
	m_nLine		= 0;
	m_errors.DeleteAll();
	m_mnemonics.DeleteAll();
	m_address = USER_PROGRAM_BEGIN_ADDRESS;
	m_startAddress = USER_PROGRAM_BEGIN_ADDRESS;
	if (m_nPass == 1)
	{
		m_literalBank.DeleteAll();
		m_labelBank.DeleteAll();
	}
}

void CAssembler::DoAssemble(LPCSTR line)
{
	m_nLine++;

	CString strLine(line);
	strLine.TrimLeft();
	if (strLine.IsEmpty())
	{
		m_errors.Add(new CAssembleError(m_nLine, line, IDS_ASMERR_NULLSTR));
		return;
	}

	strLine = line;
	OmitComment(strLine);

	if (strLine.IsEmpty())
	{
		// コメントだけの行
		CMnemonic* pMnemonic = new CMnemonicComment(m_address, line, this);
		m_mnemonics.Add(pMnemonic);
		return;
	}

	// ラベル、ニーモニック、オペランドに分解する
	CString strLabel, strMnemonic, strOperand;
	
	// ラベルの取り込み
	int nPos = strLine.FindOneOf(" \t");
	if (nPos == -1)
	{
		// ニーモニックがないエラー
		m_errors.Add(new CAssembleError(m_nLine, line, IDS_ASMERR_NO_MNEMONIC));
		return;
	}
	if (nPos > 0)
	{
		strLabel = strLine.Left(nPos);
		strLine = strLine.Mid(nPos+1);
	}
	strLine.TrimLeft();
	nPos = strLine.FindOneOf(" \t");
	if (nPos == -1)
		strMnemonic = strLine;
	else
	{
		strMnemonic = strLine.Left(nPos);
		strOperand = strLine.Mid(nPos + 1);
		strOperand.TrimLeft();
	}

	if (m_nPass == 1)
	{
		if (!m_labelBank.Regist(strLabel, m_address))
		{
			m_errors.Add(new CAssembleError(m_nLine, line, m_labelBank.GetLastError()));
			return;
		}
	}
	CMnemonic* pMnemonic = CreateMnemonic(strMnemonic, strOperand, line);
	if (pMnemonic == NULL)
		return;

	if (pMnemonic->Assemble())
	{
		m_address += pMnemonic->GetCodeSize();
		m_mnemonics.Add(pMnemonic);
		if (m_nPass == 1)
			m_literalBank.SetTopAddress(m_address);
	}
	else
	{
		m_errors.Add(new CAssembleError(m_nLine, line, pMnemonic->GetError()));
		delete pMnemonic;
	}
}

void CAssembler::OmitComment(CString &line)
{
	BOOL bInString = FALSE;
	int nLeng = line.GetLength();
	for (int i = 0; i < nLeng; i++)
	{
		char ch = line[i];
		if (ch == ';' && !bInString)
		{
			line = line.Left(i);
			break;
		}
		if (ch == '\'')
			bInString = !bInString;
	}
	line.TrimRight();
}

CMnemonic* CAssembler::CreateMnemonic(LPCSTR strMnemonic, LPCSTR strOperand, LPCSTR strNativeLine)
{
	struct _strMnemonicTable
	{
		LPCSTR name;
		WORD code;
	};
	static _strMnemonicTable mnemonicTable[] =
	{
		{"START",	CASL_START},		{"END",		CASL_END},		{"DC",		CASL_DC},
		{"DS",		CASL_DS},			{"IN",		CASL_IN},		{"OUT",		CASL_OUT},
		{"RPUSH",	CASL_RPUSH},		{"RPOP",	CASL_RPOP},

		{"LD",		COMET_LD},			{"ST",		COMET_ST},		{"LAD",		COMET_LAD},
		{"ADDA",	COMET_ADDA},		{"ADDL",	COMET_ADDL},
		{"SUBA",	COMET_SUBA},		{"SUBL",	COMET_SUBL},
		{"AND",		COMET_AND},			{"OR",		COMET_OR},		{"XOR",		COMET_XOR},
		{"CPA",		COMET_CPA},			{"CPL",		COMET_CPL},
		{"SLA",		COMET_SLA},			{"SRA",		COMET_SRA},
		{"SLL",		COMET_SLL},			{"SRL",		COMET_SRL},
		{"JPL",		COMET_JPL},			{"JMI",		COMET_JMI},
		{"JNZ",		COMET_JNZ},			{"JZE",		COMET_JZE},
		{"JOV",		COMET_JOV},			{"JUMP",	COMET_JUMP},
		{"PUSH",	COMET_PUSH},		{"POP",		COMET_POP},
		{"CALL",	COMET_CALL},		{"RET",		COMET_RET},
		{"SVC",		COMET_SVC},			{"NOP",		COMET_NOP},

		{NULL,		0x0000}
	};

	struct _strMnemonicTable* p = mnemonicTable;

	while (p->name)
	{
		if (!strcmp(p->name, strMnemonic))
			break;
		p++;
	}

	if (p->name == NULL)		// 不正なニーモニックだった
	{
		m_errors.Add(new CAssembleError(m_nLine, strNativeLine, IDS_ASMERR_BADMNEMONIC));
		return NULL;
	}

	CMnemonic* pMnemonic = NULL;
	switch (p->code)
	{
	case CASL_START:
		pMnemonic = new CMnemonicSTART(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_END:
		pMnemonic = new CMnemonicEND(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_DC:
		pMnemonic = new CMnemonicDC(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_DS:
		pMnemonic = new CMnemonicDS(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_IN:
		pMnemonic = new CMnemonicIN(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_OUT:
		pMnemonic = new CMnemonicOUT(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_RPUSH:
		pMnemonic = new CMnemonicRPUSH(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case CASL_RPOP:
		pMnemonic = new CMnemonicRPOP(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_LD:
		pMnemonic = new CMnemonicLD(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_ST:
		pMnemonic = new CMnemonicST(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_LAD:
		pMnemonic = new CMnemonicLAD(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_ADDA:
		pMnemonic = new CMnemonicADDA(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_ADDL:
		pMnemonic = new CMnemonicADDL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SUBA:
		pMnemonic = new CMnemonicSUBA(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SUBL:
		pMnemonic = new CMnemonicSUBL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_AND:
		pMnemonic = new CMnemonicAND(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_OR:
		pMnemonic = new CMnemonicOR(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_XOR:
		pMnemonic = new CMnemonicXOR(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_CPA:
		pMnemonic = new CMnemonicCPA(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_CPL:
		pMnemonic = new CMnemonicCPL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SLA:
		pMnemonic = new CMnemonicSLA(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SRA:
		pMnemonic = new CMnemonicSRA(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SLL:
		pMnemonic = new CMnemonicSLL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SRL:
		pMnemonic = new CMnemonicSRL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JPL:
		pMnemonic = new CMnemonicJPL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JMI:
		pMnemonic = new CMnemonicJMI(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JNZ:
		pMnemonic = new CMnemonicJNZ(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JZE:
		pMnemonic = new CMnemonicJZE(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JOV:
		pMnemonic = new CMnemonicJOV(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_JUMP:
		pMnemonic = new CMnemonicJUMP(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_PUSH:
		pMnemonic = new CMnemonicPUSH(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_POP:
		pMnemonic = new CMnemonicPOP(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_CALL:
		pMnemonic = new CMnemonicCALL(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_RET:
		pMnemonic = new CMnemonicRET(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_SVC:
		pMnemonic = new CMnemonicSVC(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	case COMET_NOP:
		pMnemonic = new CMnemonicNOP(m_address, strMnemonic, strOperand, strNativeLine, this);
		break;
	}

	return pMnemonic;
}

BOOL CAssembler::HaveError()
{
	return m_errors.GetSize() ? TRUE : FALSE;
}


void CAssembler::OutputCode(CMemory* pMemory)
{
	m_mnemonics.OutputCode(pMemory);
	m_literalBank.OutputCode(pMemory);
}

