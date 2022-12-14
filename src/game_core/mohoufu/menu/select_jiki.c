
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ゲーム開始時の難易度/プレイヤー選択
	-------------------------------------------------------
	[難易度選択メニュー]
	[プレイヤー選択メニュー]
---------------------------------------------------------*/

#include "kanji_system.h"
#include "111_my_file.h"/*(my_file_common_name)*/


	/*(Guの場合、会話スプライトを使う)*/
#include "kaiwa_sprite.h"
#include "../draw/gu_draw_screen.h"

/*---------------------------------------------------------
	player select用
---------------------------------------------------------*/

#define BASE_SP_BG_PNG		(MAX_08_PLAYER*0)
#define BASE_SP_ST_PNG		(MAX_08_PLAYER*1)
#define BASE_SP_PNG_MAX 	(MAX_08_PLAYER*2)

/*---------------------------------------------------------
	必ずどっちか。
---------------------------------------------------------*/
enum
{
	spec_message_00_SELECT_PLAYER = 0,
	spec_message_01_SELECT_RANK,
};
//		 if (spec_message_00_SELECT_PLAYER==set_mode)	{	... 	}
//	else if (spec_message_01_SELECT_RANK==set_mode) 	{	... 	}

/*---------------------------------------------------------
	状態をメッセージ表示。
	-------------------------------------------------------
	[難易度選択メニュー]
	[プレイヤー選択メニュー]
---------------------------------------------------------*/
#if defined(USE_LANGUAGE_ENGLISH)
	#define STR_MSG_TOTAL_SPEED 	"   Moving Speed: "
	#define STR_MSG_TOTAL_ATTACK	"   Attack Range: "
	#define STR_MSG_TOTAL_POWER 	"Offensive Power: "
#else
	#define STR_MSG_TOTAL_SPEED 	"移動速度"
	#define STR_MSG_TOTAL_ATTACK	"攻撃範囲"
	#define STR_MSG_TOTAL_POWER 	"攻撃力　"
