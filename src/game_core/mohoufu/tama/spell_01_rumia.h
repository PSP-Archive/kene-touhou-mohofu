
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���[�~�A�̃J�[�h���`���܂��B
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�� ���� �G��(�d��) �u7�����e�v[Normal]
	-------------------------------------------------------
	1����10�������A7�����B(180(5/10)+(1/10))
	7�����ɕ����B���S�����@�_���e�B
	-------------------------------------------------------
	�Ԓe�̂݁B
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�� ���� ���[�~�A �u16����3�A�e�v
	-------------------------------------------------------
	16�����ɕ����B
	-------------------------------------------------------
	�p�^�[���� 3��� ����B
	case 1: ��e.�g�t�Βe�A��e.�g�t���e�B
	case 2: ��e.�g�t�e�A��e.�Ȃ��B
	case 3: ��e.�g�t�e�A��e.�g�t�Ԓe�B
	-------------------------------------------------------
---------------------------------------------------------*/



// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�� ���� ���[�~�A �u14����5�A�e�v
	-------------------------------------------------------
	14�����ɕ����B
	R08 �e�F
---------------------------------------------------------*/
local SPELL_EXEC(03_lumia02_douchuu)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))
	{
		if ((64-14) < VR10_BOSS_SPELL_TIMER)
		{
			HATSUDAN_R13_angle65536 			= ((64+VR10_BOSS_SPELL_TIMER)<<11); /* x 2048 */				/* �e���p�x65536 */
				{
	static /*const*/ u32 codebase_exec[14] =
	{
		// (01) HATSUDAN_R15_bullet_obj_type		= (VR08);			/* [�e] */
		MCODE(OP0x01_MOVER_PD, NAX, R15, R08),
		// (02) HATSUDAN_R15_bullet_obj_type		+= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);			/* [�e] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),/*(�����O�������A�h���b�V���O��p����)*/
		(BULLET_MARU10_BASE + TAMA_IRO_03_AOI),
		// (03) HATSUDAN_R11_speed256				= (t256(0.75)); 		/* �����͒ᑬ�e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
		(t256(0.75)),
		// (04) HATSUDAN_R12_speed_offset			= t256(15);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(15)),/*(�e�X�g)*/
		// (05) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (06) HATSUDAN_R16_n_way					= (16); 							/* [16way] */
		MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (07) HATSUDAN_R17_div_angle65536 		= (int)(65536/14);		/* �����p�x(65536[360/360�x]�� 14 ����) */	/* 1����n���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(14)),
		// (08)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (09)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	};
	cpu_exec((u32*)&codebase_exec, (9));
				}
			VR08++;
		}
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�� ���� ���{�X ���[�~�A �u16�����e+3�A16�A�e�v
	-------------------------------------------------------
	16�����ɘg�t�e�B
	���@�_�� 3�����ɐԕĒe 16�A�e�B�Ԋu�����B
	-------------------------------------------------------
	R0c 	�o���Ƃ��p�x�Baaa_angle65536
---------------------------------------------------------*/
	#if 0/*(����)*/
	if (SPELL_TIME_0064-(2*16) < VR10_BOSS_SPELL_TIMER)
	{
		if ((SPELL_TIME_0064-1)!=VR10_BOSS_SPELL_TIMER) {goto rendan16;}
	//	{
		// hard 18����(1��)
		// Luna 36����(2��)
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
		VR0c = VR13;/*(���@�_���p�x���o���Ƃ�)*/
		//
		HATSUDAN_R11_speed256			= (t256(2.0));				/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [�g�t���ےe] */
		HATSUDAN_R16_n_way				= (16);// (36);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16));// (int)(65536/(36));	/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		CPU_CALL(cpu_auto_bullet_play_default);
	//	}
	rendan16:
		if (0!=(VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2���1��)*/
		HATSUDAN_R13_angle65536 		= VR0c;/*(�o���Ƃ������@�_���p�x���g��)*/
		HATSUDAN_R11_speed256			= (t256(3.0)) + (VR10_BOSS_SPELL_TIMER<<3); 			/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(1) ;/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [�ԕĒe] */
		HATSUDAN_R16_n_way				= (3);// (3);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));// (int)(65536/(36)); /* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	osimai:
		;
	}
	#endif
local SPELL_EXEC(4d_rumia_3nerai)
{
	// SPELL_TIME_0064
	//
	static /*const*/ u32 codebase_exec[35] =
	{
		// (1)	if (SPELL_TIME_0064-(2*16) < VR10_BOSS_SPELL_TIMER) {goto osimai+32;}else{goto osimai;/*�������Ȃ�*/}
		MCODE(OP0x09_BFL_RS, (SPELL_TIME_0064-(2*16)), R10, (+1)),//(start+1) �n�� �t���[�����番��
		// (2)	else	{goto osimai;/*�������Ȃ�*/}// �����܂�
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	//(start+1:)
		// (3)	if ((SPELL_TIME_0064-1) != VR10_BOSS_SPELL_TIMER) {goto rendan16;}
		MCODE(OP0x08_BNE_RS, (SPELL_TIME_0064-1), R10, (u8)(15)),// (rendan16+15)
		// hard 18����(1��)
		// Luna 36����(2��)
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		// (4)	 (calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		// (5)	VR0c = VR13;/*(���@�_���p�x���o���Ƃ�)*/
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		// (6) HATSUDAN_R11_speed256			= (t256(2.0));				/* �e�� */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
		(t256(2.0)),
		// (7) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(1)),
		// (8) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (9) HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [�g�t���ےe] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_WAKU12_BASE + TAMA_IRO_03_AOI),
		// (10) HATSUDAN_R16_n_way				= (16);/* [nway] */
		MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (11) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16));	/* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(16)),
		// (12)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (13)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//(rendan16+15:)
		//		if (0 != (VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2���1��)*/
		// (14) VR11 = VR10 & 0x01;VR11 = (VR10_BOSS_SPELL_TIMER & 0x01);
		MCODE(OP0x1d_ANDM_PD, (0x01), R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (15) if (0 != VR11) {goto osimai;}/*(2���1��)*/
		MCODE(OP0x08_BNE_RS, (0x00), R11, (u8)(14)),//	(osimai+14)
		// (16) HATSUDAN_R13_angle65536 		= VR0c;/*(�o���Ƃ������@�_���p�x���g��)*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (17) HATSUDAN_R11_speed256 = (VR10_BOSS_SPELL_TIMER << 3);			/* �e�� */
		MCODE(OP0x1f_ASLM_PD, 0x03, R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (18) VR11 += t256(3.00);/* �e�� */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(�����O�������A�h���b�V���O��p����)*/
		(t256(3.00)),
		// (19) HATSUDAN_R12_speed_offset		= t256(1) ;/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(1)),
		// (20) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (21) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [�ԕĒe] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_KOME_BASE + TAMA_IRO_01_AKA),
		// (22) HATSUDAN_R16_n_way				= (3);// (3);/* [nway] */
		MCODE(OP0x1c_MOVEM_PD, (3), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (23) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));// (int)(65536/(36)); /* �����p�x(65536[360/360�x]�� 64 ����) */	/* 1����n���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(16*5)),
		// (24)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	//(osimai+14:)//(osimai+32:)// �����܂�
		// (25)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (24));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�ʃ{�X ���[�~�A �镄�u�i�C�g�o�[�h�v�ɂ�����Ƃ��������J�[�h(�\��)
	-------------------------------------------------------
	5�e�ڂ����@�_���� 32����16���� �|��e�B
	-------------------------------------------------------
---a aaaa [aaa]
0000 xxxx 16�� ���� 		�F (0x00==((time_out)&0x20))
0001 0000 ���@�_���p�쐬	�F (0x00==((time_out)&0x20))
0010 xxxx 16�� ���� 		���F
0011 0000 ���@�_���p�쐬	���F
0100 xxxx 16�� ���� 		�F (0x00==((time_out)&0x20))
0101 0000 ���@�_���p�쐬	�F (0x00==((time_out)&0x20))
0110 xxxx 16�� ���� 		���F
0111 0000 ���@�_���p�쐬	���F
//
1000 0000 start
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^1�B
	R09 	�J�E���^2�B
	R0a 	�e�̊�p�x�Baaa_angle65536
	R0b 	�e�ԍ��B0x0f��1�e�ځA0x0e��2�e�ځB
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_EXEC(08_rumia_night_bird)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 32, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));
//	if (0x10 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* ���@�_���p�쐬 */
	if (1==(VR08))/* ���@�_���p�쐬 */
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 2, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));/*(�J�E���^2)*/
		#if 1
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */
		VR0a = HATSUDAN_R13_angle65536;/* ���@�_���p */
		#endif
		//	2048 == (65536)/(32)		: 1����32���������p�x�B
		//	8192 == (2048) * (4)		: 5�e��(4�e���̕�)�B
		// 57344 == (65536) - (8192)	: �J�n�p�x�B(���Z���Ȃ��ƌ덷���o��B)
	//	VR0a += (const int)(65536-(int)((65536*4)/(32)));/* 5�e�ڂ����@�_�� */
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
		if (1==(VR09))/*(�J�E���^2)*/
				{VR0a += (57344);}/* 5�e��(4�e���̕�)�����@�_��(65536-(4*(65536/32))) */
		else	{VR0a += (8192);}/* 5�e��(4�e���̕�)�����@�_��(65536+(4*(65536/32))) */
		mask65536(VR0a);
		/* �p�x(65536[360/360�x]�� 32����) */
		VR0b = 0x10;
	}
//	else
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x10))/* 16�� ���� */
	if (15<(VR08))/* (16 ... 31), 16�� ���� */
	{
		{
			/* ���� */
			VR0b -= (1);
		//	VR0b = (VR10_BOSS_SPELL_TIMER & 0x0f);
			#if (0)/* �f�o�b�O(���@�_���e�̐F��ς���) */
			if (0x0b==VR0b)/* 0x0b==5�e�� (0x0f��1�e�ڂ�����0x0b��5�e��) */
						{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);}/* �g���ԐF�e �F�ς���B */
			else
			#endif
			#if 1
			{
			//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
				if (1==(VR09))/*(�J�E���^2)*/
						{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);}/* �g���F�e */
				else	{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_04_MIZU_IRO);}/* �g�����F�e */
			}
			#endif
		//	HATSUDAN_R11_speed256			= (t256(1.5));								/* �e�� */
			HATSUDAN_R11_speed256			= (t256(0.75))+((16-(VR0b))<<5);	/* �e�� */
			/* �e�� 0.75 - 2.75 �{ */
			HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
			HATSUDAN_R13_angle65536 		= (VR0a);	/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			/* [�g�t���F�e] [�g�t�����F�e] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
		/* ���̒e�̊p�x */
		//	 2048 == (65536)/(32)		: 1����32���������p�x�B
		//	63488 == (65536) - (2048)	: ���Z�̏ꍇ(���Z���Ȃ��ƌ덷���o��B)
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
		if (1==(VR09))/*(�J�E���^2)*/
				{VR0a += (2048);}/* �p�x(65536[360/360�x]�� 32����) (int)(65536/(32)); */
		else	{VR0a += (63488);}/* �p�x(65536[360/360�x]�� 32����) (65536)-(int)(65536/(32)); */
		mask65536(VR0a);
		//
			static const u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase888, (1));
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g1�ʃ{�X ���[�~�A �ŕ��u�f�B�}�[�P�C�V�����v�ɂ�����Ƃ��������J�[�h(�\��)
	-------------------------------------------------------
	���[�~�A�����e:
	�����e�ɂ��ǂ�����Ǝ�ނ�����悤�ȋC�����Ă����B
	�ŕ��u�f�B�}�[�P�C�V�����v�̌����e�́B
		1. ��苗���ɔ�яo���B(�ʏ팸���e)
		2. �e��~�B
		3. �ˑR (�e�O����)90�x��]����B(�ɍ��E���݂����Ȋ����Ŋ��炩�ł͂��邪�A���΂₭��])
		4.�e�O�����X���Ȃ���e���L����B
	-------------------------------------------------------
	16
	-------------------------------------------------------
	0010 01--	0x027f == 64*10-1
	0010 00--	0x023f == 64* 9-1
				...
	0000 00--	0x003f == 64* 1-1
	-------------------------------------------------------
640==0x280
512==0x200
[15]	32*0		�T
[14]	32*1		�U
[13]	32*2		�R
[12]	32*3		�S
[11]	32*4		�P
[10]	32*5		�Q
[09]	32*6		�x��
[08]	32*7		�x��
[07]	32*8		�x��
[06]	32*9			�Ԓe
[05]	32*10		�x��
[04]	32*11			�Βe
[03]	32*12		�x��
[02]	32*13			�e
[01]	32*14		�x��
[00]	32*15		�x��

---------------------------------------------------------*/


/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
	�����e�B���v���B
256 ... 	: 8[0x07<<5] RUMIA_normal: �ʏ�e�֕ϐg����
224 ... 255 : 7[0x08<<5] RUMIA_kousa: �����e
192 ... 223 : 6[0x09<<5] RUMIA_kousa: �����e
160 ... 191 : 5[0x0a<<5] RUMIA_kousa: �����e
128 ... 159 : 4[0x0b<<5] RUMIA_kousa: �����e
128 ... 159 : 4[0x0b<<5] RUMIA_kousa: �����e
 64 ...  95 : 2[0x0d<<5] RUMIA_kousa: �����e
 32 ...  63 : 1[0x0e<<5] RUMIA_rot:   �}���ɋȂ���B
  0 ...  31 : 0[0x0f<<5] RUMIA_nop	  ���e��A�����͉������Ȃ�
x---------------------------------------------------------*/
local TAMA_FUNC(rumia_danmaku_01_callback)
{
	#if (1)/*(ok!)*/
	const void *aaa[8] =
	{
&&RUMIA_nop, // [�K�v]�����Ɠ��삵�Ȃ��B
&&RUMIA_normal, //
&&RUMIA_kousa, //
&&RUMIA_kousa, //

&&RUMIA_kousa, //
&&RUMIA_kousa, //
&&RUMIA_rot, // �}���ɋȂ���B
&&RUMIA_nop, // ���e��A�����͉������Ȃ�		;/* ���e��A�����͉������Ȃ�==���i�e */
	};
	goto *aaa[(src_tama->jyumyou & (0x07<<5))>>5];
	#endif
RUMIA_normal:
		/* (�ʏ�e�֕ϐg����==��ʓ��ł͒e�͏����Ȃ�) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		goto RUMIA_nop;
RUMIA_rot:
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			/*(�͕핗�ł͉�CCW�Ȃ̂ŁA�������������v���)*/
		//	{src_tama->rotationCCW1024 += (10);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
			{src_tama->rotationCCW65536 += (10<<6);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
		else
			/*(�͕핗�ł͉�CCW�Ȃ̂ŁA�����������v���)*/
		//	{src_tama->rotationCCW1024 -= (10);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
			{src_tama->rotationCCW65536 -= (10<<6);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
		goto RUMIA_nop;
RUMIA_kousa:
	//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
	//			{src_tama->rotationCCW1024++;}/*(�����e�Ȃ̂ŋȂ���)*/
	//	else	{src_tama->rotationCCW1024--;}/*(�����e�Ȃ̂ŋȂ���)*/
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
				{src_tama->rotationCCW65536 += (1<<6);}/*(�����e�Ȃ̂ŋȂ���)*/
		else	{src_tama->rotationCCW65536 -= (1<<6);}/*(�����e�Ȃ̂ŋȂ���)*/
RUMIA_nop:
		;
	//
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}


	#if (0)
	/* ���e�� 512 �J�E���g�ȏ�͒e�������B */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
	#endif


/*---------------------------------------------------------
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
	�A�e�B���@�_���B
	-------------------------------------------------------
	���@��_��Ȃ��ꍇ�����邪�A�������ǂ�������Ȃ��B
---------------------------------------------------------*/
local TAMA_FUNC(rumia_danmaku_02_callback)/* �A�e */
{
	/* 32 �J�E���g�Ȃ� */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[32]�J�E���g�o�߂����e */
	{
		VR06	= (src_tama->center.x256);
		VR07	= (src_tama->center.y256);
		CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
		#if 0
		/*(�_��)*/
	//	src_tama->rotationCCW1024 = (0);//�`��p�p�x(deg65536to1024(HATSUDAN_R13_angle65536));/* ���@�_���p */
		#else
		/*(���ʃP�[�X�A���̂܂�(������)�̊p�x�ňړ�����)*/
	//	src_tama->rotationCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));/* ���@�_���p */
		src_tama->rotationCCW65536 = ( (HATSUDAN_R13_angle65536));/* ���@�_���p */
		/* �����̕`��p�p�x�͌�ŗ��p����B */
		#endif
		//
		src_tama->TR01_hatudan_speed65536	= (t256(2.0)<<8);			/* �e�� */
		//
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}


/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	-------------------------------------------------------
	R08 	�J�E���^�B(32���1�񔭒e����)
	R09 	�J�E���^�B(16���)
	R0a 	x[���[�N�ňꎞ�g�ptemp]
	R0b 	[�ꎞ�g�ptemp]�e�p�x(�����e)�B	�e�p�x(�A�e)�B
	R0c 	���@�_���p�x�ۑ��p
	R0d 	��Փx�萔1(�������A�����e[32])
	R0e 	��Փx�萔2(�����p�A�����e[65536/32])
	-------------------------------------------------------
	R15 	�e�F(�����e)�B
	-------------------------------------------------------
	VR03_i	���[�v�p i (��Փx�ʂɎc��񐔂�ݒ�B)
---------------------------------------------------------*/

// �J�[�h�X�N���v�g��ł́uelse�v�͖����B
local SPELL_EXEC(29_rumia_demarcation)
{
	static const u32 codebase_exec[90/*-6*/] =
	{
		// (01) counter(32, VR08);	//if ((0x1f)==(VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x02_COUNTER, 32, R08, NAX),
		// (02) if (0 != VR08)	{goto oyasumi+0;}
		MCODE(OP0x08_BNE_RS, (0), R08, (u8)(+57)),// (oyasumi+38)
		// (03) counter(16, VR09);
		MCODE(OP0x02_COUNTER, 16, R09, NAX),
		/*---- ----*/
		// (04) VR16 = hairetu[VR09];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R09, R16, (+16)),
		(+38), (+38), (+39), (+38),//(oyasumi+38:)		/* ���x�� */
		(+39), (+38), (+39), (+38),// (kousadan+39:)
		(+38), (+38), (+0), (+0), // �A�e(rendan+0:)
		(+0), (+0), (+0), (+38), /* �Ō�̕��͎��Ԃ�����Ȃ��̂ŁA�ϐg�������Ԃɍ���Ȃ��B */
		// (05)
		MCODE(OP0x06_BRAR_NN, NAX, NAX, R16),	// �����3. VRB �̑��΃A�h���X�ɃW�����v�B
		/*---- ----*/
		// (06) if (9 < VR09)	/* [10 ... 14] ���@�_���A�e */
		//	dimmer_shot_02_rendan();
		/* �� ���@�_���A�e: �L�������ō�肪���Ȃ̂ŁA����Ń`�F�b�N�Bnormal�̏ꍇ�A���ł���A�e�͂S�񂾂����B */
	//(rendan+0:)
		// ���@�_���p�쐬�B
		// (06) (calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */ /* �e��x256 y256 �{�X�̒��S���甭�e�B */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		//	VR0c = HATSUDAN_R13_angle65536;/* ���@�_���p(�ꎞ�ۑ�) */
		// (07) VR0c = VR13;/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		// (08) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_02)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(�����O�������A�h���b�V���O)*/
		((DANMAKU_LAYER_02)|(TAMA_SPEC_8000_NON_TILT)),
		// (09) HATSUDAN_R15_bullet_obj_type	= BULLET_WAKU12_BASE + TAMA_IRO_03_AOI; 		/* [�g�t���F�e] [�g�t�����F�e] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
		(BULLET_WAKU12_BASE + TAMA_IRO_03_AOI),
		// (10) VR02_j = 6;/*(r41-�x�����邩�� 6�� �ɏC���B 8 �񃋁[�v���Ēǉ�)*/
		MCODE(OP0x1c_MOVEM_PD, (6), R02_j, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	//	MCODE(OP0x1c_MOVEM_PD, (8), R02_j, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	//		loop_j:
		//		HATSUDAN_R12_speed_offset			= (VR02_j << 6);//t256(0);/*(�e�X�g)*/
		// (11) HATSUDAN_R12_speed_offset			= (VR02_j << 8);//t256(0);/*(�e�X�g)*/
		MCODE(OP0x1f_ASLM_PD, 0x08, R12, R02_j),/*(�V���[�g�������A�h���b�V���O)*/
		// (12) VR0b = VR0c;/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R0c),
		// (13) VR0a = ((VR10) & 0x20);
		MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (14) if (0 != VR0a) {goto (aaa+3);}// if (0==VR0a) {goto (aaa+3);}
		MCODE(OP0x08_BNE_RS, (0), R0a, (+3)),//
		// (15) {VR0b += (57344);}/* �p�x(65536[360/360�x]�� 32����) (int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(57344),
		// (16) goto (bbb+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
//aaa+3:// (17) else {VR0b += (8192);}/* �p�x(65536[360/360�x]�� 32����) (65536)-(int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(8192),
//bbb+2:// (18) (811aaa8 or bbb9)	mask65536(VR0b);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0b),
		(0xffff),
		// (19) VR03_i = 16;/*(16 �񃋁[�v���Ēǉ�)*/
		MCODE(OP0x1c_MOVEM_PD, (16), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		//	loop_i://	(ddd-16)loop_i:;
		//	VR11 = VR03_i;
		//	HATSUDAN_R11_speed256				= (t256(1.5));								/* �e�� */
		//	HATSUDAN_R11_speed256				= (t256(0.75)) + ((16 - VR0a) << 5);		/* �e�� */
		//	VR11 = (16 - VR11);
		// (20) VR11 = (VR03_i << 5);
		MCODE(OP0x1f_ASLM_PD, 0x05, R11, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
		// (21) VR11 = VR11 + (t256(0.75));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(�����O�������A�h���b�V���O��p����)*/
		(t256(0.75)),
		// (22) HATSUDAN_R13_angle65536 		= (VR0b);/* ���@�_���p */	/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (23) (1�e����)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		// (24) VR0a = ((VR10) & 0x20);
		MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (25) if (0 != VR0a) {goto (aaa+3);}// if (0==VR0a) {goto (aaa+3);}
		MCODE(OP0x08_BNE_RS, (0), R0a, (+3)),//
		// (26) {VR0b += (2048);}/* �p�x(65536[360/360�x]�� 32����) (int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(2048),
		// (27) goto (bbb+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
//aaa+3:// (28) else {VR0b += (63488);}/* �p�x(65536[360/360�x]�� 32����) (65536)-(int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(63488),
//bbb+2:// (29) (19aaa8 or bbb9) mask65536(VR0b);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0b),
		(0xffff),
		// (30) VR03_i--;/*(�c��񐔌��炷�B)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
		// (31) if (0 != (s32)VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/if (0 < (s32)VR03_i) {goto loop_i;}
		MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-16)),//	(ddd-16)loop_i:;
		// (32) VR02_j--;/*(�c��񐔌��炷�B)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R02_j, R02_j), /*(�C���f�b�N�X�t)*/
		// (33) if (0 != (s32)VR02_j) {goto loop_j;}/*(�c��񐔂�����΃��[�v�B)*/if (0 < (s32)VR02_j) {goto loop_j;}
		MCODE(OP0x08_BNE_RS, (0x00), R02_j, (u8)(-30)),//	(ddd-16)loop_i:;
		// (34)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
		// (35)
	//oyasumi+38:
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	//	goto oyasumi;
	//	kousadan+39:
		/* �� �����e�B �e / �Βe / �Ԓe */
		/*---- ----*/
		#if 0// ��Փx�f�R�[�h���߁B(�g����.A)
		// (01) VR15 = (VR09 >> 1);
		MCODE(OP0x1e_ASRM_PD, 0x01, R15, R09),/*(�V���[�g�������A�h���b�V���O)*/
		// (02) VR15 = [��Փx�ʒ萔];
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R15, R15(�g����.A)/*NAX*/),/*(�������A�����e)*/
		PACK_NAN_IDO_CONST((0), (TAMA_IRO_03_AOI), (TAMA_IRO_05_MIDORI), (TAMA_IRO_01_AKA)),	/* ������(r41-) */
		#else
		// (36) VR15 = hairetu[VR09];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R09, R15, (+8)),// (+16)
		(0), (0),
		(TAMA_IRO_03_AOI), (0),
		(TAMA_IRO_05_MIDORI),  (0),
		(TAMA_IRO_01_AKA), (0),
	//	(0), (0), (0), (0),// ��΂ɂ��Ȃ��̂ŃP�`��B
	//	(0), (0), (0), (0),// ��΂ɂ��Ȃ��̂ŃP�`��B
		#endif
		/*---- ----*/
		// (37) [40]VR0b = (VR15 & 0x06);
		MCODE(OP0x1d_ANDM_PD, 0x06, R0b, R15),/*(�V���[�g�������A�h���b�V���O)*/
		//	0x06,
		// (38) VR0b = (VR0b << 8);
		MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(�V���[�g�������A�h���b�V���O)*/
		//	0x08,
		// (39) HATSUDAN_R15_bullet_obj_type		+= BULLET_KOME_BASE;		/* [�g���F�e] [�g�����F�e] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),/*(�����O�������A�h���b�V���O��p����)*/
		BULLET_KOME_BASE,
		// (40) HATSUDAN_R11_speed256		= t256(1.0);/* �e�� (t256(1.5)) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
		(t256(1.0)),
		// (41) HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
		(t256(0)),
		// (42) HATSUDAN_R13_angle65536 		= (VR0b);/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (43) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_0000_TILT),
		// (44) HATSUDAN_R16_n_way = VR0d;	/* [32way] */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
		// (45) HATSUDAN_R17_div_angle65536 = VR0e; /* �����p�x(65536/32 ) �P����32���������p�x */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
		// (46)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (47) HATSUDAN_R13_angle65536 		= (VR0b);/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (48) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT),
		// (49)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (50)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
		// (51)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (4096));/*(�e�L�g�[�����Ǒ�̂��ꂭ�炢�B������ƕ��׍������邩�ȁH)*/
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
	/* ��L�^�C�v */
local SPELL_INIT(29_rumia_demarcation)
{
	static const u32 codebase_init[3] =
	{
		// (01) // R0d = ��Փx�ʒ萔1;(�������A�����e[32])
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(�������A�����e)*/
		PACK_NAN_IDO_CONST((12), (20), (32), (48)), 	/* ������(r41-) */
		// (02) // R0e = 65536 / R0d; = ��Փx�ʒ萔2;(�����p�A�����e[65536/32])
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(�����p�A�����e)*/ 	/* �����p�x */
	//	NAX/*(�������I��)*/
	};
	cpu_exec((u32*)&codebase_init, (2));//
}
	//	PACK_NAN_IDO_CONST((24), (28), (32), (32)), 	/* ������(-r40) */
	/*
	LUNATIC:
		(48)�Ȃ�A���_���A�e�ɂ����Ă���̔������B
		(�����e��)���Ă��(64)�]�T�B(�����e��)���ĂȂ���(���_���A�e�ɂ����)���ʁB
		�܂� 2�ʂł����A�g�[�^���ōl���� (48) �̕����ǂ����ȁH
		(64)���� LUNATIC �݂����ɂȂ����Ⴄ�B���� LUNATIC �Ȃ�ł����B
	*/

/*
	(r41-)�̒������j(�\��):
	EASY:		�����e�͔������Ȃ�(�ƒf��)�B�e���V���[�̊�{�I�Ȕ�������m��Ȃ�(�ƒf��)�B�� EASY �� �e���֌W�Ȃ��āA��Փx�����ĕ��ʂ̃V���[�e�B���O�ɂ��鎖�ɂ��悤�B
	NORMAL: 	�����e�͔��������������ĂȂ�(�����ĂȂ���������x�������)�B�e���V���[�͂�����������������B
	HARD:		�����e�͔�������(��������m���Ă�)�B �e���V���[(�Ɠ���projyect)��(���₭�����I��)��������m���Ă�B(�͕핗�ł� HARD �� ����NORMAL)
	LUNATIC:	�����e�͊ȒP(�����ǎ�Ƀ~�X��)�B(���Ă��100%�������悤�ɒ���) HARD �� ������Ȃ��l�����B(HARD �͓���o���Ȃ�)
*/

	//{
	//	#define P0x80		0x80
	//	#define YASUMI000	0x00
	//	const u8 ttt[16] =
	//	{
	//	/*0x0f*/0	YASUMI000,	/* �x�� */
	//	/*0x0e*/1	YASUMI000,	/* �x�� */
	//	/*0x0d*/2	(BULLET_KOME_03_AOI    - BULLET_KOME_00_SIRO),		/* �e */
	//	/*0x0c*/3	YASUMI000,	/* �x�� */
	//	/*0x0b*/4	(BULLET_KOME_05_MIDORI - BULLET_KOME_00_SIRO),		/* �Βe */
	//	/*0x0a*/5	YASUMI000,	/* �x�� */
	//	/*0x09*/6	(BULLET_KOME_01_AKA    - BULLET_KOME_00_SIRO),		/* �Ԓe */
	//	/*0x08*/7	YASUMI000,	/* �x�� */
	//	/*0x07*/8	YASUMI000,	/* �x�� */
	//	/*0x06*/9	YASUMI000,	/* �x�� */
	//	/*0x05*/10	P0x80,	/* ���@�_���A�e */
	//	/*0x04*/	P0x80,	/* ���@�_���A�e */
	//	/*0x03*/	P0x80,	/* ���@�_���A�e */
	//	/*0x02*/	P0x80,	/* ���@�_���A�e */
	//	/*0x01*/	P0x80,	/* ���@�_���A�e */
	//	/*0x00*/	P0x80,	/* ���@�_���A�e */
	//	};
	//	tama_type = ttt[((VR09/*(VR10_BOSS_SPELL_TIMER)>>5*/)&0x0f)];
	//}

// ==================================== [�X�y�J���E] ==================================== //
