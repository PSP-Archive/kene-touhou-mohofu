
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	アリスのカードを定義します。
---------------------------------------------------------*/


/*---------------------------------------------------------
	アリス(仮)	赤の魔法(2段階目)のようなもの。
	-------------------------------------------------------
	移動を制限するカード。
	とりあえずアリスだから、赤の魔法の2段階目。
	-------------------------------------------------------
	使用レジスタ:
	R08 	カウンタ。(4回に1回発弾する)
	R09 	乱数で[破壊]
	R0a 	自機狙い角を一時保持する。(現在の実装では HATSUDAN_R13_angle65536 が破壊される仕様なので要るが、後で要らなくなるかも？)
	R0b 	[x座標一時保存] [一時使用]
	R0c 	[y座標一時保存]
	R0d 	難易度別定数1
	R0e 	難易度別定数2
---------------------------------------------------------*/

local SPELL_EXEC(0e_aka_2nd)
{
	static const u32 codebase_exec[60] =
	{
		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		// (1)	counter(&VR08, 4);
		MCODE(OP0x02_COUNTER, 4, R08, NAX),
		//	if (0 == VR08)
		// (2)	if (0 != VR08)	{return;}
		#if (1==USE_CPU_EXTRA)
		MCODE(OP0x08_BNE_RS, (0x00), R08, CPU_QUIT),// (ddd+57)
		#else
		MCODE(OP0x08_BNE_RS, (0x00), R08, (+57)),// (ddd+57)
		#endif
		//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))
		// (3)	HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R10),
		// (4)	VR11 &= (0x1f);
		MCODE(OP0x1d_ANDM_PD, (0x0f), R11, R11),
		// (5)	if (0x00 != VR11) goto (ccc+29);//if (0x00 == (VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x08_BNE_RS, (0x00), R11, (+29)),// (ccc+29)
		//------------------
		// (6)	VR0b = VR06;// (push VR06)[ボスx座標一時保存]
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R06),
		// (7)	VR0c = VR07;// (push VR07)[ボスy座標一時保存]
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R07),
		// (8)	HATSUDAN_R11_speed256	= (t256(1.0));
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
		(t256(1.0)),
		// (9)	HATSUDAN_R13_angle65536 = (VR10_BOSS_SPELL_TIMER << (8));
		MCODE(OP0x1f_ASLM_PD, (8), R13, R10),/*(ショートメモリアドレッシング)*/
		// (10)  (sincos256);/*(破壊レジスタ多いので注意)*/
		MCODE(OP0x10_SINCOS256, NAX, R06, R07),
		//	cg_BOSS_DATA_3a_center_x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//	cg_BOSS_DATA_3b_center_y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//	NAX/*(終了)*/
		//[重複]	HATSUDAN_R11_speed256			= t256(1.0);							/* 弾速 */
		// (11) HATSUDAN_R12_speed_offset			= t256(1.0);/*6(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
		(t256(1.0)),
		// (12) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(ロングメモリアドレッシング)*/
		((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
		// (13) HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [赤米弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
		((BULLET_KOME_BASE + TAMA_IRO_01_AKA)),
		// (14) HATSUDAN_R16_n_way					= (8);						/* [8way] */
		MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (15) HATSUDAN_R17_div_angle65536 		= (int)(65536/48);			/* 分割角度(65536/(6*8) ) １周を8分割した領域をさらに6分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),/*(ロングメモリアドレッシング)*/
		((int)(65536/48)),
	//	NAX/*(終了)*/
		//------------------
		// (16) VR06 = VR0b;//[ボスx座標復活]	// (pop VR06)[発射座標リストア]
		MCODE(OP0x01_MOVER_PD, NAX, R06, R0b),
		//------------------ tmp_kakudo を R0b に計算する。(レジスタ足りないから R0b を間借りする。)
		// (17) R0b/*const int tmp_kakudo*/ = (VR07/*sin_value_t256*/<<4);	/* 次に揺らぎ分[1/2]を加える。 */
		MCODE(OP0x1f_ASLM_PD, (4), R0b, R07),/*(ショートメモリアドレッシング)*/ /* 揺らぎ分[1/2]を加える。 */
		//		(65536/(4*2)) + 	/* (65536/(4*2)) == まず(90/360)度の半分加える。(後で2倍になる) */	/* 弾が絶対にこない範囲 */
		//	//	(65536/(8*2)) + 	/* (65536/(8*2)) == まず(45/360)度の半分加える。(後で2倍になる) */	/* 弾が絶対にこない範囲 */
		//	//	(65536/128) +		/* まず(2.8125/360)度加える。(左右なので2倍==5.625度になる) */		/* 弾が絶対にこない範囲 */
		//		((256<<4)); /* 次に揺らぎ分を加える[2/2]。 */
		// (18) VR0b += ((65536/(4*2))+((256<<4))); 	/* 弾が絶対にこない範囲 + 揺らぎ分[2/2] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),
		((65536/(4*2))+((256<<4))), 	/* 弾が絶対にこない範囲 + 揺らぎ分[2/2] */
		//------------------
		// (19) VR07 = VR0c;//[ボスy座標復活]	// (pop VR07)[発射座標リストア]
		MCODE(OP0x01_MOVER_PD, NAX, R07, R0c),
		//------------------(レジスタ足りないから R0c を間借りする。)
	//	/* hatudan_system_regist_katayori_n_wayの仕様が単純な為、(R0bを) 補正する */
	//	#define BA_HOSEI48	((65536/(48/8))/2)	/* 一周 65536系で 48分割弾 x 8 way の真中(つまり/2)付近 */
	//	/*tmp_kakudo-BA_HOSEI48*/R0c = /*tmp_kakudo*/R0b - BA_HOSEI48;
		// (20) VR0c = R0b - ((65536/(48/8))/2);BA_HOSEI48
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0b),
		(u32)(-((65536/(48/8))/2)), 	/*	- BA_HOSEI48 */
		//------------------ R0b == tmp_kakudo;
		// (21) [右側]	HATSUDAN_R13_angle65536 	= (( tmp_kakudo - BA_HOSEI48)&(65536-1));	/* 角度(下CCWなので正方向==右側) */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (22)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		//------------------ R0b == tmp_kakudo;
		// (23) [左側]	HATSUDAN_R13_angle65536 	= ((-tmp_kakudo - BA_HOSEI48)&(65536-1));	/* 角度(下CCWなので負方向==左側) */
		//		VR0b = (VR00 + (0) - VR0b);
		MCODE(OP0x05_SUBR_PD, (0x00), R0b, R00),/*(ゼロレジスタ使用)*/
		// (24) VR0c = R0b - ((65536/(48/8))/2);BA_HOSEI48
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0b),
		(u32)(-((65536/(48/8))/2)), 	/* - BA_HOSEI48 */
		// (25)
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (26)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		//------------------
	//(ccc+29:)
		// (27) HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R10),
		// (28) VR11 &= (0x1f);
		MCODE(OP0x1d_ANDM_PD, (0x1f), R11, R11),
		// (29) if (0x00!=VR11) goto (aaa+3);//if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x08_BNE_RS, (0x00), R11, (+3)),//(aaa+3)
		// (r35でカードの場合のみ省略可能)	set_REG_DEST_BOSS_XY();
		// (30)  (calculate_jiki_nerai);/* 自機狙い角作成 */
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
		// (31) VR0a						= HATSUDAN_R13_angle65536;/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R0a, R13),
		// (32)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//(aaa+3:)
		//	HATSUDAN_R11_speed256 = (t256(1.1));					/* 弾速 */
		// (==1)	HATSUDAN_R11_speed256 = VR10_BOSS_SPELL_TIMER;	/* 弾速 */ /* 後で撃つほうが速く */
		// (==2)	VR11 &= (0x1f);
		// (33) VR11 = (VR00 + (0x1f) - VR11);
		MCODE(OP0x05_SUBR_PD, (0x1f), R11, R00),/*(ゼロレジスタ使用)*/
		// (34) VR11 += t256(1.0);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(u32)(t256(1.0)),
		// (35) HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(3/*6*/)),
		// (36) HATSUDAN_R13_angle65536 		= (VR0a);/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
		// (37) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT),
		// (38) HATSUDAN_R15_bullet_obj_type	= (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA);	/* [赤鱗弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_UROKO14_BASE + TAMA_IRO_01_AKA),
		// (39) HATSUDAN_R16_n_way = VR0d;	/* [VR0d way] */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
		// (40) HATSUDAN_R17_div_angle65536 = VR0e; /* 分割角度(65536/(6*8) ) １周を8分割した領域をさらに6分割した角度 */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
			//	os2x	発弾するx位置(乱数的に横にずらす)
			//	VR06 += (ra _nd() & 0x1fff)-t256((32)/2);	/* 弾源x256 */
		// (41) VR06 += (VR09 & 0x1fff)-t256((32)/2);	/* 弾源x256 */
		MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
		// (42) VR09 &= (0x1fff);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R09, R09),
		(0x1fff),
		// (43) VR09 -= t256((32)/2);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
		(u32)(-t256((32)/2)),
		// (44) VR06 += VR09;
		MCODE(OP0x04_ADDR_PD, NAX, R06, R09),
		/* 自機狙い */
		// (45)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	//(ddd+57:)
		// (46)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (45));
}

