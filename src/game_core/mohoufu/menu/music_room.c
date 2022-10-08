
#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�~���[�W�b�N���[�� ���z���َ�
---------------------------------------------------------*/
#include "111_my_file.h"/*(bg�ǂ݂��݁B)*/

#include "kanji_system.h"

enum
{
	MOJI_00 = 0, MOJI_01,	MOJI_02,	MOJI_03,
	MOJI_04,	MOJI_05,	MOJI_06,	MOJI_07,
	MOJI_08,	MOJI_09,	MOJI_10,	MOJI_11,
	MOJI_12,	MOJI_13,	MOJI_14,	MOJI_15,
	MOJI_16,	MOJI_17,	MOJI_18,	MOJI_19,
	MOJI_20,	MOJI_21,	MOJI_22,	MOJI_23,
	MOJI_24,	MOJI_25,	MOJI_26,	MOJI_27,
	MOJI_28,	MOJI_29,	MOJI_30,	MOJI_31,
	MOJI_32,	MOJI_33,	MOJI_34,	MOJI_35,
	MOJI_36,	MOJI_37,	MOJI_38,	MOJI_39,
	MOJI_40,	MOJI_41,//	MOJI_42,	MOJI_43,
	MOJI_42_MAX, /*(�Ȃ̍ő吔)*/
	KIDOUYOU_LINE_00,
	KIDOUYOU_LINE_01,
	KIDOUYOU_LINE_02,
	KIDOUYOU_LINE_03_MAX/*(���ڍő吔)*/
};

enum
{
	SOUND_TYPE_00_BGM = 0,
	SOUND_TYPE_01_SOUND,
	SOUND_TYPE_02_QUIT,
	SOUND_TYPE_03_MAX,
};

enum
{
	SOUND_INDEX_00_BASE_CURSOR_01 = 0,
	SOUND_INDEX_01_BASE,
	SOUND_INDEX_04_BASE_CURSOR_02,
	SOUND_INDEX_05_BASE,
	SOUND_INDEX_02_BASE_MAX_NUM,
	SOUND_INDEX_03_BASE,
	SOUND_INDEX_06_MAX	/* �ő吔 */
};
#define MAX_KEY_NAMES_21		(MOJI_42_MAX+SOUND_TYPE_03_MAX)

/*(�I���p���b�Z�[�W)*/
#define OKAERI_LINE27			(MOJI_27)
/*(�N���p���b�Z�[�W)*/
#define KIDOU_LINE28			(MOJI_28)

/*
���ߕ���(�V�t�gJIS��2�o�C�g�ڂ�0x5c�A���Ȃ킿'\'('�_')�ł��镶���̂��ƁB)
	�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
*/

//static int music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02];

static int music_room_setting[SOUND_INDEX_06_MAX/*(2)+(2)+(2)*/];/*SOUND_TYPE_03_MAX*/
static int sound_type;
static int bg_alpha_aaa;

