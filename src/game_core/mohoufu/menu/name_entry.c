
// このファイルには2つユニットがあります。
// 1. ハイスコア表示デモ画面(夢の記録)
// 2. ハイスコア名前入力、登録画面

//////////////////////////////////////////////////////////////////

#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)
---------------------------------------------------------*/
#include "111_my_file.h"/*(bg読みこみ。)*/

#include "kanji_system.h"

#define MAX_7_LINES (7/*6*/)

global SCORE_FORMAT high_score_table[MAX_8_SAVE_PLAYERS][MAX_5_RANKING/*5*/];

/*---------------------------------------------------------
	ｎ位タイトル描画サブ
	サーフェイスを作成するが、開放はしないので注意。
	-------------------------------------------------------
	このサブルーチンは、名前入力画面でも使います。
---------------------------------------------------------*/
/*static*/static/*extern*/ void high_score_render_sub(int show_player_num, u32 iii)
{
	sprintf(my_font_text,
		"%1d "		/* 順位 */
		"%-8s " 	/* プレイヤー名 */
		"%09d0" 	/* スコア */
		"[%1d]",	/* 到達ステージ */
	//
		(iii+1),												/* 順位 */
		high_score_table[(show_player_num)][iii].name,			/* プレイヤー名 */
		(int)high_score_table[(show_player_num)][iii].score,	/* スコア */	/* gcc 4.3.5 */
		high_score_table[(show_player_num)][iii].final_stage	/* 到達ステージ */
	);
}
/*
	warning: format '%09d' expects type 'int', but argument 5 has type 'u32'
	注意: ５番目の引数は signed int(符号付32bit) なんだけど、渡すのは u32(符号無し32bit) だよ。
*/
/*
	4.3.3 では u32 -> s32 の暗黙変換は、warningにならなかった。(基本的に -std=gnu99 で -Werror の場合)
	4.3.5 では u32 -> s32 の暗黙変換は、warningになるっぽい。
	コンパイラオプションで抑制できると思うけど良くわかんないし。
	実際 psp は signed と unsigned では 最適化できるコードが大分違うから、その方が都合は良いんだけど。
*/


/*---------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)
---------------------------------------------------------*/

/*local static*/

typedef struct
{
	int x256;
	int y256;
//
	int amplifier256;		/* 横のズレ量の割合。 amplifier x offset */
	int phase256;			/* 横のズレ量。 phase x offset */
	int phaseout256;		/* 横のズレ量。 phase x offset */
	int direction;			/* ズレる方向 */
	int move_done_flag; 	/* 移動完了したか、してないかの状態 */
//	定数
	int xg256;
	int yg256;
	int amplifier_speed256;
	int phase_speed256;
	int font_color;
} RR_OBJ;
enum
{
	FLAG_00_MOVING_NOW = 0, 	/* 移動中。 */
	FLAG_01_MOVE_DONE,			/* 移動完了。 */
};
enum
{
	FLAG_00_DIRECTION_TO_LEFT = 0,		/* [←]左へ移動。/ slide-in */
	FLAG_01_DIRECTION_TO_RIGHT, 		/* [→]右へ移動。/ slide-out */
};
static RR_OBJ result_my_obj[MAX_7_LINES/*6*/];

static int move_done_lines; 			/* 移動完了した行の数 */
static int show_player_num; 			/* スコア戦歴表示中のプレイヤー番号 */


/*---------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)(文字移動用)
---------------------------------------------------------*/

