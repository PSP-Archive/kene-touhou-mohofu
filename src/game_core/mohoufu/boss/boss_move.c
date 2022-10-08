
#include "boss.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ボスの行動を定義する。
	-------------------------------------------------------
	現在ボス行動は、C言語のプログラムになっているけど、
	ここの行動はコマンド化して、弾幕スクリプトで行動できるようにしたい。
	-------------------------------------------------------
	弾幕スクリプトには弾の移動コマンド系以外に、
	ボス行動コマンド系を盛り込む。
	-------------------------------------------------------
	(r41-)ここの処理はすべて spell_move_system (r41-新規作成予定) へ移行します。
	「spell_move_system」と書いてあるものは移行中の処置です。
	-------------------------------------------------------
	(-r40)の仕組み。
	root -> move -> boss_move_33_keitai -> boss_move_00_card_settei_seisei(src) -> スペカ(スクリプト)
	だったのを
	(r41-)の仕組み(予定)。
	root -> move -> boss_move_00_card_settei_seisei(src) -> スペカ(スクリプト) -> boss_move_33_keitai
	こういう風に接続を換えて、スペカ(スクリプト)から、ボス移動がコントロール出来るように変更する予定です。
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[ボス共通カード移動]。
---------------------------------------------------------*/

/*---------------------------------------------------------
	xランダム32[pixel]以内差分移動。
	yランダム 8[pixel]以内差分移動。
---------------------------------------------------------*/

static void boss_set_position_differential32_void(void)
{
	#if 1
	/* 現在位置より左右 32[pixel] の範囲でランダム移動。但し最低16[pixel]は動く。 */
	const u16 ra_nd16	= ra_nd();
	VR06	= cg_BOSS_DATA_3a_center_x256;
	{	const u16 vector_value = ((ra_nd16&(((32)*256)-1))|(16*256));/* 移動量を決める。 但し最低16[pixel]は動く */
	//	if (ra_nd16&0x2000) /* 移動方向を決める */ /* 0x1fff == ((32)*256-1) */
	//	if (VR06 < (ra_nd16+ra_nd16)) /* 移動方向を決める */
		if (VR06 < (ra_nd16+((GAME_X_OFFSET+(GAME_320_WIDTH/2)-128)<<8))) /* 移動方向を決める */
				{VR06 += (vector_value);}
		else	{VR06 -= (vector_value);}
	}
	/* 現在位置より上下 8[pixel] の範囲でランダム移動 */
	VR07 = cg_BOSS_DATA_3b_center_y256;
	VR07 += ((((ra_nd16))&((8+8)-1))<<8);
	VR07 -= (t256(8));
	#endif
}
#if 0
/*---------------------------------------------------------
	xランダム64[pixel]以内差分移動。
	yランダム 8[pixel]以内差分移動。
---------------------------------------------------------*/

static void boss_set_position_differential64_void(void)
{
	#if 1
	/* 現在位置より左右 64[pixel] の範囲でランダム移動。但し最低16[pixel]は動く。 */
	const u16 ra_nd16	= ra_nd();
	VR06	= cg_BOSS_DATA_3a_center_x256;
	{	const u16 vector_value = ((ra_nd16&(((64)*256)-1))|(16*256));/* 移動量を決める。 但し最低16[pixel]は動く */
	//	if (ra_nd16&0x2000) /* 移動方向を決める */ /* 0x1fff == ((32)*256-1) */
	//	if (VR06 < (ra_nd16+ra_nd16)) /* 移動方向を決める */
		if (VR06 < (ra_nd16+((GAME_X_OFFSET+(GAME_320_WIDTH/2)-128)<<8))) /* 移動方向を決める */
				{VR06 += (vector_value);}
		else	{VR06 -= (vector_value);}
	}
	/* 現在位置より上下 8[pixel] の範囲でランダム移動 */
	VR07 = cg_BOSS_DATA_3b_center_y256;
	VR07 += ((((ra_nd16))&((8+8)-1))<<8);
	VR07 -= (t256(8));
	#endif
}
#endif
/*---------------------------------------------------------
	カード生成の間隔と移動時間の間隔が同期。
	xyランダム差分移動。
---------------------------------------------------------*/

//tern/*static*/ void spell_boss_move_system_05_xy_douki_differential64(void)
extern/*static*/ void spell_boss_move_system_04_xy_douki_differential32(void)
{
	/* カードを撃ってない場合に追加 */
	if (SPELL_00==card.spell_used_number)	/* カード生成終了なら、新移動先を決める。 */
	{
	//	boss_set_position_differential64_void();
		boss_set_position_differential32_void();
		#if (1)
		/* 移動座標を決める */	/* 攻撃アニメーション */
		boss_set_new_position_void();/*(誘導移動座標を設定)*/
		#endif
	}
}

/*---------------------------------------------------------
	カード生成の間隔と移動時間の間隔が同期。
	xランダム移動。
	y移動しない。
---------------------------------------------------------*/

