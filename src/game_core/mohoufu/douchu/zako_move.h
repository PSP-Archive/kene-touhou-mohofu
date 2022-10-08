
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�����̃U�R
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"�����w" �֌W
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�����w2"		�����閂���w
	"�����w1"		�΂�܂��U�������w
	-------------------------------------------------------
	�n�`�Ɋ֘A����G
---------------------------------------------------------*/

/* ���Ԑݒ� */

//#define MAHOU_TIME_LIMIT_00_MAX	(0x1ff)
//#define MAHOU_TIME_LIMIT_00_MAX	(0x17f)
#define MAHOU_TIME_LIMIT_00_MAX 	(0x13f)
#define MAHOU_TIME_LIMIT_01_ADJ 	((int)(0x0ff/3))
#define MAHOU_TIME_LIMIT_02_ADJ 	(MAHOU_TIME_LIMIT_00_MAX - MAHOU_TIME_LIMIT_01_ADJ)
#define MAHOU_TIME_LIMIT_03_EPS 	(0x04)

/*---------------------------------------------------------
	�G�U�����Ȃ�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin00)
{
	/* �U�����Ȃ� */
}
/*---------------------------------------------------------
	1:�c�U���̃J�[�h
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin01)
{
	/* �U���J�n�t���[������16�t���[���o�ߌ�� 1�񂾂��U�� */
	if ((MAHOU_TIME_LIMIT_02_ADJ-16) == src->jyumyou)
	{
		zako_shot_supeka(src);
	}
}

/*---------------------------------------------------------
	2:�����_���΂�܂��U��("�����w2")�̃J�[�h
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin02)
{
	if (0 < src->zd04_zako_wait2)
	{
		src->zd02_zako_wait1--; 		/* �΂�܂��Ԋu�J�E���^ */
		if (src->zd02_zako_wait1 <= 0)	/* �΂�܂��Ԋu�J�E���^ */
		{
			src->zd02_zako_wait1 = (8);/*(5) (�v���O�����������Ȃ��Ă镪�x������)*/
			src->zd04_zako_wait2--;
			voice_play_menu(VOICE12_MAGICF_E_SHOT, TRACK03_IVENT_DAN);/*�e�L�g�[*/
			zako_shot_supeka(src);
		}
	}
}


/*---------------------------------------------------------
	3:�����_���΂�܂��U��+���@�_��("�����w1")�̃J�[�h
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin03)
{
	#if 0
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	if (
			(src->center.y256 > zzz_player->center.y256)
	 || 	(src->center.y256 > t256(100))
	)
	{
	//	src->time_out++;/* = ST01;*/
		src->jyumyou								= MAHOU_TIME_LIMIT_01_ADJ;	/* ������ */
		zako_sh//ot_supeka(src, ZAKO_SPEKA_01_mahou_nerai);
	}
	#endif
	{
		src->zd02_zako_wait1--; 		/* �΂�܂��Ԋu�J�E���^ */
		if (src->zd02_zako_wait1 <= 0)	/* �΂�܂��Ԋu�J�E���^ */
		{
			src->zd02_zako_wait1 = (25-((cg_VR20_game_difficulty)*5)); /* �΂�܂��Ԋu�J�E���^ */
			voice_play_menu(VOICE12_MAGICF_E_SHOT, TRACK03_IVENT_DAN);/*�e�L�g�[*/
			/* ���x�� 1.0-4.0�܂ł̗���(�����������ɕ΍�)�ɕύX */
//...		HATSUDAN_R11_speed256						= ((ra_nd()&(1024-1))|(0x100))+t256(1.0);	/* �e�� */
			HATSUDAN_R13_angle65536 					= ((ra_nd()&(65536-1)));					/* �p�x */
			/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
			zako_shot_supeka(src);
		}
	}
}

/*---------------------------------------------------------
	4:�~��U���̃J�[�h(����)
	5:�~��U���̃J�[�h(���E)
	6:�~��U���̃J�[�h(�卶)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin4564)
{
	/* ��Փx�ʂɍU�� */
	//if (0 == (src->jyumyou & 0x07))
	if ((cg_VR20_game_difficulty) >= (src->jyumyou & 0x03))
	{
		zako_shot_supeka(src);
	}
}

/*---------------------------------------------------------
	�G�ړ�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_00_kougeki_mahoujin)
{
	/* �o�� */
	if (MAHOU_TIME_LIMIT_02_ADJ < src->jyumyou)
	{
		src->color32 += 0x03000000; 		/*	src->alpha += 0x03;*/ /*4*/ /*fps_factor*/
	}
	/* �����蔻��A���� */
	else
	if (MAHOU_TIME_LIMIT_02_ADJ == src->jyumyou)
	{
		src->atari_hantei			= /*(�e�L�g�[)*/score(100);/*�X�R�A���p*/	/* �����蔻�肠�� */
		/*(�����ŃX�R�A��ݒ肷��)*/
	}
	/* �U�� */
	else
	if (MAHOU_TIME_LIMIT_01_ADJ < src->jyumyou)
	{
	//	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
		/* (�����w�̍U��)�J�[�h�I�� */
		void (*aaa[8])(OBJ/**/ *src) =
		{
			/*(00)0*/attack_kougeki_mahoujin00, 	/* �U�����Ȃ� */
			/*(01)-*/attack_kougeki_mahoujin00, 	/* �U�����Ȃ� */
			/*(02)1*/attack_kougeki_mahoujin01, 	/* �c�e */
			/*(03)2*/attack_kougeki_mahoujin02, 	/* �΂�܂� #01(�������A��"�����w2") */
			/*(04)3*/attack_kougeki_mahoujin03, 	/* �΂�܂� #02(�������A��"�����w1") */
			/*(05)4*/attack_kougeki_mahoujin4564,	/* 8way�Ԓe(��) */
			/*(06)5*/attack_kougeki_mahoujin4564,	/* 8way�Ԓe(��) */
			/*(07)-*/attack_kougeki_mahoujin4564,	/* 8way�Ԓe(��) */
		};
		(*aaa[(int)((src->zd05_kougeki_type) & 0x07)])(src);	/* �e�֐��ɕ��򂷂� */
	//	(*aaa[(int)((src->center.x256) & 0x07)])(src);	/* �e�֐��ɕ��򂷂� */
	}
	/* �����蔻��A�Ȃ� */
	else
	if (MAHOU_TIME_LIMIT_01_ADJ == src->jyumyou)
	{
		src->atari_hantei			= (ATARI_HANTEI_OFF/*�X�R�A���p*/); 	/* �����蔻�薳�� */
		/*(�����蔻�薳��==�X�R�A�͖���)*/
	}
	/* ������ */
	else
	if (MAHOU_TIME_LIMIT_03_EPS < src->jyumyou) 	/*	if (0x04 0x00 > (u32)(src->alpha))*/
	{
		src->color32 -= 0x03000000; 	/*	src->alpha += 0x03;*/ /*4*/ /*fps_factor*/
	}
	/* �����܂� */
	else
	{
	//	src->color32 = 0x00ffffff;		/*	src->alpha = 0x00;*/
		src->jyumyou = JYUMYOU_NASI;
	}
	/* �A�j�� (�h���) */
//	{
//		int sin_value_t256; 		//	sin_value_t256 = 0;
//		int cos_value_t256; 		//	cos_value_t256 = 0;
//		int256_sin cos65536((src->jyumyou<<(5+6)), &sin_value_t256, &cos_value_t256);
//	//	src->center.y256 = src->zd03_start_y256 + ((cos1024(((src->jyumyou<<5)&(1024-1))))<<2);
//		src->center.y256 = src->zd03_start_y256 + ((sin_value_t256)<<2);
//	}
	//------------------
	HATSUDAN_R11_speed256	= (t256(4.0));
	HATSUDAN_R13_angle65536 = (src->jyumyou<<(5+6));
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	src->center.y256 = src->zd03_start_y256 + VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
//	src->rotationCCW1024++;
//	mask1024(src->rotationCCW1024);
}

/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/
/* �΂�܂��U�������w */	/* "�����w1" "GROUNDER", */
/* �����閂���w */	/* "�����w2" "MAGICF", */
//static GAME_COMMAND_OBJ_FUNC(regist_zako_000_mahoujin12)// MAHOUJIN A
//static GAME_COMMAND_OBJ_FUNC(regist_zako_001_mahoujin2)// MAHOUJIN B

static GAME_COMMAND_OBJ_FUNC(regist_zako_000_mahoujin)
{
//	gcmd_obj->m_Hit256R 			= ZAKO_ATARI04_PNG;/* �����蔻��T�C�Y��ς��� */
	gcmd_obj->m_Hit256R 			= ZAKO_ATARI16_PNG;
	//
	gcmd_obj->atari_hantei	= (ATARI_HANTEI_OFF/*�X�R�A���p*/); 	/* �����蔻�薳�� */
	/*(�����蔻��==�l���X�R�A)*/
	/* KETM�̑��΍��W�w��͔p�~�B��ʍ��W�w��ɂ��� */
//	gcmd_obj->center.x256				= (((short)gcmd->user_locate_x)<<8)|(((char)gcmd->user_kougeki_type) & 0x07);/* ��������C���^�[���[�u */
	gcmd_obj->center.x256				= (((short)gcmd->user_locate_x)<<8);
	gcmd_obj->zd03_start_y256			= (((short)gcmd->user_locate_y)<<8);
	//
	gcmd_obj->jyumyou					= MAHOU_TIME_LIMIT_00_MAX;/* SS00 �܂��� ST00 */
	//
	gcmd_obj->zd02_zako_wait1			= (10);
	gcmd_obj->zd04_zako_wait2			= (5);		/* �ő�܉� */
	gcmd_obj->color32					= 0x00ffffff;	/*	gcmd_obj->alpha 			= 0x02 0x00;*/
}


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"�L�X��" �֌W(���􂷂�̂ŁADAT�Ƃ̊֘A���Ȃ�)
---------------------------------------------------------*/

/*---------------------------------------------------------
		"�L�X��", "�Ԗы�1",		"MINE",
	-------------------------------------------------------
	���邮�邻�̏�œ����Ȃ��ŁA��]�A�j�����Ă�
	�ق��Ƃ���8�ɕ��􂵂�
	�Ō�ɍ����e�����ė�����(��)
	-------------------------------------------------------
	���̃L�����̂ݕ��􂷂�񂾂��ǁA�V�X�e���Ƃ���
	����̓T�|�[�g���Ȃ��Ȃ邩������Ȃ�(?)�B
	���̏ꍇ�͎n�߂���A8�d�Ȃ��ďo�Ă���B
	����́A�܂�A���X�e������T�|�[�g�����Ƃ�����A
	�ŏI�I�ȃA���X�e�̎d�g��(�܂��m�肵�Ă��Ȃ�)�Ɠ����d�g�݂ɂȂ�Ǝv���B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�G�ړ�(�����)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kisume_2nd)
{
	if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* ���̃��C����艺����͓G�������Ȃ� */
	{
		/*
		0  0/100   0/65536
		1  1/90  728/65536
		2  1/80  819/65536
		3  1/70  936/65536
		*/
	//	static const u16 kakuritu_tbl[4] =
	//	{ 0, 728, 819, 936 };
	//	if (kakuritu_tbl[((cg_VR20_game_difficulty))/*(teki_rank)*/] > (r a_nd()&(65536-1)))
		if (0==(src->center.x256 & 0x0f))
		{
			zako_shot_supeka(src);
		}
	}
/* CCW�̏ꍇ */
	src->center.x256 += (src->math_vector.x256);/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	/* �A�j���[�V���� */
	src->zako_anime_rotate_angle65536 = ( 16<<6);/*(20<<6)*/
	zako_anime_type04(src); 	/* �O����] */
}


/*---------------------------------------------------------
	�G��ǉ�����(�ϐg)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(add_local_kisume_2nd)
{
	int i;
	for (i=0; i<8; i++)/*����*/
	{
		OBJ *h;
		h						= obj_regist_teki();
		if (NULL!=h)/* �o�^�ł����ꍇ�̂� */
		{
			h->center.x256			= src->center.x256; 	/* �����O�����̂܂܈����p�� */
			h->center.y256			= src->center.y256; 	/* �����O�����̂܂܈����p�� */
			h->obj_type_set 		= src->obj_type_set;	/* �����O�����̂܂܈����p�� */
			h->base_score			= src->base_score;		/* �����������ق����X�R�A���҂��� */	/* �����O�����̂܂܈����p�� */
			h->zako_hp				= src->zako_hp; 		/* �����O�̗̑͂����̂܂܈����p��(���炵�Ă���΂��̕���炩��) */
			//
			h->m_Hit256R			= ZAKO_ATARI16_PNG;
			h->callback_mover		= move_kisume_2nd;
			h->callback_loser		= src->callback_loser;	/* �����O�����̂܂܈����p�� */
			h->callback_hit_teki	= callback_hit_zako;	/* �u�U�R�Ɏ��e�����������ꍇ�̏����v�ɁA�W���̏�����ݒ� */
			//
			{
				const int data_zzz_angle1024				= (i<<7);	/* ����p�x */	//	(/*360*/1024/8)*i;
			//	const int data_zzz_speed256 				= (t256(1.5)+((cg_game_di fficulty)<<6));	/* �������x */	/*(3.0)*/
				const int data_zzz_speed256 				= (t256(1.5)+((3)<<6)); 	/* �������x */	/*(3.0)*/
				//------------------
				HATSUDAN_R11_speed256	= (data_zzz_speed256);
				HATSUDAN_R13_angle65536 = deg1024to65536(data_zzz_angle1024);
				CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
				h->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
				h->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
				//------------------
			}
		}
	}
}

/*---------------------------------------------------------
	�G�ړ�(�{��)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_05_kisume_1st)
{
	if (2 == src->jyumyou)	/* ���� */
	{
		add_local_kisume_2nd(src);/* �ϐg ���� */	/*, data->teki_rank*/
		src->jyumyou = JYUMYOU_NASI;		/* �{�̂͂����܂� */
	}
	else
	if (31+2 > src->jyumyou)
	{
//		src->zako_anime_rotate_angle65536 = (  0);	/* �~�܂� */
	}
	else
	{
										/* �ړ� move */
		src->center.x256 += (src->math_vector.x256);	/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);	/*fps_factor*/
//		src->zako_anime_rotate_angle65536 = ( 10<<6);	/* �O����] */
	}
	/* �A�j���[�V���� */
// �O����]���Ȃ������C���p�N�g������B zako_anime_type04(src); 	/* �O����] */
}



// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	"���̑���ʃU�R" �֌W
---------------------------------------------------------*/

/*---------------------------------------------------------
	�G�ړ�
---------------------------------------------------------*/


/*---------------------------------------------------------
		"�ы�1",	"BADGUY",
	-------------------------------------------------------
	�{�Ɩы�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(my_nerai)
{
	VR04	= (src->zd00_target_x256);						/* �e��x256 */
	VR05	= (src->zd01_target_y256-t256(64)/*+(20)*/);	/* �e��y256 */
	set_REG_DEST_XY(src);
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//------------------
	HATSUDAN_R11_speed256	= (t256(1.0));
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	src->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
}

static OBJ_CALL_FUNC(move_zako_10_hai_kedama)
{
	if (JYUMYOU_ZAKO_HASSEI -128/*-64-64*/ > src->jyumyou)/* �ޏ� */
	{
		my_nerai(src);
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -64 > src->jyumyou)/* */
	{
		if (0==(src->jyumyou & 0x0f))
		{
			if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* ���̃��C����艺����͓G�������Ȃ� */
			{
				zako_shot_supeka(src);
			}
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou) /* �o�ꂷ�� */
	{
		my_nerai(src);
		{
			if (// (src->center.x256 >= www_ppp_center_x256) ||
				(src->center.y256 > t256(GAME_HEIGHT/2) ) /*(480-80)*/ /*(272-32)*/
			 )
			{
				src->math_vector.y256 = (-src->math_vector.y256);
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -64-1);
				/* ���ڕW�́A */
				src->zd00_target_x256		= t256(((480-128)/2));	// t256(-100)
				src->zd01_target_y256		= t256(0);/*((www_ppp_center_y256)&(128-1))*/
				src->zd02_system_speed256	= t256(2.5/*5.0*/);/*fps_factor*/	/*6*/
			}
		}
	}
	/* �ړ����� */
	src->center.x256 += (((src->math_vector.x256)*(src->zd02_system_speed256))>>8);
	src->center.y256 += (((src->math_vector.y256)*(src->zd02_system_speed256))>>8);
	/* �A�j���[�V���� */
	zako_anime_type04(src); 	/* �O����] */
}

/*---------------------------------------------------------
		"�ы�2",	"BADGUY",	(r27����V�K�ǉ�)
	-------------------------------------------------------
	�{�Ɩы�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_11_siro_kedama)
{
	if (JYUMYOU_ZAKO_HASSEI -256-64 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -256 > src->jyumyou)	/* �U�� */
	{
		zako_shot_supeka(src);
	}
	else
	{
		/* �΂�΂�ɓo�ꂳ���� */
		if (
			(0 >= src->center.x256)
			|| (t256(GAME_WIDTH) < src->center.x256)
			#if (1==USE_X_HOUKOU)
			|| (0 >= src->center.y256)
			|| (t256(GAME_HEIGHT) < src->center.y256)
			#endif
		)
		{
			/*��ʊO*/;
		}
		else
		{
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -256-1); /* �o�ꂷ�� */
		}
	}
	/* �ړ����� */
	src->center.x256 += (src->math_vector.x256);
	src->center.y256 += (src->math_vector.y256);
	/* �A�j���[�V���� */
	zako_anime_type04(src); 	/* �O����] */
}

/*---------------------------------------------------------
	"���ґ�2",		"GREETER",
	-------------------------------------------------------
	�T�@���ɑ�����A�ґ���s���Ă���U�R�G
	-------------------------------------------------------
	ming_greeter
	rwingx_curver(ming)�Ɏ��Ă�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_07_yukari)
{
	/* �U�R��������5[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (JYUMYOU_ZAKO_HASSEI-byou60(5) > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	{
		if (src->center.y256 >= src->zd04_max_y256)
		{
			src->jyumyou = JYUMYOU_ZAKO_HASSEI-byou60(5);	/* 5[�b]�o�ߍς݂ɃZ�b�g�B */
			if (t256(1.5/*2.0*/) < src->zd02_system_speed256)
			{	/* ���� */
				src->zd02_system_speed256 -= t256(0.2);
			//	src->zd02_system_speed256 = t256(2)/*3+difficulty*/;
			}
		//
			VR04		= (t256(GAME_WIDTH/2)); 		/* �e��x256 */
			VR05		= (t256(0));					/* �e��y256 */
			set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
			//------------------
			HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
		//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
			CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
			src->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
			//------------------
		}
		zako_shot_supeka(src);
	}
	/* ���Ă邪������ƈႤ--�ȉ�rwingx.c�Ɠ��� */
	src->center.x256 += (src->math_vector.x256);/* fps_factor */
	src->center.y256 += (src->math_vector.y256);/* fps_factor */
	/* �A�j���[�V���� */
	zako_anime_type04(src); 	/* �O����] */
}


/*---------------------------------------------------------
	"�A�z��1",		"PLASMABALL",
	-------------------------------------------------------
	(��)���ыʁA(601��)�d��
	(4*6)��24�C���o�Ă��邪���܂�Ӗ��̂Ȃ��L����
	-------------------------------------------------------
	�ԉf�˕�(?)�ɕς����B
	���Ȃ�e�L�g�[�B
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_02_inyou_dama)
{
	src->center.x256 += src->math_vector.x256;
	/* ��ʗ��[�ł́A���˕Ԃ� */
	if (
		((t256(GAME_X_OFFSET)) > (src->center.x256) ) ||
		((t256(GAME_WIDTH)) < (src->center.x256) ) )
	{
		src->math_vector.x256 = -src->math_vector.x256;
	}
	/* �ړ������ɍ��킹�ăO����] */
	if (0 < src->math_vector.x256)
			{	src->zako_anime_rotate_angle65536 = ( 24<<6);	}
	else	{	src->zako_anime_rotate_angle65536 = (-24<<6);	}
	/* ������ */
	if ((t256(2.50)) > src->math_vector.y256)	/* �ő�d�͉����x */
	{
		src->math_vector.y256 += (8);	/* �d�͉����x */
	}
	/* */
	src->center.y256 += src->math_vector.y256;
	if ((src->zd01_target_y256) < (src->center.y256))
	{
	//	src->center.y256			= src->zd01_target_y256;
		src->zd01_target_y256		= t256(300);
		src->math_vector.y256		= -src->math_vector.y256;	/* ���˂� */
	}
	/* ��ʉ��܂ŗ�����A�����܂� */
	if (t256(272) < (src->center.y256) )
	{
		src->jyumyou = JYUMYOU_NASI;	/* �����܂� */
	}
	/* �A�j���[�V���� */
	zako_anime_type04(src);
}

/*---------------------------------------------------------
		"�͗d��1",		"CUBE",
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_04_kakomi)
{
	if ((JYUMYOU_ZAKO_HASSEI-295) > src->jyumyou)		/* ���E */
	{
		src->zd02_radius256 += t256(1.2);		/*fps_factor*/	/*2.0*/
		if (src->zd02_radius256 > t256(350.0))
		{
			src->jyumyou = JYUMYOU_NASI;	/* �����܂� */
		}
	}
	else
	{
		src->zd02_radius256 -= t256(1.0);		/*fps_factor*/
	//	if (0==(r a_nd()&(512-1)))			/* 1/512 �̊m���Œe�ł� */
		if (0==(src->center.x256 & 0x0ff))
		{
			zako_shot_supeka(src);
		}
	//	src->tmp_angleCCW1024 -= (2);		/*fps_factor*/ /* deg_360_to_512(3) �������� */
	//	mask1024(src->tmp_angleCCW1024);
		src->tmp_angleCCW65536 -= (2<<6);		/*fps_factor*/ /* deg_360_to_512(3) �������� */
		mask65536(src->tmp_angleCCW65536);
	}
//	zako_move_ty pe11_radius(src);
	src->center.x256 = (src->zd00_target_x256);
	src->center.y256 = (src->zd01_target_y256);
	//
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type03(src);/* �A�j���[�V���� */
}

/*---------------------------------------------------------
		"����1",		"PROBALL",
	-------------------------------------------------------
��	��	 ��
��. ��	/��
�� .�� / ��
��	��/  ��
����++����
   /  .
	-------------------------------------------------------
	�G���X�y�J: �U�����Ȃ�(?)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_03_tatsumaki)
{
	if (JYUMYOU_ZAKO_HASSEI -512-512 > src->jyumyou)/* ���ֈړ� */
	{
		src->center.y256 += t256(1.25);/*fps_factor*/
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -512 > src->jyumyou)/* ��ֈړ� */
	{
		src->center.y256 -= t256(1.125);/*fps_factor*/
		if (0 > src->center.y256)
		{
		//	src->zd02_system_speed256 = (-(src->zd02_system_speed256));/* ���] */
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -512-512-1);
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou)/* ���ֈړ� */
	{
		src->center.y256 += t256(1.0);/*fps_factor*/
		if (t256(GAME_HEIGHT/3/*2*/) < src->center.y256) /*t256(250)*/
		{
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -512-1);
		}
	}
	//
	src->zd02_system_speed256++;	/* t256(0.1) t256(0.2)������ */
	src->zd03_px256 -= (src->zd02_system_speed256);/*fps_factor*/
	if ((0 > src->zd03_px256)||(t256(GAME_WIDTH-10) < src->zd03_px256))
	{
		src->zd02_system_speed256 = (-(src->zd02_system_speed256));/* ���] */
	}
//
	if (0 < (src->zako_anime_rotate_angle65536) )	/* vx_r ��]����(��]��) */
			{src->center.x256	= (src->zd03_px256);}
	else	{src->center.x256	= t256(GAME_WIDTH)-(src->zd03_px256);}
	//
	/* �A�j���[�V���� */
	zako_anime_type04(src);
}


/*---------------------------------------------------------
		"���΂�1",		"DRAGER",
	-------------------------------------------------------
	�ˌ����΂��A(���Ȃ肤��o���A���΂�����Ȃ����������H)
	-------------------------------------------------------
�d�l�F
	�� dat��score���w�肷��B
	�� dat�ő̗͂��w�肷��B
	�� dat�Ŋl���A�C�e�����w�肷��B
	�� dat�ŏo���ʒu x, y ���W���w�肷��B
	�� �G���̑��x�͓�Փx�Ɋ֌W�Ȃ��Œ�B���\���߁B(t256(2.0))
	�� �G���͎��@�_���œˌ����Ă���B(�r���Ō����͕ς��܂���)
	�� ���Ԋu�Œe�������Ă���B(�����|���������L��)
		easy	�����Ȃ��B
		normal	1way�e�B
		hard	3way�e�B
		luna	5way�e�B
	�� �e�̑��x�́A�G���̑��x���x���B���x�͓�Փx�Ɋ֌W�Ȃ��Œ�B(t256(1.25))
	(��ʂɎc��̂ő����|���������L��)
	-------------------------------------------------------
	�܂�t�����[�E�C�U���E�F�C�̋t�o�[�W�����ł��B
	�ƌ���������������₷�����ȁH
---------------------------------------------------------*/

/*---------------------------------------------------------
	"覐�1", "�� �� ��1",		"MING",
	-------------------------------------------------------
�d�l�F
	�� dat��score���w�肷��B
	�� dat�ő̗͂��w�肷��B
	�� dat�Ŋl���A�C�e�����w�肷��B
	�� dat�ŏo���ʒu x, y ���W���w�肷��B

	�P�̂ł΂�΂�ɁA�����Ă���U�R�G
	���@�_���ԒP�e��A�˂��Ă���
	-------------------------------------------------------
	�����ɕK�v���Y�񂾂��A���Ǝ����d�l�̕ґ���s�G�͕K�v�Ȃ��B
	�P���ɗ����Ă���G�ɕύX����B
	-------------------------------------------------------
	10�@�O�p����ɑ�����A�ґ���s���Ă���U�R�G
	ming
	rwingx_curver�Ɏ��Ă�
---------------------------------------------------------*/

/*---------------------------------------------------------
	"�Ζы�1",		"XEV",
	-------------------------------------------------------
	�Ζы�	�P�̂œ˂�����ł���B
	-------------------------------------------------------
		"�Ζы�2",		"CRUSHER",
	-------------------------------------------------------
	[�p�~]�Ζы�	�����ɕ���ŁA�ォ��˂�����ł���B
	-------------------------------------------------------
	���̂͋������s���R�ɒ����I�Ŗʔ����Ȃ��̂ŁA
	�ӂɂ�ӂɂ�ƍ~��Ă���悤�ɕύX�B
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_06_inseki)
{
	/* �U�R��������1[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(1)) > src->jyumyou ))
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	if (0==((src->jyumyou)&0x3f))/* ���Ԋu(�e�L�g�|) */
	{
		if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* ���̃��C����艺����͓G�������Ȃ� */
		{
			if (0!=(cg_VR20_game_difficulty))
			{
				zako_shot_supeka(src);	/*(�d�l��easy�͖���)*/
			}
		}
	}
//
	{
		src->center.x256 += (src->math_vector.x256);/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	}
	/* �A�j���[�V���� */
	{
		if (0==src->zako_anime_rotate_angle65536)
		{
			zako_anime_type02(src);
		}
		else		/* offset�����͉�] */
		{
			zako_anime_type04(src);
		}
	}
}


static OBJ_CALL_FUNC(move_zako_09_midori_kedama)
{
	#if 1
	/* �U�R��������3[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(3)) > src->jyumyou ))
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	/* �U�R�������璚�x3[�b]�o�߂��Ă���΁A���e���� */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(3)+1) > src->jyumyou ))
	{
		zako_shot_supeka(src);
	}
	else
	/* �U�R��������3[�b]�ȓ��́A�ӂɂ�ӂɂ�ړ� */
	{
		//------------------
		HATSUDAN_R11_speed256	= t256(1.0);// (src->zd02_system_speed256);
		HATSUDAN_R13_angle65536 = ((src->center.y256)/*<<8*/);//deg1024to65536((src->tmp_angleCCW1024));
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src->center.x256 += VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//	src->center.y256 += VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
	//	src->center.x256 += (t256(1.5));		/*fps_factor*/
	}
	src->center.y256 += (t256(0.83));	/*fps_factor*/
	#endif
	/* �A�j���[�V���� */
	zako_anime_type04(src); 	/* �O����] */
}


static OBJ_CALL_FUNC(move_zako_08_ao_kedama)
{
	/* �U�R��������5[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if ((JYUMYOU_ZAKO_HASSEI-byou60(5)) > src->jyumyou) 	/* ���E */
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
		src->zd02_system_speed256++;// = t256(3.5/*6*/);
	}
	else
	{
		int www_ppp_center_x256;
		int www_ppp_center_y256;
		www_ppp_center_x256 = ra_nd()&0xffff;/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
		www_ppp_center_y256 = ra_nd()&0xffff;/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
		if ((src->center.x256 >= www_ppp_center_x256)||
			(src->center.y256 > t256(GAME_HEIGHT-48) ) )/*480-80*/
		{
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI-byou60(5));	/* 5[�b]�o�ߍς݂ɃZ�b�g�B */
			src->zd00_target_x256	= t256(-100);
		//	src->zd01_target_y256	= www_ppp_center_y256-t256(48);
			src->zd01_target_y256	= www_ppp_center_y256-t256(48);
			zako_shot_supeka(src);
		}
	}
	VR04	= (src->zd00_target_x256);/* �e��x256 */
	VR05	= (src->zd01_target_y256);/* �e��y256 */
	set_REG_DEST_XY(src);	/* �e��x256 y256 ���S���甭�e�B */
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	#if (1)
	//------------------
	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	src->center.x256 += VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	src->center.y256 += VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	#else
	src->tmp_angleCCW1024	= deg65536to1024((HATSUDAN_R13_angle65536));
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	#endif
	//------------------
	/* �A�j���[�V���� */
	zako_anime_type04(src); 	/* �O����] */
}


/*---------------------------------------------------------
	"���΂�2"(�΂��΂�) 	"���ы�1",		"EYEFO",
	-------------------------------------------------------
	�o�O����H�H�H
---------------------------------------------------------*/
/*static*/extern OBJ_CALL_FUNC(bullet_create_teki_homing);

static OBJ_CALL_FUNC(move_zako_13_obake)
{
//	if (JYUMYOU_ZAKO_HASSEI -1200+0 > src->jyumyou)
//	{
//		src->jyumyou = JYUMYOU_NASI;	/* �����܂� */
//	}
//	else
	/* �U�R��������10[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (JYUMYOU_ZAKO_HASSEI -byou60(10) > src->jyumyou) 	/* ��֋A�� */
	{
		src->zd01_target_y256 -= t256(1.0);/*fps_factor*/
	}
	else
	/* �U�R��������5[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (JYUMYOU_ZAKO_HASSEI -byou60(5) < src->jyumyou)		/* ���֗��� */
	{
	//	if (src->zd01_target_y256 < t256(GAME_HEIGHT))
	//	if (src->zd01_target_y256 < t256(difficulty<<6) )/* ��Փx�ɂ�艺�����Ă���ʒu���Ⴄ�B�ő�192(3*64) */
	//	if (src->zd01_target_y256 < t256((cg_game_di fficulty)<<5) )/* ��Փx�ɂ�艺�����Ă���ʒu���Ⴄ�B�ő�96(3*32) */
		if (src->zd01_target_y256 < t256((3)<<5) )/* ��Փx�ɂ�艺�����Ă���ʒu���Ⴄ�B�ő�96(3*32) */
		{
			src->zd01_target_y256 += t256(1.0);/* fps_factor */
		}
	}
//
	if (0 == src->zd04_kaisu_nnn)
	{
		src->zd02_radius256 += t256(1.0);	/* fps_factor */
		if (src->zd02_radius256 > t256(64.0))/*150*/ /* �ő唼�a */
		{
			src->zd04_kaisu_nnn = (1);
		}
	}
	else
	{
		src->zd02_radius256 -= t256(2.0);	/* fps_factor */	/* 1 */
		if (src->zd02_radius256 < t256(8.0)) /* �ŏ����a */ /* <=10 */
		{
			src->zd04_kaisu_nnn = (0);
		}
	}
//	src->tmp_angleCCW1024 += (2);	/* fps_factor */	/* cv1024r(5) �������� */
//	mask1024(src->tmp_angleCCW1024);
	src->tmp_angleCCW65536 += (2<<6);	/* fps_factor */	/* cv1024r(5) �������� */
	mask65536(src->tmp_angleCCW65536);
	//
	/* ��ʊO�Ȃ�Ό����Ȃ� */
	if (0 < src->center.y256) /* ��ʓ��Ȃ猂�� */
	{
	//	if (0==(r a_nd()&(256-1)))/*(1/256�̊m����) (�e�L�g�[)*/
		if (0==((src->center.x256)&(256-1)))/*(1/256�̊m����) (�e�L�g�[)*/
		{
			bullet_create_teki_homing(src); /* �G���̗U���~�T�C�����쐬���� */
		}
	}

//	zako_move_ty pe11_radius(src);
	src->center.x256 = (src->zd00_target_x256);
	src->center.y256 = (src->zd01_target_y256);
	/*�ȉ�(rwingx.c)�Ɠ���*/
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type02(src);/*(rwingx���ʁA�A�j���[�V����)*/
}

/*---------------------------------------------------------
	"���C�h1",		"RWINGX",	rwingx
	-------------------------------------------------------
	�ォ�牡�ɓ��Ԋu�Ő��񂵂Č���A�v���C���[�Ɍ�����
	������x�߂Â��ƁA�e�u���Ĕ��]���ē�����B
	-------------------------------------------------------
	"���C�h2",		"ZATAK",
	-------------------------------------------------------
	rwingx_zatak (�Ԃ��d��)
	���E���猻��A���@�_���e��ł�����A�^���֒��i���Ă���B
	-------------------------------------------------------
		"���C�h3",		"CURVER",	rwingx_curver
	-------------------------------------------------------
�ォ�猻���S����n��`���ĉ���

