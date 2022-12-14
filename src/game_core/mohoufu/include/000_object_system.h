
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	このファイルは直接インクルードしません。
	"game_main.h" からのみ間接的にインクルードします。
---------------------------------------------------------*/

#ifndef _OBJECT_SYSTEM_H_
#define _OBJECT_SYSTEM_H_

/*---------------------------------------------------------
	スプライトオブジェクト システム
--------------------------------------------------------- */
/*
寿命:	s32 JYUMYOU
1[秒]									60			 >				  64 [frame]
1[分]									60 x 60 	 >			 64 x 64 [frame]
1[時間] 0x034BC0 ==   216000			60 x 60 x 60 >		64 x 64 x 64 [frame] ==   262144 0x040000
2.5[日] 0xC5C100 == 12960000 2.5 x 24 x 60 x 60 x 60 > 64 x 64 x 64 x 64 [frame] == 16777216 0x01000000
-------------------------------------------------
もし、毎フレーム減算するカウンタがあるとして、
signed int だと、初期値が 0x01ff ffff だった場合、2.5[日]経過しても、カウンタの値は0x01-- ----。
つまり最上位bit は符号として、最上位bitを除いた7bitは自由に使える。(カウンタ取り出すとき0x00ffffffでマスクするとして)
*/

/* HATUDAN_ITI_NO_JIKAN_USE_EFFECT==発弾エフェクト後から[0]カウント経過した弾。発弾エフェクト時間==[64]カウント。 */
#define JYUMYOU_HATUDAN_64_OFFSET		(64)

#define JYUMYOU_MUGEN		(16777216)
//#define JYUMYOU_1MIN		byou60(60)/*0x0e10*/
#define JYUMYOU_1MIN10S 	(0x1000+JYUMYOU_HATUDAN_64_OFFSET)/* (60)[sec] + (9.33333333333333)[sec] */
#define JYUMYOU_NASI		(0)
/*
JYUMYOU_MUGEN:	(寿命無限==寿命、約2.5[日])プレイヤーやオプション等、自動で消えては困るもの。
JYUMYOU_1MIN10S:	(寿命、約1[分]10[秒])
JYUMYOU_NASI:	(寿命、なし。無しになると、自動で消去されるので注意。「毎フレーム寿命=2に設定しとけば消えない。(寿命=1だと消えちゃうかも)」)

*/

/* 弾の生成時間(標準) */
#define JYUMYOU_TAMA_HASSEI 	(JYUMYOU_1MIN10S)
/* ザコの生成時間(標準) */
#define JYUMYOU_ZAKO_HASSEI 	(JYUMYOU_1MIN10S)
/* 画面外ならザコ消す場合の、リミット時間 */
//#define JYUMYOU_ZAKO_CLIP 		(2048)				/* 2048/60 = 34.13333333333[秒] */

/*
	生成時間を基点とした動きの場合、(後でシステムが変わるかもしれないから)
	上記(JYUMYOU_TAMA_HASSEI / JYUMYOU_ZAKO_HASSEI)を基準としておく。
*/
#define HATUDAN_ITI_NO_JIKAN_USE_EFFECT 	(JYUMYOU_1MIN10S-JYUMYOU_HATUDAN_64_OFFSET)
#define HATUDAN_ITI_NO_JIKAN_EFFECT_NONE	(HATUDAN_ITI_NO_JIKAN_USE_EFFECT+JYUMYOU_HATUDAN_64_OFFSET)


/*---------------------------------------------------------
	プライオリティー(優先順位)
	-------------------------------------------------------
	プライオリティーには、描画プライオリティー以外に、
	あたり判定プライオリティー(==あたり判定を領域別に判別する機能)があるので注意。
	-------------------------------------------------------
--------------------------------------------------------- */
/* ここは種類別ではなくて、機能別に分類する。 */

#define OBJ_Zff_MASK_SUB_TYPE				(0x00ff)
//		OBJ_Z00_MAHOU_JIN													/* === Gu魔方陣面 === */
#define OBJ_Z01_JIKI_GET_ITEM				(0x0100)/*0x0100*/				/* === Guプレイヤー面 === */
#define OBJ_Z02_TEKI						(0x0200)/*0x0400*/				/* === Gu敵面 === */
#define OBJ_Z03_ITEM						(0x0400)/*(0x2000)0x1000*/		/* === GuITEM面 === */
#define OBJ_Z04_TAMA						(0x0800)/*(0x1000)0x0800*/		/* === Gu敵弾面 === */
#define OBJ_Z05_FRONT						(0x1000)/*(0x8000)*/			/* フロント面(あたり判定無し) Guパネル面 === */
//efine OBJ_Z80_SHOT_SPECIAL				(0x8000)/*0x0100*/				/* 霊夢の回転ショット / kodomo_hlaserの判別 */