static void move_result(void)
{
	u32 i;
	for (i=0; i<MAX_7_LINES; i++)
	{
		if (FLAG_00_MOVING_NOW==result_my_obj[i].move_done_flag)	/* 移動は必要？ */
		{
			result_my_obj[i].x256 = ((result_my_obj[i].xg256) );
			result_my_obj[i].y256 = ((result_my_obj[i].yg256) );
			if (FLAG_00_DIRECTION_TO_LEFT==result_my_obj[i].direction)		/* 移動する向き */
			{	/* [←]左へ移動。/ slide-in */
				result_my_obj[i].amplifier256 -= result_my_obj[i].amplifier_speed256;
				if (result_my_obj[i].amplifier256 <= t256(0.3) )
				{
					result_my_obj[i].move_done_flag = (FLAG_01_MOVE_DONE);	/* 移動完了 */
					move_done_lines++;
				}
				else
				{
					result_my_obj[i].phase256 += result_my_obj[i].phase_speed256;/*fps_factor*/
					result_my_obj[i].x256 += ((result_my_obj[i].phase256*result_my_obj[i].amplifier256)>>8);
				}
			}
			else
		//	if (FLAG_01_DIRECTION_TO_RIGHT==result_my_obj[i].direction) 	/* 移動する向き */
			{	/* [→]右へ移動。/ slide-out */
				result_my_obj[i].phaseout256 += result_my_obj[i].phase_speed256;/*fps_factor*/
				result_my_obj[i].x256 += ((result_my_obj[i].phaseout256*result_my_obj[i].amplifier256)>>8);
				/* slide-out */
				result_my_obj[i].amplifier256 += result_my_obj[i].amplifier_speed256;
				if (
						(t256(PSP_WIDTH480)  < result_my_obj[i].x256)	/* 画面外 */
					)
				{
					result_my_obj[i].move_done_flag = (FLAG_01_MOVE_DONE);	/* 移動完了 */
					move_done_lines++;
				}
			}
		}
	}
}


/*---------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)
---------------------------------------------------------*/
	static char result_chars[MAX_7_LINES/*6*/][64];

static void result_font16_render_new_surface(void)
{
	u32 i;
	for (i=0; i<MAX_7_LINES; i++)
	{
		if (i<5)
		{
			high_score_render_sub(show_player_num, i);/*FONT16W*/	/*白*/
			result_my_obj[i].font_color 	= (7);
		}
		else
		if (5==i)
		{
			strcpy(my_font_text, (char*)JAPAN("夢の記録", "Score Ranking"));
			result_my_obj[i].font_color 	= (9);
		}
		else
		if (6==i)
		{
			static const/*const*/ char *score_name[MAX_08_PLAYER] =
			{
			/* 0==*/JAPAN("博麗 霊夢 A (霊符)", 	"Hakurei Reimu A (spirit card)"),
			/* 1==*/JAPAN("博麗 霊夢 B (夢符)", 	"Hakurei Reimu B (dream card)"),
			/* 2==*/JAPAN("霧雨 魔理沙 A (魔符)",	"Kirisame Marisa A (devil card)"),
			/* 3==*/JAPAN("霧雨 魔理沙 B (恋符)",	"Kirisame Marisa B (lovely card)"),
			/* 4==*/JAPAN("レミリア スカーレット",	"Remilia Scarlet"),
			/* 5==*/JAPAN("西行寺 幽々子",			"Saigyouzi Yuyuko"),
			/* 6==*/JAPAN("チルノ (氷符)",			"Chrno A (ice card)"),
			/* 7==*/JAPAN("チルノ (?H符)",			"Chrno Qute (cute card)"),
			};
			strcpy(my_font_text, (char*)score_name[(show_player_num)]);
			result_my_obj[i].font_color 	= (8);
		}
		strcpy(&result_chars[i][0], 	my_font_text);
		//
		{
			enum
			{
				RESULT_DATA_00_XG256 = 0,
				RESULT_DATA_01_YG256,
				RESULT_DATA_02_PHASE_SPEED256,
				RESULT_DATA_03_MAX		/* 最大数 */
			};
			static const signed int result_const_status[RESULT_DATA_03_MAX][MAX_7_LINES] =
			{
				{/* RESULT_DATA_00_XG256 */
					/*(t256( 4)*0) +*/ t256(64),	/*1ST*/ 	/* 20*/
					/*(t256( 4)*1) +*/ t256(64),	/*2ND*/ 	/* 20*/
					/*(t256( 4)*2) +*/ t256(64),	/*3RD*/ 	/* 20*/
					/*(t256( 4)*3) +*/ t256(64),	/*4TH*/ 	/* 20*/
					/*(t256( 4)*4) +*/ t256(64),	/*5TH*/ 	/* 20*/
					t256( (64+32)/*30*/ ),			/*"RESULT OF SCORE"*/
					t256( (64-32)/*30*/ ),			/*"REIMU"*/
				},
				{/* RESULT_DATA_01_YG256 */
					(t256( (20*0)+(144+4)) ),		/*1ST*/ 	// (25*0)+(110+25+5)/*150*/
					(t256( (20*1)+(144+4)) ),		/*2ND*/ 	// (25*1)+(110+25+5)/*150*/
					(t256( (20*2)+(144+4)) ),		/*3RD*/ 	// (25*2)+(110+25+5)/*150*/
					(t256( (20*3)+(144+4)) ),		/*4TH*/ 	// (25*3)+(110+25+5)/*150*/
					(t256( (20*4)+(144+4)) ),		/*5TH*/ 	// (25*4)+(110+25+5)/*150*/
					t256(110),						/*"RESULT OF SCORE"*/
					t256(128-2),					/*"REIMU"*/
				},
				{/* RESULT_DATA_02_PHASE_SPEED256 */
					4,		/*1ST*/
					4,		/*2ND*/
					4,		/*3RD*/
					4,		/*4TH*/
					4,		/*5TH*/
					6,		/*"RESULT OF SCORE"*/
					5,		/*"REIMU"*/
				},
			};
			result_my_obj[i].xg256				= result_const_status[RESULT_DATA_00_XG256][i];
			result_my_obj[i].yg256				= result_const_status[RESULT_DATA_01_YG256][i];
			result_my_obj[i].phase_speed256 	= result_const_status[RESULT_DATA_02_PHASE_SPEED256][i];
		}
		result_my_obj[i].amplifier_speed256 	= t256(10.0);//t256(1.0);
		result_my_obj[i].x256					= 0;					//	result_my_obj[5]->x 	= 0/*30*/;
		result_my_obj[i].y256					= 0/*(i*25+110)*/;		//	result_my_obj[5]->y 	= 0/*50*/;
	}
	for (i=0; i<MAX_7_LINES/*5*/; i++)
	{
		result_my_obj[i].phase256			= (i<<6);/*(0)*/
		result_my_obj[i].phaseout256		= ((4-i)<<6);/*(5<<6)*/
		result_my_obj[i].amplifier256		= t256(100);/*300*/
		result_my_obj[i].direction			= (FLAG_00_DIRECTION_TO_LEFT);	/* [←]左へ移動。/ slide-in */
		result_my_obj[i].move_done_flag 	= (FLAG_00_MOVING_NOW);
	}
}


