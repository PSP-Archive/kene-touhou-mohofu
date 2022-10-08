
#include "boss.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�J�[�h�Ǘ��V�X�e��
	-------------------------------------------------------
	�J�[�h�̓V�X�e���ŃT�|�[�g���Ă���̂ŁA�ǂ̃{�X���A�ǂ̃J�[�h�ł����Ă܂��B
	-------------------------------------------------------
	ToDo:
	�� �U���̊Ǘ�
	�� ����̊Ǘ�(���\����)
	�� �G��(���G��)���J�[�h�����Ă�@�\�́A�p�~���������ǂ������m��Ȃ��B
	����(���G�������G���J�[�h�@�\)��p�~���āA����ɓ����Ƀ{�X���o��������(�܂蒆-�{�X)
	�̕����A�V�X�e�����������肵�ėǂ��C������B��������ׂɂ͐F�X������������B
	����� dat �̋K�i���ƁA�����͏o���Ȃ��̂ŁA��� dat �̋K�i��ς��āA
	dat ����{�X�̉�b���N������悤�ɂ���K�v������B
	�v���C���[�ɋ����ĉ�b���Ⴄ�̂ŁA���̕ӂ̋K�i����͂܂�����B(����V�i���I�Ƃ�)
	-------------------------------------------------------
	�� �G��(���G��)���J�[�h�����Ă�@�\�́A�p�~���āA
	�G��(���G��)���J�[�h�����������ꍇ�́A�u�J�[�h�����Ă�U�R�v�Ƃ�������V�݂��Ă�����g��
	�V�X�e���ł̓T�|�[�g���Ȃ������ǂ��Ǝv���B�̂ł������������ŉ����\��B
---------------------------------------------------------*/

#include "kanji_system.h"

#include "../menu/kaiwa_sprite.h"

/*---------------------------------------------------------
	�{�X�ǉ�
---------------------------------------------------------*/

// �`���m EX1��
// ��� 6��
extern void spell_boss_move_system_17_sakuya_bimyou_idou(void);/*(�����Ɉړ�����)*/
extern void spell_boss_move_system_16_sakuya_nazo_keitai(void);/*(�������̓�`��)*/
extern void spell_boss_move_system_15_sakuya_festival_knife(void);/*(�����u�t�F�X�e�B�o���i�C�t�v)*/
extern void spell_boss_move_system_28_sakuya_miss_direction(void);/*(��p�u�~�X�f�B���N�V�����v)*/

// �p�`�F 5��

// �� 4��
extern void spell_boss_move_system_13_aya_taifu(void);
// �P�� 3��
extern void spell_boss_move_system_12_kaguya_funya_idou(void);
extern void spell_boss_move_system_11_kaguya_yureru(void);
// ���� 2��
extern void spell_boss_move_system_10_mima_keitai(void);
// �A���X 1��

// ���ʌ`��
extern void spell_boss_move_system_05_xy_douki_differential64(void);
extern void spell_boss_move_system_04_xy_douki_differential32(void);
extern void spell_boss_move_system_03_x_douki(void);
extern void spell_boss_move_system_02_xy_hidouki(void);
extern void spell_boss_move_system_01_taihi_ue_naka(void);


/*---------------------------------------------------------
	�X�v���C�g ���X�g�ɓo�^���ꂽ�X�v���C�g��S�� �B
---------------------------------------------------------*/
#define TEST_ZAKO_HIDE (0)
#if (1==TEST_ZAKO_HIDE)/* �{�X���e���󂯂� */
static void sprite_sethide_all(OBJ *s, u32 length)
{
	int ii;
	for (ii=0; ii<length; ii++)/* �S�����ׂ�B */
	{
		cg_BOSS_DATA_35_move_jyumyou	= 0xff;
		#if (1)/* �f�o�b�O�Ă��� */
		s->center.x256		= (-1);
		#endif
		s++;
	}
}
static void zako_all_timeup(void)/*int ty pe*/
{
	OBJ *s;
	s = &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+0];
	sprite_sethide_all(s, OBJ_POOL_02_TEKI_FIX_0256_MAX);
}
#endif


/*---------------------------------------------------------
	[r36�V]�{�X�U���ړ��̂݁B
---------------------------------------------------------*/

static int bos_ddd_obj_alt_x256;
static int bos_ddd_obj_alt_y256;
static int bos_ddd_obj_target_x256;
static int bos_ddd_obj_target_y256;
//static int bos_ddd_obj_ido_speed256;


/*---------------------------------------------------------
	�{�X�U���ړ��̂݁B
---------------------------------------------------------*/
/* �U���ړ�/�U���v�Z */
/*static*/static OBJ_CALL_FUNC(boss_r36_yuudou)
{
	/*(�Ƃ肠����)*/
	cg_BOSS_DATA_34_toutatu_wariai256 -= (6);/*(�{�X�ޔ��A���x�B1/t256()�`���B(�t���Ŏw�肷��) )*/	/*(�{�X�ޔ��A���x)*/
	cg_BOSS_DATA_34_toutatu_wariai256 = psp_max(cg_BOSS_DATA_34_toutatu_wariai256, 0);
	//
	if (0 < cg_BOSS_DATA_34_toutatu_wariai256)/*(�ړ����K�v�ȏꍇ�݈̂ړ��������s��)*/
	{
		int move_rate256;
		move_rate256 = cg_BOSS_DATA_34_toutatu_wariai256;
		move_rate256 = psp_min(move_rate256, 256);
		move_rate256 = psp_max(move_rate256, 0);
		#if (1)/* �񓙕��l�̌v�Z */
		{
			u32 i_rate65536;
			i_rate65536 = (move_rate256 << 8);
		//	i_rate65536 = (int)(vfpu_ease_in_out(t)*256.0);
			i_rate65536 = (int)(vfpu_ease_in_out65536(i_rate65536));	/* t65536�̓����J�E���^�l���g���A�񓙕��ɂȂ�悤�l���C������B
			�񓙕��̕����́uease_in_out�v����́A�n�߂ƍŌオ�������ŊԂ������Ƃ����z�������B */
			move_rate256 = (i_rate65536 >> 8);
		}
		#endif
		//------------------
		#if (1)/*(���B�������l�����āA��������B)*/
	//	VR04	= ((bos_ddd_obj_alt_x256)); 	/*(�����ʒu[A]t256()�`��)*/
	//	VR05	= ((bos_ddd_obj_alt_y256)); 	/*(�����ʒu[A]t256()�`��)*/
	//	VR06	= ((bos_ddd_obj_target_x256));	/*(�����ʒu[B]t256()�`��)*/
	//	VR07	= ((bos_ddd_obj_target_y256));	/*(�����ʒu[B]t256()�`��)*/
		VR04	= ((bos_ddd_obj_target_x256));	/*(�����ʒu[A]t256()�`��)*/
		VR05	= ((bos_ddd_obj_target_y256));	/*(�����ʒu[A]t256()�`��)*/
		VR06	= ((bos_ddd_obj_alt_x256)); 	/*(�����ʒu[B]t256()�`��)*/
		VR07	= ((bos_ddd_obj_alt_y256)); 	/*(�����ʒu[B]t256()�`��)*/
		REG_11_GOUSEI_WARIAI256 	= move_rate256;/*(��������t256()�`��)*/
		CPU_CALL(multiprex_rate_vector);/*(�j�󃌃W�X�^�����̂Œ���)*/
		#endif
		// ���̎��_�ŁA
		// VR06: �����l
		// VR07: �����l
		//-----------------------
		cg_BOSS_DATA_3a_center_x256 = (VR06);
		cg_BOSS_DATA_3b_center_y256 = (VR07);
	}
}
/*---------------------------------------------------------
	�{�X�U���ړ��̂݁B(�U���ړ����W��ݒ�)
---------------------------------------------------------*/
extern void boss_set_new_position_void(void)
{
	cg_BOSS_DATA_34_toutatu_wariai256	= t256(1.0);/*(�����l)*/
	/*(���݈ʒu��ݒ�)*/
	bos_ddd_obj_alt_x256		= (cg_BOSS_DATA_3a_center_x256);
	bos_ddd_obj_alt_y256		= (cg_BOSS_DATA_3b_center_y256);
	/*(�ޔ��ʒu��ݒ�)*/
	bos_ddd_obj_target_x256 	= VR06;/*(t256()�`��)*/
	bos_ddd_obj_target_y256 	= VR07;/*(t256()�`��)*/
	/*(�ړ����x��ݒ�)*/
//	bos_ddd_obj_ido_speed256	= HATSUDAN_R11_speed256;/*(==REG_11)*/
}
/*---------------------------------------------------------
	�{�X�U���ړ��̂݁B(�U���ړ����W���^�[�Q�b�g����ݒ�)
---------------------------------------------------------*/
extern void boss_set_new_position_from_target(void)/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
{
	VR06	= (cg_BOSS_DATA_30_target_x256);/*(t256()�`��)*/
	VR07	= (cg_BOSS_DATA_31_target_y256);/*(t256()�`��)*/
	boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
}
/*---------------------------------------------------------
	���ʃ{�X�ޔ�(���j��ɉ�ʊO�Ƀ{�X��������)
	[�J�[�h�V�X�e�����Ɉړ��\��]
---------------------------------------------------------*/

static OBJ_CALL_FUNC(common_99_keitai)
{
	boss_r36_yuudou(src);
	/* �ړ��������W�ɓ��������͂ݏo������A�����Ƃ���B */
	if (cg_BOSS_DATA_34_toutatu_wariai256 <= t256(0))
	{
		#if (1)
	//�d��	src->callback_mover 	= NULL; 		/* �����܂� */
		sprite_kotei_obj_r36_taihi(src);/*(�{�Xobj�g�p���ł��邪�ޔ��ʒu�֑ޔ�)*/
		bullets_to_hosi();/* �e�S���A���A�C�e���ɂ��� */
		#endif
		boss_effect_kotei_obj_r36_taihi();
		//return /*(1)*/;/*�ړ�����*/
	}
}

// ���[�U�[
extern void add_laser_off_void(void);
/* ���j��ɉ�ʊO�Ƀ{�X�������� */
static OBJ_CALL_FUNC(common_88_keitai)
{
	#if (1)//�d�����邩��(?)
	/*(���[�U�[���[�h�́A�����I��off�ɂ���B)*/
	add_laser_off_void();
	#endif
	//
	#if (1)
	/*(�ޔ��ʒu��ݒ�)*/
	VR06 = (int)(GAME_X_OFFSET*256+(GAME_320_WIDTH*256/2));
	VR07 = -t256((50.0/2));/* +t256(50.0) �{�X�O���̍ő�T�C�Y(50[pixel]) */
	boss_set_new_position_void();
	#endif
	cg_BOSS_DATA_35_boss_base_state777	= (0);	/*ST_00*/	/*�����l��0�ɂ���B*/
	src->callback_mover 					= common_99_keitai; 	/* �ŏI�`�Ԃɂ���B */
}

/*---------------------------------------------------------
	�{�X���S����
	-------------------------------------------------------
	�� �U���̏ꍇ�̎��S���� 		DESTROY_CHECK_00_WIN_BOSS
	�� ���Ԑ؂�̏ꍇ�̎��S���� 	DESTROY_CHECK_01_IS_TIME_OUT
	-------------------------------------------------------
	�{�X�G����
	�{�X�|�����ꍇ�̏���
	(�v���C���[���܂�)
---------------------------------------------------------*/
/*	�� �U���̏ꍇ�̎��S���� 	�� ���Ԑ؂�̏ꍇ�̎��S���� */

extern void player_loop_quit(void);
extern void jiki_eien_muteki_on(void);/*(���@�N���Xjiki::eien_muteki_on(void);) (src/mohoufu/jiki/jiki.c)*/
extern void set_bg_alpha(int set_bg_alpha);

/* ���ʃ{�X�ޔ�(���j��ɉ�ʊO�Ƀ{�X��������) */
/*(���j�`��)*/
//	/*(?)*/static OBJ_CALL_FUNC(NULL_keitai)/*(src==�{�X�G�{��)*/
	/*(?)*/static void NULL_keitai_void(void)/*(src==�{�X�G�{��)*/
{
	/*(card.boss_move_card_callback��NULL�ɑΉ����ĂȂ��ꍇ�ɁA�K�v�ȃ_�~�[�`��)*/
}
//	/*static*/ void boss_destroy_check_type(OBJ/**/ *src/*�G����*/, int check_type)



	// /* �{�X��|��������A�u�{�X��C�x���g�v�O�̏��� */
//	#if (0)
//	enum
//	{
//		DESTROY_CHECK_00_WIN_BOSS = 0,
//		DESTROY_CHECK_01_IS_TIME_OUT,
//	};
//	int check_type;
//	check_type = DESTROY_CHECK_00_WIN_BOSS;/*(�Ƃ肠����)*/
//	if (DESTROY_CHECK_00_WIN_BOSS == check_type)
//	#endif
extern OBJ_CALL_FUNC(common_create_item);/*(boss_item.c)*/


/*[���̊֐��̃A�h���X���̂����j��̃t���O�Ƃ��Ďg�p]*/extern void void_gekiha_keitai(void)/*(src==�{�X�G�{��)*/
{
	// card.boss_move_card_callback_void �� void_gekiha_keitai �Ȃ猂�j��B
	// ����ȊO�Ȃ猂�j��ł͂Ȃ��B
	/*[���g�͖������ǕK�v]*/
}

/*static*/ OBJ_CALL_FUNC(boss_action_05_all_gekiha_keitai)/*(src==�{�X�G�{��)*/
{
	#if 0/*(�݊�??)*/
	card.boss_move_card_callback = NULL_keitai;/*(card���{�X�ړ�������ݒ肷��)*/
	#endif
	//
	#if 0
//	bakuhatsu_add_circle(src, 1);/*(�����G�t�F�N�g)*/
	#endif
	src->boss_hp = (0);
	/* �R�[���o�b�N�o�^ */
	src->callback_hit_teki			= NULL; 	/*(�_�~�[�R�[���o�b�N�o�^)*/
	src->callback_mover 			= common_88_keitai;/* ���ʃ{�X�ޔ�(���j��ɉ�ʊO�Ƀ{�X��������) */
	src->callback_root_supeka		= NULL; 	/*(�_�~�[�R�[���o�b�N�o�^[�O�̈�])*/
//�d��(���ɐݒ�ς�)	card.boss_move_card_callback	= NULL_keitai;/*(�e�X�g)*/
	{
		#if (1==USE_BOSS_JIKANGIRE)/*(�g�p�\�肠��B������)*/
		if (0 != (cg_state_flag & JIKI_FLAG_16_0x8000_BOSS_JIKAN_GIRE))/*0 >= card.card_timer*/
		{
			;/* ���Ԑ؂�̏ꍇ�̓{�[�i�X�A�C�e���Ɠ��_�Ȃ��B */
		}
		else
		#endif
		{
			/* �U���œ|�����ꍇ�̂� */
			common_create_item(src);/*([���j���]�{�[�i�X�A�C�e�����o��)*/
			player_dummy_add_score(src->base_score);	/* �{�X�̓��_���Z */
		}
	}
	//
	#if (0)/*(�f�o�b�O)*/
	{	psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// ���p40��"�ő�\��������"
			"load stage: STAGE%d" "\\n"
			"�{�X�A���j�e�X�gOK�B", cg.game_now_stage);
	}
	#endif
//
	jiki_eien_muteki_on();/*(���@���ꎞ�I�ɁA���G��Ԃɂ���)*/
	set_bg_alpha(255);/* ��ʂ𖾂邭���� */
//	s1->color32 		= MAKE32RGBA(0xff, 0xff, 0xff, 0x50);	//	s1->alpha		= 0x50; 	/* ������ */
//	obj_maru->color32	= MAKE32RGBA(0xff, 0xff, 0xff, 0x50);	//	obj_maru->alpha = 0x50; 	/* ������ */
	// �{�X��|�����Ƃ��̏���
	bullets_to_hosi();/* �e�S���A���A�C�e���ɂ��� */
	AUDIO_18_voice_number	= VOICE03_BOSS_HAKAI;
	AUDIO_19_voice_truck	= TRACK03_IVENT_DAN/*TRACK02_JIKI_BOMBER*/; 	CPU_CALL(cpu_voice_play);
//	AUDIO_19_voice_truck	= TRACK01_PICHUN; /*�\��(���邳��)*/			CPU_CALL(cpu_voice_play);
	cg.draw_boss_hp_value	= (0); /* �K�v */ /*(boss_hp_frame_check()�𖳌��ɂ���BGu���Ń`�F�b�N�����Ȃ�)*/
	cg_bomber_time			= (0); /* �s���� */
	{
//		cg_state_flag		&= (~(JIKI_FLAG_0x0040_BOSS_GO_ITEM_JIDOU_SYUU_SYUU));		/* �I��� */
		cg_state_flag		|= ( (JIKI_FLAG_0x0040_BOSS_GO_ITEM_JIDOU_SYUU_SYUU));		/* �������W�J�n */
		/* �������W���[�h�̓X�e�[�W���[�h���ɋ������������B */
		if (
			(0==cg.game_practice_mode)/* ���K���[�h�ł̓{�X��C�x���g�͌���Ȃ���B */
			||/*(�܂���)*/
			(	/* �B���G���f�B���O */
				((1)==cg.game_practice_mode)/* ���K���[�h�ł̓{�X��C�x���g�͌���Ȃ���B */
				&&/*(����)*/
				((0)==(cg_VR20_game_difficulty))/*(easy�̏ꍇ)*/
				&&/*(����)*/
				((6) == (cg.game_now_stage))/*(6�ʂ̏ꍇ�A�B���G���h)*/
			)
		)
		{
			#if (1==USE_r36_SCENE_FLAG)
			NEXT_SCENE;/*(���̏�ʂ֐ݒ�)*/
			#else
			#endif
		}
		else/* ���K���[�h�̏ꍇ�A�I������ */
		{
			#if 1/* ���̂Q�̃Z�b�g�Ŏ����I�ɏI��(GAME OVER)���� */
			cg.game_now_max_continue = 1;	/* �R���e�B�j���[�����Ȃ� */
			player_loop_quit();
			#endif
		}
	}
}



////////  �`�Ԍn�͂�������ɋL�q���B


/*---------------------------------------------------------
	�J�[�h�o�^
	-------------------------------------------------------
		[�J�[�h�U���݂̂Ɏd�l�ύX]
		(�������̈ړ��Ȃǂ��J�[�h����)
		(�J�[�h�����Ȃ�������J�[�h����)
---------------------------------------------------------*/

// int card.number; 		/* ���p */	// �J�[�h�ԍ�

global CARD_SYSTEM_GLOBAL_CLASS card;

/*---------------------------------------------------------
	�J�[�h�ݒ�B
---------------------------------------------------------*/
#include "card_resource.h"

/*---------------------------------------------------------
	�J�[�h�����ɐi�߂�B
---------------------------------------------------------*/

static void card_set_next(void)/*(�J�[�h�����ɐi�߂�B)*/
{
	/*(�K��l�̎Z�o)*/
	/*(���~�b�g������)*/		/*(����U��)�̍U�������� */
//	set_new_limit();			/* �ʏ�U��(����U��)�̍U���� */
	card.limit_health -= (my_card_resource[(card.address_set + (4))].spell_life);	/*1000 500*/
	card.limit_health = psp_max(card.limit_health, 0);		/*(0����==�����ɂ��Ȃ�)*/
	//
	#if 0
	/*(�������Ԃ𑫂�)*/
	card.card_timer += (((my_card_resource[(card.address_set + (4))].spell_limit_time)));	/* 75*64==75[count] 	��99[�b(64/60)](�P�ʂ͕b�ł͂Ȃ�) */
	#else
	/*
		(r35 �Œ萧�����Ԃ�ݒ�[���d�l])
		�^�C�}�[�l�̕ێ�������ꃖ�����������̂ŁA�Ƃ肠�������������`�ɂ��Ƃ����B(�������Ԃ̐ݒ蕔����������)
	*/
	card.card_timer = (((my_card_resource[(card.address_set + (4))].spell_limit_time)));	/* 75*64==75[count] 	��99[�b(64/60)](�P�ʂ͕b�ł͂Ȃ�) */
	#endif
	//
//	card_address_incliment();/*(0���ځ�1���ڂ̃J�[�h���Z�b�g����B)*/
	/*(�J�[�h�����ɐi�߂�B)*/
	card.address_set += (4);/*(�J�[�h�����ɐi�߂�B)*/
	/* card���{�X�ړ�������ݒ肷��B */
	/*(�{�X�ړ��R�[���o�b�N�o�^)*/
	card.boss_move_card_callback_void = my_card_resource[(card.address_set)].boss_move_keitai_set_callback_void;/*(card���{�X�ړ�������ݒ肷��)*/
}
	/*(���j�`�Ԃ̏ꍇ�A�J�[�h�����ɐi�߂Ȃ��B)*/
//	if (SPE LL_49_r36_gekiha != my_card_resource[(card.address_set)].spell_set_number)
//	{
//	}


	/* [(�Ƃ肠����)�J�[�h�U���݂̂Ɏd�l�ύX]�����̂ŁA�Ō㌂�Ă�J�[�h���Ȃ��Ȃ����ꍇ�ɍU��������ׁB */
/*---------------------------------------------------------
	[�{�X�s��01: �J�[�h���j��̏���]
	�{�X�̃J�[�h�����j���āA���̃J�[�h�Ɉڂ�ꍇ�̏����B
---------------------------------------------------------*/
static OBJ_CALL_FUNC(boss_action_a02_new_card_set);
static OBJ_CALL_FUNC(boss_action_01_gekiha_go)
{
	#if (0)/*�����*/
	bakuhatsu_add_circle(src, 1);
	#endif
	//
	/* �{�X�`�ԕύX���̋��ʃ��[�`�� �J�[�h���j��A�C�e���o���B */
	//++	pd_bo ssmode=B04_CHANGE;
	bullets_to_hosi();/* �e�S���A���A�C�e���ɂ��� */
	/*(���ԓ��̏ꍇ)*/
	if (0 < (card.card_timer)) /*1	(card_set_next();�ȑO�ɕK�v) */
	{
		common_create_item(src);
	}
	#if (1)/*(�y�A)*/
	src->callback_root_supeka		= boss_action_a02_new_card_set;
	card_set_next();/*(�J�[�h�����ɐi�߂�B)*/
	#endif
	//
	#if 0// (1==TEST_ZAKO_HIDE)/* �{�X���e���󂯂� */
	zako_all_timeup();/* �U�R�^�C���A�E�g(�t�F�C�h�A�E�g���������ֈڍs) */
	#endif
	//
	AUDIO_18_voice_number	= VOICE07_BOMB;
	AUDIO_19_voice_truck	= TRACK02_JIKI_BOMBER;/*�e�L�g�[*/
	CPU_CALL(cpu_voice_play);
	/*--- BOSS ���ʂ��Ēl�� 0 �ɂ���B------------*/
	cg_BOSS_DATA_35_move_jyumyou = (0);
//	cg_BOSS_DATA_35_boss_base_state777 = (0);/* ���ʂ��� �l�� 0 �ɂ��� */
//	player_dummy_add_score(src->boss_base_score);
}



/*---------------------------------------------------------
	[�{�X�s��04: �J�[�h�U����]
	01�J�[�h�U����
	�{�X�A�X�y�J�ōU�����B
---------------------------------------------------------*/

static OBJ_CALL_FUNC(boss_action_04_speka_kougeki)
{
	/*(���Ԑ����J�E���g)*/
	card.card_timer--;/*fps_factor*/	/*(�X�y�J���Ԍo��)*/
	if (0 >= (card.card_timer)) /*1*/
	{
		card.card_timer 	= (0);/*(�ꎞ�I��0�ɂ���)*/
		/*(�������̃X�y�J������΁A�X�y�J�V�X�e�����Ŏ��ֈڍs����B���̍ۂ� card.card_timer �Ɏ��Ԃ����Z�����B)*/
		src->boss_hp		= card.limit_health;		/* (�Ƃ肠����) */
	//	boss_destroy_check_type(h/*�G����*/, DESTROY_CHECK_01_IS_TIME_OUT);/*	�� �U���̏ꍇ�̎��S���� 	�� ���Ԑ؂�̏ꍇ�̎��S���� */
		#if (1==USE_BOSS_JIKANGIRE)/*(�g�p�\�肠��B������)*/
		cg_state_flag |= JIKI_FLAG_16_0x8000_BOSS_JIKAN_GIRE;/*(���Ԑ؂�t���Oon)*/
		#endif
	}
	/*---------------------------------------------------------
	---------------------------------------------------------*/
//	#if (0)/*(r36, NULL�͓o�^�ł��Ȃ��B�������Ȃ��ꍇ�� NULL_keitai ��o�^����B)*/
//	if (NULL != card.boss_move_card_callback)
//	#endif
	//{
	//	(card.boss_move_card_callback)(src);/*(-r40�{�X�ړ��`�Ԗ��ɁA�{�X�ړ����������s����)*/
		(card.boss_move_card_callback_void)();/*(r41-�{�X�ړ��`�Ԗ��ɁA�{�X�ړ����������s����)*/
	//}
	/*---------------------------------------------------------
	---------------------------------------------------------*/
	/* �J�[�h�����I���Ȃ�J�[�h�ݒ肵�A�����B */
	if (SPELL_00==card.spell_used_number)	/* �J�[�h�����I���Ȃ�J�[�h���� */
	{
		/*---------------------------------------------------------
			�J�[�h�V�X�e���̃{�X�`�Ԃɓo�^���ꂽ�J�[�h�ԍ����擾���A
		//	�����ɃJ�[�h�̎��Ԑ؂��ݒ肷��B
			�����ɃX�y���̏��������s���B
		---------------------------------------------------------*/
		/* ���݂̌`�ԂŌ��Ă�J�[�h�ԍ����J�[�h�V�X�e���ɐݒ�B */
		/*(���񏉊���)+(���݌��ׂ��ԍ����J�[�h�V�X�e������擾)*/
		card.spell_used_number	= my_card_resource[(card.address_set)].spell_set_number;	/* [�V]�J�[�h���Z�b�g */
		card_maikai_init(src);/*(���񏉊���)*/
	}
	/*---------------------------------------------------------
	---------------------------------------------------------*/
	boss_r36_yuudou(src);
	if (TUKAIMA_00_OFF != card.tukaima_used_type)	/* �g���������͕K�v�H */
	{
		tukaima_system_add_dolls(src);/*(�����̎g�����B�̐���������B�g�����͈�l�łȂ��ĕ����̕��������B)*/
		card.tukaima_used_type = TUKAIMA_00_OFF;/*(�������������̂� off �ɂ���B)*/
	}
	/*---------------------------------------------------------
	�{�X���U�������ꍇ�̃t���[���`�F�b�N
	-------------------------------------------------------
	���C�t�����Ȃ��Ȃ�ƃ{�X���Ȃ��Ȃ����ȂȂ��̂́A���o�������ł��B
	�Ă��Ɓ[�ɍČ��H
	-------------------------------------------------------
	ToDo:
	���|��A�ŋ߂̓��C�t�͂���ς胊�j�A�Ɍ����ĂāA
	�\������log�Ȃ񂶂�ˁH���ċC�����Ă����B
	�����������ɂ��悤���ȁB�Q�[���o�����X�Ƃ��F�X�ς�邩��B
	---------------------------------------------------------*/
	/*�{�X���U�������ꍇ�̃t���[���`�F�b�N/�J�[�h���[�h�`�F�b�N*/
//	boss_hp_frame_check(src);
//	static OBJ_CALL_FUNC(boss_hp_frame_check)/*(�{�X�{��)*/
	{
		s32 limit_max_hp_dec_boss_by_frame;
	//	u8 test_boss_hp_value;
		u16 test_boss_hp_value;
	//	test_boss_hp_value = (src->boss_hp>>5) & 0xff; /* 8192/32 == 256 (r32) */
	//	test_boss_hp_value = (src->boss_hp>>7) & 0xff; /* 32768/32 == 256 (r33) */
		test_boss_hp_value = (src->boss_hp>>9) & 0x03ff;	/* ?/32 == 256*4 (r35u2-) */
		#if 1
	//	limit_max_hp_dec_boss_by_frame = (test_boss_hp_value>>2) | (0x0f);
	//	limit_max_hp_dec_boss_by_frame = (test_boss_hp_value>>2) | (0x08);
	//	limit_max_hp_dec_boss_by_frame = (test_boss_hp_value) | (0x10);/*(-r35u1)*/
		limit_max_hp_dec_boss_by_frame = (test_boss_hp_value) | (0x40);/*(r35u2-)*/
		#endif
		//
	//	if (limit_max_hp_dec_boss_by_frame < card.boss_hp_dec_by_frame) 	{card.boss_hp_dec_by_frame = limit_max_hp_dec_boss_by_frame;}
		card.boss_hp_dec_by_frame = psp_min(card.boss_hp_dec_by_frame, limit_max_hp_dec_boss_by_frame);
	}
	/*---------------------------------------------------------
	---------------------------------------------------------*/
	src->boss_hp -= card.boss_hp_dec_by_frame;
	card.boss_hp_dec_by_frame = 0;/* �g�����̂ŏ���(�t���[���P��) */
	if (card.limit_health >= src->boss_hp)	/* �K��l�ȉ��ɂȂ�΃J�[�h���[�h���� */
	{
		src->boss_hp = card.limit_health;	/* �K��l�����ɂ��Ȃ��B */
		src->callback_root_supeka		= boss_action_01_gekiha_go;
	//	boss_destroy_check_type(src, DESTROY_CHECK_00_WIN_BOSS);
		cg.callback_gu_draw_haikei		= cg.callback_gu_draw_haikei_modosu;
	}
}


/*---------------------------------------------------------
	[�{�X�s��03: �J�[�h�J�n�ړ�]
	02�J�[�h�J�n�ړ�
	�J�[�h�J�n�ʒu�܂Ń{�X���ړ�����B
	�����G�̏������s���B
---------------------------------------------------------*/
static int aaa_wait;
static OBJ_CALL_FUNC(boss_action_03_move_start_position)
{
	#if 1/*(r32p)*/
//	bo ss_y uudou_idou_nomi(src);/*(r32p)*/ //	/* [��	4 �b]== 4.2666==(256/60[frame]) */
//	bo ss_y uudou_hiritu_keisan(src);
	boss_r36_yuudou(src);
	/* �قډ�ʒ��S�t�߂܂ŁA�ړ������B */
	#endif/*(r32p)*/
	// �{�X(�����G�ړ�)
	#if 0/*(�����ړ�)*/
	kaiwa_sprite[1].center.y256 	= t256(272+128) - ((aaa_wait)<<9);
	#else/*(�������ړ�)*/
	{
		u32 aaa = (aaa_wait)+(aaa_wait);
		aaa += 128;/*(�㉺����ւ�)*/
		aaa &= 0xff;/*(0...255)*/
	//	aaa = ((aaa)|(aaa<<8));/*(0...65535)*/
		aaa <<= 8;/*(0...65535)*/
		aaa = vfpu_ease_in_out65536(aaa);
		aaa += 32768;/*(�㉺����ւ�)*/
		aaa &= 0xffff;/*(0...65535)*/
		aaa += aaa;/*(2�{)*/
		kaiwa_sprite[1].center.y256 	= t256(272+128) - (aaa);
	}
	#endif
	aaa_wait--; /* �{�X�s�� */
	if (0 > aaa_wait)
	{
		src->callback_root_supeka		= boss_action_04_speka_kougeki;
	}
}

/*---------------------------------------------------------

---------------------------------------------------------*/


/*---------------------------------------------------------
	[�{�X�s��02: �J�[�h�ݒ�]
	03�J�[�h�ݒ�
	���̃J�[�h���n�߂�ׂ̏����ݒ���s���B
---------------------------------------------------------*/
/* �{�X�z�[���|�W�W�����Bx���W�B(�J�[�h�J�n���ɕK���z�[���|�W�W�����ֈړ�����B) */
//#define BOSS_XP256		(t256(GAME_WIDTH/2))	/* ���S���W�Ȃ̂� */
#define BOSS_XP256			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH/2))	/* ���S���W�Ȃ̂� */
static OBJ_CALL_FUNC(boss_action_a02_new_card_set)
{
	VR10_BOSS_SPELL_TIMER = (0);	/* �J�[�h�����������I�Ɏ~�߂�B */
	bullets_to_hosi();		/* ���Ă̓G�e���Ahosi�A�C�e���ɕς��� */
	/* �^���t�߂ɑޔ� */
//	cg_BOSS_DATA_34_to utatu_wariai256	= t256(  0);/* �������ς݂̕K�v���� */
//	cg_BOSS_DATA_34_to utatu_wariai256	= t256(1.0);/* �������ς݂̕K�v���� */
//	cg_BOSS_DATA_30_ta rget_x256			= BOSS_XP256; //t256(0); t256(153);
//	cg_BOSS_DATA_31_ta rget_y256			= t256(16.0); //t256(0); cg_BOSS_DATA_3b_center_y256;
	VR06	= (BOSS_XP256);/*(t256()�`��)*/
	VR07	= (t256(16.0));/*(t256()�`��)*/
	boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
	if (void_gekiha_keitai == card.boss_move_card_callback_void)/*[���̏����Ȃ猂�j��̔�]*/
	{
		src->callback_root_supeka		= boss_action_05_all_gekiha_keitai;
	}
	else
	{
		src->callback_root_supeka		= boss_action_03_move_start_position;
	}
	// �{�X
	kaiwa_sprite[1].center.x256 	= t256(256);
	aaa_wait	= (127);/*on*/
	//
	/* �X�y���������֓�����[�p�~] */#if 1/* (�V[�J�[�h�n�܂�O�ɏ�����]) ��0�`�Ԃ���A�K���ĂԔ��B */
	/* �J�[�h������ */
//	#if (0)/*(r36, NULL�͓o�^�ł��Ȃ��B�������Ȃ��ꍇ�� NULL_keitai ��o�^����B)*/
//	if (NULL != my_card_resource[(card.address_set)].spell_init_callback)
//	#endif
//	{
	//	spell_init_callback_do(src);
	//	(my_card_resource[(card.address_set)].spell_init_callback)(src);
//	}
	#endif
	#if (1)
	/*---------------------------------------------------------
		�J�[�h����(����)�\��
		�J�[�h�w�i�́A�܂��������ǁA�����I�Ɋg���\��B
	---------------------------------------------------------*/
	//static void draw_card_name(void)
	{
		kanji_window_clear_line(ML_LINE_04);	/* �����E�B���h�E��4�s��(==3)�̓��e�������B */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_04)*(KANJI_FONT_18_HEIGHT_P2));	/* �J�[�\����4�s��(==3)�ֈړ� */
	//
		if (NULL != my_card_resource[(card.address_set)].spell_str_name)
		{
			/* �J�[�h�w�i������ꍇ */
			cg.callback_gu_draw_haikei = cg.callback_gu_draw_haikei_supeka;
			//
			// ""�J�[�h�̕����\���ʒu�B
			{
			//	ml_font[(ML_LINE_04)].timer 	= ML_ON;	/*"�\��ON"*/
				ml_font[(ML_LINE_04)].timer 	= byou60(5);	/* �� 5 �b */
				ml_font[(ML_LINE_04)].x 		= (96);/* X�ʒu */
				ml_font[(ML_LINE_04)].y 		= (12);/* Y�ʒu */
			//	ml_font[(ML_LINE_04)].render	= NULL;
			//	ml_font[(ML_LINE_04)].str		= my_font_text;/*(�f�o�b�O)*/	/*"�\��on"*/
			}
			ml_font[(0)].haikei 		= (ML_HAIKEI_01_BOSS_SPELL_CARD);/* [��/�{�X�J�[�h�p�w�i]�{�X�J�[�h�p����Ӕw�ion */
			cg.msg_time = byou60(5);	/* �� 5 �b */
			strcpy(my_font_text, my_card_resource[(card.address_set)].spell_str_name);
			kanji_color(/*int color_type*/(7)|STR_CODE_NO_ENTER);	/* ���s���Ȃ� */
			kanji_draw();
		}
		else
		{
			/* �J�[�h�w�i�������ꍇ */
			cg.callback_gu_draw_haikei = cg.callback_gu_draw_haikei_modosu;
		}
	}
	#endif
}

/*---------------------------------------------------------
	[�{�X�s��00: ��b�I���҂�]
	[��b���̌`��]�U���s�A��b�I���܂őҋ@����B
	-------------------------------------------------------
	�ҋ@���I�������A�U���\�ɂ���B
---------------------------------------------------------*/
/*static*/extern/*extern*/	void callback_hit_boss(OBJ/**/ *src, OBJ *tama);
static OBJ_CALL_FUNC(boss_action_a01_kaiwa_syuuryou_mati)
{
	/* �{�X�퓬�O�̉�b�I���ς�? */
	if (SCENE_NUMBER_0x0800_BOSS_TATAKAU==(cg_state_flag & 0x0f00))
	{
		/*(�v���C���[�e�󂯕t���R�[���o�b�N��o�^���A�{�X�ւ̍U�����\�ɂȂ�B)*/
		src->callback_hit_teki		= callback_hit_boss;/*(�v���C���[�e�󂯕t���R�[���o�b�N�o�^)*/
		#if (1)/*(�y�A)*/
		src->callback_root_supeka	= boss_action_a02_new_card_set;/*(�J�[�h���Z�b�g�����Ԃֈڍs�B)*/
		card_set_next();/*(�J�[�h�����ɐi�߂�B)*/
		#endif
	}
	boss_r36_yuudou(src);/*(�v�邩���H�H)*/
}


/*---------------------------------------------------------
	��b�V�X�e������{�X�G(�L����)��ǂ݂���ŁA
	��{�I�ȏ��������s���B
---------------------------------------------------------*/
	#if 0/* �������ς݂̕K�v����(?)*/
	h->math_vector.x256 					= t256( 0);
	h->math_vector.y256 					= t256( 0);
	#endif
extern void stage_boss_load_texture(void);
// src/core/douchu/boss.h �̏��������Q�Ƃ��鎖�B
extern OBJ_CALL_FUNC(root_boss_mover);
extern void spell_cpu_common_reset(void);
extern void called_from_kaiwa_system_boss_load(int boss_number)
{
	/*(�{�X�ԍ��� 0-7 �̂����ꂩ�ɏ���ɌŒ�(r36����)�B)*/
	boss_number &= (8-1);
	//----[BOSS]
	OBJ *h;
	h									= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(�{�X�{��)*/
	{
		h->obj_type_set 				= BOSS_00_11;/*(�Ē�`�̕K�v����(?))*/
		h->callback_mover				= root_boss_mover;/*(�{�X�u���[�g�����v��ǉ��B�{�X�̑S�Ă̍s���́u���[�g�����v���珈������B)*/
		h->callback_hit_teki			= NULL;/*(�_�~�[�R�[���o�b�N�o�^) (��b���Ƀv���C���[�e�͎󂯕t���Ȃ�)*/
		h->callback_root_supeka 		= boss_action_a01_kaiwa_syuuryou_mati;/*(��b�I���҂�)*/
	//
		//------------ �J�[�h�֘A
		{
			static const u16 boss_start_card_address[(8)] =/* �J�[�h�A�h���X��256��ނ𒴂����̂ōŒ�ł� u16 �͕K�v�B */
			{	/* �{�X�J�n�J�[�h�ԍ�(easy) */
				CARD_ADDRESS_00E_chrno_000, 	/* �`���m(?)*/	/* �G�L�X�g���p(boss0) */
				CARD_ADDRESS_00E_alice_000, 	/* �A���X */
				CARD_ADDRESS_00E_mima_000,		/* ���� */
				CARD_ADDRESS_00E_kaguya_000,	/* �P�� */
			//
				CARD_ADDRESS_00E_aya_000,		/* �� */
				CARD_ADDRESS_00E_pacheA_000,	/* �p�`�F */
				CARD_ADDRESS_00E_sakuya_000,	/* ��� */
				CARD_ADDRESS_00E_ph_000,		/* �t����(?)*/	/* �t�@���^�Y���p(boss7) */
			};
			card.address_set =
				#if (1)/*(�{�X���Ⴆ�΃X�y�J���Ⴄ)*/
				boss_start_card_address[boss_number]	/*(��ʒu)*/
				#endif
				#if (1)/*(��Փx�ʂɈႤ�X�y�J������)*/
				+ ((cg_VR20_game_difficulty)&0x03); /*(��Փx�ʃI�t�Z�b�g)*/
				#endif
			if (5==boss_number)/*(5==�p�`�F�̏ꍇ�A�v���C���[���ɈႤ�X�y�J������)*/	/*(�p�`�F�̏ꍇ�I�t�Z�b�g)*/
			{
				u8 aaa;
				aaa = ((((cg_game_select_player)&(4-1)))<<2);/* 4��(0 ... 3)�ɐ������Ă���A4�{����B(rank == E, N, H, L) */
				card.address_set += ((aaa<<3)+(aaa));/*(aaa *= 9; 9�{����Br36_gekiha �܂߃X�y�J�̈� 9 ��ށB)*/
			}
			h->boss_hp					= (my_card_resource[(card.address_set)].spell_life);	/* �S�̗̂̑� */	/*(�Ē�`�̕K�v����)*/
			/*(����̋K��l)*/
			card.limit_health			= (h->boss_hp);
		}
	}
			card.spell_used_number		= SPELL_00; 	/* �J�[�h�����I���t���O */
			card.address_temporaly		= (0);			/*(SPELL_08_rumia-1)*/ /*0*/
			#if (0)// (1)
		//	card_set_next();
			#else/*(���Ԃ�A����)*/
			card.boss_move_card_callback_void = NULL_keitai_void;/*(��b�I����Ɍ`�Ԃ��ݒ肳���̂ŁA����܂ŉ������Ȃ��B)*/
			#endif
	//
	spell_cpu_common_reset();//set_default_boss_clip();//
	//----[BOSS]
		cg_BOSS_DATA_33_kougeki_anime_count 		= (0);	/* �U���A�j���[�V�����p�J�E���^ / 0�ȉ��Ȃ�ړ��A�j���[�V���� */
		cg_BOSS_DATA_35_boss_base_state777			= (0);	/*ST_00*/	/*(�����l��0�ɂ���B) (-1) */
	/*---------------------------------------------------------
		�udat�Őݒ肵���{�X�o���ʒu�v����A
		�u�{�X�o���Œ�ʒu�v�܂ňړ�����B
		�����̏����ݒ���s���B
	---------------------------------------------------------*/
	// �o�����W�̏����ݒ�B
	VR06	= (BOSS_XP256);/*(t256()�`���A�{�X�o���Œ�ʒu)*/
	VR07	= (t256(16.0));/*(t256()�`���A�{�X�o���Œ�ʒu)*/
	//
	cg_BOSS_DATA_3a_center_x256 = h->center.x256;/*(���Ԃ�)*/
	cg_BOSS_DATA_3b_center_y256 = h->center.y256;/*(���Ԃ�)*/
	boss_set_new_position_void();/*(�U���ړ����W��ݒ�)*/
	// �{�X�e�N�X�`���ǂݍ���
	stage_boss_load_texture();
}
	#if (0)/*(�f�o�b�O)*/
	kanji_window_clear_line(0); 			/* �����E�B���h�E��1�s��(==0)�̓��e�������B */
	kanji_cursor_move_home_position();		/* �J�[�\����1�s��(==0)�ֈړ� */
	{
	//	ml_font[(0)].haikei 		= (ML_HAIKEI_02_JIKI_SPELL_CARD);/* [��/���@�J�[�h�p�w�i]����Ӕw�ion */
		cg.msg_time 				= (65536);	/* �� 18 �� */
		strcpy(my_font_text, "�{�X�A���[�h������B" "\n");
		kanji_color((7)|STR_CODE_NO_ENTER);
		kanji_draw();
	}
	#endif
	//
	#if (0)/*(�f�o�b�O)*/
	{	psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// ���p40��"�ő�\��������"
			"load stage: STAGE%d" "\\n"
			"�{�X�A���[�h�e�X�gOK�B", cg.game_now_stage);
	}
	#endif


/*---------------------------------------------------------
	�O���C���^�[�t�F�C�X�B
	-------------------------------------------------------
	�{�X���X�y�J��ς����ꍇ�A�������ă{�X�I�v�V�����������B
	�{�X�I�v�V�����A�����邩�ǂ����̔��f�B
---------------------------------------------------------*/
extern int check_boss_action(void)
{
	OBJ *src;
	src 				= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(�{�X�{��)*/
	//
	if (boss_action_04_speka_kougeki != src->callback_root_supeka)/*�{�X�A�X�y�J�ōU�����B�ȊO*/ /*(�J�[�h���ȊO)*/
	{
		/*(�U�����ȊO�Ȃ����)*/
		return (1);/*(����)*/
	}
		/*(�U�����Ȃ�����Ȃ�)*/
	return (0);/*(�����Ȃ�)*/
}



//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�����̒��{�X
	ToDo:
		(r39u1)�w��̖����w�́A���݂̌`�Ԃ͔p�~���A
		�g�����V�X�e���Ɉړ�����K�v������B
		-------------------------------------------------------
		���{�X->�g����
		�{�X->�g����
	-------------------------------------------------------
		"���[�~�A", 				"GFAIRY",
		"�d��2"(��),				"GFAIRY",
		"�d��1"(��), (�b��I)		"GFAIRY",
		"�d��3"(��), (�b��I)		"GFAIRY",
	-------------------------------------------------------
	; (72==64[������]+8[���[�~�A�e])
	; (79==64[������]+15[�V��e])		(�������̗d���݊�)�B
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�����B
---------------------------------------------------------*/

/*---------------------------------------------------------

---------------------------------------------------------*/
extern void spell_cpu_common_reset(void);
extern void spell_cpu_danmaku_callback_douchuu_init(void);
static void chuu_boss_taijyou_syori(void)
{
	/*(�t���O��߂�)*/
	cg_BOSS_DATA_32_chuu_boss_mode = (chuu_boss_00_mode_off);
	/*(�����e�p�e���R�[���o�b�N��߂�)*/
	spell_cpu_common_reset();/*(�����U�R/�{�X/�������{�X[���ʕ���])*/
	spell_cpu_danmaku_callback_douchuu_init();/*(�����U�R�e�p�ɒe���R�[���o�b�N������������)*/
	//hold_game_mode_off();
}
/*
+0
	[�ޏ�ړ�����]
	(CHUU_BOSS_JIKAN_01_0256-1);	(�ޏꏈ���J�n)
+0256
	[���Ԑ؂�̏���]
	(CHUU_BOSS_JIKAN_02_0272-1);	(���Ԑ؂�̏����J�n)
+0272
	[�J�[�h���I���܂őҋ@����]
	(CHUU_BOSS_JIKAN_03_1792-1);	(�J�[�h���I���܂őҋ@�����J�n)
+1792
	[�ォ��o��ړ�����]
	(CHUU_BOSS_JIKAN_04_2048-1);	(�ォ��o��ҋ@�����J�n)
+2048
*/
//extern OBJ_CALL_FUNC(boss_r36_yuudou);/* �U���ړ�/�U���v�Z */
extern OBJ_CALL_FUNC(chuu_boss_zako_anime_type05);
extern OBJ_CALL_FUNC(move_chuu_boss)
{
			#if 0/*(�f�o�b�O)*/
			cg_game_score = src->jyumyou;/*[ �X�R�A���Ƀf�o�b�O�l�\�� ]*/
			#endif
	chuu_boss_zako_anime_type05(src);/* �A�j���[�V���� */
	// [�ޏ�ړ�����]
	if (CHUU_BOSS_JIKAN_01_0256 > src->jyumyou) /* �u��֑ޏ�v(256[count]==��4�b) */
	{
		/* �ړ��������W�ɓ��������͂ݏo������A�����Ƃ���B */
		if (cg_BOSS_DATA_34_toutatu_wariai256 <= t256(0))
	//	if (0 > (cg_BOSS_DATA_3b_center_y256+t256(55.0)))/* 55�h�b�g�Ƃ���(�����_�A�c�̃T�C�Y) */
	//	if (0 > cg_BOSS_DATA_3b_center_y256)/* �ȗ��� */
		{
			src->jyumyou						= JYUMYOU_NASI;
			if (JYUMYOU_NASI < src->YOKAI1_DATA_s2->jyumyou)/* �w��̖����w������Ώ����B */
			{
				src->YOKAI1_DATA_s2->jyumyou	= JYUMYOU_NASI;
			}
			chuu_boss_taijyou_syori();/* �ޏꏈ�� */
		}
	}
	// [���Ԑ؂�̏���]
	else
	if ((CHUU_BOSS_JIKAN_02_0272) > src->jyumyou)/* [���Ԑ؂�̏���] */
//	if ((CHUU_BOSS_JIKAN_01_0256) == src->jyumyou)	/* �u�J�[�h���s��~�ɂ���v */
	{
			src->jyumyou = (CHUU_BOSS_JIKAN_01_0256-1);/*(�ޏꏈ���J�n)*/
			card.spell_used_number				= (SPELL_00);/*(�J�[�h���s��~�ɂ���)*/
		//	cg_BOSS_DATA_3b_center_y256 					-= t256(1.5);	/*fps_factor*/
		#if 1
		/*(���ݍ��W)*/
	//	cg_BOSS_DATA_3a_center_x256/*(�X�y�JCPU�������W[�{�X�p])*/ = gcmd_obj_2nd->center.x256;/*(�X�y�JCPU�O�����W[���{�X�p])*/
	//	cg_BOSS_DATA_3b_center_y256/*(�X�y�JCPU�������W[�{�X�p])*/ = gcmd_obj_2nd->center.y256;/*(�X�y�JCPU�O�����W[���{�X�p])*/
		/*(�o��\�茻�ݍ��W)*/
		VR06	= t256(100.0);
		VR07	= t256(-30.0);
		boss_set_new_position_void();
		#endif
	}
	/*([���Ԑ؂�̈ʒu]���Ԑ؂�̏ꍇ�A�u�J�[�h���s��~�ɂ���v)*/
	/*(�ő��8�b(512[count])�ŃX�y�J�������f)*/
	// [�J�[�h���I���܂őҋ@����]
	else
	if ((CHUU_BOSS_JIKAN_03_1792) > src->jyumyou)	/* �u�J�[�h���I���܂őҋ@�v(512[count]==��8�b) */
	{
		/*(�J�[�h�ݒ莞�Ԃ�512�����̏ꍇ�͎��R�ɏI������B���̏ꍇ�A[���Ԑ؂�̈ʒu]�܂Ŏ��Ԃ�i�߂�B)*/
		if (SPELL_00 == card.spell_used_number)
		{
			src->jyumyou = (CHUU_BOSS_JIKAN_02_0272);
		}
	//	if (SPELL_00 != card.card_number)
	//	{
	//		src->jyumyou = (CHUU_BOSS_JIKAN_02_0272);/* �u�J�[�h���s��~�ɂ���v�֐ݒ�B */
	//	}
	}
	else
//	if ((512) > src->jyumyou)	/* �u�ォ��o��v(128[count]==��2�b) */
	{
//(?)		cg_BOSS_DATA_3b_center_y256 				+= t256(2.0);	/*fps_factor*/
		/* �ړ��������W�ɓ��������͂ݏo������A�����Ƃ���B */
		if (cg_BOSS_DATA_34_toutatu_wariai256 <= t256(0))
		{
			#if 1/*(�Ă��ƁB�O�ɏo��)*/
			/*(���ݍ��W)*/
		//	cg_BOSS_DATA_3a_center_x256/*(�X�y�JCPU�������W[�{�X�p])*/ = gcmd_obj_2nd->center.x256;/*(�X�y�JCPU�O�����W[���{�X�p])*/
		//	cg_BOSS_DATA_3b_center_y256/*(�X�y�JCPU�������W[�{�X�p])*/ = gcmd_obj_2nd->center.y256;/*(�X�y�JCPU�O�����W[���{�X�p])*/
			/*(�o��\�茻�ݍ��W)*/
			VR06	= cg_BOSS_DATA_3a_center_x256;
			VR07	= cg_BOSS_DATA_3b_center_y256+t256(32.0);
			boss_set_new_position_void();
			#endif
			src->jyumyou			= (CHUU_BOSS_JIKAN_03_1792-1);/*(�J�[�h���I���܂őҋ@�����J�n) �u�J�[�h���I���܂őҋ@�v�֐ݒ�B */
			card.spell_used_number	= card.address_temporaly;	/* �J�[�h���Z�b�g */		/* "�d��2"&"���[�~�A"��p */
			card_maikai_init(src);/*(r35-, �J�[�h�̏������B�J�[�h���ς��Ɩ���s���K�v������)*/
		}
	}
	//
	#if 1/* ���݂̎��������́A����ܗǂ��Ȃ��C������B */
	/* �|�����ꍇ�w��̖����w�������Ă��邪�A���������ꍇ�w��̖����w������B */
	if (JYUMYOU_NASI < src->YOKAI1_DATA_s2->jyumyou)/* �w��̖����w������΁B */
	{
		src->YOKAI1_DATA_s2->center.x256		= cg_BOSS_DATA_3a_center_x256;	/*fps_factor*/
		src->YOKAI1_DATA_s2->center.y256		= cg_BOSS_DATA_3b_center_y256;	/*fps_factor*/
		//
	//	src->YOKAI1_DATA_s2->rotationCCW1024 += (3);
	//	mask1024(src->YOKAI1_DATA_s2->rotationCCW1024);
		src->YOKAI1_DATA_s2->rotationCCW65536 += (3<<6);
		mask65536(src->YOKAI1_DATA_s2->rotationCCW65536);
	}
	#endif
	//
	if (CHUU_BOSS_JIKAN_02_0272 > src->jyumyou)
	{
		;	/* ��֑ޏ� */
	}
	else
	{
		card_generate(src);/* �X�y����CPU���s���A�J�[�h���P�t���[����������B */
	}
	/*(�`��p���W�̐����Br41-)*/
	/*(�X�y�JCPU�ňꊇ�Ǘ����Ă���̂ŃI�u�W�F�N�g���W�́A�X�y�JCPU�̊O���ɒu��)*/
	src->center.x256/*(�X�y�JCPU�O�����W[���{�X�p])*/ = cg_BOSS_DATA_3a_center_x256;/*(�X�y�JCPU�������W[�{�X�p])*/
	src->center.y256/*(�X�y�JCPU�O�����W[���{�X�p])*/ = cg_BOSS_DATA_3b_center_y256;/*(�X�y�JCPU�������W[�{�X�p])*/
	//
	boss_r36_yuudou(src);
}
