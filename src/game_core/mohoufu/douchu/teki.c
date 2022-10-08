
/* 中ボスがカード撃つ */
#include "./../boss/boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ザコは纏める予定。
---------------------------------------------------------*/

/*---------------------------------------------------------
	設定
---------------------------------------------------------*/

	#define USE_X_HOUKOU (1)

/*---------------------------------------------------------
	雑魚共通規格
---------------------------------------------------------*/
#if 0/* めも */
/* ボス共通規格 */
	#define target_x256 			user_data00 	/* 目標x座標 */
	#define target_y256 			user_data01 	/* 目標y座標 */
	#define boss_time_out			user_data02 	/* 制限時間 */
	#define boss_base_state777		user_data02 	/* 制限時間(boss_time_outと同じ) */
	#define kougeki_anime_count 	user_data03 	/* 攻撃アニメーション用カウンタ */
#endif


	/* 敵の向き tmp_angleCCW1024 */
// user_data00: user_data01: 座標(x, y);	locate(x, y) == (user_data00, user_data01);
	#define zd00_target_x256				user_data00
	#define zd01_target_y256				user_data01
	#define zd00_clip_left256				user_data00
	#define zd01_clip_right256				user_data01
// user_data02: 速度256;		speed256 == radius256 == wait1 == user_data02
	#define zd02_system_speed256			user_data02/*([system値]速度)*/
	#define zd02_radius256					user_data02
	#define zd02_zako_wait1 				user_data02 	/* [魔方陣]カウンタ1 / [緑毛玉] 上下に動いたカウンタ */
// user_data03: 角度256;		system_hoson_angle1024 == turnspeed1024 == px256 == start_y256
	#define zd03_system_hoson_angle65536 	user_data03/*([system値]保存角度)*/
	#define zd03_turnspeed65536				user_data03
	#define zd03_px256						user_data03 	/* 仮想x位置(反転用) */
	#define zd03_start_y256 				user_data03
// user_data04: 回数等; 	system_hoson_speed256 == kaisu_nnn == zako_wait2 == max_y256 == KARASU3_houkou
	#define zd04_system_hoson_speed256		user_data04/*([system値]保存速度)*/
	#define zd04_kaisu_nnn					user_data04 	/* 繰り返した回数のカウンタ / ターンする回数 / 弾を撃つ回数 */
	#define zd04_zako_wait2 				user_data04 	/* [魔方陣] カウンタ2 */
	#define zd04_max_y256					user_data04
	#define zd04_KARASU3_houkou 			user_data04
// user_data05: 攻撃タイプ
	#define zd05_kougeki_type				user_data05/*[regist_zako_011_kedama2 灰毛玉]*/

//#define zako_pattern_base 				user_data06 		/* パターンの基準位置。アニメする場合のベース */
#define zako_anime_rotate_angle65536 		user_data06/*zako_anime_base*/	/* アニメ回転角度1024 */