static void music_room_draw_message(int cursor1, int cursor2)
{
//	kanji_window_all_clear();				/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
	static const char *const_kaisetu_str222[(3)][(KIDOUYOU_LINE_03_MAX)] =
	{
		{
		//
		//	"SOUND ���",
			JAPAN("�V���b�g",		"Player shot"),
		/*[�g]*/
			JAPAN("���j���[����",	"Menu ok"),
			JAPAN("���j���[�I��",	"Menu select"),
			JAPAN("�{�X�ޏ�",		"Give up boss"),
			JAPAN("�s�`���[��", 	"Mistake player"),
			JAPAN("�A�C�e���擾",	"Get Item"),
			JAPAN("������", 		"Extended"),
			JAPAN("�����J�[�h", 	"Use card"),
			JAPAN("�U�R�|����", 	"Treat Zako"),
			JAPAN("�O���C�Y",		"Glaze"),
			JAPAN("���Ԑ���",		"Time count"),
			JAPAN("�L��������", 	"Kirarin ��"),
			JAPAN("�{�X�V���b�g1",	"Boss shot #1"),
			JAPAN("�{�X�V���b�g2",	"Boss shot #2"),
			JAPAN("�{�X�V���b�g3",	"Boss shot #3"),
		/*[�d]*/
			JAPAN("�{�X�V���b�g4",	"Boss shot #4"),
			JAPAN("�{�X�V���b�g5",	"Boss shot #5"),
			JAPAN("�{�X����1",		"Boss Collecting power #1"),
			JAPAN("", ""),/*"���g�p18��"*/
			JAPAN("", ""),/*"���g�p19��"*/
			JAPAN("", ""),/*"���g�p20��"*/
			JAPAN("", ""),/*"���g�p21��"*/
		/*[�i]*/
			JAPAN("", ""),/*"���g�p22��"*/
			JAPAN("", ""),/*"���g�p23��"*/
			JAPAN("", ""),/*"���g�p24��"*/
			JAPAN("", ""),/*"���g�p25��"*/
		/*[����]*/
			JAPAN("", ""),/*"���g�p26��"*/
			JAPAN("����H�������A��ł����H", "Byebye"),/*"���g�p27��"OKAERI_LINE27*/
			JAPAN("", ""),/*"���g�p28��"KIDOU_LINE28*/
			JAPAN("", ""),/*"���g�p29��"*/
			JAPAN("", ""),/*"���g�p30��"*/
		/*[���̑�]*/
			JAPAN("", ""),/*"���g�p31��"*/
			JAPAN("", ""),/*"���g�p32��"*/
		/*[��]*/
			JAPAN("", ""),/*"���g�p33��"*/
			JAPAN("", ""),/*"���g�p34��"*/
		/*[�n]*/
		/*[��]*/
			JAPAN("", ""),/*"���g�p35��"*/
		/*[�_]*/
			JAPAN("", ""),/*"���g�p35��"*/
		/*[�_]*/
			JAPAN("", ""),/*"���g�p20��"*/
			JAPAN("", ""),/*"���g�p20��"*/
			JAPAN("", ""),/*"���g�p20��"*/
			JAPAN("", ""),/*"���g�p20��"*/
			JAPAN("�悤�������z���َ���",				"Wellcome to Illusion Music Room"),/*"���g�p36��"KIDOU_LINE36*/
		// "�N���p���b�Z�[�W��(4�s)�K�v"
			JAPAN("", ""),	 /* KIDOU_LINE37 */
			JAPAN("BGM�͑S�ȏ���ɃA�����W�łł��B",		"All Music the Arrenged version."), 		 /* KIDOU_LINE38 */
			JAPAN("�A�����W�ł����Ȃ�΁A�g���q.ogg",		"If you want to use the other music,"), 	 /* KIDOU_LINE39 */
			JAPAN("�ŊY��BGM���쐬����Ɩ�܂��B",		"created with '.ogg' or '.IT' format."),	 /* KIDOU_LINE40 */
		},
		{
		//	"-------------------------------------"
		//	"BGM ���", 									"-------------------------------------"
			JAPAN("�Ȃ��~�߂܂�",							"Stop Music"),
		/*[�g]*/
			JAPAN("No.1 �Ԃ��g����",						"No.1 Scarlet dreams than Red color"),
			JAPAN("No.2 �ق������݂����ɍg����",			"No.2 The red soul like Ground cherry"),
			JAPAN("No.3 �d����s",							"No.3 Apparition go to night"),
			JAPAN("No.4 ���[�l�C�g�G���t",					"No.4 Lunate elf"),
			JAPAN("No.5 ���Ă�Η���",						"No.5 Tomboy of love"),
			JAPAN("No.6 ��C�g���� �` Chinese Tea", 		"No.6 Shanghai Tea Palace - Chinese Tea"),
			JAPAN("No.7 �����\\���N�̏�C�A���X",			"No.7 Shanghai alice in 1884"),
			JAPAN("No.8 ���A�����@�}����",					"No.8 Voile Magical Library"),
			JAPAN("No.9 ���N�g�K�[�� �` ��������",			"No.9 Locked Girl - Girl in Sealed room"),
			JAPAN("No.10 ���C�h�ƌ��̉������v", 			"No.10 The maid and Pocket Bloody Watch"),
			JAPAN("No.11 �����v �` ���i�E�_�C�A��", 		"No.11 Moon Clock - Luna Dial"),
			JAPAN("No.12 �c�F�y�V���̗c������", 			"No.12 The young descendant of Vlad Tepes"),
			JAPAN("No.13 �S�������ׂ̈̃Z�v�e�b�g", 		"No.13 Septet for the Dead Princess"),
			JAPAN("No.14 ���@�����B�̕S�N��",				"No.14 Centenary of magical girls"),
			JAPAN("No.15 U.N.�I�[�G���͔ޏ��Ȃ̂��H",		"No.15 Un.kNown was she?"),
			JAPAN("No.16 �g���R���i��",					"No.16 Forever fleeting than scarlet"),
			JAPAN("No.17 �g�O �` Eastern Dream...", 		"No.17 Scarlet palace - Eastern Dream..."),
		/*[�d]*/
			JAPAN("No.18 �d�X�� �` Snow or Cherry Petal",	"No.18 Snow or Cherry Petal"),
			JAPAN("No.19 �����L�̋� �` Deep Mountain",		"No.19 Enough nothing in township"),
			JAPAN("No.20 ���쌶�z����", 					"No.20 Tono Genso Monogatari"),
			JAPAN("No.21 �u�N���V���e�B�̐l�`�t",			"No.21 Create a doll artisan in Bucharest"),
			JAPAN("No.22 �l�`�ٔ� �` �l�̌`�M�т�����", 	"No.22 Doll Judgment - Girl playing with"),
			JAPAN("No.23 �L�L�ˉ����� �` Till When?",		"No.23 Hiroari kechou wo irukoto"),
			JAPAN("No.24 �d�X���", 						"No.24 Mystic domination"),
		/*[�i]*/
			JAPAN("No.25 �i��̕�",						"No.25 Inalterability Night of"),
			JAPAN("No.26 ���F�}�X�^�[�X�p�[�N", 			"No.26 Love color Master Spark"),
			JAPAN("No.27 ���H���[�W��1969", 				"No.27 Voyage in 1969"),
			JAPAN("No.28 �|����� �` Lunatic Princess", 	"No.28 Flight of Taketori - Lunatic"),
		/*[����]*/
			JAPAN("No.29 �R���v���[�g�E�_�[�N�l�X", 		"No.29 Complete Darkness"),
			JAPAN("No.30 �o�b�h�E�A�b�v�� �` Bad Apple!!",	"No.30 Bad Apple!!"),
			JAPAN("No.31 �����Y�z�� �` capriccio",			"No.31 The girl capriccio"),
			JAPAN("No.32 ���}���e�B�b�N�E�`���h����",		"No.32 Romantic Children"),
			JAPAN("No.33 �O�����A �I�u �A���X", 			"No.33 Grimoire of Alice"),
		/*[���̑�]*/
			JAPAN("No.34 ���� �` Innocent Treasures",		"No.34 Warabe Maturi - Innocent Treasures"),
			JAPAN("No.35 ���_����", 						"No.35 The Fujin Girl"),
		/*[��]*/
			JAPAN("No.36 �t�H�[���I�u�t�H�[�� �` �H�߂���", "No.36 Fall of fall - Autumnal Waterfall"),
			JAPAN("No.37 �v���C���[�Y�X�R�A",				"No.37 Players score"),
		/*[�n]*/
			JAPAN("No.38 �������Ƃ�", 						"No.38 satori"),
		/*[��]*/
			JAPAN("No.39 �t�̖���", 						"No.39 Spring in Harbor"),
		/*[�_]*/
			JAPAN("No.40 ����̖��",						"No.40 Ghost in Night Cherry Blossoms"),
		/*[�_]*/
			JAPAN("No.41 �����̒|��",						"No.41 The Bamboo forest of full moon"),
		// "�N���p���b�Z�[�W��(4�s)�K�v"
			JAPAN("", ""),
			JAPAN("", ""),
			JAPAN("", ""),
			JAPAN("", ""),
		},
		{
		//
		//
			JAPAN("�e�ɂ͖������ǂ��ł���ˁB", 				"You have silence"),	/* */
		/*[�g]*/
			JAPAN("�^�C�g����ʂ̃e�[�}�ł��B", 				"Theme of title"),		/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("���[�~�A�̃e�[�}�ł��B", 					"Theme of Lumia"),		/* */
			JAPAN("�����Ȃł��B",								"stage ex"),			/* */
			JAPAN("�`���m�̃e�[�}�ł��B",						"Theme of Chrno"),		/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("����̃e�[�}�ł��B", 						"Theme of Mehrin"), 	/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�p�`�����[�E�m�[���b�W�̃e�[�}�ł��B",		"Theme of Pache"),		/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�\\�Z�� ���̃e�[�}�ł��B", 				"Theme of Sakuya"), 	/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("���~���A�E�X�J�[���b�g�̃e�[�}�ł��B",		"Theme of Remilia"),	/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�t�����h�[���E�X�J�[���b�g�̃e�[�}�ł��B",	"Theme of Fran"),		/* */
			JAPAN("���O���͉�ʂ̃e�[�}�ł��B", 				"Name regist"), 		/* */
			JAPAN("�G���f�B���O�̃e�[�}�ł��B", 				"ending"),				/* */
		/*[�d]*/
			JAPAN("�^�C�g����ʂ̃e�[�}�ł��B", 				" Petal. Theme of title"),		/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),				/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),				/* */
			JAPAN("�A���X�E�}�[�K�g���C�h�̃e�[�}�ł��B",		" puppet. Theme of Alice"), 	/* */
			JAPAN("�d���̃e�[�}�ł��B", 						" When? Theme of Youmu"),		/* */
			JAPAN("�����Ȃł��B",								"stage"),				/* */
		/*[�i]*/
			JAPAN("�����Ȃł��B",								" Retribution. stage"), 			/* */
			JAPAN("���J �������̃e�[�}�ł��B",					"Theme of Marisa"), 	/* */
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�H���R �P��̃e�[�}�ł��B",					" Princess. Theme of Kaguya"),	/* */
		/*[����]*/
			JAPAN("�����̃e�[�}�ł��B", 						"Theme of Mima"),		/* */	// Complete Darkness
			JAPAN("�����Ȃł��B",								"stage bgm"),				/* */
			JAPAN("���� �얲�̃e�[�}�ł��B",					"Theme of Reimu"),		/* */	// Capriccio == ��z��(���y�p��, �C�^���A��), Un sogno capriccioso == �C�܂���Ȗ�(�C�^���A��)
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�A���X�E�}�[�K�g���C�h�̃e�[�}�ł��B",		"Theme of Alice"),		/* */	// Grimoire of Alice
		/*[���̑�]*/
			JAPAN("�X�^�b�t���[���̃e�[�}�ł��B",				"Theme of staff"),		/* */	// ����Ȋw���I�u���� Innocent Treasures�v
			JAPAN("�˖��� ���̃e�[�}�ł��B",					"Theme of Aya"),		/* */
		/*[��]*/
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
			JAPAN("�G���f�B���O�̃e�[�}�ł��B", 				"ending"),				/* */
		/*[�n]*/
			JAPAN("���Ƃ�̃e�[�}�ł��B",						"Theme of satori"),		/* */
		/*[��]*/
			JAPAN("�����Ȃł��B",								"stage bgm"),			/* */
		/*[�_]*/
			JAPAN("�����Ȃł��B",								"stage bgm"),				/* */ /*("�I��"�Ŏg��)*/
		/*[�_]*/
			JAPAN("�����Ȃł��B",								"stage bgm"),				/* */
		// "�N���p���b�Z�[�W��(4�s)�K�v"
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
		},
	};
	//
	/*(�F�͂Ƃ肠������)*/
	{
		int jj;
		jj = (music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]);
		int ii;
		int yyy18;
		yyy18 = (0);/* Y�ʒu */
		for (ii=0; ii<(7); ii++) /* 7 �s�`��(8�s�ڂ͎g��Ȃ�) */
		{
			kanji_window_clear_line(ii);	/* �����E�B���h�E��4�s��(==3)�̓��e�������B */
			set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18));	/* �J�[�\����4�s��(==3)�ֈړ� */
		//	if (0==cursor1)/* BGM���[�h */
			if (2 > cursor1)/* 0:BGM���[�h & 1:���ʉ����[�h */
			{
				if (0==ii)	/* 1�s�ڂ̂�(0) */
				{	/*(�������s)*/
					kanji_color((9)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char*)const_kaisetu_str222[(/*ii+*/1-cursor1)][cursor2]);
				}
				else
				if (ii<6)	/* 23456�s�ڂ̂�(1, 2, 3, 4, 5) */
				{	/*(�X�N���[���s)*/
					if ((cursor2)==(jj))
					{
						kanji_color((9)|STR_CODE_NO_ENTER);
					}
					else
					{
						kanji_color((8)|STR_CODE_NO_ENTER);
					}
					strcpy(my_font_text, (char*)const_kaisetu_str222[(/*ii+*/1-cursor1)][jj]);
					jj += (1);
				}
				else/* 7�s�ڂ̂�(6) */
				{	/*(����s)*/
					kanji_color((7)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char*)const_kaisetu_str222[(2/*ii+1-4*/-cursor1-cursor1)][cursor2]);	/* ���ʉ����[�h �̏ꍇ����[���Ȃ����猩�o���Ɠ������ */
				}
			}
			else/* 2:�I�����[�h�A�̂�(r35u2) */
			{
				kanji_color((9)|STR_CODE_NO_ENTER);
				if (0==ii)	/* 1�s�ڂ̂� */
				{	/*(�������s�I�����b�Z�[�W)*/
					strcpy(my_font_text, (char*)const_kaisetu_str222[0][/*33*/(OKAERI_LINE27)/*cursor2*/]);
				}
				else	/* �c��(2-7�s��)�������B */
				{
					strcpy(my_font_text, (char*)"");
				}
			}
			kanji_draw();
			yyy18 += (18);
		}
	}
}
#if 0
extern void music_game_draw_message(int cursor1)
{
	static const char *const_music_title_str[(MOJI_42_MAX)] =
	{	/*	�ő唼�p��31�����B */
	/*	"feeddccbbaa99887766554433221100", '\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
		" �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@", // No. 0 "�Ȃ��~�߂܂�"
		" �@�@�@�@�@�@�@�@�@�@��t�̖���", // No. 1 "1�ʂ̃e�[�}�ł��B"
		"��i��̕� Imperishable Night", // No. 2 "2�ʂ̃e�[�}�ł��B" 				// ���}�`���͎~�߂ē���ւ���Ǝv���B
		" �@�@�@�@�@�@�􃔃H���[�W��1969", // No. 3 "3�ʂ̃e�[�}�ł��B"
		" �@ ��Fall of fall�@�` �H�߂���", // No. 4 "4�ʂ̃e�[�}�ł��B"
		" �@�@�@�@�@�@�􃔃A�����@�}����", // No. 5 "5�ʂ̃e�[�}�ł��B"
		" �@�@���S�������ׂ̈̃Z�v�e�b�g", // No. 6 "6�ʂ̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�@�@�@�@������", // No. 7 "�X�^�b�t���[���̃e�[�}�ł��B"
		" �@�@�@�@�@�@�􃋁[�l�C�g�G���t", // No. 8 "�G�L�X�g���X�e�[�W�̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�􉓖쌶�z����", // No. 9 "�t�@���^�Y���X�e�[�W�̃e�[�}�ł��B"
		" �@���C�g����  �` Chinese Tea", // No.10 "�G���f�B���O2�̃e�[�}�ł��B"
		"���l�`�ٔ��@�` �l�̌`�M�т�����", // No.11 "�A���X�̃e�[�}�ł��B"
		" �@�@�@�@�@ ��Complete Darkness", // No.12 "�����̃e�[�}�ł��B"
		"���|����ā@�` Lunatic Princess", // No.13 "�H���R �P��̃e�[�}�ł��B"
		" �@ �����_�����@�` Full Version", // No.14 "�˖��� ���̃e�[�}�ł��B"
		" �@ �􃉃N�g�K�[���@�` ��������", // No.15 "�p�`�����[�E�m�[���b�W�̃e�[�}�ł��B"
		" �@ �􌎎��v�@�` ���i�E�_�C�A��", // No.16 "�\\�Z�� ���̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@�@�􂨂Ă�Η���", // No.17 "�`���m�̃e�[�}�ł��B"
		" �@�@�@�@�@ ��Grimoire of Alice", // No.18 "�A���X�̃e�[�}�ł��B"
		" �@�@�@�@�����F�}�X�^�[�X�p�[�N", // No.19 "�������̃e�[�}�ł��B"
		" �@��L�L�ˉ����� �` Till When?", // No.20 "�d���̃e�[�}�ł��B"				// �d���ǂ�����B
		" �@�@�@�@�@��v���C���[�Y�X�R�A", // No.20 "�G���f�B���O�̃e�[�}�ł��B"		// ���������ւ���Ǝv���B
		" �������L�̋��@�` Deep Mountain", // No.21 "�L�[�R���t�B�O�̃e�[�}�ł��B"
		" �@�@�@�@�@�@�@��g���R���i��", // No.22 "�^�C�g����ʂ̃e�[�}�ł��B"
	};
	strcpy(my_font_text, (char*)const_music_title_str[cursor1]);
	kanji_color(7);
	kanji_draw();
}
#endif


/*---------------------------------------------------------
	���z���َ� �t�F�[�h�A�E�g���Ă����܂���
---------------------------------------------------------*/

static MAIN_CALL_FUNC(music_room_state_03_fade_out)
{
	bg_alpha_aaa += (2);	/*(1) (8)*/ 	/*fps_factor*/
	if ((224) < bg_alpha_aaa)/*(250-8)*/
	{
		bg_alpha_aaa = (255);
		#if 1/* �����̕\���p�摜���J������ */

		#endif
		cg.main_call_func = title_menu_start;	/* �^�C�g�����j���[�ֈړ� */
	}
	SDL_SetAlpha(cg.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
}


/*---------------------------------------------------------
	���z���َ� ���j���[�I�����āA�Đ�������A�`�悵���蒆
---------------------------------------------------------*/

static void up_down_allow_key_auto_repeat(void)
{
	#if 1/*(menu�ł́A�����I��vsync���Ƃ�)*/
//	sceDisplayWaitVblankStart();
	#endif
	#if 1/*(�㉺�{�^�����͂̏ꍇ�A�I�[�g���s�[�g�������s���B)*/
	{
		static int auto_repeat_counter;/*(�I�[�g���s�[�g�p�J�E���^)*/
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN))		/* ����㉺�{�^������ */
		{
			if (psp_pad.pad_data_alter & (PSP_KEY_UP|PSP_KEY_DOWN)) 	/* ���������㉺�{�^������ */
			{
				/*(�����ɂ���΁A�㉺�̂ǂ��炩�̃{�^�����������ςȂ��ɂ��Ă���̂��m�肵�Ă���B)*/
				auto_repeat_counter++;/*(�������ςȂ��̎��Ԃ��J�E���g)*/
				#define REPEAT_20_START 	(20)	/*(���񃊃s�[�g�J�n����: 20[frame])*/
				#define REPEAT_08_REPEAT	(8) 	/*(���s�[�g�J��Ԃ��Ԋu:  8[frame])*/
				if (REPEAT_20_START < auto_repeat_counter)/*(20[frame]���񃊃s�[�g)*/
				{
					auto_repeat_counter = (REPEAT_20_START-REPEAT_08_REPEAT);/*(8[frame]���s�[�g�J��Ԃ��Ԋu)*/
					/*(�L�[���s�[�g����)*/
					psp_pad.pad_data_alter = 0;/*(�L�[�������ꂽ���ɂ�胊�s�[�g==�A�˂��s��)*/
					/*(���̃^�C�~���O��(�O��)�L�[���͂����������Ă��A����̃��A���L�[���͂ɂ͔��f���Ȃ��B(�����珑�������Ă��ǂ�))*/
				}
			}
			else/*(���A���L�[���͂ŏ㉺���͂��������ꍇ����)*/
			{	auto_repeat_counter = 0;/*(�I�[�g���s�[�g����)*/	}
		}
		else/*(���A���L�[���͂ŏ㉺���͂��������ꍇ����)*/
		{	auto_repeat_counter = 0;/*(�I�[�g���s�[�g����)*/	}
	}
	#endif
}

static MAIN_CALL_FUNC(music_room_state_02_select_menu)
{
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
	cg.msg_time = /*(�i���ɕ`��)*/byou60(5);	/* �� 5 �b */
	//
	up_down_allow_key_auto_repeat();
	if (0==psp_pad.pad_data_alter)/* ����������������ĂȂ������ꍇ�ɃL�[�`�F�b�N(���쏀��) */
	{
		if (psp_pad.pad_data & PSP_KEY_LEFT)			/* ���{�^������ */
		{
			if (SOUND_TYPE_00_BGM == sound_type)		{	sound_type = (SOUND_TYPE_03_MAX-1); }
			else										{	sound_type--;	}
		}
		else
		if (psp_pad.pad_data & PSP_KEY_RIGHT)			/* �E�{�^������ */
		{
			if ((SOUND_TYPE_03_MAX-1) == sound_type)	{	sound_type = SOUND_TYPE_00_BGM; }
			else										{	sound_type++;	}
		}
		else	/* ���E�ȊO�̒ʏ폈��(�΂ߓ��͂�r������ׁA���E�̓��͂��������ꍇ�͂���ȊO�̏��������Ȃ�) */
		{
			if (SOUND_TYPE_02_QUIT == sound_type) /* ����[ QUIT ] ��I��ł���ꍇ */
			{
				if (psp_pad.pad_data & (PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL))	/* �V���b�g || �L�����Z���{�^������ */
				{
					#if (1)
					voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* ���@���ɉ��́A�Ȃ�ׂ��d�˂Ȃ� */
				//	voice_play(VOICE02_MENU_SELECT, TRACK01_MENU01);/*�e�L�g�[*/
					#endif
				//	pl ay_music_num(BGM_14_th07_01);
					my_file_common_name[0] = BG_TYPE_00_title_bg;psp_load_bg_file_name();/* ����ʂɃ��[�h */
					cg.msg_time = (0);	/* �� 0 �b */
//					bg_alpha_aaa		= 255;
					bg_alpha_aaa		= 0;
					cg.main_call_func = music_room_state_03_fade_out;
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN))		/* �㉺�{�^������ */
			{
				if (psp_pad.pad_data & PSP_KEY_UP)			/* ��{�^������ */
				{
					music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]--;
					if ((music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]) > music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]--;
					}
					if ((0/*MOJI_00*/) > music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]	= music_room_setting[SOUND_INDEX_02_BASE_MAX_NUM+sound_type];	/*(BGM�̍ő吔)*/	/*(���ʉ��̍ő吔)*/
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]	= (music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])-(4);
					}
				}
				else
				if (psp_pad.pad_data & PSP_KEY_DOWN)		/* ���{�^������ */
				{
					music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]++;
					if ((music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]+4) < music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]++;
					}
					if (music_room_setting[sound_type+SOUND_INDEX_02_BASE_MAX_NUM] < music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]	= (0)/*MOJI_00*/;
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]	= (0);
					}
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK) /* �V���b�g�{�^������ */
			{
				if (SOUND_TYPE_00_BGM == sound_type)	/* ����[ BGM ] ��I��ł���ꍇ */
				{
					#if (1)/*(-r38�܂łƌ݊�������Ȃ�L���ɂ���)*/
					play_music_num(BGM_00_stop);/*(r39�ł͈�x�~�߂Ȃ��Ɠ����Ȃ͎n�߂����Ȃ��l�Ɏd�l�ύX����)*/
					/*(�ʂɖ����Ă��\��Ȃ��C�����邪�A�����܂ŋȍĐ��́u�e�X�g���[�h�v�Ȃ̂�����A�n�߂���炵�������ǂ��B)*/
					/*(�u�e�X�g���[�h�v��(���݂��鎖��)�u��(�ړI)�v�ŁA�ȍĐ����u�](����)�v�B)*/
					#endif
					play_music_num(music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]/*BGM_07_th06_08*/);
				}
				else