/*---------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)(本体)
---------------------------------------------------------*/

/*---------------------------------------------------------
	SDLサーフェイスに描画する。
---------------------------------------------------------*/

static void yume_no_kiroku_draw(void)
{
	/*(背景描画)*/
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	{
		/* 移動 */
		move_result();
		/* 描画 */
		{
			u32 yyy18;
			yyy18 = (0);/* Y位置 */
			u32 i;
			for (i=0; i<MAX_7_LINES; i++)
			{
				kanji_window_clear_line(i); 	/* 漢字ウィンドウの4行目(==3)の内容を消す。 */
				set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18));	/* カーソルを4行目(==3)へ移動 */
				ml_font[i].x		= ((result_my_obj[i].x256)>>8);
				ml_font[i].y		= ((result_my_obj[i].y256)>>8);
				ml_font[i].timer	= ML_ON;
				strcpy(my_font_text, (char*)&result_chars[i][0] );
				kanji_color(result_my_obj[i].font_color/*9*/);
				kanji_draw();
				yyy18 += (18);
			}
		}
	}
}


/*---------------------------------------------------------
	do slide out now.
	退場中。
	終わったら分岐する
---------------------------------------------------------*/

static MAIN_CALL_FUNC(result_05_do_slide_out_now)
{
	if (move_done_lines==MAX_7_LINES)
	{
		cg.main_call_func = cg.return_call_func;	/* 「また見るよ」&「もうおしまい」移動の状態を反映させる。 */
		/* 注意：既にフォント解放してるから描画できないよ */
		return;/* 描画するとハングアップするので、ここで強制リターン。 */
	}
	else
	{
		yume_no_kiroku_draw();//要る(退場描画)
	}
}