����
��
����������
		��
����������
��
����������
		��
����������
	-------------------------------------------------------
	�o�O����B
	-------------------------------------------------------
	"���C�h4",		"CIR",	rwingx_cir
	-------------------------------------------------------
	�E��������c���Ō���A���Ɍ������B���Ő���B
	��������㏸���A�E���Ɍ������B��Ő���B
	�E�����牺�Ɍ������B��ʊO�֑ޏ�B
---------------------------------------------------------*/


/*---------------------------------------------------------
	JYUMYOU_ZAKO_HASSEI
... �Ȃɂ����Ȃ�
	JYUMYOU_ZAKO_HASSEI-byou60(1)
	����
	JYUMYOU_ZAKO_HASSEI-byou60(2)
	����
	JYUMYOU_ZAKO_HASSEI-byou60(2)-1
	�_��
	JYUMYOU_ZAKO_HASSEI-byou60(2)-2
	�H(�������Ȃ��őĐ��Ői��)
	JYUMYOU_ZAKO_HASSEI-byou60(16+2)-1
	�������Ȃ��� �v���C���[�ɓ˂�����ł���
	JYUMYOU_ZAKO_HASSEI-byou60(16+16+2)-1
	��ʊO�Ȃ炨���܂�
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_15_meido1)
{
//	if (JYUMYOU_ZAKO_HASSEI -byou60(16+16+2)-1 > src->jyumyou)
//	{
//		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
//	}
//	else
//	if (JYUMYOU_ZAKO_HASSEI -byou60(16+2)-1 > src->jyumyou)
//	{
//		src->zd02_system_speed256	+= t256(0.1);/*�������Ȃ��� �v���C���[�ɓ˂�����ł���*/
//		if (src->center.y256 >= t256(GAME_HEIGHT-150))
//		{
//			zako_shot_supeka(src);
//		//	src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(16+2)-1-1);
//			src->tmp_angleCCW1024 += (1024/2);	/* (1024/2) == [180/360 �x] ���]���ē����� */
//			mask1024(src->tmp_angleCCW1024);
//		//	src->zd02_system_speed256 = /*t256(6+teki_rank)*/;/*���߂�*/
//		}
//	}
//	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(2)-2 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(2)-1 > src->jyumyou)
	{
		/* �v���C���[�ɓ˂�����ł��� / schnell richtung player */
	//	src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(2)-1-1);
		VR06	= ((src->center.x256));
		VR07	= ((src->center.y256));
	//	cal culate_jikinerai();
	{
	//	OBJ *zzz_player;
	//	zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
		VR04	= t256(32+((480-128-32)/2));// (zzz_player->center.x256);		/*(�_����)*/
		VR05	= t256(200);// ()(zzz_player->center.y256); 	/*(�_����)*/
		#if (0)/*(���d�l����)*/
		VR06	= (dest->center.x256);			/*(�_����)*/
		VR07	= (dest->center.y256);			/*(�_����)*/
		#endif
		// ���d�l����(zzz_player, dest);
		CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	}
	//	src->tmp_angleCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));		/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
		src->tmp_angleCCW65536 = ( (HATSUDAN_R13_angle65536));		/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
	//	src->zd02_system_speed256	= /*t256(3+(teki_rank>>1))*/ /*(4+teki_rank)*/;/* ���߂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-byou60(2) > src->jyumyou)/* 2048+1 */
	{
		if (t256(0.0) < src->zd02_system_speed256)
		{
			src->zd02_system_speed256 -= (5);/*t256(0.1)*/ /*����*/
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-byou60(1) > src->jyumyou)/* 2048+1+60 */
	{
		if (t256(1.0) > src->zd02_system_speed256)
		{
			src->zd02_system_speed256 += (5);/*t256(0.1)*/ /*����*/
		}
	}
//
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type01(src);/*(���C�h���ʁA�A�j���[�V����)*/
}


static OBJ_CALL_FUNC(move_zako_18_meido4)
{
	{
		src->zd03_system_hoson_angle65536 += (10<<6);
		//------------------
		HATSUDAN_R11_speed256	= ((src->zd04_system_hoson_speed256)>>1);
		HATSUDAN_R13_angle65536 = ((src->zd03_system_hoson_angle65536));
		CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
		src->center.x256 += VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		src->center.y256 += VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
		//------------------
	}
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type01(src);/*(���C�h���ʁA�A�j���[�V����)*/
}


static OBJ_CALL_FUNC(move_zako_16_meido2)
{
	if (JYUMYOU_ZAKO_HASSEI -40-512-512-512-512 > src->jyumyou)/* �ޏ� */
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512-512-512 > src->jyumyou)/* �^���ɒ��i */
	{
		src->zd02_system_speed256 += t256(0.2);/*����*/ /*t256(0.3)*/
		if (src->zd02_system_speed256 > t256(2.5)) /*t256(3.0)*/
		{
			src->zd02_system_speed256 = t256(2.5); /* �����ő�l */
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-512-512-1);
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512-512 > src->jyumyou)/* �e���� */
	{
		/* CCW�̏ꍇ */
	//	src->tmp_angleCCW1024					= cv1024r(0);/* �^���Ɍ������Œ� */
		src->tmp_angleCCW65536					= cv65536r(0);/* �^���Ɍ������Œ� */
		//if (data_hari_rank256/*src->le vel*/)
		{
			zako_shot_supeka(src);
		}
		src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-512-1);/* ���� */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512 > src->jyumyou)/* �قڐ^�������� */
	{
		/* CCW�̏ꍇ */
	//	if (src->tmp_angleCCW1024 < cv1024r(180))
		if ((src->tmp_angleCCW65536>>6) < cv1024r(180))/*r42*/
		{
		//	src->tmp_angleCCW1024 -= cv1024r(3);/*fps_factor*/
			src->tmp_angleCCW65536 -= cv65536r(3);/*fps_factor*/
		//	if (src->tmp_angleCCW1024 < cv1024r(0))
			if (src->tmp_angleCCW65536 < cv65536r(0))
			{
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-1);/* ���� */
			}
		}
		else
		{
		//	src->tmp_angleCCW1024 += cv1024r(3);/*fps_factor*/
			src->tmp_angleCCW65536 += cv65536r(3);/*fps_factor*/
		//	if (src->tmp_angleCCW1024 > cv1024r(360))
		//	if (src->tmp_angleCCW65536 > cv65536r(360))/*r42���߂���*/
			if (((src->tmp_angleCCW65536)>>6) > cv1024r(360))/*r42*/
			{
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-1);/* ���� */
			}
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40 > src->jyumyou)/* ��ʍ��E����o�� */
	{
		src->zd02_system_speed256 -= t256(0.02);/*fps_factor*/ /* ���� */
		if (src->zd02_system_speed256 <= 0)/* ���x�������Ȃ� */
		{
			src->zd02_system_speed256 = 0;/* ��~ */
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-1);/* ���� */
		}
	}
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type01(src);/*(���C�h���ʁA�A�j���[�V����)*/
}


