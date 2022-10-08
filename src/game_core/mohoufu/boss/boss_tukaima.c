
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�g�����n�́A�K�i�����ʉ�����K�v������B
	(r39u1)
	ToDo:
	�g�����V�X�e���̓X�N���v�g�ォ��A�Ăяo���\�Ƃ��A
	�X�N���v�g�O�̒��{�X������R���g���[���\�ɂ���K�v������B
	-------------------------------------------------------
	���� �I�v�V����
	�P�� �I�v�V����
	-------------------------------------------------------
	��� �΂�T��1�e �I�v�V����
	-------------------------------------------------------
	�΂�T�� ���x�x��
	����	 ����
	-------------------------------------------------------
    �߂�1:������(5)�e
        �Ēe                  �ΕĒe
        �E���                  �����
        (+90�x)                 (-45�x)

            �ΕĒe          �Ēe
            �����          �E���
            (+45�x)         (0�x)
    -------------------------------------------------------
    �߂�2:�����N�i�C(6)�e   [���̕ǂŔ��˂���]
        �ԃN�i�C�e              �N�i�C�e
        �E���                  �����

            �N�i�C�e      �ԃN�i�C�e
            �����          �E���
	-------------------------------------------------------
	��� �΂�T��2�e �I�v�V����
	-------------------------------------------------------
	�΂�T�� ���x����
	����	 �Z��
	-------------------------------------------------------
    �߂�1:������(5)�e
        �Ēe                  �ΕĒe
        �E���                  �����
        (+90�x)                 (-45�x)

            �ΕĒe          �Ēe
            �����          �E���
            (+45�x)         (0�x)
    -------------------------------------------------------
    �߂�2:�����N�i�C(6)�e   [���̕ǂŔ��˂���]
        �ԃN�i�C�e              �N�i�C�e
        �E���                  �����

            �N�i�C�e      �ԃN�i�C�e
            �����          �E���
	-------------------------------------------------------
	�{�X���ʋK�i�g�p�f�[�^�[:
		TUKAIMA_KIKAKU_00_target_x256	�ڕWx���W x�ʒu�Ƃ��Ďg�p�B
		TUKAIMA_KIKAKU_01_target_y256	�ڕWy���W y�ʒu�Ƃ��Ďg�p�B
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(common_create_item);/*(boss_item.c)*/

/*---------------------------------------------------------
	�g�����G����
---------------------------------------------------------*/
#if 0
static OBJ_CALL_FUNC(lose_mima_doll)
{
//	/* easy�̓{�����o���Ȃ��čςވʓ�炩������ */
	#if 1
	item_create(src, SP_ITEM_05_TENSU, 5, ITEM_MOVE_FLAG_06_RAND_XY);
//	item_create(src, SP_ITEM_00_P001, 5, ITEM_MOVE_FLAG_06_RAND_XY);
	#else
	{	int i;
		for (i=0; i<(5); i++)
		{
			item_create_random_table(src);
		}
	}
	#endif
}
#endif


// ����: �P��:
#define shot_angle65536 			user_data02 	/*(�g��������) �V���b�g����������ێ� */
//#define rotate_angle1024			user_data03 	/* �{�X�𒆐S�Ƃ��āA��]�p�x�B(��CCW1024�`��) */
#define rotate_angle65536			user_data03 	/* �{�X�𒆐S�Ƃ��āA��]�p�x�B(��CCW1024�`��) */
#define now_hankei_256				user_data05 	/* ���ݔ��at256()�`��[pixel] */
#define set_hankei_256				user_data06 	/* �w�蔼�at256()�`��[pixel] */


// ���: �΂�T��1�e / �΂�T��2�e

enum
{
	AO_AKA_MASK 			= 0x01,
	MODE_TYPE_MASK			= 0x02,
	//
	MODE_TYPE_00_BARAMAKI01 = 0x00,
	MODE_TYPE_01_BARAMAKI02 = 0x02,
};
	#define AO_OR_AKA	(src->set_hankei_256 & AO_AKA_MASK)/* [�ԏ��] */
//
/*---------------------------------------------------------
	�q�������w �J�[�h
---------------------------------------------------------*/

/*---------------------------------------------------------
	���: �΂�T��1�e / �΂�T��2�e
---------------------------------------------------------*/
static OBJ_CALL_FUNC(tama_uti_sakuya_tukaima_baramaki)
{
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
		/* ������ 6 way�ł͂Ȃ��āA 3 way ��2��ǉ�����B�łȂ��ƃv���C�I���e�B�[���ςɂȂ�B */
	//	HATSUDAN_R16_n_way					= (2+difficulty);						/* [2-5way](r32) */
	//	HATSUDAN_R16_n_way					= (3);		/* [�j��] */				/* [5way] */ /* [3way x 2] */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 					/* �����e(r32)6.4 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/256); 					/* �����e(�����Ɩ���)4 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/512); 					/* �����e(�����Ɩ���)2 */
// MODE_TYPE_00_BARAMAKI01
//		HATSUDAN_R11_speed256				= (t256(1.5))+((((cg_VR20_game_difficulty))<<6));		/* �e��(r32/r33) */
		HATSUDAN_R11_speed256				= (t256(0.75))+((((cg_VR20_game_difficulty))<<5));		/* �e��(r35) */
// MODE_TYPE_01_BARAMAKI02
	//	HATSUDAN_R11_speed256				= (t256(1.5))+(((difficulty)<<6));		/* �e��(r32) */
//		HATSUDAN_R11_speed256				= (t256(2.0))+((((cg_VR20_game_difficulty))<<6));		/* �e��(r33) */
	//	HATSUDAN_R11_speed256				= (t256(1.0))+((((cg_VR20_game_difficulty))<<5));		/* �e��(r35) */
//
	if (MODE_TYPE_00_BARAMAKI01==((src->set_hankei_256) & MODE_TYPE_MASK))
	{
		HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI) + (AO_OR_AKA) + (AO_OR_AKA); 	/* [�ΕĒe] */
		HATSUDAN_R16_n_way					= (5);		/* [�j��] */				/* [5way] */
	}
	else
	{
		HATSUDAN_R11_speed256 += (t256(0.25));
		HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + (AO_OR_AKA) + (AO_OR_AKA);	/* [�ԃN�i�C�e] */
		HATSUDAN_R16_n_way					= (6);		/* [�j��] */				/* [3way x 2] */
	}
	HATSUDAN_R12_speed_offset				= (0);/*(�e�X�g)*/
	HATSUDAN_R13_angle65536 				= (src->shot_angle65536);			/* [�j��] */
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	{
		const u16 kakusan_tbl[4] =
		{(int)(65536/512), (int)(65536/512), (int)(65536/256), (int)(65536/128)};		// Lunatic �͂��Ȃ�g�U����B
		HATSUDAN_R17_div_angle65536 		= kakusan_tbl[(cg_VR20_game_difficulty)];		/* [�j��] */		/* �����e(�����Ɩ���)2 */
	}
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
}

/*---------------------------------------------------------
	����: �΂�T���e
---------------------------------------------------------*/
//		HATSUDAN_R11_speed256				= (t256(1.5))+(((difficulty)<<6));	/* �e�� */
//		HATSUDAN_R13_angle65536 			= ((src->shot_angle65536) );			/* */
//		HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [�ԃN�i�C�e] */
//		HATSUDAN_R16_n_way					= (2+difficulty);					/* [2-5way] */
//		HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 				/* �����e */
//		bullet_regist_multi_vector_direct();

static OBJ_CALL_FUNC(tama_uti_mima_tukaima_baramaki)
{
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
//
//	/*[r35�v������]*/HATSUDAN_R11_speed256				= t256(1.5)+((cg_VR20_game_difficulty)<<6); 	/* �e�� */
	/*[r35������]*/HATSUDAN_R11_speed256				= t256(0.75)+((cg_VR20_game_difficulty)<<6);	/* �e�� */
	HATSUDAN_R12_speed_offset			= (0);/*(�e�X�g)*/
	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [�j��] */
	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [�ԃN�i�C�e] */
	HATSUDAN_R16_n_way					= (2+(cg_VR20_game_difficulty));	/* [�j��] */	/* [2-5way] */
	HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 				/* [�j��] */	/* �����e */
//	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
}

/*---------------------------------------------------------
	�A���X: �����e
---------------------------------------------------------*/
static OBJ_CALL_FUNC(tama_uti_alice_tukaima_kousa_dan)
{
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
//
//	/*[r35�v������]*/HATSUDAN_R11_speed256				= t256(1.5)+((cg_VR20_game_difficulty)<<6); 	/* �e�� */
//	/*[r35������]*/HATSUDAN_R11_speed256				= t256(0.75)+((cg_VR20_game_difficulty)<<6);	/* �e�� */
	/*[r35������]*/HATSUDAN_R11_speed256				= t256(0.75);	/* �e�� */
	HATSUDAN_R12_speed_offset			= (0);/*(�e�X�g)*/
//	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [�j��] */
	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [�j��] */
	//
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* �e�O�� */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	//
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* �e�O�� */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
}

/*---------------------------------------------------------
	�P��: �d�͒e
---------------------------------------------------------*/

static OBJ_CALL_FUNC(tama_uti_kaguya_tukaima_gin_tama)
{
/*
0:easy	   f  16���1�񔭒e�B
1:normal   7   8���1�񔭒e�B
2:hard	   3   4���1�񔭒e�B
3:lunatic  1   2���1�񔭒e�B
*/
	if (0==(((1<<(4-cg_VR20_game_difficulty))-1) & ((src->jyumyou>>3))))
//	if ((cg_VR20_game_difficulty+1) > ((src->jyumyou>>3)&0x03))
	{
		set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
		VR0e = (src->shot_angle65536);/*(1024to65536)*/
		#if (1)
		static /*const*/ u32 codebase_exec[14] =
		{
			//---------//set_com mon_gin_tama_void();/*(���ʕ���)*/
		//	�g�p���W�X�^:	R0e 	src_shot_angle65536 �J�n�n�_
			// (01) HATSUDAN_R11_speed256					= t256(1.0);//t256(1+difficulty)/*(3+difficulty)*/ /*(4+difficulty)*/;
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
			(t256(1.00)),
			// (02) VR12 = ra _nd();
			MCODE(OP0x15_RAND_VALUE, NAX, R12, NAX),
			// (03) VR12 = (VR12 & 0x03);
			MCODE(OP0x1d_ANDM_PD, 0x03, R12, R12),/*(�V���[�g�������A�h���b�V���O)*/
			// (04) HATSUDAN_R12_speed_offset				+= (2);//t256(0.04)/*10*/ ((ra_nd()&0x03)+1);
			MCODE(OP0x01_MOVER_PD, (u8)(+2), R12, R12), /*(�C���f�b�N�X�t)*/
			// (05) VR13 = (VR0e & ((65536/4)-1));
			MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R0e),
			(((65536/4)-1)),
			// (06) HATSUDAN_R13_angle65536 				= R13 + (65536/4)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),/*(�����O�������A�h���b�V���O��p����)*/
			((65536/4)+(65536/8)),
			// (07) HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
			// (08) HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* �e�O�� */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
			((BULLET_MINI8_BASE + TAMA_IRO_03_AOI)),
			//---------//
			// (09) (1�e����)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		//	NAX/*(�I��)*/
		};
		cpu_exec((u32*)&codebase_exec, (9));
		#endif
	}
}


/*---------------------------------------------------------
	�g�����G �U���̂�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(spell_T08_NULL)
{
	/*(�U�����Ȃ�)*/
}
static OBJ_CALL_FUNC(spell_kaguya_doll_gin_tama)
{
	/*	���� & ��镗�A��]�V���b�g */
	if (0x0ff < src->jyumyou)/* 0x100�����͋��ʋK�i�㌂���Ȃ� */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* ���̃V���b�g�����܂ł̊Ԋu�A���ԁB */
		{
			src->shot_angle65536 -= ((int)(65536/64));		/* cv1024r(10)*/
			tama_uti_kaguya_tukaima_gin_tama(src);
		}
	}
}

//	if ((u32)(0x01ff/3) < src->jyumyou)/* �Ō�� 1/3 ���Ԃ͌����ė��Ȃ��B */
static OBJ_CALL_FUNC(spell_mima_doll_baramaki)
{
	/*	���� & ��镗�A��]�V���b�g */
	if (0x0ff < src->jyumyou)/* 0x100�����͋��ʋK�i�㌂���Ȃ� */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* ���̃V���b�g�����܂ł̊Ԋu�A���ԁB */
		{
			src->shot_angle65536 += (65536/18); /* �V���b�g�����������A��]������B */
			tama_uti_mima_tukaima_baramaki(src);
		}
	}
}

