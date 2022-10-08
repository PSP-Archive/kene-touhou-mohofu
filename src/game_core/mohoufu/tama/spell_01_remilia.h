
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���~���A ���ۂ��J�[�h���`���܂��B
---------------------------------------------------------*/
/*---------------------------------------------------------
	�V���b�g���e�T�u�B
	-------------------------------------------------------
	C����̏ꍇ�͋��ʃT�u�B
	�X�N���v�g�������ꍇ�́A�R�s�y����B
	-------------------------------------------------------
	�g�p���W�X�^
	cg_BOSS_DATA_38_angleCCW65536; ���n���A�_����p�x
---------------------------------------------------------*/
local BOSS_EXEC(remilia_shot00)
{
	// ��  [��ʒe]
//	HATSUDAN_R11_speed256			= (t256(3.5));						/* �e�� */
//	HATSUDAN_R11_speed256			= (t256(2.25)); 					/* �e�� */
	HATSUDAN_R11_speed256			= (t256(8.00)); 					/* �e�� */
//	HATSUDAN_R12_speed_offset		= -t256(1);/* �����e�H */
	HATSUDAN_R12_speed_offset		= -t256(4);/* �����e�H */
	HATSUDAN_R13_angle65536 		= cg_BOSS_DATA_38_angleCCW65536;/* ���n���A�_����p�x */
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	HATSUDAN_R15_bullet_obj_type	= BULLET_OODAMA32_01_AKA;			/* [�ԑ�ʒe] */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		// ��  [���ʒe]
	//	HATSUDAN_R11_speed256			= (t256(6.00)); 					/* �e�� */
		HATSUDAN_R12_speed_offset		= -t256(2);/* �����e�H */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);			/* [�ԑ咆�e] */
	{
		u32 rrr;
		rrr = (ra_nd());
		for (VR03_i=0; VR03_i<(8*3); VR03_i++)
		{
			rrr += 13579;
			rrr &= 0xffffffffu;
			HATSUDAN_R11_speed256		= (t256(5.00)+(rrr&0x1ff)); 					/* �e�� */
			HATSUDAN_R13_angle65536 	= cg_BOSS_DATA_38_angleCCW65536 + ((rrr) & ((65536/8)-1)) - ((65536/16)-1);/* ���@�_���p */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
		// ��  [���ʒe]
	//	HATSUDAN_R11_speed256			= (t256(4.00)); 					/* �e�� */
		HATSUDAN_R12_speed_offset		= -t256(1);/* �����e�H */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);				/* [�ԑ咆�e] */
		for (VR03_i=0; VR03_i<(16*2); VR03_i++)/*(16)*/
		{
			rrr += 1234567;
			rrr &= 0xffffffffu;
			HATSUDAN_R11_speed256		= (t256(2.00)+(rrr&0x1ff)); 					/* �e�� */
			HATSUDAN_R13_angle65536 	= cg_BOSS_DATA_38_angleCCW65536 + ((rrr) & ((65536/4)-1)) - ((65536/8)-1);/* ���@�_���p */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
	#if (1)
	CPU_CALL(cpu_auto_bullet_play_default);
	#endif
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]	���~���A �ʏ�U��2 ���ۂ�����
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B��{�I��24��Ɉ�񏈗��B
	R09 	���񐔐����B
	R0a 	���Z�p�x�B
	R0b 	�e�p�x(��ʒu��ێ�)�B
---------------------------------------------------------*/
//local SPELL_INIT(1f_remilia_kougeki2)
//{
//}
/*---------------------------------------------------------
	���~���A �ʏ�U��2 ���ۂ�����
	-------------------------------------------------------
	1�b��������A3�b�x��(�ړ�)�B

	REG_0f	��Փx
	REG_10	�{�X�^�C�}�[
---- ---- ---- ----
0000 0011 1111 1111
---------------------------------------------------------*/

local SPELL_EXEC(1f_remilia_kougeki2)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 24, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));// ��{�I��24��Ɉ�񏈗��B(����)
	if (0==(VR08))
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 16, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));// 16, �ő�10(10.666==256/24)�Ȃ̂�16�̓_�~�[�l�B
		if (1==(VR09))	/* �n�߂Ă̏ꍇ */
		{
			CPU_CALL(calculate_jiki_nerai);/* ���@�_���p�쐬 */
			cg_BOSS_DATA_38_angleCCW65536		= HATSUDAN_R13_angle65536;/* ���@�_���p */
			VR0a	= (int)( ((65536/12)));/*(table3[]���Z�p�x��ݒ�)*/
			if ((cg_BOSS_DATA_3a_center_x256) & 0x100)
			{
				VR0a	= -VR0a;/*(table3[]���Z�p�x��ݒ�)*/
			}
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]���Z�p�x���ړ�)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]���Z�p�x���ړ�)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]���Z�p�x���ړ�)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]���Z�p�x���ړ�)*/
			VR0b = cg_BOSS_DATA_38_angleCCW65536;/*(�n�߂̊p�x��ݒ�)*/
		}
		if (0<(6-1)+(cg_VR20_game_difficulty)-(VR09))
		{
			// easy 	�� 6�� 3�� 0000
			// normal	�� 7�� 5�� 0001
			// hard 	�� 8�� 7�� 0010
			// lunatic	�� 9�� 9�� 0011
			/*(�ێ��p�x���ړ�)*/
			{
				VR0b	+= VR0a;/*(table2[]�ێ��p�x���ړ�)*/
				/*(��p�x�ɕێ��p�x��ݒ�)*/
				cg_BOSS_DATA_38_angleCCW65536		= VR0b;/*(��p�x���w��)*/
			}
			remilia_shot00();
		}
	}
}

#if 0
	if (0x80 == (VR10_BOSS_SPELL_TIMER & 0x80))/* �㔼 */
	{
	//	if (0xc0 == (VR10_BOSS_SPELL_TIMER & 0xc0))
		if (0xc0 == (VR10_BOSS_SPELL_TIMER & 0xc7))/* �W��Ɉ�� */
		{
			#if 0
			/* ���^�[�� 8�e */
					if (0x0000 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* ���@�_������ */
			else	if (0x0100 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* CW ���� */
			else	if (0x0200 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* CCW ���� */
			else/*	if (0x0300 == (VR10_BOSS_SPELL_TIMER & 0x30)) */{remilia_shot00(src);}	/* ���@�_������ */	/* ��C���� */
			#endif
		}
	}
#endif


/*---------------------------------------------------------

��e�����e�����e����
�����u�g�F�̖��E�v
128way�����󍂑��i�C�t�e
�Ԑj�e�΂�T�����XWAY�ԑ�e�A�ˁ��S����12way���e�A�ˁi���[�v�j
�g���u�X�J�[���b�g�V���[�g�v
---------------------------------------------------------*/


/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B(8���1�񔭒e����)
	R0a 	�ێ��p�x�B
	-------------------------------------------------------
128way�����󍂑��i�C�t�e
	�g�U�^�S���ʃi�C�t�e
	80�����e == (8way[hi to 0]+8way[slow to 0]) x 5way(5����)
	-------------------------------------------------------

---------------------------------------------------------*/
//local SPELL_EXEC(07_80way_dual_five)
local SPELL_EXEC(44_remilia_rasen_knife)/* ���łȂ��ė����ł��B */
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))
	{
				HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
				HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI+1;				/* [aka�i�C�t�e] */
				HATSUDAN_R13_angle65536 		= VR0a; 		/* �p�x */
		{	/* 1����65536���������p�x */
			for (VR03_i=0; VR03_i<(4); VR03_i += (1) ) /* [4����] */	/* �p�x(65536[90/360�x]�� 4 ����) */
			{
				HATSUDAN_R13_angle65536 += (65536/4);			/* �p�x */
				mask65536(HATSUDAN_R13_angle65536);
				//
				HATSUDAN_R11_speed256			= (t256(2.00) );	/* ���e t256(3.00) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				//
				HATSUDAN_R11_speed256			= (t256(2.40) );	/* �����e t256(3.14) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
		}
				HATSUDAN_R13_angle65536 -= (65536/128); 				/* ���̊p�x */
				VR0a		= HATSUDAN_R13_angle65536;			/* �p�x��ێ� */
	}
		#if (0)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
}

/*---------------------------------------------------------
	���f�u�u���h�E�c�F�y�V���̎􂢁v
	-------------------------------------------------------
	�u���b�h�}�W�b�N�v
	-------------------------------------------------------
	��u�����ʃT�u
	-------------------------------------------------------
	R08 	�J�E���^�B�e�u���Ԋu
	R0b 	���e��A�W�܂�X���W(t256�`��)
	R0c 	���e��A�W�܂�Y���W(t256�`��)
	-------------------------------------------------------
	C����̏ꍇ�͋��ʃT�u�B
	�X�N���v�g�������ꍇ�́A�R�s�y����B
---------------------------------------------------------*/
local TAMA_FUNC(remilia_common_tama_oki_sub)
{
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* �e�� */
	//
	//	if (0==(src_tama->jyumyou&0x0f))/*16���1��e��u��*/
	//	if (0==(src_tama->jyumyou&0x07))/*8���1��e��u��*/
		if (0 == VR08)
		{
			//
			VR04	= (VR0b);
			VR05	= (VR0c);
			set_REG_DEST_XY(src_tama);			/* �e��x256 y256 �eobj���S���甭�e�B */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);//_bbb(zzz_player, dest);
	//[�d��]set_REG_DEST_XY(src_tama);			/* �e��y256 �eobj���S���甭�e�B */
			HATSUDAN_R11_speed256			= t256(0);	/* �e�� */
			HATSUDAN_R12_speed_offset		= t256(0);/*(�e�X�g)*/
		//	HATSUDAN_R13_angle65536 		= (0);	/* ��p�x */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);		/* [�Ԓe] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
}

/*---------------------------------------------------------
	���f�u�u���h�E�c�F�y�V���̎􂢁v
	-------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(brp_tamaoki_danmaku_01_callback)/* ��u�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-0) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[0]�J�E���g�̒e */
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* �e�L�g�[ */
		CPU_CALL(cpu_voice_play);
	}
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[224]�J�E���g�����̒e */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[225]�J�E���g�����̒e */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(���v���)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 -= (3<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		else
		{	/*CCW(�����v���)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		//	src_tama->rotationCCW1024 += (3);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
			src_tama->rotationCCW65536 += (3<<6);/* 90/360 �x �Ȃ��Ă݂�e�X�g(32�J�E���g�����ċȂ���B256==8*32) */
		}
		remilia_common_tama_oki_sub(src_tama);
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
	�u���b�h�}�W�b�N�v
	-------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(red_magic_tamaoki_danmaku_01_callback)/* ��u�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-0) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[0]�J�E���g�̒e */
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* �e�L�g�[ */
		CPU_CALL(cpu_voice_play);
	}
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[224]�J�E���g�����̒e */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[225]�J�E���g�����̒e */
	{
		if (0!=(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{
			/*(���E�̕ǂŔ��˂���B)*/
			if (src_tama->center.x256 < t256(32))
			{
				/*(��x�������˂��Ȃ�)*/
			//	src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			//	src_tama->rotationCCW1024 -= (1024/2);/* 180/360 �x �Ȃ��Ă݂�e�X�g */
				goto red_magic_hansya_syori;
			}
			else
			if (src_tama->center.x256 > t256(32)+t256(320) )
			{
			red_magic_hansya_syori:
				/*(��x�������˂��Ȃ�)*/
				src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_01)|(0)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			//	src_tama->rotationCCW1024 -= (1024/2);/* 180/360 �x �Ȃ��Ă݂�e�X�g */
			//	src_tama->rotationCCW1024 = (1024)-(src_tama->rotationCCW1024); /* ���][��1] */
				src_tama->rotationCCW65536 = (65536)-(src_tama->rotationCCW65536); /* ���][��1] */
			}
		}
		remilia_common_tama_oki_sub(src_tama);
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
	[callback t02 section: �e�����C���[�O���[�v(2)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(remilia_tahane_danmaku_02_callback)/* �쒵�� */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-128) == src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[128]�J�E���g �̒e */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* �e�� */
		/* (�ʏ�e�֕ϐg����) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

local void tamaoki_kankaku_void(void)
{
	//	#define TAMA_DATA_10_TAMA_OKI_KANKAKU
	VR08--;
	if (0 > VR08)
	{
		VR08 = VR09;//[�萔1]n��Ɉ��e��u���B
	}
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]	���f�u�u���h�E�c�F�y�V���̎􂢁v
	-------------------------------------------------------
	����(r35)�̃X�y�J�V�X�e���̏ꍇ�A�d�l��
	�X�y�J���܂����郌�W�X�^�l��ێ��ł��Ȃ��B
	(�X�y�J���n�܂�^�C�~���O�ŋ����I�Ƀ��W�X�^��0�N���A����Ă��܂���)
	-------------------------------------------------------
	�i�C�t��13way �� 18way�ɑ�����B
	-------------------------------------------------------
	�g�p���W�X�^:
	R09 = ��Փx�ʒ萔1;
	R0d:	���e��
	R0e:	������
---------------------------------------------------------*/
local SPELL_EXEC(42_remilia_vlad_tepes)
{
	if ((SPELL_TIME_0256-1) == VR10_BOSS_SPELL_TIMER) /*(��Ԏn��)*/
	{
		HATSUDAN_R11_speed256			= t256(1.0);	/* �e�� */
		HATSUDAN_R12_speed_offset		= t256(5);/*(�e�X�g)*/
		HATSUDAN_R13_angle65536 		= 0;	/* ��p�x */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((ra_nd()) & TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;		/* [�i�C�t�e] */
		#if 0
	//	HATSUDAN_R16_n_way				= (13); 	/* [13way] */		/* ���e�� */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(13));	/* �����p�x(65536[360/360�x]�� 13 ����) */
		#else/*(�Ƃ肠����)*/
		HATSUDAN_R16_n_way				= (VR0d); 	/* [13way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= (VR0e);	/* �����p�x(65536[360/360�x]�� 13 ����) */
		#endif

		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		u32 aaa = ra_nd();
		VR0b = ((aaa	)&0xff00) + t256(((480-128-32-256)/2));
		VR0c = ((aaa<<8 )&0xff00) + t256(((272-256)/2));
		#if (1)
		AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"�{�X����1",		/* r	�����[�� */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
		CPU_CALL(cpu_voice_play);
		#endif
	}
	tamaoki_kankaku_void();
}


/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]	�u���b�h�}�W�b�N�v
	-------------------------------------------------------
	����(r35)�̃X�y�J�V�X�e���̏ꍇ�A�d�l��
	�X�y�J���܂����郌�W�X�^�l��ێ��ł��Ȃ��B
	(�X�y�J���n�܂�^�C�~���O�ŋ����I�Ƀ��W�X�^��0�N���A����Ă��܂���)
	-------------------------------------------------------
	�g�p���W�X�^:
	R0b 	���e��A�W�܂�X���W(t256�`��)
	R0c 	���e��A�W�܂�Y���W(t256�`��)
	R0e 	�����p�x
---------------------------------------------------------*/
local SPELL_EXEC(43_remilia_red_magic)
{
	/*(���f�u�u���h�E�c�F�y�V���̎􂢁v�ɔ�ׂāA�u���b�h�}�W�b�N�v�͍X�V�Ԋu���Z���B(���񂾂񑁂��Ȃ�H))*/
	if ((SPELL_TIME_0192-1) == VR10_BOSS_SPELL_TIMER) /*(��Ԏn��)*/
	{
		/*(���f�u�u���h�E�c�F�y�V���̎􂢁v�ɔ�ׂāA�u���b�h�}�W�b�N�v�̑�ʒe�̓����͔��ɒx��)*/
		HATSUDAN_R11_speed256			= t256(0.5);	/* �e��(r40==0.5, r39==1.0) */
		HATSUDAN_R12_speed_offset		= t256(3);/*(�e�X�g)*/
	//	HATSUDAN_R13_angle65536 		= (65536/4);	/* ��p�x(�����Ɍ��B���E����O�x) */
		HATSUDAN_R13_angle65536 		= ((ra_nd()) & 0x1fff);	/* ��p�x(?)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_01_AKA); 	/* [����e] */
		HATSUDAN_R16_n_way				= VR0d;// (10); /* [10way] */		/* ���e�� */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(10)); /* �����p�x(65536[360/360�x]�� 10 ����) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		u32 aaa = ra_nd();
		VR0b = ((aaa	)&0xff00) + t256(((480-128-32-256)/2));
		VR0c = ((aaa<<8 )&0xff00) + t256(((272-256)/2));
		#if (1)
		AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"�{�X����1",		/* r	�����[�� */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
		CPU_CALL(cpu_voice_play);
		#endif
	}
	tamaoki_kankaku_void();
}
/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]	���f�u�u���h�E�c�F�y�V���̎􂢁v
	-------------------------------------------------------
	R09[�萔1]n��Ɉ��e��u���B
---------------------------------------------------------*/
//	TAMA_DATA_10_TAMA_OKI_KANKAKU	= (0);// �J�E���^
//	VR04_NAN_IDO_DECODE = ((16)-((cg_VR20_game_difficulty)<<2));//[�萔1]n��Ɉ��e��u���B
//	VR04_NAN_IDO_DECODE = NAN_IDO_DECODE((16), (12), (8), (4));//[�萔1]n��Ɉ��e��u���B
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((16), (12), (8), (4));//[�萔1]n��Ɉ��e��u���B
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((16), (10), (8), (4));//[�萔1]n��Ɉ��e��u���B
//	 (nan_ido);
//	VR09	= VR04_NAN_IDO_DECODE;
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[�萔1]�J�̑��x
//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[�萔2]�ԐN�i�C���Ȃ���p�x

local SPELL_INIT(42_remilia_vlad_tepes)
{
	//
	#define R32 R32_BOSS_DATA_chuu_boss_mode
	static const u32 codebase_init[7] =
	{
		// (1) VR0d = cg_BOSS_DATA_32_chuu_boss_mode;
		MCODE(OP0x01_MOVER_PD, NAX, R0d, R32),
		// (2)	// R09 = ��Փx�ʒ萔1;
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(�������A�����e)*/
		PACK_NAN_IDO_CONST((16), (10), (8), (4)), 	/* ������(r41-) */
		// (3)	// R0e = 65536 / R0d; = ��Փx�ʒ萔2;(�����p�A�����e[65536/32])
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(�����p�A�����e)*/ 	/* �����p�x */
		// (4) if (17 < (s32)VR32) {goto end;}/*[�ő�18way]*/
		MCODE(OP0x09_BFL_RS, (17), R32, (u8)(+1)),//	(end+1); �t���[�����番��
		// (5) cg_BOSS_DATA_32_chuu_boss_mode++;
		MCODE(OP0x01_MOVER_PD, (u8)(+1), R32, R32), /*(�C���f�b�N�X�t)*/
		// (6) //	(end+1:);
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_init, (5));//
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]	�u���b�h�}�W�b�N�v
	-------------------------------------------------------
	R09[�萔1]n��Ɉ��e��u���B
	R0d 	��Փx�ʒ萔1
---------------------------------------------------------*/

local SPELL_INIT(43_remilia_red_magic)
{
	static const u32 codebase_init[5] =
	{
		// (1)	// VR09 = [�萔1]n��Ɉ��e��u���B
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	//	PACK_NAN_IDO_CONST((32), (24), (16), (8)),//[�萔1]n��Ɉ��e��u���B
		PACK_NAN_IDO_CONST((32), (20), (16), (13)),//[�萔1]n��Ɉ��e��u���B
		// (2)	// VR0d = ��Փx�ʒ萔1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(�������A�g�F)*/
	//	PACK_NAN_IDO_CONST((10), (10), (13), (18)),/*tama_const_H06_NUMS_ALICE_RED*/	/*(�������A�g�F)*/
		PACK_NAN_IDO_CONST((10), (13), (20), (24)),/*tama_const_H06_NUMS_ALICE_RED*/	/*(�������A�g�F)*/
		// (3)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e  = 65536 / R0d;/*(�����p�A�g�F)*/	/*(�����p�x�A�g�F)*/
	};
	cpu_exec((u32*)&codebase_init, (3));//
	//
}
//	TAMA_DATA_10_TAMA_OKI_KANKAKU	= (0);// �J�E���^
//	VR09	= ((16)-((cg_VR20_game_difficulty)<<2));//[�萔1]n��Ɉ��e��u���B
//	VR09	= ((32)-((cg_VR20_game_difficulty)<<3));//[�萔1]n��Ɉ��e��u���B
	//
	#if 0
	// �� �u���b�h�}�W�b�N�v���ǂ��p
	VR0d	= [tama_const_H09_NUMS_REMI_MAGIC];  /*(�������A�g�F)*/ (10),					(10),					(13),					(18),
	VR0e	= [tama_const_H10_DIVS_REMI_MAGIC];  /*(�����p�A�g�F)*/ (int)(65536/(10)),		(int)(65536/(10)),		(int)(65536/(13)),		(int)(65536/(18)),
	#endif
