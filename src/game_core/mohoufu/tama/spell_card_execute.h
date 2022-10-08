
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�J�[�h�C���^�v���^�[
	-------------------------------------------------------
	�J�[�hCPU�̎��s�����B
	-------------------------------------------------------
	(r41)���� CPU�̎d�l�͊m�肵�Ă��܂���B(�݌v���ł�)
	���߂͂Ƃ������A�f�N�������g�͂߂�ǂ���������S���o����l�ɂ����Ⴆ�A
	�Ǝv��Ȃ����Ȃ��ł����A�Ή����Ȃ��� CPU�̃R�[�h���������Ȃ�Ƃ��������b�g������܂��B
	(���X�f�N�������g�͑S���ł���K�i�̗\��ł����B)
	-------------------------------------------------------
	�����I�� obj�̃R���g���[���� CPU�ɓ���\��Ȃ̂ŁA
	CPU�̃R�[�h����������Ώ����������A�ǂ��ł��B
	-------------------------------------------------------
	CPU�̃R�[�h����������Ώ���������(�L���b�V���̃q�b�g�����オ��̂�)�A�Q�[���S�̂̑��x��������܂��B
	�Ƃ������L���b�V���ɍڂ�傫���ɂ���΁A�ǂ�ȑ傫���ł��ǂ��ł��B
	CPU�̃R�[�h���傫���Ȃ肷���ăL���b�V���ɍڂ�Ȃ��ꍇ�A���x�ቺ���ăQ�[���ɂȂ�Ȃ��Ǝv���܂��B
	-------------------------------------------------------
	OP_01_MOVER_PD ���߂̃f�N�������g��
	�����������O�V���[�g�A�h���b�V���O�̃V���[�g�A�h���b�V���O�̏ꍇ�̃f�N�������g��
	�Œ�ł��c���\��ł��B
	�Ƃ肠�����A�C���N�������g/�f�N�������g�� OP_01_MOVER_PD ���� �ł���������ǂ��C�����܂��B
	-------------------------------------------------------
	�s�v�Ȗ��߂� �r��������j�ł��B
---------------------------------------------------------*/

//#include "spell_micro_code.h"
/*---------------------------------------------------------
	�����o�֐�(private:)
	-------------------------------------------------------
	�v���C�x�[�g�Ȋ֐��͊O���ɏo���Ȃ��̂ŁA
	�ԈႦ�ďo������R���p�C���G���[�ɂȂ�悤�׍H���Ƃ��B
---------------------------------------------------------*/


/*---------------------------------------------------------
	(r35)�萔��
---------------------------------------------------------*/
//#define MAX_I_COUNT	(8192)/* (1/60)������̍ő又�����߁B */

global int spell_register[REG_NUM_99_MAX];



#if (0)/*(�����I�ɃJ�[�h�C���^�v���^��œ��삷�閽�߂Ɉڍs����)*/
/*---------------------------------------------------------
	(r35)�����̊֐��́A���W�X�^�ł͂Ȃ��A���W�X�^�ԍ���n���̂Œ��ӂ̎��B
	�ԈႦ�ă��W�X�^�n�����ꍇ�A�ԈႢ����psp���n���O�A�b�v����B
	�ԈႢ�₷���̂ŁA�֐�����NUM����ꂽ�B
	-------------------------------------------------------
	(r35)�����̊֐����A���̃��W�X�^�l��n���Ȃ����Ƃ����ƁA
	�J�[�h�X�N���v�g�p���߂Ɉڍs�����ꍇ�A
	�J�[�h�X�N���v�g�ł͂����������W�X�^�l��n���Ȃ��B
	�Ƃ����d�l�̃X�N���v�g��\�肵�Ă���B
	���R�̓��W�X�^�l��n���ƃX�N���v�g�̎��s���x���ቺ���邩��B
---------------------------------------------------------*/
#endif


/*�Ă���*/extern void audio_voice_play(void);
/*�Ă���*/extern void audio_auto_bullet_play(void);
static CPU_FUNC(cpu_auto_bullet_play_default);
/*---------------------------------------------------------
	�J�[�hCPU���j�b�g�̃J�[�h���߂�1���ߎ��s����B
---------------------------------------------------------*/

#define USE_CPU_DEBUG_MODE (0)
#if (1==USE_CPU_DEBUG_MODE)
static u32 opecode_history[4];
static u32 opecode_history_pointer;
static u32 hook_counter = (1);
u32 *codebase_bak;
	#define opcode_fetch()\
	{\
		fetch_data32 = /**/\
		opecode_history[opecode_history_pointer] = (*codebase);\
		codebase++;\
		opecode_history_pointer++;\
		opecode_history_pointer &= 3;\
	}
//	#define OP_NOP_debug OP_NEXT
	#define OP_NOP_debug OP_0b_BRA_RS/*(�Ă���)*/
#else
	#define opcode_fetch()	{fetch_data32 = (*codebase);codebase++;}
	#define OP_NOP_debug OP_NEXT
#endif

// (��{����)-------- ���W�X�^�A�h���b�V���O�B
#define OP0x00		OP_00_EXIT
#define OP0x01		OP_01_MOVER_PD
#define OP0x02		OP_02_COUNTER
#define OP0x03		OP_03_nan_ido
#define OP0x04		OP_04_ADDR_PD
#define OP0x05		OP_05_SUBR_PD/*[�������]����]*/
#define OP0x06		OP_06_BRAR_NN	// �W�����v�e�[�u������[����������(���W�X�^�l)](���̖��߂͕K�v)
#if 0/*(��)*/
	#define OP0x07	OP_06_REGIST_PROCESS/*(�܂�����ĂȂ����ǁA���̖��߂͕K�v�B)*/
#else
	#define OP0x07	OP_NOP_debug/*(��)*/
#endif
// (�u�����`�n����)--------
#define OP0x08		OP_08_BNE_RS		// �u�����`�n����[�l���Ⴆ�Ε���](���̖��߂͕K�v)
#define OP0x09		OP_09_BFL_RS		// �u�����`�n����[�l�����l���t���[�����番��](���̖��߂͕K�v)
#define OP0x0a		OP_0a_BRA_TABLE 	// �u�����`�n����[�z��](���̖��߂͕K�v)
#define OP0x0b		OP_0b_BRA_RS		// �u�����`�n����[����������(���l)](���̖��߂͕K�v)
// (��{�e��������)--------
#define OP0x0c		OP_0c_hatudan_system_regist_tama/*single*/
#define OP0x0d		OP_0d_AUDIO_VOICE_PLAY
#define OP0x0e		OP_0e_AUDIO_AUTO_BULLET_PLAY_SET_18
#define OP0x0f		OP_0f_CLEAR_ZERO_PAGE
//	(�T�|�[�g����)--------
#define OP0x10		OP_10_SINCOS256
#define OP0x11		OP_11_BOSS_TO_JIKI_NERAI
#define OP0x12		OP_12_JIKI_NERAI
#define OP0x13		OP_13_HANYOU_NERAI
#define OP0x14		OP_14_MULTIPREX_RATE_VECTOR
#define OP0x15		OP_15_RAND_VALUE
#define OP0x16		OP_16_RAND_INIT
#define OP0x17		OP_17_DIV65536
//
#if 0
//	(�e(OBJ)���䖽��)-------- �e==(OBJ�Ȃ̂ŁA�G���{�X���������d�g�݂ŃX�y�JCPU���瑀��o����)
//	OP_xx_OBJ_REGIST_HEAD	// ���삷��e�̐擪�A�h���X���X�y�JCPU�ɓo�^����B
//	OP_xx_OBJ_LOAD_VALUE	// �e�̐ݒ�l�����W�X�^�ɓǂݍ��ށB
//	OP_xx_OBJ_STORE_VALUE	// ���W�X�^�l��e�̐ݒ�l�֏������ށB
//	�Ԑڑ���Ȃ̂Œx���B
#endif
//
//#define OP0x06	OP_NOP_debug/*OP_06_ASRR_PD*/
//#define OP0x07	OP_NOP_debug/*OP_07_ASLR_PD*/
/*OP_03_ANDR_PD*/
/*OP_18_hatudan_system_regist_n_way*/
/*OP_18_hatudan_system_regist_katayori_n_way*/

// (�g������[CPU�O���R�[�h(����)])-------- �����������O�V���[�g�A�h���b�V���O�B
#define OP0x18		OP_NOP_debug// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x19		OP_NOP_debug// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1a		OP_NOP_debug// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1b		OP_MLS// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1c		OP_MLS// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1d		OP_MLS// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1e		OP_MLS// �����������O�V���[�g�A�h���b�V���O�B
#define OP0x1f		OP_MLS// �����������O�V���[�g�A�h���b�V���O�B
// (�g������[CPU�����R�[�h])-------- �����������O�V���[�g�A�h���b�V���O�B
/*[���g�p]*/#define OB0x20		OP_NOP_debug
/*[���g�p]*/#define OB0x21		OP_NOP_debug
/*[���g�p]*/#define OB0x22		OP_NOP_debug
/*[OP_MLS]*/#define OB0x23		OB_1b_CALC_ADDM_LONG_PD// �����O�������A�h���b�V���O��p���߁B
// (�g������)-------- �������A�h���b�V���O�B
/*[OP_MLS]*/#define OB0x24		OB_1c_CALC_MOVEM_PD// �����������O�V���[�g�A�h���b�V���O�B
/*[OP_MLS]*/#define OB0x25		OB_1d_CALC_ANDM_PD// �����������O�V���[�g�A�h���b�V���O�B
/*[OP_MLS]*/#define OB0x26		OB_1e_CALC_ASRM_PD// �����������O�V���[�g�A�h���b�V���O�B
/*[OP_MLS]*/#define OB0x27		OB_1f_CALC_ASLM_PD// �����������O�V���[�g�A�h���b�V���O�B
// (�g������)--------
/*OB_1d_CALC_SUBM_PD*/	/*(���̖��߂͗v��Ȃ������B[�p�r�������C������])*/

#define USE_VFPU_INTEGER_DIVISOR (1)
#if (1==USE_VFPU_INTEGER_DIVISOR)
/*--------------------DSS-------------------------------------
	avoid cpu pipeline breaking, using the vfpu divide.
	vfpu�Ŋ���Z���邱�Ƃɂ��Acpu�̃p�C�v���C���u���C�N��h���B
	-------------------------------------------------------
	usage: �g�����B
		s32 result_value;
		s32 value000;
		s32 value111;
		value000 = 65536;
		value111 = 7;
		vfpu_div_s32(&result_value, value000, value111);// result_value = value000 / value111;
	result: ���ʁB
		result_value == 9362; // 9362.285714285714 == 65536 / 7;
	-------------------------------------------------------
	���x�Ɋւ��Ă͗ǂ��킩��Ȃ��B
---------------------------------------------------------*/
inline static void vfpu_div_s32(int *result_value000, int value000, int value111)
{
	int result_value;
	// result_value = value000 / value111;
	__asm__ volatile (
		"mtv        %1, S000\n" 			/* S000 = (value000); */
		"mtv        %2, S001\n" 			/* S001 = (value111); */
		#if 0/*(means same.����)*/
	//	"vi2f.s     S000, S000,    0\n" 	/* S000 = ((float)(S000)/(float)(0.0f)); [from int to �� float conversion.�ϊ�] */
	//	"vi2f.s     S001, S001,    0\n" 	/* S001 = ((float)(S001)/(float)(0.0f)); [from int to �� float conversion.�ϊ�] */
		#else
		"vi2f.p     C000, C000,    0\n" 	/* C000.p = ((float)(C000.p)/(float)(0.0f)); [from int to �� float conversion.�ϊ�] */
		#endif
		"vdiv.s     S002, S000, S001\n" 	// S002 = S000 / S001	// result_value = value000 / value111;
		"vf2iu.s    S002, S002,    0\n" 	/* S000.s = (int)(S000.s * (0.0f));[from float to �� int conversion.�ϊ�] */
		"mfv        %0, S002\n"
		: "=r"(result_value)				/* %0(result_value) [output.�o��]*/
		: "r"(value000), "r"(value111)		/* %1(value000), %2(value111) [input.����]*/
	);
	(*result_value000) = (s32)(result_value);
}
#endif

extern int atan_65536(int y, int x);/*(vfpu/math_atan65536i.c)*/
extern void cpu_exec(u32 *codebase, s32 icount)
{
	/*
	���̂� 'const' �� 'static const' �ɂ���ƒx���Ȃ�B
	'static const' ����Ȃ��� 'const' �̕����R�[�h���傫���Ȃ邪�����B
psp-gcc -v
Using built-in specs.
Target: psp
Configured with: ../../gcc-4.3.5/configure --build=i686-pc-mingw32
 --prefix=/pspsdk --target=psp --enable-languages=c,c++,objc,obj-c++,d
 --enable-cxx-flags=-G0 --with-newlib --with-headers --disable-win32-registry
 --disable-nls --disable-libstdcxx-pch --with-libiconv-prefix=/usr/local
 --with-gmp-include=/usr/local/include --with-gmp-lib=/usr/local/lib
 --with-mpfr-include=/usr/local/include --with-mpfr-lib=/usr/local/lib
Thread model: single
gcc version 4.3.5 (GCC)
	*/
	#define OB0x99_MAX	(0x08)/*[CPU�����R�[�h�̍ő吔]*/
	/*static*/ const void *jump_table_basic[(OP0x99_MAX + OB0x99_MAX)] __attribute__((aligned(16))) =/*(��{�I�y�R�[�h[basic opecodes])*/
	{	// 0x30 == (OP0x99_MAX + OB0x99_MAX);
		// [CPU�O������]
		&&OP0x00, &&OP0x01, &&OP0x02, &&OP0x03, &&OP0x04, &&OP0x05, &&OP0x06, &&OP0x07,// (��{����)-------- /
		&&OP0x08, &&OP0x09, &&OP0x0a, &&OP0x0b, &&OP0x0c, &&OP0x0d, &&OP0x0e, &&OP0x0f,// (��{����)-------- /
		&&OP0x10, &&OP0x11, &&OP0x12, &&OP0x13, &&OP0x14, &&OP0x15, &&OP0x16, &&OP0x17,// (�T�|�[�g����)-------- /
		&&OP0x18, &&OP0x19, &&OP0x1a, &&OP0x1b, &&OP0x1c, &&OP0x1d, &&OP0x1e, &&OP0x1f,// (�g������)-------- �����������O�V���[�g�A�h���b�V���O�B
		// [CPU�����R�[�h]
		&&OB0x20, &&OB0x21, &&OB0x22, &&OB0x23, &&OB0x24, &&OB0x25, &&OB0x26, &&OB0x27,// [CPU�����R�[�h]-------- �����������O�V���[�g�A�h���b�V���O�B
	};
//	/*static*/ const void *jump_table_memory_long_short[(8)] __attribute__((aligned(16)));/*(�����������O�V���[�g�A�h���b�V���O�B[addressing for memory long/short.])*/
//	#define JUMP_TABLE_MEMORY_LONG_SHORT_OFFSET 	(0x28)/*(�I�t�Z�b�g)*/
	u32 fetch_data32;/*(32[bit] fetch code. it used opecodes and fetch data or temporary.)*/
loop_start:
	opcode_fetch();/*[fech]*/
	u8 op = ((fetch_data32 >>  0)/*& 0x3f*/);/*(�Ƃ肠����)*/
	u8 v0 = ((fetch_data32 >>  8)/*& 0xff*/);
	u8 ra = ((fetch_data32 >> 16)/*& 0xff*/);
	u8 rb = ((fetch_data32 >> 24)/*& 0xff*/);
	#if (1==USE_CPU_DEBUG_MODE)
	if ((u8)0x1f < op)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// ���p40��"�ő�\��������"
			"CPU���߃G���[: %08x �͈Ӗ�������܂���B" "\\n"
			"%08x %08x %08x %08x %d" "\\n",
			fetch_data32,
			opecode_history[0],
			opecode_history[1],
			opecode_history[2],
			opecode_history[3],
			opecode_history_pointer
		);
	}
	#else
	if ((u8)0x1f < op)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// ���p40��"�ő�\��������"
			"CPU���߃G���[: %08x �͈Ӗ�������܂���B" "\\n",
			fetch_data32
		);
	}//1111022f
	#endif
	#if 0
	0a0a0f0b // MCODE(OP0x1d_ANDM_PD, R0f, R0a, R0a),
	0a0a0f16 // MCODE(OP0x16_RAND_INIT, R0f, R0a, R0a),
	0a0a0f21 // MCODE(OP0x06_BNE_RS, R0f, R0a, R0a),
	0c074678 // MCODE(OP0x78__???
	3
	#endif
MLS_COMMON:
	goto *jump_table_basic[(op)];
/*-------------------------------------------------------*/
OP_MLS:// �����������O�V���[�g�A�h���b�V���O�B
	if (LONG_MEMORY_ADDRESSING==v0)
			{opcode_fetch();/*[fech]*/}/*(�����O�������A�h���b�V���O)*/
	else	{fetch_data32 = (s32)(s8)v0;v0 = 0;}/*(�V���[�g�������A�h���b�V���O)*/ /*([�K�v]�C���f�b�N�X�t/�f�N�������g�t)*/
	// �V���[�g�������A�h���b�V���O�́A�f�N�������g�K�{�ł��B�łȂ��Ƃ���܈Ӗ�������[�ȋC������B
//	goto *jump_table_memory_long_short[(op & 0x07)];
//	goto *jump_table_basic[JUMP_TABLE_MEMORY_LONG_SHORT_OFFSET+(op & 0x07)];
//	goto *jump_table_basic[(op+8)];
	op += 8;
	goto MLS_COMMON;
/*-------------------------------------------------------*/
//
/*---------------------------------------------------------
[��{����]	�J�E���^�[���߁B
	-------------------------------------------------------
	���̖��߂́A�����I�ɂ͖����Ă��o���܂����A(���s���x���̊ϓ_�����܂���)
	�����������֗��Ȃ̂ő��݂��܂��B
	�X�y�J�R���p�C���̐݌v��(���Ԃ�)�y�ɂȂ�܂����B
	-------------------------------------------------------
	����: �w�肵�����W�X�^�̒l�u�J�E���^�l�v�� +1 ���܂��B
	���ꂾ�����ƁA ADD_R REG = REG + #1; �� MOVE_R REG = REG + ix(#1); �Ɠ����ł����A
	���̖��߂̏ꍇ�u�J�E���^����v���ݒ�ł��āA�u�J�E���^����v�𒴂���ƁA
	�����I�Ɂu�J�E���^�l�v���u0�v�ɂȂ�܂��B
	-------------------------------------------------------
	�u�J�E���^����v�̎w����@�͊�{�I�ɂ́u���l�v�Ŗ��߂̒��Ɋ܂܂�܂����A
	[���W�X�^�ԐڃA�h���b�V���O]���g�p���āu���W�X�^�l�v(�J�E���^�l�ł͂Ȃ�)�ŁA�w��ł��܂��B
	����́A��Փx�ʂɒe����e�̎��ԊԊu�����ω�������̂Ŏg�p���܂��B
---------------------------------------------------------*/
	#if 0/*[����]*/
	spell_register[ra]++;
	if (REGISTER_ADDRESSING==v0)/*[���W�X�^�ԐڃA�h���b�V���O]*/
	{
		if (spell_register[rb] <= (spell_register[ra]))
		{spell_register[ra] = (0);}
	}
	else/*[���l�A�h���b�V���O]*/
	{
		if (v0 <= (spell_register[ra]))
		{spell_register[ra] = (0);}
	}
	goto OP_NEXT;
	#endif
OP_02_COUNTER://	(r35)�J�[�h�X�N���v�g�p����(�J�E���^�[)
	#if 1// [���W�X�^�ԐڃA�h���b�V���O] == ��Փx�ʂɒe����e�̎��ԊԊu�����ω�������̐�p�̃J�E���^���߁B
	if (REGISTER_ADDRESSING == v0)/*[���W�X�^�ԐڃA�h���b�V���O]*/
	{v0 = spell_register[rb];}
	#endif
//	else/*[���l�A�h���b�V���O]*/	{;}
	// [���l�A�h���b�V���O]==�ʏ�̃J�E���^���߁B(�ʏ�̏ꍇ�A�J�E���^���߂͑��l�ȊO�p�r�������B)
	spell_register[ra]++;
	if (v0 <= (spell_register[ra]))
	{spell_register[ra] = (0);}
	goto OP_NEXT;
/*---------------------------------------------------------
[��{����]	���W�X�^�ԓ]�����߁B
	-------------------------------------------------------
	���̖��߂́A���W�X�^�̒l�𑼂̃��W�X�^�ɃR�s�[���܂��B
	-------------------------------------------------------
	�R�s�[����ۂɁA�C���N�������g �� �f�N�������g(�����Z)�@�\������܂��B
	(���m�Ȗ��̂� �v���C���N�������g / �v���f�N�������g)
	-------------------------------------------------------
	�u���l�v�̉����Z�͂��̖��߂łł��܂����A
	�u���W�X�^�l�v�̉����Z�͂��̖��߂łł��Ȃ��̂ŁAADDR ���g�p���܂��B
---------------------------------------------------------*/
OP_01_MOVER_PD:
//	spell_register[ra] = ((s32)spell_register[rb]) + (s32)v0;/*([�_��]�ȈՃC���f�b�N�X�f�N�������g������)*/
	// �C���N�������g/�f�N�������g�́A���̖��߂��g�������ǂ��C������
	spell_register[ra] = ((s32)spell_register[rb]) + (s32)(s8)v0;/*([�K�v]�C���f�b�N�X�t/�f�N�������g�t)*/
	goto OP_NEXT;
#if 0// [���g�p]
/*-------------------------------------------------------*/
// [���g�p]	���W�X�^�� AND���Z���߁B
OP_03_ANDR_PD://[���g�p]
//	spell_register[ra] = (((s32)spell_register[ra]) & ((s32)spell_register[rb])) + (s32)(s8)v0;//[�p�~]
//	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)spell_register[ra])) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
// ���W�X�^�� ���Z(���Z)���߁B
OP_04_ADDR_PD:
//	spell_register[ra] = (((s32)spell_register[ra]) + ((s32)spell_register[rb])) + (s32)(s8)v0;//[�p�~]
	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	goto OP_NEXT;
#if 1
/*-------------------------------------------------------*/
// ���W�X�^�� ���Z(�������])���߁B(A = B-A; �� B �� 0 �Ȃ畄�����])
OP_05_SUBR_PD://OP_05_NEGR_PD:://MCAA
	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	goto OP_NEXT;
#endif
#if 0
/*-------------------------------------------------------*/
// ���W�X�^�� ASR ���߁B
OP_06_ASRR_PD://[���g�p]
	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	goto OP_NEXT;
#endif
#if 0
/*-------------------------------------------------------*/
// ���W�X�^�� ASL ���߁B
OP_07_ASLR_PD://[���g�p]
	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
//	�����O�A�h���b�V���O
/*-------------------------------------------------------*/
//	��Փx�f�R�[�h���߁B
	#if 0// C����(-r40)
	VR04_NAN_IDO_DECODE = ((VR04_NAN_IDO_DECODE >> (cg_VR20_game_difficulty<<3)) & 0xff);
	#endif

OP_03_nan_ido:
	{
		// (�g����.A) (�������A�h���b�V���O)�̏]���݊��͂Ȃ��Ȃ邪�A�p�b�N���߂Ƃ��Ĕėp���ł���B
		#define USE_EXTRA_OP_NANIDO 	(0)
		if (REGISTER_ADDRESSING==v0)/*(��Փx�p�b�N�̓��W�X�^�ɂ���)*/
		{	/*(���W�X�^�A�h���b�V���O)*/
			fetch_data32 = spell_register[rb];
			#if (1==USE_EXTRA_OP_NANIDO)
			// (�g����.A)[������(�������A�h���b�V���O)�̂ݎw���]
			rb = R20_PLAYER_DATA_game_difficulty;// (���W�X�^�A�h���b�V���O)�̏ꍇ�A�����I�ɓ�Փx�f�R�[�h��p���߁B
			#endif
		}
		else/*(��Փx�p�b�N�̓������ɂ���)*/
	//	if (MEMORY_ADDRESSING==v0)/
		{	/*(�������A�h���b�V���O)*/
			opcode_fetch();/*[fech]*/
		}
		#if (1==USE_EXTRA_OP_NANIDO)
		// (�g����.A)[������(�������A�h���b�V���O)�̂ݎw���]
		spell_register[ra] = ((fetch_data32 >> (spell_register[rb]<<3)) & 0xff);
		#else
		spell_register[ra] = ((fetch_data32 >> (cg_VR20_game_difficulty<<3)) & 0xff);
		#endif
	}
	goto OP_NEXT;
//
/*-------------------------------------------------------*/
//	�T�|�[�g�A�h���b�V���O
/*-------------------------------------------------------*/
// ���߁B
	#if (0)/*(���d�l����)*/
	h->math_vector.x256  = si n1024((int_angle1024))*(/*p->speed*/(16*KETM075));/*fps_factor*/		/* CCW�̏ꍇ */
	h->math_vector.y256  = co s1024((int_angle1024))*(/*p->speed*/(16*KETM075));/*fps_factor*/
	VR06	= (((int)(co s(de g1024tor ad(REG_10_ANGLE1024))*REG_11_SPEED256)));/*(fps_factor)*/
	VR07	= (((int)(si n(de g1024tor ad(REG_10_ANGLE1024))*REG_11_SPEED256)));/*(fps_factor)*/
	#endif
	#if (0)/* C����(-r40) */
	{
		int sin_value_t256; 		// sin_value_t256 = 0;
		int cos_value_t256; 		// cos_value_t256 = 0;
	//	int256_sincos1024((deg65536to1024(VR13)), &sin_value_t256, &cos_value_t256);
		int256_sin cos65536((VR13), &sin_value_t256, &cos_value_t256);
		VR06	 = (((cos_value_t256)*(VR11))>>8);/*fps_factor*/
		VR07	 = (((sin_value_t256)*(VR11))>>8);/*fps_factor*/
	}
	#endif
// R13: 	HATSUDAN_R13_angle65536
// R11: 	HATSUDAN_R11_speed256
OP_10_SINCOS256:
	{
		/*register*/ int sin_value_t256;		// sin_value_t256 = 0;
		/*register*/ int cos_value_t256;		// cos_value_t256 = 0;
		int256_sincos65536((VR13), &sin_value_t256, &cos_value_t256);
		spell_register[ra]	 = (((cos_value_t256)*(VR11))>>8);/*fps_factor*/
		spell_register[rb]	 = (((sin_value_t256)*(VR11))>>8);/*fps_factor*/
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �{�X���玩�@�_�����߁B(�{�X ���� ���@ ��_���ꍇ�̊p�x�𒲂ׂ܂��B)
OP_11_BOSS_TO_JIKI_NERAI:
	VR06	= cg_BOSS_DATA_3a_center_x256;/*(�e��x256 �{�X���S���甭�e�B�_����[source])*/
	VR07	= cg_BOSS_DATA_3b_center_y256;/*(�e��y256 �{�X���S���甭�e�B�_����[source])*/
	/*(fall_through)*/	//goto OP_NEXT;
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
// ���@�_�����߁B(src ���� ���@ ��_���ꍇ�̊p�x�𒲂ׂ܂��B)
	// ���d�l����(zzz_player, dest);
	#if (0)/*(���d�l����)*/
	VR06	= (dest->center.x256);			/*(�_����[distination])*/
	VR07	= (dest->center.y256);			/*(�_����[distination])*/
	#endif
OP_12_JIKI_NERAI:
	{
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
		VR04	= (zzz_player->center.x256);	/*(�_����[distination])*/
		VR05	= (zzz_player->center.y256);	/*(�_����[distination])*/
	}
	/*(fall_through)*/	//goto OP_NEXT;
/*-------------------------------------------------------*/
// �ėp�_�����߁B(src ���� dest ��_���ꍇ�̊p�x�𒲂ׂ܂��B)
	#if (0)/*(���d�l����)*/
	VR04	= (src->center.x256);		/*(�_����[source])*/
	VR05	= (src->center.y256);		/*(�_����[source])*/
	VR06	= (dest->center.x256);		/*(�_����[distination])*/
	VR07	= (dest->center.y256);		/*(�_����[distination])*/
	#endif
OP_13_HANYOU_NERAI:
	HATSUDAN_R13_angle65536 = (atan_65536((VR05 - VR07), (VR04 - VR06)));
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �x�N�g���������߁B
	#if (0)/*(���B�������l�����āA��������B)*/
	VR04	= ((my_menu_resource[i].x_offset[move_mode	])<<8); 	/*(�����ʒu[A]t256()�`��)*/
//	VR05	= ((my_menu_resource[i].y_offset[move_mode	])<<8); 	/*(�����ʒu[A]t256()�`��)*/
	VR06	= ((my_menu_resource[i].x_offset[move_mode+1])<<8); 	/*(�����ʒu[B]t256()�`��)*/
//	VR07	= ((my_menu_resource[i].y_offset[move_mode+1])<<8); 	/*(�����ʒu[B]t256()�`��)*/
	REG_11_TAMA1	= move_rate256;/*(��������t256()�`��)*/
	multiprex_rate();
	#endif
	//
	#if 0/* C����(-r40) */
	#if 1/*([X]�x�N�g������)*/
	/*(���������͊���[A]�Ɗ���[B]�ŁA�ǂ��炪��ł��\��Ȃ��B)*/
	int x_sa256;/*(t256()�`��)*/
	/*�����ʒu[A]*/x_sa256	= (((VR04)*(256-REG_11_GOUSEI_WARIAI256))>>8);/*(����[A]������)*/
	/*�����ʒu[B]*/x_sa256 += (((VR06)*(	REG_11_GOUSEI_WARIAI256))>>8);/*(����[B]������)*/
	VR06	= x_sa256;/*(����[X])*/
	#endif
	#if 1/*([Y]�x�N�g������)*/
	/*(���������͊���[A]�Ɗ���[B]�ŁA�ǂ��炪��ł��\��Ȃ��B)*/
	int y_sa256;/*(t256()�`��)*/
	/*�����ʒu[A]*/y_sa256	= (((VR05)*(256-REG_11_GOUSEI_WARIAI256))>>8);/*(����[A]������)*/
	/*�����ʒu[B]*/y_sa256 += (((VR07)*(	REG_11_GOUSEI_WARIAI256))>>8);/*(����[B]������)*/
	VR07	= y_sa256;/*(����[Y])*/
	#endif
	#endif

OP_14_MULTIPREX_RATE_VECTOR:
	opcode_fetch();/*[fech]*/
	{
	//-----------------
	register int value256;/*(t256()�`��)*/
	#if 1/*([X]�x�N�g������)*/
	/*(���������͊���[A]�Ɗ���[B]�ŁA�ǂ��炪��ł��\��Ȃ��B)*/
	/*�����ʒu[A]*/value256	= (((VR04)*(256-(s32)fetch_data32))>>8);/*(����[A]������)*/
	/*�����ʒu[B]*/value256 += (((VR06)*(	(s32)fetch_data32))>>8);/*(����[B]������)*/
	spell_register[ra]	= value256;/*(����[X])*/
	#endif
	#if 1/*([Y]�x�N�g������)*/
	/*(���������͊���[A]�Ɗ���[B]�ŁA�ǂ��炪��ł��\��Ȃ��B)*/
	/*�����ʒu[A]*/value256	= (((VR05)*(256-(s32)fetch_data32))>>8);/*(����[A]������)*/
	/*�����ʒu[B]*/value256 += (((VR07)*(	(s32)fetch_data32))>>8);/*(����[B]������)*/
	spell_register[rb]	= value256;/*(����[Y])*/
	#endif
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �����l�擾���߁B
OP_15_RAND_VALUE:
	spell_register[ra] = (ra_nd());
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �����V�[�h�ݒ薽�߁B
OP_16_RAND_INIT:
	goto OP_NEXT;
/*-------------------------------------------------------*/
// (div65536)����Z���߁B
	#if 0// C����(-r40)
	if (0 != VR0d)
	{
		VR0e	= (int)(65536 / VR0d);/*(div command)*/ 		/* �����p�x:  (r35-) */
	}
	#endif
OP_17_DIV65536:
	if (0 != spell_register[rb])
	{
		#if (1==USE_VFPU_INTEGER_DIVISOR)
		/*(vfpu�Ŋ���Z���邱�Ƃɂ��Acpu�̃p�C�v���C���u���C�N��h���B)*/
		int a_round_65536;
		a_round_65536 = 65536;
		vfpu_div_s32(&spell_register[ra], a_round_65536, spell_register[rb]);/*(div command)*/	/* �����p�x:  (r35-) */
		#else
		spell_register[ra]	= (int)(65536 / spell_register[rb]);/*(div command)*/			/* �����p�x:  (r35-) */
		#endif
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// ��{�e�������߁B
OP_0c_hatudan_system_regist_tama:
//OP_18_hatudan_system_regist_single:
//OP_18_hatudan_system_regist_katayori_n_way:
//OP_18_hatudan_system_regist_n_way:
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);
	hatudan_system_regist_tama(v0);
	goto OP_NEXT;
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
// �ėp���ʉ����߁B
OP_0d_AUDIO_VOICE_PLAY:
	audio_voice_play();
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �e��p���ʉ����߁B
OP_0e_AUDIO_AUTO_BULLET_PLAY_SET_18:
	AUDIO_18_voice_number	= v0;
	audio_auto_bullet_play();
	goto OP_NEXT;
/*-------------------------------------------------------*/
	/* (r35)�J�[�h�X�N���v�g�p����(�J�[�h���W�X�^�S������) */
OP_0f_CLEAR_ZERO_PAGE:
	{
		int i;
		for (i=0; i<REG_NUM_0x1c_ZERO_PAGE_MAX; i++)
		{
			spell_register[i] = (0);	/* �l(0)�ŏ����� */
		}
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
	#if 0/*(��)*/ // (OP0x1f != OP_NOP_debug)/*(�܂�����ĂȂ����ǁA���̖��߂͕K�v�B)*/
//	�v���Z�X�o�^�B
OP_06_REGIST_PROCESS:
	/*(�܂�����ĂȂ�)*/
	goto OP_NEXT;
	#endif
/*-------------------------------------------------------*/
// �u�����` NOT �n���߁B
/*-------------------------------------------------------*/
// �u�����` BNE ���߁B(Branch Not Equal)
OP_08_BNE_RS:
	if (v0 != spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/else{goto OP_NEXT;}/*(���򂵂Ȃ�)*/
// �u�����` BNL ���߁B(Branch FLow)
OP_09_BFL_RS:
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/else{goto OP_NEXT;}/*(���򂵂Ȃ�)*/
/*-------------------------------------------------------*/
// �u�����`�B
/*-------------------------------------------------------*/
// �u�����`(�W�����v�e�[�u��[�⏕]����)�B
OP_06_BRAR_NN:
	/*(rb �� ���l�B���W�X�^����Ȃ��̂Œ���[�������ɃW�����v�Ή�(s8)(-127 <= rb <= +128)])*/
	// �����1. V0+VRA-VRB �̃A�h���X�ɃW�����v�B(�K�v�Ȃ�?)
//	rb = (-((s32)spell_register[rb]) + ((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	// �����2. V0+VRA �̃A�h���X�ɃW�����v�B(�K�v�Ȃ�?)
//	rb = (((s32)spell_register[ra])) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	// �����3. VRB �̑��΃A�h���X�ɃW�����v�B
	rb = spell_register[rb];
	// �K�����򂷂�B
	goto OP_0b_BRA_RS;/*(���򂷂�)*/
/*-------------------------------------------------------*/
// �u�����` �z��ǂݍ��� ���߁B
OP_0a_BRA_TABLE:
	{
		u32 *data_base;
		data_base = codebase;
		{data_base += (s32)spell_register[(u32)v0];}/*(���W�X�^)*/
		spell_register[ra] = (*data_base);
	}
	// �K�����򂷂�B
	//goto OP_0b_BRA_RS;/*(���򂷂�)*/
/*-------------------------------------------------------*/
// �u�����`�B
OP_0b_BRA_RS:
	#if (1==USE_CPU_EXTRA)/*([�����Ă��o���邯��]�����������֗�)*/
	if (CPU_QUIT==rb) {goto OP_00_EXIT;}
	#endif
	//
	#if (1==USE_CPU_DEBUG_MODE)
	codebase_bak = codebase;
	#endif
	// ���΃W�����v�ł��B(�X�y�JCPU�̏ꍇ�A����ȊO�p�r���Ȃ��B����ɐ�΃W�����v����Ă�����I)
	// +100/-100 �𒴂��郍���O�W�����v�͗p�r���Ȃ��̂ł����A���ꋐ��ȃX�y�J������ėp�r�����������ꍇ�� BRA ��g�ݍ��킹�܂��B
	// ���܂�ɋ���(���ʂ�100�{�̃T�C�Y�Ƃ�)�ȃX�y�J�́A�L���b�V�����炠�ӂ�Ă��Ԃ�Q�[���ɂȂ�Ȃ����x���Ȃ�Ǝv���̂ŁA���p�I�ł͂���܂���B
//	{codebase += (s32)rb;}/*([�_���B����ł͕������ɃW�����v�o���Ȃ�(s32)(u8)rb�ɂȂ����Ⴄ(s32)(u8)rb(0 <= rb <= 255)]���l�B���W�X�^����Ȃ��̂Œ���)*/
	{codebase += (s32)(s8)rb;}/*(rb �� ���l�B���W�X�^����Ȃ��̂Œ���[�������ɃW�����v�Ή�(s8)(-127 <= rb <= +128)])*/
	#if (1==USE_CPU_DEBUG_MODE)
	hook_counter--;
	if (0 > hook_counter)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// ���p40��"�ő�\��������"
			"bug %8x %8x %8x %8x" "\\n"
			"%8x %8x %8x %8x %d" "\\n",
			fetch_data32,
			(u32)codebase,
			(u32)codebase_bak,
			(u32)(s32)rb,
			opecode_history[0],
			opecode_history[1],
			opecode_history[2],
			opecode_history[3],
			opecode_history_pointer
			 );
		// "0a0a0f16 0a0a0f21 0c074678 0a0a0f0b 3"
	}
	#endif
	#if 0/*(0==hook_counter[1���]ok���ۂ�)*/
	// bug
	fetch_data32: 030a0020 // MCODE(OP0x20_BEQ_RS, (0), R0a, (+3)),
	(u32)codebase: 08a040e0
	(u32)codebase_bak: 08a040d4
	(u32)(s32)rb: 3
	opecode_history[0]: 00091001 // MCODE(OP0x01_COUNTER, 16, R09, NAX),
	opecode_history[1]: 00000011 // MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),//CPU_CALL(calculate_boss_to_jiki_nerai);
	opecode_history[2]: 100a200b // MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
	opecode_history[3]: 030a0020 // MCODE(OP0x20_BEQ_RS, (0), R0a, (+3)),
	opecode_history_pointer: 0
	#endif
	goto OP_NEXT;

/*-------------------------------------------------------*/
// �������� ���Z(���Z)���߁B(ToDo: ���̖��߂̃V���[�g�A�h���b�V���O�͗v��Ȃ�)
OB_1b_CALC_ADDM_LONG_PD:// �����������O�A�h���b�V���O�B(�����O��p)
//	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)fetch_data32)) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)fetch_data32)) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
#if 0// [���g�p]
/*-------------------------------------------------------*/
// �������� ���Z(�������])���߁B(A = B-A; �� B �� 0 �Ȃ畄�����])
OB_1d_CALC_SUBM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)fetch_data32)) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)fetch_data32)) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
#endif
#if 1
/*-------------------------------------------------------*/
// �������� ASL ���߁B
OB_1f_CALC_ASLM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)fetch_data32)) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)fetch_data32)) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
#endif
#if 1
/*-------------------------------------------------------*/
// �������� ASR ���߁B
OB_1e_CALC_ASRM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)fetch_data32)) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)fetch_data32)) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
// �������� AND���Z���߁B
OB_1d_CALC_ANDM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)fetch_data32)) + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)fetch_data32)) + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
	goto OP_NEXT;
