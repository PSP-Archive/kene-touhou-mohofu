
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	使い魔系は、規格を共通化する必要がある。
	(r39u1)
	ToDo:
	使い魔システムはスクリプト上から、呼び出し可能とし、
	スクリプト外の中ボスからもコントロール可能にする必要がある。
	-------------------------------------------------------
	魅魔 オプション
	輝夜 オプション
	-------------------------------------------------------
	咲夜 ばら撒き1弾 オプション
	-------------------------------------------------------
	ばら撒き 速度遅い
	寿命	 長い
	-------------------------------------------------------
    めも1:密着米(5)弾
        青米弾                  緑米弾
        右回り                  左回り
        (+90度)                 (-45度)

            緑米弾          青米弾
            左回り          右回り
            (+45度)         (0度)
    -------------------------------------------------------
    めも2:密着クナイ(6)弾   [横の壁で反射する]
        赤クナイ弾              青クナイ弾
        右回り                  左回り

            青クナイ弾      赤クナイ弾
            左回り          右回り
	-------------------------------------------------------
	咲夜 ばら撒き2弾 オプション
	-------------------------------------------------------
	ばら撒き 速度速い
	寿命	 短い
	-------------------------------------------------------
    めも1:密着米(5)弾
        青米弾                  緑米弾
        右回り                  左回り
        (+90度)                 (-45度)

            緑米弾          青米弾
            左回り          右回り
            (+45度)         (0度)
    -------------------------------------------------------
    めも2:密着クナイ(6)弾   [横の壁で反射する]
        赤クナイ弾              青クナイ弾
        右回り                  左回り

            青クナイ弾      赤クナイ弾
            左回り          右回り
	-------------------------------------------------------
	ボス共通規格使用データー:
		TUKAIMA_KIKAKU_00_target_x256	目標x座標 x位置として使用。
		TUKAIMA_KIKAKU_01_target_y256	目標y座標 y位置として使用。
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(common_create_item);/*(boss_item.c)*/

/*---------------------------------------------------------
	使い魔敵やられ
---------------------------------------------------------*/
#if 0
static OBJ_CALL_FUNC(lose_mima_doll)
{
//	/* easyはボムを出さなくて済む位軟らかくした */
	#if 1
	item_create(src, SP_ITEM_05_TENSU, 5, ITEM_MOVE_FLAG_06_RAND_XY);
//	item_create(src, SP_ITEM_00_P001, 5, ITEM_MOVE_FLAG_06_RAND_XY);
	#else
	{	int i;
		for (i=0; i<(5); i++)
		{
			item_create_random_table(src);
		}
	}
	#endif
}
#endif


// 魅魔: 輝夜:
#define shot_angle65536 			user_data02 	/*(使い魔共通) ショットを撃つ方向を保持 */
//#define rotate_angle1024			user_data03 	/* ボスを中心として、回転角度。(下CCW1024形式) */
#define rotate_angle65536			user_data03 	/* ボスを中心として、回転角度。(下CCW1024形式) */
#define now_hankei_256				user_data05 	/* 現在半径t256()形式[pixel] */
#define set_hankei_256				user_data06 	/* 指定半径t256()形式[pixel] */


// 咲夜: ばら撒き1弾 / ばら撒き2弾

enum
{
	AO_AKA_MASK 			= 0x01,
	MODE_TYPE_MASK			= 0x02,
	//
	MODE_TYPE_00_BARAMAKI01 = 0x00,
	MODE_TYPE_01_BARAMAKI02 = 0x02,
};
	#define AO_OR_AKA	(src->set_hankei_256 & AO_AKA_MASK)/* [青赤情報] */
//
/*---------------------------------------------------------
	子供魔方陣 カード
---------------------------------------------------------*/

