
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�A���X�l�`�J�[�h
	-------------------------------------------------------
�����u�����̕������l�` -easy-�v
�A���X�̕������l�̂̐l�`���A��񕪗􂷂�7way�e�����B
4 x 7 x 7 == �ő� 196[�e](�d�X��)
3 x 7 x 7 == �ő� 147[�e](�͕핗)	//3 x 8 x 8 == 192
	-------------------------------------------------------
�����u�����̕������l�`�v	�ԗؒe
�A���X�̕������Z�̂̐l�`���A��񕪗􂷂�7way�e�����B
6 x 7 x 7 == �ő� 294[�e](�d�X��)
5 x 7 x 7 == �ő� 245[�e](�͕핗)	//5 x 8 x 8 == 320
	-------------------------------------------------------
�����u�����̕������l�` -hard-�v
�A���X�̕��������̂̐l�`���A��񕪗􂷂�7way�e�����B
8 x 7 x 7 == �ő� 392[�e](�d�X��)
9 x 7 x 7 == �ő� 441[�e](�͕핗)	//7 x 8 x 8 == 448
	-------------------------------------------------------
�����u�����̃I�����A���l�`�v	�ԗؒe���Ηؒe
�A���X�̕��������̂̐l�`���A�O�񕪗􂷂�7way�e�����B
8 x 7 x 7 x 7 == �ő�2744[�e](�d�X��)
2 x 7 x 7 x 7 == �ő� 686[�e](�͕핗)	//9 x 8 x 8 == 576
	-------------------------------------------------------
	�l�`������(�͕핗)
	�e������(�d�X��)
	���ݐl�`�͎G���𗘗p���Ă��邪�A
	���̂悤�ȕ����ɂȂ��Ă���̂́A�������ׁ̈B
	-------------------------------------------------------
	���ہu����v��(�e�͑S�e�z��Ȃ̂�)�S�e�z��𒲂ׂ�
	�u(�p�x��)�ύX�v�{�u(�V���ɒe��)�ǉ��v����񂶂�Ȃ����ȁH
	�܂��G�c�Ɏd�g�݂������΁A�u����v�e����Ȃ��āu�ǉ��v�e�B
	�u����v�Ɓu�ǉ��v���ƁA���ʓI�ɉ����Ⴄ���ƌ����΁A
	�ŏI�I�Ȓe�́u�\���v���C�I���e�B�[�v�ɔ����ȈႢ���o��B
	-------------------------------------------------------
	�܂�A7way�e�ɕ��􂷂�̂ł͂Ȃ��āA
	1�e�͕ϐg�����āA6�e�ǉ�����̂��Ǝv���B
	-------------------------------------------------------
	�{�X���ʋK�i�g�p�f�[�^�[:
		TUKAIMA_KIKAKU_00_target_x256	��Œ���W x�ʒu�Ƃ��Ďg�p�B
		TUKAIMA_KIKAKU_01_target_y256	��Œ���W y�ʒu�Ƃ��Ďg�p�B
---------------------------------------------------------*/

#define recursive		user_data05 	/* �����(0>���􂵂Ȃ�) */
#define radius			user_data06 	/* �~�̔��a */

#define i_angle1024 	VR03_i
/*---------------------------------------------------------
	����(last)
	-------------------------------------------------------
	BU LLET_UROKO14_00_AOI,
	BU LLET_UROKO14_01_AKA, 	normal
	BU LLET_UROKO14_02_YUKARI,
	BU LLET_UROKO14_03_MIDORI,	luna
//
	BULLET_UROKO14_00_SIRO, 		//��	//BU LLET_UROKO14_00_AOI,		//
	BULLET_UROKO14_01_AKA,			//��	//BU LLET_UROKO14_01_AKA,		//
	BULLET_UROKO14_02_YUKARI,		//��	//BU LLET_UROKO14_02_YUKARI,	//
	BULLET_UROKO14_03_AOI,			//��	//BU LLET_UROKO14_03_MIDORI,	//
	BULLET_UROKO14_04_MIZUIRO,		//��	//BU LLET_UROKO14_04_MIZUIRO,	//
	BULLET_UROKO14_05_MIDORI,		//��	//BU LLET_UROKO14_05_KIIRO, 	//
	BULLET_UROKO14_06_KIIRO,		//��	//BU LLET_UROKO14_06_dummy, 	//
	BULLET_UROKO14_07_DAIDAI,		//��	//BU LLET_UROKO14_07_dummy, 	//
---------------------------------------------------------*/
	#if 0
	HATSUDAN_R11_speed256			= (t256(2.0));							/* �e�� */
	HATSUDAN_R13_angle65536 		= (src->rotationCCW65536);				/* �p�x */
	HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI) + ((cg_VR20_game_difficulty));	/* [�ؒe] */
	HATSUDAN_R16_n_way				= (7);								/* [7way] [8way] */
	HATSUDAN_R17_div_angle65536 	= (int)(65536/23);					/* �����p�x (65536/27) (65536/24) */
	bul let_reg ist_multi_vec tor();
	#endif


static OBJ_CALL_FUNC(move_alice_doll_last_burrets)
{
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
	#if 1
	HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	#if 0
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST(TAMA_IRO_03_AOI, TAMA_IRO_01_AKA, TAMA_IRO_02_YUKARI, TAMA_IRO_05_MIDORI);
//	CPU_CA LL(nan_ido);
	#else
	static const u32 codebase_exec[2] =
	{
		// (1)	//	VR04 = ([��Փx�ʒ萔]);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST(TAMA_IRO_03_AOI, TAMA_IRO_01_AKA, TAMA_IRO_02_YUKARI, TAMA_IRO_05_MIDORI),
	};
	cpu_exec((u32*)&codebase_exec, (1));
	#endif
	HATSUDAN_R15_bullet_obj_type	= BULLET_UROKO14_BASE + (VR04_NAN_IDO_DECODE);		/* [�ؒe] */

//	HATSUDAN_R16_n_way				= (1);								/* [7way] [8way] */
//	HATSUDAN_R17_div_angle65536 	= (int)(65536/23);					/* �����p�x (65536/27) (65536/24) */
	#define first_angle_65536 	VR02_j
//	int first_angle_65536;
//	first_angle_65536 = ((src->rotationCCW1024)<<6);
	first_angle_65536 = (src->rotationCCW65536);
//	int VR03_i;
	for (VR03_i=0; VR03_i<(7); VR03_i++)	/* �e�� */
	{
		enum
		{
			CCC_00_SPEED256 = 0,
			CCC_01_ADD_ANGLE65536,
			CCC_99_MAX
		};
		const int ccc[8][CCC_99_MAX] =
		{
			{ t256(1.00), ((65536*10)/(14))},	// ���x����
			{ t256(0.50), ((65536* 8)/(14))},	// ���x�x��
			{ t256(1.00), ((65536* 9)/(14))},	// ���x����
			{ t256(0.75), ((65536* 7)/(14))},	// ���x��
			//
			{ t256(1.00), ((65536* 6)/(14))},	// ���x����
			{ t256(0.50), ((65536* 5)/(14))},	// ���x�x��
			{ t256(1.00), ((65536* 4)/(14))},	// ���x����
			{ t256(1.00), ((65536* 7)/(14))},	// [���g�p](.align)
		};
		HATSUDAN_R11_speed256				= (ccc[VR03_i][CCC_00_SPEED256]);									/* �e�� */
		HATSUDAN_R13_angle65536 			= (first_angle_65536+ccc[VR03_i][CCC_01_ADD_ANGLE65536]);			/* �p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	#endif
}
/*
	180�x���]����B
	�V�e�ɕ���
  A   A    A   A   --- ���x����

		A------------- ���x��
		|
   A	|	 A	------ ���x�x��
		+
//
*/
/*---------------------------------------------------------
	�G�ړ�
---------------------------------------------------------*/
static OBJ_CALL_FUNC(add_zako_alice_doll_2nd_CCW);

static OBJ_CALL_FUNC(move_alice_doll_all)
{
//	jyumyou			= (60);/* 1[�b](60[frame])��ɁA�ĕ��� */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-60) < src->jyumyou)/* ���e�G�t�F�N�g�ォ��[60]�J�E���g�����̒e */
	/* �ړ����� */
	{
	//	src->rotationCCW1024 += (((src->recursive)&(1))?(10):(-10));/* �l�`���O����] */
	//	mask1024(src->rotationCCW1024);
		src->rotationCCW65536 += (((src->recursive)&(1))?(10<<6):(-10<<6));/* �l�`���O����] */
		mask65536(src->rotationCCW65536);
		{
		//	int bbb_rotationCCW1024;
			int bbb_rotationCCW65536;
		//	bbb_rotationCCW1024 = src->rotationCCW1024-(1024/8);/* -(1024/8) == -45/360�x�X���� */
		//	bbb_rotationCCW1024 = src->rotationCCW1024+(1024/8);/*	(1024/8) ==  45/360�x�X���� */
		//	mask1024(bbb_rotationCCW1024);
			bbb_rotationCCW65536 = src->rotationCCW65536+(65536/8);/*	(1024/8) ==  45/360�x�X���� */
			mask65536(bbb_rotationCCW65536);
			src->radius++;
			#if (0)//
		//	src->cen ter.x256 = src->TUKAIMA_KIKAKU_00_tar get_x256 + ((si n1024((bbb_rotationCCW1024))*(src->radius)));/*fps_factor*/	/* CCW�̏ꍇ */
		//	src->cen ter.y256 = src->TUKAIMA_KIKAKU_01_tar get_y256 + ((co s1024((bbb_rotationCCW1024))*(src->radius)));/*fps_factor*/
			#else
		//	{/*(����)*/
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536(bbb_rotationCCW65536, &sin_value_t256, &cos_value_t256);
		//		src->center.x256 = src->TUKAIMA_KIKAKU_00_target_x256 + ((sin_value_t256*(src->radius)));/*fps_factor*/
		//		src->center.y256 = src->TUKAIMA_KIKAKU_01_target_y256 + ((cos_value_t256*(src->radius)));/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= ((src->radius)<<8);
			HATSUDAN_R13_angle65536 = (bbb_rotationCCW65536);
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			src->center.x256 = src->TUKAIMA_KIKAKU_00_target_x256 + VR07;/*fps_factor*/		//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			src->center.y256 = src->TUKAIMA_KIKAKU_01_target_y256 + VR06;/*fps_factor*/		//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
			#endif//1076828
		}
	}
	/* �����܂����� */
	else/* �ړ��I�� */
	{
		if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* ���̃��C����艺����͓G�������Ȃ� */
		{
			if (0 > src->recursive)/* �ĕ��􂷂�K�v����H */
			{
				move_alice_doll_last_burrets(src);/* �ĕ��􂵂Ȃ��B�̂Œe�ɂ���B */
			}
			else/* �ĕ��􂷂� */
			{
				add_zako_alice_doll_2nd_CCW(src);/* (�ċA��)�ĕ��􂷂� */
			}
		}
		src->jyumyou = JYUMYOU_NASI;	/* �����܂� */
	//	return;
	}
}

