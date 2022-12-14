
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	Guを使った画面描画処理
---------------------------------------------------------*/
#include "111_my_file.h"/*(bg読みこみ。)*/

#include "../../libgu/pspgu.h"//#include <pspgu.h>
#include "../../libgu/pgc.h"

#include "gu_draw_screen.h"

#include "../menu/kaiwa_sprite.h"/* 立ち絵 */
#include "kanji_system.h"/*"独立ライン表示"*/


#include <malloc.h>/* memalign() free() */

/*---------------------------------------------------------
	デバッグ用テスト設定(実験中など)
---------------------------------------------------------*/
#define LINE_TEST	(1)

/*---------------------------------------------------------

---------------------------------------------------------*/

typedef struct
{
	u16 	u;
	u16 	v;
	#if (1==USE_VCOLOR)
		#if (16==USE_BLIT_COLOR_BIT)
			u16 	color;/*GU_COLOR_5650 GU_COLOR_5551 GU_COLOR_4444*/
		#else
			u32 	color;
		#endif
	#endif
	s16 	x;
	s16 	y;
	s16 	z;
} Vertex_uvcxyz;

typedef struct
{
	u16 	u;
	u16 	v;
	#if (1==USE_VCOLOR)
		#if 0// (16==USE_BLIT_COLOR_BIT)
			u16 	color;/*GU_COLOR_5650 GU_COLOR_5551 GU_COLOR_4444*/
		#else
			u32 	color;
		#endif
	#endif
	s16 	x;
	s16 	y;
	s16 	z;
} Vertex_uvcxyz_C32;

typedef struct
{
	/*float*/u16 x;
	/*float*/u16 y;
	/*float*/u16 z;
} Point_Vertex;

typedef struct
{
	#if (1==USE_VCOLOR)
		#if 0// (16==USE_BLIT_COLOR_BIT)
			u16 	color;/*GU_COLOR_5650 GU_COLOR_5551 GU_COLOR_4444*/
		#else
			u32 	color;
		#endif
	#endif
	/*float*/u16 x;
	/*float*/u16 y;
	/*float*/u16 z;
} Point_Vertex_color;

/*---------------------------------------------------------
	共通ワーク
---------------------------------------------------------*/

/*static*/global	u32 gulist[PACKET_SIZE] __attribute__((aligned(16)));

/*---------------------------------------------------------
	グローバル変数
---------------------------------------------------------*/

static u16 *render_image;
static u16 *render_image_back;
//static u16 *render_image_tex;


/*---------------------------------------------------------
	スクリーン管理
---------------------------------------------------------*/

static VIRTUAL_OBJ_STATE obj_status_table[(OBJ_BANK_MAX*OBJ_BANK_SIZE)];/*(6*8*8)*/