/*---------------------------------------------------------
	咲夜: ばら撒き1弾 / ばら撒き2弾
---------------------------------------------------------*/
static OBJ_CALL_FUNC(tama_uti_sakuya_tukaima_baramaki)
{
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
		/* ここは 6 wayではなくて、 3 way を2回追加する。でないとプライオリティーが変になる。 */
	//	HATSUDAN_R16_n_way					= (2+difficulty);						/* [2-5way](r32) */
	//	HATSUDAN_R16_n_way					= (3);		/* [破壊] */				/* [5way] */ /* [3way x 2] */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 					/* 密着弾(r32)6.4 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/256); 					/* 密着弾(もっと密着)4 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/512); 					/* 密着弾(もっと密着)2 */
// MODE_TYPE_00_BARAMAKI01
//		HATSUDAN_R11_speed256				= (t256(1.5))+((((cg_VR20_game_difficulty))<<6));		/* 弾速(r32/r33) */
		HATSUDAN_R11_speed256				= (t256(0.75))+((((cg_VR20_game_difficulty))<<5));		/* 弾速(r35) */
// MODE_TYPE_01_BARAMAKI02
	//	HATSUDAN_R11_speed256				= (t256(1.5))+(((difficulty)<<6));		/* 弾速(r32) */
//		HATSUDAN_R11_speed256				= (t256(2.0))+((((cg_VR20_game_difficulty))<<6));		/* 弾速(r33) */
	//	HATSUDAN_R11_speed256				= (t256(1.0))+((((cg_VR20_game_difficulty))<<5));		/* 弾速(r35) */
//
	if (MODE_TYPE_00_BARAMAKI01==((src->set_hankei_256) & MODE_TYPE_MASK))
	{
		HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI) + (AO_OR_AKA) + (AO_OR_AKA); 	/* [青緑米弾] */
		HATSUDAN_R16_n_way					= (5);		/* [破壊] */				/* [5way] */
	}
	else
	{
		HATSUDAN_R11_speed256 += (t256(0.25));
		HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + (AO_OR_AKA) + (AO_OR_AKA);	/* [青赤クナイ弾] */
		HATSUDAN_R16_n_way					= (6);		/* [破壊] */				/* [3way x 2] */
	}
	HATSUDAN_R12_speed_offset				= (0);/*(テスト)*/
	HATSUDAN_R13_angle65536 				= (src->shot_angle65536);			/* [破壊] */
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	{
		const u16 kakusan_tbl[4] =
		{(int)(65536/512), (int)(65536/512), (int)(65536/256), (int)(65536/128)};		// Lunatic はかなり拡散する。
		HATSUDAN_R17_div_angle65536 		= kakusan_tbl[(cg_VR20_game_difficulty)];		/* [破壊] */		/* 密着弾(もっと密着)2 */
	}
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
}

/*---------------------------------------------------------
	魅魔: ばら撒き弾
---------------------------------------------------------*/
//		HATSUDAN_R11_speed256				= (t256(1.5))+(((difficulty)<<6));	/* 弾速 */
//		HATSUDAN_R13_angle65536 			= ((src->shot_angle65536) );			/* */
//		HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [赤クナイ弾] */
//		HATSUDAN_R16_n_way					= (2+difficulty);					/* [2-5way] */
//		HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 				/* 密着弾 */
//		bullet_regist_multi_vector_direct();

static OBJ_CALL_FUNC(tama_uti_mima_tukaima_baramaki)
{
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
//
//	/*[r35要半分速]*/HATSUDAN_R11_speed256				= t256(1.5)+((cg_VR20_game_difficulty)<<6); 	/* 弾速 */
	/*[r35半分速]*/HATSUDAN_R11_speed256				= t256(0.75)+((cg_VR20_game_difficulty)<<6);	/* 弾速 */
	HATSUDAN_R12_speed_offset			= (0);/*(テスト)*/
	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [破壊] */
	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);			/* [赤クナイ弾] */
	HATSUDAN_R16_n_way					= (2+(cg_VR20_game_difficulty));	/* [破壊] */	/* [2-5way] */
	HATSUDAN_R17_div_angle65536 		= (int)(65536/160); 				/* [破壊] */	/* 密着弾 */
//	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
}

