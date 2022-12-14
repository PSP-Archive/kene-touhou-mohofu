
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	道中のザコ
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"魔方陣" 関係
---------------------------------------------------------*/

/*---------------------------------------------------------
	"魔方陣2"		消える魔方陣
	"魔方陣1"		ばらまき攻撃魔方陣
	-------------------------------------------------------
	地形に関連する敵
---------------------------------------------------------*/

/* 時間設定 */

//#define MAHOU_TIME_LIMIT_00_MAX	(0x1ff)
//#define MAHOU_TIME_LIMIT_00_MAX	(0x17f)
#define MAHOU_TIME_LIMIT_00_MAX 	(0x13f)
#define MAHOU_TIME_LIMIT_01_ADJ 	((int)(0x0ff/3))
#define MAHOU_TIME_LIMIT_02_ADJ 	(MAHOU_TIME_LIMIT_00_MAX - MAHOU_TIME_LIMIT_01_ADJ)
#define MAHOU_TIME_LIMIT_03_EPS 	(0x04)

/*---------------------------------------------------------
	敵攻撃しない
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin00)
{
	/* 攻撃しない */
}
/*---------------------------------------------------------
	1:縦攻撃のカード
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin01)
{
	/* 攻撃開始フレームから16フレーム経過後に 1回だけ攻撃 */
	if ((MAHOU_TIME_LIMIT_02_ADJ-16) == src->jyumyou)
	{
		zako_shot_supeka(src);
	}
}

/*---------------------------------------------------------
	2:ランダムばらまき攻撃("魔方陣2")のカード
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin02)
{
	if (0 < src->zd04_zako_wait2)
	{
		src->zd02_zako_wait1--; 		/* ばらまき間隔カウンタ */
		if (src->zd02_zako_wait1 <= 0)	/* ばらまき間隔カウンタ */
		{
			src->zd02_zako_wait1 = (8);/*(5) (プログラムが速くなってる分遅くする)*/
			src->zd04_zako_wait2--;
			voice_play_menu(VOICE12_MAGICF_E_SHOT, TRACK03_IVENT_DAN);/*テキトー*/
			zako_shot_supeka(src);
		}
	}
}


/*---------------------------------------------------------
	3:ランダムばらまき攻撃+自機狙い("魔方陣1")のカード
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin03)
{
	#if 0
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	if (
			(src->center.y256 > zzz_player->center.y256)
	 || 	(src->center.y256 > t256(100))
	)
	{
	//	src->time_out++;/* = ST01;*/
		src->jyumyou								= MAHOU_TIME_LIMIT_01_ADJ;	/* 消える */
		zako_sh//ot_supeka(src, ZAKO_SPEKA_01_mahou_nerai);
	}
	#endif
	{
		src->zd02_zako_wait1--; 		/* ばらまき間隔カウンタ */
		if (src->zd02_zako_wait1 <= 0)	/* ばらまき間隔カウンタ */
		{
			src->zd02_zako_wait1 = (25-((cg_VR20_game_difficulty)*5)); /* ばらまき間隔カウンタ */
			voice_play_menu(VOICE12_MAGICF_E_SHOT, TRACK03_IVENT_DAN);/*テキトー*/
			/* 速度は 1.0-4.0までの乱数(ただし上方域に偏差)に変更 */
//...		HATSUDAN_R11_speed256						= ((ra_nd()&(1024-1))|(0x100))+t256(1.0);	/* 弾速 */
			HATSUDAN_R13_angle65536 					= ((ra_nd()&(65536-1)));					/* 角度 */
			/*(基本的に雑魚ではra_nd()使用禁止)*/
			zako_shot_supeka(src);
		}
	}
}

/*---------------------------------------------------------
	4:円状攻撃のカード(小左)
	5:円状攻撃のカード(中右)
	6:円状攻撃のカード(大左)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(attack_kougeki_mahoujin4564)
{
	/* 難易度別に攻撃 */
	//if (0 == (src->jyumyou & 0x07))
	if ((cg_VR20_game_difficulty) >= (src->jyumyou & 0x03))
	{
		zako_shot_supeka(src);
	}
}