//static	MY_DIB_SURFACE *my_texture[TEXTURE_MAX];
/*static*/global			MY_TEXTURE_RESOURCE 	 my_resource[TEXTURE_MAX];
/*static*/static	const	MY_TEXTURE_RESOURCE initial_resource[TEXTURE_MAX] =
{
	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"}, 	//		TEX_00_BACK_GROUND = 0, 	/* 3D背景1 */
//	{NULL, 256, 256, 512,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"}, 	//	//	TEX_01_BACK_TEXTURE,		/* 背景障害物 */
	{NULL, 128, 128, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/teki/mahoujin128.png"}, //		TEX_02_MAHOUJIN,			/* 魔方陣 */
	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/jiki/jiki00.png"},		//		TEX_03_JIKI,				/* 自弾/自機 */
	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/teki/teki10_256.png"},	//	//	TEX_04_TEKI,				/* ボス/ザコ敵 */
//	{NULL, 256, 256, 512,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"}, 	//	//	TEX_05_ITEM,				/* アイテム/漢字スコア */
	{NULL, 128, 128, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/teki/bullet0.png"}, 	//		TEX_06_BULLET,				/* 敵弾 */
	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/teki/front256.png"},	//		TEX_07_FRONT,				/* 自機当たり表示/爆発/[コンティニュー文字(bank00)/メニュー文字(bank01)/メニュー文字(bank02)] */
//	{NULL, 256, 256, 512,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"}, 	//	//	TEX_08_SCORE_PANEL, 		/* スコアパネル/スコアフォント文字 */
	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_09_TACHIE_L,			/* 立ち絵L プレイヤー */
	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_10_TACHIE_R,			/* 立ち絵R ボス(1人目) */
	#if (1==USE_VS3)
	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_11_TACHIE_RB,			/* 立ち絵 ボス(2人目) */
	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_12_TACHIE_RC,			/* 立ち絵 ボス(3人目) */
	#endif
//	{NULL, 256, 256, 512,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"}, 	//	//	TEX_11_MESSAGE, 			/* メッセージ固定文字 */
};

//メモ:
//	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_09_TACHIE_L,			/* 立ち絵 */
//	{NULL, 128, 256, 128,	0, 0, &obj_status_table[0], (char*)DIRECTRY_NAME_DATA_STR "/tachie/remilia1.png"},	//	//	TEX_10_TACHIE_R,			/* 立ち絵 */

/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/

#include "render/gu_render_score.h"

/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/

/*---------------------------------------------------------
	画像関連
---------------------------------------------------------*/

void psp_clear_screen(void)
{
	/* 将来Guで描いた場合。ハードウェアー機能で、置き換えられるので今のうちにまとめとく */
//	SDL_FillRect(cg.sdl_screen[SDL_00_VIEW_SCREEN], NULL, 0/*SDL_MapRGB(cg.sdl_screen[SDL_00_VIEW_SCREEN]->format, 0, 0, 0)*/);
	PSPL_FillRect000(cg.sdl_screen[SDL_00_VIEW_SCREEN]);/*(とりあえず)*/
}
//extern void psp_move_screen(int src_screen_number, int dst_screen_number)
extern void psp_move_screen(int set_mode)
{
	/* 将来Guで描いた場合。ハードウェアー機能で、置き換えられるので今のうちにまとめとく */
//	PSPL_UpperBlit(cg.sdl_screen[src_screen_number], NULL, cg.sdl_screen[dst_screen_number], NULL);
	PSPL_UpperBlit(cg.sdl_screen[set_mode], NULL, cg.sdl_screen[(set_mode^1)], NULL);
}
//void psp_push_screen(void)
//{
//	PSPL_UpperBlit(sdl_screen[SDL_00_VIEW_SCREEN], NULL, sdl_screen[SDL_01_BACK_SCREEN], NULL);
//}
//void psp_pop_screen(void)
//{
//	PSPL_UpperBlit(sdl_screen[SDL_01_BACK_SCREEN], NULL, sdl_screen[SDL_00_VIEW_SCREEN], NULL);
//}


/*---------------------------------------------------------
	pspの表示中 vram からSDL画面(仮想スクリーン)(SDL_00_VIEW_SCREEN)に強制コピー
	-------------------------------------------------------

---------------------------------------------------------*/
#if 1/*(r35要るんだっけ？)*/
static void s_gu_save_screen(void)
{
	if (SDL_MUSTLOCK(cg.sdl_screen[SDL_00_VIEW_SCREEN]))	{SDL_LockSurface(cg.sdl_screen[SDL_00_VIEW_SCREEN]);}	/* ロック */
	u16 *dest;	dest = render_image;
	u16 *src;	src = (u16 *)((u32) 0x44000000);/*VRAM*/
	#if 1
	{
		int ii;
		for (ii=0; ii<(512*272); ii++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	#else
	/* ダメ */
//	sceGuStart(GU_DIRECT, gulist);
//	sceGuCopyImage(
//		/*GU_PSM_5551*/SDL_GU_PSM_0000/*GU_PSM_5650*/,	//	int psm,	GU_PSM_8888 /* Image format */
//		0,				//	int sx, 		/* src location */
//		0,				//	int sy, 		/* src location */
//		512,			//	int width,		/* Image size */
//		272,			//	int height, 	/* Image size */
//		512,			//	int srcw,		/* src buffer width */
//		src,			//	void* src,		/* src Image from RAM */
//		0,				//	int dx, 		/* dest location */
//		0,				//	int dy, 		/* dest location */
//		512,			//	int destw,		/* dest buffer width */
//		dest			//	void* dest		/* dest Image to VRAM */
//	);
//	sceGuFinish();
//	sceGuSync(0, 0);
	#endif
	if (SDL_MUSTLOCK(cg.sdl_screen[SDL_00_VIEW_SCREEN]))	{SDL_UnlockSurface(cg.sdl_screen[SDL_00_VIEW_SCREEN]);}	/* ロック解除 */
}
#endif


#include "render/SDL_pause_filter.h"


/*------------------------------------------------------------- */


void select_jiki_load_surface(void)
{
//	strcpy(filename, DIRECTRY_NAME_DATA_STR "/jiki/jiki0Z.png");
	my_resource[TEX_03_JIKI].file_name[11+DIRECTRY_NAME_DATA_LENGTH] = ('0'+(cg_game_select_player));
	psp_load_texture( TEX_03_JIKI );
//	draw_jiki_screen = 1;
}
static void gu_draw_bg_fake3D(void);
static void gu_draw_bg_2D(void);
static void gu_draw_bg_eientei(void);
static void gu_draw_bg_3D_test01(void);
static void gu_draw_bg_3D_test02(void);



void stage_bg_load_texture(void)
{
//	strcpy(filename, DIRECTRY_NAME_DATA_STR "/bg/backZ_256.png");
	my_resource[TEX_00_BACK_GROUND].file_name[8+DIRECTRY_NAME_DATA_LENGTH] = get_stage_chr(cg.game_now_stage);
	psp_load_texture( TEX_00_BACK_GROUND );
//
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"},		//		TEX_00_BACK_GROUND = 0, 	/* 3D背景1 */
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/teki/teki10_256.png"}, 	//	//	TEX_04_TEKI,				/* ボス/ザコ敵 */
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/teki/boss00_256.png"}, 	//	//	TEX_04_TEKI,				/* ボス/ザコ敵 */
//
//	my_resource[TEX_04_TEKI].file_name[10+DIRECTRY_NAME_DATA_LENGTH] = ('0'+0/*cg.game_now_stage*/);
	my_resource[TEX_04_TEKI].file_name[10+DIRECTRY_NAME_DATA_LENGTH] = get_stage_chr(cg.game_now_stage);
	my_resource[TEX_04_TEKI].file_name[11+DIRECTRY_NAME_DATA_LENGTH] = ('0');
	psp_load_texture( TEX_04_TEKI );
//
	my_resource[TEX_04_TEKI].object_table_head = (obj_status_table+(OBJ_BANK_11_ZAKO_STAGE1*OBJ_BANK_SIZE));
//
	void (*aaa[16/*8*/])(void)	=
	{
		gu_draw_bg_2D,			/*loading*/
		gu_draw_bg_fake3D,		/*1面"魔法の森"*/
		gu_draw_bg_eientei, 	/*3面"竹薮"*/
		gu_draw_bg_eientei, 	/*4面"永遠亭 廊下"*/
		gu_draw_bg_2D,			/*2面"秋めく滝"*/
		gu_draw_bg_fake3D,		/*5面"紅魔館 図書館"*/
		gu_draw_bg_fake3D,		/*6面"紅魔館 大廊下"*/
		gu_draw_bg_3D_test01,	/*ending*/
//
		gu_draw_bg_fake3D,		/* extra1面 */
		gu_draw_bg_3D_test02,	/* phantazm1面 */
		gu_draw_bg_fake3D,		/*extra*/
		gu_draw_bg_fake3D,		/*extra*/
		gu_draw_bg_2D,			/*extra*/
		gu_draw_bg_2D,			/*extra*/
		gu_draw_bg_2D,			/*extra*/
		gu_draw_bg_2D,			/*extra*/
	};
	cg.callback_gu_draw_haikei			= aaa[cg.game_now_stage&0x0f];//	dr aw_bg_screen = 1;
//	cg.callback_gu_draw_haikei			= aaa[cg.game_now_stage&0x07];//	dr aw_bg_screen = 1;
//	cg.callback_gu_draw_haikei			= callback_gu_draw_haikei_all;//	dr aw_bg_screen = 1;
	cg.callback_gu_draw_haikei_modosu	= cg.callback_gu_draw_haikei;
}
void stage_boss_load_texture(void)
{
//	strcpy(filename, DIRECTRY_NAME_DATA_STR "/bg/backZ_256.png");
//	my_resource[TEX_00_BACK_GROUND].file_name[8+DIRECTRY_NAME_DATA_LENGTH] = get_stage_chr(cg.game_now_stage);
//	psp_load_texture( TEX_00_BACK_GROUND );
//
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/bg/back0_256.png"},		//		TEX_00_BACK_GROUND = 0, 	/* 3D背景1 */
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/teki/teki10_256.png"}, 	//	//	TEX_04_TEKI,				/* ボス/ザコ敵 */
//	{NULL, 256, 256, 256,	0, 0, &obj_status_table[0], DIRECTRY_NAME_DATA_STR "/teki/boss00_256.png"}, 	//	//	TEX_04_TEKI,				/* ボス/ザコ敵 */
//
	my_resource[TEX_04_TEKI].file_name[10+DIRECTRY_NAME_DATA_LENGTH] = get_stage_chr(cg.game_now_stage);
	my_resource[TEX_04_TEKI].file_name[11+DIRECTRY_NAME_DATA_LENGTH] = ('1');
	psp_load_texture( TEX_04_TEKI );
//
//	my_resource[TEX_04_TEKI].object_table_head = (obj_status_table+(OBJ_BANK_21_BOSS_STAGE1*OBJ_BANK_SIZE));
	my_resource[TEX_04_TEKI].object_table_head = (obj_status_table+((OBJ_BANK_21_BOSS_STAGE1-1)*OBJ_BANK_SIZE)+(cg.game_now_stage<<6));
}

static void gu_init_vfpu(void);
void draw_loading_screen_test(void);
extern void sendCommandi(int cmd, int argument);

/*only boot once*/extern void /*SD LCALL*/ PSPL_VideoInit(void);/*const char *driver_name, u32 flags*/
/*only boot once*/extern void /*SD LCALL*/ PSPL_AudioInit(void);/*const char *driver_name*/
	#if 0
	if (atexit(SDL_Quit))
	{
		CHECKPOINT;
		error(ERR_WARN, "atexit dont returns zero");
	}
	#endif

global ML_FONT ml_font[ML_LINE_99_MAX];
extern void psp_video_init01(void)
{

#if (1==USE_16BIT_BLIT)
	#define  SCREEN_DEPTH	16
#else
	#define  SCREEN_DEPTH	32
#endif
	#if (16 == SCREEN_DEPTH/*depth*/)/*16 bit(5650), 15 bit(5551), 12 bit(4444) */
		#define  FRAMESIZE (0x44000)
	#else // (32 == SCREEN_DEPTH/*depth*/)/*32 bit(8888) */
		#define  FRAMESIZE (0x88000)
	#endif /* SCREEN_DEPTH */

#define USE_SWAP_BUFFER (0)

#if (1==USE_SWAP_BUFFER)
	cg.draw_frame = (void *)(FRAMESIZE * 0);
	cg.show_frame = (void *)(FRAMESIZE * 1);
	cg.work_frame = (void *)(FRAMESIZE * 2);
	cg.tex_frame  = (void *)(FRAMESIZE * 3);
#endif


//static u16 *bullet_image;

//	PSPL_Init();//SDL_INIT_VIDEO | SDL_INIT_AUDIO/*|SDL_INIT_NOPARACHUTE*/); /*| SDL_INIT_JOYSTICK*/
	PSPL_AudioInit();/*only boot once*/ 	/* Initialize the audio subsystem */

	{
	//	#define dummy_SDL_VRAM_SCREEN	vram_screen
	//	/*static*/ SDL_Surface *dummy_SDL_VRAM_SCREEN;
	//	dummy_SDL_VRAM_SCREEN =
		PSPL_video_init(
		//	PSP_WIDTH480,
		//	PSP_HEIGHT272,
			/*int depth 		=*/ SDL_5551_15/*PSP_DEPTH16*/,
		//	/*u32 videoflags =*/ (SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE /*| SDL_HW PALETTE | SDL_HW ACCEL*/)
		//	/*u32 videoflags =*/ (SDL_FULLSCREEN /*| SDL_DOUBLEBUF*/ | SDL_HWSURFACE | SDL_HW PALETTE | SDL_HW ACCEL)
			PSP_DEPTH16, /*SDL_VRAM_SCREEN->format->BitsPerPixel*/
			/*0x0000*/PSP_SCREEN_FORMAT_AMASK/*SDL_VRAM_SCREEN->format->Amask*/,	/*0*/
			/*0xf800*/PSP_SCREEN_FORMAT_BMASK/*SDL_VRAM_SCREEN->format->Bmask*/,	/*5*/
			/*0x07e0*/PSP_SCREEN_FORMAT_GMASK/*SDL_VRAM_SCREEN->format->Gmask*/,	/*6*/
			/*0x001f*/PSP_SCREEN_FORMAT_RMASK/*SDL_VRAM_SCREEN->format->Rmask*/ 	/*5*/
		);	/*0*/ /*only boot once*/	/* Initialize the video subsystem */


	//	if (NULL == dummy_SDL_VRAM_SCREEN)
	//	{
	//		CHECKPOINT;
	//		error(ERR_FATAL, "cant open screen.");
	//	}
	}


	#if 1// (1==US E_GU)
	//#define SDL_PSP_BUFFER_WIDTH512 (512)
	cg.sdl_screen[SDL_00_VIEW_SCREEN] = /*()*/
	#if 0
		PSPL_create_ABGR_surface_buffer
		(
		(void *)(FRAMESIZE * 2),
		SDL_PSP_BUFFER_WIDTH512/*PSP_WIDTH480*/, /*sdl_screen[SDL_00_VIEW_SCREEN]->w*/
		PSP_HEIGHT272, /*sdl_screen[SDL_00_VIEW_SCREEN]->h*/
		/*pitch = */ /*surface->w*/(SDL_PSP_BUFFER_WIDTH512)*(2)/*surface->format->BytesPerPixel*/
		);
	#else
		SDL_CreateSurface
		(
		/*SDL_SWSURFACE*/SDL_HWSURFACE, /*VRAMへ*/
		SDL_PSP_BUFFER_WIDTH512/*PSP_WIDTH480*/, /*sdl_screen[SDL_00_VIEW_SCREEN]->w*/
		PSP_HEIGHT272// /*sdl_screen[SDL_00_VIEW_SCREEN]->h*/
		);
	#endif
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_00_VIEW_SCREEN]))	{SDL_LockSurface(cg.sdl_screen[SDL_00_VIEW_SCREEN]);}
		render_image = (u16 *)cg.sdl_screen[SDL_00_VIEW_SCREEN]->pixels;
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_00_VIEW_SCREEN]))	{SDL_UnlockSurface(cg.sdl_screen[SDL_00_VIEW_SCREEN]);}
	#endif
//	cg.sdl_screen[SDL_01_BACK_SCREEN] = NULL;
	cg.sdl_screen[SDL_01_BACK_SCREEN] = /*()*/
	#if 0
		PSPL_create_ABGR_surface_buffer
		(
		(void *)(FRAMESIZE * 3),
		SDL_PSP_BUFFER_WIDTH512/*PSP_WIDTH480*/, /*screen->w*/
		PSP_HEIGHT272, /*screen->h*/
		/*pitch = */ /*surface->w*/(SDL_PSP_BUFFER_WIDTH512)*(2)/*surface->format->BytesPerPixel*/
		);
	#else
		SDL_CreateSurface
		(
		SDL_SWSURFACE/*SDL_HWSURFACE*/, /*メインメモリへ*/
		SDL_PSP_BUFFER_WIDTH512/*PSP_WIDTH480*/, /*screen->w*/
		PSP_HEIGHT272// /*screen->h*/
		);
	#endif
	#if 1// (1==US E_GU)
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_01_BACK_SCREEN]))	{SDL_LockSurface(cg.sdl_screen[SDL_01_BACK_SCREEN]);}
		render_image_back = (u16 *)cg.sdl_screen[SDL_01_BACK_SCREEN]->pixels;
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_01_BACK_SCREEN]))	{SDL_UnlockSurface(cg.sdl_screen[SDL_01_BACK_SCREEN]);}
	#endif
	#if (0)
	if (NULL == cg.sdl_screen[SDL_01_BACK_SCREEN])
	{
		CHECKPOINT;
		error(ERR_FATAL, "cant create SDL_Surface.");
	}
	#endif

