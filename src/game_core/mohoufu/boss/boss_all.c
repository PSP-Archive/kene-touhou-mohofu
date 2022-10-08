
#include "boss.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	現在ボス行動は、C言語のプログラムになっているけど、
	ここは総て廃止して、弾幕スクリプトで行動できるようにしたい。
	-------------------------------------------------------
	弾幕スクリプトには弾の移動コマンド系以外に、
	ボス行動コマンド系を盛り込む。
---------------------------------------------------------*/

/*---------------------------------------------------------
	★ 蓬莱山 輝夜
	Houraisan Kaguya.
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	ボス行動、第 4形態
	斜め移動
	-------------------------------------------------------
	使用レジスタ
	cg_BOSS_DATA_35_move_jyumyou	カウンタ。()
	R0e 	目標座標 x256
---------------------------------------------------------*/

extern void spell_boss_move_system_12_kaguya_funya_idou(void)
{
	/* カードを撃ってない場合に追加 */
	if (SPELL_00==card.spell_used_number)	/* スペル生成終了ならカード生成 */
	{
		/* 気分で目標を決める。 */
		VR0e = ((ra_nd() & 0xffff))+(t256(48+32));
	}
	cg_BOSS_DATA_35_move_jyumyou++;
	if (8 < cg_BOSS_DATA_35_move_jyumyou)
	{
		cg_BOSS_DATA_35_move_jyumyou = 0;
		/* 目標にちかづこうと努力。 */
		cg_BOSS_DATA_30_target_x256 += ((cg_BOSS_DATA_30_target_x256 < VR0e) ? t256(8) : -t256(8) );
		cg_BOSS_DATA_30_target_x256 &= 0xffff;
	#if (1)
	//------------------
	HATSUDAN_R11_speed256	= t256(64);//(256<<6);
	HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_30_target_x256>>4));
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	cg_BOSS_DATA_31_target_y256 = t256(25) + VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
	#else/*([未テスト])*/
	//------------------
	HATSUDAN_R11_speed256	= (t256(1.0));
	HATSUDAN_R13_angle65536 = deg1024to65536((((cg_BOSS_DATA_30_target_x256>>4)/*&(1024-1)*/)));
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	cg_BOSS_DATA_31_target_y256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	cg_BOSS_DATA_31_target_y256 <<= (6);
	cg_BOSS_DATA_31_target_y256 += t256(25);
	//------------------
	#endif
		boss_set_new_position_from_target();/*(誘導移動座標をターゲットから設定)*/
	}
}


/*---------------------------------------------------------
	ボス行動、第 1形態
	微上下移動
	-------------------------------------------------------
	使用レジスタ
	cg_BOSS_DATA_35_move_jyumyou	カウンタ。()
---------------------------------------------------------*/

extern void spell_boss_move_system_11_kaguya_yureru(void)
{
	cg_BOSS_DATA_35_move_jyumyou += (10);
//	mask1024(cg_BOSS_DATA_35_move_jyumyou);
	//------------------
	HATSUDAN_R11_speed256	= (t256(4));
	HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_35_move_jyumyou));
	CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
	cg_BOSS_DATA_3b_center_y256 = t256(25) + VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
}


/*---------------------------------------------------------
	★ 射命丸 文
	Syameimaru Aya.
	-------------------------------------------------------
	差分氏の作った攻撃をスペカにする。
	-------------------------------------------------------
	差分氏：自分で思ったよりも第2形態の攻撃パターンがカオスになってしまった。
	差分氏：もっと丁寧に作り直した方がいいかも。
	差分氏：天狗の速度を難易度ごとに変えてみた。
	-------------------------------------------------------
	使用レジスタ
	cg_BOSS_DATA_35_move_jyumyou	カウンタ。()
	R09 	攻撃タイプ(発弾部へ受け渡し用)
	R0a 	後追い弾の種類	aya_atooidan_type
---------------------------------------------------------*/

/* 1なのは随分古い仕様。現在はシステムで ketm 方式の CONTROLLER は無い。
がそれに代わる東方風 方式の CONTROLLER は作るかもしれない。
( CONTROLLER ってのは、ボスの周りふわふわして弾出すアレ。) */
#define USE_CONTROLLER (0)

/*---------------------------------------------------------
	天狗用の大玉弾(青)。乱数で怪しげな動きをする。
	-------------------------------------------------------
	見た目＞＞あたり判定です。
--------------------------------------------------------*/

