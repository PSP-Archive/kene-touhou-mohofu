
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	射命丸 文のカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	文	通常攻撃1
	-------------------------------------------------------
		赤(12)弾
		青(12)弾
		紫(12)弾
	-------------------------------------------------------
	とりあえず、まったく似てない。
	というか、まったく違う。
	「通常攻撃1」はよくわかんない。ので、色々変えちゃうと思う。
	-------------------------------------------------------
	使用レジスタ
	R02 	j	(ループ変数)
	R03 	i	(ループ変数)
	R06 	受け渡しレジスタ	弾源X座標		発弾位置 座標x
	R07 	受け渡しレジスタ	弾源Y弾源		発弾位置 座標y
	使用レジスタ
	R08 	カウンタ。			(16回に1回) 発弾
	R09 	aaa_angle65536
	R0a 	bbb_angle65536
	R0b 	だんだん大きくなる円の半径。
	R0c 	音用カウンタ。(48回に1回) 発音。
	-------------------------------------------------------
	R0d 	ccc_angle65536		内側iループでの基準角度(0, 32768, 65536)
---------------------------------------------------------*/

local SPELL_EXEC(15_aya_misogi1)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 16, R08, NAX),
		NAX
	};
//	if ((0x08)==(VR10_BOSS_SPELL_TIMER & 0x0f))/* (16回に1回)(16回毎に発弾) */
	cpu_exec((u32*)&codebase111, (1));//	/* (16回に1回)(16回毎に発弾) */
	if (1==VR08) /* (16回に1回) 発弾 */
	{
		static const u32 codebase222[4] =
		{
			// (03) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
			// (04) /
			//	const u32 VR0b = (((~(VR10_BOSS_SPELL_TIMER))>>3)&0x1f);/* テキトーに大きくしてみる。 */
			MCODE(OP0x02_COUNTER, 24, R0b, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (2));//		/*(r34, 32)*/
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* 一周(原作は12弾) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/NUM_12_OF_CIRCLE_ONE))/* 一周 */
		{
			static const u32 codebase444[45] =
			{
				//	VR06 += (sin65536((VR02_j))*(16));			/* 弾源x256 */
				//	VR07 += (cos65536((VR02_j))*(16));			/* 弾源y256 */
				//	VR06 += ((si n65536((VR02_j))*((16+(VR0b)))));/*fps_factor*/	/* 弾源x256 */	/* CCWの場合 */
				//	VR07 += ((co s65536((VR02_j))*((16+(VR0b)))));/*fps_factor*/	/* 弾源y256 */
				//	VR06 += ((si n1024((deg65536to1024(VR02_j)))*((16+(VR0b)))));/*fps_factor*/ 	/* 弾源x256 */	/* CCWの場合 */
				//	VR07 += ((co s1024((deg65536to1024(VR02_j)))*((16+(VR0b)))));/*fps_factor*/ 	/* 弾源y256 */
				// HATSUDAN_R11_speed256	= (t256(12 + VR0b)); //= ((12+(VR0b)) << 8);	/*(r34, 16)*/
				// (00) VR11 = VR0b + (12); 	/* 弾速 */
				MCODE(OP0x01_MOVER_PD, (u8)(+12), R11, R0b), /*(インデックス付)*/
				// (00) HATSUDAN_R11_speed256 = (VR11 << (8));
				MCODE(OP0x1f_ASLM_PD, (8), R11, R11),/*(ショートメモリアドレッシング)*/
				// (00) HATSUDAN_R13_angle65536 = (VR02_j);
				MCODE(OP0x01_MOVER_PD, NAX, R13, R02_j),
				// (00)
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				// (00) VR07 += VR04;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R07, R04),
				// (00) VR06 += VR05;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R06, R05),
				//	NAX/*(終了)*/
				//------------------
				//	VR09 -= ( ((VR07)));	/* 弾速 */
				//	h->center.y256 = (VR06);/*fps_factor*/
				//------------------
				// (00) VR03_i = 2;
				MCODE(OP0x1c_MOVEM_PD, (0x02), R03_i, NAX),/*(ショートメモリアドレッシング)*/
				// (00) VR0d = 1; //VR0d = 0;
				MCODE(OP0x1c_MOVEM_PD, (0x01), R0d, NAX),/*(ショートメモリアドレッシング)*/
			//	for ( ; VR03_i<(65536); )/* 一周 */
			//	for_loop_i: 				;
			// ゆっくり
			// 順回り(下CCWだから、左回りCCW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= (1);//t256(0);/*(大体0)*/ /*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, (0x01), R12, NAX),/*(ショートメモリアドレッシング)*/
			//	HATSUDAN_R13_angle65536 		= (((VR09)+VR0d) & (65536-1));			/* 発射中心角度 / 特殊機能(自機狙い/他) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR09;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R09),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [枠付き青丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (00) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// 速い
			// 逆回り(下CCWだから、右回りCW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.50)),
				// (00) HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
				(t256(1)),
			//	HATSUDAN_R13_angle65536 		= (((VR0a)+VR0d) & (65536-1));			/* 発射中心角度 / 特殊機能(自機狙い/他) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);// 	/* [枠付き 丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_01_AKA)),
				// (00) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// 逆回り(下CCWだから、右回りCW)
			// 紫(テキトー)
				// (00) if (3 != cg_VR20_game_difficulty) {goto LOOP_contine;}
				MCODE(OP0x08_BNE_RS, (3), R20_PLAYER_DATA_game_difficulty, (u8)(+13)),//(LOOP_contine)
				// (00) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= t256(2);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
				(t256(2)),
				// (00) VR0a += (int)((65536/2));	/* 角度(65536[360/360度]を 2分割) */
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
				((int)(65536/2)),
			//	HATSUDAN_R13_angle65536 		= ((VR0a+VR0d) & (65536-1));			/* 発射中心角度 / 特殊機能(自機狙い/他) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI);	/* [枠付き 丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI)),
				// (00) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
				// (00) VR0a += (int)((65536/2));	/* 角度(65536[360/360度]を 2分割) */
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
				((int)(65536/2)),
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (00) VR0d += (int)(65536/2);
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0d, R0d),
				((int)(65536/2)),
				// (00) VR03_i--;
				MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
				// (00) if (0 != VR03_i) {goto for_loop_i;}
				MCODE(OP0x08_BNE_RS, (0), R03_i, (u8)(-35)),//(LOOP_contine)
				// (00)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
			};
			cpu_exec((u32*)&codebase444, ((23*2)+8));//
		}
		static const u32 codebase333[8] =
		{
			// 回転量
			// (00) VR09 += (int)(	   (65536/(22)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)(    (65536/(22)))),
			// (00) VR0a += (int)(65536-(65536/(15)));/* ROTATE_ANGLE */		/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
			((int)(65536-(65536/(15)))),
			// 音用
			//	if ((0x10)==(VR10_BOSS_SPELL_TIMER & 0x1f))/* (32回に1回発音) */
			//	if ((0x40)==(VR10_BOSS_SPELL_TIMER & 0x7f))/* (128回に1回発音) */
			//	/* (8回に1回) ((16x8)==128回に1回発音) */
			MCODE(OP0x02_COUNTER, 3, R0c, NAX), 	/* (2回に1回) ((16x3)==48回に1回発音) */
		//	NAX
			// (55)if (0 != )goto(ccc+2);if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
			// if (0<VR0c) {goto 発音しない;}// ==if (0==VR0c) {発音する。;}// /* (48回に1回) 発音 */ if (1==VR0c)		{	}
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (u8)(+1)),//	(ccc+1)
			// (56)  (cpu_auto_bullet_play_default);
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	(ccc+1:)
			// (57)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
		};
		cpu_exec((u32*)&codebase333, (8));//
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	文	通常攻撃2
	-------------------------------------------------------
	normal
		赤(12)弾	CW弾速速い								右下45度から開始
		青(12)弾	CCW弾速遅い(青弾の2.5倍くらい？)		左下45度から開始
	-------------------------------------------------------
	luna
		赤(12)弾	CW弾速速い								右下45度から開始
		青(12)弾	CCW弾速遅い(青弾の1.5倍くらい？)		左下45度から開始
	-------------------------------------------------------
	(?)。
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。
	R09 	aaa_angle65536
	R0a 	bbb_angle65536
	R0c 	音用カウンタ。(40回に1回) 発音。