/*---------------------------------------------------------
	攻撃方法
---------------------------------------------------------*/
enum
{
/*(16)0*/	/*(00)*/ZAKO_SPEKA_00_utanai  = 0,		/*[撃たない。]*/
/*(08)*/	/*(01)*/ZAKO_SPEKA_01_mahou_nerai,		/*[]*/
/*(17)1*/	/*(02)*/ZAKO_SPEKA_02_mahou_tate,		/*[スペカ02]縦攻撃。*/
/*(18)2*/	/*(03)*/ZAKO_SPEKA_03_mahou_random, 	/*ばら撒き。*/
/*(15)3*/	/*(04)*/ZAKO_SPEKA_04_mahou_common, 	/*旧攻撃。*/
/*(20)4*/	/*(05)*/ZAKO_SPEKA_05_mahou_right,		/*右攻撃。4:円状攻撃のカード(小左)[6: 7:]*/
/*(21)5*/	/*(06)*/ZAKO_SPEKA_06_mahou_left,		/*左攻撃。5:円状攻撃のカード(中右)*/
/*(01)*/	/*(07)*/ZAKO_SPEKA_07_hai_kedama,		/*[スペカ07]灰毛玉のカード2*/
//
/*(30)*/	/*[08]*/ZAKO_SPEKA_08_hai_kedama,		/*[スペカ22]灰毛玉(?)*/
/*(09)*/	/*(09)*/ZAKO_SPEKA_09_inyou1,			/*[スペカ09]陰陽玉*/
/*(10)*/	/*[10]*/ZAKO_SPEKA_10_midori1,			/*[スペカ10]青毛玉(?)*/
/*(11)*/	/*(11)*/ZAKO_SPEKA_11_meido2,			/*[スペカ11]メイド02*/
/*(12)*/	/*[12]*/ZAKO_SPEKA_12_kisume,			/*[スペカ12]キスメ*/
/*(13)*/	/*[13]*/ZAKO_SPEKA_13_yukari,			/*[スペカ13]時空の裂け目弾*/
/*(14)*/	/*[14]*/ZAKO_SPEKA_14_obake1,			/*[スペカ14]隕石*/
/*(31)*/	/*[15]*/ZAKO_SPEKA_15_ao3_rendan,		/*[スペカ15]青妖精、連弾*/
//
/*(25)*/	/*[16]*/ZAKO_SPEKA_16_midori2,			/*[スペカ16]緑毛玉*/
/*(26)*/	/*[17]*/ZAKO_SPEKA_17_meido3,			/*[スペカ17]メイド03*/
/*(29)*/	/*(18)*/ZAKO_SPEKA_18_karasu,			/*[スペカ18 <- 21]カラス*/
/*(27)*/	/*(19)*/ZAKO_SPEKA_19_ao2,				/*[スペカ19]青妖精*/
//
	ZAKO_SPEKA_99_MAX,
};
/*---------------------------------------------------------
	中-ボス敵やられ
---------------------------------------------------------*/
/*extern*/static OBJ_CALL_FUNC(item_create_15_rumia)
{
	const u8 item_tbl[4] =
	{
		(SP_ITEM_02_P128&0xff), 	/* [F] */
		(SP_ITEM_01_P008&0xff), 	/* [P]大 */
		(SP_ITEM_00_P001&0xff), 	/* [p]小 */
		(SP_ITEM_05_TENSU&0xff),	/* [点] */
	};
	item_create_flags_num(src, /*item_type*/(OBJ_Z03_ITEM|(item_tbl[(cg_VR20_game_difficulty)])), (7), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
	/* ちらばる */
}
/*extern*/static OBJ_CALL_FUNC(item_create_14_yokai)
{
	item_create_flags_num(src, SP_ITEM_05_TENSU, (7), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
	/* ちらばる */	/* 点数を出す */
}
/*---------------------------------------------------------

---------------------------------------------------------*/

/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_00_item)	{item_create_mono(src, SP_ITEM_00_P001	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_01_item)	{item_create_mono(src, SP_ITEM_01_P008	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_02_item)	{item_create_mono(src, SP_ITEM_02_P128	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_03_item)	{item_create_mono(src, SP_ITEM_03_1UP	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_04_item)	{item_create_mono(src, SP_ITEM_04_BOMB	);}
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_05_item)	{item_create_mono(src, SP_ITEM_05_TENSU );}//static void item_create_018_meido4
/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_06_item)	{item_create_mono(src, SP_ITEM_06_HOSI	);}
#define item_create_07_item item_create_random_table


/*---------------------------------------------------------
	ザコ敵やられ
---------------------------------------------------------*/

static OBJ_CALL_FUNC(zako_shot_supeka);/*(宣言)*/

/*extern*/static/*static*/ OBJ_CALL_FUNC(item_create_002_inyou_zako)
{
	if (0==((src->center.x256)&( 8-1))) /*確率上げた。[1/8]←[1/20]*/ /*%20*/
	{
		zako_shot_supeka(src);
	}
	else
	{
	//	item_create_mono(src, (SP_ITEM_00_P001+(replay_rand()&1)) );
		item_create_mono(src, (SP_ITEM_00_P001+((src->center.x256)&1)) );
	}
}


/*---------------------------------------------------------
	ザコの攻撃方法は纏めるべき
---------------------------------------------------------*/


/*---------------------------------------------------------
	道中専用止まり弾
	-------------------------------------------------------
	全弾書き換え方式に移行するのでここは無くなる予定。
---------------------------------------------------------*/
/*---------------------------------------------------------
	ベクトル弾(基本的には、角度変化しない弾)
---------------------------------------------------------*/

#define BASE_add_speed256			user_data00 	/* 加減速 */
#define TOKUSYU_DAN_DATA_delta256	user_data01 	/* 加減速調整 */




#define TOMARI_DAN_LIMIT_00_MAX 	(512+384)	/* 適当に大きく1024==(512+64+最大停止時間) */
#define TOMARI_DAN_LIMIT_01_512 	(512)
#define TOMARI_DAN_LIMIT_02_032 	(32+0+0)

static OBJ_CALL_FUNC(bullet_move_douchu_tomari_dan)
{
	if (TOMARI_DAN_LIMIT_01_512 < src->jyumyou)/* 513 ... MAX */
	{
		/* 止まる */
	//	src->BASE_add_speed256 -= (1);
		src->BASE_add_speed256 -= (src->TOKUSYU_DAN_DATA_delta256);
		if (src->BASE_add_speed256 < t256(0))
		{
			src->BASE_add_speed256 = t256(0);
			src->jyumyou = (TOMARI_DAN_LIMIT_01_512);
		}
	}
	else
	if (TOMARI_DAN_LIMIT_02_032 < src->jyumyou)/* 33 ... 512 */
	{
		;	/* しばし停止 */
	}
	else/* 0 ... 32 */
	{
		/* 消える */
		src->color32 -= 0x10000000; 		/*	src->alpha -= 0x10; */
		if (0x20000000 > src->color32)		/*	(0x20 > src->alpha) */
		{
			src->color32 = 0x00ffffff;		/*	src->alpha = 0x00;	*/
			src->jyumyou = JYUMYOU_NASI;
		}
	}
	//
	src->center.y256 += t256(1.0);	/* 道中専用弾なのでスクロールする */
	//
//	move_bullet_vector(src);
	if (t256(1.00)!=(src->BASE_add_speed256))
	{
		#if (0)
	//	src->math_vector.x256 = ((src->math_vector.x256*src->BASE_add_speed256)>>8);/* 加速/減速 */ // 負の場合ダメ。
		#else
		const int vx256_speed = (src->math_vector.x256*src->BASE_add_speed256);
		if (0 < vx256_speed) /* 正の場合 */
		{
			src->math_vector.x256 = ((vx256_speed)>>8);/* 加速/減速 */
		}
		else /* 負の場合 */
		{
			src->math_vector.x256 = -((-vx256_speed)>>8);/* 加速/減速 */
		}
		#endif
		//
		#if (1)/* 悪影響がさしてないので... */
		src->math_vector.y256 = ((src->math_vector.y256*src->BASE_add_speed256)>>8);/* 加速/減速 */ // 負の場合ダメ。
		#else
		const int vy256_speed = (src->math_vector.y256*src->BASE_add_speed256);
		if (0 < vy256_speed) /* 正の場合 */
		{
			src->math_vector.y256 = ((vy256_speed)>>8);/* 加速/減速 */
		}
		else /* 負の場合 */
		{
			src->math_vector.y256 = -((-vy256_speed)>>8);/* 加速/減速 */
		}
		#endif
	}
	src->center.x256 += (src->math_vector.x256);	/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);	/*fps_factor*/
}

/*---------------------------------------------------------
	弾を登録する。
	-------------------------------------------------------
	弾発動時のエフェクト等の関係上、発弾部分は全部纏める必要がある。
	-------------------------------------------------------
	ベクトル弾と角度弾を統合するかもしれない。
	-------------------------------------------------------
	ToDo:
	弾システムに移行する為、廃止予定。
	カードスクリプトシステムが稼動する為には、発弾を一ヶ所に統合しないと
	速度的な面でこのままの形態では無理があるので、
	(ここの発弾処理のせいで他の弾が処理落ちする)
	ここの発弾処理を hatudan_system_regist_single に置きかえる必要がある。
---------------------------------------------------------*/
/* ベクトル特殊弾(仮、移行形態) */

//	#define hatudan_system_kousadan_angle65536 tmp_angleCCW1024
	#define hatudan_system_kousadan_angle65536 tmp_angleCCW65536


static OBJ_CALL_FUNC(bullet_regist_douchu_vector_tomari_dan)
{
	OBJ *h;
	h											= obj_regist_tama();/* 発弾登録 */
	if (NULL != h)/* 登録できた場合 */
	{
		//[67?]
		h->center.x256							= VR06;/* 発弾位置 座標x */
		h->center.y256							= VR07;/* 発弾位置 座標y */
	//	h->center.x256							= VR07;/* 発弾位置 座標x */
	//	h->center.y256							= VR06;/* 発弾位置 座標y */
		h->obj_type_set 						= (HATSUDAN_R15_bullet_obj_type);
		reflect_sprite_spec(h, OBJ_BANK_SIZE_00_TAMA);	/* 弾グラと弾あたり判定を変更する。 */
		//
		mask65536(HATSUDAN_R13_angle65536);
		h->hatudan_system_kousadan_angle65536	= (HATSUDAN_R13_angle65536);
		h->m_Hit256R							= TAMA_ATARI_MARU16_PNG;
		//
		/*angle512								= angle_jikinerai512_auto(obj_player, src, angle512);*/
	//	VR09							= (HATSUDAN_R11_speed256);
	//	ang le_to_vector(h);
		//------------------/*(角度をX軸、Y軸のベクトル速度へ変換する)*/
	//	HATSUDAN_R11_speed256	= (HATSUDAN_R11_speed256);
	//	HATSUDAN_R13_angle65536 = (h->hatudan_system_kousadan_angle65536);
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		h->math_vector.x256	= VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		h->math_vector.y256	= VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
		//
		// [レガシーシステム対応]
		h->TR00_hatudan_spec_data			= (0);/*(r35レガシーシステム側で、使わなくても、弾幕システム側で使うのでここで設定する必要がある。)*/
		//
		/* とりあえず、テキトー */
	//	h->BASE_add_speed256					= (t256(1.00)); 	/* 加速/減速、なし */
		h->BASE_add_speed256					= 1+(t256(1.00));	/* 加速 弾 */
		//
		h->TOKUSYU_DAN_DATA_delta256			= (HATSUDAN_R12_speed_offset);
		h->jyumyou								= (TOMARI_DAN_LIMIT_00_MAX);
		h->callback_mover						= bullet_move_douchu_tomari_dan;
	}
}


/*---------------------------------------------------------
	ザコの攻撃方法は纏めるべき
8 1.00
7 0.50
6 0.25
5 0.125
---------------------------------------------------------*/
typedef struct /*aa*/
{
	int SR15_bullet_obj_type;	// HATSUDAN_R15_bullet_obj_type
	s32 SR14_nan_ido_kankaku;/*(借りる)*/
	s32 SR11_nan_ido_speed64;	// HATSUDAN_R11_speed256
	s32 SR16_nan_ido_n_way; 	// HATSUDAN_R16_n_way
	s32 SR17_div_angle65536;	// HATSUDAN_R17_div_angle65536
} ZAKO_SPELL_RESOURCE;
static ZAKO_SPELL_RESOURCE kougeki_tbl[(ZAKO_SPEKA_99_MAX)] =
{
	/*
	-------------------------------------------------------
	(r41-)発弾後 16[frame] は 3倍速移動する様に、システムを変更した。
	pspの画面は狭いので、雑魚弾の弾速 t256(2.00) 以上はゲームが破綻する。
	(高速弾は避けるより先に画面外へ出る。)
	そこで t256(2.00) 以上は基本的に廃止する。(t64の範囲は最大 t64(3.99ぐらい) まで)
	-------------------------------------------------------
	将来的に スペカCPU で 雑魚の動きも発弾も行うので、
	だったらここは最終的に(BOSSの)スペカと統合されるべき気がする。
	-------------------------------------------------------
	*/
//(-r40)/*(未使用)*/{(BULLET_KOME_BASE),						PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x07, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.375), t64(1.500), t64(1.625)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((8), (8), (4), (9)), PACK_NAN_IDO_CONST(( 6), ( 8), ( 8), (16))},	/* ZAKO_SPEKA_04_mahou03[e] 8:見せ弾(無駄弾なので難易度は低い筈) */

	/* 0:紅っぽい毛玉(狭角度 奇数弾) t256(2.5)		  (r41-)				(-r40)	*/
/*(16)0*/	/*(00)*/{(0),/*(撃たない)*/ 						PACK_NAN_IDO_CONST(0x01, 0x01, 0x01, 0x01), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*0,		  */PACK_NAN_IDO_CONST((1), (1), (1), (1)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_00_utanai-*/
/*(08)*/	/*(01)*/{(BULLET_MINI8_BASE + TAMA_IRO_03_AOI), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.500), t64(0.500), t64(0.500), t64(0.500)), 		/*t256(0.500),*/PACK_NAN_IDO_CONST((1), (1), (1), (2)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_01_mahou_nerai */ 		// 6 -	// [魔方陣 3/囲妖怪1:ランダムばらまき攻撃+自機狙い("魔方陣1")のカード]
/*(17)1*/	/*(02)*/{(BULLET_KOME_BASE + TAMA_IRO_01_AKA),		PACK_NAN_IDO_CONST(0x01, 0x01, 0x01, 0x01), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((2), (2), (6),(12)), PACK_NAN_IDO_CONST(( 2), ( 2), ( 6), (12))},	/* ZAKO_SPEKA_02_mahou_tate */			// 6 7	// [魔方陣 1:縦攻撃のカード]
/*(18)2*/	/*(03)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.750), t64(1.750), t64(1.750), t64(1.750)), 		/*t256(2.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 4), ( 4), ( 4), ( 4))},	/* ZAKO_SPEKA_03_mahou_random */		// . .	// [魔方陣 2:ランダムばらまき攻撃("魔方陣2")のカード]
/*(15)3*/	/*(04)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((4), (4), (4), (5)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_04_mahou_common */		//		// [魔方陣 とりあえず共通部分]
/*(20)4*/	/*(05)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_05_mahou_right */ 		//		// [魔方陣 とりあえず共通部分]
/*(21)5*/	/*(06)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), /*?*/	/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (6)), PACK_NAN_IDO_CONST(( 7), ( 7), ( 7), ( 7))},	/* ZAKO_SPEKA_06_mahou_left */			//		// [魔方陣 とりあえず共通部分]
/*(01)*/	/*(07)*/{(BULLET_KOME_BASE),/*(灰毛玉)*/			PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x0f, 0x07), PACK_NAN_IDO_CONST(t64(1.250), t64(1.375), t64(1.500), t64(1.625)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((5), (3), (3), (7)), PACK_NAN_IDO_CONST(( 9), (12), (12), (12))},	/* ZAKO_SPEKA_01_utanai[e] (u32)(1024/12):広角なので簡単 */
					//
/*(30)*/	/*(08)*/{(BULLET_KOME_BASE),/*(灰毛玉slow)*/		PACK_NAN_IDO_CONST(0x3f, 0x1f, 0x07, 0x03), PACK_NAN_IDO_CONST(t64(0.500), t64(0.500), t64(0.500), t64(0.500)), 		/*t256(0.500),*/PACK_NAN_IDO_CONST((3), (5), (7), (9)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_08_hai_kedama */ 			// . 7	// [ 毛玉1のカード]
/*(09)*/	/*(09)*/{(BULLET_HARI32_01_AKA),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(2.000), t64(2.000), t64(2.000), t64(2.000)), 		/*t256(2.500),*/PACK_NAN_IDO_CONST((7), (7), (9),(13)), PACK_NAN_IDO_CONST((12), (18), (24), (28))},	/* ZAKO_SPEKA_09_inyou1 */				// 6 7	// [針弾]
/*(10)*/	/*(10)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.375), t64(1.375), t64(1.375), t64(1.375)), 		/*t256(1.375),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_10_midori1 */ 			// 6 -	// [緑毛玉1/メイド1 のカード]
/*(11)*/	/*(11)*/{(BULLET_HARI32_00_AOI),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(2.000), t64(2.000), t64(2.000), t64(2.000)), 		/*t256(2.500),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_11_meido2 */				// 6 -	// [ メイド2のカード]
/*(12)*/	/*(12)*/{(BULLET_MINI8_BASE + TAMA_IRO_07_DAI_DAI), PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_12_kisume */ // 6 -	// [ キスメ1のカード]
/*(13)*/	/*(13)*/{(BULLET_MINI8_BASE + TAMA_IRO_07_DAI_DAI), PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.750), t64(0.750), t64(0.750), t64(0.750)), 		/*t256(0.750),*/PACK_NAN_IDO_CONST((1), (1), (1), (3)), PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 1))},	/* ZAKO_SPEKA_13_yukari */				// 6 -	// [ 紫編隊2のカード]
/*(14)*/	/*(14)*/{(BULLET_KNIFE20_04_AOI),					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(0.625), t64(0.625), t64(0.625), t64(0.625)), 		/*t256(0.625),*/PACK_NAN_IDO_CONST((1), (1), (3), (7)), PACK_NAN_IDO_CONST((12), (18), (18), (18))},	/* ZAKO_SPEKA_14_obake1 */				// . 7	// [おばけ1 のカード]
/*(31)*/	/*[15]*/{(BULLET_MINI8_BASE),/*(連弾)*/ 			PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.250), t64(1.250), t64(1.250), t64(1.250)), 		/*t256(1.250),*/PACK_NAN_IDO_CONST((7), (7), (7), (9)), PACK_NAN_IDO_CONST(( 8), (12), (16), (24))},	/* ZAKO_SPEKA_15_ao3_rendan */			// 6 -	// [ 青妖精2のカード]
					//
