
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ミュージックルーム 幻想音樂室
---------------------------------------------------------*/
#include "111_my_file.h"/*(bg読みこみ。)*/

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
	MOJI_42_MAX, /*(曲の最大数)*/
	KIDOUYOU_LINE_00,
	KIDOUYOU_LINE_01,
	KIDOUYOU_LINE_02,
	KIDOUYOU_LINE_03_MAX/*(項目最大数)*/
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
	SOUND_INDEX_06_MAX	/* 最大数 */
};
#define MAX_KEY_NAMES_21		(MOJI_42_MAX+SOUND_TYPE_03_MAX)

/*(終了用メッセージ)*/
#define OKAERI_LINE27			(MOJI_27)
/*(起動用メッセージ)*/
#define KIDOU_LINE28			(MOJI_28)

/*
だめ文字(シフトJISの2バイト目が0x5c、すなわち'\'('＼')である文字のこと。)
	ソ噂浬欺圭構蚕十申曾箪貼能表暴予禄兔喀媾彌拿杤歃濬畚秉綵臀藹觸軆鐔饅鷭
*/

//static int music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02];

static int music_room_setting[SOUND_INDEX_06_MAX/*(2)+(2)+(2)*/];/*SOUND_TYPE_03_MAX*/
static int sound_type;
static int bg_alpha_aaa;