#if 0
	cg.sdl_screen[SDL_02_TEX_SCREEN] = SDL_CreateRGBSurface
		(
		SDL_SWSURFACE/*SDL_HWSURFACE*/, /*メインメモリへ*/
		SDL_PSP_BUFFER_WIDTH512/*PSP_WIDTH480*/, /*screen->w*/
		PSP_HEIGHT272, /*screen->h*/
		PSP_DEPTH16, /*SDL_VRAM_SCREEN->format->BitsPerPixel*/
		/*0x001f*/PSP_SCREEN_FORMAT_RMASK/*SDL_VRAM_SCREEN->format->Rmask*/,	/*5*/
		/*0x07e0*/PSP_SCREEN_FORMAT_GMASK/*SDL_VRAM_SCREEN->format->Gmask*/,	/*6*/
		/*0xf800*/PSP_SCREEN_FORMAT_BMASK/*SDL_VRAM_SCREEN->format->Bmask*/,	/*5*/
		/*0x0000*/PSP_SCREEN_FORMAT_AMASK/*SDL_VRAM_SCREEN->format->Amask*/ 	/*0*/
		);
	#if 1// (1==US E_GU)
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_02_TEX_SCREEN])) 	{SDL_LockSurface(cg.sdl_screen[SDL_02_TEX_SCREEN]);}
		render_image_tex = (u16 *)sdl_screen[SDL_02_TEX_SCREEN]->pixels;
		if (SDL_MUSTLOCK(cg.sdl_screen[SDL_02_TEX_SCREEN])) 	{SDL_UnlockSurface(cg.sdl_screen[SDL_02_TEX_SCREEN]);}
	#endif
#endif

	//# /* カスタムライブラリかGuを使う場合 */

	#define USE_GULIB (0)
	/* setup GU initialise */
	#if (1==USE_GULIB)
	sceGuInit();/*(実は内部で大抵の初期化処理==Geのレジスタ設定はする)*/
	#else
	pgc_first_initilize();/*(実は内部で大抵の初期化処理==Geのレジスタ設定はする)*/
	#endif
	#if 0
	/*(無くても殆ど同じ)*/
	pgc_display(PGC_OFF);//sceGuDisplay(GU_FALSE);/*画面OFF*/
	#endif
	sceGuStart(GU_DIRECT, gulist);
	#if (1==USE_SWAP_BUFFER)
		#if (16 == SCREEN_DEPTH/*depth*/)/*16 bit(5650), 15 bit(5551), 12 bit(4444) */
		//	sceGuDrawBuffer(GU_PSM_5551, (void*)0, PSP_BUFFER_WIDTH512);
		//	sceGuDrawBuffer(GU_PSM_5551, cg.draw_frame, PSP_BUFFER_WIDTH512);
			sceGuDrawBuffer(/*GU_PSM_5551*/SDL_GU_PSM_0000, cg.draw_frame, PSP_BUFFER_WIDTH512);
		#else // (32 == SCREEN_DEPTH/*depth*/)/*32 bit(8888) */
			sceGuDrawBuffer(GU_PSM_8888, cg.draw_frame, PSP_BUFFER_WIDTH512);
		#endif /* SCREEN_DEPTH */
		sceGuDispBuffer(PSP_WIDTH480, PSP_HEIGHT272, cg.show_frame, PSP_BUFFER_WIDTH512);
		#if (1==USE_ZBUFFER)
		sceGuDepthBuffer(cg.work_frame, PSP_BUFFER_WIDTH512);/*(void*)0x88000*/
	//	sceGuDepthBuffer(cg.work_frame, PSP_BUFFER_WIDTH512);/*(void*)0x110000*/
		#endif /* (1==USE_ZBUFFER) */
	#else
		#if (16 == SCREEN_DEPTH/*depth*/)/*16 bit(5650), 15 bit(5551), 12 bit(4444) */
		//	sceGuDrawBuffer(GU_PSM_5551, (void*)0, PSP_BUFFER_WIDTH512);
		//	sceGuDrawBuffer(GU_PSM_5551, cg.draw_frame, PSP_BUFFER_WIDTH512);
			sceGuDrawBuffer(/*GU_PSM_5551*/SDL_GU_PSM_0000, (void*)0, PSP_BUFFER_WIDTH512);
			sceGuDispBuffer(PSP_WIDTH480, PSP_HEIGHT272, (void*)0x44000, PSP_BUFFER_WIDTH512);
			#if (1==USE_ZBUFFER)
			sceGuDepthBuffer((void*)0x88000, PSP_BUFFER_WIDTH512);
			#endif /* (1==USE_ZBUFFER) */
		#else // (32 == SCREEN_DEPTH/*depth*/)/*32 bit(8888) */
			sceGuDrawBuffer(GU_PSM_8888, (void*)0, PSP_BUFFER_WIDTH512);
			sceGuDispBuffer(PSP_WIDTH480, PSP_HEIGHT272, (void*)0x88000, PSP_BUFFER_WIDTH512);
			#if (1==USE_ZBUFFER)
			sceGuDepthBuffer((void*)0x110000, PSP_BUFFER_WIDTH512);
			#endif /* (1==USE_ZBUFFER) */
		#endif /* SCREEN_DEPTH */
	#endif
	sceGuOffset(2048 - (PSP_WIDTH480 / 2), 2048 - (PSP_HEIGHT272 / 2));
	sceGuViewport(2048, 2048, PSP_WIDTH480, PSP_HEIGHT272);

#if 1
	/* 描画範囲を設定する */
	#if (1==USE_GULIB)
	sceGuEnable(GU_SCISSOR_TEST);
	#else
	pgc_scissor_enable();
	#endif
	sceGuScissor(0, 0, PSP_WIDTH480, PSP_HEIGHT272);
#endif

	#if 1/*(?)*/
	//sceGuAlphaFunc(GU_ALWAYS, 0, 0xff);
	//sceGuEnable(GU_ALPHA_TEST);		/*sceGuDisable(GU_ALPHA_TEST);noiz07*/
	//sceGuDepthFunc(GU_GEQUAL);
	//sceGuEnable(GU_DEPTH_TEST);		/*sceGuDisable(GU_DEPTH_TEST);noiz07*/
	#endif/*(?)*/

#if 000/*(?)*/
	#if 1/*(?)*/
	/*「アルファブレンディング(透明度付き、色重ね合わせ)」*/
	sceGuAlphaFunc(GU_ALWAYS, 0, 0xff);//sceGuAlphaFunc(GU_LEQUAL, 0, 0x01);
	PGC_SEND(PGC_ALPHA_TEST, PGC_ON);	//sceGuEnable(GU_ALPHA_TEST);	/*sceGuDisable(GU_ALPHA_TEST);noiz07*/
	//sceGuAlphaFunc(GU_ALWAYS, 0, 0xff);
	//sceGuEnable(GU_ALPHA_TEST);			/* 有効 */
	//sceGuDisable(GU_ALPHA_TEST);			/* 無効 */	/*noiz07*/
	#endif/*(?)*/
#endif/*000(?)*/

	#if (1==USE_ZBUFFER)
	//sceGuEnable(GU_DEPTH_TEST);			/* 有効 */
	//sceGuDisable(GU_DEPTH_TEST);			/* 無効 */	/*noiz07*/
	PGC_SEND(PGC_DEPTH_TEST, PGC_OFF);	//sceGuDisable(GU_DEPTH_TEST);
	/* psp の z値は 65535(近く) から 0(遠く)で、Z値が通常と逆。 */
	/* このz値は u16 なので、少しはみ出すと、回り込んで変な描画になってしまう。 */
	/* そこで、回り込まないように、適当に余裕分を見繕う。PSPSDK のサンプルでは */
	/* 0xc350(50000) 近く側の境界面、0x2710(10000)遠く側の境界面 となっているが、適当な値なら何でもよい */
	/* sceGuDepthRange(0xc350, 0x2710); */
	#define  Z_CLIP_LENGTH	(10000)
	sceGuDepthRange((0xffff-Z_CLIP_LENGTH), Z_CLIP_LENGTH);
//	sceGuDepthRange(65535, 0);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuDepthMask(GU_TRUE);
	#endif/* (1==USE_ZBUFFER) */

	#if 1
	/* カリングモード(裏向きポリゴンは描画しない)で、有効座標系(右手座標系にするか左手座標系にするか)を決める */
	#if (1==USE_GULIB)
	PGC_SEND(PGC_CULL_FACE, PGC_ON);	//sceGuEnable(GU_CULL_FACE);	/* カリング有効(裏向きポリゴンは描画しない) */
	#endif
	sceGuFrontFace(GU_CW);		/* clock wise(時計周り) 		  右回り、右手座標系(OpenGL 標準?)	 */
//	sceGuFrontFace(GU_CCW); 	/* counter clock wise(反時計周り) 左回り、左手座標系(Direct X 標準?) */
/*
  時計回り(とけいまわり)というのは、時計の針が進む方向と同じ回転方向の事である。
上→右→下→左、あるいは北→東→南→西の順に回転する方向である。右回りとも言われる。
  逆の回転方向を「反時計回り」(はんとけいまわり)という。同様に、これは左回りと言われる。
反時計回りは英語圏では counterclockwise と呼ばれるが、これは CCW と略す場合が多い。

  時計回りの回転方向は日時計を模している。日時計は北回帰線より北で発明された。
日時計の回転方向は、北回帰線より北においては時計回りになるが南では反時計回りになる。

  方位(方位角)は、北を0°として時計回りに数を増やすが、
逆に数学においては、平面角は反時計回りの方向を正として計測される。

  瓶のふたやネジ等は、時計回りに回すと締まり、反時計回りに回すと緩むように作られているが、
これらは右ききの場合、時計回りの方が力が入り易いという理由による。
力の入れすぎで破損するのを防ぐ為にガス管ではこれらとは逆方向になっている。

そーなのかー
*/
	#endif

#if 1/*(?)*/
	#if 1/*(?)*/
//	#define GU_FLAT 		(0)
//	#define GU_SMOOTH		(1)
//	sceGuShadeModel(GU_FLAT);		/*(グーロシェーディングしない)	頂点カラーの色補間機能を使わない場合に指定*/
	sceGuShadeModel(GU_SMOOTH); 	/*(グーロシェーディングする)	頂点カラーの色補間機能を使う場合に指定*/
	#endif/*(?)*/
