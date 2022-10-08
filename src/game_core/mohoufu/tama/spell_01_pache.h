
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�p�`�����[�E�m�[���b�W�̃J�[�h���`���܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	���j�� [[ ��{�e�n ]]
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�Ԓe
---------------------------------------------------------*/
local OBJ_CALL_FUNC(test_pache_16_shot_AKA)
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))
//	{
		CPU_CALL(calculate_jiki_nerai);
		//
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);		/* [�Ԋےe] */
		HATSUDAN_R16_n_way					= (16); 										/* [16way] */	/* ���e�� */
		HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* �����p�x(65536[360/360�x]�� 16 ����) */	/* 1����n���������p�x */
		//
		for (VR03_i=0; VR03_i<(4); VR03_i++)/* 4�e */
		{
			HATSUDAN_R12_speed_offset		= (3+VR03_i)<<8;/*(�e�X�g)*/
		//	HATSUDAN_R11_speed256			= (t256(1.00)+(VR03_i<<7)); 		/* �e��(�x���e���x������) */
			HATSUDAN_R11_speed256			= (t256(1.50)+(VR03_i<<6)); 		/* �e�� */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
//	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�e
---------------------------------------------------------*/
local OBJ_CALL_FUNC(test_pache_16_shot_AOI)
{
//	{
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);		/* [�ےe] */
	//	HATSUDAN_R16_n_way					= (16); 										/* [16way] */	/* ���e�� */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* �����p�x(65536[360/360�x]�� 16 ����) */	/* 1����n���������p�x */
	//	HATSUDAN_R16_n_way					= (8);											/* [8way] */	/* ���e�� */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/(8)); /* �����p�x(65536[360/360�x]�� 8 ����) */	/* 1����n���������p�x */
		HATSUDAN_R16_n_way					= (10); 										/* [10way] */	/* ���e�� */
		HATSUDAN_R17_div_angle65536 		= (int)(65536/(10)); /* �����p�x(65536[360/360�x]�� 10 ����) */ /* 1����n���������p�x */
		//
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/4))/* 45 */
		{
			HATSUDAN_R13_angle65536 = (lz[0].laser_angle65536+VR02_j);
			//------------------
			HATSUDAN_R11_speed256	= (VR09);
		//	HATSUDAN_R13_angle65536 = ((HATSUDAN_R13_angle65536));
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			//------------------
			//
			VR06	+= (cg_BOSS_DATA_3a_center_x256);
			VR07	+= (cg_BOSS_DATA_3b_center_y256);
			//
			CPU_CALL(calculate_jiki_nerai);
			//
			for (VR03_i=0; VR03_i<(4); VR03_i++)/* 4�e */
			{
				HATSUDAN_R12_speed_offset	= (3+VR03_i)<<8;/*(�e�X�g)*/
			//	HATSUDAN_R11_speed256		= (t256(1.00)+(VR03_i<<7)); 		/* �e��(�x���e���x������) */
				HATSUDAN_R11_speed256		= (t256(1.50)+(VR03_i<<6)); 		/* �e�� */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
		}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
//	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�����w�̈ʒu����(�Ԋےe)���@�_���e(2��)
---------------------------------------------------------*/
extern OBJ_CALL_FUNC(add_zako_pache_laser);/* �A���X�l�`�J�[�h */
local SPELL_EXEC(40_pache_laser1)
{
	static int laser_muki=0;
	static int laser_count=0;
	laser_count--;
	if (0 > laser_count)
	{
		laser_count = (150);
		laser_muki ^= 1;
		if (0==(laser_muki&1))
				{lz[0].laser_angle65536 = (0+(65536/6));	}	/* +1/8��(60/360�x) */
		else	{lz[0].laser_angle65536 = (65536-(65536/6));}	/* -1/8��(60/360�x) */
	}
	else
	if (100 < laser_count)
	{	;/*��~*/}
	else
	{	/* �ړ� **/
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 -= (100);}
		else	{lz[0].laser_angle65536 += (100);}
	}
	//
	if ((65) > (VR10_BOSS_SPELL_TIMER & 0xff))/* 5�� 3�� */
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		{
			test_pache_16_shot_AKA(src_boss);
		}
	}
	#if 0
	/*0x280*/if ((640-1) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		test_pache_16_shot_AKA(src_boss);
	}
	/*0x200*/if ((640-128) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	#endif
}

/*---------------------------------------------------------
	���[�U�[�t����Ɠ���Ȃ肷�������B
	(����̃p�`�F���[�U�[���\���������)
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	?�B
	R09 	[�萔1]���e�ʒu�܂ł̋����B
//	R0a 	z
//	R0b 	��Փx�ʒ萔�B
---------------------------------------------------------*/
local SPELL_EXEC(41_pache_laser2)
{
	static int laser_muki=0;
	static int laser_count=0;
	laser_count--;
	if (0 > laser_count)
	{
		laser_count = (150);
		laser_muki ^= 1;
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 = (0+(65536/6));		}	/* +1/8��(60/360�x) */
		else	{lz[0].laser_angle65536 = (65536-(65536/6));	}	/* -1/8��(60/360�x) */
	}
	else
	if (100 < laser_count)
	{	;/*��~*/}
	else
	{
		;/* �ړ� **/
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 -= (100);}
		else	{lz[0].laser_angle65536 += (100);}
	}
	//