/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_00_kougeki_mahoujin)
{
	/* 出現 */
	if (MAHOU_TIME_LIMIT_02_ADJ < src->jyumyou)
	{
		src->color32 += 0x03000000; 		/*	src->alpha += 0x03;*/ /*4*/ /*fps_factor*/
	}
	/* あたり判定、発生 */
	else
	if (MAHOU_TIME_LIMIT_02_ADJ == src->jyumyou)
	{
		src->atari_hantei			= /*(テキトー)*/score(100);/*スコア兼用*/	/* あたり判定あり */
		/*(ここでスコアを設定する)*/
	}
	/* 攻撃 */
	else
	if (MAHOU_TIME_LIMIT_01_ADJ < src->jyumyou)
	{
	//	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
		/* (魔方陣の攻撃)カード選択 */
		void (*aaa[8])(OBJ/**/ *src) =
		{
			/*(00)0*/attack_kougeki_mahoujin00, 	/* 攻撃しない */
			/*(01)-*/attack_kougeki_mahoujin00, 	/* 攻撃しない */
			/*(02)1*/attack_kougeki_mahoujin01, 	/* 縦弾 */
			/*(03)2*/attack_kougeki_mahoujin02, 	/* ばらまき #01(差分氏、旧"魔方陣2") */
			/*(04)3*/attack_kougeki_mahoujin03, 	/* ばらまき #02(差分氏、旧"魔方陣1") */
			/*(05)4*/attack_kougeki_mahoujin4564,	/* 8way花弾(中) */
			/*(06)5*/attack_kougeki_mahoujin4564,	/* 8way花弾(中) */
			/*(07)-*/attack_kougeki_mahoujin4564,	/* 8way花弾(中) */
		};
		(*aaa[(int)((src->zd05_kougeki_type) & 0x07)])(src);	/* 各関数に分岐する */
	//	(*aaa[(int)((src->center.x256) & 0x07)])(src);	/* 各関数に分岐する */
	}
	/* あたり判定、なし */
	else
	if (MAHOU_TIME_LIMIT_01_ADJ == src->jyumyou)
	{
		src->atari_hantei			= (ATARI_HANTEI_OFF/*スコア兼用*/); 	/* あたり判定無し */
		/*(あたり判定無し==スコアは無い)*/
	}
	/* 消える */
	else
	if (MAHOU_TIME_LIMIT_03_EPS < src->jyumyou) 	/*	if (0x04 0x00 > (u32)(src->alpha))*/
	{
		src->color32 -= 0x03000000; 	/*	src->alpha += 0x03;*/ /*4*/ /*fps_factor*/
	}
	/* おしまい */
	else
	{
	//	src->color32 = 0x00ffffff;		/*	src->alpha = 0x00;*/
		src->jyumyou = JYUMYOU_NASI;
	}
	/* アニメ (揺れる) */
//	{
//		int sin_value_t256; 		//	sin_value_t256 = 0;
//		int cos_value_t256; 		//	cos_value_t256 = 0;
//		int256_sin cos65536((src->jyumyou<<(5+6)), &sin_value_t256, &cos_value_t256);
//	//	src->center.y256 = src->zd03_start_y256 + ((cos1024(((src->jyumyou<<5)&(1024-1))))<<2);
//		src->center.y256 = src->zd03_start_y256 + ((sin_value_t256)<<2);
//	}
	//------------------
	HATSUDAN_R11_speed256	= (t256(4.0));
	HATSUDAN_R13_angle65536 = (src->jyumyou<<(5+6));
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	src->center.y256 = src->zd03_start_y256 + VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
//	src->rotationCCW1024++;
//	mask1024(src->rotationCCW1024);
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/
/* ばらまき攻撃魔方陣 */	/* "魔方陣1" "GROUNDER", */
/* 消える魔方陣 */	/* "魔方陣2" "MAGICF", */
//static GAME_COMMAND_OBJ_FUNC(regist_zako_000_mahoujin12)// MAHOUJIN A
//static GAME_COMMAND_OBJ_FUNC(regist_zako_001_mahoujin2)// MAHOUJIN B

static GAME_COMMAND_OBJ_FUNC(regist_zako_000_mahoujin)
{
//	gcmd_obj->m_Hit256R 			= ZAKO_ATARI04_PNG;/* あたり判定サイズを変える */
	gcmd_obj->m_Hit256R 			= ZAKO_ATARI16_PNG;
	//
	gcmd_obj->atari_hantei	= (ATARI_HANTEI_OFF/*スコア兼用*/); 	/* あたり判定無し */
	/*(あたり判定==獲得スコア)*/
	/* KETMの相対座標指定は廃止。画面座標指定にする */
//	gcmd_obj->center.x256				= (((short)gcmd->user_locate_x)<<8)|(((char)gcmd->user_kougeki_type) & 0x07);/* こっそりインターリーブ */
	gcmd_obj->center.x256				= (((short)gcmd->user_locate_x)<<8);
	gcmd_obj->zd03_start_y256			= (((short)gcmd->user_locate_y)<<8);
	//
	gcmd_obj->jyumyou					= MAHOU_TIME_LIMIT_00_MAX;/* SS00 または ST00 */
	//
	gcmd_obj->zd02_zako_wait1			= (10);
	gcmd_obj->zd04_zako_wait2			= (5);		/* 最大五回 */
	gcmd_obj->color32					= 0x00ffffff;	/*	gcmd_obj->alpha 			= 0x02 0x00;*/
}


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"キスメ" 関係(分裂するので、DATとの関連がない)
---------------------------------------------------------*/

/*---------------------------------------------------------
		"キスメ", "赤毛玉1",		"MINE",
	-------------------------------------------------------
	ぐるぐるその場で動かないで、回転アニメしてて
	ほっとくと8つに分裂して
	最後に高速弾撃って来るやつ(橙)
	-------------------------------------------------------
	このキャラのみ分裂するんだけど、システムとして
	分裂はサポートしなくなるかもしれない(?)。
	その場合は始めから、8つ重なって出てくる。
	分裂は、つまりアリス弾だからサポートされるとしたら、
	最終的なアリス弾の仕組み(まだ確定していない)と同じ仕組みになると思う。
---------------------------------------------------------*/

/*---------------------------------------------------------
	敵移動(分裂後)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_kisume_2nd)
{
	if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* このラインより下からは敵が撃たない */
	{
		/*
		0  0/100   0/65536
		1  1/90  728/65536
		2  1/80  819/65536
		3  1/70  936/65536
		*/
	//	static const u16 kakuritu_tbl[4] =
	//	{ 0, 728, 819, 936 };
	//	if (kakuritu_tbl[((cg_VR20_game_difficulty))/*(teki_rank)*/] > (r a_nd()&(65536-1)))
		if (0==(src->center.x256 & 0x0f))
		{
			zako_shot_supeka(src);
		}
	}
/* CCWの場合 */
	src->center.x256 += (src->math_vector.x256);/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	/* アニメーション */
	src->zako_anime_rotate_angle65536 = ( 16<<6);/*(20<<6)*/
	zako_anime_type04(src); 	/* グラ回転 */
}


/*---------------------------------------------------------
	敵を追加する(変身)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(add_local_kisume_2nd)
{
	int i;
	for (i=0; i<8; i++)/*分裂*/
	{
		OBJ *h;
		h						= obj_regist_teki();
		if (NULL!=h)/* 登録できた場合のみ */
		{
			h->center.x256			= src->center.x256; 	/* 分裂前をそのまま引き継ぐ */
			h->center.y256			= src->center.y256; 	/* 分裂前をそのまま引き継ぐ */
			h->obj_type_set 		= src->obj_type_set;	/* 分裂前をそのまま引き継ぐ */
			h->base_score			= src->base_score;		/* 爆発させたほうがスコアが稼げる */	/* 分裂前をそのまま引き継ぐ */
			h->zako_hp				= src->zako_hp; 		/* 分裂前の体力をそのまま引き継ぐ(減らしてあればその分軟らかい) */
			//
			h->m_Hit256R			= ZAKO_ATARI16_PNG;
			h->callback_mover		= move_kisume_2nd;
			h->callback_loser		= src->callback_loser;	/* 分裂前をそのまま引き継ぐ */
			h->callback_hit_teki	= callback_hit_zako;	/* 「ザコに自弾があたった場合の処理」に、標準の処理を設定 */
			//
			{
				const int data_zzz_angle1024				= (i<<7);	/* 分裂角度 */	//	(/*360*/1024/8)*i;
			//	const int data_zzz_speed256 				= (t256(1.5)+((cg_game_di fficulty)<<6));	/* 分裂速度 */	/*(3.0)*/
				const int data_zzz_speed256 				= (t256(1.5)+((3)<<6)); 	/* 分裂速度 */	/*(3.0)*/
				//------------------
				HATSUDAN_R11_speed256	= (data_zzz_speed256);
				HATSUDAN_R13_angle65536 = deg1024to65536(data_zzz_angle1024);
				CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
				h->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
				h->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
				//------------------
			}
		}
	}
}

/*---------------------------------------------------------
	敵移動(本体)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_05_kisume_1st)
{
	if (2 == src->jyumyou)	/* 分裂 */
	{
		add_local_kisume_2nd(src);/* 変身 分裂 */	/*, data->teki_rank*/
		src->jyumyou = JYUMYOU_NASI;		/* 本体はおしまい */
	}
	else
	if (31+2 > src->jyumyou)
	{
//		src->zako_anime_rotate_angle65536 = (  0);	/* 止まる */
	}
	else
	{
										/* 移動 move */
		src->center.x256 += (src->math_vector.x256);	/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);	/*fps_factor*/
//		src->zako_anime_rotate_angle65536 = ( 10<<6);	/* グラ回転 */
	}
	/* アニメーション */
// グラ回転しない方がインパクトがある。 zako_anime_type04(src); 	/* グラ回転 */
}



// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"その他一般ザコ" 関係
---------------------------------------------------------*/

/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/


/*---------------------------------------------------------
		"毛玉1",	"BADGUY",
	-------------------------------------------------------
	本家毛玉
---------------------------------------------------------*/

static OBJ_CALL_FUNC(my_nerai)
{
	VR04	= (src->zd00_target_x256);						/* 弾源x256 */
	VR05	= (src->zd01_target_y256-t256(64)/*+(20)*/);	/* 弾源y256 */
	set_REG_DEST_XY(src);
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//------------------
	HATSUDAN_R11_speed256	= (t256(1.0));
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	src->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
}

