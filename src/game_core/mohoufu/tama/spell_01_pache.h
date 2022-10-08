
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	パチュリー・ノーレッジのカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	日曜日 [[ 基本弾系 ]]
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	赤弾
---------------------------------------------------------*/
local OBJ_CALL_FUNC(test_pache_16_shot_AKA)
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))
//	{
		CPU_CALL(calculate_jiki_nerai);
		//
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);		/* [赤丸弾] */
		HATSUDAN_R16_n_way					= (16); 										/* [16way] */	/* 発弾数 */
		HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* 分割角度(65536[360/360度]を 16 分割) */	/* 1周をn分割した角度 */
		//
		for (VR03_i=0; VR03_i<(4); VR03_i++)/* 4弾 */
		{
			HATSUDAN_R12_speed_offset		= (3+VR03_i)<<8;/*(テスト)*/
		//	HATSUDAN_R11_speed256			= (t256(1.00)+(VR03_i<<7)); 		/* 弾速(遅い弾が遅すぎる) */
			HATSUDAN_R11_speed256			= (t256(1.50)+(VR03_i<<6)); 		/* 弾速 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
//	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	青弾
---------------------------------------------------------*/
local OBJ_CALL_FUNC(test_pache_16_shot_AOI)
{
//	{
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);		/* [青丸弾] */
	//	HATSUDAN_R16_n_way					= (16); 										/* [16way] */	/* 発弾数 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* 分割角度(65536[360/360度]を 16 分割) */	/* 1周をn分割した角度 */
	//	HATSUDAN_R16_n_way					= (8);											/* [8way] */	/* 発弾数 */
	//	HATSUDAN_R17_div_angle65536 		= (int)(65536/(8)); /* 分割角度(65536[360/360度]を 8 分割) */	/* 1周をn分割した角度 */
		HATSUDAN_R16_n_way					= (10); 										/* [10way] */	/* 発弾数 */
		HATSUDAN_R17_div_angle65536 		= (int)(65536/(10)); /* 分割角度(65536[360/360度]を 10 分割) */ /* 1周をn分割した角度 */
		//
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/4))/* 45 */
		{
			HATSUDAN_R13_angle65536 = (lz[0].laser_angle65536+VR02_j);
			//------------------
			HATSUDAN_R11_speed256	= (VR09);
		//	HATSUDAN_R13_angle65536 = ((HATSUDAN_R13_angle65536));
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			//------------------
			//
			VR06	+= (cg_BOSS_DATA_3a_center_x256);
			VR07	+= (cg_BOSS_DATA_3b_center_y256);
			//
			CPU_CALL(calculate_jiki_nerai);
			//
			for (VR03_i=0; VR03_i<(4); VR03_i++)/* 4弾 */
			{
				HATSUDAN_R12_speed_offset	= (3+VR03_i)<<8;/*(テスト)*/
			//	HATSUDAN_R11_speed256		= (t256(1.00)+(VR03_i<<7)); 		/* 弾速(遅い弾が遅すぎる) */
				HATSUDAN_R11_speed256		= (t256(1.50)+(VR03_i<<6)); 		/* 弾速 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
		}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
//	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	魔方陣の位置から(赤丸弾)自機狙い弾(2回)
---------------------------------------------------------*/
extern OBJ_CALL_FUNC(add_zako_pache_laser);/* アリス人形カード */
local SPELL_EXEC(40_pache_laser1)
{
	static int laser_muki=0;
	static int laser_count=0;
	laser_count--;
	if (0 > laser_count)
	{
		laser_count = (150);
		laser_muki ^= 1;
		if (0==(laser_muki&1))
				{lz[0].laser_angle65536 = (0+(65536/6));	}	/* +1/8周(60/360度) */
		else	{lz[0].laser_angle65536 = (65536-(65536/6));}	/* -1/8周(60/360度) */
	}
	else
	if (100 < laser_count)
	{	;/*停止*/}
	else
	{	/* 移動 **/
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 -= (100);}
		else	{lz[0].laser_angle65536 += (100);}
	}
	//
	if ((65) > (VR10_BOSS_SPELL_TIMER & 0xff))/* 5回 3回 */
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		{
			test_pache_16_shot_AKA(src_boss);
		}
	}
	#if 0
	/*0x280*/if ((640-1) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		test_pache_16_shot_AKA(src_boss);
	}
	/*0x200*/if ((640-128) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	#endif
}

/*---------------------------------------------------------
	レーザー付けると難しくなりすぎそう。
	(原作のパチェレーザーも十分難しいけど)
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
//	R08 	?。
	R09 	[定数1]発弾位置までの距離。
//	R0a 	z
//	R0b 	難易度別定数。
---------------------------------------------------------*/
local SPELL_EXEC(41_pache_laser2)
{
	static int laser_muki=0;
	static int laser_count=0;
	laser_count--;
	if (0 > laser_count)
	{
		laser_count = (150);
		laser_muki ^= 1;
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 = (0+(65536/6));		}	/* +1/8周(60/360度) */
		else	{lz[0].laser_angle65536 = (65536-(65536/6));	}	/* -1/8周(60/360度) */
	}
	else
	if (100 < laser_count)
	{	;/*停止*/}
	else
	{
		;/* 移動 **/
		if (0 == (laser_muki & 1))
				{lz[0].laser_angle65536 -= (100);}
		else	{lz[0].laser_angle65536 += (100);}
	}
	//
//	if ((65)>(VR10_BOSS_SPELL_TIMER & 0xff))/* 9回 5回 3回 */
	if ((65)>(VR10_BOSS_SPELL_TIMER & 0xff))/* 9回 5回 3回 */
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
		{
			test_pache_16_shot_AOI(src_boss);
		}
	}
}
	#if 0
	/*0x280*/if ((640-1) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		test_pache_16_shot_AKA(src_boss);
	}
	/*0x200*/if ((640-128) == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_pache_laser(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	#endif

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
//レーザー
extern void add_laser_off_void(void);
extern void add_laser_on_void(void);

local SPELL_INIT(40_pache_laser1)
{
	add_laser_on_void();/*(特殊)*/
//	VR09	= (t256(64));//[定数1]発弾位置までの距離。
}
local SPELL_INIT(41_pache_laser2)
{
	add_laser_on_void();/*(特殊)*/
	VR09	= (t256(64));//[定数1]発弾位置までの距離。
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	月曜日 [[ 系 ]]
---------------------------------------------------------*/



// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	火曜日 [[ アグニシャイン系 ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"　　　　火符「アグニシャイン」" No.15
	-------------------------------------------------------
	アグニシャインの炎弾は雑魚にした方が現実的かも？。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	原作はサイクロイド曲線っぽい感じだけど、良くわかんない。
	-------------------------------------------------------
//	REG_XX_REGX 		個弾の向かう方向(角度、ベクトル方向)
//	REG_YY_REGY 		個弾の向かう量(ベクトル長さ)
---------------------------------------------------------*/

local TAMA_FUNC(agnishine_danmaku_01_callback)/*(アグニシャイン弾)*/
{
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* 発弾エフェクト後から[224]カウント未満の弾 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* 発弾エフェクト後から[225]カウント未満の弾 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-320) < src_tama->jyumyou)/* 発弾エフェクト後から[225]カウント未満の弾 */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(時計回り)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(-r39)*/
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(r40-)*/
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(r40-)*/
		}
		else
		{	/*CCW(反時計回り)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(-r39)*/
		//	src_tama->rotationCCW1024 += (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 += (src_tama->jyumyou&1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(r40-)*/
			src_tama->rotationCCW65536 += ((src_tama->jyumyou&1)<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /*(r40-)*/
		}
//		src_tama->TR01_hatudan_speed65536	+= (1<<8);		/* 弾速 */
	//	src_tama->TR01_hatudan_speed65536	+= (512);		/*(加速)*/	/* 弾速 */ /*(-r39)*/
	//	src_tama->TR01_hatudan_speed65536	+= (32);		/*(加速)*/	/* 弾速 */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	-= (cg_VR20_game_difficulty);	/* 弾速 */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	-= (3); 					/* 弾速 */ /*(r40-)*/
	//	src_tama->TR01_hatudan_speed65536	+= (32);		/*(加速)*/	/* 弾速 */ /*(r40-)*/
		src_tama->TR01_hatudan_speed65536	+= (30);		/*(加速)*/	/* 弾速 */ /*(r40-)*/

	//	サイクロイド曲線
		{
	//	//	/*(常に回転)*/src_tama->tmp_angleCCW1024 += (int)(3);/*(2.844444444444444==1024/360==360/360==1/360[度])*/
	//		/*(常に回転)*/src_tama->tmp_angleCCW1024 += (int)(4);/*(2.844444444444444==1024/360==360/360==1/360[度])*/
	//	//	/*(常に回転)*/src_tama->tmp_angleCCW1024 += (int)(5);/*(2.844444444444444==1024/360==360/360==1/360[度])*/
			//
		//	/*(常に回転)*/src_tama->tmp_angleCCW65536 += (int)(3<<6);/*(182.0444444444444==65536/360==360/360==1/360[度])*/
			/*(常に回転)*/src_tama->tmp_angleCCW65536 += (int)(4<<6);/*(182.0444444444444==65536/360==360/360==1/360[度])*/
		//	/*(常に回転)*/src_tama->tmp_angleCCW65536 += (int)(5<<6);/*(182.0444444444444==65536/360==360/360==1/360[度])*/
			//
		//	/*( 1[frame]あたりに進む距離。(半径) )*/int aaa 		 = (src_tama->TR01_hatudan_speed65536>>8);	/* 速度 */
		//	/*( 1[frame]あたりに進む距離。(半径) )*/int aaa 		 = (t256(1.00));	/* 速度 */
		//	/*( 1[frame]あたりに進む距離。(半径) )*/int aaa 		 = (t256(0.50));	/* 速度 */
			/*( 1[frame]あたりに進む距離。(半径) )*/int aaa 		 = (t256(0.33));	/* 速度 */
			#if (0)//
			src_tama->center.x256 += ((si n1024((src_tama->tmp_angleCCW1024))*(aaa))>>8);/*fps_factor*/
			src_tama->center.y256 += ((co s1024((src_tama->tmp_angleCCW1024))*(aaa))>>8);/*fps_factor*/
			#else
		//	{
		//		int sin_value_t256; 	//	sin_value_t256 = 0;
		//		int cos_value_t256; 	//	cos_value_t256 = 0;
		//		int256_sin cos65536(src_tama->tmp_angleCCW65536, &sin_value_t256, &cos_value_t256);
		//		src_tama->center.x256 += ((sin_value_t256*(aaa))>>8);/*fps_factor*/
		//		src_tama->center.y256 += ((cos_value_t256*(aaa))>>8);/*fps_factor*/
		//	}
			//------------------
			HATSUDAN_R11_speed256	= (aaa);
			HATSUDAN_R13_angle65536 = (src_tama->tmp_angleCCW65536);
		//	 (sincos256);/*(破壊レジスタ多いので注意)*/
			static const u32 codebase777[2/*-1*/] =
			{
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				NAX/*(終了)*/
			};
			cpu_exec((u32*)&codebase777, (1));
			src_tama->center.x256 += VR05;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			src_tama->center.y256 += VR04;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
			#endif
		}
	}
	else	/* 発弾後 225 カウント以上は弾を消す。 */
	{
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	現在(r35)のスペカシステムの場合、仕様上
	スペカがまたがるレジスタ値を保持できない。
	(スペカが始まるタイミングで強制的にレジスタが0クリアされてしまう為)
	-------------------------------------------------------
	-------------------------------------------------------
	使用レジスタ:
	R09 	[難易度別定数1]。
	R0c 	一時使用角度
	R0d 	難易度別定数3(分割数、13 or 11)
	R0e 	難易度別定数4(分割角、(65536/(13) or (65536/(11))
---------------------------------------------------------*/
local SPELL_EXEC(2e_pache_agni_shine_1)
{
	if ((VR09) > (VR10_BOSS_SPELL_TIMER & 0x3f) ) /* 64回にn回なら撃つ */ /*(r40-)*/
	{
	//	HATSUDAN_R11_speed256			= t256(1.0);	/* 弾速 */
	//	HATSUDAN_R12_speed_offset		= t256(5);/*(テスト)*/
	//	HATSUDAN_R11_speed256			= t256(0.75);	/* 弾速 */
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R11_speed256			= t256(0.25);	/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(0.75);/*(テスト)*/
	//	HATSUDAN_R13_angle65536 		= 0;	/* 基準角度 */ /*(-r39)*/
		HATSUDAN_R13_angle65536 		= VR0c; 	/* 基準角度 */ /*(r40-)*/
		VR0c							+= ((ra_nd()) & 0x0f); /*(r40-)*/
		VR0c							+= ((1)<<8); /*(r40-)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((ra_nd()) & TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [赤鱗弾] */
		HATSUDAN_R16_n_way				= VR0d;// (13) or (11); 	/* [13way] */		/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(13)) or (int)(65536/(11));	/* 分割角度(65536[360/360度]を 18 分割) */
		// 13分割。アグニシャイン。
		// 11分割。アグニシャイン上級。
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
---------------------------------------------------------*/
local SPELL_INIT(2e_pache_agni_shine_1)
{
	static const u32 codebase_init[5-1] =
	{	// (01)	VR09 = (0x05+((cg_VR20_game_difficulty)<<1));
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((5), (7), (9), (13)),//[定数1] 64回にn回なら撃つ。
	// (02)	R0d = (13); 					// 分割数(13)
	MCODE(OP0x1c_MOVEM_PD, (13), R0d, NAX),/*(ショートメモリアドレッシング)*/
	// (03)	R0e = 65536 / (R0d);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、(65536/(13)))*/	/* 分割角度 */
//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase_init, (3));
	//
}

/*---------------------------------------------------------
	"　　火符「アグニシャイン上級」" No.20
	-------------------------------------------------------
---------------------------------------------------------*/
#if (0)/*(とりあえず)*/
local SPELL_EXEC(33_pache_agni_shine_2)
{
}
#else
/*EXEC*/#define spell_execute_33_pache_agni_shine_2		spell_execute_2e_pache_agni_shine_1
local SPELL_INIT(33_pache_agni_shine_2)
{
	static const u32 codebase_init[5-1] =
	{	// (01)	VR09 = (0x05+((cg_VR20_game_difficulty)<<1));
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((5), (7), (9), (13)),//[定数1] 64回にn回なら撃つ。
	// (02)	R0d = (11); 					// 分割数(11)
	MCODE(OP0x1c_MOVEM_PD, (11), R0d, NAX),/*(ショートメモリアドレッシング)*/
	// (03)	R0e = 65536 / (R0d);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、(65536/(11)))*/	/* 分割角度 */
//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase_init, (3));
	//
}
#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"　火符「アグニレイディアンス」" No.23
	-------------------------------------------------------
	"　火符「アグニレイディアンス」" No.23 ==
	"　　火符「アグニシャイン上級」" No.20 +
	"赤大玉"
---------------------------------------------------------*/
/*(とりあえず)*/
local SPELL_EXEC(36_pache_agni_radiance)// _agni_shine_3
{
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2回に1回なら撃つ */
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );						/* 弾速 */
		HATSUDAN_R12_speed_offset		= (t256(4));/*(テスト)*/
		HATSUDAN_R13_angle65536 		= (ra_nd());
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= BULLET_OODAMA32_01_AKA;			/* [赤大玉弾] */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"超劣化アグニシャイン"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2回に1回なら撃つ */
	{
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [赤鱗弾] */
		HATSUDAN_R11_speed256			= (t256(1.0));		/* 弾速 */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	水曜日 [[ プリンセスウンディネ系 ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"　水符「プリンセスウンディネ」" No.16
	-------------------------------------------------------
	このカードの嫌な所は、中弾のあたり判定が(見た感じより)でかい事。
	(小弾のあたり判定は小さいのに)
	だから中弾は見た目より危険。
	なんだけど、現在の模倣風に中弾無いしなー。
	丸弾は(大玉弾、ミニ弾、小弾、枠小弾)しか無い。
	中弾はあたり判定も大きいし、とりあえず雑魚に変更しようかな？
	-------------------------------------------------------
	レーザー音、間隔0.5sぐらい(6回)計3.0s?(8回?)
	0.3sぐらい休み
	後追い弾、間隔0.3sぐらい(6回)計2.0s?
	2.0sぐらい休み
	----
	8.0s==60x8==480(?)
	6.0s==60x6==360(?)
	----
	という風に感じるのだが、実時間は1 loop 4.0sぐらいっぽい。
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	temp00_angle
---------------------------------------------------------*/

local SPELL_EXEC(2f_pache_princess_undine)
{
	if (64 > VR10_BOSS_SPELL_TIMER)
	{
		;
	}
	else
	if (128 > VR10_BOSS_SPELL_TIMER)
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & (16-1)))
		{
			/* 自機狙い 角を作成 */
			/* 弾源x256 y256 ボスの中心から発弾。 */
			CPU_CALL(calculate_boss_to_jiki_nerai);
		//	VR09 = HATSUDAN_R13_angle65536;
			/* 自機狙い 3way 白laser弾 */
		//	HATSUDAN_R13_angle65536 		= VR09;
		//	HATSUDAN_R11_speed256			= (t256(0.75)); 	/* 弾速 */
		//	HATSUDAN_R11_speed256			= (t256(1.50)); 	/* 弾速 */
			HATSUDAN_R11_speed256			= (t256(1.00)); 	/* 弾速 */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI);//			/* [青弾] */
			HATSUDAN_R16_n_way				= (11); 	/* [11way] */				/* 発弾数 */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/(24)); /* 分割角度(65536[360/360度]を 16 分割) */ /* 1周をn分割した角度 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
	else
	if (250 > VR10_BOSS_SPELL_TIMER)
	{
		if (0 == (VR10_BOSS_SPELL_TIMER & (2-1)))
		{
			/* 自機狙い 3way 白laser弾 */
			//
		//	HATSUDAN_R11_speed256			= (t256(0.75)); 	/* 弾速 */
		//	HATSUDAN_R11_speed256			= (t256(1.50)); 	/* 弾速 */
			HATSUDAN_R11_speed256			= (t256(4.00)); 	/* 弾速 */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_HARI32_00_AOI);// 				/* [青針弾] */
			/* 1レーザーの長さ */
			#define pache_02_LASER_LENGTH (4)
			VR03_i = 0;// for (VR03_i=0; VR03_i<(128*pache_02_LASER_LENGTH); VR03_i+=128)
			{
				HATSUDAN_R13_angle65536 	= VR09;
				HATSUDAN_R16_n_way				= (3);	/* [3way] */	/* 発弾数 */
				/* 全部のスキマ(隙間全体)、隙間が閉じる時のtime_outは128だから。 */
				#define pache_00_SUKIMA_ZENBU		((128/*time_out*/)<<4)/*(4096)*/
				/* プレイヤーがくぐるスキマ */
				#define pache_01_SUKIMA_KUGURU		(1280)
				HATSUDAN_R17_div_angle65536 	= VR03_i+((VR10_BOSS_SPELL_TIMER)<<4)-(pache_00_SUKIMA_ZENBU-pache_01_SUKIMA_KUGURU);
				// (int)(65536/(16));	/* 分割角度(65536[360/360度]を n 分割) */	/* 1周をn分割した角度 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
			}
			if (0 == (VR10_BOSS_SPELL_TIMER & (32-1)))
			{
				/* 自機狙わない 16way(?)17way(?) 青丸弾 */
				HATSUDAN_R11_speed256			= (t256(0.50)); 					/* 弾速 */
				HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
				HATSUDAN_R13_angle65536 		= VR09 + (65536/2);
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
				HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);// 			/* [青丸弾] */
				HATSUDAN_R16_n_way				= (17); 	/* [17way] */				/* 発弾数 */
				HATSUDAN_R17_div_angle65536 	= (int)(65536/(19));	/* 分割角度(65536[360/360度]を 19 分割) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
			}
		}
	}
	else
	if (254 == VR10_BOSS_SPELL_TIMER)
	{
		/* 自機狙い 角を作成 */
		/* 弾源x256 y256 ボスの中心から発弾。 */
		CPU_CALL(calculate_boss_to_jiki_nerai);
		VR09 = HATSUDAN_R13_angle65536;
	}
}

/*---------------------------------------------------------
	"　　　水符「ベリーインレイク」" No.24
	-------------------------------------------------------
	仕様:
		"　水符「プリンセスウンディネ」" No.16
		の上級版だがこちらの方が簡単。
	-------------------------------------------------------
	仕様:
		Lunatic は Hard に比べて動きが激しい。
---------------------------------------------------------*/
#if (0)/*(とりあえず)*/
local SPELL_EXEC(37_pache_bury_in_lake)
{
}
#else
	#define spell_execute_37_pache_bury_in_lake		spell_execute_2f_pache_princess_undine
#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	木曜日 [[ シルフィホルン系 ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"　　　　木符「シルフィホルン」" No.17
	-------------------------------------------------------
	木符「シルフィホルン」は弾の動きがもっと速い。
	（出始めが速いが遅くなり、後で再加速する）
	３～４個しか出てこないで、上じゃなくて横から出てくる気もする。
	-------------------------------------------------------
	「シルフィホルン」はさっぱり分からなかったが、
	横から出てくるただの交差弾らしい。
	-------------------------------------------------------
	使用レジスタ
	R08 	乱数?。
	R09 	[定数1]雨の速度
	R0a 	?。
	R0b 	?。
//
	R0c 	一時使用マスク。
//	R0d 	?。
//	R0e 	?。
//	R0f 	難易度。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。(0x0000)
	交差弾。時計回り。(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_sh1_danmaku_01_callback)/* シルフィホルン */
{
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト時は無効 */
	{
		return;
	}
	#endif
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			/*(模倣風では下CCWなので、正方向が反時計回り)*/
		//	{src_tama->rotationCCW1024 += (10);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
		//	{src_tama->rotationCCW65536 += (10<<6);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
			{src_tama->rotationCCW65536 += (1<<4);}/* --- 度 曲げる(--カウントかけて曲げる。---) */
		else
			/*(模倣風では下CCWなので、負方向が時計回り)*/
		//	{src_tama->rotationCCW1024 -= (10);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
		//	{src_tama->rotationCCW65536 -= (10<<6);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
			{src_tama->rotationCCW65536 -= (1<<4);}/* --- 度 曲げる(--カウントかけて曲げる。---) */
	//
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
---------------------------------------------------------*/
local SPELL_EXEC(30_pache_sylphy_horn_1)
{
//	sta tic int VR08;
	VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	/*"超劣化シルフィホルン"*/
//	if (0==(VR10_BOSS_SPELL_TIMER & 0x0f))
	if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
	{
		const u32 ra_nd32 = (ra_nd()/*&0xffff*/);
//		VR0b = replay_rand32 & 0xff;
		VR08 += ra_nd32;
		// 512-480 =32
		VR06	= t256(16)+((ra_nd32 & 0xffff)<<1); 	/* 16[pixel]+(480[pixel])+16[pixel] == 512[pixel] 弾源x256 */
//		VR06	= t256(16)+(ra_nd32 & 0xff00)+(ra_nd32 & 0x3f00);	/* 弾源x256 */
//		VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 				/* 弾源y256 */
//		VR06	= ((replay_rand32) & (0x0001ffff) );/*(512-1==0x01ff)*/
		VR07	= (t256(-8));/*(画面外から降る)*/
	//	VR07	= (t256(32));/*(画面外から降る)*/
//
//		HATSUDAN_R11_speed256			= t256(1.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(12.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(33.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(128.0);		/* 弾速 */
		HATSUDAN_R11_speed256/*特殊(無視？)*/	= t256(1.0);		/* 弾速(###x256倍) */
//		HATSUDAN_R12_speed_offset		= t256(3.0);/*(テスト)*/
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= (1);/*(テスト)*/
//		HATSUDAN_R13_angle65536 		= (VR0a);
//		HATSUDAN_R13_angle65536 		= (65536)-(65536/8);//+(VR0b);
		HATSUDAN_R13_angle65536 		= (65536)-(65536/16)-(ra_nd32 & 0x0fff);//+(VR0b);
//		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_05_MIDORI);			/* [緑米弾] */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

/*---------------------------------------------------------
	"　　木符「シルフィホルン上級」" No.21
	-------------------------------------------------------
---------------------------------------------------------*/
#if (0)/*(とりあえず)*/
local SPELL_EXEC(34_pache_sylphy_horn_2)
{
}
#else
	#define spell_execute_34_pache_sylphy_horn_2 	spell_execute_30_pache_sylphy_horn_1
#endif

/*---------------------------------------------------------
	"　　　木符「グリーンストーム」" No.25
	-------------------------------------------------------
	シルフィホルン上級の上級版。
---------------------------------------------------------*/
#if (0)/*(とりあえず)*/
local SPELL_EXEC(38_pache_green_storm)//_sylphy_horn_3
{
}
#else
	#define spell_execute_38_pache_green_storm		spell_execute_30_pache_sylphy_horn_1
#endif

/*---------------------------------------------------------
	"木＆火符「フォレストブレイズ」" No.29
	-------------------------------------------------------
	休曜日 [[ 複合系 ]]
---------------------------------------------------------*/
/*(未作成)*/
local SPELL_EXEC(3c_pache_forest_blaze)
{
	#if (1)
//	sta tic int VR08;
	VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	/*"超劣化シルフィホルン"*/
//	if (0==(VR10_BOSS_SPELL_TIMER & 0x0f))
	if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
	{
		const u32 ra_nd32 = (ra_nd()/*&0xffff*/);
//		VR0b = replay_rand32 & 0xff;
		VR08 += ra_nd32;
		// 512-480 =32
		VR06	= t256(16)+((ra_nd32 & 0xffff)<<1); 	/* 16[pixel]+(480[pixel])+16[pixel] == 512[pixel] 弾源x256 */
//		VR06	= t256(16)+(ra_nd32 & 0xff00)+(ra_nd32 & 0x3f00);	/* 弾源x256 */
//		VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 				/* 弾源y256 */
//		VR06	= ((replay_rand32) & (0x0001ffff) );/*(512-1==0x01ff)*/
		VR07	= (t256(-8));/*(画面外から降る)*/
	//	VR07	= (t256(32));/*(画面外から降る)*/
//
//		HATSUDAN_R11_speed256			= t256(1.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(12.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(33.0);		/* 弾速 */
//		HATSUDAN_R11_speed256			= t256(128.0);		/* 弾速 */
		HATSUDAN_R11_speed256/*特殊(無視？)*/	= t256(1.0);		/* 弾速(###x256倍) */
//		HATSUDAN_R12_speed_offset		= t256(3.0);/*(テスト)*/
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= (1);/*(テスト)*/
//		HATSUDAN_R13_angle65536 		= (VR0a);
//		HATSUDAN_R13_angle65536 		= (65536)-(65536/8);//+(VR0b);
		HATSUDAN_R13_angle65536 		= (65536)-(65536/16)-(ra_nd32 & 0x0fff);//+(VR0b);
//		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA);			/* [赤米弾] */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
//	spell_execute_30_pache_sylphy_horn_1(src_boss);
	#endif
	#if (1)
	/*"超劣化アグニシャイン"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2回に1回なら撃つ */
	{
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [赤鱗弾] */
		HATSUDAN_R11_speed256			= (t256(1.0));		/* 弾速 */
		VR0a = ra_nd();
		VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	#endif
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(30_pache_sylphy_horn_000)
{
	static const u32 codebase_init[6] =
	{	// 横から出てくるので弾幕有効範囲を変更する。
	// (01)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// 右の範囲を設定する。
	CLIP_RECT_00_VR1c-(1024<<8),// シルフィホルン
	// (02)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上の範囲を設定する。
	CLIP_RECT_00_VR1d-(32<<8),// シルフィホルン
	// (03)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// 左の範囲を設定する。
	CLIP_RECT_00_VR1e+(1024<<8),// シルフィホルン
	};
	cpu_exec((u32*)&codebase_init, (3));
}
//	VR09	= (t256(1.0));// [定数1]雨の速度

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	金曜日 [[ メタル系 ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"　　金符「メタルファティーグ」" No.19
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。(0x0000)
	交差弾。時計回り。(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mt1_danmaku_01_callback)/* シルバードラゴン */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* 発弾エフェクト後から[64]カウント未満の弾 */
	{
	//	src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	-= (t256(0.03)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト後から[64]...[128]カウント未満の弾 */
	{
		/*(親は消える)*/
		src_tama->jyumyou = JYUMYOU_NASI;/*(弾を消す)*/
		//
		set_REG_DEST_XY(src_tama);			/* 弾源x256 y256 弾obj中心から発弾。 */ 	/*(親弾の位置から発弾)*/
		//
		HATSUDAN_R11_speed256			= t256(0.75);		/* 1.00 弾速 */
	//	HATSUDAN_R12_speed_offset		= (1<<(2+8));/* x4倍 てすと*/
		HATSUDAN_R12_speed_offset		= t256(3+1);/*(テスト)*/
		HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);	/* [黄色 大玉弾] */
		HATSUDAN_R16_n_way				= (8);							/* [8way] */		/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 	/* 分割角度(65536[360/360度]を 8 分割) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。(100回に1回発弾する)
//	R09 	カウンタ。(2種類)
//	R0a 	弾色(交差弾)。
//	R0b 	弾角度(交差弾)。	弾角度(連弾)。
---------------------------------------------------------*/

local SPELL_EXEC(32_pache_metal_fatigue)
{
	static const u32 codebase_exec[17] =
	{
	// (01)
	MCODE(OP0x02_COUNTER, 100, R08, NAX),	/* (100回に1回) */ /*(一番始め)*/
	// (02) if (0 != VR08) {goto 発弾しない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+14)),// 	(osimai+14)
	/*-----------------------*/
	// (03) HATSUDAN_R11_speed256			= t256(2.50);		/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(2.50)),
//	HATSUDAN_R12_speed_offset		= (0<<(2+8));/* x4倍 てすと*/
	// (04) HATSUDAN_R12_speed_offset		= t256(3+0);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3+0)),
	// (05) HATSUDAN_R13_angle65536 		= だいたい(0);/*(真下)*/
	MCODE(OP0x1c_MOVEM_PD, (1), R13, NAX),/*(ショートメモリアドレッシング)*/
	// (06) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT)),
	// (07) HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);	/* [黄色 大玉弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_OODAMA32_02_KIIRO),
	// (08) HATSUDAN_R16_n_way			= (8);	/* [8] */					/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (09) HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); /* 分割角度(65536[360/360度]を 8 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(8)),
	// (10)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	/*-----------------------*/
	// (11)  (cpu_auto_bullet_play_default);
// oto:
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// osimai+14:
	// (12)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (11));
}

/*---------------------------------------------------------
	"　　　金符「シルバードラゴン」" No.27
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。(0x0000)
	交差弾。時計回り。(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mt2_danmaku_01_callback)/* シルバードラゴン */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* 発弾エフェクト後から[64]カウント未満の弾 */
	{
	//	src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	-= (t256(0.05)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト後から[64]...[128]カウント未満の弾 */
	{
		if (0==(ra_nd()&1))
		{
		//	src_tama->rotationCCW1024 -= (13);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 -= (13<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (777);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 += (777<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* 弾速 */
	}
	else
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-128) < src_tama->jyumyou)/* 発弾エフェクト後から[64]...[128]カウント未満の弾 */
	{
	//	src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* 弾速 */
	}
	else	/* 発弾後 256 カウント以上は弾を消す。 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[256]カウント以上経過した弾 */
	{
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。(kankaku)
//	R09 	カウンタ。(2種類)
//	R0a 	弾色(交差弾)。
//	R0b 	弾角度(交差弾)。	弾角度(連弾)。
---------------------------------------------------------*/

local SPELL_EXEC(3a_pache_silver_dragon)
{
	if (30==VR10_BOSS_SPELL_TIMER)
	{
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);			/* 白弾 */	/* [中丸白色弾は無いので] */
		HATSUDAN_R16_n_way				= (8);							/* [8way] */		/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 	/* 分割角度(65536[360/360度]を 8 分割) */
		for (VR03_i=0; VR03_i<(5); VR03_i++)/* 5層 */
		{
		//	HATSUDAN_R12_speed_offset		= (VR03_i<<(2+8));/* x4倍 てすと*/
			HATSUDAN_R12_speed_offset		= (3+VR03_i)<<8;/*(テスト)*/
			HATSUDAN_R11_speed256			= (t256(1.00)+(VR03_i<<7)); 		/* 弾速 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		}
		//
		CPU_CALL(cpu_auto_bullet_play_default);
	}
}


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	土曜日 [[ トリリトン系 ]]
---------------------------------------------------------*/

/*---------------------------------------------------------
	"　　土符「レイジィトリリトン」" No.18
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。(0x0000)
	交差弾。時計回り。(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_rt1_danmaku_01_callback)/* レイジィトリリトン */ /*(マーキュリポイズン)*/
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-192) < src_tama->jyumyou)/* 発弾エフェクト後から[192 == 64 x 3]カウント未満の弾 */
	{
		VR09 = ((src_tama->jyumyou) & 0x3f);/* 64で割った余り */
		if (0==VR09)/* 0なら左右にぶれる。 */
		{
		//	src_tama->rotationCCW1024 += ((ra_nd()&0xff)-128);/* 90/360 度(+-45/360) 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 += (((ra_nd()&0xff)-128)<<6);/* 90/360 度(+-45/360) 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->TR01_hatudan_speed65536 = (t256(1.00)<<8);	/* 弾速 */
		}
		else
		{
			src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* 弾速 */
			src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
		}
	}
	else
	/*(ある程度[192 == 64 x 3]時間経過したら通常弾に変身する)*/
	{
		/* (通常弾へ変身する) */
		src_tama->TR01_hatudan_speed65536 = (t256(1.00)<<8);	/* 弾速 */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
}
//	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
	// 画面外は消す。
//	hatudan_system_B_gamen_gai_tama_kesu(src_tama);/*(通常弾用)*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
---------------------------------------------------------*/
local SPELL_EXEC(31_pache_rage_tririton_1)
{
	// 最初の発射 (64フレーム==約1秒)ばら撒く。
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
	//	VR04_NAN_IDO_DECODE 	= PACK_NAN_IDO_CONST((1), (3), (5), (7));/*tama_const_H06_NUMS_ALICE_RED*/	/* 分割数:(r35-) */ 	/* 註:3より4の方が簡単 */
	//	 (nan_ido);
	//	if ((VR10_BOSS_SPELL_TIMER & 3) <= (cg_VR20_game_difficulty))
	//	if ((VR10_BOSS_SPELL_TIMER & 7) <= (VR04_NAN_IDO_DECODE))
		if ((VR10_BOSS_SPELL_TIMER & 7) <= (cg_VR20_game_difficulty+cg_VR20_game_difficulty+1))
		{
			HATSUDAN_R11_speed256			= (t256(2.00) );						/* 弾速 */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
			HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [黄弾] */
		//	HATSUDAN_R16_n_way				= (1);	/* [1way] */				/* 発弾数 */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* 分割角度(65536[360/360度]を 19 分割) */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}

/*---------------------------------------------------------
	"土符「レイジィトリリトン上級」" No.22
	-------------------------------------------------------
	てすと
---------------------------------------------------------*/

/*(とりあえず)*/
local SPELL_EXEC(35_pache_rage_tririton_2)
{
	// 最初の発射 (64フレーム==約1秒)ばら撒く。
//	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		if ((VR10_BOSS_SPELL_TIMER & 7) <= (cg_VR20_game_difficulty+cg_VR20_game_difficulty+1))
		{
			HATSUDAN_R11_speed256			= (t256(2.00)); 		/* 弾速 */
			HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
			HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [黄弾] */
		//	HATSUDAN_R16_n_way				= (1);	/* [1way] */	/* 発弾数 */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* 分割角度(65536[360/360度]を 19 分割) */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}

/*---------------------------------------------------------
	"　　土符「トリリトンシェイク」" No.26
	-------------------------------------------------------
	"　　土符「トリリトンシェイク」" No.26 ==
	"土符「レイジィトリリトン上級」" No.22 +
	"七方向大玉弾。自機狙い。"
---------------------------------------------------------*/

local SPELL_EXEC(39_pache_tririton_shake)
{
	/*	繰り返しカウンタ。 */
	// 最初の発射 (64フレーム==約1秒)ばら撒く。
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );						/* 弾速 */
		HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
		HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [黄弾] */
	//	HATSUDAN_R16_n_way				= (1);	/* [1way] */				/* 発弾数 */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* 分割角度(65536[360/360度]を 19 分割) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"七方向大玉弾。自機狙い。"*/
	if (0== (VR10_BOSS_SPELL_TIMER & 0xf) ) /* 16回に1回なら撃つ */
	{
		#if 1
		CPU_CALL(calculate_jiki_nerai);/* 自機狙い角作成 */
	//	VR0a = HATSUDAN_R13_angle65536;/* 自機狙い角 */
		#endif
		HATSUDAN_R11_speed256			= (t256(2.0));		/* 弾速 */
	//	HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= t256(5);/*(テスト)*/
	//	HATSUDAN_R13_angle65536 		= (VR0a);/* 自機狙い角 */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_02_KIIRO);		/* [黄色 大玉弾] */
		HATSUDAN_R16_n_way				= (7);	/* [7way] */				/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(7)); /* 分割角度(65536[360/360度]を 7 分割) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	"火＆土符「ラーヴァクロムレク」" No.28
	-------------------------------------------------------
	"火＆土符「ラーヴァクロムレク」" No.28 ==
	"　　土符「レイジィトリリトン」" No.18 +
	"　　　　火符「アグニシャイン」" No.15
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。
	R0a 	乱数値
---------------------------------------------------------*/

local SPELL_EXEC(3b_pache_lava_cromlech)
{
	static const u32 codebase_exec111[2] =
	{
	//	MCODE(OP0x02_COUNTER, 192, R08, NAX),/* 繰り返しカウンタ。 */
		MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase_exec111, (1));
	// 最初の発射 (64フレーム==約1秒)ばら撒く。
	if (((64)) < VR10_BOSS_SPELL_TIMER) // 192== (64*3)
	{
		HATSUDAN_R11_speed256			= (t256(2.00) );					/* 弾速 */
		HATSUDAN_R12_speed_offset		= (t256(3));/*(テスト)*/
		HATSUDAN_R13_angle65536 		= (VR0a & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
	//	HATSUDAN_R13_angle65536 		= (ra_nd() & (0x7fff)) + (65536/4)+(65536/2);/*(下半分)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_06_KI_IRO);//			/* [黄弾] */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
	/*"超劣化アグニシャイン"*/
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01) ) /* 2回に1回なら撃つ */
	{
		HATSUDAN_R11_speed256			= (t256(1.0));		/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);			/* [赤鱗弾] */
	//	VR0a = ra _nd();
// (?)	VR0b = VR0a & 0xff;
		//
		HATSUDAN_R13_angle65536 		= (VR0a);
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"　水＆木符「ウォーターエルフ」" No.30
	-------------------------------------------------------
	正直よくわからん。
	パチェっぽい？。
	-------------------------------------------------------
	うーん。難しくなってる。
	-------------------------------------------------------
	1.5 秒ぐらいの周期なので１周期 100 カウントぐらい?
	とりあえず １周期 100 カウント とする。
	-------------------------------------------------------
	全弾減速弾っぽい。
	-------------------------------------------------------
	１周期に２回音がする。音がする時に発弾するとして。
	0 カウント目と 33 カウント目ということにしよう。
	-------------------------------------------------------
スケジュール
	 0: 95 水符 自機狙い 24方向全方位、水色弾 kougeki1:
	10: 85 水符 自機狙い 24方向全方位、水色弾 kougeki1:
	20: 75 木符 自機狙い 10方向半周、青中玉弾 kougeki2:
	30: 65 木符 自機狙い 10方向半周、青中玉弾 kougeki2:
	40: 55 木符 自機狙い 20方向全方位、緑色弾 kougeki3:
	50: 45 木符 自機狙い 20方向全方位、緑色弾 kougeki3:
	60: 35 発弾音
	70: 25 休み
	80: 15 休み
	90: 10 発弾音
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。(10数える)
	R09 	カウンタ。(状態 1 - 11)
	R0e 	自機狙い角度保存用。
	-------------------------------------------------------
	とりあえず
	R0b 	難易度別定数。
---------------------------------------------------------*/
local SPELL_EXEC(3d_pache_water_elf)
{
	/* 水符 自機狙い 24方向全方位、水色弾 BULLET_MARU10_04_MIZU_IRO */
	/* 木符 自機狙い 20方向全方位、緑色弾 BULLET_MARU10_05_MIDORI */
	/* 木符 自機狙い 10方向半周、青中玉弾 BULLET_OODAMA32_00_AOI */
	//	if (0 == (VR10_BOSS_SPELL_TIMER & (16-1)))
	static const u32 codebase_exec[64] =
	{
	// (1) //とりあえず	MCODE(OP0x02_COUNTER, 10, R08, NAX),	/* (10回に1回) */
//	MCODE(OP0x02_COUNTER, 3, R08, NAX), /* (10回に1回) */
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[レジスタ間接アドレッシング]*/, R08, R0b/*[難易度別定数]*/),
	// (2) if (0 != VR08) {goto 発弾しない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+16)),// 	(ccc+1)
	/*-----------------------*/
	/* 自機狙い 角を作成 */
	/* 弾源x256 y256 ボスの中心から発弾。 */
	// (3)	 (calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
	MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	// (4)	VR0e = (HATSUDAN_R13_angle65536);/* 自機狙い角 */ /* hatudan_system_regist_katayori_n_way()は角度破壊するので、まず保存。 */
	MCODE(OP0x01_MOVER_PD, NAX, R0e, R13),
	/*-----------------------*/
	// (5) R09++;
//	MCODE(OP0x01_MOVER_PD, ((u8)(+1)), R09, R09), /*(インデックス付)*/
	MCODE(OP0x02_COUNTER, 11, R09, NAX),	/* (11状態) */
	/*-----------------------*/
	// (6) VR0d = hairetu[VR09];goto (bbb+13);
	MCODE(OP0x0a_BRA_TABLE, R09, R0d, (+13)),
	//	const u32 cc_type[4] =
	(+42),// 00回目 発弾音
	(+ 0),// 01回目 水符 自機狙い 24方向全方位、水色弾 kougeki1:
	(+ 0),// 02回目 水符 自機狙い 24方向全方位、水色弾 kougeki1:
	(+14),// 03回目 木符 自機狙い 10方向半周、青中玉弾 kougeki2:
	(+14),// 04回目 木符 自機狙い 10方向半周、青中玉弾 kougeki2:
	(+28),// 05回目 木符 自機狙い 20方向全方位、緑色弾 kougeki3:
	(+28),// 06回目 木符 自機狙い 20方向全方位、緑色弾 kougeki3:
	(+42),// 07回目 発弾音 oto:
	(+43),// 08回目 休み
	(+43),// 09回目 休み
	(+42),// 10回目 発弾音(こない?)
	(+43),// 11回目 (こない?)
	// (7) めんどくさいから、とりあえず終了。[デバッグ用]
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	// (8)
	MCODE(OP0x06_BRAR_NN, NAX, NAX, R0d),	// 策定案3. VRB の相対アドレスにジャンプ。
	// (9)
	/*-----------------------*/
		//	HATSUDAN_R11_speed256				= (t256(0.75) );		/* 弾速 */
		//	HATSUDAN_R11_speed256				= (t256(1.50) );		/* 弾速 */
	//		HATSUDAN_R11_speed256				= (t256(1.00) );		/* 弾速 */
	/*-----------------------*/
	//kougeki1: /* 水符 自機狙い 24方向全方位、水色弾 BULLET_MARU10_04_MIZU_IRO */
	// (9) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (10) HATSUDAN_R12_speed_offset	= t256(1);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (11) HATSUDAN_R13_angle65536 			= VR0e;/*[自機狙い角度、復旧]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (12) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
	// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_04_MIZU_IRO);//				/* [水色弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_MARU10_BASE + TAMA_IRO_04_MIZU_IRO),
	// (14) HATSUDAN_R16_n_way			= (24); 	/* [24way] */					/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (24), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (15) HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* 分割角度(65536[360/360度]を 24 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(24)),
	// (16)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (17) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+29)),
	/*-----------------------*/
	//kougeki2: /* 木符 自機狙い 10方向半周、青中玉弾 BULLET_OODAMA32_00_AOI */
	// (18) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (19) HATSUDAN_R12_speed_offset	= t256(3);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3)),
	// (20) HATSUDAN_R13_angle65536 			= VR0e;/*[自機狙い角度、復旧]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (21) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
	// (22) HATSUDAN_R15_bullet_obj_type		= (BULLET_OODAMA32_00_AOI);//				/* [青弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_OODAMA32_00_AOI),
	// (23) HATSUDAN_R16_n_way			= (10); 	/* [10way] */					/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (10), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (24) HATSUDAN_R17_div_angle65536 	= (int)(65536/(20));	/* 分割角度(65536[360/360度]を 20 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(20)),
	// (25)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	// (26) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+15)),
	/*-----------------------*/
	//kougeki3: /* 木符 自機狙い 20方向全方位、緑色弾 BULLET_MARU10_05_MIDORI */
	// (27) HATSUDAN_R11_speed256				= (t256(1.00)); 	/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (28) HATSUDAN_R12_speed_offset	= t256(1);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (29) HATSUDAN_R13_angle65536 			= VR0e;/*[自機狙い角度、復旧]*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (30) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
	// (31) HATSUDAN_R15_bullet_obj_type		= (BULLET_MARU10_BASE + TAMA_IRO_05_MIDORI);//				/* [緑弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
	(BULLET_MARU10_BASE + TAMA_IRO_05_MIDORI),
	// (32) HATSUDAN_R16_n_way			= (20); 	/* [20way] */					/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (20), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (33) HATSUDAN_R17_div_angle65536 	= (int)(65536/(20));	/* 分割角度(65536[360/360度]を 20 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(20)),
	// (34)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (35) goto osimai;
	MCODE(OP0x0b_BRA_RS, NAX, NAX, (+1)),
	/*-----------------------*/
	// (36)  (cpu_auto_bullet_play_default);
// oto:
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// osimai:
	// (37)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (100));// テキトー
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(3d_pache_water_elf)
{
	static const u32 codebase_init[2] =
	{
	// (1)	//	VR0b = ([難易度別定数]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((10), ( 8), ( 5), ( 3)),
	};
	cpu_exec((u32*)&codebase_init, (1));
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"金＆水符「マーキュリポイズン」" No.31
	-------------------------------------------------------
	あんま似てないけど、少しだけパチェっぽい。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。(0x0000)
	交差弾。時計回り。(0x0100)
---------------------------------------------------------*/
local TAMA_FUNC(pache_mp1_danmaku_01_callback)/* マーキュリポイズン */
{
//	if (cnt < 80)/* 80未満は減速 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト後から[64]カウント未満の弾 */
	{
		src_tama->TR01_hatudan_speed65536	-= (t256(0.02)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	= psp_max( (0), (src_tama->TR01_hatudan_speed65536) );
	}
	else
//	if (cnt == 80)/* 80なら左右にぶれる。 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-80) == src_tama->jyumyou)/* 発弾エフェクト後から[80]カウント未満の弾 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-96) < src_tama->jyumyou)/* 発弾エフェクト後から[64]...[96]カウント未満の弾 */
	{
		#if 0
		s32 ang = bullet_get_angle(eb);
		int add_angle;
		add_angle = ((A_ROUND65536)/4 + deg360to_rad(replay_rand()%10));
		bullet_set_angle(eb, ang - add_angle );
		bullet_set_angle(eb, ang + add_angle );
		#else
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 += (1<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		#endif
		src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* 弾速 */
	}
	else	/* 81から 100未満は加速 */
//	if (cnt < 200)/* 81から 200未満は加速(但し100で弾強制消去) */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) < src_tama->jyumyou)/* 発弾エフェクト後から[96]...[256]カウント未満の弾 */
	{
		if (0==(ra_nd()&1))
		{
			goto test_aaa;
		}
	//	bullet_set_speed(eb, (spd256+t256(0.015) ) );/*(加速)*/
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
		//	src_tama->rotationCCW1024 -= (1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 -= (1<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		else
		{
		//	src_tama->rotationCCW1024 += (1);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 += (1<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
	//	src_tama->TR01_hatudan_speed65536	+= (t256(0.01)<<8); 		/* 弾速 */
		src_tama->TR01_hatudan_speed65536	-= (512);		/* 減速 */
	test_aaa:
		;
	}
	else	/* 発弾後 256 カウント以上は弾を消す。 */
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[256]カウント以上経過した弾 */
	{
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。(kankaku)
	R09 	カウンタ。(2種類)
	R0a 	一時使用
//	R0b 	弾角度(交差弾)。	弾角度(連弾)。
	R0d		([難易度別定数]n way);
	R0e		([難易度別定数]div angle);
---------------------------------------------------------*/
#define MERCURY_POISON_KANKAKU_030 (30)
#define MERCURY_POISON_KANKAKU_015 (15)

	#if 0
	if (0==cg_VR20_game_difficulty) 	{;}
//	if (1==cg_VR20_game_difficulty)
	else
	{
		if (enemy.hp < (enemy.maxHp*2/3))	{VR08 = (MERCURY_POISON_KANKAKU_015);}
	}
//	bullet_set_till_time(100);/*(強制的に消える時間)*/
	#endif

local SPELL_EXEC(3e_pache_mercury_poison)
{
	static const u32 codebase_exec[27] =
	{
	//----	VR08--;if (0 > VR08)	{VR08 = MERCURY_POISON_KANKAKU_030;}
	// (01)	counter(MERCURY_POISON_KANKAKU_030, VR08);
	MCODE(OP0x02_COUNTER, MERCURY_POISON_KANKAKU_030, R08, NAX),
	// (02) if (0 != VR08)	{goto 弾撃たない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R08, (+24)),//	(bbb+24)
	//	static u32 VR09 = (0);
	//	VR09 ^= 1;
	// (03)	counter(2, VR09);
	MCODE(OP0x02_COUNTER, 2, R09, NAX),/* 2[kai] == (0 or 1) */
	// ---- if (0==VR09) { } else { }
	// (04) VR15 = hairetu[VR09];goto (aaa+2);
	MCODE(OP0x0a_BRA_TABLE, R09, R15, (+2)),
	(BULLET_MARU10_BASE + TAMA_IRO_03_AOI), 		// ---- 	HATSUDAN_R15_bullet_obj_type = BULLET_MARU10_BASE + TAMA_IRO_03_AOI;		/* [中丸青色弾] [中丸水色弾] */ //	br.BULLET_REGIST_color			= ((8)+(0*5));/*(水色?)*/
	(BULLET_MARU10_BASE + TAMA_IRO_06_KI_IRO),		// ---- 	HATSUDAN_R15_bullet_obj_type = BULLET_MARU10_BASE + TAMA_IRO_06_KI_IRO; 	/* [中丸青色弾] [中丸水色弾] */ //	br.BULLET_REGIST_color			= ((8)+(1*5));/*(黄色?)*/
	// aaa+2:
	// ---- HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((VR09)<<8)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	// (05) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT),
	// HATSUDAN_R14_tama_spec			|= ((VR09)<<8);
	// (06) VR0a			= (VR09 << 8);
	MCODE(OP0x1f_ASLM_PD, 0x08, R0a, R09),/*(ショートメモリアドレッシング)*/
	// (07) VR14	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R14, R0a),
	// ---- //
	// (08) HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(1)),
	// (09) HATSUDAN_R16_n_way				= VR0d; 	/* [n way] */		/* 発弾数 */
	MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
	// (10) HATSUDAN_R17_div_angle65536 		= VR0e;	([難易度別定数]div angle);
	MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
	// ---- //	VR0a	u32 random_angle_offset;
	// ---- //	VR0a = deg360to_rad((replay_rand() % 5)); // 910.222222222222222222222222222222 random_angle_offset
	// ---- VR0a = (ra_nd() & 0x0fff);// 0xe38 == 3640 == 65536/18 random_angle_offset
	// (11) VR0a = (ra_nd()); /*ra_nd_u32*/
	MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
	// (12) VR0a	= (VR0a & 0x0fff);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R0a),
	(0x0fff),
	// (13) HATSUDAN_R13_angle65536 		= VR0a;	/* 基準角度 random_angle_offset */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (14) HATSUDAN_R11_speed256			= t256(2.00);	/* 弾速 */	= t256(3.0) + jj*t256(0.3);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(2.00)),
	// (15) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (16) HATSUDAN_R13_angle65536 		= VR0a;	/* 基準角度 random_angle_offset */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (17) HATSUDAN_R11_speed256			= t256(2.30);	/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(2.30)),
	// (18) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (19)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	// (20)
	// bbb+24:
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (19));
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
//	// (--) HATSUDAN_R16_n_way				= (18); 	/* [18way] */		/* 発弾数 */
//	MCODE(OP0x1c_MOVEM_PD, (18), R16, NAX),/*(ショートメモリアドレッシング)*/
//	// (--) HATSUDAN_R17_div_angle65536 		= (int)(65536/(18));	/* 分割角度(65536[360/360度]を 18 分割) */
//	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(ロングメモリアドレッシング)*/
//	((int)(65536/18)),

local SPELL_INIT(3e_pache_mercury_poison)
{
	static const u32 codebase_init[3] =
	{
	// (01)	VR0d = ([難易度別定数]n way);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((16), (18), (24), (28)), 	/* easyは ,normalは 18way, hardは, lunatic は28way(?) */
	// (02)	VR0e = ([難易度別定数]div angle);
	MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、紅色)*/	/* 分割角度 */
	};
	cpu_exec((u32*)&codebase_init, (2));
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	"土＆金符「エメラルドメガリス」" No.32
	-------------------------------------------------------
	テキトーに作ってみた。
	全然違うんだけど、パチェっぽいといえば、パチェっぽい。
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	乱数っぽい数値。
	R09 	一時使用 (ra_nd_u32等)
	R0a 	一時使用
	//
	R0c 	難易度別弾速定数。
	R0d 	難易度別定数。
---------------------------------------------------------*/
local SPELL_EXEC(3f_pache_emerald_megalith)
{
	static const u32 codebase_exec[59] =
	{
	/* 緑枠弾 */
	// ---- VR08 += (VR10_BOSS_SPELL_TIMER<<4);
	// (01) VR09	= (VR10_BOSS_SPELL_TIMER << 4);
	MCODE(OP0x1f_ASLM_PD, 0x04, R09, R10),/*(ショートメモリアドレッシング)*/
	// (02) VR08 += (VR09);
	MCODE(OP0x04_ADDR_PD, NAX, R08, R09),
	// ランダム緑枠弾
	// (03) VR09 = (VR10_BOSS_SPELL_TIMER & (4-1) );
	MCODE(OP0x1d_ANDM_PD, 0x03, R09, R10),/*(ショートメモリアドレッシング)*/
	// (04) if (0 != VR09)	{goto 弾撃たない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+20)),//	(aaa+20)
	//	VR08 = HATSUDAN_R13_angle65536;
	// ---- HATSUDAN_R13_angle65536 		= ((VR08&(32768-1))-16384);
	// (05) HATSUDAN_R13_angle65536 		= ((VR08&(32768-1)) );
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R08),
	(32768-1),
	// (06) HATSUDAN_R13_angle65536 		+= (-16384);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),
	((-16384)),
	// VR0c = (cg_VR20_game_difficulty)<<4);
	// ---- HATSUDAN_R11_speed256			= (t256(0.75) + (VR08&0x007f) + (VR0c); /* 弾速 */
	// (07) HATSUDAN_R11_speed256			= (VR08 & 0x007f);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R11, R08),
	(0x007f),
	// (08) HATSUDAN_R11_speed256			+= (VR0c); /* 弾速 */
	MCODE(OP0x04_ADDR_PD, NAX, R11, R0c),
	// (09) HATSUDAN_R11_speed256	+= t256(0.75);
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
	(t256(0.75)),
	// ---- HATSUDAN_R12_speed_offset		= ((VR08>>4)&0x07ff);/*(テスト)*/
	// (10) VR0a 	= (VR08 >> 4);
	MCODE(OP0x1e_ASRM_PD, (4), R0a, R08),/*(ショートメモリアドレッシング)*/
	// (11) HATSUDAN_R12_speed_offset = VR0a & (0x07ff);/*(テスト)*/
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R12, R0a),
	(0x07ff),
	// (12) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT),
	// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_05_MIDORI);//		/* [緑枠弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
	(BULLET_WAKU12_BASE + TAMA_IRO_05_MIDORI),
	// (14) HATSUDAN_R16_n_way					= (2);	/* [2way] */								/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (2), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (15) HATSUDAN_R17_div_angle65536 		= (int)(65536/(24)); /* 分割角度(65536[360/360度]を 24 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(ロングメモリアドレッシング)*/
	((int)(65536/24)),
	// (16) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
// aaa+20:
	// ランダム直下落下、緑大玉弾
	// (17) VR09 = (VR10_BOSS_SPELL_TIMER & (16-1) );
	MCODE(OP0x1d_ANDM_PD, 0x0f, R09, R10),/*(ショートメモリアドレッシング)*/
	// (18) if (0 != VR09)	{goto 弾撃たない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+29)),//	(bbb+1)
	// (19) VR09 = (ra_nd());/*&0xffff*/ /*ra_nd_u32*/
	MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
	// (20) VR08	+= (VR09);
	MCODE(OP0x04_ADDR_PD, NAX, R08, R09),
	// ---- VR06	= t256(16)+(ra_nd32&0xff00)+(ra_nd32&0x3f00);	/* 弾源x256 */
	// (21) VR0a	= (VR09 & 0xff00);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R09),
	(0xff00),
	// (22) VR06	= (VR09 & 0x3f00);
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R06, R09),
	(0x3f00),
	// (23) VR06	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R06, R0a),
	// (24) VR06	+= t256(16); 	/* 弾源x256 */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R06, R06),
	(t256(16)),
	// ---- VR07	+= -t256(32)+((ra_nd32>>8)&0x3f00); 			/* 弾源y256 */
	// (25) VR0a 	= (VR09 >> 8);
	MCODE(OP0x1e_ASRM_PD, (8), R0a, R09),/*(ショートメモリアドレッシング)*/
	// (26) VR0a &= 0x3f00;
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0a, R0a),
	(0x3f00),
	// (27) VR07	+= (VR0a);
	MCODE(OP0x04_ADDR_PD, NAX, R07, R0a),
	// (28) VR07	+= -t256(32); 	/* 弾源y256 */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R07, R07),
	(-t256(32)),
	/* 自機狙い 3way 白laser弾 */
	/* 自機狙わない 16way(?)17way(?) 青丸弾 */
	// (29) HATSUDAN_R11_speed256			= (t256(0.50) );			/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(0.50)),
	// (30) HATSUDAN_R12_speed_offset		= t256(8);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(8)),
	// (31) HATSUDAN_R13_angle65536 			= (0);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),// 0 ==LONG_MEMORY_ADDRESSING
	(t256(0)),
	// (32) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
	(DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT),
	// (33) HATSUDAN_R15_bullet_obj_type		= (BULLET_OODAMA32_03_MIDORI);//				/* [緑大玉弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
	(BULLET_OODAMA32_03_MIDORI),
	// (34) HATSUDAN_R17_div_angle65536 		= (int)(65536/19);	/* 分割角度(65536[360/360度]を 19 分割) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(ロングメモリアドレッシング)*/
	((int)(65536/19)),
	/* easyは1方向, hardは1方向, lunatic は3方向 */
	// (35) HATSUDAN_R16_n_way					= (VR0d);	/* [1-3way] */		/* 発弾数 */
	MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
	// (36) 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
// bbb+29:
	// 効果音
	// (37) VR09 = (VR10_BOSS_SPELL_TIMER & (32-1) );
	MCODE(OP0x1d_ANDM_PD, 0x1f, R09, R10),/*(ショートメモリアドレッシング)*/
	// (38) if (0 != VR09) {goto 発音しない。;}// if (0<VR0c) {goto 発音しない。;}// ==if (0==VR0c) {発音する。;}/* (40回に1回) 発音 */ if (1==VR0c)		{	}
	MCODE(OP0x08_BNE_RS, (0x00), R09, (+1)),//	(ccc+1)
	// (39)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
// ccc+1:
	// (40)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (40));
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(3f_pache_emerald_megalith)
{
	static const u32 codebase_init[4] =
	{
	// (01)	VR0d = ([難易度別定数]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(( 1), ( 1), ( 1), ( 3)), 	/* easyは1方向, hardは1方向, lunatic は3方向 */
	// (02)	VR0c = ([難易度別弾速定数]);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0c, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(( 0), (16), (32), (48)), 	/* easyは1方向, hardは1方向, lunatic は3方向 */
//	// (02) VR0c			= (cg_VR20_game_difficulty << 4);	/* 弾速 */
//	MCODE(OP0x1f_ASLM_PD, 0x04, R0c, R20_PLAYER_DATA_game_difficulty),/*(ショートメモリアドレッシング)*/
	};
	cpu_exec((u32*)&codebase_init, (2));
}