//				if (SOUND_TYPE_01_SOUND == sound_type)	/* ����[ SOUND ] ��I��ł���ꍇ */
				{
					#if (1)
					voice_play_menu(music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]/*VOICE07_BOMB*/, TRACK01_MENU01);/*�e�L�g�[*/
					#endif
				}
			}
			else	/* �ݒ荀�ڂ�ύX����ꍇ */
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL) /* �L�����Z���{�^������ */
			{
				play_music_num(BGM_00_stop);
			}
		}
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_LEFT|PSP_KEY_RIGHT))	/* �㉺���E�{�^������ */
		{
			/* �ĕ`�� */
			music_room_draw_message(sound_type, music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]);
			/* �`�� */
			{
				/* �@�\�ԍ��̕`�� */
				#define MAX_MENU_02 	(SOUND_TYPE_02_QUIT)
				{
				static const char *const_aaa_str[(3)] =
				{
					/* [[ ���j���[ ]] */
				//		  "0123456789"	"0123456789"
					JAPAN("�ȍĐ� #00", "Music  #00"),
					JAPAN("���ʉ� #00", "Effect #00"),
					JAPAN("�I��      ", "Quit      ")
				};
				strcpy(my_font_text, (char*)const_aaa_str[sound_type]);
				/* ���[�h�`�� */
					/* �ԍ��{�^���ݒ�`�� */
					if (2 > sound_type)/*0 or 1*/
					{
						int kinou_number;
						kinou_number = music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01];
						dec_print_format(kinou_number, 2, (char*)&my_font_text[8]);
					}
					kanji_window_clear_line(ML_LINE_08);	/* �����E�B���h�E��4�s��(==3)�̓��e�������B */
					set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_08*18));	/* �J�[�\����4�s��(==3)�ֈړ� */
					kanji_color(7);
					kanji_draw();
				}
			}
		}
	}
}