/*---------------------------------------------------------
	ボス行動、第 5形態
	移動攻撃パターン2(高速移動)
---------------------------------------------------------*/

/*(SS_TAN_I_JIKAN: need 2^n, 2のn乗で割り切れる必要あり)*/
#define SS_TAN_I_JIKAN (4096)
/*
---0
[A]退避座標設定
---1
[B]退避行動
---2
[C]攻撃移動
---3
[D]攻撃
---3+220 -> 0 へ。

*/
/*(文の幅50[pixel])*/
//#define AYA_OBJ_WIDTH50 (50)

/* 出現時x座標 */
//#define BOSS_XP256		(t256(GAME_WIDTH/2))	/* 中心座標なので */
#define BOSS_XP256			(t256(GAME_X_OFFSET)+t256(GAME_320_WIDTH/2))	/* 中心座標なので */
extern void spell_boss_move_system_13_aya_taifu(void)
{
	cg_BOSS_DATA_35_move_jyumyou++;
	if ((SS_TAN_I_JIKAN*1) > cg_BOSS_DATA_35_move_jyumyou)	/* [A]退避座標設定 */
	{
		cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*1);
	//	cg_BOSS_DATA_30_target_x256 = t256(GAME_X_OFFSET)+t256((GAME_320_WIDTH-AYA_OBJ_WIDTH50)/2);
	//	cg_BOSS_DATA_30_target_x256 = BOSS_XP256;
		cg_BOSS_DATA_31_target_y256 = t256(30.0); /* t256(20.0) */
		/* 移動座標を決める */
		boss_set_new_position_from_target();/*(誘導移動座標をターゲットから設定)*/
	}
	if ((SS_TAN_I_JIKAN*2) > cg_BOSS_DATA_35_move_jyumyou)	/* [B]退避行動 */
	{
	//	ca se SS00: /* 不定:初期位置情報の取得->SS02へ */
	//	ca se SS02: /* 不定:初期位置へ戻る->SS03へ */	/* 時間で */
		/*(攻撃条件[A])*/
		if (t256(31.0) > cg_BOSS_DATA_3b_center_y256)
		{
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*2);
			VR0f_AYA_LINK = AYA_LINK_01_RENDAN; /* 攻撃 */
		}
	}
	else
	if ((SS_TAN_I_JIKAN*3) > cg_BOSS_DATA_35_move_jyumyou) /* [C]攻撃移動 */
	{
	//	ca se SS03: /* 初期位置:大弾3つ->SS02, SS02, SS04 */	/* 時間で */
		/*(攻撃条件[B])*/
	//	if (/*150*/240+(SS_TAN_I_JIKAN*2) < cg_BOSS_DATA_35_move_jyumyou )	/* 時間で */
		if (/*150*/24-((cg_VR20_game_difficulty)<<2)+(SS_TAN_I_JIKAN*2) < cg_BOSS_DATA_35_move_jyumyou) /* 時間で */
		{
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*3);
			VR0f_AYA_LINK = AYA_LINK_03_OODAMA_23;	/* 攻撃 */
					/*t256(5.0)*/ /* 弾速 */		/*仕様変更*/	// t256(/*1.5*/5.0/*5.0*/)
			{	/* (1/3)の確率で分岐する。 */
				VR0a = ((0x00011122u>>(((ra_nd()&(8-1)))<<2))&3);	/* SS02, SS02, SS04 */
			}
			if (0 == VR0a)
			{
				OBJ *zzz_player;
				zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
			//	cg_BOSS_DATA_30_target_x256 = BOSS_XP256; /* 真中へワープ */
				cg_BOSS_DATA_30_target_x256 = zzz_player->center.x256;
				cg_BOSS_DATA_31_target_y256 = zzz_player->center.y256;
			//	#define KYORI_AAA (t256(128.0)+((cg_game_di fficulty)<<(8+4/*5*/)))
				#define KYORI_AAA (t256(128.0)+((3)<<(8+4/*5*/)))
				if (cg_BOSS_DATA_31_target_y256 > (signed)KYORI_AAA)
				{
					cg_BOSS_DATA_31_target_y256 = KYORI_AAA;
				}
				#undef KYORI_AAA
			}
			else
			if (1 == VR0a)
			{
				cg_BOSS_DATA_30_target_x256 = t256(GAME_X_OFFSET); /* */
			//	cg_BOSS_DATA_3b_center_y256 += t256(6.0);/*fps_factor*/ /* よくわかんない(?)*/
				cg_BOSS_DATA_31_target_y256 += t256(6.0);/*fps_factor*/ /* よくわかんない(?)*/
			}
			else
		//	if (2 == VR0a)
			{
			//	cg_BOSS_DATA_30_target_x256 = t256((GAME_X_OFFSET+GAME_320_WIDTH-AYA_OBJ_WIDTH50)); /* */
				cg_BOSS_DATA_30_target_x256 = t256((GAME_X_OFFSET+GAME_320_WIDTH)); /* */
			//	cg_BOSS_DATA_3b_center_y256 += t256(6.0);/*fps_factor*/ /* よくわかんない(?)*/
				cg_BOSS_DATA_31_target_y256 += t256(6.0);/*fps_factor*/ /* よくわかんない(?)*/
			}
		}
	}
	else
