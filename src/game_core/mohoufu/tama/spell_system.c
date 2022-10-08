
#include "./../boss/boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�X�y�������V�X�e��(�J�[�h�𐶐�)
	-------------------------------------------------------
	����u�{�X�v�ȊO�ɂ��u���U�R�v�A�u���U�R�v���X�y�������ł���̂ŁA
	�u�X�y�������v�Ɓu�J�[�h�Ǘ��v�͕ʃV�X�e���ł��B
	(����u��-�{�X�v�͍��\�肪���邪����ĂȂ��B�J�[�h�����V�X�e�����܂�����ĂȂ�)
	-------------------------------------------------------
    ����        �J�[�h����      �J�[�h  �X�y������
    �{�X        ��              ��              ��  // �{�X
    ��-�{�X     �~(?)           ��              ��  // <�\��>           (�G���̗�����u�~�߂�v)
    ���U�R      �~              �~              ��  // ��[�݂�         �J�[�h�����ĂȂ��̂ŃJ�[�h��(����)�͖����B
    ���U�R      �~              �~              ��  // �������U�R       �J�[�h�����ĂȂ��̂ŃJ�[�h��(����)�͖����B
    �U�R        �~              �~              �~  // ���̑��̃U�R     �X�y�������o���Ȃ��B
    -------------------------------------------------------
    ����            �G������    �J�[�h
    �{�X��p�R�A    �~          ��                  // �G�������֘A�̏��������Ȃ��̂ł��̕������B
    ������p�R�A    ��          �~                  // �J�[�h�Ǘ��֘A�̏��������Ȃ��̂ł��̕������B
	-------------------------------------------------------
	(r33)��L�̐�p�R�A�v��͔p�~�B
	���̕���(r33)���Ƃނ����p�R�A�ɂ����������x�ቺ����B
	-------------------------------------------------------
	���C���[�V�X�e��
	-------------------------------------------------------
	���C���[�V�X�e���́u�e���v�̕����ʂ�A
	�e��P�̂Ƃ��Ă͔F�������A���Ƃ��ĔF������V�X�e���B
	-------------------------------------------------------
---------------------------------------------------------*/


/*---------------------------------------------------------
	�J�[�hCPU���j�b�g
---------------------------------------------------------*/

#include "spell_card_execute.h"

/*---------------------------------------------------------
	�e�� �� obj ���S�֐ݒ肷��B
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(set_REG_DEST_XY)
{
	VR06	= (src->center.x256);/* �e��x256 obj���S���甭�e�B */
	VR07	= (src->center.y256);/* �e��y256 obj���S���甭�e�B */
}

/*---------------------------------------------------------
	�e�� �� �{�X obj ���S�֐ݒ肷��B
---------------------------------------------------------*/

extern void set_REG_DEST_BOSS_XY(void)
{
	VR06	= cg_BOSS_DATA_3a_center_x256;/* �e��x256 �{�X���S���甭�e�B */
	VR07	= cg_BOSS_DATA_3b_center_y256;/* �e��y256 �{�X���S���甭�e�B */
}

/*---------------------------------------------------------
	�J�[�h��������(�W��?)
---------------------------------------------------------*/

#define SPELL_TIME_0064 	(64)/*SPELL_TIME_001_00sec_04x16_0064*/

#define SPELL_TIME_0100 	(100)
#define SPELL_TIME_0128 	(128)
#define SPELL_TIME_0192 	(192)
#define SPELL_TIME_0256 	(256)
#define SPELL_TIME_0352 	(352)/*(352==32*11)*/

#define SPELL_TIME_0512 	(512)

#define SPELL_TIME_0640 	(640)

#define SPELL_TIME_1024 	(1024)
#define SPELL_TIME_9999 	(16384)
/*
704==768-64;
704== (64���e����)+(10x64);
*/
/*---------------------------------------------------------
	�J�[�h��������(����)
---------------------------------------------------------*/

#define RUMIA_TIME_0060 	(60)/*[���[�~�A]*/
#define RUMIA_TIME_0416 	(416)/*[���[�~�A]*/
//#define CHRNO_TIME_34x16_544 (512+64)
//#define CHRNO_TIME_34x16_544 (640-64)
//#define CHRNO_TIME_34x16_544	(512+32)
#define CHRNO_TIME_0544 (17*32)/*(9.5[sec64]�p�[�t�F�N�g�t���[�Y)*/

/*---------------------------------------------------------
	�X�y����Փx�ʃe�[�u��
	-------------------------------------------------------
	�J�[�h�X�N���v�g�Ɉڍs�����ꍇ[initialize section: �������Z�N�V����]�ŋL�q���鐔���̃e�[�u���B
	-------------------------------------------------------
	[initialize section: �������Z�N�V����](spell_init)�̂݁A�Q�Ƃł���B
	[execute section: ���e�Z�N�V����](spell_execute)�ł́A�Q�Ƃł��Ȃ��B
---------------------------------------------------------*/


/*---------------------------------------------------------
	�J�[�h�𐶐��B
	-------------------------------------------------------
---------------------------------------------------------*/
/* static�ϐ� �𒲂ׂ��Ƃׁ̈A�ꎞ�I��local �ɂ���B */
#define local static

/* �e�̃R�[���o�b�N�Z�N�V���� */
#define TAMA_FUNC(aaa)		void aaa(OBJ/**/ *src_tama)
/* ���s�Z�N�V���� */
#define SPELL_EXEC(aaa) 	void spell_execute_##aaa(OBJ/**/ *src_boss)
#define BOSS_EXEC(aaa)		void aaa(void)
/* �������Z�N�V���� */
#define SPELL_INIT(aaa) 	void spell_init_##aaa(OBJ/**/ *src_boss)


/*(�e�Ȃ̂��{�X�Ȃ̂����{�X�Ȃ̂�������Â炭�Ȃ��Ă����̂ŁA��������B)*/
//#define src_tama src/*(���͓���)*/


/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����p�e�����R�[���o�b�N
	�e���A�N�V����#02
	-------------------------------------------------------
	�e���̋�ݏo���`�F�b�N���s��(���t���[���s���K�v�͂Ȃ�)�B
	�e������ʊO�̏ꍇ�́A�e�������B
---------------------------------------------------------*/
//global RECT_CLIP_CLASS rect_clip;
local OBJ_CALL_FUNC(hatudan_system_B_side_hansya)/* �e���˃R�[���o�b�N */
{
	{
		/* [���̕ǂŔ��˂���] �e���e���ݒ�̈��ʂ�菭��(4[pixel])��O�̈ʒu�ɗ����ꍇ�B */
		if (0 < (VR1c_bullet_clip_min_x256) + t256(4) - (src->center.x256) )
		{
			goto common_hansya;
		}
		else
		/* [�E�̕ǂŔ��˂���] �e���e���ݒ�̈��ʂ�菭��(4[pixel])��O�̈ʒu�ɗ����ꍇ�B */
		if (0 > (VR1e_bullet_clip_max_x256) - t256(4) - (src->center.x256) )
		{
			goto common_hansya;
		}
		goto done_hansya;/*(���˂��Ȃ�)*/
	common_hansya:/*(���˂���\������)*/
		/* ���ɔ��˂��Ă���ꍇ�͔��˂��Ȃ��ŁA�e�������B */
		if (0!=(src->TR00_hatudan_spec_data & TAMA_SPEC_KABE_SAYUU_HANSYA_BIT))
		{	/*(���ˏ������s��Ȃ�)*/
			src->jyumyou = JYUMYOU_NASI;/*(�e������)*/
		}
		else
	//	if (JYUMYOU_NASI != src->jyumyou)
		{	/*(���ˏ������s��)*/
			src->TR00_hatudan_spec_data |= TAMA_SPEC_KABE_SAYUU_HANSYA_BIT;
		//	src->rotationCCW1024 += (1024*3/4);/* -90�x��] */		/* �_��[��2] */
		//	src->rotationCCW1024 += (1024/4);/* 90�x��] */ 		/* �_��[��2] */
		//	src->rotationCCW1024 = (1024)-(src->rotationCCW1024);	/* ���][��1] */
			src->rotationCCW65536 = (65536)-(src->rotationCCW65536);	/* ���][��1] */
		//	mask1024(src->rotationCCW1024);
			mask65536(src->rotationCCW65536);
			src->TR01_hatudan_speed65536	= ((t256(1.0)<<8));/*(����)*/
			src->TR02_hatudan_tra65536		= (1);/*(������)*/
		}
	done_hansya:/*(���ˏ����I���)*/
		;
	}
	/* �㉺�̏ꍇ�͒e�������B */
	if (
		(0 < (VR1d_bullet_clip_min_y256) - (src->center.y256) )||
		(0 > (VR1f_bullet_clip_max_y256) - (src->center.y256) )
	)
	{
		src->jyumyou = JYUMYOU_NASI;
	}
}


/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����p�e�����R�[���o�b�N
	�e���A�N�V����#00
	-------------------------------------------------------
	�e���̋�ݏo���`�F�b�N���s��(���t���[���s���K�v�͂Ȃ�)�B
	�e������ʊO�̏ꍇ�́A�e�������B
---------------------------------------------------------*/
local OBJ_CALL_FUNC(hatudan_system_B_gamen_gai_tama_kesu)/* ��ʊO�e�����R�[���o�b�N */
{
	/* ��ʊO�̏ꍇ�͒e�������B */
	if (
	(0 < (VR1c_bullet_clip_min_x256)-(src->center.x256) ) ||
	(0 > (VR1e_bullet_clip_max_x256)-(src->center.x256) ) ||
	(0 < (VR1d_bullet_clip_min_y256)-(src->center.y256) ) ||
	(0 > (VR1f_bullet_clip_max_y256)-(src->center.y256) ) )
	{
		src->jyumyou = JYUMYOU_NASI;
	}
}

/*(���̕ӂ͔p�~���ăX�y�JCPU�̃X�N���v�g�Œ��ڏ����Ηǂ�)*/
//enum
//{
//	CLIP_RECT_TYPE_00_NORMAL =0,
//	CLIP_RECT_TYPE_01_UE_YOKO,
//	CLIP_RECT_TYPE_02_UE_ONLY,
//	CLIP_RECT_TYPE_03_UE_WIDE,
//	CLIP_RECT_TYPE_99_MAX,
//};

/*---------------------------------------------------------
	�e�͈̔͂��u�W���v�ɐݒ�
	�W���^�C�v
	-------------------------------------------------------
	set_default_bullet_clip
---------------------------------------------------------*/
#define CLIP_RECT_00_VR1c			(((GAME_X_OFFSET))<<8)						/*(�E�͕W���͈�)*/
#define CLIP_RECT_00_VR1d			(((-32))<<8)								/*(��͕W���͈�)*/
#define CLIP_RECT_00_VR1e			(((GAME_X_OFFSET) + (GAME_320_WIDTH))<<8)	/*(���͕W���͈�)*/
#define CLIP_RECT_00_VR1f			(((GAME_HEIGHT))<<8)						/*(���͕W���͈�)*/

/*---------------------------------------------------------
	�e�͈̔͂��u��Ɖ��̍L�͈́v�ɐݒ�
	��ɍL���^�C�v
	-------------------------------------------------------
	set_aya_bullet_clip
---------------------------------------------------------*/
#define CLIP_RECT_01_VR1c					(((GAME_X_OFFSET) + t256(-100))<<8) 		/*(�E�͍L�͈�)*/
#define CLIP_RECT_01_VR1d					(((-256))<<8)								/*(��͍L�͈�)*/		/* ���� */
#define CLIP_RECT_01_VR1e					(((GAME_X_OFFSET) + (GAME_320_WIDTH) + ( 100))<<8)/*(���͍L�͈�)*/
//�W���͈�#define CLIP_RECT_01_VR1f 		/*(���͕W���͈�)*/

/*---------------------------------------------------------
	�e�͈̔͂��u�ゾ���L���^�C�v�v�ɐݒ�
	�ゾ���L���^�C�v
	-------------------------------------------------------
	set_cirno_bullet_clip
---------------------------------------------------------*/
//�W���͈�#define CLIP_RECT_02_VR1c 		/*(�E�͕W���͈�)*/
#define CLIP_RECT_02_VR1d					(((-256))<<8)			/*(��͍L�͈�)*/	/*(�Ă��ƃ`���m)*/
//�W���͈�#define CLIP_RECT_02_VR1e 		/*(���͕W���͈�)*/
//�W���͈�#define CLIP_RECT_02_VR1f 		/*(���͕W���͈�)*/

/*---------------------------------------------------------
	�e�͈̔͂��u��Ɖ��̍L�͈́v�ɐݒ�
	��ɂ����ƍL���^�C�v
	-------------------------------------------------------
	set_aya_bullet_clip
---------------------------------------------------------*/
//�W���͈�#define CLIP_RECT_03_VR1c 		/*(�E�͕W���͈�)*/
#define CLIP_RECT_03_VR1d					(((-512))<<8)			/*(��͂����ƍL�͈�)*/		/* ������� */
//�W���͈�#define CLIP_RECT_03_VR1e 		/*(���͕W���͈�)*/
//�W���͈�#define CLIP_RECT_03_VR1f 		/*(���͕W���͈�)*/

/*---------------------------------------------------------
	-------------------------------------------------------

---------------------------------------------------------*/
	/* �W���^�C�v */		/* �e�͈̔͂�W���ɐݒ� */ /*(�e�̗L���͈͂�W��==������͈͂̂ݗL���ɐݒ�)*/
//local void set_default_bullet_clip(void)/* call from load_stage.c */

#define CLIP_BOSS_00_VR3c			(t256(GAME_X_OFFSET)+t256(			0)+t256(24))		/*(�E�͈̔�)*/
#define CLIP_BOSS_00_VR3d			(t256(0))												/*(��͈̔�)*/
#define CLIP_BOSS_00_VR3e			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24)) 	/*(���͈̔�)*/
//efine CLIP_BOSS_00_VR3f			(96<<8) 												/*(���͈̔�)*/

 // #01�����^�C�v�B
//local void set_default_boss_clip(void)/* call from boss_card.c */
#define CLIP_BOSS_01_VR3c			(t256(GAME_X_OFFSET)+t256(			0)+t256(24)+t256(64))		/*(�E�͈̔�)*/
#define CLIP_BOSS_01_VR3e			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24)-t256(64))	/*(���͈̔�)*/


/*---------------------------------------------------------
	�O���C���^�[�t�F�C�X�B
	-------------------------------------------------------
	�����p�́A�e�͈̔͂��u�W���v�ɐݒ�B(from load_stage.c)
---------------------------------------------------------*/

/*---------------------------------------------------------
	�J�[�h�𐶐��B
	-------------------------------------------------------
---------------------------------------------------------*/

extern void set_tukaima_start(void);
//
#include "spell_00_common.h"
//
#include "spell_00_zako.h"
#include "spell_00_sonota.h"
//
#include "spell_01_mima.h"
#include "spell_01_alice.h"
#include "spell_01_rumia.h"
#include "spell_01_meirin.h"
#include "spell_01_chrno.h"
#include "spell_01_kaguya.h"
#include "spell_01_daiyousei.h"
#include "spell_01_aya.h"
#include "spell_01_momiji.h"

//
#include "spell_01_pache.h"
#include "spell_01_sakuya.h"
#include "spell_01_remilia.h"

//
#include "spell_01_ruiz.h"


/*---------------------------------------------------------
	���ʃJ�[�h������
	-------------------------------------------------------
	�J�[�h���Ƃɗ\�ߐ������Ԃ��o�^���Ă���B
---------------------------------------------------------*/
enum
{
	TAMA_MAP_06_KOUMA	= 0,	/* �g����/�d�X��(�i�C�t�e/���e) */
	TAMA_MAP_08_EIYA,			/* �i�鏴/���_�\(�D�e/���e) */
	TAMA_MAP_10_TIREI,			/* �n��a/�ԉf��(�n�[�g�e/�K�e) */
};

#if (1==LINK_DUAL_SYSTEM)
enum//(�f�o�b�O�p���Ƃ�)
{
	RUN_00_CARD_INTERPRETER 	= 0,	/* �J�[�h�C���^�v���^�B */
	RUN_01_C_LANGUAGE,					/* C����(�p�~�\��)�B(C�����S�Ĕp�~�ł���΁A���s���x�����シ�遦1) */
};
#else
	#define RUN_00_CARD_INTERPRETER /**/
	#define RUN_01_C_LANGUAGE /**/
#endif /*(LINK_DUAL_SYSTEM)*/

typedef struct
{
	void (*spell_execute_section)(OBJ/**/ *sss);		/* [executes section: �X�y�����s�Z�N�V����]���e(�e����)���� */
	void (*spell_initialze_section)(OBJ/**/ *sss);		/* [initialize section: �X�y���������Z�N�V����]�X�y������������ */
	//
	void (*layer_callback_preset[(DANMAKU_LAYER_04_MAX)])(OBJ/**/ *src_tama);
	//
	u16 spell_limit_max_time;							/* �J�[�h�������� */						/* �J�[�h�X�N���v�g�Ɉڍs�����ꍇ�A�{��[initialize section: �������Z�N�V����]���ōs���B */
	u8 tama_map;										/* �e�摜�̃}�b�v�ԍ� */					/* �J�[�h�X�N���v�g�Ɉڍs�����ꍇ�A�{��[initialize section: �������Z�N�V����]���ōs���B */
//	u8 dummy_clip_type_haisi;
//	#if (1==LINK_DUAL_SYSTEM)
	u8 scr_ipt_run_flag;								/* (�f�o�b�O�p���Ƃ�)���s����(�J�[�h�C���^�v���^ / C����) */
//	#endif /*(LINK_DUAL_SYSTEM)*/
} SPELL_RESOURCE;

//	/*const*/ static void (*spell_execute_bbb[(SPELL_MAX/*16+1*/)])(OBJ/**/ *sss) =
	/*const*/ static SPELL_RESOURCE system_spell_resource[(SPELL_MAX/*16+1*/)] =
{
/* 02 02 */ //{ spell_execute_02_24nerai,						NULL,									{standard_angle_mover_00_callback, NULL,							NULL,							NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 02 */	/* [���] �g5�ʒ�-�{�X 24�J�[�h (��p�u�~�X�f�B���N�V�������ǂ�(1/2)�v) */
/* 03 03 */ //{ spell_execute_03_11nife,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 03 */	/* [���] �g5�ʒ�-�{�X 11�J�[�h (��p�u�~�X�f�B���N�V�������ǂ�(2/2)�v) */

	#define spell_execute_99_mitei spell_execute_08_rumia_night_bird
	#define spell_execute_40_meirin_kasou_yume_kazura spell_execute_99_mitei
/* 00 00 */ {NULL,												NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 00 */	/* �J�[�h�������Ȃ� */
			// 0x00- ���U�R / �{�X���p�J�[�h
/* 01 01 */ {spell_execute_01_sakuya_misogi_normal, 			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 01 */	/* [���] �g5�ʒ�-�{�X �u�ʏ�U��1�v����S�J�[�h */
/* 02 02 */ {spell_execute_99_mitei,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 02 */	/* [�G��] (���g�p) */
/* 03 03 */ {spell_execute_03_lumia02_douchuu,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	RUMIA_TIME_0060, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 03 */	/* [���[�~�A] (����) */
/* 04 04 */ {spell_execute_04_pink_hearts,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 04 */	/* [���] �g5�ʃ{�X �u�ʏ�U��1(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) SPELL_TIME_0128(r32) */
/* 05 05 */ {spell_execute_05_32way_dual,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 05 */	/* [���] �g5�ʃ{�X �u�ʏ�U��1/2(2/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
/* 06 06 */ {spell_execute_06_luna_clock_32way, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 06 */	/* [���] �g5�ʃ{�X ���ہu���i�N���b�N(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
/* 07 07 */ {spell_execute_07_80way_dual_five,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 07 */	/* [���] �g5�ʃ{�X �u�ʏ�U��3(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
			// 0x08- ���U�R / �{�X���p�J�[�h
/* 08 08 */ {spell_execute_08_rumia_night_bird, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	RUMIA_TIME_0416, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 08 */	/* [���[�~�A] �g1�ʃ{�X �镄�u�i�C�g�o�[�h�v�ɂ�����Ƃ��������J�[�h(�\��) */
/* 09 09 */ {spell_execute_09_test_inuno_fuguri,				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 09 */	/* [�G��] ����@�J�[�h(�Ƃ肠�����J�[�h�V�X�e���쐬�̎����ō���Ă݂��z) */
/* 10 0a */ {spell_execute_1a_1b_dai_yousei_midori_aka, 		spell_init_1a_dai_yousei_midori,		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1a */	/* [��d��] �Ί��� */
/* 11 0b */ {spell_execute_1a_1b_dai_yousei_midori_aka, 		spell_init_1b_dai_yousei_aka,			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1b */	/* [��d��] �Ԋ��� */
/* 12 0c */ {spell_execute_14_sakuya_jack_oodama32, 			spell_init_14_sakuya_jack_oodama32, 	{standard_angle_mover_00_callback, sakuya_danmaku_01_callback,		sakuya_danmaku_02_callback, 	NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 14 */	/* [���] ���H�u�W���b�N�E�U�E���h�r���v�ɂȂ邩������Ȃ��e�X�g */
/* 40 28 */ {spell_execute_0d_dai_yousei_9_shot,				NULL,									{standard_angle_mover_00_callback, dai_yousei_danmaku_01_callback,	NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [��d��] 9shot */
/* 14 0e */ {spell_execute_1f_remilia_kougeki2, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1f */	/* [���~���A] �ʏ�U��2 ���ۂ����� */
/* 15 0f */ {spell_execute_11_tengu_shot,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 11 */	/* [�V��l] �������̗d��1(�V��l?)�����J�[�h */
			// 0x10- ���U�R / �{�X���p�J�[�h
/* 16 10 */ {spell_execute_10_cirno_misogi, 					spell_init_10_cirno_misogi, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 10 */	/* [�`���m] �g2�ʃ{�X �`���m�S�J�[�h */
/* 17 11 */ {spell_execute_13_perfect_freeze,					NULL,									{standard_angle_mover_00_callback, cirno_danmaku_01_callback,		NULL, NULL},
																																								CHRNO_TIME_0544, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 13 */	/* [�`���m] �g2�ʃ{�X �p�[�t�F�N�g�t���[�Y */
/* 18 12 */ {spell_execute_16_diamond_blizzard, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 16 */	/* [�`���m] �g2�ʃ{�X �ᕄ�u�_�C�A�����h�u���U�[�h�v */
/* 19 13 */ {spell_execute_25_alice_suwako, 					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 25 */	/* [�A���X] �A���X	�z�K�q���ۂ�(?)�J�[�h */
/* 20 14 */ {spell_execute_17_alice_nejiri10sec,/*(r39)*/		spell_init_17_alice_nejiri10sec,		{standard_angle_mover_00_callback, alice_aaa_danmaku_01_callback,	NULL, NULL},
																																								SPELL_TIME_0192, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 17 */	/* [�A���X] �ʏ�U��(���ǂ�) �˂���e10�b SPELL_TIME_0640 */
/* 21 15 */ {spell_execute_0e_aka_2nd,							spell_init_0e_aka_2nd,					{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_1024, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0e */	/* [�A���X] ��EX�ʃ{�X �Ԃ̖��@2�i�K�ڂ��ǂ� */
/* 22 16 */ {spell_execute_0b_alice_zako_doll,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0b */	/* [�A���X] SPELL_TIME_0128 �d3�ʃ{�X �l�`�J�[�h(���ǂ�)(256>240=4x60) */
/* 23 17 */ {spell_execute_1e_alice_tama_doll,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1e */	/* [�A���X] �d3�ʃ{�X �l�`�J�[�h(���ǂ�)(256>240=4x60) �����u�����̕������l�`�v */
			// 0x18- ���U�R / �{�X���p�J�[�h
/* 24 18 */ {spell_execute_0c_hana_test,						NULL,									{standard_angle_mover_00_callback, mima_danmaku_01_callback,		NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0c */	/* [����] �ԂĂ��ƃJ�[�h */
/* 64 40 */ //{spell_execute_20_sonota_debug_cw_ao, 			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 40 */	/* [���̑�] �f�o�b�O�J�[�hCW�� */
/* 65 41 */ //{spell_execute_21_sonota_debug_ccw_aka,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 41 */	/* [���̑�] �f�o�b�O�J�[�hCCW�� */
/* 64 40 */ {spell_execute_19_meirin_5_houkou,					spell_init_19_meirin_5_houkou,			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 40 */	/* [�g����] �����u�ؑz�����v */
/* 65 41 */ {spell_execute_40_meirin_kasou_yume_kazura, 		NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 41 */	/* [�g����] �����u�ʓ��̕���v */
/* 27 1b */ {spell_execute_1b_cirno_icecle_fall,				spell_init_1b_cirno_icecle_fall,		{standard_angle_mover_00_callback, cirno_icecle_fall_01_callback,	NULL, NULL},
																																								SPELL_TIME_0352, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [�`���m] �X���u�A�C�V�N���t�H�[���v */
/* 68 44 */ {spell_execute_44_ruiz3,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 44 */	/* [���C�Y] ���E���J�[�h */
/* 29 1d */ {spell_execute_1d_amefuri_test, 					spell_init_1d_amefuri_test, 			{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/							NULL,							NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [(���A��)] �J�Ă��� */
/* 30 1e */ {spell_execute_1e_momiji_no_nonoji, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [��] �̂̂��J�[�h */
/* 31 1f */ {spell_execute_1f_koakuma,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [�p�`�F] �T�C�����g�Z���i �� �Ă��Ɨp */
			// 0x20- �{�X��p�J�[�h
/* 32 20 */ {spell_execute_15_aya_misogi1,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 15 */	/* [��] �̒ʏ�e���ۂ��J�[�h�������Ă݂�e�X�g1 */
/* 33 21 */ {spell_execute_23_aya_misogi2,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 23 */	/* [��]�̒ʏ�e���ۂ��J�[�h�������Ă݂�e�X�g2 */
/* 34 22 */ {spell_execute_22_aya_yatimata, 					spell_init_22_aya_yatimata, 			{standard_angle_mover_00_callback, aya_danmaku_01_callback, 		NULL,							NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 22 */	/* [��] �򕄁u�V�̔��ˁv */
/* 35 23 */ {spell_execute_12_meirin_magaru_kunai,				spell_init_12_meirin_magaru_kunai,		{standard_angle_mover_00_callback, common_01_amefuri_callback,		meirin_02_aka_ao_kunai_callback, meirin_03_aka_ao_kunai_time256_callback},/*(�ԐN�i�C�p2)*/
																																																					SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 12 */	/* [����] �g3�ʒ��{�X �u�ʏ�U���v�̋Ȃ���N�i�C�B */
/* 36 24 */ {spell_execute_0f_aya_doll, 						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0f */	/* [��] �l�`�J�[�h(�Ă��ƃJ�[�h�u�댯�Ȏ�v) */
/* 37 25 */ {spell_execute_0a_houka_kenran, 					spell_init_0a_houka_kenran, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0a */	/* [�g����] �g3�ʃ{�X �ؕ��u�F�؈�ࣁv�ɂ�����Ƃ��������J�[�h(�\��) */
/* 38 26 */ {spell_execute_26_aya_saifu,						spell_init_26_aya_saifu,				{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [��] �Ǖ� */
/* 39 27 */ {spell_execute_27_hosigata_test,					spell_init_27_hosigata_test,			{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/							move_bullet_sakuya_hosi_gata_callback,/*(���^�p�B)*/	/*(���g�p)*/NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 27 */	/* [���̑�] ���^�e�X�g */
			// 0x28- �{�X��p�J�[�h
/* 13 0d */ {spell_execute_28_sakuya_miss_direction,			spell_init_28_sakuya_miss_direction,	{standard_angle_mover_00_callback, danmaku_01_standard_angle_sayuu_hansya_mover,	NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1c */	/* [���] ��p�u�~�X�f�B���N�V�����v */
/* 41 29 */ {spell_execute_29_rumia_demarcation,				spell_init_29_rumia_demarcation,		{standard_angle_mover_00_callback, rumia_danmaku_01_callback,		rumia_danmaku_02_callback,	NULL},	SPELL_TIME_0512, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 31 */	/* [���[�~�A] �g1�ʃ{�X �ŕ��u�f�B�}�[�P�C�V�����v�ɂ�����Ƃ��������J�[�h(�\��) dimmercation / demarcation ���E */
	//
	#if 0
	//[�v���Z�X�o�^] �X�N���v�g�������ꍇ�ɕK�v�ȏ����B
	regist_process(0, spell_execute_29_rumia_demarcation);	// [execute section: ���e�Z�N�V����]�v���O�������s�J�n�Ԓn�o�^
	regist_process(1, rumia_danmaku_01_callback);			// [callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]�v���O�������s�J�n�Ԓn�o�^
	regist_process(2, rumia_danmaku_02_callback);			// [callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]�v���O�������s�J�n�Ԓn�o�^
	#endif


/* 42 2a */ {spell_execute_2a_sakuya_baramaki1, 				spell_init_2a_sakuya_baramaki1, 		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [���] �g5�ʒ�-�{�X �΂�T��1 �J�[�h () */
/* 43 2b */ {spell_execute_2b_sakuya_baramaki2, 				spell_init_2b_sakuya_baramaki2, 		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [���] �g5�ʒ�-�{�X �΂�T��2 �J�[�h () */
/* 44 2c */ {spell_execute_2c_sakuya_blue_red_knife,			NULL,									{standard_angle_mover_00_callback, danmaku_01_standard_angle_sayuu_hansya_mover,/*(�ʏ�e�p)*/ /*(��ʊO�Ȃ甽�ˌ���)*/ /*(���g�p)*/NULL, NULL},
																																								SPELL_TIME_0512, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [���] �g5�ʒ�-�{�X �u�ʏ�U��3�v�ԃi�C�t */
/* 45 2d */ {spell_execute_2d_sakuya_misogi_lunatic,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 01 */	/* [���] �g5�ʒ�-�{�X �u�ʏ�U��1�v����S�J�[�h(lunatic only) */
// ==================================== [�X�y�J���E] ==================================== //
/* 46 2e */ {spell_execute_2e_pache_agni_shine_1,				spell_init_2e_pache_agni_shine_1,		{standard_angle_mover_00_callback,	agnishine_danmaku_01_callback,/*(�A�O�j�V���C���p)*/ /*(���g�p)*/NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 2e */	/* [�p�`�F] "�@�@�@�@�Ε��u�A�O�j�V���C���v" No.15 */	// (�΂������ς�������) (�P��)�A�O�j(�C���h�_�b�̉΂̐_)
/* 47 2f */ {spell_execute_2f_pache_princess_undine,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 2f */	/* [�p�`�F] "�@�����u�v�����Z�X�E���f�B�l�v" No.16 */	// (���������ς�������) �u�d���̏�(����:�B���p�t�p���P���X�X)�v�ɓo�ꂷ�鐅�̐��B
			// 0x30- �{�X��p�J�[�h
/* 48 30 */ {spell_execute_30_pache_sylphy_horn_1,				spell_init_30_pache_sylphy_horn_000,	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(�V���t�B�z�����p)*/ /*(���g�p)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */ /* [�p�`�F] "�@�@�@�@�ؕ��u�V���t�B�z�����v" No.17 */	// (�؂������ς�������) (�����i�鐸���)�p�J
/* 49 31 */ {spell_execute_31_pache_rage_tririton_1,			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(�g�t���ےe�B�����e�B? ���B)*/ /*(���g�p)*/NULL, NULL},				SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 31 */ /* [�p�`�F] "�@�@�y���u���C�W�B�g�����g���v" No.18 */	// (�y�������ς�������) (�{��)�g�����g��(�X�g�[���w���W)
/* 50 32 */ {spell_execute_32_pache_metal_fatigue,				NULL,									{standard_angle_mover_00_callback, pache_mt1_danmaku_01_callback,/*(���F ��ʒe�B)*/	/*(���g�p)*/NULL, NULL},							SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 32 */ /* [�p�`�F] "�@�@�����u���^���t�@�e�B�[�O�v" No.19 */	// (��(����)�������ς�������) ������J
/* 51 33 */ {spell_execute_33_pache_agni_shine_2,				spell_init_33_pache_agni_shine_2,		{standard_angle_mover_00_callback, agnishine_danmaku_01_callback,/*(�A�O�j�V���C���p)*/ /*(���g�p)*/NULL, NULL},							SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 33 */ /* [�p�`�F] "�@�@�Ε��u�A�O�j�V���C���㋉�v" No.20 */	// (�΂������ς�������) (�P��)�A�O�j(�C���h�_�b�̉΂̐_)
/* 52 34 */ {spell_execute_34_pache_sylphy_horn_2,		/*���p*/spell_init_30_pache_sylphy_horn_000,  	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(�V���t�B�z�����p)*/ /*(���g�p)*/NULL, NULL},																					SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 34 */ /* [�p�`�F] "�@�@�ؕ��u�V���t�B�z�����㋉�v" No.21 */	// (�؂������ς�������) (�����i�鐸���)�p�J
/* 53 35 */ {spell_execute_35_pache_rage_tririton_2,			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(�g�t���ےe�B�����e�B? ���B)*/ /*(���g�p)*/NULL, NULL},				SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 35 */ /* [�p�`�F] "�y���u���C�W�B�g�����g���㋉�v" No.22 */	// (�y�������ς�������) (�{��)�g�����g��(�X�g�[���w���W)
/* 54 36 */ {spell_execute_36_pache_agni_radiance,/* _agni_shine_3 */ NULL, 							{standard_angle_mover_00_callback, agnishine_danmaku_01_callback/*(�A�O�j�V���C���p)*/, /*(���g�p)*/NULL, NULL},																						SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 36 */ /* [�p�`�F] "�@�Ε��u�A�O�j���C�f�B�A���X�v" No.23 */	// (�΂������ς������ς�������) �A�O�j(�C���h�_�b�̉΂̐_)
/* 55 37 */ {spell_execute_37_pache_bury_in_lake,				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 37 */ /* [�p�`�F] "�@�@�@�����u�x���[�C�����C�N�v" No.24 */	// (���������ς������ς�������)  �΂ɖ��߂�(����)
			// 0x38- �{�X��p�J�[�h
/* 56 38 */ {spell_execute_38_pache_green_storm,/*sh_3 ���p*/	spell_init_30_pache_sylphy_horn_000, 	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(�V���t�B�z����)*/ /*(���g�p)*/NULL, NULL},																				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 38 */ /* [�p�`�F] "�@�@�@�ؕ��u�O���[���X�g�[���v" No.25 */	// (�؂������ς������ς�������) �΂̗�
/* 57 39 */ {spell_execute_39_pache_tririton_shake, 			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(�g�t���ےe�B�����e�B? ���B)*/ /*(���g�p)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 39 */ /* [�p�`�F] "�@�@�y���u�g�����g���V�F�C�N�v" No.26 */	// (�y�������ς������ς�������) (�h���)�g�����g��(�X�g�[���w���W)
/* 58 3a */ {spell_execute_3a_pache_silver_dragon,				NULL,									{standard_angle_mover_00_callback, pache_mt2_danmaku_01_callback,/*(���e�B)*/ /*(���g�p)*/NULL, NULL},										SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3a */ /* [�p�`�F] "�@�@�@�����u�V���o�[�h���S���v" No.27 */	// (��(����)�������ς������ς�������) �u���Ƌ�(����:���R)�v
/* 59 3b */ {spell_execute_3b_pache_lava_cromlech,				NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(�g�t���ےe�B�����e�B? ���B)*/ /*(���g�p)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3b */ /* [�p�`�F] "�΁��y���u���[���@�N�������N�v" No.28 */	// (�΁{�y���n��) ����(�X�g�[���w���W)
/* 60 3c */ {spell_execute_3c_pache_forest_blaze,				spell_init_30_pache_sylphy_horn_000,	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(�V���t�B�z����)*/ /*(���g�p)*/NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3c */ /* [�p�`�F] "�؁��Ε��u�t�H���X�g�u���C�Y�v" No.29 */	// (�؁{�΁�)�X�щ΍�
/* 61 3d */ {spell_execute_3d_pache_water_elf,					spell_init_3d_pache_water_elf,			{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0100, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3d */ /* [�p�`�F] "�@�����ؕ��u�E�H�[�^�[�G���t�v" No.30 */	// (���{�؁�)���n��(���d��)
/* 62 3e */ {spell_execute_3e_pache_mercury_poison, 			spell_init_3e_pache_mercury_poison,		{standard_angle_mover_00_callback, pache_mp1_danmaku_01_callback,/*(�g�t���ےe�B�����e�B�����v���/���v���B)*/ /*(���g�p)*/NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3e */ /* [�p�`�F] "���������u�}�[�L�����|�C�Y���v" No.31 */	// (��(����)�{����)���⒆��
/* 63 3f */ {spell_execute_3f_pache_emerald_megalith,			spell_init_3f_pache_emerald_megalith,	{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3f */ /* [�p�`�F] "�y�������u�G�������h���K���X�v" No.32 */	// (�y�{��(����)��)�G�������h�̋���
// ==================================== [�X�y�J���E] ==================================== //
			// 0x40
/* 66 42 */ /*40*/	{spell_execute_40_pache_laser1, 			spell_init_40_pache_laser1, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 42 */	/* [�p�`�F] �ʏ�U��(���ǂ�) �̃��[�U�[���ǂ� */
/* 67 43 */ /*41*/	{spell_execute_41_pache_laser2, 			spell_init_41_pache_laser2, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 43 */	/* [�p�`�F] �ʏ�U��(���ǂ�) �̃��[�U�[���ǂ� */
/* 4e 4e */ /*4e*/	{spell_execute_42_remilia_vlad_tepes,		spell_init_42_remilia_vlad_tepes,		{standard_angle_mover_00_callback, brp_tamaoki_danmaku_01_callback,/*(��u���p)*/	remilia_tahane_danmaku_02_callback,/*(�쒵�˗p)*/ /*(���g�p)*/NULL},		SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [���/���~���A] �g6�ʃ{�X ���f�u�u���h�E�c�F�y�V���̎􂢁v */
/* 4f 4f */ /*4f*/	{spell_execute_43_remilia_red_magic,		spell_init_43_remilia_red_magic,		{standard_angle_mover_00_callback, red_magic_tamaoki_danmaku_01_callback,/*(��u���p)*/	remilia_tahane_danmaku_02_callback,/*(�쒵�˗p)*/ /*(���g�p)*/NULL},	SPELL_TIME_0192, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4f */	/* [���/���~���A] �g6�ʃ{�X �u���b�h�}�W�b�N�v */
/* 4d 4d */ /*4d*/	{spell_execute_44_remilia_rasen_knife,		NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4d */	/* [���/���~���A] �g6�ʃ{�X �ʏ�U��  */
/* 71 47 */ /*47*/	{spell_execute_45_sakuya_festival_knife,	spell_init_45_sakuya_festival_knife,	{standard_angle_mover_00_callback, sakuya_ryoute_knife_danmaku_01_callback,/*(���E�e�i�C�t�B)*/	sakuya_hajikeru_knife_danmaku_02_callback,/*(�e����i�C�t�B)*/	sakuya_kurukuru_knife_danmaku_03_callback},/*(���邭��i�C�t�B)*/
																																																SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 47 */	/* [���] ���z�u�t�F�X�e�B�o���i�C�t�v(?) �ނ���ϊ� */
/* 25 19 */ /*42*/	{spell_execute_46_mima_sekkin,				NULL, 			 						{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/ NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0d */	/* [����] �ڋ߃J�[�h */
/* 26 1a */ /*43*/	{spell_execute_47_mima_toge,				spell_init_47_mima_toge, 				{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/ NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 24 */	/* [����] �g�Q�J�[�h */
					// 0x48
/* 49 49 */ /*49*/	{spell_execute_48_kaguya000,				spell_init_kaguya000, /*(����)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 18 */	/* [�P��] �Ƃ肠���������ɕϊ�000 */
/* 69 45 */ /*44*/	{spell_execute_48_kaguya000,				spell_init_kaguya111, /*(����)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 18 */	/* [�P��] �Ƃ肠���������ɕϊ�111 */
/* 70 46 */ /*45*/	{spell_execute_4a_kaguya222,				spell_init_kaguya222, /*(����)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 19 */	/* [�P��] �Ƃ肠���������ɕϊ�222 */
/* 28 1c */ /*46*/	{spell_execute_4b_kaguya333_tamanoe,		spell_init_kaguya333, /*(����)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/								NULL,									NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [�P��] �H���̋ʂ̎}���ǂ� */
/* 4c 4c */ /*4c*/	{spell_execute_4b_kaguya333_tamanoe,		spell_init_kaguya444, /*(����)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(�J�p)*/								NULL,									NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [�P��] �H���̋ʂ̎}���ǂ� */
/* 4a 4a */ /*4a*/	{spell_execute_4d_rumia_3nerai, 			NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4a */	/* [���[�~�A] */
/* 4b 4b */ /*4b*/	{spell_execute_99_mitei,					NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4b */	/* [] */
/* 48 48 */ /*48*/	{spell_execute_48_aya_taifu,				NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 48 */	/* [r34]r34�ȑO�̌݊��@�\�B(r35-)�V�X�e���ŕK���K�v�B */
//
/* 50 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */
/* 51 */ {spell_execute_51_kaguya_tujyou_kougeki_01,			spell_init_51_kaguya_tujyou_kougeki_01, {standard_angle_mover_00_callback, kaguya_tujyou_kougeki_01_wait_callback,/*(��u���p)*/	NULL,				NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �ʏ�U��1
/* 52 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// ���u������̋ʁ@-�ܐF�̒e��-�v
/* 53 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �_��u�u�����A���g�h���S���o���b�^�v
/* 54 */ {spell_execute_54_kaguya_tujyou_kougeki_02,			spell_init_54_kaguya_tujyou_kougeki_02, {standard_angle_mover_00_callback, kaguya_tujyou_kougeki_02_wait_callback,/*(��u���p)*/	NULL,				NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �ʏ�U��2,
/* 55 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// ���u���̌�΂̔��@-�ӂ��ʈӎu-�v,
/* 56 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �_��u�u�f�B�X�g�_�C�A�����h�v
/* 57 */ {spell_execute_57_kaguya_tujyou_kougeki_03,			spell_init_57_kaguya_tujyou_kougeki_03, {standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �ʏ�U��3,
//
/* 58 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// ���u�Αl�̔�߁@-�ł�ʐS-�v,
/* 59 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �_��u�T���}���_�[�V�[���h�v
/* 5a */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �ʏ�U��4,
/* 5b */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// ���u���̎q���L�@-�i����-�v
/* 5c */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �_��u���C�t�X�v�����O�C���t�B�j�e�B�v
/* 5d */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// ���u�H���̋ʂ̎}�@-���F�̒e��-�v
/* 5e */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �_��u�H���̋ʂ̎}�@-���F�̋�-�v
/* 5f */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// �u�i��Ԃ��@�]�閾���]�v�iN�j
};
#if 0
/*50*/	SPELL_50_,
/*51*/	SPELL_51_kaguya_tujyou_kougeki_01,			// �ʏ�U��1
/*52*/	SPELL_52_kaguya_tatu_no_kubi_no_tama,		// ���u������̋ʁ@-�ܐF�̒e��-�v
/*53*/	SPELL_53_kaguya_brilliant_dragon_bullet,	// �_��u�u�����A���g�h���S���o���b�^�v
/*54*/	SPELL_54_kaguya_tujyou_kougeki_02,			// �ʏ�U��2,
/*55*/	SPELL_55_kaguya_hotoke_no_oisi_no_hati, 	// ���u���̌�΂̔��@-�ӂ��ʈӎu-�v,
/*56*/	SPELL_56_kaguya_bdist_diamond,				// �_��u�u�f�B�X�g�_�C�A�����h�v
/*57*/	SPELL_57_kaguya_tujyou_kougeki_03,			// �ʏ�U��3,
		//
/*58*/	SPELL_58_kaguya_hi_nezumi_no_kawa_goromo,	// ���u�Αl�̔�߁@-�ł�ʐS-�v,
/*59*/	SPELL_59_kaguya_salamnder_shiled,			// �_��u�T���}���_�[�V�[���h�v
/*5a*/	SPELL_5a_kaguya_tujyou_kougeki_04,			// �ʏ�U��4,
/*5b*/	SPELL_5b_kaguya_tubame_no_koyasugai,		// ���u���̎q���L�@-�i����-�v
/*5c*/	SPELL_5c_kaguya_life_spring_infinity,		// �_��u���C�t�X�v�����O�C���t�B�j�e�B�v
/*5d*/	SPELL_5d_kaguya_hourai_no_tama_no_eda01,	// ���u�H���̋ʂ̎}�@-���F�̒e��-�v
/*5e*/	SPELL_5e_kaguya_hourai_no_tama_no_eda02,	// �_��u�H���̋ʂ̎}�@-���F�̋�-�v
/*5f*/	SPELL_5f_kaguya_eiya_gaesi_yoake,			// �u�i��Ԃ��@�]�閾���]�v�iN�j
#endif

/*---------------------------------------------------------
	�����U�R/�{�X/�������{�X�A�X�y��CPU������	[���ʕ���]�B
---------------------------------------------------------*/

extern void spell_cpu_common_reset(void)
{
	#if (1==USE_BOSS_JIKANGIRE)/*(�g�p�\�肠��B������)*/
	cg_state_flag &= (~JIKI_FLAG_16_0x8000_BOSS_JIKAN_GIRE);/*(���Ԑ؂�t���Ooff)*/
	#endif
	/* �J�[�h���W�X�^�S������ */
	static const u32 codebase_init[18] =
	{
		// (01)
		MCODE(OP0x0f_CLEAR_ZERO_PAGE, NAX, NAX, NAX),
		//---- set_default_bullet_clip();	/* �e�͈̔͂�W���ɐݒ� */	//	/*(��������/�U�R/�������{�X�p������)*/
	// (CLIP_RECT_TYPE_00_NORMAL);
		// (02)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// �E�͈̔͂�ݒ肷��B
		CLIP_RECT_00_VR1c,// �W���^�C�v
		// (03)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// ��͈̔͂�ݒ肷��B
		CLIP_RECT_00_VR1d,// �W���^�C�v
		// (04)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// ���͈̔͂�ݒ肷��B
		CLIP_RECT_00_VR1e,// �W���^�C�v
		// (05)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1f_bullet_clip_max_y256, NAX),// ���͈̔͂�ݒ肷��B
		CLIP_RECT_00_VR1f,// �W���^�C�v
	//----
	//	VR3f_boss_clip_max_y256 = ((boss_clip_y_pixel[((cg_VR20_game_difficulty)&3)])<<8);/*t256()*/
	//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((64), (80), (96), (96));/*[boss_clip_y_pixel]*/
	//	CPU_CA LL(nan_ido);
	/* boss_rect_init */
		//---- set_default_boss_clip();/*(�{�X�͈̔͂����Z�b�g����)*/
		/*(�{�X�{�̂̈ړ��͈͂𐧌�����B)*/
		// (06) VR3c_boss_clip_min_x256 = t256(GAME_X_OFFSET)+t256( 			0)+t256(24);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3c_boss_clip_min_x256, NAX),// �E�͈̔͂�ݒ肷��B
		CLIP_BOSS_00_VR3c,
		// (07) VR3d_boss_clip_min_y256 = t256(0);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3d_boss_clip_min_y256, NAX),// ��͈̔͂�ݒ肷��B
		CLIP_BOSS_00_VR3d,
		// (08) VR3e_boss_clip_max_x256 = t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3e_boss_clip_max_x256, NAX),// ���͈̔͂�ݒ肷��B
		CLIP_BOSS_00_VR3e,
	//----
		// (09) //	VR04 = ([��Փx�ʒ萔]); // ���͈̔͂�ݒ肷��B
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R3f_boss_clip_max_y256, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((64), (80), (96)/*(hard)[r39]*/, (96)),/*[boss_clip_y_pixel]*/
		// (10) VR04_NAN_IDO_DECODE 	<<= (8);/*�ϊ� t256()[convert by pixel to t256()]*/
		MCODE(OP0x1f_ASLM_PD, (8), R3f_boss_clip_max_y256, R3f_boss_clip_max_y256),/*(�V���[�g�������A�h���b�V���O)*/
		//VR3f_boss_clip_max_y256	= (VR04_NAN_IDO_DECODE);/*[decoded difficulty by boss clip at y pixel]*/
		// (11)
	//	NAX
	};
	cpu_exec((u32*)&codebase_init, (10));
	add_laser_off_void();/*(���[�U�[off)*/
	/* �u�������Z�N�V�����v���O��clip������������ */ /*(�e�̗L���͈͂�W��==������͈͂̂ݗL���ɐݒ�)*/
	// �� [�{�X�e���̏ꍇ]
	// ���̒����[initialize section: �������Z�N�V����]�����s����̂ŁA
	// ���[�U�[on �� �e�̗L���͈͂�����Ȃ��̂́A
	// ������[initialize section: �������Z�N�V����]���ł̂ݎ��s���܂��B
	// �� [�����A���{�X�̏ꍇ]
	// ���{�X�̏ꍇ�̓{�X�̏ꍇ�ƈ����������Ȃ̂ŁA�����[initialize section: �������Z�N�V����]�Ŏ��s���܂��B
	// �� [�����̏ꍇ]
	// �����̏ꍇ����(���[�U�[�Ȃ��A�e�̗L���͈͂�W��==������͈͂̂ݗL��)���f�t�H���g�ł��B
	// �ς������ꍇ�A���Ȃ��Ƃ� spell_cpu_common_reset(); �ȍ~�Ɏ��s���Ă��������B
	//
}

/*---------------------------------------------------------
	�����̑O�ɏ���������K�v�����镔���B
---------------------------------------------------------*/
static void set_basic_cb(void)
{
	int jj;
	for (jj=0; jj<DANMAKU_LAYER_04_MAX; jj++)/*(�B)*/
	{
		card.layer_callback[jj] = system_spell_resource[(card.spell_used_number/*-1*/)].layer_callback_preset[jj];/*(r36-���������֎~)*/	/*(�ʏ�e�p)*/
	}
}


extern void spell_cpu_danmaku_callback_douchuu_init(void)/*(�����U�R�e�p�ɒe���R�[���o�b�N������������)*/
{
	#if (1)/*[�����U�R�p]*/
	set_basic_cb();/* �e���R�[���o�b�N�V�X�e���̏����� */
	card.layer_callback[1] = danmaku_01_standard_angle_mover_douchu_start; /*(�����e�p�J�n)*/
	#endif
}


/*---------------------------------------------------------
	�J�[�h�̏������B�J�[�h���ς��Ɩ���s���K�v������B
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(card_maikai_init)
{
	spell_cpu_common_reset();/*(�����U�R/�{�X/�������{�X[���ʕ���])*/
	#if (1)/*[�{�X/�������{�X�p]*/
	set_basic_cb();/* �e���R�[���o�b�N�V�X�e���̏����� */
	#endif
	#if (1)/* �J�[�h�X�N���v�g�Ɉڍs�����ꍇ��[initialize section: �������Z�N�V����]�B */
	#if (1==LINK_DUAL_SYSTEM)
	/*(���s����(�J�[�h�C���^�v���^ / C����) �ʂŁA[execute section: ���e�Z�N�V����]��o�^)*/
	if (system_spell_resource[(card.spell_used_number/*-1*/)].scr_ipt_run_flag) /*(���s����(  C����) �̏ꍇ�B)*/
	#endif /*(LINK_DUAL_SYSTEM)*/
	{
		/* �J�[�h�������Z�N�V���������s����B */
		if (NULL!=(system_spell_resource[(card.spell_used_number/*-1*/)].spell_initialze_section))
		{
			(system_spell_resource[(card.spell_used_number/*-1*/)].spell_initialze_section)(src);
		}
		/* �J�[�h���s�Z�N�V������o�^����B */
		card.boss_spell_callback = system_spell_resource[(card.spell_used_number/*-1*/)].spell_execute_section;
	}
	#if (1==LINK_DUAL_SYSTEM)
	else	/*(���s����(�J�[�h�C���^�v���^)�̏ꍇ�B)*/
	{
		/* �J�[�h�������Z�N�V���������s����B */
		ci_run_init_section(src);
		/* �J�[�h���s�Z�N�V������o�^����B */
		card.boss_spell_callback = ci_spell_cpu;
	}
	#endif /*(LINK_DUAL_SYSTEM)*/
	/* �J�[�h���Ԃɗ\�ߓo�^���ꂽ�������Ԃ�ݒ肷��B */
	/* �J�[�h�̐������Ԃ�ݒ�(�\�߃J�[�h���Ƃɐݒ肳��Ă���W�����Ԃɐݒ�) */
	/* �J�[�h�̎��Ԑ؂��ݒ� */
	VR10_BOSS_SPELL_TIMER = system_spell_resource[(card.spell_used_number/*-1*/)].spell_limit_max_time;
	#endif
}


/*---------------------------------------------------------
	�X�y��CPU�����s���A�J�[�h���P�t���[����������B
	-------------------------------------------------------
	�J�[�h��������Ǝ��Ԍo�߂��A�J�[�h�������Ԃ������Ō���B
	�J�[�h�������Ԃ������Ȃ����ꍇ�́A�J�[�h�^�C�v������(SPELL_00)�ɂȂ�B
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(card_generate)/* �J�[�h���� */
{
	if (SPELL_00 != card.spell_used_number) 	/* �X�y�������͕K�v�H */
	{
		VR10_BOSS_SPELL_TIMER--;				/* ���Ԍo�߂��� */	/*fps_factor*/
		if (0 < VR10_BOSS_SPELL_TIMER)		/* ���Ԑ؂�H */
		{
			set_REG_DEST_BOSS_XY();/* �e��x256 y256 �{�X�̒��S���甭�e�B */
			#if (1)/* �J�[�h���s */
		//	(system_spell_resource[(card.spell_used_number/*-1*/)].spell_execute_section)(src);/*-r40*/
			(card.boss_spell_callback)(src);/*r41-*/	/*(���s����(�J�[�h�C���^�v���^ / C����) �ʂŁA���e����)*/
			#endif
		}
		else
		{
			card.spell_used_number = SPELL_00;		/* �J�[�h�����I�� */
		}
	}
}
