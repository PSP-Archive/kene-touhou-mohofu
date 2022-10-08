
/* ���{�X���J�[�h���� */
#include "./../boss/boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�U�R�͓Z�߂�\��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�ݒ�
---------------------------------------------------------*/

	#define USE_X_HOUKOU (1)

/*---------------------------------------------------------
	�G�����ʋK�i
---------------------------------------------------------*/
#if 0/* �߂� */
/* �{�X���ʋK�i */
	#define target_x256 			user_data00 	/* �ڕWx���W */
	#define target_y256 			user_data01 	/* �ڕWy���W */
	#define boss_time_out			user_data02 	/* �������� */
	#define boss_base_state777		user_data02 	/* ��������(boss_time_out�Ɠ���) */
	#define kougeki_anime_count 	user_data03 	/* �U���A�j���[�V�����p�J�E���^ */
#endif


	/* �G�̌��� tmp_angleCCW1024 */
// user_data00: user_data01: ���W(x, y);	locate(x, y) == (user_data00, user_data01);
	#define zd00_target_x256				user_data00
	#define zd01_target_y256				user_data01
	#define zd00_clip_left256				user_data00
	#define zd01_clip_right256				user_data01
// user_data02: ���x256;		speed256 == radius256 == wait1 == user_data02
	#define zd02_system_speed256			user_data02/*([system�l]���x)*/
	#define zd02_radius256					user_data02
	#define zd02_zako_wait1 				user_data02 	/* [�����w]�J�E���^1 / [�Ζы�] �㉺�ɓ������J�E���^ */
// user_data03: �p�x256;		system_hoson_angle1024 == turnspeed1024 == px256 == start_y256
	#define zd03_system_hoson_angle65536 	user_data03/*([system�l]�ۑ��p�x)*/
	#define zd03_turnspeed65536				user_data03
	#define zd03_px256						user_data03 	/* ���zx�ʒu(���]�p) */
	#define zd03_start_y256 				user_data03
// user_data04: �񐔓�; 	system_hoson_speed256 == kaisu_nnn == zako_wait2 == max_y256 == KARASU3_houkou
	#define zd04_system_hoson_speed256		user_data04/*([system�l]�ۑ����x)*/
	#define zd04_kaisu_nnn					user_data04 	/* �J��Ԃ����񐔂̃J�E���^ / �^�[������� / �e������ */
	#define zd04_zako_wait2 				user_data04 	/* [�����w] �J�E���^2 */
	#define zd04_max_y256					user_data04
	#define zd04_KARASU3_houkou 			user_data04
// user_data05: �U���^�C�v
	#define zd05_kougeki_type				user_data05/*[regist_zako_011_kedama2 �D�ы�]*/

//#define zako_pattern_base 				user_data06 		/* �p�^�[���̊�ʒu�B�A�j������ꍇ�̃x�[�X */
#define zako_anime_rotate_angle65536 		user_data06/*zako_anime_base*/	/* �A�j����]�p�x1024 */