static OBJ_CALL_FUNC(spell_sakuya_doll_baramaki)
{
	/*	���� & ��镗�A��]�V���b�g */
	if (0x0ff < src->jyumyou)/* 0x100�����͋��ʋK�i�㌂���Ȃ� */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* ���̃V���b�g�����܂ł̊Ԋu�A���ԁB */
		{
			src->shot_angle65536 += ((AO_OR_AKA)?(-(65536/18)):((65536/18)));	/* �V���b�g�����������A��]������B */
			tama_uti_sakuya_tukaima_baramaki(src);
		}
	}

}
static OBJ_CALL_FUNC(spell_alice_doll_kousa_dan)
{
	/*	���� & ��镗�A��]�V���b�g */
	if (0x0ff < src->jyumyou)/* 0x100�����͋��ʋK�i�㌂���Ȃ� */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* ���̃V���b�g�����܂ł̊Ԋu�A���ԁB */
		{
		//	src->shot_angle65536 -= ((int)(65536/64));		/* cv1024r(10)*/
//			src->shot_angle65536 += ((int)((2)*64));/*64==(65536/1024)*/		/* cv1024r(10)*/
		//	src->shot_angle65536 = ((src->rotate_angle1024+128)<<6);/*(�O���V���b�g45�x�X����)*/	/*64==(65536/1024)*/
			src->shot_angle65536 = (src->rotate_angle65536 + (128<<6));/*(�O���V���b�g45�x�X����)*/	/*64==(65536/1024)*/
			tama_uti_alice_tukaima_kousa_dan(src);
		}
	}
}