static OBJ_CALL_FUNC(move_zako_10_hai_kedama)
{
	if (JYUMYOU_ZAKO_HASSEI -128/*-64-64*/ > src->jyumyou)/* 退場 */
	{
		my_nerai(src);
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -64 > src->jyumyou)/* */
	{
		if (0==(src->jyumyou & 0x0f))
		{
			if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* このラインより下からは敵が撃たない */
			{
				zako_shot_supeka(src);
			}
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou) /* 登場する */
	{
		my_nerai(src);
		{
			if (// (src->center.x256 >= www_ppp_center_x256) ||
				(src->center.y256 > t256(GAME_HEIGHT/2) ) /*(480-80)*/ /*(272-32)*/
			 )
			{
				src->math_vector.y256 = (-src->math_vector.y256);
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -64-1);
				/* 第二目標は、 */
				src->zd00_target_x256		= t256(((480-128)/2));	// t256(-100)
				src->zd01_target_y256		= t256(0);/*((www_ppp_center_y256)&(128-1))*/
				src->zd02_system_speed256	= t256(2.5/*5.0*/);/*fps_factor*/	/*6*/
			}
		}
	}
	/* 移動する */
	src->center.x256 += (((src->math_vector.x256)*(src->zd02_system_speed256))>>8);
	src->center.y256 += (((src->math_vector.y256)*(src->zd02_system_speed256))>>8);
	/* アニメーション */
	zako_anime_type04(src); 	/* グラ回転 */
}

/*---------------------------------------------------------
		"毛玉2",	"BADGUY",	(r27から新規追加)
	-------------------------------------------------------
	本家毛玉
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_11_siro_kedama)
{
	if (JYUMYOU_ZAKO_HASSEI -256-64 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -256 > src->jyumyou)	/* 攻撃 */
	{
		zako_shot_supeka(src);
	}
	else
	{
		/* ばらばらに登場させる */
		if (
			(0 >= src->center.x256)
			|| (t256(GAME_WIDTH) < src->center.x256)
			#if (1==USE_X_HOUKOU)
			|| (0 >= src->center.y256)
			|| (t256(GAME_HEIGHT) < src->center.y256)
			#endif
		)
		{
			/*画面外*/;
		}
		else
		{
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -256-1); /* 登場する */
		}
	}
	/* 移動する */
	src->center.x256 += (src->math_vector.x256);
	src->center.y256 += (src->math_vector.y256);
	/* アニメーション */
	zako_anime_type04(src); 	/* グラ回転 */
}

/*---------------------------------------------------------
	"紫編隊2",		"GREETER",
	-------------------------------------------------------
	５機一列に続がり、編隊飛行してくるザコ敵
	-------------------------------------------------------
	ming_greeter
	rwingx_curver(ming)に似てる
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_07_yukari)
{
	/* ザコ発生から5[秒]以上経過していれば、チェック */
	if (JYUMYOU_ZAKO_HASSEI-byou60(5) > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	{
		if (src->center.y256 >= src->zd04_max_y256)
		{
			src->jyumyou = JYUMYOU_ZAKO_HASSEI-byou60(5);	/* 5[秒]経過済みにセット。 */
			if (t256(1.5/*2.0*/) < src->zd02_system_speed256)
			{	/* 減速 */
				src->zd02_system_speed256 -= t256(0.2);
			//	src->zd02_system_speed256 = t256(2)/*3+difficulty*/;
			}
		//
			VR04		= (t256(GAME_WIDTH/2)); 		/* 弾源x256 */
			VR05		= (t256(0));					/* 弾源y256 */
			set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
			//------------------
			HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
		//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			src->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
		}
		zako_shot_supeka(src);
	}
	/* 似てるがちょっと違う--以下rwingx.cと同じ */
	src->center.x256 += (src->math_vector.x256);/* fps_factor */
	src->center.y256 += (src->math_vector.y256);/* fps_factor */
	/* アニメーション */
	zako_anime_type04(src); 	/* グラ回転 */
}


/*---------------------------------------------------------
	"陰陽玉1",		"PLASMABALL",
	-------------------------------------------------------
	(旧)白毛玉、(601氏)青妖精
	(4*6)で24匹も出てくるがあまり意味のないキャラ
	-------------------------------------------------------
	花映塚風(?)に変えた。
	かなりテキトー。
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_02_inyou_dama)
{
	src->center.x256 += src->math_vector.x256;
	/* 画面両端では、跳ね返る */
	if (
		((t256(GAME_X_OFFSET)) > (src->center.x256) ) ||
		((t256(GAME_WIDTH)) < (src->center.x256) ) )
	{
		src->math_vector.x256 = -src->math_vector.x256;
	}
	/* 移動向きに合わせてグラ回転 */
	if (0 < src->math_vector.x256)
			{	src->zako_anime_rotate_angle65536 = ( 24<<6);	}
	else	{	src->zako_anime_rotate_angle65536 = (-24<<6);	}
	/* 落ちる */
	if ((t256(2.50)) > src->math_vector.y256)	/* 最大重力加速度 */
	{
		src->math_vector.y256 += (8);	/* 重力加速度 */
	}
	/* */
	src->center.y256 += src->math_vector.y256;
	if ((src->zd01_target_y256) < (src->center.y256))
	{
	//	src->center.y256			= src->zd01_target_y256;
		src->zd01_target_y256		= t256(300);
		src->math_vector.y256		= -src->math_vector.y256;	/* 跳ねる */
	}
	/* 画面下まで来たら、おしまい */
	if (t256(272) < (src->center.y256) )
	{
		src->jyumyou = JYUMYOU_NASI;	/* おしまい */
	}
	/* アニメーション */
	zako_anime_type04(src);
}

/*---------------------------------------------------------
		"囲妖怪1",		"CUBE",
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_04_kakomi)
{
	if ((JYUMYOU_ZAKO_HASSEI-295) > src->jyumyou)		/* 離脱 */
	{
		src->zd02_radius256 += t256(1.2);		/*fps_factor*/	/*2.0*/
		if (src->zd02_radius256 > t256(350.0))
		{
			src->jyumyou = JYUMYOU_NASI;	/* おしまい */
		}
	}
	else
	{
		src->zd02_radius256 -= t256(1.0);		/*fps_factor*/
	//	if (0==(r a_nd()&(512-1)))			/* 1/512 の確率で弾打つ */
		if (0==(src->center.x256 & 0x0ff))
		{
			zako_shot_supeka(src);
		}
	//	src->tmp_angleCCW1024 -= (2);		/*fps_factor*/ /* deg_360_to_512(3) 速すぎる */
	//	mask1024(src->tmp_angleCCW1024);
		src->tmp_angleCCW65536 -= (2<<6);		/*fps_factor*/ /* deg_360_to_512(3) 速すぎる */
		mask65536(src->tmp_angleCCW65536);
	}
//	zako_move_ty pe11_radius(src);
	src->center.x256 = (src->zd00_target_x256);
	src->center.y256 = (src->zd01_target_y256);
	//
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type03(src);/* アニメーション */
}

/*---------------------------------------------------------
		"竜巻1",		"PROBALL",
	-------------------------------------------------------
→	↓	 ←
↑. ↓	/↑
↑ .↓ / ↑
↑	↓/  ↑
←←++→→
   /  .
	-------------------------------------------------------
	雑魚スペカ: 攻撃しない(?)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_03_tatsumaki)
{
	if (JYUMYOU_ZAKO_HASSEI -512-512 > src->jyumyou)/* 下へ移動 */
	{
		src->center.y256 += t256(1.25);/*fps_factor*/
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -512 > src->jyumyou)/* 上へ移動 */
	{
		src->center.y256 -= t256(1.125);/*fps_factor*/
		if (0 > src->center.y256)
		{
		//	src->zd02_system_speed256 = (-(src->zd02_system_speed256));/* 反転 */
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -512-512-1);
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou)/* 下へ移動 */
	{
		src->center.y256 += t256(1.0);/*fps_factor*/
		if (t256(GAME_HEIGHT/3/*2*/) < src->center.y256) /*t256(250)*/
		{
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -512-1);
		}
	}
	//
	src->zd02_system_speed256++;	/* t256(0.1) t256(0.2)速すぎ */
	src->zd03_px256 -= (src->zd02_system_speed256);/*fps_factor*/
	if ((0 > src->zd03_px256)||(t256(GAME_WIDTH-10) < src->zd03_px256))
	{
		src->zd02_system_speed256 = (-(src->zd02_system_speed256));/* 反転 */
	}