local SPELL_INIT(0e_aka_2nd)
{
	static const u32 codebase_init[5] =
	{
		// (1)	VR0d = 難易度別定数1	VR0d = [tama_const_H06_NUMS_ALICE_RED];/*(分割数、紅色)*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST(( 8), ( 7), ( 7), ( 7)),/*tama_const_H06_NUMS_ALICE_RED*/	/* 分割数:(r35-) */ 	/* 註:3より4の方が簡単 */
		// (2)	VR0e = 難易度別定数2	VR0e = [tama_const_H07_DIVS_ALICE_RED];/*(分割角、紅色)*/		/*((VR10_BOSS_SPELL_TIMER & 0x20)>>3)+*/
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0e, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((18), (18), (20), (24)),/*tama_const_H07_DIVS_ALICE_RED*/	/*((VR10_BOSS_SPELL_TIMER & 0x20)>>3)+*/		/* 分割角度:  (r35-) */
		// (3)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0e),// R0e = 65536 / R0e;
	};
	cpu_exec((u32*)&codebase_init, (3));//
}
//	VR0d	= NAN_IDO_DECODE(PACK_NAN_IDO_CONST((12), (18), (20), (24)));
//	VR0d	= NAN_IDO_DECODE(PACK_NAN_IDO_CONST((6), (3), (5), (7)));
	#if 0
	// ★ アリス 「赤の魔法」用
	//	(3),								(4),								(5),								(6),								/* 分割数:(-r34) */
		(6),								(3),								(5),								(7),								/* 分割数:(r35-) */ 	/* 註:3より4の方が簡単 */
	//	(int)(65536/(18)),					(int)(65536/(24)),					(int)(65536/(40)),					(int)(65536/(64)),					/* 分割角度:  (-r34) */
	//	(int)(65536-(int)(65536/(18))), 	(int)(65536-(int)(65536/(24))), 	(int)(65536-(int)(65536/(40))), 	(int)(65536-(int)(65536/(64))), 	/* 分割角度_R:(-r34) */
		(int)(65536/(12)),					(int)(65536/(18)),					(int)(65536/(20)),					(int)(65536/(24)),					/* 分割角度:  (r35-) */
	//	(int)(65536-(int)(65536/(12))), 	(int)(65536-(int)(65536/(18))), 	(int)(65536-(int)(65536/(20))), 	(int)(65536-(int)(65536/(24))), 	/* 分割角度_R:(r35-) */
	#endif