/*---------------------------------------------------------
	�g�����G �ړ��̂�
---------------------------------------------------------*/
static /*extern*/ OBJ_CALL_FUNC(move_tukaima00)
{
	//------------------
	HATSUDAN_R11_speed256	= (((src->now_hankei_256)));/*(t256�`��)*/
//	HATSUDAN_R13_angle65536 = deg1024to65536((src->rotate_angle1024));
	HATSUDAN_R13_angle65536 = ((src->rotate_angle65536));
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	src->center.x256 = (src->TUKAIMA_KIKAKU_00_target_x256) + VR07;//sin_value_t256 // �c
	src->center.y256 = (src->TUKAIMA_KIKAKU_01_target_y256) + VR06;//cos_value_t256 // ��
	//------------------
	//define now_hankei_256 t256(45)			/* ���a */
	if (0 < (src->set_hankei_256))
	{
		if ((src->set_hankei_256) > (src->now_hankei_256))		{src->now_hankei_256 += t256(1);};
	}
	else
	{
		if (-(src->set_hankei_256) < (src->now_hankei_256)) 	{src->now_hankei_256 -= t256(1);};
	}
}

/*---------------------------------------------------------
	�I�v�V�����ʒu�A��]�ړ� ���ʕ���
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_option_rotate)
{
	/* �I�v�V�����ʒu�A��]�ړ� */
