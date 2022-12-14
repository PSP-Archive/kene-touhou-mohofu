
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	スコアパネル(表示)関連
	-------------------------------------------------------
	現在(r33)SDLの為、処理落ちするとかなり酷いです。
---------------------------------------------------------*/
#include "111_my_file.h"/*(my_file_common_name)*/
#include "gu_draw_screen.h"
#include "../menu/kaiwa_sprite.h"

static SDL_Surface *panel_base; 	// パネルベース
//static S_DL_Surface *star_gauge;
//	/*static*/extern SDL_Surface *cg.FONT_fontimg;

/* サイドパネルの横表示位置 pannel x offset */
//#define PPP (380)
#define PPP (GAME_WIDTH)
#if 0/*(メモ)*/
	#define STR_MAX 		"MAX"
	#define STR_MISSILE 	"MISSILE"
	#define STR_WEAPON_UP	"WEAPON_UP"
	#define STR_LASER		"LASER"
	#define STR_BOMB		"BOMB"
	#define STR_TIME_		"TIME :"
	#define STR_EXTRA_		"EXTRA  :"
	//#define STR_MAX		"ABCD"			/*4つ*/
	//#define STR_MISSILE	"EFGHIJ"		/*6つ*/
	//#define STR_WEAPON_UP "KLMNOPQR"		/*8つ*/
	//#define STR_LASER 	"STUVW" 		/*5つ*/
	//#define STR_BOMB		"XYZab" 		/*5つ*/
	//#define STR_TIME_ 	"cdefg" 		/*5つ*/
	//#define STR_EXTRA_	"hijkl" 		/*5つ*/
//
//	#define STR_MAX 		"ABCD"			/*4つ*/
//	#define STR_EASY		"EFGH" " "		/*4つ*/
//	#define STR_NORMAL		"IJKLM" 		/*5つ*/
//	#define STR_HARD		"NOPQ" " "		/*4つ*/
//	#define STR_LUNATIC 	"RSTUV" 		/*5つ*/
//	#define CHR_PIRIOD_ 	'W' 			/*1つ*/
//	#define STR_FPS_		"XYZ"			/*3つ*/
//	#define STR_EXTRA		"XYZab" 		/*5つ*/ 	/* 未使用(r33) */
//	#define STR_TIME_		"cdef"			/*4つ*/ 	/* 地味に処理落ち要因になっていたので廃止。(r33) */
//	#define STR_RANK_		"hijkl" 		/*5つ*/
//	#define STR_FPS_		"hij"			/*3つ*/
//	#define CHR_PIRIOD_ 	'g' 			/*1つ*/
//	#define STR_ENEMY		"klmno" 		/*5つ*/
#endif

	// (r35font)
	#define STR_MAX 		"ABCD"			/*4つ*/
	#define STR_EASY		"EFGH" " "		/*4つ*/
	#define STR_NORMAL		"JKLMN" 		/*5つ*/
	#define STR_HARD		"PQRS" " "		/*4つ*/
	#define STR_LUNATIC 	"UVWXY" 		/*5つ*/
	#define CHR_PIRIOD_ 	'a' 			/*1つ*/
	#define STR_FPS_		"bcd"			/*3つ*/

