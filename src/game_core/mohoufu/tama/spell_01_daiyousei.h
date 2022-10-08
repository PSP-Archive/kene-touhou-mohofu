
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	大妖精のカードを定義します。
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅2面中-ボス 大妖精 通常攻撃1(1/3)
	-------------------------------------------------------
緑クナイ弾
下から始めて、時計回り、2段づつ
	-------------------------------------------------------
	紅2面中-ボス 大妖精 通常攻撃1(2/3)
	-------------------------------------------------------
赤クナイ弾
下から始めて、反時計回り、2段づつ
メモ:Lunaticも一応同じ48方向弾。(4ヶ所から出て2段?3段に整列?)
	-------------------------------------------------------
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。
	R09 	aaa_temp_angleCCW65536
	R0a 	bbb
	R0b 	HATSUDAN_R16_n_way			[破壊]
	R0c 	HATSUDAN_R17_div_angle65536 [破壊]

	R0d 	弾色
	R0e 	弾加算角度
	-------------------------------------------------------
	VR03_i	ループ用 i (難易度別に残り回数を設定。)
---------------------------------------------------------*/

local SPELL_EXEC(1a_1b_dai_yousei_midori_aka)
{
	static const u32 codebase[2] =
	{
		MCODE(OP0x02_COUNTER, 64, R08, NAX),
		NAX
	};
//	if ((64-(48))<((src->boss_spe ll_timer)))
	cpu_exec((u32*)&codebase, (1));
	if (16 < (VR08))
	{
	//	if (0x00==((src->boss_spe ll_timer)&(2-1)))/*(2回に1回)*/
		{
			static const u32 codebase222[8] =
			{
				// (1) HATSUDAN_R12_speed_offset		= t256(1.0);/*(テスト)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
				(int)(t256(1.0)),
				// (2) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
				(int)((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
				// (3)	HATSUDAN_R16_n_way = PACK_NAN_IDO_CONST((12), (14), (16), (20));	/* [12way] */
				MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
				PACK_NAN_IDO_CONST((1), (1), (4), (4)),
				// (4) VR0c 	= (int)(65536/(VR0b));			/* 分割角度(65536[360/360度]を VR0b 分割) */	/* 1周をn分割した角度 */
				MCODE(OP0x17_DIV65536, NAX, R0c, R0b),// R0c = 65536 / R0b;/*(分割角、紅色)*/	/* 分割角度 */
				// (5)	HATSUDAN_R15_bullet_obj_type	= (VR0d);	/* [ 弾] */
				MCODE(OP0x01_MOVER_PD, NAX, R15, R0d),// 弾色
			//	NAX
			};
			cpu_exec((u32*)&codebase222, (5));
		//	for (VR03_i=0; VR03_i<(1+(unsigned)cg_VR20_game_difficulty); VR03_i++)/*(2段づつ)*/
			VR03_i = cg_VR20_game_difficulty;// (難易度別に残り回数を設定。)
		loop_i:
			{
				static const u32 codebase_exec333[9] =
				{
					// HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a<<2)+(VR03_i<<6));			/* 弾速 */
					// (1) VR16 = (VR03_i << (6));
					MCODE(OP0x1f_ASLM_PD, (6), R16, R03_i),/*(ショートメモリアドレッシング)*/
					// (2) VR11 = (VR0a << (2));
					MCODE(OP0x1f_ASLM_PD, (2), R11, R0a),/*(ショートメモリアドレッシング)*/
					// (3) VR11 += VR16;
					MCODE(OP0x04_ADDR_PD, NAX, R11, R16),
					// (4) VR11 += (t256(0.6));
					MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
					(t256(0.6)),	/* 弾速 */
					// (5)	HATSUDAN_R13_angle65536 		= (VR09);
					MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
					// (6)	HATSUDAN_R16_n_way				= (VR0b);
					MCODE(OP0x01_MOVER_PD, NAX, R16, R0b),
					// (7)	HATSUDAN_R17_div_angle65536 	= (VR0c);
					MCODE(OP0x01_MOVER_PD, NAX, R17, R0c),
					// (8)	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
					MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
				};
				cpu_exec((u32*)&codebase_exec333, (8));
			}
			VR03_i--;/*(残り回数減らす。)*/if (0 < VR03_i) {goto loop_i;}/*(残り回数があればループ。)*/
			VR09 += (VR0e);
			VR0a++;
		}
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_INIT(1a_dai_yousei_midori)
{
	VR09 = 0;
	VR0a = 0;
	VR0d = (BULLET_KUNAI12_BASE + TAMA_IRO_05_MIDORI);
	VR0e = (-(65536/48));
}
local SPELL_INIT(1b_dai_yousei_aka)
{
	VR09 = 0;
	VR0a = 0;
	VR0d = (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);
	VR0e = (65536/48);
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅2面中-ボス 大妖精弾
	9方向青弾 + 9方向ちょっと経ったら自機狙い白弾
	-------------------------------------------------------
	⑨方向。90度くらい。
	連弾と一定速度まで進むと自機狙い弾のミックス。
---------------------------------------------------------*/
local TAMA_FUNC(dai_yousei_danmaku_01_callback)/*  */
{
//	if (cnt < 80)/* 80未満は減速 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) < src_tama->jyumyou)/* 発弾エフェクト後から[32]カウント未満の弾 */
	{
		/*(何もしない[通常弾と同じ])*/;
	}
	else
	{
		/* 32 カウントなら、自機狙い弾に変身する。 */
		set_REG_DEST_XY(src_tama);			/* 弾源x256 y256 弾obj中心から発弾。 */
		CPU_CALL(calculate_jiki_nerai);/* 自機狙い角作成 */
		src_tama->tmp_angleCCW65536 = ((HATSUDAN_R13_angle65536));
		src_tama->rotationCCW65536 = ((src_tama->tmp_angleCCW65536)); /* 表示角度 */
		//------------------
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	}
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	-------------------------------------------------------
	VR0c	自機狙い角 退避用
---------------------------------------------------------*/
local SPELL_EXEC(0d_dai_yousei_9_shot)
{
	static /*const*/ u32 codebase_exec[34] =
	{
	//	if (100 < (VR10_BOSS_SPELL_TIMER & 0x7f)) {return;}
	/* VR11, [破壊]*/
	// (1) VR11 = VR10 & 0x7f;
	MCODE(OP0x1d_ANDM_PD, 0x7f, R11, R10),/*(ショートメモリアドレッシング)*/
	// (2) if (100 < VR11)) {goto qqq_4+26;}/*(フローしたら分岐。)*/
	MCODE(OP0x09_BFL_RS, (100), R11, (u8)(+31)),// (qqq_4+31:); 	/* 初めの 28[frame]はお休み */
	//------------------
	// (3)	//	VR04 = [];
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST((19), (15), (11), ( 7)),
	// (4)	//	count_up_limit_NUM(R08, VR04);
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[レジスタ間接アドレッシング]*/, R08, R04/*[難易度別定数]*/),
	// (5)	if (0 != VR08)	{return;}
	MCODE(OP0x08_BNE_RS, (0), R08, (u8)(+27)),// (qqq_4+27)
	/*(ボススペカの場合のみ省略可能、中ボスの場合省略できない)*/
	/* 弾源x256 y256 中心から発弾。 */
	// 自機狙い角作成。
	// (6)	(calculate_boss_to_jiki_nerai);/* 自機狙い角作成 */ /* 弾源x256 y256 ボスの中心から発弾。 */
	MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	// (7) VR0c 		= (HATSUDAN_R13_angle65536) */
	MCODE(OP0x01_MOVER_PD, LONG_MEMORY_ADDRESSING, R0c, R13),// 退避: stack(VR0c) = VR13;
	/*----[ 狙い弾 ]----*/
	/* VR11, VR12[破壊]*/
	// (8) VR11 = (cg_VR20_game_difficulty << 6);
	MCODE(OP0x1f_ASLM_PD, (6), R11, R20_PLAYER_DATA_game_difficulty),/*(ショートメモリアドレッシング)*/
	// (9) HATSUDAN_R11_speed256			+= (t256(2.0));//(t256(3.0));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
	(t256(2.0)),
	// (10) HATSUDAN_R12_speed_offset		= t256(3/*6*/);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(3/*6*/)),/*(テスト)*/
	//	HATSUDAN_R13_angle65536 		= ((HATSUDAN_R13_angle65536));
	//	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT)),
	// (12) HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE + TAMA_IRO_03_AOI);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
	// (13) HATSUDAN_R16_n_way				= (9);
	MCODE(OP0x01_MOVER_PD, (u8)(+9), R16, NAX),/*(インデックス付)*/
	// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/24);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/24),
	// (15)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	/*----[ 直進弾 ]----*/
	// (16) HATSUDAN_R13_angle65536 		= (VR0c) */
	MCODE(OP0x01_MOVER_PD, LONG_MEMORY_ADDRESSING, R13, R0c),// 復旧: VR13 = stack(VR0c);
	// (17) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_0000_TILT)),
	// (18) HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE + TAMA_IRO_03_AOI);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_KOME_BASE + TAMA_IRO_00_SIRO)),
	// (19) HATSUDAN_R16_n_way				= (9);
	MCODE(OP0x01_MOVER_PD, (u8)(+9), R16, NAX),/*(インデックス付)*/
	// (20) HATSUDAN_R17_div_angle65536 	= (int)(65536/24);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/24),
	// (21)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	/*--------*/
	// (22) AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* テキトー */
	MCODE(OP0x1c_MOVEM_PD, TRACK04_TEKIDAN, R19, NAX),/*(ショートメモリアドレッシング)*/
	// (23) AUDIO_18_voice_number	= VOICE15_BOSS_KOUGEKI_01;
	MCODE(OP0x1c_MOVEM_PD, VOICE15_BOSS_KOUGEKI_01, R18, NAX),/*(ショートメモリアドレッシング)*/
	// (24)  (cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
// (qqq_4+27:) (qqq_4+31:)
	// (25)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (24));/* テキトー */
}
// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅4面中-ボス 小悪魔 通常攻撃1
	-------------------------------------------------------
	紫大玉弾。8方向。1/24ずつ反時計回りに回転。
	青クナイ弾。バラマキ。
	-------------------------------------------------------
	紫大玉弾。は無いので代わりに青大玉弾で。
	-------------------------------------------------------
	ちょっと休んで、次は逆周り（作ってない）
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。
	R09 	角度1調整用。
	R0a 	乱数。
	R0b 	乱数加算角(テキトー)
---------------------------------------------------------*/
local SPELL_EXEC(1f_koakuma)
{
//	if (64 == VR10_BOSS_SPELL_TIMER) /* 始めに初期化 */
	static const u32 codebase_exec[45] =
	{
	// (1) counter(192, VR08);
	MCODE(OP0x02_COUNTER, 192, R08, NAX),	/*	繰り返しカウンタ。 */
	// (2) if (1 != VR08) {goto aaa+9:}/* 始めに初期化 */
	MCODE(OP0x08_BNE_RS, (1), R08, (u8)(+9)),// (aaa+9)
	// (3) VR09 = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R09, NAX),//
	(0),
	// (4) VR0a = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R0a, NAX),//
	(0),
	// (5) VR0b = 0;
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R0b, NAX),//
	(0),
	// (6) AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"ボス溜め1",		/* r	うぃーん音 */
	MCODE(OP0x1c_MOVEM_PD, (VOICE17_BOSS_TAME01), R18, NAX),/*(ショートメモリアドレッシング)*/
	// (7) AUDIO_19_voice_truck = TRACK03_IVENT_DAN;
	MCODE(OP0x1c_MOVEM_PD, (TRACK03_IVENT_DAN), R19, NAX),/*(ショートメモリアドレッシング)*/
	// (8)	(cpu_voice_play);
	MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
// (aaa+9:)
	//	if (0 != (VR08 & 0x0f) ) {goto bbb;}/* 16回に1回なら撃つ */
	// (9) VR11 = (VR08 & 0x0f);
	MCODE(OP0x1d_ANDM_PD, 0x0f, R11, R08),/*(ショートメモリアドレッシング)*/
	// (10)
	MCODE(OP0x08_BNE_RS, (0), R11, (u8)(+16)),// (bbb+16)
	// (11) HATSUDAN_R11_speed256			= (t256(1.0));			/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(1.0)),
	//	HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
	// (12) HATSUDAN_R12_speed_offset		= t256(5);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(5)),
	// (13) HATSUDAN_R13_angle65536 		= (VR09);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
	// (14) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
	// (15) HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI); 	/* [青大玉弾] 紫無いから */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_OODAMA32_00_AOI),
	// (16) HATSUDAN_R16_n_way				= (8);							/* 発弾数 */
	MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(ショートメモリアドレッシング)*/
	// (17) HATSUDAN_R17_div_angle65536 	= (int)(65536/(8)); 			/* 分割角度(65536[360/360度]を 8 分割) */	/* 1周をn分割した角度 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(8)),
	// (18)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
	// (19) VR09 += ((65536/24)-256);	/* 平均(1周/24)を足す。(+-256乱数を足す) */
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),/*(ロングメモリアドレッシング専用命令)*/
	(((65536/24)-256)),
	// (20) VR09 += (VR0b); 	/* 乱数加算角 */
	MCODE(OP0x04_ADDR_PD, NAX, R09, R0b),
// (bbb+16:)
	// (21)if (0 != (VR08 & 0x01) ) {goto ccc;} /* 2回に1回なら撃つ */
	// (21) VR11 = (VR08 & 0x01);
	MCODE(OP0x1d_ANDM_PD, 0x01, R11, R08),/*(ショートメモリアドレッシング)*/
	// (22)
	MCODE(OP0x08_BNE_RS, (0), R11, (u8)(+13)),// (ccc+13)
	// (23) HATSUDAN_R12_speed_offset		= t256(1.5);/*(テスト)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
	(t256(1.5)),/*(テスト)*/
	// (24) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (25) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI);			/* [白米弾] */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI),
	// (26) HATSUDAN_R11_speed256			= (t256(1.0));		/* 弾速 */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
	(t256(1.0)),
	// (27) VR0a = ra_nd();
	MCODE(OP0x15_RAND_VALUE, NAX, R0a, NAX),
	// (28) VR0b = VR0a & 0x01ff;/*(0 ... 511)*/
	MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0a),
	(0x01ff),/*(0 ... 511)*/
	// (29) HATSUDAN_R13_angle65536 		= (VR0a);
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
	// (30) (1弾撃つ)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
// (ccc+13:)
	// (31)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (30));//
}