/*---------------------------------------------------------
	退場準備。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(result_04_set_slide_out)
{
	{
		move_done_lines = 0;
		int i;
		for (i=0; i<MAX_7_LINES; i++)
		{
			result_my_obj[i].direction		= (FLAG_01_DIRECTION_TO_RIGHT); 	/* [→]右へ移動。/ slide-out */
			result_my_obj[i].move_done_flag = (FLAG_00_MOVING_NOW);
		}
		cg.main_call_func = result_05_do_slide_out_now;
	}
//	yume_no_kiroku_draw();//要らない
}


/*---------------------------------------------------------
	キーチェック。
---------------------------------------------------------*/
static MAIN_CALL_FUNC(result_01_set_location);/*(宣言が必要)*/
static MAIN_CALL_FUNC(result_03_pad_check)
{
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		/* 次の人の戦歴をまた見る */
		if (psp_pad.pad_data & (PSP_KEY_RIGHT|PSP_KEY_LEFT|PSP_KEY_UP|PSP_KEY_DOWN))	/* PSP_KEY_SHOT_OKが押された */
		{
			show_player_num++;										/* 次の人にする */
		//	if (/*4*/7<show_player_num) 	{show_player_num=0;}	/* 最後まで見たら始めから見る */
			show_player_num &= (0x07);								/* 最後まで見たら始めから見る */
			cg.return_call_func 	= result_01_set_location;		/* また見るの場合の移動先を設定(反映するのは、まだ先) */
			cg.main_call_func		= result_04_set_slide_out;
		}
		/* 見るのやめてメニューに戻る */
		else
		if (psp_pad.pad_data & (PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL|PSP_KEY_OPTION|PSP_KEY_PAUSE|PSP_KEY_SELECT))
		{
			cg.return_call_func 	= title_menu_start; 			/* タイトルメニューへ移動先を設定(反映するのは、まだ先) */
			cg.main_call_func		= result_04_set_slide_out;
		}
	}
//	yume_no_kiroku_draw();//要らない
}


/*---------------------------------------------------------
	登場中。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(result_02_do_slide_in_now)
{
	if (move_done_lines==MAX_7_LINES)
	{
		cg.main_call_func		= result_03_pad_check;
	}
	yume_no_kiroku_draw();//要る(登場描画)
}


/*---------------------------------------------------------
	登場準備。新しい戦績の文字をレンダリングする。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(result_01_set_location)
{
	move_done_lines 		= 0;
	result_font16_render_new_surface();
	cg.main_call_func		= result_02_do_slide_in_now;
}


/*---------------------------------------------------------
	ハイスコア表示デモ画面(夢の記録)(開始、初期設定)
---------------------------------------------------------*/

extern MAIN_CALL_FUNC(yume_no_kiroku_start)
{
	//void result_init(void)
	show_player_num 		= ((cg_game_select_player) & 0x07);/*0*/	/* 現在選択されているプレイヤーから記録を表示開始する。 */
	psp_move_screen(MODE_00_PUSH);/*(現在の表示画面を裏画面に保存)*/
	cg.msg_time 			= (65536);	/* 約 18 分 */
	cg.main_call_func		= result_01_set_location;/* 動作先 */
//	return_call_func		= result_01_set_location;/* 戻り動作先、「また見るよ」に設定 */
}


//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ハイスコア名前入力、登録画面
---------------------------------------------------------*/

//	/*static*/extern void high_score_render_sub(int show_player_num, int iii, int bbb);

/*---------------------------------------------------------
	ハイスコア名前入力、登録画面
---------------------------------------------------------*/

#define KEYBOARD_W10	(16)
#define KEYBOARD_H04	(5)
#define KEYBOARD_M40	((KEYBOARD_W10)*(KEYBOARD_H04))

#define MAX_40_LETTER	(KEYBOARD_M40)
static SDL_Surface *letter_surface[MAX_40_LETTER];

typedef struct
{
	int xpos;
	int ypos;
	u8 ascii;
	u8 dummy_scale256;
} LETTER;
static LETTER letter[MAX_40_LETTER];

static int now_select_name_chr;
static /*un*/signed int sel_aaa;

static int plate_x;
static int plate_y;


/* ランキング表示位置 */
#define RANK_LOCATE_OFS_X_32		(32)		/*	 8 24 */
#define RANK_LOCATE_OFS_Y_40		(40)

