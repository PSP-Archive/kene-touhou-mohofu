
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�P��̃J�[�h���`���܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�P��
	-------------------------------------------------------
	�������ǉ�
---------------------------------------------------------*/

/*---------------------------------------------------------
	4�ʐ�p
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_uroko_dan_seisei)
{
	/* 4�ʂ̏ꍇ---- */
	const u16 my_ra_nd = ra_nd();
	if (my_ra_nd & 0x8000)		/* 50%�̊m���� */
	{
		s32 kakudo65536;
	//	kakudo65536 = ((255-32)<<6);
	//	kakudo65536 = ((256-32)<<6);
	//	kakudo65536 = (((1024/4)-(1024/32))<<6);
		kakudo65536 = ((65536/4)-(65536/32));
		kakudo65536 += ((my_ra_nd)&((/*64<<6*/4096)-1));
		HATSUDAN_R12_speed_offset	= t256(0);			/* (-5) (-3)���������e */	/* ���̕����ɂȂ邩������ */
		HATSUDAN_R13_angle65536 	= (kakudo65536);
		HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R16_n_way			= (24);
		HATSUDAN_R17_div_angle65536 = (int)(65536/24);	/* �����p�x([360/360]�x��24����) */
//
	static const void *JumpTable[(8)] =
	{
		&&OPKA0x00, &&OPKA0x01, &&OPKA0x02, &&OPKA0x03,
		&&OPKA0x04, &&OPKA0x05, &&OPKA0x06, &&OPKA0x07,
	};
		goto *JumpTable[((src->boss_hp>>13)&(0x07))];
		{
		OPKA0x03:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(0.6);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_05_MIDORI);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(1.4);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x02:/*not_break;*/
		OPKA0x04:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(1.0);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(1.8);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x05:/*not_break;*/
		OPKA0x01:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(1.2);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_02_YUKARI);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(0.8);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(2.0);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x00:
		OPKA0x06:
		OPKA0x07:
			;
		}
	}
}


/*---------------------------------------------------------
	���E�V���b�g
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_hari_shot)
{
	int hari_no_iro;
	hari_no_iro = BULLET_HARI32_00_AOI;
	{	/* 4�ʂ̏ꍇ---- */
		u16 iro_tbl[8] =
		{
/**/		BULLET_HARI32_01_AKA,
/*1*/		BULLET_HARI32_01_AKA,
/*2*/		BULLET_HARI32_03_DAIDAI,
/*3*/		BULLET_HARI32_02_KIIRO,
/*4*/		BULLET_HARI32_00_AOI,
/*5*/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
		};
		int vvv;
	//	vvv = (((src->boss_hp)&(0x0000e000) )>>(13));/*(-r32)*/
		vvv = (((src->boss_hp)&(0x0001c000) )>>(14));/*(r33-)*/
		hari_no_iro = iro_tbl[vvv];
	//											0x0001c000 == 114688 == 3.5*32*1024
	}
		HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= hari_no_iro;		/* [ �e] */
	//
	{
		static int hari = 0;
		hari--;
		hari &= 32;
		//
		int spd;/*(�e��)*/
		spd = t256(1.5) + /*(t256(0.0 ... 0.99)�̗���)*/(ra_nd() & 0x00ff);
			//	angle512 += (/*22*/21+hari-difficulty/*cv1024r(20)*/)		/* 23�{(360) �� 8�{(180) */ /* ((4+1)<<16) 4 difficulty*/
		for (VR03_i=0; VR03_i<((5)<<16); VR03_i += ((/*44*/36<<6)+((hari)<<7)-((cg_VR20_game_difficulty)<<(8)) /*cv1024r(20)*/) ) /* �Œ� == 10 == 48�{(360) */
		{
			HATSUDAN_R11_speed256			= (int)(spd);	/* �e�� */	/*6*/	/*t256(2.5)*/
			HATSUDAN_R13_angle65536 		= (VR03_i);
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			spd += (64>>3/*difficulty*/);
		}
	}
	//
	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
	AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* �e�L�g�[ */
	CPU_CALL(cpu_voice_play);
}

/*---------------------------------------------------------
	���E�V���b�g
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_hari_dan_seisei)
{
//	if (CARD_ADDRESS_00_kaguya_000 < sp ell_card_number)
	{
		static int fire_wait1;
		fire_wait1--;
		if (0 > fire_wait1)
		{
			fire_wait1 = (45*4);
			kaguya_hari_shot(src);
		}
	}
}


/*---------------------------------------------------------
	4�ʂ̏ꍇ���˂��
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_pong_boll)
{
	/* 4�ʂ̏ꍇ���˂�� */
	{
		/* �̗̓Q�[�W�� 3�{�ȉ��ɂȂ�����A���˂��𗎂Ƃ��n�߂�B */
	//	if (src->boss_hp < (3*(8192)))/*(-r32)*/
		if (src->boss_hp < (3*(1024*32)))/*(r33-)*/
		{
			kaguya_data_fire_wait3--;
			if (kaguya_data_fire_wait3 < 0)
			{
			//	kaguya_data_fire_wait3 = ((src->boss_hp)>>(2+3));
			//	kaguya_data_fire_wait3 = ((src->boss_hp)>>(7)); 	/* 3*(8192)>>7 == 192 */
				kaguya_data_fire_wait3 = ((src->boss_hp)>>(7+2));	/* 3*(32768)>>9 == 192 */
				//
				#define LIMIT_LOW50 (/*50*/64)
				if (kaguya_data_fire_wait3 < (LIMIT_LOW50))
				{	kaguya_data_fire_wait3 = (LIMIT_LOW50);}
			//	1 ... 40
					#if 0	/*�Â�*/
					HATSUDAN_R11_speed256					= t256(0.05)+((cg_VR20_game_difficulty)<<6);	/* ���x t256(5.0) */
					HATSUDAN_R15_bullet_obj_type			= BULLET_MINI8_BASE + (TAMA_IRO_04_MIZU_IRO +(cg_VR20_game_difficulty));
				//	HATSUDAN_R16_n_way						= (8);
					HATSUDAN_R17_VECTOR_leg acy_dan_delta256 = (t256(0.07));	/*17.92==t256(0.07)*/
			//	kaguya_data_bomb_aaa += 9;
			//	if (448 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 448;}/* 512-448 == 64 == 1024/16...���� / �ő�16�����̏ꍇ�B */
			//	if (433 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 433;}/* 512-433 == 79 == 1024/13...���� / �ő�13�����̏ꍇ�B */
			//	if (427 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 427;}/* 512-427 == 85 == 1024/12...���� / �ő�12�����̏ꍇ�B */
			//	if (419 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 419;}/* 512-419 == 93 == 1024/11...���� / �ő�11�����̏ꍇ�B */
			//	for (VR03_i=0; VR03_i<(1024); VR03_i+=(512-kaguya_data_bomb_aaa))/* ���X�ő�16�������炢�o�Ȃ��Ƃ������Ĕ�����Ȃ��B */
			//	{
			//		HATSUDAN_R13_angle65536 			= ((VR03_i)<<6);	/* �p�x */
			//		bullet_regist_leg acy_vector_direct();
			//	}
					#else	/*�V����*/
					HATSUDAN_R11_speed256					= t256(0.05)+((cg_VR20_game_difficulty)<<6);	/* ���x t256(5.0) */
					HATSUDAN_R12_speed_offset				= (t256(0.07)); 								/*17.92==t256(0.07)*/
					HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
					HATSUDAN_R15_bullet_obj_type			= BULLET_MINI8_BASE + (TAMA_IRO_04_MIZU_IRO +(cg_VR20_game_difficulty));
				kaguya_data_bomb_aaa += (9*64);
				if ((419*64) < kaguya_data_bomb_aaa)	{kaguya_data_bomb_aaa = (419*64);}/* 512-419 == 93 == 1024/11...���� / �ő�11�����̏ꍇ�B */
				//
				for (VR03_i=0; VR03_i<(65536); VR03_i+=((65536/2)-kaguya_data_bomb_aaa))/* 16������葝�₷�ƁA�������Ĕ�����̂�����Ȃ肷����̂ōő�ł�16�����B */
				{
					HATSUDAN_R13_angle65536 			= (VR03_i);/* �p�x */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				}
					#endif
			}
		}
	}
}

/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/

local OBJ_CALL_FUNC(boss_init_kaguya_start000)
{
	kaguya_data_fire_wait3			= 0;
	kaguya_data_bomb_aaa			= 0;
}

/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/
local SPELL_EXEC(48_kaguya000)
{
//	if (50 == VR10_BOSS_SPELL_TIMER)
	if ((64-10) == VR10_BOSS_SPELL_TIMER)
	{
		kaguya_uroko_dan_seisei(src_boss);
	}
	kaguya_hari_dan_seisei(src_boss);
}
local SPELL_EXEC(4a_kaguya222)
{
//	if (50 == VR10_BOSS_SPELL_TIMER)
	if ((64-10) == VR10_BOSS_SPELL_TIMER)
	{
		kaguya_uroko_dan_seisei(src_boss);
	}
	kaguya_hari_dan_seisei(src_boss);
	kaguya_pong_boll(src_boss);
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�u�i��Ԃ��@�]�閾���]�v�iN�j
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���u�H���̋ʂ̎}�@-���F�̒e��-�v
	-------------------------------------------------------
	�����|��I�v�V����7���獶�E�ɒe���L����
	��ʒ[�Ŕ��˂��Ă��玩�@�_���e�ɂȂ�B
	-------------------------------------------------------
	�����|��I�v�V������6�����e(����)�����B
	�����|��I�v�V�����̒e�F�͌Œ�ō����珇�ɁA
	�ԁB���B�B���B�΁B���B��B(�e�Ɠ����ŏ�����HSV�A�F�p�x��)
---------------------------------------------------------*/

/*---------------------------------------------------------
	�P��A�H���̋ʂ̎}���ǂ�
	�_��u�H���̋ʂ̎} - ���F�̋� -�v
	-------------------------------------------------------
	���񂺂����ĂȂ�...
//	�P�D�P�邪���ڌ��e��16�����e��17�����e��16�����e�փW���W���ɕω�����B
	�P�D�P�邪���ڌ��e��8�����e��2�Z�b�g�B(?)
		�Z�b�g�ʂɉ�]�������Ⴄ(?)�B
	�Q�D�|��ɂȂ�񂾃I�v�V��������n�߂����S����(48����)�e���ˁB
	�R�D�|��ɂȂ�񂾃I�v�V���������ʍ��E�[�ɔ��]�F�Ēe���˂��A
		��ʍ��E�[�Œʏ�F�Ēe�̃v���C���[�_���e�ɕς��B
	-------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	��̐F(1 ... 7)�B
	R09 	�p�x?
---------------------------------------------------------*/
// 4096 == 65536/16
// 3855.05882352941176470588235294118 == 65536/17
//	240.941176470588235294117647058824 == ((65536/16)-(16636/17)) ����
local SPELL_EXEC(4b_kaguya333_tamanoe)
{
//	if ((0x02)==(VR10_BOSS_SPELL_TIMER & 0x03))/* (2���1��)(8�񖈂ɔ��e) */
	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (2���1��)(8�񖈂ɔ��e) */
	{
	#if (1)//[-r39]�ϐ�������ƃX�y�J�؂�ւ����Ƀ��Z�b�g�����B
		static u32 kaguya_VR09;
		static u32 kaguya_VR08;
	#else//[r40]�ϐ�������ƃX�y�J�؂�ւ����Ƀ��Z�b�g�����B
		#define kaguya_VR09 VR09
		#define kaguya_VR08 VR08
	#endif
		kaguya_VR08++;
		kaguya_VR08 &= (0x07);
		if (0==kaguya_VR08) {	kaguya_VR08++;	};
		//
//		HATSUDAN_R11_speed256			= (t256(1.00)); 			/* �e�� */
		HATSUDAN_R11_speed256			= (t256(0.50)); 			/* �e�� */
//		HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE) + kaguya_VR08;	/* [���ےe] */
	//	HATSUDAN_R16_n_way				= (17); 						/* [17way] */	/* ���e�� */
		HATSUDAN_R16_n_way				= (16/*8*/);					/* [16way] */	/* ���e�� */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(16))-(((si n1024(( ra_nd() & VR10_BOSS_SPELL_TIMER)))&0xff));	/*(int)(65536/(6))*/	/* �����p�x(65536[360/360�x]�� 6 ����) */	/* 1����n���������p�x */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16/*8*/));		/* 1����16���������p�x */
//
//		HATSUDAN_R13_angle65536 		= ((65536/2));					/* ���˒��S�p�x / ����@�\(���@�_��/��) */
//		HATSUDAN_R13_angle65536 		= (int)((65536*1/4))+(VR10_BOSS_SPELL_TIMER&0xff);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		kaguya_VR09 += (77);
		HATSUDAN_R13_angle65536 		= ((kaguya_VR09));						/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x08))
		{
//			HATSUDAN_R13_angle65536 	= (int)((65536*3/4))+(VR10_BOSS_SPELL_TIMER&0xff);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
			HATSUDAN_R13_angle65536 	= -(kaguya_VR09);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		}
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	}
	/*(r40�Ă���)*/
//	if ((64-10) == VR10_BOSS_SPELL_TIMER)
//	{kaguya_hari_dan_seisei(src);}
}



/*---------------------------------------------------------
	�H���̋ʂ̎}���ǂ�
	-------------------------------------------------------
	���������͕핗�ŋP�邪�o��̂�����A
	�H���̋ʂ̎}���ǂ�������肽���C������B
	���[�U�[���v��Ȃ����B
	�ȉ������B
//
	�Ԏ����Ή���̏�(�܂菇����HSV�A�F�p�x��)��7�F�J��Ԃ��ŏo�Ă���B
	��ʒ����㕔�̋P�邩��͑S���ʌ��\������葬�x�ےe�B
	�قړ������������ɉ������Ă�C������B(�C�̂�������)
	�P��͏㉺�ɗh��Ă��邪�A�ˏo�ʒu�͗h��Ȃ��ŌŒ�B
	�S���ʒe(�J������16�����S���ʒe)������������(�����_�����ۂ��p�x��)�e����������B
	(�܂蕪���p�x������)
	17�����S���ʒe���A������ƍ��x��16�����S���ʒe�܂Ō���(����)�B����̌J��Ԃ��B
//
	��ʒ�������(�Ƃ������قډ�ʒ��S)�ɖ����w���������d�Ȃ���7�B���z�u�B
	�J���������A�S���ʕĒe�����Ă���B
	�����ɖ����w����͍��E�ɔ��]�F�A�Ēe�B�p�����w����͓����ɒe���o��B
	�e���͔�r�I������肾���A�P��ےe��葬���B
	��������قړ������������ɉ������Ă�C������B(�C�̂�������)
	�F�̏����͍����͏�Ɠ����B�E���͋t���B
	�T�C�����ۂ������ł��˂��Ďˏo�B7�F���Ƃ��΂��x�ށB
	�E��angle=90[�x]+(sin(����++)*���p�x�萔)�B
	����angle=270[�x]+(sin(����++)*���p�x�萔)�B�݂����ɂ���΂����̂����H
	(���p�x�萔��+-11.25�x(360/(2^5))���炢�H�Ȃ�>>4�Ƃ��ł������ȁH)
	���]�F�A�Ēe�́A���E�̕ǂɂ�����ƐF�����F�Ŕ��]��(�Ⴆ�ΐԔ��]�F�Ēe���ԕĒe�ɂȂ�Ƃ����Ӗ�)�A
	���@�_���e�ɂȂ�B
	-------------------------------------------------------
	��̂���Ȋ������Ǝv�����ǁA�Ԉ���Ă邩������Ȃ��B
	�ȏ�𖞂����΁A���Ȃ�ו��̓���������Ă��A���������ɂȂ�Ȃ����Ȃ��H
---------------------------------------------------------*/









// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���u���̎q���L�@-�i����-�v
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ʏ�U��4
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���u�Αl�̔�߁@-�ł�ʐS-�v
---------------------------------------------------------*/


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ʏ�U��3
	-------------------------------------------------------
	���]�Ēe�͉~��48�����B
	�Α�ʒe
	����ʒe
	�Β��e
	���e
	-------------------------------------------------------
---------------------------------------------------------*/
#if (1)// �Ƃ肠����(��)�B
/*---------------------------------------------------------
	(�e�L�g�[)�ܕ������v���e
	-------------------------------------------------------
	�^�オ��ʒu�B
	�����p�́A5*13/360 ���炢����n�܂�B
	���񂾂񑝂���B
	�����p�́A65536/5/13 == 1008.246153846154 �Ȃ̂ŁA
	1000����n�߂鎖�ɂ���B
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09
	-------------------------------------------------------
	R0b 	�����p�B
	R0c 	���݉�]�p�B
	R0d 	�B
---------------------------------------------------------*/

local SPELL_EXEC(57_kaguya_tujyou_kougeki_03)
{
	static const u32 codebase_exec[25] =
	{
		// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x04);
		MCODE(OP0x1d_ANDM_PD, 0x04, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (02) if (0 != VR0a) {goto label_ddd+17;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+17)),// (ddd+17)
		// (03) VR0c += VR0b;
		MCODE(OP0x04_ADDR_PD, NAX, R0c, R0b),
		// (04) VR0a = (VR10_BOSS_SPELL_TIMER & 0xff);
		MCODE(OP0x1d_ANDM_PD, 0xff, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (05) VR0a = (VR00 + (0xff) - VR0a);		VR0a = (0xff - VR0a);
		MCODE(OP0x05_SUBR_PD, (0xff), R0a, R00),/*(�[�����W�X�^�g�p)*/
		// (06) VR0b += VR0a;
		MCODE(OP0x04_ADDR_PD, NAX, R0b, R0a),
		// (07) HATSUDAN_R11_speed256			= t256(2.0);/* �e��(0) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(2.0)),
		// (08) HATSUDAN_R12_speed_offset		= t256(-1);/* �����H */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(-1)),/* �����H */
		// (09) HATSUDAN_R13_angle65536 		= VR0c; /* �e���p�x65536 */ 	/*��CCW*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (10) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT)),
		// (11) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); /* [�ԕĒe] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KOME_BASE + TAMA_IRO_01_AKA)), /* [�ԕĒe] */
		// (12) HATSUDAN_R16_n_way				= (5);		/* [5way] */		/* ���e�� */
		MCODE(OP0x1c_MOVEM_PD, (5), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (13) HATSUDAN_R17_div_angle65536 	= (int)(512-64);		/* �����p�x(65536[360/360�x]��	 ����) */	/* 1����n���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(512-64),	/* (65536/1024)*7 448==(64*7)[�����e]�̕����p�x(r32) */
		// (14)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//	label_ddd+17:
		// (15) VR0a = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (16) if (0 != VR0a) {goto label_eee+3;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+3)),//	(eee+3)
		// ���ʉ�.
		// (17) AUDIO_18_voice_number		= VOICE16_BOSS_KYUPIN;/*(�i�C�t�ǉ���)*/
		MCODE(OP0x1c_MOVEM_PD, (VOICE16_BOSS_KYUPIN), R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (18) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;
		MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (19)  (cpu_voice_play);
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
//	label_eee+3:
		// (20)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (19));
}

local SPELL_INIT(57_kaguya_tujyou_kougeki_03)
{
	VR0b = 1000;
	VR0c = 0;
}
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���u���̌�΂̔��@-�ӂ��ʈӎu-�v
	-------------------------------------------------------
	�I�v�V���������w����1 09��	�z�u�����p�x(65536/(9*2))
	�I�v�V���������w����2 11��	�z�u�����p�x(65536/(11*2))
	�I�v�V���������w����3 13��	�z�u�����p�x(65536/(13*2))
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(kaguya_tujyou_kougeki_02_wait_callback)/* �쒵�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256/*128*/) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[128]�J�E���g �̒e */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* �e�� */
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
//	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]	�ʏ�U��2
	-------------------------------------------------------
SPELL_4e_kaguya_tujyou_kougeki_02


lt == 32[pixel]
stat == 128[pixel]
game == 160[pixel]

|lt|---game--|stat|
|32|32|256|32|128| == |480[pixel] psp ����|
|-64--|128+---------kaguya x(center)

32 + 32 + 256 + 32 + 128 == 480 [pixel] == psp width.
	-------------------------------------------------------
4 + 4 + 32 + 4 + 16 == 60, 60*8 == 480 [pixel] == psp width.
2 + 2 + 16 + 2 + 8 == 30, 30*16 == 480 [pixel] == psp width.

---------------------------------------------------------*/

local SPELL_EXEC(54_kaguya_tujyou_kougeki_02)
{
	HATSUDAN_R11_speed256			= (t256(0.5));				/* �e��(2.5) */
	HATSUDAN_R12_speed_offset		= t256(2);/*(�Ă���)*/
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
//	HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);	/* [�ےe] */
//	HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [�g�e] */
	HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* [�~�j�e] */
	//
//	VR03_i = 0;
	//
	not_tama:
		;
//	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (2���1��)(8�񖈂ɔ��e) */
	//	int boss_x256;cg_BOSS_DATA_3a_center_x256
	//	int boss_y256;cg_BOSS_DATA_3b_center_y256
	//VR06	int tama_x256;
	//VR07	int tama_y256;
		//
		int dr; 	/* ���a(==radius) */
		int dx; 	/* x����(����x����, delta x) */
		int dy; 	/* y����(����y����, delta x) */
		//
	//	VR06 = cg_BOSS_DATA_3a_center_x256 - (128<<8) + ((ra_nd()&0xff)<<8);
	//	VR07 = cg_BOSS_DATA_3b_center_y256 + ((ra_nd()&0xff)<<8);
	//	VR06 = ((ra_nd() & 0xffff)) + t256(64);/* (0 ... 255)[pixel], 64[pixel] == lt:32[pixel] + game_lt:32[pixel] */
	//	VR07 = ((ra_nd() & 0x7fff));/* (0 ... 127)[pixel] */
		VR06 = ((ra_nd() & 0xff)) +  (64);/* (0 ... 255)[pixel], 64[pixel] == lt:32[pixel] + game_lt:32[pixel] */
		VR07 = ((ra_nd() & 0xff));/* (0 ... 255)[pixel] */
	//	VR07 = ((ra_nd() & 0x7f));/* (0 ... 127)[pixel] */
		//
	//	dr = (/*obj2->m_Hit256R*/ /*+*/t256(80) /*boss_m_Hit256R*/);
	//	dr = (/*obj2->m_Hit256R*/ /*+*/t256(100) /*boss_m_Hit256R*/);
		dr = (VR0b);
		/* ���S���m�ō��B�܂莲���Ƃ̋��������߂�B */
	//	dx = ((VR06) - (cg_BOSS_DATA_3a_center_x256));/* ���S���m�ō������߂�B */
	//	dy = ((VR07) - (cg_BOSS_DATA_3b_center_y256));/* ���S���m�ō������߂�B */
	//	dx = ((VR06) - (t256(32+32+128)));/* ���S���m�ō������߂�B */
	//	dy = ((VR07) - (t256(0)));/* ���S���m�ō������߂�B */
		dx = ((VR06) - ( (32+32+128)));/* ���S���m�ō������߂�B */
		dy = ((VR07) - ( (0)));/* ���S���m�ō������߂�B */

		/* check collision, delta x position. ��`����i�w���j */
		if (dx < 0) 	{dx = (-dx);}	/* dx = abs(dx); */
	//	if (dx > dr)	{goto not_tama;/*(FALSE)*/ }	/* not hit, because not near the dx. �w�̍������傫���̂ŁA�������ĂȂ� */
	//
		/* check collision, delta y position. ��`����i�x���j */
		if (dy < 0) 	{dy = (-dy);}	/* dy = abs(dy); */
		if (dy > dr)	{goto not_tama;/*(FALSE)*/ }	/*	not hit, because not near the dy. �x�̍������傫���̂ŁA�������ĂȂ� */

		/* check collision, circle delta round distance.  �~�̔��a�Ŕ��� */
		dr *= dr;
	//	dr = t256(80*80);
		dx *= dx;
		dy *= dy;
		dx += dy;
		/* �����蔻��O�Ȃ� */
		if (dr < dx)/* if ((dr^2) < ( (dx^2) + (dy^2) )) */
		{
			goto not_tama;/*(FALSE)*/	/*(not hit. �������ĂȂ�)*/
		}
	//	return (1);/*(TRUE)*/	/*(hit! ��������)*/
//	VR06 &= 0x00fff000;
//	VR07 &= 0x00fff000;
//	VR06 &= 0x00fff0;
//	VR07 &= 0x00fff0;
	VR06 &= 0x00fff8;
	VR07 &= 0x00fff8;
	VR06 <<= 8;
	VR07 <<= 8;

//	VR06 = VR06;
//	VR07 = VR07;
	HATSUDAN_R13_angle65536 		= (ra_nd());/*( )*/
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	//
//	VR03_i++;
//	if (2 > VR03_i) goto not_tama;
//	if (1 > VR03_i) goto not_tama;

	// ���ʉ�.
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
	{
		AUDIO_18_voice_number	= VOICE16_BOSS_KYUPIN;/*(�i�C�t�ǉ���)*/
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;
		CPU_CALL(cpu_voice_play);
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
	VR0b	t256(��Փx�ʒ萔1);
---------------------------------------------------------*/

local SPELL_INIT(54_kaguya_tujyou_kougeki_02)
{
	static const u32 codebase_init[3-1] =
	{
		// (1)	VR0b = t256(��Փx�ʒ萔1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((50), (90), (120), (150)),/*(���a[pixel])*/
		// (2)	VR0b = VR0b * (256);/*(t256�`���ɕϊ�����)*/
		// (2)	VR0b = (VR0b << 8);/*(t256�`���ɕϊ�����)*/
	//	MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(�V���[�g�������A�h���b�V���O)*/
	//	NAX/*(�������I��)*/
	};
	cpu_exec((u32*)&codebase_init, (2-1));//
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���u������̋ʁ@-�ܐF�̒e��-�v
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ʏ�U��1
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(kaguya_tujyou_kougeki_01_wait_callback)/* �쒵�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+16/*128*/) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[128]�J�E���g �̒e */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* �e�� */
		/* (�ʏ�e�֕ϐg����) */
	//	src_tama->obj_type_set				= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{
		//	src_tama->rotationCCW1024 += ((int)((1024/2)+(1024/12)));
			src_tama->rotationCCW65536 += ((int)((65536/2)+(65536/12)));
			src_tama->obj_type_set			= (BULLET_KOME_BASE + TAMA_IRO_01_AKA);//minus[��]
		}
		else
		{
		//	src_tama->rotationCCW1024 += ((int)((1024/2)-(1024/12)));
			src_tama->rotationCCW65536 += ((int)((65536/2)-(65536/12)));
			src_tama->obj_type_set			= (BULLET_KOME_BASE + TAMA_IRO_03_AOI);//plus[��]
		}
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
	}
	// �����B �e��(2.5)  ->  �e��(0.5)
	src_tama->TR01_hatudan_speed65536 -= t256((2.0/32));
	// ��]�B
