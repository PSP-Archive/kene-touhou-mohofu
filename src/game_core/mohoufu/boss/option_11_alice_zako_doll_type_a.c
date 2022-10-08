
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	アリス人形カード
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形 -easy-」
アリスの放った四体の人形が、二回分裂する7way弾を撃つ。
4 x 7 x 7 == 最大 196[弾](妖々夢)
3 x 7 x 7 == 最大 147[弾](模倣風)	//3 x 8 x 8 == 192
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形」	赤鱗弾
アリスの放った六体の人形が、二回分裂する7way弾を撃つ。
6 x 7 x 7 == 最大 294[弾](妖々夢)
5 x 7 x 7 == 最大 245[弾](模倣風)	//5 x 8 x 8 == 320
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形 -hard-」
アリスの放った八体の人形が、二回分裂する7way弾を撃つ。
8 x 7 x 7 == 最大 392[弾](妖々夢)
9 x 7 x 7 == 最大 441[弾](模倣風)	//7 x 8 x 8 == 448
	-------------------------------------------------------
蒼符「博愛のオルレアン人形」	赤鱗弾→緑鱗弾
アリスの放った八体の人形が、三回分裂する7way弾を撃つ。
8 x 7 x 7 x 7 == 最大2744[弾](妖々夢)
2 x 7 x 7 x 7 == 最大 686[弾](模倣風)	//9 x 8 x 8 == 576
	-------------------------------------------------------
	人形が分裂(模倣風)
	弾が分裂(妖々夢)
	現在人形は雑魚を利用しているが、
	このような方式になっているのは、実験中の為。
	-------------------------------------------------------
	実際「分裂」は(弾は全弾配列なので)全弾配列を調べて
	「(角度を)変更」＋「(新たに弾を)追加」するんじゃないかな？
	つまり大雑把に仕組みを言えば、「分裂」弾じゃなくて「追加」弾。
	「分裂」と「追加」だと、結果的に何が違うかと言えば、
	最終的な弾の「表示プライオリティー」に微妙な違いが出る。
	-------------------------------------------------------
	つまり、7way弾に分裂するのではなくて、
	1弾は変身させて、6弾追加するのだと思う。
	-------------------------------------------------------
	ボス共通規格使用データー:
		TUKAIMA_KIKAKU_00_target_x256	基準固定座標 x位置として使用。
		TUKAIMA_KIKAKU_01_target_y256	基準固定座標 y位置として使用。
---------------------------------------------------------*/

#define recursive		user_data05 	/* 分裂回数(0>分裂しない) */
#define radius			user_data06 	/* 円の半径 */

#define i_angle1024 	VR03_i
/*---------------------------------------------------------
	分裂(last)
	-------------------------------------------------------
	BU LLET_UROKO14_00_AOI,
	BU LLET_UROKO14_01_AKA, 	normal
	BU LLET_UROKO14_02_YUKARI,
	BU LLET_UROKO14_03_MIDORI,	luna
//
	BULLET_UROKO14_00_SIRO, 		//白	//BU LLET_UROKO14_00_AOI,		//
	BULLET_UROKO14_01_AKA,			//赤	//BU LLET_UROKO14_01_AKA,		//
	BULLET_UROKO14_02_YUKARI,		//紫	//BU LLET_UROKO14_02_YUKARI,	//
	BULLET_UROKO14_03_AOI,			//青	//BU LLET_UROKO14_03_MIDORI,	//
	BULLET_UROKO14_04_MIZUIRO,		//水	//BU LLET_UROKO14_04_MIZUIRO,	//
	BULLET_UROKO14_05_MIDORI,		//緑	//BU LLET_UROKO14_05_KIIRO, 	//
	BULLET_UROKO14_06_KIIRO,		//黄	//BU LLET_UROKO14_06_dummy, 	//
	BULLET_UROKO14_07_DAIDAI,		//橙	//BU LLET_UROKO14_07_dummy, 	//
---------------------------------------------------------*/
	#if 0
	HATSUDAN_R11_speed256			= (t256(2.0));							/* 弾速 */
	HATSUDAN_R13_angle65536 		= (src->rotationCCW65536);				/* 角度 */
	HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI) + ((cg_VR20_game_difficulty));	/* [青鱗弾] */
	HATSUDAN_R16_n_way				= (7);								/* [7way] [8way] */
	HATSUDAN_R17_div_angle65536 	= (int)(65536/23);					/* 分割角度 (65536/27) (65536/24) */
	bul let_reg ist_multi_vec tor();
	#endif