#endif/*1(?)*/

	#if (1==USE_GULIB)
		#if 0/*(?)*/
		PGC_SEND(PGC_BLEND, PGC_OFF);	//sceGuDisable(GU_BLEND);
		#else
		PGC_SEND(PGC_BLEND, PGC_ON);	//sceGuEnable(GU_BLEND);			/* アルファブレンディング有効 */
		#endif/*(?)*/

		#if 1
		/* テクスチャー有効モードでは、線や面等のフラットポリゴンが使えない */
		PGC_SEND(PGC_TEXTURE_2D, PGC_ON);	//sceGuEnable(GU_TEXTURE_2D);	/* テクスチャー有効 */
		#else
		/* テクスチャー無効モードでは、線や面等のフラットポリゴンが使える(テクスチャーポリゴン、2D画像転送等は出来ない) */
		PGC_SEND(PGC_TEXTURE_2D, PGC_OFF);	//sceGuDisable(GU_TEXTURE_2D);	/* テクスチャー無効 */
		#endif
	#endif

	#if (1==USE_ZBUFFER)
	sceGuClearDepth(0);//Z_BUFFER
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);	/*noiz07*/	/*(Zバッファを消す??)*/
//	sceGuClear(GU_COLOR_BUFFER_BIT/*|GU_DEPTH_BUFFER_BIT*/);	/*noiz07*/
	#endif/* (1==USE_ZBUFFER) */

	#if (1)
		sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);/* 半透明 */
	#else
		sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);/* 半透明不可？ */
	#endif

//	PGC_SEND(PGC_TEX_FILTER, PU8(GU_NEAREST, GU_NEAREST));	//sceGuTexFilter(GU_NEAREST, GU_NEAREST);/*くっきり拡大画面(拡大時直線補完)*/
	PGC_SEND(PGC_TEX_FILTER, PU8(GU_LINEAR, GU_LINEAR));	//sceGuTexFilter(GU_LINEAR, GU_LINEAR);/*ぼやぼや拡大画面(拡大時双曲線補完)*/
	sceGuTexScale(1.0f, 1.0f);//sceGuTexScale(1, 1);
	sceGuTexOffset(0.0f, 0.0f);
//
	/* 環境色を決める？ */
	PGC_SEND(PGC_TEX_ENV_COLOR, 0x00000000);//sceGuTexEnvColor(0x00000000);
//	sceGuTexEnvColor(			0x00ffff00);
	sceGuAmbientColor(			0xffffffff);
	sceGuColor( 				0xff000000);

//
//	u8	ColorKey	= 1;
/* カラーキーを設定する */
//	if (ColorKey)
	{
//		if (!sceGuGetStatus(GU_COLOR_TEST))
		{
			#if (1==USE_GULIB)
			PGC_SEND(PGC_COLOR_TEST, PGC_ON);	//sceGuEnable(GU_COLOR_TEST);
			#endif
		}/*カラーキー有効*/
	//	sceGuColorFunc(GU_NOTEQUAL, 0/*texptr->colorkey*/, 0x00fefefe);
		sceGuColorFunc(GU_NOTEQUAL, 0/*texptr->colorkey*/, 0x00ffffff);
	//	sendCommandi(216, GU_NOTEQUAL & 0x03);
	//	sendCommandi(217, 0 & 0xffffff);
	//	sendCommandi(218, 0x00fefefe);
	}
//	else
//	{
//		if (sceGuGetStatus(GU_COLOR_TEST))
//		{	sceGuDisable(GU_COLOR_TEST);}/*カラーキー無効*/
//	}
			#if (1==USE_GULIB)
	#if 1
	PGC_SEND(PGC_CLIP_PLANES, PGC_ON);	//sceGuEnable(GU_CLIP_PLANES);
	#endif
			#endif
//
	sceGuFinish();
	sceGuSync(0, 0);

//	sceDisplayWaitVblankStart();/* vsync */

	#if (1==USE_GULIB)
	sceGuDisplay(GU_TRUE/*1*/);/* 画面ON */
	#else
	pgc_display(PGC_ON);/* 画面ON */
	#endif
	/* ここまで初期設定 */
	gu_init_vfpu();
	/* ここまで初期設定 */
//	sceGuSync(0, 0);/* (ここまで Gu) */
//	sceDisplayWaitVblankStart();/*vsync*/
//	sceGuSwapBuffers();
	//
	/* --- 入力装置の初期設定 */
	sceCtrlSetSamplingCycle(0); 	/* pad初期化 */
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);	/* アナログキー有効(標準ではデジタルのみ) */
	/*
	psp_pad初期化には時間がかかる。
	ここで初期化しておく。
	初期化してすぐに読もうとしても一番始めの入力が読めない、少し時間(1[frame]程度)が経てば読める。
	そこで、この直後にローディング画面を配置する。
	ローディング画面表示は画像ロードに数フレーム時間がかかるので、パッド初期化後の時間稼ぎに行う。
	*/
	/* --- ローディング画面 */
	#if (1)/* ローディング画面の画像を読みこむ */
	my_file_common_name[0] = BG_TYPE_04_loading;psp_load_bg_file_name();/*(蓮池の画像を作画用画面に読みこむ)*/
	/*(読みこんだ画像を作画用画面から表示用画面に転送する。*/
	/*(この時点では表示用画面の表示部分がまだ無い為、まだ表示されない))*/
	psp_move_screen(MODE_01_POP);/*(仮想スクリーンを復活、取って置いた画面を描く)*/
	#endif
	//
	#if (1)/* ロード専用画面表示を行う。(まだ他の初期化が済んでないので通常の画面表示は出来ない) */
	draw_loading_screen_test();/* ロード画面表示専用。 */
//	draw_loading_screen_test();//仕様変更でダメ
//	blit_direct_vram_loading_screen();
	#endif
	//
	#if (1)/*("独立ライン表示"の初期化)*/
	{
		u32 yyy;
		yyy = (64);/* Y位置 */
		u32 gg;
		for (gg=0; gg<ML_LINE_99_MAX; gg++)
		{
			ml_font[gg].x = (32);/* X位置 */
			ml_font[gg].y = (yyy);
			ml_font[gg].timer	= ML_OFF;
		//	ml_font[gg].render	= NULL;
		//	ml_font[gg].str 	= NULL;
			yyy += (KANJI_FONT_18_HEIGHT_P2);
		}
	}
//			ml_font[0].timer	= ML_ON;/*(デバッグ)*/
//			ml_font[1].timer	= ML_ON;/*(デバッグ)*/
//			ml_font[2].timer	= ML_ON;/*(デバッグ)*/
//		//	ml_font[0].str	= my_font_text;/*(デバッグ)*/
//		//	ml_font[1].str	= my_font_text;/*(デバッグ)*/
//		//	ml_font[2].str	= my_font_text;/*(デバッグ)*/
	#endif





}
	#if (0)/*(デバッグ)*/
	kanji_window_clear_line(0); 			/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
	kanji_cursor_move_home_position();		/* カーソルを1行目(==0)へ移動 */
	{
	//	ml_font[(0)].haikei 		= (ML_HAIKEI_02_JIKI_SPELL_CARD);/* [赤/自機カード用背景]せりふ背景on */
		cg.msg_time 				= (65536);	/* 約 18 分 */
		strcpy(my_font_text, "漢字システムを組み込みました。" "\n");
		kanji_color((7)|STR_CODE_NO_ENTER);
		kanji_draw();
	}
	#endif

void psp_video_init02(void)
{
	{	/* テクスチャ領域の初期化 */
		u32 i;
		for (i=0; i<TEXTURE_MAX; i++)
		{
		//	my_resource[i].my_texture = NULL;
			my_resource[i].my_texture			= initial_resource[i].my_texture;
			my_resource[i].texture_width		= initial_resource[i].texture_width;/*(テクスチャ全体の幅サイズ)*/
			my_resource[i].texture_height		= initial_resource[i].texture_height;/*(テクスチャ全体の高さサイズ)*/
			my_resource[i].buffer_width 		= initial_resource[i].buffer_width;/*(テクスチャ全体の幅サイズの中で、使用している領域サイズ)*/
			//
			my_resource[i].color_format 		= initial_resource[i].color_format;/*([未定]テクスチャの色形式)*/
			my_resource[i].hh					= initial_resource[i].hh;/*([未定]予備)*/
			my_resource[i].object_table_head	= initial_resource[i].object_table_head;
			my_resource[i].file_name			= initial_resource[i].file_name;/*([未定]テクスチャのファイル名)*/
			//
			psp_load_texture(i);/*(テクスチャの初期化。全ての領域にテクスチャを読みこむ。)*/
		}
	}
	kaiwa_obj_set_256();/*(会話スプライトの設定。サイズを 256x256にする。)*/
	/* --- その他の初期設定 */
	cg.side_panel_draw_flag 	= (0);
	cg.draw_boss_hp_value		= (0);
//	callback_gu_draw_haikei 	= NULL;//dr aw_bg_screen = 0;
	cg.callback_gu_draw_haikei_supeka = gu_draw_bg_3D_test01;
	cg.conv_bg_alpha			= 0xffffffff;
//	cg.conv_bg_alpha			= 0x7f7f7f7f;
//

	cg.game_now_stage	= 0;
//	stage_bg_load_texture();//仕様変更で無意味
//	sceKernelDelayThread(5000000);/* 5[秒]何もしないで待つ */
}
			#if (0)
				psp_load_texture( TEX_00_BACK_GROUND	);/*game*/
				psp_load_texture( TEX_02_MAHOUJIN		);/*game*/
				psp_load_texture( TEX_03_JIKI			);/*game*/
				psp_load_texture( TEX_04_TEKI			);/*game*/
				psp_load_texture( TEX_06_BULLET 		);/*game*/
				psp_load_texture( TEX_07_FRONT			);/*game*/
				psp_load_texture( TEX_09_TACHIE_L		);/*game*/
				psp_load_texture( TEX_10_TACHIE_R		);/*game*/
			#endif
/*-------------*/
//	#include "gu_fake_loading.h"
/*-------------*/

/*---------------------------------------------------------
	テクスチャをロードする
---------------------------------------------------------*/



//#if (SDL_BYTE ORDER == SDL_BIG_ENDIAN)
	//#define RMASK 0xff000000
	//#define GMASK 0x00ff0000
	//#define BMASK 0x0000ff00
	//#define AMASK 0x000000ff
	//#define RMASK16 0x0000f800
	//#define GMASK16 0x000007c0
	//#define BMASK16 0x0000003f
	//#define AMASK16 0x00000001
//#else//psp
	//#define RMASK 0x000000ff
	//#define GMASK 0x0000ff00
	//#define BMASK 0x00ff0000
	//#define AMASK 0xff000000
	#define RMASK16 0x0000001f
	#define GMASK16 0x000003e0
	#define BMASK16 0x00007c00
	#define AMASK16 0x00008000
//#endif

