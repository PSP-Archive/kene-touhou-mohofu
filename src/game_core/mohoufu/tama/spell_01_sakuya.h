
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃J�[�h���`���܂��B
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*-------------------------------------------------------
	s->center.x256	�i�C�t��x���W
	data->center.x256 �m�[�h��x���W
	s->w/2		�i�C�t�̉����̔���
	�i�C�t��x���W == �m�[�h��x���W + co_s1024((data->angle1024)) x length - �i�C�t�̉����̔���
	#define ryoute_knife_length256 t256(128)
	��angle �� �C��/(2�΁~ryoute_knife_length/��2)
---------------------------------------------------------*/

/*---------------------------------------------------------
	[���] ���z�u�t�F�X�e�B�o���i�C�t�v
	-------------------------------------------------------
	(r35)�i�C�t�̐�΍��W�ʒu����x�ŋ��߂�l��������A
	���΍��W(�i�C�t�̈ړ��x�N�g���ʁA���݈ʒu����̍���)�����߂�l�����Ɉڍs���A
	�v���O�������V���v���ɏC���B
	-------------------------------------------------------
	(r41)��邪�������e����i�C�t���炭�邭��i�C�t�܂ł̈��ʊ֌W�Ƃ�����
	���֊֌W�������̂ŁA�������U������Ă���̂����������C���B
	����i�C�t�e �� �e����i�C�t �� ���邭��i�C�t�B�Ə��Ԃɕϐg���鎖�ɂ����B
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	���e�p�J�E���^�B(���E�ŋ��p)
//	R0a 	aaa
//	R0b 	bbb
	-------------------------------------------------------
	R0e:	��Փx(bullet_create_sakuya_kurukuru:�v���C���[�̎����8�e�z�u����)
	R0f_SAKUYA_LINK 	[���e�A�����W�X�^]
		0:	�Ȃ��B
		1:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ ryoute_knife); ��� ����i�C�t�J�[�h
		2:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ kurukuru);	  ��� ���邭��i�C�t�J�[�h
	-------------------------------------------------------
	�{�X���ʋK�i�g�p�f�[�^�[:
	-------------------------------------------------------
	����i�C�t�e(��)
	-------------------------------------------------------
	length	teki-obj_player�Ԃ̋���/��2
	r_or_l	0==�E	1==��
	-------------------------------------------------------
	���̂��邭��i�C�t�e(����)
	���
	�v���C���[�̎�������邭�����Ă���A�����_���̃i�C�t�B
	���΂ɐF���ς��B
	-------------------------------------------------------
	�S�����i�C�t(��)
	�_���i�C�t(��)
	-------------------------------------------------------
	�v���C���[�̎���ɎU��΂�A���Ԃ��o�ƃv���C���[�_���e
	-------------------------------------------------------
---------------------------------------------------------*/

//#include "boss.h"//#include "game_main.h"

#if 0/*(�v���C���[�̎���ɔ��e�ł���==���g�p)*/
static OBJ_CALL_FUNC(bullet_create_sakuya_kurukuru)
{
	OBJ *zzz_player;
	zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	/* ������x�����ɏo�Ȃ��ƔF�����Â炢 */
	/* �L����(�R�A)���ł����Ɣ�����O�Ɏ��ʁB(�i�C�t���L����O�ɂ�����) */
//[�d��]set_REG_DEST_BOSS_XY(); /* �i�C�t(��)�e�͍��̈ʒu���甭�e�B */	/*(���Ɏ��@�_���̎��ɐݒ�ς�)*/
//	HATSUDAN_R11_speed256			= (0);				/* �e��(0) */
	//
	for (VR03_i=0; VR03_i<65536; VR03_i+=VR0e/*tmp_step[(cg_VR20_game_difficulty)]*/)	/* �v���C���[�̎����8�e�z�u���� */
	{
		//	VR0b = VR06;//[�{�Xx���W�ꎞ�ۑ�]
		//	VR0c = VR07;//[�{�Xy���W�ꎞ�ۑ�]
		//------------------
		HATSUDAN_R11_speed256	= (t256(128));
		HATSUDAN_R13_angle65536 = (VR03_i);
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		VR07 += (zzz_player->center.x256);//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		VR06 += (zzz_player->center.y256);//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
		//	// ���ˍ��W���X�g�A�B
		//	VR06 = VR0b;//[�{�Xx���W����]
		//	VR07 = VR0c;//[�{�Xy���W����]
		//
	}
}
#endif
//
#if 0
	cg_BOSS_DATA_38_angleCCW65536 = HATSUDAN_R13_angle65536;/*(���@�_���p���ꎞ�ۑ�����)*/
	/*(�i�C�t�̐i�s����������)*/
	/*(���@�_���p�x����A�����p�x�Ƃ��� 1/8���p�x�����炷)*/
	int sabun_kaku;
	sabun_kaku = (65536/8);
	if (KNIFE_TYPE_RIGHT!=r_or_l)	{sabun_kaku = -sabun_kaku;}
	/*(�i�C�t�̔��e���W������)*/
	//------------------
	HATSUDAN_R11_speed256	= t256(8.00);/*(?)*/
//	HATSUDAN_R13_angle65536 = (tmp1024);	/*(�i�C�t�̐i�s�����͕\�������Ɠ����Ȃ̂ŁA�\�������ŕێ�����)*/
	HATSUDAN_R13_angle65536 =  cg_BOSS_DATA_38_angleCCW65536 + (sabun_kaku);/*(�_���p == ���@�_���p + �����p)*/
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	VR06 += (cg_BOSS_DATA_3a_center_x256);/*fps_factor*/
	VR07 += (cg_BOSS_DATA_3b_center_y256);/*fps_factor*/
	//------------------
//	VR06	= cg_BOSS_DATA_3a_center_x256;/* �e��x256 �{�X���S���甭�e�B */
//	VR07	= cg_BOSS_DATA_3b_center_y256;/* �e��y256 �{�X���S���甭�e�B */
	set_REG_DEST_BOSS_XY();
#endif
//
#if 0
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	int kk_speed256;
	kk_speed256 = (t256(1.6));
	kk_speed256 += (t256(0.2));
	HATSUDAN_R11_speed256		= (kk_speed256);
//
#endif

	/*-r34���d�l����*/ /* r(-1)==+128, l(+1)==-128 */	/* -1==l, +1==r */
	/*(==TAMA_SPEC_KAITEN_HOUKOU_BIT; tama_system�� HATSUDAN_R14_tama_spec �Ɉڍs�\��)*/

	//	if ((SAKUYA_LINK_02_KURU_KURU)==VR0f_SAKUYA_LINK)/*[��� ���邭��i�C�t�J�[�h]*/
	//	{
	//		bullet_create_sakuya_kurukuru(src);
	//	}
	//	if ((SAKUYA_LINK_01_RYOUTE_KNIFE)==VR0f_SAKUYA_LINK)/*[��� ����i�C�t�J�[�h]*/
	//	{
	//	}

/*-------------------------------------------------------
	[callback t03 section: �e�����C���[�O���[�v(3)�Z�N�V����]
	���邭��i�C�t�p
	-------------------------------------------------------
---------------------------------------------------------*/

local TAMA_FUNC(sakuya_kurukuru_knife_danmaku_03_callback)
{
	/* 0-64 �J�E���g�܂� */ 	/* [0]�J�E���g==���e�ʒu */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[0-31]�J�E���g�o�߂����e */
	{
		/* ���e��A���邭�邳���� */
	//	src_tama->rotationCCW1024 += (64);
		src_tama->rotationCCW65536 += (64<<6);
	//	mask1024(src_tama->rotationCCW1024);/* �˂�̂��� */
		mask65536(src_tama->rotationCCW65536);/* �˂�̂��� */
	}
	else/* ���e�G�t�F�N�g�ォ��[65]�J�E���g�o�߂����e */
	{
		/* 65 �J�E���g�Ȃ�A���@�_���e�ɕϐg����B */
		src_tama->obj_type_set			= BULLET_KNIFE20_07_MIDORI;/* (���΃i�C�t�ɕϐg) */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
		set_REG_DEST_XY(src_tama);			/* �e��x256 y256 �eobj���S���甭�e�B */
		CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
	//	src_tama->tmp_angleCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536)); 	/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
		src_tama->tmp_angleCCW65536 = ((HATSUDAN_R13_angle65536));
	//	mask1024(src_tama->tmp_angleCCW1024);/* �˂�̂��� */
	//	src_tama->rotationCCW1024 = ((src_tama->tmp_angleCCW1024)); /* �\���p�x */
		src_tama->rotationCCW65536 = ((src_tama->tmp_angleCCW65536)); /* �\���p�x */
		//------------------
		src_tama->TR01_hatudan_speed65536	= (t256(2)<<8);
		//------------------
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	}
}

/*-------------------------------------------------------
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	�e����i�C�t�p
	-------------------------------------------------------
---------------------------------------------------------*/

local TAMA_FUNC(sakuya_hajikeru_knife_danmaku_02_callback)
{
	src_tama->TR01_hatudan_speed65536 -= (10);/*(����)*/
	//		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
	//				{src_tama->rotationCCW1024		+= (1);}//plus[��]
	//		else	{src_tama->rotationCCW1024		-= (1);}//minus[��]
			if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
					{src_tama->rotationCCW65536		+= (1<<6);}//plus[��]
			else	{src_tama->rotationCCW65536		-= (1<<6);}//minus[��]

	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
	//
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(��ʊO�e����)*/
	/* ���e�� 16 [�J�E���g]�ȏ�͒ʏ�e�֕ϐg����B */
//	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-(16)) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-32) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-16) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
//	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-16) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-64) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	{
		/* (���邭��i�C�t�e�֕ϐg����==��ʓ��ł͒e�͏����Ȃ�) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_03)|(TAMA_SPEC_0000_TILT);/* (r33-)��X���e */
	}
}
/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	���E�e�i�C�t�p
	-------------------------------------------------------
---------------------------------------------------------*/
#define KNIFE_TYPE_RIGHT (0)

static TAMA_FUNC(sakuya_ryoute_knife_danmaku_01_callback)
{
	/*(�i�C�t�̎���������)*/
//	E: 128==128 +	0;(-r40)
//	N: 192==128 +  64;(-r40)
//	H: 256==128 + 128;(-r40)
//	L: 320==128 + 192;(-r40)
	// jyumyou	== (128+(cg_VR20_game_difficulty<<6));/*(r33)*/
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[0-31]�J�E���g�o�߂����e */
	{
		/*(�i�C�t���i�s���鎞�ɋȂ���p�x[��])*/
		{
		/* �`��p�p�x(����0�x�ō����(�����v���)) */
		//	0:KNIFE_TYPE_RIGHT
		//	1:KNIFE_TYPE_LEFT
		//	if (KNIFE_TYPE_RIGHT==src_tama->RYOUTE_KNIFE_DATA_l_or_r)
		//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		//			{src_tama->rotationCCW1024 += (1024-(1));}//minus[��]
		//	else	{src_tama->rotationCCW1024 += ((1));}//plus[��]
			if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
					{src_tama->rotationCCW65536 += (65536-(1<<6));}//minus[��]
			else	{src_tama->rotationCCW65536 += ((1<<6));}//plus[��]
			/*fps_factor*/	/* R(0)== +2, L(1)== -2 */		/*(r35-)*/
		}
	//	mask1024(src_tama->rotationCCW1024);/*�K���v��*/
		mask65536(src_tama->rotationCCW65536);/*�K���v��*/
		/*(�i�C�t�̑��Έړ��ʁB�x�N�g���B)*/
		//------------------
		HATSUDAN_R11_speed256	= t256(1.00);
		/*(���ׂ��p�x)*/
		HATSUDAN_R13_angle65536 = (src_tama->rotationCCW65536);/* �u1����65536�����v */
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src_tama->center.x256 += (VR07);/*fps_factor*/
		src_tama->center.y256 += (VR06);/*fps_factor*/
		//------------------
		/*(�e����i�C�t�̔��e�Ԋu)*/
		/*(���̃J�E���^�͍��E�ŋ��p�Ȃ̂�2�{�i��)*/
		VR09++;
		if (((10)+(10)) < VR09)
	//	if (((10/8)+(10/8)) < VR09)/*(�e��t256(8.0)��8�{�Ȃ�A8�Ŋ���Ȃ��Əo��e�������Ȃ��Ȃ肷����)*/
		if (((10/2)+(10/2)) < VR09)/*(�e��t256(2.0)��2�{�Ȃ�A2�Ŋ���Ȃ��Əo��e�������Ȃ��Ȃ肷����)*/
	//	if (((2)+(2)) < VR09)
		{
			VR09 = (0);
			/* �e�i�C�t(��)���A1�񕪂̒e����q�i�C�t�e(��)��4�e�A���B */
			/*(�e����q�i�C�t�e��4�e�A����)*/
			set_REG_DEST_XY(src_tama);	/* �e����q�i�C�t�e�͐e�i�C�t(��)�e�̈ʒu���甭�e�B */
			//
			HATSUDAN_R11_speed256			= t256(2.0);/* �e��(0) */
			HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|(0)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		//	HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;	/* [�i�C�t�e] */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_KNIFE20_04_AOI);	/* (���΃i�C�t�ɕϐg) */
		//	HATSUDAN_R16_n_way				= (1+cg_VR20_game_difficulty);/*(1���4�e�A�e����i�C�t������)*/
			HATSUDAN_R16_n_way				= (4+cg_VR20_game_difficulty);/*(1���4�e�A�e����i�C�t������)*/
			// 65536/12 == 5461.333333333333;
			/*(�i�C�t���i�s���鎞�ɋȂ���p�x�Ƌt�̕����ɒǉ�����)*/
			if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
					{HATSUDAN_R17_div_angle65536		= ((int)(65536/12));}//plus[��]
			else	{HATSUDAN_R17_div_angle65536		= ((int)(65536)-(int)(65536/12));}//minus[��]// ���Z���Ƃ����̂ŉ��Z����B
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
	}
	else/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	}
	hatudan_system_B_side_hansya(src_tama);/*(��ʍ��E���˒e����)*/