/*---------------------------------------------------------
	�G��ǉ�����(2nd)
---------------------------------------------------------*/
static OBJ_CALL_FUNC(add_zako_alice_doll_2nd_CCW)
{
//	const int add_angle = ( (1024/7) ); /* ���Z�p�x */	/* �Q��ڈȍ~�̕��񐔂͏��7�� */
	int first_angle65536;	/* �J�n�p�x */
//	first_angle1024 = (src->rotationCCW1024)+(1024/4);
	first_angle65536 = (src->rotationCCW65536)+(65536/4);
//	int i_angle1024;	/* �ώZ�p�x */
//	for (i_angle1024=(0); i_angle1024<(1024); i_angle1024 += (1024/7)/*add_angle*/) 	/* �e�� */
	/* ������7���� */
//	for (i_angle1024=(0); i_angle1024<(1024/2); i_angle1024 += (1024/(7*2))/*add_angle*/)	/* �e�� */
	for (i_angle1024=(0); i_angle1024<(1024/2); i_angle1024 += (1024/(7*2))/*add_angle*/)	/* �e�� */
	{
		OBJ *h;
		h						= obj_regist_teki();
		if (NULL!=h)/* �o�^�ł����ꍇ�̂� */
		{
			h->m_Hit256R			= ZAKO_ATARI02_PNG;
			h->obj_type_set 		= TEKI_16_10+((1)<<2)+((src->recursive)<<2);
			h->atari_hantei 		= (ATARI_HANTEI_TAOSENAI/*1�X�R�A���p*/);
			h->callback_mover		= move_alice_doll_all;
		//	h->callback_loser		= NULL;
			h->callback_hit_teki	= callback_hit_zako;
		//	h->rotationCCW1024		= (first_angle1024 + i_angle1024);
			h->rotationCCW65536		= (first_angle65536 + (i_angle1024<<6));/*r42�Ƃ肠����*/
	//
	//		h->base_score			= score(25*2);/*�_�~�[*/
			h->zako_hp				= (ZAKO_HP_TAOSENAI);/*(�|���Ȃ�)*/
	//
			h->jyumyou = HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			{
				/* �����ʒu */
			/*	h->center.x256 =*/ h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
			/*	h->center.y256 =*/ h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
			}
			// [���K�V�[�V�X�e���Ή�]�G�̈悾���疳��(?)
			h->TR00_hatudan_spec_data	= (0);/*([���C���[�V�X�e���������Ȃ��悤�ɂ���]�悭�킩��Ȃ�)*/
			h->radius				= (0);
			h->recursive			= ((src->recursive)-1);/* �ĕ���񐔂�1���炷�B(�e�����A) */
		}
	}
}


