
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	敵弾発生基本システム(発弾システム)。[basic bullet create system]
	-------------------------------------------------------
	敵が発弾する場合は、発弾エフェクトがあっても無くても、
	必ず発弾システムを経由して発弾する。
	-------------------------------------------------------
	敵弾はここ以外で発弾する事は出来ない。
---------------------------------------------------------*/

/*(C++で例えるとprivateな関数)*/
#define PRIVATE_FUNC_HATUDAN_SYSTEM(private_func_name) static void private_func_hatudan_system_##private_func_name(void)

/*---------------------------------------------------------
	レーザー関連は仕組みが違いすぎるものの、
	発弾システムと統合する。(C++で例れば同クラスもしくは継承して派生クラス)
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	-------------------------------------------------------
	同期して行動するレーザー類を生成します。
	-------------------------------------------------------
	laser_link_angle();==パチェレーザー。
---------------------------------------------------------*/

global LASER lz[MAX_99_LASER];

/*---------------------------------------------------------
	レーザー
---------------------------------------------------------*/
extern void add_laser_off_void(void)
{
	lz[0].laser_type = LASER_TYPE_00_OFF;/* off */
	lz[1].laser_type = LASER_TYPE_00_OFF;/* off */
}
extern void add_laser_on_void(void)
{
	lz[0].laser_type = LASER_TYPE_01_4_PACHE;/* on */
	lz[1].laser_type = LASER_TYPE_01_4_PACHE;/* on */
}

/*---------------------------------------------------------
	-------------------------------------------------------
	前の弾を追いかける行動をとるレーザー類を生成します。
	-------------------------------------------------------
	laser_chain();==チルノレーザー。
	laser_henyori();==へにょり(誘導)レーザー。
---------------------------------------------------------*/

/*---------------------------------------------------------
	-------------------------------------------------------
---------------------------------------------------------*/


/*---------------------------------------------------------
	角度弾、基本定義
	-------------------------------------------------------
	角度弾では、ベクトル移動をしない。
	代わりに基点座標として使う。
	base基点、origin==原点。
---------------------------------------------------------*/
#define origin									math_vector/*(発弾位置 座標)*/
//	#define hatudan_system_kousadan_angle65536		tmp_angleCCW1024
	#define hatudan_system_kousadan_angle65536		tmp_angleCCW65536

/*---------------------------------------------------------
	移動処理選択。
---------------------------------------------------------*/
static OBJ_CALL_FUNC(move_bullet_hatsudan_effect);
static OBJ_CALL_FUNC(set_mover)
{
	if (0x03==(((src->TR00_hatudan_spec_data)>>12)&0x03))
	{	/* エフェクトなし==発弾開始処理 */
		src->callback_mover 	= NULL;/*(弾は弾幕で移動する為に、本家は恐らく個弾の移動処理はそもそも無い。)*/
		{
			/* 発弾開始直前にあたり判定を有効にする。 */
			/* 非傾き弾は、発弾開始直前に設定。 */
			src->atari_hantei	= (ATARI_HANTEI_TAOSENAI/*スコア兼用*/);/* あたり判定有効 */
			if (src->TR00_hatudan_spec_data & TAMA_SPEC_8000_NON_TILT)/* 非傾き弾 */
			{
				src->m_zoom.y256 = M_ZOOM_Y256_NO_TILT;/* 特殊機能で傾かないようシステム拡張(r33)。 */
			}
			#if (1)/*(発弾エフェクトが無い場合に困る)*/
			src->center.x256 = (src->origin.x256);/*fps_factor*/
			src->center.y256 = (src->origin.y256);/*fps_factor*/
			#endif
		}
	}
	else/* エフェクトあり==(発弾エフェクト処理)*/
	{
		src->callback_mover 	= move_bullet_hatsudan_effect;
	}
}
/*---------------------------------------------------------
	発弾エフェクト
	-------------------------------------------------------
	傾かない弾 / 傾き弾(通常)
---------------------------------------------------------*/
static OBJ_CALL_FUNC(set_mover);
static OBJ_CALL_FUNC(move_bullet_hatsudan_effect)
{
//	hatudan_system_common_hatudan_000(src);
	{
		const int aaabbb = (src->TR03_hatudan_frame_counter);
		#if (0)
		src->center.x256 = (src->origin.x256) + ((si n65536((src->rotationCCW65536))*(aaabbb)) );/*fps_factor*/
		src->center.y256 = (src->origin.y256) + ((co s65536((src->rotationCCW65536))*(aaabbb)) );/*fps_factor*/
		#else
		{
			int sin_value_t256; 	// sin_value_t256 = 0;
			int cos_value_t256; 	// cos_value_t256 = 0;
			int256_sincos65536(src->rotationCCW65536, &sin_value_t256, &cos_value_t256);
			src->center.x256 = (src->origin.x256) + ((sin_value_t256*(aaabbb))>>(((src->TR00_hatudan_spec_data)>>12)&0x03));/*fps_factor*/
			src->center.y256 = (src->origin.y256) + ((cos_value_t256*(aaabbb))>>(((src->TR00_hatudan_spec_data)>>12)&0x03));/*fps_factor*/
		}
		#endif
		src->color32		= ((256-aaabbb)<<(24))|0x00ffffff;
		src->m_zoom.x256	= t256(1.0) + (aaabbb) + (aaabbb);
		src->m_zoom.y256	= t256(1.0) + (aaabbb) + (aaabbb);
	}
	src->TR03_hatudan_frame_counter -= (4);
	if (0 > src->TR03_hatudan_frame_counter)
	{
		src->TR03_hatudan_frame_counter = (0);/*(この後で使うなら)*/
		/*(エフェクトなし に設定する。)*/
		src->TR00_hatudan_spec_data |= (TAMA_SPEC_3000_EFFECT_NONE);
		set_mover(src);
	}
}