//	if (src_tama->jyumyou == JYUMYOU_NASI)
//	{
//		�V������������
//	}
}


/*---------------------------------------------------------
	[���] ���z�u�t�F�X�e�B�o���i�C�t�v
	-------------------------------------------------------
	VR0f_SAKUYA_LINK	[���e�A�����W�X�^]
		0:	�Ȃ��B
		1:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ryoute_knife); ��� ����i�C�t�J�[�h
		2:	extern OBJ_CALL_FUNC(bullet_create_sakuya_kurukuru);	 ��� ���邭��i�C�t�J�[�h
	-------------------------------------------------------
---------------------------------------------------------*/
//tern OBJ_CALL_FUNC(bullet_create_sakuya_ryoute_knife); /* ��� ����i�C�t�J�[�h */
//tern OBJ_CALL_FUNC(bullet_create_sakuya_kurukuru);	/* ��� ���邭��i�C�t�J�[�h */
local SPELL_EXEC(45_sakuya_festival_knife)
{
	/*[���e�A������]*/
	if ((SAKUYA_LINK_00_DONE)!=VR0f_SAKUYA_LINK)/*[���e�w���������]*/
	{
		/*(���葝�B�i�C�t[�e]��ǉ�����B)*/
		VR09	= (0);/*(���E���p���e�J�E���^)*/
			/*(���ʏ���)*/
	//	bullet_create_sakuya_ryoute_knife(src);/*[��� ����i�C�t�J�[�h]*/
	//	local OBJ_CALL_FUNC(bullet_create_sakuya_ryoute_knife)
		CPU_CALL(calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */
//[�d��]set_REG_DEST_BOSS_XY(); /* �i�C�t(��)�e�͍��̈ʒu���甭�e�B */	/*(���Ɏ��@�_���̎��ɐݒ�ς�)*/
	//	HATSUDAN_R11_speed256			= (0);				/* �e��(0) */
	//	HATSUDAN_R11_speed256			= t256(1.0);	/* �e��(?) */
	//	HATSUDAN_R11_speed256			= t256(8.0);	/* �e��(?) */
		HATSUDAN_R11_speed256			= t256(2.0);	/* �e��(?) */
		HATSUDAN_R12_speed_offset		= t256(0);/*(�Ă���)*/
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KNIFE20_06_YUKARI);	/* �i�C�t�e(��) */
		/*(�i�C�t�̍��E�ʃt���O������)*/
		int knife_no_muki;
		if ((SAKUYA_LINK_01_RYOUTE_KNIFE)==VR0f_SAKUYA_LINK)/*[��� ����i�C�t�J�[�h]*/
	//	if ((SAKUYA_LINK_02_KURU_KURU)==VR0f_SAKUYA_LINK)/*[��� ���邭��i�C�t�J�[�h]*/
				{knife_no_muki = 0/*(right)*/;}
		else	{knife_no_muki = 1/*(left)*/;}
		/*(r35-)*/
	//	HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(knife_no_muki<<8)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(knife_no_muki<<8)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		VR0f_SAKUYA_LINK = (SAKUYA_LINK_00_DONE);/*[���������]*/
			#if (1)
			AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"�{�X����1",		/* r	�����[�� */
			AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
			CPU_CALL(cpu_voice_play);
			#endif
	}
};
/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(45_sakuya_festival_knife)
{
	static const u32 codebase_init[3] =
	{
		// (1)	// VR0d = ��Փx�ʒ萔1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(?)*/
		PACK_NAN_IDO_CONST((8), (10), (12), (16)),/*tama_const_H06_NUMS_ALICE_RED*/ /* ������:(r35-) */
		// (2)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e  = 65536 / R0d;/*(�����p�A?)*/ /* �����p�x:  (r35-) */
	};
	cpu_exec((u32*)&codebase_init, (2));//
}
//	const int tmp_step[4]	= { 	(65536/8), (65536/10), (65536/12), (65536/16),	};
//	VR04_NAN_IDO_DECODE 	= PACK_NAN_IDO_CONST((8), (10), (12), (16));
//	VR0d					= VR04_NAN_IDO_DECODE;



// ==================================== [�X�y�J���E] ==================================== //