extern void spell_boss_move_system_03_x_douki(void)
{
	/* カードを撃ってない場合に追加 */
	if (SPELL_00==card.spell_used_number)	/* カード生成終了なら、新移動先を決める。 */
	{
		#if 1
		const u16 ra_nd16	= ra_nd();
		VR06	= ((ra_nd16/*&((256*256)-1)*/));	/* 0(?) =:= t256(((480-128-256)/2)-50)) */
		VR07	= (cg_BOSS_DATA_3b_center_y256);/*(t256()形式)*/
		#endif
		#if (1)
		/* 移動座標を決める */	/* 攻撃アニメーション */
		boss_set_new_position_void();/*(誘導移動座標を設定)*/
		#endif
	}
}

/*---------------------------------------------------------
	カード生成の間隔と移動時間の間隔が非同期。
	xランダム移動。
	yランダム移動。
---------------------------------------------------------*/

extern void spell_boss_move_system_02_xy_hidouki(void)
{
	/* カード生成の間隔と移動時間の間隔が非同期。 */
	cg_BOSS_DATA_35_move_jyumyou--;/*fps_factor*/
	if (cg_BOSS_DATA_35_move_jyumyou <= 0)
	{
		cg_BOSS_DATA_35_move_jyumyou	= (300);	/* 移動時間、間隔 */
		#if 1
		int rand32 = ((ra_nd()));
		/* 移動座標を決める */
		VR06 = ((rand32&0xff00)+(((rand32<<8)&0x3f00)));	/* (256+64) == 320 == (480-128-32) */
		VR07 = (((rand32>>8)&0x3f00));	/* (64) */
		#endif
		#if (1)
		/* 移動座標を決める */	/* 攻撃アニメーション */
		boss_set_new_position_void();/*(誘導移動座標を設定)*/
		#endif
	}
}

/* 出現時x座標 */
//#define BOSS_XP256		(t256(GAME_WIDTH/2))	/* 中心座標なので */
#define BOSS_XP256			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH/2))	/* 中心座標なので */

/*---------------------------------------------------------
	固定退避位置へ移動後、動かないでカードを撃つ。
	-------------------------------------------------------
	固定退避位置は上部、X軸は中心。とりあえず。
---------------------------------------------------------*/
extern void spell_boss_move_system_01_taihi_ue_naka(void)
{
	#if (1)
	/* 移動座標を決める */	/* 攻撃アニメーション */
//	VR06	= (cg_BOSS_DATA_30_target_x256);/*(t256()形式)*/
//	VR07	= (cg_BOSS_DATA_31_target_y256);/*(t256()形式)*/
	VR06	= (BOSS_XP256);/*(t256()形式)*/
	VR07	= (t256(16.0));/*(t256()形式)*/
	boss_set_new_position_void();/*(誘導移動座標を設定)*/
	#endif
}

#if 1
/*---------------------------------------------------------
	第11形態: 最終形態(その3)
---------------------------------------------------------*/

extern void spell_boss_move_system_17_sakuya_bimyou_idou(void)
{
	u32 iii;
	iii = ra_nd();
	if (0==(iii&0x07))
	{
	//	src->math_vector.x256 = (((signed int)((iii>> 8)&0xff))-127);
	//	src->math_vector.y256 = (((signed int)((iii>>16)&0xff))-127);
		cg_BOSS_DATA_3a_center_x256 += (((signed int)((iii>> 8)&0xff))-127);
		cg_BOSS_DATA_3b_center_y256 += (((signed int)((iii>>16)&0xff))-127);
	}
}
#endif


/*---------------------------------------------------------
	-------------------------------------------------------
---------------------------------------------------------*/
extern void set_tukaima_start(void);/*(使い魔システム)*/
static void spell_move_system_boss_move_tukaima_keitai_void(void)
{
	static int tukaima_tuika_timer = 0; /* 使い魔、追加タイマー。追加間隔をあまり短くしない。 */
	tukaima_tuika_timer--;
	if (0 > tukaima_tuika_timer)
	{
		tukaima_tuika_timer = (1024);
		cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0e_mima_T0e;
		set_tukaima_start();/*(使い魔システム)*/
	}
}
/*---------------------------------------------------------
	-------------------------------------------------------
---------------------------------------------------------*/

extern void spell_boss_move_system_10_mima_keitai(void)
{
	spell_move_system_boss_move_tukaima_keitai_void();
	spell_boss_move_system_02_xy_hidouki();
}

/*---------------------------------------------------------
---------------------------------------------------------*/


/*---------------------------------------------------------
	[ボス共通カード行動]。
---------------------------------------------------------*/


/*---------------------------------------------------------
	ボス移動処理の共通ルーチン
	-------------------------------------------------------
★ 移動範囲の登録、機能：
	あらかじめボス移動範囲を登録しておく。
★ 範囲内ならば移動、機能：
	移動範囲内ならば、ボスが移動する。
	移動範囲外ならば、ボスは移動しない。
★ 移動判定、機能：
	ボスが移動しない場合は、「移動できなかったフラグ」がＯＮになる。
---------------------------------------------------------*/