/*---------------------------------------------------------
 * 10進数表示を行う。
 * 数字がない上位桁の 0 は 表示しない。
 * 常に最大桁数分の表示になる。
 *
 * @param num [in] 表示する値
 * @param size [in] 表示する最大桁数
 * @param sprite [in] 使用するスプライトワークの先頭番号
 * @param x [in] 表示するパネル内位置 X
 * @param y [in] 表示するパネル内位置 Y
---------------------------------------------------------*/
extern void dec_print_format(
		u32 num,
		int size,
//		int sprite,
//		int x,
//		int y
		char *my_str
)
{
	int sss;
//	int j;
	//u32 n;
	u32 ch;
	const u32 sub10[10/*8*/]=
	{
		1,
		10,
		100,
		1000,
		//
		10000,
		100000,
		1000000,
		10000000,
		//
		100000000,
		1000000000//,
	//	2147483647	== 0x7fffffff == signed int 32bit  max
	};
	sss = 0;
	num++;/*最後桁の辻褄合わせ*/
//	j = 256* (x);
	while (size)
	{
		size--;
		ch = 0;
		while (num > sub10[size])
		{
			num -= sub10[size];
			ch++;
			sss = (1);
		}
		if (
			(0 != sss) //&& /* 上位桁の 0 は表示しない */
			// (0!=size)	/* 1桁目は必ず表示する */
		)
		{
	//	//	obj_01_panel[sprite+size].x256			= 256* (x + ((size - 1 - i) * 16/DIV2));
	//		obj_01_panel[sprite+size].x256			= (j);
	//		obj_01_panel[sprite+size].y256			= 256* (y);
	//		obj_01_panel[sprite+size].w 			= TEX1_W_STR_09;
	//		obj_01_panel[sprite+size].h 			= TEX1_H_STR_09;
	//	//	obj_01_panel[sprite+size].m_Priority	= BS_DEPTH_PANEL_ITEM;
	//		obj_01_panel[sprite+size].alpha 		= 255;	/* α値(255 で不透明、0 で透明) */
	//		obj_01_panel[sprite+size].texture_x 	= TEX1_X_STR_09+(/*9 **/16* c);
	//		obj_01_panel[sprite+size].texture_y 	= TEX1_Y_STR_09;
	//	//	obj_01_panel[sprite+size].m_TexW		= TEX1_W_STR_09;
	//	//	obj_01_panel[sprite+size].m_TexH		= TEX1_H_STR_09;
	//	//	obj_01_panel[sprite+size].m_RollX		= 0.0;
	//	//	obj_01_panel[sprite+size].m_RollY		= 0.0;
	//		obj_01_panel[sprite+size].m_RollZ		= 0.0;
	//		obj_01_panel[sprite+size].m_Use 		= TRUE;
	//	//	obj_01_panel[sprite+size].m_PosCenter	= FALSE;
			(*my_str) = ('0'+ch);
		}
	//	else
	//	{
	//		;// 	obj_01_panel[sprite+size].m_Use 	= FALSE;
	//	}
		my_str++;
	//	j += ( 256* (16/DIV2) );
	}
}


/*---------------------------------------------------------
	SDL転送
---------------------------------------------------------*/
static SDL_Rect rect_dest;
static SDL_Rect rect_src;
static void SDL_blit_common(void)
{
//	PSPL_UpperBlit(star_gauge, &rect_src, cg.sdl_screen[SDL_00_VIEW_SCREEN], &rect_dest);
//	PSPL_UpperBlit(star_gauge/*power_gauge*/, &rect_src, cg.sdl_screen[SDL_00_VIEW_SCREEN], &rect_dest);
//	PSPL_UpperBlit(cg.FONT_fontimg, &rect_src, cg.sdl_screen[SDL_00_VIEW_SCREEN], &rect_dest);/*power_gauge*/
	PSPL_UpperBlit(cg.FONT_fontimg, &rect_src, cg.sdl_screen[SDL_00_VIEW_SCREEN], &rect_dest);/*(領域チェックあり描画)*/
//	SDL_LowerBlit(cg.FONT_fontimg, &rect_src, cg.sdl_screen[SDL_00_VIEW_SCREEN], &rect_dest);/*(領域チェックなし描画)*/
}


/*---------------------------------------------------------
	任意のサーフェイスに、文字列をレンダリング
---------------------------------------------------------*/

extern void s_font88_print_screen_xy(void)
{
	rect_src.w = ( 8); rect_dest.w = (rect_src.w);
	rect_src.h = (10); rect_dest.h = (rect_src.h);
	u32/*char*/ i;
	u32/*char*/ j;
	i = 0;
//	for (i=0; i<strlen(my_font_text); i++)
	{
	loop_str:
		j = my_font_text[i];
		if (0==j)
		{
			return;
		}
		j -= 0x20;//0x20==' ';(space)
		rect_src.x = (j & 0x0f)*(rect_src.w);
		rect_src.y = ((j>>4))*(rect_src.h) + (0)/* y_offset*/;
		rect_dest.x = cg.PSPL_font_x + (i)*(rect_src.w);
		rect_dest.y = cg.PSPL_font_y;			/*0*/
		SDL_blit_common();/*(抜き色0転送)*/
		i++;
		goto loop_str;
	}
}