/*-------------------------------------------------------*/
// �������� �]�����߁B(ZERO���W�X�^�g���Ȃ� OB_1b_CALC_ADDM_LONG_PD �ő�p�ł���)
OB_1c_CALC_MOVEM_PD:
//	spell_register[ra] = (s32)fetch_data32 + (s32)(s8)v0;/*(�C���f�b�N�X�t/�f�N�������g�t)*/
	spell_register[ra] = (s32)fetch_data32 + (s32)v0;/*(�ȈՃC���f�b�N�X�f�N�������g������)*/
//	goto OP_NEXT;
/*-------------------------------------------------------*/
OP_NEXT:// ���̖��߂ɐi�ށB
// �c����s�����B
	icount--;/*[one machine code executed.][�c����s�J�E���g��������炷]*/
	/*[icount remain, if goto loop.][�c����s�J�E���g��������΃��[�v���Ď��s�𑱂���]*/
	if (0 < icount) goto loop_start;
	/*[no icount when done.][�c����s�J�E���g�����Ȃ���ΏI��]*/
/*---------------------------------------------------------
[��{����]	�X�y�J�t���[���I�����߁B
	-------------------------------------------------------
	���̖��߂́A�����I�ɃX�y�J�t���[�����I�����܂��B
	-------------------------------------------------------
	�c����s�J�E���g���������Ă��A�����I�Ƀ[���ɂȂ�܂��B
---------------------------------------------------------*/
OP_00_EXIT:
	;
