
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̑��̃J�[�h���`���܂��B
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�������̗d��1(�V��l?)�����J�[�h
	-------------------------------------------------------
	28�x�� �� 100��e �� 7���� BULLET_UROKO14_05_MIDORI		speed256	= t256(3.25)+((difficulty)<<6);
	28�x�� �� 100�����e �� 8���� BULLET_UROKO14_04_MIZUIRO		speed256	= (t256(3.0)+((difficulty)<<6));
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B	(�U��wait�p)	  int YOKAI1_DATA_wait2 = 0;	// (10-1)
	R0a 	�F�l(0��1)
---------------------------------------------------------*/

local SPELL_EXEC(11_tengu_shot)
{
	static /*const*/ u32 codebase_exec[29] =
	{
	//	if (100 < (VR10_BOSS_SPELL_TIMER & 0x7f)) {return;}
	/* VR11, [�j��]*/
	// (1) VR11 = VR10 & 0x7f;
	MCODE(OP0x1d_ANDM_PD, 0x7f, R11, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (2) if (100 < VR11)) {goto qqq_4+26;}/*(�t���[�����番��B)*/
	MCODE(OP0x09_BFL_RS, (100), R11, (u8)(+26)),// (qqq_4+26:); 	/* ���߂� 28[frame]�͂��x�� */
	//------------------
	//	if (128 > (VR10_BOSS_SPELL_TIMER))
	//			{VR0a = (1);}/* �����e �� 8���� */
	//	else	{VR0a = (0);}/* ��e �� 7���� */
	// (3) VR0a = (VR10_BOSS_SPELL_TIMER >> 7); 	/*[�����e����t�ɂȂ邯�Ǌȗ���]*/
	MCODE(OP0x1e_ASRM_PD, (7), R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (4) VR0a = VR0a & 0x01;	/*[����ł͗v��Ȃ����ǁA�X�y�����Ԃ𒷂��ύX�����ꍇ�ɍ���̂ŔO�̈׃}�X�N���Ƃ�]*/
	MCODE(OP0x1d_ANDM_PD, 0x01, R0a, R0a),/*(�V���[�g�������A�h���b�V���O)*/
	// (5)	//	VR04 = ((20-1)-(cg_VR20_game_difficulty<<2));
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((19), (15), (11), ( 7)),
	// (6)	//	count_up_limit_NUM(R08, VR04);
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[���W�X�^�ԐڃA�h���b�V���O]*/, R08, R04/*[��Փx�ʒ萔]*/),
	// (7)	if (0 != VR08)	{return;}
	MCODE(OP0x08_BNE_RS, (0), R08, (u8)(+20)),// (qqq_4+20)
	/*(�{�X�X�y�J�̏ꍇ�̂ݏȗ��\�A���{�X�̏ꍇ�ȗ��ł��Ȃ�)*/
	/* �e��x256 y256 ���S���甭�e�B */
	// ���@�_���p�쐬�B
	// (8)  (calculate_boss_to_jiki_nerai);/* ���@�_���p�쐬 */ /* �e��x256 y256 �{�X�̒��S���甭�e�B */
	MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	/* VR11, VR12[�j��]*/
	// (9) VR12 = (cg_VR20_game_difficulty << 6);
	MCODE(OP0x1f_ASLM_PD, (6), R12, R20_PLAYER_DATA_game_difficulty),/*(�V���[�g�������A�h���b�V���O)*/
	// (10) VR11 = (VR0a << (8-2));
	MCODE(OP0x1f_ASLM_PD, (8-2), R11, R0a),/*(�V���[�g�������A�h���b�V���O)*/
	// (11) 	VR11 += VR12;
	MCODE(OP0x04_ADDR_PD, NAX, R11, R12),
	// (12) HATSUDAN_R11_speed256			+= (t256(2.0));//(t256(3.0));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
	(t256(2.0)),
	// (13) HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(�e�X�g)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3/*6*/)),/*(�e�X�g)*/
	//	HATSUDAN_R13_angle65536 		= ((HATSUDAN_R13_angle65536));
	//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	// (14) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT)),
	// (15) HATSUDAN_R15_bullet_obj_type	= (VR0a);
	MCODE(OP0x01_MOVER_PD, NAX, R15, R0a),
	// (16) VR15 += (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
	((BULLET_KOME_BASE + TAMA_IRO_04_MIZU_IRO)),
//	((BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO)),
	// (17) HATSUDAN_R16_n_way				= (7)+(VR0a);
	MCODE(OP0x01_MOVER_PD, (u8)(+7), R16, R0a),/*(�C���f�b�N�X�t)*/
	// (18) HATSUDAN_R17_div_angle65536 	= (int)(65536/24);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/24),
	// (19)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	// (20) AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* �e�L�g�[ */
	MCODE(OP0x1c_MOVEM_PD, TRACK04_TEKIDAN, R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (21) AUDIO_18_voice_number	= VOICE15_BOSS_KOUGEKI_01;
//	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	MCODE(OP0x1c_MOVEM_PD, VOICE15_BOSS_KOUGEKI_01, R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (22)  (cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
// (qqq_4+20:) (qqq_4+26:)
	// (23)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (22));
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	���^��`�������w�p �e
	-------------------------------------------------------
	���^�`����
	-------------------------------------------------------
	VR08 �ꎞ�g�ptemp�B
---------------------------------------------------------*/
//	VR09	= (t256(1.0));//[�萔1]�J�̑��x
#define VR0a_hosi_set_position_cx256	VR0a	/* ���^�`���Ă���W�ʒu��ێ��B */
#define VR0b_hosi_set_position_cy256	VR0b	/* ���^�`���Ă���W�ʒu��ێ��B */
#define VR0c_hosi_vx256 				VR0c	/* ���^�̍����ړ��x�N�g���ʁBvx256 */
#define VR0d_hosi_vy256 				VR0d	/* ���^�̍����ړ��x�N�g���ʁBvy256 */
#define VR0e_my_angle65536				VR0e	/* �ێ��p�x[���^��`���ꍇ�Ɏg���p�x] */

local TAMA_FUNC(move_bullet_sakuya_hosi_gata_callback)
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-(128)) < src_tama->jyumyou)/* ���e�G�t�F�N�g�ォ��[128]�J�E���g�����̒e */
	{
		;
	}
	else/* �\�ߐݒ肳�ꂽ���Ԃœ��� */
	{
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
			/* (�J�~��e�֕ϐg����) */
			src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		}
		else
		{
			/* (�ʏ�e�֕ϐg����) */	/*(��ǂ��e�͒ʏ�e)*/
			src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		}
	}
