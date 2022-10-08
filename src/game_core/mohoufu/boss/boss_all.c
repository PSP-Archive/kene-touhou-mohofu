
#include "boss.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���݃{�X�s���́AC����̃v���O�����ɂȂ��Ă��邯�ǁA
	�����͑��Ĕp�~���āA�e���X�N���v�g�ōs���ł���悤�ɂ������B
	-------------------------------------------------------
	�e���X�N���v�g�ɂ͒e�̈ړ��R�}���h�n�ȊO�ɁA
	�{�X�s���R�}���h�n�𐷂荞�ށB
---------------------------------------------------------*/

/*---------------------------------------------------------
	�� �H���R �P��
	Houraisan Kaguya.
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	�{�X�s���A�� 4�`��
	�΂߈ړ�
	-------------------------------------------------------
	�g�p���W�X�^
	cg_BOSS_DATA_35_move_jyumyou	�J�E���^�B()
	R0e 	�ڕW���W x256
---------------------------------------------------------*/

extern void spell_boss_move_system_12_kaguya_funya_idou(void)
{
	/* �J�[�h�������ĂȂ��ꍇ�ɒǉ� */
	if (SPELL_00==card.spell_used_number)	/* �X�y�������I���Ȃ�J�[�h���� */
	{
		/* �C���ŖڕW�����߂�B */
		VR0e = ((ra_nd() & 0xffff))+(t256(48+32));
	}
	cg_BOSS_DATA_35_move_jyumyou++;
	if (8 < cg_BOSS_DATA_35_move_jyumyou)
	{
		cg_BOSS_DATA_35_move_jyumyou = 0;
		/* �ڕW�ɂ����Â����Ɠw�́B */
		cg_BOSS_DATA_30_target_x256 += ((cg_BOSS_DATA_30_target_x256 < VR0e) ? t256(8) : -t256(8) );
		cg_BOSS_DATA_30_target_x256 &= 0xffff;
	#if (1)
	//------------------
	HATSUDAN_R11_speed256	= t256(64);//(256<<6);
	HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_30_target_x256>>4));
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	cg_BOSS_DATA_31_target_y256 = t256(25) + VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
	#else/*([���e�X�g])*/
	//------------------
	HATSUDAN_R11_speed256	= (t256(1.0));
	HATSUDAN_R13_angle65536 = deg1024to65536((((cg_BOSS_DATA_30_target_x256>>4)/*&(1024-1)*/)));
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	cg_BOSS_DATA_31_target_y256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	cg_BOSS_DATA_31_target_y256 <<= (6);
	cg_BOSS_DATA_31_target_y256 += t256(25);
	//------------------
	#endif
		boss_set_new_position_from_target();/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
	}
}


/*---------------------------------------------------------
	�{�X�s���A�� 1�`��
	���㉺�ړ�
	-------------------------------------------------------
	�g�p���W�X�^
	cg_BOSS_DATA_35_move_jyumyou	�J�E���^�B()
---------------------------------------------------------*/

extern void spell_boss_move_system_11_kaguya_yureru(void)
{
	cg_BOSS_DATA_35_move_jyumyou += (10);
//	mask1024(cg_BOSS_DATA_35_move_jyumyou);
	//------------------
	HATSUDAN_R11_speed256	= (t256(4));
	HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_35_move_jyumyou));
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	cg_BOSS_DATA_3b_center_y256 = t256(25) + VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
}


/*---------------------------------------------------------
	�� �˖��� ��
	Syameimaru Aya.
	-------------------------------------------------------
	�������̍�����U�����X�y�J�ɂ���B
	-------------------------------------------------------
	�������F�����Ŏv����������2�`�Ԃ̍U���p�^�[�����J�I�X�ɂȂ��Ă��܂����B
	�������F�����ƒ��J�ɍ�蒼�����������������B
	�������F�V��̑��x���Փx���Ƃɕς��Ă݂��B
	-------------------------------------------------------
	�g�p���W�X�^
	cg_BOSS_DATA_35_move_jyumyou	�J�E���^�B()
	R09 	�U���^�C�v(���e���֎󂯓n���p)
	R0a 	��ǂ��e�̎��	aya_atooidan_type
---------------------------------------------------------*/

/* 1�Ȃ̂͐����Â��d�l�B���݂̓V�X�e���� ketm ������ CONTROLLER �͖����B
������ɑ��铌���� ������ CONTROLLER �͍�邩������Ȃ��B
( CONTROLLER ���Ă̂́A�{�X�̎���ӂ�ӂ킵�Ēe�o���A���B) */
#define USE_CONTROLLER (0)