/*---------------------------------------------------------
	弾を登録する。
	-------------------------------------------------------
	弾発動時のエフェクト等の関係上、発弾部分は全部纏める必要がある。
	-------------------------------------------------------
	ベクトル弾と角度弾を統合するかもしれない。
---------------------------------------------------------*/


/*---------------------------------------------------------
	標準の角度弾を複数(n way弾)登録する。
	-------------------------------------------------------
	弾の発弾方式は、1ヶ所に纏める予定なのだが、
	現在仕様が決まっていない。
	弾の発弾が、1ヶ所に纏まっていないと、発弾のエフェクトが作れない。
	「発弾のエフェクトが作れない」というのは、
	弾の発弾が、1ヶ所に纏まっていないのに強引に「作ると遅くなる」からやりたくないという意味。
	現在(r33)も速度がネック(遅い)になっているので、そういう事はしない。というか出来ない。
	もちろん1ヶ所に纏まって速度も解消できたら発弾のエフェクトを作る予定。
	現在(r33)の速度低下は、
		サイドのパネルがSDL描画。
		会話がSDL描画。
		Gu回転描画で横sliceしてない。
		ボスがカードシステムに移行出来てないので無駄な処理がある。
	あたりが、主な処理落ち。
	-------------------------------------------------------
	あくまで暫定仕様(r32)
	-------------------------------------------------------
	BULLET_REGIST_06_n_way: 		n way弾の総弾数
		一度に弾を撃つ数。1つしか撃たないなら1。
	BULLET_REGIST_02_angle65536:		開始向き
		１周を65536分割した値(0 ... 65535)でnway弾の発弾開始角度を指定する。
		下向きが0度で半時計回り。(下CCW)
	BULLET_REGIST_04_bullet_obj_type:	弾の種類(具体的にはグラ)の番号

	BULLET_REGIST_00_speed256:		初速(打ち出し速度)

	BULLET_REGIST_07_div_angle65536:	n way弾の分割角度

	BULLET_REGIST_01_speed_offset:	加速度(又は減速度)

---------------------------------------------------------*/

/*---------------------------------------------------------
	弾システム:
	基本弾発生
	-------------------------------------------------------
	仕様： 引数は破壊しない。
---------------------------------------------------------*/