---------------------------------------------------------*/

local SPELL_EXEC(23_aya_misogi2)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 8, R08, NAX),
		NAX
	};

//	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (8回に1回 発弾) */
	cpu_exec((u32*)&codebase111, (1));//	/* (8回に1回 発弾) */
	if (1==VR08) /* (8回に1回) 発弾 */
	{
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
//
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* 一周(原作は12弾) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
		for (VR02_j=0; VR02_j<(65536);	VR02_j+=(65536/NUM_12_OF_CIRCLE_ONE))/* 一周 */
		{
			static const u32 codebase555[31/*-1*/] =
			{
				//	VR06 += (sin65536((VR02_j))*(16));			/* 弾源x256 */
				//	VR07 += (cos65536((VR02_j))*(16));			/* 弾源y256 */
				// (01) HATSUDAN_R11_speed256	= (t256(12)); // = ((12)<<8);	/*(r34, 16)*/	/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(((12)<<8)),
				// (02) HATSUDAN_R13_angle65536 = (VR02_j);
				MCODE(OP0x01_MOVER_PD, NAX, R13, R02_j),
				// (03)
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				// (04) VR07 += VR04;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R07, R04),
				// (05) VR06 += VR05;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R06, R05),
				//
			//	VR06 += ((si n1024((deg65536to1024(VR02_j)))*(16)));/*fps_factor*/	/* 弾源x256 */	/* CCWの場合 */
			//	VR07 += ((co s1024((deg65536to1024(VR02_j)))*(16)));/*fps_factor*/	/* 弾源y256 */
			//	NAX/*(終了)*/
				//------------------
			// [ゆっくり]
				// 順回り(下CCWだから、左回りCCW)
				// (06) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.75)),
				// (07) HATSUDAN_R12_speed_offset		= (1);//t256(0);/*(大体0)*/ /*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, (0x01), R12, NAX),/*(ショートメモリアドレッシング)*/
				// (08) VR13 = VR09;	HATSUDAN_R13_angle65536 		= ((VR09) & (65536-1)); 		/* 発射中心角度 / 特殊機能(自機狙い/他) */
				MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
				// (09) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [枠付き青丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (10) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// [速い]
				// 逆回り(下CCWだから、右回りCW)
				// (11) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.50)),
				// (12) HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
				(t256(1)),
				//		HATSUDAN_R13_angle65536 		= ((VR0a) & (65536-1)); 		/* 発射中心角度 / 特殊機能(自機狙い/他) */
				// (13) VR13 = VR0a;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
				// (14) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);// 	/* [枠付き 丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_01_AKA)),
				// (15) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
				// ()
				// 紫(テキトー)
				// (16) if (3 != cg_VR20_game_difficulty) {goto LOOP_contine;}
				MCODE(OP0x08_BNE_RS, (3), R20_PLAYER_DATA_game_difficulty, (u8)(+7)),//(LOOP_contine)
				// 順回り(下CCWだから、左回りCCW)
				// (17) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.75)),
				// (18) HATSUDAN_R12_speed_offset		= t256(3);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
				(t256(3)),
				// (19) VR13 = VR09;	HATSUDAN_R13_angle65536 		= ((VR09) & (65536-1)); 		/* 発射中心角度 / 特殊機能(自機狙い/他) */
				MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
				// (20) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI);	/* [枠付き 丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI)),
				// (21) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (22)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
			};
			cpu_exec((u32*)&codebase555, (21));
		}
		static const u32 codebase333[8] =
		{
			// 回転量
		//	VR09 += (((int)(	  (65536/(22)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
		//	VR0a += (((int)(65536-(65536/(15)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
		//	VR09 += (((int)(	  (65536/(44)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
		//	VR0a += (((int)(65536-(65536/(30)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
			// 回転量が 22分割(但し半周毎, 実質44分割)の場合.
			// (01) VR09 += ((int)( 	  (65536/(44)) + (65536/(2))   ));		/* 角度(65536[360/360度]を 22分割、但し半周毎に描く ==	((65536/44)+(65536/2)) ) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)( 	  (65536/(44)) + (65536/(2))   )),
			// 回転量が 15分割(但し半周毎, 実質30分割)の場合.
			// (02) VR0a += ((int)(65536-( (65536/(30)) + (65536/(2)) ) )); /* 角度(65536[360/360度]を 15分割、但し半周毎に描く == -((65536/30)+(65536/2)) ) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
			((int)(65536-( (65536/(30)) + (65536/(2)) ) )),
			// (03)
			// 音用
			//	if ((0x10)==(VR10_BOSS_SPELL_TIMER & 0x1f))/* (32回に1回) */
			//	if ((0x40)==(VR10_BOSS_SPELL_TIMER & 0x7f))/* (128回に1回) */
			MCODE(OP0x02_COUNTER, 5, R0c, NAX), 	/* (5回に1回) ((8x5)==40回に1回発音) */
		//	NAX
			// (04) if (0 != VR0c) {goto 発音しない。;}// if (0<VR0c) {goto 発音しない。;}// ==if (0==VR0c) {発音する。;}/* (40回に1回) 発音 */ if (1==VR0c)		{	}
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (u8)(+1)),//	(ccc+1)
			// (05)  (cpu_auto_bullet_play_default);
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	(ccc+1:)
			// (06)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
		};
		cpu_exec((u32*)&codebase333, (5));//
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	文	岐符「天の八衢」
	-------------------------------------------------------
	６層x32方向弾
	-------------------------------------------------------
	初期展開時、下側左右22.5/360度[1周/16分割]の範囲は弾がこない。

         /|X
        / | X
       /  |  X
      /   |   X
     /    |    X
    /     |     X
	22.5  | 22.5
	弾がこない範囲 == [1周/16分割] + [1周/16分割]
	原作のスクショから測るとこう。
	-------------------------------------------------------
	だけど、pspだと角度が広く感じる。
	上下切れてる上に(ゲームフィールドが)横広の画面だから、錯視が働くんだろうな。
	錯視(目の錯覚):
	同じ人が縦縞の服と横縞の服を着た場合、縦縞の服の方が(全体が)細く見える。
	同じカードでも左右トリミングしてカットすると、目の錯覚で細く見える。
	同じカードでも上下トリミングしてカットすると、目の錯覚で太く見える。
	この場合(psp)両方同時に働くから、目の錯覚で極端に太く見える。
	-------------------------------------------------------
	だからといって、角度を狭めたり、全体を縮小して調整すると、余計無理ゲに近づく気がする。
	個人的には、「横避(よ)け」が一番やりたかったんだか、pspの画面狭いから、現状(r32)横避(よ)けは無理ゲっぽい。
	横避(よ)けは無理ゲっぽいが、横避(さ)けはできる。
	-------------------------------------------------------
	横避(よ)け:横に張り付きながら、文の体力を削る攻略法。(誘導系以外を想定。誘導系以外で攻撃できる)
	横避(さ)け:単に弾を避(さ)けるだけ、攻撃できない。誘導系なら攻撃できるかも知れないが想定外(現状の模倣風では出来ない)。
	このカードは単に弾を避(さ)けるだけなら簡単。
	-------------------------------------------------------
	現状(r32)では攻略もヘッタくれもなく直ぐ次に変わる。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(aya_danmaku_01_callback)/* 岐符「天の八衢」 */
{
	if (((32*18)-HATUDAN_FRAME64)==((VR0a) ))/* 約0.33[秒](==20[frame])停止 */
	{
		/* ここでは効果音なし */
		/*(弾幕レイヤーグループ(1)を全弾停止。向きを変える。)*/
		src_tama->TR02_hatudan_tra65536 				= t256(0);		/* 調整加速弾 */
		src_tama->TR01_hatudan_speed65536				= t256(0);		/* 弾速 */
	}
	else
	if (((32*18)-HATUDAN_FRAME64-20)==((VR0a) ))/* 止まってから20[frame]後 */ /*(32*17)*/
	{
		/* 移動。 再加速。 */
			/*(弾幕レイヤーグループ(1)を全弾加速させる。)
				-------------------------------------------------------
				加速弾(正確には等加速弾)なのに、加速弾に見えないで、
				等速弾(正確には等速度弾、加速==0)に見えちゃう問題がある。
			*/
		{
			#if 1
			/* 擬似乱数==加算固定値(KOTEITI_AYA_1234) */
		//	#define KOTEITI_AYA_1234 (1234<<6)
		//	#define KOTEITI_AYA_1234 (78976)
			#define KOTEITI_AYA_1234 (7777)
			VR09 += (KOTEITI_AYA_1234);
		//	src_tama->rotationCCW1024				= (ra_nd()&((1024)-1)); 	/* 向き */	/* 向きは乱数でない気がする */
		//	src_tama->rotationCCW1024				= (deg65536to1024(VR09));			/* 向き */
		//	src_tama->rotationCCW1024				= ((((deg65536to1024(VR09))&(512-1))+(256*(4-1)))&(1024-1));		/* 向き(下(180/360[度])にしか落ちない) */
		//	src_tama->rotationCCW1024				= ((((deg65536to1024(VR09))&((256<<6)-1))+((128<<6)*(8-1)))&(65536-1)); 	/* 向き(下( 90/360[度])にしか落ちない) */
			src_tama->rotationCCW65536				= (((((VR09))&((256<<6)-1))+((128<<6)*(8-1)))&(65536-1));		/* 向き(下( 90/360[度])にしか落ちない) */
			#endif
			src_tama->TR02_hatudan_tra65536 		= t256(1);	/* (1) 調整加速弾 */
		/* チルノ(パーフェクトフリーズ)の場合は先に変身するが、文(天の八衢)の場合は後で変身する。 */
			src_tama->obj_type_set							= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);	/* 青丸弾 */
			reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* 弾グラと弾あたり判定を変更する。 */
			/* (通常弾へ変身する) */
			src_tama->TR00_hatudan_spec_data		= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		}
		/* 止まった時よりも、動き始める時に効果音鳴らした方がそれっぽい。 */
		#if (1)
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;/* 効果音: きらりん */
	//	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;/* 効果音: きらりん */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;	CPU_CALL(cpu_voice_play);
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;		CPU_CALL(cpu_voice_play);
		/* 大事な事なので２回言いました。 */
		#endif
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
//	R09 	add_angle
	R0a 	ボスタイマー値、コールバック側に連絡用。(とりあえず)
//	R0b 	再加速の速度用に一時使用。
---------------------------------------------------------*/
local SPELL_EXEC(22_aya_yatimata)
{
	static const u32 codebase_exec[23] =
	{
	// (01) VR0a = (VR10_BOSS_SPELL_TIMER);/*(ボスタイマー値、コールバック側に連絡用。(とりあえず))*/
	MCODE(OP0x01_MOVER_PD, NAX, R0a, R10),
	//----
	// (02) VR03_i = (VR10_BOSS_SPELL_TIMER);
	MCODE(OP0x01_MOVER_PD, NAX, R03_i, R10),
	// (03) VR03_i = VR03_i - (((32*20)-1));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R03_i, R03_i),
	(int)(-(((32*20)-1))),
	// (04) if ((0) != VR03_i)/* 約1.0[秒](==64[frame])全弾を展開 */	{goto ccc_end+17;}
	MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(+17)),//	(ccc_end+17)
	/* 弾生成 */
	// (05) HATSUDAN_R11_speed256			= (t256(0.5));			/* 弾速(pspの画面は狭い) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.5)),
	// (06) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT)),
	// (07) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);		/* 白弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO)),
	//----
	// (08) VR03_i = (6);/* ６層。 */
	MCODE(OP0x1c_MOVEM_PD, (6), R03_i, NAX),/*(ショートメモリアドレッシング)*/
//	bbb_loop-9: 	;
	//		HATSUDAN_R12_speed_offset		= t256(-5); 		/* (-5) (-3)調整減速弾 */	/* この方式になるか検討中 */
	//		HATSUDAN_R12_speed_offset		= t256(-VR03_i);/*(テスト)*/
	//		HATSUDAN_R12_speed_offset		= t256(VR03_i<<2);/* x4倍 てすと*/
	// (09) HATSUDAN_R12_speed_offset		= (VR03_i<<(2+8));/* x4倍 てすと*/
	MCODE(OP0x1f_ASLM_PD, (2+8), R12, R03_i),/*(ショートメモリアドレッシング)*/
	//		HATSUDAN_R13_angle65536 		= (65536/16);			/* 向き */
	// (10) HATSUDAN_R13_angle65536 		= (65536/2);			/* [破壊] */	/* 真上向き */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),
	((65536/2)),
	// (11) HATSUDAN_R16_n_way				= (32); 				/* [破壊] */	/* [32way] */	/* 32方向弾 */
	MCODE(OP0x1c_MOVEM_PD, (32), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (12) HATSUDAN_R17_div_angle65536 	= ((65536-(65536/8))/32);/*(1792)*/ /* [破壊] */	/* 分割角度(弾がこない範囲を除き32分割) */	/* (ra_nd16>>4) == 乱数(0-4095) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
	(((65536-(65536/8))/32)),/*(1792)*/
	// (13) (1弾撃つ)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(42-)*/
	// (14) VR03_i--;
	MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i),/*(インデックス付)*/
	// (15) if (0 != VR03_i) {goto bbb_loop-9;}
	MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-9)),//	(bbb_loop-9)
	// (16)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