//	if (SS02 ==cg_BOSS_DATA_35_move_jyumyou)	/* [D]攻撃 */
	{
//-------- 分岐 [SS02]
//-------- 分岐 [SS02]
//-------- [攻撃A]
//-------- 分岐 [SS04]
//		//	/* (1/2)の確率で[攻撃A]へ分岐する。 */
//		//	if (0==(ra_nd()&(2-1)))
//			/* (1/4)の確率で[攻撃A]へ分岐する。 */
//			{
//				/* (1/2)の確率で[攻撃A]へ分岐しない。 */
//			}
//	ca se SS02: /* 左移動中->SS05へ */
//	ca se SS02: /* 右移動中->SS04へ */
//	ca se SS05: /* 左:待機->SS06へ */
//	ca se SS03: /* 左:前へ -> SS11 */
//	ca se SS04: /* プレイヤー位置付近移動中 -> プレイヤー位置付近:大弾3つ -> SS00へ */
//		sakuya_anime00(src);//		sakuya_anime08(src);
		/* ayaの稼動範囲 */ 	/* 時間で */
		/*(攻撃条件[C])*/
	//	if (/*150*/220+(SS_TAN_I_JIKAN*3) < cg_BOSS_DATA_35_move_jyumyou )	/* 時間で */
		if (/*150*/22-((cg_VR20_game_difficulty)<<2)+(SS_TAN_I_JIKAN*3) < cg_BOSS_DATA_35_move_jyumyou) 	/* 時間で */
		{
		//	cg_BOSS_DATA_35_move_jyumyou++; //	sakuya_wait_state_bbb(src/*, SS06*/);
			cg_BOSS_DATA_35_move_jyumyou = (SS_TAN_I_JIKAN*0); /* SS00へ */
			//ca se SS06: /* 左:右回転攻撃->SS00, SS03 */
			{	/* (1/3)の確率で分岐する。 */
				VR0a = ((0x00011122u>>(((ra_nd()&(8-1)))<<2))&3); 	/* SS02, SS02, SS04 */
			}
			if (0 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_02_FUDADAN;	/* 攻撃 */
				cg_BOSS_DATA_31_target_y256 = t256(GAME_HEIGHT/3); /* */
			}
			else
			#if (1==USE_CONTROLLER)
			if (1 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_03_OODAMA_21;	/* 攻撃 */
				#if (1==USE_CONTROLLER)
				eee_boss02_sr_add1(src);/* 左:右回転攻撃 */
				eee_boss02_sr_add2(src);/* 右:左回転攻撃 */
				#endif // (1==USE_CONTROLLER)
			}
			else
			#endif // (1==USE_CONTROLLER)
		//	if (2 == VR0a)
			{
				VR0f_AYA_LINK = AYA_LINK_03_OODAMA_22;	/* 攻撃 */
			}
		}
	}
	#if 1
	// 難易度が低い場合に、あまり撃たないように修正する。
	if (AYA_LINK_00_NONE != VR0f_AYA_LINK)	/*[攻撃タイプ00: 攻撃しない。]*/
	{
	// 0xfe:1111 1110 /easy.
	// 0xaa:1010 1010 /normal.
	// 0x92:1001 0010 /hard.
	// 0x00:0000 0000 /luna.
		if ((0x0092aafeu >> (((cg_VR20_game_difficulty & 0x03) << 3) + (cg_BOSS_DATA_35_move_jyumyou & 0x07))) & 0x01)
		{
			VR0f_AYA_LINK = AYA_LINK_00_NONE;// '1' の bit の場合、撃つのを止める。
		}
	}
	#endif
}