static OBJ_CALL_FUNC(move_zako_17_meido3)
{
	if (JYUMYOU_ZAKO_HASSEI -byou60(8+8+8) > src->jyumyou)				// SS03:	/* ��(�΂ߏ�)�ֈړ��� */
	{
		if (0 < src->zd04_kaisu_nnn)
		{
			if (src->center.x256 <= src->zd00_clip_left256)
			{
				src->zd04_kaisu_nnn--;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI-1);/*SS00*/
			}
		}
		else	/* �ޏꒆ */
		{
			gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(8+8) > src->jyumyou)			// SS02:	/* �E����ŉ�]�� */
	{
		src->tmp_angleCCW65536 -= src->zd03_turnspeed65536;/*fps_factor*/	/* CCW�̏ꍇ */
		mask65536(src->tmp_angleCCW65536);
		/* ��(�΂ߏ�)���������� */
	//	if ((512+32) < src->tmp_angleCCW1024)			//cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
		/* CCW�̏ꍇ */
	//	if (0 != (0x200 & src->tmp_angleCCW1024))			/* (cv1024r(180) < src->tmp_angleCCW1024) */
		if (0 != ((0x200<<6) & src->tmp_angleCCW65536)) 		/* (cv1024r(180) < src->tmp_angleCCW1024) */
		{
		//	if ((512+256-32) > src->tmp_angleCCW1024)	//cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
			if (((512+256-32)<<6) > src->tmp_angleCCW65536) //cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
			{
			//	src->tmp_angleCCW1024 = cv1024r(180/*+10*/);
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8+8+8)-1);/*SS03*/
				zako_shot_supeka(src);	/* easy�ȊO�͑_���e������ */
			}
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(8) > src->jyumyou)		// SS01:	/* �E(�΂ߏ�)�ֈړ��� */
	{
		if (0 < src->zd04_kaisu_nnn)
		{
			if (src->center.x256 >= src->zd01_clip_right256)
			{
				src->zd04_kaisu_nnn--;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8+8)-1);/*SS02*/
			}
		}
		else	/* �ޏꒆ */
		{
			gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou) 	// SS00:	/* ������ŉ�]�� */
	{
		src->tmp_angleCCW65536 += src->zd03_turnspeed65536;/*fps_factor*/	/* CCW�̏ꍇ */
		mask65536(src->tmp_angleCCW65536);
		/* �E(�΂ߏ�)���������� */
		/* CW�̏ꍇ */
	//	if ((1024-32) < src->tmp_angleCCW1024)		/*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
		/* CCW�̏ꍇ */
	//	if (0 == (0x200 & src->tmp_angleCCW1024))/* (cv1024r(180) > src->tmp_angleCCW1024) */
		if (0 == ((0x200<<6) & src->tmp_angleCCW65536))/* (cv1024r(180) > src->tmp_angleCCW1024) */
		{
		//	if ((256+32) < src->tmp_angleCCW1024)	/*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
			if (((256+32)<<6) < src->tmp_angleCCW65536) /*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
			{
			//	src->tmp_angleCCW1024 = cv1024r(0/*360*/ /*-10*/)/*cv1024r(360)*/;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8)-1);/*SS01*/
				zako_shot_supeka(src);	/* easy�ȊO�͑_���e������ */
			}
		}
	}
