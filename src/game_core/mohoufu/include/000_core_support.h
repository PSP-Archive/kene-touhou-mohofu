
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃t�@�C���͒��ڃC���N���[�h���܂���B
	"game_main.h" ����̂݊ԐړI�ɃC���N���[�h���܂��B
---------------------------------------------------------*/

#ifndef _BGM_VOICE_H_
#define _BGM_VOICE_H_

//;�u���y�f�ށv�K�v�ȃt�@�C��

enum	//; ���ʉ�(Voice)
{
	VOICE00_SHOT = 0,			//	"�V���b�g", 		/* a				�V���b�g��							[���肿�肿��] */
	VOICE01_MENU_OK,			//	"���j���[����", 	/*[b]	[s(?)]		��									[�т傢�[] */
	VOICE02_MENU_SELECT,		//	"���j���[�I��", 	/* c				�T�R���ɉ� + �e������ + ���j���[	[����] */
	VOICE03_BOSS_HAKAI, 		//	"�{�X�ޏ�", 		/*[d];	[s(?)]		�{�X���ɉ�? 						[�ڂ��[�[��] */
	VOICE04_SHIP_HAKAI, 		//	"�s�`���[��",		/* e :				���@�j��							[�҂���[��] */
	VOICE05_BONUS,				//	"�A�C�e���擾", 	/* f				�A�C�e���擾��						[����] */
	VOICE06_EXTEND, 			//	"������",			/* g :				�c�@������							[�т������] */
	VOICE07_BOMB,				//	"�����J�[�h",		/*[h]	[s(?)]		��									[������邵�Ⴕ���] */
//
	VOICE08_DEATH,				//	"�U�R�|����",		/* i				�T�R���ɉ���p						[�ǂ��[�[�[] */
	VOICE09_GRAZE,				//	"�O���C�Y", 		/* j				�O���C�Y��							[��] */
	VOICE10_COUNT_TIMER,		//	"���Ԑ���", 		/* p :				���Ԑ����J�E���g��					[�ւɂ��] */
	VOICE11_BOSS_KIRARIN,		//	"�L��������",		/* l				������ */
//
	VOICE12_MAGICF_E_SHOT,		//	"�{�X�V���b�g1",	/* k				��									[�ӂ�] */
	VOICE13_SAKUYA_B2_SHOT, 	//	"�{�X�V���b�g2",	/* m				��� �� 							[�ς���] */
	VOICE14_SAKUYA_SHOT02,		//	"�{�X�V���b�g3",	/* n				��邶���V���b�g��				[����邿��邿���] */
	VOICE15_BOSS_KOUGEKI_01,	//	"�{�X�V���b�g4",	/*[o];	[s(?)]		�{�X�U����? 						[�΂���] */
	VOICE16_BOSS_KYUPIN,		//	"�{�X�V���b�g5",	/* l				�L���s�[���� */
//
	VOICE17_BOSS_TAME01,		//	"�{�X����1",		/* r				�����[�� */
	VOICE18_MAX_FILES,
};
	/* �{�Ƃɒቹ�n�̌��ʉ��͖�����������Ȃ��̂Ŕp�~�B ��� �� [�ǂǂǂǂ�] */


enum	//; ��(Music) [.it �� .ogg�`��]
{
	BGM_00_stop = 0,	/* ----- BGM ���t��~�R�}���h */
	/*[�g]*/
	BGM_01_th06_01, 	/* th06_01.IT �Ԃ��g���� */
	BGM_02_th06_02, 	/* th06_02.IT �ق������݂����ɍg���� �����Ȃł��B */
	BGM_03_th06_03, 	/* th06_03.IT �d����s ���[�~�A */
	BGM_04_th06_04, 	/* th06_04.IT ���[�l�C�g�G���t �G�L�X�g���X�e�[�W���� */
	BGM_05_th06_05, 	/* th06_05.IT �`���m �G�L�X�g���X�e�[�W1�{�X ���Ă�Η��� */
	BGM_06_th06_06, 	/* th06_06.IT ��C�g���� */
	BGM_07_th06_07, 	/* th06_07.IT ���C�����B  */
	BGM_08_th06_08, 	/* th06_08.IT ���A�����@�}���� 5�ʓ��� */
	BGM_09_th06_09, 	/* th06_09.IT ���N�g�K�[�� �` �������� 5�ʃ{�X (�p�`�F) */
	BGM_10_th06_10, 	/* th06_10.IT ���C�h�ƌ��̉������v 6�ʓ��� */
	BGM_11_th06_11, 	/* th06_11.IT �����v �` ���i�E�_�C�A�� 6�ʃ{�X (���) */
	BGM_12_th06_12, 	/* th06_12.IT �c�F�y�V���̗c������ */
	BGM_13_th06_13, 	/* th06_13.IT �S�������ׂ̈̃Z�v�e�b�g ���~���A */
	BGM_14_th06_14, 	/* th06_14.IT ���@�����B�̕S�N�� */
	BGM_15_th06_15, 	/* th06_15.IT U.N.�I�[�G���͔ޏ��Ȃ̂��H �t���� */
	BGM_16_th06_16, 	/* th06_16.IT �g���R���i�� */
	BGM_17_th06_17, 	/* th06_17.IT �g�O �` Eastern Dream... */
	/*[�d]*/
	BGM_18_th07_01, 	/* th07_01.IT �d�X�� �` Snow or Cherry Petal �^�C�g����� */
	BGM_19_th07_02, 	/* th07_02.IT �����L�̋� �` Deep Mountain �L�[�R���t�B�O */
	BGM_20_th07_04, 	/* th07_04.IT ���쌶�z���� �t�@���^�Y���X�e�[�W���� */
	BGM_21_th07_06, 	/* th07_06.IT �u�N���V���e�B�̐l�`�t �����Ȃł��B */
	BGM_22_th07_07, 	/* th07_07.IT �l�`�ٔ� �` �l�̌`�M�т����� 1�ʃ{�X (�A���X) */
	BGM_23_th07_11, 	/* th07_11.IT �L�L�ˉ����� �` Till When? �d��  */
	BGM_24_th07_15, 	/* th07_15.IT �d�X��� �����Ȃł��B */
	/*[�i]*/
	BGM_25_th08_08, 	/* th08_08.IT �i��̕� �g�p�Ȃł��B */
	BGM_26_th08_10, 	/* th08_10.IT ���F�}�X�^�[�X�p�[�N ������ �G�L�X�g���X�e�[�W3�{�X */
	BGM_27_th08_13, 	/* th08_13.IT ���H���[�W��1969 3�ʓ��� */
	BGM_28_th08_15, 	/* th08_15.IT �|����� �` Lunatic Princess 3�ʃ{�X (�P��) */
	/*[����]*/
	BGM_29_th02_11, 	/* th02_11.IT �R���v���[�g�E�_�[�N�l�X 2�ʃ{�X (����) */
	BGM_30_th04_07, 	/* th04_07.IT �o�b�h�E�A�b�v�� �` Bad Apple!! �g�p�Ȃł��B */
	BGM_31_th04_10, 	/* th04_10.IT �����Y�z�� �` capriccio �얲 */
	BGM_32_th05_06, 	/* th05_06.IT ���}���e�B�b�N�E�`���h���� 2�ʓ��� */
	BGM_33_th05_17, 	/* th05_17.IT �O�����A �I�u �A���X �A���X �G�L�X�g���X�e�[�W2�{�X */
	/*[���̑�]*/
	BGM_34_th00_01, 	/* th00_01.IT [����Ȋw���I] ���� �` Innocent Treasures �G���f�B���O(����) */
	BGM_35_th00_11, 	/* th00_11.IT [���Ԓ�] ���_���� (Full Version) 4�ʃ{�X (��) */
	/*[��]*/
	BGM_36_th10_08, 	/* th10_08.IT �t�H�[���I�u�t�H�[�� �` �H�߂��� 4�ʓ��� */
	BGM_37_th10_18, 	/* th10_18.IT�v���C���[�Y�X�R�A �G���f�B���O(�V�i���I)  */
	/*[�n]*/
	BGM_38_th11_09, 	/* th11_09.IT �������Ƃ� (�{�X) */
	/*[��]*/
	BGM_39_th12_02, 	/* th12_02.IT �t�̖��� 1�ʓ��� */
	/*[�_]*/
	BGM_40_th13_02, 	/* th13_02.IT ����̖�� �g�p�Ȃł��B */
	/*[�_]*/
	BGM_41_th14_06, 	/* th14_06.IT �����̒|�� �����Ȃł��B */
/* ----- �Ȃ̐�(�ǂݍ��݃t�@�C����) */
	USE_42_MUSIC_FILES
};

/*(�Q�[�����̃g���b�N�݌v)*/
enum
{
	TRACK00_JIKI_SHOT = 0,	// "���@�e"�p�B(�Q�[�����́A��ɔ������Ă���̂ŁA���p�r�Ɏg���Ȃ��B��{�I�ɐ�p)
	TRACK01_PICHUN, 		// "���@�s�`���[����" / "���@��������"�p�B
	TRACK02_JIKI_BOMBER,	// "���@�{��"�p�B
	TRACK03_IVENT_DAN,		// (�G�e)"�G�e�ڗ����������p"/"�ڗ����������C�x���g"�p�B
	TRACK04_TEKIDAN,		// (�G�e)"�G�e�ʏ�p"
	TRACK05_ZAKO_DEATH, 	// "�G���j��"�p�B(���ݐ�p)
	TRACK06_ITEM,			// ���@"�A�C�e��"�擾�p�B
	TRACK07_GRAZE_AUDIO_DRIVER_INTERNAL/*(voice_play_graze();�ȊO�ŁA�O������g�p���Ă�����ɖ�Ȃ�)*/
};
#if (1)/*(�����o����悤�ɁA�G�C���A�X[�ʖ�]��`����B)*/
	/*(���j���[�̃g���b�N�݌v)*/
	#define TRACK01_MENU01 TRACK01_PICHUN
	#define TRACK02_MENU02 TRACK02_JIKI_BOMBER
#endif

extern void init_audio(void);
extern void exit_audio(void);

extern void set_voice_volume(int volume);
extern void set_music_volume(int volume);

//extern void stop_music(void);/*(�p�~)*/
//#define stop_music(aaa)	play_music_num(BGM_00_stop)
extern void fadeout_music(void);
extern void pause_music(void);
extern void resume_music(void);

extern void play_music_num(int num);

// �X�N���v�g I/F

//------------
extern CPU_FUNC(nan_ido);/*(�X�N���v�g�p)*/
extern CPU_FUNC(cpu_voice_play);/*(�X�N���v�g�p)*/
//extern void voice_play(int req, int play_track );
extern void voice_play_menu(int request_number, int play_track);/*(�O���p)*/
//------------
extern void play_voice_auto_track(int request_index_number);
extern void voice_play_graze(void); 	/* �O���C�Y���Ɋւ��ẮA��p�̔����������K�v�B */

extern void voice_play_vbl(void);

/* ���ʉ��̉����݌v���s��(�g���b�N����U��) */
#define USE_DESIGN_TRACK	(1)

#endif /* _BGM_VOICE_H_ */


/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃t�@�C���͒��ڃC���N���[�h���܂���B
	"game_main.h" ����̂݊ԐړI�ɃC���N���[�h���܂��B
---------------------------------------------------------*/
// "000_my_math.h" ����̕K�v����B

#ifndef _GAME_FILE_H_
#define _GAME_FILE_H_

/*---------------------------------------------------------
	�f�B���N�g������
	-------------------------------------------------------
	�f�B���N�g�����͕̂ς��\�������邩�� game_main.h �Œ�`
---------------------------------------------------------*/

#define DIRECTRY_NAME_DATA_STR			"data"
/* 'data' �̕������� 4 ���� */
#define DIRECTRY_NAME_DATA_LENGTH		(4)

#define DIRECTRY_NAME_KAIWA_STR 		"/kaiwa/"
/* '/kaiwa/' �̕������� 7 ���� */
#define DIRECTRY_NAME_KAIWA_LENGTH		(7)

#define DIRECTRY_NAME_KAKUCHOUSI_TEXT_STR			".txt"

/*
����:
/fonts/ �̏ꍇ�A/src/core/font.c �̂݁B
	"font01.png"
	"font03.png"
	"font05.png"
/fonts/ �̏ꍇ�A/src/core/draw/draw_kanji.c �̂݁B


/fonts/ �̏ꍇ�A/src/core/draw/score_panel.c �̂݁B
	"panel_base.png"

/kaiwa/s/ �̏ꍇ�A/src/core/load_stage.c �̂݁B
/kaiwa/0/ �̏ꍇ�A/src/core/menu/kaiwa.c �̂݁B

*/
/*---------------------------------------------------------
	�X�R�A�t�H�[�}�b�g
---------------------------------------------------------*/

typedef struct
{
	char name[16/*4*/];
//
	/*u32*/s32 score;/*[r41�d�l�ύXs32�ŏ\���As32�łȂ��ƃX�y�JCPU�œs��������]*/
	int player;
	int final_stage;	/* ���B�X�e�[�W */
	int difficulty; 	/* ��Փx */
//
	int use_continue;	/* �R���e�B�j���[�� */
	int count_miss; 	/* �~�X�� */
	int used_bomber;	/* �{���g�p�� */
	int count_bonus;	/* �J�[�h�{�[�i�X�� */
} SCORE_FORMAT;

#define MAX_8_SAVE_PLAYERS	(8)
#define MAX_5_RANKING		(5)

extern SCORE_FORMAT high_score_table[MAX_8_SAVE_PLAYERS][MAX_5_RANKING];

/*---------------------------------------------------------
	�I�v�V�������j���[�Őݒ肷��ݒ�l
---------------------------------------------------------*/

enum /*_option_config_*/
{
	OPTION_CONFIG_00_PLAYER = 0,
	OPTION_CONFIG_01_BOMB,
	OPTION_CONFIG_02_BGM,
	OPTION_CONFIG_03_SOUND,
	OPTION_CONFIG_04_CURRENT_DIFFICULTY,
	OPTION_CONFIG_05_CURRENT_PLAYER,
	OPTION_CONFIG_06_ANALOG,
	OPTION_CONFIG_07_OPEN,
	OPTION_CONFIG_08_MAX	/* �ő吔 */
};

extern int option_config[OPTION_CONFIG_08_MAX]; 	/* 8 */ 	// ����=�{�^���ϐ�

/*---------------------------------------------------------
	�R���t�B�O
---------------------------------------------------------*/

extern u32 pad_config[KINOU_08_WARIATE_MAX];
//extern int ke yconfig[KINOU_08_WARIATE_MAX];

/*---------------------------------------------------------
	�w�i�ǂ݂���
---------------------------------------------------------*/

enum /*_bg_resource_*/
{
	BG_TYPE_00_title_bg = 0,
	BG_TYPE_01_name_regist,
	BG_TYPE_02_key_config,
	BG_TYPE_03_music_room,
	BG_TYPE_04_loading, 		/*(�@�r�̉摜)*/
	BG_TYPE_99_MAX_HAIKEI,
};
//extern void load_S DL_bg(int bg_type_number);/*([�p�~] my_file_common_name[0] = bg_type_number;psp_load_bg_file_name();�Ō݊�)*/
extern void psp_load_bg_file_name(void);


#endif /* _GAME_FILE_H_ */


/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃t�@�C���͒��ڃC���N���[�h���܂���B
	"game_main.h" ����̂݊ԐړI�ɃC���N���[�h���܂��B
---------------------------------------------------------*/

#ifndef _SDL_USE_FONT_H_
#define _SDL_USE_FONT_H_

/*---------------------------------------------------------
	�t�H���g
---------------------------------------------------------*/

//enum FONTS
//{
//	FONT10W = 0,		/*	8x10 x WHITE �� (mini) */
//	FONT16B,			/* 16x16 x �����̂a�f�p  */
//	FONT16K,			/* 16x16 x �L�[�R���t�B�O�p */
//	FONT16W,			/* 16x16 x WHITE �� */
//	FONT_MAX
//};
/*(-r34�݊��p)*/	/* 16x16 x RED	 �g(�p�~) */
//#define FONT16R	FONT16W


/* �T�[�t�F�C�X�����Ȃ��ŁA���ډ�ʂɕ\�� */
extern void font_render_view_screen(void);

/* [�p�~�\��]�V�K�T�[�t�F�C�X���쐬���A������������_�����O */
extern SDL_Surface *font16_render_new_surface(void);

#define MY_FONT_256_TEXT_LENGTH 		(256)
extern char my_font_text[MY_FONT_256_TEXT_LENGTH];

#endif /* _SDL_USE_FONT_H_ */