#endif
static void draw_spec_message(u32 set_mode)
{
	kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	static const char *const_player_spec_str[(8)/*(8人)*/+(4)/*(4難易度)*/][(2)/*(白文字+黄文字)*/] =
	{	/*"針巫女の攻撃力の解説は、おかしい気がするけど貼りつかなければ弱い。"*/
		{	JAPAN("楽園の素敵な巫女", "Lovely shrine maiden of paradise")"\\n"
			JAPAN("博麗 霊夢 (霊符)",			"Hakurei Reimu A (spirit card)")"\\n"
			JAPAN("ホーミングアミュレット", 	"Homing Amulet")"\\n"
			JAPAN("夢想封印",					"Seal Reverie")"\\n",
			STR_MSG_TOTAL_SPEED  "★★☆\\n"
			STR_MSG_TOTAL_ATTACK "★★★\\n"
			STR_MSG_TOTAL_POWER  "★☆☆",	}, // No. 0 霊夢 A(霊符)
		{	JAPAN("楽園の素敵な巫女", "Lovely shrine maiden of paradise")"\\n"
			JAPAN("博麗 霊夢 (夢符)",			"Hakurei Reimu B (dream card)")"\\n"
			JAPAN("封魔針", 					"Demon sealed Needle")"\\n"
			JAPAN("夢想結界",					"Reverie Barrier")"\\n",
			STR_MSG_TOTAL_SPEED  "★★☆\\n"
			STR_MSG_TOTAL_ATTACK "★★☆\\n"
			STR_MSG_TOTAL_POWER  "★★☆",	}, // No. 1 霊夢 B(夢符)
		{	JAPAN("普通の黒魔術師", "Standard Necromancer")"\\n"
			JAPAN("霧雨 魔理沙 (魔符)", 		"Kirisame Marisa A (devil card)")"\\n"
			JAPAN("マジックミサイル",			"Magic Missile")"\\n"
			JAPAN("スターダストレヴァリエ", 	"Stardust Reverie")"\\n",
			STR_MSG_TOTAL_SPEED  "★★★\\n"
			STR_MSG_TOTAL_ATTACK "★★★\\n"
			STR_MSG_TOTAL_POWER  "★☆☆",	}, // No. 2 魔理沙 A(魔符)
		{	JAPAN("古風な魔法使い", "Retrospective Magician")"\\n"
			JAPAN("霧雨 魔理沙 (恋符)", 		"Kirisame Marisa B (lovely card)")"\\n"
			JAPAN("イリュージョンレーザー", 	"Illusion Laser")"\\n"
			JAPAN("マスタースパーク",			"Master Spark")"\\n",
			STR_MSG_TOTAL_SPEED  "★★★\\n"
			STR_MSG_TOTAL_ATTACK "★☆☆\\n"
			STR_MSG_TOTAL_POWER  "★★★",	}, // No. 3 魔理沙 B(恋符)
		{	JAPAN("吸血鬼", "Vampire")"\\n"
			JAPAN("レミリア スカーレット",		"Remilia Scarlet")"\\n"
			JAPAN("ナイトダンス",				"Night Dance")"\\n"
			JAPAN("不夜城ブレッド", 			"All Night Blood")"\\n",// 不夜城（ふやじょう）は、中国の山東省にあったとされる古代都市。夜も日が出たとされたため、この名がある。
			STR_MSG_TOTAL_SPEED  "★★☆\\n"
			STR_MSG_TOTAL_ATTACK "★★☆\\n"
			STR_MSG_TOTAL_POWER  "★★☆",	}, // No. 4 レミリア(血符)
		{	JAPAN("華胥の亡霊", "Ghost of Peaceful land")"\\n"// 華胥の国 中国の黄帝が夢の中で見たという、無為自然で治まる理想の国。太平の国。
			JAPAN("西行寺 幽々子",				"Saigyouzi Yuyuko")"\\n"
			JAPAN("対岸の誘い", 				"Invitation of the other side ...")"\\n"
			JAPAN("ギャストリドリーム", 		"Ghastly Dream")"\\n",
			STR_MSG_TOTAL_SPEED  "☆☆☆\\n"
			STR_MSG_TOTAL_ATTACK "★★☆\\n"
			STR_MSG_TOTAL_POWER  "★★★",	}, // No. 5 幽々子(符蝶)
		{	JAPAN("湖上の氷精", "Ice fairy on the lake")"\\n"
			JAPAN("チルノ (氷符)",				"Chrno A (ice card)")"\\n"
			JAPAN("アイシクルニードル", 		"Icicle Needle")"\\n"
			JAPAN("アイシクルストライク",		"Icicle Strike")"\\n",
			STR_MSG_TOTAL_SPEED  "★★★★\\n"
			STR_MSG_TOTAL_ATTACK "？？？\\n"
			STR_MSG_TOTAL_POWER  "★★☆",	}, // No. 6 チルノ A(氷符)
		{	JAPAN("湖上の氷精", "Ice fairy on the lake")"\\n"
			JAPAN("チルノ (?H符)",				"Chrno Qute (qute card)")"\\n"
			JAPAN("★アイスソ\ード",			"★Ice Sword")"\\n"
			JAPAN("冷凍剣+99999",				"Blizzard Blade add 99999 levels")"\\n",
			STR_MSG_TOTAL_SPEED  "★★★★★\\n"
			STR_MSG_TOTAL_ATTACK "？？？\\n"
			STR_MSG_TOTAL_POWER  "?H?H?H",	}, // No. 7 チルノ Q(?H系)
		//
		{	"Easy\\n"
			JAPAN("簡単かどうかは人による。",	"So easily be only Select")"\\n",
			JAPAN("エンディング無し", "NOT contains good ending")"\\n"
			JAPAN("(全５面)", "(5 stages)"), }, // No. 0 easy
		{	"Normal\\n"
			JAPAN("普通な人にはハード。",		"Normally when Hard.")"\\n",
			JAPAN("(全６面)", "(6 stages)"), }, // No. 1 normal
		{	"Hard\\n"
			JAPAN("ハードな人には普通。",		"Hardest when Normally.")"\\n",
			JAPAN("(全６面)", "(6 stages)"), }, // No. 2 hard
		{	"Lunatic\\n"
			JAPAN("つきが必要。",				"No doubt just Lunatic.")"\\n",
			JAPAN("(全６面)", "(6 stages)"), }, // No. 3 lunatic
		//
		// 1節目(白)													// 2節目(黄色)
	};/* 氷柱 == Icicle == アイシクル */
	//
	const u32 aaa = (spec_message_00_SELECT_PLAYER==set_mode)?((unsigned)cg_game_select_player):((8)+((unsigned)cg_VR20_game_difficulty));
	// 文字を決める。												// 色を決める。 				// 描画する。
	strcpy(my_font_text, (char*)const_player_spec_str[((aaa))][0]); kanji_color(7);/*(白色)*/		kanji_draw();
	strcpy(my_font_text, (char*)const_player_spec_str[((aaa))][1]); kanji_color(14);/*(黄色)*/		kanji_draw();
	strcpy(my_font_text, (spec_message_00_SELECT_PLAYER==set_mode)?
		("\\n"JAPAN("誰が行くの？", "Who are you going?")):
		("\\n\\n\\n\\n\\n"JAPAN("モードを選択してね", "Select difficulty"))
	);
	kanji_color(9);/*(青/白色)*/	kanji_draw();
}
// "簡単に言えば、ボムゲです。"
// "簡単には攻略できない。"
// "普通に言えば、難しいです。"
// "お硬く言えば、厳しいです。"
// "月並みに言えば、激しいです。"