//	icount = (0);	// [�I���Ȃ̂Ŏc����s�J�E���g���̓[���ɂ���]
//	[�X�y�J�t���[���I���t���O = on;]
//	goto CPU_EXIT;
}

/*---------------------------------------------------------
[��1]
�u�����` BPL ���߂́A
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}
�Ȃ̂ŁA�Ⴆ�� v0==3�Aspell_register[ra]==3 �̏ꍇ�A
	if ((3) <= (3)) 	{goto OP_0b_BRA_RS;}
�ƂȂ蕪�򂵂܂��B���̂��肬�蕪�򂷂鋫�E����
�u�����` BHI ���߂ŗႦ��ƁA
	if ((2) < (3))		{goto OP_0b_BRA_RS;}
�ŕ��򂵂܂��B
v0 �͂��̏ꍇ�j�󂵂Ă��ǂ����A�K�������Ȃ̂�����A
�u�����` BHI ���߂� v0 = v0 + (1); ����� �u�����` BPL ���� �Ƃقړ����ɂȂ�܂��B
���҂̈Ⴂ�́Av0 �̗L���͈� �� singned char �`��(-127 <= v0 <= 128) �Ȃ̂ŁA
�L���͈͂̋��E�t�߂̓���͕ς��܂��B(���R�ЂƂ����)
---------------------------------------------------------*/
	#if (000)/*([����]���̕ӂ́A�v��Ȃ�)*/