static void music_room_draw_message(int cursor1, int cursor2)
{
//	kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	static const char *const_kaisetu_str222[(3)][(KIDOUYOU_LINE_03_MAX)] =
	{
		{
		//
		//	"SOUND 解説",
			JAPAN("ショット",		"Player shot"),
		/*[紅]*/
			JAPAN("メニュー決定",	"Menu ok"),
			JAPAN("メニュー選択",	"Menu select"),
			JAPAN("ボス退場",		"Give up boss"),
			JAPAN("ピチューン", 	"Mistake player"),
			JAPAN("アイテム取得",	"Get Item"),
			JAPAN("増えた", 		"Extended"),
			JAPAN("自分カード", 	"Use card"),
			JAPAN("ザコ倒した", 	"Treat Zako"),
			JAPAN("グレイズ",		"Glaze"),
			JAPAN("時間制限",		"Time count"),
			JAPAN("キラリン☆", 	"Kirarin ☆"),
			JAPAN("ボスショット1",	"Boss shot #1"),
			JAPAN("ボスショット2",	"Boss shot #2"),
			JAPAN("ボスショット3",	"Boss shot #3"),
		/*[妖]*/
			JAPAN("ボスショット4",	"Boss shot #4"),
			JAPAN("ボスショット5",	"Boss shot #5"),
			JAPAN("ボス溜め1",		"Boss Collecting power #1"),
			JAPAN("", ""),/*"未使用18音"*/
			JAPAN("", ""),/*"未使用19音"*/
			JAPAN("", ""),/*"未使用20音"*/
			JAPAN("", ""),/*"未使用21音"*/
		/*[永]*/
			JAPAN("", ""),/*"未使用22音"*/
			JAPAN("", ""),/*"未使用23音"*/
			JAPAN("", ""),/*"未使用24音"*/
			JAPAN("", ""),/*"未使用25音"*/
		/*[旧作]*/
			JAPAN("", ""),/*"未使用26音"*/
			JAPAN("あれ？もうお帰りですか？", "Byebye"),/*"未使用27音"OKAERI_LINE27*/
			JAPAN("", ""),/*"未使用28音"KIDOU_LINE28*/
			JAPAN("", ""),/*"未使用29音"*/
			JAPAN("", ""),/*"未使用30音"*/
		/*[その他]*/
			JAPAN("", ""),/*"未使用31音"*/
			JAPAN("", ""),/*"未使用32音"*/
		/*[風]*/
			JAPAN("", ""),/*"未使用33音"*/
			JAPAN("", ""),/*"未使用34音"*/
		/*[地]*/
		/*[星]*/
			JAPAN("", ""),/*"未使用35音"*/
		/*[神]*/
			JAPAN("", ""),/*"未使用35音"*/
		/*[神]*/
			JAPAN("", ""),/*"未使用20音"*/
			JAPAN("", ""),/*"未使用20音"*/
			JAPAN("", ""),/*"未使用20音"*/
			JAPAN("", ""),/*"未使用20音"*/
			JAPAN("ようこそ幻想音樂室へ",				"Wellcome to Illusion Music Room"),/*"未使用36音"KIDOU_LINE36*/
		// "起動用メッセージで(4行)必要"
			JAPAN("", ""),	 /* KIDOU_LINE37 */
			JAPAN("BGMは全曲勝手にアレンジ版です。",		"All Music the Arrenged version."), 		 /* KIDOU_LINE38 */
			JAPAN("アレンジ版が嫌ならば、拡張子.ogg",		"If you want to use the other music,"), 	 /* KIDOU_LINE39 */
			JAPAN("で該当BGMを作成すると鳴ります。",		"created with '.ogg' or '.IT' format."),	 /* KIDOU_LINE40 */
		},
		{
		//	"-------------------------------------"
		//	"BGM 解説", 									"-------------------------------------"
			JAPAN("曲を止めます",							"Stop Music"),
		/*[紅]*/
			JAPAN("No.1 赤より紅い夢",						"No.1 Scarlet dreams than Red color"),
			JAPAN("No.2 ほおずきみたいに紅い魂",			"No.2 The red soul like Ground cherry"),
			JAPAN("No.3 妖魔夜行",							"No.3 Apparition go to night"),
			JAPAN("No.4 ルーネイトエルフ",					"No.4 Lunate elf"),
			JAPAN("No.5 おてんば恋娘",						"No.5 Tomboy of love"),
			JAPAN("No.6 上海紅茶館 ～ Chinese Tea", 		"No.6 Shanghai Tea Palace - Chinese Tea"),
			JAPAN("No.7 明治十\七年の上海アリス",			"No.7 Shanghai alice in 1884"),
			JAPAN("No.8 ヴアル魔法図書館",					"No.8 Voile Magical Library"),
			JAPAN("No.9 ラクトガール ～ 少女密室",			"No.9 Locked Girl - Girl in Sealed room"),
			JAPAN("No.10 メイドと血の懐中時計", 			"No.10 The maid and Pocket Bloody Watch"),
			JAPAN("No.11 月時計 ～ ルナ・ダイアル", 		"No.11 Moon Clock - Luna Dial"),
			JAPAN("No.12 ツェペシュの幼き末裔", 			"No.12 The young descendant of Vlad Tepes"),
			JAPAN("No.13 亡き王女の為のセプテット", 		"No.13 Septet for the Dead Princess"),
			JAPAN("No.14 魔法少女達の百年祭",				"No.14 Centenary of magical girls"),
			JAPAN("No.15 U.N.オーエンは彼女なのか？",		"No.15 Un.kNown was she?"),
			JAPAN("No.16 紅より儚い永遠",					"No.16 Forever fleeting than scarlet"),
			JAPAN("No.17 紅楼 ～ Eastern Dream...", 		"No.17 Scarlet palace - Eastern Dream..."),
		/*[妖]*/
			JAPAN("No.18 妖々夢 ～ Snow or Cherry Petal",	"No.18 Snow or Cherry Petal"),
			JAPAN("No.19 無何有の郷 ～ Deep Mountain",		"No.19 Enough nothing in township"),
			JAPAN("No.20 遠野幻想物語", 					"No.20 Tono Genso Monogatari"),
			JAPAN("No.21 ブクレシュティの人形師",			"No.21 Create a doll artisan in Bucharest"),
			JAPAN("No.22 人形裁判 ～ 人の形弄びし少女", 	"No.22 Doll Judgment - Girl playing with"),
			JAPAN("No.23 広有射怪鳥事 ～ Till When?",		"No.23 Hiroari kechou wo irukoto"),
			JAPAN("No.24 妖々跋扈", 						"No.24 Mystic domination"),
		/*[永]*/
			JAPAN("No.25 永夜の報い",						"No.25 Inalterability Night of"),
			JAPAN("No.26 恋色マスタースパーク", 			"No.26 Love color Master Spark"),
			JAPAN("No.27 ヴォヤージュ1969", 				"No.27 Voyage in 1969"),
			JAPAN("No.28 竹取飛翔 ～ Lunatic Princess", 	"No.28 Flight of Taketori - Lunatic"),
		/*[旧作]*/
			JAPAN("No.29 コンプリート・ダークネス", 		"No.29 Complete Darkness"),
			JAPAN("No.30 バッド・アップル ～ Bad Apple!!",	"No.30 Bad Apple!!"),
			JAPAN("No.31 少女綺想曲 ～ capriccio",			"No.31 The girl capriccio"),
			JAPAN("No.32 ロマンティック・チルドレン",		"No.32 Romantic Children"),
			JAPAN("No.33 グリモア オブ アリス", 			"No.33 Grimoire of Alice"),
		/*[その他]*/
			JAPAN("No.34 童祭 ～ Innocent Treasures",		"No.34 Warabe Maturi - Innocent Treasures"),
			JAPAN("No.35 風神少女", 						"No.35 The Fujin Girl"),
		/*[風]*/
			JAPAN("No.36 フォールオブフォール ～ 秋めく滝", "No.36 Fall of fall - Autumnal Waterfall"),
			JAPAN("No.37 プレイヤーズスコア",				"No.37 Players score"),
		/*[地]*/
			JAPAN("No.38 少女さとり", 						"No.38 satori"),
		/*[星]*/
			JAPAN("No.39 春の湊に", 						"No.39 Spring in Harbor"),
		/*[神]*/
			JAPAN("No.40 死霊の夜桜",						"No.40 Ghost in Night Cherry Blossoms"),
		/*[神]*/
			JAPAN("No.41 満月の竹林",						"No.41 The Bamboo forest of full moon"),
		// "起動用メッセージで(4行)必要"
			JAPAN("", ""),
			JAPAN("", ""),
			JAPAN("", ""),
			JAPAN("", ""),
		},
		{
		//
		//
			JAPAN("弾には無音も良いですよね。", 				"You have silence"),	/* */
		/*[紅]*/
			JAPAN("タイトル画面のテーマです。", 				"Theme of title"),		/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("ルーミアのテーマです。", 					"Theme of Lumia"),		/* */
			JAPAN("道中曲です。",								"stage ex"),			/* */
			JAPAN("チルノのテーマです。",						"Theme of Chrno"),		/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("美鈴のテーマです。", 						"Theme of Mehrin"), 	/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("パチュリー・ノーレッジのテーマです。",		"Theme of Pache"),		/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("十\六夜 咲夜のテーマです。", 				"Theme of Sakuya"), 	/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("レミリア・スカーレットのテーマです。",		"Theme of Remilia"),	/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("フランドール・スカーレットのテーマです。",	"Theme of Fran"),		/* */
			JAPAN("名前入力画面のテーマです。", 				"Name regist"), 		/* */
			JAPAN("エンディングのテーマです。", 				"ending"),				/* */
		/*[妖]*/
			JAPAN("タイトル画面のテーマです。", 				" Petal. Theme of title"),		/* */
			JAPAN("道中曲です。",								"stage bgm"),				/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("道中曲です。",								"stage bgm"),				/* */
			JAPAN("アリス・マーガトロイドのテーマです。",		" puppet. Theme of Alice"), 	/* */
			JAPAN("妖夢のテーマです。", 						" When? Theme of Youmu"),		/* */
			JAPAN("道中曲です。",								"stage"),				/* */
		/*[永]*/
			JAPAN("道中曲です。",								" Retribution. stage"), 			/* */
			JAPAN("霧雨 魔理沙のテーマです。",					"Theme of Marisa"), 	/* */
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("蓬莱山 輝夜のテーマです。",					" Princess. Theme of Kaguya"),	/* */
		/*[旧作]*/
			JAPAN("魅魔のテーマです。", 						"Theme of Mima"),		/* */	// Complete Darkness
			JAPAN("道中曲です。",								"stage bgm"),				/* */
			JAPAN("博麗 霊夢のテーマです。",					"Theme of Reimu"),		/* */	// Capriccio == 奇想曲(音楽用語, イタリア語), Un sogno capriccioso == 気まぐれな夢(イタリア語)
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("アリス・マーガトロイドのテーマです。",		"Theme of Alice"),		/* */	// Grimoire of Alice
		/*[その他]*/
			JAPAN("スタッフロールのテーマです。",				"Theme of staff"),		/* */	// 夢違科学世紀「童祭 Innocent Treasures」
			JAPAN("射命丸 文のテーマです。",					"Theme of Aya"),		/* */
		/*[風]*/
			JAPAN("道中曲です。",								"stage bgm"),			/* */
			JAPAN("エンディングのテーマです。", 				"ending"),				/* */
		/*[地]*/
			JAPAN("さとりのテーマです。",						"Theme of satori"),		/* */
		/*[星]*/
			JAPAN("道中曲です。",								"stage bgm"),			/* */
		/*[神]*/
			JAPAN("道中曲です。",								"stage bgm"),				/* */ /*("終了"で使う)*/
		/*[神]*/
			JAPAN("道中曲です。",								"stage bgm"),				/* */
		// "起動用メッセージで(4行)必要"
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
			JAPAN("", ""),											/* */
		},
	};
	//
	/*(色はとりあえず白)*/
	{
		int jj;
		jj = (music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]);
		int ii;
		int yyy18;
		yyy18 = (0);/* Y位置 */
		for (ii=0; ii<(7); ii++) /* 7 行描画(8行目は使わない) */
		{
			kanji_window_clear_line(ii);	/* 漢字ウィンドウの4行目(==3)の内容を消す。 */
			set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18));	/* カーソルを4行目(==3)へ移動 */
		//	if (0==cursor1)/* BGMモード */
			if (2 > cursor1)/* 0:BGMモード & 1:効果音モード */
			{
				if (0==ii)	/* 1行目のみ(0) */
				{	/*(見だし行)*/
					kanji_color((9)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char*)const_kaisetu_str222[(/*ii+*/1-cursor1)][cursor2]);
				}
				else
				if (ii<6)	/* 23456行目のみ(1, 2, 3, 4, 5) */
				{	/*(スクロール行)*/
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
				else/* 7行目のみ(6) */
				{	/*(解説行)*/
					kanji_color((7)|STR_CODE_NO_ENTER);
					strcpy(my_font_text, (char*)const_kaisetu_str222[(2/*ii+1-4*/-cursor1-cursor1)][cursor2]);	/* 効果音モード の場合しょーがないから見出しと同じ解説 */
				}
			}
			else/* 2:終了モード、のみ(r35u2) */
			{
				kanji_color((9)|STR_CODE_NO_ENTER);
				if (0==ii)	/* 1行目のみ */
				{	/*(見だし行終了メッセージ)*/
					strcpy(my_font_text, (char*)const_kaisetu_str222[0][/*33*/(OKAERI_LINE27)/*cursor2*/]);
				}
				else	/* 残り(2-7行目)を消す。 */
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
	{	/*	最大半角で31文字。 */
	/*	"feeddccbbaa99887766554433221100", '\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
		" 　　　　　　　　　　　　　　　", // No. 0 "曲を止めます"
		" 　　　　　　　　　　♪春の湊に", // No. 1 "1面のテーマです。"
		"♪永夜の報い Imperishable Night", // No. 2 "2面のテーマです。" 				// ロマチルは止めて入れ替えると思う。
		" 　　　　　　♪ヴォヤージュ1969", // No. 3 "3面のテーマです。"
		" 　 ♪Fall of fall　～ 秋めく滝", // No. 4 "4面のテーマです。"
		" 　　　　　　♪ヴアル魔法図書館", // No. 5 "5面のテーマです。"
		" 　　♪亡き王女の為のセプテット", // No. 6 "6面のテーマです。"
		" 　　　　　　　　　　　　♪童祭", // No. 7 "スタッフロールのテーマです。"
		" 　　　　　　♪ルーネイトエルフ", // No. 8 "エキストラステージのテーマです。"
		" 　　　　　　　　♪遠野幻想物語", // No. 9 "ファンタズムステージのテーマです。"
		" 　♪上海紅茶館  ～ Chinese Tea", // No.10 "エンディング2のテーマです。"
		"♪人形裁判　～ 人の形弄びし少女", // No.11 "アリスのテーマです。"
		" 　　　　　 ♪Complete Darkness", // No.12 "魅魔のテーマです。"
		"♪竹取飛翔　～ Lunatic Princess", // No.13 "蓬莱山 輝夜のテーマです。"
		" 　 ♪風神少女　～ Full Version", // No.14 "射命丸 文のテーマです。"
		" 　 ♪ラクトガール　～ 少女密室", // No.15 "パチュリー・ノーレッジのテーマです。"
		" 　 ♪月時計　～ ルナ・ダイアル", // No.16 "十\六夜 咲夜のテーマです。"
		" 　　　　　　　　♪おてんば恋娘", // No.17 "チルノのテーマです。"
		" 　　　　　 ♪Grimoire of Alice", // No.18 "アリスのテーマです。"
		" 　　　　♪恋色マスタースパーク", // No.19 "魔理沙のテーマです。"
		" 　♪広有射怪鳥事 ～ Till When?", // No.20 "妖夢のテーマです。"				// 妖夢どうしよ。
		" 　　　　　♪プレイヤーズスコア", // No.20 "エンディングのテーマです。"		// これも入れ替えると思う。
		" ♪無何有の郷　～ Deep Mountain", // No.21 "キーコンフィグのテーマです。"
		" 　　　　　　　♪紅より儚い永遠", // No.22 "タイトル画面のテーマです。"
	};
	strcpy(my_font_text, (char*)const_music_title_str[cursor1]);
	kanji_color(7);
	kanji_draw();
}
#endif


/*---------------------------------------------------------
	幻想音樂室 フェードアウトしておしまい中
---------------------------------------------------------*/

static MAIN_CALL_FUNC(music_room_state_03_fade_out)
{
	bg_alpha_aaa += (2);	/*(1) (8)*/ 	/*fps_factor*/
	if ((224) < bg_alpha_aaa)/*(250-8)*/
	{
		bg_alpha_aaa = (255);
		#if 1/* 文字の表示用画像を開放する */

		#endif
		cg.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
	}
	SDL_SetAlpha(cg.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
}


/*---------------------------------------------------------
	幻想音樂室 メニュー選択して、再生したり、描画したり中
---------------------------------------------------------*/

static void up_down_allow_key_auto_repeat(void)
{
	#if 1/*(menuでは、強制的にvsyncをとる)*/
//	sceDisplayWaitVblankStart();
	#endif
	#if 1/*(上下ボタン入力の場合、オートリピート処理を行う。)*/
	{
		static int auto_repeat_counter;/*(オートリピート用カウンタ)*/
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN))		/* 今回上下ボタン入力 */
		{
			if (psp_pad.pad_data_alter & (PSP_KEY_UP|PSP_KEY_DOWN)) 	/* さっきも上下ボタン入力 */
			{
				/*(ここにくれば、上下のどちらかのボタンを押しっぱなしにしているのが確定している。)*/
				auto_repeat_counter++;/*(押しっぱなしの時間をカウント)*/
				#define REPEAT_20_START 	(20)	/*(初回リピート開始時間: 20[frame])*/
				#define REPEAT_08_REPEAT	(8) 	/*(リピート繰り返し間隔:  8[frame])*/
				if (REPEAT_20_START < auto_repeat_counter)/*(20[frame]初回リピート)*/
				{
					auto_repeat_counter = (REPEAT_20_START-REPEAT_08_REPEAT);/*(8[frame]リピート繰り返し間隔)*/
					/*(キーリピート処理)*/
					psp_pad.pad_data_alter = 0;/*(キーが離された事によりリピート==連射を行う)*/
					/*(このタイミングで(前回)キー入力を書き換えても、次回のリアルキー入力には反映しない。(だから書き換えても良い))*/
				}
			}
			else/*(リアルキー入力で上下入力があった場合解除)*/
			{	auto_repeat_counter = 0;/*(オートリピート解除)*/	}
		}
		else/*(リアルキー入力で上下入力があった場合解除)*/
		{	auto_repeat_counter = 0;/*(オートリピート解除)*/	}
	}
	#endif
}

static MAIN_CALL_FUNC(music_room_state_02_select_menu)
{
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	cg.msg_time = /*(永遠に描画)*/byou60(5);	/* 約 5 秒 */
	//
	up_down_allow_key_auto_repeat();
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		if (psp_pad.pad_data & PSP_KEY_LEFT)			/* 左ボタン入力 */
		{
			if (SOUND_TYPE_00_BGM == sound_type)		{	sound_type = (SOUND_TYPE_03_MAX-1); }
			else										{	sound_type--;	}
		}
		else
		if (psp_pad.pad_data & PSP_KEY_RIGHT)			/* 右ボタン入力 */
		{
			if ((SOUND_TYPE_03_MAX-1) == sound_type)	{	sound_type = SOUND_TYPE_00_BGM; }
			else										{	sound_type++;	}
		}
		else	/* 左右以外の通常処理(斜め入力を排除する為、左右の入力があった場合はそれ以外の処理をしない) */
		{
			if (SOUND_TYPE_02_QUIT == sound_type) /* 項目[ QUIT ] を選んでいる場合 */
			{
				if (psp_pad.pad_data & (PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL))	/* ショット || キャンセルボタン入力 */
				{
					#if (1)
					voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* 自機死に音は、なるべく重ねない */
				//	voice_play(VOICE02_MENU_SELECT, TRACK01_MENU01);/*テキトー*/
					#endif
				//	pl ay_music_num(BGM_14_th07_01);
					my_file_common_name[0] = BG_TYPE_00_title_bg;psp_load_bg_file_name();/* 裏画面にロード */
					cg.msg_time = (0);	/* 約 0 秒 */
//					bg_alpha_aaa		= 255;
					bg_alpha_aaa		= 0;
					cg.main_call_func = music_room_state_03_fade_out;
				}
			}
			else	/* 設定項目を変更する場合 */
			if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN))		/* 上下ボタン入力 */
			{
				if (psp_pad.pad_data & PSP_KEY_UP)			/* 上ボタン入力 */
				{
					music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]--;
					if ((music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]) > music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]--;
					}
					if ((0/*MOJI_00*/) > music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])
					{
						music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]	= music_room_setting[SOUND_INDEX_02_BASE_MAX_NUM+sound_type];	/*(BGMの最大数)*/	/*(効果音の最大数)*/
						music_room_setting[sound_type+SOUND_INDEX_04_BASE_CURSOR_02]	= (music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01])-(4);
					}
				}
				else
				if (psp_pad.pad_data & PSP_KEY_DOWN)		/* 下ボタン入力 */
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
			else	/* 設定項目を変更する場合 */
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK) /* ショットボタン入力 */
			{
				if (SOUND_TYPE_00_BGM == sound_type)	/* 項目[ BGM ] を選んでいる場合 */
				{
					#if (1)/*(-r38までと互換させるなら有効にする)*/
					play_music_num(BGM_00_stop);/*(r39では一度止めないと同じ曲は始めから鳴らない様に仕様変更した)*/
					/*(別に無くても構わない気もするが、あくまで曲再生の「テストモード」なのだから、始めから鳴らした方が良い。)*/
					/*(「テストモード」が(存在する事が)「主(目的)」で、曲再生が「従(結果)」。)*/
					#endif
					play_music_num(music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]/*BGM_07_th06_08*/);
				}
				else