//
	if (0 < (src->zako_anime_rotate_angle65536) )	/* vx_r 回転方向(回転量) */
			{src->center.x256	= (src->zd03_px256);}
	else	{src->center.x256	= t256(GAME_WIDTH)-(src->zd03_px256);}
	//
	/* アニメーション */
	zako_anime_type04(src);
}


/*---------------------------------------------------------
		"おばけ1",		"DRAGER",
	-------------------------------------------------------
	突撃おばけ、(かなりうろ覚え、おばけじゃなかったかも？)
	-------------------------------------------------------
仕様：
	■ datでscoreを指定する。
	■ datで体力を指定する。
	■ datで獲得アイテムを指定する。
	■ datで出現位置 x, y 座標を指定する。
	■ 雑魚の速度は難易度に関係なく固定。結構速め。(t256(2.0))
	■ 雑魚は自機狙いで突撃してくる。(途中で向きは変えません)
	■ 等間隔で弾を撃ってくる。(早く倒した方が有利)
		easy	撃たない。
		normal	1way弾。
		hard	3way弾。
		luna	5way弾。
	■ 弾の速度は、雑魚の速度より遅い。速度は難易度に関係なく固定。(t256(1.25))
	(画面に残るので早く倒した方が有利)
	-------------------------------------------------------
	つまりフラワーウイザラウェイの逆バージョンです。
	と言った方が分かりやすいかな？
---------------------------------------------------------*/

/*---------------------------------------------------------
	"隕石1", "紫 編 隊1",		"MING",
	-------------------------------------------------------
仕様：
	■ datでscoreを指定する。
	■ datで体力を指定する。
	■ datで獲得アイテムを指定する。
	■ datで出現位置 x, y 座標を指定する。

	単体でばらばらに、落ちてくるザコ敵
	自機狙い赤単弾を連射してくる
	-------------------------------------------------------
	道中に必要か悩んだが、元と似た仕様の編隊飛行敵は必要ない。
	単純に落ちてくる敵に変更する。
	-------------------------------------------------------
	10機三角錐状に続がり、編隊飛行してくるザコ敵
	ming
	rwingx_curverに似てる
---------------------------------------------------------*/

/*---------------------------------------------------------
	"緑毛玉1",		"XEV",
	-------------------------------------------------------
	緑毛玉	単体で突っ込んでくる。
	-------------------------------------------------------
		"緑毛玉2",		"CRUSHER",
	-------------------------------------------------------
	[廃止]緑毛玉	横一列に並んで、上から突っ込んでくる。
	-------------------------------------------------------
	元のは挙動が不自然に直線的で面白くないので、
	ふにゃふにゃと降りてくるように変更。
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_06_inseki)
{
	/* ザコ発生から1[秒]以上経過していれば、チェック */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(1)) > src->jyumyou ))
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	if (0==((src->jyumyou)&0x3f))/* 等間隔(テキト−) */
	{
		if (ENEMY_LAST_SHOT_LINE256 > src->center.y256) /* このラインより下からは敵が撃たない */
		{
			if (0!=(cg_VR20_game_difficulty))
			{
				zako_shot_supeka(src);	/*(仕様上easyは無理)*/
			}
		}
	}
//
	{
		src->center.x256 += (src->math_vector.x256);/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	}
	/* アニメーション */
	{
		if (0==src->zako_anime_rotate_angle65536)
		{
			zako_anime_type02(src);
		}
		else		/* offset無しは回転 */
		{
			zako_anime_type04(src);
		}
	}
}


static OBJ_CALL_FUNC(move_zako_09_midori_kedama)
{
	#if 1
	/* ザコ発生から3[秒]以上経過していれば、チェック */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(3)) > src->jyumyou ))
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	/* ザコ発生から丁度3[秒]経過していれば、発弾する */
	if (( (JYUMYOU_ZAKO_HASSEI-byou60(3)+1) > src->jyumyou ))
	{
		zako_shot_supeka(src);
	}
	else
	/* ザコ発生から3[秒]以内は、ふにゃふにゃ移動 */
	{
		//------------------
		HATSUDAN_R11_speed256	= t256(1.0);// (src->zd02_system_speed256);
		HATSUDAN_R13_angle65536 = ((src->center.y256)/*<<8*/);//deg1024to65536((src->tmp_angleCCW1024));
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		src->center.x256 += VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//	src->center.y256 += VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
	//	src->center.x256 += (t256(1.5));		/*fps_factor*/
	}
	src->center.y256 += (t256(0.83));	/*fps_factor*/
	#endif
	/* アニメーション */
	zako_anime_type04(src); 	/* グラ回転 */
}


static OBJ_CALL_FUNC(move_zako_08_ao_kedama)
{
	/* ザコ発生から5[秒]以上経過していれば、チェック */
	if ((JYUMYOU_ZAKO_HASSEI-byou60(5)) > src->jyumyou) 	/* 離脱 */
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
		src->zd02_system_speed256++;// = t256(3.5/*6*/);
	}
	else
	{
		int www_ppp_center_x256;
		int www_ppp_center_y256;
		www_ppp_center_x256 = ra_nd()&0xffff;/*(基本的に雑魚ではra_nd()使用禁止)*/
		www_ppp_center_y256 = ra_nd()&0xffff;/*(基本的に雑魚ではra_nd()使用禁止)*/
		if ((src->center.x256 >= www_ppp_center_x256)||
			(src->center.y256 > t256(GAME_HEIGHT-48) ) )/*480-80*/
		{
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI-byou60(5));	/* 5[秒]経過済みにセット。 */
			src->zd00_target_x256	= t256(-100);
		//	src->zd01_target_y256	= www_ppp_center_y256-t256(48);
			src->zd01_target_y256	= www_ppp_center_y256-t256(48);
			zako_shot_supeka(src);
		}
	}
	VR04	= (src->zd00_target_x256);/* 弾源x256 */
	VR05	= (src->zd01_target_y256);/* 弾源y256 */
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	#if (1)
	//------------------
	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	src->center.x256 += VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	src->center.y256 += VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	#else
	src->tmp_angleCCW1024	= deg65536to1024((HATSUDAN_R13_angle65536));
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	#endif
	//------------------
	/* アニメーション */
	zako_anime_type04(src); 	/* グラ回転 */
}


/*---------------------------------------------------------
	"おばけ2"(ばけばけ) 	"虹毛玉1",		"EYEFO",
	-------------------------------------------------------
	バグあり？？？
---------------------------------------------------------*/
/*static*/extern OBJ_CALL_FUNC(bullet_create_teki_homing);