//	gamen_gai_nara_osimai(src_tama);/* ��ʊO�Ȃ炨���܂� */
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(��ʊO�e����)*/
}

local SPELL_EXEC(27_hosigata_test)
{		/* ���^��`���� */
//	if ((64*8) < src_boss->boss_time_out)	{;}
	static /*const*/ u32 codebase_exec[50] =
	{
	// (01) VR08 = (VR10_BOSS_SPELL_TIMER & 0x0f);
	MCODE(OP0x1d_ANDM_PD, 0x0f, R08, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (02) if (0 != VR08)		{goto aaa+7}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+7)),
	// (--) VR0e_my_angle65536 += (int)(1024*2/5);
	// (03) VR0e_my_angle65536 += (int)(65536*2/5);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0e, R0e),/*(�����O�������A�h���b�V���O��p����)*/
	((int)(65536*2/5)),
	// (--) mask1024(VR0e_my_angle65536);
	//------------------
	// (04) VR11 = t256(4.0);// #define HGT_DOLL_SPEED10		(4)/*8*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(4.00)),
	// (05) VR13 = (VR0e_my_angle65536/*<<6*/);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (06) CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
//	MCODE(OP0x10_SINCOS256, NAX, R06, R07),
	// (--) VR0d_hosi_vy256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	// (--) VR0c_hosi_vx256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	MCODE(OP0x10_SINCOS256, NAX, R0d, R0c),
	//------------------
	// (07) goto ggg+38:
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+38)),
//aaa+7:
	/* CCW�̏ꍇ */
//	bullet_crate_sakuya_hosi_gata(/*&hosi_position_obj*/);
//	static void bullet_crate_sakuya_hosi_gata(void/*OBJ *src*/)
	// (08) VR06		= VR0a_hosi_set_position_cx256;/*(���e�ʒu ���Wx)*/
	MCODE(OP0x01_MOVER_PD, NAX, R06, R0a),
	// (09) VR07		= VR0b_hosi_set_position_cy256;/*(���e�ʒu ���Wy)*/
	MCODE(OP0x01_MOVER_PD, NAX, R07, R0b),
	// (10) VR08 		= cg_VR20_game_difficulty & 0x02;
	MCODE(OP0x1d_ANDM_PD, 0x02, R08, R20_PLAYER_DATA_game_difficulty),/*(�V���[�g�������A�h���b�V���O)*/
	// (11) if (0 != VR08)	{goto bbb+2;}//	if (1 < cg_VR20_game_difficulty)
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+2)),
	// (12) VR11 = VR0b_hosi_set_position_cy256;/*(easy normal)*/
	MCODE(OP0x01_MOVER_PD, NAX, R11, R0b),
	// (13) goto ccc+1;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+1)),
//bbb+2:
	// (14) VR11 = VR0a_hosi_set_position_cx256;		/*(hard luna)*/
	MCODE(OP0x01_MOVER_PD, NAX, R11, R0a),
//ccc+1:
	// (15) VR08 = (VR11 & 0x0100);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R08, R11),
	(0x0100),
	// (16) if (0 != (VR08))			{goto ddd+14:}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+14)),
	//---------//set_com mon_gin_tama_void();/*(���ʕ���)*/