// ==================================== [スペカ境界] ==================================== //

#if 1/*(r39)*/
/*---------------------------------------------------------
	アリス normal通常攻撃3(の一部)
	-------------------------------------------------------
	-------------------------------------------------------
	使用レジスタ
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
	交差弾。時計回り。
---------------------------------------------------------*/
local TAMA_FUNC(alice_aaa_danmaku_01_callback)
{
	/* 0-256 カウントまで */	/* [0]カウント==発弾位置 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-80) < src_tama->jyumyou)/* 発弾エフェクト後から[0-79]カウント経過した弾 */
	{
	//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
	//			{src_tama->rotationCCW1024++;}/* 曲げてみるテスト */
	//	else	{src_tama->rotationCCW1024--;}/* 曲げてみるテスト */
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
				{src_tama->rotationCCW65536 += (1<<6);}/* 曲げてみるテスト */
		else	{src_tama->rotationCCW65536 -= (1<<6);}/* 曲げてみるテスト */
	}
	// (この方が解かりやすい？)
	else
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256) == src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[256]カウント経過した弾 */
	{
		/* (通常弾へ変身する==画面内では弾は消えない) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		#if (1)/*(デバッグ)*/
		src_tama->obj_type_set					= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);		/* [ミニ赤丸弾] */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* 弾グラと弾あたり判定を変更する。 */
		#endif
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