#define SOZAI_HABA_184 (185-1)		/* 素材幅184[ドット] */
#define SOZAI_TATE_064 ( 64-1)		/* 素材幅 63[ドット] */

/*---------------------------------------------------------
	ローカル使用変数。
---------------------------------------------------------*/

static int sp_scale256; 	 /*(自機を選択しなおすと、確定するまで、ずれているX座標)*/
static int sp_diff256;
static int is_turn_right;
static SDL_Surface *difficulty_select_fg0_surface;
static SDL_Surface *player_select_bg0_surface;
static SDL_Surface *player_select_bg2_surface;

/*(キャッシュにいれると、アルファが出ない。)*/
#define DFF_USE_KETM_IMAGE_CHACHE (0)

/*---------------------------------------------------------
	漢字表示移動処理
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
		ml_font[i].x	= (kanji_move_x_position);/* X位置 */
	}
}


/*---------------------------------------------------------
	[プレイヤー選択メニュー]
---------------------------------------------------------*/
static void player_select_08_load(void);/*(宣言が必要)*/
static void player_select_10_select(void)/* [選択] */
{
	cg.msg_time = byou60(5);/* 必要 */	/* 約 5 秒 */
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL)) /* 左か右かショットかキャンセルのいづれか */
		{	/* 状態が変わる場合で*/
			/* 状態が変わる場合、ちゃんと SDLサーフェイスを開放 しないとメモリーリークするよ */
			#if (1==USE_KETM_IMAGE_CHACHE)
			unloadbmp_by_surface(player_select_bg0_surface);	// キャッシュに入ってるのでNULLに出来ない。player_select_bg0_surface = NULL;
			unloadbmp_by_surface(player_select_bg2_surface);	// キャッシュに入ってるのでNULLに出来ない。player_select_bg2_surface = NULL;
			#else
			SDL_FreeSurface(player_select_bg0_surface); 		// キャッシュに入ってるのでNULLに出来ない。
			player_select_bg0_surface = NULL;
			SDL_FreeSurface(player_select_bg2_surface); 		// キャッシュに入ってるのでNULLに出来ない。
			player_select_bg2_surface = NULL;
			#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
		//
			if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT)/*左か右の両方*/) /* 左右ボタン入力 */
			{
				is_turn_right = (psp_pad.pad_data & PSP_KEY_RIGHT)?1:0;/* 右なら1, 左なら0 */
				voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
				cg.main_call_func = player_select_08_load;	/* [load] */	/*(戻る)*/
			}
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
			{
				cg.msg_time = (0);/* 必要 */
				{
					/* 状態が変わる場合、ちゃんと SDLサーフェイスを開放 しないとメモリーリークするよ */
					#if (1==DFF_USE_KETM_IMAGE_CHACHE)
					unloadbmp_by_surface(difficulty_select_fg0_surface);	// キャッシュに入ってるのでNULLに出来ない。difficulty_select_fg0_surface = NULL;
					#else
					SDL_FreeSurface(difficulty_select_fg0_surface); 		// キャッシュに入ってるので NULL に出来ない。
					difficulty_select_fg0_surface = NULL;
					#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
				}
				voice_play_menu(VOICE01_MENU_OK, TRACK01_MENU01);/* テキトー */
				if (0!=cg.game_practice_mode)
				{	/* プラクティスモードの場合 */
					cg.main_call_func = stage_select_menu_start; /* ステージ選択メニューの開始 */
				}
				else/* プラクティスモード以外の場合 */
				{
					cg.main_call_func = stage_first_init;			/* ゲーム開始 */
				}
			}
			else
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
			{
				cg.msg_time = (0);/* 必要 */
				voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* 自機死に音は、なるべく重ねない */
				/* 難易度選択メニューに戻る */
				cg.main_call_func = rank_select_menu_start;	/* 難易度選択メニューへ(戻る) */
			}
		}
	}
	move_kanji();
}


