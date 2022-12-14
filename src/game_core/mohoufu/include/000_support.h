
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	このファイルは直接インクルードしません。
	"game_main.h" からのみ間接的にインクルードします。
---------------------------------------------------------*/

#ifndef _SUPPORT_H_
#define _SUPPORT_H_

/*---------------------------------------------------------
	サポート設定(一番最初にインクルード)
	本システムを使う上での基本的なマクロ等のサポート関連
---------------------------------------------------------*/

	// PSPSDK(standard)

	#include <psptypes.h>
	#include <pspaudio.h>
	#include <pspctrl.h>
	#include <pspdisplay.h>
//	#include <pspgu.h>
//	#include <pspgum.h>/* gumはguより後にインクルード */
	#include <pspiofilemgr.h>
	#include <pspkernel.h>
	#include <psppower.h>
	#include <psprtc.h>

	// C(standard)

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <malloc.h>/*calloc*/

	// PSPSDK(debug)

//	#include "./../../debug/psp_debug.h"//#include <pspdebug.h>
//	#include "psp_debug.h"//#include <pspdebug.h>
#ifdef ENABLE_PROFILE
	#include <pspprof.h>
#endif

	// PSPSDK(optional)

//	#include <pspsdk.h>
//	#include <psputility.h>
//	#include <pspmoduleinfo.h>
//	#include <pspnet_apctl.h>
//	#include <pspnet_inet.h>
//	#include <pspnet_resolver.h>
//	#include <netinet/in.h>
//	#include "net_io.h"
//	#include <pspuser.h>

	// C(optional)

	#include <unistd.h>
	#include <stdarg.h>
	#include <dirent.h>
	#include <ctype.h>
	#include <math.h>/*sin(), at an2()*/
//	#include <signal.h>
//	#include <sys/stat.h>


#ifdef ENABLE_PSP
	//# /* カスタムライブラリを使う */
	#include "./../../PSPL/include/PSPL.h"//#include <SDL/SDL.h>//#include "SDL.h"
	#include "./../../PSPL/image/PSP_SDL_image.h"	//#include "SDL_image.h"
//	#include <SD L/SD L_mixer.h>//#include "SD L_mixer.h"
#else
	/* (r34)アンサポート */
	//# /* 標準ライブラリを使う */
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
//	#include <SDL/SDL_mixer.h>/*#include "SD L_mixer.h"*/
#endif

	//
	#ifndef offs_t
		#define offs_t unsigned int
	#endif

//	#ifndef TRUE
//		#define TRUE	(1)
//	#endif
//
//	#ifndef FALSE
//		#define FALSE	(0)
//	#endif

	#ifndef global
		/* static なのか global なのか 明示する。 */
		#define global /**/
	#endif

	#define my_TRUE 	(1)/**/
	#define my_FALSE	(0)/**/

	/* デバッグ中無効値、常に0. */
	#define TEST000 	(0)

