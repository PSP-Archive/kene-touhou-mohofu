
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	��d���̃J�[�h���`���܂��B
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g2�ʒ�-�{�X ��d�� �ʏ�U��1(1/3)
	-------------------------------------------------------
�΃N�i�C�e
������n�߂āA���v���A2�i�Â�
	-------------------------------------------------------
	�g2�ʒ�-�{�X ��d�� �ʏ�U��1(2/3)
	-------------------------------------------------------
�ԃN�i�C�e
������n�߂āA�����v���A2�i�Â�
����:Lunatic���ꉞ����48�����e�B(4��������o��2�i?3�i�ɐ���?)
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B
	R09 	aaa_temp_angleCCW65536
	R0a 	bbb
	R0b 	HATSUDAN_R16_n_way			[�j��]
	R0c 	HATSUDAN_R17_div_angle65536 [�j��]

	R0d 	�e�F
	R0e 	�e���Z�p�x
	-------------------------------------------------------
	VR03_i	���[�v�p i (��Փx�ʂɎc��񐔂�ݒ�B)
---------------------------------------------------------*/

local SPELL_EXEC(1a_1b_dai_yousei_midori_aka)
{
	static const u32 codebase[2] =
	{
		MCODE(OP0x02_COUNTER, 64, R08, NAX),
		NAX
	};
//	if ((64-(48))<((src->boss_spe ll_timer)))
	cpu_exec((u32*)&codebase, (1));
	if (16 < (VR08))
	{
	//	if (0x00==((src->boss_spe ll_timer)&(2-1)))/*(2���1��)*/
		{
			static const u32 codebase222[8] =
			{
				// (1) HATSUDAN_R12_speed_offset		= t256(1.0);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
				(int)(t256(1.0)),
				// (2) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
				(int)((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
				// (3)	HATSUDAN_R16_n_way = PACK_NAN_IDO_CONST((12), (14), (16), (20));	/* [12way] */
				MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
				PACK_NAN_IDO_CONST((1), (1), (4), (4)),
				// (4) VR0c 	= (int)(65536/(VR0b));			/* �����p�x(65536[360/360�x]�� VR0b ����) */	/* 1����n���������p�x */
				MCODE(OP0x17_DIV65536, NAX, R0c, R0b),// R0c = 65536 / R0b;/*(�����p�A�g�F)*/	/* �����p�x */
				// (5)	HATSUDAN_R15_bullet_obj_type	= (VR0d);	/* [ �e] */
				MCODE(OP0x01_MOVER_PD, NAX, R15, R0d),// �e�F
			//	NAX
			};
			cpu_exec((u32*)&codebase222, (5));
		//	for (VR03_i=0; VR03_i<(1+(unsigned)cg_VR20_game_difficulty); VR03_i++)/*(2�i�Â�)*/
			VR03_i = cg_VR20_game_difficulty;// (��Փx�ʂɎc��񐔂�ݒ�B)
		loop_i:
			{
				static const u32 codebase_exec333[9] =
				{
					// HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a<<2)+(VR03_i<<6));			/* �e�� */
					// (1) VR16 = (VR03_i << (6));
					MCODE(OP0x1f_ASLM_PD, (6), R16, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
					// (2) VR11 = (VR0a << (2));
					MCODE(OP0x1f_ASLM_PD, (2), R11, R0a),/*(�V���[�g�������A�h���b�V���O)*/
					// (3) VR11 += VR16;
					MCODE(OP0x04_ADDR_PD, NAX, R11, R16),
					// (4) VR11 += (t256(0.6));
					MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
					(t256(0.6)),	/* �e�� */
					// (5)	HATSUDAN_R13_angle65536 		= (VR09);
					MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
					// (6)	HATSUDAN_R16_n_way				= (VR0b);
					MCODE(OP0x01_MOVER_PD, NAX, R16, R0b),
					// (7)	HATSUDAN_R17_div_angle65536 	= (VR0c);
					MCODE(OP0x01_MOVER_PD, NAX, R17, R0c),
					// (8)	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
					MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
				};
				cpu_exec((u32*)&codebase_exec333, (8));
			}
			VR03_i--;/*(�c��񐔌��炷�B)*/if (0 < VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/
			VR09 += (VR0e);
			VR0a++;
		}
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(1a_dai_yousei_midori)
{
	VR09 = 0;
	VR0a = 0;
	VR0d = (BULLET_KUNAI12_BASE + TAMA_IRO_05_MIDORI);
	VR0e = (-(65536/48));
}
local SPELL_INIT(1b_dai_yousei_aka)
{
	VR09 = 0;
	VR0a = 0;
	VR0d = (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);
	VR0e = (65536/48);
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g2�ʒ�-�{�X ��d���e
	9�����e + 9����������ƌo�����玩�@�_�����e
	-------------------------------------------------------
	�H�����B90�x���炢�B
	�A�e�ƈ�葬�x�܂Ői�ނƎ��@�_���e�̃~�b�N�X�B
---------------------------------------------------------*/
local TAMA_FUNC(dai_yousei_danmaku_01_callback)/*  */
{
//	if (cnt < 80)/* 80�����͌��� */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[32]�J�E���g�����̒e */
	{
		/*(�������Ȃ�[�ʏ�e�Ɠ���])*/;
	}
	else
	{
		/* 32 �J�E���g�Ȃ�A���@�_���e�ɕϐg����B */
		set_REG_DEST_XY(src_tama);			/* �e��x256 y256 �eobj���S���甭�e�B */
		CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
		src_tama->tmp_angleCCW65536 = ((HATSUDAN_R13_angle65536));
		src_tama->rotationCCW65536 = ((src_tama->tmp_angleCCW65536)); /* �\���p�x */
		//------------------
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	}
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	-------------------------------------------------------
	VR0c	���@�_���p �ޔ�p
---------------------------------------------------------*/
local SPELL_EXEC(0d_dai_yousei_9_shot)
{
	static /*const*/ u32 codebase_exec[34] =
	{
	//	if (100 < (VR10_BOSS_SPELL_TIMER & 0x7f)) {return;}
	/* VR11, [�j��]*/
	// (1) VR11 = VR10 & 0x7f;
	MCODE(OP0x1d_ANDM_PD, 0x7f, R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (2) if (100 < VR11)) {goto qqq_4+26;}/*(�t���[�����番��B)*/
	MCODE(OP0x09_BFL_RS, (100), R11, (u8)(+31)),// (qqq_4+31:); 	/* ���߂� 28[frame]�͂��x�� */
	//------------------
	// (3)	//	VR04 = [];
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((19), (15), (11), ( 7)),
	// (4)	//	count_up_limit_NUM(R08, VR04);
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[���W�X�^�ԐڃA�h���b�V���O]*/, R08, R04/*[��Փx�ʒ萔]*/),
	// (5)	if (0 != VR08)	{return;}
	MCODE(OP0x08_BNE_RS, (0), R08, (u8)(+27)),// (qqq_4+27)
	/*(�{�X�X�y�J�̏ꍇ�̂ݏȗ��\�A���{�X�̏ꍇ�ȗ��ł��Ȃ�)*/
	/* �e��x256 y256 ���S���甭�e�B */
	// ���@�_���p�쐬�B
	// (6)	(calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */ /* �e��x256 y256 �{�X�̒��S���甭�e�B */
	MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	// (7) VR0c 		= (HATSUDAN_R13_angle65536) */
	MCODE(OP0x01_MOVER_PD, LONG_MEMORY_ADDRESSING, R0c, R13),// �ޔ�: stack(VR0c) = VR13;
	/*----[ �_���e ]----*/
	/* VR11, VR12[�j��]*/
	// (8) VR11 = (cg_VR20_game_difficulty << 6);
	MCODE(OP0x1f_ASLM_PD, (6), R11, R20_PLAYER_DATA_game_difficulty),/*(�V���[�g�������A�h���b�V���O)*/
	// (9) HATSUDAN_R11_speed256			+= (t256(2.0));//(t256(3.0));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
	(t256(2.0)),
	// (10) HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3/*6*/)),/*(�e�X�g)*/
	//	HATSUDAN_R13_angle65536 		= ((HATSUDAN_R13_angle65536));
	//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT)),
	// (12) HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE + TAMA_IRO_03_AOI);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
	// (13) HATSUDAN_R16_n_way				= (9);
	MCODE(OP0x01_MOVER_PD, (u8)(+9), R16, NAX),/*(�C���f�b�N�X�t)*/
	// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/24);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/24),
	// (15)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	/*----[ ���i�e ]----*/
	// (16) HATSUDAN_R13_angle65536 		= (VR0c) */
	MCODE(OP0x01_MOVER_PD, LONG_MEMORY_ADDRESSING, R13, R0c),// ����: VR13 = stack(VR0c);
	// (17) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT)),
	// (18) HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE + TAMA_IRO_03_AOI);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_KOME_BASE + TAMA_IRO_00_SIRO)),
	// (19) HATSUDAN_R16_n_way				= (9);
	MCODE(OP0x01_MOVER_PD, (u8)(+9), R16, NAX),/*(�C���f�b�N�X�t)*/
	// (20) HATSUDAN_R17_div_angle65536 	= (int)(65536/24);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/24),
	// (21)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	/*--------*/
	// (22) AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* �e�L�g�[ */
	MCODE(OP0x1c_MOVEM_PD, TRACK04_TEKIDAN, R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (23) AUDIO_18_voice_number	= VOICE15_BOSS_KOUGEKI_01;
	MCODE(OP0x1c_MOVEM_PD, VOICE15_BOSS_KOUGEKI_01, R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (24)  (cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
// (qqq_4+27:) (qqq_4+31:)
	// (25)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (24));/* �e�L�g�[ */
}
// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g4�ʒ�-�{�X ������ �ʏ�U��1
	-------------------------------------------------------
	����ʒe�B8�����B1/24�������v���ɉ�]�B
	�N�i�C�e�B�o���}�L�B
	-------------------------------------------------------
	����ʒe�B�͖����̂ő���ɐ�ʒe�ŁB
	-------------------------------------------------------
	������Ƌx��ŁA���͋t����i����ĂȂ��j
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B
	R09 	�p�x1�����p�B
	R0a 	�����B
	R0b 	�������Z�p(�e�L�g�[)
---------------------------------------------------------*/
local SPELL_EXEC(1f_koakuma)
{
//	if (64 == VR10_BOSS_SPELL_TIMER) /* �n�߂ɏ����� */
	static const u32 codebase_exec[45] =
	{
	// (1) counter(192, VR08);
	MCODE(OP0x02_COUNTER, 192, R08, NAX),	/*	�J��Ԃ��J�E���^�B */
	// (2) if (1 != VR08) {goto aaa+9:}/* �n�߂ɏ����� */
	MCODE(OP0x08_BNE_RS, (1), R08, (u8)(+9)),// (aaa+9)
	// (3) VR09 = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R09, NAX),//
	(0),
	// (4) VR0a = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R0a, NAX),//
	(0),
	// (5) VR0b = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R0b, NAX),//
	(0),
	// (6) AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"�{�X����1",		/* r	�����[�� */
	MCODE(OP0x1c_MOVEM_PD, (VOICE17_BOSS_TAME01), R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (7) AUDIO_19_voice_truck = TRACK03_IVENT_DAN;
	MCODE(OP0x1c_MOVEM_PD, (TRACK03_IVENT_DAN), R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (8)	(cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
// (aaa+9:)
	//	if (0 != (VR08 & 0x0f) ) {goto bbb;}/* 16���1��Ȃ猂�� */
	// (9) VR11 = (VR08 & 0x0f);
	MCODE(OP0x1d_ANDM_PD, 0x0f, R11, R08),/*(�V���[�g�������A�h���b�V���O)*/
	// (10)
	MCODE(OP0x08_BNE_RS, (0), R11, (u8)(+16)),// (bbb+16)
	// (11) HATSUDAN_R11_speed256			= (t256(1.0));			/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(1.0)),
	//	HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
	// (12) HATSUDAN_R12_speed_offset		= t256(5);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(5)),
	// (13) HATSUDAN_R13_angle65536 		= (VR09);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
	// (14) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
	// (15) HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI); 	/* [��ʒe] ���������� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_OODAMA32_00_AOI),
	// (16) HATSUDAN_R16_n_way				= (8);							/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (17) HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 			/* �����p�x(65536[360/360�x]�� 8 ����) */	/* 1����n���������p�x */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(8)),
	// (18)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (19) VR09 += ((65536/24)-256);	/* ����(1��/24)�𑫂��B(+-256�����𑫂�) */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),/*(�����O�������A�h���b�V���O��p����)*/
	(((65536/24)-256)),
	// (20) VR09 += (VR0b); 	/* �������Z�p */
	MCODE(OP0x04_ADDR_PD, NAX, R09, R0b),
// (bbb+16:)
	// (21)if (0 != (VR08 & 0x01) ) {goto ccc;} /* 2���1��Ȃ猂�� */
	// (21) VR11 = (VR08 & 0x01);
	MCODE(OP0x1d_ANDM_PD, 0x01, R11, R08),/*(�V���[�g�������A�h���b�V���O)*/
	// (22)
	MCODE(OP0x08_BNE_RS, (0), R11, (u8)(+13)),// (ccc+13)
	// (23) HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(1.5)),/*(�e�X�g)*/
	// (24) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (25) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI);			/* [���Ēe] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI),
	// (26) HATSUDAN_R11_speed256			= (t256(1.0));		/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(1.0)),
	// (27) VR0a = ra_nd();
	MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
	// (28) VR0b = VR0a & 0x01ff;/*(0 ... 511)*/
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0a),
	(0x01ff),/*(0 ... 511)*/
	// (29) HATSUDAN_R13_angle65536 		= (VR0a);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (30) (1�e����)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
// (ccc+13:)
	// (31)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (30));//
}