/*-------------------------------------------------------*/
// �u�����` BEQ ���߁B
OP_20_BEQ_RS:
	if (v0 == spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/
	goto OP_NEXT;/*(���򂵂Ȃ�)*/
/*-------------------------------------------------------*/
#if 0
// �u�����` BHI ���߁B
OP_22_BHI_RS:
	#if (0)
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/
	goto OP_NEXT;/*(���򂵂Ȃ�)*/
	#else
	v0++;/*(�قړ���[��1])*/
	#endif
/*-------------------------------------------------------*/
// �u�����` BPL ���߁B
OP_23_BPL_RS:
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/
	goto OP_NEXT;/*(���򂵂Ȃ�)*/
#else
// �u�����` BPL ���߁B
OP_23_BPL_RS:
	#if (0)
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/
	goto OP_NEXT;/*(���򂵂Ȃ�)*/
	#else
	v0--;/*(�قړ���[��1])*/
	#endif
/*-------------------------------------------------------*/
// �u�����` BHI ���߁B
OP_22_BHI_RS:
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(���򂷂�)*/
	goto OP_NEXT;/*(���򂵂Ȃ�)*/
#endif
	#endif// (000)


/*---------------------------------------------------------
	�O�� I/F (�C���^�[�t�F�C�X)
	-------------------------------------------------------
	�X�y�JCPU�ɂ̓Q�[���̑S�@�\���W�񂳂�Ă���̂ŁA
	�Q�[���̋@�\���g���ꍇ�ɃX�y�JCPU���g���K�v������܂��B
	�����ł����́A�X�y�JCPU�ɊO�� ����A�N�Z�X����ꍇ��
	�C���^�[�t�F�C�X�ł��B
	�K�v�������́A�����I�ɏ����p�~��������ŁB
---------------------------------------------------------*/
#if 0
extern void cpu_bios(int call_bios_number)
{
	/*static*/ const void *jump_table_bios[(0x10)] __attribute__((aligned(16))) =/*()*/
	{
		// [BIOS]
		&&BIOS0x00, &&BIOS0x01, &&BIOS0x02, &&BIOS0x03, &&BIOS0x04, &&BIOS0x05, &&BIOS0x06, &&BIOS0x07,//
		&&BIOS0x08, &&BIOS0x09, &&BIOS0x0a, &&BIOS0x0b, &&BIOS0x0c, &&BIOS0x0d, &&BIOS0x0e, &&BIOS0x0f,//
		&&BIOS0x10, &&BIOS0x11, &&BIOS0x12, &&BIOS0x13, &&BIOS0x14, &&BIOS0x15, &&BIOS0x16, &&BIOS0x17,//
		&&BIOS0x18, &&BIOS0x19, &&BIOS0x1a, &&BIOS0x1b, &&BIOS0x1c, &&BIOS0x1d, &&BIOS0x1e, &&BIOS0x1f,//
	};
	goto *jump_table_bios[(call_bios_number)];
		BIOS0x00: BIOS0x01: BIOS0x02: BIOS0x03: BIOS0x04: BIOS0x05: BIOS0x06: BIOS0x07:
		BIOS0x08: BIOS0x09: BIOS0x0a: BIOS0x0b: BIOS0x0c: BIOS0x0d: BIOS0x0e: BIOS0x0f:
		BIOS0x10: BIOS0x11: BIOS0x12: BIOS0x13: BIOS0x14: BIOS0x15: BIOS0x16: BIOS0x17:
		BIOS0x18: BIOS0x19: BIOS0x1a: BIOS0x1b: BIOS0x1c: BIOS0x1d: BIOS0x1e: BIOS0x1f:
}
#endif
/*---------------------------------------------------------
	(r36)�J�[�h�X�N���v�g�p����(sincos)
	-------------------------------------------------------
	�g�p���W�X�^:
	R11 	REG_11		== HATSUDAN_R11_speed256	����(���x�A���a, t256�`��)
	R13 	REG_13		== HATSUDAN_R13_angle65536	����(�p�x65536, d65536�`��)
	R06 	REG_02: 	�o��(cos(angle) x radius, t256�`��)
	R07 	REG_03: 	�o��(sin(angle) x radius, t256�`��)
---------------------------------------------------------*/
extern CPU_FUNC(sincos256)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x10_SINCOS256, NAX, R06, R07),
	//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	�{�X���玩�@�_���p�쐬
	-------------------------------------------------------
	boss(x, y)�̈ʒu����A�v���C���[(x, y)�Ɍ������p�x��
	HATSUDAN_R13_angle65536�Ɍv�Z����B
---------------------------------------------------------*/
extern CPU_FUNC(calculate_boss_to_jiki_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	���@�_���p�쐬
	-------------------------------------------------------
	dest(x, y)�̈ʒu����A�v���C���[(x, y)�Ɍ������p�x��
	HATSUDAN_R13_angle65536�Ɍv�Z����B
---------------------------------------------------------*/
extern CPU_FUNC(calculate_jiki_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
	//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	���@(src)�_���e(dest)�̊p�x(���S�����S)��
	(�J�[�hcpu�̓���������HATSUDAN_R13_angle65536��)�v�Z�B
	-------------------------------------------------------
	��(src)�̒��S���W����A
	��(dest)�̒��S���W�֑_���p�x���v�Z���A
	�ꎞ�p�x�ϐ�(HATSUDAN_R13_angle65536)�Ɍv�Z����B
	-------------------------------------------------------
	�Ⴆ�΁A��(src)==���@�A��(dest)==�G�e�Ȃ�A���@�_���e�B
	-------------------------------------------------------
	(r35)�_���p�v�Z�͑S�āA�J�[�hCPU���o�R����悤�ɕύX�����B
	�_���p�v�Z���v���O�����̕��������ɂ���ƁA���s���x���x�����Ēe���͖����B
	���̕ύX�Ŗ��̂��镔�����o�Ă��邪�A
	�{�Ƃł͂���Ǝ����d�l�ɂȂ��Ă���Ǝv����B
---------------------------------------------------------*/
extern CPU_FUNC(cpu_VR_angleCCW65536_src_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x13_HANYOU_NERAI, NAX, NAX, NAX),
	//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r36)�J�[�h�X�N���v�g�p����(multiprex_rate_vector)
	�������������B
	-------------------------------------------------------
	�g�p���W�X�^:
	REG_00: 	����(x0)
	REG_01: 	����(y0)
	REG_02: 	����(x1)/�o��(x2)
	REG_03: 	����(y1)/�o��(y2)
	REG_11: 	����(��������, t256�`��)
---------------------------------------------------------*/
extern CPU_FUNC(multiprex_rate_vector)
{
	static /*const*/ u32 codebase[2/*-1*/] =
	{
		MCODE(OP0x14_MULTIPREX_RATE_VECTOR, NAX, R06, R07),// �������A�h���b�V���O�B
		NAX,/*(REG_11_GOUSEI_WARIAI256)*/					// ������ �u����(��������, t256�`��)�v
	//	NAX/*(�I��)*/
	};
	codebase[1] = (u32)REG_11_GOUSEI_WARIAI256;// ����������CPU���s�������֏������ށB
	cpu_exec((u32*)&codebase, (1));// CPU���s�B
}

/*---------------------------------------------------------
	(r36)�J�[�h�X�N���v�g�p����(replay_rand_init)
	���v���C�Ή����������B
	-------------------------------------------------------
	�g�p���W�X�^:
	REG_00: 	����(���v���C�Ή������V�[�h�ݒ�)
---------------------------------------------------------*/

/*---------------------------------------------------------
	(r36)�J�[�h�X�N���v�g�p����(replay_rand)
	���v���C�Ή����������B
	-------------------------------------------------------
	�g�p���W�X�^:
	REG_03: 	�o��(���v���C�Ή������l)
---------------------------------------------------------*/

/*---------------------------------------------------------
	(r41)�J�[�h�X�N���v�g�p����(div65536)����Z���߁B
	-------------------------------------------------------
	1��(65536)�� ������ n���� ����B
	-------------------------------------------------------
	�g�p���W�X�^:
	R0d:	����(����l)
	R0e:	�o��(���������ʂ̒l)
	-------------------------------------------------------
	���̖��߂�CPU�L���b�V�����t���b�V������đ��x�ቺ����̂ŁA
	��{�I��[initialize section: �������Z�N�V����]�ȊO�ł͎g��Ȃ����B
---------------------------------------------------------*/
#if 0/*(�p�~)*/
//	/*(�p�~)*/extern CPU_FUNC(div65536);/*(�X�N���v�g�p)*/
//extern CPU_FUNC(div65536)
//{
//	static const u32 codebase[2] =
//	{
//		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),
//		NAX/*(�I��)*/
//	};
//	cpu_exec((u32*)&codebase, (1));
//}
#endif
/*---------------------------------------------------------
	(r41)�J�[�h�X�N���v�g�p����(nan_ido)��Փx�f�R�[�h���߁B
	-------------------------------------------------------
	��Փx���f�R�[�h����B
	-------------------------------------------------------
	�g�p���W�X�^:
	R04_NAN_IDO_DECODE: 	����(�S��Փx�p�b�N�l)
	R04_NAN_IDO_DECODE: 	�o��(���݂̓�Փx�A�萔�l)
---------------------------------------------------------*/
extern CPU_FUNC(nan_ido)
{
	#if 0//�o�O
//	static /*const*/ u32 codebase[2] =
//	{
//	//	MCODE(OP0x03_NAN_IDO, NAX, R04, NAX),//�o�O
//		NAX
//	};
//	codebase[1] = (u32)VR04;
//	cpu_exec((u32*)&codebase, (1));
	#endif
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R04, R04),
	//	NAX,/*(dummy?)*/
	//	NAX/*(�I��)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r41)�J�[�h�X�N���v�g�p
	�ėp���ʉ����߁B
---------------------------------------------------------*/
extern CPU_FUNC(cpu_voice_play)
{
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
	//	NAX/*(�I��)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r41)�J�[�h�X�N���v�g�p����
	�e��p���ʉ����߁B
---------------------------------------------------------*/
static CPU_FUNC(cpu_auto_bullet_play_default)
{
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	NAX/*(�I��)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	�X�y�J�� C���ꂩ�� �X�N���v�g�֊��S�ڍs�����ꍇ�̏���
	-------------------------------------------------------
	�܂�����ĂȂ��ł��B
---------------------------------------------------------*/
#define LINK_DUAL_SYSTEM (0)
#if (1==LINK_DUAL_SYSTEM)

#if 0
static u32 compiled_spell[] =
{
	/*[�R���p�C���ς݃X�y��]*/
}
#endif


static OBJ_CALL_FUNC(ci_run_init_section)
{
	/*[�X�y���������Z�N�V����]*/
}

static OBJ_CALL_FUNC(ci_spell_cpu)
{
	/*[�X�y�����s�Z�N�V����]*/
}
#endif /*(LINK_DUAL_SYSTEM)*/