/*---------------------------------------------------------
	★ 十六夜 咲夜
	Izayoi Sakuya.
	-------------------------------------------------------
	ToDo:
	移動と弾の処理を分離しよう。でないと訳わからん。
	-------------------------------------------------------
	咲夜背後の魔方陣についてメモ
	-------------------------------------------------------
	5面中-ボスで出てくる時は、大きさ60x60(たぶん64x64obj)ぐらい。
	5面ボスで出てくる時は、大きさ125x125(たぶん128x128obj)ぐらい。
	模倣風は基本的に縮小率75%なので、咲夜背後の魔方陣は
	48x48[pixel](2倍拡大時は96x96[pixel])ぐらいが妥当かな？
---------------------------------------------------------*/

/*---------------------------------------------------------
	第10形態: 最終形態(その2)
---------------------------------------------------------*/

extern void spell_boss_move_system_16_sakuya_nazo_keitai(void)
{
	{
#if (0)/*[r41とりあえずToDo: 残件]*/
		if (src->color32 > 0xf9000000)	/*	if (src->alpha > 0xf9) */	/* (src->alpha>0xff) */
		{src->color32 = 0xffffffff;}/*	src->alpha = 0xff;*/
		else /*if (src->alpha<0xff)*/
		{src->color32 += 0x05000000;}/* src->alpha += 0x05;*/
#endif
//
#if (0)/*[r41とりあえずToDo: 残件]*/
		#if (0)//
		cg_BOSS_DATA_3a_center_x256 -= ((si n1024((src->tm p_ang leCCW1024))*(t256(0.03)))>>8);/*fps_factor*/		/* CCWの場合 */
		cg_BOSS_DATA_3b_center_y256 -= ((co s1024((src->tm p_ang leCCW1024))*(t256(0.03)))>>8);/*fps_factor*/
		#else
		{
			int sin_value_t256; 	//	sin_value_t256 = 0;
			int cos_value_t256; 	//	cos_value_t256 = 0;
			int256_sincos1024( (src->tmp_angleCCW1024), &sin_value_t256, &cos_value_t256);
			cg_BOSS_DATA_3a_center_x256 -= ((sin_value_t256*(t256(0.03)))>>8);/*fps_factor*/
			cg_BOSS_DATA_3b_center_y256 -= ((cos_value_t256*(t256(0.03)))>>8);/*fps_factor*/
		}
		#endif
#endif
	}
}


/*---------------------------------------------------------
	第九形態: 幻葬「フェスティバルナイフ」 最終形態(その1)
	-------------------------------------------------------
	使用レジスタ
	cg_BOSS_DATA_35_move_jyumyou	カウンタ。()
	R0c 	BO SS_DATA_07_sakuya_data_common_wait256
	-------------------------------------------------------
	R0f_SAKUYA_LINK 	[発弾連絡レジスタ]
		0:	なし。
		1:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ ryoute_knife); 咲夜 両手ナイフカード
		2:	extern OBJ_CALL_FUNC(bullet_create_sakuya_ kurukuru);	  咲夜 くるくるナイフカード
	-------------------------------------------------------
	R0e:	難易度(bullet_create_sakuya_kurukuru:プレイヤーの周りに8弾配置する)
---------------------------------------------------------*/
/*
0
	[B] [E] 両手ナイフで攻撃
//2049 ==(1024+1024+1)
81
0
	[A] [D] 何もしない(待機時間)
	[C] [F] 真ん中に来るまで移動
//2089 ==(1024+10024+1+40)
1024
	[G] [A]に戻る。

*/
	/* [C] [F] 真ん中に来るまで移動 */
	/* [G] [A]に戻る。 */