/*---------------------------------------------------------
	ボス誘導比率計算。
---------------------------------------------------------*/
//	/**/extern int boss_hamidasi;		/* 「移動できなかったフラグ」(使用前に手動でOFF==0にしとく) */

static OBJ_CALL_FUNC(boss_move_vx_vy_animation)
{
	cg_BOSS_DATA_3a_center_x256 += (src->math_vector.x256);
	cg_BOSS_DATA_3b_center_y256 += (src->math_vector.y256);
	#define USE_BOSS_HAMIDASI_CHECK (0)
	#if (1==USE_BOSS_HAMIDASI_CHECK)
		 if (cg_BOSS_DATA_3a_center_x256 < VR3c_boss_clip_min_x256)	{cg_BOSS_DATA_3a_center_x256 = VR3c_boss_clip_min_x256;	card.boss_hamidasi = (1);	}
	else if (cg_BOSS_DATA_3a_center_x256 > VR3e_boss_clip_max_x256)	{cg_BOSS_DATA_3a_center_x256 = VR3e_boss_clip_max_x256;	card.boss_hamidasi = (1);	}
//
		 if (cg_BOSS_DATA_3b_center_y256 < VR3d_boss_clip_min_y256)	{cg_BOSS_DATA_3b_center_y256 = VR3d_boss_clip_min_y256;	card.boss_hamidasi = (1);	}
	else if (cg_BOSS_DATA_3b_center_y256 > VR3f_boss_clip_max_y256)	{cg_BOSS_DATA_3b_center_y256 = VR3f_boss_clip_max_y256;	card.boss_hamidasi = (1);	}
	#else
	/*(とりあえず)*/
	cg_BOSS_DATA_3a_center_x256 = psp_min(cg_BOSS_DATA_3a_center_x256, VR3e_boss_clip_max_x256);/* 右チェック(喰み出す) */
	cg_BOSS_DATA_3a_center_x256 = psp_max(cg_BOSS_DATA_3a_center_x256, VR3c_boss_clip_min_x256);/* 左チェック(喰み出す) */
	cg_BOSS_DATA_3b_center_y256 = psp_min(cg_BOSS_DATA_3b_center_y256, VR3f_boss_clip_max_y256);/* 下チェック(喰み出す) */
	cg_BOSS_DATA_3b_center_y256 = psp_max(cg_BOSS_DATA_3b_center_y256, VR3d_boss_clip_min_y256);/* 上チェック(喰み出す) */
	#endif
//
	/*(攻撃アニメーション指示があれば、攻撃アニメーションを優先する。)*/
	if (0 < cg_BOSS_DATA_33_kougeki_anime_count)	/* 攻撃アニメーション */	/* 攻撃アニメーション用カウンタ / 0以下なら移動アニメーション */
	{
		cg_BOSS_DATA_33_kougeki_anime_count--;
				if ((32) > cg_BOSS_DATA_33_kougeki_anime_count) {src->obj_type_set = BOSS_09_32;}	/*src->an im_frame = 0x23;*/
		else	if ((40) > cg_BOSS_DATA_33_kougeki_anime_count) {src->obj_type_set = BOSS_10_33;}	/*src->an im_frame = 0x22;*/
		else													{src->obj_type_set = BOSS_09_32;}	/*src->an im_frame = 0x21;*/
	}
	/*(攻撃アニメーション指示がなければ、移動アニメーションをする。)*/
	else	/* 移動アニメーション */
	{
		s32 aaa;
		aaa = (cg_BOSS_DATA_3a_center_x256 > cg_BOSS_DATA_30_target_x256)?(BOSS_00_11/*0x00*/):(BOSS_04_21/*0x10*/); /* 左右 */
		s32 bbb;
		bbb = cg_BOSS_DATA_34_toutatu_wariai256;
		bbb = psp_min(bbb, (0xff) );
		bbb = 0xff-bbb;
		bbb &= 0xff;
		src->obj_type_set = aaa + (cg_BOSS_DATA_34_toutatu_wariai256 >> 6);
	}
}

/*---------------------------------------------------------
	全ボス行動
	(boss->callback_mover)で呼ばれるルート(根源)。
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(root_boss_mover)
{
	/*(ボス行動選択処理)*/
	if (NULL != src->callback_root_supeka)
	{
		(*src->callback_root_supeka)(src);
	}
//	card_boss_move_generate_check_regist(src);	/* カード登録可能なら登録 / カード生成 */
	boss_move_vx_vy_animation(src);
	move_card_square_effect(src);				/* 回エフェクト */
	/*(スペル生成処理)*/
	card_generate(src);/* スペルをCPU実行し、カードを１フレーム生成する。 */
	/*(描画用座標の生成。r41-)*/
	/*(スペカCPUで一括管理しているのでオブジェクト座標は、スペカCPUの外部に置く)*/
	src->center.x256/*(スペカCPU外部座標[ボス用])*/ = cg_BOSS_DATA_3a_center_x256;/*(スペカCPU内部座標[ボス用])*/
	src->center.y256/*(スペカCPU外部座標[ボス用])*/ = cg_BOSS_DATA_3b_center_y256;/*(スペカCPU内部座標[ボス用])*/
}