/*---------------------------------------------------------
	�U�����@
---------------------------------------------------------*/
enum
{
/*(16)0*/	/*(00)*/ZAKO_SPEKA_00_utanai  = 0,		/*[�����Ȃ��B]*/
/*(08)*/	/*(01)*/ZAKO_SPEKA_01_mahou_nerai,		/*[]*/
/*(17)1*/	/*(02)*/ZAKO_SPEKA_02_mahou_tate,		/*[�X�y�J02]�c�U���B*/
/*(18)2*/	/*(03)*/ZAKO_SPEKA_03_mahou_random, 	/*�΂�T���B*/
/*(15)3*/	/*(04)*/ZAKO_SPEKA_04_mahou_common, 	/*���U���B*/
/*(20)4*/	/*(05)*/ZAKO_SPEKA_05_mahou_right,		/*�E�U���B4:�~��U���̃J�[�h(����)[6: 7:]*/
/*(21)5*/	/*(06)*/ZAKO_SPEKA_06_mahou_left,		/*���U���B5:�~��U���̃J�[�h(���E)*/
/*(01)*/	/*(07)*/ZAKO_SPEKA_07_hai_kedama,		/*[�X�y�J07]�D�ыʂ̃J�[�h2*/
//
/*(30)*/	/*[08]*/ZAKO_SPEKA_08_hai_kedama,		/*[�X�y�J22]�D�ы�(?)*/
/*(09)*/	/*(09)*/ZAKO_SPEKA_09_inyou1,			/*[�X�y�J09]�A�z��*/
/*(10)*/	/*[10]*/ZAKO_SPEKA_10_midori1,			/*[�X�y�J10]�ы�(?)*/
/*(11)*/	/*(11)*/ZAKO_SPEKA_11_meido2,			/*[�X�y�J11]���C�h02*/
/*(12)*/	/*[12]*/ZAKO_SPEKA_12_kisume,			/*[�X�y�J12]�L�X��*/
/*(13)*/	/*[13]*/ZAKO_SPEKA_13_yukari,			/*[�X�y�J13]����̗􂯖ڒe*/
/*(14)*/	/*[14]*/ZAKO_SPEKA_14_obake1,			/*[�X�y�J14]覐�*/
/*(31)*/	/*[15]*/ZAKO_SPEKA_15_ao3_rendan,		/*[�X�y�J15]�d���A�A�e*/
//
/*(25)*/	/*[16]*/ZAKO_SPEKA_16_midori2,			/*[�X�y�J16]�Ζы�*/
/*(26)*/	/*[17]*/ZAKO_SPEKA_17_meido3,			/*[�X�y�J17]���C�h03*/
/*(29)*/	/*(18)*/ZAKO_SPEKA_18_karasu,			/*[�X�y�J18 <- 21]�J���X*/
/*(27)*/	/*(19)*/ZAKO_SPEKA_19_ao2,				/*[�X�y�J19]�d��*/
//
	ZAKO_SPEKA_99_MAX,
};
/*---------------------------------------------------------
	��-�{�X�G����
---------------------------------------------------------*/
/*extern*/static OBJ_CALL_FUNC(item_create_15_rumia)
{
	const u8 item_tbl[4] =
	{
		(SP_ITEM_02_P128&0xff), 	/* [F] */
		(SP_ITEM_01_P008&0xff), 	/* [P]�� */
		(SP_ITEM_00_P001&0xff), 	/* [p]�� */
		(SP_ITEM_05_TENSU&0xff),	/* [�_] */
	};
	item_create_flags_num(src, /*item_type*/(OBJ_Z03_ITEM|(item_tbl[(cg_VR20_game_difficulty)])), (7), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
	/* ����΂� */
}
/*extern*/static OBJ_CALL_FUNC(item_create_14_yokai)
{
	item_create_flags_num(src, SP_ITEM_05_TENSU, (7), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
	/* ����΂� */	/* �_�����o�� */
}
/*---------------------------------------------------------

---------------------------------------------------------*/

/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_00_item)	{item_create_mono(src, SP_ITEM_00_P001	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_01_item)	{item_create_mono(src, SP_ITEM_01_P008	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_02_item)	{item_create_mono(src, SP_ITEM_02_P128	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_03_item)	{item_create_mono(src, SP_ITEM_03_1UP	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_04_item)	{item_create_mono(src, SP_ITEM_04_BOMB	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_05_item)	{item_create_mono(src, SP_ITEM_05_TENSU );}//static void item_create_018_meido4
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_06_item)	{item_create_mono(src, SP_ITEM_06_HOSI	);}
#define item_create_07_item item_create_random_table


/*---------------------------------------------------------
	�U�R�G����
---------------------------------------------------------*/

static OBJ_CALL_FUNC(zako_shot_supeka);/*(�錾)*/

/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_002_inyou_zako)
{
	if (0==((src->center.x256)&( 8-1))) /*�m���グ���B[1/8]��[1/20]*/ /*%20*/
	{
		zako_shot_supeka(src);
	}
	else
	{
	//	item_create_mono(src, (SP_ITEM_00_P001+(replay_rand()&1)) );
		item_create_mono(src, (SP_ITEM_00_P001+((src->center.x256)&1)) );
	}
}


/*---------------------------------------------------------
	�U�R�̍U�����@�͓Z�߂�ׂ�
---------------------------------------------------------*/


/*---------------------------------------------------------
	������p�~�܂�e
	-------------------------------------------------------
	�S�e�������������Ɉڍs����̂ł����͖����Ȃ�\��B
---------------------------------------------------------*/
/*---------------------------------------------------------
	�x�N�g���e(��{�I�ɂ́A�p�x�ω����Ȃ��e)
---------------------------------------------------------*/

#define BASE_add_speed256			user_data00 	/* ������ */
#define TOKUSYU_DAN_DATA_delta256	user_data01 	/* ���������� */




#define TOMARI_DAN_LIMIT_00_MAX 	(512+384)	/* �K���ɑ傫��1024==(512+64+�ő��~����) */
#define TOMARI_DAN_LIMIT_01_512 	(512)
#define TOMARI_DAN_LIMIT_02_032 	(32+0+0)

static OBJ_CALL_FUNC(bullet_move_douchu_tomari_dan)
{
	if (TOMARI_DAN_LIMIT_01_512 < src->jyumyou)/* 513 ... MAX */
	{
		/* �~�܂� */
	//	src->BASE_add_speed256 -= (1);
		src->BASE_add_speed256 -= (src->TOKUSYU_DAN_DATA_delta256);
		if (src->BASE_add_speed256 < t256(0))
		{
			src->BASE_add_speed256 = t256(0);
			src->jyumyou = (TOMARI_DAN_LIMIT_01_512);
		}
	}
	else
	if (TOMARI_DAN_LIMIT_02_032 < src->jyumyou)/* 33 ... 512 */
	{
		;	/* ���΂���~ */
	}
	else/* 0 ... 32 */
	{
		/* ������ */
		src->color32 -= 0x10000000; 		/*	src->alpha -= 0x10; */
		if (0x20000000 > src->color32)		/*	(0x20 > src->alpha) */
		{
			src->color32 = 0x00ffffff;		/*	src->alpha = 0x00;	*/
			src->jyumyou = JYUMYOU_NASI;
		}
	}
	//
	src->center.y256 += t256(1.0);	/* ������p�e�Ȃ̂ŃX�N���[������ */
	//
//	move_bullet_vector(src);
	if (t256(1.00)!=(src->BASE_add_speed256))
	{
		#if (0)
	//	src->math_vector.x256 = ((src->math_vector.x256*src->BASE_add_speed256)>>8);/* ����/���� */ // ���̏ꍇ�_���B
		#else
		const int vx256_speed = (src->math_vector.x256*src->BASE_add_speed256);
		if (0 < vx256_speed) /* ���̏ꍇ */
		{
			src->math_vector.x256 = ((vx256_speed)>>8);/* ����/���� */
		}
		else /* ���̏ꍇ */
		{
			src->math_vector.x256 = -((-vx256_speed)>>8);/* ����/���� */
		}
		#endif
		//
		#if (1)/* ���e���������ĂȂ��̂�... */
		src->math_vector.y256 = ((src->math_vector.y256*src->BASE_add_speed256)>>8);/* ����/���� */ // ���̏ꍇ�_���B
		#else
		const int vy256_speed = (src->math_vector.y256*src->BASE_add_speed256);
		if (0 < vy256_speed) /* ���̏ꍇ */
		{
			src->math_vector.y256 = ((vy256_speed)>>8);/* ����/���� */
		}
		else /* ���̏ꍇ */
		{
			src->math_vector.y256 = -((-vy256_speed)>>8);/* ����/���� */
		}
		#endif
	}
	src->center.x256 += (src->math_vector.x256);	/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);	/*fps_factor*/
}

/*---------------------------------------------------------
	�e��o�^����B
	-------------------------------------------------------
	�e�������̃G�t�F�N�g���̊֌W��A���e�����͑S���Z�߂�K�v������B
	-------------------------------------------------------
	�x�N�g���e�Ɗp�x�e�𓝍����邩������Ȃ��B
	-------------------------------------------------------
	ToDo:
	�e�V�X�e���Ɉڍs����ׁA�p�~�\��B
	�J�[�h�X�N���v�g�V�X�e�����ғ�����ׂɂ́A���e���ꃖ���ɓ������Ȃ���
	���x�I�Ȗʂł��̂܂܂̌`�Ԃł͖���������̂ŁA
	(�����̔��e�����̂����ő��̒e��������������)
	�����̔��e������ hatudan_system_regist_single �ɒu��������K�v������B
---------------------------------------------------------*/
/* �x�N�g������e(���A�ڍs�`��) */

//	#define hatudan_system_kousadan_angle65536 tmp_angleCCW1024
	#define hatudan_system_kousadan_angle65536 tmp_angleCCW65536


static OBJ_CALL_FUNC(bullet_regist_douchu_vector_tomari_dan)
{
	OBJ *h;
	h											= obj_regist_tama();/* ���e�o�^ */
	if (NULL != h)/* �o�^�ł����ꍇ */
	{
		//[67?]
		h->center.x256							= VR06;/* ���e�ʒu ���Wx */
		h->center.y256							= VR07;/* ���e�ʒu ���Wy */
	//	h->center.x256							= VR07;/* ���e�ʒu ���Wx */
	//	h->center.y256							= VR06;/* ���e�ʒu ���Wy */
		h->obj_type_set 						= (HATSUDAN_R15_bullet_obj_type);
		reflect_sprite_spec(h, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
		//
		mask65536(HATSUDAN_R13_angle65536);
		h->hatudan_system_kousadan_angle65536	= (HATSUDAN_R13_angle65536);
		h->m_Hit256R							= TAMA_ATARI_MARU16_PNG;
		//
		/*angle512								= angle_jikinerai512_auto(obj_player, src, angle512);*/
	//	VR09							= (HATSUDAN_R11_speed256);
	//	ang le_to_vector(h);
		//------------------/*(�p�x��X���AY���̃x�N�g�����x�֕ϊ�����)*/
	//	HATSUDAN_R11_speed256	= (HATSUDAN_R11_speed256);
	//	HATSUDAN_R13_angle65536 = (h->hatudan_system_kousadan_angle65536);
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		h->math_vector.x256	= VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		h->math_vector.y256	= VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
		//
		// [���K�V�[�V�X�e���Ή�]
		h->TR00_hatudan_spec_data			= (0);/*(r35���K�V�[�V�X�e�����ŁA�g��Ȃ��Ă��A�e���V�X�e�����Ŏg���̂ł����Őݒ肷��K�v������B)*/
		//
		/* �Ƃ肠�����A�e�L�g�[ */
	//	h->BASE_add_speed256					= (t256(1.00)); 	/* ����/�����A�Ȃ� */
		h->BASE_add_speed256					= 1+(t256(1.00));	/* ���� �e */
		//
		h->TOKUSYU_DAN_DATA_delta256			= (HATSUDAN_R12_speed_offset);
		h->jyumyou								= (TOMARI_DAN_LIMIT_00_MAX);
		h->callback_mover						= bullet_move_douchu_tomari_dan;
	}
}


/*---------------------------------------------------------
	�U�R�̍U�����@�͓Z�߂�ׂ�
8 1.00
7 0.50
6 0.25
5 0.125
---------------------------------------------------------*/
typedef struct /*aa*/
{
	int SR15_bullet_obj_type;	// HATSUDAN_R15_bullet_obj_type
	s32 SR14_nan_ido_kankaku;/*(�؂��)*/
	s32 SR11_nan_ido_speed64;	// HATSUDAN_R11_speed256
	s32 SR16_nan_ido_n_way; 	// HATSUDAN_R16_n_way
	s32 SR17_div_angle65536;	// HATSUDAN_R17_div_angle65536
} ZAKO_SPELL_RESOURCE;
static ZAKO_SPELL_RESOURCE kougeki_tbl[(ZAKO_SPEKA_99_MAX)] =
{
	/*
	-------------------------------------------------------
	(r41-)���e�� 16[frame] �� 3�{���ړ�����l�ɁA�V�X�e����ύX�����B
	psp�̉�ʂ͋����̂ŁA�G���e�̒e�� t256(2.00) �ȏ�̓Q�[�����j�]����B
	(�����e�͔��������ɉ�ʊO�֏o��B)
	������ t256(2.00) �ȏ�͊�{�I�ɔp�~����B(t64�͈͍̔͂ő� t64(3.99���炢) �܂�)
	-------------------------------------------------------
	�����I�� �X�y�JCPU �� �G���̓��������e���s���̂ŁA
	�������炱���͍ŏI�I��(BOSS��)�X�y�J�Ɠ��������ׂ��C������B
	-------------------------------------------------------
	*/
//(-r40)/*(���g�p)*/{(BULLET_KOME_BASE),						PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x07, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.375), t64(1.500), t64(1.625)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((8), (8), (4), (9)), PACK_NAN_IDO_CONST(( 6), ( 8), ( 8), (16))},	/* ZAKO_SPEKA_04_mahou03[e] 8:�����e(���ʒe�Ȃ̂œ�Փx�͒Ⴂ��) */

	/* 0:�g���ۂ��ы�(���p�x ��e) t256(2.5)		  (r41-)				(-r40)	*/
/*(16)0*/	/*(00)*/{(0),/*(�����Ȃ�)*/ 						PACK_NAN_IDO_CONST(0x01, 0x01, 0x01, 0x01), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*0,		  */PACK_NAN_IDO_CONST((1), (1), (1), (1)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_00_utanai-*/
/*(08)*/	/*(01)*/{(BULLET_MINI8_BASE + TAMA_IRO_03_AOI), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.500), t64(0.500), t64(0.500), t64(0.500)), 		/*t256(0.500),*/PACK_NAN_IDO_CONST((1), (1), (1), (2)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_01_mahou_nerai */ 		// 6 -	// [�����w 3/�͗d��1:�����_���΂�܂��U��+���@�_��("�����w1")�̃J�[�h]
/*(17)1*/	/*(02)*/{(BULLET_KOME_BASE + TAMA_IRO_01_AKA),		PACK_NAN_IDO_CONST(0x01, 0x01, 0x01, 0x01), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((2), (2), (6),(12)), PACK_NAN_IDO_CONST(( 2), ( 2), ( 6), (12))},	/* ZAKO_SPEKA_02_mahou_tate */			// 6 7	// [�����w 1:�c�U���̃J�[�h]
/*(18)2*/	/*(03)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.750), t64(1.750), t64(1.750), t64(1.750)), 		/*t256(2.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 4), ( 4), ( 4), ( 4))},	/* ZAKO_SPEKA_03_mahou_random */		// . .	// [�����w 2:�����_���΂�܂��U��("�����w2")�̃J�[�h]
/*(15)3*/	/*(04)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((4), (4), (4), (5)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_04_mahou_common */		//		// [�����w �Ƃ肠�������ʕ���]
/*(20)4*/	/*(05)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_05_mahou_right */ 		//		// [�����w �Ƃ肠�������ʕ���]
/*(21)5*/	/*(06)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_06_mahou_left */			//		// [�����w �Ƃ肠�������ʕ���]
/*(01)*/	/*(07)*/{(BULLET_KOME_BASE),/*(�D�ы�)*/			PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x0f, 0x07), PACK_NAN_IDO_CONST(t64(1.250), t64(1.375), t64(1.500), t64(1.625)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((5), (3), (3), (7)), PACK_NAN_IDO_CONST(( 9), (12), (12), (12))},	/* ZAKO_SPEKA_01_utanai[e] (u32)(1024/12):�L�p�Ȃ̂ŊȒP */
					//
/*(30)*/	/*(08)*/{(BULLET_KOME_BASE),/*(�D�ы�slow)*/		PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x07, 0x03), PACK_NAN_IDO_CONST(t64(0.500), t64(0.500), t64(0.500), t64(0.500)), 		/*t256(0.500),*/PACK_NAN_IDO_CONST((3), (5), (7), (9)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_08_hai_kedama */ 			// . 7	// [ �ы�1�̃J�[�h]
/*(09)*/	/*(09)*/{(BULLET_HARI32_01_AKA),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(2.000), t64(2.000), t64(2.000), t64(2.000)), 		/*t256(2.500),*/PACK_NAN_IDO_CONST((7), (7), (9),(13)), PACK_NAN_IDO_CONST((12), (18), (24), (28))},	/* ZAKO_SPEKA_09_inyou1 */				// 6 7	// [�j�e]
/*(10)*/	/*(10)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.375), t64(1.375), t64(1.375), t64(1.375)), 		/*t256(1.375),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_10_midori1 */ 			// 6 -	// [�Ζы�1/���C�h1 �̃J�[�h]
/*(11)*/	/*(11)*/{(BULLET_HARI32_00_AOI),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(2.000), t64(2.000), t64(2.000), t64(2.000)), 		/*t256(2.500),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_11_meido2 */				// 6 -	// [ ���C�h2�̃J�[�h]
/*(12)*/	/*(12)*/{(BULLET_MINI8_BASE + TAMA_IRO_07_DAI_DAI), PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_12_kisume */ // 6 -	// [ �L�X��1�̃J�[�h]
/*(13)*/	/*(13)*/{(BULLET_MINI8_BASE + TAMA_IRO_07_DAI_DAI), PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.750), t64(0.750), t64(0.750), t64(0.750)), 		/*t256(0.750),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_13_yukari */				// 6 -	// [ ���ґ�2�̃J�[�h]
/*(14)*/	/*(14)*/{(BULLET_KNIFE20_04_AOI),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.625), t64(0.625), t64(0.625), t64(0.625)), 		/*t256(0.625),*/PACK_NAN_IDO_CONST((1), (1), (3), (7)), PACK_NAN_IDO_CONST((12), (18), (18), (18))},	/* ZAKO_SPEKA_14_obake1 */				// . 7	// [���΂�1 �̃J�[�h]
/*(31)*/	/*[15]*/{(BULLET_MINI8_BASE),/*(�A�e)*/ 			PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((7), (7), (7), (9)), PACK_NAN_IDO_CONST(( 8), (12), (16), (24))},	/* ZAKO_SPEKA_15_ao3_rendan */			// 6 -	// [ �d��2�̃J�[�h]
					//
/*(25)*/	/*(16)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.500), t64(1.500), t64(1.500), t64(1.500)), 		/*t256(1.500),*/PACK_NAN_IDO_CONST((1), (2), (3), (3)), PACK_NAN_IDO_CONST((12), (48), (48), (48))},	/* ZAKO_SPEKA_16_midori2 */ 			// . 7	// [�Ζы�2 �̃J�[�h]
/*(26)*/	/*[17]*/{(BULLET_UROKO14_BASE + TAMA_IRO_01_AKA),	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (2), (4), (7)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_17_meido3 */				// . 7	// [ ���C�h3�̃J�[�h]
/*(29)*/	/*(18)*/{(BULLET_KUNAI12_BASE), 					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((8), (8), (8), (9)), PACK_NAN_IDO_CONST(( 8), ( 8), ( 8), ( 8))},	/* ZAKO_SPEKA_18_karasu */				// 6 7	// [ �d��3/�G1�̃J�[�h]
/*(27)*/	/*(19)*/{(BULLET_UROKO14_BASE + TAMA_IRO_03_AOI),	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (5)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_19_ao2 */ 				// . 7	// [ �d��1/�d��4�̃J�[�h(B)]
	//
};

	#if 0/*(�Ă���)*/
	if (0==(cg_VR20_game_difficulty))
	{
		return;
	}
	#endif

static OBJ_CALL_FUNC(zako_shot_supeka)
{
	const void *aaa[(ZAKO_SPEKA_99_MAX)] =
	{
/*(16)0*/		/*(00)*/&&COMMON_JIKI_NERAI,				// mahoujin00 ZAKO_SPEKA_10_aaa [���g�p]�̃J�[�h	/* �U�����Ȃ� */
/*(08)*/		/*(01)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_01_mahou_nerai	�����w 3:�����_���΂�܂��U��+���@�_��("�����w1")�̃J�[�h
/*(17)1*/		/*(02)*/&&label_ZAKO_SPEKA_02_mahou_tate,	// mahoujin01 ZAKO_SPEKA_02_mahou_tate �����w 1:�c�U���̃J�[�h
/*(18)2*/		/*(03)*/&&label_ZAKO_SPEKA_03_mahou_random, // mahoujin02 ZAKO_SPEKA_03_mahou_random �����w 2:�����_���΂�܂��U��("�����w2")�̃J�[�h	/* �΂�܂� #01(�������A��"�����w2") */
/*(15)3*/		/*(04)*/&&label_ZAKO_SPEKA_04_mahou_common, // ZAKO_SPEKA_04_mahou_common �����w �Ƃ肠�������ʕ���
/*(20)4*/		/*(05)*/&&label_muki_mahou_right,			// mahoujin04 ZAKO_SPEKA_05_mahou_right �̃J�[�h	/* 8way�Ԓe(��) */
/*(21)5*/		/*(06)*/&&label_muki_mahou_left,			// mahoujin05 ZAKO_SPEKA_06_mahou_left �̃J�[�h /* 8way�Ԓe(��) */
/*(01)*/		/*(07)*/&&label_ZAKO_SPEKA_07_haikedama,	// ZAKO_SPEKA_07_hai_kedama �D�ы� �̃J�[�h2
						//
/*(30)*/		/*(08)*/&&COMMON_JIKI_NERAI_p_cx,			// ZAKO_SPEKA_08_hai_kedama		�̃J�[�h
/*(09)*/		/*(09)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_09_inyou1 		�A�z��1 �̃J�[�h [�j�e]
/*(10)*/		/*(10)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_10_midori1		�Ζы�1 �̃J�[�h
/*(11)*/		/*(11)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_11_meido2 		�̃J�[�h
/*(12)*/		/*(12)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_12_kisume 		�L�X�� �̃J�[�h
/*(13)*/		/*(13)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_13_yukari 		�̃J�[�h
/*(14)*/		/*(14)*/&&COMMON_MULTI_VECTER,				// ZAKO_SPEKA_14_obake1 		���΂�1 �̃J�[�h
/*(31)*/		/*[15]*/&&label_ZAKO_SPEKA_15_ao3_rendan,	// ZAKO_SPEKA_15_ao3_rendan 	�̃J�[�h
						//
/*(25)*/		/*(16)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_16_midori2 		�Ζы�2 �̃J�[�h
/*(26)*/		/*[17]*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_17_meido3 		�̃J�[�h
/*(29)*/		/*(18)*/&&COMMON_JIKI_NERAI_p_cx,			// ZAKO_SPEKA_18_karasu 		�̃J�[�h
/*(27)*/		/*(19)*/&&label_ZAKO_SPEKA_19_ao2,			// ZAKO_SPEKA_19_ao2			�̃J�[�h
		//
	};
	s32 zako_supeka_type;
	zako_supeka_type = (src->zd05_kougeki_type);
	zako_supeka_type = psp_min(zako_supeka_type, (ZAKO_SPEKA_99_MAX-1));//	if (ZAKO_SPEKA_99_MAX < zako_supeka_type)	{zako_supeka_type = 0;}//	zako_supeka_type &= 0x1f;/*(�O�̈�)*/
	//-------------------------
	HATSUDAN_R15_bullet_obj_type	= kougeki_tbl[(zako_supeka_type)].SR15_bullet_obj_type;
	VR11							= kougeki_tbl[(zako_supeka_type)].SR11_nan_ido_speed64;	// speed64�͓�Փx�ʂɐݒ�B
	VR14							= kougeki_tbl[(zako_supeka_type)].SR14_nan_ido_kankaku;	// speed64�͓�Փx�ʂɐݒ�B/*(�؂��)*/
	HATSUDAN_R16_n_way				= kougeki_tbl[(zako_supeka_type)].SR16_nan_ido_n_way;	// n_way�͓�Փx�ʂɐݒ�B
	HATSUDAN_R17_div_angle65536 	= kougeki_tbl[(zako_supeka_type)].SR17_div_angle65536;	// �����p�x�͓�Փx�ʂɐݒ�B
	//-------------------------
	static const u32 codebase000[6] =
	{
		// (1)	VR11 = ��Փx�ʒ萔; HATSUDAN_R11_speed256 t64();
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R11, R11),
		// (2)	VR14 = ��Փx�ʒ萔; VR14(�؂��)
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R14, R14),
		// (3)	VR16 = ��Փx�ʒ萔1; HATSUDAN_R16_n_way
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R16, R16),
		// (4)	VR17 = ��Փx�ʒ萔2; HATSUDAN_R17_div_angle65536
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R17, R17),
		// (5)	VR17 = 65536 / VR17;
		MCODE(OP0x17_DIV65536, NAX, R17, R17),
		// (6)	HATSUDAN_R11_speed256 <<= 2;/*�ϊ� t256() <- t64(); */
		MCODE(OP0x1f_ASLM_PD, (2), R11, R11),/*(�V���[�g�������A�h���b�V���O)*/
		// (7)
	//	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase000, (6));//
	//-------------------------
	// �Q�[�������N�Ŕ������B(����x�ł͂ǂ��������Ă����ƒe��������������ʓ��̒e���������ăQ�[�����ȒP�ɂȂ�)
	HATSUDAN_R11_speed256	+= ((cg_game_rank)>>8);/*([1-6�ʂ܂Ńm�[�~�X�Ƃ���]�ő�ł�2�{�����x�ɂ����Ȃ�Ȃ�)*/
	//-------------------------
	//
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
	//
	goto *aaa[(zako_supeka_type)/*& 0x1f*/];
label_ZAKO_SPEKA_07_haikedama:
	//static void zako_spell_01_hai_kedama(OBJ/**/ *src, u8 zako_supeka_type)
		//	zako_supeka_type -= (ZAKO_SPEKA_18_hai_kedama);
		//	zako_supeka_type &= (0x07);
		if (0==(src->jyumyou & VR14/*(�؂��)*/))/*0x0f*/ //kougeki_tbl[(zako_supeka_type & 0x07)].kankaku
		{
			HATSUDAN_R15_bullet_obj_type			= BULLET_KOME_BASE + (src->center.x256 & 0x07);
			goto COMMON_JIKI_NERAI;
		}
	//	else	{goto EXIT_ZAKO_SPEKA;}
		goto EXIT_ZAKO_SPEKA;
//-------------------------
		//	attack_kougeki_mahoujin_common(src);
//-------------------------
label_muki_mahou_left:
		HATSUDAN_R13_angle65536 						= (((-(src->jyumyou+src->jyumyou)+((src->jyumyou&0x07)<<7)))<<6);	/* ���� */
		goto label_ZAKO_SPEKA_04_mahou_common;
label_muki_mahou_right:
		HATSUDAN_R13_angle65536 						= ((( (src->jyumyou+src->jyumyou)+((src->jyumyou&0x07)<<7)))<<6);	/* ���� */
	//	goto label_ZAKO_SPEKA_04_mahou_common;
label_ZAKO_SPEKA_04_mahou_common:	// [�����w �Ƃ肠�������ʕ���]
	//	HATSUDAN_R13_angle65536 						= (int)(65536/(7)); 						/* �p�x(����� 7 ����) */	/* 1����n���������p�x */
		HATSUDAN_R12_speed_offset						= (1);//t256(0.03); 						/* �����萔 */
		goto COMMON_LEGACY_DIRECT;

label_ZAKO_SPEKA_03_mahou_random:	// [�����w 2:�����_���΂�܂��U��("�����w2")�̃J�[�h]
		/* ���x�� 1.0-3.0�܂ł̖��i�K�����ɕύX */
		HATSUDAN_R11_speed256							+= ((ra_nd()&(512-1))); 	/* �e�� */
		HATSUDAN_R13_angle65536 						= ((ra_nd()&(65536-1)));					/* �p�x */
		HATSUDAN_R12_speed_offset						= (2);//10.24==t256(0.04);					/* �����萔 */
		goto COMMON_LEGACY_DIRECT;
//------------------------- �Œ�e
label_ZAKO_SPEKA_02_mahou_tate: 	// [�����w	1:�c�U���̃J�[�h]
		HATSUDAN_R13_angle65536 						= (int)(65536/(4)); 		/* �E����(�㉺�e)�A�����e�Ȃ̂Ō��ʓI�ɏ㉺�e�B */
//		HATSUDAN_R15_bullet_obj_type					= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* �ԕĒe */
//		HATSUDAN_R16_n_way								= (2);						/* [2way] */
//		HATSUDAN_R17_div_angle65536 					= (int)(65536/(2)); 		/* �p�x(����� 2 ����) */	/* 1����n���������p�x */
		goto COMMON_MULTI_VECTER;


//------------------------- �A�e
/*
	-------------------------------------------------------
	R0c 	�o���Ƃ��p�x�Baaa_angle65536
*/
label_ZAKO_SPEKA_15_ao3_rendan: 	// [ �d��2�̃J�[�h]
	{
		static /*const*/ u32 codebase_exec[19] =
		{
			// (1)	 (calculate_jiki_nerai); /* ���@�_���e�����B */
			MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
			// (2)	VR0c = VR13;/*(���@�_���p�x���o���Ƃ�)*/
			MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		//	static const u16 bunkatsu65536_tbl[4] =
		//	{((int)(65536/8)), ((int)(65536/12)), ((int)(65536/16)), ((int)(65536/24))};
		//	HATSUDAN_R16_n_way							= (7);									/* [7way] */
		//	HATSUDAN_R17_div_angle65536 				= (bunkatsu65536_tbl[((cg_VR20_game_difficulty))]); 	/* �����p�x */
			// (3) HATSUDAN_R12_speed_offset					= t256(3/*6*/);/*(�e�X�g)*/
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
			(t256(3/*6*/)),/*(�e�X�g)*/
			//		HATSUDAN_R14_tama_spec						= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			// (4)	HATSUDAN_R14_tama_spec						= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
			((DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			/* �~�j�e�̘A�e */
			// (5)	VR03_i = 8;/*(8 �񃋁[�v���Ēǉ�)*/ /*8 6(4)*/
			MCODE(OP0x1c_MOVEM_PD, (8), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		//loop_i;// (ddd-11)loop_i:;
			//	/*[r35�v������]*/HATSUDAN_R11_speed256		= (t256(2.5)+(VR03_i<<6));		/* �e�� */
			//	/*[r35������]*/HATSUDAN_R11_speed256		= (t256(1.25)+(VR03_i << 5));	/* �e�� */
			// (6)	VR11 = (VR03_i << 4);// VR11 = (VR03_i << 5);
			MCODE(OP0x1f_ASLM_PD, 0x04, R11, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
			// (7)	VR11 += (t256(1.25));
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
			(t256(0.75)),		//	(t256(1.25)),
			// (8) HATSUDAN_R13_angle65536				= VR0c;/*(�o���Ƃ������@�_���p�x���g��)*/
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
			//	HATSUDAN_R15_bullet_obj_type			= ((BULLET_MINI8_BASE + TAMA_IRO_01_AKA)+(/*0*/6-VR03_i/*�Ƃ肠����*/)); /* [ �e] */
			// (9) VR15 = VR03_i;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R03_i),
			// (10) VR15 = (VR00 + 8 - VR15);
			MCODE(OP0x05_SUBR_PD, (8), R15, R00),/*(�[�����W�X�^�g�p)*/
			// (11)  VR15 += (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			((BULLET_MINI8_BASE + TAMA_IRO_01_AKA)),
			// (12)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
			// (13) VR03_i--;/*(�c��񐔌��炷�B)*/
			MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
			// (14) if (0 != (s32)VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/ if (0 < (s32)VR03_i) {goto loop_i;}
			MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-11)),//	(ddd-11)loop_i:;
		//(osimai+14:)//(osimai+32:)// �����܂�
			// (15)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
		};
		cpu_exec((u32*)&codebase_exec, (15+6*11));/*(�e�L�g�[)*/
	}
	goto EXIT_ZAKO_SPEKA;
//-------------------------
	COMMON_LEGACY_DIRECT:
		bullet_regist_douchu_vector_tomari_dan(src);/*(�G���ł͂����ȊO����)*/
		goto EXIT_ZAKO_SPEKA;
	//
//------------------------- ���@�_��
	COMMON_JIKI_NERAI_p_cx:
		HATSUDAN_R15_bullet_obj_type					+= (src->center.x256 & 0x07);
		goto COMMON_JIKI_NERAI;

label_ZAKO_SPEKA_19_ao2:	// [ �d��1/�d��4�̃J�[�h(B)]
		HATSUDAN_R17_div_angle65536 					-= ((cg_VR20_game_difficulty)<<6);	/* �����p�x */
	//	goto COMMON_JIKI_NERAI;
		/*(not_break;)*/
	COMMON_JIKI_NERAI:
		CPU_CALL(calculate_jiki_nerai);
		/*(not_break;)*/
	COMMON_MULTI_VECTER:
	//	HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= (2);/*(�Ƃ肠����)*/
	//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
/*(�����e�p�J�n)*/HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/* (r42-) */
		//	goto EXIT_ZAKO_SPEKA;
	EXIT_ZAKO_SPEKA:
			;
}



/*---------------------------------------------------------
	�U�R�ړ����ʁA�������ړ������B
	-------------------------------------------------------
	���x: src->zd02_system_speed256�B�G���o�^���Ɏ����ݒ���g�p����B
	�p�x: src->tmp_angleCCW1024�B	 �G���o�^���Ɏ����ݒ���g�p����B
	-------------------------------------------------------
---------------------------------------------------------*/
#if 0
�܂肽���o�ꂷ�邾���ŁA�������ʂȏ��������Ȃ��A
�������ړ�����G���Ȃ�A����Ȋ����B
static OBJ_CALL_FUNC(move_zako_sample)
{
	if (JYUMYOU_ZAKO_HASSEI -byou60(3) > src->jyumyou)/*(��������3[�b]�ȏ�o�߂����G������ʊO�Ȃ�Ώ���)*/
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type01(src);/*(���C�h���ʁA�A�j���[�V����)*/
}
#endif

static OBJ_CALL_FUNC(zako_system_move_vector)
{
	//------------------
	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
	HATSUDAN_R13_angle65536 = (src->tmp_angleCCW65536);
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	src->center.x256 += VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	src->center.y256 += VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
}

#if 0/*(����)*/
	#if (0)//
	src->center.x256 += ((si n1024((src->tmp_angleCCW1024))*(src->zd02_system_speed256))>>8);/*fps_factor*/ /* CCW�̏ꍇ */
	src->center.y256 += ((co s1024((src->tmp_angleCCW1024))*(src->zd02_system_speed256))>>8);/*fps_factor*/
	#else
	{
		int sin_value_t256; 	//	sin_value_t256 = 0;
		int cos_value_t256; 	//	cos_value_t256 = 0;
		int256_sin cos65536(src->tmp_angleCCW65536, &sin_value_t256, &cos_value_t256);
		src->center.x256 += ((sin_value_t256*(src->zd02_system_speed256))>>8);/*fps_factor*/
		src->center.y256 += ((cos_value_t256*(src->zd02_system_speed256))>>8);/*fps_factor*/
	}
	#endif
#endif

/*---------------------------------------------------------
	�U�R�A�j������
---------------------------------------------------------*/
/* 0000 0100 0000 0000 = 0x0400 = 1024 */
/* 0000 0011 1--- ---- */
static OBJ_CALL_FUNC(zako_anime_type_99_rotate)
{
	src->rotationCCW65536 += (src->zako_anime_rotate_angle65536);/*�O����]*/
	mask65536(src->rotationCCW65536);
}
static OBJ_CALL_FUNC(zako_anime_type01)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
	//	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW1024)&(1024-1)))>>7);
	//	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW1024)&(0x0380)))>>7);
	///	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW65536>>6)&(0x0380)))>>7);/*r42�Ƃ肠����*/
		src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW65536)&(0x0380<<6)))>>(6+7));/*r42�Ƃ肠����*/
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type02)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x03)) + ((src->jyumyou>>2)&(4-1));
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type05)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x03)) + ((src->jyumyou>>4)&(4-1));
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type03)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x01)) + ((src->jyumyou&0x10)>>4);
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type04)
{
	src->rotationCCW65536 += (src->zako_anime_rotate_angle65536);/*�O����]*/
	mask65536(src->rotationCCW65536);
}