#if (1)
/* RGBA5551:
	psp には RGBA5551 (GU_PSM_5551) モードがある。ここの A の1ビットは、言い換えればハードウェアーのcolor-key機能。
//
	しかし SDL では 5551 モードにしても A の 1 ビットは、無視されて使う事が出来ない。(つまり強制的にRGBA5550となる)
	(直接サーフェイスをいじった場合を除いて)「SDLのみ」(の描画を)使用している限りでは「ハードウェアーのcolor-key機能」は使用出来ない。
	 SDL では 5551 モードの場合、color-keyを別に設定し、「ソフトウェアーのcolor-key機能」を使用する。
//
	間違い//一方、PSPSDK では「ハードウェアーのcolor-key機能」が使える。PSPSDKではalpha-bitが使える。
	間違い//PSPSDK では「ソフトウェアーのcolor-key機能」というものは存在しない為、逆に言えば、
	間違い//必ずここでcolor-keyを設定しなければならない。(PSPSDKではalpha-bit==抜き色==color-key)
//
	間違い//つまり、PSPSDK では RGBA8888(GU_PSM_8888) や RGBA5551(GU_PSM_5551) モードではcolor-key機能があるが、
	間違い//RGBA5650(GU_PSM_5650) モードではcolor-key機能が無い｡
	間違い// (ハードウェアー/ソフトウェアーに関わらず、透明度は設定できるがcolor-key(抜き色)を実現させる方法がない)

	PSPSDK では sceGuBlendFunc(); で color-key が設定できるみたい。

void sceGuBlendFunc(int op, int src, int dest, u32 srcfix, u32 destfix);

備考:
ブレンド関数を設定します。DirectXで謂うところの「ブレンドファクター」に該当します。
描画先に既に存在する色と書き込む予定の色を比較、演算して実際に書き込む色を決定します。

opに設定できる定数は以下の通り

GU_ADD
GU_SUBTRACT
GU_REVERSE_SUBTRACT
GU_MIN
GU_MAX
GU_ABS
srcとdestに設定できる定数は以下の通り

GU_SRC_COLOR
GU_ONE_MINUS_SRC_COLOR
GU_SRC_ALPHA
GU_ONE_MINUS_SRC_ALPHA
GU_DST_ALPHA
GU_ONE_MINUS_DST_ALPHA
GU_DST_COLOR
GU_ONE_MINUS_DST_COLOR
GU_FIX
srcfixとdestfixに設定する値はそれぞれsrcとdestにGU_FIXが使われる場合のみ適用されます。
R8G8B8A8フォーマットで色を設定する事になりますが、PSPはリトルエンディアンのCPUを使っていることに注意してください。


*/
	/* 16bit(15bit) RGBA5551 */
	/*
	15: abbb bbgg gggr rrrr
	15: -bbb b-gg gg-r rrr- (pspのSDLではaが使えない？ので)
	*/
	#define MAKECOL15A(r, g, b, a)	(((b & 0xf8) << 7) | ((g & 0xf8) << 2) | ((r & 0xf8) >> 3) | ((a & 0x80)<<8))
	#define MAKECOL15(r, g, b)		(((b & 0xf8) << 7) | ((g & 0xf8) << 2) | ((r & 0xf8) >> 3))
	#define GETR15F(col)			(((col << 3) & 0xf8) /*| ((col >>  2) & 0x07)*/)
	#define GETG15F(col)			(((col >> 2) & 0xf8) /*| ((col >>  7) & 0x07)*/)
	#define GETB15F(col)			(((col >> 7) & 0xf8) /*| ((col >> 12) & 0x07)*/)
	#define GETR15(col) 			(((col << 3) & 0xf8) | ((col >>  2) & 0x07))
	#define GETG15(col) 			(((col >> 2) & 0xf8) | ((col >>  7) & 0x07))
	#define GETB15(col) 			(((col >> 7) & 0xf8) | ((col >> 12) & 0x07))
#endif

#if (1)
	/* 16bit RGBA5650 */
	/*
	16: bbbb bggg gggr rrrr
	16: bbbb -ggg gg-r rrr-
	*/
	#define MAKECOL16A(r, g, b, a)	(((b & 0xf8) << 8) | ((g & 0xfc) << 3) | ((r & 0xf8) >> 3))
	#define MAKECOL16(r, g, b)		(((b & 0xf8) << 8) | ((g & 0xfc) << 3) | ((r & 0xf8) >> 3))
	#define GETR16F(col)			(((col << 3) & 0xf8) /*| ((col >>  2) & 0x07)*/)
	#define GETG16F(col)			(((col >> 3) & 0xfc) /*| ((col >>  8) & 0x03)*/)
	#define GETB16F(col)			(((col >> 8) & 0xf8) /*| ((col >> 13) & 0x07)*/)
	#define GETR16(col) 			(((col << 3) & 0xf8) | ((col >>  2) & 0x07))
	#define GETG16(col) 			(((col >> 3) & 0xf8) | ((col >>  8) & 0x07))
	#define GETB16(col) 			(((col >> 8) & 0xf8) | ((col >> 13) & 0x07))
