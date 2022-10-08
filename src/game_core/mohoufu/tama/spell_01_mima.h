
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	魅魔のカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	魅魔、花てすとカード
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	adj_hari65536	開始地点
	R0a 	x位置/退避/復旧
	R0b 	y位置/退避/復旧
	R0c 	増分temp65536
	R0d 	speed256 難易度別速度256
---------------------------------------------------------*/
/*---------------------------------------------------------
	#001 角度弾の移動を行う(通常弾用)
---------------------------------------------------------*/

static TAMA_FUNC(mima_danmaku_01_callback)
{
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) < src_tama->jyumyou)/* 発弾エフェクト時は無効 */
	{	return; }
	#endif
	#if (1)
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) == src_tama->jyumyou)/* 発弾エフェクト後から512カウント経過した弾 */
	{	/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	}
	#endif
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}


/*---------------------------------------------------------
	魅魔、花てすとカード
	-------------------------------------------------------
	封魔禄では4方向バラマキっぽいのを撃ってくるが、
	アレンジして5方向。花映塚っぽい奴に。
	-------------------------------------------------------
	テキトー
-dd 1 0000 0x10 == (xxx)&0x1f
-11 1 0000 luna
-10 1 0000 luna hard
-01 1 0000 luna hard norm
-00 1 0000 luna hard norm easy
---------------------------------------------------------*/