/*---------------------------------------------------------
	アリス: 交差弾
---------------------------------------------------------*/
static OBJ_CALL_FUNC(tama_uti_alice_tukaima_kousa_dan)
{
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
//
//	/*[r35要半分速]*/HATSUDAN_R11_speed256				= t256(1.5)+((cg_VR20_game_difficulty)<<6); 	/* 弾速 */
//	/*[r35半分速]*/HATSUDAN_R11_speed256				= t256(0.75)+((cg_VR20_game_difficulty)<<6);	/* 弾速 */
	/*[r35半分速]*/HATSUDAN_R11_speed256				= t256(0.75);	/* 弾速 */
	HATSUDAN_R12_speed_offset			= (0);/*(テスト)*/
//	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [破壊] */
	HATSUDAN_R13_angle65536 			= (src->shot_angle65536);		/* [破壊] */
	//
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* 弾グラ */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	//
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* 弾グラ */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
}

/*---------------------------------------------------------
	輝夜: 重力弾
---------------------------------------------------------*/

static OBJ_CALL_FUNC(tama_uti_kaguya_tukaima_gin_tama)
{
/*
0:easy	   f  16回に1回発弾。
1:normal   7   8回に1回発弾。
2:hard	   3   4回に1回発弾。
3:lunatic  1   2回に1回発弾。
*/
	if (0==(((1<<(4-cg_VR20_game_difficulty))-1) & ((src->jyumyou>>3))))
//	if ((cg_VR20_game_difficulty+1) > ((src->jyumyou>>3)&0x03))
	{
		set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
		VR0e = (src->shot_angle65536);/*(1024to65536)*/
		#if (1)
		static /*const*/ u32 codebase_exec[14] =
		{
			//---------//set_com mon_gin_tama_void();/*(共通部分)*/
		//	使用レジスタ:	R0e 	src_shot_angle65536 開始地点
			// (01) HATSUDAN_R11_speed256					= t256(1.0);//t256(1+difficulty)/*(3+difficulty)*/ /*(4+difficulty)*/;
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
			(t256(1.00)),
			// (02) VR12 = ra _nd();
			MCODE(OP0x15_RAND_VALUE, NAX, R12, NAX),
			// (03) VR12 = (VR12 & 0x03);
			MCODE(OP0x1d_ANDM_PD, 0x03, R12, R12),/*(ショートメモリアドレッシング)*/
			// (04) HATSUDAN_R12_speed_offset				+= (2);//t256(0.04)/*10*/ ((ra_nd()&0x03)+1);
			MCODE(OP0x01_MOVER_PD, (u8)(+2), R12, R12), /*(インデックス付)*/
			// (05) VR13 = (VR0e & ((65536/4)-1));
			MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R0e),
			(((65536/4)-1)),
			// (06) HATSUDAN_R13_angle65536 				= R13 + (65536/4)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),/*(ロングメモリアドレッシング専用命令)*/
			((65536/4)+(65536/8)),
			// (07) HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
			// (08) HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* 弾グラ */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
			((BULLET_MINI8_BASE + TAMA_IRO_03_AOI)),
			//---------//
			// (09) (1弾撃つ)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		//	NAX/*(終了)*/
		};
		cpu_exec((u32*)&codebase_exec, (9));
		#endif
	}
}


/*---------------------------------------------------------
	使い魔敵 攻撃のみ
---------------------------------------------------------*/

static OBJ_CALL_FUNC(spell_T08_NULL)
{
	/*(攻撃しない)*/
}
static OBJ_CALL_FUNC(spell_kaguya_doll_gin_tama)
{
	/*	旧作 & 咲夜風、回転ショット */
	if (0x0ff < src->jyumyou)/* 0x100未満は共通規格上撃たない */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* 次のショットを撃つまでの間隔、時間。 */
		{
			src->shot_angle65536 -= ((int)(65536/64));		/* cv1024r(10)*/
			tama_uti_kaguya_tukaima_gin_tama(src);
		}
	}
}