//				if (SOUND_TYPE_01_SOUND == sound_type)	/* 項目[ SOUND ] を選んでいる場合 */
				{
					#if (1)
					voice_play_menu(music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]/*VOICE07_BOMB*/, TRACK01_MENU01);/*テキトー*/
					#endif
				}
			}
			else	/* 設定項目を変更する場合 */
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL) /* キャンセルボタン入力 */
			{
				play_music_num(BGM_00_stop);
			}
		}
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_LEFT|PSP_KEY_RIGHT))	/* 上下左右ボタン入力 */
		{
			/* 再描画 */
			music_room_draw_message(sound_type, music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01]);
			/* 描画 */
			{
				/* 機能番号の描画 */
				#define MAX_MENU_02 	(SOUND_TYPE_02_QUIT)
				{
				static const char *const_aaa_str[(3)] =
				{
					/* [[ メニュー ]] */
				//		  "0123456789"	"0123456789"
					JAPAN("曲再生 #00", "Music  #00"),
					JAPAN("効果音 #00", "Effect #00"),
					JAPAN("終了      ", "Quit      ")
				};
				strcpy(my_font_text, (char*)const_aaa_str[sound_type]);
				/* モード描画 */
					/* 番号ボタン設定描画 */
					if (2 > sound_type)/*0 or 1*/
					{
						int kinou_number;
						kinou_number = music_room_setting[sound_type+SOUND_INDEX_00_BASE_CURSOR_01];
						dec_print_format(kinou_number, 2, (char*)&my_font_text[8]);
					}
					kanji_window_clear_line(ML_LINE_08);	/* 漢字ウィンドウの4行目(==3)の内容を消す。 */
					set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_08*18));	/* カーソルを4行目(==3)へ移動 */
					kanji_color(7);
					kanji_draw();
				}
			}
		}
	}
}


