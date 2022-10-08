
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�A���X�̃J�[�h���`���܂��B
---------------------------------------------------------*/


/*---------------------------------------------------------
	�A���X(��)	�Ԃ̖��@(2�i�K��)�̂悤�Ȃ��́B
	-------------------------------------------------------
	�ړ��𐧌�����J�[�h�B
	�Ƃ肠�����A���X������A�Ԃ̖��@��2�i�K�ځB
	-------------------------------------------------------
	�g�p���W�X�^:
	R08 	�J�E���^�B(4���1�񔭒e����)
	R09 	������[�j��]
	R0a 	���@�_���p���ꎞ�ێ�����B(���݂̎����ł� HATSUDAN_R13_angle65536 ���j�󂳂��d�l�Ȃ̂ŗv�邪�A��ŗv��Ȃ��Ȃ邩���H)
	R0b 	[x���W�ꎞ�ۑ�] [�ꎞ�g�p]
	R0c 	[y���W�ꎞ�ۑ�]
	R0d 	��Փx�ʒ萔1
	R0e 	��Փx�ʒ萔2
---------------------------------------------------------*/

local SPELL_EXEC(0e_aka_2nd)
{
	static const u32 codebase_exec[60] =
	{
		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		// (1)	counter(&VR08, 4);
		MCODE(OP0x02_COUNTER, 4, R08, NAX),
		//	if (0 == VR08)
		// (2)	if (0 != VR08)	{return;}
		#if (1==USE_CPU_EXTRA)
		MCODE(OP0x08_BNE_RS, (0x00), R08, CPU_QUIT),// (ddd+57)
		#else
		MCODE(OP0x08_BNE_RS, (0x00), R08, (+57)),// (ddd+57)
		#endif
		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		// (3)	HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R10),
		// (4)	VR11 &= (0x1f);
		MCODE(OP0x1d_ANDM_PD, (0x0f), R11, R11),
		// (5)	if (0x00 != VR11) goto (ccc+29);//if (0x00 == (VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x08_BNE_RS, (0x00), R11, (+29)),// (ccc+29)
		//------------------
		// (6)	VR0b = VR06;// (push VR06)[�{�Xx���W�ꎞ�ۑ�]
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R06),
		// (7)	VR0c = VR07;// (push VR07)[�{�Xy���W�ꎞ�ۑ�]
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R07),
		// (8)	HATSUDAN_R11_speed256	= (t256(1.0));
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
		(t256(1.0)),
		// (9)	HATSUDAN_R13_angle65536 = (VR10_BOSS_SPELL_TIMER << (8));
		MCODE(OP0x1f_ASLM_PD, (8), R13, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (10)  (sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		MCODE(OP0x10_SINCOS256, NAX, R06, R07),
		//	cg_BOSS_DATA_3a_center_x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//	cg_BOSS_DATA_3b_center_y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//	NAX/*(�I��)*/
		//[�d��]	HATSUDAN_R11_speed256			= t256(1.0);							/* �e�� */
		// (11) HATSUDAN_R12_speed_offset			= t256(1.0);/*6(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
		(t256(1.0)),
		// (12) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(�����O�������A�h���b�V���O)*/
		((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
		// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [�ԕĒe] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
		((BULLET_KOME_BASE + TAMA_IRO_01_AKA)),
		// (14) HATSUDAN_R16_n_way					= (8);						/* [8way] */
		MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (15) HATSUDAN_R17_div_angle65536 		= (int)(65536/48);			/* �����p�x(65536/(6*8) ) �P����8���������̈�������6���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(�����O�������A�h���b�V���O)*/
		((int)(65536/48)),
	//	NAX/*(�I��)*/
		//------------------
		// (16) VR06 = VR0b;//[�{�Xx���W����]	// (pop VR06)[���ˍ��W���X�g�A]
		MCODE(OP0x01_MOVER_PD, NAX, R06, R0b),
		//------------------ tmp_kakudo �� R0b �Ɍv�Z����B(���W�X�^����Ȃ����� R0b ���Ԏ؂肷��B)
		// (17) R0b/*const int tmp_kakudo*/ = (VR07/*sin_value_t256*/<<4);	/* ���ɗh�炬��[1/2]��������B */
		MCODE(OP0x1f_ASLM_PD, (4), R0b, R07),/*(�V���[�g�������A�h���b�V���O)*/ /* �h�炬��[1/2]��������B */
		//		(65536/(4*2)) + 	/* (65536/(4*2)) == �܂�(90/360)�x�̔���������B(���2�{�ɂȂ�) */	/* �e����΂ɂ��Ȃ��͈� */
		//	//	(65536/(8*2)) + 	/* (65536/(8*2)) == �܂�(45/360)�x�̔���������B(���2�{�ɂȂ�) */	/* �e����΂ɂ��Ȃ��͈� */
		//	//	(65536/128) +		/* �܂�(2.8125/360)�x������B(���E�Ȃ̂�2�{==5.625�x�ɂȂ�) */		/* �e����΂ɂ��Ȃ��͈� */
		//		((256<<4)); /* ���ɗh�炬����������[2/2]�B */
		// (18) VR0b += ((65536/(4*2))+((256<<4))); 	/* �e����΂ɂ��Ȃ��͈� + �h�炬��[2/2] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),
		((65536/(4*2))+((256<<4))), 	/* �e����΂ɂ��Ȃ��͈� + �h�炬��[2/2] */
		//------------------
		// (19) VR07 = VR0c;//[�{�Xy���W����]	// (pop VR07)[���ˍ��W���X�g�A]
		MCODE(OP0x01_MOVER_PD, NAX, R07, R0c),
		//------------------(���W�X�^����Ȃ����� R0c ���Ԏ؂肷��B)
	//	/* hatudan_system_regist_katayori_n_way�̎d�l���P���ȈׁA(R0b��) �␳���� */
	//	#define BA_HOSEI48	((65536/(48/8))/2)	/* ��� 65536�n�� 48�����e x 8 way �̐^��(�܂�/2)�t�� */
	//	/*tmp_kakudo-BA_HOSEI48*/R0c = /*tmp_kakudo*/R0b - BA_HOSEI48;
		// (20) VR0c = R0b - ((65536/(48/8))/2);BA_HOSEI48
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0b),
		(u32)(-((65536/(48/8))/2)), 	/*	- BA_HOSEI48 */
		//------------------ R0b == tmp_kakudo;
		// (21) [�E��]	HATSUDAN_R13_angle65536 	= (( tmp_kakudo - BA_HOSEI48)&(65536-1));	/* �p�x(��CCW�Ȃ̂Ő�����==�E��) */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (22)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		//------------------ R0b == tmp_kakudo;
		// (23) [����]	HATSUDAN_R13_angle65536 	= ((-tmp_kakudo - BA_HOSEI48)&(65536-1));	/* �p�x(��CCW�Ȃ̂ŕ�����==����) */
		//		VR0b = (VR00 + (0) - VR0b);
		MCODE(OP0x05_SUBR_PD, (0x00), R0b, R00),/*(�[�����W�X�^�g�p)*/
		// (24) VR0c = R0b - ((65536/(48/8))/2);BA_HOSEI48
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0b),
		(u32)(-((65536/(48/8))/2)), 	/* - BA_HOSEI48 */
		// (25)
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (26)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		//------------------
	//(ccc+29:)
		// (27) HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R10),
		// (28) VR11 &= (0x1f);
		MCODE(OP0x1d_ANDM_PD, (0x1f), R11, R11),
		// (29) if (0x00!=VR11) goto (aaa+3);//if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x08_BNE_RS, (0x00), R11, (+3)),//(aaa+3)
		// (r35�ŃJ�[�h�̏ꍇ�̂ݏȗ��\)	set_REG_DEST_BOSS_XY();
		// (30)  (calculate_jiki_nerai);/* ���@�_���p�쐬 */
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
		// (31) VR0a						= HATSUDAN_R13_angle65536;/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R0a, R13),
		// (32)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//(aaa+3:)
		//	HATSUDAN_R11_speed256 = (t256(1.1));					/* �e�� */
		// (==1)	HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;	/* �e�� */ /* ��Ō��ق������� */
		// (==2)	VR11 &= (0x1f);
		// (33) VR11 = (VR00 + (0x1f) - VR11);
		MCODE(OP0x05_SUBR_PD, (0x1f), R11, R00),/*(�[�����W�X�^�g�p)*/
		// (34) VR11 += t256(1.0);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(u32)(t256(1.0)),
		// (35) HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(3/*6*/)),
		// (36) HATSUDAN_R13_angle65536 		= (VR0a);/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
		// (37) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT),
		// (38) HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);	/* [�ԗؒe] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_UROKO14_BASE + TAMA_IRO_01_AKA),
		// (39) HATSUDAN_R16_n_way = VR0d;	/* [VR0d way] */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
		// (40) HATSUDAN_R17_div_angle65536 = VR0e; /* �����p�x(65536/(6*8) ) �P����8���������̈�������6���������p�x */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
			//	os2x	���e����x�ʒu(�����I�ɉ��ɂ��炷)
			//	VR06 += (ra _nd() & 0x1fff)-t256((32)/2);	/* �e��x256 */
		// (41) VR06 += (VR09 & 0x1fff)-t256((32)/2);	/* �e��x256 */
		MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
		// (42) VR09 &= (0x1fff);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R09, R09),
		(0x1fff),
		// (43) VR09 -= t256((32)/2);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
		(u32)(-t256((32)/2)),
		// (44) VR06 += VR09;
		MCODE(OP0x04_ADDR_PD, NAX, R06, R09),
		/* ���@�_�� */
		// (45)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	//(ddd+57:)
		// (46)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (45));
}

local SPELL_INIT(0e_aka_2nd)
{
	static const u32 codebase_init[5] =
	{
		// (1)	VR0d = ��Փx�ʒ萔1	VR0d = [tama_const_H06_NUMS_ALICE_RED];/*(�������A�g�F)*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST(( 8), ( 7), ( 7), ( 7)),/*tama_const_H06_NUMS_ALICE_RED*/	/* ������:(r35-) */ 	/* ��:3���4�̕����ȒP */
		// (2)	VR0e = ��Փx�ʒ萔2	VR0e = [tama_const_H07_DIVS_ALICE_RED];/*(�����p�A�g�F)*/		/*((VR10_BOSS_SPELL_TIMER & 0x20)>>3)+*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0e, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((18), (18), (20), (24)),/*tama_const_H07_DIVS_ALICE_RED*/	/*((VR10_BOSS_SPELL_TIMER & 0x20)>>3)+*/		/* �����p�x:  (r35-) */
		// (3)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0e),// R0e = 65536 / R0e;
	};
	cpu_exec((u32*)&codebase_init, (3));//
}
//	VR0d	= NAN_IDO_DECODE(PACK_NAN_IDO_CONST((12), (18), (20), (24)));
//	VR0d	= NAN_IDO_DECODE(PACK_NAN_IDO_CONST((6), (3), (5), (7)));
	#if 0
	// �� �A���X �u�Ԃ̖��@�v�p
	//	(3),								(4),								(5),								(6),								/* ������:(-r34) */
		(6),								(3),								(5),								(7),								/* ������:(r35-) */ 	/* ��:3���4�̕����ȒP */
	//	(int)(65536/(18)),					(int)(65536/(24)),					(int)(65536/(40)),					(int)(65536/(64)),					/* �����p�x:  (-r34) */
	//	(int)(65536-(int)(65536/(18))), 	(int)(65536-(int)(65536/(24))), 	(int)(65536-(int)(65536/(40))), 	(int)(65536-(int)(65536/(64))), 	/* �����p�x_R:(-r34) */
		(int)(65536/(12)),					(int)(65536/(18)),					(int)(65536/(20)),					(int)(65536/(24)),					/* �����p�x:  (r35-) */
	//	(int)(65536-(int)(65536/(12))), 	(int)(65536-(int)(65536/(18))), 	(int)(65536-(int)(65536/(20))), 	(int)(65536-(int)(65536/(24))), 	/* �����p�x_R:(r35-) */
	#endif

// ==================================== [�X�y�J���E] ==================================== //

#if 1/*(r39)*/
/*---------------------------------------------------------
	�A���X normal�ʏ�U��3(�̈ꕔ)
	-------------------------------------------------------
	-------------------------------------------------------
	�g�p���W�X�^
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
	�����e�B���v���B
---------------------------------------------------------*/
local TAMA_FUNC(alice_aaa_danmaku_01_callback)
{
	/* 0-256 �J�E���g�܂� */	/* [0]�J�E���g==���e�ʒu */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-80) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[0-79]�J�E���g�o�߂����e */
	{
	//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
	//			{src_tama->rotationCCW1024++;}/* �Ȃ��Ă݂�e�X�g */
	//	else	{src_tama->rotationCCW1024--;}/* �Ȃ��Ă݂�e�X�g */
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
				{src_tama->rotationCCW65536 += (1<<6);}/* �Ȃ��Ă݂�e�X�g */
		else	{src_tama->rotationCCW65536 -= (1<<6);}/* �Ȃ��Ă݂�e�X�g */
	}
	// (���̕���������₷���H)
	else
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) == src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[256]�J�E���g�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����==��ʓ��ł͒e�͏����Ȃ�) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		#if (1)/*(�f�o�b�O)*/
		src_tama->obj_type_set					= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);		/* [�~�j�Ԋےe] */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
		#endif
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

local SPELL_EXEC(17_alice_nejiri10sec)
{
	/*(����[�l�`�ɂ�点�Ė{�l�͌��Ă邾����������...])*/
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(17_alice_nejiri10sec)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0f_alice_T0f;
	set_tukaima_start();
}

