
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	雑魚のカードを定義します。
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //


#if 0
/*---------------------------------------------------------
	アリス(仮)	洗濯機カード
	-------------------------------------------------------
	テキトー
---------------------------------------------------------*/
#define cg_BOSS_DATA_38_angleCCW1024 cg_BOSS_DATA_38_angleCCW65536
local SPELL_EXEC(09_zako_sentakki)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
	{
		cg_BOSS_DATA_38_angleCCW1024 -= (int)(1024/24);
		mask1024(cg_BOSS_DATA_38_angleCCW1024);
	//
		#if 0
			HATSUDAN_R16_n_way					= (8);										/* [8way] */
			HATSUDAN_R17_div_angle65536 		= (int)(65536/24);							/* 分割角度 */
	//
			HATSUDAN_R11_speed256				= (t256(2.0)+((VR10_BOSS_SPELL_TIMER)<<2)); /* 弾速 */
		{
			HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW1024)<<6);				/* 角度 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [青鱗弾] */
			bullet_regist_multi_vector_direct();
		//
			HATSUDAN_R13_angle65536 			= ((-((cg_BOSS_DATA_38_angleCCW1024)<<6))&(65536-1));		/* 角度 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [水鱗弾] */
			bullet_regist_multi_vector_direct();
		}
		#endif
		#if 1
			HATSUDAN_R12_speed_offset			= t256(1);		/* 調整減速弾 */	/* この方式になるか検討中 */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R16_n_way					= (8);										/* [8way] */
			HATSUDAN_R17_div_angle65536 		= (int)(65536/24);							/* 分割角度 */
	//
			HATSUDAN_R11_speed256				= (t256(1.0)+((VR10_BOSS_SPELL_TIMER)<<2)); /* 弾速 */
		{
			int first_angle65536 = ((cg_BOSS_DATA_38_angleCCW1024)<<6);
			HATSUDAN_R13_angle65536 			= (first_angle65536);						/* 角度 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [青鱗弾] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r33-) */
		//
			HATSUDAN_R13_angle65536 			= ((-first_angle65536)&(65536-1));			/* 角度 */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [水鱗弾] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r33-) */
		}
		#endif
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}
#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	[その他] 青小華弾 easy用
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
local SPELL_EXEC(09_test_inuno_fuguri)
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
			// (3) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
			// (4) /
			//	const u32 VR0b = (((~(VR10_BOSS_SPELL_TIMER))>>3)&0x1f);/* テキトーに大きくしてみる。 */
			MCODE(OP0x02_COUNTER, 24, R0b, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (2));//		/*(r34, 32)*/
		#define NUM_05_OF_CIRCLE_ONE	(5)/* 一周(原作は5弾) */
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/NUM_05_OF_CIRCLE_ONE))/* 一周 */
		{
			static const u32 codebase444[22] =
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

			// 速い
			// 逆回り(下CCWだから、右回りCW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* 弾速 */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
				(t256(1)),
			//	HATSUDAN_R13_angle65536 		= (((VR0a)+VR0d) & (65536-1));			/* 発射中心角度 / 特殊機能(自機狙い/他) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [枠付き 青丸弾] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (00) (1弾撃つ)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (00) VR0d += (int)(65536/3);
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0d, R0d),
				((int)(65536/3)),
				// (00) VR03_i--;
				MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
				// (00) if (0 != VR03_i) {goto for_loop_i;}
				MCODE(OP0x08_BNE_RS, (0), R03_i, (u8)(-13)),//(LOOP_contine)
				// (00)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
			};
			cpu_exec((u32*)&codebase444, ((23*2)+8));//
		}
		static const u32 codebase333[8] =
		{
			// 回転量
			// VR09 += (int)(	   (65536/(22)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)(    (65536/(22)))),
			// VR0a += (int)(65536-(65536/(15)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* 角度(65536[360/360度]を 48分割) */
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
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (+1)),//	(ccc+1)
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