//#define S P_GROUP_ALL_SDL_CORE_TYPE		(0x1f00)/* game_core動作 */
//#define OBJ_Zff_MASK_SUB_TYPE 			(0x007f)


/*---------------------------------------------------------
	オブジェクトバンクシステム
	-------------------------------------------------------
	画像1テクスチャに最大64のオブジェクトを割り当てる事が出来る。
	最大64なのは、pspではあまり多いと低速化する。
	-------------------------------------------------------
	オブジェクトを登録しただけでは画像は更新されないので、
	画像をオブジェクトに反映させる為には reflect_sprite_spec(); で、
	反映するテクスチャバンク(画像番号)を指定して、
	オブジェクトのバンク設定を反映させると、画像が更新される。
--------------------------------------------------------- */

/* 管理するオブジェクトバンク */
enum
{
	OBJ_BANK_00_TAMA = 0,		// 敵弾用バンク 		//	※1.敵弾/アイテム用テクスチャは共用
	OBJ_BANK_01_ITEM,			// アイテム用バンク 	//	※1.敵弾/アイテム用テクスチャは共用
	OBJ_BANK_02_FRONT_BANK0,	// フロント面用バンク	//	※2.フロント/パネル用テクスチャは共用
//	OBJ_BANK_07_FRONT_BANK1,	// 用バンク
//	OBJ_BANK_07_FRONT_BANK2,	// 用バンク
	OBJ_BANK_03_TITLE_dummy,	/*[予定]*/	// タイトル画面用バンク //	※2.フロント/パネル用テクスチャは共用
//	OBJ_BANK_09_EFFECT, 		/*[予定]*/	// 用バンク
//
	OBJ_BANK_01_REIMU_A,		// 自機用バンク(霊夢A、霊符)
	OBJ_BANK_02_REIMU_B,		// 自機用バンク(霊夢B、夢符)
	OBJ_BANK_03_MARISA_A,		// 自機用バンク(魔理沙_A、魔符)
	OBJ_BANK_04_MARISA_B,		// 自機用バンク(魔理沙_B、恋符)
	OBJ_BANK_05_REMILIA,		// 自機用バンク(レミリア)
	OBJ_BANK_06_YUYUKO, 		// 自機用バンク(幽々子)
	OBJ_BANK_07_CIRNO_A,		// 自機用バンク(チルノA、氷符)
	OBJ_BANK_08_CIRNO_Q,		// 自機用バンク(チルノ?H、?H符)
//
	OBJ_BANK_21_BOSS_STAGE1,	// ボス用バンク(ステージ 1、アリス)
	OBJ_BANK_22_BOSS_STAGE2,	// ボス用バンク(ステージ 2、未定)
	OBJ_BANK_23_BOSS_STAGE3,	// ボス用バンク(ステージ 3、輝夜)
	OBJ_BANK_24_BOSS_STAGE4,	// ボス用バンク(ステージ 4、文)
	OBJ_BANK_25_BOSS_STAGE5,	// ボス用バンク(ステージ 5、パチュリー)
	OBJ_BANK_26_BOSS_STAGE6,	// ボス用バンク(ステージ 6、咲夜)
	OBJ_BANK_11_ZAKO_STAGE1,	// ザコ用バンク(ステージ 1-6, extra, phantasm)		// OBJ_BANK_27_BOSS_STAGE7_dummy,
	OBJ_BANK_28_BOSS_STAGE8,	// ボス用バンク(ステージ 8、エキストラ)
	OBJ_BANK_29_BOSS_STAGE9,	// ボス用バンク(ステージ 9、ファンタズム)
//
//	OBJ_BANK_11_ZAKO_STAGE1,
//	OBJ_BANK_12_ZAKO_STAGE2,
//	OBJ_BANK_13_ZAKO_STAGE3,
//	OBJ_BANK_14_ZAKO_STAGE4,
//	OBJ_BANK_15_ZAKO_STAGE5,
//	OBJ_BANK_16_ZAKO_STAGE6,
//	OBJ_BANK_17_ZAKO_STAGE7_dummy,
//	OBJ_BANK_18_ZAKO_STAGE8,
//
	OBJ_BANK_MAX
};
#define 	OBJ_BANK_SIZE			(8*8)
#define 	OBJ_BANK_SIZE_00_TAMA	(OBJ_BANK_00_TAMA*OBJ_BANK_SIZE)
#define 	OBJ_BANK_SIZE_01_ITEM	(OBJ_BANK_01_ITEM*OBJ_BANK_SIZE)

/*---------------------------------------------------------
	スプライト
--------------------------------------------------------- */

typedef struct /*_point256*/
{
	u16 x;	/*	union POINT */	/* x 位置 */
	u16 y;	/*	union POINT */	/* y 位置 */
} POINT_u16;
/* u16座標 */

typedef struct /*_point256*/
{
	int x256;	/*	union POINT */	/* x表示位置  (256固定小数点形式) / akt. Position */
	int y256;	/*	union POINT */	/* y表示位置  (256固定小数点形式) / akt. Position */
} POINT256;
/* t256座標 */