/*(25)*/	/*(16)*/{(BULLET_MINI8_BASE + TAMA_IRO_01_AKA), 	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.500), t64(1.500), t64(1.500), t64(1.500)), 		/*t256(1.500),*/PACK_NAN_IDO_CONST((1), (2), (3), (3)), PACK_NAN_IDO_CONST((12), (48), (48), (48))},	/* ZAKO_SPEKA_16_midori2 */ 			// . 7	// [緑毛玉2 のカード]
/*(26)*/	/*[17]*/{(BULLET_UROKO14_BASE + TAMA_IRO_01_AKA),	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (2), (4), (7)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_17_meido3 */				// . 7	// [ メイド3のカード]
/*(29)*/	/*(18)*/{(BULLET_KUNAI12_BASE), 					PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((8), (8), (8), (9)), PACK_NAN_IDO_CONST(( 8), ( 8), ( 8), ( 8))},	/* ZAKO_SPEKA_18_karasu */				// 6 7	// [ 青妖精3/烏1のカード]
/*(27)*/	/*(19)*/{(BULLET_UROKO14_BASE + TAMA_IRO_03_AOI),	PACK_NAN_IDO_CONST(0x03, 0x03, 0x03, 0x03), PACK_NAN_IDO_CONST(t64(1.000), t64(1.000), t64(1.000), t64(1.000)), 		/*t256(1.000),*/PACK_NAN_IDO_CONST((1), (1), (2), (5)), PACK_NAN_IDO_CONST((12), (24), (24), (24))},	/* ZAKO_SPEKA_19_ao2 */ 				// . 7	// [ 青妖精1/青妖精4のカード(B)]
	//
};

	#if 0/*(てすつ)*/
	if (0==(cg_VR20_game_difficulty))
	{
		return;
	}
	#endif