/*---------------------------------------------------------
	�V��p�̑�ʒe(��)�B�����ŉ������ȓ���������B
	-------------------------------------------------------
	�����ځ��������蔻��ł��B
--------------------------------------------------------*/

/*---------------------------------------------------------
	�{�X�s���A�� 5�`��
	�ړ��U���p�^�[��2(�����ړ�)
---------------------------------------------------------*/

/*(SS_TAN_I_JIKAN: need 2^n, 2��n��Ŋ���؂��K�v����)*/
#define SS_TAN_I_JIKAN (4096)
/*
---0
[A]�ޔ����W�ݒ�
---1
[B]�ޔ��s��
---2
[C]�U���ړ�
---3
[D]�U��
---3+220 -> 0 �ցB

*/
/*(���̕�50[pixel])*/
//#define AYA_OBJ_WIDTH50 (50)

/* �o����x���W */
//#define BOSS_XP256		(t256(GAME_WIDTH/2))	/* ���S���W�Ȃ̂� */
#define BOSS_XP256			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH/2))	/* ���S���W�Ȃ̂� */
extern void spell_boss_move_system_13_aya_taifu(void)
{
	cg_BOSS_DATA_35_move_jyumyou++;
	if ((SS_TAN_I_JIKAN*1) > cg_BOSS_DATA_35_move_jyumyou)	/* [A]�ޔ����W�ݒ� */
	{
		cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*1);
	//	cg_BOSS_DATA_30_target_x256 = t256(GAME_X_OFFSET)+t256((GAME_320_WIDTH-AYA_OBJ_WIDTH50)/2);
	//	cg_BOSS_DATA_30_target_x256 = BOSS_XP256;
		cg_BOSS_DATA_31_target_y256 = t256(30.0); /* t256(20.0) */
		/* �ړ����W�����߂� */
		boss_set_new_position_from_target();/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
	}
	if ((SS_TAN_I_JIKAN*2) > cg_BOSS_DATA_35_move_jyumyou)	/* [B]�ޔ��s�� */
	{
	//	ca se SS00: /* �s��:�����ʒu���̎擾->SS02�� */
	//	ca se SS02: /* �s��:�����ʒu�֖߂�->SS03�� */	/* ���Ԃ� */
		/*(�U������[A])*/
		if (t256(31.0) > cg_BOSS_DATA_3b_center_y256)
		{
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*2);
			VR0f_AYA_LINK = AYA_LINK_01_RENDAN; /* �U�� */
		}
	}
	else
	if ((SS_TAN_I_JIKAN*3) > cg_BOSS_DATA_35_move_jyumyou) /* [C]�U���ړ� */
	{
	//	ca se SS03: /* �����ʒu:��e3��->SS02, SS02, SS04 */	/* ���Ԃ� */
		/*(�U������[B])*/
	//	if (/*150*/240+(SS_TAN_I_JIKAN*2) < cg_BOSS_DATA_35_move_jyumyou )	/* ���Ԃ� */
		if (/*150*/24-((cg_VR20_game_difficulty)<<2)+(SS_TAN_I_JIKAN*2) < cg_BOSS_DATA_35_move_jyumyou) /* ���Ԃ� */
		{
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*3);
			VR0f_AYA_LINK = AYA_LINK_03_OODAMA_23;	/* �U�� */
					/*t256(5.0)*/ /* �e�� */		/*�d�l�ύX*/	// t256(/*1.5*/5.0/*5.0*/)
			{	/* (1/3)�̊m���ŕ��򂷂�B */
				VR0a = ((0x00011122u>>(((ra_nd()&(8-1)))<<2))&3);	/* SS02, SS02, SS04 */
			}
			if (0 == VR0a)
			{
				OBJ *zzz_player;
				zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
			//	cg_BOSS_DATA_30_target_x256 = BOSS_XP256; /* �^���փ��[�v */
				cg_BOSS_DATA_30_target_x256 = zzz_player->center.x256;
				cg_BOSS_DATA_31_target_y256 = zzz_player->center.y256;
			//	#define KYORI_AAA (t256(128.0)+((cg_game_di fficulty)<<(8+4/*5*/)))
				#define KYORI_AAA (t256(128.0)+((3)<<(8+4/*5*/)))
				if (cg_BOSS_DATA_31_target_y256 > (signed)KYORI_AAA)
				{
					cg_BOSS_DATA_31_target_y256 = KYORI_AAA;
				}
				#undef KYORI_AAA
			}
			else
			if (1 == VR0a)
			{
				cg_BOSS_DATA_30_target_x256 = t256(GAME_X_OFFSET); /* */
			//	cg_BOSS_DATA_3b_center_y256 += t256(6.0);/*fps_factor*/ /* �悭�킩��Ȃ�(?)*/
				cg_BOSS_DATA_31_target_y256 += t256(6.0);/*fps_factor*/ /* �悭�킩��Ȃ�(?)*/
			}
			else
		//	if (2 == VR0a)
			{
			//	cg_BOSS_DATA_30_target_x256 = t256((GAME_X_OFFSET+GAME_320_WIDTH-AYA_OBJ_WIDTH50)); /* */
				cg_BOSS_DATA_30_target_x256 = t256((GAME_X_OFFSET+GAME_320_WIDTH)); /* */
			//	cg_BOSS_DATA_3b_center_y256 += t256(6.0);/*fps_factor*/ /* �悭�킩��Ȃ�(?)*/
				cg_BOSS_DATA_31_target_y256 += t256(6.0);/*fps_factor*/ /* �悭�킩��Ȃ�(?)*/
			}
		}
	}
	else