local SPELL_EXEC(0c_hana_test)
{
//	if (0x40 == (VR10_BOSS_SPELL_TIMER & 0xcf))/* 4回 */
//	if (0x10 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* (16回に1回)(128なら計8回) */
	if (0x10 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* (16回に1回)(128なら計4回) */
	{
		if (((unsigned)cg_VR20_game_difficulty) >= (((unsigned)VR10_BOSS_SPELL_TIMER)>>5))
		{
		//	mima_boss01_nway_fire(src_boss);
		//	local OBJ_CALL_FUNC(mima_boss01_nway_fire)
			/* 弾源x256 y256 ボスの中心から発弾。 */
			CPU_CALL(calculate_boss_to_jiki_nerai);/* 自機狙い角作成 */
			VR09 = (HATSUDAN_R13_angle65536);
			//
			VR0d = (/*0x200*/0x100)+(ra_nd()&0xff)-((3-(cg_VR20_game_difficulty))<<6);/* 難易度別で速度低下 */
			//------------------
			// 退避VR0a = VR06;VR0b = VR07;
			//------------------
			//
		//	HATSUDAN_R12_speed_offset			= t256(1/*0*/);/*(テスト)*/
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R15_bullet_obj_type		= BULLET_HARI32_00_AOI + ((VR10_BOSS_SPELL_TIMER)>>5);	/* [水色針弾] */	/*hari_no_iro*/
			//
			VR02_j = (0);
			loop_j:;
			VR0c = (0);
			VR03_i = 0;
			loop_i:;
			//------------------
	static const u32 codebase[16+4] =
	{
		// (07) HATSUDAN_R11_speed256	= t256(1.00);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(1.00)),
		// (08) HATSUDAN_R13_angle65536 = (VR03_i);
		MCODE(OP0x01_MOVER_PD, NAX, R13, R03_i),
		// (09)  (sincos256);/*(破壊レジスタ多いので注意)*/
	//	MCODE(OP0x10_SINCOS256, NAX, R06, R07),
		MCODE(OP0x10_SINCOS256, NAX, R12, R11),/*(R12はダミー破壊)*/		//	HATSUDAN_R11_speed256 = VR07; /* 弾速 */
		// (10) 	VR11 += VR0d;
		MCODE(OP0x04_ADDR_PD, NAX, R11, R0d),
		//	h->center.y256 = (VR06);/*fps_factor*/
		// 復旧VR06 = VR0a;VR07 = VR0b;
		//	VR12	= t256(HATSUDAN_R11_speed256 >> (6));/* (魅魔様lunaticで)これでも良い気もするけど。 */
		//	VR12	= t256(HATSUDAN_R11_speed256 >> (7));/* (パチェがあるから)少し簡単にしとく。 */
		//	VR12	= (HATSUDAN_R11_speed256 << (8-6));/* (魅魔様lunaticで)これでも良い気もするけど。 */
		//	VR12	= (HATSUDAN_R11_speed256 << (8-7));/* (パチェがあるから)少し簡単にしとく。 */
		// (11) VR12 = (VR11 << (8-7));
		MCODE(OP0x1f_ASLM_PD, (8-7), R12, R11),/*(ショートメモリアドレッシング)*/
		// (12) VR12 = (VR00 + (0) - VR12); HATSUDAN_R12_speed_offset	= 0 - VR12;
		MCODE(OP0x05_SUBR_PD, (0x00), R12, R00),/*(ゼロレジスタ使用)*/
		// (13) HATSUDAN_R13_angle65536 	= VR09; 	/* 角度 */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
		// (14) 	VR13 += VR02_j; 	/* 角度 */
		MCODE(OP0x04_ADDR_PD, NAX, R13, R02_j),
		// (15) 	VR13 += VR0c;			/* 角度 */
		MCODE(OP0x04_ADDR_PD, NAX, R13, R0c),
		// (16) (1弾撃つ)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		// (17) VR0c += ((65536/16)/5);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0c),/*(ロングメモリアドレッシング専用命令)*/
		((65536/16)/5),
		// (18) VR03_i += (65536/32);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R03_i, R03_i),/*(ロングメモリアドレッシング専用命令)*/
		((65536/32)),
		//------------------
		//	if (VR03_i < (65536/2)) {goto loop_i;}
		/*R11, R12はダミー破壊*/
		// (19) VR12 = (65536/2);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		((65536/2)),
		// (20) VR11 = VR03_i;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R03_i),
		// (21) VR11 = (VR12 + (0) - VR11);
		MCODE(OP0x05_SUBR_PD, (0x00), R11, R12),
		//------------------
		// (29)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase, (15));
			//------------------
			if (0 < VR11) {goto loop_i;}
			VR02_j += (65536/5);
			//------------------
			if (VR02_j < (65536-(20*64))) {goto loop_j;}
			//
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE11_BOSS_KIRARIN, NAX, NAX),
			//	NAX/*(終了)*/
			};
			cpu_exec((u32*)&codebase888, (1));
		}
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	魅魔、接近カード
	-------------------------------------------------------
	ここで下方うねり4方向、重力弾っぽい奴(予定)
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R0a 	temporary 一時使用
	R0e 	src_shot_angle65536 開始地点
---------------------------------------------------------*/
	//	if (difficulty >= ((VR10_BOSS_SPELL_TIMER)>>5))		{}
//	if (0x40 == (VR10_BOSS_SPELL_TIMER & 0xcf))/* 4回 */
//	if (0x10 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* (32回に1回)(128なら計 回) */
local SPELL_EXEC(46_mima_sekkin)
{
	static /*const*/ u32 codebase_exec[21] =
	{
	// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x07);
	MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R10),/*(ショートメモリアドレッシング)*/
	// (02) if (0x04 != VR0a)	{goto aaa+17;:}
	MCODE(OP0x08_BNE_RS, (0x04), R0a, (+17)),// ( aaa+17)
	//	VR0e -= (16);		/* cv1024r(10)*/
	//	VR0e -= (16*64);	/* cv1024r(10)*/
	//	VR0e = ((s rc->shot_angle65536));/*(1024to65536)*/
	// (03) VR0e -= (1820); 	/* cv1024r(10)*/	// 1820.44444444444444444444444444444 == 65536/36
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0e, R0e),/*(ロングメモリアドレッシング専用命令)*/
	(int)(-1820),
	//---------//set_com mon_gin_tama_void();/*(共通部分)*/
//	使用レジスタ:	R0e 	src_shot_angle65536 開始地点
	// (04) HATSUDAN_R11_speed256					= t256(1.0);//t256(1+difficulty)/*(3+difficulty)*/ /*(4+difficulty)*/;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.00)),
	// (05) VR12 = ra _nd();
	MCODE(OP0x15_RAND_VALUE, NAX, R12, NAX),
	// (06) VR12 = (VR12 & 0x03);
	MCODE(OP0x1d_ANDM_PD, 0x03, R12, R12),/*(ショートメモリアドレッシング)*/
	// (07) HATSUDAN_R12_speed_offset				+= (2);//t256(0.04)/*10*/ ((ra_nd()&0x03)+1);
	MCODE(OP0x01_MOVER_PD, (u8)(+2), R12, R12), /*(インデックス付)*/
	// (08) VR13 = (VR0e & ((65536/4)-1));
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R13, R0e),
	((65536/4)-1),
	// (09) HATSUDAN_R13_angle65536 				= R13 + (65536/4)+(65536/8);// /*deg512_2rad*/( (doll_data->br_angle512&(256-1) )+deg_360_to_512(90) );
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R13, R13),/*(ロングメモリアドレッシング専用命令)*/
	((65536/4)+(65536/8)),
	// (10) HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
	// (11) HATSUDAN_R15_bullet_obj_type			= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* 弾グラ */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_MINI8_BASE + TAMA_IRO_03_AOI)),
	//---------//
	// (12) (1弾撃つ)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
	// (13)
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE11_BOSS_KIRARIN, NAX, NAX),
//aaa+17:
	// (14)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (13));
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	魅魔、トゲカード(秋 静葉、葉符「狂いの落葉」っぽい？)
	-------------------------------------------------------
	テキトー
	f e d [c] 1100
	b a 9 [8] 1000
	7 6 5 [4] 0100
	3 2 1 [0] 0000
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	kaiten_aaa
	R0a 	temporary 一時使用
	R0b 	temporary 一時使用
	R0c 	kakudo_111