static OBJ_CALL_FUNC(zako_shot_supeka)
{
	const void *aaa[(ZAKO_SPEKA_99_MAX)] =
	{
/*(16)0*/		/*(00)*/&&COMMON_JIKI_NERAI,				// mahoujin00 ZAKO_SPEKA_10_aaa [未使用]のカード	/* 攻撃しない */
/*(08)*/		/*(01)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_01_mahou_nerai	魔方陣 3:ランダムばらまき攻撃+自機狙い("魔方陣1")のカード
/*(17)1*/		/*(02)*/&&label_ZAKO_SPEKA_02_mahou_tate,	// mahoujin01 ZAKO_SPEKA_02_mahou_tate 魔方陣 1:縦攻撃のカード
/*(18)2*/		/*(03)*/&&label_ZAKO_SPEKA_03_mahou_random, // mahoujin02 ZAKO_SPEKA_03_mahou_random 魔方陣 2:ランダムばらまき攻撃("魔方陣2")のカード	/* ばらまき #01(差分氏、旧"魔方陣2") */
/*(15)3*/		/*(04)*/&&label_ZAKO_SPEKA_04_mahou_common, // ZAKO_SPEKA_04_mahou_common 魔方陣 とりあえず共通部分
/*(20)4*/		/*(05)*/&&label_muki_mahou_right,			// mahoujin04 ZAKO_SPEKA_05_mahou_right のカード	/* 8way花弾(中) */
/*(21)5*/		/*(06)*/&&label_muki_mahou_left,			// mahoujin05 ZAKO_SPEKA_06_mahou_left のカード /* 8way花弾(中) */
/*(01)*/		/*(07)*/&&label_ZAKO_SPEKA_07_haikedama,	// ZAKO_SPEKA_07_hai_kedama 灰毛玉 のカード2
						//
/*(30)*/		/*(08)*/&&COMMON_JIKI_NERAI_p_cx,			// ZAKO_SPEKA_08_hai_kedama		のカード
/*(09)*/		/*(09)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_09_inyou1 		陰陽玉1 のカード [針弾]
/*(10)*/		/*(10)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_10_midori1		緑毛玉1 のカード
/*(11)*/		/*(11)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_11_meido2 		のカード
/*(12)*/		/*(12)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_12_kisume 		キスメ のカード
/*(13)*/		/*(13)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_13_yukari 		のカード
/*(14)*/		/*(14)*/&&COMMON_MULTI_VECTER,				// ZAKO_SPEKA_14_obake1 		おばけ1 のカード
/*(31)*/		/*[15]*/&&label_ZAKO_SPEKA_15_ao3_rendan,	// ZAKO_SPEKA_15_ao3_rendan 	のカード
						//
/*(25)*/		/*(16)*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_16_midori2 		緑毛玉2 のカード
/*(26)*/		/*[17]*/&&COMMON_JIKI_NERAI,				// ZAKO_SPEKA_17_meido3 		のカード
/*(29)*/		/*(18)*/&&COMMON_JIKI_NERAI_p_cx,			// ZAKO_SPEKA_18_karasu 		のカード
/*(27)*/		/*(19)*/&&label_ZAKO_SPEKA_19_ao2,			// ZAKO_SPEKA_19_ao2			のカード
		//
	};
	s32 zako_supeka_type;
	zako_supeka_type = (src->zd05_kougeki_type);
	zako_supeka_type = psp_min(zako_supeka_type, (ZAKO_SPEKA_99_MAX-1));//	if (ZAKO_SPEKA_99_MAX < zako_supeka_type)	{zako_supeka_type = 0;}//	zako_supeka_type &= 0x1f;/*(念の為)*/
	//-------------------------
	HATSUDAN_R15_bullet_obj_type	= kougeki_tbl[(zako_supeka_type)].SR15_bullet_obj_type;
	VR11							= kougeki_tbl[(zako_supeka_type)].SR11_nan_ido_speed64;	// speed64は難易度別に設定。
	VR14							= kougeki_tbl[(zako_supeka_type)].SR14_nan_ido_kankaku;	// speed64は難易度別に設定。/*(借りる)*/
	HATSUDAN_R16_n_way				= kougeki_tbl[(zako_supeka_type)].SR16_nan_ido_n_way;	// n_wayは難易度別に設定。
	HATSUDAN_R17_div_angle65536 	= kougeki_tbl[(zako_supeka_type)].SR17_div_angle65536;	// 分割角度は難易度別に設定。
	//-------------------------
	static const u32 codebase000[6] =
	{
		// (1)	VR11 = 難易度別定数; HATSUDAN_R11_speed256 t64();
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R11, R11),
		// (2)	VR14 = 難易度別定数; VR14(借りる)
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R14, R14),
		// (3)	VR16 = 難易度別定数1; HATSUDAN_R16_n_way
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R16, R16),
		// (4)	VR17 = 難易度別定数2; HATSUDAN_R17_div_angle65536
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R17, R17),
		// (5)	VR17 = 65536 / VR17;
		MCODE(OP0x17_DIV65536, NAX, R17, R17),
		// (6)	HATSUDAN_R11_speed256 <<= 2;/*変換 t256() <- t64(); */
		MCODE(OP0x1f_ASLM_PD, (2), R11, R11),/*(ショートメモリアドレッシング)*/
		// (7)
	//	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase000, (6));//
	//-------------------------
	// ゲームランクで微加速。(高難度ではどっちかっていうと弾速が速い方が画面内の弾数が減ってゲームが簡単になる)
	HATSUDAN_R11_speed256	+= ((cg_game_rank)>>8);/*([1-6面までノーミスとして]最大でも2倍速程度にしかならない)*/
	//-------------------------
	//
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
	//
	goto *aaa[(zako_supeka_type)/*& 0x1f*/];