//	if (SS02 ==cg_BOSS_DATA_35_move_jyumyou)	/* [D]�U�� */
	{
//-------- ���� [SS02]
//-------- ���� [SS02]
//-------- [�U��A]
//-------- ���� [SS04]
//		//	/* (1/2)�̊m����[�U��A]�֕��򂷂�B */
//		//	if (0==(ra_nd()&(2-1)))
//			/* (1/4)�̊m����[�U��A]�֕��򂷂�B */
//			{
//				/* (1/2)�̊m����[�U��A]�֕��򂵂Ȃ��B */
//			}
//	ca se SS02: /* ���ړ���->SS05�� */
//	ca se SS02: /* �E�ړ���->SS04�� */
//	ca se SS05: /* ��:�ҋ@->SS06�� */
//	ca se SS03: /* ��:�O�� -> SS11 */
//	ca se SS04: /* �v���C���[�ʒu�t�߈ړ��� -> �v���C���[�ʒu�t��:��e3�� -> SS00�� */
//		sakuya_anime00(src);//		sakuya_anime08(src);
		/* aya�̉ғ��͈� */ 	/* ���Ԃ� */
		/*(�U������[C])*/
	//	if (/*150*/220+(SS_TAN_I_JIKAN*3) < cg_BOSS_DATA_35_move_jyumyou )	/* ���Ԃ� */
		if (/*150*/22-((cg_VR20_game_difficulty)<<2)+(SS_TAN_I_JIKAN*3) < cg_BOSS_DATA_35_move_jyumyou) 	/* ���Ԃ� */
		{
		//	cg_BOSS_DATA_35_move_jyumyou++; //	sakuya_wait_state_bbb(src/*, SS06*/);
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*0); /* SS00�� */
			//ca se SS06: /* ��:�E��]�U��->SS00, SS03 */
			{	/* (1/3)�̊m���ŕ��򂷂�B */
				VR0a = ((0x00011122u>>(((ra_nd()&(8-1)))<<2))&3); 	/* SS02, SS02, SS04 */
			}
			if (0 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_02_FUDADAN;	/* �U�� */
				cg_BOSS_DATA_31_target_y256 = t256(GAME_HEIGHT/3); /* */
			}
			else
			#if (1==USE_CONTROLLER)
			if (1 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_03_OODAMA_21;	/* �U�� */
				#if (1==USE_CONTROLLER)
				eee_boss02_sr_add1(src);/* ��:�E��]�U�� */
				eee_boss02_sr_add2(src);/* �E:����]�U�� */
				#endif // (1==USE_CONTROLLER)
			}
			else
			#endif // (1==USE_CONTROLLER)
		//	if (2 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_03_OODAMA_22;	/* �U�� */
			}
		}
	}
	#if 1
	// ��Փx���Ⴂ�ꍇ�ɁA���܂茂���Ȃ��悤�ɏC������B
	if (AYA_LINK_00_NONE != VR0f_AYA_LINK)	/*[�U���^�C�v00: �U�����Ȃ��B]*/
	{
	// 0xfe:1111 1110 /easy.
	// 0xaa:1010 1010 /normal.
	// 0x92:1001 0010 /hard.
	// 0x00:0000 0000 /luna.
		if ((0x0092aafeu >> (((cg_VR20_game_difficulty & 0x03) << 3) + (cg_BOSS_DATA_35_move_jyumyou & 0x07))) & 0x01)
		{
			VR0f_AYA_LINK = AYA_LINK_00_NONE;// '1' �� bit �̏ꍇ�A���̂��~�߂�B
		}
	}
	#endif
}