#define KEYBORD_LOCATE_OFS_X_064	(64+16) 	/*	32 48  30 */
#define KEYBORD_LOCATE_OFS_Y_168	(168)		/* 160 84 100 */


/*---------------------------------------------------------
	ハイスコア名前入力、登録画面、動作(の子関数)[表示部分]
---------------------------------------------------------*/
static char *ranking_enter_name_string;

static void name_entry_draw(void)
{
	/*(背景描画)*/
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	//
	SDL_Rect s;
	SDL_Rect r;
	s.x = 0;
	s.y = 0;
	/* キーボード文字を描画 */
	{
		/*unsigned*/ int i;
		for (i=0; i<KEYBOARD_M40; i++)
		{
			r.w 	= s.w	= (letter_surface[i]->w);
			r.h 	= s.h	= (letter_surface[i]->h);
			r.x = (letter[i].xpos);
			r.y = (letter[i].ypos);
			if (i == sel_aaa)/* 選択中文字==キーボード文字 */
			{
//				letter[i].scale256 = t256(1.6);
				{
					static int angle65536;		/*=0*/
					angle65536 += cv65536r((5));	/*fps_factor*/
				//	mask1024(angle1024);
				//	{
				//		int sin_value_t256; 		//	sin_value_t256 = 0;
				//		int cos_value_t256; 		//	cos_value_t256 = 0;
				//		int256_sin cos65536(angle65536, &sin_value_t256, &cos_value_t256);
				//		r.x 	+= ((sin_value_t256)>>(5));
				//		r.y 	+= ((sin_value_t256)>>(6));
				//	}
					//------------------
					HATSUDAN_R11_speed256	= ((256)>>5);
					HATSUDAN_R13_angle65536 = (angle65536);
					CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
					r.x 		+= (VR07);//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
					r.y 		+= (VR07>>1);//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
					//------------------
				}
			}
//			else/* 選択中文字 != キーボード文字 */
//			{
//				letter[i].scale256 = t256(1.0);
//			}
			/* 描画 */
							SDL_SetAlpha(	letter_surface[i], SDL_SRCALPHA, /*bg_alpha_aaa*/(255));
			/*blit_scaled*/ PSPL_UpperBlit(letter_surface[i], &s, cg.sdl_screen[SDL_00_VIEW_SCREEN], &r);
		}
	}
	/* 決定文字を描画 */
/*	if (0 <= sel_aaa)*/
	{
		strcpy(my_font_text, ranking_enter_name_string);
		SDL_Surface *tmp_surface;
		tmp_surface 	= font16_render_new_surface();
	//	s.x 	= 0;
	//	s.y 	= 0;
		r.w 	=	s.w 	= tmp_surface->w;
		r.h 	=	s.h 	= tmp_surface->h;
		r.x 	= plate_x;
		r.y 	= plate_y;
							SDL_SetAlpha(	tmp_surface, SDL_SRCALPHA, /*bg_alpha_aaa*/(255));
		/*blit_scaled*/ 	PSPL_UpperBlit(tmp_surface, &s, cg.sdl_screen[SDL_00_VIEW_SCREEN], &r);
		SDL_FreeSurface(tmp_surface);
	}
}


/*---------------------------------------------------------
	ハイスコア名前入力、登録画面、動作[キー入力＆状態変更部分]
---------------------------------------------------------*/


//static MAIN_CALL_FUNC(name_entry_local_final)
//{
//}
#define MY_CODE_DEL_KEY 	(0x7e)
#define MY_CODE_OK_KEY		(0x7f)