label_ZAKO_SPEKA_07_haikedama:
	//static void zako_spell_01_hai_kedama(OBJ/**/ *src, u8 zako_supeka_type)
		//	zako_supeka_type -= (ZAKO_SPEKA_18_hai_kedama);
		//	zako_supeka_type &= (0x07);
		if (0==(src->jyumyou & VR14/*(借りる)*/))/*0x0f*/ //kougeki_tbl[(zako_supeka_type & 0x07)].kankaku
		{
			HATSUDAN_R15_bullet_obj_type			= BULLET_KOME_BASE + (src->center.x256 & 0x07);
			goto COMMON_JIKI_NERAI;
		}
	//	else	{goto EXIT_ZAKO_SPEKA;}
		goto EXIT_ZAKO_SPEKA;
//-------------------------
		//	attack_kougeki_mahoujin_common(src);
//-------------------------
label_muki_mahou_left:
		HATSUDAN_R13_angle65536 						= (((-(src->jyumyou+src->jyumyou)+((src->jyumyou&0x07)<<7)))<<6);	/* 向き */
		goto label_ZAKO_SPEKA_04_mahou_common;
label_muki_mahou_right:
		HATSUDAN_R13_angle65536 						= ((( (src->jyumyou+src->jyumyou)+((src->jyumyou&0x07)<<7)))<<6);	/* 向き */
	//	goto label_ZAKO_SPEKA_04_mahou_common;
label_ZAKO_SPEKA_04_mahou_common:	// [魔方陣 とりあえず共通部分]
	//	HATSUDAN_R13_angle65536 						= (int)(65536/(7)); 						/* 角度(一周を 7 分割) */	/* 1周をn分割した角度 */
		HATSUDAN_R12_speed_offset						= (1);//t256(0.03); 						/* 減速定数 */
		goto COMMON_LEGACY_DIRECT;

label_ZAKO_SPEKA_03_mahou_random:	// [魔方陣 2:ランダムばらまき攻撃("魔方陣2")のカード]
		/* 速度は 1.0-3.0までの無段階乱数に変更 */
		HATSUDAN_R11_speed256							+= ((ra_nd()&(512-1))); 	/* 弾速 */
		HATSUDAN_R13_angle65536 						= ((ra_nd()&(65536-1)));					/* 角度 */
		HATSUDAN_R12_speed_offset						= (2);//10.24==t256(0.04);					/* 減速定数 */
		goto COMMON_LEGACY_DIRECT;
//------------------------- 固定弾
label_ZAKO_SPEKA_02_mahou_tate: 	// [魔方陣	1:縦攻撃のカード]
		HATSUDAN_R13_angle65536 						= (int)(65536/(4)); 		/* 右向き(上下弾)、偶数弾なので結果的に上下弾。 */
//		HATSUDAN_R15_bullet_obj_type					= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* 赤米弾 */
//		HATSUDAN_R16_n_way								= (2);						/* [2way] */
//		HATSUDAN_R17_div_angle65536 					= (int)(65536/(2)); 		/* 角度(一周を 2 分割) */	/* 1周をn分割した角度 */
		goto COMMON_MULTI_VECTER;