/*---------------------------------------------------------
	�� �\�Z�� ���
	Izayoi Sakuya.
	-------------------------------------------------------
	ToDo:
	�ړ��ƒe�̏����𕪗����悤�B�łȂ��Ɩ�킩���B
	-------------------------------------------------------
	���w��̖����w�ɂ��ă���
	-------------------------------------------------------
	5�ʒ�-�{�X�ŏo�Ă��鎞�́A�傫��60x60(���Ԃ�64x64obj)���炢�B
	5�ʃ{�X�ŏo�Ă��鎞�́A�傫��125x125(���Ԃ�128x128obj)���炢�B
	�͕핗�͊�{�I�ɏk����75%�Ȃ̂ŁA���w��̖����w��
	48x48[pixel](2�{�g�厞��96x96[pixel])���炢���Ó����ȁH
---------------------------------------------------------*/

/*---------------------------------------------------------
	��10�`��: �ŏI�`��(����2)
---------------------------------------------------------*/

extern void spell_boss_move_system_16_sakuya_nazo_keitai(void)
{
	{
#if (0)/*[r41�Ƃ肠����ToDo: �c��]*/
		if (src->color32 > 0xf9000000)	/*	if (src->alpha > 0xf9) */	/* (src->alpha>0xff) */
		{src->color32 = 0xffffffff;}/*	src->alpha = 0xff;*/
		else /*if (src->alpha<0xff)*/
		{src->color32 += 0x05000000;}/* src->alpha += 0x05;*/
#endif
//
#if (0)/*[r41�Ƃ肠����ToDo: �c��]*/
		#if (0)//
		cg_BOSS_DATA_3a_center_x256 -= ((si n1024((src->tm p_ang leCCW1024))*(t256(0.03)))>>8);/*fps_factor*/		/* CCW�̏ꍇ */
		cg_BOSS_DATA_3b_center_y256 -= ((co s1024((src->tm p_ang leCCW1024))*(t256(0.03)))>>8);/*fps_factor*/
		#else
		{
			int sin_value_t256; 	//	sin_value_t256 = 0;
			int cos_value_t256; 	//	cos_value_t256 = 0;
			int256_sincos1024( (src->tmp_angleCCW1024), &sin_value_t256, &cos_value_t256);
			cg_BOSS_DATA_3a_center_x256 -= ((sin_value_t256*(t256(0.03)))>>8);/*fps_factor*/
			cg_BOSS_DATA_3b_center_y256 -= ((cos_value_t256*(t256(0.03)))>>8);/*fps_factor*/
		}
		#endif
#endif
	}
}


/*---------------------------------------------------------
	���`��: �����u�t�F�X�e�B�o���i�C�t�v �ŏI�`��(����1)
	-------------------------------------------------------
	�g�p���W�X�^
	cg_BOSS_DATA_35_move_jyumyou	�J�E���^�B()
	R0c 	BO SS_DATA_07_sakuya_data_common_wait256
	-------------------------------------------------------
	R0f_SAKUYA_LINK 	[���e�A�����W�X�^]
		0:	�Ȃ��B
		1:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ ryoute_knife); ��� ����i�C�t�J�[�h
		2:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ kurukuru);	  ��� ���邭��i�C�t�J�[�h
	-------------------------------------------------------
	R0e:	��Փx(bullet_create_sakuya_kurukuru:�v���C���[�̎����8�e�z�u����)
---------------------------------------------------------*/
/*
0
	[B] [E] ����i�C�t�ōU��
//2049 ==(1024+1024+1)
81
0
	[A] [D] �������Ȃ�(�ҋ@����)
	[C] [F] �^�񒆂ɗ���܂ňړ�
//2089 ==(1024+10024+1+40)
1024
	[G] [A]�ɖ߂�B

*/
	/* [C] [F] �^�񒆂ɗ���܂ňړ� */
	/* [G] [A]�ɖ߂�B */