//	�g�p���W�X�^:	R0e 	src_shot_angle65536 �J�n�n�_
	// (17) HATSUDAN_R11_speed256					= t256(1.0);//t256(1+difficulty)/*(3+difficulty)*/ /*(4+difficulty)*/;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (18) VR12 = ra _nd();
	MCODE(OP0x15_RAND_VALUE, NAX, R12, NAX),
	// (19) VR12 = (VR12 & 0x03);
	MCODE(OP0x1d_ANDM_PD, 0x03, R12, R12),/*(�V���[�g�������A�h���b�V���O)*/
	// (20) HATSUDAN_R12_speed_offset				+= (2);//t256(0.04)/*10*/ ((ra_nd()&0x03)+1);
	MCODE(OP0x01_MOVER_PD, (u8)(+2), R12, R12), /*(�C���f�b�N�X�t)*/
	// (21) VR13 = (VR0e & ((1024)-1));//VR13 = (VR0e & ((65536/4)-1));
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R0e),
	(((1024)-1)),//	(((65536/4)-1)),
	// (22) HATSUDAN_R13_angle65536 				= R13 + (65536/4)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),/*(�����O�������A�h���b�V���O��p����)*/
	((65536/4)+(65536/8)),
	// (23) HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
//	HATSUDAN_R14_tama_spec	|= (TAMA_SPEC_KAITEN_HOUKOU_BIT);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
	// (24) HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* �e�O�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_MINI8_BASE + TAMA_IRO_03_AOI)),
	// (25) goto eee+13:
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+13)),
	//---------//
//ddd+14:
	/* �L����e�ݒ� */
	//local  void set_common_hirogaridan_void(void)
	// (26) HATSUDAN_R11_speed256			= t256(0);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0)),
	/* �������x(��-��������) */
	// (27) VR12 = VR10_BOSS_SPELL_TIMER & (0x3<<2);
	MCODE(OP0x1d_ANDM_PD, (0x3<<2), R12, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (28) VR12 = (VR12 >> (2));
	MCODE(OP0x1e_ASRM_PD, (2), R12, R12),/*(�V���[�g�������A�h���b�V���O)*/
	// (29) VR12 = VR12 + (4);
	MCODE(OP0x01_MOVER_PD, (u8)(+4), R12, R12), /*(�C���f�b�N�X�t)*/
	// (30) HATSUDAN_R12_speed_offset		= (VR12 << (8));	/* �������x(��-��������) */
	MCODE(OP0x1f_ASLM_PD, (8), R12, R12),/*(�V���[�g�������A�h���b�V���O)*/
	// (31) VR13 = (VR10_BOSS_SPELL_TIMER & 0x0f);
	MCODE(OP0x1d_ANDM_PD, 0x0f, R13, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (32) VR13 = (VR13 << (4/*3*/+6));
	MCODE(OP0x1f_ASLM_PD, (4/*3*/+6), R13, R13),/*(�V���[�g�������A�h���b�V���O)*/
//	// (--) VR08 = (VR0e_my_angle65536 << (0/*6*/));
//	MCODE(OP0x1f_ASLM_PD, (0/*6*/), R08, R0e),/*(�V���[�g�������A�h���b�V���O)*/
	// (33) HATSUDAN_R13_angle65536 		= VR13 + (VR0e);
	MCODE(OP0x04_ADDR_PD, NAX, R13, R0e),
	// (34) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
	// (35) HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);	/*�ےe�W(�Ԃq�f�a�Ύቩ��)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_MINI8_BASE + TAMA_IRO_01_AKA)),
	//---------//
//eee+13:
	// (36) (1�e����)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
	//---------//
//ggg+38:
	// ���^�����w �ړ� ����
	// (37)VR0a_hosi_set_position_cx256 += (VR0c_hosi_vx256);/*fps_factor*/
	MCODE(OP0x04_ADDR_PD, NAX, R0a, R0c),
	// (38)VR0b_hosi_set_position_cy256 += (VR0d_hosi_vy256);/*fps_factor*/
	MCODE(OP0x04_ADDR_PD, NAX, R0b, R0d),
	// (39)/*(�I��)*/
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (38));
}

local SPELL_INIT(27_hosigata_test)
{
	static /*const*/ u32 codebase_init[6] =
	{
	// (01)VR09	= (t256(1.0));//[�萔1]�J�̑��x
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R09, NAX),
	(t256(1.0)),
	/* �e�������n�߂�ʒu(���^�`���n�߂�ʒu) */
	/* �q�������w�A�z�u�ʒu */
	// (02)VR0a_hosi_set_position_cx256	= (cg_BOSS_DATA_3a_center_x256);
	MCODE(OP0x01_MOVER_PD, NAX, R0a, R3a_BOSS_DATA_center_x256),
	// (03)VR0b_hosi_set_position_cy256	= (cg_BOSS_DATA_3b_center_y256);
	MCODE(OP0x01_MOVER_PD, NAX, R0b, R3b_BOSS_DATA_center_y256),
	/* ���^��`������ */
	// (--)//	VR0c_hosi_vx256 			= t256(1.0);	/*-t256(0.125)*/ /*t256(1.0)*/
	// (--)//	VR0d_hosi_vy256 			= t256(0.0);	/* t256(2.0)*/ /*t256(0.0)*/
	// (04)VR0e_my_angle65536			= (0);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R0e, NAX),
	(0),
	};
	cpu_exec((u32*)&codebase_init, (4));
}