//	if ((u32)(0x01ff/3) < src->jyumyou)/* 最後の 1/3 時間は撃って来ない。 */
static OBJ_CALL_FUNC(spell_mima_doll_baramaki)
{
	/*	旧作 & 咲夜風、回転ショット */
	if (0x0ff < src->jyumyou)/* 0x100未満は共通規格上撃たない */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* 次のショットを撃つまでの間隔、時間。 */
		{
			src->shot_angle65536 += (65536/18); /* ショットを撃つ方向を、回転させる。 */
			tama_uti_mima_tukaima_baramaki(src);
		}
	}
}

static OBJ_CALL_FUNC(spell_sakuya_doll_baramaki)
{
	/*	旧作 & 咲夜風、回転ショット */
	if (0x0ff < src->jyumyou)/* 0x100未満は共通規格上撃たない */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* 次のショットを撃つまでの間隔、時間。 */
		{
			src->shot_angle65536 += ((AO_OR_AKA)?(-(65536/18)):((65536/18)));	/* ショットを撃つ方向を、回転させる。 */
			tama_uti_sakuya_tukaima_baramaki(src);
		}
	}

}
static OBJ_CALL_FUNC(spell_alice_doll_kousa_dan)
{
	/*	旧作 & 咲夜風、回転ショット */
	if (0x0ff < src->jyumyou)/* 0x100未満は共通規格上撃たない */
	{
		if (0 == ((src->jyumyou) & 0x07))	/* 次のショットを撃つまでの間隔、時間。 */
		{
		//	src->shot_angle65536 -= ((int)(65536/64));		/* cv1024r(10)*/
//			src->shot_angle65536 += ((int)((2)*64));/*64==(65536/1024)*/		/* cv1024r(10)*/
		//	src->shot_angle65536 = ((src->rotate_angle1024+128)<<6);/*(外側ショット45度傾ける)*/	/*64==(65536/1024)*/
			src->shot_angle65536 = (src->rotate_angle65536 + (128<<6));/*(外側ショット45度傾ける)*/	/*64==(65536/1024)*/
			tama_uti_alice_tukaima_kousa_dan(src);
		}
	}
}




/*---------------------------------------------------------
	使い魔敵 移動のみ
---------------------------------------------------------*/
static /*extern*/ OBJ_CALL_FUNC(move_tukaima00)
{
	//------------------
	HATSUDAN_R11_speed256	= (((src->now_hankei_256)));/*(t256形式)*/
//	HATSUDAN_R13_angle65536 = deg1024to65536((src->rotate_angle1024));
	HATSUDAN_R13_angle65536 = ((src->rotate_angle65536));
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	src->center.x256 = (src->TUKAIMA_KIKAKU_00_target_x256) + VR07;//sin_value_t256 // 縦
	src->center.y256 = (src->TUKAIMA_KIKAKU_01_target_y256) + VR06;//cos_value_t256 // 横
	//------------------
	//define now_hankei_256 t256(45)			/* 半径 */
	if (0 < (src->set_hankei_256))
	{
		if ((src->set_hankei_256) > (src->now_hankei_256))		{src->now_hankei_256 += t256(1);};
	}
	else
	{
		if (-(src->set_hankei_256) < (src->now_hankei_256)) 	{src->now_hankei_256 -= t256(1);};
	}
}

/*---------------------------------------------------------
	オプション位置、回転移動 共通部分
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_option_rotate)
{
	/* オプション位置、回転移動 */
//	src->rotate_angle1024 += (2);
//	mask1024(src->rotate_angle1024);
	src->rotate_angle65536 += (2<<6);
	mask65536(src->rotate_angle65536);
	/* オプション位置、移動 */
	move_tukaima00(src);
}
/*---------------------------------------------------------

---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_sakuya01_doll_T04_T05)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(攻撃処理/時間経過で終了。ボスを倒すと皆破壊される。)*/
	#if 1
	/* 魔方陣回転アニメーション */
//	src->rotationCCW1024--;/* 右回り */
//	src->rotationCCW1024 += (((AO_OR_AKA)<<2)-2);
//	mask1024(src->rotationCCW1024);
	src->rotationCCW65536 += ((((AO_OR_AKA)<<2)-2)<<6);
	mask65536(src->rotationCCW65536);
	#endif
	/* オプション位置、回転移動 */
	/* オプション位置、移動 */
	move_tukaima00(src);
}