/*---------------------------------------------------------

---------------------------------------------------------*/
#include "zako_move.h"					/* �G���ړ�/�o�^ */

/*---------------------------------------------------------
	�|�����ꍇ�̃A�C�e���w��
	���{�X�Ƌ��p����K�v������B
---------------------------------------------------------*/

static GAME_COMMAND_OBJ_FUNC(regist_items_common)
{
	void (*aaa[(16)])(OBJ/**/ *gcmd_obj) =
	{
		item_create_00_item,			item_create_01_item,				item_create_02_item,			item_create_03_item,
		item_create_04_item,			item_create_05_item,				item_create_06_item,			item_create_07_item,
		item_create_random_table,		item_create_random_table,			item_create_002_inyou_zako, 	item_create_random_table,
		item_create_random_table,		item_create_random_table,			item_create_14_yokai,			item_create_15_rumia,
	};
	gcmd_obj->callback_loser	= aaa[(((gcmd->user_item8)) & 0x0f)];	/* �u�U�R/���{�X/(�{�X)�����ꂽ�ꍇ�̏����v�ɁA�u�����_���e�[�u������A�C�e�������v��ݒ� */
}
/*
gcmd_obj->jyumyou		 ---a bc--
gcmd_obj->yx_an im_frame  yyyy xxxx
gcmd_obj->yx_an im_frame  --1a --bc
*/