/*---------------------------------------------------------

---------------------------------------------------------*/
static int toutatu_wariai;

/* 登場速度は、ゆっくり。 */
	#define SPEED_04_FADE_IN	(4) 	/* 4*FPS_MENU_FACTOR */
/* 退避速度は、速い。 */
	#define SPEED_06_FADE_OUT	(6) 	/* 6*FPS_MENU_FACTOR */


static int move_mode;
/*(計4状態==3状態+1状態)*/
enum
{
	MODE_00_TOUJYOU = 0,			/*(move_mode[0]: メニュー文字登場中)*/
	MODE_01_MENU_SELECT,			/*(move_mode[1]: メニュー選択中)*/
	MODE_02_TAIJYOU_EASY,			/*(move_mode[2]: メニュー文字退避中)*/
	MODE_03_TAIHI_ITI_EASY, 		/*(+退避位置の先読み分)*/
	MODE_04_TAIJYOU_NORMAL, 		/*(move_mode[2]: メニュー文字退避中)*/
	MODE_05_TAIHI_ITI_NORMAL,		/*(+退避位置の先読み分)*/
	MODE_06_TAIJYOU_HARD,			/*(move_mode[2]: メニュー文字退避中)*/
	MODE_07_TAIHI_ITI_HARD, 		/*(+退避位置の先読み分)*/
	MODE_08_TAIJYOU_LUNATIC,		/*(move_mode[2]: メニュー文字退避中)*/
	MODE_09_TAIHI_ITI_LUNATIC,		/*(+退避位置の先読み分)*/
	MODE_10_MAX_JYOUTAI/*(最大値)*/
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
	難易度タグを一つ描画
---------------------------------------------------------*/
static void draw_tag_number(u32 tag_number)
{
	int move_rate256;
	move_rate256	= toutatu_wariai;
	move_rate256	= psp_min(move_rate256, 256);
	move_rate256	= psp_max(move_rate256, 0);
	#if (1)/* 非等分値の計算 */
	{
		u32 i_rate65536;
		i_rate65536 	= (move_rate256 << 8);
	//	i_rate65536 	= (int)(vfpu_ease_in_out(t)*256.0);
		i_rate65536 	= (int)(vfpu_ease_in_out65536(i_rate65536));	/* t65536の等分カウンタ値を使い、非等分になるよう値を修正する。
		非等分の方式は「ease_in_out」これは、始めと最後がゆっくりで間が速いという配分方式。 */
		move_rate256	= (i_rate65536 >> 8);
	}
	#endif
	{
		SDL_Rect ds;
		ds.x	= (0);
		ds.y	= (tag_number << 6);
		ds.w	= (SOZAI_HABA_184);/* 素材幅184[ドット] */ /* 素材幅191[ドット] */
		ds.h	= (SOZAI_TATE_064);/* 素材幅 63[ドット] */
		//
		SDL_Rect dr;
		SDL_Surface *src;
		src 	= difficulty_select_fg0_surface;
		dr.w	= (src->w);
		dr.h	= (63/*src->h*/);
		#if (1)/*(到達割合を考慮して、合成する。)*/
		VR04	= ((my_menu_resource[tag_number].x_offset[move_mode  ])<<8);/*(合成位置[A]t256()形式)*/
		VR05	= ((my_menu_resource[tag_number].y_offset[move_mode  ])<<8);/*(合成位置[A]t256()形式)*/
		VR06	= ((my_menu_resource[tag_number].x_offset[move_mode+1])<<8);/*(合成位置[B]t256()形式)*/
		VR07	= ((my_menu_resource[tag_number].y_offset[move_mode+1])<<8);/*(合成位置[B]t256()形式)*/
		REG_11_GOUSEI_WARIAI256 	= move_rate256;/*(合成割合t256()形式)*/
		CPU_CALL(multiprex_rate_vector);/*(破壊レジスタ多いので注意)*/
		#endif
		// この時点で、
		// VR06: 合成値
		// VR07: 合成値
		// -----------------------
	//	menu_item_my_obj[i].x256 = (VR06)+(VR08);		// 横だけ揺らす。
	//	menu_item_my_obj[i].y256 = (VR07);// +(VR09);	// 縦は揺らさない。(== y offset は使わない。)
		#if (1)/*(表示位置)*/
		dr.x	= ((VR06)>>8);/*(X位置)*/
		dr.y	= ((VR07)>>8);/*(Y位置)*/
	//	dr.x	= (set_x_offset);
	//	dr.y	= (set_y_offset);
		#endif
		{
			int set_alpha256;
			if ((tag_number==((unsigned)cg_VR20_game_difficulty)))/*(選択されている場合)*/
			{
				dr.x -= (16);/*(左にずらす)*/
				dr.y -= ( 8);/*(上にずらす)*/
				set_alpha256 = (255);/*(半透明なし)*/
			}
			else/*(選択されていない場合)*/
			{
				/*(基準位置から、ずらさない)*/
				set_alpha256 = (64);// (127);/*(半透明あり)*/
			}
		//	SDL_SetColorKey(src, (SDL_SRCCOLORKEY), 0x00000000);
			SDL_SetAlpha(src, SDL_SRCALPHA, set_alpha256);/*(半透明設定、転送元画像の半透明が有効)*/
		}
		PSPL_UpperBlit(src, &ds, cg.sdl_screen[SDL_00_VIEW_SCREEN], &dr);/*(仮想画面へ描画)*/
	}
}


/*---------------------------------------------------------
	難易度タグを四つ描画
---------------------------------------------------------*/
static void move_tag_4(void)/* [描画444] */
{
	int i;
	for (i=0; i<4; i++)
	{
		draw_tag_number(i);
	}
}


/*---------------------------------------------------------
	[プレイヤー選択メニュー]
---------------------------------------------------------*/
static void player_select_09_move_draw(void)/* [描画1] */
{
//	sp_scale256 -= (18);	// 18 == 255/14[枚]。14枚描画する。/*(古い奴)*/
//	sp_scale256 -= (15);	// 15 == 255/17[枚]。17枚描画する。 [立ち絵がPSPL描画] + [BGがPSPL描画]の場合の設定値(15)。(-r35u1)
	sp_scale256 -=	(8);	//	8 == 255/32[枚]。32枚描画する。 [立ち絵がGu描画] + [BGがPSPL描画]の場合の設定値(15)。(r35u2-)
	if (0 > sp_scale256)
	{
		sp_scale256 = (0);
		cg.main_call_func = player_select_10_select;/* [選択] */
	}
	SDL_SetAlpha(player_select_bg0_surface, SDL_SRCALPHA, (255-sp_scale256) );
	PSPL_UpperBlit(player_select_bg2_surface, NULL, cg.sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	PSPL_UpperBlit(player_select_bg0_surface, NULL, cg.sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	/* プレイヤー(1&2) / 背景(1&2) / 描画 */
	{
		int aaa;
		/*(Guの場合、会話スプライトを使う)*/
		#define PLAYER_OBJ_LOCATE_X 	(256-32)		/* cx256(r35) 素材[256x256] */
		#define PLAYER_OBJ_LOCATE_Y 	(8) 			/* cy256(r35) 素材[256x256] */
		kaiwa_sprite[0].center.y256 = ((PLAYER_OBJ_LOCATE_Y) << 8);
		sp_diff256 += (sp_scale256);
		aaa = (((sp_diff256)) >> 8)-16;
		if (is_turn_right)	{aaa = (-(aaa));}
		kaiwa_sprite[0].center.x256 = ((PLAYER_OBJ_LOCATE_X) << 8) + (aaa << 8);
		kaiwa_sprite[0].color32 = ((	sp_scale256) << 24) | (0x00ffffff);/*(透明)*/
		//
		kaiwa_sprite[1].center.y256 = ((PLAYER_OBJ_LOCATE_Y) << 8);
		sp_diff256 += (sp_scale256);
		aaa = ((sp_diff256 >> 8)-16);
		if (1-is_turn_right)	{aaa = (-(aaa));}
		kaiwa_sprite[1].center.x256 = ((PLAYER_OBJ_LOCATE_X) << 8) + (aaa << 8);
		kaiwa_sprite[1].color32 = ((255-sp_scale256) << 24) | (0x00ffffff);/*(透明)*/
	}
	/* 難易度タグを描画 */
	move_tag_4();
	#if 0
	draw_tag_number(cg_VR20_game_difficulty);
	#endif
	move_kanji();
}


/*---------------------------------------------------------
	選択プレイヤー画像と背景の名前を決める。
---------------------------------------------------------*/
static void set_file_name(u8 is_pl)
{
	strcpy(my_file_common_name, (char*)DIRECTRY_NAME_DATA_STR "/select/" "pl00.png");
	my_file_common_name[DIRECTRY_NAME_DATA_LENGTH+(10)] = '0'+(cg_game_select_player);
	my_file_common_name[DIRECTRY_NAME_DATA_LENGTH+(11)] = '0'+(is_pl);
}


/*---------------------------------------------------------
	[プレイヤー選択メニュー]選択プレイヤー画像と背景をロード。
---------------------------------------------------------*/
static MAIN_CALL_FUNC(player_select_08_load)/* [load] */
{
	cg_game_select_player &= (0x07);
	//
	set_file_name(0);	strcpy(&my_resource[TEX_09_TACHIE_L+0].file_name[0], (&my_file_common_name[0]) );
						kaiwa_sprite[0].draw_flag = (1);	/* 描画する。 */
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
						kaiwa_sprite[1].draw_flag = (1);	/* 描画する。 */
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
	kanji_set_x_position = (24);/*(漢字移動先座標設定)*/
	draw_spec_message(spec_message_00_SELECT_PLAYER);	// [プレイヤー選択]状態をメッセージ表示。
	cg.main_call_func = player_select_09_move_draw;
}


/*---------------------------------------------------------
	キャンセル音を鳴らして、タイトルメニューへ移動。
	共通サブ。(外部のあちこちから呼ばれる)
---------------------------------------------------------*/
extern void menu_cancel_and_voice(void)
{
	voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* 自機死に音は、なるべく重ねない */
	cg.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
}


/*---------------------------------------------------------
	[難易度選択メニュー:文字退避]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_07_moji_taihi)/* [文字退避] */
{
	toutatu_wariai += (SPEED_06_FADE_OUT);
	if (255 <= toutatu_wariai)
	{
		toutatu_wariai = (0);
		move_mode++;// (3=2+1=easy, 5=4+1=normal, 7=6+1=hard, 9=8+1=lunatic)になる。
		cg.main_call_func = player_select_08_load;
	}
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	move_tag_4();
	/*(?)*/move_kanji();/*(現状意味無いっぽい)*/
}


/*---------------------------------------------------------
	[難易度選択メニュー]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_04_initialize_value);/*(宣言が必要)*/
static MAIN_CALL_FUNC(rank_select_06_select)/* [選択] */
{
	cg.msg_time = byou60(5);/* 必要 */	/* 約 5 秒 */
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL)) /* 左か右かショットかキャンセルのいづれか */
		{	/* 状態が変わる場合で*/
		//
			if (psp_pad.pad_data & (PSP_KEY_UP|PSP_KEY_DOWN)/*上か下の両方*/ ) /* 上下ボタン入力 */
			{
				if (psp_pad.pad_data & PSP_KEY_UP)
						{cg_VR20_game_difficulty--; cg_VR20_game_difficulty = psp_max(cg_VR20_game_difficulty, (0)	 );}	/* メニュー上で停止 */
				else	{cg_VR20_game_difficulty++; cg_VR20_game_difficulty = psp_min(cg_VR20_game_difficulty, (4-1) );}	/* メニュー下で停止 */
				voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
				cg.main_call_func = rank_select_04_initialize_value; /* [load] */	/*(戻る)*/
			}
			if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
			{
				cg.msg_time = (0);/* 必要 */
				voice_play_menu(VOICE01_MENU_OK, TRACK01_MENU01);/* テキトー */
				/* 通常／プラクティス、ゲーム開始 */
				// static void player_opt_init(void)吸収。なし
				{
					is_turn_right = 0;/* 必要 */
					(cg_game_select_player)++;/* プログラムplayer_select_work()の都合上調整 */	/*player_select_work()::[init]*/
				}
				cg.main_call_func = rank_select_07_moji_taihi;
				move_mode++;// (2)になる。
				move_mode += ((cg_VR20_game_difficulty)<<1);// (2=easy, 4=normal, 6=hard, 8=lunatic)になる。
			}
			else
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
			{
				cg.msg_time = (0);/* 必要 */
				{
					/* 状態が変わる場合、ちゃんと SDLサーフェイスを開放 しないとメモリーリークするよ */
				//	unloadbmp_by_surface(difficulty_select_fg0_surface);	// キャッシュに入ってるのでNULLに出来ない。difficulty_select_fg0_surface = NULL;
					/* 状態が変わる場合、ちゃんと SDLサーフェイスを開放 しないとメモリーリークするよ */
					#if (1==DFF_USE_KETM_IMAGE_CHACHE)
					unloadbmp_by_surface(difficulty_select_fg0_surface);	// キャッシュに入ってるのでNULLに出来ない。difficulty_select_fg0_surface = NULL;
					#else
					SDL_FreeSurface(difficulty_select_fg0_surface); 		// キャッシュに入ってるのでNULLに出来ない。
					difficulty_select_fg0_surface = NULL;
					#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
				}
				menu_cancel_and_voice();	/* タイトルメニューへ移動 */
			}
		}
	}
	move_kanji();
}