---------------------------------------------------------*/
local SPELL_EXEC(47_mima_toge)
{
	static const u32 codebase_exec[38] =
	{
	// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x33);
	MCODE(OP0x1d_ANDM_PD, 0x33, R0a, R10),/*(ショートメモリアドレッシング)*/
	// (02) if (0 != VR0a)	{goto 弾撃たない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (+35)),// (bbb+35)
	// (03) VR0a = (VR10_BOSS_SPELL_TIMER & 0x3f);
	MCODE(OP0x1d_ANDM_PD, 0x3f, R0a, R10),/*(ショートメモリアドレッシング)*/
	// (04) if (0 != VR0a)	{goto 弾撃たない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (+11)),// (aaa+11)
	// (05) VR0c += (65536/7);	/* ちょっとアリス風味 */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0c, R0c),/*(ロングメモリアドレッシング専用命令)*/
	((65536/7)),
	// (06) HATSUDAN_R11_speed256	= t256(64.00);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(64.00)),
	// (07) HATSUDAN_R13_angle65536 = (VR0c);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
	// (08)  (sincos256);/*(破壊レジスタ多いので注意)*/
//	MCODE(OP0x10_SINCOS256, NAX, R06, R07),
	MCODE(OP0x10_SINCOS256, NAX, R0a, R0b),
	// VR09 -= VR0b;	/* 弾速 */
	// (09) VR0b = (VR00 + (0) - VR0b); VR0b	= 0 - VR0b;
	MCODE(OP0x05_SUBR_PD, (0x00), R0b, R00),/*(ゼロレジスタ使用)*/
	// (10) VR09 += VR0b;			/* 角度 */
	MCODE(OP0x04_ADDR_PD, NAX, R09, R0b),
//	h->center.y256 = (VR0a);/*fps_factor*/
	// (11) AUDIO_18_voice_number		= VOICE11_BOSS_KIRARIN;
	MCODE(OP0x1c_MOVEM_PD, (VOICE11_BOSS_KIRARIN), R18, NAX),/*(ショートメモリアドレッシング)*/
	// (12) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;/*テキトー*/
	MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(ショートメモリアドレッシング)*/
	// (13)  (cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
//	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE11_BOSS_KIRARIN, NAX, NAX),
//aaa+11:
	//------------------
	// (14) HATSUDAN_R11_speed256		= (t256(1.5));		/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(1.5)),
	// (15) HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (16) HATSUDAN_R15_bullet_obj_type		= (BULLET_HARI32_00_AOI);				/* [水色針弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_HARI32_00_AOI),
	// (17) HATSUDAN_R16_n_way					= (5);									/* [5way] */
	MCODE(OP0x1c_MOVEM_PD, (5), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (18) HATSUDAN_R17_div_angle65536 		= (int)(65536/5);						/* 分割角度 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
	((int)(65536/5)),
	//------------------
	// (19) VR0a = (VR10_BOSS_SPELL_TIMER & 0x0f);
	MCODE(OP0x1d_ANDM_PD, 0x0f, R0a, R10),/*(ショートメモリアドレッシング)*/
	// ---- VR0b = ((0x0c-VR0a)<<8);
	// (20) VR0b = VR0a;
	MCODE(OP0x01_MOVER_PD, NAX, R0b, R0a),
	// (21) VR0b = (VR00 + (0x0c) - VR0b);
	MCODE(OP0x05_SUBR_PD, (0x0c), R0b, R00),/*(ゼロレジスタ使用)*/
	// (22) VR0b = (VR0b << (8));
	MCODE(OP0x1f_ASLM_PD, (8), R0b, R0b),/*(ショートメモリアドレッシング)*/
	//------------------
	// ---- HATSUDAN_R12_speed_offset			= (t256(1)+(VR0a<<8));/*(テスト)*/
	// (23) VR12 = (VR0a << (8));
	MCODE(OP0x1f_ASLM_PD, (8), R12, R0a),/*(ショートメモリアドレッシング)*/
	// (24) VR12 += (t256(1));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R12, R12),/*(ロングメモリアドレッシング専用命令)*/
	(t256(1)),
	// ---- HATSUDAN_R13_angle65536 			= (((VR09+VR0b))&(65536-1));	/* 角度 */
	// (25) VR13 = VR09;
	MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
	// (26) VR13 += VR0b;			/* 角度 */
	MCODE(OP0x04_ADDR_PD, NAX, R13, R0b),
	// (27)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// ---- HATSUDAN_R13_angle65536 	= (((VR09-VR0b))&(65536-1));	/* 角度 */
	// (28) VR13 = VR0b;
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
	// (29) VR13 = (VR09 + (0x00) - VR13);
	MCODE(OP0x05_SUBR_PD, (0x00), R13, R09),
	// (30)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//bbb+35:
	// (31) (終了)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (30));
}

local SPELL_INIT(47_mima_toge)
{
	VR09	= (t256(1.0));//[定数1]雨の速度
//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[定数2]赤青クナイが曲がる角度
}