extern void spell_boss_move_system_15_sakuya_festival_knife(void)
{
	cg_BOSS_DATA_35_move_jyumyou--;/*fps_factor*/
	if (cg_BOSS_DATA_35_move_jyumyou <= 0)
	{
		cg_BOSS_DATA_35_move_jyumyou	= (300);	/* 移動時間、間隔 */
		/* [B] [E] 待機時間が終わったら 両手ナイフで攻撃 */
		{
//++	pd->bo ssmode = B00_NONE/*B01_BA TTLE*/;
		// (r35でカードの場合のみ省略可能)	VR06	= ((cg_BOSS_DATA_3a_center_x256));
		// (r35でカードの場合のみ省略可能)	VR07	= ((cg_BOSS_DATA_3b_center_y256));
		// (r35でカードの場合のみ省略可能)	set_REG_DEST_BOSS_XY(); 	/* 弾源x256 y256 中心から発弾。 */
			VR04	= (t256(GAME_X_OFFSET+(GAME_320_WIDTH/2))); 		/* 弾源x256 */
			VR05	= (t256(30));					/* 弾源y256 */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);
		/* 移動座標を決める */
			cg_BOSS_DATA_36_sakuya_data_move_angle1024 = (deg65536to1024(HATSUDAN_R13_angle65536)); /* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
			//	[SAKUYA_ANIME_12_HATUDAN_START]
			//	[SAKUYA_ANIME_15_HATUDAN_END]
			VR0f_SAKUYA_LINK = (SAKUYA_LINK_01_RYOUTE_KNIFE);/*[咲夜 両手ナイフカード]*/
			if (cg_BOSS_DATA_3b_center_y256 > t256(150))
		//	{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(	210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}	/* CWの場合 */
		//	{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(360-210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}	/* CCWの場合 */
			{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = cv1024r(360-210) + (((ra_nd()&(4096-1))*21)>>8) /*(ra_nd()%(deg_360_to_512(120)))*/;}
			else
			{	cg_BOSS_DATA_36_sakuya_data_move_angle1024 = ((ra_nd()&(1024-1)));}
			#if 1
			/*念の為*/
			mask1024(cg_BOSS_DATA_36_sakuya_data_move_angle1024);
			#endif
			#if (0)//t256(3.0) t256(3.5)
			cg_BOSS_DATA_3a_center_x256 += ((si n1024((cg_BOSS_DATA_36_sakuya_data_move_angle1024))*(t256(3.0)))>>8);/*fps_factor*/ /* CCWの場合 */
			cg_BOSS_DATA_3b_center_y256 += ((co s1024((cg_BOSS_DATA_36_sakuya_data_move_angle1024))*(t256(3.0)))>>8);/*fps_factor*/
			#else
		//	{
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536( deg1024to65536(cg_BOSS_DATA_36_sakuya_data_move_angle1024), &sin_value_t256, &cos_value_t256);
		//		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 + ((sin_value_t256*(t256(30.0)))>>8);/*fps_factor*/
		//		cg_BOSS_DATA_31_target_y256 = cg_BOSS_DATA_3b_center_y256 + ((cos_value_t256*(t256(30.0)))>>8);/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= (t256(30.0));
			HATSUDAN_R13_angle65536 = (deg1024to65536(cg_BOSS_DATA_36_sakuya_data_move_angle1024));
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 + VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			cg_BOSS_DATA_31_target_y256 = cg_BOSS_DATA_3b_center_y256 + VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
			#endif
			#if (1)
			/* 移動座標を決める */	/* 攻撃アニメーション */
			boss_set_new_position_from_target();/*(誘導移動座標をターゲットから設定)*/
			#endif
			//
			OBJ *zzz_player;
			zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
			#if 1/*Gu(中心座標)*/
			if ((zzz_player->center.x256 < cg_BOSS_DATA_3a_center_x256 + t256(25)) &&	/* (?)*/
				(zzz_player->center.x256 > cg_BOSS_DATA_3a_center_x256 - t256(25)))
			#endif
			{
				VR0c++;/*fps_factor*/
			}
			if (VR0c > 24)/*(21 r35u1)*/
			{
				VR0c	= 0;
#if (0)/*[r41とりあえずToDo: 残件]*/
				{
			//		src->color32			= MAKE32RGBA(0xff, 0xff, 0xff, 0x00);			/*	src->alpha			= 0x00;*/
					src->color32			= MAKE32RGBA(0xff, 0xff, 0xff, 0x80);			/*	src->alpha			= 0x00;*/	/* 半透明 */
					src->tmp_angleCCW1024	= (0);
				}
#endif
				//	[SAKUYA_ANIME_12_HATUDAN_START]
				//	[SAKUYA_ANIME_15_HATUDAN_END]
				VR0f_SAKUYA_LINK = (SAKUYA_LINK_02_KURU_KURU);/*[咲夜 くるくるナイフカード]*/
			}
		}
	}
}