#endif

#if (1)
	/* 32bit RGBA8888 */
	#define MAKE32RGBA(r, g, b, a)	(((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff))
	#define GETR32(col) 			(((col		) & 0xff) )
	#define GETG32(col) 			(((col >>  8) & 0xff) )
	#define GETB32(col) 			(((col >> 16) & 0xff) )
	#define GETA32(col) 			(((col >> 24) & 0xff) )
#endif

/* PSPの表示画面領域 */
#ifndef PSP_BUFFER_WIDTH512
	#define PSP_BUFFER_WIDTH512 	(512)
#endif
#ifndef PSP_WIDTH480
	#define PSP_WIDTH480			(480)
#endif
#ifndef PSP_HEIGHT272
	#define PSP_HEIGHT272			(272)
#endif
#if 0/*(メモ)*/
■ pspの場合、縦は論外で足りない。
ただでさえ縦が足り無くて困ってるのに
縦の上下に枠を付けるとかありえない。
あまりに縦が無い為に、自機が上下に喰み出せるのは仕様とする。
(というか上下に喰み出しちゃダメなら作らないレベルで縦が足りない)

■ pspの場合、横はあまりに広すぎる。
(r39時点でwindowsシリーズと比較して2倍ぐらい。
旧作と比較しても1.5倍ある(旧作はアスペクト比が1:1ではないので注意))

windowsシリーズで640x480ドット(ドット＝＝ピクセル)の画面を描いたとする。
この時横の長さが64cm。の縦長さが48cm。だったとする。
(32インチぐらいの画面かな?)
その場合640[mm]x480[mm]なので1ドットの大きさは。もとい1ピクセルの大きさは、
縦が1[mm]x横が1[mm]の正方形。

今度は同じディスプレイに pc-98x1を繋ぐ。windowsシリーズで480x400ドット描いたのと同じ面積に
pc-98x1では 640x400ピクセルが映る。この時横の長さが64cm。の縦長さが48cm。
縦長さがもし40cmだったならwindowsシリーズと同じだけど、横の長さは48cm。
もとい1ピクセルの大きさは、縦が1.2[mm]x横が1[mm]の縦に長い長方形。エミュでは再現できない。
--------------------
□ windowsの場合。384x448[pixel]。アスペクト比はpspと同じ1:1なので単純に縮小すると、
384x448 == 233x272
384 == 233 x (1.64806866952789699570815450643777...)
448 == 272 x (1.64806866952789699570815450643777...)
pspで横が233[pixel]。でもpspのアスペクト比は1:1じゃなくて数パーセントずれてる。
なんかpspは横に長い。実際は224[pixel]とか。(ちゃんと逆算しないと正確な値が出ない)
233 == 1.37339055793991416309012875536481 倍 (320/233) (アスペクト比が1:1ならここだけど実際に測定すると違う)
224 == 1.42857142857142857142857142857143 倍 (320/224)
設計上はpspはアスペクト比が約1:1のつもりなんだろうけど、実際に測定してみるとpspは全然1:1じゃない。
 windowsの場合の縮小イメージとして考えた場合なら、
r39時点で現実には横は1.4倍ぐらい(1.4倍以上)広くなってる。

448/384＝＝1.16666666666666666666666666666667倍
--------------------
□ 旧作の場合。
旧作の場合なにより注意しなければならないのがアスペクト比は約4:3な事。
windowsは約4:4(==1:1)。縦が1.2倍長いので縦のドット数を1.2倍しないとならない。(480==400x1.2)
旧作の場合。384x368[pixel]。アスペクト比が1:1に換算するとゲーム画面は384x441.6[pixel]である。
windowsの場合に換算して384x441.6[pixel]の面積を描くと言う事。旧作の画面は6.4[pixel]狭いだけなので
恐らく同面積かも知れない。(ディスプレイの調整次第でアスペクト比が4:3にならない事。)
windowsの場合に換算して
縦の長さが 98.5714285714285714285714285714286% (==98.5%) これは殆ど同じと言う事を意味する。