/*---------------------------------------------------------
	テクスチャーの読み込み、登録
---------------------------------------------------------*/
#if 0
{
	int kk;
	for (kk=0; kk<(trans_length); kk++)
	{
		#if 0
		/* --- 15bit色に 減色して保持 (color key 使用可) */
		*pixdst =
			((*pixsrc & 0x80000000) >> 16) |
			((*pixsrc & 0x00f80000) >>	9) |
			((*pixsrc & 0x0000f800) >>	6) |
			((*pixsrc & 0x000000f8) >>	3);
	//	*pixdst = MAKECOL15A(GETR32(*pixsrc), GETG32(*pixsrc), GETB32(*pixsrc), GETA32(*pixsrc));
		#else
		/* --- 16bit色に 減色して保持 (color key 使用不可) */
		*pixdst = MAKECOL16(GETR32(*pixsrc), GETG32(*pixsrc), GETB32(*pixsrc));
		#endif
		pixdst++;
		pixsrc++;
	}
}
#endif
		#if (0==USE_32BIT_DRAW_MODE)
	/*static*/ /*extern*/void trans_format8888to5650(u32 *pixsrc, u16 *pixdst, int trans_length)
	{
		int kk;
		for (kk=0; kk<(trans_length); kk++)
		{
		//	(*(cg.kanji_window_screen_image+kk)) = (*(/*font_bg_bitmap_surface_image*/(u32 *)(font_bg_bitmap_surface->pixels)+kk));/*BG_FONT_HAIKEI_OFFSET*/
			/* --- 16bit色に 減色して保持 (color key 使用不可) */
			*pixdst = MAKECOL16(GETR32(*pixsrc), GETG32(*pixsrc), GETB32(*pixsrc));
			pixdst++;
			pixsrc++;
		}
	}
		#else
		/* 色32bitモード */
		#endif

#include "gu_load_texture.h"



/*---------------------------------------------------------
	汎用スプライトの表示(画面転送)
---------------------------------------------------------*/

#if (1==USE_ZBUFFER)
	/* ハードウェアーでソート */
	#define SPR_PRIORITY	(spr->priority)
#else
	/* ソフトウェアーで Zソート */
	#define SPR_PRIORITY	(0)
#endif

#include "render/gu_render_sprite_normal.h"
#include "render/gu_render_sprite_roz.h"



/*---------------------------------------------------------
	フレームタイミングによる全描画
---------------------------------------------------------*/

#if 000
static /*int*/u8 texture_cacheId = 127/*-1*/;
static void trans_texture(void)
{
	MY_DIB_SURFACE *texture_cache_ptr;
	//	texture_cache_ptr = NULL/*0*/;
	//	texture_cache_ptr = gu_bbb_sprite_pool[0].Texture_ptr;
		texture_cache_ptr = my_texture[texture_cacheId];
		/* - テクスチャ転送コマンド */
		sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		#if (1==USE_COLOR_16_AND_32)
		if (16 == texture_cache_ptr->format->BitsPerPixel)
		{
			sceGuTexMode(GU_PSM_5551, 0, 0, /*1*/(USE_SWIZZLE)/*0 swizzle*/);
		}
		else
		#endif
		{
			sceGuTexMode(GU_PSM_8888, 0, 0, /*1*/(USE_SWIZZLE)/*0 swizzle*/);
		}
		sceGuTexImage(0,
			 512/*texture_cache_ptr->w*/,
			 512/*texture_cache_ptr->h*/,
			 512/*texture_cache_ptr->w*/,
			 texture_cache_ptr->MY_DIB_DATA);
	//	sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
//test		sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	//	sceGuTexScale(1.0f, 1.0f);
	//	sceGuTexOffset(0.0f, 0.0f);
}
#endif



/*---------------------------------------------------------

---------------------------------------------------------*/
//extern OBJ *sprite_list000_head;
//extern OBJ *sprite_list444_head;

#include "gu_obj_table.h"

/*static*/static void rotate_and_zoom_check_blit(OBJ *sss)
{
	if (M_ZOOM_Y256_NO_TILT/*0.0*/ != sss->m_zoom.y256) 	/* 特殊機能 */
	{
		if (256/*t256(1.0)*/ != sss->m_zoom.y256)	{goto my_roz;}
		if (256/*t256(1.0)*/ != sss->m_zoom.x256)	{goto my_roz;}
	//	if ((0!= sss->rotationCCW1024)) 			{goto my_roz;}
		if ((0!= sss->rotationCCW65536)) 			{goto my_roz;}
	}
	/* 回転拡大縮小なし、単純矩形コピー */
	render_object_no_rot_zoom(sss);
	return;
my_roz:
	/* 回転拡大縮小あり */
	render_object_use_rot_zoom(sss);
}
#if 0
//	debug_view_objs++;
	/* --- テクスチャの転送が必要なら */
	{
		//if (sss->Texture_ptr != NULL)
		{
			if (( sss->rotationCCW1024 == 0/*.0*/) &&
				( sss->m_zoom.x256 == 256/*1.0*/) &&
				( sss->m_zoom.y256 == 256/*1.0*/)
			)
			{
				/* 回転拡大縮小なし、単純矩形コピー */
				render_object_no_rot_zoom(sss);
			}
			else
			{
				/* 回転拡大縮小あり */
				render_object_use_rot_zoom(sss);
			}
		}
	}
#endif

/* 直接描画 */
#if 1
typedef struct /*()*/
{
	int offset;
	int maximum;
} AAA_TBL;
	static const  AAA_TBL aaa_tbl[OBJECT_TYPE_04_MAX] =
	{
		{	OBJ_HEAD_00_0x0000_TAMA,		OBJ_POOL_00_TAMA_1024_MAX}, 		// OBJECT_TYPE_00_TAMA
	//	{	OBJ_HEAD_02_0x0900_TEKI_FIX,	OBJ_POOL_02_TEKI_FIX_0256_MAX}, 	// OBJECT_TYPE_01_TEKI
		{	OBJ_HEAD_01_0x0800_TOUROKU, 	(OBJ_POOL_01_TOUROKU_0256_MAX+OBJ_POOL_02_TEKI_FIX_0256_MAX)},	// OBJECT_TYPE_01_TEKI
		{	OBJ_HEAD_03_0x0a00_KOTEI,		OBJ_POOL_03_KOTEI_0016_MAX},		// OBJECT_TYPE_02_KOTEI
		{	OBJ_HEAD_04_0x0a10_PANEL,		OBJ_POOL_04_PANEL_0056_MAX},		// OBJECT_TYPE_03_PANEL
	};

//	OBJ *sss, //, VIRTUAL_OBJ_STATE *head_obj_status_table)
//static void common_transfer_objects_01_teki_blit();
//static void common_transfer_objects_02_kotei_blit();
static void common_transfer_objects_blit(
	const int object_type,
	int num,
	int obj_group)
{
	VIRTUAL_OBJ_STATE *head_obj_status_table;
	head_obj_status_table = my_resource[num].object_table_head;
//
	{
			OBJ *sss;
	//		sss = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+ii];
		int ii;
	//	for (ii=0; ii<OBJ_POOL_03_KOTEI_0016_MAX/*OBJ_111JIKI_POOL_MAX*/; ii++)/* 全部調べる。 */
		for (ii=0; ii<aaa_tbl[object_type].maximum/*OBJ_POOL_02_TEKI_FIX_0256_MAX*/; ii++)/* 全部調べる。 */
		{
			sss = &obj99[/*OBJ_HEAD_02_0x0900_TEKI_FIX*/(aaa_tbl[object_type].offset)+ii];
		//
			if (JYUMYOU_NASI < sss->jyumyou)/* あれば */
			{
				if (/*SP_BULLET*/obj_group/*OBJ_Z04_TAMA*/ & sss->obj_type_set)
				{
					{
						int tama_index = (OBJ_Zff_MASK_SUB_TYPE & sss->obj_type_set);
						sss->w			= head_obj_status_table[tama_index].w;
						sss->h			= head_obj_status_table[tama_index].h;
						sss->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
						sss->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
					}
					/* --- 汎用スプライト描画 */
					rotate_and_zoom_check_blit(sss);
				}
			}
		//	sss += sizeof(OBJ);
//			sss = sss->next;/*次*/
		}
	}
}
#endif

#if 0
/*---------------------------------------------------------

---------------------------------------------------------*/
//static void common_transfer_objects_01_teki_blit();
//static void common_transfer_objects_02_kotei_blit();
static void common_transfer_objects_01_teki_blit(
//	const int object_type,
	int num,
	int obj_group)
{
	VIRTUAL_OBJ_STATE *head_obj_status_table;
	head_obj_status_table = my_resource[num].object_table_head;
//
	{
			OBJ *sss;
	//		sss = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+ii];
		int ii;
	//	for (ii=0; ii<OBJ_POOL_03_KOTEI_0016_MAX/*OBJ_111JIKI_POOL_MAX*/; ii++)/* 全部調べる。 */
		for (ii=0; ii</*aaa_tbl[object_type].maximum*/OBJ_POOL_02_TEKI_FIX_0256_MAX/*OBJ_POOL_02_TEKI_FIX_0256_MAX*/; ii++)/* 全部調べる。 */
		{
			sss = &obj99[/*OBJ_HEAD_02_0x0900_TEKI_FIX*/OBJ_HEAD_02_0x0900_TEKI_FIX/*(aaa_tbl[object_type].offset)*/+ii];
		//
			if (JYUMYOU_NASI < sss->jyumyou)/* あれば */
			{
				if (/*SP_BULLET*/obj_group/*OBJ_Z04_TAMA*/ & sss->obj_type_set)
				{
					{
						int tama_index = (OBJ_Zff_MASK_SUB_TYPE & sss->obj_type_set);
						sss->w			= head_obj_status_table[tama_index].w;
						sss->h			= head_obj_status_table[tama_index].h;
						sss->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
						sss->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
					}
					/* --- 汎用スプライト描画 */
					rotate_and_zoom_check_blit(sss);
				}
			}
		//	sss += sizeof(OBJ);
//			sss = sss->next;/*次*/
		}
	}
}//static void common_transfer_objects_01_teki_blit();
//static void common_transfer_objects_02_kotei_blit();
static void common_transfer_objects_02_kotei_blit(
//	const int object_type,
	int num,
	int obj_group)
{
	VIRTUAL_OBJ_STATE *head_obj_status_table;
	head_obj_status_table = my_resource[num].object_table_head;
//
	{
			OBJ *sss;
	//		sss = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+ii];
		int ii;
	//	for (ii=0; ii<OBJ_POOL_03_KOTEI_0016_MAX/*OBJ_111JIKI_POOL_MAX*/; ii++)/* 全部調べる。 */
		for (ii=0; ii</*aaa_tbl[object_type].maximum*/OBJ_POOL_03_KOTEI_0016_MAX/*OBJ_POOL_02_TEKI_FIX_0256_MAX*/; ii++)/* 全部調べる。 */
		{
			sss = &obj99[/*OBJ_HEAD_02_0x0900_TEKI_FIX*/OBJ_HEAD_03_0x0a00_KOTEI/*(aaa_tbl[object_type].offset)*/+ii];
		//
			if (JYUMYOU_NASI < sss->jyumyou)/* あれば */
			{
				if (/*SP_BULLET*/obj_group/*OBJ_Z04_TAMA*/ & sss->obj_type_set)
				{
					{
						int tama_index = (OBJ_Zff_MASK_SUB_TYPE & sss->obj_type_set);
						sss->w			= head_obj_status_table[tama_index].w;
						sss->h			= head_obj_status_table[tama_index].h;
						sss->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
						sss->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
					}
					/* --- 汎用スプライト描画 */
					rotate_and_zoom_check_blit(sss);
				}
			}
		//	sss += sizeof(OBJ);
//			sss = sss->next;/*次*/
		}
	}
}
#endif