#endif
// ==================================== [�X�y�J���E] ==================================== //

#if 0/*(r38)*/
/*---------------------------------------------------------
	�A���X normal�ʏ�U��3(�̈ꕔ)
	-------------------------------------------------------
	�Ȃ񂩑S�R�܂��������ĂȂ��B
	�d�X�����̂���őn���Ă��������Y�k���ɂȂ����B
	���������Ă�̂��킩��Ȃ��Ǝv�����A�킽���ɂ��킩��Ȃ���B
	���낵�����̂̕З؂��ȉ����B
	psp�𑜓x���S�R�Ⴄ����A�����Ɏ����悤�Ƃ��Ȃ������ǂ������H
	-------------------------------------------------------
	�g�p���W�X�^
---------------------------------------------------------*/

local SPELL_EXEC(17_alice_nejiri10sec)
{
	if ((64*1) < VR10_BOSS_SPELL_TIMER)
	{
		/* [CW ���v���] */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		{
			cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/24);
			#if 0
			cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & ((1<<difficulty)-1) );
			#else
			{
				static const u8 masked_tbl[4] = { 0x00, 0x0f, 0x3f, 0xff };
				cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & (masked_tbl[(cg_VR20_game_difficulty)]) );
			}
			#endif
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
			//
				HATSUDAN_R11_speed256				= (t256(1.0));							/* �e�� */
				HATSUDAN_R12_speed_offset			= t256(1);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
				HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);				/* [�g�t���ےe] */
				HATSUDAN_R16_n_way					= (6);									/* [6way] */
				HATSUDAN_R17_div_angle65536 		= (int)(65536/48);						/* �����p�x(65536/(6*8)) �P����8���������̈�������6���������p�x */
			{
				HATSUDAN_R13_angle65536 			= (cg_BOSS_DATA_38_angleCCW65536);							/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			//
				HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW65536+(65536/2))&(65536-1));					/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
	else
	if ((64*2) < VR10_BOSS_SPELL_TIMER)
	{
		/*[CCW �����v���]*/
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		{
			cg_BOSS_DATA_38_angleCCW65536 += (int)(65536/24);
			#if 0
			cg_BOSS_DATA_38_angleCCW65536 -= (int)(ra_nd() & ((1<<difficulty)-1) );
			#else
			{	static const u8 masked_tbl[4] = { 0x00, 0x0f, 0x3f, 0xff };
				cg_BOSS_DATA_38_angleCCW65536 -= (int)(ra_nd() & (masked_tbl[(cg_VR20_game_difficulty)]) );
			}
			#endif
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
			//
				HATSUDAN_R11_speed256				= (t256(1.0));							/* �e�� */
				HATSUDAN_R12_speed_offset			= t256(1);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
				HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);				/* [�g�t���Ԋےe] */
				HATSUDAN_R16_n_way					= (6);									/* [6way] */
				HATSUDAN_R17_div_angle65536 		= (int)(65536/48);						/* �����p�x(65536/(6*8)) �P����8���������̈�������6���������p�x */
			{
				HATSUDAN_R13_angle65536 			= (cg_BOSS_DATA_38_angleCCW65536);							/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			//
				HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW65536+(65536/2))&(65536-1));					/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
}
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�A���X	�A���X�l�`�J�[�h
	-------------------------------------------------------
�����u�����̕������l�` -easy-�v
�A���X�̕������l�̂̐l�`���A��񕪗􂷂�7way�e�����B
4 x 7 x 7 == �ő� 196[�e](�d�X��)
3 x 7 x 7 == �ő� 147[�e](�͕핗)	//3 x 8 x 8 == 192
	-------------------------------------------------------
�����u�����̕������l�`�v
�A���X�̕������Z�̂̐l�`���A��񕪗􂷂�7way�e�����B
6 x 7 x 7 == �ő� 294[�e](�d�X��)
5 x 7 x 7 == �ő� 245[�e](�͕핗)	//5 x 8 x 8 == 320
	-------------------------------------------------------
�����u�����̕������l�` -hard-�v
�A���X�̕��������̂̐l�`���A��񕪗􂷂�7way�e�����B
8 x 7 x 7 == �ő� 392[�e](�d�X��)
9 x 7 x 7 == �ő� 441[�e](�͕핗)	//7 x 8 x 8 == 448
	-------------------------------------------------------
�����u�����̃I�����A���l�`�v�Ԓe���Βe
�A���X�̕��������̂̐l�`���A�O�񕪗􂷂�7way�e�����B
8 x 7 x 7 x 7 == �ő�2744[�e](�d�X��)
2 x 7 x 7 x 7 == �ő� 686[�e](�͕핗)	//9 x 8 x 8 == 576
---------------------------------------------------------*/
extern OBJ_CALL_FUNC(add_zako_alice_doll_type_a);/* �A���X�l�`�J�[�h */
local SPELL_EXEC(0b_alice_zako_doll)
{
	if (50 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_alice_doll_type_a(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	�v7�ɕ��􂷂�B
	-------------------------------------------------------
---------------------------------------------------------*/
#if 0
local void exchange_damnaku_alice_7_bunretu(void)
{
	int jj = 0;
	int ii;
	for (ii=0; ii<OBJ_POOL_00_TAMA_1024_MAX; ii++)/* �S�����ׂ�B */
	{
		OBJ *s;
		s = &obj99[OBJ_HEAD_00_0x0000_TAMA+ii];
		/* �F�Ɋ֌W�Ȃ��ؒe[ ... ]�Ȃ� */
		if (((BULLET_UROKO14_03_AOI+1) & 0xfff8) == (s->type & 0xfff8) )	/* [�ԗؒe]�Ȃ� */
		{
			jj++;
		//	jj &= 0x07; 	// 2 3 4 5	6 7 8 9
			jj &= 0x03; 	// 3 4 5 6
		//	s_change_meirin_yajirusi_one(s);
		//	s->tra65536 					= t256(6);		/* ���������e */
		//	s->tra65536 					= (jj<<8)+t256(2);	/* (2 ... 9) ���������e */
			s->tra65536 					= (jj<<8)+t256(3);	/* (3 ... 6) ���������e */
			/* (1�͒x�������̂ŏ��O) 9 ���Ƒ��߂��邩�� */
		}
	}
}
#endif
extern OBJ_CALL_FUNC(add_zako_alice_doll_type_b);/* �A���X�l�`�J�[�h */
local SPELL_EXEC(1e_alice_tama_doll)
{
	if (250 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_alice_doll_type_b(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))
	{
		/* �e���� */
//		exchange_damnaku_arice_7_bunretu();
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}
/*
// �����u�����̕������l�`�v
	�e�l�`��1�e����(�e)
	�O���Ɏˏo�B
//
	180�x���]����B
	�V�e�ɕ���(�e�����e)
  A   A    A   A   --- ���x����

		A------------- ���x��
		|
   A	|	 A	------ ���x�x��
		+
//
	180�x���]����B
	�V�e�ɕ���(���e���Ԓe)
  A   A    A   A   --- ���x����

		A------------- ���x��
		|
   A	|	 A	------ ���x�x��
		+
// �����u�����̃I�����A���l�`�v�̂�
	180�x���]����B
	�V�e�ɕ���(�Ԓe���Βe)
  A   A    A   A   --- ���x����

		A------------- ���x��
		|
   A	|	 A	------ ���x�x��
		+
//

*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�A���X	�z�K�q���ۂ�(?)�J�[�h
	-------------------------------------------------------
	�e�L�g�[
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�����B

---------------------------------------------------------*/

local SPELL_EXEC(25_alice_suwako)
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))/* 2���1�� */
	{
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))/*  8��1�� */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))/* 16��1�� */
		{
			VR08 -= (int)(65536*8/256);
			CPU_CALL(cpu_auto_bullet_play_default);
		}
	//	VR08 -= (65536/256);	/* 1����256���������p�x */
	//	VR08 -= (65536/512);	/* 1����256���������p�x�̔����B */
		VR08 -= (200);	/*	�e�L�g�[ 1����256���������p�x�̔����B */
		/* �e���� */
		{
			HATSUDAN_R11_speed256				= (t256(1.0) ); 					/* �e��(psp�̉�ʂ͋���) */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R16_n_way					= (8);								/* [8way] */			/* 8�����e */
			HATSUDAN_R17_div_angle65536 		= (65536/8);						/* �����p�x(�e�����Ȃ��͈͂�����32����) */	/* (ra_nd16>>4) == ����(0-4095) */
			//
			/* 0 [...��] 150 [...��+��] 180 [...��] 255 */
			if ((0) == (VR10_BOSS_SPELL_TIMER & 1))
			{
				if ((s32)(128+((cg_VR20_game_difficulty)<<2)) > (VR10_BOSS_SPELL_TIMER))
				{
					HATSUDAN_R12_speed_offset		= t256(2);			/* ���������e */	/* ���̕����ɂȂ邩������ */
					HATSUDAN_R13_angle65536 		= (VR08);			/* ���� */
					HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* �ԕĒe */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
				}
			}
			else
			{
				if ((s32)(128-((cg_VR20_game_difficulty)<<2)) < (VR10_BOSS_SPELL_TIMER))
				{
					HATSUDAN_R12_speed_offset		= t256(1);			/* ���������e */	/* ���̕����ɂȂ邩������ */
					HATSUDAN_R13_angle65536 		= (65536-VR08); 	/* ���� */
					HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* �Ēe */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
				}
			}
		}
	}
}
// ==================================== [�X�y�J���E] ==================================== //