extern void spell_boss_move_system_15_sakuya_festival_knife(void)
{
	cg_BOSS_DATA_35_move_jyumyou--;/*fps_factor*/
	if (cg_BOSS_DATA_35_move_jyumyou <= 0)
	{
		cg_BOSS_DATA_35_move_jyumyou	= (300);	/* �ړ����ԁA�Ԋu */
		/* [B] [E] �ҋ@���Ԃ��I������� ����i�C�t�ōU�� */
		{
//++	pd->bo ssmode = B00_NONE/*B01_BA TTLE*/;
		// (r35�ŃJ�[�h�̏ꍇ�̂ݏȗ��\)	VR06	= ((cg_BOSS_DATA_3a_center_x256));
		// (r35�ŃJ�[�h�̏ꍇ�̂ݏȗ��\)	VR07	= ((cg_BOSS_DATA_3b_center_y256));
		// (r35�ŃJ�[�h�̏ꍇ�̂ݏȗ��\)	set_REG_DEST_BOSS_XY(); 	/* �e��x256 y256 ���S���甭�e�B */
			VR04	= (t256(GAME_X_OFFSET+(GAME_320_WIDTH/2))); 		/* �e��x256 */
			VR05	= (t256(30));					/* �e��y256 */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
		/* �ړ����W�����߂� */
			cg_BOSS_DATA_36_sakuya_data_move_angle1024 = (deg65536to1024(HATSUDAN_R13_angle65536)); /* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
			//	[SAKUYA_ANIME_12_HATUDAN_START]
			//	[SAKUYA_ANIME_15_HATUDAN_END]
			VR0f_SAKUYA_LINK = (SAKUYA_LINK_01_RYOUTE_KNIFE);/*[��� ����i�C�t�J�[�h]*/
			if (cg_BOSS_DATA_3b_center_y256 > t256(150))
		//	{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(	210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}	/* CW�̏ꍇ */
		//	{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(360-210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}	/* CCW�̏ꍇ */
			{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(360-210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}
			else
			{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = ((ra_nd()&(1024-1)));}
			#if 1
			/*�O�̈�*/
			mask1024(cg_BOSS_DATA_36_sakuya_data_move_angle1024);
			#endif
			#if (0)//t256(3.0) t256(3.5)
			cg_BOSS_DATA_3a_center_x256 += ((si n1024((cg_BOSS_DATA_36_sakuya_data_move_angle1024))*(t256(3.0)))>>8);/*fps_factor*/ /* CCW�̏ꍇ */
			cg_BOSS_DATA_3b_center_y256 += ((co s1024((cg_BOSS_DATA_36_sakuya_data_move_angle1024))*(t256(3.0)))>>8);/*fps_factor*/
			#else
		//	{
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536( deg1024to65536(cg_BOSS_DATA_36_sakuya_data_move_angle1024), &sin_value_t256, &cos_value_t256);
		//		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 + ((sin_value_t256*(t256(30.0)))>>8);/*fps_factor*/
		//		cg_BOSS_DATA_31_target_y256 = cg_BOSS_DATA_3b_center_y256 + ((cos_value_t256*(t256(30.0)))>>8);/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= (t256(30.0));
			HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_36_sakuya_data_move_angle1024));
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 + VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			cg_BOSS_DATA_31_target_y256 = cg_BOSS_DATA_3b_center_y256 + VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
			#endif
			#if (1)
			/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
			boss_set_new_position_from_target();/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
			#endif
			//
			OBJ *zzz_player;
			zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
			#if 1/*Gu(���S���W)*/
			if ((zzz_player->center.x256 < cg_BOSS_DATA_3a_center_x256 + t256(25)) &&	/* (?)*/
				(zzz_player->center.x256 > cg_BOSS_DATA_3a_center_x256 - t256(25)))
			#endif
			{
				VR0c++;/*fps_factor*/
			}
			if (VR0c > 24)/*(21 r35u1)*/
			{
				VR0c	= 0;
#if (0)/*[r41�Ƃ肠����ToDo: �c��]*/
				{
			//		src->color32			= MAKE32RGBA(0xff, 0xff, 0xff, 0x00);			/*	src->alpha			= 0x00;*/
					src->color32			= MAKE32RGBA(0xff, 0xff, 0xff, 0x80);			/*	src->alpha			= 0x00;*/	/* ������ */
					src->tmp_angleCCW1024	= (0);
				}
#endif
				//	[SAKUYA_ANIME_12_HATUDAN_START]
				//	[SAKUYA_ANIME_15_HATUDAN_END]
				VR0f_SAKUYA_LINK = (SAKUYA_LINK_02_KURU_KURU);/*[��� ���邭��i�C�t�J�[�h]*/
			}
		}
	}
}