//	if ((65)>(VR10_BOSS_SPELL_TIMER & 0xff))/* 9�� 5�� 3�� */
	if ((65)>(VR10_BOSS_SPELL_TIMER & 0xff))/* 9�� 5�� 3�� */
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
		{
			test_pache_16_shot_AOI(src_boss);
		}
	}
}
	#if 0
	/*0x280*/if ((640-1) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		test_pache_16_shot_AKA(src_boss);
	}
	/*0x200*/if ((640-128) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	#endif

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
//���[�U�[
extern void add_laser_off_void(void);
extern void add_laser_on_void(void);

local SPELL_INIT(40_pache_laser1)
{
	add_laser_on_void();/*(����)*/
//	VR09	= (t256(64));//[�萔1]���e�ʒu�܂ł̋����B
}
local SPELL_INIT(41_pache_laser2)
{
	add_laser_on_void();/*(����)*/
	VR09	= (t256(64));//[�萔1]���e�ʒu�܂ł̋����B
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���j�� [[ �n ]]
---------------------------------------------------------*/



// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�Ηj�� [[ �A�O�j�V���C���n ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�@�@�@�@�Ε��u�A�O�j�V���C���v" No.15
	-------------------------------------------------------
	�A�O�j�V���C���̉��e�͎G���ɂ������������I�����H�B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	����̓T�C�N���C�h�Ȑ����ۂ����������ǁA�ǂ��킩��Ȃ��B
	-------------------------------------------------------
//	REG_XX_REGX 		�e�̌���������(�p�x�A�x�N�g������)
//	REG_YY_REGY 		�e�̌�������(�x�N�g������)
---------------------------------------------------------*/

local TAMA_FUNC(agnishine_danmaku_01_callback)/*(�A�O�j�V���C���e)*/
{
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[224]�J�E���g�����̒e */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[225]�J�E���g�����̒e */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-320) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[225]�J�E���g�����̒e */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(���v���)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(-r39)*/
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(r40-)*/
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(r40-)*/
		}
		else
		{	/*CCW(�����v���)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(-r39)*/
		//	src_tama->rotationCCW1024 += (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 += (src_tama->jyumyou&1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(r40-)*/
			src_tama->rotationCCW65536 += ((src_tama->jyumyou&1)<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */ /*(r40-)*/
		}
//		src_tama->TR01_hatudan_speed65536	+= (1<<8);		/* �e�� */
	//	src_tama->TR01_hatudan_speed65536	+= (512);		/*(����)*/	/* �e�� */ /*(-r39)*/
	//	src_tama->TR01_hatudan_speed65536	+= (32);		/*(����)*/	/* �e�� */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	-= (cg_VR20_game_difficulty);	/* �e�� */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	-= (3); 					/* �e�� */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	+= (32);		/*(����)*/	/* �e�� */ /*(r40-)*/
		src_tama->TR01_hatudan_speed65536	+= (30);		/*(����)*/	/* �e�� */ /*(r40-)*/

	//	�T�C�N���C�h�Ȑ�
		{
	//	//	/*(��ɉ�])*/src_tama->tmp_angleCCW1024 += (int)(3);/*(2.844444444444444==1024/360==360/360==1/360[�x])*/
	//		/*(��ɉ�])*/src_tama->tmp_angleCCW1024 += (int)(4);/*(2.844444444444444==1024/360==360/360==1/360[�x])*/
	//	//	/*(��ɉ�])*/src_tama->tmp_angleCCW1024 += (int)(5);/*(2.844444444444444==1024/360==360/360==1/360[�x])*/
			//
		//	/*(��ɉ�])*/src_tama->tmp_angleCCW65536 += (int)(3<<6);/*(182.0444444444444==65536/360==360/360==1/360[�x])*/
			/*(��ɉ�])*/src_tama->tmp_angleCCW65536 += (int)(4<<6);/*(182.0444444444444==65536/360==360/360==1/360[�x])*/
		//	/*(��ɉ�])*/src_tama->tmp_angleCCW65536 += (int)(5<<6);/*(182.0444444444444==65536/360==360/360==1/360[�x])*/
			//
		//	/*( 1[frame]������ɐi�ދ����B(���a) )*/int aaa 		 = (src_tama->TR01_hatudan_speed65536>>8);	/* ���x */
		//	/*( 1[frame]������ɐi�ދ����B(���a) )*/int aaa 		 = (t256(1.00));	/* ���x */
		//	/*( 1[frame]������ɐi�ދ����B(���a) )*/int aaa 		 = (t256(0.50));	/* ���x */
			/*( 1[frame]������ɐi�ދ����B(���a) )*/int aaa 		 = (t256(0.33));	/* ���x */
			#if (0)//
			src_tama->center.x256 += ((si n1024((src_tama->tmp_angleCCW1024))*(aaa))>>8);/*fps_factor*/
			src_tama->center.y256 += ((co s1024((src_tama->tmp_angleCCW1024))*(aaa))>>8);/*fps_factor*/
			#else
		//	{
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536(src_tama->tmp_angleCCW65536, &sin_value_t256, &cos_value_t256);
		//		src_tama->center.x256 += ((sin_value_t256*(aaa))>>8);/*fps_factor*/
		//		src_tama->center.y256 += ((cos_value_t256*(aaa))>>8);/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= (aaa);
			HATSUDAN_R13_angle65536 = (src_tama->tmp_angleCCW65536);
		//	 (sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			static const u32 codebase777[2/*-1*/] =
			{
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase777, (1));
			src_tama->center.x256 += VR05;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			src_tama->center.y256 += VR04;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
			#endif
		}
	}
	else	/* ���e�� 225 �J�E���g�ȏ�͒e�������B */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	����(r35)�̃X�y�J�V�X�e���̏ꍇ�A�d�l��
	�X�y�J���܂����郌�W�X�^�l��ێ��ł��Ȃ��B
	(�X�y�J���n�܂�^�C�~���O�ŋ����I�Ƀ��W�X�^��0�N���A����Ă��܂���)
	-------------------------------------------------------
	-------------------------------------------------------
	�g�p���W�X�^:
	R09 	[��Փx�ʒ萔1]�B
	R0c 	�ꎞ�g�p�p�x
	R0d 	��Փx�ʒ萔3(�������A13 or 11)
	R0e 	��Փx�ʒ萔4(�����p�A(65536/(13) or (65536/(11))
---------------------------------------------------------*/
local SPELL_EXEC(2e_pache_agni_shine_1)
{
	if ((VR09) > (VR10_BOSS_SPELL_TIMER & 0x3f) ) /* 64���n��Ȃ猂�� */ /*(r40-)*/
	{
	//	HATSUDAN_R11_speed256			= t256(1.0);	/* �e�� */
	//	HATSUDAN_R12_speed_offset		= t256(5);/*(�e�X�g)*/
	//	HATSUDAN_R11_speed256			= t256(0.75);	/* �e�� */
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R11_speed256			= t256(0.25);	/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(0.75);/*(�e�X�g)*/
	//	HATSUDAN_R13_angle65536 		= 0;	/* ��p�x */ /*(-r39)*/
		HATSUDAN_R13_angle65536 		= VR0c; 	/* ��p�x */ /*(r40-)*/
		VR0c							+= ((ra_nd()) & 0x0f); /*(r40-)*/
		VR0c							+= ((1)<<8); /*(r40-)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((ra_nd()) & TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [�ԗؒe] */
		HATSUDAN_R16_n_way				= VR0d;// (13) or (11); 	/* [13way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(13)) or (int)(65536/(11));	/* �����p�x(65536[360/360�x]�� 18 ����) */
		// 13�����B�A�O�j�V���C���B
		// 11�����B�A�O�j�V���C���㋉�B
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
---------------------------------------------------------*/
local SPELL_INIT(2e_pache_agni_shine_1)
{
	static const u32 codebase_init[5-1] =
	{	// (01)	VR09 = (0x05+((cg_VR20_game_difficulty)<<1));
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((5), (7), (9), (13)),//[�萔1] 64���n��Ȃ猂�B
	// (02)	R0d = (13); 					// ������(13)
	MCODE(OP0x1c_MOVEM_PD, (13), R0d, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (03)	R0e = 65536 / (R0d);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(�����p�A(65536/(13)))*/	/* �����p�x */
//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase_init, (3));
	//
}

/*---------------------------------------------------------
	"�@�@�Ε��u�A�O�j�V���C���㋉�v" No.20
	-------------------------------------------------------
---------------------------------------------------------*/
#if (0)/*(�Ƃ肠����)*/
local SPELL_EXEC(33_pache_agni_shine_2)
{
}
#else
/*EXEC*/#define spell_execute_33_pache_agni_shine_2		spell_execute_2e_pache_agni_shine_1
local SPELL_INIT(33_pache_agni_shine_2)
{
	static const u32 codebase_init[5-1] =
	{	// (01)	VR09 = (0x05+((cg_VR20_game_difficulty)<<1));
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((5), (7), (9), (13)),//[�萔1] 64���n��Ȃ猂�B
	// (02)	R0d = (11); 					// ������(11)
	MCODE(OP0x1c_MOVEM_PD, (11), R0d, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (03)	R0e = 65536 / (R0d);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(�����p�A(65536/(11)))*/	/* �����p�x */
//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase_init, (3));
	//
}
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"�@�Ε��u�A�O�j���C�f�B�A���X�v" No.23
	-------------------------------------------------------
	"�@�Ε��u�A�O�j���C�f�B�A���X�v" No.23 ==
	"�@�@�Ε��u�A�O�j�V���C���㋉�v" No.20 +
	"�ԑ��"
---------------------------------------------------------*/
/*(�Ƃ肠����)*/
local SPELL_EXEC(36_pache_agni_radiance)// _agni_shine_3
{
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2���1��Ȃ猂�� */
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );						/* �e�� */
		HATSUDAN_R12_speed_offset		= (t256(4));/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= (ra_nd());
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= BULLET_OODAMA32_01_AKA;			/* [�ԑ�ʒe] */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"���򉻃A�O�j�V���C��"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2���1��Ȃ猂�� */
	{
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [�ԗؒe] */
		HATSUDAN_R11_speed256			= (t256(1.0));		/* �e�� */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���j�� [[ �v�����Z�X�E���f�B�l�n ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�@�����u�v�����Z�X�E���f�B�l�v" No.16
	-------------------------------------------------------
	���̃J�[�h�̌��ȏ��́A���e�̂����蔻�肪(�����������)�ł������B
	(���e�̂����蔻��͏������̂�)
	�����璆�e�͌����ڂ��댯�B
	�Ȃ񂾂��ǁA���݂̖͕핗�ɒ��e�������ȁ[�B
	�ےe��(��ʒe�A�~�j�e�A���e�A�g���e)���������B
	���e�͂����蔻����傫�����A�Ƃ肠�����G���ɕύX���悤���ȁH
	-------------------------------------------------------
	���[�U�[���A�Ԋu0.5s���炢(6��)�v3.0s?(8��?)
	0.3s���炢�x��
	��ǂ��e�A�Ԋu0.3s���炢(6��)�v2.0s?
	2.0s���炢�x��
	----
	8.0s==60x8==480(?)
	6.0s==60x6==360(?)
	----
	�Ƃ������Ɋ�����̂����A�����Ԃ�1 loop 4.0s���炢���ۂ��B
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	temp00_angle
---------------------------------------------------------*/

local SPELL_EXEC(2f_pache_princess_undine)
{
	if (64 > VR10_BOSS_SPELL_TIMER)
	{
		;
	}
	else
	if (128 > VR10_BOSS_SPELL_TIMER)
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & (16-1)))
		{
			/* ���@�_�� �p���쐬 */
			/* �e��x256 y256 �{�X�̒��S���甭�e�B */
			CPU_CALL(calculate_boss_to_jiki_nerai);
		//	VR09 = HATSUDAN_R13_angle65536;
			/* ���@�_�� 3way ��laser�e */
		//	HATSUDAN_R13_angle65536 		= VR09;
		//	HATSUDAN_R11_speed256			= (t256(0.75)); 	/* �e�� */
		//	HATSUDAN_R11_speed256			= (t256(1.50)); 	/* �e�� */
			HATSUDAN_R11_speed256			= (t256(1.00)); 	/* �e�� */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI);//			/* [�e] */
			HATSUDAN_R16_n_way				= (11); 	/* [11way] */				/* ���e�� */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/(24)); /* �����p�x(65536[360/360�x]�� 16 ����) */ /* 1����n���������p�x */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
	else
	if (250 > VR10_BOSS_SPELL_TIMER)
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & (2-1)))
		{
			/* ���@�_�� 3way ��laser�e */
			//
		//	HATSUDAN_R11_speed256			= (t256(0.75)); 	/* �e�� */
		//	HATSUDAN_R11_speed256			= (t256(1.50)); 	/* �e�� */
			HATSUDAN_R11_speed256			= (t256(4.00)); 	/* �e�� */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_HARI32_00_AOI);// 				/* [�j�e] */
			/* 1���[�U�[�̒��� */
			#define pache_02_LASER_LENGTH (4)
			VR03_i = 0;// for (VR03_i=0; VR03_i<(128*pache_02_LASER_LENGTH); VR03_i+=128)
			{
				HATSUDAN_R13_angle65536 	= VR09;
				HATSUDAN_R16_n_way				= (3);	/* [3way] */	/* ���e�� */
				/* �S���̃X�L�}(���ԑS��)�A���Ԃ����鎞��time_out��128������B */
				#define pache_00_SUKIMA_ZENBU		((128/*time_out*/)<<4)/*(4096)*/
				/* �v���C���[��������X�L�} */
				#define pache_01_SUKIMA_KUGURU		(1280)
				HATSUDAN_R17_div_angle65536 	= VR03_i+((VR10_BOSS_SPELL_TIMER)<<4)-(pache_00_SUKIMA_ZENBU-pache_01_SUKIMA_KUGURU);
				// (int)(65536/(16));	/* �����p�x(65536[360/360�x]�� n ����) */	/* 1����n���������p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
			}
			if (0 == (VR10_BOSS_SPELL_TIMER & (32-1)))
			{
				/* ���@�_��Ȃ� 16way(?)17way(?) �ےe */
				HATSUDAN_R11_speed256			= (t256(0.50)); 					/* �e�� */
				HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
				HATSUDAN_R13_angle65536 		= VR09 + (65536/2);
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
				HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);// 			/* [�ےe] */
				HATSUDAN_R16_n_way				= (17); 	/* [17way] */				/* ���e�� */
				HATSUDAN_R17_div_angle65536 	= (int)(65536/(19));	/* �����p�x(65536[360/360�x]�� 19 ����) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
			}
		}
	}
	else
	if (254 == VR10_BOSS_SPELL_TIMER)
	{
		/* ���@�_�� �p���쐬 */
		/* �e��x256 y256 �{�X�̒��S���甭�e�B */
		CPU_CALL(calculate_boss_to_jiki_nerai);
		VR09 = HATSUDAN_R13_angle65536;
	}
}

/*---------------------------------------------------------
	"�@�@�@�����u�x���[�C�����C�N�v" No.24
	-------------------------------------------------------
	�d�l:
		"�@�����u�v�����Z�X�E���f�B�l�v" No.16
		�̏㋉�ł���������̕����ȒP�B
	-------------------------------------------------------
	�d�l:
		Lunatic �� Hard �ɔ�ׂē������������B
---------------------------------------------------------*/
#if (0)/*(�Ƃ肠����)*/
local SPELL_EXEC(37_pache_bury_in_lake)
{
}
#else
	#define spell_execute_37_pache_bury_in_lake		spell_execute_2f_pache_princess_undine
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ؗj�� [[ �V���t�B�z�����n ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�@�@�@�@�ؕ��u�V���t�B�z�����v" No.17
	-------------------------------------------------------
	�ؕ��u�V���t�B�z�����v�͒e�̓����������Ƒ����B
	�i�o�n�߂��������x���Ȃ�A��ōĉ�������j
	�R�`�S�����o�Ă��Ȃ��ŁA�ザ��Ȃ��ĉ�����o�Ă���C������B
	-------------------------------------------------------
	�u�V���t�B�z�����v�͂����ς蕪����Ȃ��������A
	������o�Ă��邽���̌����e�炵���B
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	����?�B
	R09 	[�萔1]�J�̑��x
	R0a 	?�B
	R0b 	?�B
//
	R0c 	�ꎞ�g�p�}�X�N�B
//	R0d 	?�B
//	R0e 	?�B
//	R0f 	��Փx�B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B(0x0000)
	�����e�B���v���B(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_sh1_danmaku_01_callback)/* �V���t�B�z���� */
{
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g���͖��� */
	{
		return;
	}
	#endif
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			/*(�͕핗�ł͉�CCW�Ȃ̂ŁA�������������v���)*/
		//	{src_tama->rotationCCW1024 += (10);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
		//	{src_tama->rotationCCW65536 += (10<<6);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
			{src_tama->rotationCCW65536 += (1<<4);}/* --- �x �Ȃ���(--�J�E���g�����ċȂ���B---) */
		else
			/*(�͕핗�ł͉�CCW�Ȃ̂ŁA�����������v���)*/
		//	{src_tama->rotationCCW1024 -= (10);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
		//	{src_tama->rotationCCW65536 -= (10<<6);}/* 90/360 �x �Ȃ���(32�J�E���g�����ċȂ���B256==8*32) */
			{src_tama->rotationCCW65536 -= (1<<4);}/* --- �x �Ȃ���(--�J�E���g�����ċȂ���B---) */
	//
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
---------------------------------------------------------*/
local SPELL_EXEC(30_pache_sylphy_horn_1)
{
//	sta tic int VR08;
	VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	/*"���򉻃V���t�B�z����"*/
//	if (0==(VR10_BOSS_SPELL_TIMER & 0x0f))
	if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
	{
		const u32 ra_nd32 = (ra_nd()/*&0xffff*/);
//		VR0b = replay_rand32 & 0xff;
		VR08 += ra_nd32;
		// 512-480 =32
		VR06	= t256(16)+((ra_nd32 & 0xffff)<<1); 	/* 16[pixel]+(480[pixel])+16[pixel] == 512[pixel] �e��x256 */
//		VR06	= t256(16)+(ra_nd32 & 0xff00)+(ra_nd32 & 0x3f00);	/* �e��x256 */
//		VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 				/* �e��y256 */
//		VR06	= ((replay_rand32) & (0x0001ffff) );/*(512-1==0x01ff)*/
		VR07	= (t256(-8));/*(��ʊO����~��)*/
	//	VR07	= (t256(32));/*(��ʊO����~��)*/
//
//		HATSUDAN_R11_speed256			= t256(1.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(12.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(33.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(128.0);		/* �e�� */
		HATSUDAN_R11_speed256/*����(�����H)*/	= t256(1.0);		/* �e��(###x256�{) */
//		HATSUDAN_R12_speed_offset		= t256(3.0);/*(�e�X�g)*/
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= (1);/*(�e�X�g)*/
//		HATSUDAN_R13_angle65536 		= (VR0a);
//		HATSUDAN_R13_angle65536 		= (65536)-(65536/8);//+(VR0b);
		HATSUDAN_R13_angle65536 		= (65536)-(65536/16)-(ra_nd32 & 0x0fff);//+(VR0b);
//		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_05_MIDORI);			/* [�ΕĒe] */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

/*---------------------------------------------------------
	"�@�@�ؕ��u�V���t�B�z�����㋉�v" No.21
	-------------------------------------------------------
---------------------------------------------------------*/
#if (0)/*(�Ƃ肠����)*/
local SPELL_EXEC(34_pache_sylphy_horn_2)
{
}
#else
	#define spell_execute_34_pache_sylphy_horn_2 	spell_execute_30_pache_sylphy_horn_1
#endif

/*---------------------------------------------------------
	"�@�@�@�ؕ��u�O���[���X�g�[���v" No.25
	-------------------------------------------------------
	�V���t�B�z�����㋉�̏㋉�ŁB
---------------------------------------------------------*/
#if (0)/*(�Ƃ肠����)*/
local SPELL_EXEC(38_pache_green_storm)//_sylphy_horn_3
{
}
#else
	#define spell_execute_38_pache_green_storm		spell_execute_30_pache_sylphy_horn_1
#endif

/*---------------------------------------------------------
	"�؁��Ε��u�t�H���X�g�u���C�Y�v" No.29
	-------------------------------------------------------
	�x�j�� [[ �����n ]]
---------------------------------------------------------*/
/*(���쐬)*/
local SPELL_EXEC(3c_pache_forest_blaze)
{
	#if (1)
//	sta tic int VR08;
	VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	/*"���򉻃V���t�B�z����"*/
//	if (0==(VR10_BOSS_SPELL_TIMER & 0x0f))
	if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
	{
		const u32 ra_nd32 = (ra_nd()/*&0xffff*/);
//		VR0b = replay_rand32 & 0xff;
		VR08 += ra_nd32;
		// 512-480 =32
		VR06	= t256(16)+((ra_nd32 & 0xffff)<<1); 	/* 16[pixel]+(480[pixel])+16[pixel] == 512[pixel] �e��x256 */
//		VR06	= t256(16)+(ra_nd32 & 0xff00)+(ra_nd32 & 0x3f00);	/* �e��x256 */
//		VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 				/* �e��y256 */
//		VR06	= ((replay_rand32) & (0x0001ffff) );/*(512-1==0x01ff)*/
		VR07	= (t256(-8));/*(��ʊO����~��)*/
	//	VR07	= (t256(32));/*(��ʊO����~��)*/
//
//		HATSUDAN_R11_speed256			= t256(1.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(12.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(33.0);		/* �e�� */
//		HATSUDAN_R11_speed256			= t256(128.0);		/* �e�� */
		HATSUDAN_R11_speed256/*����(�����H)*/	= t256(1.0);		/* �e��(###x256�{) */
//		HATSUDAN_R12_speed_offset		= t256(3.0);/*(�e�X�g)*/
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= (1);/*(�e�X�g)*/
//		HATSUDAN_R13_angle65536 		= (VR0a);
//		HATSUDAN_R13_angle65536 		= (65536)-(65536/8);//+(VR0b);
		HATSUDAN_R13_angle65536 		= (65536)-(65536/16)-(ra_nd32 & 0x0fff);//+(VR0b);
//		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA);			/* [�ԕĒe] */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
//	spell_execute_30_pache_sylphy_horn_1(src_boss);
	#endif
	#if (1)
	/*"���򉻃A�O�j�V���C��"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2���1��Ȃ猂�� */
	{
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [�ԗؒe] */
		HATSUDAN_R11_speed256			= (t256(1.0));		/* �e�� */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	#endif
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(30_pache_sylphy_horn_000)
{
	static const u32 codebase_init[6] =
	{	// ������o�Ă���̂Œe���L���͈͂�ύX����B
	// (01)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// �E�͈̔͂�ݒ肷��B
	CLIP_RECT_00_VR1c-(1024<<8),// �V���t�B�z����
	// (02)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// ��͈̔͂�ݒ肷��B
	CLIP_RECT_00_VR1d-(32<<8),// �V���t�B�z����
	// (03)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// ���͈̔͂�ݒ肷��B
	CLIP_RECT_00_VR1e+(1024<<8),// �V���t�B�z����
	};
	cpu_exec((u32*)&codebase_init, (3));
}
//	VR09	= (t256(1.0));// [�萔1]�J�̑��x

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���j�� [[ ���^���n ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�@�@�����u���^���t�@�e�B�[�O�v" No.19
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B(0x0000)
	�����e�B���v���B(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mt1_danmaku_01_callback)/* �V���o�[�h���S�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]�J�E���g�����̒e */
	{
	//	src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	-= (t256(0.03)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]...[128]�J�E���g�����̒e */
	{
		/*(�e�͏�����)*/
		src_tama->jyumyou = JYUMYOU_NASI;/*(�e������)*/
		//
		set_REG_DEST_XY(src_tama);			/* �e��x256 y256 �eobj���S���甭�e�B */ 	/*(�e�e�̈ʒu���甭�e)*/
		//
		HATSUDAN_R11_speed256			= t256(0.75);		/* 1.00 �e�� */
	//	HATSUDAN_R12_speed_offset		= (1<<(2+8));/* x4�{ �Ă���*/
		HATSUDAN_R12_speed_offset		= t256(3+1);/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);	/* [���F ��ʒe] */
		HATSUDAN_R16_n_way				= (8);							/* [8way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 	/* �����p�x(65536[360/360�x]�� 8 ����) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(100���1�񔭒e����)
//	R09 	�J�E���^�B(2���)
//	R0a 	�e�F(�����e)�B
//	R0b 	�e�p�x(�����e)�B	�e�p�x(�A�e)�B
---------------------------------------------------------*/

local SPELL_EXEC(32_pache_metal_fatigue)
{
	static const u32 codebase_exec[17] =
	{
	// (01)
	MCODE(OP0x02_COUNTER, 100, R08, NAX),	/* (100���1��) */ /*(��Ԏn��)*/
	// (02) if (0 != VR08) {goto ���e���Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+14)),// 	(osimai+14)
	/*-----------------------*/
	// (03) HATSUDAN_R11_speed256			= t256(2.50);		/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(2.50)),
//	HATSUDAN_R12_speed_offset		= (0<<(2+8));/* x4�{ �Ă���*/
	// (04) HATSUDAN_R12_speed_offset		= t256(3+0);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3+0)),
	// (05) HATSUDAN_R13_angle65536 		= ��������(0);/*(�^��)*/
	MCODE(OP0x1c_MOVEM_PD, (1), R13, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (06) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT)),
	// (07) HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);	/* [���F ��ʒe] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_OODAMA32_02_KIIRO),
	// (08) HATSUDAN_R16_n_way			= (8);	/* [8] */					/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (09) HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); /* �����p�x(65536[360/360�x]�� 8 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(8)),
	// (10)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	/*-----------------------*/
	// (11)  (cpu_auto_bullet_play_default);
// oto:
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// osimai+14:
	// (12)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (11));
}

/*---------------------------------------------------------
	"�@�@�@�����u�V���o�[�h���S���v" No.27
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B(0x0000)
	�����e�B���v���B(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mt2_danmaku_01_callback)/* �V���o�[�h���S�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]�J�E���g�����̒e */
	{
	//	src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	-= (t256(0.05)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]...[128]�J�E���g�����̒e */
	{
		if (0==(ra_nd()&1))
		{
		//	src_tama->rotationCCW1024 -= (13);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 -= (13<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (777);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 += (777<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* �e�� */
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-128) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]...[128]�J�E���g�����̒e */
	{
	//	src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* �e�� */
	}
	else	/* ���e�� 256 �J�E���g�ȏ�͒e�������B */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[256]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B(kankaku)
//	R09 	�J�E���^�B(2���)
//	R0a 	�e�F(�����e)�B
//	R0b 	�e�p�x(�����e)�B	�e�p�x(�A�e)�B
---------------------------------------------------------*/

local SPELL_EXEC(3a_pache_silver_dragon)
{
	if (30==VR10_BOSS_SPELL_TIMER)
	{
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);			/* ���e */	/* [���۔��F�e�͖����̂�] */
		HATSUDAN_R16_n_way				= (8);							/* [8way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 	/* �����p�x(65536[360/360�x]�� 8 ����) */
		for (VR03_i=0; VR03_i<(5); VR03_i++)/* 5�w */
		{
		//	HATSUDAN_R12_speed_offset		= (VR03_i<<(2+8));/* x4�{ �Ă���*/
			HATSUDAN_R12_speed_offset		= (3+VR03_i)<<8;/*(�e�X�g)*/
			HATSUDAN_R11_speed256			= (t256(1.00)+(VR03_i<<7)); 		/* �e�� */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
		//
		CPU_CALL(cpu_auto_bullet_play_default);
	}
}


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�y�j�� [[ �g�����g���n ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�@�@�y���u���C�W�B�g�����g���v" No.18
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B(0x0000)
	�����e�B���v���B(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_rt1_danmaku_01_callback)/* ���C�W�B�g�����g�� */ /*(�}�[�L�����|�C�Y��)*/
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-192) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[192 == 64 x 3]�J�E���g�����̒e */
	{
		VR09 = ((src_tama->jyumyou) & 0x3f);/* 64�Ŋ������]�� */
		if (0==VR09)/* 0�Ȃ獶�E�ɂԂ��B */
		{
		//	src_tama->rotationCCW1024 += ((ra_nd()&0xff)-128);/* 90/360 �x(+-45/360) �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 += (((ra_nd()&0xff)-128)<<6);/* 90/360 �x(+-45/360) �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->TR01_hatudan_speed65536 = (t256(1.00)<<8);	/* �e�� */
		}
		else
		{
			src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* �e�� */
			src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
		}
	}
	else
	/*(������x[192 == 64 x 3]���Ԍo�߂�����ʏ�e�ɕϐg����)*/
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR01_hatudan_speed65536 = (t256(1.00)<<8);	/* �e�� */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
}
//	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	// ��ʊO�͏����B
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(�ʏ�e�p)*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
---------------------------------------------------------*/
local SPELL_EXEC(31_pache_rage_tririton_1)
{
	// �ŏ��̔��� (64�t���[��==��1�b)�΂�T���B
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
	//	VR04_NAN_IDO_DECODE 	= PACK_NAN_IDO_CONST((1), (3), (5), (7));/*tama_const_H06_NUMS_ALICE_RED*/	/* ������:(r35-) */ 	/* ��:3���4�̕����ȒP */
	//	 (nan_ido);
	//	if ((VR10_BOSS_SPELL_TIMER & 3) <= (cg_VR20_game_difficulty))
	//	if ((VR10_BOSS_SPELL_TIMER & 7) <= (VR04_NAN_IDO_DECODE))
		if ((VR10_BOSS_SPELL_TIMER & 7) <= (cg_VR20_game_difficulty+cg_VR20_game_difficulty+1))
		{
			HATSUDAN_R11_speed256			= (t256(2.00) );						/* �e�� */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
			HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [���e] */
		//	HATSUDAN_R16_n_way				= (1);	/* [1way] */				/* ���e�� */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* �����p�x(65536[360/360�x]�� 19 ����) */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}

/*---------------------------------------------------------
	"�y���u���C�W�B�g�����g���㋉�v" No.22
	-------------------------------------------------------
	�Ă���
---------------------------------------------------------*/

/*(�Ƃ肠����)*/
local SPELL_EXEC(35_pache_rage_tririton_2)
{
	// �ŏ��̔��� (64�t���[��==��1�b)�΂�T���B
//	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		if ((VR10_BOSS_SPELL_TIMER & 7) <= (cg_VR20_game_difficulty+cg_VR20_game_difficulty+1))
		{
			HATSUDAN_R11_speed256			= (t256(2.00)); 		/* �e�� */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
			HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [���e] */
		//	HATSUDAN_R16_n_way				= (1);	/* [1way] */	/* ���e�� */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* �����p�x(65536[360/360�x]�� 19 ����) */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}

/*---------------------------------------------------------
	"�@�@�y���u�g�����g���V�F�C�N�v" No.26
	-------------------------------------------------------
	"�@�@�y���u�g�����g���V�F�C�N�v" No.26 ==
	"�y���u���C�W�B�g�����g���㋉�v" No.22 +
	"��������ʒe�B���@�_���B"
---------------------------------------------------------*/

local SPELL_EXEC(39_pache_tririton_shake)
{
	/*	�J��Ԃ��J�E���^�B */
	// �ŏ��̔��� (64�t���[��==��1�b)�΂�T���B
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );						/* �e�� */
		HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [���e] */
	//	HATSUDAN_R16_n_way				= (1);	/* [1way] */				/* ���e�� */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* �����p�x(65536[360/360�x]�� 19 ����) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"��������ʒe�B���@�_���B"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0xf) ) /* 16���1��Ȃ猂�� */
	{
		#if 1
		CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
	//	VR0a = HATSUDAN_R13_angle65536;/* ���@�_���p */
		#endif
		HATSUDAN_R11_speed256			= (t256(2.0));		/* �e�� */
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R12_speed_offset		= t256(5);/*(�e�X�g)*/
	//	HATSUDAN_R13_angle65536 		= (VR0a);/* ���@�_���p */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);		/* [���F ��ʒe] */
		HATSUDAN_R16_n_way				= (7);	/* [7way] */				/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(7)); /* �����p�x(65536[360/360�x]�� 7 ����) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	"�΁��y���u���[���@�N�������N�v" No.28
	-------------------------------------------------------
	"�΁��y���u���[���@�N�������N�v" No.28 ==
	"�@�@�y���u���C�W�B�g�����g���v" No.18 +
	"�@�@�@�@�Ε��u�A�O�j�V���C���v" No.15
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B
	R0a 	�����l
---------------------------------------------------------*/

local SPELL_EXEC(3b_pache_lava_cromlech)
{
	static const u32 codebase_exec111[2] =
	{
	//	MCODE(OP0x02_COUNTER, 192, R08, NAX),/* �J��Ԃ��J�E���^�B */
		MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase_exec111, (1));
	// �ŏ��̔��� (64�t���[��==��1�b)�΂�T���B
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );					/* �e�� */
		HATSUDAN_R12_speed_offset		= (t256(3));/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= (VR0a & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
	//	HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(������)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [���e] */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"���򉻃A�O�j�V���C��"*/
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2���1��Ȃ猂�� */
	{
		HATSUDAN_R11_speed256			= (t256(1.0));		/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [�ԗؒe] */
	//	VR0a = ra _nd();
// (?)	VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"�@�����ؕ��u�E�H�[�^�[�G���t�v" No.30
	-------------------------------------------------------
	�����悭�킩���B
	�p�`�F���ۂ��H�B
	-------------------------------------------------------
	���[��B����Ȃ��Ă�B
	-------------------------------------------------------
	1.5 �b���炢�̎����Ȃ̂łP���� 100 �J�E���g���炢?
	�Ƃ肠���� �P���� 100 �J�E���g �Ƃ���B
	-------------------------------------------------------
	�S�e�����e���ۂ��B
	-------------------------------------------------------
	�P�����ɂQ�񉹂�����B�������鎞�ɔ��e����Ƃ��āB
	0 �J�E���g�ڂ� 33 �J�E���g�ڂƂ������Ƃɂ��悤�B
	-------------------------------------------------------
�X�P�W���[��
	 0: 95 ���� ���@�_�� 24�����S���ʁA���F�e kougeki1:
	10: 85 ���� ���@�_�� 24�����S���ʁA���F�e kougeki1:
	20: 75 �ؕ� ���@�_�� 10���������A���ʒe kougeki2:
	30: 65 �ؕ� ���@�_�� 10���������A���ʒe kougeki2:
	40: 55 �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e kougeki3:
	50: 45 �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e kougeki3:
	60: 35 ���e��
	70: 25 �x��
	80: 15 �x��
	90: 10 ���e��
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(10������)
	R09 	�J�E���^�B(��� 1 - 11)
	R0e 	���@�_���p�x�ۑ��p�B
	-------------------------------------------------------
	�Ƃ肠����
	R0b 	��Փx�ʒ萔�B
---------------------------------------------------------*/
local SPELL_EXEC(3d_pache_water_elf)
{
	/* ���� ���@�_�� 24�����S���ʁA���F�e BULLET_MARU10_04_MIZU_IRO */
	/* �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e BULLET_MARU10_05_MIDORI */
	/* �ؕ� ���@�_�� 10���������A���ʒe BULLET_OODAMA32_00_AOI */
	//	if (0 == (VR10_BOSS_SPELL_TIMER & (16-1)))
	static const u32 codebase_exec[64] =
	{
	// (1) //�Ƃ肠����	MCODE(OP0x02_COUNTER, 10, R08, NAX),	/* (10���1��) */
//	MCODE(OP0x02_COUNTER, 3, R08, NAX), /* (10���1��) */
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[���W�X�^�ԐڃA�h���b�V���O]*/, R08, R0b/*[��Փx�ʒ萔]*/),
	// (2) if (0 != VR08) {goto ���e���Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+16)),// 	(ccc+1)
	/*-----------------------*/
	/* ���@�_�� �p���쐬 */
	/* �e��x256 y256 �{�X�̒��S���甭�e�B */
	// (3)	 (calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
	MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	// (4)	VR0e = (HATSUDAN_R13_angle65536);/* ���@�_���p */ /* hatudan_system_regist_katayori_n_way()�͊p�x�j�󂷂�̂ŁA�܂��ۑ��B */
	MCODE(OP0x01_MOVER_PD, NAX, R0e, R13),
	/*-----------------------*/
	// (5) R09++;
//	MCODE(OP0x01_MOVER_PD, ((u8)(+1)), R09, R09), /*(�C���f�b�N�X�t)*/
	MCODE(OP0x02_COUNTER, 11, R09, NAX),	/* (11���) */
	/*-----------------------*/
	// (6) VR0d = hairetu[VR09];goto (bbb+13);
	MCODE(OP0x0a_BRA_TABLE, R09, R0d, (+13)),
	//	const u32 cc_type[4] =
	(+42),// 00��� ���e��
	(+ 0),// 01��� ���� ���@�_�� 24�����S���ʁA���F�e kougeki1:
	(+ 0),// 02��� ���� ���@�_�� 24�����S���ʁA���F�e kougeki1:
	(+14),// 03��� �ؕ� ���@�_�� 10���������A���ʒe kougeki2:
	(+14),// 04��� �ؕ� ���@�_�� 10���������A���ʒe kougeki2:
	(+28),// 05��� �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e kougeki3:
	(+28),// 06��� �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e kougeki3:
	(+42),// 07��� ���e�� oto:
	(+43),// 08��� �x��
	(+43),// 09��� �x��
	(+42),// 10��� ���e��(���Ȃ�?)
	(+43),// 11��� (���Ȃ�?)
	// (7) �߂�ǂ���������A�Ƃ肠�����I���B[�f�o�b�O�p]
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	// (8)
	MCODE(OP0x06_BRAR_NN, NAX, NAX, R0d),	// �����3. VRB �̑��΃A�h���X�ɃW�����v�B
	// (9)
	/*-----------------------*/
		//	HATSUDAN_R11_speed256				= (t256(0.75) );		/* �e�� */
		//	HATSUDAN_R11_speed256				= (t256(1.50) );		/* �e�� */
	//		HATSUDAN_R11_speed256				= (t256(1.00) );		/* �e�� */
	/*-----------------------*/
	//kougeki1: /* ���� ���@�_�� 24�����S���ʁA���F�e BULLET_MARU10_04_MIZU_IRO */
	// (9) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (10) HATSUDAN_R12_speed_offset	= t256(1);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (11) HATSUDAN_R13_angle65536 			= VR0e;/*[���@�_���p�x�A����]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (12) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
	// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_04_MIZU_IRO);//				/* [���F�e] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_MARU10_BASE + TAMA_IRO_04_MIZU_IRO),
	// (14) HATSUDAN_R16_n_way			= (24); 	/* [24way] */					/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (24), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (15) HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* �����p�x(65536[360/360�x]�� 24 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(24)),
	// (16)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (17) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+29)),
	/*-----------------------*/
	//kougeki2: /* �ؕ� ���@�_�� 10���������A���ʒe BULLET_OODAMA32_00_AOI */
	// (18) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (19) HATSUDAN_R12_speed_offset	= t256(3);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3)),
	// (20) HATSUDAN_R13_angle65536 			= VR0e;/*[���@�_���p�x�A����]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (21) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
	// (22) HATSUDAN_R15_bullet_obj_type		= (BULLET_OODAMA32_00_AOI);//				/* [�e] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_OODAMA32_00_AOI),
	// (23) HATSUDAN_R16_n_way			= (10); 	/* [10way] */					/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (10), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (24) HATSUDAN_R17_div_angle65536 	= (int)(65536/(20));	/* �����p�x(65536[360/360�x]�� 20 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(20)),
	// (25)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	// (26) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+15)),
	/*-----------------------*/
	//kougeki3: /* �ؕ� ���@�_�� 20�����S���ʁA�ΐF�e BULLET_MARU10_05_MIDORI */
	// (27) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (28) HATSUDAN_R12_speed_offset	= t256(1);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (29) HATSUDAN_R13_angle65536 			= VR0e;/*[���@�_���p�x�A����]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (30) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
	// (31) HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_05_MIDORI);//				/* [�Βe] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_MARU10_BASE + TAMA_IRO_05_MIDORI),
	// (32) HATSUDAN_R16_n_way			= (20); 	/* [20way] */					/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (20), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (33) HATSUDAN_R17_div_angle65536 	= (int)(65536/(20));	/* �����p�x(65536[360/360�x]�� 20 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(20)),
	// (34)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (35) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+1)),
	/*-----------------------*/
	// (36)  (cpu_auto_bullet_play_default);
// oto:
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// osimai:
	// (37)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (100));// �e�L�g�[
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(3d_pache_water_elf)
{
	static const u32 codebase_init[2] =
	{
	// (1)	//	VR0b = ([��Փx�ʒ萔]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((10), ( 8), ( 5), ( 3)),
	};
	cpu_exec((u32*)&codebase_init, (1));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"���������u�}�[�L�����|�C�Y���v" No.31
	-------------------------------------------------------
	����܎��ĂȂ����ǁA���������p�`�F���ۂ��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�����e�B�����v���B(0x0000)
	�����e�B���v���B(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mp1_danmaku_01_callback)/* �}�[�L�����|�C�Y�� */
{
//	if (cnt < 80)/* 80�����͌��� */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]�J�E���g�����̒e */
	{
		src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
//	if (cnt == 80)/* 80�Ȃ獶�E�ɂԂ��B */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-80) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[80]�J�E���g�����̒e */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-96) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[64]...[96]�J�E���g�����̒e */
	{
		#if 0
		s32 ang = bullet_get_angle(eb);
		int add_angle;
		add_angle = ((A_ROUND65536)/4 + deg360to_rad(replay_rand()%10));
		bullet_set_angle(eb, ang - add_angle );
		bullet_set_angle(eb, ang + add_angle );
		#else
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 += (1<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		#endif
		src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* �e�� */
	}
	else	/* 81���� 100�����͉��� */
//	if (cnt < 200)/* 81���� 200�����͉���(�A��100�Œe��������) */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[96]...[256]�J�E���g�����̒e */
	{
		if (0==(ra_nd()&1))
		{
			goto test_aaa;
		}
	//	bullet_set_speed(eb, (spd256+t256(0.015) ) );/*(����)*/
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (1);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 += (1<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
	//	src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* �e�� */
		src_tama->TR01_hatudan_speed65536	-= (512);		/* ���� */
	test_aaa:
		;
	}
	else	/* ���e�� 256 �J�E���g�ȏ�͒e�������B */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[256]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(kankaku)
	R09 	�J�E���^�B(2���)
	R0a 	�ꎞ�g�p
//	R0b 	�e�p�x(�����e)�B	�e�p�x(�A�e)�B
	R0d		([��Փx�ʒ萔]n way);
	R0e		([��Փx�ʒ萔]div angle);
---------------------------------------------------------*/
#define MERCURY_POISON_KANKAKU_030 (30)
#define MERCURY_POISON_KANKAKU_015 (15)

	#if 0
	if (0==cg_VR20_game_difficulty) 	{;}
//	if (1==cg_VR20_game_difficulty)
	else
	{
		if (enemy.hp < (enemy.maxHp*2/3))	{VR08 = (MERCURY_POISON_KANKAKU_015);}
	}
//	bullet_set_till_time(100);/*(�����I�ɏ����鎞��)*/
	#endif

local SPELL_EXEC(3e_pache_mercury_poison)
{
	static const u32 codebase_exec[27] =
	{
	//----	VR08--;if (0 > VR08)	{VR08 = MERCURY_POISON_KANKAKU_030;}
	// (01)	counter(MERCURY_POISON_KANKAKU_030, VR08);
	MCODE(OP0x02_COUNTER, MERCURY_POISON_KANKAKU_030, R08, NAX),
	// (02) if (0 != VR08)	{goto �e�����Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+24)),//	(bbb+24)
	//	static u32 VR09 = (0);
	//	VR09 ^= 1;
	// (03)	counter(2, VR09);
	MCODE(OP0x02_COUNTER, 2, R09, NAX),/* 2[kai] == (0 or 1) */
	// ---- if (0==VR09) { } else { }
	// (04) VR15 = hairetu[VR09];goto (aaa+2);
	MCODE(OP0x0a_BRA_TABLE, R09, R15, (+2)),
	(BULLET_MARU10_BASE + TAMA_IRO_03_AOI), 		// ---- 	HATSUDAN_R15_bullet_obj_type = BULLET_MARU10_BASE + TAMA_IRO_03_AOI;		/* [���ېF�e] [���ې��F�e] */ //	br.BULLET_REGIST_color			= ((8)+(0*5));/*(���F?)*/
	(BULLET_MARU10_BASE + TAMA_IRO_06_KI_IRO),		// ---- 	HATSUDAN_R15_bullet_obj_type = BULLET_MARU10_BASE + TAMA_IRO_06_KI_IRO; 	/* [���ېF�e] [���ې��F�e] */ //	br.BULLET_REGIST_color			= ((8)+(1*5));/*(���F?)*/
	// aaa+2:
	// ---- HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((VR09)<<8)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	// (05) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT),
	// HATSUDAN_R14_tama_spec			|= ((VR09)<<8);
	// (06) VR0a			= (VR09 << 8);
	MCODE(OP0x1f_ASLM_PD, 0x08, R0a, R09),/*(�V���[�g�������A�h���b�V���O)*/
	// (07) VR14	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R14, R0a),
	// ---- //
	// (08) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(1)),
	// (09) HATSUDAN_R16_n_way				= VR0d; 	/* [n way] */		/* ���e�� */
	MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
	// (10) HATSUDAN_R17_div_angle65536 		= VR0e;	([��Փx�ʒ萔]div angle);
	MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
	// ---- //	VR0a	u32 random_angle_offset;
	// ---- //	VR0a = deg360to_rad((replay_rand() % 5)); // 910.222222222222222222222222222222 random_angle_offset
	// ---- VR0a = (ra_nd() & 0x0fff);// 0xe38 == 3640 == 65536/18 random_angle_offset
	// (11) VR0a = (ra_nd()); /*ra_nd_u32*/
	MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
	// (12) VR0a	= (VR0a & 0x0fff);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R0a),
	(0x0fff),
	// (13) HATSUDAN_R13_angle65536 		= VR0a;	/* ��p�x random_angle_offset */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (14) HATSUDAN_R11_speed256			= t256(2.00);	/* �e�� */	= t256(3.0) + jj*t256(0.3);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(2.00)),
	// (15) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (16) HATSUDAN_R13_angle65536 		= VR0a;	/* ��p�x random_angle_offset */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (17) HATSUDAN_R11_speed256			= t256(2.30);	/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(2.30)),
	// (18) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (19)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	// (20)
	// bbb+24:
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (19));
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
//	// (--) HATSUDAN_R16_n_way				= (18); 	/* [18way] */		/* ���e�� */
//	MCODE(OP0x1c_MOVEM_PD, (18), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
//	// (--) HATSUDAN_R17_div_angle65536 		= (int)(65536/(18));	/* �����p�x(65536[360/360�x]�� 18 ����) */
//	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(�����O�������A�h���b�V���O)*/
//	((int)(65536/18)),

local SPELL_INIT(3e_pache_mercury_poison)
{
	static const u32 codebase_init[3] =
	{
	// (01)	VR0d = ([��Փx�ʒ萔]n way);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((16), (18), (24), (28)), 	/* easy�� ,normal�� 18way, hard��, lunatic ��28way(?) */
	// (02)	VR0e = ([��Փx�ʒ萔]div angle);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(�����p�A�g�F)*/	/* �����p�x */
	};
	cpu_exec((u32*)&codebase_init, (2));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"�y�������u�G�������h���K���X�v" No.32
	-------------------------------------------------------
	�e�L�g�[�ɍ���Ă݂��B
	�S�R�Ⴄ�񂾂��ǁA�p�`�F���ۂ��Ƃ����΁A�p�`�F���ۂ��B
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�������ۂ����l�B
	R09 	�ꎞ�g�p (ra_nd_u32��)
	R0a 	�ꎞ�g�p
	//
	R0c 	��Փx�ʒe���萔�B
	R0d 	��Փx�ʒ萔�B
---------------------------------------------------------*/
local SPELL_EXEC(3f_pache_emerald_megalith)
{
	static const u32 codebase_exec[59] =
	{
	/* �Θg�e */
	// ---- VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	// (01) VR09	= (VR10_BOSS_SPELL_TIMER << 4);
	MCODE(OP0x1f_ASLM_PD, 0x04, R09, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (02) VR08 += (VR09);
	MCODE(OP0x04_ADDR_PD, NAX, R08, R09),
	// �����_���Θg�e
	// (03) VR09 = (VR10_BOSS_SPELL_TIMER & (4-1) );
	MCODE(OP0x1d_ANDM_PD, 0x03, R09, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (04) if (0 != VR09)	{goto �e�����Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+20)),//	(aaa+20)
	//	VR08 = HATSUDAN_R13_angle65536;
	// ---- HATSUDAN_R13_angle65536 		= ((VR08&(32768-1))-16384);
	// (05) HATSUDAN_R13_angle65536 		= ((VR08&(32768-1)) );
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R08),
	(32768-1),
	// (06) HATSUDAN_R13_angle65536 		+= (-16384);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),
	((-16384)),
	// VR0c = (cg_VR20_game_difficulty)<<4);
	// ---- HATSUDAN_R11_speed256			= (t256(0.75) + (VR08&0x007f) + (VR0c); /* �e�� */
	// (07) HATSUDAN_R11_speed256			= (VR08 & 0x007f);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R11, R08),
	(0x007f),
	// (08) HATSUDAN_R11_speed256			+= (VR0c); /* �e�� */
	MCODE(OP0x04_ADDR_PD, NAX, R11, R0c),
	// (09) HATSUDAN_R11_speed256	+= t256(0.75);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
	(t256(0.75)),
	// ---- HATSUDAN_R12_speed_offset		= ((VR08>>4)&0x07ff);/*(�e�X�g)*/
	// (10) VR0a 	= (VR08 >> 4);
	MCODE(OP0x1e_ASRM_PD, (4), R0a, R08),/*(�V���[�g�������A�h���b�V���O)*/
	// (11) HATSUDAN_R12_speed_offset = VR0a & (0x07ff);/*(�e�X�g)*/
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R12, R0a),
	(0x07ff),
	// (12) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT),
	// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_05_MIDORI);//		/* [�Θg�e] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
	(BULLET_WAKU12_BASE + TAMA_IRO_05_MIDORI),
	// (14) HATSUDAN_R16_n_way					= (2);	/* [2way] */								/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (2), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (15) HATSUDAN_R17_div_angle65536 		= (int)(65536/(24)); /* �����p�x(65536[360/360�x]�� 24 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(�����O�������A�h���b�V���O)*/
	((int)(65536/24)),
	// (16) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
// aaa+20:
	// �����_�����������A�Α�ʒe
	// (17) VR09 = (VR10_BOSS_SPELL_TIMER & (16-1) );
	MCODE(OP0x1d_ANDM_PD, 0x0f, R09, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (18) if (0 != VR09)	{goto �e�����Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+29)),//	(bbb+1)
	// (19) VR09 = (ra_nd());/*&0xffff*/ /*ra_nd_u32*/
	MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
	// (20) VR08	+= (VR09);
	MCODE(OP0x04_ADDR_PD, NAX, R08, R09),
	// ---- VR06	= t256(16)+(ra_nd32&0xff00)+(ra_nd32&0x3f00);	/* �e��x256 */
	// (21) VR0a	= (VR09 & 0xff00);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R09),
	(0xff00),
	// (22) VR06	= (VR09 & 0x3f00);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R06, R09),
	(0x3f00),
	// (23) VR06	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R06, R0a),
	// (24) VR06	+= t256(16); 	/* �e��x256 */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R06, R06),
	(t256(16)),
	// ---- VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 			/* �e��y256 */
	// (25) VR0a 	= (VR09 >> 8);
	MCODE(OP0x1e_ASRM_PD, (8), R0a, R09),/*(�V���[�g�������A�h���b�V���O)*/
	// (26) VR0a &= 0x3f00;
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R0a),
	(0x3f00),
	// (27) VR07	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R07, R0a),
	// (28) VR07	+= -t256(32); 	/* �e��y256 */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R07, R07),
	(-t256(32)),
	/* ���@�_�� 3way ��laser�e */
	/* ���@�_��Ȃ� 16way(?)17way(?) �ےe */
	// (29) HATSUDAN_R11_speed256			= (t256(0.50) );			/* �e�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(0.50)),
	// (30) HATSUDAN_R12_speed_offset		= t256(8);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(8)),
	// (31) HATSUDAN_R13_angle65536 			= (0);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),// 0 ==LONG_MEMORY_ADDRESSING
	(t256(0)),
	// (32) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT),
	// (33) HATSUDAN_R15_bullet_obj_type		= (BULLET_OODAMA32_03_MIDORI);//				/* [�Α�ʒe] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
	(BULLET_OODAMA32_03_MIDORI),
	// (34) HATSUDAN_R17_div_angle65536 		= (int)(65536/19);	/* �����p�x(65536[360/360�x]�� 19 ����) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(�����O�������A�h���b�V���O)*/
	((int)(65536/19)),
	/* easy��1����, hard��1����, lunatic ��3���� */
	// (35) HATSUDAN_R16_n_way					= (VR0d);	/* [1-3way] */		/* ���e�� */
	MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
	// (36) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
// bbb+29:
	// ���ʉ�
	// (37) VR09 = (VR10_BOSS_SPELL_TIMER & (32-1) );
	MCODE(OP0x1d_ANDM_PD, 0x1f, R09, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (38) if (0 != VR09) {goto �������Ȃ��B;}// if (0<VR0c) {goto �������Ȃ��B;}// ==if (0==VR0c) {��������B;}/* (40���1��) ���� */ if (1==VR0c)		{	}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+1)),//	(ccc+1)
	// (39)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// ccc+1:
	// (40)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (40));
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(3f_pache_emerald_megalith)
{
	static const u32 codebase_init[4] =
	{
	// (01)	VR0d = ([��Փx�ʒ萔]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 3)), 	/* easy��1����, hard��1����, lunatic ��3���� */
	// (02)	VR0c = ([��Փx�ʒe���萔]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0c, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(( 0), (16), (32), (48)), 	/* easy��1����, hard��1����, lunatic ��3���� */
//	// (02) VR0c			= (cg_VR20_game_difficulty << 4);	/* �e�� */
//	MCODE(OP0x1f_ASLM_PD, 0x04, R0c, R20_PLAYER_DATA_game_difficulty),/*(�V���[�g�������A�h���b�V���O)*/
	};
	cpu_exec((u32*)&codebase_init, (2));
}