/*
	���H�u�W���b�N�E�U�E���h�r���v�̌����B
	���̃J�[�h�͎n�߂�[�ԑ�e]�������_�����ۂ��΂�T���B
	���̂΂�T���́A���Ď��̂Ȃ������̓����΂�T���Ȃ񂾂��ǁB
	�ǂ������d�g�݂Ȃ̂������ς�킩���̂ŁA�������Ă݂�B
	�܂��A�΂�T�������œK���ɃX�N�V���B�e�B
	��ʂ�2/3�ʂ����e������Ȃ��B
	�����Ń`�}�`�}���𐔂����20�e�`26�e���炢�B
	��ʔ�������16�`18�e���炢�Ȃ̂ŁA�����S����32�e�`36�e�Ȃ̂ł́H�Ɛ����B
	32�e�A36�e�B�ǂ��������肻���Ȃ̂ŉ��x�������Ă݂�B�悭����Ȃ���32�e���ۂ��B
	���Q�[���t�B�[���h��384x448, ��邳��̍��W��291x49,
	�������̍��W��ڎ�(�摜���S���W)�{���G�����\�t�g�Ōv�����鎖�ɂ����B
	��e�Ȃ̂ŁA���G�����\�t�g�œ��ډ~�ɂȂ�悤�Ɏl�p��`���B���̂��ƑΊp���ɐ���`���Ē��S���W������o���B
	----------------
	�ԍ�, �摜���S���W, 	���΍��W
	 1�e�ڂ� 94x 87,	-(291- 94)x 87-49,	==(-197, +38)
	 2�e�ڂ�171x 69,	-(291-171)x 69-49,	==(-120, +20)
	 3�e�ڂ�192x 65,	-(291-192)x 65-49,	==(- 99, +16)
	 4�e�ڂ�151x119,	-(291-151)x119-49,	==(-140, +70)
	 5�e�ڂ�181x116,	-(291-181)x116-49,	==(-110, +67)
	 6�e�ڂ�221x 80,	-(291-221)x 80-49,	==(- 70, +31)
	 7�e�ڂ�175x139,	-(291-175)x139-49,	==(-116, +90)
	 8�e�ڂ�159x153,	-(291-159)x153-49,	==(-132, +104)
	 9�e�ڂ�210x152,	-(291-210)x152-49,	==(- 81, +103)
	10�e�ڂ�258x119,	-(291-258)x119-49,	==(- 33, +70)
	11�e�ڂ�255x152,	-(291-255)x152-49,	==(- 36, +103)
	12�e�ڂ�215x178,	-(291-215)x178-49,	==(- 76, +129)
	13�e�ڂ�254x170,	-(291-254)x170-49,	==(- 37, +121)
	14�e�ڂ�206x236,	-(291-206)x236-49,	==(- 85, +187)
	15�e�ڂ�233x273,	-(291-233)x273-49,	==(- 58, +224)
	16�e�ڂ�280x255,	-(291-280)x255-49,	==(- 11, +206)
	------------------���̕ӂ��������ۂ��B
	�����܂ő���B
	���΍��W����p�x������o���Ă݂�B�悭�킩��Ȃ����ǁA
	tan(197/38)�Ŋp�x���o��̂��ȁH
//							(x/y)									tan(x/y)	���Ԃ�p�x
	 1�e�ڂ�(-197, +38) 	5.18421052631578947368421052631579		0.0907292755019070511126536298905576
	 2�e�ڂ�(-120, +20) 	6										0.105104235265676462511502380139882
	 3�e�ڂ�(- 99, +16) 	6.1875									0.108414028737611378659694904675177
	 4�e�ڂ�(-140, +70) 	2										0.0349207694917477305004026257737253
	 5�e�ڂ�(-110, +67) 	1.64179104477611940298507462686567		0.0286625046177796138852122880504812
	 6�e�ڂ�(- 70, +31) 	2.25806451612903225806451612903226		0.0394310774284007674631847355929523
	 7�e�ڂ�(-116, +90) 	1.28888888888888888888888888888889		0.0224991500955683949518891752039385
	 8�e�ڂ�(-132, +104)	1.26923076923076923076923076923077		0.0221558801384605992607822428428949
	 9�e�ڂ�(- 81, +103)	0.786407766990291262135922330097087 	0.0137262667569302851091532667488299
	10�e�ڂ�(- 33, +70) 	0.471428571428571428571428571428571 	0.00822816644161695626063183252739627
	11�e�ڂ�(- 36, +103)	0.349514563106796116504854368932039 	0.00610025557803738263689086699115253
	12�e�ڂ�(- 76, +129)	0.589147286821705426356589147286822 	0.010282922344805178445884641481058
	13�e�ڂ�(- 37, +121)	0.305785123966942148760330578512397 	0.00533700788847012290939546575203758
	14�e�ڂ�(- 85, +187)	0.454545454545454545454545454545455 	0.00793348122027169612990511645481441
	15�e�ڂ�(- 58, +224)	0.258928571428571428571428571428571 	0.00451918686372985895525414665154542
	16�e�ڂ�(- 11, +206)	0.0533980582524271844660194174757282	0.000931972200504819213720633933431873
//
	Windows�̓d����g���Ă݂�B
	Windows�̓d���tan(1)��0.0174550649282175857651288952197278�������ȁB
	tan(1)��(45�x)�̔�������A���W�A��(�P����2�΂̒P�ʌn)�Ƃ���
	(2*pai)/360==tan(1)�H�H�H�B�悭�킩���ȁB
	�ǂ�����tan�Ȃ̂��悭�킩��Ȃ��B
	tan(99)==-6.31375151467504309897946424476819()
	tan(90)==�G���[�����Ȓl�ł��B
	tan(89)==57.2899616307594246872781475371126
	tan(88)==28.6362532829156035507565093209464
	tan(55)==1.4281480067421145021606184849985
//
�킩�����Barc_tan()����Ȃ��Ƒʖڂ��B	Windows�̓d��́Atan(360�x�̊p�x)����B
	----------------
�Ƃɂ����~��ɍL����Ȃ��̂ŁABULLET_REGIST_01_speed_offset�ɍ������Ȃ肠��̂����H
*/
/*---------------------------------------------------------
	���H�u�W���b�N�E�U�E���h�r���v�ɂȂ邩������Ȃ��e�X�g
	-------------------------------------------------------
---------------------------------------------------------*/



/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
	�ԑ�e�p
---------------------------------------------------------*/