/*---------------------------------------------------------
	子供魔方陣 移動 共通部分
---------------------------------------------------------*/



/*---------------------------------------------------------
	移動タイプ01: rotate from boss posion.
	-------------------------------------------------------
	ボスの周りを回転する。
	-------------------------------------------------------
	宝物 敵移動
	子供魔方陣01 移動
	子供魔方陣 移動
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kaguya01_doll_rotate_from_boss)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(攻撃処理/時間経過で終了。ボスを倒すと皆破壊される。)*/
	move_option_rotate(src);
}


/*---------------------------------------------------------
	移動タイプ02: radius from fixed posion.
	-------------------------------------------------------
	固定位置から半径分移動する。
	-------------------------------------------------------
	子供魔方陣02 移動
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kaguya02_doll_radius_from_fixed)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(攻撃処理/時間経過で終了。ボスを倒すと皆破壊される。)*/
	/* オプション位置、回転移動 */
	/* オプション位置、移動 */
	if (0x2ff == src->jyumyou)
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
	//	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK02_JIKI_BOMBER;/*(流用する)*/	CPU_CALL(cpu_voice_play);
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;/*(流用する)*/		CPU_CALL(cpu_voice_play);
	}
	if (0x2ff > src->jyumyou)
	{
		move_tukaima00(src);
	}
}


/*---------------------------------------------------------
	子供魔方陣07 移動
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_alice01_doll_T0f)
{
	boss_control_check_tukaima_kougeki_time_out(src);/*(攻撃処理/時間経過で終了。ボスを倒すと皆破壊される。)*/
	/* オプション位置、回転移動 */
//	src->rotate_angle1024 += (3-(cg_VR20_game_difficulty));/*(加算分「標準+2に加える」)*/
	src->rotate_angle65536 += ((3-(cg_VR20_game_difficulty))<<6);/*(加算分「標準+2に加える」)*/
	/*(多少[+3]なら、回転が速い方が間隔が広がり多分簡単。)*/
	move_option_rotate(src);
	src->set_hankei_256--;
}


/*---------------------------------------------------------
	子供魔方陣01/02 登録共通部分
---------------------------------------------------------*/
//	#define ADD_ANGLE		(341)	/* 1周を 3分割した角度、341.33 == 1024/3  */
//	#define ADD_ANGLE		(171)	/* 1周を 6分割した角度、170.66 == 1024/6  */
//	#define ADD_ANGLE205	(205)	/* 1周を 5分割した角度、204.80 == 1024/5  */
//	#define ADD_ANGLE		(51)	/* 1周を20分割した角度、 51.20 == 1024/20 */
//	#define ADD_ANGLE043	(43)	/* 1周を24分割した角度、 42.66 == 1024/24 */	/* 1日 は 24 時間 */