//	(ccc_end+17:)
	// (17)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (51));// 51==16+5x7
}

local SPELL_INIT(22_aya_yatimata)
{	// (CLIP_RECT_TYPE_01_UE_YOKO);
	static /*const*/ u32 codebase_init[6] =
	{
	// (01)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// 上に広いタイプ
	CLIP_RECT_01_VR1c,// 上に広いタイプ
	// (02)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上に広いタイプ
	CLIP_RECT_01_VR1d,// 上に広いタイプ
	// (03)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// 上に広いタイプ
	CLIP_RECT_01_VR1e,// 上に広いタイプ
	};
	cpu_exec((u32*)&codebase_init, (3));
}
// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	塞符「山神渡御」(normal)
	塞符「天上天下の照國」(luna)
	-------------------------------------------------------
	ぜんぜん作ってない...
	-------------------------------------------------------
	使用レジスタ
	R08 	bbb カウンタ。
	R09 	[未使用]
	R0a 	一時使用temp。
	R0b 	カウンタ。
	R0c 	zzz カウンタ 難易度別定数。
	-------------------------------------------------------
	R0d 	弾の種類1	cc_type[(cg_VR20_game_difficulty)]
	R0e 	弾の種類2	ba_type[(cg_VR20_game_difficulty)]
---------------------------------------------------------*/