local TAMA_FUNC(sakuya_danmaku_01_callback)
{
	#if (0)/*(r35u1�o�O�B �����̓R���e�B�j���[�œ����ǂ݂��݃��[�h������on�ɂ��Ă����ׁB
	�R���e�B�j���[��̏ꍇ�A�����������N�����Ă����B)*/
	if (0 >= VR10_BOSS_SPELL_TIMER)
	{
		return;
	}
	#endif
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	//	/*[(24-12)x8]*/if ((32-8)==(VR09))	// 192== (64*3)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-((24-18)*8)) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[??]�J�E���g�o�߂����e */
	{
		/* ��e���A�S�ăX�g�b�v */
		/* ��e���A�ԑ�e�֐F�ύX�B */
		src_tama->TR02_hatudan_tra65536 			= t256(0);		/* ���������e */
		src_tama->TR01_hatudan_speed65536			= t256(0);		/* �e�� */
		src_tama->obj_type_set							= (BULLET_OODAMA32_01_AKA); 	/* [�ԑ�e](��==����) */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
//	}
//	else
//	if ((32-8)==(VR08)) // 192== (64*3)
//	{
	//	���̔��e�ʒu��ݒ�B	/* �e��x256 y256 ��ʒu01�֌����Ĕ��e�B */
		VR04	= t256(0);					/* �e��x256 */
		VR05	= t256(256);				/* �e��y256 */
		goto exchange_damnaku_sakuya_tuika;/*�i�C�t�ǉ�*/
	}
	else
	//	/*[(25-12)x8]*/if ((32-7)==(VR09))		// 192== (64*3)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-((25-18)*8)) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[??]�J�E���g�o�߂����e */
	{
	//	���̔��e�ʒu��ݒ�B	/* �e��x256 y256 ��ʒu02�֌����Ĕ��e�B */
		VR04	= t256(GAME_WIDTH); 		/* �e��x256 */
		VR05	= t256(256);				/* �e��y256 */
		goto exchange_damnaku_sakuya_tuika;/*�i�C�t�ǉ�*/
	}
	else
	//	/*[(26-12)x8]*/if ((32-6)==(VR09))		// 192== (64*3)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-((26-18)*8)) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[??]�J�E���g�o�߂����e */
	{
	//	���̔��e�ʒu��ݒ�B		/* �e��x256 y256 �v���C���[���S�֌����Ĕ��e�B */
		VR04	= zzz_player->center.x256;		/* �e��x256 */
		VR05	= zzz_player->center.y256;		/* �e��y256 */
		goto exchange_damnaku_sakuya_tuika;/*�i�C�t�ǉ�*/
	}
	else
	/*(�i�C�t�̔��e�G�t�F�N�g�̕��Ƒ�ʂ̔��e�G�t�F�N�g�̕��łQ�񕪂��炷�B)*/
	//	if ((32-5)==(VR09)) 	// 192== (64*3)
	//	/*[(29-12)x8]*/if ((32-3)==(VR09))		// 192== (64*3)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-((29-18)*8)) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[??]�J�E���g�o�߂����e */
	{/* 29 */
		/*(�ĉ���)*/
	//	int jj = 0;
	//	jj++;
	//	jj &= 0x07; 	// 2 3 4 5	6 7 8 9
	//	jj &= 0x03; 	// 3 4 5 6
	//	src_tama->TR02_hatudan_tra65536 = t256(6);			/* ���������e */
	//	src_tama->TR02_hatudan_tra65536 = (jj<<8)+t256(2);	/* (2 ... 9) ���������e */
	//	src_tama->TR02_hatudan_tra65536 = (jj<<8)+t256(3);	/* (3 ... 6) ���������e */
		src_tama->TR02_hatudan_tra65536 = t256(3);			/* (3 ... 6) ���������e */
		/* (1�͒x�������̂ŏ��O) 9 ���Ƒ��߂��邩�� */
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	//	goto my_quit;
	}
	goto my_quit;
	/*---------------------------------------------------------
		�i�C�t�ǉ��T�u���[�`�������B(�J�[�h�X�N���v�g�������ꍇ�A�T�u���[�`�������͏o�������̂ŋz������K�v����)
	---------------------------------------------------------*/
exchange_damnaku_sakuya_tuika:
	{
		/* �e�̌��ݍ��W�Ƀi�C�t�e��o�^����B */
		VR06	= (src_tama->center.x256);/* �e�̌��ݍ��W */
		VR07	= (src_tama->center.y256);/* �e�̌��ݍ��W */
		if (
			( (16*256) > abs(VR06-VR04) ) &&
			( (16*256) > abs(VR07-VR05) )
		)/*(�X�N���v�g���炠���蔻������@�\�����肻�����ȁB)*/
		{
			;/*(���e�ʒu���߂�����ꍇ�A�ǉ����Ȃ�)*/
		}
		else
		{
			HATSUDAN_R11_speed256		= (t256(0));			/* �e�� */
			HATSUDAN_R12_speed_offset	= t256(0);/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type = BULLET_KNIFE20_04_AOI;			/* [�i�C�t�e] */
		//	���e�ʒu���󂯎��B
		//	���e�ʒu��ݒ肷��B
			{
				CPU_CALL(cpu_VR_angleCCW65536_src_nerai);/* src�_���p�쐬 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
			AUDIO_18_voice_number	= VOICE16_BOSS_KYUPIN;/*(�i�C�t�ǉ���)*/
			AUDIO_19_voice_truck	= TRACK04_TEKIDAN;
			CPU_CALL(cpu_voice_play);
		}
	}
my_quit:
	;
	#if (0)
	/* ���e�� 512 �J�E���g�ȏ�͒e�������B */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
	#endif
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
	�ǉ������i�C�t�e�p
---------------------------------------------------------*/

local TAMA_FUNC(sakuya_danmaku_02_callback)
{
	/*(���ʂ�8���邪�Ƃ肠�����̑Ή�)*/
	if (29==VR09)
	{
		/*(�~�߂Ă���i�C�t���A�΃i�C�t�ɂȂ蓮���o���B)*/
	//	src_tama->TR02_hatudan_tra65536 = (jj<<8)+t256(3);	/* (3 ... 6) ���������e */
		src_tama->TR02_hatudan_tra65536 = t256(2);			/* (3 ... 6) ���������e */
		//
		src_tama->obj_type_set						= BULLET_KNIFE20_07_MIDORI;/* (���΃i�C�t�ɕϐg) */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
		//
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
	#if (0)
	/* ���e�� 512 �J�E���g�ȏ�͒e�������B */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) > src_tama->jyumyou/*(�����Ȃ̂Ŏ����Ō���)*/)/* ���e�G�t�F�N�g�ォ��[512]�J�E���g�ȏ�o�߂����e */
	{
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
	#endif
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(8���1�񔭒e����)
	R09 	�J�E���^�B(32��Ń��[�v==(SPELL_TIME_0256==256/8))
	R0a 	��Փx�ʒ萔1
	R0c 	�J�E���^�B(kk)
	R0d 	�����p�x�A�ꎞ�ۑ��p�B(ra_nd32)
	-------------------------------------------------------
	�V�X�e���g�p���W�X�^(�R���p�C�������蓖�Ă�)
	VR03_i	���[�v�p i (��Փx�ʂɎc��񐔂�ݒ�B)
---------------------------------------------------------*/
local SPELL_EXEC(14_sakuya_jack_oodama32)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 8, R08, NAX),// �J�E���^�B(8���1�񔭒e����)
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));// �J�E���^�B(8���1�񔭒e����)
	if (1==(VR08))	/* 1���( 0 �ɏ���������āA�J�E���g�A�b�v���� 1 �ɂȂ�̂ŁB) */
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 32, R09, NAX),// �J�E���^�B(32��Ń��[�v)
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));// �J�E���^�B(32��Ń��[�v)
		/* (r33)���e�G�t�F�N�g���ǉ����ꂽ�̂ŁA�ǉ����Ԃ𑁂߂āA���덇�킹�B */
	//	if (((12)+(HATUDAN_FRAME64/8))==(VR08)) // 192== (64*3)
		/*[12x8]*/if (((32-20))==(VR09))		// 192== (64*3)
		{
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= BULLET_OODAMA32_00_AOI;			/* [��e](��==�Ö�) */
		//
			VR0c = (0);
		//	mm = 0; /* �J�E���^ */
		//	jj = (1024-960);
			VR0d = ra_nd();/*(�����p)*/
			VR03_i = VR0a;/*(��Փx�ʂɎc��񐔂�ݒ�B)*/	/* 32�e�΂�T�� */
		loop_i:
			{
			/* 960==30720/32,  30720 == 32768 -1024 -1024 */
			/* 936 = 936.228571428571428571428571428571 == (32768/(32+2���E�̗]�T��))	*/
			//	jj += (960);/* (=936)< 1024 [180�x(32768)���኱�����͈͂ɂ΂�T��] */
			//	VR0c += 386;
				VR0c += VR0d;/*(�����p���Z)*/
			//	VR0c += 42857142;
			//	mm += 42857142;
			//	HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
			//	HATSUDAN_R12_speed_offset		= t256(8);/*(�e�X�g)*/
			//	HATSUDAN_R12_speed_offset		= t256(12);/*(�e�X�g)*/
				HATSUDAN_R12_speed_offset		= (t256(4)+((VR0c&0x07)<<8));/*(�e�X�g)*/
			//	HATSUDAN_R11_speed256			= ((VR0c)&(512-1))+t256(0.25);	/*��͍����e*/
				HATSUDAN_R11_speed256			= ((VR0c)&(1024-1))+t256(0.25); /*��͍����e*/
				HATSUDAN_R13_angle65536 		= ((VR0c)&(32768-1))+(int)(65536*3/4);	/* �p�x */
			//	HATSUDAN_R13_angle65536 		= ((mm)&(1024-1))+jj+(int)(65536*3/4);			/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
			VR03_i--;/*(�c��񐔌��炷�B)*/if (0 < VR03_i) {goto loop_i;}/*(�c��񐔂�����΃��[�v�B)*/
			#if (1)
			AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"�{�X����1",		/* r	�����[�� */
			AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
			CPU_CALL(cpu_voice_play);
			#endif
		}
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(14_sakuya_jack_oodama32)
{
	#if 0
	// �� ���H�u�W���b�N�E�U�E���h�r���v���ǂ��p
	/* easy 	normal		hard		lunatic 	*/
//	(6),		(12),		(24),		(32),		/* ���H�u�W���b�N�E�U�E���h�r���v���ǂ��p */
	(16),		(32),		(40),		(48),		/* ���H�u�W���b�N�E�U�E���h�r���v���ǂ��p */
	VR0a	= [tama_const_H08_NUMS_SAKUYA_JACK	+(cg_VR20_game_difficulty)];/*(�������A�F)*/
	#else
//	VR0a	= NAN_IDO_DECODE((16), (32), (40), (48));
//	VR04_NAN_IDO_DECODE 	= PACK_NAN_IDO_CONST((16), (32), (40), (48));
//	CPU_CA LL(nan_ido);
//	VR0a	= VR04_NAN_IDO_DECODE;
	#endif
	static const u32 codebase_init[2] =
	{
		// (1)	//	VR0b = ([��Փx�ʒ萔]);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0a, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((16), (32), (40), (48)),
	};
	cpu_exec((u32*)&codebase_init, (1));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���C�h��Z�u����h�[���v
---------------------------------------------------------*/
#if 0
#endif

// ==================================== [�X�y�J���E] ==================================== //

#if 0
/*---------------------------------------------------------
	��11�`��: �ŏI�`��(����3)
---------------------------------------------------------*/
local SPELL_EXEC(45_sakuya_meek)
{
	if (0 == VR10_BOSS_SPELL_TIMER)
	{
		add_za ko_sakuya_doll_01_laser(src);/* ���[�U�[�ǉ� */
	}
//
	src->color32	= MAKE32RGBA(0xff, 0xff, 0xff, 0xff);		/*	src->alpha = 0xff;*/
//
}
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�ʏ�U���A�ԃi�C�t
	��CW�A�Ԃ�CCW
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_EXEC(2c_sakuya_blue_red_knife)
{
	if (0 != (VR10_BOSS_SPELL_TIMER & 0x0180))
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))
		{
			u32 kk;
			kk = (((VR10_BOSS_SPELL_TIMER) & 0x0100)>>8);
				HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI+kk; 			/* [�i�C�t�e] */
		//
			/*VR03_i 1����65536���������p�x */
			/* VR02_j �J�E���^ */
			VR02_j = 0;
			for (VR03_i=0; VR03_i<(0x10000); VR03_i+=(819))/* 819.2(65536/80) 80���� [5����] */ 	/* (65536/5) �p�x(65536[72/360�x]�� 5 ����) */
			{
				VR02_j++;
				VR02_j &= (16-1);/* 16way(8way[hi to 0]+8way[slow to 0]) */
				HATSUDAN_R11_speed256			= (t256(3.0)-((VR02_j)<<5)-((VR02_j&1)<<7));		/*��͍����e*/
				HATSUDAN_R13_angle65536 		= ((kk?(0-VR03_i):(VR03_i))&(65536-1)); 			/* �p�x */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�u�ʏ�U��3(1/2)�v
	-------------------------------------------------------
	�g�U�^�S���ʃi�C�t�e
	80�����e == (8way[hi to 0]+8way[slow to 0]) x 5way(5����)
	-------------------------------------------------------
	�{���͉�ʏ�Ɖ�ʍ��Ɖ�ʉE�̒[�Ńi�C�t����x�������˂���B
---------------------------------------------------------*/
local SPELL_EXEC(07_80way_dual_five)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))
	{
			HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;				/* [�i�C�t�e] */
	//
			/* VR03_i 1����65536���������p�x */
		/* VR02_j �J�E���^ */
		VR02_j=0;
		for (VR03_i=0; VR03_i<(0x10000); VR03_i += 819)/* 819.2(65536/80)	12.8==(1024/80) 80���� [5����] */	/* 204.8==(1024/5) �p�x(1024[72/360�x]�� 5 ����) */
		{
			VR02_j++;
			VR02_j &= (16-1);/* 16way(8way[hi to 0]+8way[slow to 0]) */
			HATSUDAN_R11_speed256			= (t256(3.0)-((VR02_j)<<5)-((VR02_j&1)<<7));	/*��͍����e*/
			HATSUDAN_R13_angle65536 		= (((0-VR03_i))&(65536-1)); 			/* �p�x */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���ہu���i�N���b�N(2/2)�v
---------------------------------------------------------*/
#if 0
#endif

/*---------------------------------------------------------
	���ہu���i�N���b�N(1/2)�v
	-------------------------------------------------------
	32way �Œ�A�e	x 4��
---------------------------------------------------------*/
local SPELL_EXEC(06_luna_clock_32way)
{
	if (0x40 == (VR10_BOSS_SPELL_TIMER & 0xcf))/* 4�� */
	{
		HATSUDAN_R11_speed256			= (t256(1.0));				/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= (0);						/* ���˒��S�p�x / ����@�\(���@�_��/��) */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= BULLET_CAP16_04_TUTU_SIROI;	/* [������e] */	/* �e�O�� */
		HATSUDAN_R16_n_way				= (32); 					/* [32way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(32));		/* �����p�x(65536[360/360�x]�� 32 ����) */	/* 1����n���������p�x */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

// ==================================== [�X�y�J���E] ==================================== //


/*---------------------------------------------------------
	���݁u�N���b�N�R�[�v�X(2/2)�v
---------------------------------------------------------*/
#if 0
#endif


/*---------------------------------------------------------
	���݁u�N���b�N�R�[�v�X(1/2)�v
---------------------------------------------------------*/
#if 0
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g5�ʃ{�X ��� �u�ʏ�U��1(2/2)�v�ɂ�����Ƃ��������J�[�h(�\��)
	-------------------------------------------------------
	32�����ɕ����A�����͒ᑬ�e�A��͍����e�B
	16������2��o�^����B
	-------------------------------------------------------
	32����	�p�x(1024[360/360�x]�� 32 ����)1024 == 32 x 32
---------------------------------------------------------*/
local SPELL_EXEC(05_32way_dual)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))
	{
		HATSUDAN_R12_speed_offset			= t256(1/*0*/);/*(�e�X�g)*/
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type		= BULLET_KNIFE20_04_AOI;			/* [�i�C�t�e] */
		HATSUDAN_R16_n_way					= (16); 							/* [16way] */
		HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));		/* �����p�x(65536[360/360�x]�� 16 ����) */	/* 1����n���������p�x */
	//
		HATSUDAN_R11_speed256				= (t256(0.75)); 		/* �����͒ᑬ�e */
		HATSUDAN_R13_angle65536 			= (0);					/* �e���p�x65536 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	//
		HATSUDAN_R11_speed256				= (t256(1.25)); 		/* ��͍����e */
		HATSUDAN_R13_angle65536 			= (65536/32);			/* �e���p�x65536 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}
/*---------------------------------------------------------
	�g5�ʃ{�X ��� �u�ʏ�U��1(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��)
	-------------------------------------------------------
	24way =(�E12way)+(��12way)
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_EXEC(04_pink_hearts)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))/* �{���� 8 �e(128==0x80==spell_time_out) */
	{
			HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_06_YUKARI; 		/* [�s���N�i�C�t�e] */
		//	VR07					= (src->center.y256);	/* �e��y256 �{�X���S���甭�e�B */
			VR07					= cg_BOSS_DATA_3b_center_y256;	/* �e��y256 �{�X���S���甭�e�B */
		//	���e�����ʒu�̏C��
			VR06					-= t256(4.0);		/* �e��x256 �{�X�����֔��e�B */
		//
		VR02_j = 0;
		for (VR03_i=0; VR03_i<(13*12*4)/*144*/; VR03_i+=(13*4))/*12����*/						/* �p�x(128[(90+a)/360�x]�� 10 ����) */
		{
			HATSUDAN_R11_speed256			= (((160*4)-VR03_i));						/* �e�� */
			//
		//	VR06					= (cg_BOSS_DATA_3a_center_x256) + t256(4.0);			/* �e��x256 �{�X�E�����甭�e�B */
			VR06					+= t256(8.0);			/* �e��x256 �{�X�E�����甭�e�B */
			HATSUDAN_R13_angle65536 		= (VR02_j/*(0+i+i)&(65536-1)*/);
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			//
		//	VR06					= (cg_BOSS_DATA_3a_center_x256) - t256(4.0);			/* �e��x256 �{�X�������甭�e�B */
			VR06					-= t256(8.0);			/* �e��x256 �{�X�������甭�e�B */
			HATSUDAN_R13_angle65536 		= ((0-VR02_j)&(65536-1));
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			//
			VR02_j += (13*2*64);
		}
		#if (1)
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase888, (1));
		#endif
	}
}

/*---------------------------------------------------------
	5�u�ʏ�U��3�v�����e�Ƃ̑g�ݍ��킹
---------------------------------------------------------*/
local SPELL_EXEC(2b_sakuya_baramaki2)
{
	if (64 > (VR10_BOSS_SPELL_TIMER))
	{
		spell_execute_04_pink_hearts(src_boss);
	}
	else
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0xff))	/* 256 512 (768) */
	if (0 == (VR10_BOSS_SPELL_TIMER & 0xff))	/* 256 512 (768) */
	{
		spell_execute_05_32way_dual(src_boss);
	}
}

/*---------------------------------------------------------
	3�u�ʏ�U��1�v�x���e�Ƃ̑g�ݍ��킹
---------------------------------------------------------*/
local SPELL_EXEC(2a_sakuya_baramaki1)
{
//	if (64 == (VR10_BOSS_SPELL_TIMER))
//	{
//	}
//	else
	if (64 > (VR10_BOSS_SPELL_TIMER))
	{
		spell_execute_04_pink_hearts(src_boss);
	}
	else
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x7f))	/* 128 256 384 512 (640 768) */
	{
		spell_execute_05_32way_dual(src_boss);
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g5�ʒ�-�{�X ���u��p�F�~�X�f�B���N�V�����v�ɂ�����Ƃ��������J�[�h
	-------------------------------------------------------
	Lunatic �ԃN�i�C�e 19way
	-------------------------------------------------------
---------------------------------------------------------*/
/*
------------------
		/	256
		/		�ԃN�i�C
		/	// (-r33)208 208==	64+144==256-48
27*8	/	216 == 64+152== 256-40// (r34-)
		/		�Ȃɂ����Ȃ�
14*8	/	112 112==	64+48
		/		�i�C�t
		/	64	64==	64+0
		/	------------
		/	64	64==	((64+256)-256)
		/		�Ȃɂ����Ȃ�
		/	48	48==	((64+240)-256)
		/		�i�C�t�̉������B
		/	0	0== 	((64+192)-256)
		/		���]�ړ�
		/	0	0== 	((64+192)-256)
*/

local SPELL_EXEC(28_sakuya_miss_direction)
{
//	if (/*256-64-48*/(64+144)< VR10_BOSS_SPELL_TIMER)
	if (/*256-64-48*/(256-40)< VR10_BOSS_SPELL_TIMER)
	{
		/*---------------------------------------------------------
			���@�_���A�S����24�����A�ԃN�i�C�e
		---------------------------------------------------------*/
		/* �ԃN�i�C�e */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		{
		//	���e�ʒu���{�X���S�փZ�b�g�B
			//	HATSUDAN_R11_speed256				= (t256(2.0)+((VR10_BOSS_SPELL_TIMER)<<2)); /* �e�� */
				HATSUDAN_R11_speed256				= (t256(2.0)-(VR10_BOSS_SPELL_TIMER));	/* �e�� */
				HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [�ԃN�i�C�e] */
				HATSUDAN_R16_n_way					= (24); 							/* [24way] */
			//	Lunatic �ԃN�i�C�e 19way
				HATSUDAN_R17_div_angle65536 		= (int)(65536/24);					/* �����p�x */
			// lunatic ��[19way]
		//
			for (VR03_i=0; VR03_i<(((cg_VR20_game_difficulty)+1)); VR03_i++)
			{
			//	VR06							+= (VR03_i<<10);	/* �e��x256 */
				VR06							+= (1<<10); 	/* �e��x256 */		//	���e�ʒu�����炷�B
			//
				HATSUDAN_R12_speed_offset			= t256(1)+(VR03_i<<8);/*(�e�X�g)*/
				CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
				#if 1/*(r35�̃V�X�e���ł́A�ȗ��\)*/
			//	HATSUDAN_R13_angle65536 			= (HATSUDAN_R13_angle65536); /* �e���p�x65536 */	/* ���@�_���e */
				#endif
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
	else
//	if (256-192< VR10_BOSS_SPELL_TIMER)
	if ((64+48)< VR10_BOSS_SPELL_TIMER)
	{;}/* �Ȃɂ����Ȃ� */
	else
//	if (256-192< VR10_BOSS_SPELL_TIMER)
	if ((64+0)< VR10_BOSS_SPELL_TIMER)
	{
		/* �i�C�t */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		{
			/* �e��x256 y256 �{�X�̒��S���甭�e�B */
			CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:���������쐬������ۂ��B */
				int int_aaa 					= ((HATSUDAN_R13_angle65536));		/* �e���p�x1024 */
				HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;			/* [�i�C�t�e] */
			for (VR03_i=0; VR03_i<3; VR03_i++)
			{
				// �e1 �e2	1.0 (1.5 2.0)
				HATSUDAN_R11_speed256			= (t256(1.0)+(VR03_i<<7));					/* �e�� */
				HATSUDAN_R13_angle65536 		= (int_aaa);			/* [�j��] */	/* �e���p�x1024 */
				HATSUDAN_R16_n_way				= (11); 				/* [�j��] */	/* [11way] */
				HATSUDAN_R17_div_angle65536 	= (int)(65536/(7*4));	/* [�j��] */	/* �����p�x([90/360]�x��7����==28����) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);/* �i�C�t�̉��͂��炷�K�v������ */
			#endif
		}
	}
	#if 0
	else
	if (/*256-64*/(48/*(64+240)-256*/) < VR10_BOSS_SPELL_TIMER)
	{;}/* �Ȃɂ����Ȃ� */
	else
	//if (/*256-64*/(0/*(64+192)-256*/) < VR10_BOSS_SPELL_TIMER)
	{
		/* �i�C�t�̉�����(3��) */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		{
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);/* �i�C�t�̉��͂��炷�K�v������ */
			#endif
		}
	}
	#endif
}
/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(28_sakuya_miss_direction)
{
	if (1<cg_VR20_game_difficulty)
	// Hard or Lunatic only.
	{
		card.layer_callback[1] = danmaku_01_standard_angle_sayuu_hansya_mover;/*(�ʏ�e�p)*/	/*(��ʊO�Ȃ甽�ˌ���)*/
	}
	else
	{
		// Easy or Normal only.(�W�����)
		card.layer_callback[1] = standard_angle_mover_00_callback;/*(�ʏ�e�p)*/
	}
//	card.dan maku_callback[2] = NULL;/*(���g�p)*/
//	card.dan maku_callback[3] = NULL;/*(���g�p)*/
	/*(���f�u�u���h�E�c�F�y�V���̎􂢁v�p)*/cg_BOSS_DATA_32_chuu_boss_mode = (13);/*[�J�n13way]*/
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g5�ʒ�-�{�X ��� ���U���ɂ�����Ƃ��������J�[�h(L)
	-------------------------------------------------------
	�͕핗�Ȃ񂾂��班���͕핗�ȃJ�[�h��������ƃe�X�g�őn���Ă݂��B
	��x�I�ɂ�psp-2000�Ȃ�A�gnormal5�ʂɒʏ�J�[�h�Ƃ��ďo�Ă����Ƃ��ē������炢���A
	������҂������Ȃ��Ċ����B�^�u���B
	�ȒP�ł��Ȃ����ǁA������Ȃ����ĕӂ��_���Ă݂��񂾂��ǁA��Փx�ǂ��������B
	psp-1000�̕����L�[�͎n�߂���lunatic�����A�i���O���ƈʒu������������邵�ȁB
	-------------------------------------------------------
	�݌v�����̂́A
	�ԃN�i�C�͂��܂ł���ʂɎc��̂Ō���(�߂�ǂ�����)�����B
	�i�C�t�͒ʏ�A�ԃi�C�t�͔��Ύ���B�i�C�t�͕K�����Ԋu�B
	�i�C�t�R��B��ʉ����ƃi�C�t��A�����Ɍ�������̂ő��x�����Ȋ����B
	�R��ɂ����͈̂Ӑ}�I�łQ������Ĕ��Α��ɐ؂�Ԃ��p�^�[��(���̎�����)������B
	(�Q�򂾂Ə��Ȃ����A�S�򂾂ƃ����Q���ۂ�)
	(�n�߂Č������͂R�򒼐��I�ɔ����邾�낤���A������Ɗ����Β����C���t�����A
	���������́u���̎������v�B�v�������Ԋu�������̂ŁA����邯�ǃ^�C�~���O���኱�V�r�A�B)
	-------------------------------------------------------
	lunatic�Ƃ����A����ȏ��Ŏ���Ŗ���Ă͍���̂Ŋ�{�I�ɂ������ǂ��B
	�ꌩ����������ǁA��̃i�C�t�Q�𔲂��邾��������A
	���Ƃ������ǂ��ňӊO�ƊȒP���ƁB(�^�u��)
	��{�I�ɖڐ�̃i�C�t�̑��x���x����āB�ԃN�i�C�ǂ����ĂȂ��Ƃ��ʂ�^�C�v�B
	�ԃN�i�C�����̓����_���Ȃ񂾂���A�l���Đ�ǂ݂��Ȃ��ƒǂ��l�߂���B
	�ǂ��l�߂�ꂽ�ꍇ�{�����Ă��ǂ����ǁA������x���Ȃ�i�C�t�Ɍ��Ԃ������̂Ō��Ԃ𔲂�����B
	�ǂ��l�߂��ă{����ꍇ�A�i�C�t�̑��x�������񂾂���A���R(���̃J�[�h�Ń{����ꍇ���)��������
	���Ȃ��ƂȂ�Ȃ���(��炢�{�����Ԃ��₽�璷���얲�͏���)�A�����Ɍ��ȃp�^�[���̐ԃN�i�C��
	���f�݂��Ă�̂��|�C���g�Ƃ����΃|�C���g���ȁH
	���Ȃ݂ɗH�X�q�Ŕ�����鑬�x�ɒ������Ă���܂��B
	�i�C�t���R�򒼐��I�ɔ�����p�^�[���ȊO�ɁA
	�i�C�t���Q������Ĕ��Α��ɐ؂�Ԃ��p�^�[��������̂�����A
	���̕ӁA�Ջ@���ςɐ؂�ւ���̂��R�c�Ƃ����΃R�c���ȁB
	(�i�C�t����W�O�U�O�ɂ����p�^�[���͈ꉞ�o���邯�ǁA���Ȃ����Ǝv����B
	���[��[�̂̕������ӂȐl�����邯�ǈ�ʓI(?)�ɂ͑哹�|���ۂ�����)
	(�i�C�t���P������Ĕ��Α��ɐ؂�Ԃ��p�^�[�������邯�ǁA�g����������B�m��Ȃ��Ă��������ȁB
	���̕����ƂŐԃN�i�C���o��̂�����A�ԃN�i�C�𑁂������ǂ݂��Ƃ��Ȃ��ƂȂ�Ȃ��B
	��ǂݎ��s�����ꍇ�A�W�O�U�O�ɓ�����̂͋Z�p�I�ɓ���̂�����A���̕��s���ɂȂ�B)
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	aaa_angle65536
	R0a 	aka_kunai_timer 	�ԃN�i�C�^�C�}�[
	R0b 	knife_kaiten		0(�i�C�t) or 1(�ԃi�C�t)
//	sta tic int ao_knife_timer; 		// �i�C�t�^�C�}�[
---------------------------------------------------------*/

//#define ADJUST3916	((65536/20)+(640))
#define ADJUST3916	(4000)
//#define ADJUST4444	(4200)
#define ADJUST4444	(4190)

local SPELL_EXEC(2d_sakuya_misogi_lunatic)
{
//	SPELL_TIME_0256 SPELL_TIME_0128
	if (127 == VR10_BOSS_SPELL_TIMER)/* �����l�Ƀ��Z�b�g�B */
	{
		#if 1
		/* �i�C�t: �E�㑤���猂���n�߂�B�E���Ȃ̂�90�x���炵�āAhatudan_system_regist_katayori_n_way()�̕␳���s���B */
	//	cg_BOSS_DATA_38_angleCCW65536	= (65536+(65536/4)-((65536*8)/20))+(ADJUST3916);				// �i�C�t
	//	cg_BOSS_DATA_38_angleCCW65536	= (((65536*2)/20))+(ADJUST3916);				// �i�C�t 	(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);�ŉ�����ɁA���v����(2/20)���猂���n�߂�B
		cg_BOSS_DATA_38_angleCCW65536	= (((65536*1)/18))+(ADJUST3916);				// �i�C�t 	(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);�ŉ�����ɁA���v����(2/20)���猂���n�߂�B
		// �{���͑ł��n�߂̐i�C�t�̒[���E��60�x���炢����ł��n�߁A
		// �ł��I���́A����60�x���炢�̈ʒu�ɂȂ�B
		#endif
		#if 1
		/* �ԃN�i�C: */
	//	VR09		= (65536/2);		// �ԃN�i�C
		VR09		= (65536/4)-(0);	// �ԃN�i�C (�E������)
		#endif
//		ao_knife_timer = 0; 	// �i�C�t
//		VR0a = 0;	// �ԃN�i�C
		VR0b &= 1;/* �O�̂��߃}�X�N */
		VR0b ^= 1;/* ���] */
	}
//	if (DANMAKU_0096_TIME > VR10_BOSS_SPELL_TIMER)/* �b���������Ȃ��B */
	if (48 > VR10_BOSS_SPELL_TIMER)/* �b���������Ȃ��B */
	{
//		ao_knife_timer--;
//		if (0 >= ao_knife_timer)
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
		{
		//	ao_knife_timer = (12);
//			ao_knife_timer = (8);
			/*	�i�C�t */
			if (0==VR0b)
			{	/* 0(�i�C�t) */
			//	cg_BOSS_DATA_38_angleCCW1024 -= (int)(256/5)+(10); /*CCW*/
			//	cg_BOSS_DATA_38_angleCCW1024 -= (int)(1024/20)+(10); /*CCW*/
			//	cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/20)+(640); /*CCW*/
			//	cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/20)+(640)+(128); /*CCW*/	/* 3276== (65536/20) */
				cg_BOSS_DATA_38_angleCCW65536 -= (ADJUST3916); /*CCW*/
			}
			else	/* 1(�ԃi�C�t) */
			{
				cg_BOSS_DATA_38_angleCCW65536 += (ADJUST3916); /*CCW*/
			}
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
			HATSUDAN_R13_angle65536 		= (cg_BOSS_DATA_38_angleCCW65536);	/* �e���p�x65536 */ 		/* [������e] */
			//
		//	HATSUDAN_R11_speed256			= (t256(2.5));						/* �e�� (t256(2.5)�Q�l�B�g�m�[�}��5��) */
		//	HATSUDAN_R11_speed256			= (t256(2.0));						/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
//			HATSUDAN_R11_speed256			= (t256(1.75)); 					/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
			HATSUDAN_R11_speed256			= (t256(1.00)); 					/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
			HATSUDAN_R12_speed_offset		= t256(6);/*�������Ă݂�Ă���*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI+VR0b;			/* [�i�C�t�e] */
			HATSUDAN_R16_n_way				= (8);								/* [8way] */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(5*4));
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/20);					/* �����p�x([360/360]�x��20����) */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/18);					/* �����p�x([360/360]�x��20����)[�ł��I��肪���΂ߏ�ɂȂ�] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */

		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* reset (1/32) */
		//	{
		//	//	aaa_angle1024	= (cg_BOSS_DATA_38_angleCCW1024)-(int)((1024/2));
		//		VR09 = (cg_BOSS_DATA_38_angleCCW65536)-(int)((65536/2));
		//	}
			#if (1)
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase888, (1));
			#endif
		}
	}
	VR0a--;
	if (0 > VR0a)
	{
		VR0a = 64+(ra_nd()&0x3f);
	}
	else
//	/* �ԃN�i�C�̕����x���̂ŁA�i�C�t����Ɍ����n�߂鎖�ɂ���B */
//	if (DANMAKU_0032_TIME > (VR0a))/* �b���������Ȃ��B */
	if (41 > (VR0a))/* �b���������Ȃ��B */
//	if ((128-40) < (VR0a))/* �Ō�͎b���������Ȃ��B */
	{
	//	else/* �������̒e�͖{���͂���ďo�銴���ɂ������B */
//	//	if ((10-1)>((((u8)VR0a)^0x20)&0x2f))/* x 10set */
//		if ((10-1)>(((VR0a)   )&0x0f))/* x 10set */
		/* 4��Ɉ��A�v10set */
		if ((0)==(((VR0a)	  )&0x03))/* x 10set */
		{
			/* �������͐ԃN�i�C */
		//	aaa_angle1024 -= (int)(256/5);
		//	aaa_angle1024 -= (int)(1024/20);
			VR09 -= (int)(65536/20);
		//	if (0 > (int)VR09)	{	VR09 = (65536/2);	}
			mask65536(VR09);
		//	HATSUDAN_R13_angle65536 		= (((VR09)+(65536*3/4))&(65536-1)); /* �e���p�x65536 */ 	/*��CCW*/
		//	HATSUDAN_R13_angle65536 		= (((VR09)+(65536*3/4))&(65536-1)); /* �e���p�x65536 */ 	/*��CCW*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [�ԃN�i�C�e] */
			HATSUDAN_R16_n_way				= (4);								/* [4way] */
			HATSUDAN_R17_div_angle65536 	= (int)(512-64);					/* [�����e]�̕����p�x(r32) */
//-------------------------
	// ��  [�����e]
			HATSUDAN_R11_speed256			= (t256(2.00)); 							/* �e�� (�o�n�߂͒x��) */
			HATSUDAN_R12_speed_offset		= t256(-1);/* �����H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
			HATSUDAN_R13_angle65536 		= (VR09);	/* �e���p�x65536 */ 	/*��CCW*/
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
//-------------------------
	// ��  [�����e]
			HATSUDAN_R11_speed256			= (t256(2.25)); 							/* �e�� (�o�n�߂͒x��) */
			HATSUDAN_R12_speed_offset		= t256(-1);/* �����H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
			HATSUDAN_R13_angle65536 		= (VR09);	/* �e���p�x65536 */ 	/*��CCW*/
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�g5�ʒ�-�{�X ��� ���U���ɂ�����Ƃ��������J�[�h(E-N-H)
	-------------------------------------------------------
	���̃J�[�h�̖{���́A
	�P�D��r�I����(�Ƃ����������x)�̐i�C�t�e�̕ǂ�������Ȃ���A
	�ُ�ɒx�����������Ȃ̂Œ������܂��Ĕ�����ԃN�i�C�e������鎖�B
	�Q�D�i�C�t�e�ƐԃN�i�C�e�̑��x���Ⴄ�̂ŁA�d�Ȃ��Ĕ�����ꍇ���������鎖�B
	�R�D�������Ȃ���A�d�Ȃ�͂�����x�̎��Ԃ��ώ@���Ă���Δ�������B
	�S�D(�R�D)�ɖ������āA�ώ@���Ԃ��Z��(���������ꍇ���K����������)�Ɖ^�������Ɣ������Ȃ��B
	-------------------------------------------------------
	�� �i�C�t
		�i�C�t�͋Ȃ������ǂɂȂ�Ȃ��Ɩ��͖͂����B
		��r�I�������x�����A���߂���Ɩ��͖͂����B�����ɂ��炢�炷��x�����K�v�B
	�� �ԃN�i�C
		�ԃN�i�C�ɂ͂��炢�炷��x�����K�v�B
		��ʉ��Ŕ����Ă����ꍇ�ɁA�u��ʉ�������ł̂݋}���ɑ��x���ω�����v�B
		�������������x�Œ�������K�v����B
		�O�L�Q�|�S�͎�ɉ�ʉ�������Ŕ������錻�ہB
		��ʒ�������ł́A���̕��G�ɋ߂��̂Ŕ��ː_�o�͗v�邪�A�O�L�Q�|�S�̌��ۂ͔������ɂ����B
	-------------------------------------------------------
	�� �ԃN�i�C
		�Ȃ񂩒m��񂪌����蒼������u�����e�v�������B
		�u�����e�v�{�u�����e�v���Ď����Ȃ��H
	-------------------------------------------------------
	����ƈႢ�A����������ɍs���Ȃ�����A������͏o���Ȃ��B
	(psp�̏c�𑜓x�ł͏�ɍs���X�y�[�X���Ȃ�)
	��������psp�̏c�𑜓x���S�R����Ȃ�����A�{�ƕ��̃`���������͖����B
	������x���E�ɓ�������Ĕ����ĖႤ����z�肵�Ă���B(������e���x��)
	����ɕ����Ė����e�͂����Ă��񂺂�Ⴄ�B(�ʕϐ��Ƃ�̂��ʓ|��������������)
	-------------------------------------------------------
	�i�C�t�̒e���͂��ꂭ�炢�����H�ԃN�i�C�̒e���͑��߂���B
	�ԃN�i�C�e�̎����͌���͂����Ԃ���Ă���̂ŕς������񂾂��ǁA
	�u�J�[�h�V�X�e����d���v���Ȃ��Ə�肭�����Ȃ������H�B
	-------------------------------------------------------
	�u�J�[�h�V�X�e����d���v�F2��ނ̈قȂ����J�[�h�������Ɍ��Ă�J�[�h�V�X�e���B
	�����������̂ɂ���ׂ������Ȃ��ׂ����������B(�p�`�F)
	-------------------------------------------------------
	�܂��S(����)�Ȃ̂ŁA(�v���C���[�ɂ���ȏ���)����ł�����Ă͍���B
	-------------------------------------------------------
	�i�C�tspeed256	speed_offset	/	�ԃN�i�Cspeed256	speed_offset
	t256(2.5)			(0) 			/	(0) 				(4) 			// �ǂ��񂾂��ǖ{��������B
	t256(2.0)			(0) 			/	(0) 				(2) 			// �ԃN�i�C�̏����x�����邩�Ȃ��B// �i�C�t�ƐԃN�i�C�����ꂷ���B�{��������B
	t256(1.75)			(0) 			/	(0) 				(1)
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
	R09 	aaa_angle65536
	R0a 	aka_kunai_timer 	�ԃN�i�C�^�C�}�[
	R0b 	ao_knife_timer		�i�C�t�^�C�}�[
---------------------------------------------------------*/
local SPELL_EXEC(01_sakuya_misogi_normal)
{
//	SPELL_TIME_0256 SPELL_TIME_0128
	if (127 == VR10_BOSS_SPELL_TIMER)/* �����l�Ƀ��Z�b�g�B */
	{
		#if 1
		/* �i�C�t: �E�㑤���猂���n�߂�B�E���Ȃ̂�90�x���炵�āAhatudan_system_regist_katayori_n_way()�̕␳���s���B */
	//	cg_BOSS_DATA_38_angleCCW65536	= (65536+(65536/4)-((65536*8)/20))+(ADJUST4444);				// �i�C�t
	//	cg_BOSS_DATA_38_angleCCW65536	= (((65536*2)/20))+(ADJUST4444);				// �i�C�t 	(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);�ŉ�����ɁA���v����(2/20)���猂���n�߂�B
		cg_BOSS_DATA_38_angleCCW65536	= (((65536*1)/18))+(ADJUST4444);				// �i�C�t 	(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);�ŉ�����ɁA���v����(2/20)���猂���n�߂�B
		// �{���͑ł��n�߂̐i�C�t�̒[���E��60�x���炢����ł��n�߁A
		// �ł��I���́A����60�x���炢�̈ʒu�ɂȂ�B
		#endif
		#if 1
		/* �ԃN�i�C: */
	//	VR09		= (65536/2);		// �ԃN�i�C
		VR09		= (65536/4)-(0);	// �ԃN�i�C (�E������)
		#endif
		VR0b = 0;	// �i�C�t
//		VR0a = 0;	// �ԃN�i�C
	}
//	if (DANMAKU_0096_TIME > VR10_BOSS_SPELL_TIMER)/* �b���������Ȃ��B */
	if (100 > VR10_BOSS_SPELL_TIMER)/* �b���������Ȃ��B */
	{
		VR0b--;
		if (0 >= VR0b)
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
		{
		//	VR0b = (12);
			VR0b = (8);
			/*	�i�C�t */
		//	cg_BOSS_DATA_38_angleCCW1024 -= (int)(256/5)+(10); /*CCW*/
		//	cg_BOSS_DATA_38_angleCCW1024 -= (int)(1024/20)+(10); /*CCW*/
		//	cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/20)+(640); /*CCW*/
		//	cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/20)+(640)+(128); /*CCW*/	/* 3276== (65536/20) */
			cg_BOSS_DATA_38_angleCCW65536 -= (ADJUST4444); /*CCW*/
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
		//	HATSUDAN_R11_speed256			= (t256(2.5));					/* �e�� (t256(2.5)�Q�l�B�g�m�[�}��5��) */
		//	HATSUDAN_R11_speed256			= (t256(2.0));					/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
//			HATSUDAN_R11_speed256			= (t256(1.75)); 				/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
		//	HATSUDAN_R11_speed256			= (t256(1.00)); 				/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
			HATSUDAN_R11_speed256			= (t256(1.25)); 				/* �e�� psp�͏c�𑜓x���Ȃ��̂łƂɂ����x�����Ȃ��ƁB */
		//	HATSUDAN_R12_speed_offset		= t256(0.0);/* �Ă��� */
		//	HATSUDAN_R12_speed_offset		= t256(1.0);/* �������Ă݂�Ă��� */
		//	HATSUDAN_R12_speed_offset		= t256(6.0);/* �������Ă݂�Ă��� */
			HATSUDAN_R12_speed_offset		= t256(4.0);/* �������Ă݂�Ă��� */
			HATSUDAN_R13_angle65536 		= (cg_BOSS_DATA_38_angleCCW65536);	/* �e���p�x65536 */ 		/* [������e] */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;		/* [�i�C�t�e] */
			HATSUDAN_R16_n_way				= (8);							/* [8way] */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(5*4));
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/20);				/* �����p�x([360/360]�x��20����) */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/18);				/* �����p�x([360/360]�x��20����)[�ł��I��肪���΂ߏ�ɂȂ�] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* reset (1/32) */
		//	{
		//	//	aaa_angle1024	= (cg_BOSS_DATA_38_angleCCW1024)-(int)((1024/2));
		//		VR09	= (cg_BOSS_DATA_38_angleCCW65536)-(int)((65536/2));
		//	}
			#if (1)
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(�I��)*/
			};
			cpu_exec((u32*)&codebase888, (1));
			#endif
		}
	}
	VR0a--;
	if (0 > VR0a) /* VR0a �����̏ꍇ */
	{
		VR0a = 32/*64*/+(ra_nd()&0x3f);
	}
	else /* VR0a �����̏ꍇ */
//	/* �ԃN�i�C�̕����x���̂ŁA�i�C�t����Ɍ����n�߂鎖�ɂ���B */
//	if (DANMAKU_0032_TIME > (VR0a))/* �b���������Ȃ��B */
//	if ((41) > (VR0a))/* �b���������Ȃ��B */
	if ((41-16+(((unsigned)cg_VR20_game_difficulty)<<4)) > (u32)(VR0a))/* �b���������Ȃ��B */
//	if ((128-40) < (VR0a))/* �Ō�͎b���������Ȃ��B */
	{
	//	else/* �������̒e�͖{���͂���ďo�銴���ɂ������B */
//	//	if ((10-1)>((((u8)VR0a)^0x20)&0x2f))/* x 10set */
//		if ((10-1)>(((VR0a)   )&0x0f))/* x 10set */
		/* 4��Ɉ��A�v10set */
		if ((0)==(((VR0a)	  )&0x03))/* x 10set */
		{
			/* �������̐ԃN�i�C�͑S�R�_���D */
		//	aaa_angle1024 -= (int)(256/5);
		//	aaa_angle1024 -= (int)(1024/20);
			VR09 -= (int)(65536/20);
		//	if (0 > (int)VR09)	{	VR09 = (65536/2);	}
			mask65536(VR09);
		//	HATSUDAN_R11_speed256			= (t256(2.0));						/* �e�� ���߂��� */
		//	HATSUDAN_R11_speed256			= (t256(1.0));						/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R11_speed256			= (t256(0.5));						/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R11_speed256			= (t256(0.25)); 					/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R13_angle65536 		= (((VR09)+(65536*3/4))&(65536-1)); /* �e���p�x65536 */ 	/*��CCW*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [�ԃN�i�C�e] */
			HATSUDAN_R16_n_way				= (4);								/* [4way] */
			HATSUDAN_R17_div_angle65536 	= (int)(512-64);					/* [�����e]�̕����p�x(r32) */
//-------------------------
	// ��  [�����e]
		//	HATSUDAN_R11_speed256			= (0);								/* �e�� (�o�n�߂͒x��) */
//			HATSUDAN_R11_speed256			= (t256(0.25)); 					/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R11_speed256			= (t256(3.25)); 					/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R11_speed256			= (t256(3.00)); 					/* �e�� (�o�n�߂͒x��) */
			HATSUDAN_R11_speed256			= (t256(2.00)); 					/* �e�� (�o�n�߂͒x��) */

		//	HATSUDAN_R12_speed_offset		= t256(3/*0*/);/* �������Ă݂� �Ă��� */
//			HATSUDAN_R12_speed_offset		= t256(2);/* �������H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
		//	HATSUDAN_R12_speed_offset		= t256(1);/* �������H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
			HATSUDAN_R12_speed_offset		= t256(-1);/* �����H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
			HATSUDAN_R13_angle65536 		= (VR09);	/* �e���p�x65536 */ 	/*��CCW*/
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
//-------------------------
	// ��  [�����e]
		//	HATSUDAN_R11_speed256			= (t256(0.25)); 					/* �e�� (�o�n�߂͒x��) */
		//	HATSUDAN_R11_speed256			= (t256(1.25)); 					/* �e�� (�o�n�߂͒x��) */
			HATSUDAN_R11_speed256			= (t256(2.25)); 					/* �e�� (�o�n�߂͒x��) */
			HATSUDAN_R12_speed_offset		= t256(-1);/* �����H(�������e�Ȏ��͊ԈႢ�Ȃ��H) */
			HATSUDAN_R13_angle65536 		= (VR09);	/* �e���p�x65536 */ 	/*��CCW*/
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
	}
}
