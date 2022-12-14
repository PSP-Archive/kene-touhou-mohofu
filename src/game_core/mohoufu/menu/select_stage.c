
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	共通選択メニュー
	-------------------------------------------------------
	ステージ選択メニュー
	ポーズ メニュー
	コンティニュー？メニュー
	-------------------------------------------------------
---------------------------------------------------------*/

#include "kaiwa_system.h"	/* 会話システムにSDL再描画指示。 */
#include "kanji_system.h"
//#include "common_menu.h"


static int	aaa_max_items;			/* オプションの項目数 */
static int	aaa_selected_number;	/* 現在メニュー上で選択されている項目番号 */
static int	aaa_menu_brite; 		/* メニューの明るさ(α値) */


/*---------------------------------------------------------

---------------------------------------------------------*/

//	#define FPS_MENU_FACTOR8	(8*fps_factor)
	#define FPS_MENU_FACTOR8	(16)/* 8*FPS_MENU_FACTOR */

/*---------------------------------------------------------

---------------------------------------------------------*/
enum
{
	MENU_RESOURCES_00_STAGE01 = 0,
	MENU_RESOURCES_01_STAGE02,
	MENU_RESOURCES_02_STAGE03,
	MENU_RESOURCES_03_STAGE04,
	MENU_RESOURCES_04_STAGE05,
	MENU_RESOURCES_05_STAGE06,
//	MR_06_STOP, //----------------
	MENU_RESOURCES_06_MAX
};


/*---------------------------------------------------------

---------------------------------------------------------*/
static void stage_select_menu_draw_all(void)
{
	/* 描画 */
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	{
		u32 yyy18;
		yyy18 = (0);/* Y位置 */
		u32 yyy21;
		yyy21 = (113);/* Y位置 */
		kanji_cursor_move_home_position();		/* 漢字カーソルをホームポジションへ移動 */
		cg.msg_time = (65536);	/* 約 18 分 */
		int i;
		for (i=0; i<aaa_max_items; i++)
		{
			u32 text_color;
			text_color = (4);/*(白緑色)*/
			//
			ml_font[i].x		= (256);// (aaa_menu_item_my_obj[i].offset_x);
			ml_font[i].y		= (yyy21);// (aaa_menu_item_my_obj[i].offset_y);
			if (((signed)i)==aaa_selected_number)	/* 選択された */
			{
				text_color = (12);/*(緑色)*/
				ml_font[i].x += (2);	/* オフセットを 2[pixel] にする */
				ml_font[i].y += (2);	/* オフセットを 2[pixel] にする */
			}
			ml_font[i].timer	= ML_ON;
			//
			kanji_window_clear_line(i); 	/* 漢字ウィンドウのn行目(==0)の内容を消す。 */
			set_kanji_xy( (0), (yyy18) );
			strcpy(my_font_text, (char*)"STAGE 0 0000000000");
			my_font_text[6] = ('1' + i);
			kanji_color(text_color);
			kanji_draw();
			//
			yyy18 += (18);
			yyy21 += (21);
		}
	}
}


/*---------------------------------------------------------
	終了処理と移動処理。
---------------------------------------------------------*/
extern void player_continue_value(void);
static MAIN_CALL_FUNC(common_menu_work_MENU_STATE_03_FININSH)
{
//	SDL_SetAlpha(cg.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, 255);
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	//
	if ((0)>aaa_selected_number)/*(CANCELの場合)*/
	{
		cg.main_call_func = rank_select_menu_start;	/* 選択メニューへ戻る */
	}
	else/*(OKの場合)*/
	{
		cg.game_continue_stage = aaa_selected_number;
		/* プラクティス ゲーム開始 */
		cg.main_call_func = stage_first_init;			/* ゲーム開始 */
	}
}