// 4096 == 65536/16
// 3855.05882352941176470588235294118 == 65536/17
//	240.941176470588235294117647058824 == ((65536/16)-(16636/17)) 差分
local SPELL_EXEC(26_aya_saifu)
{
	static const u32 codebase_exec[40] =
	{
	// (01) //	count_up_limit_NUM(R0b, VR0c);
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[レジスタ間接アドレッシング]*/, R0b, R0c/*[難易度別定数]*/),
	// (02) if (0 != VR0b)	{goto (bbb+18);}
	MCODE(OP0x08_BNE_RS, (0), R0b, (u8)(+18)),// (bbb+18)
	// ---- VR0c -= (cg_VR20_game_difficulty);
	// (03) VR0a = cg_VR20_game_difficulty;
	MCODE(OP0x01_MOVER_PD, NAX, R0a, R20_PLAYER_DATA_game_difficulty),
	// (04) VR0a = (VR00 + (0) - VR0a);
	MCODE(OP0x05_SUBR_PD, (0x00), R0a, R00),/*(ゼロレジスタ使用)*/
	// (05) VR0c += VR0a;
	MCODE(OP0x04_ADDR_PD, NAX, R0c, R0a),
//	#define min_24zzz (26)/* (r33) */
//	#define min_24zzz (40)/* (r34)若干弾切れする。 */
	#define min_24zzz (44)/* (r34) */
	// ---- if (min_24zzz > VR0c)	{VR0c = min_24zzz;}
	// (06) if (min_24zzz < VR0c)) {goto qqq+1;}/*(フローしたら分岐。)*/
	MCODE(OP0x09_BFL_RS, (min_24zzz), R0c, (u8)(+1)),// (aaa+1:);	/* フローしたら分岐 */
	// (07) VR0c				= (min_24zzz);
	MCODE(OP0x1c_MOVEM_PD, (min_24zzz), R0c, NAX),/*(ショートメモリアドレッシング)*/
//aaa+1:
	#undef min_24zzz
	// (08) HATSUDAN_R11_speed256			= (t256(0.50)); 	/* 弾速(t256(1.00)) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.50)),
	// (09) HATSUDAN_R12_speed_offset		= t256(1);/*(テストt256(0))*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (10) HATSUDAN_R13_angle65536 		= (0);				/* 発射中心角度 / 特殊機能(自機狙い/他) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),
	(0),
	// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (12) HATSUDAN_R15_bullet_obj_type	= VR0d; 		/*	弾の種類1[ 弾] */
	MCODE(OP0x01_MOVER_PD, NAX, R15, R0d),
	// (13) HATSUDAN_R16_n_way				= (16*5);		/* [80way] */	/*(6)*/ 	/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (16*5), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));	/* 分割角度(65536[360/360度]を 8 分割) */	/* 1周をn分割した角度 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(16*5)),
	// (15)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//bbb+18:
	// ---- VR0a = ((VR10_BOSS_SPELL_TIMER+4)&0x07);/* (2回に1回)(8回毎に発弾) */
	// (16) VR0a = VR10_BOSS_SPELL_TIMER + (4); 	/* 弾速 */
	MCODE(OP0x01_MOVER_PD, (u8)(+4), R0a, R10), /*(インデックス付)*/
	// (17) VR0a = ((VR0a)&0x07);
	MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R0a),/*(ショートメモリアドレッシング)*/
	// (18) if (0 != VR0a)		{goto ddd+16;}		//	if (0==VR0a)	{	}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+16)),// (ddd+16)
	// (19) VR08 += (77);
	MCODE(OP0x01_MOVER_PD, (u8)(+77), R08, R08), /*(インデックス付)*/
	//	//	HATSUDAN_R13_angle65536 		= (int)((65536*3/4))+(VR10_BOSS_SPELL_TIMER&0xff);
	//	//	HATSUDAN_R13_angle65536 		= (int)((65536*1/4))+(VR10_BOSS_SPELL_TIMER&0xff);
	// (20) HATSUDAN_R13_angle65536 		= (VR08);	/* 発射中心角度 / 特殊機能(自機狙い/他) */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R08),
	// (21) VR0a = (VR10_BOSS_SPELL_TIMER & 0x08);
	MCODE(OP0x1d_ANDM_PD, 0x08, R0a, R10),/*(ショートメモリアドレッシング)*/
	// (22) if (0 != VR0a)		{goto 負方向にしない。;}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+1)),//	(ccc+1)
	// (23) HATSUDAN_R13_angle65536 			= -(HATSUDAN_R13_angle65536); VR13 = (VR00 + (0x00) - VR13);
	MCODE(OP0x05_SUBR_PD, (0x00), R13, R00),/*(ゼロレジスタ使用)*/