static MAIN_CALL_FUNC(name_entry_local_work)
{
	if (0 == psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		/* 斜め移動はしない */
			 if (psp_pad.pad_data & PSP_KEY_LEFT )	{	sel_aaa--;				if (sel_aaa <  (0)) 				{	sel_aaa  = (KEYBOARD_M40-1);}	}
		else if (psp_pad.pad_data & PSP_KEY_RIGHT)	{	sel_aaa++;				if (sel_aaa == (KEYBOARD_M40))		{	sel_aaa  = (0); 			}	}
		else if (psp_pad.pad_data & PSP_KEY_UP	 )	{	sel_aaa-=KEYBOARD_W10;	if (sel_aaa <  (0)) 				{	sel_aaa += (KEYBOARD_M40);	}	}
		else if (psp_pad.pad_data & PSP_KEY_DOWN )	{	sel_aaa+=KEYBOARD_W10;	if (sel_aaa >  (KEYBOARD_M40-1))	{	sel_aaa -= (KEYBOARD_M40);	}	}
		//
		if (psp_pad.pad_data & PSP_KEY_SHOT_OK) /* 入力決定 == 入力決定ボタンが押された。 */
		{
			if (MY_CODE_DEL_KEY==(letter[sel_aaa].ascii))
			{/* [削除キー](DEL)を決定した場合。 Delete last character */
				goto delete_last_character;
			}
			else
			if (MY_CODE_OK_KEY==(letter[sel_aaa].ascii))
			{/* [入力終了キー](OK)を決定した場合。 Input completed. 入力終了。 Eingabe abgeschlossen. */
				goto agree_entry;
			}
			else
			{
				if (8 > now_select_name_chr) /* 8[3]文字以下決定した場合は文字入力。  3 chrs, name input entry. */
				{
					ranking_enter_name_string[now_select_name_chr] = letter[sel_aaa].ascii;
					now_select_name_chr++;
				}
				else /* 8[3]文字以上の決定した場合は自動的に入力終了キーを押したことにする。 */
				{
					sel_aaa = (KEYBOARD_M40-1);/* [入力終了キー](OK)を押したのと同じ。 force set [OK] */
				}
			}
		}
		else if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL/*PSP_KEY_OPTION*/)	/* キャンセルボタンが押された。 */
		{
		delete_last_character:
			if (0 < now_select_name_chr) /* 名前入力の入力文字がある場合で。  at first chr? */
			{
				now_select_name_chr--;				/* [削除キー](DEL) が入力されているので、その分戻る。 */
				ranking_enter_name_string[now_select_name_chr] = ' ';	/* 消す */
			}
		}
		else if (psp_pad.pad_data & PSP_KEY_PAUSE)		/* 終了(強制決定)ボタンが押された。 */
		{
		agree_entry:	/* 入力終了決定 */
			if (0 < now_select_name_chr)	// 名前入力の入力文字がある場合で。何か入力されている場合で。
			{
			//	cg.main_call_func = name_entry_local_final;/*(解放処理)*/
				cg.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
				/*(有効にしても大丈夫な気もするけど、せっかくハイスコア出してハングアップすると、がっかりするし。)*/
				/*(pspはmallocがあやしーのでハングアップする可能性がある。模倣風の場合BGMにmp3(libmad)とか使うと高確率でハングアップする。)*/
				#if (0)/*(解放処理)*/
				/* キーボードの文字を開放する */
				{	int i;
					for (i=0; i<KEYBOARD_M40; i++)
					{
						#if (1)
					//	if (letter_surface[i])
						{
							/* ここでハングアップ */
							SDL_FreeSurface(letter_surface[i]);
						}
						#endif
					}
				}
				/*(注意：既にフォント解放してるから描画できないよ)*/
				return;/*(描画するとハングアップするので、ここで強制リターン。)*/
				#endif
			}
		}
	}
	name_entry_draw();/*描画部分*/
}


