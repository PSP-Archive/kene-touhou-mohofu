
#include "./../boss/boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	スペル生成システム(カードを生成)
	-------------------------------------------------------
	現状「ボス」以外にも「中ザコ」、「小ザコ」がスペル生成できるので、
	「スペル生成」と「カード管理」は別システムです。
	(現状「中-ボス」は作る予定があるが作ってない。カード履歴システムもまだ作ってない)
	-------------------------------------------------------
    分類        カード履歴      カード  スペル生成
    ボス        ○              ○              ○  // ボス
    中-ボス     ×(?)           ○              ○  // <予定>           (雑魚の流れを「止める」)
    中ザコ      ×              ×              ○  // るーみあ         カードを撃てないのでカード名(符名)は無い。
    小ザコ      ×              ×              ○  // 魔道書ザコ       カードを撃てないのでカード名(符名)は無い。
    ザコ        ×              ×              ×  // その他のザコ     スペル生成出来ない。
    -------------------------------------------------------
    分類            雑魚生成    カード
    ボス専用コア    ×          ○                  // 雑魚生成関連の処理をしないのでその分速い。
    道中専用コア    ○          ×                  // カード管理関連の処理をしないのでその分速い。
	-------------------------------------------------------
	(r33)上記の専用コア計画は廃止。
	今の方式(r33)だとむしろ専用コアにした方が速度低下する。
	-------------------------------------------------------
	レイヤーシステム
	-------------------------------------------------------
	レイヤーシステムは「弾幕」の文字通り、
	弾を単体としては認識せず、幕として認識するシステム。
	-------------------------------------------------------
---------------------------------------------------------*/


/*---------------------------------------------------------
	カードCPUユニット
---------------------------------------------------------*/

#include "spell_card_execute.h"

/*---------------------------------------------------------
	弾源 を obj 中心へ設定する。
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(set_REG_DEST_XY)
{
	VR06	= (src->center.x256);/* 弾源x256 obj中心から発弾。 */
	VR07	= (src->center.y256);/* 弾源y256 obj中心から発弾。 */
}

/*---------------------------------------------------------
	弾源 を ボス obj 中心へ設定する。
---------------------------------------------------------*/

extern void set_REG_DEST_BOSS_XY(void)
{
	VR06	= cg_BOSS_DATA_3a_center_x256;/* 弾源x256 ボス中心から発弾。 */
	VR07	= cg_BOSS_DATA_3b_center_y256;/* 弾源y256 ボス中心から発弾。 */
}

/*---------------------------------------------------------
	カード生成時間(標準?)
---------------------------------------------------------*/

#define SPELL_TIME_0064 	(64)/*SPELL_TIME_001_00sec_04x16_0064*/

#define SPELL_TIME_0100 	(100)
#define SPELL_TIME_0128 	(128)
#define SPELL_TIME_0192 	(192)
#define SPELL_TIME_0256 	(256)
#define SPELL_TIME_0352 	(352)/*(352==32*11)*/

#define SPELL_TIME_0512 	(512)

#define SPELL_TIME_0640 	(640)

#define SPELL_TIME_1024 	(1024)
#define SPELL_TIME_9999 	(16384)
/*
704==768-64;
704== (64発弾時間)+(10x64);
*/
/*---------------------------------------------------------
	カード生成時間(特殊)
---------------------------------------------------------*/

#define RUMIA_TIME_0060 	(60)/*[ルーミア]*/
#define RUMIA_TIME_0416 	(416)/*[ルーミア]*/
//#define CHRNO_TIME_34x16_544 (512+64)
//#define CHRNO_TIME_34x16_544 (640-64)
//#define CHRNO_TIME_34x16_544	(512+32)
#define CHRNO_TIME_0544 (17*32)/*(9.5[sec64]パーフェクトフリーズ)*/

/*---------------------------------------------------------
	スペル難易度別テーブル
	-------------------------------------------------------
	カードスクリプトに移行した場合[initialize section: 初期化セクション]で記述する数字のテーブル。
	-------------------------------------------------------
	[initialize section: 初期化セクション](spell_init)のみ、参照できる。
	[execute section: 発弾セクション](spell_execute)では、参照できない。
---------------------------------------------------------*/


/*---------------------------------------------------------
	カードを生成。
	-------------------------------------------------------
---------------------------------------------------------*/
/* static変数 を調べる作業の為、一時的にlocal にする。 */
#define local static

/* 弾のコールバックセクション */
#define TAMA_FUNC(aaa)		void aaa(OBJ/**/ *src_tama)
/* 実行セクション */
#define SPELL_EXEC(aaa) 	void spell_execute_##aaa(OBJ/**/ *src_boss)
#define BOSS_EXEC(aaa)		void aaa(void)
/* 初期化セクション */
#define SPELL_INIT(aaa) 	void spell_init_##aaa(OBJ/**/ *src_boss)


/*(弾なのかボスなのか中ボスなのか分かりづらくなってきたので、明示する。)*/
//#define src_tama src/*(実は同じ)*/


/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	道中用弾消しコールバック
	弾幕アクション#02
	-------------------------------------------------------
	弾幕の喰み出しチェックを行う(毎フレーム行う必要はない)。
	弾幕が画面外の場合は、弾を消す。
---------------------------------------------------------*/
//global RECT_CLIP_CLASS rect_clip;
local OBJ_CALL_FUNC(hatudan_system_B_side_hansya)/* 弾反射コールバック */
{
	{
		/* [左の壁で反射する] 弾が弾幕設定領域画面より少し(4[pixel])手前の位置に来た場合。 */
		if (0 < (VR1c_bullet_clip_min_x256) + t256(4) - (src->center.x256) )
		{
			goto common_hansya;
		}
		else
		/* [右の壁で反射する] 弾が弾幕設定領域画面より少し(4[pixel])手前の位置に来た場合。 */
		if (0 > (VR1e_bullet_clip_max_x256) - t256(4) - (src->center.x256) )
		{
			goto common_hansya;
		}
		goto done_hansya;/*(反射しない)*/
	common_hansya:/*(反射する可能性あり)*/
		/* 既に反射している場合は反射しないで、弾を消す。 */
		if (0!=(src->TR00_hatudan_spec_data & TAMA_SPEC_KABE_SAYUU_HANSYA_BIT))
		{	/*(反射処理を行わない)*/
			src->jyumyou = JYUMYOU_NASI;/*(弾を消す)*/
		}
		else
	//	if (JYUMYOU_NASI != src->jyumyou)
		{	/*(反射処理を行う)*/
			src->TR00_hatudan_spec_data |= TAMA_SPEC_KABE_SAYUU_HANSYA_BIT;
		//	src->rotationCCW1024 += (1024*3/4);/* -90度回転 */		/* ダメ[※2] */
		//	src->rotationCCW1024 += (1024/4);/* 90度回転 */ 		/* ダメ[※2] */
		//	src->rotationCCW1024 = (1024)-(src->rotationCCW1024);	/* 反転[※1] */
			src->rotationCCW65536 = (65536)-(src->rotationCCW65536);	/* 反転[※1] */
		//	mask1024(src->rotationCCW1024);
			mask65536(src->rotationCCW65536);
			src->TR01_hatudan_speed65536	= ((t256(1.0)<<8));/*(等速)*/
			src->TR02_hatudan_tra65536		= (1);/*(微加速)*/
		}
	done_hansya:/*(反射処理終わり)*/
		;
	}
	/* 上下の場合は弾を消す。 */
	if (
		(0 < (VR1d_bullet_clip_min_y256) - (src->center.y256) )||
		(0 > (VR1f_bullet_clip_max_y256) - (src->center.y256) )
	)
	{
		src->jyumyou = JYUMYOU_NASI;
	}
}


