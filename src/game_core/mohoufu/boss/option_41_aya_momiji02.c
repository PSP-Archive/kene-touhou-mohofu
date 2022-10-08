
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�J�[�h
	-------------------------------------------------------
	�{�X���ʋK�i�g�p�f�[�^�[:
---------------------------------------------------------*/

#define MOMIJI_KODOMO_DATA_angle65536			user_data00 	/*union BULLET_ANGLE_DATA*/
#define MOMIJI_KODOMO_DATA_speed256 			user_data01 	/*union BULLET_ANGLE_DATA*/
//
//
#define MOMIJI_KODOMO_DATA_angle222_65536		user_data03
#define MOMIJI_KODOMO_DATA_adjust_speed256		user_data06


/*---------------------------------------------------------
	����(last)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_aya_doll_last_burrets)
{
//	/*[r35�v������]*/HATSUDAN_R11_speed256	= (t256(0.75)+(ra_nd()&0xff));					/* �e�� */
	/*[r35������]*/HATSUDAN_R11_speed256	= (t256(0.375)+(ra_nd()&0xff)); 				/* �e�� */
	HATSUDAN_R12_speed_offset				= (2);/*(�Ƃ肠����)*/
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	HATSUDAN_R13_angle65536 				= ((ra_nd()&(65536-1)));						/* src->tmp_angleCCW1024 */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_KOME_BASE + TAMA_IRO_01_AKA) + (((cg_VR20_game_difficulty)&0x02)<<1); /* [��(0x01)/��(0x05)�Ēe] */
	HATSUDAN_R16_n_way						= (1+(cg_VR20_game_difficulty));				/* [7way] [8way] */
	HATSUDAN_R17_div_angle65536 			= (int)(65536/23);								/* �p�x (65536/27) (65536/24) */
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
//	bullet_regist_multi_vector_direct();
}

/*---------------------------------------------------------

---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_bullet_momiji)
{
	//	jyumyou 		= (50); 	/* 200���� */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-50) < src->jyumyou)/* ���e�G�t�F�N�g�ォ��[50]�J�E���g�����̒e */
	/* �ړ����� */
	{
		if (src->MOMIJI_KODOMO_DATA_speed256 < t256(0.5) )
		{
			src->MOMIJI_KODOMO_DATA_angle222_65536 += (65536/2);	/* (65536/2) == ���� == [180/360 �x] */
			#if 1
			/* �˂�̂��� */
		//	mask65536(src->MOMIJI_KODOMO_DATA_angle222_65536);
			#endif
			src->MOMIJI_KODOMO_DATA_angle65536	= src->MOMIJI_KODOMO_DATA_angle222_65536;
			src->MOMIJI_KODOMO_DATA_adjust_speed256 = (-(src->MOMIJI_KODOMO_DATA_adjust_speed256));
		}
		src->MOMIJI_KODOMO_DATA_speed256 += src->MOMIJI_KODOMO_DATA_adjust_speed256;
		if (((src->MOMIJI_KODOMO_DATA_angle65536-src->MOMIJI_KODOMO_DATA_angle222_65536)>>6/*r42�Ƃ肠����*/) < (int)(1024*1/12) )
		{
			src->MOMIJI_KODOMO_DATA_angle65536 += ((1+1)<<6);/*0.01*/
		}
		#if 1
		/* �˂�̂��� */
	//	mask65536(src->MOMIJI_KODOMO_DATA_angle65536);
		#endif
	//	mono_angle_move(src, (BULLET_ANGLE_DATA *)data);
		#if (0)//r42(?)
	//	src->math_vector.x256			= ((si n65536((src->MOMIJI_KODOMO_DATA_angle65536))*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/	/* CCW�̏ꍇ */
	//	src->math_vector.y256			= ((co s65536((src->MOMIJI_KODOMO_DATA_angle65536))*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
		{
			int sin_value_t256; 	//	sin_value_t256 = 0;
			int cos_value_t256; 	//	cos_value_t256 = 0;
			int256_sin cos65536( (src->MOMIJI_KODOMO_DATA_angle65536), &sin_value_t256, &cos_value_t256);
			src->math_vector.x256			= ((sin_value_t256*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
			src->math_vector.y256			= ((cos_value_t256*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
		}
		#else
		//------------------
		HATSUDAN_R11_speed256	= (src->MOMIJI_KODOMO_DATA_speed256);
		HATSUDAN_R13_angle65536 = (src->MOMIJI_KODOMO_DATA_angle65536);
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
		#endif
		src->center.x256 += (src->math_vector.x256);/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	}
	/* �����܂����� */
	else
	{
		move_aya_doll_last_burrets(src);
		src->jyumyou = JYUMYOU_NASI;	/* �����܂� */
	}
}

/*---------------------------------------------------------
	5�������݂����e�𐶐�
---------------------------------------------------------*/
#define MOMIJI_KODOMO_next_angle65536	tmp_angleCCW65536	/* �q���e�A�����p�x */

#define i_angle65536	VR03_i

/*static*/ OBJ_CALL_FUNC(add_zako_aya_5_momiji)
{
	/* �����ʒu */
	VR05			= src->center.x256;
	VR04			= src->center.y256;
//	int i_angle65536;
	i_angle65536 = (src->MOMIJI_KODOMO_next_angle65536)-((int)(65536*1/20));
//
//	int VR02_j;
	for (VR02_j=(0); VR02_j<(5); VR02_j++)
	{
		OBJ *h;
		h							= obj_regist_teki();
		if (NULL != h)/* �o�^�ł����ꍇ�̂� */
		{
			h->center.x256							= VR05;/* ���e�ʒu ���Wx */
			h->center.y256							= VR04;/* ���e�ʒu ���Wy */
			//
			h->obj_type_set 						= (TEKI_32_20) + ((i_angle65536>>(7+6)) & 0x07);/* 0 ... 8 */
			h->m_Hit256R							= ZAKO_ATARI16_PNG;
			h->atari_hantei 						= (1/*�X�R�A���p*/);
		//
			h->callback_mover						= move_bullet_momiji;
			h->jyumyou								= HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			//
			h->MOMIJI_KODOMO_DATA_angle222_65536	= (i_angle65536);/*r42�Ƃ肠����*/
			h->MOMIJI_KODOMO_DATA_angle65536		= (i_angle65536);/*r42�Ƃ肠����*/
			h->MOMIJI_KODOMO_DATA_speed256			= t256(3.0);
			h->MOMIJI_KODOMO_DATA_adjust_speed256	= t256(-0.04);
			//
			i_angle65536 += (int)(65536*1/20);/*offset_angle*/
		//	mask65536(i_angle65536);
		}
	}
}