//typedef struct /*_point_vector256*/
//{
// POINT256 c;	/*	union POINT */	/* x表示位置  (256固定小数点形式) / akt. Position */
//				/*	union POINT */	/* y表示位置  (256固定小数点形式) / akt. Position */
// POINT256 v;	/*	union POINT_VECTOR */	/* 共用regist_vector(); */	/*union BULLET_VECTOR_DATA*/
//				/*	union POINT_VECTOR */	/* 共用regist_vector(); */	/*union BULLET_VECTOR_DATA*/
//} POINT_VECTOR256;
/* t256座標 + t256ベクトル */

/*
	強制傾きoffの特殊機能:
	m_zoom.y256 に M_ZOOM_Y256_NO_TILT を設定しておくと、
	rotationCCW1024(描画用角度) を無視して、回転無し、強制1.0倍で描画する。
*/
#define M_ZOOM_Y256_NO_TILT (0)
/*
	パチェの炎のアニメーション(火符「アグニシャイン」)や
	チルノやルーミアの丸弾や大玉弾が回転していなかったり、その他色々使用している。
	本家も描画用設定角度をシンプルに無視する何らかの機能があるのでは?と思い実装してみた。
	基本的に丸弾は回転させると無駄に遅くなる。
*/


#if 1
// union 共用
	// [体力値]
	#define boss_hp 					tairyoku_ti
	#define zako_hp 					tairyoku_ti
	#define base_time_out				tairyoku_ti/*bakuhatsu*/
	#define ZAKO_HP_TAOSENAI			(99999)/*(倒せない値)*/
	// [攻撃値]/スコア/あたり判定。
	#define base_score					kougeki_ti
	#define atari_hantei				kougeki_ti
	#define ATARI_HANTEI_OFF			(0)/*(あたらない値)*/
	#define ATARI_HANTEI_TAOSENAI		(0x3fffffff)/*(倒せない値)*/
	//#define base_state				user01
#endif
//
/* スプライトの使い方
----------------------------+---------------------------+---------------------------------------+
分類						|	tairyoku_ti[体力値] 	|	kougeki_ti[攻撃値]					|
----------------------------+---------------------------+---------------------------------------+
自機 / プレイヤー			|	--				--		|	無敵時強さ。無敵期間に雑魚に体当たりする場合の攻撃値。
----------------------------+---------------------------+---------------------------------------+
自弾 / プレイヤーショット	|	--				--		|	ショットの強さ。|	kougeki_ti		武器強さ	|
----------------------------+---------------------------+---------------------------------------+
ボス						|	boss_hp[特殊]	体力	|	雑魚がプレイヤーに体当たりする場合の攻撃値。及び倒した場合に得られるスコアbase_score。
----------------------------+---------------------------+---------------------------------------+
中ボス						|	zako_hp[zako]	体力	|	雑魚がプレイヤーに体当たりする場合の攻撃値。及び倒した場合に得られるスコアbase_score。
----------------------------+---------------------------+---------------------------------------+
雑魚 / ザコ 				|	zako_hp[zako]	体力	|	雑魚がプレイヤーに体当たりする場合の攻撃値。及び倒した場合に得られるスコアbase_score。
----------------------------+---------------------------+---------------------------------------+
敵弾						|	base_time_out	時間	|	--				--					|
----------------------------+---------------------------+---------------------------------------+
爆発						|	base_time_out	時間	|	--				--					|
----------------------------+---------------------------+---------------------------------------+
攻撃値とスコアは同じ物なので、プレーヤーがボスに体当たりされて受けるダメージはボスのスコアと同じ量。
スコア0ならばプレーヤーは触ってもダメージを受けないので、プレーヤーは死なない。
----------------------------------------------------------------------------------------------
*/
/*
kougeki_ti: 	攻撃値:
演出obj:					攻撃値:都合上, 常に(0)を保持。(?)

*/

