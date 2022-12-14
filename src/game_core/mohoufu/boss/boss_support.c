
#include "boss.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ボスの移動。
	ボスのアクション後の処理。
	-------------------------------------------------------
	雑魚のアクション後の処理。
---------------------------------------------------------*/


/*---------------------------------------------------------
	ボス形態変更時の共通
---------------------------------------------------------*/

//extern OBJ *obj_effect[8]; /* [□]（カードのグラフィック） */
		#if 0/* あたった敵は倒せない敵かもしれないので、ここで必ず消すのはまずい気がする */
	/* あたった敵爆発 */
	bakuhatsu_add_type(src, BAKUHATSU_MINI00);
	cg.teki->jyumyou	= (0);/* (?)*/
	set_REG_DEST_XY(src);/* 発弾位置 座標xy */
	bakuhatsu_add_type_ccc(BAKUHATSU_FIRE08);
		#endif
/*---------------------------------------------------------
	敵移動(ザコ消滅爆発エフェクト)
---------------------------------------------------------*/
//	/* ザコ消滅爆発エフェクトを登録(現在Gu部分がないので描画してない) */

//	bakuhatsu_add_type_ccc(BAKUHATSU_ZAKO04/*BAKUHATSU_MINI00*/);/* ザコ消滅爆発 */

static OBJ_CALL_FUNC(move_zako_yarare)
{
	/* 描画用グラ回転 */
//	src->rotationCCW1024	= (src->jyumyou<<6);
	src->rotationCCW65536	= (src->jyumyou<<(6+6));
	/* グラ拡大 */
	src->m_zoom.x256		= (t256(4.0))-(src->jyumyou<<3);
	src->m_zoom.y256		= (t256(4.0))-(src->jyumyou<<3);
	/* 半透明 */
	src->color32 -= 0x08000000; /* 8==256/32 */
}
static OBJ_CALL_FUNC(init_zako_yarare)
{	// ザコ消滅爆発エフェクトを登録
	src->callback_mover 	= move_zako_yarare;
	src->callback_hit_teki	= NULL;
	src->jyumyou			= (32);/* 雑魚やられ時間。 */
	src->atari_hantei		= (ATARI_HANTEI_OFF);/*(ザコ消滅爆発エフェクトには当たり判定無し)*/
	static int bbb = 0;
	const u32 aaa[4] =
	{
		MAKE32RGBA(0xff, 0x00, 0x00, 0xff), // 赤
		MAKE32RGBA(0x00, 0xff, 0x00, 0xff), // 緑
		MAKE32RGBA(0x00, 0x00, 0xff, 0xff), // 青
		MAKE32RGBA(0xff, 0xff, 0x00, 0xff), // 黄
	};
	bbb++;
	bbb &= (4-1);
	src->color32			= aaa[bbb];
}


/*---------------------------------------------------------
	ザコを攻撃して、ザコに自弾があたった場合の共通ルーチン
	-------------------------------------------------------
	ザコは道中ザコ以外に、ボスが生成する使い魔も含む。
	-------------------------------------------------------
	OBJ *src;	ザコ敵自体
	OBJ *tama;	自弾
---------------------------------------------------------*/

/* 使い魔があるから global */
extern void callback_hit_zako(OBJ/**/ *src, OBJ/**/ *tama)
{
	/* 雑魚に自弾があたった場合の火花エフェクトを登録(現在Gu部分がないので描画してない) */
	set_REG_DEST_XY(tama);/* 発弾位置 座標xy */
	bakuhatsu_add_type_ccc(BAKUHATSU_MOVE12/*BAKUHATSU_MINI00*/);/* 先に実行した方が速い */
//
	/* 上と分離した方がコード効率があがる。 */
	{
		src->zako_hp -= tama->kougeki_ti;	/* 攻撃して体力減らす(強さ分引く) */
		if (0 >= src->zako_hp)			/* ０か負値なら、倒した。 */
		{
			/* (ザコの)カスタムやられ処理 */
			if (NULL != src->callback_loser)	/* カスタムやられ処理があれば実行。 */
			{
				(src->callback_loser)(src); 	/* カスタムやられ処理を実行する。(標準は「ランダムテーブルからアイテム生成」) */
				src->callback_loser = NULL; 	/* 実行したので(念の為)消す。 */
				/* (やられ処理は1度しか実行しない) */
			}
			/* ザコ、スコア加算処理 */
			bonus_info_any_score_nodel(src, ((src->base_score)*(cg.game_now_stage)) );
		//	/* 自動消去へ仕様変更 */src->jyumyou = JYUMYOU_NASI;/* スプライトシステムに再利用をお願いする。 */
			init_zako_yarare(src);	// ザコを消滅爆発エフェクトにする。
			voice_play_menu(VOICE08_DEATH, TRACK05_ZAKO_DEATH);/* 雑魚爆発音を鳴らす。 */
		}
	}
}