/*---------------------------------------------------------
	�|�����ꍇ�̃A�C�e���w��
	���{�X/�{�X�Ƌ��p����K�v������B
	-------------------------------------------------------
	(r36-)�̎d�l��A�X�R�A�ƃU�R�̂����蔻��͓������B
	���������� DAT�� �X�R�A 0 �ɐݒ肵�Ă����ƁA���G�U�R�ɂȂ�B
---------------------------------------------------------*/
static GAME_COMMAND_FUNC(set_locate_xy_to_R06_R07)
{
	//[67!!]
	VR06 = ((gcmd->user_locate_x)<<8);	/* [pixel�P��] �ݒ�t�@�C������ �o��x���W �����߂�B */
	VR07 = ((gcmd->user_locate_y)<<8);	/* [pixel�P��] �ݒ�t�@�C������ �o��y���W �����߂�B */
//	VR07 = ((gcmd->user_locate_x)<<8);	/* [pixel�P��] �ݒ�t�@�C������ �o��x���W �����߂�B */
//	VR06 = ((gcmd->user_locate_y)<<8);	/* [pixel�P��] �ݒ�t�@�C������ �o��y���W �����߂�B */
}

/*extern*/static GAME_COMMAND_OBJ_FUNC(regist_settei_common)
{
	game_command_regist_items_common(gcmd, gcmd_obj);/* ���{�X�Ƌ��p����K�v������B */
	gcmd_obj->m_Hit256R 		= ZAKO_ATARI16_PNG; 	/* �O�����炠���蔻������߂�B */
	//------------------
	gcmd_obj->obj_type_set		= (OBJ_Z02_TEKI)|((gcmd->user_select_gazou)&0x3f); /* �ݒ�t�@�C������摜�����߂�B */
	//------------------
	/*
		DAT�͐l�Ԃ������̂ŁA�Ԉ���Ă��肷��B
		�p�^�[���A�j���[�V������p�̃U�R�L�����ɁA
		��]�n�O�����w�肵���ꍇ�A
		�p�^�[���A�j���[�V�����o���Ȃ��̂ŁA
		�o�O�����L�����ɂȂ��Ă��܂��B
		�����ł��������ꍇ�́A�����I�ɉ�]�n�ɕ␳����B
	*/
	if (11<((gcmd->user_select_gazou) & 0x0f))/*(12, 13, 14, 15) */
	{
		gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* ��]�A�j�� */	/* ��]���鑬�� */
	}
	else
	{
		gcmd_obj->zako_anime_rotate_angle65536 = (0);	/* �O���^�C�v */	/* off */
	}
	//------------------
	game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel�P��] �ݒ�t�@�C������ �o��(x, y)���W ��(VR06, VR07)�ɐݒ肷��B */
	//[67!!]
	gcmd_obj->center.x256		= VR06; 						/* [pixel�P��] �ݒ�t�@�C������ �o��x���W �����߂�B */
	gcmd_obj->center.y256		= VR07; 						/* [pixel�P��] �ݒ�t�@�C������ �o��y���W �����߂�B */