//ccc+1:
	// (24) HATSUDAN_R11_speed256				= (t256(0.50)); 	/* 弾速(t256(1.00)) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.50)),
	// (25) HATSUDAN_R12_speed_offset			= t256(1);/*(テストt256(0))*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (26) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (27) HATSUDAN_R15_bullet_obj_type = VR0e;	/*	弾の種類2[ 弾] */
	MCODE(OP0x01_MOVER_PD, NAX, R15, R0e),
	// (28) HATSUDAN_R16_n_way					= (16); 	/* [16way] */	/* 発弾数(17) (8) (6) */
	MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (29) HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* 分割角度(65536[360/360度]を 16 分割) */	/* 1周をn分割した角度 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(16)),
	// (30)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//ddd+16:
	// (31)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (30));
}

local SPELL_INIT(26_aya_saifu)
{
	static const u32 codebase_init[11] =
	{
	//	VR0d = cc_type[(cg_VR20_game_difficulty)];//	弾の種類1
	// (01) VR0d = hairetu[VR20_game_difficulty];goto (bbb+16);
	MCODE(OP0x0a_BRA_TABLE, R20_PLAYER_DATA_game_difficulty, R0d, (+4)),
	//	const u32 cc_type[4] =
	(BULLET_MINI8_BASE + TAMA_IRO_05_MIDORI),
	(BULLET_MINI8_BASE + TAMA_IRO_00_SIRO), 		// 塞符「山神渡御」(normal)
	(BULLET_KOME_BASE  + TAMA_IRO_06_KI_IRO),
	(BULLET_KOME_BASE  + TAMA_IRO_06_KI_IRO),		// 塞符「天上天下の照國」(luna)
	//	VR0e = ba_type[(cg_VR20_game_difficulty)];//	弾の種類2
	// (02) VR0e = hairetu[R20_game_difficulty];goto (bbb+16);
	MCODE(OP0x0a_BRA_TABLE, R20_PLAYER_DATA_game_difficulty, R0e, (+4)),
	//	const u32 ba_type[4] =
	(BULLET_KOME_BASE	 + TAMA_IRO_03_AOI),
	(BULLET_KOME_BASE	 + TAMA_IRO_03_AOI),		// 塞符「山神渡御」(normal)
	(BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO),
	(BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO), 	// 塞符「天上天下の照國」(luna)
	//----
	// (03) VR0c = (64);/* 64から始める。 */
	MCODE(OP0x1c_MOVEM_PD, (64), R0c, NAX),/*(ショートメモリアドレッシング)*/
	// [重複]VR0b = 0;
	// (04)