typedef struct _obj_tag_
{
	POINT256	center; 				/* 表示 中心座標位置(x256, y256)  (256固定小数点形式) / akt. Position */
	POINT256	math_vector;			/* 数学的な意味でのベクトル。(x256, y256) */	/* 共用regist_vector(); */	/*union BULLET_VECTOR_DATA*/
//[4==1*4]
	int 		rotationCCW65536;		/* 描画用角度(下が0度で左回り(反時計回り), 一周は65536分割, 0-65535度) */
	int 		tmp_angleCCW65536;		/* 保持用角度(下が0度で左回り(反時計回り), 一周は65536分割, 0-65535度) */
	s32 		jyumyou;				/* 寿命 */
	int 		obj_type_set;			/* [デバッグ中/検索出来るように変な名前にしとく] 種類及び使用可否 / Sprite-Type, ( enum OBJ_TYPE), 0 = remove. */
//[8==2*4]
	u32 		color32;				/* Gu color AGBR8888 MAKE32RGBA(RED, GREEN, BLUE, ALPHA)で各要素 0 から 255 (0x00 から 0xff)まで。 */
	int 		m_Hit256R;				/* あたり判定用 */
	POINT256	m_zoom; 				/* 表示拡大率(x256, y256) (画像の横の拡大率t256()形式で指定) */
	//
//[12==3*4]
	int 		system_data00;			/*(レイヤーシステム用)*/	/* (r35-弾幕システム用途でレイヤー管理しているので重要)*/
	struct _obj_tag_ *target_obj;		/* とりあえず移行用(3)移行したらなくなる。 */
	int 		kougeki_ti; 			/* 攻撃値 / score / あたり判定 */		/* 敵スコア */
	int 		tairyoku_ti;			//int health;	int time_out;		//int score;	int state;
	/* とりあえず移行用(2)追加弾、基本機能 */
//[16==4*4]
	void (*callback_move01)(struct _obj_tag_ *src); 			/* Custom-Move-Routine. */
	void (*callback_move02)(struct _obj_tag_ *src); 			/* Custom-Attack-Routine. */
	void (*callback_move03)(struct _obj_tag_ *src, struct _obj_tag_ *tama);
	void (*callback_move04)(struct _obj_tag_ *src); 			/* Custom-loser-Routine (やられた後にボーナスを出すとか、違う爆発するとか) / 自機オプションのアニメーションコールバック */
//[20==5*4]
	/* とりあえず移行用(1)従来互換(弾) */
	int user_data00;
	int user_data01;
	int user_data02;
	int user_data03;
//[24==6*4]
	int user_data04;
	int user_data05;
	int user_data06;
	int user_data_bug_07;// バグ対策。	 良くワカンナイ 。()
//[28==7*4]
// 描画用
	/*u16*/u16/*int*/ tx;	//	u16 u0;//tx = u0;		int tx; 	/* u テクスチャ座標 */
	/*u16*/u16/*int*/ ty;	//	u16 v0;//ty = v0;		int ty; 	/* v テクスチャ座標 */
	/*u16*/u16/*int*/ w;	//	u16 u1;//w = (u1-u0);	int w;
	/*u16*/u16/*int*/ h;	//	u16 v1;//h = (v1-v0);	int h;
	int for_align_dummy_11;/* .align 合わせ用。.align合ってた方が実行速度は速いし、プログラムも簡略化出来るので常に小さい。使ってないダミー。 */
	int for_align_dummy_22; /*[拡張予定]*/	/* .align 合わせ用。.align合ってた方が実行速度は速いし、プログラムも簡略化出来るので常に小さい。使ってないダミー。 */
//[32==8*4]
} OBJ;
/* Custom-Tamakesi-Routine / Zako Anime */


#if (1)
/*
	-------------------------------------------------------
	ゲームでは何かアクションが起こった場合、ＯＢＪ(キャラ)によって対処の方法が異なる。
	例えばＯＢＪ(キャラ)がぶつかった場合。
	自機と弾がぶつかった場合、自機が死ぬ(ダメージ受ける)。
	自機とアイテムがぶつかった場合、アイテムが死ぬ(アイテム取る)。
	これらの関係は、ぶつかる処までは同じ。で、ぶつかってからの処理が違う。
	-------------------------------------------------------
	処理が違う部分は、コールバックという方法で吸収する。
	コールバックに予め処理を登録しておくと、ぶつかった場合予め登録しておいた、
	コールバックルーチン(コールバックされる処理)が呼ばれる。
	-------------------------------------------------------
	コールバックの種類として、ぶつかった場合以外にも、
	移動する場合。やられた場合。もコールバックになっている。
	-------------------------------------------------------
	コールバックは便利だけど、原理的に遅い。だから珠にしか使用しない処理には、良い方法だが、
	煩雑に呼ばれる処理には使うと遅くなる。
	-------------------------------------------------------
	攻撃処理をシステム側に入れたら、異常に遅くて無理だった。
	-------------------------------------------------------
*/
/* callback_move01: 移動する場合の処理。 */
	#define callback_mover			callback_move01

/* callback_move02: スペカ。攻撃処理。 */
	#define callback_kougeki		callback_move02/*(r39現在使い魔のみ)*/

/* callback_move03: ぶつかった場合の処理。 */
	#define callback_hit_teki		callback_move03

/* callback_move04: [ボス以外]やられた場合の処理。 */
/* callback_move04: [ボスのみ]スペカ処理。 */
	#define callback_loser			callback_move04
// 雑魚からみるのに card_system の方が良い気がしたので card_system へ移動。
	#define callback_root_supeka	callback_move04
/*
[ボス]がやられた場合、共通処理なので、callback_loserは要らない。
そこで、[ボス]の場合は、スペカコールバックに割り当てる。
*/

