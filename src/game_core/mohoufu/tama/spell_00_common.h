
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���ʕ����B
	-------------------------------------------------------
	(r32-)��ݏo���`�F�b�N�ɂ��āA
	�u�ړ����Ɂv��ݏo���`�F�b�N�����Ȃ������O��Ő݌v����Ă���J�[�h�������B
	���ׁ̈u�ړ����Ɂv�V�X�e���ŋ�ݏo���`�F�b�N�����܂���B
	�Ⴆ�Ή�ʒ[�Œ��˕Ԃ�e�́u�ړ����Ɂv��ݏo���`�F�b�N�����Ȃ����ɂ��������Ă���@�\�ł��B
	�u�ړ��ƕʂŁv�S�e�z��𒲂ׂāu��ݏo���`�F�b�N�v���s���܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�����e�͐F�X�e�ɂ���ĈႢ����������B(�X�̎��ԂƂ�)
	�S���V�X�e�����ŋz������ƁA�x���Ȃ�C������B
	�����e�V�X�e�����ŋz������Ȃ�A�p�x�e�Ɠ������Ċp�x�e�������ׂ�
	������(�����͂Ƃ�����)����ł͊p�x�e�ėp�ɂ���ƒx������B
	-------------------------------------------------------
	����̑��x�Ȃ�A�����e�͑S�e�z�񏑂������őΉ����ׂ��B
	(�p�`�F�Ƃ����������̗��ɂȂ肻���ł����B)
	�V�X�e���������e�Ή��́A�����Ȃ肻���B
---------------------------------------------------------*/

#if (1)
	/*(tama_system.c�̓���@�\)*/
//	#define hatudan_system_kousadan_angle65536 tmp_angleCCW1024
	#define hatudan_system_kousadan_angle65536 tmp_angleCCW65536
#endif

/*---------------------------------------------------------
	#001 �p�x�e�̈ړ����s��(�ʏ�e�p)
---------------------------------------------------------*/

static TAMA_FUNC(hatudan_system_tama_move_angle)/*(�p�x�e�ړ�)*/
{
	#if 1/* ������(�����Ă��o���邯�ǁA�����������ȒP) */
	src_tama->TR01_hatudan_speed65536		+= (src_tama->TR02_hatudan_tra65536);		/* ���������� */
	#endif
//
	#if (0)//r42(?)
	/*( 1[frame]������ɐi�ދ����B(���a) )*/int aaa 		 = (src_tama->TR01_hatudan_speed65536>>8);	/* ���x */
//	src_tama->center.x256 += ((si n65536((src_tama->rotationCCW65536))*(aaa))>>8);/*fps_factor*/
//	src_tama->center.y256 += ((co s65536((src_tama->rotationCCW65536))*(aaa))>>8);/*fps_factor*/
	{
		int sin_value_t256; 	//	sin_value_t256 = 0;
		int cos_value_t256; 	//	cos_value_t256 = 0;
		int256_sin cos65536(src_tama->rotationCCW65536, &sin_value_t256, &cos_value_t256);
		src_tama->center.x256 += ((sin_value_t256*(aaa))>>8);/*fps_factor*/
		src_tama->center.y256 += ((cos_value_t256*(aaa))>>8);/*fps_factor*/
	}
	#else
		//------------------
		HATSUDAN_R11_speed256	= (src_tama->TR01_hatudan_speed65536>>8);
		HATSUDAN_R13_angle65536 = (src_tama->rotationCCW65536);
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src_tama->center.x256 += VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		src_tama->center.y256 += VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
	#endif
}

static TAMA_FUNC(standard_angle_mover_00_callback)/*(�p�x�e�ړ�+��ʊO�e����)*/
{
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(��ʊO�e����)*/
}
static TAMA_FUNC(danmaku_01_standard_angle_sayuu_hansya_mover)/*(�p�x�e�ړ�+��ʍ��E���˒e����)*/
{
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	hatudan_system_B_side_hansya(src_tama);/*(��ʍ��E���˒e����)*/
}

/*
	�����U�R�e�p�B
	���e�� 16 [frame] �� 3�{���B
	����ȍ~�͒ʏ�e�֕ϐg���Ēʏ푬�ɂȂ�B
*/
static TAMA_FUNC(danmaku_01_standard_angle_mover_douchu_start)/*(�p�x�e�ړ�+��ʊO�e����)*/
{
	/*(2�{��)*/ 	/*(3�{��)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
//	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	//
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(��ʊO�e����)*/
	/* ���e�� 16 [�J�E���g]�ȏ�͒ʏ�e�֕ϐg����B */
//	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-(16)) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-32) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-16) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-16) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����==��ʓ��ł͒e�͏����Ȃ�) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
}