/*---------------------------------------------------------
	��02�`��: ��p�u�~�X�f�B���N�V�����v
	-------------------------------------------------------
	�g�p���W�X�^
//	cg_BOSS_DATA_35_move_jyumyou	�J�E���^�B()
//	R09 	BO SS_DATA_07_sakuya_data_common_wait256
---------------------------------------------------------*/

/*
		64		256-64		256-0
	//	�^���փ��[�v
		128 				256-64
	// �Ȃɂ����Ȃ�
		192 				256-128
	// ���]�ړ������Z�b�g
		256 				256-192
	// �Ȃɂ����Ȃ�
		0		256 		256-256
	//	���Α��փ��[�v
-------------------------

256 	�^���փ��[�v

250 	���Α��փ��[�v
*/
/*(�Q�[����ʂ�x���W���S�ʒu)==(���[�̃p�l������)+(�Q�[���̈��ʂ̔���)*/
#define SAKUYA_POINT_X_MID			(t256(GAME_X_OFFSET+(GAME_320_WIDTH/2)))

extern void spell_boss_move_system_28_sakuya_miss_direction(void)
{
	if (/*(256-64)*/(255)/*192+64*/ == VR10_BOSS_SPELL_TIMER) /* ���]�ړ������Z�b�g */
	{
		/* ���`�Ԃł͎g���Ė������痘�p(���p)���� */
		#define cg_BOSS_DATA_37_sakuya_data_sayuu_mode cg_BOSS_DATA_37_sakuya_data_common_wait256
		{	/* ��邳��̗U���|�C���g���W */
			cg_BOSS_DATA_37_sakuya_data_sayuu_mode ^= (2-1);/* ���] */
			if (/*0==*/cg_BOSS_DATA_37_sakuya_data_sayuu_mode & (2-1))
					{cg_BOSS_DATA_30_target_x256 = SAKUYA_POINT_X_MID-(t256(128)); }//96==128*0.75
			else	{cg_BOSS_DATA_30_target_x256 = SAKUYA_POINT_X_MID+(t256(128)); }//
		}
		goto set_new_boss_position;/* �ړ����W�����߂� */
	}
	//
	else
//	if (/*(256-256)*/(59)/*((251+64)-256)*/ == VR10_BOSS_SPELL_TIMER) /* �^���փ��[�v */
//	{
//		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = SAKUYA_POINT_X_MID; /* �^���փ��[�v */
//		goto set_new_boss_position;/* �ړ����W�����߂� */
//	}
//	else
	if (/*(256-256)*/(58)/*((250+64)-256)*/ == VR10_BOSS_SPELL_TIMER) /* ���Α��փ��[�v */
	{
	/*
		 ���Α��̍��W==(���[�̃p�l������)+(�Q�[���̈���)-(���݂̍��W-(���[�̃p�l������));
		 ���Α��̍��W==(���[�̃p�l������)+(���[�̃p�l������)+(�Q�[���̈���)-(���݂̍��W));
	*/
	//	cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256(GAME_X_OFFSET) + ( t256(GAME_320_WIDTH) - ( (cg_BOSS_DATA_3a_center_x256) - t256(GAME_X_OFFSET) ) );	/* ���Α��փ��[�v */
	//	cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256((GAME_X_OFFSET+GAME_X_OFFSET+GAME_320_WIDTH)) - (cg_BOSS_DATA_3a_center_x256); 			/* ���Α��փ��[�v */
		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256((GAME_X_OFFSET+GAME_X_OFFSET+GAME_320_WIDTH)) - (SAKUYA_POINT_X_MID); 			/* ���Α��փ��[�v */
		goto set_new_boss_position;/* �ړ����W�����߂� */
	}
	goto nasi;
set_new_boss_position:
	#if (1)
	/* �ړ����W�����߂� */	/* �U���A�j���[�V���� */
	boss_set_new_position_from_target();/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
	#endif
nasi:
	;
}
//	if (/*(256-256)*/(0) == VR10_BOSS_SPELL_TIMER) /* �^���փ��[�v */
//	if (/*(256-192)*/(64) == VR10_BOSS_SPELL_TIMER) /* �^���փ��[�v */
//	if (/*(256-180)*/(76) == VR10_BOSS_SPELL_TIMER) /* �^���փ��[�v */