PRIVATE_FUNC_HATUDAN_SYSTEM(regist_single)
{
	OBJ 	*h;
	h											= obj_regist_tama();/* 発弾登録 */
	if (NULL != h)/* 登録できた場合 */
	{
		h->origin.x256							= VR06;/*(発弾位置 座標x)*/
		h->origin.y256							= VR07;/*(発弾位置 座標y)*/
		h->obj_type_set 						= (HATSUDAN_R15_bullet_obj_type);
		h->atari_hantei 						= (ATARI_HANTEI_OFF/*スコア兼用*/);/* あたり判定無効(発弾エフェクト用) */
		reflect_sprite_spec(h, OBJ_BANK_SIZE_00_TAMA);
	//
		h->hatudan_system_kousadan_angle65536	= (HATSUDAN_R13_angle65536);				/* 交差弾用 */
	//	h->rotationCCW1024						= (deg65536to1024(HATSUDAN_R13_angle65536)); /* 「1周が65536分割」から「1周が1024分割」へ変換する。 */	/* (i<<4) deg_360_to_512(90) */
		h->rotationCCW65536						= ( (HATSUDAN_R13_angle65536)); /* 「1周が65536分割」から「1周が1024分割」へ変換する。 */	/* (i<<4) deg_360_to_512(90) */
		h->m_Hit256R							= TAMA_ATARI_JIPPOU32_PNG;
	//
		h->TR01_hatudan_speed65536			= ((HATSUDAN_R11_speed256)<<8); 	/* t65536形式で。 速度 */	/* 初速(打ち出し速度) */
		h->TR03_hatudan_frame_counter		= (0xff);
		h->TR02_hatudan_tra65536			= (HATSUDAN_R12_speed_offset);		/* t65536形式で。 調整減速弾 */ 	/* この方式になるか検討中 */
		h->TR00_hatudan_spec_data			= (HATSUDAN_R14_tama_spec); 		/* 弾の基本所属能力を設定する。 */
		set_mover(h);
	}
}


/*---------------------------------------------------------
	弾システム:
	偏り n way 弾
	紅魔郷の n way 弾システムは、どうもこういうものっぽい。
	★ 5面ボス咲夜の「通常攻撃1」及び「通常攻撃2」で
	咲夜が生成した魔方陣は、 5way とか 6way とか 弾を撃ってくるが、
	一気に描かないで、左右で2回にかけて描く。
	つまり左右でプライオリティー(弾の重なり具合)が違う。

	★ 5面中-ボス咲夜の「通常攻撃」は(青ナイフ、赤クナイ共に)左右が固定の固定弾なので、
	こういう n way 弾だと都合が良い。(旧作のなぎ払いを再現するのも都合が良い)
	★ 5面中-ボス咲夜の「ミスディレクション」も、正確な自機狙いが保証されるので、
	こういう n way 弾だと都合が良い。
	-------------------------------------------------------
	以下は基本部分で撃てるのか、それとも若干改変したものなのか不明(たぶん基本部分で撃てる)

	★ 5面ボス咲夜の「通常攻撃1」のピンクのナイフは基本部分で撃てるのか
	それとも基本部分を若干改変したものかは判らないが殆ど同じもの。

	★ ルーミアの紅魔郷の「ナイトバード」は基本部分で撃てるのか
	それとも基本部分を若干改変したものかは判らないが殆ど同じもの。
	-------------------------------------------------------
	仕様： 下記の引数を破壊するので注意
	HATSUDAN_R13_angle65536 [破壊]
---------------------------------------------------------*/

PRIVATE_FUNC_HATUDAN_SYSTEM(regist_katayori_n_way)
{
	#if (0)/*[ここ有効にすれば、たぶん復旧可能]*/
	const int j_angle65536	= (HATSUDAN_R13_angle65536);/* 始めの開始角度、向き */
	#endif
	{
		int i;
		for (i=0; i<(HATSUDAN_R16_n_way); i++)/* n way弾を登録する。 */
		{
			private_func_hatudan_system_regist_single();
			/* 次の角度 */
			HATSUDAN_R13_angle65536 += (HATSUDAN_R17_div_angle65536);
		//	mask65536(HATSUDAN_R13_angle65536);たぶん要らない。
		}
	}
	#if (0)/*[ここ有効にすれば、たぶん復旧可能]*/
	HATSUDAN_R13_angle65536 	= (j_angle65536);/*[復旧]*/
	#endif
}
/*
	弾システム:
	n way 弾
	n way 弾は、一気に生成しないで、偏り n way 弾を2回呼ぶ事で生成する。
	これは奇数弾の場合の狙い誤差を最小にする為に必要な措置。
	奇数弾の積算誤差が大きいと自機狙い弾のつもりで生成しても
	多弾生成時の積算誤差で角度がずれるので、自機を狙わなくなってしまう。
	プライオリティー(弾の重なり具合)を調べると原作でもこの方式を採用している事がわかる。
	原作では弾の生成順にプライオリティー(ZバッファなのでZ値)を決めている。
	-------------------------------------------------------
	仕様： 下記の引数を破壊するので注意
	HATSUDAN_R13_angle65536 	[破壊]
	HATSUDAN_R16_n_way			[破壊]
	HATSUDAN_R17_div_angle65536 [破壊]
*/