441.6/384＝＝1.15倍
--------------------

pspのアスペクト比は1:1に近いけど、前測定したら正確に1:1じゃなかった。
(これはpspの画面は正確に16:9では無いと言う事で地デジを圧縮したのと微妙に縦横比が違う。(大体同じだけど))
(1:1なら272x272ドットを画面に描いてものさしで測ると、縦と横の物理的長さが同じになる。
pspでは縦と横の長さが少し違う。)
slice32 					 128なのは描画の関係で32で割り切れる数の方が速い。
+---+------------------------+-----------+
|32 |  ---	320[pixel] ---	 | -- 128 -- | == 480[pixel]
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
|	|						 |			 |
+---+------------------------+-----------+
(0) (32)					 (480-128)	 (480)

#endif
/* シューティングGAME部分の表示画面領域 */
//#define GAME_WIDTH			(320)/*(352)*/ /*(380)*/
#define PANEL_WIDTH 			(128)
#define GAME_X_OFFSET			(32)
#define GAME_320_WIDTH			(PSP_WIDTH480-PANEL_WIDTH-GAME_X_OFFSET)
#define GAME_WIDTH				(GAME_320_WIDTH+GAME_X_OFFSET)
#define GAME_HEIGHT 			(PSP_HEIGHT272)
//	GAME_X_OFFSET 対応。

/* x位置が480の場合(==481ドット目) Scissorが働くので必ず表示しない */
#define GAME_NOT_VISIBLE480 	(PSP_WIDTH480)

#if (1)
	/* ソフトウェアーで Zソート */
	#define USE_ZBUFFER 	(0)
#else
	/* ハードウェアーでソート */
	#define USE_ZBUFFER 	(1)
#endif


/* C:/cygwin/pspdev/psp/include/math.h で宣言されているので要らない */
//#ifndef M_PI
//	#define M_PI			(3.14159265358979323846)
//#endif

#ifndef T_GU_M_PI
	#define T_GU_M_PI		GU_PI
#endif

//#if 0
/* CWの場合 */
	/* １周が360度の単位系(deg360)を１周が２πの単位系(radian)へ変換。及び逆変換。 */
	#define deg360_2rad(x)		(((T_GU_M_PI*2)/(360.0))*(x))
	#define rad2deg360(x)		( (int)((x)*((360.0)/(T_GU_M_PI*2))+360)%360 )

	/* １周が512度の単位系(deg512)を１周が２πの単位系(radian)へ変換。及び逆変換。 */
//	#define deg512_2rad(x)		(((T_GU_M_PI*2)/(512.0))*(x))
	//#define rad2deg512(x) 	( (int)((x)*((512.0)/(T_GU_M_PI*2))+512)%512 )
	//#define rad2deg512(x) 	( (int)((x)*((512.0)/(T_GU_M_PI*2))+512)&(512-1) )
//	#define rad2deg512(x)		( (int)((x)*((512.0)/(T_GU_M_PI*2))/*+512*/)&(512-1) )

	/* １周が1024度の単位系(deg1024)を１周が２πの単位系(radian)へ変換。及び逆変換。 */
	#define deg1024_2rad(x) 	(((T_GU_M_PI*2)/(1024.0))*(x))
	//#define rad2deg1024(x)	( (int)((x)*((1024.0)/(T_GU_M_PI*2))+1024)%1024 )
	//#define rad2deg1024(x)	( (int)((x)*((1024.0)/(T_GU_M_PI*2))+1024)&(1024-1) )
	#define rad2deg1024(x)		( (int)((x)*((1024.0)/(T_GU_M_PI*2))/*+1024*/)&(1024-1) )

	/* １周が4096度の単位系(deg4096)を１周が２πの単位系(radian)へ変換。及び逆変換。 */