/*���ݎd�l�エ������*/
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type01(src);/*(���C�h���ʁA�A�j���[�V����)*/
}

/*---------------------------------------------------------
		"�d��1",		"FAIRY",
		"�d��4", (�\��)		"FAIRY",	(r27����V�K�ǉ�)
	-------------------------------------------------------
	user_locate_x:	���x256[speed256]
	user_locate_y:	���ʒu[pixel]
	-------------------------------------------------------
		"�d��2",		"SPLASH",
	-------------------------------------------------------
		"�d��3",		"FAIRY",	(r27����V�K�ǉ�)
	-------------------------------------------------------
	user_locate_x:	���x256[speed256]
	user_locate_y:	���ʒu[pixel]
	-------------------------------------------------------
		"�G1",		"", (r27����V�K�ǉ�)
	-------------------------------------------------------
	user_locate_x:	���x256[speed256]
	user_locate_y:	���ʒu[pixel]
---------------------------------------------------------*/


static OBJ_CALL_FUNC(move_ao_yousei1)
{
	/* �U�R��������5[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if (JYUMYOU_ZAKO_HASSEI-byou60(5) > src->jyumyou)	/* ���E */
	{
		src->zd02_system_speed256 += (2);/*(2+1)*/
	//	src->tmp_angleCCW1024 += (4);
		src->tmp_angleCCW65536 += (4<<6);
	//	if (511 < src->tmp_angleCCW1024)
	//	{
	//		src->tmp_angleCCW1024 = (511);/*�^��*/
	//	}
		if ((511<<6) < src->tmp_angleCCW65536)
		{
		//	src->tmp_angleCCW1024 = (511);/*�^��*/
			src->tmp_angleCCW65536 = (511<<6);/*�^��*/
		}
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else	/* �U�� */
	{
		/* �U�R��������4.5[�b]�o�߂����ꍇ�ɁA�U�� */
	//	if ((JYUMYOU_ZAKO_HASSEI-byou60(4.5) )==src->jyumyou)
	//	{
	//		if (0!=(cg_VR20_game_difficulty))
	//		{
	//			zako_shot_supeka(src);
	//		}
	//	}
//		ca se 0x40: /*not_break;*/	/*0x40==064 0x46==070*/
//		ca se 0x80: /*not_break;*/	/*0x80==128 0x78==120*/
//		ca se 0xa0: /*not_break;*/	/*0x  ==170 0xaa==170*/
//		ca se 0xc0: 				/*0x  ==220 0xdc==220*/
		if (0x00==(src->jyumyou&(0x1f)))/* 8�� */
		{
			if (0!=(cg_VR20_game_difficulty))
			{
				zako_shot_supeka(src);
			}
		}
		src->zd02_system_speed256 -= (5/*5*/);
		if (0 >= src->zd02_system_speed256)
		{
			src->zd02_system_speed256 = 1;
		}
	}
	/*�ȉ�(rwingx.c)�Ɠ���*/
	zako_system_move_vector(src);/*(�U�R�V�X�e���W���ړ�����)*/
	zako_anime_type02(src);/*(rwingx���ʁA�A�j���[�V����)*/
}


static OBJ_CALL_FUNC(move_zako_12_ao_yousei)
{
	if (JYUMYOU_ZAKO_HASSEI-60 > src->jyumyou)	/* �ޏ�̓��� */
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
		src->center.x256 -= src->math_vector.x256;/*fps_factor*/
		src->center.y256 -= src->math_vector.y256;/*fps_factor*/
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-59 > src->jyumyou)	/* �e������ */
	{
		zako_shot_supeka(src);
		src->zd04_kaisu_nnn--;
		if (0 > src->zd04_kaisu_nnn)
		{
			;/* �ޏꏀ�� */
		}
		else
		{
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -50);/*�߂�*/
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-49 > src->jyumyou)	/* �����҂� */
	{
//		VR06	= ((src->center.x256));
//		VR07	= ((src->center.y256));
//	//	cal culate_jikinerai();
//	{
//		#if (0)/*(���d�l����)*/
//		VR06	= (dest->center.x256);			/*(�_����)*/
//		VR07	= (dest->center.y256);			/*(�_����)*/
//		#endif
//		// ���d�l����
//		 (calculate_jiki_nerai);/* ���@�_���p�쐬 */
//	}
	//	src->tmp_angleCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));		/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
	//	mask1024(src->tmp_angleCCW1024);
		src->tmp_angleCCW65536 = ( (HATSUDAN_R13_angle65536));		/* �u1����65536�����v����u1����1024�����v�֕ϊ�����B */
		mask65536(src->tmp_angleCCW65536);
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI+1-10 > src->jyumyou)	/* �o��̓��� */
	{
		src->center.x256 += src->math_vector.x256;/*fps_factor*/
		src->center.y256 += src->math_vector.y256;/*fps_factor*/
	}
	/* �A�j���[�V���� */
	zako_anime_type01(src);
}