#endif


/*	struct _sprite *target_obj;
	用途は(
		player用誘導弾、
		後ろの魔方陣"妖怪2"(赤)
	)
	ほんとは複雑にキャストすれば要らないんだけどバグでそうだし。
 */



/*---------------------------------------------------------
	スプライトオブジェクト システム
---------------------------------------------------------*/
/*(登録処理系)*/
extern OBJ *obj_regist_tama(void);	/* [A00登録弾領域]にobjを登録する。(==弾/アイテム専用) */
extern OBJ *obj_regist_teki(void);	/* [A01登録敵領域]にobjを登録する。(==敵専用) */
/* 任意の領域に強制的に登録する。[A02固定領域]と[A04パネル領域]はこの方法で登録する。 */
/* 内部管理値のオフセットを素直に指定する。例えば専用固定スプライトの場合は固定値までのオフセットOBJ_HEAD_01_0x0800_TOUROKUを足す。 */
extern OBJ *obj_regist_direct_number(u32 register_object_absolute_direct_number);	/* 強制登録用。危険なので注意して使う。*/

/*(当たり判定系)*/
/* [A00登録弾領域]のobjとのあたり判定チェック。 */
extern OBJ *obj_collision_check_00_tama(OBJ *tocheck, int type);/*弾専用、typeには弾かアイテムかを指定する。*/
/* [A01敵領域]のobjとのあたり判定チェック。 */
extern OBJ *obj_collision_check_A01_A02_teki(OBJ *tocheck);/*敵専用*/	//, int type);

/*(プレイヤーにとっての敵を探す)*/
extern OBJ *obj_teki_search(void);

/*(その他系)*/
/* [A00登録弾領域]と[A01登録敵領域]と[A02固定領域]と[A04パネル領域]のOBJを全消去。 */
extern void obj_system_cleanup_all(void);

/* [A00登録弾領域]と[A01登録敵領域]と[A02固定敵領域]と[A03固定領域]のOBJを移動処理する。[A04パネル領域]のobjは移動しない。 */
extern void obj_system_move_all(void);

extern OBJ_CALL_FUNC(gamen_gai_nara_zako_osimai);/* 画面外ならおしまい */
extern OBJ_CALL_FUNC(boss_control_check_tukaima_kougeki_time_out);/*(攻撃/時間制限/処理)*/

/* 使用中であるが退避したい場合。画面外にスプライトを移動させ、無効にする。 */
extern OBJ_CALL_FUNC(sprite_kotei_obj_r36_taihi);




#endif/* _OBJECT_SYSTEM_H_ */




#ifndef _OBJ_AREA_H_
#define _OBJ_AREA_H_

#if 1
/*---------------------------------------------------------
	敵弾管理システム
---------------------------------------------------------*/

	/* 描画プライオリティーが自機テクスチャーのもの */
/* -- プライオリティー＃６．自機を描画 */
//#define OBJ_111JIKI_POOL_MAX FIX_OBJ_07_JIKI_OPTION3

/*
 参考: kouma_tr013/東方紅魔郷/マニュアル/html/faq.html
Ｑ２３　アイテムの表示限界は？

　画面内５１２個までです。
　敵弾の数が６４０個なので、全てがボーナスアイテムになるとは限りませんが、
　殆どの場合はスコアパターンに影響するようなことはありません。

*/

enum/* [A00]エリア#00: [A00弾領域] */
{
/* 弾の最大数は OBJ_POOL_00_TAMA_1024_MAX (==1024) それ以上登録しようとしても登録されない。 */
//	OBJ_POOL_00_TAMA_1024_MAX = (1<<9), /*(旧仕様512のメモ)*/
	OBJ_POOL_00_TAMA_1024_MAX = (1<<10), /* 弾登録プログラムの都合上 2^n である必要があります。(1024==(1<<10) ) */
//	OBJ_POOL_00_TAMA_1024_MAX = (1<<11), /* 弾登録プログラムの都合上 2^n である必要があります。(2048==(1<<11) ) */
};

enum/* [A01]エリア#01: [A01登録敵領域] */
{
/* 敵(自機、オプション、自弾等、弾以外の全てのスプライト含む)の最大数は OBJ_POOL_02_TEKI_FIX_0256_MAX (==256) それ以上登録しようとしても登録されない。 */
	OBJ_POOL_01_TOUROKU_0256_MAX = (1<<8), /* 敵登録プログラムの都合上 2^n である必要があります。(256==(1<<8) ) */
};