/*---------------------------------------------------------
	プレイヤーの星の表示の子関数
---------------------------------------------------------*/

enum
{
	R_00_aka_hosi_png = 0,
	R_01_mizu_hosi_png = 10,
};

static void draw_stars_status(int img_num, int value, int y_offset)
{
//	if (value<1)	{	value=0;}
	value = psp_max(value, 0);
//
//	rect_src.x = (0);
	rect_src.x = (156);
	rect_src.y = (img_num);/*(0)*/
	rect_src.w = (10*value);
	rect_src.h = (10);
//
	rect_dest.x = PSP_WIDTH480-4-(10*value);
	rect_dest.y = y_offset;
	rect_dest.w = (100);
	rect_dest.h = (11);
	SDL_blit_common();/*(単純転送)*/
}

/*---------------------------------------------------------
	プレイヤーのウェポンゲージの表示の子関数
---------------------------------------------------------*/

static void draw_power_gauge(int weapon)/*, int dx, int dy*/
{
	#define WP_GAUGE_X_OFS (PPP+48-2)
	#define WP_GAUGE_Y_OFS (128+8+4)
//	rect_src.x = (0);
	rect_src.x = (156);
	rect_src.y = (20);/*(0)*/
	rect_src.h = (13);
	#if 0
//	rect_src.w = (int)((dou ble)weapon / 127/*128*/ * (dou ble)power_gauge->w);
	#else
	/* 1[pixel]ぐらい誤差あるかもしれないけど簡略化(高速化) */
	rect_src.w = ((int)(weapon * (80)/*power_gauge->w*/)>>7);
	#endif
	rect_dest.w = (80);/*power_gauge->w*/
	rect_dest.h = (13);/*power_gauge->h*/
	rect_dest.x = WP_GAUGE_X_OFS;/*dx*/
	rect_dest.y = WP_GAUGE_Y_OFS;/*dy*/
	SDL_blit_common();/*(単純転送)*/
}

/*---------------------------------------------------------
	スコアパネルのステータス表示
---------------------------------------------------------*/

#if (1==USE_EXTEND_CHECK)
extern void player_check_extend_score(void);
#endif

/*---------------------------------------------------------
	60フレームごとに一回呼ぶことにより、
	実時間から算出したfpsを取得する。
	fps は 100 倍した整数形式で返す。
	-------------------------------------------------------
	用途：fps計測用。
	注意：60フレームごとに必ず呼ぶ事。
	注意：複数ヵ所で呼ばれる事は考慮されてないので、必ず一ヶ所から呼ぶ事。
	注意：前回から約72分以内に必ず呼ぶ事。(60フレームで72分以上って...どんな状況やねん)
	そういや模倣風ってスリープ出来るんだね。
	スリープして約72分以上たった場合は、始めのfpsが正確に出ない(本当より良く出る)
	だけなので特に問題ないです。
---------------------------------------------------------*/