typedef struct
{
	u32 loop_start; 	/*(開始角度)*/
	u32 loop_stop;		/*(終了角度)*/
	u32 loop_step;		/*(増分角度)*/
	u32 add_pattern256; /*(グラ加算量)*/
	//
	int limit_hankei_256;	/*(最大半径)*/
	int limit_move_jyumyou;
	void (*move_callback)(OBJ *sss);
	void (*kougeki_callback)(OBJ *sss);
} tukaima_status_BBB;
static tukaima_status_BBB tukaima_status[(16/*16*/)] =/*(8)*/
{
/*T00 T00*/ {0, 0, 0, (0), 0, 0, 0, 0, },// TUKAIMA_00_OFF
/*T0a T01*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(未定)*/
/*T0b T02*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(未定)*/
/*T0c T03*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(未定)*/
//
/*T05 T04*/ {((1024*3/4))+0,			((1024*3/4)+((1024/2)+1)),	(1024/6),	(0x000), t256(64),		(0x04ff),			move_sakuya01_doll_T04_T05, 			spell_sakuya_doll_baramaki},/*(sakuya)*/	/* 4つ */ /* 制限時間(長い) (0x03ff) */
/*T06 T05*/ {((1024*3/4))+0,			((1024*3/4)+((1024/2)+1)),	(1024/6),	(0x000), t256(64),		(0x04ff),			move_sakuya01_doll_T04_T05, 			spell_sakuya_doll_baramaki},/*(sakuya)*/	/* 4つ */ /* 制限時間(長い) (0x03ff) */
/*T08 T06*/ {0, 						(1024), 					(1024/24),	(0x055), 0, 0, 0, 0, },/*(aya)*/ /*(0x55==((1024*256)/(24*128)))*/	/*([未使用])*/
/*T0d T07*/ {0, 0, 0, (0), 0, 0, 0, 0, },/*(未定)*/
//
/*T01 T08*/ {0, 						(1024), 					(1024/5),	(0x100), t256(45),		(0x01ff),			move_kaguya01_doll_rotate_from_boss,	spell_T08_NULL},			/*(kaguya)*/	/* 指定半径 45[pixel] */	/* 制限時間 */
/*T02 T09*/ {0, 						(1024), 					(1024/5),	(0x000), t256(45+48),	(0x02ff),			move_kaguya01_doll_rotate_from_boss,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* (0x01ff)制限時間 */ /* 一周 */
/*T0e T0a*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/16),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* 指定半径 224[pixel] 256[pixel] */ /* 配置範囲(上を中心として1/3周) */
/*T0f T0b*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/18),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* 指定半径 224[pixel] 256[pixel] */ /* 配置範囲(上を中心として1/3周) */
//
/*T03 T0c*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/24),	(0x000), t256(32*7),	(0x02ff)-(1024/3),	move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* 指定半径 224[pixel] 256[pixel] */ /* 配置範囲(上を中心として1/3周) */
/*T09 T0d*/ {((1024/2)-(1024*1/6)), 	((1024/2)+(1024*1/6)),		(1024/24),	(0x000), -t256(32*7),	(0x08ff),			move_kaguya02_doll_radius_from_fixed,	spell_kaguya_doll_gin_tama},/*(kaguya)*/	/* 指定半径 224[pixel] 256[pixel] */ /* 配置範囲(上を中心として1/3周) */
/*T04 T0e*/ {0, 						(1024), 					(1024/5),	(0x000), t256(45),		(0x02ff),			move_kaguya01_doll_rotate_from_boss,	spell_mima_doll_baramaki},/*(mima)*/		/* 指定半径 45[pixel] */ /* 制限時間 / 予想以上に速く消える位に。(r33) (0x01ff) */ /* 一周 */
/*T07 T0f*/ {0, 						(1024), 					(1024/3),	(0x000), t256(32),		(0x08ff),			move_alice01_doll_T0f,					spell_alice_doll_kousa_dan},/*(alice)*/ 	/* (0x01ff)制限時間 */ /* 一周 */
};


/*---------------------------------------------------------
	(使い魔システム)敵を追加する。
---------------------------------------------------------*/

#define i_angle1024 	VR03_i
#define i_type256		VR02_j
#define even_or_odd 	VR08

extern OBJ_CALL_FUNC(tukaima_system_add_dolls)
{
//	card.tukaima_used_type &= 0x07;
	card.tukaima_used_type &= 0x0f;
	//
//	int even_or_odd;
	even_or_odd = 0;/*even_or_odd==blue_or_red [青赤情報] */
//	int i_type256;
	i_type256 = 0x000;/*(グラ初期パターン)*/
//	u32 i_angle1024;	/* 積算角度 */
	for (
		i_angle1024=tukaima_status[card.tukaima_used_type].loop_start;
		(unsigned)i_angle1024 < (unsigned)tukaima_status[card.tukaima_used_type].loop_stop;
		i_angle1024 += tukaima_status[card.tukaima_used_type].loop_step
		) /* 一周 */
	{
		/*(とりあえず使用数制限)*/
	//	if (16 > card.tukaima_now_counts)
		{
			OBJ *h;
			h							= obj_regist_teki();
			/*(使い間は[A02]汎用領域ではマズイ。[A01]固定領域に変更する必要がある。)*/
			if (NULL!=h)/* 登録できた場合のみ */
			{
	//			card.tukaima_now_counts++;
			//	h->rotate_angle1024 	= ((i_angle1024) & (1024-1));
				h->rotate_angle65536	= (((i_angle1024) & (1024-1))<<6);/*r42とりあえず*/
				// 基準位置(輝夜)
				h->TUKAIMA_KIKAKU_00_target_x256 = (src->center.x256);
				h->TUKAIMA_KIKAKU_01_target_y256 = (src->center.y256);
				//
				h->m_Hit256R			= ZAKO_ATARI16_PNG;
				h->obj_type_set 		= BOSS_20_YOUSEI1_SYOUMEN;
				#if (1)/*(追加部分)*/
				h->obj_type_set 		+= (((i_type256)>>8) & 0x07);/*(グラは最大8パターン)*/
				i_type256				+= (tukaima_status[card.tukaima_used_type].add_pattern256);
				#endif
				h->atari_hantei 		= (1/*スコア兼用*/);
				//
				h->callback_loser		= common_create_item;//lose_mima_doll;
				h->callback_hit_teki	= callback_hit_zako;
				//
				h->now_hankei_256		= t256(0);			/* 現在半径  0[pixel] */
				h->shot_angle65536		= (0);
			//							= ((8*1024)-1); 	/* 8192==(8*1024) */
			//							= ((2*1024)-1); 	/* 8192==(8*1024) (r36)やわらかい */
			//							= ((3*1024)-1); 	/* 8192==(8*1024) */	/* 硬いけど倒せる */
			//							= (((difficulty+1)<<10)-1); 	/* 8192==(8*1024) */	/* 硬いけど倒せる */
				/* 難度上がると微妙に硬くなる(==倒すのにそれだけ時間がかかる) */
			//							= (((1024)+((cg_VR20_game_difficulty)<<8))-1);	/* 8192==(8*1024) */	/* 硬いけど倒せる */
				h->zako_hp				= (((3*1024)+((cg_VR20_game_difficulty)<<8))-1); /* 8192==(8*1024) */	/* 硬いけど倒せる */
				//
				/*---------------------------------------------------------
				子供魔方陣01/02 登録共通部分
				---------------------------------------------------------*/
			//	set_score_common(h);//static OBJ_CALL_FUNC(set_score_common)
			//				= adjust_score_by_difficulty( ( 40));	/* 40万 */
			//				= adjust_score_by_difficulty( (  5));	/* 5万 (計30万==6x5万) (r33) */
			//				= adjust_score_by_difficulty( ( 50));	/* 50万 (計300万==6x50万) (r32) */
			//				= adjust_score_by_difficulty( ( 50));	/* 50万 (計300万==6x50万) */
			//				= difficulty_score_tbl[(cg_VR20_game_difficulty)];	/* 難易度によるが、かなり稼げる。 */
				//
				/* easy 10万 (計 50万==5x 10万) (r32) */	/* easy 1万 (計 5万==5x 1万) (r33) */
				/* norm 30万 (計150万==5x 30万) (r32) */	/* norm 3万 (計15万==5x 3万) (r33) */
				/* hard 50万 (計250万==5x 50万) (r32) */	/* hard 5万 (計25万==5x 5万) (r33) */
				/* luna100万 (計500万==5x100万) (r32) */	/* luna10万 (計50万==5x10万) (r33) */
			//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((10), (30), (50), (100));/*(r32)*/
				VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((1), (3), (5), (10));/*(r33)*/
				CPU_CALL(nan_ido);
				VR04_NAN_IDO_DECODE = VR04_NAN_IDO_DECODE * score(10000);	/* x1万[pts] */
				h->base_score	= VR04_NAN_IDO_DECODE;
				{
					h->callback_mover					= tukaima_status[card.tukaima_used_type].move_callback;
					h->callback_kougeki 				= tukaima_status[card.tukaima_used_type].kougeki_callback;
					h->set_hankei_256					= tukaima_status[card.tukaima_used_type].limit_hankei_256;
					h->jyumyou	= tukaima_status[card.tukaima_used_type].limit_move_jyumyou;
				}
			/* 特別初期化があるものは初期化する。 */
				const void *aaa[(16/*16*/)] =
				{
				/*00 T00*/	&&label_continue_T00,
				/*0a T01*/	&&label_continue_T00,
				/*0b T02*/	&&label_continue_T00,
				/*0c T03*/	&&label_continue_T00,
						//
				/*05 T04*/	&&label_create_dolls_sakuya_T04_T05,
				/*06 T05*/	&&label_create_dolls_sakuya_T04_T05,
				/*08 T06*/	&&label_continue_T00,
				/*0d T07*/	&&label_continue_T00,
						//
				/*01 T08*/	&&label_continue_T00, /*(共通のみ)宝物 敵を追加する */
				/*02 T09*/	&&label_create_dolls_kaguya_T09,
				/*0e T0a*/	&&label_create_dolls_kaguya_T0a_T0d,/*(下から、広い04)*/
				/*0f T0b*/	&&label_create_dolls_kaguya_T0a_T0d,/*(下から、広い05)*/
						//
				/*03 T0c*/	&&label_create_dolls_kaguya_T0a_T0d,/*(下から、狭い06)*/
				/*09 T0d*/	&&label_create_dolls_kaguya_T0a_T0d,/*(上から)*/ /*T09*/
				/*04 T0e*/	&&label_continue_T00, /*(mima共通のみ)*/
				/*07 T0f*/	&&label_continue_T00, /*(alice)*/
				};
				goto *aaa[card.tukaima_used_type];
			label_create_dolls_kaguya_T0a_T0d:			/* 子供魔方陣02 敵を追加する */
				/* 夜は 1日 の 1/3 時間 */
				// 基準位置(画面下方中心)
				h->TUKAIMA_KIKAKU_00_target_x256		= (t256((GAME_WIDTH/2)));//;(src->center.x256);
				h->TUKAIMA_KIKAKU_01_target_y256		= (t256(272)		   );//;(src->center.y256);
				//
			//	h->jyumyou		= (0x01ff); 		/* 制限時間 */
			//	h->jyumyou		= (0x02ff)+(i<<6);	/* 制限時間 */
			//	h->jyumyou		= (0x02ff)-(1024/3)+(i_angle1024);	/* 制限時間 */
				h->jyumyou		+= (i_angle1024);	/* 制限時間 */
				if (0 > h->set_hankei_256)/*T09*/
				{
				//	h->now_hankei_256		= t256(32*12);			/* 現在半径  384[pixel] */
					h->now_hankei_256		= t256(32*10);			/* 現在半径  320[pixel] */
				}
				goto label_continue_T00;
			label_create_dolls_kaguya_T09:/* 子供魔方陣01 敵を追加する */
				h->set_hankei_256					-= (cg_VR20_game_difficulty<<(4+8));	/* 指定半径 45[pixel] */
				goto label_continue_T00;
			label_create_dolls_sakuya_T04_T05:
				#if (1)/*(追加部分)*/
				h->zako_hp				= (8192-1);/*(硬い)*/
				#endif
			//	h->set_hankei_256 &= 0xfffffffcu;
				h->set_hankei_256	 |= ((card.tukaima_used_type<<1) & 2/*mode*/);
				h->set_hankei_256	 |= (even_or_odd);/* [青赤情報]をインターリーブ */
			//	goto label_continue_T00;
			label_continue_T00:// なにもせず
				;
				even_or_odd ^= (1);/*(1)[bit]*/
			}
		}
	}
}


/*---------------------------------------------------------
	(使い魔システム)追加敵を設定する。
---------------------------------------------------------*/
extern void set_tukaima_start(void)
{
	card.tukaima_used_type = cg_BOSS_DATA_39_tukaima_type;
}

