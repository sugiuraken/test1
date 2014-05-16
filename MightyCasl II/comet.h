//////////////////////////////////////////////////////////////////////////////////////
//
// COMET マシン 命令定義


////////////////////////////////////////////////////////////////////////
// 命令語フォーマット(２語)
//
// [１語目］
//           bit0 - 7 : 命令コード   
//		     bit8 -11 : オペランド１ (GR)
//           bit12-15 : オペランド３ (XR)
// [２語目］
//           bit0 -15 : オペランド２ (addr)


/////////////////////////////////////////////////////////////////////////
// 命令コード
#define COMET_RR_BIT	0x0400			// r,r オペランドを示すのビット

#define COMET_NOP		0x0000

#define COMET_LD		0x1000
#define COMET_ST		0x1100
#define COMET_LAD		0x1200

#define	COMET_ADDA		0x2000
#define	COMET_SUBA		0x2100
#define	COMET_ADDL		0x2200
#define	COMET_SUBL		0x2300

#define COMET_AND		0x3000
#define COMET_OR		0x3100
#define COMET_XOR		0x3200

#define COMET_CPA		0x4000
#define COMET_CPL		0x4100

#define COMET_SLA		0x5000
#define COMET_SRA		0x5100
#define COMET_SLL		0x5200
#define COMET_SRL		0x5300

#define COMET_JMI		0x6100
#define COMET_JNZ		0x6200
#define COMET_JZE		0x6300
#define COMET_JUMP		0x6400
#define COMET_JPL		0x6500
#define COMET_JOV		0x6600

#define COMET_PUSH		0x7000
#define COMET_POP		0x7100

#define	COMET_CALL		0x8000
#define	COMET_RET		0x8100

#define COMET_SVC		0xF000

////////////////////////////////////////////////////////////////////////////
// オペランド１および３
//
#define COMET_GR0		0x0
#define COMET_GR1		0x1
#define COMET_GR2		0x2
#define COMET_GR3		0x3
#define COMET_GR4		0x4
#define COMET_GR5		0x5
#define COMET_GR6		0x6
#define COMET_GR7		0x7
#define COMET_GRNULL	0xF

////////////////////////////////////////////////////////////////////////////
// スーバーバイザーコール形式
//
// [１語目］  bit0 - 7 : 命令コード   (0xFE固定)
//		     bit8 -15 : オペランド    (0x00固定)
// [２語目］ 動作コード

#define COMET_SVC_IN		1
// COMET_IN パラメータ
//        GR1  入力領域アドレス
//        GR2  入力文字長格納アドレス
#define COMET_SVC_OUT		2
// COMET_OUT パラメータ
//        GR1  出力領域アドレス
//        GR2  出力文字長格納アドレス

////////////////////////////////////////////////////////////////////////////
// 擬似命令仮コード
//
#define CASL_START		0xFF01
#define CASL_END		0xFF02
#define CASL_DC			0xFF03
#define CASL_DS			0xFF04
#define CASL_IN			0xFF05
#define CASL_OUT		0xFF06
#define CASL_RPUSH		0xFF07
#define CASL_RPOP		0xFF08