//static MAIN_CALL_FUNC(name_entry_init)
extern MAIN_CALL_FUNC(name_entry_start)
{
	int i;
	int j;
	/* キーボード(の文字)の初期化 */
	{
		my_font_text[1] = '\0';/* 0 == EOS 文字列の終わり / End of String */
		for (i=0; i<(KEYBOARD_M40); i++)
		{
				/* 現在定義されているフォントが少ない為 */
			//	"ABCDEFGHIJKLMNOP"
			//	"QRSTUVWXYZ..:://"		/* 注意:スコア記録形式を変えるまで ',' 文字は使えない。 */
			//	"ABCDEFGHIJKLMNOP"
			//	"QRSTUVWXYZ--//--"
			//	"0123456789[]!?" /*("DEL")*/"/"  /*("OK")*/"!"
			const char str_aaa[(KEYBOARD_M40)] = /* 80==16x5  8*5==40==38(chars)+1(dummy)+1(0) */
			{
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.', '$', ':', ';', '|', '@', 	/* 注意:スコア記録形式を変えるまで ',' 文字は使えない。 */
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '+', '-', '/', '*', '=', '%',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', ')', '!', '?', MY_CODE_DEL_KEY, MY_CODE_OK_KEY,
			};
			u8 c;
			c = str_aaa[i];
			my_font_text[0] = c;
			letter[i].ascii = c;
			letter_surface[i] = font16_render_new_surface(); /* */
		}
	}
	{
		int k;
		k = 0;
		for (j=0; j<(KEYBOARD_H04*20);/*(4*36)*/ j+=(20))	 /*(36)*/ /*25*/
		{
			for (i=0; i<(KEYBOARD_W10*20);/*(10*30)*/ i+=(20))/*(30)*/ /*25*/
			{
				letter[k].xpos		= (i) + (KEYBORD_LOCATE_OFS_X_064);
				letter[k].ypos		= (j) + (KEYBORD_LOCATE_OFS_Y_168);
			//	letter[k].scale256	= t256(1.0);/*0.0*/ 	/* キーボード(の文字)の拡大率を初期化 */
				k++;
			}
		}
	}

	/* 新たにランクインしたスコア位置を調べる */
	for (i=0; i<5; i++)
	{
		if (cg_game_score > high_score_table[(cg_game_select_player)][i].score)
		{
			break;
		}
	}
	/* 以降 i がランクインした位置。判りにくいので、別名で定義しとく。 */
	#define 	my_rank 	i
	/* スコア位置より下を移動させる */
	for (j=4; j>my_rank; j--)
	{
		high_score_table[(cg_game_select_player)][j] = high_score_table[(cg_game_select_player)][j-1];
	}
	/* 新たにランクインしたスコア位置へ挿入 */
	high_score_table[(cg_game_select_player)][my_rank].score			= cg_game_score;
	high_score_table[(cg_game_select_player)][my_rank].final_stage		= cg.game_now_stage;/**/
	//
	ranking_enter_name_string = high_score_table[(cg_game_select_player)][my_rank].name;
	ranking_enter_name_string[0] = ' ';
	ranking_enter_name_string[1] = ' ';
	ranking_enter_name_string[2] = ' ';
	ranking_enter_name_string[3] = ' ';
	//
	ranking_enter_name_string[4] = ' ';
	ranking_enter_name_string[5] = ' ';
	ranking_enter_name_string[6] = ' ';
	ranking_enter_name_string[7] = ' ';
	ranking_enter_name_string[8] = 0;
	now_select_name_chr = 0;
	/** 描画 **/
	{
		set_kanji_hide_line(ML_LINE_99_MAX);/*(全行表示する。)*/
		kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	}
	/* PLAY RESULTが付いたから、画面おもいっきり消すことにした。 */
	{
	//	psp_clear_screen(); /* 表画面を消す */
		my_file_common_name[0] = BG_TYPE_01_name_regist;psp_load_bg_file_name();/* 裏画面にロード */
		/* 裏画面を表にコピー */
		psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	}
	/* ｎ位タイトル描画 */
	{
		for (j=0; j<5; j++)
		{
			high_score_render_sub((cg_game_select_player), j);/* FONT16W 白  FONT16R 紅(黄) */
			cg.PSPL_font_x = (RANK_LOCATE_OFS_X_32);
			cg.PSPL_font_y = (RANK_LOCATE_OFS_Y_40)+(j*20);
			font_render_view_screen();
		}
	}
	#if 1
	/* 決定文字の位置 */
	plate_x = (RANK_LOCATE_OFS_X_32)+((16/*FONT16RW*/)*(2));
	plate_y = (RANK_LOCATE_OFS_Y_40)+(my_rank*20);
	#endif
	psp_move_screen(MODE_00_PUSH);/*(現在の表示画面を裏画面に保存)*/
	sel_aaa = 0;
	cg.main_call_func = name_entry_local_work;
	//
//	set_music_volume(128);/*とりあえず*/
	play_music_num(BGM_16_th06_16);/*(th06_16.IT 紅より儚い永遠)*/
}
