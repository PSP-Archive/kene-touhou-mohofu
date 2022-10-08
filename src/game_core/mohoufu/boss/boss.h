
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
---------------------------------------------------------*/

#ifndef _BOSS_H_
#define _BOSS_H_

#include "game_main.h"
#include "card_address.h"
#include "./../tama/spell_name.h"
//------------ �J�[�h�֘A
//[�d��]#include "boss.h"//#include "card_address.h"
//[�d��]#include "boss.h"//#include "./../tama/spell_name.h"
//[�d��]#include "./../boss/card_address.h"//#include "spell_address.h"
//[�d��]#include "spell_name.h"

/*---------------------------------------------------------
	�J�[�h�ݒ�B
---------------------------------------------------------*/

/* �ڕW��ݒ肵�A�U���ړ� */
extern void boss_set_new_position_void(void);			/*(�U���ړ����W��ݒ�)*/
extern void boss_set_new_position_from_target(void);	/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/



extern OBJ_CALL_FUNC(add_zako_sakuya_doll_02_tama_oki);/* ��u���J�[�h */


/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_01_laser);/* ���[�U�[ */

/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_03_star);/* �q�������w(���^��`��) */
/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_04_360knife);/* �q�������w(360�i�C�t������) */
#endif /* _BOSS_H_ */

#ifndef _TUKAIMA_SYSTEM_H_
#define _TUKAIMA_SYSTEM_H_
extern OBJ_CALL_FUNC(tukaima_system_add_dolls);/*(�g�����V�X�e��)*/
//
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T01);
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T02);
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T03);
extern OBJ_CALL_FUNC(init_set_dolls_mima_T04);
extern OBJ_CALL_FUNC(init_set_dolls_sakuya_T05);	/* ��� �΂�T��2�e �I�v�V���� */
extern OBJ_CALL_FUNC(init_set_dolls_sakuya_T06);	/* ��� �΂�T��1�e �I�v�V���� */
extern OBJ_CALL_FUNC(init_set_dolls_alice_T07); 	/*(�ʏ�e)*/

enum
{
	/*00*/	TUKAIMA_00_OFF = 0,
	/*0a*/	TUKAIMA_01_,/*([���g�p])*/
	/*0b*/	TUKAIMA_02_,/*([���g�p])*/
	/*0c*/	TUKAIMA_03_,/*([���g�p])*/
			//
	/*05*/	TUKAIMA_04_sakuya_T04, /*(sakuya)*/
	/*06*/	TUKAIMA_05_sakuya_T05, /*(sakuya)*/
	/*08*/	TUKAIMA_06_aya_T06, /*(aya)*/
	/*0d*/	TUKAIMA_07_,/*([���g�p])*/
			//
	/*01*/	TUKAIMA_08_kaguya_T08, /*(kaguya)*/
	/*02*/	TUKAIMA_09_kaguya_T09, /*(kaguya)*/
	/*0e*/	TUKAIMA_0a_kaguya_sitakara_type04_hiroi,/*(kaguya)*/
	/*0f*/	TUKAIMA_0b_kaguya_sitakara_type05_hiroi,/*(kaguya)*/
			//
	/*03*/	TUKAIMA_0c_kaguya_sitakara_type06, /*(kaguya)*/
	/*09*/	TUKAIMA_0d_kaguya_uekara, /*(kaguya)*/
	/*04*/	TUKAIMA_0e_mima_T0e, /*(mima)*/
	/*07*/	TUKAIMA_0f_alice_T0f, /*(alice�ʏ�e)*/
	//
	TUKAIMA_10_MAX/*(�ő吔)*/
};
#if 1
/* [�g�������ʋK�i] */
/*[�g�p��]*/#define TUKAIMA_KIKAKU_00_target_x256					user_data00 	/* �ڕWx���W */
/*[�g�p��]*/#define TUKAIMA_KIKAKU_01_target_y256					user_data01 	/* �ڕWy���W */
//

//
// ���g�p�B #define BOSS_tuk aima_DATA_03_kougeki_anime_count			user_data03 	/* �U���A�j���[�V�����p�J�E���^ / 0�ȉ��Ȃ�ړ��A�j���[�V���� */
//
//
//�p�~	#define bo ss_spell_timer		user_data04 	/* �X�y���o�ߎ��� */
// VR10_BOSS_SPELL_TIMER �ֈڍs�B
#endif

#endif /* _TUKAIMA_SYSTEM_H_ */


#ifndef _CHUU_BOSS_H_
#define _CHUU_BOSS_H_

#define CHUU_BOSS_JIKAN_01_0256 (256)
#define CHUU_BOSS_JIKAN_02_0272 (272)
#define CHUU_BOSS_JIKAN_03_1792 (256+1024+512+512)
#define CHUU_BOSS_JIKAN_04_2048 (256+1024+512+512+256)

//#define YOKAI1_DATA_repeat			/*�p�~*/user_data04 	/* �J��Ԃ��� */
//#define YOKAI1_DATA_start_limit_y256	/*�p�~*/user_data05 	/* �o��y���W */
//#define yokai_type					/*�p�~*/user_data06 	/* �d���̎��(0 ... 3) */
	/* �J�n����J�[�h�ԍ� */

//
#define YOKAI1_DATA_s2					target_obj		/* OBJ *s2;*/

//enum /* _yokai_type_ */
//{
//	YOKAI_TYPE_00_RUMIA = 0,	/* 0:00 ���[�~�A */
//	YOKAI_TYPE_01_YOUKAI02, 	/* 1:32 "�d��2"(��) */
//	YOKAI_TYPE_02_YOUKAI01, 	/* 2:64 "�d��1"(��) */
//	YOKAI_TYPE_03_YOUKAI03		/* 3:96 "�d��3"(��) */
//};


#endif /* _CHUU_BOSS_H_ */