/*---------------------------------------------------------
	オブジェバンクシステム
	-------------------------------------------------------
	バンク設定を反映させる
	オブジェクトのグラフィックや当たり判定を変更する。
	弾グラと弾あたり判定を変更する。
---------------------------------------------------------*/

extern void reflect_sprite_spec(OBJ *sss, u32 bank_offset)
{
//	int num = TEX_06_BULLET;
	VIRTUAL_OBJ_STATE *head_obj_status_table;
//	my_resource[TEX_06_BULLET].object_table_head = (obj_status_table+(OBJ_BANK_00_TAMA*OBJ_BANK_SIZE));
//	my_resource[TEX_06_BULLET].object_table_head = (obj_status_table+(OBJ_BANK_01_ITEM*OBJ_BANK_SIZE));
//	head_obj_status_table = my_resource[TEX_06_BULLET/*num*/].object_table_head;
	head_obj_status_table = (obj_status_table+(bank_offset));
	{
		int tama_index = (OBJ_Zff_MASK_SUB_TYPE & sss->obj_type_set);
		sss->w			= head_obj_status_table[tama_index].w;
		sss->h			= head_obj_status_table[tama_index].h;
		sss->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
		sss->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
	}
}


/*---------------------------------------------------------
	直接描画
---------------------------------------------------------*/

static void common_transfer_objects_00_tama_blit_non_reflect(
//	OBJ *sss,
//TEX_06_BULLET int num,
	int obj_group)//, VIRTUAL_OBJ_STATE *head_obj_status_table)
{
	int ii;
	for (ii=0; ii<OBJ_POOL_00_TAMA_1024_MAX; ii++)/* 全部調べる。 */
	{
		OBJ *sss;
		sss = &obj99[OBJ_HEAD_00_0x0000_TAMA+ii];
	//
		if (JYUMYOU_NASI < sss->jyumyou)/* あれば */
		{
			if (/*SP_BULLET*/obj_group/*OBJ_Z04_TAMA*/ & sss->obj_type_set)
			{
				/* --- 汎用スプライトの描画 */
				rotate_and_zoom_check_blit(sss);
			}
		}
	}
	//	s_blit_all_objects();/*PRIORITY_05_BULLETS*/
}


#if 1
/*---------------------------------------------------------
	ボスの HP 表示の子関数
---------------------------------------------------------*/
extern void dec_print_format( u32 num, int size, char *my_str);


static u8 es_panel[4];




/*r43*/static int boss_work_life_value;/* ボスhp体力値 */ /* ボス魔方陣サイズ描画値 */

static void check_draw_boss_hp_value(void)
{
	OBJ *h;
	h		= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(ボス本体)*/
	#if (1)/*(r36要らない？)*/
	if (NULL == h)
	{
		return;/* ボスが無い場合は何もしない */
	}
	#endif
	boss_work_life_value = (h->boss_hp);
	#if 0
	if (0 > boss_work_life_value)	return;/* 負数の場合は何もしない */
	if (9*(4*8*1024) < boss_work_life_value) return;/* 範囲外の場合は何もしない */
	#else
//	if (0 != ((boss_work_life_value)&(0xffffc000)) ) return;/* 範囲外の場合は何もしない */
	if (0 > boss_work_life_value)
	{
		boss_work_life_value = 0;	//	/* まずいかも(?)*/
	}
	if (0 == boss_work_life_value)/*+bo ss_life_value*/
	{
		return;/* 範囲外の場合は何もしない */
	}
	#endif
//	s_cg_game_boss_cx256 = (h->center.x256);/*(?)141477*/
//	s_cg_game_boss_cy256 = (h->center.y256);/*(?)141477*/
// 0001 1111 1110 0000;  >>=(2+3);		0000 0000 1111 1111; 0xff;
// 0111 1111 1000 0000;  >>=(2+3+2);	0000 0000 1111 1111; 0xff;
	/*static*/ int draw_boss_hp_value_set;
//	draw_boss_hp_value_set = ((boss_work_life_value & 0x03fc)>>2);/* ボスhp描画値 */
//	draw_boss_hp_value_set = ((boss_work_life_value & 0x1fe0)>>(2+3));/* ボスhp描画値 */
//	draw_boss_hp_value_set = ((boss_work_life_value & 0x7f80)>>(7));/* (2+3+2)ボスhp描画値(-r35u1) */
//	draw_boss_hp_value_set = ((boss_work_life_value & 0x1fe00)>>(9));/* (2+3+2+2)ボスhp描画値(r35u2-) */
	draw_boss_hp_value_set = ((boss_work_life_value>>(9)) & 0xff);/* (2+3+2+2)ボスhp描画値(r35u2-) */
	if (cg.draw_boss_hp_value < draw_boss_hp_value_set)
			{cg.draw_boss_hp_value++;}
	else	{cg.draw_boss_hp_value--;}
}



/*---------------------------------------------------------
	カウンタについて：
	カウンタは 9 から点滅＆音を鳴らすという風に
	心理的に受けとれるようにしてある。
	これを本当に 9 から処理すると人間の感覚に合わない。
//
	音は 10 (の終わり)から鳴らす。これは 10 の始めは 9 の終わりなので、
	9 から鳴っているとみなせる。(理屈上ズレはない)
//
	点滅は 10 から点滅させる。これは 10 から本当に点滅している。
	注意深く見れば 10 が消えている。(音が鳴る前に 10 が消えている)
	しかし人間の感覚からすると「 9 から点滅しているように感じる」
	人間の視覚は予告が無いと区切りに反応しない。
//
	11 11 11 10 10 10 09 09 09 08 08 08 (時間の流れ)
	無 無 無 無 無 無 音 無 無 音 無 無 (音は 10 (の終わり)から鳴らす。理屈上ズレはない)
	点 点 点 点 点 消 点 点 消 点 点 消 (点滅は 10 から点滅させる。人間の感覚からすると「 9 から点滅しているように感じる」)
				   ↑
---------------------------------------------------------*/
				#if 000
				card.card_timer 	= byou64(60);		/* (とりあえず) */
				#endif
	#if 0
	OBJ *h;
	h		= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(ボス本体)*/
	#endif

static void set_boss_gauge(void)
{
	#if 1/*ボス時間経過*/
	u8 boss_draw_timer_low		= ((card.card_timer) & 0x3f);/* */
	u32 boss_draw_timer_value	= ((card.card_timer) >> (6));/* */
	#endif
	//	99 以上は 99 表示
	if (99 < boss_draw_timer_value)
	{
		boss_draw_timer_value = 99;
	}
	/*カウンタ*/
	if (0==boss_draw_timer_low)
	{
		/* カウント 9 から音を鳴らす。 */
	//	if ((10  ) > boss_draw_timer_value) 	/* (10	)==設定値 10 で、カウント 8 から音が鳴るように聞こえる。 */
		if ((10+1) > boss_draw_timer_value) 	/* (10+1)==設定値 11 で、カウント 9 から音が鳴るように聞こえる。 */
		{
			voice_play_menu(VOICE10_COUNT_TIMER, TRACK06_ITEM/*TRACK03_IVENT_DAN*/);/*(テキトー)*/
		}
	}
	/* boss hp 画像の文字幅分 / gauge stringth x width */
//	#define HPGAUGE_X_OFS (50)
//	#define HPGAUGE_Y_OFS (6)
	#define HP_FONT_X_OFS (4)	/*(50-(8*5)-3)*/	/*(37+10) dx*/
	#define HP_FONT_Y_OFS (1)/*(0+0) dy*/
	//
	#define BOSS_TIMER_X_OFS (PPP-16-4)/* dx*/
	#define BOSS_TIMER_Y_OFS (1)/*(0+0) dy*/
	/* 1024以上の値は数字で表示 */
	{	char buffer[8/* 4 3*/];
	#if 1
		//	スペル残り時間表示
		if (
			//	( 9 < boss_draw_timer_value) || 	/* 10以上は無条件で表示。カウント 8 から点滅してるように見える。 */
				(10 < boss_draw_timer_value) || 	/* 11以上は無条件で表示。カウント 9 から点滅してるように見える。 */
				(20 < boss_draw_timer_low)			/* 点滅 20=(64/3) */
			)
		{
			strcpy(buffer, "00");
			dec_print_format( (boss_draw_timer_value), 2, (char*)buffer);
			es_panel[2] = (buffer[0] & 0x0f);	/* 残りカード時間10の桁 */
			es_panel[3] = (buffer[1] & 0x0f);	/* 残りカード時間 1の桁 */
		}
	#endif
	//	残りライフ表示
	//	es_panel[1] = ((bo ss_work_life_value>>(13)) & 0x0f);	/* (10+3)ボス体力目安 */
	//	es_panel[1] = ((bo ss_work_life_value>>(15)) & 0x0f);	/* (10+3+2)ボス体力目安(-r35u1) */
	//	es_panel[1] = ((bo ss_work_life_value>>(17)) & 0x0f);	/* (10+3+2)ボス体力目安(r35u2-) */
	//	es_panel[1] = ((draw_boss_hp_value_set>>(17-9)) & 0x0f);	/* (10+3+2)ボス体力目安(r35u2-) */
	//	es_panel[1] = ((draw_boss_hp_value_set>>(8)) & 0x0f);	/* 8==(17-9) (10+3+2)ボス体力目安(r35u2-) */
	#if 1
//	/*(バグ!描かないr43)*/		es_panel[1] = (((cg.draw_boss_hp_value)>>(8)) & 0x0f);	/* 8==(17-9) (10+3+2)ボス体力目安(r35u2-) */
	/*(r43とりあえず)*/			es_panel[1] = (((boss_work_life_value)>>(16)) & 0x0f);	/* 8==(17-9) (10+3+2)ボス体力目安(r35u2-) */
	#endif

	//	es_panel[0] = (10);/* 10(r38)"ene my" ボスの位置表示 */
	//	es_panel[0] = (13);/* 13(r39)"ene my" ボスの位置表示 */
		es_panel[0] = (8+((PANEL_STR_ene_my)&0x0f));/* 13(r39)"ene my" ボスの位置表示 */
	}
}