//------------------------- 連弾
/*
	-------------------------------------------------------
	R0c 	覚えとく角度。aaa_angle65536
*/
label_ZAKO_SPEKA_15_ao3_rendan: 	// [ 青妖精2のカード]
	{
		static /*const*/ u32 codebase_exec[19] =
		{
			// (1)	 (calculate_jiki_nerai); /* 自機狙い弾を撃つ。 */
			MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
			// (2)	VR0c = VR13;/*(自機狙い角度を覚えとく)*/
			MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		//	static const u16 bunkatsu65536_tbl[4] =
		//	{((int)(65536/8)), ((int)(65536/12)), ((int)(65536/16)), ((int)(65536/24))};
		//	HATSUDAN_R16_n_way							= (7);									/* [7way] */
		//	HATSUDAN_R17_div_angle65536 				= (bunkatsu65536_tbl[((cg_VR20_game_difficulty))]); 	/* 分割角度 */
			// (3) HATSUDAN_R12_speed_offset					= t256(3/*6*/);/*(テスト)*/
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
			(t256(3/*6*/)),/*(テスト)*/
			//		HATSUDAN_R14_tama_spec						= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			// (4)	HATSUDAN_R14_tama_spec						= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
			((DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			/* ミニ弾の連弾 */
			// (5)	VR03_i = 8;/*(8 回ループして追加)*/ /*8 6(4)*/
			MCODE(OP0x1c_MOVEM_PD, (8), R03_i, NAX),/*(ショートメモリアドレッシング)*/
		//loop_i;// (ddd-11)loop_i:;
			//	/*[r35要半分速]*/HATSUDAN_R11_speed256		= (t256(2.5)+(VR03_i<<6));		/* 弾速 */
			//	/*[r35半分速]*/HATSUDAN_R11_speed256		= (t256(1.25)+(VR03_i << 5));	/* 弾速 */
			// (6)	VR11 = (VR03_i << 4);// VR11 = (VR03_i << 5);
			MCODE(OP0x1f_ASLM_PD, 0x04, R11, R03_i),/*(ショートメモリアドレッシング)*/
			// (7)	VR11 += (t256(1.25));
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
			(t256(0.75)),		//	(t256(1.25)),
			// (8) HATSUDAN_R13_angle65536				= VR0c;/*(覚えといた自機狙い角度を使う)*/
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
			//	HATSUDAN_R15_bullet_obj_type			= ((BULLET_MINI8_BASE + TAMA_IRO_01_AKA)+(/*0*/6-VR03_i/*とりあえず*/)); /* [ 弾] */
			// (9) VR15 = VR03_i;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R03_i),
			// (10) VR15 = (VR00 + 8 - VR15);
			MCODE(OP0x05_SUBR_PD, (8), R15, R00),/*(ゼロレジスタ使用)*/
			// (11)  VR15 += (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			((BULLET_MINI8_BASE + TAMA_IRO_01_AKA)),
			// (12)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
			// (13) VR03_i--;/*(残り回数減らす。)*/
			MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
			// (14) if (0 != (s32)VR03_i) {goto loop_i;}/*(残り回数があればループ。)*/ if (0 < (s32)VR03_i) {goto loop_i;}
			MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-11)),//	(ddd-11)loop_i:;
		//(osimai+14:)//(osimai+32:)// おしまい
			// (15)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
		};
		cpu_exec((u32*)&codebase_exec, (15+6*11));/*(テキトー)*/
	}
	goto EXIT_ZAKO_SPEKA;
//-------------------------
	COMMON_LEGACY_DIRECT:
		bullet_regist_douchu_vector_tomari_dan(src);/*(雑魚ではここ以外無い)*/
		goto EXIT_ZAKO_SPEKA;
	//
//------------------------- 自機狙い
	COMMON_JIKI_NERAI_p_cx:
		HATSUDAN_R15_bullet_obj_type					+= (src->center.x256 & 0x07);
		goto COMMON_JIKI_NERAI;

label_ZAKO_SPEKA_19_ao2:	// [ 青妖精1/青妖精4のカード(B)]
		HATSUDAN_R17_div_angle65536 					-= ((cg_VR20_game_difficulty)<<6);	/* 分割角度 */
	//	goto COMMON_JIKI_NERAI;
		/*(not_break;)*/
	COMMON_JIKI_NERAI:
		CPU_CALL(calculate_jiki_nerai);
		/*(not_break;)*/
	COMMON_MULTI_VECTER:
	//	HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= (2);/*(とりあえず)*/
	//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
/*(道中弾用開始)*/HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/* (r42-) */
		//	goto EXIT_ZAKO_SPEKA;
	EXIT_ZAKO_SPEKA:
			;
}



/*---------------------------------------------------------
	ザコ移動共通、等直線移動処理。
	-------------------------------------------------------
	速度: src->zd02_system_speed256。雑魚登録時に自動設定を使用する。
	角度: src->tmp_angleCCW1024。	 雑魚登録時に自動設定を使用する。
	-------------------------------------------------------
---------------------------------------------------------*/
#if 0
つまりただ登場するだけで、何も特別な処理をしなく、
等直線移動する雑魚なら、こんな感じ。
static OBJ_CALL_FUNC(move_zako_sample)
{
	if (JYUMYOU_ZAKO_HASSEI -byou60(3) > src->jyumyou)/*(発生から3[秒]以上経過した雑魚が画面外ならば消去)*/
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type01(src);/*(メイド共通、アニメーション)*/
}
#endif

static OBJ_CALL_FUNC(zako_system_move_vector)
{
	//------------------
	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
	HATSUDAN_R13_angle65536 = (src->tmp_angleCCW65536);
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	src->center.x256 += VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	src->center.y256 += VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
}

#if 0/*(メモ)*/
	#if (0)//
	src->center.x256 += ((si n1024((src->tmp_angleCCW1024))*(src->zd02_system_speed256))>>8);/*fps_factor*/ /* CCWの場合 */
	src->center.y256 += ((co s1024((src->tmp_angleCCW1024))*(src->zd02_system_speed256))>>8);/*fps_factor*/
	#else
	{
		int sin_value_t256; 	//	sin_value_t256 = 0;
		int cos_value_t256; 	//	cos_value_t256 = 0;
		int256_sin cos65536(src->tmp_angleCCW65536, &sin_value_t256, &cos_value_t256);
		src->center.x256 += ((sin_value_t256*(src->zd02_system_speed256))>>8);/*fps_factor*/
		src->center.y256 += ((cos_value_t256*(src->zd02_system_speed256))>>8);/*fps_factor*/
	}
	#endif
#endif

/*---------------------------------------------------------
	ザコアニメ共通
---------------------------------------------------------*/
/* 0000 0100 0000 0000 = 0x0400 = 1024 */
/* 0000 0011 1--- ---- */
static OBJ_CALL_FUNC(zako_anime_type_99_rotate)
{
	src->rotationCCW65536 += (src->zako_anime_rotate_angle65536);/*グラ回転*/
	mask65536(src->rotationCCW65536);
}
static OBJ_CALL_FUNC(zako_anime_type01)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
	//	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW1024)&(1024-1)))>>7);
	//	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW1024)&(0x0380)))>>7);
	///	src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW65536>>6)&(0x0380)))>>7);/*r42とりあえず*/
		src->obj_type_set				= ((src->obj_type_set)&(~0x07)) + ((((src->tmp_angleCCW65536)&(0x0380<<6)))>>(6+7));/*r42とりあえず*/
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type02)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x03)) + ((src->jyumyou>>2)&(4-1));
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type05)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x03)) + ((src->jyumyou>>4)&(4-1));
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type03)
{
	if (0==(src->zako_anime_rotate_angle65536))
	{
		src->obj_type_set				= ((src->obj_type_set)&(~0x01)) + ((src->jyumyou&0x10)>>4);
	}
	else
	{
		zako_anime_type_99_rotate(src);
	}
}
static OBJ_CALL_FUNC(zako_anime_type04)
{
	src->rotationCCW65536 += (src->zako_anime_rotate_angle65536);/*グラ回転*/
	mask65536(src->rotationCCW65536);
}