local SPELL_EXEC(17_alice_nejiri10sec)
{
	/*(無い[人形にやらせて本人は見てるだけだったり...])*/
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_INIT(17_alice_nejiri10sec)
{
	cg_BOSS_DATA_39_tukaima_type = TUKAIMA_0f_alice_T0f;
	set_tukaima_start();
}

#endif
// ==================================== [スペカ境界] ==================================== //

#if 0/*(r38)*/
/*---------------------------------------------------------
	アリス normal通常攻撃3(の一部)
	-------------------------------------------------------
	なんか全然まったく似てない。
	妖々夢風のつもりで創っていたが怪綺談風になった。
	何を言ってるのかわからないと思うが、わたしにもわからないや。
	恐ろしいものの片鱗を以下略。
	psp解像度が全然違うから、無理に似せようとしない方が良いかも？
	-------------------------------------------------------
	使用レジスタ
---------------------------------------------------------*/

local SPELL_EXEC(17_alice_nejiri10sec)
{
	if ((64*1) < VR10_BOSS_SPELL_TIMER)
	{
		/* [CW 時計回り] */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		{
			cg_BOSS_DATA_38_angleCCW65536 -= (int)(65536/24);
			#if 0
			cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & ((1<<difficulty)-1) );
			#else
			{
				static const u8 masked_tbl[4] = { 0x00, 0x0f, 0x3f, 0xff };
				cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & (masked_tbl[(cg_VR20_game_difficulty)]) );
			}
			#endif
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
			//
				HATSUDAN_R11_speed256				= (t256(1.0));							/* 弾速 */
				HATSUDAN_R12_speed_offset			= t256(1);/*(テスト)*/
				HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
				HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);				/* [枠付き青丸弾] */
				HATSUDAN_R16_n_way					= (6);									/* [6way] */
				HATSUDAN_R17_div_angle65536 		= (int)(65536/48);						/* 分割角度(65536/(6*8)) １周を8分割した領域をさらに6分割した角度 */
			{
				HATSUDAN_R13_angle65536 			= (cg_BOSS_DATA_38_angleCCW65536);							/* 角度 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			//
				HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW65536+(65536/2))&(65536-1));					/* 角度 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
	else
	if ((64*2) < VR10_BOSS_SPELL_TIMER)
	{
		/*[CCW 反時計回り]*/
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
		{
			cg_BOSS_DATA_38_angleCCW65536 += (int)(65536/24);
			#if 0
			cg_BOSS_DATA_38_angleCCW65536 -= (int)(ra_nd() & ((1<<difficulty)-1) );
			#else
			{	static const u8 masked_tbl[4] = { 0x00, 0x0f, 0x3f, 0xff };
				cg_BOSS_DATA_38_angleCCW65536 -= (int)(ra_nd() & (masked_tbl[(cg_VR20_game_difficulty)]) );
			}
			#endif
			mask65536(cg_BOSS_DATA_38_angleCCW65536);
			//
				HATSUDAN_R11_speed256				= (t256(1.0));							/* 弾速 */
				HATSUDAN_R12_speed_offset			= t256(1);/*(テスト)*/
				HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
				HATSUDAN_R15_bullet_obj_type		= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);				/* [枠付き赤丸弾] */
				HATSUDAN_R16_n_way					= (6);									/* [6way] */
				HATSUDAN_R17_div_angle65536 		= (int)(65536/48);						/* 分割角度(65536/(6*8)) １周を8分割した領域をさらに6分割した角度 */
			{
				HATSUDAN_R13_angle65536 			= (cg_BOSS_DATA_38_angleCCW65536);							/* 角度 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			//
				HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW65536+(65536/2))&(65536-1));					/* 角度 */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
			}
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
}
#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	アリス	アリス人形カード
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形 -easy-」
アリスの放った四体の人形が、二回分裂する7way弾を撃つ。
4 x 7 x 7 == 最大 196[弾](妖々夢)
3 x 7 x 7 == 最大 147[弾](模倣風)	//3 x 8 x 8 == 192
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形」
アリスの放った六体の人形が、二回分裂する7way弾を撃つ。
6 x 7 x 7 == 最大 294[弾](妖々夢)
5 x 7 x 7 == 最大 245[弾](模倣風)	//5 x 8 x 8 == 320
	-------------------------------------------------------
蒼符「博愛の仏蘭西人形 -hard-」
アリスの放った八体の人形が、二回分裂する7way弾を撃つ。
8 x 7 x 7 == 最大 392[弾](妖々夢)
9 x 7 x 7 == 最大 441[弾](模倣風)	//7 x 8 x 8 == 448
	-------------------------------------------------------
蒼符「博愛のオルレアン人形」赤弾→緑弾
アリスの放った八体の人形が、三回分裂する7way弾を撃つ。
8 x 7 x 7 x 7 == 最大2744[弾](妖々夢)
2 x 7 x 7 x 7 == 最大 686[弾](模倣風)	//9 x 8 x 8 == 576
---------------------------------------------------------*/
extern OBJ_CALL_FUNC(add_zako_alice_doll_type_a);/* アリス人形カード */
local SPELL_EXEC(0b_alice_zako_doll)
{
	if (50 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_alice_doll_type_a(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

/*---------------------------------------------------------
	計7つに分裂する。
	-------------------------------------------------------
---------------------------------------------------------*/
#if 0
local void exchange_damnaku_alice_7_bunretu(void)
{
	int jj = 0;
	int ii;
	for (ii=0; ii<OBJ_POOL_00_TAMA_1024_MAX; ii++)/* 全部調べる。 */
	{
		OBJ *s;
		s = &obj99[OBJ_HEAD_00_0x0000_TAMA+ii];
		/* 色に関係なく鱗弾[ ... ]なら */
		if (((BULLET_UROKO14_03_AOI+1) & 0xfff8) == (s->type & 0xfff8) )	/* [赤鱗弾]なら */
		{
			jj++;
		//	jj &= 0x07; 	// 2 3 4 5	6 7 8 9
			jj &= 0x03; 	// 3 4 5 6
		//	s_change_meirin_yajirusi_one(s);
		//	s->tra65536 					= t256(6);		/* 調整加速弾 */
		//	s->tra65536 					= (jj<<8)+t256(2);	/* (2 ... 9) 調整加速弾 */
			s->tra65536 					= (jj<<8)+t256(3);	/* (3 ... 6) 調整加速弾 */
			/* (1は遅すぎたので除外) 9 だと速過ぎるかも */
		}
	}
}
#endif
extern OBJ_CALL_FUNC(add_zako_alice_doll_type_b);/* アリス人形カード */
local SPELL_EXEC(1e_alice_tama_doll)
{
	if (250 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_alice_doll_type_b(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))
	{
		/* 弾分裂 */
//		exchange_damnaku_arice_7_bunretu();
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}
/*
// 蒼符「博愛の仏蘭西人形」
	各人形が1弾生成(青弾)
	外側に射出。
//
	180度反転する。
	７弾に分裂(青弾→白弾)
  A   A    A   A   --- 速度速い

		A------------- 速度中
		|
   A	|	 A	------ 速度遅い
		+
//
	180度反転する。
	７弾に分裂(白弾→赤弾)
  A   A    A   A   --- 速度速い

		A------------- 速度中
		|
   A	|	 A	------ 速度遅い
		+
// 蒼符「博愛のオルレアン人形」のみ
	180度反転する。
	７弾に分裂(赤弾→緑弾)
  A   A    A   A   --- 速度速い

		A------------- 速度中
		|
   A	|	 A	------ 速度遅い
		+
//

*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	アリス	諏訪子っぽい(?)カード
	-------------------------------------------------------
	テキトー
	-------------------------------------------------------
	使用レジスタ
	R08 	向き。

---------------------------------------------------------*/

local SPELL_EXEC(25_alice_suwako)
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))/* 2回に1回 */
	{
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))/*  8に1回 */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))/* 16に1回 */
		{
			VR08 -= (int)(65536*8/256);
			CPU_CALL(cpu_auto_bullet_play_default);
		}
	//	VR08 -= (65536/256);	/* 1周を256分割した角度 */
	//	VR08 -= (65536/512);	/* 1周を256分割した角度の半分。 */
		VR08 -= (200);	/*	テキトー 1周を256分割した角度の半分。 */
		/* 弾生成 */
		{
			HATSUDAN_R11_speed256				= (t256(1.0) ); 					/* 弾速(pspの画面は狭い) */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R16_n_way					= (8);								/* [8way] */			/* 8方向弾 */
			HATSUDAN_R17_div_angle65536 		= (65536/8);						/* 分割角度(弾がこない範囲を除き32分割) */	/* (ra_nd16>>4) == 乱数(0-4095) */
			//
			/* 0 [...赤] 150 [...青+赤] 180 [...青] 255 */
			if ((0) == (VR10_BOSS_SPELL_TIMER & 1))
			{
				if ((s32)(128+((cg_VR20_game_difficulty)<<2)) > (VR10_BOSS_SPELL_TIMER))
				{
					HATSUDAN_R12_speed_offset		= t256(2);			/* 調整減速弾 */	/* この方式になるか検討中 */
					HATSUDAN_R13_angle65536 		= (VR08);			/* 向き */
					HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* 赤米弾 */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
				}
			}
			else
			{
				if ((s32)(128-((cg_VR20_game_difficulty)<<2)) < (VR10_BOSS_SPELL_TIMER))
				{
					HATSUDAN_R12_speed_offset		= t256(1);			/* 調整減速弾 */	/* この方式になるか検討中 */
					HATSUDAN_R13_angle65536 		= (65536-VR08); 	/* 向き */
					HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* 青米弾 */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
				}
			}
		}
	}
}
// ==================================== [スペカ境界] ==================================== //