/*---------------------------------------------------------
	�G��ǉ�����(1st)
---------------------------------------------------------*/

/**/ OBJ_CALL_FUNC(add_zako_alice_doll_type_a)
{
	#if (1)
	const int aaa_tbl[(4)] =
	{
//		(int)(1024/3), (int)(1024/5), (int)(1024/9), (int)(1024/2), /*[�͕핗]*/	/*(�I�����A���l�`)*/
//		(int)(1024/3), (int)(1024/5), (int)(1024/9), (int)(1024/3), /*(�I�����A���l�`)*/	/* [���݂̕����ł͖���] */
		(int)(1024/4), (int)(1024/6), (int)(1024/8), (int)(1024/2), /*[�d�X����]*/	/*(�I�����A���l�`)*/	/* [���݂̕����ł͖���] */
//		(int)(1024/4), (int)(1024/6), (int)(1024/7), (int)(1024/2), /*[�d�X����]*/	/*(�I�����A���l�`)*/	/* [���݂̕����ł͖���] */
		/* �͕핗��r32���݂����蔻��Ӑ}�I�ɏ��������Ă���̂ŁA������1�ʂƂ͂���
			����ϓ�Փx�Ⴗ����C������B(�I�����A���l�`)�ȊO�d�X�����ɂ����B */
	};
	//
	const int add_angle1024 = ( (aaa_tbl[((cg_VR20_game_difficulty)&3)])); /* ���Z�p�x */	/* �Q��ڈȍ~�̕��񐔂͏��7�� */
//	const int add_angle1024 = (int)(1024/6);	/*(?)*/
	#else/*(ok!)*/
	static const u32 codebase111[3] =
	{
		// (1)	//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((4), (6), (8), (2));/*(Lunatic==�I�����A���l�`)*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),// R04 = [��Փx];
		PACK_NAN_IDO_CONST((4), (6), (8), (2)),
		// (2)	//	 (div65536);/*[�������Z�N�V�����ȊO�ł͑��x�ቺ�̉\������]*/
		MCODE(OP0x17_DIV65536, NAX, R04, R04),//  R04 = 65536 / R04;
	//	NAX
	};
	cpu_exec((u32*)&codebase111, (2));
	const int add_angle1024 = (deg65536to1024((VR04_NAN_IDO_DECODE)));
	#endif

	HATSUDAN_R15_bullet_obj_type = (TEKI_16_10+((0/*2*/)<<2));
//	int i_angle1024;	/* �ώZ�p�x */
	for (i_angle1024=0; i_angle1024<(1024); i_angle1024 += add_angle1024)	/* ��� */
	{
		OBJ *h;
		h							= obj_regist_teki();
		if (NULL!=h)/* �o�^�ł����ꍇ�̂� */
		{
			h->obj_type_set 		= (HATSUDAN_R15_bullet_obj_type);
			h->atari_hantei 		= (ATARI_HANTEI_TAOSENAI/*1�X�R�A���p*/);
			//
			h->rotationCCW65536		= ((i_angle1024)<<6);/*r42�Ƃ肠����*/
			h->m_Hit256R			= ZAKO_ATARI02_PNG;
			//
			//
			h->callback_mover		= move_alice_doll_all;
		//	h->callback_loser		= NULL;
	//		h->callback_hit_teki	= callback_hit_zako;/*(?)*/
	//
	//		h->base_score		= score(25*2);/*�_�~�[*/
			h->zako_hp			= (ZAKO_HP_TAOSENAI);/*(�|���Ȃ�)*/
	//
			h->jyumyou = HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			{
				/* �����ʒu */
			/*	h->center.x256 =*/ h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
			/*	h->center.y256 =*/ h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
			}
			// [���K�V�[�V�X�e���Ή�]�G�̈悾���疳��(?)
//			h->TR00_hatudan_spec_data			= (0);/*([���C���[�V�X�e���������Ȃ��悤�ɂ���]�悭�킩��Ȃ�)*/
			h->radius				= (0);
			#if 0
		//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST(0, 0, 0, 1);/*(Lunatic==�I�����A���l�`)*/
		//	CPU_CA LL(nan_ido);
			#else
			static const u32 codebase_exec666[2] =
			{
				// (1)	//	VR04 = ([��Փx�ʒ萔]);
				MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
				PACK_NAN_IDO_CONST(0, 0, 0, 1),/*(Lunatic==�I�����A���l�`)*/
			};
			cpu_exec((u32*)&codebase_exec666, (1));
			#endif
			h->recursive			= (VR04_NAN_IDO_DECODE);
		}
	}
}