PRIVATE_FUNC_HATUDAN_SYSTEM(regist_n_way)
{
	const int j_angle65536	= (HATSUDAN_R13_angle65536);/* 開始向き */
	const int j_n_way		= (HATSUDAN_R16_n_way)&0xff;/* 弾数 */
	const int j_n_way_harf	= (j_n_way>>1)&0xff;/* 弾数 */
	//
	{
		/* 偶数弾の場合の差分を生成
			偶数弾の場合、分割角度の半分の角度がオフセット角度。
			奇数弾の場合オフセット角度は必ずゼロ。
		*/
	//	const int j_guusuu_harf_angle_offset = ((HATSUDAN_R17_div_angle65536)>>1);	/* 偶数弾なら分割角の半分が差分、奇数弾はなし */
		const int j_guusuu_harf_angle_offset = (0==(j_n_way&1)) ? ((HATSUDAN_R17_div_angle65536)>>1) : (0); /* 偶数弾なら分割角の半分が差分、奇数弾はなし */
		/*(右半分を生成)*/
		/* 右半分(差分が正値の場合) */
		HATSUDAN_R13_angle65536 	= j_angle65536 + j_guusuu_harf_angle_offset;/* 偶数弾 & 奇数弾 */
		HATSUDAN_R16_n_way			= (j_n_way - (j_n_way_harf));	/* 例えば 7way なら 4弾描く。 8way なら 4弾描く。 */
		private_func_hatudan_system_regist_katayori_n_way();
		/*(左半分を生成)*/
		#if 0/* デバッグ用 */
			HATSUDAN_R15_bullet_obj_type ^= 2;/* デバッグ用: 同じグループだけど、左右で違う色の弾にしてみる。 */
		#endif
		/* 差分角度を逆にする。(逆周りに描くway弾になる) */
		HATSUDAN_R17_div_angle65536 = (65536)-(HATSUDAN_R17_div_angle65536);
		#if 1
		HATSUDAN_R13_angle65536 	= j_angle65536 - j_guusuu_harf_angle_offset;/* 偶数弾 & 奇数弾 */
		/* 左半分(差分が正値の場合) */
		if (0!=(j_n_way&1))/* 奇数弾 */
		{
			HATSUDAN_R13_angle65536 += HATSUDAN_R17_div_angle65536;/* 奇数弾(は1弾少ないのでずらす) */
		}
	//	else/* 偶数弾 */
	//	{;/* なにもしない */}
	//	HATSUDAN_R13_angle65536 	= j_angle65536 + ((0==(j_n_way&1))?(-j_guusuu_harf_angle_offset):(HATSUDAN_R17_div_angle65536));
		HATSUDAN_R16_n_way			= ( 		 (j_n_way_harf));	/* 例えば 7way なら 3弾描く。 8way なら 4弾描く。 */
		private_func_hatudan_system_regist_katayori_n_way();
		#endif
	}
	#if (0)/*[ここ有効にすれば、たぶん復旧可能]*/
	HATSUDAN_R13_angle65536 	= (j_angle65536);/*[復旧]*/
	HATSUDAN_R16_n_way			= (j_n_way);/*[復旧]*/
	HATSUDAN_R17_div_angle65536 = (65536)-(HATSUDAN_R17_div_angle65536);/*[たぶん復旧]*/
	#endif
}
/*(C++で例えるとここだけpublic)*/
extern void hatudan_system_regist_tama(int set_addressing)
{
	if (HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE==set_addressing)
	{private_func_hatudan_system_regist_single();}
	else
	if (HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY==set_addressing)
	{private_func_hatudan_system_regist_katayori_n_way();}
	else
//	if (HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY==set_addressing)
	{private_func_hatudan_system_regist_n_way();}
}
