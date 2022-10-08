
#include "boss.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�{�X�̍s�����`����B
	-------------------------------------------------------
	���݃{�X�s���́AC����̃v���O�����ɂȂ��Ă��邯�ǁA
	�����̍s���̓R�}���h�����āA�e���X�N���v�g�ōs���ł���悤�ɂ������B
	-------------------------------------------------------
	�e���X�N���v�g�ɂ͒e�̈ړ��R�}���h�n�ȊO�ɁA
	�{�X�s���R�}���h�n�𐷂荞�ށB
	-------------------------------------------------------
	(r41-)�����̏����͂��ׂ� spell_move_system (r41-�V�K�쐬�\��) �ֈڍs���܂��B
	�uspell_move_system�v�Ə����Ă�����͈̂ڍs���̏��u�ł��B
	-------------------------------------------------------
	(-r40)�̎d�g�݁B
	root -> move -> boss_move_33_keitai -> boss_move_00_card_settei_seisei(src) -> �X�y�J(�X�N���v�g)
	�������̂�
	(r41-)�̎d�g��(�\��)�B
	root -> move -> boss_move_00_card_settei_seisei(src) -> �X�y�J(�X�N���v�g) -> boss_move_33_keitai
	�����������ɐڑ��������āA�X�y�J(�X�N���v�g)����A�{�X�ړ����R���g���[���o����悤�ɕύX����\��ł��B
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[�{�X���ʃJ�[�h�ړ�]�B
---------------------------------------------------------*/

/*---------------------------------------------------------
	x�����_��32[pixel]�ȓ������ړ��B
	y�����_�� 8[pixel]�ȓ������ړ��B
---------------------------------------------------------*/

static void boss_set_position_differential32_void(void)
{
	#if 1
	/* ���݈ʒu��荶�E 32[pixel] �͈̔͂Ń����_���ړ��B�A���Œ�16[pixel]�͓����B */
	const u16 ra_nd16	= ra_nd();
	VR06	= cg_BOSS_DATA_3a_center_x256;
	{	const u16 vector_value = ((ra_nd16&(((32)*256)-1))|(16*256));/* �ړ��ʂ����߂�B �A���Œ�16[pixel]�͓��� */
	//	if (ra_nd16&0x2000) /* �ړ����������߂� */ /* 0x1fff == ((32)*256-1) */
	//	if (VR06 < (ra_nd16+ra_nd16)) /* �ړ����������߂� */
		if (VR06 < (ra_nd16+((GAME_X_OFFSET+(GAME_320_WIDTH/2)-128)<<8))) /* �ړ����������߂� */
				{VR06 += (vector_value);}
		else	{VR06 -= (vector_value);}
	}
	/* ���݈ʒu���㉺ 8[pixel] �͈̔͂Ń����_���ړ� */
	VR07 = cg_BOSS_DATA_3b_center_y256;
	VR07 += ((((ra_nd16))&((8+8)-1))<<8);
	VR07 -= (t256(8));
	#endif
}
#if 0
/*---------------------------------------------------------
	x�����_��64[pixel]�ȓ������ړ��B
	y�����_�� 8[pixel]�ȓ������ړ��B
---------------------------------------------------------*/

static void boss_set_position_differential64_void(void)
{
	#if 1
	/* ���݈ʒu��荶�E 64[pixel] �͈̔͂Ń����_���ړ��B�A���Œ�16[pixel]�͓����B */
	const u16 ra_nd16	= ra_nd();
	VR06	= cg_BOSS_DATA_3a_center_x256;
	{	const u16 vector_value = ((ra_nd16&(((64)*256)-1))|(16*256));/* �ړ��ʂ����߂�B �A���Œ�16[pixel]�͓��� */
	//	if (ra_nd16&0x2000) /* �ړ����������߂� */ /* 0x1fff == ((32)*256-1) */
	//	if (VR06 < (ra_nd16+ra_nd16)) /* �ړ����������߂� */
		if (VR06 < (ra_nd16+((GAME_X_OFFSET+(GAME_320_WIDTH/2)-128)<<8))) /* �ړ����������߂� */
				{VR06 += (vector_value);}
		else	{VR06 -= (vector_value);}
	}
	/* ���݈ʒu���㉺ 8[pixel] �͈̔͂Ń����_���ړ� */
	VR07 = cg_BOSS_DATA_3b_center_y256;
	VR07 += ((((ra_nd16))&((8+8)-1))<<8);
	VR07 -= (t256(8));
	#endif
}
#endif
/*---------------------------------------------------------
	�J�[�h�����̊Ԋu�ƈړ����Ԃ̊Ԋu�������B
	xy�����_�������ړ��B
---------------------------------------------------------*/

//tern/*static*/ void spell_boss_move_system_05_xy_douki_differential64(void)
extern/*static*/ void spell_boss_move_system_04_xy_douki_differential32(void)
{
	/* �J�[�h�������ĂȂ��ꍇ�ɒǉ� */
	if (SPELL_00==card.spell_used_number)	/* �J�[�h�����I���Ȃ�A�V�ړ�������߂�B */
	{
	//	boss_set_position_differential64_void();
		boss_set_position_differential32_void();
		#if (1)
		/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
		boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
		#endif
	}
}

/*---------------------------------------------------------
	�J�[�h�����̊Ԋu�ƈړ����Ԃ̊Ԋu�������B
	x�����_���ړ��B
	y�ړ����Ȃ��B
---------------------------------------------------------*/

extern void spell_boss_move_system_03_x_douki(void)
{
	/* �J�[�h�������ĂȂ��ꍇ�ɒǉ� */
	if (SPELL_00==card.spell_used_number)	/* �J�[�h�����I���Ȃ�A�V�ړ�������߂�B */
	{
		#if 1
		const u16 ra_nd16	= ra_nd();
		VR06	= ((ra_nd16/*&((256*256)-1)*/));	/* 0(?) =:= t256(((480-128-256)/2)-50)) */
		VR07	= (cg_BOSS_DATA_3b_center_y256);/*(t256()�`��)*/
		#endif
		#if (1)
		/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
		boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
		#endif
	}
}

/*---------------------------------------------------------
	�J�[�h�����̊Ԋu�ƈړ����Ԃ̊Ԋu���񓯊��B
	x�����_���ړ��B
	y�����_���ړ��B
---------------------------------------------------------*/

extern void spell_boss_move_system_02_xy_hidouki(void)
{
	/* �J�[�h�����̊Ԋu�ƈړ����Ԃ̊Ԋu���񓯊��B */
	cg_BOSS_DATA_35_move_jyumyou--;/*fps_factor*/
	if (cg_BOSS_DATA_35_move_jyumyou <= 0)
	{
		cg_BOSS_DATA_35_move_jyumyou	= (300);	/* �ړ����ԁA�Ԋu */
		#if 1
		int rand32 = ((ra_nd()));
		/* �ړ����W�����߂� */
		VR06 = ((rand32&0xff00)+(((rand32<<8)&0x3f00)));	/* (256+64) == 320 == (480-128-32) */
		VR07 = (((rand32>>8)&0x3f00));	/* (64) */
		#endif
		#if (1)
		/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
		boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
		#endif
	}
}

/* �o����x���W */
//#define BOSS_XP256		(t256(GAME_WIDTH/2))	/* ���S���W�Ȃ̂� */
#define BOSS_XP256			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH/2))	/* ���S���W�Ȃ̂� */

/*---------------------------------------------------------
	�Œ�ޔ��ʒu�ֈړ���A�����Ȃ��ŃJ�[�h�����B
	-------------------------------------------------------
	�Œ�ޔ��ʒu�͏㕔�AX���͒��S�B�Ƃ肠�����B
---------------------------------------------------------*/
extern void spell_boss_move_system_01_taihi_ue_naka(void)
{
	#if (1)
	/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
//	VR06	= (cg_BOSS_DATA_30_target_x256);/*(t256()�`��)*/
//	VR07	= (cg_BOSS_DATA_31_target_y256);/*(t256()�`��)*/
	VR06	= (BOSS_XP256);/*(t256()�`��)*/
	VR07	= (t256(16.0));/*(t256()�`��)*/
	boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
	#endif
}

#if 1
/*---------------------------------------------------------
	��11�`��: �ŏI�`��(����3)
---------------------------------------------------------*/

extern void spell_boss_move_system_17_sakuya_bimyou_idou(void)
{
	u32 iii;
	iii = ra_nd();
	if (0==(iii&0x07))
	{
	//	src->math_vector.x256 = (((signed int)((iii>> 8)&0xff))-127);
	//	src->math_vector.y256 = (((signed int)((iii>>16)&0xff))-127);
		cg_BOSS_DATA_3a_center_x256 += (((signed int)((iii>> 8)&0xff))-127);
		cg_BOSS_DATA_3b_center_y256 += (((signed int)((iii>>16)&0xff))-127);
	}
}
#endif


/*---------------------------------------------------------
	-------------------------------------------------------
---------------------------------------------------------*/
extern void set_tukaima_start(void);/*(�g�����V�X�e��)*/
static void spell_move_system_boss_move_tukaima_keitai_void(void)
{
	static int tukaima_tuika_timer = 0; /* �g�����A�ǉ��^�C�}�[�B�ǉ��Ԋu�����܂�Z�����Ȃ��B */
	tukaima_tuika_timer--;
	if (0 > tukaima_tuika_timer)
	{
		tukaima_tuika_timer = (1024);
		cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0e_mima_T0e;
		set_tukaima_start();/*(�g�����V�X�e��)*/
	}
}
/*---------------------------------------------------------
	-------------------------------------------------------
---------------------------------------------------------*/

extern void spell_boss_move_system_10_mima_keitai(void)
{
	spell_move_system_boss_move_tukaima_keitai_void();
	spell_boss_move_system_02_xy_hidouki();
}

/*---------------------------------------------------------
---------------------------------------------------------*/


/*---------------------------------------------------------
	[�{�X���ʃJ�[�h�s��]�B
---------------------------------------------------------*/


/*---------------------------------------------------------
	�{�X�ړ������̋��ʃ��[�`��
	-------------------------------------------------------
�� �ړ��͈͂̓o�^�A�@�\�F
	���炩���߃{�X�ړ��͈͂�o�^���Ă����B
�� �͈͓��Ȃ�Έړ��A�@�\�F
	�ړ��͈͓��Ȃ�΁A�{�X���ړ�����B
	�ړ��͈͊O�Ȃ�΁A�{�X�͈ړ����Ȃ��B
�� �ړ�����A�@�\�F
	�{�X���ړ����Ȃ��ꍇ�́A�u�ړ��ł��Ȃ������t���O�v���n�m�ɂȂ�B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�{�X�U���䗦�v�Z�B
---------------------------------------------------------*/
//	/**/extern int boss_hamidasi;		/* �u�ړ��ł��Ȃ������t���O�v(�g�p�O�Ɏ蓮��OFF==0�ɂ��Ƃ�) */

static OBJ_CALL_FUNC(boss_move_vx_vy_animation)
{
	cg_BOSS_DATA_3a_center_x256 += (src->math_vector.x256);
	cg_BOSS_DATA_3b_center_y256 += (src->math_vector.y256);
	#define USE_BOSS_HAMIDASI_CHECK (0)
	#if (1==USE_BOSS_HAMIDASI_CHECK)
		 if (cg_BOSS_DATA_3a_center_x256 < VR3c_boss_clip_min_x256)	{cg_BOSS_DATA_3a_center_x256 = VR3c_boss_clip_min_x256;	card.boss_hamidasi = (1);	}
	else if (cg_BOSS_DATA_3a_center_x256 > VR3e_boss_clip_max_x256)	{cg_BOSS_DATA_3a_center_x256 = VR3e_boss_clip_max_x256;	card.boss_hamidasi = (1);	}
//
		 if (cg_BOSS_DATA_3b_center_y256 < VR3d_boss_clip_min_y256)	{cg_BOSS_DATA_3b_center_y256 = VR3d_boss_clip_min_y256;	card.boss_hamidasi = (1);	}
	else if (cg_BOSS_DATA_3b_center_y256 > VR3f_boss_clip_max_y256)	{cg_BOSS_DATA_3b_center_y256 = VR3f_boss_clip_max_y256;	card.boss_hamidasi = (1);	}
	#else
	/*(�Ƃ肠����)*/
	cg_BOSS_DATA_3a_center_x256 = psp_min(cg_BOSS_DATA_3a_center_x256, VR3e_boss_clip_max_x256);/* �E�`�F�b�N(��ݏo��) */
	cg_BOSS_DATA_3a_center_x256 = psp_max(cg_BOSS_DATA_3a_center_x256, VR3c_boss_clip_min_x256);/* ���`�F�b�N(��ݏo��) */
	cg_BOSS_DATA_3b_center_y256 = psp_min(cg_BOSS_DATA_3b_center_y256, VR3f_boss_clip_max_y256);/* ���`�F�b�N(��ݏo��) */
	cg_BOSS_DATA_3b_center_y256 = psp_max(cg_BOSS_DATA_3b_center_y256, VR3d_boss_clip_min_y256);/* ��`�F�b�N(��ݏo��) */
	#endif
//
	/*(�U���A�j���[�V�����w��������΁A�U���A�j���[�V������D�悷��B)*/
	if (0 < cg_BOSS_DATA_33_kougeki_anime_count)	/* �U���A�j���[�V���� */	/* �U���A�j���[�V�����p�J�E���^ / 0�ȉ��Ȃ�ړ��A�j���[�V���� */
	{
		cg_BOSS_DATA_33_kougeki_anime_count--;
				if ((32) > cg_BOSS_DATA_33_kougeki_anime_count) {src->obj_type_set = BOSS_09_32;}	/*src->an im_frame = 0x23;*/
		else	if ((40) > cg_BOSS_DATA_33_kougeki_anime_count) {src->obj_type_set = BOSS_10_33;}	/*src->an im_frame = 0x22;*/
		else													{src->obj_type_set = BOSS_09_32;}	/*src->an im_frame = 0x21;*/
	}
	/*(�U���A�j���[�V�����w�����Ȃ���΁A�ړ��A�j���[�V����������B)*/
	else	/* �ړ��A�j���[�V���� */
	{
		s32 aaa;
		aaa = (cg_BOSS_DATA_3a_center_x256 > cg_BOSS_DATA_30_target_x256)?(BOSS_00_11/*0x00*/):(BOSS_04_21/*0x10*/); /* ���E */
		s32 bbb;
		bbb = cg_BOSS_DATA_34_toutatu_wariai256;
		bbb = psp_min(bbb, (0xff) );
		bbb = 0xff-bbb;
		bbb &= 0xff;
		src->obj_type_set = aaa + (cg_BOSS_DATA_34_toutatu_wariai256 >> 6);
	}
}

/*---------------------------------------------------------
	�S�{�X�s��
	(boss->callback_mover)�ŌĂ΂�郋�[�g(����)�B
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(root_boss_mover)
{
	/*(�{�X�s���I������)*/
	if (NULL != src->callback_root_supeka)
	{
		(*src->callback_root_supeka)(src);
	}
//	card_boss_move_generate_check_regist(src);	/* �J�[�h�o�^�\�Ȃ�o�^ / �J�[�h���� */
	boss_move_vx_vy_animation(src);
	move_card_square_effect(src);				/* ��G�t�F�N�g */
	/*(�X�y����������)*/
	card_generate(src);/* �X�y����CPU���s���A�J�[�h���P�t���[����������B */
	/*(�`��p���W�̐����Br41-)*/
	/*(�X�y�JCPU�ňꊇ�Ǘ����Ă���̂ŃI�u�W�F�N�g���W�́A�X�y�JCPU�̊O���ɒu��)*/
	src->center.x256/*(�X�y�JCPU�O�����W[�{�X�p])*/ = cg_BOSS_DATA_3a_center_x256;/*(�X�y�JCPU�������W[�{�X�p])*/
	src->center.y256/*(�X�y�JCPU�O�����W[�{�X�p])*/ = cg_BOSS_DATA_3b_center_y256;/*(�X�y�JCPU�������W[�{�X�p])*/
}