/*---------------------------------------------------------
	直接描画
---------------------------------------------------------*/

static void gu_draw_score_chache(void)
{
	VIRTUAL_OBJ_STATE *head_obj_status_table;
	head_obj_status_table = my_resource[TEX_07_FRONT/*num*/].object_table_head;
//
	static	/*TGameSprite*/OBJ gu_bbb_sprite_pool[1];
	/*TGameSprite*/OBJ *obj;
	obj = &gu_bbb_sprite_pool[0];
	int i;
	for (i=0; i<MAX_SCORE_CHACHE; i++)
	{
		SCORE_CHACHE_DATA *aaa;
		aaa = &(score_number_chache[i]);
	//	if (SCORE_DELETE < aaa->time_out_color8888)
		if (0x80000000 & (aaa->time_out_color8888) )
		{
			aaa->time_out_color8888 -= 0x01000000;	// 時間経過
			obj->color32		= aaa->time_out_color8888;		/* α値(0xff==255 で不透明、0 で透明) */
			/* --- オブジェクト表示設定 */
			obj->center.y256	= aaa->y256;	aaa->y256 -= 50;	/* 上に移動 */
			obj->center.x256	= aaa->x256;	/*x 512/256 */
			{
		//	int tama_index = ((6*8)+3)+es_panel[i]/*(aaa->number)*/;
			int tama_index = ((6*8)+6)+(aaa->number);
			obj->w			= head_obj_status_table[tama_index].w;
			obj->h			= head_obj_status_table[tama_index].h;
			obj->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
			obj->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
			}
			#if (1==USE_ZBUFFER)
			obj->priority	= sss->m_priority;			/*aaa*/ 	/* 表示優先順位 */
			#endif/* (1==USE_ZBUFFER) */
			{
				/* 回転拡大縮小なし、単純矩形コピー */
				render_object_no_rot_zoom(obj);
			}
		}
	}
//
	/* [ ボスの体力チェック ] */
	//	if (B01_BA TTLE == pd_bo ssmode)
	//	if ((STATE_FLAG_0x0800_IS_BOSS|0) == (cg_state_flag & (STATE_FLAG_0x0800_IS_BOSS|STATE_FLAG_0x0200_IS_KAIWA_MODE)))
	if (SCENE_NUMBER_0x0800_BOSS_TATAKAU==(cg_state_flag & (SCENE_NUMBER_MASK)))
	{
		check_draw_boss_hp_value();
	}
//
	if (0!=cg.draw_boss_hp_value)
	{
		/* [ ボスの体力表示 ] */
		{
			set_boss_gauge();
		}
		/* FRONT 面を間借りして、スコア表示 */
	/* 数字を表示 */
		/* ボスの位置を表示 */
		for (i=0; i<4; i++)
		{
			enum
			{
				my_pos_cx = 0,
				my_pos_cy,
				my_pos_MAX
			};
			/* 座標はobjの中心座標、 */
			static const int ttt_aaa_tbl[4][my_pos_MAX] =
			{
				/* cx256,					cy256 */
				{t256(256+4),				t256(272-(10/2)-2)},	/* "ene my" */
				{t256(50+4),				t256(1+(10/2))},		/* "boss" */
				{t256((GAME_WIDTH-16-4)),	t256(1+(10/2))},		/* "timex1"8x10ローマ数字 */
				{t256((GAME_WIDTH-16-4+8)), t256(1+(10/2))},		/* "timex10"8x10ローマ数字 */
			};
			/* --- オブジェクト表示設定 */
			obj->center.y256			= ttt_aaa_tbl[i][my_pos_cy];// ((aaa->center.y256)); // aaa->center.y256 -= 50; /* 上に移動 */
			obj->center.x256			= ttt_aaa_tbl[i][my_pos_cx];// ((aaa->center.x256)); /*x 512/256 */
			obj->color32				= 0xffffffff;		/* α値(0xff==255 で不透明、0 で透明) */
			if (0==i)
			{
				OBJ *zzz_player;
				zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
				OBJ *obj_boss;
				obj_boss	= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(ボス本体)*/
					obj->center.x256			= (obj_boss->center.x256);
				if (t256(32)<abs((obj_boss->center.x256)-(zzz_player->center.x256)))
				{
				//	obj->center.x256			= (obj_boss->center.x256);
					;
				}
				else
				{
				//	obj->center.x256			= (t256(512-128));
// 見難い			obj->color32		= 0x77ffffff;		/* α値(0xff==255 で不透明、0 で透明) */
					obj->color32		= 0x33ffffff;		/* α値(0xff==255 で不透明、0 で透明) */
					/* 普通の半透明だと見にくすぎるので、かなり薄くする。 */
				}
			}
			{
		//	int tama_index = ((5*8)+4)+(9);// (aaa->number);
		//	int tama_index = ((5*8)+3)+(9)/*(aaa->number)*/;
//			int tama_index = ((5*8)+3)+es_panel[i]/*(aaa->number)*/;		// (r38)
			int tama_index = ((5*8)/*+3*/)+es_panel[i]/*(aaa->number)*/;	// (r39)
			obj->w			= head_obj_status_table[tama_index].w;
			obj->h			= head_obj_status_table[tama_index].h;
			obj->tx 		= head_obj_status_table[tama_index].u;		//sss->texture_x;
			obj->ty 		= head_obj_status_table[tama_index].v;		//sss->texture_y;
			}
			#if (1==USE_ZBUFFER)
			obj->priority	= sss->m_priority;			/*aaa*/ 	/* 表示優先順位 */
			#endif/* (1==USE_ZBUFFER) */
			{
				/* 回転拡大縮小なし、単純矩形コピー */
				render_object_no_rot_zoom(obj);
			}
		}
	}
}
#endif

	/* 共通部分 */
	#include "render/gu_render.h"

	/* テクスチャ変形による擬似3D 将来的に無くなる予定。 */
	#include "render/gu_haikei_03_bg_fake_3D.h"

	/* "永遠亭"の予定。 */
	#include "render/gu_haikei_02_bg_eientei.h"

	/* 256x256テクスチャを敷き詰める2D背景を描画 */
	#include "render/gu_haikei_00_bg_2D_256.h"

	/* ボスの後ろの魔方陣(大)を描画 */
	#include "render/gu_render_boss_big_mahoujin.h"

	/* 自分がボム(カード)撃った場合に出る。文字のロゴを描画 */
	#include "render/gu_render_spell_logo.h"

	/* SDL画面を描画 */
	#include "render/gu_render_SDL_screen.h"
	#include "render/gu_render_tache_screen.h"/*(立ち絵のテスト)*/

	#if (0)/*(-r34)*/
//	#include "render/gu_render_serifu_moji.h"	/* 会話の文字を描画 */
//	#include "render/gu_render_supeka_name.h"	/* ボスのカード名を描画 */
	#else
	/* (r35)漢字の文字(独立ライン描画システムへ変更) */
	#include "render/gu_render_kanji_system.h"
	#endif

	/* スコアパネルになる予定の部分(現在SDL) */
	/* ボス体力描画のみ(現在Gu) */
	#include "render/gu_render_score_window.h"
//	/* 半透明のせりふウィンドウ枠 */
	#include "render/gu_render_serifu_window.h"


	/* ラインテスト(まだ使用してない) */
//	#include "render/gu_render_line_test.h"
	#include "render/gu_render_laser_test.h"

	/* 3Dのテスト */
	#include "render/gu_haikei_01_bg_3D_test01.h"
	#include "render/gu_haikei_01_bg_3D_test02.h"


/*---------------------------------------------------------

---------------------------------------------------------*/

static void gu_draw_serifu_haikei(void)
{
	if (0 <= ml_font[(0)].haikei)/*(-1で無効)*/
	{
		gu_draw_rect_window(ml_font[(0)].haikei);
	}
}


/*---------------------------------------------------------

---------------------------------------------------------*/

static void gu_draw_font_texture_transfer(void)
{
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);/*(?)*/		/*勝手にdou ble buffer(?)*/
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuTexMode(/*GU_PSM_5551*/SDL_GU_PSM_0000/*GU_PSM_5650*/, 0, 0, 0/*0 swizzle*/);
	sceGuTexImage(0, 512, 512, 512, cg.kanji_window_screen_image);
}

/*---------------------------------------------------------
	テクスチャをセット
	-------------------------------------------------------
	テクスチャ設定コマンド(sceGuTexImage)は内部で、キャッシュ(GPU)が
	フラッシュバックされ、速度低下します。
	使い過ぎる(100回以下ぐらいなら問題ないかも)と 60fpsを保つのは無理ですので、
	少なくなるようにゲームを設計します。
---------------------------------------------------------*/
static void gu_set_texture(int texture_number)
{
//	sceGuTexFunc(GU_TFX_ADD, GU_TCC_RGB);// (?)
//	sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);/* 半透明 */
	sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGB);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
//	sceGuBlendFunc(GU_ADD, GU_FIX, GU_ONE_MINUS_SRC_ALPHA, (cg.conv_bg_alpha), 0xffffffff);
		#if (16==USE_BLIT_COLOR_BIT)
//	sceGuTexMode(/*GU_PSM_5551*/SDL_GU_PSM_0000/*GU_PSM_5650*/, 0, 0, (USE_SWIZZLE));/*1 swizzle*/
//	sceGuTexMode(/*GU_PSM_5551*/GU_PSM_5551/*GU_PSM_5650*/, 0, 0, (USE_SWIZZLE));/*1 swizzle*/
//	sceGuTexMode(/*GU_PSM_5551*/GU_PSM_4444/*GU_PSM_5650*/, 0, 0, (USE_SWIZZLE));/*1 swizzle*/
	sceGuTexMode(/*GU_PSM_5551*/GU_PSM_5650/*GU_PSM_5650*/, 0, 0, (USE_SWIZZLE));/*1 swizzle*/
		#else
	sceGuTexMode(/*GU_PSM_5551*/GU_PSM_8888/*GU_PSM_5650*/, 0, 0, (USE_SWIZZLE));/*1 swizzle*/
		#endif