static OBJ_CALL_FUNC(move_zako_13_obake)
{
//	if (JYUMYOU_ZAKO_HASSEI -1200+0 > src->jyumyou)
//	{
//		src->jyumyou = JYUMYOU_NASI;	/* おしまい */
//	}
//	else
	/* ザコ発生から10[秒]以上経過していれば、チェック */
	if (JYUMYOU_ZAKO_HASSEI -byou60(10) > src->jyumyou) 	/* 上へ帰る */
	{
		src->zd01_target_y256 -= t256(1.0);/*fps_factor*/
	}
	else
	/* ザコ発生から5[秒]以上経過していれば、チェック */
	if (JYUMYOU_ZAKO_HASSEI -byou60(5) < src->jyumyou)		/* 下へ来る */
	{
	//	if (src->zd01_target_y256 < t256(GAME_HEIGHT))
	//	if (src->zd01_target_y256 < t256(difficulty<<6) )/* 難易度により下がってくる位置が違う。最大192(3*64) */
	//	if (src->zd01_target_y256 < t256((cg_game_di fficulty)<<5) )/* 難易度により下がってくる位置が違う。最大96(3*32) */
		if (src->zd01_target_y256 < t256((3)<<5) )/* 難易度により下がってくる位置が違う。最大96(3*32) */
		{
			src->zd01_target_y256 += t256(1.0);/* fps_factor */
		}
	}
//
	if (0 == src->zd04_kaisu_nnn)
	{
		src->zd02_radius256 += t256(1.0);	/* fps_factor */
		if (src->zd02_radius256 > t256(64.0))/*150*/ /* 最大半径 */
		{
			src->zd04_kaisu_nnn = (1);
		}
	}
	else
	{
		src->zd02_radius256 -= t256(2.0);	/* fps_factor */	/* 1 */
		if (src->zd02_radius256 < t256(8.0)) /* 最小半径 */ /* <=10 */
		{
			src->zd04_kaisu_nnn = (0);
		}
	}
//	src->tmp_angleCCW1024 += (2);	/* fps_factor */	/* cv1024r(5) 速すぎる */
//	mask1024(src->tmp_angleCCW1024);
	src->tmp_angleCCW65536 += (2<<6);	/* fps_factor */	/* cv1024r(5) 速すぎる */
	mask65536(src->tmp_angleCCW65536);
	//
	/* 画面外ならば撃たない */
	if (0 < src->center.y256) /* 画面内なら撃つ */
	{
	//	if (0==(r a_nd()&(256-1)))/*(1/256の確率で) (テキトー)*/
		if (0==((src->center.x256)&(256-1)))/*(1/256の確率で) (テキトー)*/
		{
			bullet_create_teki_homing(src); /* 敵側の誘導ミサイルを作成する */
		}
	}

//	zako_move_ty pe11_radius(src);
	src->center.x256 = (src->zd00_target_x256);
	src->center.y256 = (src->zd01_target_y256);
	/*以下(rwingx.c)と同じ*/
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type02(src);/*(rwingx共通、アニメーション)*/
}

/*---------------------------------------------------------
	"メイド1",		"RWINGX",	rwingx
	-------------------------------------------------------
	上から横に等間隔で整列して現れ、プレイヤーに向かい
	ある程度近づくと、弾置いて反転して逃げる。
	-------------------------------------------------------
	"メイド2",		"ZATAK",
	-------------------------------------------------------
	rwingx_zatak (赤い妖精)
	左右から現れ、自機狙い弾を打った後、真下へ直進してくる。
	-------------------------------------------------------
		"メイド3",		"CURVER",	rwingx_curver
	-------------------------------------------------------
上から現れてS字をn回描いて横へ

←←
↓
→→→→→
		↓
←←←←←
↓
→→→→→
		↓
←←←←←
	-------------------------------------------------------
	バグあり。
	-------------------------------------------------------
	"メイド4",		"CIR",	rwingx_cir
	-------------------------------------------------------
	右側から二列縦隊で現れ、下に向かい。下で旋回。
	中央から上昇し、右側に向かい。上で旋回。
	右側から下に向かい。画面外へ退場。
---------------------------------------------------------*/


/*---------------------------------------------------------
	JYUMYOU_ZAKO_HASSEI
... なにもしない
	JYUMYOU_ZAKO_HASSEI-byou60(1)
	加速
	JYUMYOU_ZAKO_HASSEI-byou60(2)
	減速
	JYUMYOU_ZAKO_HASSEI-byou60(2)-1
	狙う
	JYUMYOU_ZAKO_HASSEI-byou60(2)-2
	？(何もしないで惰性で進む)
	JYUMYOU_ZAKO_HASSEI-byou60(16+2)-1
	加速しながら プレイヤーに突っ込んでくる
	JYUMYOU_ZAKO_HASSEI-byou60(16+16+2)-1
	画面外ならおしまい
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_zako_15_meido1)
{
//	if (JYUMYOU_ZAKO_HASSEI -byou60(16+16+2)-1 > src->jyumyou)
//	{
//		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
//	}
//	else
//	if (JYUMYOU_ZAKO_HASSEI -byou60(16+2)-1 > src->jyumyou)
//	{
//		src->zd02_system_speed256	+= t256(0.1);/*加速しながら プレイヤーに突っ込んでくる*/
//		if (src->center.y256 >= t256(GAME_HEIGHT-150))
//		{
//			zako_shot_supeka(src);
//		//	src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(16+2)-1-1);
//			src->tmp_angleCCW1024 += (1024/2);	/* (1024/2) == [180/360 度] 反転して逃げる */
//			mask1024(src->tmp_angleCCW1024);
//		//	src->zd02_system_speed256 = /*t256(6+teki_rank)*/;/*速過ぎ*/
//		}
//	}
//	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(2)-2 > src->jyumyou)
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(2)-1 > src->jyumyou)
	{
		/* プレイヤーに突っ込んでくる / schnell richtung player */
	//	src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(2)-1-1);
		VR06	= ((src->center.x256));
		VR07	= ((src->center.y256));
	//	cal culate_jikinerai();
	{
	//	OBJ *zzz_player;
	//	zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
		VR04	= t256(32+((480-128-32)/2));// (zzz_player->center.x256);		/*(狙い先)*/
		VR05	= t256(200);// ()(zzz_player->center.y256); 	/*(狙い先)*/
		#if (0)/*(旧仕様メモ)*/
		VR06	= (dest->center.x256);			/*(狙い元)*/
		VR07	= (dest->center.y256);			/*(狙い元)*/
		#endif
		// 旧仕様メモ(zzz_player, dest);
		CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	}
	//	src->tmp_angleCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));		/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
		src->tmp_angleCCW65536 = ( (HATSUDAN_R13_angle65536));		/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
	//	src->zd02_system_speed256	= /*t256(3+(teki_rank>>1))*/ /*(4+teki_rank)*/;/* 速過ぎ */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-byou60(2) > src->jyumyou)/* 2048+1 */
	{
		if (t256(0.0) < src->zd02_system_speed256)
		{
			src->zd02_system_speed256 -= (5);/*t256(0.1)*/ /*減速*/
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-byou60(1) > src->jyumyou)/* 2048+1+60 */
	{
		if (t256(1.0) > src->zd02_system_speed256)
		{
			src->zd02_system_speed256 += (5);/*t256(0.1)*/ /*加速*/
		}
	}
//
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type01(src);/*(メイド共通、アニメーション)*/
}


static OBJ_CALL_FUNC(move_zako_18_meido4)
{
	{
		src->zd03_system_hoson_angle65536 += (10<<6);
		//------------------
		HATSUDAN_R11_speed256	= ((src->zd04_system_hoson_speed256)>>1);
		HATSUDAN_R13_angle65536 = ((src->zd03_system_hoson_angle65536));
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		src->center.x256 += VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		src->center.y256 += VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
	}
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type01(src);/*(メイド共通、アニメーション)*/
}


static OBJ_CALL_FUNC(move_zako_16_meido2)
{
	if (JYUMYOU_ZAKO_HASSEI -40-512-512-512-512 > src->jyumyou)/* 退場 */
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512-512-512 > src->jyumyou)/* 真下に直進 */
	{
		src->zd02_system_speed256 += t256(0.2);/*加速*/ /*t256(0.3)*/
		if (src->zd02_system_speed256 > t256(2.5)) /*t256(3.0)*/
		{
			src->zd02_system_speed256 = t256(2.5); /* 加速最大値 */
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-512-512-1);
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512-512 > src->jyumyou)/* 弾撃つ */
	{
		/* CCWの場合 */
	//	src->tmp_angleCCW1024					= cv1024r(0);/* 真下に向きを固定 */
		src->tmp_angleCCW65536					= cv65536r(0);/* 真下に向きを固定 */
		//if (data_hari_rank256/*src->le vel*/)
		{
			zako_shot_supeka(src);
		}
		src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-512-1);/* 次へ */
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40-512 > src->jyumyou)/* ほぼ真下を向く */
	{
		/* CCWの場合 */
	//	if (src->tmp_angleCCW1024 < cv1024r(180))
		if ((src->tmp_angleCCW65536>>6) < cv1024r(180))/*r42*/
		{
		//	src->tmp_angleCCW1024 -= cv1024r(3);/*fps_factor*/
			src->tmp_angleCCW65536 -= cv65536r(3);/*fps_factor*/
		//	if (src->tmp_angleCCW1024 < cv1024r(0))
			if (src->tmp_angleCCW65536 < cv65536r(0))
			{
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-1);/* 次へ */
			}
		}
		else
		{
		//	src->tmp_angleCCW1024 += cv1024r(3);/*fps_factor*/
			src->tmp_angleCCW65536 += cv65536r(3);/*fps_factor*/
		//	if (src->tmp_angleCCW1024 > cv1024r(360))
		//	if (src->tmp_angleCCW65536 > cv65536r(360))/*r42だめかも*/
			if (((src->tmp_angleCCW65536)>>6) > cv1024r(360))/*r42*/
			{
				src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-512-1);/* 次へ */
			}
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -40 > src->jyumyou)/* 画面左右から登場 */
	{
		src->zd02_system_speed256 -= t256(0.02);/*fps_factor*/ /* 減速 */
		if (src->zd02_system_speed256 <= 0)/* 速度が無いなら */
		{
			src->zd02_system_speed256 = 0;/* 停止 */
			src->jyumyou	= (JYUMYOU_ZAKO_HASSEI -40-512-1);/* 次へ */
		}
	}
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type01(src);/*(メイド共通、アニメーション)*/
}