//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
//			{src_tama->rotationCCW1024 += (1024-1);}//minus[��]
//	else	{src_tama->rotationCCW1024 += (1);}//plus[��]
	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			{src_tama->rotationCCW65536 += (65536-(1<<6));}//minus[��]
	else	{src_tama->rotationCCW65536 += (1<<6);}//plus[��]
	//
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]	�ʏ�U��2
	-------------------------------------------------------
SPELL_4e_kaguya_tujyou_kougeki_02


lt == 32[pixel]
stat == 128[pixel]
game == 160[pixel]

|lt|---game--|stat|
|32|32|256|32|128| == |480[pixel] psp ����|
|-64--|128+---------kaguya x(center)

32 + 32 + 256 + 32 + 128 == 480 [pixel] == psp width.
	-------------------------------------------------------
4 + 4 + 32 + 4 + 16 == 60, 60*8 == 480 [pixel] == psp width.
2 + 2 + 16 + 2 + 8 == 30, 30*16 == 480 [pixel] == psp width.

	-------------------------------------------------------
	�g�p���W�X�^
	R0a		�ꎞ�g�p�B
---------------------------------------------------------*/

local SPELL_EXEC(51_kaguya_tujyou_kougeki_01)
{
	static const u32 codebase_exec[28] =
	{
		// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x01);
		MCODE(OP0x1d_ANDM_PD, 0x01, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (02) if (0 != VR0a) {goto label_ddd+20;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+20)),//	(ddd+20)
		// (03) VR0a = (VR10_BOSS_SPELL_TIMER & 0x10);
		MCODE(OP0x1d_ANDM_PD, 0x10, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (04) if (0 != VR0a) {goto label_bbb+5;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+5)),//	(bbb+5)
		// (05) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
		// (06) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI);	/* [�N�i�C�e] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI)),	/* [�N�i�C�e] */
		// (07) goto label_ccc+4;
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (u8)(+4)),
//	label_bbb+5:
		// (08) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0x0000)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(0x0000)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
		// (09) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);	/* [�ԃN�i�C�e] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)),	/* [�ԃN�i�C�e] */
//	label_ccc+4:
		// (10) HATSUDAN_R13_angle65536 		= (ra _nd());/*( )*/
		MCODE(OP0x15_RAND_VALUE, NAX, R13, NAX),
		// (11) HATSUDAN_R16_n_way				= (5);		/* [5way] */		/* ���e�� */
		MCODE(OP0x1c_MOVEM_PD, (5), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (12) HATSUDAN_R11_speed256			= (t256(2.5));/* �e��(2.5) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(2.5)),
		// (13) HATSUDAN_R12_speed_offset		= t256(2);/*(�Ă���)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(2)),
		// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/(32*5));		/* �����p�x(65536[360/360�x]�� 32 ����) */	/* 1����n���������p�x */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(32*5)),
		// (15)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//	label_ddd+20:
		// (16) VR0a = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
		// (17) if (0 != VR0a) {goto label_eee+3;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+3)),//	(eee+3)
		// ���ʉ�.
		// (18) AUDIO_18_voice_number		= VOICE16_BOSS_KYUPIN;/*(�i�C�t�ǉ���)*/
		MCODE(OP0x1c_MOVEM_PD, (VOICE16_BOSS_KYUPIN), R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (19) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;
		MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
		// (20)	 (cpu_voice_play);
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
//	label_eee+3:
		// (21)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (20));
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
	VR0b	t256(��Փx�ʒ萔1);
---------------------------------------------------------*/

local SPELL_INIT(51_kaguya_tujyou_kougeki_01)
{
	static const u32 codebase_init[4] =
	{	//	 (CLIP_RECT_TYPE_03_UE_WIDE);/*(����)*/
		// (01)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// ��ɂ����ƍL���^�C�v
		CLIP_RECT_03_VR1d,// ��ɂ����ƍL���^�C�v
		// ----
		// (02)	VR0b = t256(��Փx�ʒ萔1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((50), (90), (120), (150)),/*(���a[pixel])*/
		// (03)	VR0b = VR0b * (256);/*(t256�`���ɕϊ�����)*/
		// (04)	VR0b = (VR0b << 8);/*(t256�`���ɕϊ�����)*/
	//	MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(�V���[�g�������A�h���b�V���O)*/
	//	NAX/*(�������I��)*/
	};
	cpu_exec((u32*)&codebase_init, (2));//
}

// ==================================== [�X�y�J���E] ==================================== //