//	gcmd_obj->center.x256		= VR07; 						/* [pixel�P��] �ݒ�t�@�C������ �o��x���W �����߂�B */
//	gcmd_obj->center.y256		= VR06; 						/* [pixel�P��] �ݒ�t�@�C������ �o��y���W �����߂�B */
	gcmd_obj->zako_hp			= (gcmd->user_hp);				/* �ݒ�t�@�C������ �̗� �����߂�B */
	gcmd_obj->base_score		= (gcmd->user_score);			/* �ݒ�t�@�C������ �l���X�R�A �����߂�B(�����蔻�苤�p) */
	//
	gcmd_obj->zd05_kougeki_type = (gcmd->user_kougeki_type);	/* �ݒ�t�@�C������ �U���^�C�v �����߂�B */
	#if 1
	//------------------�ݒ�t�@�C������ �U���p�x �����߂�B
	// �ݒ�l�p�x��1024�̏ꍇ�A���ʋ@�\�Ŏ��@�_���p�𐶐�(r39-)�B
	if (1023 < (gcmd->user_angle1024))
	{
	//	VR06	= ((gcmd_obj->center.x256));
	//	VR07	= ((gcmd_obj->center.y256));
		set_REG_DEST_XY(gcmd_obj);
		CPU_CALL(calculate_jiki_nerai);
	//  HATSUDAN_R13_angle65536 = (�U���p�x);
	}
	else/* �ݒ�l�p�x��0-1023�̏ꍇ�A0-65535�ɕϊ����p�x�����߂�B */
	{
		HATSUDAN_R13_angle65536 		= (deg1024to65536(gcmd->user_angle1024));	/* �p�xdeg1024 */	/* [deg1024�P��]  �ݒ�t�@�C������ */
	}
	#endif
	//------------------�ݒ�t�@�C������ �U�����x �����߂�B
	HATSUDAN_R11_speed256					= (gcmd->user_speed256);	/* ���xt256 */	/* [t256�P��]  �ݒ�t�@�C������ �U�����x �����߂�B */
	// �����܂ł� �U�����x �� HATSUDAN_R11_speed256 (VR11) �֐ݒ�ς݁B
	// �����܂ł� �U���p�x �� HATSUDAN_R13_angle65536 (VR13) �֐ݒ�ς݁B
	//------------------ [�����l] ��ۑ�����B
	gcmd_obj->zd03_system_hoson_angle65536	= (HATSUDAN_R13_angle65536);	/* �U���p�x �� �����l�Ƃ��Ďg�p����̂ŕۑ��B */
	gcmd_obj->zd02_system_speed256			= (HATSUDAN_R11_speed256);		/* �U�����x �� �����l�Ƃ��Ďg�p����̂ŕۑ��B */
	gcmd_obj->zd04_system_hoson_speed256 	= (HATSUDAN_R11_speed256);		/* �U�����x �� �����l�Ƃ��Ďg�p����̂ŕۑ��B */
	//------------------
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	//[76?]
//	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
//	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
}
//	(r36) gcmd_obj->base_score === src->atari_hantei	= (1/*�X�R�A���p*/);	/* �f�t�H���g�͂����蔻�肠�� */