/*---------------------------------------------------------
	[難易度選択メニュー]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_05_move_draw)/* [描画1] */
{
	sp_scale256 -= 15/*18*/;
	if (0 > sp_scale256)
	{
		sp_scale256 = (0);
		cg.main_call_func = rank_select_06_select;/* [文字集まる] */
	}
//	SDL_SetAlpha(player_select_bg0_surface, SDL_SRCALPHA, (255-sp_scale256) );
//	PSPL_UpperBlit(player_select_bg0_surface, NULL, sdl_screen[SDL_00_VIEW_SCREEN], NULL);
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	move_tag_4();
	move_kanji();/*(現状意味無いっぽい)*/
}

/*---------------------------------------------------------
	[難易度選択メニュー]変数等を開始状態へ初期化設定。
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_04_initialize_value)
{
	cg_VR20_game_difficulty &= (0x03);
	//
	sp_scale256 	= (255);
	sp_diff256		= (0);
	//
	kanji_set_x_position = (256+32);/*(漢字移動先座標設定)*/
	draw_spec_message(spec_message_01_SELECT_RANK); 	// [難易度選択]状態をメッセージ表示。
	cg.main_call_func = rank_select_05_move_draw;
}

/*---------------------------------------------------------
	[難易度選択メニュー:文字集まる]
---------------------------------------------------------*/
static MAIN_CALL_FUNC(rank_select_03_atumaru)/* [文字集まる] */
{
	toutatu_wariai += (SPEED_06_FADE_OUT);
	if (255 <= toutatu_wariai)
	{
		toutatu_wariai = (0);
		move_mode++;// (1)になる。
		cg.main_call_func = rank_select_04_initialize_value;/* [選択] */
	}
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	move_tag_4();
	/*(?)*/move_kanji();/*(現状意味無いっぽい)*/
}