//	#define deg4096_2rad(x) 	(((T_GU_M_PI*2)/(4096.0))*(x))
	//#define rad2deg4096(x)	( (int)((x)*((4096.0)/(T_GU_M_PI*2))+4096)%4096 )
	//#define rad2deg4096(x)	( (int)((x)*((4096.0)/(T_GU_M_PI*2))+4096)&(4096-1) )
//	#define rad2deg4096(x)		( (int)((x)*((4096.0)/(T_GU_M_PI*2))/*+4096*/)&(4096-1) )

	/* １周が65536度の単位系(deg65536)を１周が２πの単位系(radian)へ変換。及び逆変換。 */
	#define deg65536_2rad(x)	(((T_GU_M_PI*2)/(65536.0))*(x))
	//#define rad2deg65536(x)	( (int)((x)*((65536.0)/(T_GU_M_PI*2))+65536)%65536 )
	//#define rad2deg65536(x)	( (int)((x)*((65536.0)/(T_GU_M_PI*2))+65536)&(65536-1) )
	#define rad2deg65536(x) 	( (int)((x)*((65536.0)/(T_GU_M_PI*2))/*+65536*/)&(65536-1) )

	/* １周が360度の単位系(deg360)を１周が512度の単位系(deg512)へ変換。及び逆変換。 */
//	#define deg_360_to_512(x)	((int)((x)*(512.0/360.0)))
//	#define deg_512_to_360(x)	((int)((x)*(360.0/512.0)))

	/* １周が360度の単位系(deg360)を１周が1024度の単位系(deg1024)へ変換。及び逆変換。 */
	#define deg_360_to_1024(x)	((int)((x)*(1024.0/360.0)))
	#define deg_1024_to_360(x)	((int)((x)*(360.0/1024.0)))

	/* １周が360度の単位系(deg360)を１周が4096度の単位系(deg4096)へ変換。及び逆変換。 */
	#define deg_360_to_4096(x)	((int)((x)*(4096.0/360.0)))
	#define deg_4096_to_360(x)	((int)((x)*(360.0/4096.0)))

	/* １周が360度の単位系(deg360)を１周が65536度の単位系(deg65536)へ変換。及び逆変換。 */
	#define deg360_to_65536(x)	((int)((x)*(65536.0/360.0)))
	#define deg65536_to_360(x)	((int)((x)*(360.0/65536.0)))

	/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
	/* １周が65536度の単位系(deg65536)を１周が1024度の単位の単位系(deg1024)へ変換。及び逆変換。 */
	/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
	#define deg65536to1024(x)	((x)>>6)
	/* 「1周が1024分割」から「1周が65536分割」へ変換する。 */
	#define deg1024to65536(x)	((x)<<6)

//#else
/* CCWの場合 */

	/* １周が360度の単位系(deg360)を１周が512度の単位系(deg512)へ変換。 */
//	#define cv512r(x)		((int)((x)*(512.0/360.0)))
	/* １周が360度の単位系(deg360)を１周が1024度の単位系(deg1024)へ変換。 */
	#define cv1024r(x)		((int)((x)*(1024.0/360.0)))
	/* １周が360度の単位系(deg360)を１周が65536度の単位系(deg1024)へ変換。 */
	#define cv65536r(x)		((int)((x)*(65536.0/360.0)))
//#endif

/* １周 の範囲内にクリッピング */
#define mask256(aaa)		{aaa &= (256-1);}/* pspでは u8 にキャストするのとコードは大抵同じになる。 */
//#define mask512(aaa)		{aaa &= (512-1);}/*模倣風でr31現在、無い筈*/
#define mask1024(aaa)		{aaa &= (1024-1);}/*標準精度弾*/
//#define mask4096(aaa) 	{aaa &= (4096-1);}/*模倣風でr31現在、無い筈*/
#define mask65536(aaa)		{aaa &= (65536-1);}/*精密弾*/	/* 註:※１ */

/*	1/n周 の範囲内にクリッピング。
	(正確には 1/(2^bbb)周 の範囲内にクリッピング。)
	(bbb=1の場合1/2周, bbb=2の場合1/4周)
*/
#define mask_harf65536(aaa, bbb)	{aaa = ((aaa+((65536>>(bbb+1))))&((65536>>(bbb))-1))-((65536>>(bbb+1)));}/*精密弾*/


