
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	共通部分。
	-------------------------------------------------------
	(r32-)喰み出しチェックについて、
	「移動時に」喰み出しチェックをしない事が前提で設計されているカードが多い。
	この為「移動時に」システムで喰み出しチェックをしません。
	例えば画面端で跳ね返る弾は「移動時に」喰み出しチェックをしない事により実現している機能です。
	「移動と別で」全弾配列を調べて「喰み出しチェック」を行います。
---------------------------------------------------------*/

/*---------------------------------------------------------
	交差弾は色々弾によって違いが多すぎる。(個々の時間とか)
	全部システム側で吸収すると、遅くなる気がする。
	交差弾システム側で吸収するなら、角度弾と統合して角度弾無くすべき
	だけど(将来はともかく)現状では角度弾汎用にすると遅すぎる。
	-------------------------------------------------------
	現状の速度なら、交差弾は全弾配列書き換えで対応すべき。
	(パチェとか書き換えの嵐になりそうですが。)
	システム側交差弾対応は、無くなりそう。
---------------------------------------------------------*/

#if (1)
	/*(tama_system.cの特殊機能)*/
//	#define hatudan_system_kousadan_angle65536 tmp_angleCCW1024
	#define hatudan_system_kousadan_angle65536 tmp_angleCCW65536
#endif

/*---------------------------------------------------------
	#001 角度弾の移動を行う(通常弾用)
---------------------------------------------------------*/

static TAMA_FUNC(hatudan_system_tama_move_angle)/*(角度弾移動)*/
{
	#if 1/* 検討中(無くても出来るけど、あった方が簡単) */
	src_tama->TR01_hatudan_speed65536		+= (src_tama->TR02_hatudan_tra65536);		/* 加減速調整 */
	#endif
//
	#if (0)//r42(?)
	/*( 1[frame]あたりに進む距離。(半径) )*/int aaa 		 = (src_tama->TR01_hatudan_speed65536>>8);	/* 速度 */
//	src_tama->center.x256 += ((si n65536((src_tama->rotationCCW65536))*(aaa))>>8);/*fps_factor*/
//	src_tama->center.y256 += ((co s65536((src_tama->rotationCCW65536))*(aaa))>>8);/*fps_factor*/
	{
		int sin_value_t256; 	//	sin_value_t256 = 0;
		int cos_value_t256; 	//	cos_value_t256 = 0;
		int256_sin cos65536(src_tama->rotationCCW65536, &sin_value_t256, &cos_value_t256);
		src_tama->center.x256 += ((sin_value_t256*(aaa))>>8);/*fps_factor*/
		src_tama->center.y256 += ((cos_value_t256*(aaa))>>8);/*fps_factor*/
	}
	#else
		//------------------
		HATSUDAN_R11_speed256	= (src_tama->TR01_hatudan_speed65536>>8);
		HATSUDAN_R13_angle65536 = (src_tama->rotationCCW65536);
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		src_tama->center.x256 += VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		src_tama->center.y256 += VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
	#endif
}

static TAMA_FUNC(standard_angle_mover_00_callback)/*(角度弾移動+画面外弾消し)*/
{
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(画面外弾消し)*/
}
static TAMA_FUNC(danmaku_01_standard_angle_sayuu_hansya_mover)/*(角度弾移動+画面左右反射弾消し)*/
{
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
	hatudan_system_B_side_hansya(src_tama);/*(画面左右反射弾消し)*/
}