/*---------------------------------------------------------
	���z���َ� �t�F�[�h�C����
---------------------------------------------------------*/

static MAIN_CALL_FUNC(music_room_state_01_fade_in)
{
	bg_alpha_aaa += (2);	/*fps_factor*/
	if ((200) < bg_alpha_aaa)/*(250-6) (224)*/
	{
		bg_alpha_aaa = (255);
		psp_move_screen(MODE_00_PUSH);/*(���݂̕\����ʂ𗠉�ʂɕۑ�)*/
		cg.main_call_func = music_room_state_02_select_menu;
	}
	SDL_SetAlpha(cg.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_move_screen(MODE_01_POP);/*(���z�X�N���[���𕜊��A����Ēu������ʂ�`��)*/
}


/*---------------------------------------------------------
	���z���َ� �J�n����
---------------------------------------------------------*/

extern MAIN_CALL_FUNC(music_room_start)
{
	play_music_num(BGM_22_th07_07);/* �l�`�ٔ� */
	my_file_common_name[0] = BG_TYPE_03_music_room;psp_load_bg_file_name();/* ����ʂɃ��[�h */
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_00_BASE_CURSOR_01] = (0);
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_00_BASE_CURSOR_01] = (0);
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_04_BASE_CURSOR_02] = (0);
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_04_BASE_CURSOR_02] = (0);
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_02_BASE_MAX_NUM] = (USE_42_MUSIC_FILES-1);/*MOJI_42_MAX*/	/*(BGM�̍ő吔)*/
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_02_BASE_MAX_NUM] = (VOICE18_MAX_FILES-1);/*MOJI_42_MAX*/	/*(���ʉ��̍ő吔)*/
//
	sound_type			= SOUND_TYPE_02_QUIT;
	bg_alpha_aaa		= (0);
	set_kanji_origin_xy(24, 100);/*(�\�����_�̐ݒ�)*/
	set_kanji_origin_kankaku(19);/*(���Ԃ������L����)*/
	//
	set_kanji_hide_line(ML_LINE_99_MAX);/*(�S�s�\������B)*/
	{
		/* 1�s�ڂ̂ݓ���Ȉʒu�ֈړ��B */
		ml_font[ML_LINE_01].x		=  (0);/* X�ʒu */
		ml_font[ML_LINE_01].y		= (64);/* Y�ʒu */
	}
	{
		/* 8�s�ڂ̂ݓ���Ȉʒu�ֈړ��B */
		ml_font[ML_LINE_08].x		= (160);/* X�ʒu */
		ml_font[ML_LINE_08].y		= (240);/* Y�ʒu */
	}
	kanji_window_all_clear();	/* ������ʂ�S�s�����B�����J�[�\�����z�[���|�W�V�����ֈړ��B */
	cg.msg_time = (65536);		/* �� 18 �� */
//	cg.msg_time = byou60(5);	/* �� 5 �b */
	#if (1)/*(r38�����łŃn���O�A�b�v�o�O�C��)*/
	music_room_draw_message(0+1, (KIDOU_LINE28)/*(�N���p���b�Z�[�W)*/);
	#endif
	cg.main_call_func = music_room_state_01_fade_in;
}