/*---------------------------------------------------------
	第02形態: 奇術「ミスディレクション」
	-------------------------------------------------------
	使用レジスタ
//	cg_BOSS_DATA_35_move_jyumyou	カウンタ。()
//	R09 	BO SS_DATA_07_sakuya_data_common_wait256
---------------------------------------------------------*/

/*
		64		256-64		256-0
	//	真中へワープ
		128 				256-64
	// なにもしない
		192 				256-128
	// 反転移動方向セット
		256 				256-192
	// なにもしない
		0		256 		256-256
	//	反対側へワープ
-------------------------

256 	真中へワープ

250 	反対側へワープ
*/
/*(ゲーム画面のx座標中心位置)==(左端のパネル部分)+(ゲーム領域画面の半分)*/
#define SAKUYA_POINT_X_MID			(t256(GAME_X_OFFSET+(GAME_320_WIDTH/2)))

extern void spell_boss_move_system_28_sakuya_miss_direction(void)
{
	if (/*(256-64)*/(255)/*192+64*/ == VR10_BOSS_SPELL_TIMER) /* 反転移動方向セット */
	{
		/* 第二形態では使って無いから利用(共用)する */
		#define cg_BOSS_DATA_37_sakuya_data_sayuu_mode cg_BOSS_DATA_37_sakuya_data_common_wait256
		{	/* 咲夜さんの誘導ポイント座標 */
			cg_BOSS_DATA_37_sakuya_data_sayuu_mode ^= (2-1);/* 反転 */
			if (/*0==*/cg_BOSS_DATA_37_sakuya_data_sayuu_mode & (2-1))
					{cg_BOSS_DATA_30_target_x256 = SAKUYA_POINT_X_MID-(t256(128)); }//96==128*0.75
			else	{cg_BOSS_DATA_30_target_x256 = SAKUYA_POINT_X_MID+(t256(128)); }//
		}
		goto set_new_boss_position;/* 移動座標を決める */
	}
	//
	else
//	if (/*(256-256)*/(59)/*((251+64)-256)*/ == VR10_BOSS_SPELL_TIMER) /* 真中へワープ */
//	{
//		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = SAKUYA_POINT_X_MID; /* 真中へワープ */
//		goto set_new_boss_position;/* 移動座標を決める */
//	}
//	else
	if (/*(256-256)*/(58)/*((250+64)-256)*/ == VR10_BOSS_SPELL_TIMER) /* 反対側へワープ */
	{
	/*
		 反対側の座標==(左端のパネル部分)+(ゲーム領域画面)-(現在の座標-(左端のパネル部分));
		 反対側の座標==(左端のパネル部分)+(左端のパネル部分)+(ゲーム領域画面)-(現在の座標));
	*/
	//	cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256(GAME_X_OFFSET) + ( t256(GAME_320_WIDTH) - ( (cg_BOSS_DATA_3a_center_x256) - t256(GAME_X_OFFSET) ) );	/* 反対側へワープ */
	//	cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256((GAME_X_OFFSET+GAME_X_OFFSET+GAME_320_WIDTH)) - (cg_BOSS_DATA_3a_center_x256); 			/* 反対側へワープ */
		cg_BOSS_DATA_30_target_x256 = cg_BOSS_DATA_3a_center_x256 = t256((GAME_X_OFFSET+GAME_X_OFFSET+GAME_320_WIDTH)) - (SAKUYA_POINT_X_MID); 			/* 反対側へワープ */
		goto set_new_boss_position;/* 移動座標を決める */
	}
	goto nasi;
set_new_boss_position:
	#if (1)
	/* 移動座標を決める */	/* 攻撃アニメーション */
	boss_set_new_position_from_target();/*(誘導移動座標をターゲットから設定)*/
	#endif
nasi:
	;
}
//	if (/*(256-256)*/(0) == VR10_BOSS_SPELL_TIMER) /* 真中へワープ */
//	if (/*(256-192)*/(64) == VR10_BOSS_SPELL_TIMER) /* 真中へワープ */
//	if (/*(256-180)*/(76) == VR10_BOSS_SPELL_TIMER) /* 真中へワープ */