/*---------------------------------------------------------
	だんだん暗くする。暗くなったら次へ。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(common_menu_work_MENU_STATE_02_FADE_OUT)
{
	aaa_menu_brite -= FPS_MENU_FACTOR8;
	if (0 >= (aaa_menu_brite) )
	{
		aaa_menu_brite	= (0);
		cg.main_call_func = common_menu_work_MENU_STATE_03_FININSH; /* */
	}
	stage_select_menu_draw_all();
}
/*---------------------------------------------------------
	メニューキー入力受け付け。確定したら次へ。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(stage_select_menu_work_MENU_STATE_01_WORK_MENU)
{
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		/*(上下を押した場合に操作音を出す。)*/
		if (psp_pad.pad_data & (PSP_KEY_DOWN|PSP_KEY_UP/*|PSP_KEY_PAUSE|PSP_KEY_SELECT*/))
		{
			voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
		}
		#if 0/*(-r34)*/
		/*(上下を押した場合、回り込み選択をする。上下は必ずワープ)*/
		if (psp_pad.pad_data & PSP_KEY_DOWN)
		{
			if (aaa_selected_number == aaa_max_items-1)
					{aaa_selected_number = 0;}
			else	{aaa_selected_number++;}
		}
		else
		if (psp_pad.pad_data & PSP_KEY_UP)
		{
			if (0 == aaa_selected_number)
					{aaa_selected_number = aaa_max_items-1;}
			else	{aaa_selected_number--;}
		}
		#else/*(r35-)*/
		/*(上下を押した場合、最大最小選択をする。メニュー上下は必ず停止)*/
		if (psp_pad.pad_data & PSP_KEY_DOWN)
		{	aaa_selected_number++;		aaa_selected_number = psp_min(aaa_selected_number, (aaa_max_items-1) ); 	}	/* メニュー下で停止 */
		else
		if (psp_pad.pad_data & PSP_KEY_UP)
		{	aaa_selected_number--;		aaa_selected_number = psp_max(aaa_selected_number, (0) );					}	/* メニュー上で停止 */
		#endif
		/*(OKボタン)*/
		if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
		{
			voice_play_menu(VOICE01_MENU_OK/*VOICE02_MENU_SELECT*/, TRACK01_MENU01);
			cg.main_call_func = common_menu_work_MENU_STATE_02_FADE_OUT; /* メニュー消去準備 */
		}
		else
		/*(CANCELボタン)*/
		if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
		{
			voice_play_menu(VOICE04_SHIP_HAKAI, TRACK02_MENU02/*TRACK01_MENU01*/);/* 自機死に音は、なるべく重ねない */
			aaa_selected_number = (-1);/*(負数ならなんでもいい)*/
			cg.main_call_func = common_menu_work_MENU_STATE_02_FADE_OUT; /* メニュー消去準備 */
		}
	}
	stage_select_menu_draw_all();
}


/*---------------------------------------------------------
	だんだん明るくする。明るくなったら次へ。
---------------------------------------------------------*/

static MAIN_CALL_FUNC(common_menu_work_MENU_STATE_00_FADE_IN_MENU)
{
	aaa_menu_brite += FPS_MENU_FACTOR8;
	if ((255) <= (aaa_menu_brite) )
	{
		aaa_menu_brite = (255);
		cg.main_call_func = stage_select_menu_work_MENU_STATE_01_WORK_MENU; /* */
	}
	stage_select_menu_draw_all();
}


/*---------------------------------------------------------
	メニュー初期化。
---------------------------------------------------------*/


/*---------------------------------------------------------
	ステージ選択メニューの開始処理。
	-------------------------------------------------------
---------------------------------------------------------*/
/*static*/extern MAIN_CALL_FUNC(stage_select_menu_start)
{
	psp_move_screen(MODE_00_PUSH);/*(現在の表示画面を裏画面に保存)*/
	{
		#if 1
		/*
			エキストラステージをプレイした後で、
			「エキストラステージ、プラクティス」と
			「エンディング、スタッフロール、プラクティス」が
			選べるバグがあるので、修正する。
		*/
		if ((6-1) < cg.game_continue_stage) 	{cg.game_continue_stage = (6-1);}
		#endif
		aaa_selected_number = cg.game_continue_stage;
	}
	// メニューに使用するサブ項目の数を調べる。
	{
		aaa_max_items		= (0);
		{
	loop:
			/* セレクトステージメニューの場合 */
			/* 解放された部分まで。 */
			if (aaa_max_items > (option_config[OPTION_CONFIG_07_OPEN] & 0x07))	{goto loop_quit;}
			aaa_max_items++;
			/* (終わりまで調べる) */
			/*while*/if (MENU_RESOURCES_06_MAX == /*aaa_menu_offset+*/aaa_max_items)	{goto loop_quit;}
			goto loop;
	loop_quit:
			;
		}
	}
	// ステージ選択項目。ゲームの進行度によって項目数は可変なので。
	// とりあえず項目を画面外に退避しとく。
	{
		int i;
		for (i=0; i<7; i++)
		{
		//	ml_font[i].x		= (480);// (とりあえず表示しない);
			ml_font[i].timer	= ML_OFF;// (とりあえず表示しない);
		}
	}
	// メニューに使用するサブ項目の文字。
	aaa_menu_brite		= (0);
//	fade_out_flag		= (0)/*set_fade_out_flag*/;/*構造的問題*/
	cg.msg_time 		= (65536);/* 約 18 分 */
	cg.main_call_func = common_menu_work_MENU_STATE_00_FADE_IN_MENU;
}