/*
	道中ザコ弾用。
	発弾後 16 [frame] は 3倍速。
	それ以降は通常弾へ変身して通常速になる。
*/
static TAMA_FUNC(danmaku_01_standard_angle_mover_douchu_start)/*(角度弾移動+画面外弾消し)*/
{
	/*(2倍速)*/ 	/*(3倍速)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
//	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
	//
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(画面外弾消し)*/
	/* 発弾後 16 [カウント]以上は通常弾へ変身する。 */
//	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-(16)) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[512]カウント以上経過した弾 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-32) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[512]カウント以上経過した弾 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+64-16) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[512]カウント以上経過した弾 */
	if ((HATUDAN_ITI_NO_JIKAN_EFFECT_NONE-16) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[512]カウント以上経過した弾 */
	{
		/* (通常弾へ変身する==画面内では弾は消えない) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
}


local TAMA_FUNC(move_vector_gamen_sita)
{
	// ベクトル弾移動。move vector.
	src_tama->center.x256 += (src_tama->math_vector.x256);	/*fps_factor*/
	src_tama->center.y256 += (src_tama->math_vector.y256);	/*fps_factor*/
//	src_tama->center.x256 += 1;// (t256( 0.1)); /*fps_factor*/
//	src_tama->center.y256 += 1;// (t256(-0.1)); /*fps_factor*/
//	src_tama->math_vector.y256 += ((src_tama->TR02_hatudan_tra65536)<<8);	/* 加減速調整 */
	src_tama->math_vector.y256 += ((src_tama->TR02_hatudan_tra65536)); /* 加減速調整 */
	// 消去判定
	#if 1
	// 画面外は消す。
//	hatudan_system_B_gamen_gai_tama_kesu(src);/*(通常弾用)*/
	/* 画面外の場合は弾を消す。 */
	if (
//	(0 < (VR1c_bullet_clip_min_x256)-(src_tama->center.x256) ) ||
//	(0 > (VR1e_bullet_clip_max_x256)-(src_tama->center.x256) ) ||
//	(0 < (VR1d_bullet_clip_min_y256)-(src_tama->center.y256) ) ||
//	(0 > (VR1f_bullet_clip_max_y256)-(src_tama->center.y256) ) )	/*(画面下のみ)*/
//	( (src_tama->center.y256) > (VR1f_bullet_clip_max_y256) ) ) /*(画面下のみ)*/
	( (src_tama->center.y256) > (t256(272)) ) ) 	/*(画面下のみ)*/
	{
		src_tama->jyumyou = JYUMYOU_NASI;
	}
	#endif
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	雨降り弾
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	[定数1]雨の速度
//	R0a 	[定数2]赤青クナイが曲がる角度(180/360ちょい回転)
	-------------------------------------------------------
	sincos計算用
	R0b 	angle_65536
	R0c 	sine   の値用。
	R0d 	cosine の値用。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	R06 	破壊
	R07 	破壊
---------------------------------------------------------*/
local TAMA_FUNC(common_01_amefuri_callback)
{
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト時は無効 */
	{
		return;
	}
	#endif
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) == src_tama->jyumyou)/* 発弾エフェクト後から64カウント経過した弾 */
	{
		//	ang le_to_vector(src_tama);
		//	local TAMA_FUNC(ang le_to_vector)
		/*(角度をX軸、Y軸のベクトル速度へ変換する)*/
		//------------------
		HATSUDAN_R11_speed256	= (VR09);
		HATSUDAN_R13_angle65536 = (src_tama->hatudan_system_kousadan_angle65536);
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		src_tama->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		src_tama->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
	}
	#endif
	move_vector_gamen_sita(src_tama);/*(ベクトル移動+画面下消去)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
	#if 0
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))	// 4カウントに1回上に8way弾を撃つ
	{
			HATSUDAN_R11_speed256				= (VR09);
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [青白米弾] */	/* 弾グラ */
	//		HATSUDAN_R16_n_way					= (8);
//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
		for (VR03_i=0; VR03_i<(8); VR03_i++)
		{
			/* ショット */
		//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			HATSUDAN_R13_angle65536 	= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
			HATSUDAN_R17_VECTOR_legacy_dan_delta256 = ((ra_nd()&0x03)+2);//t256(0.04)
			bullet_regist_legacy_vector_direct();
		}
	}
	#endif
local SPELL_EXEC(common_amefuri)
{
	if (0==(VR10_BOSS_SPELL_TIMER & 0x03))	// 4カウントに1回上に8way弾を撃つ
	{
			HATSUDAN_R11_speed256				= VR09;// [定数1]雨の速度
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);	/* 弾グラ */	/* [白米弾] */
		for (VR03_i=(0); VR03_i<(8); VR03_i++)/*(x位置)*/
		{
				#if 0
				/* ショット */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 				= (int)(65536/64);
				HATSUDAN_R17_VECTOR_legacy_dan_delta256 = ((ra_nd()&0x03)+2);//t256(0.04)
				bullet_regist_legacy_vector_direct();
				#else
				/* ショット */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			//	HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
				/*(とりあえず)*/HATSUDAN_R12_speed_offset			= ((ra_nd()&0x07)+1);//t256(0.04)
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
	//	//		int aaa_1024;
	//	//						aaa_1024			= (1024/4)+(1024/8)+(VR03_i<<5)+((VR10_BOSS_SPELL_TIMER>>2)&0x3f);
	//	//		HATSUDAN_R13_angle65536 			= ((aaa_1024)<<6);
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
	//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(VR03_i<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
				//
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);
				#endif
		}
	}
}


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
	とりあえず共通規格
