
#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�Q�[���J�n���̓�Փx/�v���C���[�I��
	-------------------------------------------------------
	[��Փx�I�����j���[]
	[�v���C���[�I�����j���[]
---------------------------------------------------------*/

#include "kanji_system.h"
#include "111_my_file.h"/*(my_file_common_name)*/


	/*(Gu�̏ꍇ�A��b�X�v���C�g���g��)*/
#include "kaiwa_sprite.h"
#include "../draw/gu_draw_screen.h"

/*---------------------------------------------------------
	player select�p
---------------------------------------------------------*/

#define BASE_SP_BG_PNG		(MAX_08_PLAYER*0)
#define BASE_SP_ST_PNG		(MAX_08_PLAYER*1)
#define BASE_SP_PNG_MAX 	(MAX_08_PLAYER*2)

/*---------------------------------------------------------
	�K���ǂ������B
---------------------------------------------------------*/
enum
{
	spec_message_00_SELECT_PLAYER = 0,
	spec_message_01_SELECT_RANK,
};
//		 if (spec_message_00_SELECT_PLAYER==set_mode)	{	... 	}
//	else if (spec_message_01_SELECT_RANK==set_mode) 	{	... 	}

/*---------------------------------------------------------
	��Ԃ����b�Z�[�W�\���B
	-------------------------------------------------------
	[��Փx�I�����j���[]
	[�v���C���[�I�����j���[]
---------------------------------------------------------*/
#if defined(USE_LANGUAGE_ENGLISH)
	#define STR_MSG_TOTAL_SPEED 	"   Moving Speed: "
	#define STR_MSG_TOTAL_ATTACK	"   Attack Range: "
	#define STR_MSG_TOTAL_POWER 	"Offensive Power: "
#else
	#define STR_MSG_TOTAL_SPEED 	"�ړ����x"
	#define STR_MSG_TOTAL_ATTACK	"�U���͈�"
	#define STR_MSG_TOTAL_POWER 	"�U���́@"
#endif
static void draw_spec_message(u32 set_mode)
{
	kanji_window_all_clear();				/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
	static const char *const_player_spec_str[(8)/*(8�l)*/+(4)/*(4��Փx)*/][(2)/*(������+������)*/] =
	{	/*"�j�ޏ��̍U���͂̉���́A���������C�����邯�Ǔ\����Ȃ���Ύア�B"*/
		{	JAPAN("�y���̑f�G�țޏ�", "Lovely shrine maiden of paradise")"\\n"
			JAPAN("���� �얲 (�아)",			"Hakurei Reimu A (spirit card)")"\\n"
			JAPAN("�z�[�~���O�A�~�����b�g", 	"Homing Amulet")"\\n"
			JAPAN("���z����",					"Seal Reverie")"\\n",
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 0 �얲 A(�아)
		{	JAPAN("�y���̑f�G�țޏ�", "Lovely shrine maiden of paradise")"\\n"
			JAPAN("���� �얲 (����)",			"Hakurei Reimu B (dream card)")"\\n"
			JAPAN("�����j", 					"Demon sealed Needle")"\\n"
			JAPAN("���z���E",					"Reverie Barrier")"\\n",
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 1 �얲 B(����)
		{	JAPAN("���ʂ̍����p�t", "Standard Necromancer")"\\n"
			JAPAN("���J ������ (����)", 		"Kirisame Marisa A (devil card)")"\\n"
			JAPAN("�}�W�b�N�~�T�C��",			"Magic Missile")"\\n"
			JAPAN("�X�^�[�_�X�g�����@���G", 	"Stardust Reverie")"\\n",
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 2 ������ A(����)
		{	JAPAN("�Õ��Ȗ��@�g��", "Retrospective Magician")"\\n"
			JAPAN("���J ������ (����)", 		"Kirisame Marisa B (lovely card)")"\\n"
			JAPAN("�C�����[�W�������[�U�[", 	"Illusion Laser")"\\n"
			JAPAN("�}�X�^�[�X�p�[�N",			"Master Spark")"\\n",
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 3 ������ B(����)
		{	JAPAN("�z���S", "Vampire")"\\n"
			JAPAN("���~���A �X�J�[���b�g",		"Remilia Scarlet")"\\n"
			JAPAN("�i�C�g�_���X",				"Night Dance")"\\n"
			JAPAN("�s���u���b�h", 			"All Night Blood")"\\n",// �s���i�ӂ₶�傤�j�́A�����̎R���Ȃɂ������Ƃ����Ñ�s�s�B��������o���Ƃ��ꂽ���߁A���̖�������B
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 4 ���~���A(����)
		{	JAPAN("����̖S��", "Ghost of Peaceful land")"\\n"// ����̍� �����̉��邪���̒��Ō����Ƃ����A���׎��R�Ŏ��܂闝�z�̍��B�����̍��B
			JAPAN("���s�� �H�X�q",				"Saigyouzi Yuyuko")"\\n"
			JAPAN("�Ί݂̗U��", 				"Invitation of the other side ...")"\\n"
			JAPAN("�M���X�g���h���[��", 		"Ghastly Dream")"\\n",
			STR_MSG_TOTAL_SPEED  "������\\n"
			STR_MSG_TOTAL_ATTACK "������\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 5 �H�X�q(����)
		{	JAPAN("�Ώ�̕X��", "Ice fairy on the lake")"\\n"
			JAPAN("�`���m (�X��)",				"Chrno A (ice card)")"\\n"
			JAPAN("�A�C�V�N���j�[�h��", 		"Icicle Needle")"\\n"
			JAPAN("�A�C�V�N���X�g���C�N",		"Icicle Strike")"\\n",
			STR_MSG_TOTAL_SPEED  "��������\\n"
			STR_MSG_TOTAL_ATTACK "�H�H�H\\n"
			STR_MSG_TOTAL_POWER  "������",	}, // No. 6 �`���m A(�X��)
		{	JAPAN("�Ώ�̕X��", "Ice fairy on the lake")"\\n"
			JAPAN("�`���m (�H��)",				"Chrno Qute (qute card)")"\\n"
			JAPAN("���A�C�X�\\�[�h",			"��Ice Sword")"\\n"
			JAPAN("�Ⓚ��+99999",				"Blizzard Blade add 99999 levels")"\\n",
			STR_MSG_TOTAL_SPEED  "����������\\n"
			STR_MSG_TOTAL_ATTACK "�H�H�H\\n"
			STR_MSG_TOTAL_POWER  "�H�H�H",	}, // No. 7 �`���m Q(�H�n)
		//
		{	"Easy\\n"
			JAPAN("�ȒP���ǂ����͐l�ɂ��B",	"So easily be only Select")"\\n",
			JAPAN("�G���f�B���O����", "NOT contains good ending")"\\n"
			JAPAN("(�S�T��)", "(5 stages)"), }, // No. 0 easy
		{	"Normal\\n"
			JAPAN("���ʂȐl�ɂ̓n�[�h�B",		"Normally when Hard.")"\\n",
			JAPAN("(�S�U��)", "(6 stages)"), }, // No. 1 normal
		{	"Hard\\n"
			JAPAN("�n�[�h�Ȑl�ɂ͕��ʁB",		"Hardest when Normally.")"\\n",
			JAPAN("(�S�U��)", "(6 stages)"), }, // No. 2 hard
		{	"Lunatic\\n"
			JAPAN("�����K�v�B",				"No doubt just Lunatic.")"\\n",
			JAPAN("(�S�U��)", "(6 stages)"), }, // No. 3 lunatic
		//
		// 1�ߖ�(��)													// 2�ߖ�(���F)
	};/* �X�� == Icicle == �A�C�V�N�� */
	//
	const u32 aaa = (spec_message_00_SELECT_PLAYER==set_mode)?((unsigned)cg_game_select_player):((8)+((unsigned)cg_VR20_game_difficulty));
	// ���������߂�B												// �F�����߂�B 				// �`�悷��B
	strcpy(my_font_text, (char*)const_player_spec_str[((aaa))][0]); kanji_color(7);/*(���F)*/		kanji_draw();
	strcpy(my_font_text, (char*)const_player_spec_str[((aaa))][1]); kanji_color(14);/*(���F)*/		kanji_draw();
	strcpy(my_font_text, (spec_message_00_SELECT_PLAYER==set_mode)?
		("\\n"JAPAN("�N���s���́H", "Who are you going?")):
		("\\n\\n\\n\\n\\n"JAPAN("���[�h��I�����Ă�", "Select difficulty"))
	);
	kanji_color(9);/*(��/���F)*/	kanji_draw();
}
// "�ȒP�Ɍ����΁A�{���Q�ł��B"
// "�ȒP�ɂ͍U���ł��Ȃ��B"
// "���ʂɌ����΁A����ł��B"
// "���d�������΁A�������ł��B"
// "�����݂Ɍ����΁A�������ł��B"

#define SOZAI_HABA_184 (185-1)		/* �f�ޕ�184[�h�b�g] */
#define SOZAI_TATE_064 ( 64-1)		/* �f�ޕ� 63[�h�b�g] */

/*---------------------------------------------------------
	���[�J���g�p�ϐ��B
---------------------------------------------------------*/

static int sp_scale256; 	 /*(���@��I�����Ȃ����ƁA�m�肷��܂ŁA����Ă���X���W)*/
static int sp_diff256;
static int is_turn_right;
static SDL_Surface *difficulty_select_fg0_surface;
static SDL_Surface *player_select_bg0_surface;
static SDL_Surface *player_select_bg2_surface;

/*(�L���b�V���ɂ����ƁA�A���t�@���o�Ȃ��B)*/
#define DFF_USE_KETM_IMAGE_CHACHE (0)

/*---------------------------------------------------------
	�����\���ړ�����
---------------------------------------------------------*/
static int kanji_set_x_position;
static int kanji_move_x_position;
static void move_kanji(void)
{
	const int sabun = (kanji_move_x_position-kanji_set_x_position);
	if (0 != sabun)
	{
		const int value = (32 - __builtin_allegrex_clz(sabun - 1));
		if (0 > sabun)
				{kanji_move_x_position += value;}
		else	{kanji_move_x_position -= value;}
	}
	int i;
	for (i=0; i<7; i++)
	{
		ml_font[i].x	= (kanji_move_x_position);/* X�ʒu */
	}
}


/*---------------------------------------------------------
	[�v���C���[�I�����j���[]
---------------------------------------------------------*/
static void player_select_08_load(void);/*(�錾���K�v)*/
static void player_select_10_select(void)/* [�I��] */
{
	cg.msg_time = byou60(5);/* �K�v */	/* �� 5 �b */
	if (0==psp_pad.pad_data_alter)/* ����������������ĂȂ������ꍇ�ɃL�[�`�F�b�N(���쏀��) */
	{
		if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL)) /* �����E���V���b�g���L�����Z���̂��Âꂩ */
		{	/* ��Ԃ��ς��ꍇ��*/
			/* ��Ԃ��ς��ꍇ�A������ SDL�T�[�t�F�C�X���J�� ���Ȃ��ƃ������[���[�N����� */
			#if (1==USE_KETM_IMAGE_CHACHE)
			unloadbmp_by_surface(player_select_bg0_surface);	// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��Bplayer_select_bg0_surface = NULL;
			unloadbmp_by_surface(player_select_bg2_surface);	// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��Bplayer_select_bg2_surface = NULL;
			#else
			SDL_FreeSurface(player_select_bg0_surface); 		// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��B
			player_select_bg0_surface = NULL;
			SDL_FreeSurface(player_select_bg2_surface); 		// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��B
			player_select_bg2_surface = NULL;
			#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
		//
			if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT)/*�����E�̗���*/) /* ���E�{�^������ */
			{
				is_turn_right = (psp_pad.pad_data & PSP_KEY_RIGHT)?1:0;/* �E�Ȃ�1, ���Ȃ�0 */
				voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
				cg.main_call_func = player_select_08_load;	/* [load] */	/*(�߂�)*/
			}
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
			{
				cg.msg_time = (0);/* �K�v */
				{
					/* ��Ԃ��ς��ꍇ�A������ SDL�T�[�t�F�C�X���J�� ���Ȃ��ƃ������[���[�N����� */
					#if (1==DFF_USE_KETM_IMAGE_CHACHE)
					unloadbmp_by_surface(difficulty_select_fg0_surface);	// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��Bdifficulty_select_fg0_surface = NULL;
					#else
					SDL_FreeSurface(difficulty_select_fg0_surface); 		// �L���b�V���ɓ����Ă�̂� NULL �ɏo���Ȃ��B
					difficulty_select_fg0_surface = NULL;
					#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
				}
				voice_play_menu(VOICE01_MENU_OK, TRACK01_MENU01);/* �e�L�g�[ */
				if (0!=cg.game_practice_mode)
				{	/* �v���N�e�B�X���[�h�̏ꍇ */
					cg.main_call_func = stage_select_menu_start; /* �X�e�[�W�I�����j���[�̊J�n */
				}
				else/* �v���N�e�B�X���[�h�ȊO�̏ꍇ */
				{
					cg.main_call_func = stage_first_init;			/* �Q�[���J�n */
				}
			}
			else
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
			{
				cg.msg_time = (0);/* �K�v */
				voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* ���@���ɉ��́A�Ȃ�ׂ��d�˂Ȃ� */
				/* ��Փx�I�����j���[�ɖ߂� */
				cg.main_call_func = rank_select_menu_start;	/* ��Փx�I�����j���[��(�߂�) */
			}
		}
	}
	move_kanji();
}


/*---------------------------------------------------------

---------------------------------------------------------*/
static int toutatu_wariai;

/* �o�ꑬ�x�́A�������B */
	#define SPEED_04_FADE_IN	(4) 	/* 4*FPS_MENU_FACTOR */
/* �ޔ𑬓x�́A�����B */
	#define SPEED_06_FADE_OUT	(6) 	/* 6*FPS_MENU_FACTOR */


static int move_mode;
/*(�v4���==3���+1���)*/
enum
{
	MODE_00_TOUJYOU = 0,			/*(move_mode[0]: ���j���[�����o�ꒆ)*/
	MODE_01_MENU_SELECT,			/*(move_mode[1]: ���j���[�I��)*/
	MODE_02_TAIJYOU_EASY,			/*(move_mode[2]: ���j���[�����ޔ�)*/
	MODE_03_TAIHI_ITI_EASY, 		/*(+�ޔ��ʒu�̐�ǂݕ�)*/
	MODE_04_TAIJYOU_NORMAL, 		/*(move_mode[2]: ���j���[�����ޔ�)*/
	MODE_05_TAIHI_ITI_NORMAL,		/*(+�ޔ��ʒu�̐�ǂݕ�)*/
	MODE_06_TAIJYOU_HARD,			/*(move_mode[2]: ���j���[�����ޔ�)*/
	MODE_07_TAIHI_ITI_HARD, 		/*(+�ޔ��ʒu�̐�ǂݕ�)*/
	MODE_08_TAIJYOU_LUNATIC,		/*(move_mode[2]: ���j���[�����ޔ�)*/
	MODE_09_TAIHI_ITI_LUNATIC,		/*(+�ޔ��ʒu�̐�ǂݕ�)*/
	MODE_10_MAX_JYOUTAI/*(�ő�l)*/
};
typedef struct
{
	s16 x_offset[MODE_10_MAX_JYOUTAI];
	s16 y_offset[MODE_10_MAX_JYOUTAI];

} MENU222_RESOURCE;
static const MENU222_RESOURCE my_menu_resource[MODE_10_MAX_JYOUTAI] =
{
// mode:				   [easy-------]   [normal------]  [hard--------]  [lunatic-----]
// mode:	[0] 	[1] 	[2e]	[2+1]	[4n]	[4+1]	[6h]	[6+1]	[8l]	[8+1]
	{	{	512,	128,	128,   (16),	128,	  0,	128,	  0,	128,	  0,  },
		{	-44,	 16,	 16,  (216),	 16,	272,	 16,	272,	 16,	272,  }, }, // <EASY>
	{	{	512,	128,	128,	  0,	128,   (16),	128,	  0,	128,	  0,  },
		{	 50,	 80,	 80,	272,	 80,  (216),	 80,	272,	 80,	272,  }, }, // <NORMAL>
	{	{	512,	128,	128,	  0,	128,	  0,	128,   (16),	128,	  0,  },
		{	174,	144,	144,	272,	144,	272,	144,  (216),	144,	272,  }, }, // <HARD>
	{	{	512,	128,	128,	  0,	128,	  0,	128,	  0,	128,   (16),  },
		{	268,	208,	208,	272,	208,	272,	208,	272,	208,  (216),  }, }, // <LUNATIC>
};


/*---------------------------------------------------------
	��Փx�^�O����`��
---------------------------------------------------------*/
static void draw_tag_number(u32 tag_number)
{
	int move_rate256;
	move_rate256	= toutatu_wariai;
	move_rate256	= psp_min(move_rate256, 256);
	move_rate256	= psp_max(move_rate256, 0);
	#if (1)/* �񓙕��l�̌v�Z */
	{
		u32 i_rate65536;
		i_rate65536 	= (move_rate256 << 8);
	//	i_rate65536 	= (int)(vfpu_ease_in_out(t)*256.0);
		i_rate65536 	= (int)(vfpu_ease_in_out65536(i_rate65536));	/* t65536�̓����J�E���^�l���g���A�񓙕��ɂȂ�悤�l���C������B
		�񓙕��̕����́uease_in_out�v����́A�n�߂ƍŌオ�������ŊԂ������Ƃ����z�������B */
		move_rate256	= (i_rate65536 >> 8);
	}
	#endif
	{
		SDL_Rect ds;
		ds.x	= (0);
		ds.y	= (tag_number << 6);
		ds.w	= (SOZAI_HABA_184);/* �f�ޕ�184[�h�b�g] */ /* �f�ޕ�191[�h�b�g] */
		ds.h	= (SOZAI_TATE_064);/* �f�ޕ� 63[�h�b�g] */
		//
		SDL_Rect dr;
		SDL_Surface *src;
		src 	= difficulty_select_fg0_surface;
		dr.w	= (src->w);
		dr.h	= (63/*src->h*/);
		#if (1)/*(���B�������l�����āA��������B)*/
		VR04	= ((my_menu_resource[tag_number].x_offset[move_mode  ])<<8);/*(�����ʒu[A]t256()�`��)*/
		VR05	= ((my_menu_resource[tag_number].y_offset[move_mode  ])<<8);/*(�����ʒu[A]t256()�`��)*/
		VR06	= ((my_menu_resource[tag_number].x_offset[move_mode+1])<<8);/*(�����ʒu[B]t256()�`��)*/
		VR07	= ((my_menu_resource[tag_number].y_offset[move_mode+1])<<8);/*(�����ʒu[B]t256()�`��)*/
		REG_11_GOUSEI_WARIAI256 	= move_rate256;/*(��������t256()�`��)*/
		CPU_CALL(multiprex_rate_vector);/*(�j�󃌃W�X�^�����̂Œ���)*/
		#endif
		// ���̎��_�ŁA
		// VR06: �����l
		// VR07: �����l
		// -----------------------
	//	menu_item_my_obj[i].x256 = (VR06)+(VR08);		// �������h�炷�B
	//	menu_item_my_obj[i].y256 = (VR07);// +(VR09);	// �c�͗h�炳�Ȃ��B(== y offset �͎g��Ȃ��B)
		#if (1)/*(�\���ʒu)*/
		dr.x	= ((VR06)>>8);/*(X�ʒu)*/
		dr.y	= ((VR07)>>8);/*(Y�ʒu)*/
	//	dr.x	= (set_x_offset);
	//	dr.y	= (set_y_offset);
		#endif
		{
			int set_alpha256;
			if ((tag_number==((unsigned)cg_VR20_game_difficulty)))/*(�I������Ă���ꍇ)*/
			{
				dr.x -= (16);/*(���ɂ��炷)*/
				dr.y -= ( 8);/*(��ɂ��炷)*/
				set_alpha256 = (255);/*(�������Ȃ�)*/
			}
			else/*(�I������Ă��Ȃ��ꍇ)*/
			{
				/*(��ʒu����A���炳�Ȃ�)*/
				set_alpha256 = (64);// (127);/*(����������)*/
			}
		//	SDL_SetColorKey(src, (SDL_SRCCOLORKEY), 0x00000000);
			SDL_SetAlpha(src, SDL_SRCALPHA, set_alpha256);/*(�������ݒ�A�]�����摜�̔��������L��)*/
		}
		PSPL_UpperBlit(src, &ds, cg.sdl_screen[SDL_00_VIEW_SCREEN], &dr);/*(���z��ʂ֕`��)*/
	}
}


/*---------------------------------------------------------
	��Փx�^�O���l�`��
---------------------------------------------------------*/
static void move_tag_4(void)/* [�`��444] */
{
	int i;
	for (i=0; i<4; i++)
	{
		draw_tag_number(i);
	}
}


/*---------------------------------------------------------
	[�v���C���[�I�����j���[]
---------------------------------------------------------*/
static void player_select_09_move_draw(void)/* [�`��1] */
{
//	sp_scale256 -= (18);	// 18 == 255/14[��]�B14���`�悷��B/*(�Â��z)*/
//	sp_scale256 -= (15);	// 15 == 255/17[��]�B17���`�悷��B [�����G��PSPL�`��] + [BG��PSPL�`��]�̏ꍇ�̐ݒ�l(15)�B(-r35u1)
	sp_scale256 -=	(8);	//	8 == 255/32[��]�B32���`�悷��B [�����G��Gu�`��] + [BG��PSPL�`��]�̏ꍇ�̐ݒ�l(15)�B(r35u2-)
	if (0 > sp_scale256)
	{
		sp_scale256 = (0);
		cg.main_call_func = player_select_10_select;/* [�I��] */
	}
	SDL_SetAlpha(player_select_bg0_surface, SDL_SRCALPHA, (255-sp_scale256) );
	PSPL_UpperBlit(player_select_bg2_surface, NULL, cg.sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	PSPL_UpperBlit(player_select_bg0_surface, NULL, cg.sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	/* �v���C���[(1&2) / �w�i(1&2) / �`�� */
	{
		int aaa;
		/*(Gu�̏ꍇ�A��b�X�v���C�g���g��)*/
		#define PLAYER_OBJ_LOCATE_X 	(256-32)		/* cx256(r35) �f��[256x256] */
		#define PLAYER_OBJ_LOCATE_Y 	(8) 			/* cy256(r35) �f��[256x256] */
		kaiwa_sprite[0].center.y256 = ((PLAYER_OBJ_LOCATE_Y) << 8);
		sp_diff256 += (sp_scale256);
		aaa = (((sp_diff256)) >> 8)-16;
		if (is_turn_right)	{aaa = (-(aaa));}
		kaiwa_sprite[0].center.x256 = ((PLAYER_OBJ_LOCATE_X) << 8) + (aaa << 8);
		kaiwa_sprite[0].color32 = ((	sp_scale256) << 24) | (0x00ffffff);/*(����)*/
		//
		kaiwa_sprite[1].center.y256 = ((PLAYER_OBJ_LOCATE_Y) << 8);
		sp_diff256 += (sp_scale256);
		aaa = ((sp_diff256 >> 8)-16);
		if (1-is_turn_right)	{aaa = (-(aaa));}
		kaiwa_sprite[1].center.x256 = ((PLAYER_OBJ_LOCATE_X) << 8) + (aaa << 8);
		kaiwa_sprite[1].color32 = ((255-sp_scale256) << 24) | (0x00ffffff);/*(����)*/
	}
	/* ��Փx�^�O��`�� */
	move_tag_4();
	#if 0
	draw_tag_number(cg_VR20_game_difficulty);
	#endif
	move_kanji();
}


/*---------------------------------------------------------
	�I���v���C���[�摜�Ɣw�i�̖��O�����߂�B
---------------------------------------------------------*/
static void set_file_name(u8 is_pl)
{
	strcpy(my_file_common_name, (char*)DIRECTRY_NAME_DATA_STR "/select/" "pl00.png");
	my_file_common_name[DIRECTRY_NAME_DATA_LENGTH+(10)] = '0'+(cg_game_select_player);
	my_file_common_name[DIRECTRY_NAME_DATA_LENGTH+(11)] = '0'+(is_pl);
}


/*---------------------------------------------------------
	[�v���C���[�I�����j���[]�I���v���C���[�摜�Ɣw�i�����[�h�B
---------------------------------------------------------*/
static MAIN_CALL_FUNC(player_select_08_load)/* [load] */
{
	cg_game_select_player &= (0x07);
	//
	set_file_name(0);	strcpy(&my_resource[TEX_09_TACHIE_L+0].file_name[0], (&my_file_common_name[0]) );
						kaiwa_sprite[0].draw_flag = (1);	/* �`�悷��B */
						psp_load_texture(TEX_09_TACHIE_L+0);
	set_file_name(1);
	#if (1==USE_KETM_IMAGE_CHACHE)
	player_select_bg2_surface = load_chache_bmp();
	#else
	player_select_bg2_surface = IMG_Load(my_file_common_name);
	#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
	//
	if (0==is_turn_right)
			{cg_game_select_player--;}
	else	{cg_game_select_player++;}
	cg_game_select_player &= 0x07;
	//
	set_file_name(0);	strcpy(&my_resource[TEX_09_TACHIE_L+1].file_name[0], (&my_file_common_name[0]) );
						kaiwa_sprite[1].draw_flag = (1);	/* �`�悷��B */
						psp_load_texture(TEX_09_TACHIE_L+1);
	set_file_name(1);
	#if (1==USE_KETM_IMAGE_CHACHE)
	player_select_bg0_surface = load_chache_bmp();
	#else
	player_select_bg0_surface = IMG_Load(my_file_common_name);
	#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
	//
	sp_scale256 	= (255);
	sp_diff256		= (0);
	//
	kanji_set_x_position = (24);/*(�����ړ�����W�ݒ�)*/
	draw_spec_message(spec_message_00_SELECT_PLAYER);	// [�v���C���[�I��]��Ԃ����b�Z�[�W�\���B
	cg.main_call_func = player_select_09_move_draw;
}


/*---------------------------------------------------------
	�L�����Z������炵�āA�^�C�g�����j���[�ֈړ��B
	���ʃT�u�B(�O���̂�����������Ă΂��)
---------------------------------------------------------*/
extern void menu_cancel_and_voice(void)
{
	voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* ���@���ɉ��́A�Ȃ�ׂ��d�˂Ȃ� */
	cg.main_call_func = title_menu_start;	/* �^�C�g�����j���[�ֈړ� */
}


/*---------------------------------------------------------
	[��Փx�I�����j���[:�����ޔ�]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_07_moji_taihi)/* [�����ޔ�] */
{
	toutatu_wariai += (SPEED_06_FADE_OUT);
	if (255 <= toutatu_wariai)
	{
		toutatu_wariai = (0);
		move_mode++;// (3=2+1=easy, 5=4+1=normal, 7=6+1=hard, 9=8+1=lunatic)�ɂȂ�B
		cg.main_call_func = player_select_08_load;
	}
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
	move_tag_4();
	/*(?)*/move_kanji();/*(����Ӗ��������ۂ�)*/
}


/*---------------------------------------------------------
	[��Փx�I�����j���[]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_04_initialize_value);/*(�錾���K�v)*/
static MAIN_CALL_FUNC(rank_select_06_select)/* [�I��] */
{
	cg.msg_time = byou60(5);/* �K�v */	/* �� 5 �b */
	if (0==psp_pad.pad_data_alter)/* ����������������ĂȂ������ꍇ�ɃL�[�`�F�b�N(���쏀��) */
	{
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL)) /* �����E���V���b�g���L�����Z���̂��Âꂩ */
		{	/* ��Ԃ��ς��ꍇ��*/
		//
			if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN)/*�ォ���̗���*/ ) /* �㉺�{�^������ */
			{
				if (psp_pad.pad_data & PSP_KEY_UP)
						{cg_VR20_game_difficulty--; cg_VR20_game_difficulty = psp_max(cg_VR20_game_difficulty, (0)	 );}	/* ���j���[��Œ�~ */
				else	{cg_VR20_game_difficulty++; cg_VR20_game_difficulty = psp_min(cg_VR20_game_difficulty, (4-1) );}	/* ���j���[���Œ�~ */
				voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
				cg.main_call_func = rank_select_04_initialize_value; /* [load] */	/*(�߂�)*/
			}
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
			{
				cg.msg_time = (0);/* �K�v */
				voice_play_menu(VOICE01_MENU_OK, TRACK01_MENU01);/* �e�L�g�[ */
				/* �ʏ�^�v���N�e�B�X�A�Q�[���J�n */
				// static void player_opt_init(void)�z���B�Ȃ�
				{
					is_turn_right = 0;/* �K�v */
					(cg_game_select_player)++;/* �v���O����player_select_work()�̓s���㒲�� */	/*player_select_work()::[init]*/
				}
				cg.main_call_func = rank_select_07_moji_taihi;
				move_mode++;// (2)�ɂȂ�B
				move_mode += ((cg_VR20_game_difficulty)<<1);// (2=easy, 4=normal, 6=hard, 8=lunatic)�ɂȂ�B
			}
			else
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
			{
				cg.msg_time = (0);/* �K�v */
				{
					/* ��Ԃ��ς��ꍇ�A������ SDL�T�[�t�F�C�X���J�� ���Ȃ��ƃ������[���[�N����� */
				//	unloadbmp_by_surface(difficulty_select_fg0_surface);	// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��Bdifficulty_select_fg0_surface = NULL;
					/* ��Ԃ��ς��ꍇ�A������ SDL�T�[�t�F�C�X���J�� ���Ȃ��ƃ������[���[�N����� */
					#if (1==DFF_USE_KETM_IMAGE_CHACHE)
					unloadbmp_by_surface(difficulty_select_fg0_surface);	// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��Bdifficulty_select_fg0_surface = NULL;
					#else
					SDL_FreeSurface(difficulty_select_fg0_surface); 		// �L���b�V���ɓ����Ă�̂�NULL�ɏo���Ȃ��B
					difficulty_select_fg0_surface = NULL;
					#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
				}
				menu_cancel_and_voice();	/* �^�C�g�����j���[�ֈړ� */
			}
		}
	}
	move_kanji();
}

/*---------------------------------------------------------
	[��Փx�I�����j���[]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_05_move_draw)/* [�`��1] */
{
	sp_scale256 -= 15/*18*/;
	if (0 > sp_scale256)
	{
		sp_scale256 = (0);
		cg.main_call_func = rank_select_06_select;/* [�����W�܂�] */
	}
//	SDL_SetAlpha(player_select_bg0_surface, SDL_SRCALPHA, (255-sp_scale256) );
//	PSPL_UpperBlit(player_select_bg0_surface, NULL, sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
	move_tag_4();
	move_kanji();/*(����Ӗ��������ۂ�)*/
}

/*---------------------------------------------------------
	[��Փx�I�����j���[]�ϐ������J�n��Ԃ֏������ݒ�B
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_04_initialize_value)
{
	cg_VR20_game_difficulty &= (0x03);
	//
	sp_scale256 	= (255);
	sp_diff256		= (0);
	//
	kanji_set_x_position = (256+32);/*(�����ړ�����W�ݒ�)*/
	draw_spec_message(spec_message_01_SELECT_RANK); 	// [��Փx�I��]��Ԃ����b�Z�[�W�\���B
	cg.main_call_func = rank_select_05_move_draw;
}

/*---------------------------------------------------------
	[��Փx�I�����j���[:�����W�܂�]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_03_atumaru)/* [�����W�܂�] */
{
	toutatu_wariai += (SPEED_06_FADE_OUT);
	if (255 <= toutatu_wariai)
	{
		toutatu_wariai = (0);
		move_mode++;// (1)�ɂȂ�B
		cg.main_call_func = rank_select_04_initialize_value;/* [�I��] */
	}
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
	move_tag_4();
	/*(?)*/move_kanji();/*(����Ӗ��������ۂ�)*/
}


/*---------------------------------------------------------
	[��Փx�I�����j���[#02]�̏������ݒ�B(��蒼���̏ꍇ�͂�������)
---------------------------------------------------------*/
extern void kaiwa_obj_set_256(void);
extern MAIN_CALL_FUNC(rank_select_menu_start)
{
	/* [load] */
	{
		strcpy(my_file_common_name, (char*)DIRECTRY_NAME_DATA_STR "/teki/" "teki00_256.png" );
		#if (1==DFF_USE_KETM_IMAGE_CHACHE)
		difficulty_select_fg0_surface = load_chache_bmp();
		#else
		difficulty_select_fg0_surface = IMG_Load(my_file_common_name);
		#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
		SDL_SetColorKey(difficulty_select_fg0_surface, (SDL_SRCCOLORKEY), 0x00000000);
	}
	{
		#if (1)/*(�����֘A�̏�����)*/
		set_kanji_origin_xy(24, 64);/*(�\�����_�̐ݒ�)*/
		set_kanji_origin_kankaku(19);/*(���Ԃ������L����)*/
		set_kanji_hide_line(ML_LINE_99_MAX);/*(�S�s�\������B)*/
		kanji_window_all_clear();				/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
		cg.msg_time = (65536);	/* �� 18 �� */
		#endif
	{
		/* 8�s�ڂ̂ݓ���Ȉʒu�ֈړ��B */
		ml_font[ML_LINE_08].x		= (16);/* X�ʒu */
		ml_font[ML_LINE_08].y		= (16);/* Y�ʒu */
	}
//		kanji_window_clear_line(5); /* �����E�B���h�E��1�s��(==0)�̓��e�������B */
//		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (5) ); /* �J�[�\����1�s��(==0)�ֈړ� */
//		//
//		kanji_color((9));
//		strcpy(my_font_text, "���[�h��I�����Ă�"	 );
//		kanji_draw();
	}
	kaiwa_obj_set_256();
	#if (1)
	kaiwa_all_obj_draw_on_off(0/*off*/);/*(src/mohoufu/menu/kaiwa.c ��bobj��`�悵�Ȃ��B)*/
	#endif
	/*(��bobj���t����ʂŕ\��)*/
	{	/*(�t�����=="Story" ���[�h��p�̗����G�ړ�)*/
		cg.side_panel_draw_flag 		= (0);/*(�E�T�C�h�̃X�R�A�p�l���\��off)*/
	}
	//
	move_mode			= (0);
	toutatu_wariai		= (0);
	cg.main_call_func = rank_select_03_atumaru;
}