static OBJ_CALL_FUNC(move_alice_doll_last_burrets)
{
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
	#if 1
	HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	#if 0
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST(TAMA_IRO_03_AOI, TAMA_IRO_01_AKA, TAMA_IRO_02_YUKARI, TAMA_IRO_05_MIDORI);
//	CPU_CA LL(nan_ido);
	#else
	static const u32 codebase_exec[2] =
	{
		// (1)	//	VR04 = ([難易度別定数]);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST(TAMA_IRO_03_AOI, TAMA_IRO_01_AKA, TAMA_IRO_02_YUKARI, TAMA_IRO_05_MIDORI),
	};
	cpu_exec((u32*)&codebase_exec, (1));
	#endif
	HATSUDAN_R15_bullet_obj_type	= BULLET_UROKO14_BASE + (VR04_NAN_IDO_DECODE);		/* [青鱗弾] */

//	HATSUDAN_R16_n_way				= (1);								/* [7way] [8way] */
//	HATSUDAN_R17_div_angle65536 	= (int)(65536/23);					/* 分割角度 (65536/27) (65536/24) */
	#define first_angle_65536 	VR02_j
//	int first_angle_65536;
//	first_angle_65536 = ((src->rotationCCW1024)<<6);
	first_angle_65536 = (src->rotationCCW65536);
//	int VR03_i;
	for (VR03_i=0; VR03_i<(7); VR03_i++)	/* 弾数 */
	{
		enum
		{
			CCC_00_SPEED256 = 0,
			CCC_01_ADD_ANGLE65536,
			CCC_99_MAX
		};
		const int ccc[8][CCC_99_MAX] =
		{
			{ t256(1.00), ((65536*10)/(14))},	// 速度速い
			{ t256(0.50), ((65536* 8)/(14))},	// 速度遅い
			{ t256(1.00), ((65536* 9)/(14))},	// 速度速い
			{ t256(0.75), ((65536* 7)/(14))},	// 速度中
			//
			{ t256(1.00), ((65536* 6)/(14))},	// 速度速い
			{ t256(0.50), ((65536* 5)/(14))},	// 速度遅い
			{ t256(1.00), ((65536* 4)/(14))},	// 速度速い
			{ t256(1.00), ((65536* 7)/(14))},	// [未使用](.align)
		};
		HATSUDAN_R11_speed256				= (ccc[VR03_i][CCC_00_SPEED256]);									/* 弾速 */
		HATSUDAN_R13_angle65536 			= (first_angle_65536+ccc[VR03_i][CCC_01_ADD_ANGLE65536]);			/* 角度 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	#endif
}
/*
	180度反転する。
	７弾に分裂
  A   A    A   A   --- 速度速い

		A------------- 速度中
		|
   A	|	 A	------ 速度遅い
		+
//
*/
/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/
static OBJ_CALL_FUNC(add_zako_alice_doll_2nd_CCW);

static OBJ_CALL_FUNC(move_alice_doll_all)
{
//	jyumyou			= (60);/* 1[秒](60[frame])後に、再分裂 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-60) < src->jyumyou)/* 発弾エフェクト後から[60]カウント未満の弾 */
	/* 移動処理 */
	{
	//	src->rotationCCW1024 += (((src->recursive)&(1))?(10):(-10));/* 人形＆グラ回転 */
	//	mask1024(src->rotationCCW1024);
		src->rotationCCW65536 += (((src->recursive)&(1))?(10<<6):(-10<<6));/* 人形＆グラ回転 */
		mask65536(src->rotationCCW65536);
		{
		//	int bbb_rotationCCW1024;
			int bbb_rotationCCW65536;
		//	bbb_rotationCCW1024 = src->rotationCCW1024-(1024/8);/* -(1024/8) == -45/360度傾ける */
		//	bbb_rotationCCW1024 = src->rotationCCW1024+(1024/8);/*	(1024/8) ==  45/360度傾ける */
		//	mask1024(bbb_rotationCCW1024);
			bbb_rotationCCW65536 = src->rotationCCW65536+(65536/8);/*	(1024/8) ==  45/360度傾ける */
			mask65536(bbb_rotationCCW65536);
			src->radius++;
			#if (0)//
		//	src->cen ter.x256 = src->TUKAIMA_KIKAKU_00_tar get_x256 + ((si n1024((bbb_rotationCCW1024))*(src->radius)));/*fps_factor*/	/* CCWの場合 */
		//	src->cen ter.y256 = src->TUKAIMA_KIKAKU_01_tar get_y256 + ((co s1024((bbb_rotationCCW1024))*(src->radius)));/*fps_factor*/
			#else
		//	{/*(メモ)*/
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536(bbb_rotationCCW65536, &sin_value_t256, &cos_value_t256);
		//		src->center.x256 = src->TUKAIMA_KIKAKU_00_target_x256 + ((sin_value_t256*(src->radius)));/*fps_factor*/
		//		src->center.y256 = src->TUKAIMA_KIKAKU_01_target_y256 + ((cos_value_t256*(src->radius)));/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= ((src->radius)<<8);
			HATSUDAN_R13_angle65536 = (bbb_rotationCCW65536);
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			src->center.x256 = src->TUKAIMA_KIKAKU_00_target_x256 + VR07;/*fps_factor*/		//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			src->center.y256 = src->TUKAIMA_KIKAKU_01_target_y256 + VR06;/*fps_factor*/		//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
			#endif//1076828
		}
	}
	/* おしまい処理 */
	else/* 移動終了 */
	{
		if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* このラインより下からは敵が撃たない */
		{
			if (0 > src->recursive)/* 再分裂する必要あり？ */
			{
				move_alice_doll_last_burrets(src);/* 再分裂しない。ので弾にする。 */
			}
			else/* 再分裂する */
			{
				add_zako_alice_doll_2nd_CCW(src);/* (再帰で)再分裂する */
			}
		}
		src->jyumyou = JYUMYOU_NASI;	/* おしまい */
	//	return;
	}
}

/*---------------------------------------------------------
	敵を追加する(2nd)
---------------------------------------------------------*/
static OBJ_CALL_FUNC(add_zako_alice_doll_2nd_CCW)
{
//	const int add_angle = ( (1024/7) ); /* 加算角度 */	/* ２回目以降の分列数は常に7回 */
	int first_angle65536;	/* 開始角度 */
//	first_angle1024 = (src->rotationCCW1024)+(1024/4);
	first_angle65536 = (src->rotationCCW65536)+(65536/4);
//	int i_angle1024;	/* 積算角度 */
//	for (i_angle1024=(0); i_angle1024<(1024); i_angle1024 += (1024/7)/*add_angle*/) 	/* 弾数 */
	/* 半周を7分割 */
//	for (i_angle1024=(0); i_angle1024<(1024/2); i_angle1024 += (1024/(7*2))/*add_angle*/)	/* 弾数 */
	for (i_angle1024=(0); i_angle1024<(1024/2); i_angle1024 += (1024/(7*2))/*add_angle*/)	/* 弾数 */
	{
		OBJ *h;
		h						= obj_regist_teki();
		if (NULL!=h)/* 登録できた場合のみ */
		{
			h->m_Hit256R			= ZAKO_ATARI02_PNG;
			h->obj_type_set 		= TEKI_16_10+((1)<<2)+((src->recursive)<<2);
			h->atari_hantei 		= (ATARI_HANTEI_TAOSENAI/*1スコア兼用*/);
			h->callback_mover		= move_alice_doll_all;
		//	h->callback_loser		= NULL;
			h->callback_hit_teki	= callback_hit_zako;
		//	h->rotationCCW1024		= (first_angle1024 + i_angle1024);
			h->rotationCCW65536		= (first_angle65536 + (i_angle1024<<6));/*r42とりあえず*/
	//
	//		h->base_score			= score(25*2);/*ダミー*/
			h->zako_hp				= (ZAKO_HP_TAOSENAI);/*(倒せない)*/
	//
			h->jyumyou = HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			{
				/* 初期位置 */
			/*	h->center.x256 =*/ h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
			/*	h->center.y256 =*/ h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
			}
			// [レガシーシステム対応]敵領域だから無駄(?)
			h->TR00_hatudan_spec_data	= (0);/*([レイヤーシステムが働かないようにする]よくわかんない)*/
			h->radius				= (0);
			h->recursive			= ((src->recursive)-1);/* 再分裂回数を1減らす。(テロメア) */
		}
	}
}


/*---------------------------------------------------------
	敵を追加する(1st)
---------------------------------------------------------*/

/**/ OBJ_CALL_FUNC(add_zako_alice_doll_type_a)
{
	#if (1)
	const int aaa_tbl[(4)] =
	{
//		(int)(1024/3), (int)(1024/5), (int)(1024/9), (int)(1024/2), /*[模倣風]*/	/*(オルレアン人形)*/
//		(int)(1024/3), (int)(1024/5), (int)(1024/9), (int)(1024/3), /*(オルレアン人形)*/	/* [現在の方式では無理] */
		(int)(1024/4), (int)(1024/6), (int)(1024/8), (int)(1024/2), /*[妖々夢風]*/	/*(オルレアン人形)*/	/* [現在の方式では無理] */
//		(int)(1024/4), (int)(1024/6), (int)(1024/7), (int)(1024/2), /*[妖々夢風]*/	/*(オルレアン人形)*/	/* [現在の方式では無理] */
		/* 模倣風はr32現在あたり判定意図的に小さくしているので、いくら1面とはいえ
			やっぱ難易度低すぎる気もする。(オルレアン人形)以外妖々夢風にした。 */
	};
	//
	const int add_angle1024 = ( (aaa_tbl[((cg_VR20_game_difficulty)&3)])); /* 加算角度 */	/* ２回目以降の分列数は常に7回 */
//	const int add_angle1024 = (int)(1024/6);	/*(?)*/
	#else/*(ok!)*/
	static const u32 codebase111[3] =
	{
		// (1)	//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((4), (6), (8), (2));/*(Lunatic==オルレアン人形)*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),// R04 = [難易度];
		PACK_NAN_IDO_CONST((4), (6), (8), (2)),
		// (2)	//	 (div65536);/*[初期化セクション以外では速度低下の可能性あり]*/
		MCODE(OP0x17_DIV65536, NAX, R04, R04),//  R04 = 65536 / R04;
	//	NAX
	};
	cpu_exec((u32*)&codebase111, (2));
	const int add_angle1024 = (deg65536to1024((VR04_NAN_IDO_DECODE)));
	#endif

	HATSUDAN_R15_bullet_obj_type = (TEKI_16_10+((0/*2*/)<<2));
//	int i_angle1024;	/* 積算角度 */
	for (i_angle1024=0; i_angle1024<(1024); i_angle1024 += add_angle1024)	/* 一周 */
	{
		OBJ *h;
		h							= obj_regist_teki();
		if (NULL!=h)/* 登録できた場合のみ */
		{
			h->obj_type_set 		= (HATSUDAN_R15_bullet_obj_type);
			h->atari_hantei 		= (ATARI_HANTEI_TAOSENAI/*1スコア兼用*/);
			//
			h->rotationCCW65536		= ((i_angle1024)<<6);/*r42とりあえず*/
			h->m_Hit256R			= ZAKO_ATARI02_PNG;
			//
			//
			h->callback_mover		= move_alice_doll_all;
		//	h->callback_loser		= NULL;
	//		h->callback_hit_teki	= callback_hit_zako;/*(?)*/
	//
	//		h->base_score		= score(25*2);/*ダミー*/
			h->zako_hp			= (ZAKO_HP_TAOSENAI);/*(倒せない)*/
	//
			h->jyumyou = HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			{
				/* 初期位置 */
			/*	h->center.x256 =*/ h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
			/*	h->center.y256 =*/ h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
			}
			// [レガシーシステム対応]敵領域だから無駄(?)
//			h->TR00_hatudan_spec_data			= (0);/*([レイヤーシステムが働かないようにする]よくわかんない)*/
			h->radius				= (0);
			#if 0
		//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST(0, 0, 0, 1);/*(Lunatic==オルレアン人形)*/
		//	CPU_CA LL(nan_ido);
			#else
			static const u32 codebase_exec666[2] =
			{
				// (1)	//	VR04 = ([難易度別定数]);
				MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
				PACK_NAN_IDO_CONST(0, 0, 0, 1),/*(Lunatic==オルレアン人形)*/
			};
			cpu_exec((u32*)&codebase_exec666, (1));
			#endif
			h->recursive			= (VR04_NAN_IDO_DECODE);
		}
	}
}