static OBJ_CALL_FUNC(move_zako_14_karasu)
{
	/* �U�R��������5[�b]�ȏ�o�߂��Ă���΁A�`�F�b�N */
	if ((JYUMYOU_ZAKO_HASSEI-/*320*/(5*60)/*512*/) > src->jyumyou)	/* ���E */
	{
		gamen_gai_nara_zako_osimai(src);/* ��ʊO�Ȃ炨���܂� */
	}
	else
	{
		/* �U�� */
		if (0 == ((src->jyumyou) & 0x3f))
		{
			if (cg_VR20_game_difficulty)
			{
				zako_shot_supeka(src);
			}
		}
	}
	/* �ړ����� */
	src->center.x256 += (src->math_vector.x256);/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	/* �A�j���[�V���� */
	zako_anime_type02(src);
}


// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�U�R�G��ǉ�����
---------------------------------------------------------*/

static GAME_COMMAND_OBJ_FUNC(regist_zako_12_ao_yousei)
{
	/* �o��̓��� / �ޏ�̓��� */
		 if (t256(64)			 > gcmd_obj->center.x256)	{gcmd_obj->math_vector.x256 =	t256(2.0);	}	/* �o���ʒu�����Ȃ�A�E�ֈړ� */
	else if (t256(GAME_WIDTH-64) < gcmd_obj->center.x256)	{;} 					/* ���S�t�߂Ȃ獶�E�Ɉړ����Ȃ� */
	else													{gcmd_obj->math_vector.x256 = -t256(2.0);	}	/* �o���ʒu���E�Ȃ�A���ֈړ� */

	gcmd_obj->math_vector.y256 = (0);

	#if 1// (1==USE_X_HOUKOU)
	if (0 > (gcmd_obj->center.y256))
	{
		/* y���W���������̏ꍇ�́Ax���W�w��Ȃ̂�(x���W y���W ���t�ɂ���) */
		{
			int s_sss;
			s_sss					=  (gcmd_obj->center.x256);
			gcmd_obj->center.x256	= -(gcmd_obj->center.y256);
			gcmd_obj->center.y256	= s_sss;
		}
		gcmd_obj->math_vector.y256	= (gcmd_obj->math_vector.x256);
		gcmd_obj->math_vector.x256	= (0);
	}
	#endif
	gcmd_obj->zd04_kaisu_nnn		= (3);	/* 3�񌂂� */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_11_siro_kedama)
{
	gcmd_obj->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/* �����ۂ� */
	//
	gcmd_obj->center.y256			= ((gcmd->user_locate_y)<<8);
	gcmd_obj->math_vector.x256		= ((gcmd->user_locate_x));
	gcmd_obj->math_vector.y256		= (0);
	//
	{
		if (0 < (gcmd_obj->math_vector.x256))
		{/* [���� user_locate_y ���������̏ꍇ�A�E�ֈړ�(��)] [����y���������̏ꍇ�A���ֈړ�(��)] */
			gcmd_obj->center.x256	= t256(-30)/*-(i<<(5+8))*/;
		}
		else
		{/* [���� user_locate_y ���������̏ꍇ�A���ֈړ�(��)] [����y���������̏ꍇ�A��ֈړ�(��)] */
			gcmd_obj->center.x256	= t256(360)/*+(i<<(5+8))*/;/* 360 > 352(x_max) > 272(y_max) */
		}
	}
	//
	if (0 > (gcmd_obj->center.y256))
	{
		/* y���W���������̏ꍇ�́Ax���W�w��Ȃ̂�(x���W y���W ���t�ɂ���) */
		{
			int s_sss;
			s_sss					= gcmd_obj->center.x256;
			gcmd_obj->center.x256	= -(gcmd_obj->center.y256);
			gcmd_obj->center.y256	= s_sss;
		}
		gcmd_obj->math_vector.y256	= (gcmd_obj->math_vector.x256);
		gcmd_obj->math_vector.x256	= (0);
	}
	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* ��]�A�j�� */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_14_karasu)
{
//	gcmd_obj->center.y256				= ((gcmd->us er_loc ate_y)<<8);
//	gcmd_obj->math_vector.x256			= ((gcmd->us er_loc ate_x));
//	game_command_regist_zako_999_karasu_common( l, h);
//	if (512 > gcmd_obj->tmp_angleCCW1024)
	if ((512<<6) > gcmd_obj->tmp_angleCCW65536)
	{/* [�p�x�� 0 ...511 �̏ꍇ�A�E�ֈړ�(��)] [����y���������̏ꍇ�A���ֈړ�(��)] */
		gcmd_obj->zd04_KARASU3_houkou		= ((0x30)>>2);/*�E�����J���X*/
	}
	else
	{/* [�p�x�� 512 ...1023 �̏ꍇ�A���ֈړ�(��)] [����y���������̏ꍇ�A��ֈړ�(��)] */
		gcmd_obj->zd04_KARASU3_houkou		= ((0x50)>>2);/*�������J���X*/
	}
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_05_kisume)
{
//	/* �����ʒu */
	/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
	VR04	= ((ra_nd()&((256*256)-1)))+t256(64);/*320?*/ /*t256(ra_nd()%270)+t256(50)*/	/* �e��x256 */
	VR05	= ((ra_nd()&((256*128)-1)))+t256(16);/*350?*/ /*t256(ra_nd()%300)+t256(50)*/	/* �e��y256 (256*256) */
	set_REG_DEST_XY(gcmd_obj);
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//------------------
//384	src->zd02_system_speed256	= (t256(1.5));
//	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(�j�󃌃W�X�^�����̂Œ���)*/
	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//------------------
//
	gcmd_obj->jyumyou				= (80)+byou60(1)+(2);
// �O����]���Ȃ������C���p�N�g������B
	gcmd_obj->zako_anime_rotate_angle65536 = (0);	/* ��]�A�j�� */
//�d��	gcmd_obj->rotationCCW65536 = (0);
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_10_hai_kedama)
//static GAME_COMMAND_OBJ_FUNC(regist_zako_010_kedama1)
{
	gcmd_obj->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/*�����ۂ� */
	{
		/* ���ڕW�̓v���C���[�̂����ʒu */
		int www_ppp_center_x256;
		int www_ppp_center_y256;
		www_ppp_center_x256 			= ra_nd()&0xffff;/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
		www_ppp_center_y256 			= ra_nd()&0xffff;/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
		gcmd_obj->zd00_target_x256		= (www_ppp_center_x256);
		gcmd_obj->zd01_target_y256		= (www_ppp_center_y256);
	//	gcmd_obj->zd01_target_y256		= ((www_ppp_center_y256)>>1);	/* ���U�֎~ */
	}
	gcmd_obj->math_vector.x256			= (0);
	gcmd_obj->math_vector.y256			= (0);
//	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* ��]�A�j�� */
//	gcmd_obj->zako_anime_rotate_angle65536 = (5<<6);	/* ��]�A�j��(5) */
	gcmd_obj->zako_anime_rotate_angle65536 = (7<<6);	/* ��]�A�j�� */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_07_yukari)
{
//	s_jikinerai_sincos(h);
	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* ��]�A�j�� */
	gcmd_obj->zd04_max_y256 		= (t256(GAME_HEIGHT)-t256(60));
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_13_obake)
{
	/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
//	gcmd_obj->tmp_angleCCW1024		= (ra_nd()&(1024-1));
	gcmd_obj->tmp_angleCCW65536 	= (ra_nd()&(65536-1));
	gcmd_obj->zd00_target_x256		= t256( 62) + ((ra_nd()&((256*256)-1)));/*t256*/  /*(GAME_WIDTH/2)*/ /* GAME_WIDTH 380 ~= 380 == 62+256+62 */
	gcmd_obj->zd01_target_y256		= t256(-32);/*(-100)*/
	gcmd_obj->zd02_radius256		= t256(10);
	gcmd_obj->zd04_kaisu_nnn		= (0);/*(�t���O)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_02_inyou_dama)
{
	gcmd_obj->callback_loser		= item_create_002_inyou_zako;
	gcmd_obj->zd01_target_y256		= (t256(128)-((/*yyy*/(gcmd->user_kougeki_type)&0x0f)<<(5+8))); /* ���z�n�� / 臒l */
	gcmd_obj->math_vector.x256		= (ra_nd()&0x1ff);/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
	gcmd_obj->math_vector.y256		= (ra_nd()&0x1ff);/*(��{�I�ɎG���ł�ra_nd()�g�p�֎~)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_04_kakomi)
{
	#if 0
	gcmd_obj->zd02_radius256		= t256(350);
	gcmd_obj->tmp_angleCCW1024		= (gcmd->user_locate_x);/*(�p�x[deg1024])*/
	gcmd_obj->zd00_target_x256		= t256(GAME_WIDTH/2);/* GAME_WIDTH 380 ~= 380 == 62+256+62 */
	gcmd_obj->zd01_target_y256		= t256(GAME_HEIGHT/2);
	#endif