/*
	註:※１こう書いておくとpspでは、GCC(4.xx以降なら)が and演算などしない。
	単純にショートにするだけ。
	2byte になってるだけだから、pspでは速い筈。
*/

/* 数字をスコアに変換。及び逆変換。 */
#define score(x)	((u32)(((u32)(x))/10))
#define score_r(x)	((u32)(((u32)(x))*10))

/*---------------------------------------------------------
	256固定小数点: 模倣風で主に使用する形式。
	-------------------------------------------------------
	64固定小数点: 4.00未満の値を扱う場合、この形式なら 32bit で 4難易度パック可能。
	-------------------------------------------------------
	8固定小数点: (r41現在) さあいあたり、使ってない。
---------------------------------------------------------*/

/* 数字を256固定小数点形式に変換。及びdou bleへ逆変換。 */
#define t256(x) 				((int)((x)*256))
//#define t256_to_dou ble(x)	(((dou ble)(x))*(1.0/256.0))
#define t256_floor(x)			((x)>>(8))

/* 数字を64固定小数点形式に変換。及びdou bleへ逆変換。 */
#define t64(x)				((int)((x)*64))
//#define t64_to_dou ble(x) (((dou ble)(x))*(1.0/64.0))
#define t64_floor(x)			((x)>>(6))

/* 数字を8固定小数点形式に変換。及びdou bleへ逆変換。 */
//#define t8(x)					((short)((x)*8))
//#define t8_to_dou ble(x)		(((dou ble)(x))*(1.0/8.0))
//#define t8_floor(x) 			((x)>>(3))

/* 秒単位の時間で */
#define byou60(x)	((int)(x*60))
/* 約秒単位の時間で */
#define byou64(x)	((int)(x*64))


/*---------------------------------------------------------
	難易度変数
	-------------------------------------------------------
	32bitで4つの難易度を一度で扱います。
---------------------------------------------------------*/

#define PACK_NAN_IDO_CONST(easy_value, normal_value, hard_value, lunatic_value) (const u32)((easy_value&0xff)|((normal_value&0xff)<<8)|((hard_value&0xff)<<16)|((lunatic_value&0xff)<<24))
//#define DIRECT_NAN_IDO_DECODE(easy_value, normal_value, hard_value, lunatic_value) ((PACK_NAN_IDO_CONST(easy_value, normal_value, hard_value, lunatic_value) >> (cg_VR20_game_difficulty<<3)) & 0xff)

/* ラジアン撲滅対策。pspは dou bleの値を保持するだけでも遅い。(例えば関数の引数とか)
intで値を保持して、使う度に変換、逆変換した方が、ずっと速い。
そこでラジアン撲滅する為のマクロ */
#if 0
	/* １周が512度の単位系の at an2(y, x), cos(x), sin(x) */
	#define at an_512(y, x) (rad2deg512(at an2((y), (x))))
	#define co_s512(x)		(cos(deg512_2rad((x))))
	#define si_n512(x)		(sin(deg512_2rad((x))))
	/* 変な名前になってるのは cos( とか sin( で検索するため */
#else
//	#define SINTABLE_SIZE512	512
//	#define SINTABLE_MASK512	(SINTABLE_SIZE512-1)
//	#define SINTABLE_SIZE1024	1024
//	#define SINTABLE_MASK1024	(SINTABLE_SIZE1024-1)
//	#define SINTABLE_SIZE65536	65536
//	#define SINTABLE_MASK65536	(SINTABLE_SIZE65536-1)

