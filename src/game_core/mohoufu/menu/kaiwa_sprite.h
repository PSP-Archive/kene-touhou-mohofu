
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
---------------------------------------------------------*/

#ifndef _KAIWA_OBJ_00_H_
#define _KAIWA_OBJ_00_H_

/*(現在規格は、とりあえず仮のもの。後でOBJと統合する。)*/
typedef struct /* _kaiwa_obj_tag_ */
{
	POINT256	center; 	/* objの中心 x 座標, 精度確保用(256固定小数点形式) */
							/* objの中心 y 座標, 精度確保用(256固定小数点形式) */
	POINT256	target; 	/* 目標 x 座標 */
							/* 目標 y 座標 */
//[4==1*4]
	POINT256	origin; 	/* 原点 x 座標 */
							/* 原点 y 座標 */
	POINT256	offset; 	/* 原点からの差分 x 座標 */
							/* 原点からの差分 y 座標 */
//[8==2*4]
	POINT256	alt;		/* 以前の x 座標(補間移動用) */
							/* 以前の y 座標(補間移動用) */
	int width_2n;// 	2^n 単位での画像横幅。(256とか128とか)	int w_bit;	/* objの幅(1<<w_bit) */
	int height_2n;//	2^n 単位での画像高さ。(256とか128とか)	int h_bit;	/* objの高さ(1<<h_bit) */
//[12==3*4]
	int move_flag;		/* 0:停止中。 0以外(仮に 1):移動中。 */
	int draw_flag;		/* 0:描画しない。 0以外(仮に 1):描画する。 */
	u32 color32;		/* 半透明用 */
	int toutatu_wariai256;	/* (r36)立ち絵移動率t256形式。(0%...100% == 0...256)  */
//[16==4*4]
} KAIWA_OBJ;
/*
注意: width_2n は 2^n である事という制限以外に、Gu描画の制限で 64で割り切れる必要があります。
つまり、 64, 128, 256, 512 以外の値は出来ません。
*/

/*
-3 ==1 29
-2 ==0 30
-1 ==1 31
 0 ==0 32
 1 ==1
 2 ==0
 3 ==1
*/
enum
{
	KAIWA_OBJ_MOVE_FLAG_00_MOVE_COMPLETE = 0,
	KAIWA_OBJ_MOVE_FLAG_01_MOVE_START,
	KAIWA_OBJ_MOVE_FLAG_99_MAX/*(最大値)*/
};


enum
{
	KAIWA_OBJ_00_TACHIE_RIGHT = 0,	// プレイヤー / 会話 ボム絵共用。
	KAIWA_OBJ_01_TACHIE_LEFT_,		// ボス(1人目) / 会話 ボム絵共用。
	#if (1==USE_VS3)
	KAIWA_OBJ_02_TACHIE_LEFTB,		// ボス(2人目) / さしあたり会話 専用。
	KAIWA_OBJ_03_TACHIE_LEFTC,		// ボス(3人目) / さしあたり会話 専用。
	#endif
	KAIWA_OBJ_99_MAX/*(最大値)*/	//	(2/*32*/)	/*32*/ /*20*/
};

/*static*/extern KAIWA_OBJ kaiwa_sprite[KAIWA_OBJ_99_MAX];	/* 汎用スプライト */

extern void kaiwa_obj_set_256(void);/*(会話スプライトの設定。サイズを 256x256にする。)*/

	/* 立ち絵を描画する/しない。全ての立ち絵が対象。 */
extern void kaiwa_all_obj_draw_on_off(u32 on_off);


#endif /* _KAIWA_OBJ_00_H_ */