static OBJ_CALL_FUNC(move_zako_17_meido3)
{
	if (JYUMYOU_ZAKO_HASSEI -byou60(8+8+8) > src->jyumyou)				// SS03:	/* 左(斜め上)へ移動中 */
	{
		if (0 < src->zd04_kaisu_nnn)
		{
			if (src->center.x256 <= src->zd00_clip_left256)
			{
				src->zd04_kaisu_nnn--;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI-1);/*SS00*/
			}
		}
		else	/* 退場中 */
		{
			gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(8+8) > src->jyumyou)			// SS02:	/* 右周りで回転中 */
	{
		src->tmp_angleCCW65536 -= src->zd03_turnspeed65536;/*fps_factor*/	/* CCWの場合 */
		mask65536(src->tmp_angleCCW65536);
		/* 左(斜め上)を向いたら */
	//	if ((512+32) < src->tmp_angleCCW1024)			//cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
		/* CCWの場合 */
	//	if (0 != (0x200 & src->tmp_angleCCW1024))			/* (cv1024r(180) < src->tmp_angleCCW1024) */
		if (0 != ((0x200<<6) & src->tmp_angleCCW65536)) 		/* (cv1024r(180) < src->tmp_angleCCW1024) */
		{
		//	if ((512+256-32) > src->tmp_angleCCW1024)	//cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
			if (((512+256-32)<<6) > src->tmp_angleCCW65536) //cv1024r(180 /*270*/ /*90+*/ /*180-90-90*/ /*+10*/)
			{
			//	src->tmp_angleCCW1024 = cv1024r(180/*+10*/);
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8+8+8)-1);/*SS03*/
				zako_shot_supeka(src);	/* easy以外は狙い弾を撃つ */
			}
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI -byou60(8) > src->jyumyou)		// SS01:	/* 右(斜め上)へ移動中 */
	{
		if (0 < src->zd04_kaisu_nnn)
		{
			if (src->center.x256 >= src->zd01_clip_right256)
			{
				src->zd04_kaisu_nnn--;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8+8)-1);/*SS02*/
			}
		}
		else	/* 退場中 */
		{
			gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
		}
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI > src->jyumyou) 	// SS00:	/* 左周りで回転中 */
	{
		src->tmp_angleCCW65536 += src->zd03_turnspeed65536;/*fps_factor*/	/* CCWの場合 */
		mask65536(src->tmp_angleCCW65536);
		/* 右(斜め上)を向いたら */
		/* CWの場合 */
	//	if ((1024-32) < src->tmp_angleCCW1024)		/*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
		/* CCWの場合 */
	//	if (0 == (0x200 & src->tmp_angleCCW1024))/* (cv1024r(180) > src->tmp_angleCCW1024) */
		if (0 == ((0x200<<6) & src->tmp_angleCCW65536))/* (cv1024r(180) > src->tmp_angleCCW1024) */
		{
		//	if ((256+32) < src->tmp_angleCCW1024)	/*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
			if (((256+32)<<6) < src->tmp_angleCCW65536) /*eps*/ /*<= cv1024r(0)*/	//cv1024r(10/*90*/ /*-90*/ /*360*/ /*-10*/
			{
			//	src->tmp_angleCCW1024 = cv1024r(0/*360*/ /*-10*/)/*cv1024r(360)*/;
				src->jyumyou = (JYUMYOU_ZAKO_HASSEI -byou60(8)-1);/*SS01*/
				zako_shot_supeka(src);	/* easy以外は狙い弾を撃つ */
			}
		}
	}
/*現在仕様上おかしい*/
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type01(src);/*(メイド共通、アニメーション)*/
}

/*---------------------------------------------------------
		"青妖精1",		"FAIRY",
		"青妖精4", (予定)		"FAIRY",	(r27から新規追加)
	-------------------------------------------------------
	user_locate_x:	速度256[speed256]
	user_locate_y:	横位置[pixel]
	-------------------------------------------------------
		"青妖精2",		"SPLASH",
	-------------------------------------------------------
		"青妖精3",		"FAIRY",	(r27から新規追加)
	-------------------------------------------------------
	user_locate_x:	速度256[speed256]
	user_locate_y:	横位置[pixel]
	-------------------------------------------------------
		"烏1",		"", (r27から新規追加)
	-------------------------------------------------------
	user_locate_x:	速度256[speed256]
	user_locate_y:	横位置[pixel]
---------------------------------------------------------*/