//	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_init, (3));
}
// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	文	危険な種弾カード
	-------------------------------------------------------
	テキトー
---------------------------------------------------------*/
//tern OBJ_CALL_FUNC(add_zako_aya_doll);/* 椛弾 */
extern OBJ_CALL_FUNC(add_zako_aya_doll);/* 文人形カード */
local SPELL_EXEC(0f_aya_doll)
{
	if (50 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_aya_doll(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	雨降り弾
	-------------------------------------------------------
	R09 	[定数1]雨の速度
	//
	R0a 	[未使用]揺れる量。揺れる量 == (揺れる大きさ) x cos(揺れる回転角度)。
	R0b 	揺れる量。揺れる量 == (揺れる大きさ) x sin(揺れる回転角度)。
	//
	//
	R0d 	work x。難易度別。小弾のx位置を保持する為に必要。
	R0e 	揺れる回転角度を保持。
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
---------------------------------------------------------*/

//#define spell_execute_1d_amefuri_test spell_execute_common_amefuri
local SPELL_EXEC(1d_amefuri_test)
{
//	spell_execute_aya_amefuri_oodama(src);
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))	// 16カウントに1回上に8way弾を撃つ
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))	// 64カウントに1回上に8way弾を撃つ
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))	// 16カウントに1回上に1弾を撃つ
	{
	static const u32 codebase999[14] =
	{
	// 揺れる回転角度
	// (01) VR0e += (1234);/*(テキトーに加算)*/
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0e, R0e),
	(1234),/*(テキトーに加算)*/
	//	VR0e &= (0xffff);
	//------------------
	//	[r41]角度弾だけの場合は、問題ないが、ベクトル弾が入る場合、特別な対策が必要。
	//	(r41時点の[たぶんr36ぐらいから])ベクトル弾は、
	//	VR06, VR07 は、 local TAMA_FUNC(common_01_amefuri_callback)で使用しているので破壊できない。
	//------------------
	// (02) HATSUDAN_R11_speed256	= (t256(33.3));/*(揺れる大きさ)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	((t256(33.3))),
	// (03) HATSUDAN_R13_angle65536 = (VR0e);/*(揺れる角度)*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (04) p[VR0a, VR0b] = sincos256(VR11, VR13);
	MCODE(OP0x10_SINCOS256, NAX, R0a, R0b),
	//VR0b	src->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//VR0a	src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//	sincos 破壊レジスタ多いので、予め sincos で VR0b を計算しておく
	//------------------
	//		HATSUDAN_R11_speed256				= t256(0.5)/*VR09*/;// [定数1]雨の速度
	//		HATSUDAN_R11_speed256				= t256(0.45)/*VR09*/;// [定数1]雨の速度
	// (05) HATSUDAN_R11_speed256				= t256(0.33)/*VR09*/;// [定数1]雨の速度
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	((t256(33.3))),
	//		HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
	//		HATSUDAN_R12_speed_offset	= ((ra_nd()&0x07)+1);//t256(0.04)/*(とりあえず)*/
	// (06) HATSUDAN_R12_speed_offset	= ((0)+1);//t256(0.04)/*(とりあえず)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(((0)+1)),
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		//	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	// (07) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT)),
	// (08) HATSUDAN_R15_bullet_obj_type		= BULLET_OODAMA32_00_AOI;/* [青大玉弾] */	/* 弾グラ */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_OODAMA32_00_AOI),/* [青大玉弾] */
	//------------------
	// (09)
//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase999, (8));
	//	for (jj=(0); jj<(8); jj++)
		{
			/* ショット */
		//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((0	 )&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (jj<<(10));
			#if 0
		//	HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(10-4));
		//	VR13 += (65536/4)+(65536/8)+(65536/16);
		//	VR13 += (VR0b);
		//	HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(8-4));
		//	VR13 += (65536/4)+(65536/8)+(65536/16)+(65536/32);
		//	VR13 += (VR0b);
			HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(6-4));
			VR13 += (int)((65536/4)+(65536/8)+(65536/16)+(65536/32)+(65536/64)+(65536/128));
			VR13 += (VR0b);
			#endif
			HATSUDAN_R13_angle65536 			= (0);
			VR13 += (int)((65536/2));
		//	VR13 += (VR0b<<4);
			VR13 += (VR0b);
			//
//	//		HATSUDAN_R16_n_way					= (8);
//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
//	spell_execute_aya_amefuri_kodan(src);
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))	// 4カウントに1回上に8way弾を撃つ
	{
			HATSUDAN_R11_speed256				= VR09;// [定数1]雨の速度
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);	/* 弾グラ */	/* [白米弾] */
		int jj;
		jj = (8);/*(x位置)*/
		{
		loop_oodama:
			VR0d -= cg_VR20_game_difficulty;// jj は x位置なので変えると位置が偏る。そこで間引く。
			if (1 > VR0d)
			{
				VR0d += (3);
				#if 0
				/* ショット */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 				= (int)(65536/64);
				HATSUDAN_R17_VECTOR_leg acy_dan_delta256	= ((ra_nd()&0x03)+2);//t256(0.04)
				bul let_reg ist_leg acy_vec tor_dir ect();
				#else
				/* ショット */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			//	HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
				/*(とりあえず)*/HATSUDAN_R12_speed_offset			= ((ra_nd()&0x07)+1);//t256(0.04)
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
	//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
				//
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				#endif
			}
			jj--;
			if ((0) < jj) {goto loop_oodama;}
		}
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
#if 1
//	#define spell_init_1d_amefuri_test spell_init_12_com mon_amefuri
local SPELL_INIT(1d_amefuri_test)
{
//	in it_00_bullet_clip_type(CLIP_RECT_TYPE_03_UE_WIDE);/*(特殊)*/
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[定数1]雨の速度
//	/*(とりあえず)*/VR09	= (t256(1.5)+((0)<<6));//[定数1]雨の速度
//	/*(とりあえず)*/VR09	= (t256(1.5)+((0)<<6));//[定数1]雨の速度
	//	cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & ((1<<difficulty)-1) );
	static /*const*/ u32 codebase_init[6] =
	{
	// (01) (CLIP_RECT_TYPE_03_UE_WIDE);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上にもっと広いタイプ
	CLIP_RECT_03_VR1d,// 上にもっと広いタイプ
	// ----
	// (02) VR0d = 難易度別定数1	(nan_ido);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(0x00, 0x1f, 0x3f, 0x5f),
	// (03) VR09 = t256(1.0) + VR09;//[定数1]雨の速度
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
	(t256(1.0)),
//	// (04) VR0a = 難易度別定数2
//	//	VR0a	= ((65536/2)+(65536/24)+(cg_VR20_game_difficulty<<(3+6)));//[定数2]赤青クナイが曲がる角度
//	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
//	PACK_NAN_IDO_CONST((0), (8), (16), (24)),
//	// (05)
//	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
//	((65536/2)+(65536/24)),
	};
	cpu_exec((u32*)&codebase_init, (3));
//	VR0c = (0);/*[ゼロページは必ず0クリアされるので省略可能](小弾のx位置を保持する為に必要。)*/
//	VR0e = (0);/*[ゼロページは必ず0クリアされるので省略可能](揺れる回転角度を保持。)*/
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[定数1]雨の速度
}
#endif
// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	文 台風形態
	-------------------------------------------------------
	VR0f_AYA_LINK		攻撃タイプ
	-------------------------------------------------------
	AYA_LINK_00_NONE	攻撃タイプ00: 攻撃しない。;
		攻撃しない場合(AYA_LINK_00_NONE == VR0f_AYA_LINK)は移動更新もしない。
		攻撃した場合(AYA_LINK_00_NONE != VR0f_AYA_LINK)は、
		新たな次の目標を設定する。
	-------------------------------------------------------
	AYA_LINK_01_RENDAN	攻撃タイプ01: 米連弾;
		正確に狙ってくる米連弾。ちょん避けでＯＫ。
		[r42]単色に変更。
	-------------------------------------------------------
	AYA_LINK_02_FUDADAN 攻撃タイプ02: 後追い札弾;
		さりげなくばら撒く札弾。さりげなく嫌。
	-------------------------------------------------------
	AYA_LINK_03_OODAMA	攻撃タイプ03: 大玉弾;
		結構狙ってくる大玉弾。速度が違うので嫌な感じ。