enum/* [A02]エリア#02: [A02固定敵領域] */
{
	TEKI_OBJ_00_BOSS00_HONTAI = 0, /*<使用中>[r36]*/
	TEKI_OBJ_01_BOSS01_HONTAI, /*<拡張予定フラン、リリカ、>[r39u1]*/
	TEKI_OBJ_02_BOSS02_HONTAI, /*<拡張予定フラン、メルラン>[r39u1]*/
	TEKI_OBJ_03_BOSS03_HONTAI, /*<拡張予定フラン、>[r39u1]*/
	//
	TEKI_OBJ_04_TUKAIMA00, /*<>[r39u1]*/
	TEKI_OBJ_05_TUKAIMA01, /*<>[r39u1]*/
	TEKI_OBJ_06_TUKAIMA02, /*<>[r39u1]*/
	TEKI_OBJ_07_TUKAIMA03, /*<>[r39u1]*/
	TEKI_OBJ_08_TUKAIMA04, /*<>[r39u1]*/
	TEKI_OBJ_09_TUKAIMA05, /*<>[r39u1]*/
	TEKI_OBJ_0a_TUKAIMA06, /*<>[r39u1]*/
	TEKI_OBJ_0b_TUKAIMA07, /*<>[r39u1]*/
	//
/* 敵(自機、オプション、自弾等、弾以外の全てのスプライト含む)の最大数は OBJ_POOL_02_TEKI_FIX_0256_MAX (==256) それ以上登録しようとしても登録されない。 */
	OBJ_POOL_02_TEKI_FIX_0256_MAX = (1<<8), /*	仮(256) */
};

enum/* [A03]エリア#03: [A03固定領域] */
{
	/* 描画プライオリティーが自機テクスチャーのもの */
	FIX_OBJ_00_PLAYER = 0,		/*<使用中>[r32変更済み] obj_regist_direct_number(OBJ_HEAD_01_0x0800_TOUROKU+FIX_OBJ_00_PLAYER); */
	FIX_OBJ_01_JIKI_MARU,		/*<使用中>[r32変更済み] obj_regist_direct_number(OBJ_HEAD_01_0x0800_TOUROKU+FIX_OBJ_01_JIKI_MARU); */
	FIX_OBJ_02_BOMBER_HONTAI,	/*<使用中>[r36] ボンバーの親 */
	FIX_O_BJ_03_SEND2,			/*[予定]*/
	FIX_OBJ_04_JIKI_OPTION0,	/*<使用中>[r32変更済み] obj_regist_direct_number(OBJ_HEAD_01_0x0800_TOUROKU+FIX_OBJ_04_JIKI_OPTION0+jj); */
	FIX_OBJ_05_JIKI_OPTION1,	/*<使用中>[r32変更済み]*/
	FIX_OBJ_06_JIKI_OPTION2,	/*<使用中>[r32変更済み]*/
	FIX_OBJ_07_JIKI_OPTION3,	/*<使用中>[r32変更済み]*/
//
	/* 描画プライオリティーがfrontテクスチャーのもの */
//	xxx_FIX_OBJ_08_BOSS,		/* <あたり判定の都合上出来ない> */	/*<使用中>[r32変更済み] obj_regist_direct_number(OBJ_HEAD_01_0x0800_TOUROKU+FIX_OBJ_08_BOSS); */
//	FIX_O_BJ_09_,				/*[予定]*/
//	FIX_O_BJ_10_,				/*[予定]*/
//	FIX_OBJ_11_EFFECT01,				/*<使用中>*/
//	FIX_O_BJ_12_SUPPORT0,		/*[予定]*/		/*<使用中>*/
//	FIX_O_BJ_13_SUPPORT1,		/*[予定]*/		/*<使用中>*/
//	FIX_O_BJ_14_SUPPORT2,		/*[予定]*/		/*<使用中>*/
//	FIX_O_BJ_15_SUPPORT3,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_08_EFFECT01,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_09_EFFECT02,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_10_EFFECT03,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_11_EFFECT04,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_12_EFFECT05,		/*[予定]*/		/*<使用中>*/
	FIX_OBJ_13, 	/*[予定]*/
	FIX_OBJ_14, 	/*[予定]*/
	FIX_OBJ_15_JIKI_TEISOKU_EFFECT, 	/*[予定]*/				/*<使用中>*/
	OBJ_POOL_03_KOTEI_0016_MAX/*MAX*/, /* 専用自動登録プログラムが無いので 2^n に限定する必要性はない。 */
};