local TAMA_FUNC(move_vector_gamen_sita)
{
	// �x�N�g���e�ړ��Bmove vector.
	src_tama->center.x256 += (src_tama->math_vector.x256);	/*fps_factor*/
	src_tama->center.y256 += (src_tama->math_vector.y256);	/*fps_factor*/
//	src_tama->center.x256 += 1;// (t256( 0.1)); /*fps_factor*/
//	src_tama->center.y256 += 1;// (t256(-0.1)); /*fps_factor*/
//	src_tama->math_vector.y256 += ((src_tama->TR02_hatudan_tra65536)<<8);	/* ���������� */
	src_tama->math_vector.y256 += ((src_tama->TR02_hatudan_tra65536)); /* ���������� */
	// ��������
	#if 1
	// ��ʊO�͏����B
//	hatudan_system_B_gamen_gai_tama_kesu(src);/*(�ʏ�e�p)*/
	/* ��ʊO�̏ꍇ�͒e�������B */
	if (
//	(0 < (VR1c_bullet_clip_min_x256)-(src_tama->center.x256) ) ||
//	(0 > (VR1e_bullet_clip_max_x256)-(src_tama->center.x256) ) ||
//	(0 < (VR1d_bullet_clip_min_y256)-(src_tama->center.y256) ) ||
//	(0 > (VR1f_bullet_clip_max_y256)-(src_tama->center.y256) ) )	/*(��ʉ��̂�)*/
//	( (src_tama->center.y256) > (VR1f_bullet_clip_max_y256) ) ) /*(��ʉ��̂�)*/
	( (src_tama->center.y256) > (t256(272)) ) ) 	/*(��ʉ��̂�)*/
	{
		src_tama->jyumyou = JYUMYOU_NASI;
	}
	#endif
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�J�~��e
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	[�萔1]�J�̑��x
//	R0a 	[�萔2]�ԐN�i�C���Ȃ���p�x(180/360���傢��])
	-------------------------------------------------------
	sincos�v�Z�p
	R0b 	angle_65536
	R0c 	sine   �̒l�p�B
	R0d 	cosine �̒l�p�B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	R06 	�j��
	R07 	�j��
---------------------------------------------------------*/
local TAMA_FUNC(common_01_amefuri_callback)
{
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g���͖��� */
	{
		return;
	}
	#endif
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��64�J�E���g�o�߂����e */
	{
		//	ang le_to_vector(src_tama);
		//	local TAMA_FUNC(ang le_to_vector)
		/*(�p�x��X���AY���̃x�N�g�����x�֕ϊ�����)*/
		//------------------
		HATSUDAN_R11_speed256	= (VR09);
		HATSUDAN_R13_angle65536 = (src_tama->hatudan_system_kousadan_angle65536);
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src_tama->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		src_tama->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
	}
	#endif
	move_vector_gamen_sita(src_tama);/*(�x�N�g���ړ�+��ʉ�����)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
	#if 0
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))	// 4�J�E���g��1����8way�e������
	{
			HATSUDAN_R11_speed256				= (VR09);
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [���Ēe] */	/* �e�O�� */
	//		HATSUDAN_R16_n_way					= (8);
//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
		for (VR03_i=0; VR03_i<(8); VR03_i++)
		{
			/* �V���b�g */
		//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			HATSUDAN_R13_angle65536 	= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
			HATSUDAN_R17_VECTOR_legacy_dan_delta256 = ((ra_nd()&0x03)+2);//t256(0.04)
			bullet_regist_legacy_vector_direct();
		}
	}
	#endif
local SPELL_EXEC(common_amefuri)
{
	if (0==(VR10_BOSS_SPELL_TIMER & 0x03))	// 4�J�E���g��1����8way�e������
	{
			HATSUDAN_R11_speed256				= VR09;// [�萔1]�J�̑��x
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);	/* �e�O�� */	/* [���Ēe] */
		for (VR03_i=(0); VR03_i<(8); VR03_i++)/*(x�ʒu)*/
		{
				#if 0
				/* �V���b�g */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 				= (int)(65536/64);
				HATSUDAN_R17_VECTOR_legacy_dan_delta256 = ((ra_nd()&0x03)+2);//t256(0.04)
				bullet_regist_legacy_vector_direct();
				#else
				/* �V���b�g */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			//	HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
				/*(�Ƃ肠����)*/HATSUDAN_R12_speed_offset			= ((ra_nd()&0x07)+1);//t256(0.04)
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
	//	//		int aaa_1024;
	//	//						aaa_1024			= (1024/4)+(1024/8)+(VR03_i<<5)+((VR10_BOSS_SPELL_TIMER>>2)&0x3f);
	//	//		HATSUDAN_R13_angle65536 			= ((aaa_1024)<<6);
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
	//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
				//
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);
				#endif
		}
	}
}


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
	�Ƃ肠�������ʋK�i