static OBJ_CALL_FUNC(move_ao_yousei1)
{
	/* ザコ発生から5[秒]以上経過していれば、チェック */
	if (JYUMYOU_ZAKO_HASSEI-byou60(5) > src->jyumyou)	/* 離脱 */
	{
		src->zd02_system_speed256 += (2);/*(2+1)*/
	//	src->tmp_angleCCW1024 += (4);
		src->tmp_angleCCW65536 += (4<<6);
	//	if (511 < src->tmp_angleCCW1024)
	//	{
	//		src->tmp_angleCCW1024 = (511);/*真上*/
	//	}
		if ((511<<6) < src->tmp_angleCCW65536)
		{
		//	src->tmp_angleCCW1024 = (511);/*真上*/
			src->tmp_angleCCW65536 = (511<<6);/*真上*/
		}
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else	/* 攻撃 */
	{
		/* ザコ発生から4.5[秒]経過した場合に、攻撃 */
	//	if ((JYUMYOU_ZAKO_HASSEI-byou60(4.5) )==src->jyumyou)
	//	{
	//		if (0!=(cg_VR20_game_difficulty))
	//		{
	//			zako_shot_supeka(src);
	//		}
	//	}
//		ca se 0x40: /*not_break;*/	/*0x40==064 0x46==070*/
//		ca se 0x80: /*not_break;*/	/*0x80==128 0x78==120*/
//		ca se 0xa0: /*not_break;*/	/*0x  ==170 0xaa==170*/
//		ca se 0xc0: 				/*0x  ==220 0xdc==220*/
		if (0x00==(src->jyumyou&(0x1f)))/* 8回 */
		{
			if (0!=(cg_VR20_game_difficulty))
			{
				zako_shot_supeka(src);
			}
		}
		src->zd02_system_speed256 -= (5/*5*/);
		if (0 >= src->zd02_system_speed256)
		{
			src->zd02_system_speed256 = 1;
		}
	}
	/*以下(rwingx.c)と同じ*/
	zako_system_move_vector(src);/*(ザコシステム標準移動処理)*/
	zako_anime_type02(src);/*(rwingx共通、アニメーション)*/
}


static OBJ_CALL_FUNC(move_zako_12_ao_yousei)
{
	if (JYUMYOU_ZAKO_HASSEI-60 > src->jyumyou)	/* 退場の動き */
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
		src->center.x256 -= src->math_vector.x256;/*fps_factor*/
		src->center.y256 -= src->math_vector.y256;/*fps_factor*/
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-59 > src->jyumyou)	/* 弾を撃つ */
	{
		zako_shot_supeka(src);
		src->zd04_kaisu_nnn--;
		if (0 > src->zd04_kaisu_nnn)
		{
			;/* 退場準備 */
		}
		else
		{
			src->jyumyou = (JYUMYOU_ZAKO_HASSEI -50);/*戻る*/
		}
	}
	else
	if (JYUMYOU_ZAKO_HASSEI-49 > src->jyumyou)	/* 少し待つ */
	{
//		VR06	= ((src->center.x256));
//		VR07	= ((src->center.y256));
//	//	cal culate_jikinerai();
//	{
//		#if (0)/*(旧仕様メモ)*/
//		VR06	= (dest->center.x256);			/*(狙い元)*/
//		VR07	= (dest->center.y256);			/*(狙い元)*/
//		#endif
//		// 旧仕様メモ
//		 (calculate_jiki_nerai);/* 自機狙い角作成 */
//	}
	//	src->tmp_angleCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));		/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
	//	mask1024(src->tmp_angleCCW1024);
		src->tmp_angleCCW65536 = ( (HATSUDAN_R13_angle65536));		/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
		mask65536(src->tmp_angleCCW65536);
	}
	else
//	if (JYUMYOU_ZAKO_HASSEI+1-10 > src->jyumyou)	/* 登場の動き */
	{
		src->center.x256 += src->math_vector.x256;/*fps_factor*/
		src->center.y256 += src->math_vector.y256;/*fps_factor*/
	}
	/* アニメーション */
	zako_anime_type01(src);
}