/*---------------------------------------------------------
	幻想音樂室 フェードイン中
---------------------------------------------------------*/

static MAIN_CALL_FUNC(music_room_state_01_fade_in)
{
	bg_alpha_aaa += (2);	/*fps_factor*/
	if ((200) < bg_alpha_aaa)/*(250-6) (224)*/
	{
		bg_alpha_aaa = (255);
		psp_move_screen(MODE_00_PUSH);/*(現在の表示画面を裏画面に保存)*/
		cg.main_call_func = music_room_state_02_select_menu;
	}
	SDL_SetAlpha(cg.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, bg_alpha_aaa);
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
}


/*---------------------------------------------------------
	幻想音樂室 開始処理
---------------------------------------------------------*/

extern MAIN_CALL_FUNC(music_room_start)
{
	play_music_num(BGM_22_th07_07);/* 人形裁判 */
	my_file_common_name[0] = BG_TYPE_03_music_room;psp_load_bg_file_name();/* 裏画面にロード */
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_00_BASE_CURSOR_01] = (0);
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_00_BASE_CURSOR_01] = (0);
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_04_BASE_CURSOR_02] = (0);
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_04_BASE_CURSOR_02] = (0);
	music_room_setting[SOUND_TYPE_00_BGM   + SOUND_INDEX_02_BASE_MAX_NUM] = (USE_42_MUSIC_FILES-1);/*MOJI_42_MAX*/	/*(BGMの最大数)*/
	music_room_setting[SOUND_TYPE_01_SOUND + SOUND_INDEX_02_BASE_MAX_NUM] = (VOICE18_MAX_FILES-1);/*MOJI_42_MAX*/	/*(効果音の最大数)*/
//
	sound_type			= SOUND_TYPE_02_QUIT;
	bg_alpha_aaa		= (0);
	set_kanji_origin_xy(24, 100);/*(表示原点の設定)*/
	set_kanji_origin_kankaku(19);/*(字間を少し広げる)*/
	//
	set_kanji_hide_line(ML_LINE_99_MAX);/*(全行表示する。)*/
	{
		/* 1行目のみ特殊な位置へ移動。 */
		ml_font[ML_LINE_01].x		=  (0);/* X位置 */
		ml_font[ML_LINE_01].y		= (64);/* Y位置 */
	}
	{
		/* 8行目のみ特殊な位置へ移動。 */
		ml_font[ML_LINE_08].x		= (160);/* X位置 */
		ml_font[ML_LINE_08].y		= (240);/* Y位置 */
	}
	kanji_window_all_clear();	/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	cg.msg_time = (65536);		/* 約 18 分 */
//	cg.msg_time = byou60(5);	/* 約 5 秒 */
	#if (1)/*(r38署名版でハングアップバグ修正)*/
	music_room_draw_message(0+1, (KIDOU_LINE28)/*(起動用メッセージ)*/);
	#endif
	cg.main_call_func = music_room_state_01_fade_in;
}
