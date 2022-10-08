
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	誘導ミサイル敵
	-------------------------------------------------------
	誘導ホーミングにしようと思ったのに
	なぜかショット風に(作成中)
	色々未完成。
---------------------------------------------------------*/

#define target_x256 		user_data00 	/* 目標地点(出現時のプレイヤー位置) */
#define target_y256 		user_data01 	/* 目標地点(出現時のプレイヤー位置) */

#define radius				user_data02 	/* 半径 */
#define ax256				user_data04 	/* 量 */
#define ay256				user_data05 	/* 量 */


/*---------------------------------------------------------
	敵の誘導ホーミングボム(緑色の奴)
---------------------------------------------------------*/

/* プレイヤーのいた位置に到達する基準時間 */
#define GENTEN_FRAME128 (128)
#define ZERO_FRAME256	(256)

static OBJ_CALL_FUNC(teki_homing_move)
{
	if (GENTEN_FRAME128 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
//	if ((GENTEN_FRAME128-16) < src->jyumyou)	/* 一定時間まで */
//	if ((256+GENTEN_FRAME128-256-64+16) < src->jyumyou) /* 一定時間まで */
//	if ((256-16) < src->jyumyou)	/* (遅い) 一定時間まで */
	if ((256+32) < src->jyumyou)	/* 一定時間まで */
	{
		VR04	= (src->target_x256);					/* 弾源x256 */
		VR05	= (src->target_y256);					/* 弾源y256 */
		VR06	= ((src->center.x256));
		VR07	= ((src->center.y256));
		CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//	#define ROTATE_1024HARF 	(1024/2)/*半周*/
	//	const int sabun_aaa = ((deg65536to1024(HATSUDAN_R13_angle65536))-src->rotationCCW1024);
		#define ROTATE_65536HARF 	(65536/2)/*半周*/
		const int sabun_aaa = (( (HATSUDAN_R13_angle65536))-src->rotationCCW65536);
		if (0 > (sabun_aaa) )/* 0レジスタ+共通最適化 */
		{
			/* 目標角度 < 制御角度 */
			if ((ROTATE_65536HARF) > (sabun_aaa) )/* 共通最適化 */
			{
			//	src->rotationCCW1024 -= (10);
				src->rotationCCW65536 -= (10<<6);
			}
		}
		else	/* 目標角度 > 制御角度 */
		{
			if ((ROTATE_65536HARF) > -(sabun_aaa) )
			{
			//	src->rotationCCW1024 += (10);
				src->rotationCCW65536 += (10<<6);
			}
		}
		#undef ROTATE_65536HARF
		// 正弦関数による加減速
		{
		//	const u8 ddd[4] =
		//	{
		//		GENTEN_FRAME128-31, 	//-(((255)>>2)-GENTEN_FRAME128), /*(まず狙わない。ほぼ見せるだけ)*/
		//		GENTEN_FRAME128- 0, 	//-(((255)>>2)-GENTEN_FRAME128), /*(ほぼ狙わない。大して難しくない)*/
		//		GENTEN_FRAME128-47, 	//-(((255)>>2)-GENTEN_FRAME128), /*(少し狙う。)*/
		//		GENTEN_FRAME128-63, 	//-(((255)>>2)-GENTEN_FRAME128), /*(63==正確に狙う) (r34互換)*/
		//	};
		//	int radius_aaa;/* 速度 */
			//------------------
			HATSUDAN_R11_speed256	= (t256(1.0));
			HATSUDAN_R13_angle65536 = (deg1024to65536((((src->jyumyou-(GENTEN_FRAME128-63))<<2))));
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		//	radius_aaa = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//	src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
			HATSUDAN_R11_speed256	= ((VR07)<<2);
			HATSUDAN_R13_angle65536 = (src->rotationCCW65536);
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			src->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
		}
	}
	/* 実移動 */
	src->center.x256 += (src->math_vector.x256);
	src->center.y256 += (src->math_vector.y256);
}


/*---------------------------------------------------------
	敵側の誘導ミサイルを作成する
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(bullet_create_teki_homing)
{
	/* 目標地点 */
	OBJ *zzz_player;
	zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	//
	u32 i_angle;
	for (i_angle=0; i_angle<(1024); i_angle += (1024/8) )/* */
	{
		OBJ *h;
		h					= obj_regist_teki();
		if (NULL!=h)/* 登録できた場合のみ */
		{
			h->m_Hit256R				= ZAKO_ATARI_HOMING16_PNG;
			h->obj_type_set 			= ZAKO_63_HOMING_STUFF;
			h->callback_mover			= teki_homing_move;
			/* (r34u1)壊せるようにした */
			h->callback_hit_teki		= callback_hit_zako;		/* 「ザコに自弾があたった場合の処理」に、標準の処理を設定 */
			h->atari_hantei 			= (score(5*2)/*スコア兼用*/);
			h->zako_hp					= (1);		/* 誘導ミサイルの硬さ。 */
			h->center.x256				= (src->center.x256);/* 発弾位置 */
			h->center.y256				= (src->center.y256);/* 発弾位置 */
	//
		//	h->rotationCCW1024			= (i_angle);/* ミサイルの向き */
			h->rotationCCW65536			= ((i_angle)<<6);/*(r42とりあえず) ミサイルの向き */
			{
				h->target_x256			= (zzz_player->center.x256);/* 目標位置 */
				h->target_y256			= (zzz_player->center.y256);/* 目標位置 */
			}
			h->jyumyou		= (256+GENTEN_FRAME128);
		}
	}
}