//	src->rotate_angle1024 += (2);
//	mask1024(src->rotate_angle1024);
	src->rotate_angle65536 += (2<<6);
	mask65536(src->rotate_angle65536);
	/* �I�v�V�����ʒu�A�ړ� */
	move_tukaima00(src);
}
/*---------------------------------------------------------

---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_sakuya01_doll_T04_T05)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(�U������/���Ԍo�߂ŏI���B�{�X��|���ƊF�j�󂳂��B)*/
	#if 1
	/* �����w��]�A�j���[�V���� */
//	src->rotationCCW1024--;/* �E��� */
//	src->rotationCCW1024 += (((AO_OR_AKA)<<2)-2);
//	mask1024(src->rotationCCW1024);
	src->rotationCCW65536 += ((((AO_OR_AKA)<<2)-2)<<6);
	mask65536(src->rotationCCW65536);
	#endif
	/* �I�v�V�����ʒu�A��]�ړ� */
	/* �I�v�V�����ʒu�A�ړ� */
	move_tukaima00(src);
}

/*---------------------------------------------------------
	�q�������w �ړ� ���ʕ���
---------------------------------------------------------*/



/*---------------------------------------------------------
	�ړ��^�C�v01: rotate from boss posion.
	-------------------------------------------------------
	�{�X�̎������]����B
	-------------------------------------------------------
	�� �G�ړ�
	�q�������w01 �ړ�
	�q�������w �ړ�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kaguya01_doll_rotate_from_boss)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(�U������/���Ԍo�߂ŏI���B�{�X��|���ƊF�j�󂳂��B)*/
	move_option_rotate(src);
}