/*---------------------------------------------------------
	[難易度選択メニュー#02]の初期化設定。(やり直しの場合はここから)
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
		#if (1)/*(漢字関連の初期化)*/
		set_kanji_origin_xy(24, 64);/*(表示原点の設定)*/
		set_kanji_origin_kankaku(19);/*(字間を少し広げる)*/
		set_kanji_hide_line(ML_LINE_99_MAX);/*(全行表示する。)*/
		kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
		cg.msg_time = (65536);	/* 約 18 分 */
		#endif
	{
		/* 8行目のみ特殊な位置へ移動。 */
		ml_font[ML_LINE_08].x		= (16);/* X位置 */
		ml_font[ML_LINE_08].y		= (16);/* Y位置 */
	}
//		kanji_window_clear_line(5); /* 漢字ウィンドウの1行目(==0)の内容を消す。 */
//		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (5) ); /* カーソルを1行目(==0)へ移動 */
//		//
//		kanji_color((9));
//		strcpy(my_font_text, "モードを選択してね"	 );
//		kanji_draw();
	}
	kaiwa_obj_set_256();
	#if (1)
	kaiwa_all_obj_draw_on_off(0/*off*/);/*(src/mohoufu/menu/kaiwa.c 会話objを描画しない。)*/
	#endif
	/*(会話objをフル画面で表示)*/
	{	/*(フル画面=="Story" モード専用の立ち絵移動)*/
		cg.side_panel_draw_flag 		= (0);/*(右サイドのスコアパネル表示off)*/
	}
	//
	move_mode			= (0);
	toutatu_wariai		= (0);
	cg.main_call_func = rank_select_03_atumaru;
}