/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	道中用弾消しコールバック
	弾幕アクション#00
	-------------------------------------------------------
	弾幕の喰み出しチェックを行う(毎フレーム行う必要はない)。
	弾幕が画面外の場合は、弾を消す。
---------------------------------------------------------*/
local OBJ_CALL_FUNC(hatudan_system_B_gamen_gai_tama_kesu)/* 画面外弾消しコールバック */
{
	/* 画面外の場合は弾を消す。 */
	if (
	(0 < (VR1c_bullet_clip_min_x256)-(src->center.x256) ) ||
	(0 > (VR1e_bullet_clip_max_x256)-(src->center.x256) ) ||
	(0 < (VR1d_bullet_clip_min_y256)-(src->center.y256) ) ||
	(0 > (VR1f_bullet_clip_max_y256)-(src->center.y256) ) )
	{
		src->jyumyou = JYUMYOU_NASI;
	}
}

/*(この辺は廃止してスペカCPUのスクリプトで直接書けば良い)*/
//enum
//{
//	CLIP_RECT_TYPE_00_NORMAL =0,
//	CLIP_RECT_TYPE_01_UE_YOKO,
//	CLIP_RECT_TYPE_02_UE_ONLY,
//	CLIP_RECT_TYPE_03_UE_WIDE,
//	CLIP_RECT_TYPE_99_MAX,
//};

/*---------------------------------------------------------
	弾の範囲を「標準」に設定
	標準タイプ
	-------------------------------------------------------
	set_default_bullet_clip
---------------------------------------------------------*/
#define CLIP_RECT_00_VR1c			(((GAME_X_OFFSET))<<8)						/*(右は標準範囲)*/
#define CLIP_RECT_00_VR1d			(((-32))<<8)								/*(上は標準範囲)*/
#define CLIP_RECT_00_VR1e			(((GAME_X_OFFSET) + (GAME_320_WIDTH))<<8)	/*(左は標準範囲)*/
#define CLIP_RECT_00_VR1f			(((GAME_HEIGHT))<<8)						/*(下は標準範囲)*/

/*---------------------------------------------------------
	弾の範囲を「上と横の広範囲」に設定
	上に広いタイプ
	-------------------------------------------------------
	set_aya_bullet_clip
---------------------------------------------------------*/
#define CLIP_RECT_01_VR1c					(((GAME_X_OFFSET) + t256(-100))<<8) 		/*(右は広範囲)*/
#define CLIP_RECT_01_VR1d					(((-256))<<8)								/*(上は広範囲)*/		/* あや */
#define CLIP_RECT_01_VR1e					(((GAME_X_OFFSET) + (GAME_320_WIDTH) + ( 100))<<8)/*(左は広範囲)*/
//標準範囲#define CLIP_RECT_01_VR1f 		/*(下は標準範囲)*/

/*---------------------------------------------------------
	弾の範囲を「上だけ広いタイプ」に設定
	上だけ広いタイプ
	-------------------------------------------------------
	set_cirno_bullet_clip
---------------------------------------------------------*/
//標準範囲#define CLIP_RECT_02_VR1c 		/*(右は標準範囲)*/
#define CLIP_RECT_02_VR1d					(((-256))<<8)			/*(上は広範囲)*/	/*(てすとチルノ)*/
//標準範囲#define CLIP_RECT_02_VR1e 		/*(左は標準範囲)*/
//標準範囲#define CLIP_RECT_02_VR1f 		/*(下は標準範囲)*/

/*---------------------------------------------------------
	弾の範囲を「上と横の広範囲」に設定
	上にもっと広いタイプ
	-------------------------------------------------------
	set_aya_bullet_clip
---------------------------------------------------------*/
//標準範囲#define CLIP_RECT_03_VR1c 		/*(右は標準範囲)*/
#define CLIP_RECT_03_VR1d					(((-512))<<8)			/*(上はもっと広範囲)*/		/* あやややや */
//標準範囲#define CLIP_RECT_03_VR1e 		/*(左は標準範囲)*/
//標準範囲#define CLIP_RECT_03_VR1f 		/*(下は標準範囲)*/

/*---------------------------------------------------------
	-------------------------------------------------------

---------------------------------------------------------*/
	/* 標準タイプ */		/* 弾の範囲を標準に設定 */ /*(弾の有効範囲を標準==見える範囲のみ有効に設定)*/
//local void set_default_bullet_clip(void)/* call from load_stage.c */

#define CLIP_BOSS_00_VR3c			(t256(GAME_X_OFFSET)+t256(			0)+t256(24))		/*(右の範囲)*/
#define CLIP_BOSS_00_VR3d			(t256(0))												/*(上の範囲)*/
#define CLIP_BOSS_00_VR3e			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24)) 	/*(左の範囲)*/
//efine CLIP_BOSS_00_VR3f			(96<<8) 												/*(下の範囲)*/

 // #01狭いタイプ。
//local void set_default_boss_clip(void)/* call from boss_card.c */
#define CLIP_BOSS_01_VR3c			(t256(GAME_X_OFFSET)+t256(			0)+t256(24)+t256(64))		/*(右の範囲)*/
#define CLIP_BOSS_01_VR3e			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24)-t256(64))	/*(左の範囲)*/