/*---------------------------------------------------------

---------------------------------------------------------*/
#include "zako_move.h"					/* 雑魚移動/登録 */

/*---------------------------------------------------------
	倒した場合のアイテム指定
	中ボスと共用する必要がある。
---------------------------------------------------------*/

static GAME_COMMAND_OBJ_FUNC(regist_items_common)
{
	void (*aaa[(16)])(OBJ/**/ *gcmd_obj) =
	{
		item_create_00_item,			item_create_01_item,				item_create_02_item,			item_create_03_item,
		item_create_04_item,			item_create_05_item,				item_create_06_item,			item_create_07_item,
		item_create_random_table,		item_create_random_table,			item_create_002_inyou_zako, 	item_create_random_table,
		item_create_random_table,		item_create_random_table,			item_create_14_yokai,			item_create_15_rumia,
	};
	gcmd_obj->callback_loser	= aaa[(((gcmd->user_item8)) & 0x0f)];	/* 「ザコ/中ボス/(ボス)がやられた場合の処理」に、「ランダムテーブルからアイテム生成」を設定 */
}
/*
gcmd_obj->jyumyou		 ---a bc--
gcmd_obj->yx_an im_frame  yyyy xxxx
gcmd_obj->yx_an im_frame  --1a --bc
*/

/*---------------------------------------------------------
	倒した場合のアイテム指定
	中ボス/ボスと共用する必要がある。
	-------------------------------------------------------
	(r36-)の仕様上、スコアとザコのあたり判定は同じ物。
	したがって DATで スコア 0 に設定しておくと、無敵ザコになる。
---------------------------------------------------------*/
static GAME_COMMAND_FUNC(set_locate_xy_to_R06_R07)
{
	//[67!!]
	VR06 = ((gcmd->user_locate_x)<<8);	/* [pixel単位] 設定ファイルから 出現x座標 を決める。 */
	VR07 = ((gcmd->user_locate_y)<<8);	/* [pixel単位] 設定ファイルから 出現y座標 を決める。 */
//	VR07 = ((gcmd->user_locate_x)<<8);	/* [pixel単位] 設定ファイルから 出現x座標 を決める。 */
//	VR06 = ((gcmd->user_locate_y)<<8);	/* [pixel単位] 設定ファイルから 出現y座標 を決める。 */
}

/*extern*/static GAME_COMMAND_OBJ_FUNC(regist_settei_common)
{
	game_command_regist_items_common(gcmd, gcmd_obj);/* 中ボスと共用する必要がある。 */
	gcmd_obj->m_Hit256R 		= ZAKO_ATARI16_PNG; 	/* グラからあたり判定を決める。 */
	//------------------
	gcmd_obj->obj_type_set		= (OBJ_Z02_TEKI)|((gcmd->user_select_gazou)&0x3f); /* 設定ファイルから画像を決める。 */
	//------------------
	/*
		DATは人間が書くので、間違ってたりする。
		パターンアニメーション専用のザコキャラに、
		回転系グラを指定した場合、
		パターンアニメーション出来ないので、
		バグったキャラになってしまう。
		そこでそういう場合は、強制的に回転系に補正する。
	*/
	if (11<((gcmd->user_select_gazou) & 0x0f))/*(12, 13, 14, 15) */
	{
		gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* 回転アニメ */	/* 回転する速さ */
	}
	else
	{
		gcmd_obj->zako_anime_rotate_angle65536 = (0);	/* グラタイプ */	/* off */
	}
	//------------------
	game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel単位] 設定ファイルから 出現(x, y)座標 を(VR06, VR07)に設定する。 */
	//[67!!]
	gcmd_obj->center.x256		= VR06; 						/* [pixel単位] 設定ファイルから 出現x座標 を決める。 */
	gcmd_obj->center.y256		= VR07; 						/* [pixel単位] 設定ファイルから 出現y座標 を決める。 */
//	gcmd_obj->center.x256		= VR07; 						/* [pixel単位] 設定ファイルから 出現x座標 を決める。 */
//	gcmd_obj->center.y256		= VR06; 						/* [pixel単位] 設定ファイルから 出現y座標 を決める。 */
	gcmd_obj->zako_hp			= (gcmd->user_hp);				/* 設定ファイルから 体力 を決める。 */
	gcmd_obj->base_score		= (gcmd->user_score);			/* 設定ファイルから 獲得スコア を決める。(あたり判定共用) */
	//
	gcmd_obj->zd05_kougeki_type = (gcmd->user_kougeki_type);	/* 設定ファイルから 攻撃タイプ を決める。 */
	#if 1
	//------------------設定ファイルから 攻撃角度 を決める。
	// 設定値角度が1024の場合、特別機能で自機狙い角を生成(r39-)。
	if (1023 < (gcmd->user_angle1024))
	{
	//	VR06	= ((gcmd_obj->center.x256));
	//	VR07	= ((gcmd_obj->center.y256));
		set_REG_DEST_XY(gcmd_obj);
		CPU_CALL(calculate_jiki_nerai);
	//  HATSUDAN_R13_angle65536 = (攻撃角度);
	}
	else/* 設定値角度が0-1023の場合、0-65535に変換し角度を決める。 */
	{
		HATSUDAN_R13_angle65536 		= (deg1024to65536(gcmd->user_angle1024));	/* 角度deg1024 */	/* [deg1024単位]  設定ファイルから */
	}
	#endif
	//------------------設定ファイルから 攻撃速度 を決める。
	HATSUDAN_R11_speed256					= (gcmd->user_speed256);	/* 速度t256 */	/* [t256単位]  設定ファイルから 攻撃速度 を決める。 */
	// ここまでで 攻撃速度 を HATSUDAN_R11_speed256 (VR11) へ設定済み。
	// ここまでで 攻撃角度 を HATSUDAN_R13_angle65536 (VR13) へ設定済み。
	//------------------ [初期値] を保存する。
	gcmd_obj->zd03_system_hoson_angle65536	= (HATSUDAN_R13_angle65536);	/* 攻撃角度 を 初期値として使用するので保存。 */
	gcmd_obj->zd02_system_speed256			= (HATSUDAN_R11_speed256);		/* 攻撃速度 を 初期値として使用するので保存。 */
	gcmd_obj->zd04_system_hoson_speed256 	= (HATSUDAN_R11_speed256);		/* 攻撃速度 を 初期値として使用するので保存。 */
	//------------------
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	//[76?]
//	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
//	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
}
//	(r36) gcmd_obj->base_score === src->atari_hantei	= (1/*スコア兼用*/);	/* デフォルトはあたり判定あり */


/*---------------------------------------------------------
	ザコ登録の共通ルーチン
	-------------------------------------------------------
---------------------------------------------------------*/
static GAME_COMMAND_OBJ_FUNC(regist_NULL)	{	;	}

