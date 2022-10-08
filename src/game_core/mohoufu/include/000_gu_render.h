
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	このファイルは直接インクルードしません。
	"game_main.h" からのみ間接的にインクルードします。
---------------------------------------------------------*/

#ifndef _PSP_GU_RENDER_H_
#define _PSP_GU_RENDER_H_

enum
{
	GU_HAIKEI_00_2D_256 = 0,	/* 256x256テクスチャを敷き詰める2D。 */
	GU_HAIKEI_01_3D_TEST01, 	/* 3Dのテスト */
	GU_HAIKEI_02_EIENTEI,		/* "永遠亭"の予定。 */
	GU_HAIKEI_03_FAKE_3D,		/* テクスチャ変形による擬似3D 将来的に無くなる予定。 */
	GU_HAIKEI_99_MAX,
};

/*---------------------------------------------------------
	背景ヘルパー
---------------------------------------------------------*/

/* 背景を消す色を 32bit colorで指定する。 */
extern void gu_set_bg_u32_clear_color(u32 set_u32_clear_color);

/*---------------------------------------------------------
about...
	draw screen:	480x272 SDL surface. this screen can drawing.(for drawing virtual screen)
	temp screen:	480x272 SDL surface. this screen not drawing.(temporary virtual screen)
	-------------------------------------------------------
	draw screen:(描画仮想画面)
		this screen can drawing. or not drawing, used programmable switch.
		this screen do not directly loading files.
		(この画面は描画用です。画像の読み込みはしません。
		SDLの表示画面 と似ていますが、違いは SDLの表示画面 は表示を消せないのですが、
		この画面は プログラムで表示を on/off できます。)
	temp screen:(退避仮想画面)
		this screen can not drawing.
		this screen can loading files.(gazo.png, gazo.jpg, ... ) and
		psp_move_screen(MODE_01_POP);// image copy, temp screen to draw screen.
		when drawing.
		(この画面は退避用です。画像の読み込みプログラムは、この画面用にしか要りません。
		画像を読み込んだら、
		psp_move_screen(MODE_01_POP);
		で、描画仮想画面に内容をコピーする事で画像を表示できます。)
	-------------------------------------------------------
---------------------------------------------------------*/
enum
{
	MODE_00_PUSH = 0,/*[saved draw screen to temp screen.](仮想スクリーンを退避)*/
	MODE_01_POP,/*([loaded temp screen to draw screen]仮想スクリーンを復活)*/
};
extern void psp_move_screen(int set_mode);

/*---------------------------------------------------------
	背景の描画プログラムを登録する。
	背景カード
---------------------------------------------------------*/

/* カード時に背景のプログラム種類を設定 */

/*---------------------------------------------------------
	メニューシステム
---------------------------------------------------------*/

extern void psp_pause_filter(void);/*[draw flitering, only draw screen.](描画仮想スクリーンにもやもやエフェクトをかける)*/
extern void psp_clear_screen(void);/*[image clear, only draw screen.](描画仮想スクリーンを黒で消す)*/

#endif /* _PSP_GU_RENDER_H_ */