/*---------------------------------------------------------
	�U�R�o�^�̋��ʃ��[�`��
	-------------------------------------------------------
---------------------------------------------------------*/
static GAME_COMMAND_OBJ_FUNC(regist_NULL)	{	;	}

typedef struct
{
	void (*aaa_init_callback)(GAME_COMMAND *gcmd, OBJ *gcmd_obj);	/* ������ ���� */
	void (*aaa_move_callback)(OBJ *sss);					/* �ړ� ���� */
} SPELL_aaa_RESOURCE;

extern GAME_COMMAND_FUNC(00_regist_zako)
{
	if (chuu_boss_00_mode_off != cg_BOSS_DATA_32_chuu_boss_mode)
	{
		/* ��-�{�X������ꍇ�ɂ͎G���ǉ����Ȃ��B */
		return;/* error */
	}
	if ((20) < gcmd->user_255_code)
	{
		return;/* error */
	}
	/* ���ԃR�[�h�`���̃R�}���h����e�֐��ɕ��򂷂� */
	/* teki�̐�����ԍ��ŊǗ�(load_stage.c �� ctype_name[]�ɑΉ����Ă���) */
	SPELL_aaa_RESOURCE aaa_resource[(20)] =
	{
	/* �����w */
/*,000,*/		/*(���g�p)*/{game_command_regist_zako_000_mahoujin, 		move_zako_00_kougeki_mahoujin}, 	/* "�����{" /"�����w1"	TEKI_RED_BOOK	 MAHOUJIN A */	/* �΂�܂��U�������w */
/*,001,*/		/*(�����w)*/{game_command_regist_zako_000_mahoujin, 		move_zako_00_kougeki_mahoujin}, 	/* "�����w" /"�����w2"	TEKI_MAHOJIN	 MAHOUJIN B */	/* �����閂���w */
	/* ���� �A�z�� */
/*,002,*/		{game_command_regist_zako_02_inyou_dama,		move_zako_02_inyou_dama},				/* "�A�z��" /"�A�z��1"	TEKI_INYOU_DAI */
/*,003,*/		{game_command_regist_zako_03_tatsumaki, 		move_zako_03_tatsumaki},			/* "����"	/"����1"	TEKI_TATSUMAKI */
	/* �d�� */
/*,004,*/		{game_command_regist_zako_04_kakomi,			move_zako_04_kakomi},				/* "�͗d��" /"�͗d��1"	TEKI_CHOU1 */
/*,005,*/		{game_command_regist_zako_05_kisume,			move_zako_05_kisume_1st},			/* "�L�X��" /"�Ԗы�1"	TEKI_CHEN */	/* �� */
	/* �ы� */
/*,006,*/		{game_command_regist_NULL,						move_zako_06_inseki}, /*(��/��]���p)*/ 		/* "覐�"	/"覐�1"	TEKI_NIJI_HOSI */	/* ���̑��U�R */
/*,007,*/		{game_command_regist_zako_07_yukari,			move_zako_07_yukari}, /*(��]��p?)*/			/* "���ґ�" /"���ґ�2"	TEKI_NIJI_HOSI */	/* ���̑��U�R */
/*,008,*/		{game_command_regist_zako_10_hai_kedama,		move_zako_08_ao_kedama},						/* "�ы�" /"�Ζы�1"	TEKI_AKA_KEDAMA */
/*,009,*/		{game_command_regist_NULL,						move_zako_09_midori_kedama}, /*(��]��p?)*/	/* "�Ζы�" /"�Ζы�2"	TEKI_AKA_KEDAMA */
/*,010,*/		{game_command_regist_zako_10_hai_kedama,		move_zako_10_hai_kedama},	/* "�D�ы�" /"�ы�1"	TEKI_HAI_KEDAMA */
/*,011,*/		{game_command_regist_zako_11_siro_kedama,		move_zako_11_siro_kedama},	/* "���ы�" /"�ы�2"	TEKI_HAI_KEDAMA */
	/* [C�d��]���̑��U�R */
/*,012,*/		{game_command_regist_zako_12_ao_yousei, 		move_zako_12_ao_yousei},	/* "�d��" /"�d��2"	TEKI_YOUSEI1_1 */
/*,013,*/		{game_command_regist_zako_13_obake, 			move_zako_13_obake},		/* "���΂�" /"���΂�2"	TEKI_YOUSEI2_5	"���ы�1" */
/*,014,*/		{game_command_regist_zako_14_karasu,			move_zako_14_karasu},		/* "�G" 	/"�G1"		TEKI_YOUSEI2_1 */
	/* [B�d��]���d�� */
/*,015,*/		{game_command_regist_NULL,						move_zako_15_meido1},		/* "���C�h1"	TEKI_YOUSEI3_1 */
/*,016,*/		{game_command_regist_NULL,						move_zako_16_meido2},		/* "���C�h2"	TEKI_YOUSEI3_1 */
/*,017,*/		{game_command_regist_zako_17_meido3,			move_zako_17_meido3},		/* "���C�h3"	TEKI_YOUSEI3_1 */
/*,018,*/		{game_command_regist_NULL,						move_zako_18_meido4},		/* "���C�h4"	TEKI_YOUSEI3_1 */
	/* [A�d��]���d�� */
/*,019,*/		{game_command_regist_NULL,						move_ao_yousei1},			/* "�d��1"	TEKI_YOUSEI1_1 */
	};
//012�p�~{game_command_regist_NULL/*(��/��]���p)*/,	move_zako_06_inseki},				/* "���΂�1"	TEKI_YOUSEI2_5 */
//020�p�~{regist_zako_012_ao_yousei,					move_zako_12_ao_yousei},			/* "�d��2"	TEKI_YOUSEI1_1 */
	//	{regist_zako_014_karasu1,						move_zako_14_karasu},				/* ["�G1"�֋z��]"�d��3"	TEKI_YOUSEI1_1 */
	//	{game_command_regist_NULL,						move_ao_yousei1},					/* ["�d��1"�֋z��]"�d��4"	TEKI_YOUSEI1_1 */ // (r33�ł͖��g�p)
	OBJ *gcmd_obj;
	gcmd_obj = obj_regist_teki();/*(�U�R�G��obj��V�K�쐬����B)*/
	if (NULL != gcmd_obj)/* �o�^�ł����ꍇ�̂�(�o�^�Ɏ��s�����ꍇ�́A��ʓ��̃U�R�G������������̂ł���ȏ�o�^�ł��Ȃ��B) */
	{
		// �W�����ʓo�^�����B
		GAME_COMMAND_OBJ_CALL(regist_settei_common);/* ���{�X�Ƌ��p����K�v������B */
		gcmd_obj->callback_hit_teki = callback_hit_zako;		/* �u�U�R�Ɏ��e�����������ꍇ�̏����v�ɁA�����l�Ƃ��ĕW���̏�����ݒ肵�Ă����B */
		//
		gcmd_obj->callback_mover = aaa_resource[ (int)(gcmd->user_255_code) ].aaa_move_callback;	/* ���ԃR�[�h�`���̃R�}���h�ԍ�����ړ����������߂�B */
		(aaa_resource[ (int)(gcmd->user_255_code) ].aaa_init_callback)(gcmd, gcmd_obj); 			/* ���ԃR�[�h�`���̃R�}���h�ԍ�����e�֐��ɕ��򂷂�B */
	}
}
#include "boss_douchu.h"/*(�����̒��{�X / �{�X)*/