enum/* [A04]エリア#04: [A04パネル領域] */
{
	PANEL_OBJ_00_S00 = 0,	/* スコア10桁目 */
	PANEL_OBJ_01_S01,		/* スコア9桁目 */
	PANEL_OBJ_02_S02,		/* スコア8桁目 */
	PANEL_OBJ_03_S03,		/* スコア7桁目 */
	PANEL_OBJ_04_S04,		/* スコア6桁目 */
	PANEL_OBJ_05_S05,		/* スコア5桁目 */
	PANEL_OBJ_06_S06,		/* スコア4桁目 */
	PANEL_OBJ_07_S07,		/* スコア3桁目 */
	PANEL_OBJ_08_S08,		/* スコア2桁目 */
	PANEL_OBJ_09_S09,		/* スコア1桁目 */
	PANEL_OBJ_0a_P00,		/* パワー1桁目 */
	PANEL_OBJ_0b_P01,		/* パワー小数点1桁目 */
	PANEL_OBJ_0c_P02,		/* パワー小数点2桁目 */
	PANEL_OBJ_0d_Time,		/* "Time:" */
	PANEL_OBJ_0e_P0p,		/* パワー'.' */
	PANEL_OBJ_0f_NAN_IDO,	/* 難易度表示 "Easy", "Normal", "Hard", "Lunatic", */
	//
	PANEL_OBJ_10_H00,		/* ハイスコア10桁目 */
	PANEL_OBJ_11_H01,		/* ハイスコア9桁目 */
	PANEL_OBJ_12_H02,		/* ハイスコア8桁目 */
	PANEL_OBJ_13_H03,		/* ハイスコア7桁目 */
	PANEL_OBJ_14_H04,		/* ハイスコア6桁目 */
	PANEL_OBJ_15_H05,		/* ハイスコア5桁目 */
	PANEL_OBJ_16_H06,		/* ハイスコア4桁目 */
	PANEL_OBJ_17_H07,		/* ハイスコア3桁目 */
	PANEL_OBJ_18_H08,		/* ハイスコア2桁目 */
	PANEL_OBJ_19_H09,		/* ハイスコア1桁目 */
	PANEL_OBJ_1a_fps00, 	/* fps2桁目 */
	PANEL_OBJ_1b_fps01, 	/* fps1桁目 */
	PANEL_OBJ_1c_fps02, 	/* fps小数点1桁目 */
	PANEL_OBJ_1d_fps03, 	/* fps小数点2桁目 */
	PANEL_OBJ_1e_fps0p, 	/* fps '.' */
	PANEL_OBJ_1f_fps_str,	/* "fps" */
	//
	PANEL_OBJ_20_N00,		/* 残りガッツ8桁目 */
	PANEL_OBJ_21_N01,		/* 残りガッツ7桁目 */
	PANEL_OBJ_22_N02,		/* 残りガッツ6桁目 */
	PANEL_OBJ_23_N03,		/* 残りガッツ5桁目 */
	PANEL_OBJ_24_N04,		/* 残りガッツ4桁目 */
	PANEL_OBJ_25_N05,		/* 残りガッツ3桁目 */
	PANEL_OBJ_26_N06,		/* 残りガッツ2桁目 */
	PANEL_OBJ_27_N07,		/* 残りガッツ1桁目 */
	PANEL_OBJ_28_B00,		/* ボム8桁目 */
	PANEL_OBJ_29_B01,		/* ボム7桁目 */
	PANEL_OBJ_2a_B02,		/* ボム6桁目 */
	PANEL_OBJ_2b_B03,		/* ボム5桁目 */
	PANEL_OBJ_2c_B04,		/* ボム4桁目 */
	PANEL_OBJ_2d_B05,		/* ボム3桁目 */
	PANEL_OBJ_2e_B06,		/* ボム2桁目 */
	PANEL_OBJ_2f_B07,		/* ボム1桁目 */
	//
	PANEL_OBJ_30_J00,		/* 残り時間3桁目 */
	PANEL_OBJ_31_J01,		/* 残り時間2桁目 */
	PANEL_OBJ_32_J02,		/* 残り時間1桁目 */
	PANEL_OBJ_33_G03,		/* グレイズ5桁目 */
	PANEL_OBJ_34_G04,		/* グレイズ4桁目 */
	PANEL_OBJ_35_G05,		/* グレイズ3桁目 */
	PANEL_OBJ_36_G06,		/* グレイズ2桁目 */
	PANEL_OBJ_37_G07,		/* グレイズ1桁目 */
	//
	/* パネル用スプライトは OBJ_POOL_04_PANEL_0056_MAX (==256) それ以上登録しようとしても登録されない。 */
//	OBJ_POOL_04_PANEL_0056_MAX = (256), /*(旧仕様のメモ)*/
	OBJ_POOL_04_PANEL_0056_MAX/* MAX */, /* 専用自動登録プログラムが無いので 2^n に限定する必要性はない。 */
};

#if 0
[A00]エリア#00: [A00弾領域]
[A01]エリア#01: [A01登録敵領域]
[A02]エリア#02: [A02固定敵領域]
[A03]エリア#03: [A03固定領域]
[A04]エリア#04: [A04パネル領域]
スプライトオブジェクト相対オフセットアドレス。(the sprites object struct, relative address.)
0x0000 +----------------------------------+ OBJ_HEAD_00_0x0000_TAMA
	   | [A00]弾専用スプライト(2048)	  | OBJ_POOL_00_TAMA_1024_MAX (need, 2^n)
