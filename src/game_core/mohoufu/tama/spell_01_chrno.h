
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�`���m�̃J�[�h���`���܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�g2�ʃ{�X �`���m	�ʏ�U��1(1/3)	���@�_���g�U�e(1-2-3-4-5-6-7-8�e)
	-------------------------------------------------------
	(1-2-3-4-5-6-7�e)���Ǝv���Ă����ǁA�����蒼������A
	(1-2-3-4-5-6-7-8�e)�������̂ŏC���B
���[��
	�����蒼���Ă悭������A
//	(1-2-3-4-5-6-7�e)�� 			(easy�Ƃ�)�ԈႢ�H�H�H

	�`���m�͂ǂ����u���������N�v�ňႤ�����̒e�������Ă���B�̂ŗǂ�����Ȃ��B

	-------------------------------------------------------
	�����蒼���Ă悭������A
	(2-3-4-5-6-7�e) 				(easy)
									(normal)
	(3-4-5-6-7-8�e)�B				(hard)
	(3-4-5-6-7-8�e)�B				(lunatic)
	-------------------------------------------------------
	�n�߂̕��̒e�������A��̒e�͂������B

1100 0111 0xc7
0100 0000
--11 0111 0x37

	-------------------------------------------------------
0x38(56) --0
0x30(48) --1
0x28(40) --2 �S���ʐg�ےe
0x20(32) --3 �S���ʐg�ےe
0x18(24) --4
0x10(16) --5
0x08( 8) --6
0x00( 0) --7
	-------------------------------------------------------
	lunatic�Ƃ����ƑS���ʐg�ےe�������Ɍ����Ă���B(2�񂮂炢)
	-------------------------------------------------------
	�g�p���W�X�^
	R0c 	�o���Ƃ��p�x�Baaa_angle65536
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	---
	R09 	�����J�E���^2�B
	R0a 	��Փx�ʒ萔3(E=0, N=0, H=1, L=1)
//	R0b 	---
	R0c 	�o���Ƃ��p�x�Baaa_angle65536
	R0d 	��Փx�ʒ萔1
	R0e 	��Փx�ʒ萔2
---------------------------------------------------------*/
local SPELL_EXEC(10_cirno_misogi)
{
	// SPELL_TIME_0128
	if (SPELL_TIME_0064-(8*8) < VR10_BOSS_SPELL_TIMER)
	{
		if ((SPELL_TIME_0064-1)!=VR10_BOSS_SPELL_TIMER) {goto rendan16;}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#else
		{
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase888, (1));
		}
		#endif
		//
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
		VR0c = VR13;/*(���@�_���p�x���o���Ƃ�)*/
	// --------
	rendan16:
	//	if (0x40==((s rc->boss_sp ell_timer)&0xc7))/* 8��(�C��1-2-3-4-5-6-7�e:0way�͌����Ȃ��̂Ō��̂�7��) */
	//	if (0x00==((s rc->boss_sp ell_timer)&0x07))/* 8��(�C��1-2-3-4-5-6-7�e:0way�͌����Ȃ��̂Ō��̂�7��) */
		if (0!=(VR10_BOSS_SPELL_TIMER&7)) {goto easy_ha_nasi;}/*(8���1��)*/ /* 8�񖈂�1�� */
		//{
		/*(0 ... 11 : 12�� �J�E���^2)*/
		/* --10 -000 == 0011 0111 */
		//	if (0x20==((s rc->boss_sp ell_timer)&0x37))/* 2�� */
		if (SPELL_TIME_0064-(2*8) < VR10_BOSS_SPELL_TIMER){;}else{goto easy_ha_nasi;}/* 2�� */	/* (0) or (1) �̏ꍇ�B */
		if (0 == VR0d) {goto easy_ha_nasi;}
		//{
		// hard 18����(1��)
		// Luna 36����(2��)
		HATSUDAN_R13_angle65536 		= VR0c;/*(�o���Ƃ������@�_���p�x���g��)*/
		HATSUDAN_R11_speed256			= (t256(2.0));				/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [�g�t���ےe] */
		HATSUDAN_R16_n_way				= VR0d;// (36);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(36));	/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		//}
	// --------
	easy_ha_nasi:
		;
		if (0!=(VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2���1��)*/ /* 8�񖈂�1�� */
		if (SPELL_TIME_0064-(6*8) < VR10_BOSS_SPELL_TIMER){;}else{goto osimai;}/* 2�� */	/* (0) or (1) �̏ꍇ�B */
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 12, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));/*(0 ... 11 : �J�E���^2)*/
	}
		//if (6 > VR09)/*(0, 1, 2, 3, 4, 5 �̏ꍇ)*/
	/* 2.50, 2.375, 2.250, 2.125, 2.00, 1.875 :  (8-3)==0.125,	8==1.00, 7==0.50, 6==0.25, 5==0.125 */
	//	HATSUDAN_R11_speed256			= (t256(2.5))-((R09)<<5);				/* �e�� */
		HATSUDAN_R11_speed256			= (t256(2.5)) + (VR10_BOSS_SPELL_TIMER<<2); 			/* �e�� */
	//	HATSUDAN_R12_speed_offset		= t256(6);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= t256(6);/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= VR0c;/*(�o���Ƃ������@�_���p�x���g��)*/ // /* [�j��] */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [�Ēe] �ɂȂ��Ă�̂͌��� �X�e �̃O������������ */
		HATSUDAN_R16_n_way				= (2) + (VR09) + (VR0a);/* [nway] */	/* [�j��] */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(64));		/* [�j��] */		/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(80));		/* [�j��] */		/* �����p�x(65536[360/360�x]�� 80 ����) */	/* 1����n���������p�x */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(96));		/* [�j��] */		/* �����p�x(65536[360/360�x]�� 80 ����) */	/* 1����n���������p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/

		//}
	osimai:
		;
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
---------------------------------------------------------*/
local SPELL_INIT(10_cirno_misogi)
{
//	if ((64-1)==((s rc->boss_sp ell_timer)))
//	if ((SPELL_TIME_0060-1)==((s rc->boss_sp ell_timer)))	{;}
	//	/*�ʕϐ��ł��ǂ�?*/cg_BOSS_DATA_38_angleCCW65536
	static const u32 codebase_init[5] =
	{
		// (01) VR0a = ((cg_VR20_game_difficulty)>>1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0a, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*()*/
		PACK_NAN_IDO_CONST((0), (0), (1), (1)),/* R0a	��Փx�ʒ萔3(E=0, N=0, H=1, L=1) */
		// (02) // VR0d = ��Փx�ʒ萔1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(�������A���F)*/
		PACK_NAN_IDO_CONST((0), (0), (18), (36)),/*tama_const_H06_NUMS_ALICE_RED*/	/* ������:(r35-) */
		// (03)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e  = 65536 / R0d;/*(�����p�A���F)*/	/* �����p�x:  (r35-) */
	};
	cpu_exec((u32*)&codebase_init, (3));//
}
	#if 0
	// �� �`���m�u�v�p
	VR0d = [tama_const_H04_NUMS_CIRNO_BLUE];/*(�������A�F)*/	(0),	(0),	(18),				(36),				/* ��:3���4�̕����ȒP */
	VR0e = [tama_const_H05_DIVS_CIRNO_BLUE];/*(�����p�A�F)*/	(0),	(0),	(int)(65536/(18)),	(int)(65536/(36)),	/* ��:3���4�̕����ȒP */
	#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g2�ʃ{�X �`���m	�ʏ�U��1(2/3)	���@�_���S���ʒe
	-------------------------------------------------------
	[easy]10�����g�t���e�B
	-------------------------------------------------------
	�����̑S���ʂ΂�܂��B
	-------------------------------------------------------
	�g2�ʃ{�X �`���m	�ʏ�U��1(3/3)	���@�_�������e
	-------------------------------------------------------
	[easy]���@�_������18�������Ēe�́A����̃X�N�V������
	�e�̒��S��138x138[pix]���炢�܂ōL������ۂ��B
	70[pix]�Ƃ��āApsp�ł�52[pix]���炢�H(52.5==70*0.75)
	-------------------------------------------------------
	�n�߂͂����̑S���ʂ΂�܂��Bspeedt256(2.0)���炢�H
	70[pix]�i�񂾂�A�S�e���@�_���ɕω��B
	�������������speedt256(0.5)���炢�H
---------------------------------------------------------*/
#if 0
#endif

// ==================================== [�X�y�J���E] ==================================== //


/*---------------------------------------------------------
	�g2�ʃ{�X �`���m	�X���u�A�C�V�N���t�H�[���v
	-------------------------------------------------------
	�ォ�珇�ԂɌv11�񌂂B(�����[�v�ڂ�2��ڂ̈ʒu����n�߂�̂Ōv10��A2���[�v�ڂ���͌v11�񌂂�)
	3��ڂ��炢������(���኱��)�B
	10��ڂ��炢��45�x�΂߂��炢(���኱��)�B
	-------------------------------------------------------
	���̃J�[�h�ł̓`���m�͓����Ȃ��̂ŁA�摜��͂��Ă݂�B
	http://code.google.com/p/kene-touhou-mohofu/htm/lab/20110704.html
	-------------------------------------------------------
	�摜��͂��Ă݂�ƁA�p�x���������Ȃ肠��B
	�킴�Ƃ���Ă�̂�������Ȃ��B�ǂ�����Ȃ��B
	-------------------------------------------------------
	45/360�x��8���������p�x�炵���B(���߂�)
	�ƌ�������1����64���������p�x�H�H�H
	-------------------------------------------------------
	1��0.5[�b]���炢���ȁH
	-------------------------------------------------------
	0.5[�b]�� 32[�J�E���g]�Ƃ��� 10[��]������A
	�J��Ԃ�1���� == 320[�J�E���g]�H
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B(����p)
	-------------------------------------------------------
	Windows 7 �̊֐��d��� tan(theta) ���v�Z�ł���B
	Deg �� Degree �� 1����360�x�̌`���B
	Rad �� Radian �� 1���� 2.0 x PI(3.14...) �̌`���B(���Ԃ�)
	-------------------------------------------------------
	[Deg] 45 [tan] �� 1 == (y / x)
	-------------------------------------------------------
	�`���m�̉��ɏo���e�͐�������Ȃ��āA�����������Ă�B
	224[pixel]��10[pixel]���炢������B
	0.04464285714285714285714285714286 == 10[pixel] / 224[pixel] �B������
	0.04464285714285714285714285714286 == tan(theta[Deg]) �Ƃ���B
	0.04464285714148814522111963147185 == tan(2.5561500785...[Deg])
	-------------------------------------------------------
	arc tan�������̂ŁA�K���ɓ��ꂽ����2.5�x�ő�̓����B(�������A 2.5�x���炢�������Ă�)
	theta[Deg] == 2.5561500785...[Deg](arc tan�������̂ŁA�r���ł߂�ǂ������Ȃ���w)
	465.33292095715555555555555555556 == 2.5561500785... x 65536[�͕핗�ł�1��] / 360[Deg�ł�1��]
	140.93763440860215053763440860215 == 65536 / 465
	141����(?)
	464.79432624113475177304964539007 == 65536 / 141
	���[��[��� (465) �𑫂����ɂ���B
---------------------------------------------------------*/
#define CIRNO_SAGARU_BUN465 (465)
/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(cirno_icecle_fall_01_callback)/* �X���u�A�C�V�N���t�H�[���v */
{
//	if (((32*18)-HATUDAN_FRAME64)==((VR0a) ))/* ��0.33[�b](==20[frame])��~ */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]�J�E���g�̒e */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(���v���)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 -= (1024/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */	/* [�����(-r40)] */
		//	src_tama->rotationCCW1024 += (1024/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */	/* [�E���(r41-)] */
			src_tama->rotationCCW65536 += (65536/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /* [�E���(r41-)] */
		}
		else
		{	/*CCW(�����v���)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 += (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 += (1024/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */	/* [�����(-r40)] */
		//	src_tama->rotationCCW1024 -= (1024/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */	/* [�E���(r41-)] */
			src_tama->rotationCCW65536 -= (65536/4);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /* [�E���(r41-)] */
		}
		//	src_tama->TR02_hatudan_tra65536 		= t256(1);		/* (1) ���������e */
		//	src_tama->TR02_hatudan_tra65536 		= t256(7);		/* (1) ���������e */
			src_tama->TR02_hatudan_tra65536 		= t256(/*4+*/1+cg_VR20_game_difficulty);		/* (1) ���������e */
		//	src_tama->TR01_hatudan_speed65536		= t256(128);		/* �e�� */
			src_tama->TR01_hatudan_speed65536		= t256(256);		/* �e�� */
			/* (�ʏ�e�֕ϐg����) */
			src_tama->TR00_hatudan_spec_data		= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	VR03_i		��x��5�e���B[n]
	VR0b		int aaa_angle;
	-------------------------------------------------------
	�V�X�e���g�p���W�X�^(�R���p�C�������蓖�Ă�)
	VR03_i	���[�v�p i (��Փx�ʂɎc��񐔂�ݒ�B)
---------------------------------------------------------*/
local SPELL_EXEC(1b_cirno_icecle_fall)
{
//	if ((64-1)==((s rc->boss_sp ell_timer)))
//	if ((SPELL_TIME_0060-1)==((s rc->boss_sp ell_timer)))
//	{
//		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
//		 (calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */
//		HATSUDAN_R13_angle65536 = HATSUDAN_R13_angle65536;	/* [�p�x�����ڂ��Ƃ�] */
//	}
//	else
//	if (0x40 == (VR10_BOSS_SPELL_TIMER & 0xc7))/* 8��(�C��1-2-3-4-5-6-7�e:0way�͌����Ȃ��̂Ō��̂�7��) */
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))/* 8��(�C��1-2-3-4-5-6-7�e:0way�͌����Ȃ��̂Ō��̂�7��) */
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* ��0.5[�b]�Ƃ��āA32���1��B */
	{
		static /*const*/ u32 codebase777[22] =
		{
			//	HATSUDAN_R11_speed256				= (t256(0.5));			/* �e��(psp�̉�ʂ͋���) */
			//	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				//	HATSUDAN_R12_speed_offset			= t256(6);/*(�e�X�g)*/
				//	HATSUDAN_R12_speed_offset			= (jj<<(2+8));/* x4�{ �Ă���*/
			// (01) HATSUDAN_R12_speed_offset			= (0);/* x4�{ �Ă���*/
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
			((0)),
			// (02) HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [�Ēe] �ɂȂ��Ă�̂͌��� �X�e �̃O������������ */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
			((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
			// (03) VR03_i = 5;/* ��x��5�e���B */
			MCODE(OP0x1c_MOVEM_PD, (0x05), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		//	{
		//	loop_i:(ddd-15)
			//		HATSUDAN_R11_speed256				= (t256(2.0)-(VR03_i<<5));				/* �e��(2.5) */
			//		HATSUDAN_R11_speed256				= (t256(1.5)-(VR03_i<<8));				/* �e��(2.5) */
			//		HATSUDAN_R11_speed256				= (t256(1.25)-(VR03_i<<5)); 		/* �e��(1.250 1.125 1.000, 0.875 0.750, 0.625 ) */
			//		HATSUDAN_R11_speed256				= (t256(1.25)-(VR03_i<<6)); 		/* �e��(1.250 1.000 0.750, 0.500 0.250	) */
			// (04) HATSUDAN_R11_speed256				= (VR03_i<<6)); 		/* �e��(1.250 1.000 0.750, 0.500 0.250	) */
			MCODE(OP0x1f_ASLM_PD, (6), R11, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
			//		HATSUDAN_R13_angle65536 			= (0);	/* ������ */	/* [�j��] */
			//		HATSUDAN_R16_n_way					= (1);/* [nway] */		/* [�j��] */
			//		HATSUDAN_R17_div_angle65536 		= (int)(65536/(5))+((VR10_BOSS_SPELL_TIMER)<<7);	/* [�j��] */		/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
			//		VR0b = (65536/2) + (int)(65536/5) + ((VR10_BOSS_SPELL_TIMER)<<(10-5));/*n x 1024, 1024==65536/64[����]�B */
			//		VR0b = (int)(65536/5) + ((VR10_BOSS_SPELL_TIMER)<<(10-5));/*n x 1024, 1024==65536/64[����]�B */ /* [�����(-r40)] */
			// (05) VR0b = ((VR10_BOSS_SPELL_TIMER)<<(10-5));
			MCODE(OP0x1f_ASLM_PD, (10-5), R0b, R10),/*(�V���[�g�������A�h���b�V���O)*/
			// (06) VR0b += (int)(65536/8) - (int)(CIRNO_SAGARU_BUN465)/*�������኱�������Ă���*/;/*n x 1024, 1024==65536/64[����]�B */	/* [�E���(r41-)] */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),
			((int)(65536/8) - (int)(CIRNO_SAGARU_BUN465)), /*�������኱�������Ă���*/
			// (07) HATSUDAN_R13_angle65536 = VR0b;
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
			/* HATSUDAN_R13_angle65536 [�j��??] */
			// (08) HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(�����O�������A�h���b�V���O)*/
			((DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			// (09) (1�e����)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// (10) VR0b = (VR00 + (0) - VR0b); 	HATSUDAN_R13_angle65536 = (65536-VR0b);/*(���Α���_��)*/
			MCODE(OP0x05_SUBR_PD, (0x00), R0b, R00),/*(�[�����W�X�^�g�p)*/
			// (11) HATSUDAN_R13_angle65536 = VR0b;
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
			// (12) HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(�����O�������A�h���b�V���O)*/
			((DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			/* HATSUDAN_R13_angle65536 [�j��??] */
			// (13) (1�e����)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// (14) VR03_i--;/*(�c��񐔌��炷�B)*/
			/*(ok!�C���N�������g/�f�N�������g�́A���̖��߂��g�������ǂ��C������)*/
			MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
			// (15) if (0 != (s32)VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/ if (0 < (s32)VR03_i) {goto loop_i;}
			MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-15)),//	(ddd-15)loop_i:;
		//	}
		//(eee:)
			// (16)
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			// (17)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
		};
		cpu_exec((u32*)&codebase777, (3+12*5+1));
	}
	if (0x20 == (VR10_BOSS_SPELL_TIMER & 0x37))/* 2�� */
	{
		if (0 < cg_VR20_game_difficulty)
		{
			/* �e��x256 y256 �{�X�̒��S���甭�e�B */
			CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
			HATSUDAN_R11_speed256			= (t256(1.0));				/* (t256(2.0)) �e��(2.5) */
			HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
			/* HATSUDAN_R13_angle65536 [�j��] */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_07_DAI_DAI);		/* [�g�t�����ےe] */
		//	HATSUDAN_R16_n_way				= (5);/* [nway] */	/* [�j��] */
			HATSUDAN_R16_n_way				= (7);/* [nway] */	/* [�j��] */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(36));	/* [�j��] */		/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* [�j��] */		/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
}

local SPELL_INIT(1b_cirno_icecle_fall)
{	// (CLIP_RECT_TYPE_02_UE_ONLY);
	static /*const*/ u32 codebase_init[2] =
	{
		// (01)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// �ゾ���L���^�C�v
		CLIP_RECT_02_VR1d,// �ゾ���L���^�C�v
	};
	cpu_exec((u32*)&codebase_init, (1));
}
// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�p�[�t�F�N�g�t���[�Y�̌���
	-------------------------------------------------------
	����ł͒e�ɂǂ̐F�����蓖�Ă邩�Ƃ������ɂ͍S�肪����B
	�`���m�� 5��ނ̐F�̒e�������A���e�̐F�̏o��m�����ϓ��ł͂Ȃ��΂��Ă���B
	���̐F�̕΂�́A�v���O�����̓s�����ŋ��R�΂������̂ł͂Ȃ��A��דI�ȉ��o�ł���B
	�����ł̓`���m����(aho)�Ȃ̂ŁA�Q�[���I�Ƀ`���m��ڗ������邽�߂ɐe�����Ȃ�����Ƃ������o�Ӑ}������B
	(�e�������ƃ`���m�������ɂ��邩����Ȃ��Ȃ�Ƃ����Q�[����̓s��������B)
	���̐F�̕΂肪�A�`���m�炵�������o���Ă���̂ŁA�����̍Č��͎��͏d�v���Ǝv���B
	(aho�Ƃ������ݒ�͊֌W�Ȃ���)�e�̐F�̕΂肪����ƈႤ�ƁA�����炭�u�Q�[���I�Ƀ`���m�炵���Ȃ�Ȃ��v�B
	�`���m�炵��: �� -> ���� -> ao -> aho -> �A�z -> baka -> baka==�H(�ԉf�ˌ�������������)
	//
	�����œK���ȃX�N�V������e�̐��𒲂ׂ�B
	1(1).�� 27/141��	3/16�� == 3.06382978723404255319148936170213 = 27*16/141	(R+G+B�͔��Ȃ̂Ő��኱���Ȃ����قړ��l�ɂ���)
	2(3).�� 21/141��	2/16�� == 2.38297872340425531914893617021277 = 21*16/141	(R+G+B�͔��Ȃ̂Ő��኱���Ȃ����قړ��l�ɂ���)
	3(5).�� 26/141��	3/16�� == 2.95035460992907801418439716312057 = 26*16/141	(R+G+B�͔��Ȃ̂Ő��኱���Ȃ����قړ��l�ɂ���)
	4(6).�� 34/141��	4/16�� == 3.85815602836879432624113475177305 = 34*16/141	�����Ȃ킿(R+G)�Ȃ̂Ő����Ȃ��Ƃ������o�B
	5(7).�� 33/141��	4/16�� == 3.74468085106382978723404255319149 = 33*16/141	�򂷂Ȃ킿(R+R+G)�Ȃ̂Ő����Ȃ��Ƃ������o�B
	�]���āA���L�̊m���e�[�u��������B
	-------------------------------------------------------
	const u8 p_tama_tbl[(16)] =
	{
		// �m���𓙂�������B
		// �F���U��΂�悤�Ȕz�u���l����B
		 TAMA_IRO_01_AKA, TAMA_IRO_03_AOI,	  TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI,
		 TAMA_IRO_01_AKA, TAMA_IRO_03_AOI,	  TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI,
		 TAMA_IRO_01_AKA, TAMA_IRO_06_KI_IRO, TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI, TAMA_IRO_07_DAI_DAI,
	};
	-------------------------------------------------------
	�{���̓p�[�t�F�N�g�t���[�Y�ɗ����͈�������̂ł́H
	�ƌl�I�ɂ͍l���Ă���B
	-------------------------------------------------------
	�Ƃ肠�����A���O�̗��������֐�(�P�Ɏ����̒����֐�)���A���ƕi���̗ǂ��������o���̂ŁA
	�������׍H���Ȃ��Ă��΂�Ȃ��̂œ��ɖ��Ȃ������B
	�ł��ǂ����Ȃ�S���Ă݂�B
//
	�܂��`���m�͖��t���[���e���΂�T���Ă���Ɍ��܂��Ă���̂�(���̑O�񂪂��������\���͂��܂薳���Ǝv����)�B
	�`���m���΂�T���e�ʂ���A1�b�Ԃ�60�e���x�A1�b�Ԃ�120�e���x�A1�b�Ԃ�180�e���x�̒��ł́A1�b�Ԃ�120�e���x���߂��B
	�]����1�t���[��2�e�Ƃ���B
//
	�p�b�g���ɂ͔���Ȃ����A�`���m�̗����e�͂��邮����Ȃ���A�΂��ďo�Ă���B�炵���̂ŁB
	�ǂꂮ�炢�̑��x�ŉ��̂Ȃ�A����Č����Ȃ������������Ă݂�B(����͌����Ȃ���Δ���Ȃ����x)
	(16����==)��1�b��(64�t���[��)��4��(0.25�b��1��)���ƁA�I���ɉ���Ă��銴���B�Ȃ̂ŁA����ł͖��炩�ɂ��������B
	(8����==)��1�b��(64�t���[��)��8��(0.125�b��1��)���ƁA�����Ȃ���Δ���Ȃ����x�B
	(4����==)��1�b��(64�t���[��)��16��(0.0625�b��1��)���ƁA�����̈悪���������ς����āA��������Ӗ����Ȃ��̂ł͂Ȃ����H�B
	1�t���[��2�e�Ƒ��e�ʂ����܂��Ă���ׁA���񐔂𑝂��΂��̕��A�����̈悪�L���Ȃ�A��������Ӗ����Ȃ��Ȃ�B
	(������1�͕������������Ȃ��̂Ɠ���������)
	�܂�A�e�ʂ�1�t���[��2�e�̏ꍇ�A8�����ɋ߂����̂������肦�Ȃ��Ƃ�����������B
//
	��L�̎�������A1�t���[���ӂ�� 8����1���x�̗̈�� 2�e���m�肵���B
	�������A���̗̈�͌����� 8����1 �ł͂Ȃ��B
	�Ȃ��Ȃ�A���̗̈悪 n����1�Ŋ���؂��ƁA����Č����₷����ɃQ�[���I�Ɉ��S�n�т��o���₷���B
	������A���̗̈�͌����� n����1 �ł͂Ȃ��B
	65536/8 == 8192�B65536/10 == 6553.6�B�����ɋ߂��l�Ǝv����B
	8����1(8192) > ? > 10����1(6554) �e�L�g�[�� KOTEITI_CHIRNO_7777 �ɂ��Ă݂�B
	7777�̏ꍇ 8.42689983284042689983284042689983����1�B(==65536/7777)
//
	��L������ 8�����Ȃ̂ŁA2�e�ڂ̊p�x�́A16 �������ꂽ��́A16 �������x�̗����l(0-4095)���ǂ��Ǝv����B
	( 8���� == 16����(�Œ�l) + 16����(�����l) )
	-------------------------------------------------------
	�� �v�C��:
	�p�[�t�F�N�g�t���[�Y�̌�ǂ��e(��)�͂�蒼������S�R������B
	���ʂ͎~�܂��Ĕ����邩�画��Ȃ������B(���Ă��������U���U�����l���Ȃ�����)
	�Ȃ񂩓����Ȃ��������ƁA�\�����킩��B
	�����_���Ƃ�����Ȃ��āA(�W�����e��)�u�O�Z�b�g�v(�������ۂ�)�����ė���݂����B
	(���@�_��Ȃ�)���@�_�������e�B
	���񎞂Ɏ��@�_���pa, b, c���쐬(?)�B
	a��b��c�͓Ɨ��B
---------------------------------------------------------*/

//#define KOTEITI_CHIRNO_7777	(7777<<6)
//#define KOTEITI_CHIRNO_7777	(497728)
#define KOTEITI_CHIRNO_7777 	(492013)
//#define KOTEITI_CHIRNO_7777	(7777)
/* �[������==���Z�Œ�l(KOTEITI_CHIRNO_7777) */

/*---------------------------------------------------------
	�p�[�t�F�N�g�t���[�Y
	1��������10[�b]�Ƃ���B
0x280  0000 0010 1000 0000	>>=6  0x000a
	-------------------------------------------------------
64 x  0 	(640==0x0280) a
	�����_������
64 x  1 	(576==0x0240) 9
	�����_������
64 x  2 	(512==0x0200) 8
	�����_������
64 x  3 	(448==0x01c0) 7 �����J�n
	//����
64 x  4 	(384==0x0180) 6 ��~
	//��~	// ���@�ˑ��ɂ��8��������
64 x  5 	(320==0x0140) 5 �ĉ���
	//�ĉ���
64 x  6 	(256==0x0100) 4
64 x  7 	(192==0x00c0) 3
64 x  8 	(128==0x0080) 2
64 x  9 	( 64==0x0040) 1
64 x 10 	(  0==0x0000) 0
	-------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
[09sec] 34 33		| -- --
[08sec] 32 31 30 29 | -- -- -- --
[07sec] 28 27 26 25 | AA -- -- -- // [07sec] �����J�n�B
[06sec] 24 23 22 21 | -- -- -- --
[05sec] 20 19 18 17 | -- -- -- --
[04sec] 16 15 14 13 | BB -- -- -- // [04sec] �S�ăX�g�b�v�B
[03sec] 12 11 10 09 | CC -- -- -- // [03sec] �ĉ����B
[02sec] 08 07 06 05 | -- -- -- --
[01sec] 04 03 02 01 | -- -- -- --
	-------------------------------------------------------
	[execute section: ���e�Z�N�V����]
[09sec] 34 33		| RR RR
[08sec] 32 31 30 29 | RR RR RR RR
[07sec] 28 27 26 25 | RR RR RR RR
[06sec] 24 23 22 21 | -- -- RR RR // [06.50sec]�ŏ��̃����_�����ˁB((12*16)192[�t���[��]==��3�b)�΂�T���B
[05sec] 20 19 18 17 | ZZ ZZ -- --
[04sec] 16 15 14 13 | -- -- ZZ ZZ // [04.50sec] ��ǂ��e����
[03sec] 12 11 10 09 | -- -- -- --
[02sec] 08 07 06 05 | -- -- -- --
[01sec] 04 03 02 01 | -- -- -- --
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	add_angle ���Z�p�x��ێ��B
	R0a 	���@�_���p���ꎞ�ێ�����B(���݂̎����ł� HATSUDAN_R13_angle65536 ���j�󂳂��d�l�Ȃ̂ŗv�邪�A��ŗv��Ȃ��Ȃ邩���H)
	R0b 	�ĉ����̑��x�p�ɗ����ێ��B
	R0c 	ra_nd16 ���� 16bit
	R0d 	temp �ꎞ�g�p [�j��]�B/ ���[�v�ϐ�jj;
	-------------------------------------------------------
	VR10_BOSS_SPELL_TIMER	�{�X�^�C�}�[�l�B
	VR11 VR10 �̔��f�ŗp�r�O�g�p�B
	-------------------------------------------------------
	�V�X�e���g�p���W�X�^(�R���p�C�������蓖�Ă�)
	VR03_i	���[�v�p i (��Փx�ʂɎc��񐔂�ݒ�B)
---------------------------------------------------------*/
local TAMA_FUNC(cirno_danmaku_01_callback)/* �p�[�t�F�N�g�t���[�Y */
{
	VR11 = (VR10 & 0x0f);
	if (0 != VR11)	{goto tugi444;}
	//
	VR11 = (VR10 >> 4);
//	if ((28*16) == VR10_BOSS_SPELL_TIMER) /*[07sec] �����J�n*/
//	if ((28*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi222;} /*[07sec] �����J�n*/
	if (28 != VR11) 	{goto tugi222;} /*[07sec] �����J�n*/
	/*---------------------------------------------------------
		(�S�e����) (�g��12�ےe��S�e����������B)
	---------------------------------------------------------*/
	//{
	//	src_tama->TR02_hatudan_tra65536 	= t256(-6); 	/* (-5.12==98%)���������e x 1.0 */
	//	src_tama->TR02_hatudan_tra65536 	= t256(-12);	/* (-5.12==98%)���������e x 2.0 */	/* -12==�����߂� */
		src_tama->TR02_hatudan_tra65536 	= t256(-9); 	/* (-5.12==98%)���������e x 1.5 */
	//}
	goto tugi444;
tugi222:
//	else
//	if ((24*16) == VR10_BOSS_SPELL_TIMER) /*[06sec] �S�ăX�g�b�v*/
//	if ((20*16) == VR10_BOSS_SPELL_TIMER) /*[05sec] �S�ăX�g�b�v*/
//	if ((16*16) == VR10_BOSS_SPELL_TIMER) /*[04sec] �S�ăX�g�b�v*/
//	if ((16*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi333;}  /*[04sec] �S�ăX�g�b�v*/
	if (16 != VR11) 	{goto tugi333;} /*[04sec] �S�ăX�g�b�v*/
	/*---------------------------------------------------------
		(�S�e��~) (�g��12�ےe��S�e��~�B)
		�e�̐F�𔒂�����B
		������ς���B
	---------------------------------------------------------*/
	//{
			#if 0
		//	s->rotationCCW1024					= (ra_nd()&((1024)-1)); 	/* ���� */	/* �����͗����łȂ��C������ */
			#else
			/* ���Ȃ��Ƃ��������͖{���ɋ߂��B ���A�S�R�Ⴄ�B */
			/* ���Z�Œ�l(KOTEITI_CHIRNO_7777)�ȊO�̗v���Ƃ��āA�S�e�z��̃T�C�Y�Ń��[�v����ׁA�S�e�z��̃T�C�Y�� */
			/* ���݂� 1024 ����A�{���Ɠ��� 640 �Ɍ��点�΁A����\���͂���B */
			VR09 += (KOTEITI_CHIRNO_7777);
		//	src_tama->rotationCCW1024			= (deg65536to1024(VR09));	/* ���� */	/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
			src_tama->rotationCCW65536			= ((VR09)); /* ���� */
			#endif
		src_tama->TR02_hatudan_tra65536 	= t256(0.0);		/* ���������e */
		src_tama->TR01_hatudan_speed65536	= t256(0.0);		/* �e�� */
		src_tama->obj_type_set					= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
	//}
	goto tugi444;
tugi333:
//	else
//	if ((12*16) == VR10_BOSS_SPELL_TIMER) /*[03sec] �ĉ���*/
//	if ((12*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi444;} /*[03sec] �ĉ���*/
	if (12 != VR11) 	{goto tugi444;} /*[03sec] �ĉ���*/
	/*---------------------------------------------------------
		(�S�e����) (�g��12�ےe��S�e����������B)
		�����e(���m�ɂ͓������e)�Ȃ̂ɁA�����e�Ɍ����Ȃ���
		�����e(���m�ɂ͓����x�e�A����==0)�Ɍ������Ⴄ��肪����B
	---------------------------------------------------------*/
	//{
		//{
			#if 0
			VR0b += 0x0100;
		//	VR0b &= 0x0700; 	// 2 3 4 5	6 7 8 9
			VR0b &= 0x0300; 	// 3 4 5 6
		//	src_tama->TR02_hatudan_tra65536 = t256(6);					/* ���������e */
		//	src_tama->TR02_hatudan_tra65536 = (jj<<8)+t256(2);			/* (2 ... 9) ���������e */
	//		src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(3.0);/*(r34)*/	/* (3 ... 6) ���������e */
			#endif
			/* (1�͒x�������̂ŏ��O) 9 ���Ƒ��߂��邩�� */
			/*
				r35�Œe���V�X�e���̎d�l��ύX���āA���̒e���ɂ����鎖���o����悤�ɂȂ����B(r34�̃V�X�e���ł͏o���Ȃ�)
				(�{���͉������x���̂Ŏ��̒e���ɂ�����)
				���������āA�����Ƃ�������������B
				r34�̃V�X�e���ł̓��C���[��ʂ������A�e�̎�ނŔ��肵�Ă���ׁA�O�̒e���Ǝ��̒e���̋�ʂ��o���Ȃ��B
				���ׁ̈A�x��鎖�͋�����Ȃ��ׂɁA�e���̎d�l��ύX���Ă����B
				r35�̃V�X�e���ł͒e���ʂɃ��C���[�𕪂��ĊǗ����Ă���B���̈�r34�ɔ�׎኱�x���B
				�e���̃��C���[�Ǘ���r34�͌v1���C���[�Ǘ�����(==���C���[�Ǘ�����)�Br35�͌v4���C���[�Ǘ�����B
				r35�ł͑O�̒e��(���C���[0)�Ǝ��̒e��(���C���[1)�̓��C���[���Ⴄ�̂œ����ɏo�����Ă���薳���B
			*/
			#if (0)
			VR0b += (123);
			VR0b &= (0x01ff);/* 0 ... 2 */
			src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(1.0);/*(r35)*/	/* (1 ... 3) ���������e */
			#else
			VR0b += (97);
			VR0b &= (0xff);/* 0 ... 1 */
			src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(1.0);/*(r35)*/	/* (1 ... 2) ���������e */
			#endif
		//}
		/* (�ʏ�e�֕ϐg����) */	/*(��ǂ��e�͒ʏ�e)*/
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	//}
//	goto tugi444;
tugi444:
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
#define T_01_AKA		(BULLET_WAKU12_BASE | TAMA_IRO_01_AKA)
#define T_03_AOI		(BULLET_WAKU12_BASE | TAMA_IRO_03_AOI)
#define T_05_MIDORI 	(BULLET_WAKU12_BASE | TAMA_IRO_05_MIDORI)
#define T_06_KI_IRO 	(BULLET_WAKU12_BASE | TAMA_IRO_06_KI_IRO)
#define T_07_DAI_DAI	(BULLET_WAKU12_BASE | TAMA_IRO_07_DAI_DAI)
local SPELL_EXEC(13_perfect_freeze)
{
	static const u32 codebase_exec[68] =/*24+16+21+10*/
	{
		// (01) VR11 = (VR10 >> 4);
		MCODE(OP0x1e_ASRM_PD, (4), R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
		//	(memo)if (((SPELL_TIME_34x16_544)-(12*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if ((22*16) < VR10_BOSS_SPELL_TIMER) {goto colorful_particle;}/* [06.50sec]�ŏ��̃����_������ ((12*16)192[�t���[��]==��3�b)�΂�T���B */
		// (02) if ((22) < VR11) {goto colorful_particle;}/* [06.50sec]�ŏ��̃����_������ ((12*16)192[�t���[��]==��3�b)�΂�T���B */
		MCODE(OP0x09_BFL_RS, (22), R11, (+26)),// colorful_particle+26/*[�J���t���e]*/ �t���[�����番��
		//	(memo)if (((SPELL_TIME_34x16_544)-(16*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if (((SPELL_TIME_34x16_544)-(16*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)else if ((18*16) < VR10_BOSS_SPELL_TIMER) {return;/*�������Ȃ�*/}/*[05.50sec] �������Ȃ�*/
		// (03) else if ((18) < VR11) {goto osimai;/*�������Ȃ�*/}/*[05.50sec] �������Ȃ�*/
		MCODE(OP0x09_BFL_RS, (18), R11, (+1)),// osimai+1;/*�������Ȃ�*/ �t���[�����番��
		/*[04.50sec] ��ǂ��e���� */
		//	(memo)if (((SPELL_TIME_34x16_544)-(20*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if (((SPELL_TIME_34x16_544)-(19*16)/*(24*16)*/) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)else if ((15*16) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		// (04) else if ((15) < VR11) // 192== (12*16)
		MCODE(OP0x09_BFL_RS, (15), R11, (+1)),// ato_oidan_check+1;/*��ǂ��e�`�F�b�N*/ �t���[�����番��
//osimai+1://osimai-3:
		// (05) else	{goto osimai;/*�������Ȃ�*/}
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
/*[��ǂ��e�`�F�b�N]*/
//ato_oidan_check+1:
	//{
		// (06) 	VR11 = VR10 & 0x07;VR11 = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, (0x07), R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
		//	(memo)if (0 == (VR10_BOSS_SPELL_TIMER & 0x07)) /* 8[frame]��1�� */
	//	if (0x00==VR11) /* 8[frame]��1�� */
	//	{
	//	//(?)	(memo)if ((4+(cg_VR20_game_difficulty))>(VR10_BOSS_SPELL_TIMER & 0x07))//[�Ӗ��s��]
	//		goto ato_oidan;
	//	}
		// (07) if (0 != VR0a)	{return;}	//if (0==VR0a) goto (aaa+3);
		MCODE(OP0x08_BNE_RS, (0), R11, (-3)),/*�������Ȃ�*/
/*[��ǂ��e]*/
//ato_oidan:
		/*
		Normal�œK���ɂ���Ă݂��B
		��ǂ��e�́A���x�̈Ⴄ�e(�O��)�𓯎��ɏo���B�̃Z�b�g��6�񂾂����B
		*/
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		// (08)  (calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		// (09) VR0a = (HATSUDAN_R13_angle65536);/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R0a, R13),
		// (10) HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(0)),
		// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
		// (12) HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_MARU10_BASE + TAMA_IRO_03_AOI),
		// (13) VR03_i = 3;
		MCODE(OP0x1c_MOVEM_PD, (0x03), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	//(ddd-11:)loop_i:;
		//	HATSUDAN_R11_speed256			= (t256(2.5));				/* �e�� */
		//	HATSUDAN_R11_speed256			= (t256(1.75)+(jj<<7)); 	/* �e�� */
		// (14) HATSUDAN_R11_speed256			= (VR03_i << 8);	/* �e�� */
		MCODE(OP0x1f_ASLM_PD, 0x08, R11, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
		// (15) HATSUDAN_R13_angle65536 		= (VR11);	/* [�j��] */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R11),
		// (16) VR11 += t256(2.00);/* �e�� */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(t256(2.00)),
		// (17) VR13 += (VR0a);/* ���@�_���p */
		MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
		// (18) HATSUDAN_R16_n_way				= (8);			/* [�j��] */	/* [8way] */
		MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (19) HATSUDAN_R17_div_angle65536 	= (65536/16);	/* [�j��] */	/* �����p�x([360/360]�x��16����) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/16),
		// (20)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
		// (21) VR03_i--;/*(�c��񐔌��炷�B)*/
		#if 1/*(ok!�C���N�������g/�f�N�������g�́A���̖��߂��g�������ǂ��C������)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
		#endif
		// (22) if (0 != (s32)VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/ if (0 < (s32)VR03_i) {goto loop_i;}
		MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-11)),//	(ddd-11)loop_i:;
	//(eee:)//return;
		// (23)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	//}
/*[�J���t���e]*/
//colorful_particle+6:
		// (24) VR09 += (KOTEITI_CHIRNO_7777);	/* �Œ�l�B8����1 ���� 10����1 ���x�̒l�ŁAn����1�Ŋ���؂�Ȃ��l�B */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
		(u32)(KOTEITI_CHIRNO_7777), /* �����p�x([360/360]�x��16����) */
		// (25) VR0c = (ra_nd());/*&0xffff*/
		MCODE(OP0x15_RAND_VALUE, NAX, R0c, NAX),
		// (26) VR0c = VR0c & (65536-1);	VR0c &= (0xffff);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0c, R0c),
		(0xffff),
		//		HATSUDAN_R11_speed256			= (t256(1.9)+(VR0c>>7));		/* �e�� */	/* (VR0c>>7) == ����(0-511) */
		//		HATSUDAN_R11_speed256			= (t256(1.5)+(VR0c>>7));		/* �e�� */	/* (VR0c>>7) == ����(0-511) */
		// (27) HATSUDAN_R11_speed256 = (VR0c >> 7);
		MCODE(OP0x1e_ASRM_PD, (7), R11, R0c),/*(�V���[�g�������A�h���b�V���O)*/
		// (28) HATSUDAN_R11_speed256 += (u32)(t256(1.5));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(u32)(t256(1.5)),	/* */
		//		HATSUDAN_R12_speed_offset		= t256(-5); 		/* (-5) (-3)���������e */	/* ���̕����ɂȂ邩������ */
		// (29) HATSUDAN_R12_speed_offset	= t256(0);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(0)),
		/*
			�����̒e�������́A�P���ɑ����������������A�x���������������Ƃ������͖����B
			����܂葬�����߂���(�{�����炢�H)�ƁA�����̃G�^�[�i���~�[�N�ɂȂ����Ⴄ�͔̂���Ǝv�����ǁB
			//
			�����ꍇ�́A�n�߂̒e�������̂͂��̕�����Ȃ邪�A�㔼�͒e��������̂ō����ȒP�ɂȂ�B
			�x���ꍇ�́A�n�߂̒e�������̂͂��̕��ȒP�ɂȂ邪�A�㔼�͒e����������̂ł��̕�����Ȃ�B
		*/
		//		HATSUDAN_R13_angle65536 	= (0/65536);					/* ������ */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((32768)-1)) + ((VR10_BOSS_SPELL_TIMER)<<(8+6)); 	/* ���� */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((32768/32)-1)) + ((VR10_BOSS_SPELL_TIMER)<<(8+4));		/* ���� */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((65536)-1)) ;		/* ���� */
		// (30) HATSUDAN_R13_angle65536 	= (VR09)/*8����(0.125�b��1��)*/;	/* ���� */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
		// (31) HATSUDAN_R14_tama_spec = (DANMAKU_LAYER_01)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
		// (32) VR0d = (VR10_BOSS_SPELL_TIMER & 0x0f);
		MCODE(OP0x1d_ANDM_PD, (0x0f), R0d, R10),/*(�V���[�g�������A�h���b�V���O)*/
		//	HATSUDAN_R15_bullet_obj_type		= (p_tama_tbl[(VR0d)]);
		// (33) VR15 = hairetu[R0d];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R0d, R15, (+16)),
		// [16]
		T_01_AKA, T_03_AOI,   T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI,
		T_01_AKA, T_03_AOI,   T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI,
		T_01_AKA, T_06_KI_IRO, T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI, T_07_DAI_DAI,
//		/* �m���𓙂�������B */
//		/* �F���U��΂�悤�Ȕz�u���l����B */
//	(bbb+16:)
		// (...) HATSUDAN_R17_div_angle65536 += (u32)(65536/16);
	//	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
	//	(BULLET_WAKU12_BASE),	/* */
	//	#if 0
	//	HATSUDAN_R16_n_way	= (2);	/* [2way] */	/* 1�t���[����2�e */
	//	#else
	//	HATSUDAN_R16_n_way	= (1 + (cg_VR20_game_difficulty)); /* �͕핗�Ȃ̂ŁA��Փx���� */
	//	#endif
		// (50) VR16 = VR20 + 1;//HATSUDAN_R16_n_way = (1+(cg_VR20_game_difficulty));
		MCODE(OP0x01_MOVER_PD, (u8)(+1), R16, R20_PLAYER_DATA_game_difficulty),/*(�C���f�b�N�X�t)*/
		// (51) HATSUDAN_R17_div_angle65536 = (VR0c >> 4); /* (VR0c >> 4) == ����(0-4095) */
		MCODE(OP0x1e_ASRM_PD, (4), R17, R0c),/*(�V���[�g�������A�h���b�V���O)*/
		// (52) HATSUDAN_R17_div_angle65536 += (u32)(65536/16);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R17, R17),
		(u32)(65536/16),	/* �����p�x([360/360]�x��16����) */
		// (53)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (54) VR0d = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, (0x07), R0d, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (55)if (0 != VR0d){goto(ccc+2);}if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
		MCODE(OP0x08_BNE_RS, (0x00), R0d, (+1)),//	(ccc+1)
		// (56)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
//	(ccc+1:)
		// (57)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (30+6/*9*/+8));/*(?�e�L�g�[�ɑ���)*/
//	cpu_exec((u32*)&codebase_exec, (17));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ᕄ�u�_�C�A�����h�u���U�[�h�v
	-------------------------------------------------------
	(r35)�I�������ĂȂ��B
	-------------------------------------------------------
	�`���m�̎���ŕX�e���΂�T��
	�����Ɍ����e���ۂ��B
		1.�`���m�̎��藣�ꂽ�ʒu���甭�e�B(�����_��?)
		2.������x�܂ōL����B
		3.�������e�B
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(����p)
	R09 	angle_65536
	R0a 	sine   �̒l�p�B
	R0b 	cosine �̒l�p�B
---------------------------------------------------------*/

local SPELL_EXEC(16_diamond_blizzard)
{
	// VR06;/*(�{�Xx���W)*/
	// VR07;/*(�{�Xy���W)*/
	static const u32 codebase_exec[23] =
	{
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/*(32���1��)*/
	/*(���t���[�����e)*/
	//	{
		// (01) VR13 = (ra _nd()/*&0xffff*/);
		MCODE(OP0x15_RAND_VALUE, NAX, R13, NAX),	//	HATSUDAN_R13_angle65536 		= VR09;
		// (02) VR09 = (ra _nd()/*&0xffff*/);
		MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
	//	HATSUDAN_R13_angle65536 		= VR09;
	//	HATSUDAN_R11_speed256			= (VR09&0x7fff);
		// (03) VR11 = VR09;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R09),
		// (04) VR11 &= 0x7fff;
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R11, R11),
		(0x7fff),
		// (05)  (sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		MCODE(OP0x10_SINCOS256, NAX, R0b, R0a),// ���L: �������� sin �� cos ���t.
		// (06) VR07 = (VR07 << 1);VR07 >>= 1;/*(�ȉ~�͈̔͂Ŕ��e)*/
		MCODE(OP0x1e_ASRM_PD, 0x01, R0b, R0b),/*(�V���[�g�������A�h���b�V���O)*/
		// (07) VR06 += VR0a;/*(�{�Xx���W�֍���R0a�����Z)*/
		MCODE(OP0x04_ADDR_PD, NAX, R06, R0a),//
		// (08) VR07 += VR0b;/*(�{�Xy���W�֍���R0b�����Z)*/
		MCODE(OP0x04_ADDR_PD, NAX, R07, R0b),//
	//	NAX
		// (09) HATSUDAN_R11_speed256			= (t256(0.5));				/* �e��(2.5) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(0.5)),
		// (10) HATSUDAN_R12_speed_offset		= t256(2);/*(�Ă���)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(2)),
		// (11) HATSUDAN_R13_angle65536 		= (VR09);/*(���̂��_��(?))*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
		// (12) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
		// (13) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [�Ēe] �ɂȂ��Ă�̂͌��� �X�e �̃O������������ */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
		// (14) (1�e����)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
	//	}
		//	radius_aaa = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//	src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		// (15)
		MCODE(OP0x02_COUNTER, 32, R08, NAX),	//	/* (32�񖈂ɔ���) */
		// (16) if (1 != VR08){goto eee;} /* (32���1��) ���� */
		MCODE(OP0x08_BNE_RS, (0x01), R08, (+1)),
		// (17)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE16_BOSS_KYUPIN, NAX, NAX),
//	(eee+19):
		// (18)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (17));
}

/*
	�ŋ��u�G�^�[�i���t�H�[�X�u���U�[�h�v
	(Eternal Force Blizzard, EFB)

	�G�^�[�i���t�H�[�X�u���U�[�h
		��u�ő���̎��͂̑�C���ƕX��������
		����͎���

	2�����˂�̃j���[�X����̃X���b�h(�ʏ�VIP)�ōl���o���ꂽ���@(�K�E�Z�H)
	���܂�̃N�H���e�B�̍����ɗl�X��AA�������B
	�܂��A�����̉{���҂Ɏ������ߋ��ɓ����悤�Ȏ����l���Ă����ƌ����g���E�}���Ăъo�܂������B
*/