---------------------------------------------------------*/

local void s_aya_kougeki_all_void(void)
{
	// (r35でカードの場合のみ省略可能)	/* 弾源x256 y256 中心から発弾。 */
	/* 弾源x256 y256 中心から発弾。 */
	CPU_CALL(calculate_boss_to_jiki_nerai);
	#if 0/*(r35のシステムでは、省略可能)*/
	HATSUDAN_R13_angle65536 			= (HATSUDAN_R13_angle65536);	/* [破壊] */
	#endif
	//
//	if (AYA_LINK_00_NONE==VR0f_AYA_LINK)	/*[攻撃タイプ00: 攻撃しない。]*/
//	{
//	}
//	else
	if (AYA_LINK_01_RENDAN==VR0f_AYA_LINK)	/*[攻撃タイプ01: 米連弾]*/
	{
		/* 毎回 */
		static const u32 codebase_exec111[16] =
		{
			// (01) AUDIO_18_voice_number		= VOICE11_BOSS_KIRARIN;
			MCODE(OP0x1c_MOVEM_PD, (VOICE11_BOSS_KIRARIN), R18, NAX),/*(ショートメモリアドレッシング)*/
			// (02) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;/*テキトー*/
			MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(ショートメモリアドレッシング)*/
			// (03)  (cpu_voice_play);
			MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
			// (04) HATSUDAN_R12_speed_offset	= t256(1.0);/* ？ */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(t256(1.0)),
			// (05) HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			//	VR04 = ((cg_game_dif ficulty)<<6)+t256(4.50);/*(aya_speed)*/
			#if 0
			easy	0	  0+1152 1152  t256(4.50) t256(4.50)	// 3.5だとeasyが難しすぎる。 t256(3.5)
			normal	1	 64+1152 1216  t256(4.75) t256(4.50)
			hard	2	128+1152 1280  t256(5.00) t256(4.75)
			luna	3	192+1152 1344  t256(5.25) t256(4.00)
			#endif
			// (06) VR04 = ([難易度別定数]);	VR04 = PACK_NAN_IDO_CONST((u8)(4.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4));
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(4.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4)), 	// 4==2^2, 6+2==8==t256()
			PACK_NAN_IDO_CONST((u8)(2.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4)), 	// 4==2^2, 6+2==8==t256()
			// (07) VR04 <<= (6);/*(aya_speed)*/											// 4==2^2, 6+2==8==t256()
			MCODE(OP0x1f_ASLM_PD, (6), R04, R04),/*(ショートメモリアドレッシング)*/
			// (08) VR05		= (HATSUDAN_R13_angle65536);	/* [破壊] */
			MCODE(OP0x01_MOVER_PD, NAX, R05, R13),
			// HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE) + (/*ra_nd()*/(HATSUDAN_R13_angle65536>>8) & 0x0f);	/* 弾グラ */
			// (09) VR15 = VR13;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R13),
			// (10) VR15 >>= (8);
			MCODE(OP0x1e_ASRM_PD, (8), R15, R15),/*(ショートメモリアドレッシング)*/
			// (11) VR15 &= (0x0f);
			MCODE(OP0x1d_ANDM_PD, (0x0f), R15, R15),/*(ショートメモリアドレッシング)*/
			// (12) VR15 += (BULLET_KOME_BASE);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			(BULLET_KOME_BASE), 	/* 弾グラ */
		};
		cpu_exec((u32*)&codebase_exec111, (12));
		//
		for (VR03_i=0; VR03_i<(8+cg_VR20_game_difficulty); VR03_i++)
		{
			VR04 -= (t256(0.125));
			HATSUDAN_R11_speed256			= (VR04);			/* 弾速 */
			HATSUDAN_R13_angle65536 		= (VR05);			/* [破壊] */
			HATSUDAN_R16_n_way				= (11-VR03_i);		/* [破壊] */	/* [10way] */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/24);	/* [破壊] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
	else
	if (AYA_LINK_02_FUDADAN==VR0f_AYA_LINK) /*[攻撃タイプ02:	後追い札弾]*/
	{	/*(札弾は意図的に遅くする)*/
		static const u32 codebase_exec222[14] =
		{
			//	HATSUDAN_R11_speed256			= (t256(2.0)+((cg_VR20_game_difficulty)<<8));	/* 弾速 */	/*t256(5.0)*/
			//	HATSUDAN_R11_speed256			= (t256(1.5)+((cg_VR20_game_difficulty)<<4));	/* 弾速 */	/*t256(5.0)*/
			#if 0
			easy	0	t256(1.5000==1.50+0.0000) == (24<<4)
			normal	1	t256(1.5625==1.50+0.0625) == (25<<4)
			hard	2	t256(1.6250==1.50+0.1250) == (26<<4)
			luna	3	t256(1.6875==1.50+0.1875) == (27<<4)
			#endif
			// (01) //	VR11 = ([難易度別定数]);
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R11, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(1.5000*16), (u8)(1.5625*16), (u8)(1.6250*16), (u8)(1.6875*16)), 	// 16==4^2, 4+4==8==t256()
			PACK_NAN_IDO_CONST((u8)(2.0000*16), (u8)(1.5625*16), (u8)(1.6250*16), (u8)(1.6875*16)), 	// 16==4^2, 4+4==8==t256()
			// (02) VR11 <<= (4);/*(aya_speed)*/														// 16==4^2, 4+4==8==t256()
			MCODE(OP0x1f_ASLM_PD, (4), R11, R11),/*(ショートメモリアドレッシング)*/
			// (03) HATSUDAN_R12_speed_offset		= t256(1.0);/* ？ */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(t256(1.0)),
			// (04) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			//	HATSUDAN_R15_bullet_obj_type	= BULLET_KOME_BASE + (ra_nd()&0x0f);	/* 弾グラ */
			//	HATSUDAN_R15_bullet_obj_type	= (BULLET_OFUDA12_00_AOI) + (VR0a); 	/* 弾グラ */
			// (05) VR15 = VR0a + (BULLET_OFUDA12_00_AOI);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R0a),
			(BULLET_OFUDA12_00_AOI),	/* 弾グラ */
			// (06) HATSUDAN_R16_n_way = ([難易度別定数]);		/* [破壊] */	/* [5way] */
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R16, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((5), (5), (7), (7)),
			// (07) HATSUDAN_R17_div_angle65536 	= (65536/12);	/* [破壊] */	/* 12分割 == (30/360)[度] */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
			((65536/12)),
			// (08)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
		};
		cpu_exec((u32*)&codebase_exec222, (8));
	}
	else