0x0800 +----------------------------------+ OBJ_HEAD_01_0x0800_TOUROKU
	   | [A01]登録敵専用スプライト(256)   | OBJ_POOL_01_TOUROKU_0256_MAX (need, 2^n)
0x0900 +----------------------------------+ OBJ_HEAD_02_0x0900_TEKI_FIX
	   | [A02]固定敵専用スプライト(仮256) | OBJ_POOL_02_TEKI_FIX_0256_MAX (need, 2^n)
0x0900 +----------------------------------+ OBJ_HEAD_03_0x0a00_KOTEI
	   | [A03]自機等固定スプライト(16)	  | OBJ_POOL_03_KOTEI_0016_MAX (not need, 2^n)
0x0910 +----------------------------------+ OBJ_HEAD_04_0x0a10_PANEL
	   | [A04]パネル用スプライト(56)	  | OBJ_POOL_04_PANEL_0056_MAX (not need, 2^n)
0x0948 +----------------------------------+ OBJ_LAST_99_0x0a48_MAX
全スプライトオブジェクト OBJ_LAST_99_0x0a48_MAX
//
「弾専用スプライトオブジェクト」 及び 「敵専用スプライトオブジェクト」 は、
自動登録プログラムの都合上、必ず 2^n である必要があります。
//
「固定スプライトオブジェクト」 及び 「パネル用スプライトオブジェクト」 は、
アドレス固定なので、自動登録プログラムが無い為、2^nサイズである必要はありません。
//
(r39u1)[A01登録敵領域]はスクリプト化が難しいので、将来的に無くなる可能性が高い。
登録敵領域を使いたいのは、主に道中。
道中のobjは128objもあれば十分なので、[A02固定敵領域]の後半を自動登録できる機能にする予定。
(r39u1)現在廃止していないのは、アリス弾(src/mohoufu/boss/option_11_alice_zako_doll_type_a.c)で
[A01登録敵領域]を利用している為廃止できない。
obj_regist_teki();を使用できない。
option_11_alice_zako_doll_type_a.c
option_10_alice_zako_doll_type_b.c
option_40_aya_momiji01.c
option_41_aya_momiji02.c
//
道中の雑魚は[A01登録敵領域]([A02固定敵領域]の後半128)とし、
中ボスの本体、及び中ボスの背景魔方陣(使い魔システムへ移行)は[A02固定敵領域](前半128の固定位置)へ
移動予定。
(使い魔システム(スクリプトから使用可能に拡張する)は[A02固定敵領域]しか使用できない予定。
登録機能をスクリプトで管理すると複雑になりすぎる(遅くなる)為。)
#endif
/*(全スプライトの定義)*/
/*([領域の]先頭[相対オフセットアドレス])*/	/*([一つ前の領域に]接続する)*/	/*([使用する]領域サイズ)*/
#define OBJ_HEAD_00_0x0000_TAMA 		(0) 																/* 登録弾専用スプライトの先頭 */
#define OBJ_HEAD_01_0x0800_TOUROKU		(OBJ_HEAD_00_0x0000_TAMA		+OBJ_POOL_00_TAMA_1024_MAX) 		/* 登録敵専用スプライトの先頭 */
#define OBJ_HEAD_02_0x0900_TEKI_FIX 	(OBJ_HEAD_01_0x0800_TOUROKU 	+OBJ_POOL_01_TOUROKU_0256_MAX)		/* 固定敵専用スプライトの先頭 */
#define OBJ_HEAD_03_0x0a00_KOTEI		(OBJ_HEAD_02_0x0900_TEKI_FIX	+OBJ_POOL_02_TEKI_FIX_0256_MAX) 	/* 固定自機等スプライトの先頭 */
#define OBJ_HEAD_04_0x0a10_PANEL		(OBJ_HEAD_03_0x0a00_KOTEI		+OBJ_POOL_03_KOTEI_0016_MAX)		/* 固定パネル用スプライトの先頭 */
#define OBJ_LAST_99_0x0a48_MAX			(OBJ_HEAD_04_0x0a10_PANEL		+OBJ_POOL_04_PANEL_0056_MAX)		/* 全スプライトの数 */
extern OBJ obj99[OBJ_LAST_99_0x0a48_MAX];	/* 全スプライト */

enum/*(OBJの種類)*/
{
	OBJECT_TYPE_00_TAMA = 0, /* 弾専用スプライト */
	OBJECT_TYPE_01_TEKI, /* 敵専用スプライト */
	OBJECT_TYPE_02_KOTEI, /* 自機等固定スプライト */
	OBJECT_TYPE_03_PANEL, /* パネル用スプライト */
	OBJECT_TYPE_04_MAX/* 全スプライト */
};

/*---------------------------------------------------------
	オブジェバンクシステム
--------------------------------------------------------- */
extern void reflect_sprite_spec(OBJ *sss, u32 bank_offset); /* オブジェクトのバンク設定を反映させる。 */
#endif

#endif /* _OBJ_AREA_H_ */