---------------------------------------------------------*/

local OBJ_CALL_FUNC(boss_init_kaguya_start000);
static int kaguya_data_fire_wait3;
static int kaguya_data_bomb_aaa;

#define USE_KAGUYA_TORIAEZU_PATCH (1)
#if (1==USE_KAGUYA_TORIAEZU_PATCH)
// とりあえずパッチ
static int kaguya_data_tuika_tukaima;
local void kaguya_tuika_tukaima0123(void)
{
	kaguya_data_tuika_tukaima++;
	kaguya_data_tuika_tukaima &= 0x07;
}
#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)



local void select_T08(void)
{
		cg_BOSS_DATA_39_tukaima_type = TUKAIMA_08_kaguya_T08;
		set_tukaima_start();/*(使い魔システム)*/
}


local SPELL_INIT(kaguya000)
{
	boss_init_kaguya_start000(src_boss);
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		select_T08();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[定数1]雨の速度//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya111)
{
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		select_T08();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[定数1]雨の速度//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya222)
{
	//
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	if (0==kaguya_data_tuika_tukaima)
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	{
		#if 0
			 if (0==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_09_kaguya_T09;}
		else if (1==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0a_kaguya_sitakara_type04_hiroi;}
		else if (2==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0b_kaguya_sitakara_type05_hiroi;}
		else									{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0c_kaguya_sitakara_type06;}
		#endif
		#if 1
		static const u32 codebase111[3-1] =
		{
			// (01)	//	cg_BOSS_DATA_39_tukaima_type// ボス用。使用する使い魔のタイプ。
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R39_BOSS_DATA_tukaima_type, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((TUKAIMA_09_kaguya_T09), (TUKAIMA_0a_kaguya_sitakara_type04_hiroi), (TUKAIMA_0b_kaguya_sitakara_type05_hiroi), (TUKAIMA_0c_kaguya_sitakara_type06)),
		//	NAX
		};
		cpu_exec((u32*)&codebase111, (1));
		#endif
		//
		set_tukaima_start();
	}
	#if (1==USE_KAGUYA_TORIAEZU_PATCH)
	kaguya_tuika_tukaima0123();
	#endif // (1==USE_KAGUYA_TORIAEZU_PATCH)
	VR09	= (t256(1.0));//[定数1]雨の速度//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya333)
{
//	{
		#if 0
			 if (0==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_09_kaguya_T09;}
		else if (1==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0b_kaguya_sitakara_type05_hiroi;}
		else if (2==cg_VR20_game_difficulty)	{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0c_kaguya_sitakara_type06;}
		else									{cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0d_kaguya_uekara;}
		#endif
		#if 1
		static const u32 codebase222[3-1] =
		{
			// (01)	//	cg_BOSS_DATA_39_tukaima_type// ボス用。使用する使い魔のタイプ。
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R39_BOSS_DATA_tukaima_type, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((TUKAIMA_09_kaguya_T09), (TUKAIMA_0b_kaguya_sitakara_type05_hiroi), (TUKAIMA_0c_kaguya_sitakara_type06), (TUKAIMA_0d_kaguya_uekara)),
		//	NAX
		};
		cpu_exec((u32*)&codebase222, (1));
		#endif
		//
		set_tukaima_start();
//	}
	VR09	= (t256(1.0));//[定数1]雨の速度//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(kaguya444)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0d_kaguya_uekara;
	set_tukaima_start();
	VR09	= (t256(1.0));//[定数1]雨の速度//spell_init_mi ma_kaguya(src_boss);
}
local SPELL_INIT(2a_sakuya_baramaki1)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_04_sakuya_T04;
	set_tukaima_start();
}
local SPELL_INIT(2b_sakuya_baramaki2)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_05_sakuya_T05;
	set_tukaima_start();
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
//extern/*local*/ void set_com mon_gin_tama_void(void)
//{
//	/*(共通部分)*/
//}
											//R13 (src->shot_angle65536&(256*64-1))+512*64+128*64;// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
							 				//R13 (src->shot_angle65536&(256*64-1))+(65536/2)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