//	sceGuTexImage(0, TW128, TH128, 512, bullet_image);
//	sceGuTexImage(0, TW128/2, TH128/2, TW128/2/*WK512*/, my_texture[TEX_06_BULLET]->pixels);
//	sceGuTexImage(0, TW128, TH128, TW128/*WK512*/, my_texture[TEX_00_BACK_GROUND]->pixels);
//	sceGuTexImage(0, 256, 256, 256/*WK512*/, ((my_resource[texture_number].my_texture)->pixels));
	sceGuTexImage(0,
		(my_resource[texture_number].texture_width),
		(my_resource[texture_number].texture_height),
		(my_resource[texture_number].buffer_width), 	/*WK512*/
		((my_resource[texture_number].my_texture)->pixels));
//	sceGuTexFilter(GU_LINEAR, GU_LINEAR);//test
}


/*---------------------------------------------------------
	ゲーム中の描画処理その１
	---------------------------------------------------------
	弾よりプライオリティーが下にあるものをプライオリティー順に描く。
	プライオリティー＃２．BG 画面を描画
	プライオリティー＃３．背景障害物を描画
	プライオリティー＃４．魔方陣を描画
	プライオリティー＃５．ポリゴンライン面を描画(未作成)
	プライオリティー＃６．自機を描画(A)
	プライオリティー＃６．自機を描画(B)
	プライオリティー＃７．ラインテスト画面を描画
	プライオリティー＃８．敵を描画
	プライオリティー＃９．ITEMを描画
	プライオリティー＃10．敵弾を描画
---------------------------------------------------------*/

//static void callback_gu_draw_haikei_all(void)
static void gu_blit_render_screen_01(void)
{
/* -- プライオリティー＃２BG 画面を描画 */
	#if (1)
	{
		gu_set_texture(TEX_00_BACK_GROUND);
	//	sceGuEnable(GU_CLIP_PLANES);
	//	#if (1==USE_F3D)
	//	gu_draw_bg_fake3D();
	//	#else
	//	gu_draw_bg_2D();
	//	#endif
		(cg.callback_gu_draw_haikei)(); //callback_gu_draw_haikei_all();
	//	sceGuDisable(GU_CLIP_PLANES);
	}
	#endif
/* -- プライオリティー＃３．背景障害物を描画 */
	#if (1)
	#endif
/* -- プライオリティー＃４．魔方陣を描画 */
	#if (1)
	{
		if (0!=cg.draw_boss_hp_value)
		{
			gu_set_texture(TEX_02_MAHOUJIN);	/* テクスチャをセット */
			gu_draw_big_maho_jin();
		}
	}
	#endif
/* -- プライオリティー＃５．ポリゴンライン面を描画 */
	#if (0)
	{
		/* 魔方陣画像の一部を間借りする予定 */
		/* パチェレーザー */
	}
	#endif
/* -- プライオリティー＃６．自機を描画 */
	#if (1)
//	if (NULL != callback_gu_draw_haikei)	//共用if (0!=dr aw_bg_screen)
	{
		gu_set_texture(TEX_03_JIKI);

		/*jiki_transfer_object();*/
		{
		//	common_transfer_objects(sprite_list000_head, TEX_03_JIKI, OBJ_Z01_JIKI_GET_ITEM, obj_status_table+(2*4*8*8));
		//	common_transfer_objects(sprite_list000_head, TEX_03_JIKI, OBJ_Z01_JIKI_GET_ITEM, obj_status_table+(8*8)+((cg_game_select_player)<<6) );
			my_resource[TEX_03_JIKI].object_table_head = (obj_status_table+(OBJ_BANK_01_REIMU_A*OBJ_BANK_SIZE)+((cg_game_select_player)<<6));
			/* 自機直接描画(自機面) */
			common_transfer_objects_blit(OBJECT_TYPE_02_KOTEI, TEX_03_JIKI, OBJ_Z01_JIKI_GET_ITEM); /*sprite_list000_head, */
			/* その他 */
		//	TGameScreen_ClearSprite();
			#if 1/*システムの自機面描画(雑魚として登録したもの) */
			common_transfer_objects_blit(OBJECT_TYPE_01_TEKI, TEX_03_JIKI, OBJ_Z01_JIKI_GET_ITEM);/* 自機弾やボム時の立ち絵等の描画 */  /*sprite_list000_head, */
			#endif
		}
	//	s_blit_all_objects();/*PRIORITY_02_PLAYER*/
	}
	#endif /*(000)*/




/* -- プライオリティー＃７．ラインテスト画面を描画 */
	#if (1==LINE_TEST)
	if (NULL != cg.callback_gu_draw_haikei) //if (0!=dr aw_bg_screen)
	{
		/* -- ラインテスト画面を描画 */
	//	if (cg.laser_mode)
		if (LASER_TYPE_00_OFF != (lz[0].laser_type))/* lz[0]==0;の場合、すべてoff。(レーザーモード 0:off, 1:on) */
		{
		//	gu_blit_lines();
			gu_blit_laser_test();
		}
	}
	#endif /*(000)*/
	#if 000
//	sceGuScissor(0, 0, PSP_WIDTH480, PSP_HEIGHT272);	/* 描画範囲を設定する */
//	[ 旧SDL画面描画 ]
//	sceGuScissor(0, 0, GAME_WIDTH, GAME_HEIGHT);	/* 描画範囲を設定する */
	#endif
//
/* -- プライオリティー＃８．敵を描画 */
	/* ☆ 敵面エフェクト */
	/* ザコ(敵面エフェクト) */
	/* ボス(敵面エフェクト) */
	#if (1)
	{
		gu_set_texture(TEX_04_TEKI);	/* テクスチャをセット */
		#if (1)
		/*bullet_transfer_object();*/
		{
		//	common_transfer_objects(sprite_list000_head, TEX_04_TEKI, OBJ_Z04_TAMA, obj_status_table+0);
			#if 0000/* 別で設定 */
			my_resource[TEX_04_TEKI].object_table_head = (obj_status_table+(OBJ_BANK_11_ZAKO_STAGE1*OBJ_BANK_SIZE));
			#endif
		//	TGameScreen_ClearSprite();
			common_transfer_objects_blit(OBJECT_TYPE_01_TEKI, TEX_04_TEKI, OBJ_Z02_TEKI); /*sprite_list000_head, */
		}
	//	s_blit_all_objects();/*PRIORITY_05_BULLETS*/
		#else
		blit_bullet_all();
		#endif /*(000)*/
	}
	#endif /*(000)*/
//
/* -- プライオリティー＃９．ITEMを描画 */
//	/* その他の自機素材(アイテム面エフェクト) */
	#if (1)
	{
		gu_set_texture(TEX_06_BULLET);	/* テクスチャをセット */
		#if (1)
		/*bullet_transfer_object();*/
		{
		//	common_transfer_objects(sprite_list444_head, TEX_06_BULLET, OBJ_Z04_TAMA, obj_status_table+0);
			#if 000/* 別で設定 使ってない*/
			my_resource[TEX_06_BULLET].object_table_head = (obj_status_table+(OBJ_BANK_01_ITEM*OBJ_BANK_SIZE));
			#endif/*000*/
		//	TGameScreen_ClearSprite();// (?)
			common_transfer_objects_00_tama_blit_non_reflect(OBJ_Z03_ITEM);/*sprite_list444_head, */ /*TEX_06_BULLET, */
		}
		#else
		blit_bullet_all();
		#endif /*(000)*/
	}
	#endif /*(000)*/
//
/* -- プライオリティー＃10．敵弾を描画 */
	/* ☆ 弾面エフェクト */
	#if (1)
	/*
		VRAMが使えないと、タイミングの関係でめんどくさい？
	*/
	/* 0==リリース, 1==開発中 */
//	#define KAIHATSU_MODE (0)
//	#if (0==KAIHATSU_MODE)
//	if (shooting_game_core_work == cg.main_call_func)/* game_coreの場合のみ弾を描画(continue画面とかでは描かない) */
//	#endif
	{
	//	gu_set_texture(TEX_06_BULLET);	/* テクスチャをセット */
		#if (1)
		/* 全弾配列は分割する予定 なので専用に書き換える予定 */
		/*bullet_transfer_object();*/
		{
		//	common_transfer_objects(sprite_list444_head, TEX_06_BULLET, OBJ_Z04_TAMA, obj_status_table+0);
			#if 000/* 別で設定 使ってない*/
			my_resource[TEX_06_BULLET].object_table_head = (obj_status_table+(OBJ_BANK_00_TAMA*OBJ_BANK_SIZE));/*使ってない*/
			#endif/*000*/
		//	TGameScreen_ClearSprite();// (?)
			common_transfer_objects_00_tama_blit_non_reflect(OBJ_Z04_TAMA);/*sprite_list444_head, */ /*TEX_06_BULLET, */
		}
		#else
		blit_bullet_all();
		#endif /*(000)*/
	}
	#endif /*(000)*/
//
}


static u32 gu_bg_set_clear_color;
extern void gu_set_bg_u32_clear_color(u32 set_u32_clear_color)
{
	gu_bg_set_clear_color = set_u32_clear_color;
}

/*---------------------------------------------------------
	画面描画
---------------------------------------------------------*/

	#define USE_VSYNC			(0)
/* 0:VSYNC取らない。 USE_VSYNC いわゆるv-sync 1 で on だが、まだ遅いので無理。 */
	#define USE_MAX_GU_TIME 	(0)
//	#define USE_MAX_GU_TIME 	(1)
/* 0:USE_MAX_GU_TIME [Gu時間を最大に取るタイプ](色々制限あり)
	Guの転送を考えて、Gu側でなるべく並列動作させるようにタイミングを考えたもの。
	pspで始めて実装したのは、 http://www.fumi2kick.com/pspapp/ この辺。
	SDL共用する場合(ソフト描画)は、(タイミング的に)絶対に間に合わない。
	(フレームバッファを設けてスワップさせれば間に合う。つまりトリプルバッファ。但しメモリ食うし、遅くなるかも？)
	(Gu描画しかしないなら、1:USE_MAX_GU_TIMEで十分ではある。)
	現状はSDL共用するので、1:USE_MAX_GU_TIMEに出来ない。(SDL使わないなら1:USE_MAX_GU_TIMEに出来る)
*/
#include "gu_video_frame_normal.h"
#include "gu_video_frame_only_loading.h"

//#include "render/dxp_test.h"