/*---------------------------------------------------------
	�ړ��^�C�v02: radius from fixed posion.
	-------------------------------------------------------
	�Œ�ʒu���甼�a���ړ�����B
	-------------------------------------------------------
	�q�������w02 �ړ�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kaguya02_doll_radius_from_fixed)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(�U������/���Ԍo�߂ŏI���B�{�X��|���ƊF�j�󂳂��B)*/
	/* �I�v�V�����ʒu�A��]�ړ� */
	/* �I�v�V�����ʒu�A�ړ� */
	if (0x2ff == src->jyumyou)
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
	//	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK02_JIKI_BOMBER;/*(���p����)*/	CPU_CALL(cpu_voice_play);
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;/*(���p����)*/		CPU_CALL(cpu_voice_play);
	}
	if (0x2ff > src->jyumyou)
	{
		move_tukaima00(src);
	}
}


/*---------------------------------------------------------
	�q�������w07 �ړ�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_alice01_doll_T0f)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(�U������/���Ԍo�߂ŏI���B�{�X��|���ƊF�j�󂳂��B)*/
	/* �I�v�V�����ʒu�A��]�ړ� */
//	src->rotate_angle1024 += (3-(cg_VR20_game_difficulty));/*(���Z���u�W��+2�ɉ�����v)*/
	src->rotate_angle65536 += ((3-(cg_VR20_game_difficulty))<<6);/*(���Z���u�W��+2�ɉ�����v)*/
	/*(����[+3]�Ȃ�A��]�����������Ԋu���L���葽���ȒP�B)*/
	move_option_rotate(src);
	src->set_hankei_256--;
}


/*---------------------------------------------------------
	�q�������w01/02 �o�^���ʕ���
---------------------------------------------------------*/
//	#define ADD_ANGLE		(341)	/* 1���� 3���������p�x�A341.33 == 1024/3  */
//	#define ADD_ANGLE		(171)	/* 1���� 6���������p�x�A170.66 == 1024/6  */
//	#define ADD_ANGLE205	(205)	/* 1���� 5���������p�x�A204.80 == 1024/5  */
//	#define ADD_ANGLE		(51)	/* 1����20���������p�x�A 51.20 == 1024/20 */
//	#define ADD_ANGLE043	(43)	/* 1����24���������p�x�A 42.66 == 1024/24 */	/* 1�� �� 24 ���� */