static OBJ_CALL_FUNC(move_zako_14_karasu)
{
	/* ザコ発生から5[秒]以上経過していれば、チェック */
	if ((JYUMYOU_ZAKO_HASSEI-/*320*/(5*60)/*512*/) > src->jyumyou)	/* 離脱 */
	{
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	{
		/* 攻撃 */
		if (0 == ((src->jyumyou) & 0x3f))
		{
			if (cg_VR20_game_difficulty)
			{
				zako_shot_supeka(src);
			}
		}
	}
	/* 移動する */
	src->center.x256 += (src->math_vector.x256);/*fps_factor*/
	src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	/* アニメーション */
	zako_anime_type02(src);
}


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	ザコ敵を追加する
---------------------------------------------------------*/

static GAME_COMMAND_OBJ_FUNC(regist_zako_12_ao_yousei)
{
	/* 登場の動き / 退場の動き */
		 if (t256(64)			 > gcmd_obj->center.x256)	{gcmd_obj->math_vector.x256 =	t256(2.0);	}	/* 出現位置が左なら、右へ移動 */
	else if (t256(GAME_WIDTH-64) < gcmd_obj->center.x256)	{;} 					/* 中心付近なら左右に移動しない */
	else													{gcmd_obj->math_vector.x256 = -t256(2.0);	}	/* 出現位置が右なら、左へ移動 */

	gcmd_obj->math_vector.y256 = (0);

	#if 1// (1==USE_X_HOUKOU)
	if (0 > (gcmd_obj->center.y256))
	{
		/* y座標が負方向の場合は、x座標指定なので(x座標 y座標 を逆にする) */
		{
			int s_sss;
			s_sss					=  (gcmd_obj->center.x256);
			gcmd_obj->center.x256	= -(gcmd_obj->center.y256);
			gcmd_obj->center.y256	= s_sss;
		}
		gcmd_obj->math_vector.y256	= (gcmd_obj->math_vector.x256);
		gcmd_obj->math_vector.x256	= (0);
	}
	#endif
	gcmd_obj->zd04_kaisu_nnn		= (3);	/* 3回撃つ */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_11_siro_kedama)
{
	gcmd_obj->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/* 白っぽく */
	//
	gcmd_obj->center.y256			= ((gcmd->user_locate_y)<<8);
	gcmd_obj->math_vector.x256		= ((gcmd->user_locate_x));
	gcmd_obj->math_vector.y256		= (0);
	//
	{
		if (0 < (gcmd_obj->math_vector.x256))
		{/* [引数 user_locate_y が正方向の場合、右へ移動(→)] [引数yが負方向の場合、下へ移動(↓)] */
			gcmd_obj->center.x256	= t256(-30)/*-(i<<(5+8))*/;
		}
		else
		{/* [引数 user_locate_y が正方向の場合、左へ移動(←)] [引数yが負方向の場合、上へ移動(↑)] */
			gcmd_obj->center.x256	= t256(360)/*+(i<<(5+8))*/;/* 360 > 352(x_max) > 272(y_max) */
		}
	}
	//
	if (0 > (gcmd_obj->center.y256))
	{
		/* y座標が負方向の場合は、x座標指定なので(x座標 y座標 を逆にする) */
		{
			int s_sss;
			s_sss					= gcmd_obj->center.x256;
			gcmd_obj->center.x256	= -(gcmd_obj->center.y256);
			gcmd_obj->center.y256	= s_sss;
		}
		gcmd_obj->math_vector.y256	= (gcmd_obj->math_vector.x256);
		gcmd_obj->math_vector.x256	= (0);
	}
	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* 回転アニメ */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_14_karasu)
{
//	gcmd_obj->center.y256				= ((gcmd->us er_loc ate_y)<<8);
//	gcmd_obj->math_vector.x256			= ((gcmd->us er_loc ate_x));
//	game_command_regist_zako_999_karasu_common( l, h);
//	if (512 > gcmd_obj->tmp_angleCCW1024)
	if ((512<<6) > gcmd_obj->tmp_angleCCW65536)
	{/* [角度が 0 ...511 の場合、右へ移動(→)] [引数yが負方向の場合、下へ移動(↓)] */
		gcmd_obj->zd04_KARASU3_houkou		= ((0x30)>>2);/*右向きカラス*/
	}
	else
	{/* [角度が 512 ...1023 の場合、左へ移動(←)] [引数yが負方向の場合、上へ移動(↑)] */
		gcmd_obj->zd04_KARASU3_houkou		= ((0x50)>>2);/*左向きカラス*/
	}
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_05_kisume)
{
//	/* 初期位置 */
	/*(基本的に雑魚ではra_nd()使用禁止)*/
	VR04	= ((ra_nd()&((256*256)-1)))+t256(64);/*320?*/ /*t256(ra_nd()%270)+t256(50)*/	/* 弾源x256 */
	VR05	= ((ra_nd()&((256*128)-1)))+t256(16);/*350?*/ /*t256(ra_nd()%300)+t256(50)*/	/* 弾源y256 (256*256) */
	set_REG_DEST_XY(gcmd_obj);
	CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
	//------------------
//384	src->zd02_system_speed256	= (t256(1.5));
//	HATSUDAN_R11_speed256	= (src->zd02_system_speed256);
//	HATSUDAN_R13_angle65536 = (HATSUDAN_R13_angle65536);
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	gcmd_obj->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	gcmd_obj->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
//
	gcmd_obj->jyumyou				= (80)+byou60(1)+(2);
// グラ回転しない方がインパクトがある。
	gcmd_obj->zako_anime_rotate_angle65536 = (0);	/* 回転アニメ */
//重複	gcmd_obj->rotationCCW65536 = (0);
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_10_hai_kedama)
//static GAME_COMMAND_OBJ_FUNC(regist_zako_010_kedama1)
{
	gcmd_obj->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/*白っぽく */
	{
		/* 第一目標はプレイヤーのいた位置 */
		int www_ppp_center_x256;
		int www_ppp_center_y256;
		www_ppp_center_x256 			= ra_nd()&0xffff;/*(基本的に雑魚ではra_nd()使用禁止)*/
		www_ppp_center_y256 			= ra_nd()&0xffff;/*(基本的に雑魚ではra_nd()使用禁止)*/
		gcmd_obj->zd00_target_x256		= (www_ppp_center_x256);
		gcmd_obj->zd01_target_y256		= (www_ppp_center_y256);
	//	gcmd_obj->zd01_target_y256		= ((www_ppp_center_y256)>>1);	/* 特攻禁止 */
	}
	gcmd_obj->math_vector.x256			= (0);
	gcmd_obj->math_vector.y256			= (0);
//	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* 回転アニメ */
//	gcmd_obj->zako_anime_rotate_angle65536 = (5<<6);	/* 回転アニメ(5) */
	gcmd_obj->zako_anime_rotate_angle65536 = (7<<6);	/* 回転アニメ */
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_07_yukari)
{
//	s_jikinerai_sincos(h);
	gcmd_obj->zako_anime_rotate_angle65536 = (10<<6);	/* 回転アニメ */
	gcmd_obj->zd04_max_y256 		= (t256(GAME_HEIGHT)-t256(60));
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_13_obake)
{
	/*(基本的に雑魚ではra_nd()使用禁止)*/
//	gcmd_obj->tmp_angleCCW1024		= (ra_nd()&(1024-1));
	gcmd_obj->tmp_angleCCW65536 	= (ra_nd()&(65536-1));
	gcmd_obj->zd00_target_x256		= t256( 62) + ((ra_nd()&((256*256)-1)));/*t256*/  /*(GAME_WIDTH/2)*/ /* GAME_WIDTH 380 ~= 380 == 62+256+62 */
	gcmd_obj->zd01_target_y256		= t256(-32);/*(-100)*/
	gcmd_obj->zd02_radius256		= t256(10);
	gcmd_obj->zd04_kaisu_nnn		= (0);/*(フラグ)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_02_inyou_dama)
{
	gcmd_obj->callback_loser		= item_create_002_inyou_zako;
	gcmd_obj->zd01_target_y256		= (t256(128)-((/*yyy*/(gcmd->user_kougeki_type)&0x0f)<<(5+8))); /* 仮想地面 / 閾値 */
	gcmd_obj->math_vector.x256		= (ra_nd()&0x1ff);/*(基本的に雑魚ではra_nd()使用禁止)*/
	gcmd_obj->math_vector.y256		= (ra_nd()&0x1ff);/*(基本的に雑魚ではra_nd()使用禁止)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_04_kakomi)
{
	#if 0
	gcmd_obj->zd02_radius256		= t256(350);
	gcmd_obj->tmp_angleCCW1024		= (gcmd->user_locate_x);/*(角度[deg1024])*/
	gcmd_obj->zd00_target_x256		= t256(GAME_WIDTH/2);/* GAME_WIDTH 380 ~= 380 == 62+256+62 */
	gcmd_obj->zd01_target_y256		= t256(GAME_HEIGHT/2);
	#endif
//
	gcmd_obj->zd00_target_x256		= (gcmd_obj->center.x256);/*(中心位置)*/
	gcmd_obj->zd01_target_y256		= (gcmd_obj->center.y256);/*(中心位置)*/
	gcmd_obj->zd02_radius256		= /*t256(350);*/((gcmd_obj->zd02_system_speed256)<<8);/*(初期半径)*/	/*([r39例外]とりあえず)*/
//	gcmd_obj->tmp_angleCCW1024		= (gcmd_obj->tmp_angleCCW1024);/*(角度[deg1024])*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_03_tatsumaki)
{
//	src->zako_anime_rotate_angle1024	= (src->tmp_angleCCW1024); /* vx_r 回転方向(回転量) */
//	src->zako_anime_rotate_angle1024	= (src->zako_anime_rotate_angle1024);	/* vx_r 回転方向(回転量) */
	gcmd_obj->zd03_px256				= t256(GAME_WIDTH-10);	/*0*/	/*t256(GAME_WIDTH/2)*/
}


static GAME_COMMAND_OBJ_FUNC(regist_zako_17_meido3)
{
	gcmd_obj->zd03_turnspeed65536		= ((7*2)<<6);
	gcmd_obj->zd04_kaisu_nnn			= (4);
//
	gcmd_obj->zd00_clip_left256 		= (t256(32+16));	/*50*/			/* 32,	224(128+64+32)	*/
	if (t256(GAME_WIDTH/2) < gcmd_obj->center.x256)
	{	/* 画面右側から出現 */
		gcmd_obj->jyumyou				+= (512+512+512+512);	/* (1024-1) or (2048-1) */		/*SS00*/
		gcmd_obj->zd00_clip_left256 	+= (t256((128+64)));	/*50*/			/* 32,	224(128+64+32)	*/
	}
//	else	{;/* 画面左側から出現 */}
	gcmd_obj->zd01_clip_right256		= (gcmd_obj->zd00_clip_left256)+t256(128-32); /* 128, 320(256+64) */	 //  /*GAME_WIDTH-50-s->w*/
}