//	#define OFFS_SIN512 		(0)
//	#define OFFS_COS512 		((SINTABLE_SIZE512/4)-1)/*127 90*/
//	#define OFFS_SIN1024		(0)
//	#define OFFS_COS1024		((SINTABLE_SIZE1024/4)-1)/*255 90*/
//	#define OFFS_SIN65536		(0)
//	#define OFFS_COS65536		((SINTABLE_SIZE65536/4)-1)/*255 90*/
//	extern int at an_512(int y, int x);
//	extern int at an_1024(int y, int x);
//	extern int at an_65536(int y, int x);
	#if 1
		#include "psp_vfpu.h"
	//	#define cos512(x)		((int)(int256_si n1024((((x+x)+OFFS_COS512+OFFS_COS512)&(1024-1)))))
	//	#define sin512(x)		((int)(int256_si n1024((((x+x)						 )&(1024-1)))))
	//	#define co s1024(x) 	((int)(int256_si n1024((((x)+OFFS_COS1024)&(1024-1)))))
	//	#define si n1024(x) 	((int)(int256_si n1024((((x)			)&(1024-1)))))
//		#define cos65536(x) 	((int)(int256_si n1024((((x)+OFFS_COS65536)&(65536-1))>>6)))
//		#define sin65536(x) 	((int)(int256_si n1024((((x)			 )&(65536-1))>>6)))
	//	#define cos65536(x) 	((int)(int256_si n1024((((x)+OFFS_COS65536)&(65536-1))>>6)))
	//	#define sin65536(x) 	((int)(int256_si n1024((((x)			 )&(65536-1))>>6)))
	//	#define cos65536(x) 	((int)(int256_sin65536((((x)+OFFS_COS65536)&(65536-1)) )))
	//	#define sin65536(x) 	((int)(int256_sin65536((((x)			 )&(65536-1)) )))
	#endif
#endif

/* rand()撲滅対策。本家にはリプレイ機能がある。
リプレイ機能を再現する為には内蔵の組み込み関数rand()は使えない。
周期の長い自前の擬似乱数の関数を用意する必要がある。
リプレイ開始時やゲーム開始時(面の始め)に乱数系列の初期化をする。 */
/* 変な名前になってるのは rand( で検索するため */
#if 0
	#define ra_nd(x)		(rand(x))
#else
	extern int ra_nd(void);
#endif


/*
	min, max は psp_min, psp_max にした。
	理由は２つある。
	--------------
1.	C++リンクする場合(しないけど)
	std::min
	std::max
	あたりで苦労するので、
	min, max は psp_min, psp_max にした。
	そもそも模倣風は Cコンパイラの方で、 C++コンパイラ 使ってないけど。
	--------------
2.	psp_min, psp_max の場合、引数は必ず signed int なので、
	それを明示しておく必要もある。
	--------------
	まあ模倣風エンジンPCに流用可能だし。する人居ないと思うけど。
*/

/* psp専用の命令(pspのcpuにしか無いアセンブラ命令)を活用する。(組み込み関数) */
//#ifdef psp_min
//	!print_error("include fileの順序がおかしいです。")
//#endif
//#ifdef psp_max
//	!print_error("include fileの順序がおかしいです。")
//#endif
/* 無いと思うけど念の為消去 */
//#undef min
//#undef max
//
#ifndef psp_max
	#define psp_min __builtin_allegrex_min
	#define psp_max __builtin_allegrex_max
#endif/*(psp_max)*/
//
#ifndef JAPAN
	#if defined(USE_LANGUAGE_ENGLISH)
		#define JAPAN(for_japanese, for_english)	for_english
	#else
		#define JAPAN(for_japanese, for_english)	for_japanese
	#endif
#endif/*(JAPAN)*/
//

#if (1)/*(アセンブラ関連)*/
extern int tiny_strcmp(char *aaa, const char *bbb);/* MIPS R4000系にあわせて、最適化してみました。 */
/*
	転送データーが多い時専用です。
	転送データーが少ない(256bytes以下とか)の場合、低速化します。
	(64bytes単位で転送しています。)
*/
extern void memset32(int *dest, int c, int count);
extern void memset32_uncached(int *dest, int c, int count);
extern void memcpy32(int *dest, int *src, int count); // 32bit word count
#endif/*(てすと)*/



#endif /* _SUPPORT_H_ */