typedef struct
{
	u32 loop_start; 	/*(�J�n�p�x)*/
	u32 loop_stop;		/*(�I���p�x)*/
	u32 loop_step;		/*(�����p�x)*/
	u32 add_pattern256; /*(�O�����Z��)*/
	//
	int limit_hankei_256;	/*(�ő唼�a)*/
	int limit_move_jyumyou;
	void (*move_callback)(OBJ *sss);
	void (*kougeki_callback)(OBJ *sss);
} tukaima_status_BBB;
static tukaima_status_BBB tukaima_status[(16/*16*/)] =/*(8)*/
{
/*T00 T00*/ {0, 0, 0, (0), 0, 0, 0, 0, },// TUKAIMA_00_OFF
/*T0a T01*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(����)*/
/*T0b T02*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(����)*/
/*T0c T03*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(����)*/
//
/*T05 T04*/ {((1024*3/4))+0,			((1024*3/4)+((1024/2)+1)),	(1024/6),	(0x000), t256(64),		(0x04ff),			move_sakuya01_doll_T04_T05, 			spell_sakuya_doll_baramaki},/*(sakuya)*/	/* 4�� */ /* ��������(����) (0x03ff) */
/*T06 T05*/ {((1024*3/4))+0,			((1024*3/4)+((1024/2)+1)),	(1024/6),	(0x000), t256(64),		(0x04ff),			move_sakuya01_doll_T04_T05, 			spell_sakuya_doll_baramaki},/*(sakuya)*/	/* 4�� */ /* ��������(����) (0x03ff) */
/*T08 T06*/ {0, 						(1024), 					(1024/24),	(0x055), 0, 0, 0, 0, },/*(aya)*/ /*(0x55==((1024*256)/(24*128)))*/	/*([���g�p])*/
/*T0d T07*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(����)*/
//
/*T01 T08*/ {0, 						(1024), 					(1024/5),	(0x100), t256(45),		(0x01ff),			move_kaguya01_doll_rotate_from_boss,	spell_T08_NULL},			/*(kaguya)*/	/* �w�蔼�a 45[pixel] */	/* �������� */
/*T02 T09*/ {0, 						(1024), 					(1024/5),	(0x000), t256(45+48),	(0x02ff),			move_kaguya01_doll_rotate_from_boss,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* (0x01ff)�������� */ /* ��� */
/*T0e T0a*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/16),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* �w�蔼�a 224[pixel] 256[pixel] */ /* �z�u�͈�(��𒆐S�Ƃ���1/3��) */
/*T0f T0b*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/18),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* �w�蔼�a 224[pixel] 256[pixel] */ /* �z�u�͈�(��𒆐S�Ƃ���1/3��) */
//
/*T03 T0c*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/24),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* �w�蔼�a 224[pixel] 256[pixel] */ /* �z�u�͈�(��𒆐S�Ƃ���1/3��) */
/*T09 T0d*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/24),	(0x000), -t256(32*7),	(0x08ff),			move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* �w�蔼�a 224[pixel] 256[pixel] */ /* �z�u�͈�(��𒆐S�Ƃ���1/3��) */
/*T04 T0e*/ {0, 						(1024), 					(1024/5),	(0x000), t256(45),		(0x02ff),			move_kaguya01_doll_rotate_from_boss,	spell_mima_doll_baramaki},/*(mima)*/		/* �w�蔼�a 45[pixel] */ /* �������� / �\�z�ȏ�ɑ���������ʂɁB(r33) (0x01ff) */ /* ��� */
/*T07 T0f*/ {0, 						(1024), 					(1024/3),	(0x000), t256(32),		(0x08ff),			move_alice01_doll_T0f,					spell_alice_doll_kousa_dan},/*(alice)*/ 	/* (0x01ff)�������� */ /* ��� */
};


/*---------------------------------------------------------
	(�g�����V�X�e��)�G��ǉ�����B
---------------------------------------------------------*/

#define i_angle1024 	VR03_i
#define i_type256		VR02_j
#define even_or_odd 	VR08

extern OBJ_CALL_FUNC(tukaima_system_add_dolls)
{
//	card.tukaima_used_type &= 0x07;
	card.tukaima_used_type &= 0x0f;
	//
//	int even_or_odd;
	even_or_odd = 0;/*even_or_odd==blue_or_red [�ԏ��] */
//	int i_type256;
	i_type256 = 0x000;/*(�O�������p�^�[��)*/
//	u32 i_angle1024;	/* �ώZ�p�x */
	for (
		i_angle1024=tukaima_status[card.tukaima_used_type].loop_start;
		(unsigned)i_angle1024 < (unsigned)tukaima_status[card.tukaima_used_type].loop_stop;
		i_angle1024 += tukaima_status[card.tukaima_used_type].loop_step
		) /* ��� */
	{
		/*(�Ƃ肠�����g�p������)*/
	//	if (16 > card.tukaima_now_counts)
		{
			OBJ *h;
			h							= obj_regist_teki();
			/*(�g���Ԃ�[A02]�ėp�̈�ł̓}�Y�C�B[A01]�Œ�̈�ɕύX����K�v������B)*/
			if (NULL!=h)/* �o�^�ł����ꍇ�̂� */
			{
	//			card.tukaima_now_counts++;
			//	h->rotate_angle1024 	= ((i_angle1024) & (1024-1));
				h->rotate_angle65536	= (((i_angle1024) & (1024-1))<<6);/*r42�Ƃ肠����*/
				// ��ʒu(�P��)
				h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
				h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
				//
				h->m_Hit256R			= ZAKO_ATARI16_PNG;
				h->obj_type_set 		= BOSS_20_YOUSEI1_SYOUMEN;
				#if (1)/*(�ǉ�����)*/
				h->obj_type_set 		+= (((i_type256)>>8) & 0x07);/*(�O���͍ő�8�p�^�[��)*/
				i_type256				+= (tukaima_status[card.tukaima_used_type].add_pattern256);
				#endif
				h->atari_hantei 		= (1/*�X�R�A���p*/);
				//
				h->callback_loser		= common_create_item;//lose_mima_doll;
				h->callback_hit_teki	= callback_hit_zako;
				//
				h->now_hankei_256		= t256(0);			/* ���ݔ��a  0[pixel] */
				h->shot_angle65536		= (0);
			//							= ((8*1024)-1); 	/* 8192==(8*1024) */
			//							= ((2*1024)-1); 	/* 8192==(8*1024) (r36)���炩�� */
			//							= ((3*1024)-1); 	/* 8192==(8*1024) */	/* �d�����Ǔ|���� */
			//							= (((difficulty+1)<<10)-1); 	/* 8192==(8*1024) */	/* �d�����Ǔ|���� */
				/* ��x�オ��Ɣ����ɍd���Ȃ�(==�|���̂ɂ��ꂾ�����Ԃ�������) */
			//							= (((1024)+((cg_VR20_game_difficulty)<<8))-1);	/* 8192==(8*1024) */	/* �d�����Ǔ|���� */
				h->zako_hp				= (((3*1024)+((cg_VR20_game_difficulty)<<8))-1); /* 8192==(8*1024) */	/* �d�����Ǔ|���� */
				//
				/*---------------------------------------------------------
				�q�������w01/02 �o�^���ʕ���
				---------------------------------------------------------*/
			//	set_score_common(h);//static OBJ_CALL_FUNC(set_score_common)
			//				= adjust_score_by_difficulty( ( 40));	/* 40�� */
			//				= adjust_score_by_difficulty( (  5));	/* 5�� (�v30��==6x5��) (r33) */
			//				= adjust_score_by_difficulty( ( 50));	/* 50�� (�v300��==6x50��) (r32) */
			//				= adjust_score_by_difficulty( ( 50));	/* 50�� (�v300��==6x50��) */
			//				= difficulty_score_tbl[(cg_VR20_game_difficulty)];	/* ��Փx�ɂ�邪�A���Ȃ�҂���B */
				//
				/* easy 10�� (�v 50��==5x 10��) (r32) */	/* easy 1�� (�v 5��==5x 1��) (r33) */
				/* norm 30�� (�v150��==5x 30��) (r32) */	/* norm 3�� (�v15��==5x 3��) (r33) */
				/* hard 50�� (�v250��==5x 50��) (r32) */	/* hard 5�� (�v25��==5x 5��) (r33) */
				/* luna100�� (�v500��==5x100��) (r32) */	/* luna10�� (�v50��==5x10��) (r33) */
			//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((10), (30), (50), (100));/*(r32)*/
				VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((1), (3), (5), (10));/*(r33)*/
				CPU_CALL(nan_ido);
				VR04_NAN_IDO_DECODE = VR04_NAN_IDO_DECODE * score(10000);	/* x1��[pts] */
				h->base_score	= VR04_NAN_IDO_DECODE;
				{
					h->callback_mover					= tukaima_status[card.tukaima_used_type].move_callback;
					h->callback_kougeki 				= tukaima_status[card.tukaima_used_type].kougeki_callback;
					h->set_hankei_256					= tukaima_status[card.tukaima_used_type].limit_hankei_256;
					h->jyumyou	= tukaima_status[card.tukaima_used_type].limit_move_jyumyou;
				}
			/* ���ʏ�������������̂͏���������B */
				const void *aaa[(16/*16*/)] =
				{
				/*00 T00*/	&&label_continue_T00,
				/*0a T01*/	&&label_continue_T00,
				/*0b T02*/	&&label_continue_T00,
				/*0c T03*/	&&label_continue_T00,
						//
				/*05 T04*/	&&label_create_dolls_sakuya_T04_T05,
				/*06 T05*/	&&label_create_dolls_sakuya_T04_T05,
				/*08 T06*/	&&label_continue_T00,
				/*0d T07*/	&&label_continue_T00,
						//
				/*01 T08*/	&&label_continue_T00, /*(���ʂ̂�)�� �G��ǉ����� */
				/*02 T09*/	&&label_create_dolls_kaguya_T09,
				/*0e T0a*/	&&label_create_dolls_kaguya_T0a_T0d,/*(������A�L��04)*/
				/*0f T0b*/	&&label_create_dolls_kaguya_T0a_T0d,/*(������A�L��05)*/
						//
				/*03 T0c*/	&&label_create_dolls_kaguya_T0a_T0d,/*(������A����06)*/
				/*09 T0d*/	&&label_create_dolls_kaguya_T0a_T0d,/*(�ォ��)*/ /*T09*/
				/*04 T0e*/	&&label_continue_T00, /*(mima���ʂ̂�)*/
				/*07 T0f*/	&&label_continue_T00, /*(alice)*/
				};
				goto *aaa[card.tukaima_used_type];
			label_create_dolls_kaguya_T0a_T0d:			/* �q�������w02 �G��ǉ����� */
				/* ��� 1�� �� 1/3 ���� */
				// ��ʒu(��ʉ������S)
				h->TUKAIMA_KIKAKU_00_target_x256		= (t256((GAME_WIDTH/2)));//;(src->center.x256);
				h->TUKAIMA_KIKAKU_01_target_y256		= (t256(272)		   );//;(src->center.y256);
				//
			//	h->jyumyou		= (0x01ff); 		/* �������� */
			//	h->jyumyou		= (0x02ff)+(i<<6);	/* �������� */
			//	h->jyumyou		= (0x02ff)-(1024/3)+(i_angle1024);	/* �������� */
				h->jyumyou		+= (i_angle1024);	/* �������� */
				if (0 > h->set_hankei_256)/*T09*/
				{
				//	h->now_hankei_256		= t256(32*12);			/* ���ݔ��a  384[pixel] */
					h->now_hankei_256		= t256(32*10);			/* ���ݔ��a  320[pixel] */
				}
				goto label_continue_T00;
			label_create_dolls_kaguya_T09:/* �q�������w01 �G��ǉ����� */
				h->set_hankei_256					-= (cg_VR20_game_difficulty<<(4+8));	/* �w�蔼�a 45[pixel] */
				goto label_continue_T00;
			label_create_dolls_sakuya_T04_T05:
				#if (1)/*(�ǉ�����)*/
				h->zako_hp				= (8192-1);/*(�d��)*/
				#endif
			//	h->set_hankei_256 &= 0xfffffffcu;
				h->set_hankei_256	 |= ((card.tukaima_used_type<<1) & 2/*mode*/);
				h->set_hankei_256	 |= (even_or_odd);/* [�ԏ��]���C���^�[���[�u */
			//	goto label_continue_T00;
			label_continue_T00:// �Ȃɂ�����
				;
				even_or_odd ^= (1);/*(1)[bit]*/
			}
		}
	}
}


/*---------------------------------------------------------
	(�g�����V�X�e��)�ǉ��G��ݒ肷��B
---------------------------------------------------------*/
extern void set_tukaima_start(void)
{
	card.tukaima_used_type = cg_BOSS_DATA_39_tukaima_type;
}