//
	gcmd_obj->zd00_target_x256		= (gcmd_obj->center.x256);/*(���S�ʒu)*/
	gcmd_obj->zd01_target_y256		= (gcmd_obj->center.y256);/*(���S�ʒu)*/
	gcmd_obj->zd02_radius256		= /*t256(350);*/((gcmd_obj->zd02_system_speed256)<<8);/*(�������a)*/	/*([r39��O]�Ƃ肠����)*/
//	gcmd_obj->tmp_angleCCW1024		= (gcmd_obj->tmp_angleCCW1024);/*(�p�x[deg1024])*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_03_tatsumaki)
{
//	src->zako_anime_rotate_angle1024	= (src->tmp_angleCCW1024); /* vx_r ��]����(��]��) */
//	src->zako_anime_rotate_angle1024	= (src->zako_anime_rotate_angle1024);	/* vx_r ��]����(��]��) */
	gcmd_obj->zd03_px256				= t256(GAME_WIDTH-10);	/*0*/	/*t256(GAME_WIDTH/2)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_17_meido3)
{
	gcmd_obj->zd03_turnspeed65536		= ((7*2)<<6);
	gcmd_obj->zd04_kaisu_nnn			= (4);
//
	gcmd_obj->zd00_clip_left256 		= (t256(32+16));	/*50*/			/* 32,	224(128+64+32)	*/
	if (t256(GAME_WIDTH/2) < gcmd_obj->center.x256)
	{	/* ��ʉE������o�� */
		gcmd_obj->jyumyou				+= (512+512+512+512);	/* (1024-1) or (2048-1) */		/*SS00*/
		gcmd_obj->zd00_clip_left256 	+= (t256((128+64)));	/*50*/			/* 32,	224(128+64+32)	*/
	}
//	else	{;/* ��ʍ�������o�� */}
	gcmd_obj->zd01_clip_right256		= (gcmd_obj->zd00_clip_left256)+t256(128-32); /* 128, 320(256+64) */	 //  /*GAME_WIDTH-50-s->w*/
}