/*---------------------------------------------------------
	外部インターフェイス。
	-------------------------------------------------------
	道中用の、弾の範囲を「標準」に設定。(from load_stage.c)
---------------------------------------------------------*/

/*---------------------------------------------------------
	カードを生成。
	-------------------------------------------------------
---------------------------------------------------------*/

extern void set_tukaima_start(void);
//
#include "spell_00_common.h"
//
#include "spell_00_zako.h"
#include "spell_00_sonota.h"
//
#include "spell_01_mima.h"
#include "spell_01_alice.h"
#include "spell_01_rumia.h"
#include "spell_01_meirin.h"
#include "spell_01_chrno.h"
#include "spell_01_kaguya.h"
#include "spell_01_daiyousei.h"
#include "spell_01_aya.h"
#include "spell_01_momiji.h"

//
#include "spell_01_pache.h"
#include "spell_01_sakuya.h"
#include "spell_01_remilia.h"

//
#include "spell_01_ruiz.h"


/*---------------------------------------------------------
	共通カード生成部
	-------------------------------------------------------
	カードごとに予め生成時間が登録してある。
---------------------------------------------------------*/
enum
{
	TAMA_MAP_06_KOUMA	= 0,	/* 紅魔郷/妖々夢(ナイフ弾/炎弾) */
	TAMA_MAP_08_EIYA,			/* 永夜抄/風神禄(札弾/星弾) */
	TAMA_MAP_10_TIREI,			/* 地霊殿/花映塚(ハート弾/銭弾) */
};

#if (1==LINK_DUAL_SYSTEM)
enum//(デバッグ用あとで)
{
	RUN_00_CARD_INTERPRETER 	= 0,	/* カードインタプリタ。 */
	RUN_01_C_LANGUAGE,					/* C言語(廃止予定)。(C言語を全て廃止できれば、実行速度が向上する※1) */
};
#else
	#define RUN_00_CARD_INTERPRETER /**/
	#define RUN_01_C_LANGUAGE /**/
#endif /*(LINK_DUAL_SYSTEM)*/

typedef struct
{
	void (*spell_execute_section)(OBJ/**/ *sss);		/* [executes section: スペル実行セクション]発弾(弾生成)処理 */
	void (*spell_initialze_section)(OBJ/**/ *sss);		/* [initialize section: スペル初期化セクション]スペル初期化処理 */
	//
	void (*layer_callback_preset[(DANMAKU_LAYER_04_MAX)])(OBJ/**/ *src_tama);
	//
	u16 spell_limit_max_time;							/* カード寿命時間 */						/* カードスクリプトに移行した場合、本来[initialize section: 初期化セクション]内で行う。 */
	u8 tama_map;										/* 弾画像のマップ番号 */					/* カードスクリプトに移行した場合、本来[initialize section: 初期化セクション]内で行う。 */
//	u8 dummy_clip_type_haisi;
//	#if (1==LINK_DUAL_SYSTEM)
	u8 scr_ipt_run_flag;								/* (デバッグ用あとで)実行言語(カードインタプリタ / C言語) */
//	#endif /*(LINK_DUAL_SYSTEM)*/
} SPELL_RESOURCE;