typedef struct
{
	void (*aaa_init_callback)(GAME_COMMAND *gcmd, OBJ *gcmd_obj);	/* 初期化 処理 */
	void (*aaa_move_callback)(OBJ *sss);					/* 移動 処理 */
} SPELL_aaa_RESOURCE;

extern GAME_COMMAND_FUNC(00_regist_zako)
{
	if (chuu_boss_00_mode_off != cg_BOSS_DATA_32_chuu_boss_mode)
	{
		/* 中-ボスがいる場合には雑魚追加しない。 */
		return;/* error */
	}
	if ((20) < gcmd->user_255_code)
	{
		return;/* error */
	}
	/* 中間コード形式のコマンドから各関数に分岐する */
	/* tekiの生成を番号で管理(load_stage.c の ctype_name[]に対応している) */
	SPELL_aaa_RESOURCE aaa_resource[(20)] =
	{
	/* 魔方陣 */
/*,000,*/		/*(未使用)*/{game_command_regist_zako_000_mahoujin, 		move_zako_00_kougeki_mahoujin}, 	/* "魔方本" /"魔方陣1"	TEKI_RED_BOOK	 MAHOUJIN A */	/* ばらまき攻撃魔方陣 */
/*,001,*/		/*(魔方陣)*/{game_command_regist_zako_000_mahoujin, 		move_zako_00_kougeki_mahoujin}, 	/* "魔方陣" /"魔方陣2"	TEKI_MAHOJIN	 MAHOUJIN B */	/* 消える魔方陣 */
	/* 竜巻 陰陽玉 */
/*,002,*/		{game_command_regist_zako_02_inyou_dama,		move_zako_02_inyou_dama},				/* "陰陽玉" /"陰陽玉1"	TEKI_INYOU_DAI */
/*,003,*/		{game_command_regist_zako_03_tatsumaki, 		move_zako_03_tatsumaki},			/* "竜巻"	/"竜巻1"	TEKI_TATSUMAKI */
	/* 妖怪 */
/*,004,*/		{game_command_regist_zako_04_kakomi,			move_zako_04_kakomi},				/* "囲妖怪" /"囲妖怪1"	TEKI_CHOU1 */
/*,005,*/		{game_command_regist_zako_05_kisume,			move_zako_05_kisume_1st},			/* "キスメ" /"赤毛玉1"	TEKI_CHEN */	/* 橙 */
	/* 毛玉 */
/*,006,*/		{game_command_regist_NULL,						move_zako_06_inseki}, /*(非/回転共用)*/ 		/* "隕石"	/"隕石1"	TEKI_NIJI_HOSI */	/* その他ザコ */
/*,007,*/		{game_command_regist_zako_07_yukari,			move_zako_07_yukari}, /*(回転専用?)*/			/* "紫編隊" /"紫編隊2"	TEKI_NIJI_HOSI */	/* その他ザコ */
/*,008,*/		{game_command_regist_zako_10_hai_kedama,		move_zako_08_ao_kedama},						/* "青毛玉" /"緑毛玉1"	TEKI_AKA_KEDAMA */
/*,009,*/		{game_command_regist_NULL,						move_zako_09_midori_kedama}, /*(回転専用?)*/	/* "緑毛玉" /"緑毛玉2"	TEKI_AKA_KEDAMA */
/*,010,*/		{game_command_regist_zako_10_hai_kedama,		move_zako_10_hai_kedama},	/* "灰毛玉" /"毛玉1"	TEKI_HAI_KEDAMA */
/*,011,*/		{game_command_regist_zako_11_siro_kedama,		move_zako_11_siro_kedama},	/* "白毛玉" /"毛玉2"	TEKI_HAI_KEDAMA */
	/* [C妖精]その他ザコ */
/*,012,*/		{game_command_regist_zako_12_ao_yousei, 		move_zako_12_ao_yousei},	/* "青妖精" /"青妖精2"	TEKI_YOUSEI1_1 */
/*,013,*/		{game_command_regist_zako_13_obake, 			move_zako_13_obake},		/* "おばけ" /"おばけ2"	TEKI_YOUSEI2_5	"虹毛玉1" */
/*,014,*/		{game_command_regist_zako_14_karasu,			move_zako_14_karasu},		/* "烏" 	/"烏1"		TEKI_YOUSEI2_1 */
	/* [B妖精]中妖精 */
/*,015,*/		{game_command_regist_NULL,						move_zako_15_meido1},		/* "メイド1"	TEKI_YOUSEI3_1 */
/*,016,*/		{game_command_regist_NULL,						move_zako_16_meido2},		/* "メイド2"	TEKI_YOUSEI3_1 */
/*,017,*/		{game_command_regist_zako_17_meido3,			move_zako_17_meido3},		/* "メイド3"	TEKI_YOUSEI3_1 */
/*,018,*/		{game_command_regist_NULL,						move_zako_18_meido4},		/* "メイド4"	TEKI_YOUSEI3_1 */
	/* [A妖精]小妖精 */
/*,019,*/		{game_command_regist_NULL,						move_ao_yousei1},			/* "青妖精1"	TEKI_YOUSEI1_1 */
	};
//012廃止{game_command_regist_NULL/*(非/回転共用)*/,	move_zako_06_inseki},				/* "おばけ1"	TEKI_YOUSEI2_5 */
//020廃止{regist_zako_012_ao_yousei,					move_zako_12_ao_yousei},			/* "青妖精2"	TEKI_YOUSEI1_1 */
	//	{regist_zako_014_karasu1,						move_zako_14_karasu},				/* ["烏1"へ吸収]"青妖精3"	TEKI_YOUSEI1_1 */
	//	{game_command_regist_NULL,						move_ao_yousei1},					/* ["青妖精1"へ吸収]"青妖精4"	TEKI_YOUSEI1_1 */ // (r33では未使用)
	OBJ *gcmd_obj;
	gcmd_obj = obj_regist_teki();/*(ザコ敵のobjを新規作成する。)*/
	if (NULL != gcmd_obj)/* 登録できた場合のみ(登録に失敗した場合は、画面内のザコ敵数が多すぎるのでこれ以上登録できない。) */
	{
		// 標準共通登録処理。
		GAME_COMMAND_OBJ_CALL(regist_settei_common);/* 中ボスと共用する必要がある。 */
		gcmd_obj->callback_hit_teki = callback_hit_zako;		/* 「ザコに自弾があたった場合の処理」に、初期値として標準の処理を設定しておく。 */
		//
		gcmd_obj->callback_mover = aaa_resource[ (int)(gcmd->user_255_code) ].aaa_move_callback;	/* 中間コード形式のコマンド番号から移動処理を決める。 */
		(aaa_resource[ (int)(gcmd->user_255_code) ].aaa_init_callback)(gcmd, gcmd_obj); 			/* 中間コード形式のコマンド番号から各関数に分岐する。 */
	}
}
#include "boss_douchu.h"/*(道中の中ボス / ボス)*/