/*static*/static u32 psp_get_fps60_00(void)
{
	static u64 ticks_alt;	/* 前回の時間 the clock time of alter ticks. */
	static u64 ticks_now;	/* 今回の時間 the clock time of current ticks. */
	ticks_alt	= ticks_now;
	sceRtcGetCurrentTick(&ticks_now);
	/*	前回計測時間との差分を 1[nano sec] 単位  ( 1[nano sec] == 1/(1000*1000)[sec] )
	の u32 == 符号なし32bit形式へ変換 */
	u32 ttt;
	ttt= ((u32)(ticks_now - ticks_alt));/* 差分時間 the clock time of differencial ticks. */
	/* fps を 100 倍した整数形式へ変換 */
	ttt >>= 4;/*(16で割る。理由は後述)*/
	if (0 != ttt)/* ゼロ 0 で割る場合を回避する(Devision by zero 防止) */
//	if (0x0f < ttt)/* ゼロ 0 で割る場合を回避する(Devision by zero 防止) */
	{
	//	ttt = ( (u32)(60*60*16666) / (ttt));					/*"60fps"*/
	//	ttt = ( (u32)(60*60*166666) / (u32)(ttt));	/*"60.0fps"*/
	//	ttt = ( (u64)(60*60*1666666) / (u64)(ttt)); 					/*"60.00fps"*/
	/*"60.00fps"[普通に考えると整数型で計算するには 33bit 要るので、u32 (32bit) で足りない。]*/
	/*[しかし、(60*60 == 3600) は、16 で割り切れる。(60*60)/16==(225)]*/
	/*[そこで 16(==4bit)で割れば、必要なのは 29bit(==33-4)なので、u32 (32bit) で足りる。]*/
		ttt = ( (u32)((((60*60)/16)*(1666666))) / (u32)(ttt/*>>4*/));/*(Devision by zero を回避する為、ここでではなく先に16で割る)*/
	}
	return (ttt);
}