/*---------------------------------------------------------
	OBJ *src;	中-ボス敵自体
	OBJ *tama;	自弾
---------------------------------------------------------*/

extern void callback_hit_chuu_boss(OBJ/**/ *src, OBJ/**/ *tama)
{
	/* ボス & 中-ボスに自弾があたった場合の火花エフェクトを登録(現在Gu部分がないので描画してない) */
	set_REG_DEST_XY(tama);/* 発弾位置 座標xy */
	bakuhatsu_add_type_ccc(BAKUHATSU_MOVE12);/* 先に実行した方が速い */ /*BAKUHATSU_MINI00*/
//
	/* 上と分離した方がコード効率があがる。 */
	{
		src->boss_hp -= tama->kougeki_ti;	/* 攻撃して体力減らす(強さ分引く) */
		if (0 >= src->boss_hp)			/* ０か負値なら、倒した。 */
		{
			#if 1/*要るの？*/
			src->boss_hp	= (ZAKO_HP_TAOSENAI);/* ２回は倒せない */
			#endif
			card.spell_used_number		= (SPELL_00);/*(カード実行停止にする)*/
			bullets_to_hosi();/* 弾全部、星アイテムにする */
		//
			/* (ザコの)カスタムやられ処理 */
/*[スペカコールバック共用なので不可能]*/	if (NULL != src->callback_loser)	/* カスタムやられ処理があれば実行。 */
/*[スペカコールバック共用なので不可能]*/	{
/*[スペカコールバック共用なので不可能]*/		src->callback_loser(src);	/* カスタムやられ処理を実行する。(標準は「ランダムテーブルからアイテム生成」) */
/*[スペカコールバック共用なので不可能]*/		src->callback_loser = NULL; 	/* 実行したので(念の為)消す。 */
/*[スペカコールバック共用なので不可能]*/		/* (やられ処理は1度しか実行しない) */
/*[スペカコールバック共用なので不可能]*/	}
			player_dummy_add_score(src->base_score);
			//
			bakuhatsu_add_circle(src, 0);
			/* 倒した場合背後の魔方陣が消えているが、逃がした場合背後の魔方陣がある。 */
			src->YOKAI1_DATA_s2->jyumyou		= JYUMYOU_NASI; /* 倒した場合、背後の魔方陣を消す。 */
			src->jyumyou						= (CHUU_BOSS_JIKAN_02_0272-1);/*(時間切れの処理開始) [時間切れの位置]まで時間を進める。 */
			/* コールバック登録 */
			src->callback_hit_teki = NULL;	/* ダミーコールバック登録 */
		}
	}
}
/*---------------------------------------------------------
	[カードシステム内に移動予定]
	-------------------------------------------------------
	ボスを攻撃した場合の共通ルーチン
	-------------------------------------------------------
	OBJ *src;	ボス敵自体
	OBJ *tama;	自弾
---------------------------------------------------------*/

/*static*/extern/*extern*/	void callback_hit_boss(OBJ/**/ *src, OBJ *tama)
{
	/* ボス & 中-ボスに自弾があたった場合の火花エフェクトを登録(現在Gu部分がないので描画してない) */
	set_REG_DEST_XY(tama);/* 発弾位置 座標xy */
	bakuhatsu_add_type_ccc(BAKUHATSU_MOVE12/*BAKUHATSU_MINI00*/);/* 先に実行した方が速い */
	//
	/* 上と分離した方がコード効率があがる。 */
	{
		card.boss_hp_dec_by_frame += /*w->*/tama->kougeki_ti; /* 攻撃して体力減らす(強さ分引く) */
	}
}