//	if (AYA_LINK_03_OODAMA==VR0f_AYA_LINK)	/*[攻撃タイプ03:	大玉弾]*/
	{	/*(連弾より若干遅くする)*/
		static const u32 codebase_exec333[16] =
		{
			//	HATSUDAN_R11_speed256			= speed256; 			/* 弾速 */
			//	HATSUDAN_R11_speed256			= (t256(4.0)-((cg_VR20_game_difficulty)<<7));	/* 弾速 */
			//	HATSUDAN_R11_speed256			= (t256(3.5)-((cg_VR20_game_difficulty)<<6));	/* 弾速 */
			#if 0
			easy	0	t256(3.50)
			normal	1	t256(3.25)
			hard	2	t256(3.00)
			luna	3	t256(2.75)
			#endif
			// (01) //	VR11 = ([難易度別定数]);
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R11, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(3.50*4), (u8)(3.25*4), (u8)(3.00*4), (u8)(2.75*4)), 	// 4==2^2, 6+2==8==t256()
			PACK_NAN_IDO_CONST((u8)(3.00*4), (u8)(3.25*4), (u8)(3.00*4), (u8)(2.75*4)), 	// 4==2^2, 6+2==8==t256()
			// (02) VR11 <<= (6);/*(aya_speed)*/											// 4==2^2, 6+2==8==t256()
			MCODE(OP0x1f_ASLM_PD, (6), R11, R11),/*(ショートメモリアドレッシング)*/
			// (03) HATSUDAN_R12_speed_offset		= t256(-2);/* 減速弾？ */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(-(t256(2.0))),
			// (04) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT)),
			// HATSUDAN_R15_bullet_obj_type = (BULLET_OODAMA32_00_AOI) + ((HATSUDAN_R13_angle65536>>8) & 0x03); 	/* 弾グラ */
			// (05) VR15 = VR13;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R13),
			// (06) VR15 >>= (8);
			MCODE(OP0x1e_ASRM_PD, (8), R15, R15),/*(ショートメモリアドレッシング)*/
			// (07) VR15 &= (0x03);
			MCODE(OP0x1d_ANDM_PD, (0x03), R15, R15),/*(ショートメモリアドレッシング)*/
			// (08) VR15 += (BULLET_OODAMA32_00_AOI);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			(BULLET_OODAMA32_00_AOI),	/* 弾グラ */
			// (09) HATSUDAN_R16_n_way = PACK_NAN_IDO_CONST((12), (14), (16), (20));	/* [12way] */
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R16, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((12), (14), (16), (20)),
			// (10)  (div65536);/*[初期化セクション以外では速度低下の可能性あり]*/	(65536/12); 	/* 12分割 == (30/360)[度] */
			MCODE(OP0x17_DIV65536, NAX, R17, R16),// HATSUDAN_R17_div_angle65536  = 65536 / VR04_NAN_IDO_DECODE;
			// (11)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		};
		cpu_exec((u32*)&codebase_exec333, (11));
	}
}
local SPELL_EXEC(48_aya_taifu)
{
	if (AYA_LINK_00_NONE != VR0f_AYA_LINK)
	{
		s_aya_kougeki_all_void();
		VR0f_AYA_LINK = AYA_LINK_00_NONE;
		/* 移動座標を決める */
		boss_set_new_position_from_target();/*(誘導移動座標をターゲットから設定)*/
	}
}
