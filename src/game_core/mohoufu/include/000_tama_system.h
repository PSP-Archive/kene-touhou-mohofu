
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃t�@�C���͒��ڃC���N���[�h���܂���B
	"game_main.h" ����̂݊ԐړI�ɃC���N���[�h���܂��B
---------------------------------------------------------*/

#ifndef _CARD_CPU_H_
#define _CARD_CPU_H_
/*---------------------------------------------------------
	�J�[�hCPU
---------------------------------------------------------*/

/*---------------------------------------------------------
	�J�[�hCPU�p�̃��W�X�^(���[�J���������[)
	-------------------------------------------------------
	�����I�Ɂu�J�[�h�v�́A�S�āu�J�[�h�X�N���v�g�v�ŏ�������p�Ɉڍs����(�\��)�B
	-------------------------------------------------------
	���́u�J�[�h�X�N���v�g�v�́A�u�J�[�hCPU
	(�J�[�h�X�N���v�g�����������j�b�g)
	(SPEll-CArd script, Central Prcessing Unit.)�v
	���A���ۂ̏������s���B
	-------------------------------------------------------
	���̃J�[�hCPU�ɂ́A���W�X�^(Resister)�ƌĂ΂��J�[�hCPU�̓���������������B
	�J�[�hCPU�����s������ꍇ(�܂�X�y���J�[�h�����ꍇ)�ɁA�J�[�hCPU�̓��W�X�^�ȊO�A�N�Z�X�ł��Ȃ��B
	-------------------------------------------------------
	�d�l:
		�[���y�[�W���W�X�^(reg00-reg1f)�́A�J�[�h�X�N���v�g�J�n���ɕK��(0)�ŏ��������B
		���̌�A�J�[�h�X�N���v�g�p��[initialize section: �������Z�N�V����]�Ŏw�����ꂽ��������������x�����s����B
	-------------------------------------------------------
	��Փx���W�X�^(r41-)�d�l�ύX:
		��Փx���W�X�^�̓�Փx�͂��ł��g�p�ł���B
		�l��j�󂵂Ă̓_���B
	-------------------------------------------------------
	(r41-)�{�X�̃R���g���[���͏����I�ɁA�X�N���v�g����s���K�v������B
	�J�[�hCPU�̓��W�X�^�ȊO�A�N�Z�X�ł��Ȃ��̂ŁA
	�{�X�̊֌W�̒l�́A���ׂă��W�X�^�ֈړ������B
	���l�ɁA�v���C���[�̒l���A�X�N���v�g����s���K�v������̂ŁA
	���ׂă��W�X�^�ֈړ������B
	-------------------------------------------------------
	�[���y�[�W:
		�[���y�[�W������A�N�Z�X�������Ȃ�Ă��Ƃ͂Ȃ���B
		�Ȃ�ł���Ȗ��O�Ȃ̂��Ƃ����ƁA�J�[�h�X�N���v�g�J�n����
		�K���[���N���A����邩��B
	-------------------------------------------------------
	ToDo:
	�J�[�hCPU��I/O �|�[�g(==���W�X�^)�ɁA�{�X�̈ړ��������}�b�s���O���āA
	�{�X�̃R���g���[���͂��ׂăJ�[�hCPU�o�R�ōs���l�ɂ���B
	���l�ɃT�E���h�����ׂ�I/O �|�[�g(==���W�X�^)�ɁA�}�b�s���O����B
---------------------------------------------------------*/

/*---------------------------------------------------------
	���W�X�^
	-------------------------------------------------------
	'R##' means Register Number, '##' means Hex number(00 ... 2f).
	Always equal 'R##' and '##', but '##' means number and 'R##' means Register Number.
	-------------------------------------------------------
	R## �� ���W�X�^(Register)�ԍ�(Number)�ł��BR## == ## �ł��B
	����(Number)�ŏ����ƁA�����Ȃ̂����W�X�^�Ȃ̂�����Ȃ��̂ł����Ȃ�܂����B
	-------------------------------------------------------
	'VR##' means Register Number of Value.
	ex. VR08 = 5; // R08 into value of 5.
	-------------------------------------------------------
	VR## �� ���W�X�^�l�ł��BVR## == R##�̒l �ł��B
	'V' �� Value(�Ӗ��͒l) �ł��B
	C����ł́A VR08 = 5; �Ƃ��� R08 �ɐ��l 5 ������܂��B
---------------------------------------------------------*/

enum
{
	// �[���y�[�W[�[���N���A�����B]
	// ���W�X�^(�S�Ă̌v�Z�͓������W�X�^0x00-0x0f�ł����o���Ȃ�)
	R00 = (0),	// ZERO���W�X�^�B ��� �萔(0) �����鎖�ŁA�����ꍇ�ɔ��CPU���߂��팸�ł���B
	R01,		// [����]CC1���W�X�^�BCONDITION_CODE1 IF��LOOP���ňÖقɗ��p(�\��)�B// [���g�p]�B
	R02_j,		// j���W�X�^(���[�v2�p)�B// ��{�I�ɓ�������2�Ԗڂ̃��[�v�p�B(�Ⴕ���͎G�ϐ�)
	R03_i,		// i���W�X�^(���[�v1�p)�B// ��{�I�Ɉ�ԓ����̃��[�v�p�B(�Ⴕ���͎G�ϐ�)
	R04,		// 0�󂯓n�����W�X�^�BREG_ _00_SRC_X
	R05,		// 1�󂯓n�����W�X�^�BREG_ _01_SRC_Y
	R06,		// 2�󂯓n�����W�X�^�BREG_ _02_DEST_X
	R07,		// 3�󂯓n�����W�X�^�BREG_ _03_DEST_Y
	//
	R08,		// �ėp���W�X�^0�B
	R09,		// �ėp���W�X�^1�B
	R0a,		// �ėp���W�X�^2�B
	R0b,		// �ėp���W�X�^3�B
	R0c,		// �ėp���W�X�^4�B
	R0d,		// �ėp���W�X�^5�B
	R0e,		// �ėp���W�X�^6�B
	R0f,		// �ėp���W�X�^7�B
	// I/O�|�[�g(�O���̓��o�͂�I/O�|�[�g0x10-0x1f���o�R���Ȃ��Əo���Ȃ�)
	R10,		// �X�y���o�ߎ��ԗp���W�X�^�BREG_ _10_BOSS_SPELL_TIMER
	R11,		// ���e�p���W�X�^1�Btama_system �ɐڑ��BHATSUDAN_R11_speed256
	R12,		// ���e�p���W�X�^2�Btama_system �ɐڑ��BHATSUDAN_R12_speed_offset
	R13,		// ���e�p���W�X�^3�Btama_system �ɐڑ��BHATSUDAN_R13_angle65536
	R14,		// ���e�p���W�X�^4�Btama_system �ɐڑ��BHATSUDAN_R14_tama_spec
	R15,		// ���e�p���W�X�^5�Btama_system �ɐڑ��BHATSUDAN_R15_bullet_obj_type
	R16,		// ���e�p���W�X�^6�Btama_system �ɐڑ��BHATSUDAN_R16_n_way
	R17,		// ���e�p���W�X�^7�Btama_system �ɐڑ��BHATSUDAN_R17_div_angle65536
	// �X�N���v�g������ʉ����ǂ��������d�l���m�肵�Ă��Ȃ��B
	R18,		// REG_NUM_18_ VOICE_NUMBER REG_NUM_18_SOUND_REG0, // ���ʉ��ԍ��ێ��p���W�X�^�B
	R19,		// REG_NUM_19_ VOICE_TRACK REG_NUM_19_SOUND_REG1, // ���ʉ��g���b�N�ԍ��ێ��p���W�X�^�B
	R1a_,					// R1a_SOUND_REG2,	// [���g�p]�B
	R1b_,					// R1b_SOUND_REG3,	// [���g�p]�B
	//=================== ���������́A�[���N���A�����B
	R1c_bullet_clip_min_x256,					// POINT256 bullet_clip_min;	/* �e�͈̔�(�ŏ��l)�����������W���E�l */
	R1d_bullet_clip_min_y256,					// POINT256 bullet_clip_min;	/* �e�͈̔�(�ŏ��l)�c���������W���E�l */
	R1e_bullet_clip_max_x256,					// POINT256 bullet_clip_max;	/* �e�͈̔�(�ő�l)�����������W���E�l */
	R1f_bullet_clip_max_y256,					// POINT256 bullet_clip_max;	/* �e�͈̔�(�ő�l)�c���������W���E�l */
//===================
	// cg ����ړ��B
	/* R20: ��Փx���W�X�^�B ���̃��W�X�^�́A��Փx������B */
	R20_PLAYER_DATA_game_difficulty,			//	s32 game_difficulty;			/* (psp��max, min���߂��g���Ă���̂� signed int �̕K�v������ ) */
	R21_PLAYER_DATA_game_score, 				//	u32 game_score; 				/* �X�R�A���_ */
	R22_PLAYER_DATA_graze_point,				//	u32 graze_point;				/* �O���C�Y���_ */
	R23_PLAYER_DATA_bombs,						//	int bombs;						/* �{���� */
	R24_PLAYER_DATA_zanki,						//	int zanki;						/* �c��`�����X */
	R25_PLAYER_DATA_game_rank,					//	s32 game_rank;					/* �����N�ϓ��V�X�e���̃Q�[�������N */
	R26_PLAYER_DATA_jiki_weapon_level,			//	u32 jiki_weapon_level;			/* (r35u2)�����̂� */		//	/*u8*/u32 jiki_weapon_level_offset;/* �����������탌�x��(�ԍ�)�̂W�{�Ƀv���C���[�l�𑫂����l���I�t�Z�b�g�Ƃ��ĕێ� */
	R27_PLAYER_DATA_weapon_power,				//	int weapon_power;				/* 0x00-0x80  (0-128 ��129�i�K==�{�ƂƓ���)   max==128==�u129�i�K�v*/
	R28_PLAYER_DATA_bomber_time,				//	s32 bomber_time;				/* Use Gu */  // /* bomb_wait */ /* �{���̗L������ */
	R29_PLAYER_DATA_chain_point,				//	int chain_point;
	R2a_PLAYER_DATA_state_flag, 				//	u32 state_flag; 				/* �ݒ�t���O(�W) */
	R2b_PLAYER_DATA_player_data_use_continue,	//	int player_data_use_continue;	/* �R���e�B�j���[�� */
	R2c_PLAYER_DATA_player_data_count_misstake, //	int player_data_count_miss; 	/* �~�X�� */
	R2d_PLAYER_DATA_player_data_used_bomber,	//	int player_data_used_bomber;	/* �{���g�p�� */
	R2e_PLAYER_DATA_player_data_use_kurai_bomb, //	int player_data_use_kurai_bomb; /* ��炢�{�������� */
	R2f_PLAYER_DATA_player_data_count_bonus,	//	int player_data_count_bonus;	/* �J�[�h�{�[�i�X�� */
	// �W�v�V�X�e��(player_data)				//	/* �W�v�V�X�e��(player_data) */
	R30_BOSS_DATA_target_x256,					// �{�X�p�B /* �ڕWx���W */
	R31_BOSS_DATA_target_y256,					// �{�X�p�B /* �ڕWy���W */
	R32_BOSS_DATA_chuu_boss_mode,				// (���{�X�p)�B/ [remilia] ���e���J�E���^�B
	R33_BOSS_DATA_kougeki_anime_count,			// �{�X�p�B /* �U���A�j���[�V�����p�J�E���^ / 0�ȉ��Ȃ�ړ��A�j���[�V���� */
	R34_BOSS_DATA_toutatu_wariai256,			// �{�X�p�B /* �ڕW���W�ւ̓��B���� */
	R35_BOSS_DATA_move_jyumyou, 	// �{�X�p�B /* �������� */	/* ��������(boss_move_timer�Ɠ���) */
	R36_BOSS_DATA_sakuya_data_move_angle1024,	// �{�X�p�B /* ���̊p�x */
	R37_BOSS_DATA_sakuya_data_common_wait256,	// �{�X�p�B /* ���� */
	R38_BOSS_DATA_angleCCW65536,				// �{�X�p�B (��src->tm p_angleCCW65536)
	R39_BOSS_DATA_tukaima_type, 				// �{�X�p�B�g�p����g�����̃^�C�v�B
	R3a_BOSS_DATA_center_x256,					// �{�X�p�Bobj ���Sx���W(�R�s�[)
	R3b_BOSS_DATA_center_y256,					// �{�X�p�Bobj ���Sy���W(�R�s�[)
	R3c_boss_clip_min_x256, 					// POINT256 boss_clip_min;	/* �{�X�ړ��͈�(�ŏ��l)�����������W���E�l */
	R3d_boss_clip_min_y256, 					// POINT256 boss_clip_min;	/* �{�X�ړ��͈�(�ŏ��l)�c���������W���E�l */
	R3e_boss_clip_max_x256, 					// POINT256 boss_clip_max;	/* �{�X�ړ��͈�(�ő�l)�����������W���E�l */
	R3f_boss_clip_max_y256, 					// POINT256 boss_clip_max;	/* �{�X�ړ��͈�(�ő�l)�c���������W���E�l */
	//
	REG_NUM_99_MAX// = 0x20/*(.align 32)*/
};
// �[���y�[�W�̃T�C�Y
#define REG_NUM_0x1c_ZERO_PAGE_MAX (R1b_+1)

// �e�͈̔�(alias)
#define VR1c_bullet_clip_min_x256		spell_register[R1c_bullet_clip_min_x256]
#define VR1d_bullet_clip_min_y256		spell_register[R1d_bullet_clip_min_y256]
#define VR1e_bullet_clip_max_x256		spell_register[R1e_bullet_clip_max_x256]
#define VR1f_bullet_clip_max_y256		spell_register[R1f_bullet_clip_max_y256]
// �{�X�ړ��͈�(alias)
#define VR3c_boss_clip_min_x256 		spell_register[R3c_boss_clip_min_x256]
#define VR3d_boss_clip_min_y256 		spell_register[R3d_boss_clip_min_y256]
#define VR3e_boss_clip_max_x256 		spell_register[R3e_boss_clip_max_x256]
#define VR3f_boss_clip_max_y256 		spell_register[R3f_boss_clip_max_y256]

//typedef struct /*_clip_class_*/
//{
//	POINT256 boss_clip_min; 	/* �{�X�ړ��͈�(�ŏ��l) */
//	POINT256 boss_clip_max; 	/* �{�X�ړ��͈�(�ő�l) */
//
//	POINT256 bullet_clip_min;	/* �e�͈̔�(�ŏ��l) */
//	POINT256 bullet_clip_max;	/* �e�͈̔�(�ő�l) */
//} RECT_CLIP_CLASS;
//extern RECT_CLIP_CLASS rect_clip;

/*---------------------------------------------------------
	�V�X�e�����W�X�^�B�K��͈�: R00 ... R07
	-------------------------------------------------------
	�K��͈�: R00	�g�p�֎~�B0�ȊO��������CPU���ߎ��̂����퓮��ł��܂���B(private)
	�K��͈�: R01	CPU�̓�������p�Ȃ̂ŊO������g�p�֎~�B(private)
	-------------------------------------------------------
	�K��͈�: R02 ... R03	���[�v�ϐ��p�ł��B(public)
	-------------------------------------------------------
	�K��͈�: R04 ... R07	�󂯓n����ƂɎg�p���܂��B(public)
---------------------------------------------------------*/

//#define MAX_FIX_VALUE (REG_NUM_01_FIX_VALUE+1)/*�Œ�l�͈̔�*/
//�J�[�h�X�N���v�g���s���ɂ͖��t���[���A�{�X�̌��ݍ��W���X�V�����B
/*static*/extern int spell_register[REG_NUM_99_MAX];

/* ���ۂ̃��W�X�^ */
// [system registers]�V�X�e�����W�X�^�B
//0[�Œ�]#define VR00	spell_register[R00]�g�p�֎~�B
// [����]#define VR01	spell_register[R01]
#define VR02_j	spell_register[R02_j]
#define VR03_i	spell_register[R03_i]
// [delivery registers]�󂯓n�����W�X�^�B
#define VR04	spell_register[R04]
#define VR05	spell_register[R05]
#define VR06	spell_register[R06]
#define VR07	spell_register[R07]
//
//
/* �󂯓n�����W�X�^��[alias]�G�C���A�X[�ʖ���`] */
#define VR04_NAN_IDO_DECODE 	VR04
#define VR04_temp				VR04

/*---------------------------------------------------------
	���[�N���W�X�^�B�K��͈�: R08 ... R0f
	-------------------------------------------------------
	�X�y�J�Ŏg�p���郌�W�X�^�B
---------------------------------------------------------*/
// [general registers]�ėp���W�X�^�B(�ėp==general purpose)
#define VR08	spell_register[R08]
#define VR09	spell_register[R09]
#define VR0a	spell_register[R0a]
#define VR0b	spell_register[R0b]
#define VR0c	spell_register[R0c]
#define VR0d	spell_register[R0d]
#define VR0e	spell_register[R0e]
#define VR0f	spell_register[R0f]
//
#if (1)/*(�����ɃX�y�J�����Ă���ׁA�A�������Ƀ��W�X�^����v��)*/

// [alias]�G�C���A�X[�ʖ���`]
#define VR0f_SAKUYA_LINK		VR0f/*[���:���e�A�����W�X�^]*/
//#define VR0f_AYA_LINK 		VR0f/*[��:���e�A�����W�X�^]*/
#define VR0f_AYA_LINK			VR09/*[��:���e�A�����W�X�^]*/
enum
{
	SAKUYA_LINK_00_DONE = (0),	/*(�I�������)*/
	SAKUYA_LINK_01_RYOUTE_KNIFE,/*(attack type 1)*/
	SAKUYA_LINK_02_KURU_KURU,	/*(attack type 2)*/
};
enum
{
	AYA_LINK_00_NONE = (0), 	/*(�Ȃ�)*/
	AYA_LINK_01_RENDAN, 		/*(attack type 1)*/
	AYA_LINK_02_FUDADAN,		/*(attack type 2)*/
	AYA_LINK_03_OODAMA, 		/*(attack type 3)*/
};
#define AYA_LINK_03_OODAMA_23	AYA_LINK_03_OODAMA
#define AYA_LINK_03_OODAMA_22	AYA_LINK_03_OODAMA
#define AYA_LINK_03_OODAMA_21	AYA_LINK_03_OODAMA

#endif

/*---------------------------------------------------------
	�e�V�X�e���ڑ�I/O�|�[�g�B�K��͈�: R10 ... R17
---------------------------------------------------------*/
// [tama registers](���e�V�X�e��)
/*
	tama (teki-dan) == enemy bullets, japan language.
	shot (ji-dan)	== player bullets, japan language.
	when tama system, enemy bullets only.
*/
#define VR10	spell_register[R10] 	/* �X�y���o�ߎ��� */
/*([tama_system �ɒ��ڐڑ����Ă��郌�W�X�^])*/
#define VR11	spell_register[R11]
#define VR12	spell_register[R12]
#define VR13	spell_register[R13]
#define VR14	spell_register[R14]
#define VR15	spell_register[R15]
#define VR16	spell_register[R16]
#define VR17	spell_register[R17]
// [alias]�G�C���A�X[�ʖ���`]
#define VR10_BOSS_SPELL_TIMER	VR10	/* �X�y���o�ߎ��� */

/*---------------------------------------------------------
	���ʉ��V�X�e���ڑ�I/O�|�[�g�B�K��͈�: R18 ... R1f
---------------------------------------------------------*/

#define VR18	spell_register[R18]
#define VR19	spell_register[R19]

/*([audio_system �ɒ��ڐڑ����Ă��郌�W�X�^])*/
#define AUDIO_18_voice_number	VR18/*(���ʉ��̌ŗL�ԍ��B���̎��)*/
#define AUDIO_19_voice_truck	VR19/*(�Đ��g���b�N�w��)*/


/*---------------------------------------------------------
	���蒆���W�X�^�B	�K��͈�: R20 ... R2f
	���蒆���W�X�^�B	�K��͈�: R30 ... R3f
	-------------------------------------------------------
	�{�X���ʋK�i���W�X�^�B
	���@��ԃ��W�X�^�B
---------------------------------------------------------*/
enum
{
	chuu_boss_00_mode_off = (0),
	chuu_boss_01_mode_stay,
//	chuu_boss_02_mode_spell,/*(�\��)*/
};
/* �{�X���ʋK�i */
#define cg_BOSS_DATA_30_target_x256 					spell_register[R30_BOSS_DATA_target_x256]
#define cg_BOSS_DATA_31_target_y256 					spell_register[R31_BOSS_DATA_target_y256]
#define cg_BOSS_DATA_32_chuu_boss_mode					spell_register[R32_BOSS_DATA_chuu_boss_mode]
#define cg_BOSS_DATA_33_kougeki_anime_count 			spell_register[R33_BOSS_DATA_kougeki_anime_count]
#define cg_BOSS_DATA_34_toutatu_wariai256				spell_register[R34_BOSS_DATA_toutatu_wariai256]
#define cg_BOSS_DATA_35_move_jyumyou					spell_register[R35_BOSS_DATA_move_jyumyou]
// [alias]�G�C���A�X[�ʖ���`]
#define cg_BOSS_DATA_35_boss_base_state777				cg_BOSS_DATA_35_move_jyumyou
/*(���)*/
#define cg_BOSS_DATA_36_sakuya_data_move_angle1024		spell_register[R36_BOSS_DATA_sakuya_data_move_angle1024]
#define cg_BOSS_DATA_37_sakuya_data_common_wait256		spell_register[R37_BOSS_DATA_sakuya_data_common_wait256]
//
#define cg_BOSS_DATA_38_angleCCW65536					spell_register[R38_BOSS_DATA_angleCCW65536]
//
#define cg_BOSS_DATA_3a_center_x256 					spell_register[R3a_BOSS_DATA_center_x256]
#define cg_BOSS_DATA_3b_center_y256 					spell_register[R3b_BOSS_DATA_center_y256]
//
#define cg_BOSS_DATA_39_tukaima_type					spell_register[R39_BOSS_DATA_tukaima_type]

//

#define cg_VR20_game_difficulty 						spell_register[R20_PLAYER_DATA_game_difficulty]
#define cg_game_score									spell_register[R21_PLAYER_DATA_game_score]
#define cg_graze_point									spell_register[R22_PLAYER_DATA_graze_point]
#define cg_bombs										spell_register[R23_PLAYER_DATA_bombs]
#define cg_zanki										spell_register[R24_PLAYER_DATA_zanki]
#define cg_game_rank									spell_register[R25_PLAYER_DATA_game_rank]
#define cg_jiki_weapon_level							spell_register[R26_PLAYER_DATA_jiki_weapon_level]
#define cg_weapon_power 								spell_register[R27_PLAYER_DATA_weapon_power]
#define cg_bomber_time									spell_register[R28_PLAYER_DATA_bomber_time]
#define cg_chain_point									spell_register[R29_PLAYER_DATA_chain_point]
//
#define cg_state_flag									spell_register[R2a_PLAYER_DATA_state_flag]
//
#define cg_player_data_use_continue 					spell_register[R2b_PLAYER_DATA_player_data_use_continue]
#define cg_player_data_count_miss						spell_register[R2c_PLAYER_DATA_player_data_count_misstake]
#define cg_player_data_used_bomber						spell_register[R2d_PLAYER_DATA_player_data_used_bomber]
#define cg_player_data_use_kurai_bomb					spell_register[R2e_PLAYER_DATA_player_data_use_kurai_bomb]
#define cg_player_data_count_bonus						spell_register[R2f_PLAYER_DATA_player_data_count_bonus]


/*---------------------------------------------------------
	�w���p�[�}�N���B
	-------------------------------------------------------
---------------------------------------------------------*/

/*([�����Ă��o���邯��]�����������֗�)*/
//#define USE_CPU_EXTRA (1)
#define USE_CPU_EXTRA (0)

/*(�}�C�N���I�y�R�[�h�֕ϊ�[�R���p�C��])*/
#define MCODE(reg_op,reg_v0,reg_ra,reg_rb) (((reg_op)&0xff)|(((reg_v0)&0xff)<<8)|(((reg_ra)&0xff)<<16)|(((reg_rb)&0xff)<<24))

#define NAX 	(0)/*[����`�l�B���̃V�X�e���� 0 �Œ�]*/

enum
{
	LONG_MEMORY_ADDRESSING = (0),	/*(0==�����O�A�h���b�V���O)*/
//	NANIDO_REGISTER_ADDRESSING = (0),		/*(0==��Փx���W�X�^�A�h���b�V���O)*/
	REGISTER_ADDRESSING = (0),		/*(0==���W�X�^�A�h���b�V���O)*/
	MEMORY_ADDRESSING,				/*(1==�������A�h���b�V���O)*/
	#if (1==USE_CPU_EXTRA)/*([�����Ă��o���邯��]�����������֗�)*/
	CPU_QUIT = (0), 				/*(0==quit)*/
	#endif
	#if (1)/*(��{�e�������߂̃A�h���b�V���O)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE = (0),		/*(0 == 1�e�ł�)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY,	/*(1 == �΂� n way �e)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, 			/*(2 == ���� n way �e[�ʏ� n way �e�B�ʏ� n way �e�́A�u�΂� n way �e�v�������2���Ԏ��ɂ�萶������])*/
	#endif
};
#define LONG_ONLY	(LONG_MEMORY_ADDRESSING)/*(�����O�������A�h���b�V���O��p����)*/


/*---------------------------------------------------------
	�J�[�h CPU �}�C�N���R�[�h
	-------------------------------------------------------
	���� CPU �́A1���[�h(�ŏ���{�P��)�� 32[bit]�ł��B
	���߂� �ϒ� �ŁA�����̖��߂́A1���[�h���߂ł��� 2���[�h���߂�����܂��B
	�e�[�u�����߂� �e�[�u���̒������[�h����܂��B(n���[�h����)
	1���[�h��(32bit)�́A���W�X�^���a(u8) + ���W�X�^���`(u8) + ���l(s8) + �I�y�R�[�h(u8) �̍\���� 32[bit]�B
	2���[�h��(32bit)���A�I�y�����h(u32) �̍\���� 32[bit]�B(2���[�h�ڂ́A�K�{�łȂ���2���[�h�ڂ����閽�߂� 1/3 ���炢�ł�)
	3���[�h��(32bit)�ȍ~������̂̓e�[�u�����߂ł��B
	-------------------------------------------------------
	This CPU own basic wards as 32 bit.(say word == 32bit, word not 16bit, 'word' means 'long word' not short word.)
	The Opecode, valiable length. 1[word=32bit] or 2[word=32bit]==64bit.
	The table opecode 2 words.
	1 [word=32bit==4x8bytes]:
		MSB 4[byte]) name reg B (8[bit]==u8== 0 ... 255)
			3[byte]) name reg A (8[bit]==u8== 0 ... 255)
			2[byte]) immidiate value(8[bit]==s8 == -128 ... 127)
		LSB 1[byte]) opecode  (8[bit]==u8== 0 ... 255)
	2 [word=32bit]:
		(u32) valiable.(s32 valiable)
	3 ...  [word=32bit]:
		(u32) valiable.(s32 valiable)
	-------------------------------------------------------
	���W�X�^����(8bit)�Ȃ̂ŁA���� CPU �̍ő�ێ����W�X�^�� 256���W�X�^�B
	���� 256���W�X�^�͑��Čv�Z�Ŏg�����ł͂Ȃ��AI/O�|�[�g�@�\(�Q�[���̑S�@�\�������)�� �S�̂� 3/4 ���炢����ׁA���� �ő�64���W�X�^���炢�B
	�Ƃ肠����[r40]�����_�̍ő僌�W�X�^�� ���W�X�^(12) +I/O�|�[�g(8)�ōς�ł���B
	-------------------------------------------------------
----:	����`
OPxx:	�}�C�N���I�y�R�[�h (L--- ---- L: 0:�V���[�g�A�h���b�V���O(32bit), 1:�����O�A�h���b�V���O(32bit x 2) )
RA--:	���W�X�^���`
RB--:	���W�X�^���a
VAL0:	�V���[�g�l (0 ... 255)
JR++:	�}�C�N���R�[�h�ЂƂ��W�����v(1���ߕ���΂�)
[M+]:	�}�C�N���R�[�h�̎��ʒu�̃���������ǂށB
L32:	u32 �萔�B (32bit)
	-------------------------------------------------------
��	�u�����`(�W�����v)�n���߂́A���΃u�����` PC+(s8)VAL; �����v��Ȃ��B
��	�e�̈ړ�������V������`����ꍇ�B�����O�A�h���X���v�邪���ڎg��Ȃ��B
��	�R�[�h�� ���LRAM �ɃR�s�[���ē����\���ɂ���ƁA�e�̈ړ������̏ꍇ�ɍ���Ȃ��H
	���LRAM�� ���C���v���Z�X���R�s�[���ē������ǁA�e�̈ړ������̏ꍇ�A
	���I�ɃA�h���X���t���āA�e�̃v���Z�X���R�s�[���ē����B
	��������A�������Z�N�V�����Ŏg�p�e�̃v���Z�X���R�s�[���Ă��������������悢�B
---------------------------------------------------------*/
#define USE_CPU_BHI_BPL (0)
enum
{
	// �R�[�h�ԍ�					// �Ӗ� 						����format(32bit)					���ߒ�		����									PC++;	PC++;	//	�Ή�����C����ł̖���
	// (��{����)--------
	OP0x00_EXIT = 0,				// �X�y���I���B 				----, ----, ----, OPxx				(1) 		����̃t���[���I���B					PC++;	PC++;	//	�Ȃ��B(return;)
	OP0x01_MOVER_PD,				// ���W�X�^�ԓ]���B 			RB--, RA--, VAL0, OPxx				(1) 		RA = (RB) + VAL0;						PC++;	PC++;	//	CPU_CALL(MOVER_PD_NUM);
	OP0x02_COUNTER, 				// �J�E���^�[�B 				----, RA--, VAL0, OPxx				(1) 		RA++;if (RA > (s32)VAL0) {RA=0;}		PC++;	PC++;	//	CPU_CALL(count_up_limit_NUM);
	OP0x03_NAN_IDO, 				// ��Փx���f�R�[�h����B		0x00, RA--, ----, OPxx	data32		(2) 		PC++;	R9 = decode[data32];					PC++;	//	CPU_CALL(nan_ido);
	OP0x04_ADDR_PD, 				// ���W�X�^�� ���Z(���Z)�B		RB--, RA--, VAL0, OPxx				(1) 		RA = (RA + RB) + VAL0;					PC++;	PC++;	//	CPU_CALL(ADDR_PD_NUM);
	OP0x05_SUBR_PD, 				// �������]/���Z
	OP0x06_BRAR_NN, 				// ����������(���W�X�^�l)		----, RA--, ----, OPxx				(1) 							PC += RA;							//	�Ȃ��B	// (���̖��߂͕K�v) �W�����v�e�[�u��[�⏕]����
	/*[���g�pr42]*/OP0x07_REGIST_PROCESS,// �v���Z�X�o�^(���̖��߂͂�����K�v)
	//--------
	// (�u�����`�n����)--------
	OP0x08_BNE_RS,					// �l���Ⴆ�Ε���				IRB-, RA--, VAL0, OPxx				(1) 		if (VAL0 != RA) 	{PC += IRB;} else {PC++;}			//	�Ȃ��B	// (���̖��߂͕K�v)
	OP0x09_BFL_RS,					// �l�������Ȃ番�� 			IRB-, RA--, VAL0, OPxx				(1) 		if (VAL0 < RA)		{PC += IRB;} else {PC++;}			//	�Ȃ��B	// (���̖��߂͕K�v)
	OP0x0a_BRA_TABLE,				// �z�� 						IRB-, RA--, VAL0, OPxx				(1) 		RA = PC+1[VAL0];	PC += IRB;							//	�Ȃ��B	// (���̖��߂͕K�v)
	OP0x0b_BRA_RS,					// ����������(���l) 			IRB-, ----, ----, OPxx				(1) 							PC += IRB;							//	�Ȃ��B	// (���̖��߂͕K�v)
	// (��{�e��������)-------- (�����������e�V�X�e�����œZ�߂������ǂ�����)
	OP0x0c_hatudan_system_regist_tama,			// ��{�e�������߁B(single, n_way, katayori_n_way)
	OP0x0d_AUDIO_VOICE_PLAY,
	OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18,
	OP0x0f_CLEAR_ZERO_PAGE, 		/* (r35)�J�[�h�X�N���v�g�p����(�J�[�h���W�X�^�S������) */
	//	(�T�|�[�g����)--------
	OP0x10_SINCOS256,				// �T�C�� & �R�T�C���B			----, ----, ----, OPxx				(1) 		sin();cos();							PC++;	PC++;	//	CPU_CALL(sincos256);
	OP0x11_BOSS_TO_JIKI_NERAI,		// �{�X���玩�@�_���B
	OP0x12_JIKI_NERAI,				// ���@�_���p�쐬�B 			----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(calculate_jiki_nerai);
	OP0x13_HANYOU_NERAI,			// �ėp�ڕW�_���p�쐬�B 		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(atan_65536);
	OP0x14_MULTIPREX_RATE_VECTOR,	// �������������B				----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(multiprex_rate_vector);
	OP0x15_RAND_VALUE,				// ���v���C�Ή����������B		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(replay_rand_init);
	OP0x16_RAND_INIT,				// ���v���C�Ή����������B		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(replay_rand);
	OP0x17_DIV65536,				// ����Z���߁B65535 / n		RB--, RA--, ----, OPxx				(1) 		R6 = 65536 / R5;						PC++;	PC++;	//	CPU_CALL(div65536); ([�\��] RA = 65536 / RB;)
	//--------
	// (�g������[CPU�O���R�[�h(����)])-------- �����������O�V���[�g�A�h���b�V���O�B
	/*[���g�pr42]*/OP0x18_,
	/*[���g�pr42]*/OP0x19_,
	/*[���g�pr42]*/OP0x1a_,
	OP0x1b_ADDM_LONG_PD,			// u32�Œ�l ���Z(���Z) 		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA +=	([data32] + VAL0);				PC++;	//	�Ȃ��B
	//
	OP0x1c_MOVEM_PD,				// u32�Œ�l ���l����B 		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA =	([data32] + VAL0);				PC++;	//	�Ȃ��B
	OP0x1d_ANDM_PD, 				// u32�Œ�l AND���Z			0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA &=	([data32] + VAL0);				PC++;	//	�Ȃ��B
	OP0x1e_ASRM_PD, 				// u32�Œ�l �Z�p�E�V�t�g		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA >>=	([data32] + VAL0);				PC++;	//	�Ȃ��B(��3:)
	OP0x1f_ASLM_PD, 				// u32�Œ�l �Z�p���V�t�g		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA <<=	([data32] + VAL0);				PC++;	//	�Ȃ��B
	//--------
	OP0x99_MAX,/*[CPU�O�����߂̍ő吔]*/
};
	#if 0/*(����)*/
	(��3:)
	�Z�p�V�t�g�Ȃ̂ōŏ��bit�� 1 �̏ꍇ�A�_���V�t�g�ƌ��ʂ��Ⴄ�B
	�V���[�g�A�h���b�V���O�̏ꍇ�� �ŏ��bit�� 8 �ŁA
	�����O�A�h���b�V���O�̏ꍇ�� �ŏ��bit�� 32 �Ɠ�����قȂ�B
	#endif

	//	/*[���g�pr42]*/OP0x0d_SUBM_PD,/*�Ă���*/
	//--------
//	OP0x1a_/*ANDR_PD*/, 			//[���g�p] ���W�X�^�� AND���Z�B 		RB--, RA--, VAL0, OPxx	dummy32 	(1) 	RA = (RA & RB) + VAL0;					PC++;	PC++;	//	CPU_CALL(ANDR_PD_NUM);
// u32�Œ�l ���l����B 		----, ----, VAL0, OPxx	data32		(2) 	[VAL0]PC = [data32];					PC++;

//#define OP0x05_NEGR_PD OP0x05_SUBR_PD

// (����)/#define MCODE_OP0x05_NEGR_PD(arg_v0, arg_rb) MCODE(OP0x05_SUBR_PD, arg_v0, R00, arg_rb)

	#if 0/*(�܂��l����̑���(?))*/
//	OP0x08_BEQR,					// u8����	�W�����v			RB--, RA--, VAL0, OPxx	dummy32 	(1) 	if (RA==RB) goto PC+(s32)VAL0;			PC++;	PC++;	//	�Ȃ��B Branch relative Jump, if Equal. for register.
//	OP0x08_BEQS,					// u8����	�W�����v			VAL2, RA--, VAL0, OPxx	dummy32 	(1) 	if (RA==(s32)VAL2) goto PC+(s32)VAL0;	PC++;	PC++;	//	�Ȃ��B Branch relative Jump, if Equal. for short index.
//	BEQ BNE BLS BHI ...
	#endif


/*
OP0x16_div65536�̈�

	OP16, ----, RA--, RB--
	RB = 65536 / RA;


ToDo:
	������������������
*/

extern void cpu_exec(u32 *codebase, s32 icount);

/*(CARD CPU ��������)*/
extern CPU_FUNC(sincos256);

#endif /* _CARD_CPU_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _HATSUDAN_SYSTEM_H_
#define _HATSUDAN_SYSTEM_H_
/*---------------------------------------------------------
	���e�V�X�e��
	-------------------------------------------------------
	�ǂ�Ȓe�ł����e����ꍇ�͕K���u���e�V�X�e���v��ʂ�Ȃ���΂Ȃ�Ȃ��B
	����́A�ꃖ���ɖ����Ƌɒ[�ɑ��x�ቺ����̂���ȗ��R�B
	-------------------------------------------------------
	���e�V�X�e���͎�ɔ��e�G�t�F�N�g�̎w������邪�A
	���e�G�t�F�N�g�̖����e�ł����R���e�V�X�e����ʂ�Ȃ���΂Ȃ�Ȃ��B
	-------------------------------------------------------
	���e�G�t�F�N�g�͌��󔭒e�V�X�e�����S�����Ă��邪�A
	�����I�ɂ����ƌ����I�ȕʃV�X�e���ɂȂ�B
	�u�e���v�ɓ������āu�e(�e)�v��(�ړ�)�������o���Ȃ��Ȃ�B
	����́u�e���v�V���[�e�B���O�̏ꍇ�A�e�̈ړ������͕K�v�����ׁA
	�e�̈ړ������͖����B����ƒx���B
---------------------------------------------------------*/

/*---------------------------------------------------------
	���e�P�ʂ̎󂯓n���ݒ�(�p�x�e�̏ꍇ)
	-------------------------------------------------------
	�p�x�e�̕���\��65536�x�Ɍ���B
	-------------------------------------------------------
	�����J�[�h�X�N���v�g�V�X�e���Ɉڍs�����ꍇ�A
	���̍\���̂́A�J�[�h�X�N���v�g�p�̃��W�X�^(���[�J���������[)��
	�ړ�����B(�łȂ��ƃJ�[�h�X�N���v�g�ォ��e���ǂ������ł��Ȃ��̂�)
---------------------------------------------------------*/

#if 1

	/*([tama_system �ɒ��ڐڑ����Ă��郌�W�X�^])*/
	// �ȉ��́A �e�̐ݒ�B
	#define HATSUDAN_R11_speed256			VR11 /* ���x */
	#define HATSUDAN_R12_speed_offset		VR12 /* �����x */
	#define HATSUDAN_R13_angle65536 		VR13 /* �p�x */ 				/* <����\65536�x�Ɍ���> */
	#define HATSUDAN_R14_tama_spec			VR14 /* �e�̔\�͑��� */
	#define HATSUDAN_R15_bullet_obj_type	VR15 /* �e�O���t�B�b�N�̎�� */
	// �ȉ��́A n_way�e�̏ꍇ�ɕK�v�ȗv�f�B
	#define HATSUDAN_R16_n_way				VR16 /* n way �e�̒e�� */
	#define HATSUDAN_R17_div_angle65536 	VR17 /* n way �e�̕����p�x */	/* <����\65536�x�Ɍ���> */
	// �ʖ���`�B(alias)
	/* �����������ǁA 65536�����Ȃ̂� 1024 �����Ȃ̂���������ׂɕK�v�B */
	//[�p�~�ς�r42]#define HATSUDAN_R13_angle1024			VR13	/* �`��p�p�x */	/* <�`��p�̕���\1024�x�ɗ��Ƃ��Ă��鎖�𖾎�����B> */
	/* �����������ǁA  �B */
	#define REG_11_GOUSEI_WARIAI256 		VR11
#endif

#if 1
	/*([tukaima_system �ɒ��ڐڑ����Ă��郌�W�X�^])*/
	/*
		�g�����Ɋւ��ẮA���ڃX�N���v�g����R���g���[���ł��Ȃ��Ƙb�ɂȂ�Ȃ��̂ŁA
		���ڐڑ����Ă��郌�W�X�^������B
	*/
#endif

#if 1
	/*([audio_system�ɒ��ڐڑ����Ă��郌�W�X�^])*/
	/*
		���ʉ��ABGM�����W�X�^�o�R�łȂ��ƃX�N���v�g���o���Ȃ��B
	*/
#endif

/*---------------------------------------------------------
	�o�^���
---------------------------------------------------------*/

//extern void hatudan_system_regist_single(void);			/* �P�� */
//extern void hatudan_system_regist_katayori_n_way(void);	/* �΂� n way�e */
//extern void hatudan_system_regist_n_way(void);				/* �ʏ� n way�e */
extern void hatudan_system_regist_tama(int set_addressing);

/*---------------------------------------------------------
	���e�o�^�K�i
---------------------------------------------------------*/
	#define TR00_hatudan_spec_data				system_data00	/* ��ʊO��������┽�ˋ@�\ */
	//
	#define TR01_hatudan_speed65536 			user_data00 	/* ������ */
	#define TR02_hatudan_tra65536				user_data01 	/* ���������� */
	#define TR03_hatudan_frame_counter			user_data02 	/* ���e�t���[���J�E���^(���l�Ŕ��e) */
	//
//	#define hatudan_system_bbb					user_data04 	/* �g���\��(?) (r33���ݖ��g�p) / */
//	#define hatudan_system_ccc					user_data05 	/* �g���\��(?) (r33���ݖ��g�p) / */

/*---------------------------------------------------------
	�e�X�y�b�N
	�e�̔\�́A��Ԃ�����킷�B
	�`�悷��ꍇ�̃O���t�B�b�N�A�X���e�B��X���e�B�̋�ʁB
	�e���V�X�e���̂ǂ̃��C���[�ɏ�������e���̋�ʁB
---------------------------------------------------------*/

#if 1
	#define TAMA_SPEC_0000_TILT 				(0x0000)/* �X���e(�ʏ�e) */
	#define TAMA_SPEC_8000_NON_TILT 			(0x8000)/* ��X���e */		/* �X���Ȃ��e(��ʒe�A�`���m�e�A���p) */
	#define TAMA_SPEC_4000_GRAZE				(0x4000)/* �O���C�Y�ς݂��Ƃ����̃t���O */
	#define TAMA_SPEC_3000_EFFECT_MASK			(0x3000)/* �G�t�F�N�g�I�� */
	#define TAMA_SPEC_3000_EFFECT_NONE			(0x3000)/* �G�t�F�N�g�Ȃ� */
	#define TAMA_SPEC_2000_EFFECT_MINI			(0x2000)/* �G�t�F�N�g�� */
	#define TAMA_SPEC_1000_EFFECT_MIDDLE		(0x1000)/* �G�t�F�N�g�� */
	#define TAMA_SPEC_0000_EFFECT_LARGE 		(0x0000)/* �G�t�F�N�g��(��r34�݊�) */
#endif
	/*(CCW)*/
	#define TAMA_SPEC_0x0100_CCW_BIT 			(0x0100)
	/*(���`���m���E�̕ǂ�1�x��������)*/
	#define TAMA_SPEC_KABE_SAYUU_HANSYA_BIT 	(TAMA_SPEC_0x0100_CCW_BIT)
	/*(����̋Ȃ���N�i�C�A�e�A��]�����t���O)*/
	/*(�p�`�F�̃}�L�����[�|�C�Y���A��]�����t���O)*/
	/*(���~���A�A���f�u�u���h�E�c�F�y�V���̎􂢁v�A��]�����t���O)*/
	/*(���[�~�A�A�ŕ��u�f�B�}�[�P�C�V�����v�A��]�����t���O)*/
	#define TAMA_SPEC_KAITEN_HOUKOU_BIT 		(TAMA_SPEC_0x0100_CCW_BIT)
//	#define TAMA_SPEC_KAITEN_HOUKOU_0x0000_CW	(0x0000)
//	#define TAMA_SPEC_KAITEN_HOUKOU_0x1000_CCW	(TAMA_SPEC_0x0100_CCW_BIT)

#endif /* _HATSUDAN_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*---------------------------------------------------------
	���[�U�[�V�X�e��
---------------------------------------------------------*/

#ifndef _LASER_SYSTEM_H_
#define _LASER_SYSTEM_H_

/*
	�p�`�F�u�ʏ�U���v
	�t�����֊��u���[���@�e�C���v
	�t�����֒e�u�ߋ������ގ��v�v
	�����̃J�[�h����邩�ǂ����͕ʖ��Ƃ��āA�����̃��[�U�[�e��
	�V�X�e���őΉ��ł���悤�ɐ݌v���Ƃ��K�v������B
*/
enum
{
	LASER_TYPE_00_OFF		= 0, // LASER_TYPE_00_1_PACHE	= 0,	// 0==off, lz[0]==off�̏ꍇ�A����@�\�őS��off�B
	LASER_TYPE_01_4_PACHE,	/* 4�{�A�O���^�C�v(�p�`�F�u�ʏ�U���v�p) */
	LASER_TYPE_02_1_FRAN,	/* 1�{�A�^�C�v	  (�t�����֊��u���[���@�e�C���v�p) */
	LASER_TYPE_03_4_FRAN,	/* 4�{�A�����^�C�v(�t�����֒e�u�ߋ������ގ��v�v�p) */
	MAX_99_LASER_TYPE
};
enum
{
	LASER_00_ = 0,
	LASER_01_,
	MAX_99_LASER
	/*	2�e�H==�֊��u���[���@�e�C���v(�u�n�߁v�Ɓu�Ōォ�^��������v�̂ݔ��肪����΁A�c���S���ɔ��肪�Ȃ��Ă��債�ĕς��Ȃ��C������)
		8�e�H==�֊��u���[���@�e�C���v
		�Ō�łȂ��āA�^��������ɂ���͓̂�Փx�𒲐�����ׁB(�Ō�̕����኱���)
		�������Ȃ̂ŁA���ۂ́u���肬��œ������Ă�v�̂����ǁA���̏ꍇ�������ĂȂ����ɂ��������u���肬��œ�����Ȃ������v�Ƃ����z�B
		�Q�{�v�闝�R�́A�����ړ��L�����ŁA1�{�ڂł��蔲���Ă��A�Q�{�ڂɓ�����B
	 */
};
typedef struct _laser_
{
	int laser_type; 		/* ���[�U�[�̎�� / ����off�w��. LASER_TYPE */
	int laser_angle65536;	/* ���[�U�[�̊p�x */
} LASER;
extern LASER lz[MAX_99_LASER];
/* lz[0]==0;�̏ꍇ�A���ׂ�off�B(���[�U�[���[�h 0:off, 1:on) */

#endif /* _LASER_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _SPELL_SYSTEM_H_
#define _SPELL_SYSTEM_H_
/*
	�X�y���V�X�e��==�J�[�h�̊Ǘ��V�X�e���B(�J�[�h�V�X�e���Ƃ͈Ⴄ�̂Œ���)
*/

/*---------------------------------------------------------
	�X�y�������V�X�e��(�J�[�h�𐶐�)
---------------------------------------------------------*/

	/* �e��x256 �e��y256 �{�X���S���甭�e�B */
//#define set_REG_DEST_XY(aaa) {REG_02_SEND1_BOSS_X_LOCATE = (aaa->center.x256);	REG_03_SEND1_BOSS_Y_LOCATE = (aaa->center.y256); }
extern void set_REG_DEST_BOSS_XY(void);
extern OBJ_CALL_FUNC(set_REG_DEST_XY);
#if 0/*���ƂŗL���ɂ���*/
extern OBJ_CALL_FUNC(card_maikai_init);
extern OBJ_CALL_FUNC(card_generate);
#endif

/* HATSUDAN_R13_angle65536 �� ���@�_���e�̊p�x���v�Z */
extern CPU_FUNC(cpu_VR_angleCCW65536_src_nerai);

/* HATSUDAN_R13_angle65536 �� ���@�_���e�̊p�x���v�Z */
extern CPU_FUNC(calculate_boss_to_jiki_nerai);
extern CPU_FUNC(calculate_jiki_nerai);

/*---------------------------------------------------------
	(r36)�J�[�h�X�N���v�g�p����(multiprex_rate_vector)
	�������������B
---------------------------------------------------------*/
extern CPU_FUNC(multiprex_rate_vector);

/* �X�y����CPU���s���A�J�[�h���P�t���[����������B */
extern OBJ_CALL_FUNC(card_generate);

#endif /* _SPELL_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _CARD_SYSTEM_H_
#define _CARD_SYSTEM_H_

//------------ �J�[�h�֘A

extern void create_card(OBJ/**/ *src, int card_number);

//extern OBJ_CALL_FUNC(ch eck_regist_card);/* �J�[�h�̍X�V�`�F�b�N */
extern OBJ_CALL_FUNC(card_boss_move_generate_check_regist); /* �J�[�h�o�^�\�Ȃ�o�^ / �J�[�h���� */

// extern OBJ_CALL_FUNC(card_state_check_holding);/* �J�[�h���I���܂ő҂B */

enum
{
	DANMAKU_LAYER_00 = 0,	// (0)/* �e���R���g���[�����Ȃ��ʏ�e(��ʊO�Œe����) */
	DANMAKU_LAYER_01,		// (1)/* �e���R���g���[���O���[�v(1)�e */
	DANMAKU_LAYER_02,		// (2)/* �e���R���g���[���O���[�v(2)�e */
	DANMAKU_LAYER_03,		// (3)/* �e���R���g���[���O���[�v(3)�e */
	DANMAKU_LAYER_04_MAX/* �e���R���g���[���O���[�v�ő吔 */
};

typedef struct /*_card_global_class_*/
{
	void (*boss_spell_callback)(OBJ/**/ *sss);				/* �{�Xspell system���u���e�����v����(���s����(�J�[�h�C���^�v���^ / C����)���ʂ��̂ňꎞ�I�ɗv��BC�����S�Ĕp�~�ł���΁A�s�v�ɂȂ�) */
//	void (*boss_move_card_callback)(OBJ/**/ *sss);			/* �{�Xcard���u�ړ��v����(-r40) */
	void (*boss_move_card_callback_void)(void); 			/* �{�Xcard���u�ړ��v����(r41-) */
	int limit_health;		/* �K��l�ȉ��ɂȂ�� �J�[�h���[�h���� */
	int card_timer; 		/* [���p]�X�y�J�̐������� */
	//
	int address_set;		/* [���p]�J�[�h�A�h���X�ԍ� */
	int address_temporaly;	/* [�ꎞ�g�p]�J�[�h�A�h���X�ԍ� */
	int spell_used_number;	/* [�g�p���̃X�y���ԍ�] */
	int boss_hp_dec_by_frame;/* �{�X�U�������l�A�t���[���P�� */
	//
	void (*layer_callback[(DANMAKU_LAYER_04_MAX)])(OBJ/**/ *sss); /* �e�����C���[�A�R�[���o�b�N�V�X�e��(�X�y���ϐg����) */
	int tukaima_used_type;/*(�g�����V�X�e���A�g�����)*/
//	int tukaima_now_counts;/*(�g�����V�X�e���A)*/
//	int tukaima_add_interval;/*(�g�����V�X�e��)*/

} CARD_SYSTEM_GLOBAL_CLASS;
extern CARD_SYSTEM_GLOBAL_CLASS card;
//	/* ���l�ɂȂ�΃{�X���J�[�h���[�h�ɓ���Ȃ� */
//	void (*boss_sel ect_action_callback)(OBJ/**/ *sss); 	/* �{�Xcard���u�s���I���v���� */

/* �Ƃ肠���� */

//------------ "��"�݂����ȃ}�[�N�̃G�t�F�N�g
/* �u"��"�݂����ȃ}�[�N�v�́A�{�X�������Ă�J�[�h�������ł��B */
/*static*/extern OBJ_CALL_FUNC(move_card_square_effect);
/*static*/extern void boss_effect_kotei_obj_r36_taihi(void);

extern void game_core_danmaku_system_callback(void);
#endif /* _CARD_SYSTEM_H_ */