//static u8 *pb_image;
static void 	blit_panel_base(void)
{
//	#define USE_PANEL_BASE_DIRECT (1)
/*([A]パネルベースをブロック転送。SDL版)*/
//	#if 0// (0==USE_PANEL_BASE_DIRECT)/*テストoff*/
//	/* [ パネルベースを表示 ] */
//	{
//		SDL_Rect panel_base_r = {GAME_WIDTH, 0, 0, 0};	// データウィンドウ用rect_srct->w, h, x, y
//		PSPL_UpperBlit(panel_base, NULL, cg.sdl_screen[SDL_00_VIEW_SCREEN], &panel_base_r);
//	}
//	#endif

//#else

/*([B]パネルベースをブロック転送。SDL版を単純変換した版)*/
#if (0)/*(良くわかんないが、とりあえず動く版。強引に8bitのポインタでアドレス計算させてるので動く)*/
//	#define BG_PANEL_HAIKEI_OFFSET		((512*10))
	#define BG_PANEL_HAIKEI_OFFSET		((480-128))
	int x;
	int y;
	x= 0;
	y= 0;
	int haikei_offset;
	haikei_offset	= (0);
	u32 dy;
	for (dy=0; dy<272/*16*/ /*KANJI_FONT_16_HEIGHT_P0*/; dy++)
	{
		u32 dx;
		for (dx=0; dx<(128)/*16*/ /*KANJI_FONT_08_HARF_WIDTH*/; dx++)
		{
				/*
					いまいち良くわかんない(が、とりあえず動く)。
					アドレスはバイト単位なので u8 ポインタでＣ言語に計算させてる。
					(short なら2で割るとか、int なら4で割るとか)
					変える場合は、定数(BG_PANEL_HAIKEI_OFFSET_U16等)や変数(dy, y, 他)も変えないとダメ。
				*/
				#if (0==USE_32BIT_DRAW_MODE)/*(16bit mode)*/
			//	s_getpixel16
			volatile u8 *src_p = (u8 *)(/*font_bg_bitmap_surface_image*/((panel_base->pixels)/*cg.FONT_fontimg->pixels*/)/*cg.kanji_window_screen_image*/) /*surface*/
					+ (dy * (/*幅128なので*/256/*512*/ /*font_bg_bitmap_surface_pitch*/))		/*surface*/
					+ (dx+dx)
					+ (haikei_offset+haikei_offset);
			//	putpixel16
			volatile u8 *dst_p = (u8 *)(cg.sdl_screen[SDL_00_VIEW_SCREEN]->pixels/*cg.kanji_window_screen_image*/)/*surface->pixels*/
					+ (((dy+y))*(512*2))/*surface->pitch*/
					+ (dx+dx)
					+ (x+x)
					+ (BG_PANEL_HAIKEI_OFFSET*2);	/* 512[pixel]x 2[bytes](short) */
				*(u16 *)dst_p = (u32)(*(u16 *)src_p);
				#else/*(32bit mode)*/
			//	s_getpixel16
			volatile u8 *src_p = (u8 *)(/*font_bg_bitmap_surface_image*/((panel_base->pixels)/*cg.FONT_fontimg->pixels*/)/*cg.kanji_window_screen_image*/)	/*surface*/
					+ (dy * (2*512/*font_bg_bitmap_surface_pitch*/))		/*surface*/
					+ (dx+dx+dx+dx)
					+ (haikei_offset+haikei_offset+haikei_offset+haikei_offset);
			//	putpixel16
			volatile u8 *dst_p = (u8 *)(cg.sdl_screen[SDL_00_VIEW_SCREEN]->pixels/*cg.kanji_window_screen_image*/)/*surface->pixels*/
					+ (((dy+y))*(2*512*2))/*surface->pitch*/
					+ (dx+dx+dx+dx)
					+ (x+x+x+x)
					+ (BG_PANEL_HAIKEI_OFFSET*4);	/* 512[pixel]x 2[bytes](short) */
			//	*(u16 *)dst_p = (u32)(*(u16 *)src_p);
				*(u32 *)dst_p = (u32)(*(u16 *)src_p);
				#endif
		}
	}
#endif

/*([C]パネルベースをブロック転送。とりあえず普通に書いた版)*/
#if (1)/*(16bitだけてすと。とりあえず動く版。)*/
	// 512 == (pspの)vram幅 == cg.sdl_screen[SDL_00_VIEW_SCREEN]の幅。
	// 128 == 右のパネル幅。
	//	32 == 左のパネル幅。
	// 384 == 512-128 == 1行の加算差分。
	// 352 == 512-128-32 == 始めの位置は左のパネル幅を考慮しないと。
				#if (0==USE_32BIT_DRAW_MODE)/*(16bit mode)*/
	//[とりあえず動く]
	// 16[bit]のポインタなので +1 すると 2[byte] 加算される事に注意。
	volatile u16 *dst_p = (u16 *)(cg.sdl_screen[SDL_00_VIEW_SCREEN]->pixels/*cg.kanji_window_screen_image*/) + (352);/*(始めの位置, 352x2[bytes])*/
	volatile u16 *src_p = (u16 *)(/*font_bg_bitmap_surface_image*/((panel_base->pixels)/*cg.FONT_fontimg->pixels*/)/*cg.kanji_window_screen_image*/) /*surface*/;
	u32 dy;
	for (dy=0; dy<272; dy++)/*(psp縦272[pixel])*/
	{
		u32 dx;
		for (dx=0; dx<(128); dx++)/*(右のパネル幅128[pixel])*/
		{
		//	*dst_p = (u16)(0x11fa);/*(デバッグ用ダミー色)*/
			*dst_p = *src_p;
			dst_p += (1);/*(1==わざとらしいですが, +2[bytes])*/
			src_p += (1);/*(1==わざとらしいですが, +2[bytes])*/
		}
		dst_p += (384);/*(1行の加算差分, 384x2[bytes])*/
	}
				#else/*(32bit mode)*/
	//[未テスト。上のが動くので動く気もするが未テスト]
	// 32[bit]のポインタなので +1 すると 4[byte] 加算される事に注意。
	volatile u32 *dst_p = (u32 *)(cg.sdl_screen[SDL_00_VIEW_SCREEN]->pixels/*cg.kanji_window_screen_image*/) + (352);/*(始めの位置, 352x4[bytes])*/
	volatile u32 *src_p = (u32 *)(/*font_bg_bitmap_surface_image*/((panel_base->pixels)/*cg.FONT_fontimg->pixels*/)/*cg.kanji_window_screen_image*/) /*surface*/;
	u32 dy;
	for (dy=0; dy<272; dy++)/*(psp縦272[pixel])*/
	{
		u32 dx;
		for (dx=0; dx<(128); dx++)/*(右のパネル幅128[pixel])*/
		{
		//	*dst_p = (u32)(0xff11ffaa);/*(デバッグ用ダミー色)*/
			*dst_p = *src_p;
			dst_p += (1);/*(1==わざとらしいですが, +4[bytes])*/
			src_p += (1);/*(1==わざとらしいですが, +4[bytes])*/
		}
		dst_p += (384);/*(1行の加算差分, 384x4[bytes])*/
	}
				#endif
#endif


/*([D]パネルベース部分を(0)で消去。Guであとで転送)*/
#if 0
/*(上の奴コピペしてsrc_p削除して、データーは(0)にする。SDLがあるとめんどくさいよなぁ。)*/
/*(それかmemcpy32の方が良いかも？)*/
/*(パネルベースのコピーは、 sceGuCopyImage() あたりでいけそうな気がする。)*/
	/* こんな感じかな？ */
//	sceGuStart(GU_DIRECT, gulist);
//	sceGuCopyImage(
//		/*GU_PSM_5551*/SDL_GU_PSM_0000/*GU_PSM_5650*/,	//	int psm,	GU_PSM_8888 /* Image format */
//		0,						//	int sx, 		/* src location */
//		0,						//	int sy, 		/* src location */
//		(128)/*512*/,			//	int width,		/* Image size */右のパネル幅
//		272,					//	int height, 	/* Image size */右のパネル高さ
//		(128)/*512*/,			//	int srcw,		/* src buffer width */右のパネル幅
//		(panel_base->pixels),	//	void* src,		/* src Image from RAM */転送元。
//		(352)/*0*/, 			//	int dx, 		/* dest location */
//		0,						//	int dy, 		/* dest location */
//		512,					//	int destw,		/* dest buffer width */
//		draw_frame/*dest_p*/	//	void* dest		/* dest Image to VRAM */
//	);
//	sceGuFinish();
//	sceGuSync(0, 0);
#endif
}


