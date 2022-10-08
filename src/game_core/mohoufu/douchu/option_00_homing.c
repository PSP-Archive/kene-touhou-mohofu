
#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�U���~�T�C���G
	-------------------------------------------------------
	�U���z�[�~���O�ɂ��悤�Ǝv�����̂�
	�Ȃ����V���b�g����(�쐬��)
	�F�X�������B
---------------------------------------------------------*/

#define target_x256 		user_data00 	/* �ڕW�n�_(�o�����̃v���C���[�ʒu) */
#define target_y256 		user_data01 	/* �ڕW�n�_(�o�����̃v���C���[�ʒu) */

#define radius				user_data02 	/* ���a */
#define ax256				user_data04 	/* �� */
#define ay256				user_data05 	/* �� */


/*---------------------------------------------------------
	�G�̗U���z�[�~���O�{��(�ΐF�̓z)
---------------------------------------------------------*/

/* �v���C���[�̂����ʒu�ɓ��B�������� */
#define GENTEN_FRAME128 (128)
#define ZERO_FRAME256	(256)

static OBJ_CALL_FUNC(teki_homing_move)
{
	if (GENTEN_FRAME128 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
//	if ((GENTEN_FRAME128-16) < src->jyumyou)	/* ��莞�Ԃ܂� */
//	if ((256+GENTEN_FRAME128-256-64+16) < src->jyumyou) /* ��莞�Ԃ܂� */
//	if ((256-16) < src->jyumyou)	/* (�x��) ��莞�Ԃ܂� */
	if ((256+32) < src->jyumyou)	/* ��莞�Ԃ܂� */
	{
		VR04	= (src->target_x256);					/* �e��x256 */
		VR05	= (src->target_y256);					/* �e��y256 */
		VR06	= ((src->center.x256));
		VR07	= ((src->center.y256));
		CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//	#define ROTATE_1024HARF 	(1024/2)/*����*/
	//	const int sabun_aaa = ((deg65536to1024(HATSUDAN_R13_angle65536))-src->rotationCCW1024);
		#define ROTATE_65536HARF 	(65536/2)/*����*/
		const int sabun_aaa = (( (HATSUDAN_R13_angle65536))-src->rotationCCW65536);
		if (0 > (sabun_aaa) )/* 0���W�X�^+���ʍœK�� */
		{
			/* �ڕW�p�x < ����p�x */
			if ((ROTATE_65536HARF) > (sabun_aaa) )/* ���ʍœK�� */
			{
			//	src->rotationCCW1024 -= (10);
				src->rotationCCW65536 -= (10<<6);
			}
		}
		else	/* �ڕW�p�x > ����p�x */
		{
			if ((ROTATE_65536HARF) > -(sabun_aaa) )
			{
			//	src->rotationCCW1024 += (10);
				src->rotationCCW65536 += (10<<6);
			}
		}
		#undef ROTATE_65536HARF
		// �����֐��ɂ�������
		{
		//	const u8 ddd[4] =
		//	{
		//		GENTEN_FRAME128-31, 	//-(((255)>>2)-GENTEN_FRAME128), /*(�܂��_��Ȃ��B�قڌ����邾��)*/
		//		GENTEN_FRAME128- 0, 	//-(((255)>>2)-GENTEN_FRAME128), /*(�قڑ_��Ȃ��B�債�ē���Ȃ�)*/
		//		GENTEN_FRAME128-47, 	//-(((255)>>2)-GENTEN_FRAME128), /*(�����_���B)*/
		//		GENTEN_FRAME128-63, 	//-(((255)>>2)-GENTEN_FRAME128), /*(63==���m�ɑ_��) (r34�݊�)*/
		//	};
		//	int radius_aaa;/* ���x */
			//------------------
			HATSUDAN_R11_speed256	= (t256(1.0));
			HATSUDAN_R13_angle65536 = (deg1024to65536((((src->jyumyou-(GENTEN_FRAME128-63))<<2))));
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		//	radius_aaa = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//	src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
			HATSUDAN_R11_speed256	= ((VR07)<<2);
			HATSUDAN_R13_angle65536 = (src->rotationCCW65536);
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			src->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
		}
	}
	/* ���ړ� */
	src->center.x256 += (src->math_vector.x256);
	src->center.y256 += (src->math_vector.y256);
}


/*---------------------------------------------------------
	�G���̗U���~�T�C�����쐬����
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(bullet_create_teki_homing)
{
	/* �ڕW�n�_ */
	OBJ *zzz_player;
	zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	//
	u32 i_angle;
	for (i_angle=0; i_angle<(1024); i_angle += (1024/8) )/* */
	{
		OBJ *h;
		h					= obj_regist_teki();
		if (NULL!=h)/* �o�^�ł����ꍇ�̂� */
		{
			h->m_Hit256R				= ZAKO_ATARI_HOMING16_PNG;
			h->obj_type_set 			= ZAKO_63_HOMING_STUFF;
			h->callback_mover			= teki_homing_move;
			/* (r34u1)�󂹂�悤�ɂ��� */
			h->callback_hit_teki		= callback_hit_zako;		/* �u�U�R�Ɏ��e�����������ꍇ�̏����v�ɁA�W���̏�����ݒ� */
			h->atari_hantei 			= (score(5*2)/*�X�R�A���p*/);
			h->zako_hp					= (1);		/* �U���~�T�C���̍d���B */
			h->center.x256				= (src->center.x256);/* ���e�ʒu */
			h->center.y256				= (src->center.y256);/* ���e�ʒu */
	//
		//	h->rotationCCW1024			= (i_angle);/* �~�T�C���̌��� */
			h->rotationCCW65536			= ((i_angle)<<6);/*(r42�Ƃ肠����) �~�T�C���̌��� */
			{
				h->target_x256			= (zzz_player->center.x256);/* �ڕW�ʒu */
				h->target_y256			= (zzz_player->center.y256);/* �ڕW�ʒu */
			}
			h->jyumyou		= (256+GENTEN_FRAME128);
		}
	}
}