/*---------------------------------------------------------

---------------------------------------------------------*/
static int ee_angle1024;
static int ff_angle1024;
/*static*/ OBJ_CALL_FUNC(move_card_square_effect)
{
	ee_angle1024 += (4);	/* 4 回転速度 */
	ff_angle1024 += (2);	/* 2 拡大縮小速度 */
	int ww_angle1024;	ww_angle1024 = ee_angle1024;
	int vv_angle1024;	vv_angle1024 = ff_angle1024;
	int radius;
//	int VR03_i;
	for (VR03_i=0; VR03_i<5; VR03_i++)
	{
		ww_angle1024 += 20; 	/* 20 回転速度 */
		vv_angle1024 += 200;	/* 40 拡大縮小速度 */
		{
			int sin_value_t256; 		//	sin_value_t256 = 0;
			int cos_value_t256; 		//	cos_value_t256 = 0;
			int256_sincos65536((deg1024to65536(vv_angle1024)), &sin_value_t256, &cos_value_t256);
			radius = ((sin_value_t256)>>2) + 16; /* 80==16+64 */
		}
		OBJ *h;
		h					= &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_08_EFFECT01+VR03_i];
		#if (0)//
		h->center.x256			= src->center.x256 + ((si n1024((ww_angle1024))*(radius)) );/*fps_factor*/	/* CCWの場合 */
		h->center.y256			= src->center.y256 + ((co s1024((ww_angle1024))*(radius)) );/*fps_factor*/
		#else
		{
			int sin_value_t256; 	//	sin_value_t256 = 0;
			int cos_value_t256; 	//	cos_value_t256 = 0;
			int256_sincos65536( deg1024to65536(ww_angle1024), &sin_value_t256, &cos_value_t256);
			h->center.x256			= src->center.x256 + ((sin_value_t256*(radius)) );/*fps_factor*/
			h->center.y256			= src->center.y256 + ((cos_value_t256*(radius)) );/*fps_factor*/
		}
		#endif
		h->m_zoom.x256		= ( (1/*+255*/+(radius<<2)) );
		h->m_zoom.y256		= ( (1/*+255*/+(radius<<2)) );
		#if 1
		/* 描画用角度(下が0度で左回り(反時計回り)) */
	//	h->rotationCCW1024	= -ww_angle1024;
		h->rotationCCW65536	= -((ww_angle1024)<<6);/*(r42とりあえず)*/
		#endif
	}
}

/*static*/ void boss_effect_kotei_obj_r36_taihi(void)
{
//	int VR03_i;
	for (VR03_i=0; VR03_i<5; VR03_i++)
	{
		OBJ *h;
		h = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_08_EFFECT01+VR03_i];
		sprite_kotei_obj_r36_taihi(h);/*(effect obj使用中であるが退避位置へ退避)*/
	}
}


/*---------------------------------------------------------
	ボス使い魔コントロール(共通)
---------------------------------------------------------*/
extern int check_boss_action(void);
extern OBJ_CALL_FUNC(boss_control_check_tukaima_kougeki_time_out)
{
	/*(攻撃処理があれば攻撃する。)*/
	if (NULL != src->callback_kougeki)
	{
		(src->callback_kougeki)(src);/*(攻撃処理)*/
	}
	//
	#if (1)
//	/* ボスを倒すと皆破壊される。 */
	/*(ボスがスペカを変えた場合、同期してボスオプションを消す)*/
//	if (CARD_BOSS_TIMER_0000_HATUDAN <= card.mo de_state)/*発弾時以外*/ /*(カード中以外)*/
//	if (boss_01_speka_kougeki != card.bo ss_select_action_callback)/*ボス、スペカで攻撃中。以外*/ /*(カード中以外)*/
	if (check_boss_action())/*ボス、スペカで攻撃中。以外*/ /*(カード中以外)*/
	{
		src->jyumyou		= JYUMYOU_NASI;/*(消去)*/
	}
	#endif
	/*---------------------------------------------------------
		使い魔、共通
		時間切れの場合の透明度設定
	---------------------------------------------------------*/
//	set_za ko_timeout_alpha(src);
//	extern OBJ_CALL_FUNC(set_za ko_timeout_alpha)
	if (0x1ff > (src->jyumyou))
	{
		src->color32		= (src->color32 & 0x00ffffff) | ((src->jyumyou<<(23))&0xff000000);
	}
}