//static u32 top_score;
extern void score_display(void)
{
	blit_panel_base();/*(単純転送)*/
//
	/* [ プレイヤー数表示 ] */
	draw_stars_status( R_00_aka_hosi_png,  (cg_zanki), 10*8+4); /*R_01_mizu_hosi_png*/
//
	/* [ ボム数表示 ] */
	draw_stars_status( R_01_mizu_hosi_png, (cg_bombs), 14*8+1); /*R_00_aka_hosi_png*/

	//{/*←何故かスコープしない方が良い(もちろんスコープあるなしで, コードが変わる)*/

	/* 通常時(デバッグ以外は死ぬ(喰らいボムモードへ)) */

		#if (0/*(r39Gu化済み)*/)/* [ ハイスコア比較 ] */
	//	if (top_score < cg_game_score)
	//	{	top_score = cg_game_score;}
		top_score = psp_max(top_score, cg_game_score);
		#endif
		//
		#if (0/*(r39Gu化済み)*/)/* [ ハイスコア表示 ] */
	//	sp rintf(my_font_text, "%09d0", top_score);
		strcpy(my_font_text, "0000000000");
		dec_print_format(top_score, 	9/*8*/, (char*)my_font_text);
		//
		cg.PSPL_font_x		= (PPP+5*8+4);
		cg.PSPL_font_y		= (3*8+2);
		s_font88_print_screen_xy();
		#endif
		//
		#if (0/*(r39Gu化済み)*/)/* [ スコア表示 ] */
	//	sp rintf(my_font_text, "%09d0", pd_game_score);
		strcpy(my_font_text, "0000000000");
		dec_print_format(cg_game_score, 9/*8*/, (char*)my_font_text);
		//
	//	cg.PSPL_font_x		= (PPP+5*8+4);
		cg.PSPL_font_y		= (6*8+7);
		s_font88_print_screen_xy();
		#endif
		//
		/* [ パワーゲージ表示 ] */
		draw_power_gauge(cg_weapon_power); /*, PPP+7, 124*/
		if (cg_weapon_power > (MAX_POWER_IS_128-1) /*== 128*/)/*max==MAX_POWER_IS_128==「129段階」*/
		{
			strcpy(my_font_text, STR_MAX);
		}
		else
		{
			#if 0/* 100% 表記 */
		//	sp rintf(my_font_text, "%d", (int)((dou ble)p->weapon / 128 * 100 ));
		//	sp rintf(my_font_text, " %d", (((int)(pd_weapon_power) * 200) >>8) );
			strcpy(my_font_text, "  0");
			dec_print_format( (((int)(cg_weapon_power) * 200) >>8), 2, (char*)&my_font_text[1]);
			#endif
			#if 1/* [P]数 表記(r33) */
			strcpy(my_font_text, "  0");
			dec_print_format( (((int)(cg_weapon_power) ) ), 3, (char*)&my_font_text[0]);
			#endif
			#if 0/* 5.00 表記(r32) */
		//	sp rintf(my_font_text, "%d", (int)((dou ble)p->weapon / 128 * 100 ));
		//	sp rintf(my_font_text, " %d", (((int)(pd_weapon_power) * 200) >>8) );
			/* "5.00" */
			strcpy(my_font_text, "0000");
			dec_print_format( (((int)(cg_weapon_power) * (200*5)) >>8), 3, (char*)&my_font_text[0]);
		//	my_font_text[4] = 0;
			my_font_text[3] = my_font_text[2];
			my_font_text[2] = my_font_text[1];
			my_font_text[1] = CHR_PIRIOD_;
			#endif
		}
		//
		cg.PSPL_font_x		= (PPP+(10*8)+7);
		cg.PSPL_font_y		= ((17*8)+5);
		s_font88_print_screen_xy();
	//
		#if (0/*(r39Gu化済み)*/)/* [ グレイズスコア表示 ] */
		/* --- 妖のグレイズカンスト 99999回 (5桁) --- */
		//	sp rintf(my_font_text, " %d", pd_graze_point);
			strcpy(my_font_text, "   0");
			dec_print_format(cg_graze_point, 4, (char*)&my_font_text[0]);
		//
			cg.PSPL_font_x		= (PPP+(11*8)+4);
			cg.PSPL_font_y		= (20*8);
			s_font88_print_screen_xy();/*4桁(稼げる)*/ /*3桁(足りない)*/
		#endif
	//
		/* [ 難易度表示 ] */
		{
			static const char *rank_name[(4)] =
			{
			/* 0==PLX_NONE*/		STR_EASY,
			/* 1==PLX_HOMING:*/ 	STR_NORMAL,
			/* 2==PLX_HLASER:*/ 	STR_HARD,
			/* 3==PLX_SHIELD:*/ 	STR_LUNATIC,
		//	/* 4==PLX_BOMB:*/		STR_EXTRA,
			//	/*default:*/		"UNKNOWN (?)",
			};
			strcpy(my_font_text, (char*)rank_name[((cg_VR20_game_difficulty))&(4-1)]);
			cg.PSPL_font_x		= (PPP+(1*8));
			cg.PSPL_font_y		= (256);
			s_font88_print_screen_xy();
		}
	//
		#if 1
		/* [ fps 表示(60フレーム単位で表示) ] */
		/* (pspは1秒が59.9なんたらフレームで、厳密に60でないらしいです。 ) */
		{
		//	static int ttt;
			static u32 ttt;
			static int fps_draw_wait_counter;
			fps_draw_wait_counter--;
			if (fps_draw_wait_counter < 1)
			{
				fps_draw_wait_counter = 60;
				/* エクステンドチェックは1秒に1回(笑)で問題ないと思う。 */
				#if (1==USE_EXTEND_CHECK)
				player_check_extend_score();
				#endif
			//	[1/60sec]	0.016 666 [nsec] 6666666666666666666666666667
			//	16666.66666 / x == 60.0,  16666.666666/60.0 == x, x== 277.7777777777777
			//	16666.00(int) / 60.00(int) == 60.1660649819494584837545126353791 = 60.000 (int)
				ttt = psp_get_fps60_00();/* 前回計測時間との差分を 1[nano sec] 単位の signed int == 符号付32bit形で返す。 */
			}
			/*"60.00fps"*/
			strcpy(my_font_text, /*STR_TIME_*/"00000"STR_FPS_);
			dec_print_format(ttt,	4, (char*)&my_font_text[0/*5*/]);
			my_font_text[9-5] = my_font_text[8-5];
			my_font_text[8-5] = my_font_text[7-5];
			my_font_text[7-5] = CHR_PIRIOD_;/*' ' '.'*/
		//
			cg.PSPL_font_x		= (PPP+8*8+2);
			cg.PSPL_font_y		= (256);
			s_font88_print_screen_xy();
		}
		#endif
	//}
}