---------------------------------------------------------*/

local OBJ_CALL_FUNC(boss_init_kaguya_start000);
static int kaguya_data_fire_wait3;
static int kaguya_data_bomb_aaa;

#define USE_KAGUYA_TORIAEZU_PATCH (1)
#if (1==USE_KAGUYA_TORIAEZU_PATCH)
// �Ƃ肠�����p�b�`
static int kaguya_data_tuika_tukaima;
local void kaguya_tuika_tukaima0123(void)
{
	kaguya_data_tuika_tukaima++;
	kaguya_data_tuika_tukaima &= 0x07;
}
#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)



local void select_T08(void)
{
		cg_BOSS_DATA_39_tukaima_type = TUKAIMA_08_kaguya_T08;
		set_tukaima_start();/*(�g�����V�X�e��)*/
}


local SPELL_INIT(kaguya000)
{
	boss_init_kaguya_start000(src_boss);
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		select_T08();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[�萔1]�J�̑��x//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya111)
{
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		select_T08();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[�萔1]�J�̑��x//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya222)
{
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		#if 0
			 if (0==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_09_kaguya_T09;}
		else if (1==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0a_kaguya_sitakara_type04_hiroi;}
		else if (2==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0b_kaguya_sitakara_type05_hiroi;}
		else									{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0c_kaguya_sitakara_type06;}
		#endif
		#if 1
		static const u32 codebase111[3-1] =
		{
			// (01)	//	cg_BOSS_DATA_39_tukaima_type// �{�X�p�B�g�p����g�����̃^�C�v�B
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R39_BOSS_DATA_tukaima_type, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((TUKAIMA_09_kaguya_T09), (TUKAIMA_0a_kaguya_sitakara_type04_hiroi), (TUKAIMA_0b_kaguya_sitakara_type05_hiroi), (TUKAIMA_0c_kaguya_sitakara_type06)),
		//	NAX
		};
		cpu_exec((u32*)&codebase111, (1));
		#endif
		//
		set_tukaima_start();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[�萔1]�J�̑��x//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya333)
{
//	{
		#if 0
			 if (0==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_09_kaguya_T09;}
		else if (1==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0b_kaguya_sitakara_type05_hiroi;}
		else if (2==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0c_kaguya_sitakara_type06;}
		else									{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0d_kaguya_uekara;}
		#endif
		#if 1
		static const u32 codebase222[3-1] =
		{
			// (01)	//	cg_BOSS_DATA_39_tukaima_type// �{�X�p�B�g�p����g�����̃^�C�v�B
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R39_BOSS_DATA_tukaima_type, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((TUKAIMA_09_kaguya_T09), (TUKAIMA_0b_kaguya_sitakara_type05_hiroi), (TUKAIMA_0c_kaguya_sitakara_type06), (TUKAIMA_0d_kaguya_uekara)),
		//	NAX
		};
		cpu_exec((u32*)&codebase222, (1));
		#endif
		//
		set_tukaima_start();
//	}
	VR09	= (t256(1.0));//[�萔1]�J�̑��x//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya444)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0d_kaguya_uekara;
	set_tukaima_start();
	VR09	= (t256(1.0));//[�萔1]�J�̑��x//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(2a_sakuya_baramaki1)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_04_sakuya_T04;
	set_tukaima_start();
}
local SPELL_INIT(2b_sakuya_baramaki2)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_05_sakuya_T05;
	set_tukaima_start();
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
//extern/*local*/ void set_com mon_gin_tama_void(void)
//{
//	/*(���ʕ���)*/
//}
											//R13 (src->shot_angle65536&(256*64-1))+512*64+128*64;// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
							 				//R13 (src->shot_angle65536&(256*64-1))+(65536/2)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