//	/*const*/ static void (*spell_execute_bbb[(SPELL_MAX/*16+1*/)])(OBJ/**/ *sss) =
	/*const*/ static SPELL_RESOURCE system_spell_resource[(SPELL_MAX/*16+1*/)] =
{
/* 02 02 */ //{ spell_execute_02_24nerai,						NULL,									{standard_angle_mover_00_callback, NULL,							NULL,							NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 02 */	/* [咲夜] 紅5面中-ボス 24カード (奇術「ミスディレクションもどき(1/2)」) */
/* 03 03 */ //{ spell_execute_03_11nife,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 03 */	/* [咲夜] 紅5面中-ボス 11カード (奇術「ミスディレクションもどき(2/2)」) */

	#define spell_execute_99_mitei spell_execute_08_rumia_night_bird
	#define spell_execute_40_meirin_kasou_yume_kazura spell_execute_99_mitei
/* 00 00 */ {NULL,												NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 00 */	/* カード生成しない */
			// 0x00- 中ザコ / ボス共用カード
/* 01 01 */ {spell_execute_01_sakuya_misogi_normal, 			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 01 */	/* [咲夜] 紅5面中-ボス 「通常攻撃1」咲夜禊カード */
/* 02 02 */ {spell_execute_99_mitei,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 02 */	/* [雑魚] (未使用) */
/* 03 03 */ {spell_execute_03_lumia02_douchuu,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	RUMIA_TIME_0060, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 03 */	/* [ルーミア] (道中) */
/* 04 04 */ {spell_execute_04_pink_hearts,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 04 */	/* [咲夜] 紅5面ボス 「通常攻撃1(1/2)」にちょっとだけ似たカード(予定) SPELL_TIME_0128(r32) */
/* 05 05 */ {spell_execute_05_32way_dual,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 05 */	/* [咲夜] 紅5面ボス 「通常攻撃1/2(2/2)」にちょっとだけ似たカード(予定) */
/* 06 06 */ {spell_execute_06_luna_clock_32way, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 06 */	/* [咲夜] 紅5面ボス 幻象「ルナクロック(1/2)」にちょっとだけ似たカード(予定) */
/* 07 07 */ {spell_execute_07_80way_dual_five,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 07 */	/* [咲夜] 紅5面ボス 「通常攻撃3(1/2)」にちょっとだけ似たカード(予定) */
			// 0x08- 中ザコ / ボス共用カード
/* 08 08 */ {spell_execute_08_rumia_night_bird, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	RUMIA_TIME_0416, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 08 */	/* [ルーミア] 紅1面ボス 夜符「ナイトバード」にちょっとだけ似たカード(予定) */
/* 09 09 */ {spell_execute_09_test_inuno_fuguri,				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 09 */	/* [雑魚] 洗濯機カード(とりあえずカードシステム作成の実験で作ってみた奴) */
/* 10 0a */ {spell_execute_1a_1b_dai_yousei_midori_aka, 		spell_init_1a_dai_yousei_midori,		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1a */	/* [大妖精] 緑巻き */
/* 11 0b */ {spell_execute_1a_1b_dai_yousei_midori_aka, 		spell_init_1b_dai_yousei_aka,			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1b */	/* [大妖精] 赤巻き */
/* 12 0c */ {spell_execute_14_sakuya_jack_oodama32, 			spell_init_14_sakuya_jack_oodama32, 	{standard_angle_mover_00_callback, sakuya_danmaku_01_callback,		sakuya_danmaku_02_callback, 	NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 14 */	/* [咲夜] 幻幽「ジャック・ザ・ルドビレ」になるかもしれないテスト */
/* 40 28 */ {spell_execute_0d_dai_yousei_9_shot,				NULL,									{standard_angle_mover_00_callback, dai_yousei_danmaku_01_callback,	NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [大妖精] 9shot */
/* 14 0e */ {spell_execute_1f_remilia_kougeki2, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1f */	/* [レミリア] 通常攻撃2 っぽいもの */
/* 15 0f */ {spell_execute_11_tengu_shot,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 11 */	/* [天狗様] 差分氏の妖怪1(天狗様?)が撃つカード */
			// 0x10- 中ザコ / ボス共用カード
/* 16 10 */ {spell_execute_10_cirno_misogi, 					spell_init_10_cirno_misogi, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 10 */	/* [チルノ] 紅2面ボス チルノ禊カード */
/* 17 11 */ {spell_execute_13_perfect_freeze,					NULL,									{standard_angle_mover_00_callback, cirno_danmaku_01_callback,		NULL, NULL},
																																								CHRNO_TIME_0544, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 13 */	/* [チルノ] 紅2面ボス パーフェクトフリーズ */
/* 18 12 */ {spell_execute_16_diamond_blizzard, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 16 */	/* [チルノ] 紅2面ボス 雪符「ダイアモンドブリザード」 */
/* 19 13 */ {spell_execute_25_alice_suwako, 					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 25 */	/* [アリス] アリス	諏訪子っぽい(?)カード */
/* 20 14 */ {spell_execute_17_alice_nejiri10sec,/*(r39)*/		spell_init_17_alice_nejiri10sec,		{standard_angle_mover_00_callback, alice_aaa_danmaku_01_callback,	NULL, NULL},
																																								SPELL_TIME_0192, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 17 */	/* [アリス] 通常攻撃(もどき) ねじり弾10秒 SPELL_TIME_0640 */
/* 21 15 */ {spell_execute_0e_aka_2nd,							spell_init_0e_aka_2nd,					{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_1024, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0e */	/* [アリス] 怪EX面ボス 赤の魔法2段階目もどき */
/* 22 16 */ {spell_execute_0b_alice_zako_doll,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0b */	/* [アリス] SPELL_TIME_0128 妖3面ボス 人形カード(もどき)(256>240=4x60) */
/* 23 17 */ {spell_execute_1e_alice_tama_doll,					NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1e */	/* [アリス] 妖3面ボス 人形カード(もどき)(256>240=4x60) 蒼符「博愛の仏蘭西人形」 */
			// 0x18- 中ザコ / ボス共用カード
/* 24 18 */ {spell_execute_0c_hana_test,						NULL,									{standard_angle_mover_00_callback, mima_danmaku_01_callback,		NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0c */	/* [魅魔] 花てすとカード */
/* 64 40 */ //{spell_execute_20_sonota_debug_cw_ao, 			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 40 */	/* [その他] デバッグカードCW青 */
/* 65 41 */ //{spell_execute_21_sonota_debug_ccw_aka,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 41 */	/* [その他] デバッグカードCCW赤 */
/* 64 40 */ {spell_execute_19_meirin_5_houkou,					spell_init_19_meirin_5_houkou,			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 40 */	/* [紅美鈴] 幻符「華想夢葛」 */
/* 65 41 */ {spell_execute_40_meirin_kasou_yume_kazura, 		NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 41 */	/* [紅美鈴] 虹符「彩虹の風鈴」 */
/* 27 1b */ {spell_execute_1b_cirno_icecle_fall,				spell_init_1b_cirno_icecle_fall,		{standard_angle_mover_00_callback, cirno_icecle_fall_01_callback,	NULL, NULL},
																																								SPELL_TIME_0352, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [チルノ] 氷符「アイシクルフォール」 */
/* 68 44 */ {spell_execute_44_ruiz3,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 44 */	/* [ルイズ] 左右白カード */
/* 29 1d */ {spell_execute_1d_amefuri_test, 					spell_init_1d_amefuri_test, 			{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/							NULL,							NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [(文、仮)] 雨てすと */
/* 30 1e */ {spell_execute_1e_momiji_no_nonoji, 				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [椛] ののじカード */
/* 31 1f */ {spell_execute_1f_koakuma,							NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [パチェ] サイレントセレナ の てすと用 */
			// 0x20- ボス専用カード
/* 32 20 */ {spell_execute_15_aya_misogi1,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 15 */	/* [文] の通常弾っぽいカード撃たせてみるテスト1 */
/* 33 21 */ {spell_execute_23_aya_misogi2,						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 23 */	/* [文]の通常弾っぽいカード撃たせてみるテスト2 */
/* 34 22 */ {spell_execute_22_aya_yatimata, 					spell_init_22_aya_yatimata, 			{standard_angle_mover_00_callback, aya_danmaku_01_callback, 		NULL,							NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 22 */	/* [文] 岐符「天の八衢」 */
/* 35 23 */ {spell_execute_12_meirin_magaru_kunai,				spell_init_12_meirin_magaru_kunai,		{standard_angle_mover_00_callback, common_01_amefuri_callback,		meirin_02_aka_ao_kunai_callback, meirin_03_aka_ao_kunai_time256_callback},/*(赤青クナイ用2)*/
																																																					SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 12 */	/* [美鈴] 紅3面中ボス 「通常攻撃」の曲がるクナイ。 */
/* 36 24 */ {spell_execute_0f_aya_doll, 						NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0f */	/* [文] 人形カード(てすとカード「危険な種」) */
/* 37 25 */ {spell_execute_0a_houka_kenran, 					spell_init_0a_houka_kenran, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0a */	/* [紅美鈴] 紅3面ボス 華符「芳華絢爛」にちょっとだけ似たカード(予定) */
/* 38 26 */ {spell_execute_26_aya_saifu,						spell_init_26_aya_saifu,				{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [文] 塞符 */
/* 39 27 */ {spell_execute_27_hosigata_test,					spell_init_27_hosigata_test,			{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/							move_bullet_sakuya_hosi_gata_callback,/*(星型用。)*/	/*(未使用)*/NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 27 */	/* [その他] 星型テスト */
			// 0x28- ボス専用カード
/* 13 0d */ {spell_execute_28_sakuya_miss_direction,			spell_init_28_sakuya_miss_direction,	{standard_angle_mover_00_callback, danmaku_01_standard_angle_sayuu_hansya_mover,	NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1c */	/* [咲夜] 奇術「ミスディレクション」 */
/* 41 29 */ {spell_execute_29_rumia_demarcation,				spell_init_29_rumia_demarcation,		{standard_angle_mover_00_callback, rumia_danmaku_01_callback,		rumia_danmaku_02_callback,	NULL},	SPELL_TIME_0512, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 31 */	/* [ルーミア] 紅1面ボス 闇符「ディマーケイション」にちょっとだけ似たカード(予定) dimmercation / demarcation 境界 */
	//
	#if 0
	//[プロセス登録] スクリプト化した場合に必要な処理。
	regist_process(0, spell_execute_29_rumia_demarcation);	// [execute section: 発弾セクション]プログラム実行開始番地登録
	regist_process(1, rumia_danmaku_01_callback);			// [callback t01 section: 弾幕レイヤーグループ(1)セクション]プログラム実行開始番地登録
	regist_process(2, rumia_danmaku_02_callback);			// [callback t02 section: 弾幕レイヤーグループ(2)セクション]プログラム実行開始番地登録
	#endif


/* 42 2a */ {spell_execute_2a_sakuya_baramaki1, 				spell_init_2a_sakuya_baramaki1, 		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [咲夜] 紅5面中-ボス ばら撒き1 カード () */
/* 43 2b */ {spell_execute_2b_sakuya_baramaki2, 				spell_init_2b_sakuya_baramaki2, 		{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [咲夜] 紅5面中-ボス ばら撒き2 カード () */
/* 44 2c */ {spell_execute_2c_sakuya_blue_red_knife,			NULL,									{standard_angle_mover_00_callback, danmaku_01_standard_angle_sayuu_hansya_mover,/*(通常弾用)*/ /*(画面外なら反射減速)*/ /*(未使用)*/NULL, NULL},
																																								SPELL_TIME_0512, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 26 */	/* [咲夜] 紅5面中-ボス 「通常攻撃3」青赤ナイフ */
/* 45 2d */ {spell_execute_2d_sakuya_misogi_lunatic,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 01 */	/* [咲夜] 紅5面中-ボス 「通常攻撃1」咲夜禊カード(lunatic only) */
// ==================================== [スペカ境界] ==================================== //
/* 46 2e */ {spell_execute_2e_pache_agni_shine_1,				spell_init_2e_pache_agni_shine_1,		{standard_angle_mover_00_callback,	agnishine_danmaku_01_callback,/*(アグニシャイン用)*/ /*(未使用)*/NULL, NULL},
																																								SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 2e */	/* [パチェ] "　　　　火符「アグニシャイン」" No.15 */	// (火がいっぱいだから) (輝く)アグニ(インド神話の火の神)
/* 47 2f */ {spell_execute_2f_pache_princess_undine,			NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 2f */	/* [パチェ] "　水符「プリンセスウンディネ」" No.16 */	// (水がいっぱいだから) 「妖精の書(著者:錬金術師パラケルスス)」に登場する水の精。
			// 0x30- ボス専用カード
/* 48 30 */ {spell_execute_30_pache_sylphy_horn_1,				spell_init_30_pache_sylphy_horn_000,	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(シルフィホルン用)*/ /*(未使用)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */ /* [パチェ] "　　　　木符「シルフィホルン」" No.17 */	// (木がいっぱいだから) (風を司る精霊の)角笛
/* 49 31 */ {spell_execute_31_pache_rage_tririton_1,			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(枠付き丸弾。交差弾。? 回り。)*/ /*(未使用)*/NULL, NULL},				SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 31 */ /* [パチェ] "　　土符「レイジィトリリトン」" No.18 */	// (土がいっぱいだから) (怒る)トリリトン(ストーンヘンジ)
/* 50 32 */ {spell_execute_32_pache_metal_fatigue,				NULL,									{standard_angle_mover_00_callback, pache_mt1_danmaku_01_callback,/*(黄色 大玉弾。)*/	/*(未使用)*/NULL, NULL},							SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 32 */ /* [パチェ] "　　金符「メタルファティーグ」" No.19 */	// (金(金属)がいっぱいだから) 金属疲労
/* 51 33 */ {spell_execute_33_pache_agni_shine_2,				spell_init_33_pache_agni_shine_2,		{standard_angle_mover_00_callback, agnishine_danmaku_01_callback,/*(アグニシャイン用)*/ /*(未使用)*/NULL, NULL},							SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 33 */ /* [パチェ] "　　火符「アグニシャイン上級」" No.20 */	// (火がいっぱいだから) (輝く)アグニ(インド神話の火の神)
/* 52 34 */ {spell_execute_34_pache_sylphy_horn_2,		/*共用*/spell_init_30_pache_sylphy_horn_000,  	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(シルフィホルン用)*/ /*(未使用)*/NULL, NULL},																					SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 34 */ /* [パチェ] "　　木符「シルフィホルン上級」" No.21 */	// (木がいっぱいだから) (風を司る精霊の)角笛
/* 53 35 */ {spell_execute_35_pache_rage_tririton_2,			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(枠付き丸弾。交差弾。? 回り。)*/ /*(未使用)*/NULL, NULL},				SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 35 */ /* [パチェ] "土符「レイジィトリリトン上級」" No.22 */	// (土がいっぱいだから) (怒る)トリリトン(ストーンヘンジ)
/* 54 36 */ {spell_execute_36_pache_agni_radiance,/* _agni_shine_3 */ NULL, 							{standard_angle_mover_00_callback, agnishine_danmaku_01_callback/*(アグニシャイン用)*/, /*(未使用)*/NULL, NULL},																						SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 36 */ /* [パチェ] "　火符「アグニレイディアンス」" No.23 */	// (火がいっぱいいっぱいだから) アグニ(インド神話の火の神)
/* 55 37 */ {spell_execute_37_pache_bury_in_lake,				NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 37 */ /* [パチェ] "　　　水符「ベリーインレイク」" No.24 */	// (水がいっぱいいっぱいだから)  湖に埋める(水葬)
			// 0x38- ボス専用カード
/* 56 38 */ {spell_execute_38_pache_green_storm,/*sh_3 共用*/	spell_init_30_pache_sylphy_horn_000, 	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(シルフィホルン)*/ /*(未使用)*/NULL, NULL},																				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 38 */ /* [パチェ] "　　　木符「グリーンストーム」" No.25 */	// (木がいっぱいいっぱいだから) 緑の嵐
/* 57 39 */ {spell_execute_39_pache_tririton_shake, 			NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(枠付き丸弾。交差弾。? 回り。)*/ /*(未使用)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 39 */ /* [パチェ] "　　土符「トリリトンシェイク」" No.26 */	// (土がいっぱいいっぱいだから) (揺れる)トリリトン(ストーンヘンジ)
/* 58 3a */ {spell_execute_3a_pache_silver_dragon,				NULL,									{standard_angle_mover_00_callback, pache_mt2_danmaku_01_callback,/*(白弾。)*/ /*(未使用)*/NULL, NULL},										SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3a */ /* [パチェ] "　　　金符「シルバードラゴン」" No.27 */	// (金(かね)がいっぱいいっぱいだから) 「金と銀(著者:福山)」
/* 59 3b */ {spell_execute_3b_pache_lava_cromlech,				NULL,									{standard_angle_mover_00_callback, pache_rt1_danmaku_01_callback,/*(枠付き丸弾。交差弾。? 回り。)*/ /*(未使用)*/NULL, NULL},				SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3b */ /* [パチェ] "火＆土符「ラーヴァクロムレク」" No.28 */	// (火＋土＝溶岩) 環状列石(ストーンヘンジ)
/* 60 3c */ {spell_execute_3c_pache_forest_blaze,				spell_init_30_pache_sylphy_horn_000,	{standard_angle_mover_00_callback, pache_sh1_danmaku_01_callback,/*(シルフィホルン)*/ /*(未使用)*/NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3c */ /* [パチェ] "木＆火符「フォレストブレイズ」" No.29 */	// (木＋火＝)森林火災
/* 61 3d */ {spell_execute_3d_pache_water_elf,					spell_init_3d_pache_water_elf,			{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0100, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3d */ /* [パチェ] "　水＆木符「ウォーターエルフ」" No.30 */	// (水＋木＝)水溶性(水妖精)
/* 62 3e */ {spell_execute_3e_pache_mercury_poison, 			spell_init_3e_pache_mercury_poison,		{standard_angle_mover_00_callback, pache_mp1_danmaku_01_callback,/*(枠付き丸弾。交差弾。反時計回り/時計回り。)*/ /*(未使用)*/NULL, NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3e */ /* [パチェ] "金＆水符「マーキュリポイズン」" No.31 */	// (金(金属)＋水＝)水銀中毒
/* 63 3f */ {spell_execute_3f_pache_emerald_megalith,			spell_init_3f_pache_emerald_megalith,	{standard_angle_mover_00_callback, NULL, NULL, NULL},																						SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 3f */ /* [パチェ] "土＆金符「エメラルドメガリス」" No.32 */	// (土＋金(かね)＝)エメラルドの巨石
// ==================================== [スペカ境界] ==================================== //
			// 0x40
/* 66 42 */ /*40*/	{spell_execute_40_pache_laser1, 			spell_init_40_pache_laser1, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 42 */	/* [パチェ] 通常攻撃(もどき) のレーザーもどき */
/* 67 43 */ /*41*/	{spell_execute_41_pache_laser2, 			spell_init_41_pache_laser2, 			{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 43 */	/* [パチェ] 通常攻撃(もどき) のレーザーもどき */
/* 4e 4e */ /*4e*/	{spell_execute_42_remilia_vlad_tepes,		spell_init_42_remilia_vlad_tepes,		{standard_angle_mover_00_callback, brp_tamaoki_danmaku_01_callback,/*(珠置き用)*/	remilia_tahane_danmaku_02_callback,/*(珠跳ね用)*/ /*(未使用)*/NULL},		SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [咲夜/レミリア] 紅6面ボス 呪詛「ブラド・ツェペシュの呪い」 */
/* 4f 4f */ /*4f*/	{spell_execute_43_remilia_red_magic,		spell_init_43_remilia_red_magic,		{standard_angle_mover_00_callback, red_magic_tamaoki_danmaku_01_callback,/*(珠置き用)*/	remilia_tahane_danmaku_02_callback,/*(珠跳ね用)*/ /*(未使用)*/NULL},	SPELL_TIME_0192, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4f */	/* [咲夜/レミリア] 紅6面ボス 「レッドマジック」 */
/* 4d 4d */ /*4d*/	{spell_execute_44_remilia_rasen_knife,		NULL,									{standard_angle_mover_00_callback, NULL, NULL, NULL},																											SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4d */	/* [咲夜/レミリア] 紅6面ボス 通常攻撃  */
/* 71 47 */ /*47*/	{spell_execute_45_sakuya_festival_knife,	spell_init_45_sakuya_festival_knife,	{standard_angle_mover_00_callback, sakuya_ryoute_knife_danmaku_01_callback,/*(左右親ナイフ。)*/	sakuya_hajikeru_knife_danmaku_02_callback,/*(弾けるナイフ。)*/	sakuya_kurukuru_knife_danmaku_03_callback},/*(くるくるナイフ。)*/
																																																SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 47 */	/* [咲夜] 幻想「フェスティバルナイフ」(?) むりやり変換 */
/* 25 19 */ /*42*/	{spell_execute_46_mima_sekkin,				NULL, 			 						{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/ NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 0d */	/* [魅魔] 接近カード */
/* 26 1a */ /*43*/	{spell_execute_47_mima_toge,				spell_init_47_mima_toge, 				{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/ NULL, NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 24 */	/* [魅魔] トゲカード */
					// 0x48
/* 49 49 */ /*49*/	{spell_execute_48_kaguya000,				spell_init_kaguya000, /*(特殊)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 18 */	/* [輝夜] とりあえず強引に変換000 */
/* 69 45 */ /*44*/	{spell_execute_48_kaguya000,				spell_init_kaguya111, /*(特殊)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 18 */	/* [輝夜] とりあえず強引に変換111 */
/* 70 46 */ /*45*/	{spell_execute_4a_kaguya222,				spell_init_kaguya222, /*(特殊)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 19 */	/* [輝夜] とりあえず強引に変換222 */
/* 28 1c */ /*46*/	{spell_execute_4b_kaguya333_tamanoe,		spell_init_kaguya333, /*(特殊)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/								NULL,									NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [輝夜] 蓬莱の玉の枝もどき */
/* 4c 4c */ /*4c*/	{spell_execute_4b_kaguya333_tamanoe,		spell_init_kaguya444, /*(特殊)*/		{standard_angle_mover_00_callback, common_01_amefuri_callback,/*(雨用)*/								NULL,									NULL},	SPELL_TIME_0640, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 1d */	/* [輝夜] 蓬莱の玉の枝もどき */
/* 4a 4a */ /*4a*/	{spell_execute_4d_rumia_3nerai, 			NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0064, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4a */	/* [ルーミア] */
/* 4b 4b */ /*4b*/	{spell_execute_99_mitei,					NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 4b */	/* [] */
/* 48 48 */ /*48*/	{spell_execute_48_aya_taifu,				NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 48 */	/* [r34]r34以前の互換機能。(r35-)システムで必ず必要。 */
//
/* 50 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */
/* 51 */ {spell_execute_51_kaguya_tujyou_kougeki_01,			spell_init_51_kaguya_tujyou_kougeki_01, {standard_angle_mover_00_callback, kaguya_tujyou_kougeki_01_wait_callback,/*(珠置き用)*/	NULL,				NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 通常攻撃1
/* 52 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 難題「龍の頸の玉　-五色の弾丸-」
/* 53 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 神宝「ブリリアントドラゴンバレッタ」
/* 54 */ {spell_execute_54_kaguya_tujyou_kougeki_02,			spell_init_54_kaguya_tujyou_kougeki_02, {standard_angle_mover_00_callback, kaguya_tujyou_kougeki_02_wait_callback,/*(珠置き用)*/	NULL,				NULL},	SPELL_TIME_0256, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 通常攻撃2,
/* 55 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 難題「仏の御石の鉢　-砕けぬ意志-」,
/* 56 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 神宝「ブディストダイアモンド」
/* 57 */ {spell_execute_57_kaguya_tujyou_kougeki_03,			spell_init_57_kaguya_tujyou_kougeki_03, {standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_9999, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 通常攻撃3,
//
/* 58 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 難題「火鼠の皮衣　-焦れぬ心-」,
/* 59 */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 神宝「サラマンダーシールド」
/* 5a */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 通常攻撃4,
/* 5b */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 難題「燕の子安貝　-永命線-」
/* 5c */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 神宝「ライフスプリングインフィニティ」
/* 5d */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 難題「蓬莱の玉の枝　-虹色の弾幕-」
/* 5e */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 神宝「蓬莱の玉の枝　-夢色の郷-」
/* 5f */ {spell_execute_99_mitei,								NULL,									{standard_angle_mover_00_callback, NULL,								NULL,									NULL},	SPELL_TIME_0128, TAMA_MAP_06_KOUMA, RUN_01_C_LANGUAGE}, /* 30 */	/* [] */	// 「永夜返し　‐夜明け‐」（N）
};
#if 0
/*50*/	SPELL_50_,
/*51*/	SPELL_51_kaguya_tujyou_kougeki_01,			// 通常攻撃1
/*52*/	SPELL_52_kaguya_tatu_no_kubi_no_tama,		// 難題「龍の頸の玉　-五色の弾丸-」
/*53*/	SPELL_53_kaguya_brilliant_dragon_bullet,	// 神宝「ブリリアントドラゴンバレッタ」
/*54*/	SPELL_54_kaguya_tujyou_kougeki_02,			// 通常攻撃2,
/*55*/	SPELL_55_kaguya_hotoke_no_oisi_no_hati, 	// 難題「仏の御石の鉢　-砕けぬ意志-」,
/*56*/	SPELL_56_kaguya_bdist_diamond,				// 神宝「ブディストダイアモンド」
/*57*/	SPELL_57_kaguya_tujyou_kougeki_03,			// 通常攻撃3,
		//
/*58*/	SPELL_58_kaguya_hi_nezumi_no_kawa_goromo,	// 難題「火鼠の皮衣　-焦れぬ心-」,
/*59*/	SPELL_59_kaguya_salamnder_shiled,			// 神宝「サラマンダーシールド」
/*5a*/	SPELL_5a_kaguya_tujyou_kougeki_04,			// 通常攻撃4,
/*5b*/	SPELL_5b_kaguya_tubame_no_koyasugai,		// 難題「燕の子安貝　-永命線-」
/*5c*/	SPELL_5c_kaguya_life_spring_infinity,		// 神宝「ライフスプリングインフィニティ」
/*5d*/	SPELL_5d_kaguya_hourai_no_tama_no_eda01,	// 難題「蓬莱の玉の枝　-虹色の弾幕-」
/*5e*/	SPELL_5e_kaguya_hourai_no_tama_no_eda02,	// 神宝「蓬莱の玉の枝　-夢色の郷-」
/*5f*/	SPELL_5f_kaguya_eiya_gaesi_yoake,			// 「永夜返し　‐夜明け‐」（N）
#endif

/*---------------------------------------------------------
	道中ザコ/ボス/道中中ボス、スペルCPU初期化	[共通部分]。
---------------------------------------------------------*/

extern void spell_cpu_common_reset(void)
{
	#if (1==USE_BOSS_JIKANGIRE)/*(使用予定あり。未検証)*/
	cg_state_flag &= (~JIKI_FLAG_16_0x8000_BOSS_JIKAN_GIRE);/*(時間切れフラグoff)*/
	#endif
	/* カードレジスタ全初期化 */
	static const u32 codebase_init[18] =
	{
		// (01)
		MCODE(OP0x0f_CLEAR_ZERO_PAGE, NAX, NAX, NAX),
		//---- set_default_bullet_clip();	/* 弾の範囲を標準に設定 */	//	/*(実質道中/ザコ/道中中ボス用初期化)*/
	// (CLIP_RECT_TYPE_00_NORMAL);
		// (02)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// 右の範囲を設定する。
		CLIP_RECT_00_VR1c,// 標準タイプ
		// (03)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上の範囲を設定する。
		CLIP_RECT_00_VR1d,// 標準タイプ
		// (04)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// 左の範囲を設定する。
		CLIP_RECT_00_VR1e,// 標準タイプ
		// (05)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1f_bullet_clip_max_y256, NAX),// 下の範囲を設定する。
		CLIP_RECT_00_VR1f,// 標準タイプ
	//----
	//	VR3f_boss_clip_max_y256 = ((boss_clip_y_pixel[((cg_VR20_game_difficulty)&3)])<<8);/*t256()*/
	//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((64), (80), (96), (96));/*[boss_clip_y_pixel]*/
	//	CPU_CA LL(nan_ido);
	/* boss_rect_init */
		//---- set_default_boss_clip();/*(ボスの範囲もリセットする)*/
		/*(ボス本体の移動範囲を制限する。)*/
		// (06) VR3c_boss_clip_min_x256 = t256(GAME_X_OFFSET)+t256( 			0)+t256(24);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3c_boss_clip_min_x256, NAX),// 右の範囲を設定する。
		CLIP_BOSS_00_VR3c,
		// (07) VR3d_boss_clip_min_y256 = t256(0);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3d_boss_clip_min_y256, NAX),// 上の範囲を設定する。
		CLIP_BOSS_00_VR3d,
		// (08) VR3e_boss_clip_max_x256 = t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH)-t256(24);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3e_boss_clip_max_x256, NAX),// 左の範囲を設定する。
		CLIP_BOSS_00_VR3e,
	//----
		// (09) //	VR04 = ([難易度別定数]); // 下の範囲を設定する。
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R3f_boss_clip_max_y256, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((64), (80), (96)/*(hard)[r39]*/, (96)),/*[boss_clip_y_pixel]*/
		// (10) VR04_NAN_IDO_DECODE 	<<= (8);/*変換 t256()[convert by pixel to t256()]*/
		MCODE(OP0x1f_ASLM_PD, (8), R3f_boss_clip_max_y256, R3f_boss_clip_max_y256),/*(ショートメモリアドレッシング)*/
		//VR3f_boss_clip_max_y256	= (VR04_NAN_IDO_DECODE);/*[decoded difficulty by boss clip at y pixel]*/
		// (11)
	//	NAX
	};
	cpu_exec((u32*)&codebase_init, (10));
	add_laser_off_void();/*(レーザーoff)*/
	/* 「初期化セクション」より前にclipを初期化する */ /*(弾の有効範囲を標準==見える範囲のみ有効に設定)*/
	// ★ [ボス弾幕の場合]
	// この直後に[initialize section: 初期化セクション]を実行するので、
	// レーザーon や 弾の有効範囲が特殊なものは、
	// それらは[initialize section: 初期化セクション]内でのみ実行します。
	// ★ [道中、中ボスの場合]
	// 中ボスの場合はボスの場合と扱いが同じなので、直後の[initialize section: 初期化セクション]で実行します。
	// ★ [道中の場合]
	// 道中の場合これ(レーザーなし、弾の有効範囲を標準==見える範囲のみ有効)がデフォルトです。
	// 変えたい場合、少なくとも spell_cpu_common_reset(); 以降に実行してください。
	//
}

/*---------------------------------------------------------
	道中の前に初期化する必要がある部分。
---------------------------------------------------------*/
static void set_basic_cb(void)
{
	int jj;
	for (jj=0; jj<DANMAKU_LAYER_04_MAX; jj++)/*(。)*/
	{
		card.layer_callback[jj] = system_spell_resource[(card.spell_used_number/*-1*/)].layer_callback_preset[jj];/*(r36-書き換え禁止)*/	/*(通常弾用)*/
	}
}


extern void spell_cpu_danmaku_callback_douchuu_init(void)/*(道中ザコ弾用に弾幕コールバックを初期化する)*/
{
	#if (1)/*[道中ザコ用]*/
	set_basic_cb();/* 弾幕コールバックシステムの初期化 */
	card.layer_callback[1] = danmaku_01_standard_angle_mover_douchu_start; /*(道中弾用開始)*/
	#endif
}


/*---------------------------------------------------------
	カードの初期化。カードが変わると毎回行う必要がある。
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(card_maikai_init)
{
	spell_cpu_common_reset();/*(道中ザコ/ボス/道中中ボス[共通部分])*/
	#if (1)/*[ボス/道中中ボス用]*/
	set_basic_cb();/* 弾幕コールバックシステムの初期化 */
	#endif
	#if (1)/* カードスクリプトに移行した場合の[initialize section: 初期化セクション]。 */
	#if (1==LINK_DUAL_SYSTEM)
	/*(実行言語(カードインタプリタ / C言語) 別で、[execute section: 発弾セクション]を登録)*/
	if (system_spell_resource[(card.spell_used_number/*-1*/)].scr_ipt_run_flag) /*(実行言語(  C言語) の場合。)*/
	#endif /*(LINK_DUAL_SYSTEM)*/
	{
		/* カード初期化セクションを実行する。 */
		if (NULL!=(system_spell_resource[(card.spell_used_number/*-1*/)].spell_initialze_section))
		{
			(system_spell_resource[(card.spell_used_number/*-1*/)].spell_initialze_section)(src);
		}
		/* カード実行セクションを登録する。 */
		card.boss_spell_callback = system_spell_resource[(card.spell_used_number/*-1*/)].spell_execute_section;
	}
	#if (1==LINK_DUAL_SYSTEM)
	else	/*(実行言語(カードインタプリタ)の場合。)*/
	{
		/* カード初期化セクションを実行する。 */
		ci_run_init_section(src);
		/* カード実行セクションを登録する。 */
		card.boss_spell_callback = ci_spell_cpu;
	}
	#endif /*(LINK_DUAL_SYSTEM)*/
	/* カード時間に予め登録された寿命時間を設定する。 */
	/* カードの制限時間を設定(予めカードごとに設定されている標準時間に設定) */
	/* カードの時間切れを設定 */
	VR10_BOSS_SPELL_TIMER = system_spell_resource[(card.spell_used_number/*-1*/)].spell_limit_max_time;
	#endif
}


/*---------------------------------------------------------
	スペルCPUを実行し、カードを１フレーム生成する。
	-------------------------------------------------------
	カード生成すると時間経過し、カード寿命時間が自動で減る。
	カード寿命時間が無くなった場合は、カードタイプが無し(SPELL_00)になる。
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(card_generate)/* カード生成 */
{
	if (SPELL_00 != card.spell_used_number) 	/* スペル生成は必要？ */
	{
		VR10_BOSS_SPELL_TIMER--;				/* 時間経過する */	/*fps_factor*/
		if (0 < VR10_BOSS_SPELL_TIMER)		/* 時間切れ？ */
		{
			set_REG_DEST_BOSS_XY();/* 弾源x256 y256 ボスの中心から発弾。 */
			#if (1)/* カード実行 */
		//	(system_spell_resource[(card.spell_used_number/*-1*/)].spell_execute_section)(src);/*-r40*/
			(card.boss_spell_callback)(src);/*r41-*/	/*(実行言語(カードインタプリタ / C言語) 別で、発弾する)*/
			#endif
		}
		else
		{
			card.spell_used_number = SPELL_00;		/* カード生成終了 */
		}
	}
}