/*---------------------------------------------------------

---------------------------------------------------------*/
//extern void kaiwa_obj_set2n(u32 obj_number);
static/*extern*/ void kaiwa_obj_set2n(u32 obj_number)
{
	KAIWA_OBJ *my_std_obj;
	my_std_obj = &kaiwa_sprite[obj_number]; /* 汎用オブジェ */
	/*(Guの場合)*/
	my_std_obj->draw_flag = (1);	/* 描画する。 */
	/*(縦横共、強制的に2^nに変換)*/
	my_std_obj->width_2n	= (1<<(32 - __builtin_allegrex_clz((my_resource[TEX_09_TACHIE_L+obj_number].texture_width)-1)));/*/frames*/ 	//tmp->cw		= ((tmp->w)>>1);
	my_std_obj->height_2n	= (1<<(32 - __builtin_allegrex_clz((my_resource[TEX_09_TACHIE_L+obj_number].texture_height)-1)));				//tmp->ch		= ((tmp->h)>>1);
}

/*---------------------------------------------------------
	パネル表示、初期化
---------------------------------------------------------*/
extern void set_topscore(void);
extern void score_panel_init(void)
{
	/*(会話スプライトの設定。サイズを128x256にする。)*/
	int i;
	for (i=0; i<KAIWA_OBJ_99_MAX; i++)
	{
		my_resource[TEX_09_TACHIE_L+i].texture_width	= (128);/*(転送先画像の横幅)*/
		my_resource[TEX_09_TACHIE_L+i].texture_height	= (256);/*(転送先画像の縦幅)*/
		my_resource[TEX_09_TACHIE_L+i].buffer_width 	= (128);/*(転送元画像のバッファ幅)*/
		kaiwa_obj_set2n(i);
	}
	kaiwa_all_obj_draw_on_off(0/*off*/);/*(会話スプライトの設定。表示をoffにする。)*/
	//
	set_topscore();
	strcpy(my_file_common_name, (char*)DIRECTRY_NAME_DATA_STR"/fonts/" "panel_base.png");
	//#if 0// memory on load で解放しない。==画像キャッシュしない。(1==USE_KETM_IMAGE_CHACHE)
	#if (1==USE_KETM_IMAGE_CHACHE)/*(?)*/
	panel_base	= load_chache_bmp();
	#else
	panel_base	= IMG_Load(my_file_common_name);/*(何故か、巧くいかない)*/
	#endif /*(1==USE_KETM_IMAGE_CHACHE)*/
//	#if (1==USE_PANEL_BASE_DIRECT)
//	pb_image = (panel_base->pixels);
//	#endif
}


/*---------------------------------------------------------
	会話スプライトの設定。サイズを 256x256にする。
---------------------------------------------------------*/

extern void kaiwa_obj_set_256(void)
{
	int i;
	for (i=0; i<KAIWA_OBJ_99_MAX; i++)
	{
		my_resource[TEX_09_TACHIE_L+i].texture_width	= (256);/*(転送先画像の横幅)*/
		my_resource[TEX_09_TACHIE_L+i].texture_height	= (256);/*(転送先画像の縦幅)*/
		my_resource[TEX_09_TACHIE_L+i].buffer_width 	= (256);/*(転送元画像のバッファ幅)*/
		kaiwa_obj_set2n(i);
	}
}
