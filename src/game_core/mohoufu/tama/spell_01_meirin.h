
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	美鈴のカードを定義します。
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅3面中ボス 紅美鈴
	通常攻撃1(1/2)
	16方位偏り全方位ばら撒き弾
	-------------------------------------------------------
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅3面中ボス 紅美鈴
	華符「芳華絢爛」
	時計回り、反時計回りの6way螺旋弾(黄色)		1回毎に(65536/(6*8))[65536/65536度]回転
	48方位全方位弾(赤色)						8回毎に発弾
	-------------------------------------------------------
	芳華絢爛
	解像度とか速度とかの要因で、そのままでは pspで難しい気もする。
	Lunatic はこのままで、Hard 以下は細工して易しくする。
	-------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	条件 temp			一時使用[発弾判定]
	R0a 	aaa_angle65536		現在の回転角度を保持
	R0b 	難易度別定数1(分割数、黄色)
	R0c 	難易度別定数2(分割角、黄色)
	R0d 	難易度別定数3(分割数、紅色)
	R0e 	難易度別定数4(分割角、紅色)
---------------------------------------------------------*/

local SPELL_EXEC(0a_houka_kenran)
{
	static const u32 codebase_exec[34] __attribute__((aligned(16))) =
	{
		// (01) 条件 VR09 = (VR10_BOSS_SPELL_TIMER & 0x7f);/* (16回に1回)(128なら計8回) */
		MCODE(OP0x1d_ANDM_PD, 0x7f, R09, R10),/*(ショートメモリアドレッシング)*/
		// (02) if (0x40 != VR09) {goto aaa+13;/*(発弾しない)*/}
		MCODE(OP0x08_BNE_RS, (0x40), R09, (+13)),// (aaa+13):
		// (03) (calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),	/* 弾源x256 y256 ボスの中心から発弾。 */
		// (04) HATSUDAN_R11_speed256			 = (t256(1.75));	 /* 弾速 */  /* 3.5 2.5 2.0 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(0.66)),// 赤弾の方が1.5倍くらい遅い	(t256(1.75)),
		// (05) HATSUDAN_R12_speed_offset		 = t256(0);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(1)),//(t256(0)),
		// (06) HATSUDAN_R14_tama_spec		 = (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		(DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT),
		// (07) HATSUDAN_R15_bullet_obj_type	 = (BULLET_KOME_BASE + TAMA_IRO_01_AKA);	 /* [赤色米弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		(BULLET_KOME_BASE + TAMA_IRO_01_AKA),
		// (08) HATSUDAN_R16_n_way			 = VR0d;/*(分割数、紅色)*/	 /*(分割角、紅色)*/  /*(48)*/	 /* [48way] */	 /* 発弾数 */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
		// (09) HATSUDAN_R17_div_angle65536  = VR0e;/*(分割角、紅色)*/	 /*(分割数、紅色)*/  /*(int)(65536/(48))*/	 /* 分割角度(65536[360/360度]を 48 分割) */  /* 1周をn分割した角度 */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
		// (10)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (11) (cpu_auto_bullet_play_default);/* 本家はきこきこ音 */
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	(aaa+13):
		// (12) 条件 VR09 = (VR10_BOSS_SPELL_TIMER & 0x0f);/* (2回に1回)(8回毎に発弾) */
		MCODE(OP0x1d_ANDM_PD, 0x0f, R09, R10),/*(ショートメモリアドレッシング)*/
		// (13) if (0x08 != VR09) {goto bbb+16;/*(発弾しない)*/}
		MCODE(OP0x08_BNE_RS, (0x08), R09, (+16)),// (bbb+16)
		// (14) HATSUDAN_R11_speed256		= (t256(1.75)); 	/* 弾速 */	/*3.5 2.5 2.0*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(1.33)),	//(t256(1.75))
		// (15) HATSUDAN_R12_speed_offset	= t256(0);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(3)),//(t256(0)),
		// (16) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		(DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT),
		// (17) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_06_KI_IRO);	/* [黄色米弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		(BULLET_KOME_BASE + TAMA_IRO_06_KI_IRO),
		// (18) HATSUDAN_R16_n_way				= VR0b;/*(分割数、黄色)*/	/*(6)*/ 	/* [1way] */	/* 発弾数 */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0b),
		// (19) HATSUDAN_R17_div_angle65536 	= VR0c;/*(分割角、黄色)*/	/*(int)(65536/(6))*/ /* 分割角度(65536[360/360度]を 6 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0c),
		//	// 順回り(下CCWだから、左回りCCW)
		//	HATSUDAN_R13_angle65536 			= ((/*0+*/(VR0a))&(65536-1));	/* 発射中心角度 / 特殊機能(自機狙い/他) */
		// (20) VR13 = VR0a;// & (65536-1);
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
		// (21)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// 逆回り(下CCWだから、右回りCW)
	//	HATSUDAN_R13_angle65536 			= ((65536-(VR0a))&(65536-1));	/* 発射中心角度 / 特殊機能(自機狙い/他) */
		// (22) VR13 = VR0a;
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
		// (23) VR13 = (VR00 + (0) - VR13);		// VR13 = VR13 //& (65536-1);
		MCODE(OP0x05_SUBR_PD, (0x00), R13, R00),/*(ゼロレジスタ使用)*/
		// (24)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (25) 		VR0a += VR0e; /*(回転量、黄色)==(分割角、紅色)*/	/*(1024/(6*8))*/	/* 角度(1024[360/360度]を 48分割) */
		MCODE(OP0x04_ADDR_PD, NAX, R0a, R0e),// VR06
	//	(bbb+19):
		// (26)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (25));
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
	/* 通常タイプ */
local SPELL_INIT(0a_houka_kenran)
{
	static const u32 codebase_init[6-1] =
	{
		// (1)	VR0d = 難易度別定数1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(分割数、黄色)*/
		PACK_NAN_IDO_CONST((6), (7), (9), (12)),/*tama_const_H06_NUMS_ALICE_RED*/	/* 分割数(r41-) */
	//	PACK_NAN_IDO_CONST((6), (7), (8), (10)),/*tama_const_H06_NUMS_ALICE_RED*/	/* 分割数(-r40) */
		// (2)
		MCODE(OP0x17_DIV65536, NAX, R0c, R0b),// R4 = 65536 / R3;/*(分割角、黄色)*/ 	/* 分割角度 */
		// (3)	VR0d = 難易度別定数2/*tama_const_H07_DIVS_ALICE_RED*/	/* 分割数 */
		// (3)	VR0d = VR0b * (8);/*(分割数、紅色)*/
		// (3)	VR0d = (VR0b << 3);/*(分割数、紅色)*/
		MCODE(OP0x1f_ASLM_PD, 0x03, R0d, R0b),/*(ショートメモリアドレッシング)*/
		// (4)	/* (R6) == (R3 * 8) だけど速度より精度重視で。(割り算使わなくても掛け算で済む。しかし掛け算の場合、割り算に比べ 3[bit]精度が悪いので使わない)  */
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、紅色)*/	/* 分割角度 */
	//	NAX/*(初期化終了)*/
	};
	cpu_exec((u32*)&codebase_init, (4));//
}
	#if 0
	// ★ 紅 美鈴、華符「芳華絢爛」用
	// easy 	華符「芳華絢爛」と同じ。(easyは時間で簡単になるように調整する)
	// normal	華符「芳華絢爛」と同じ。
	// hard 	--。
	// lunatic	17分割でちゃんと避けれるの確認済み。(これ以上高密度だと辛いかも)
	/* easy 				normal					hard					lunatic 			*/
//	(6),					(6),					(10),					(17),					/* 華符「芳華絢爛」用 */
//	(6*8),					(6*8),					(10*8), 				(17*8), 				/* 華符「芳華絢爛」用 */
//	(int)(65536/(6)),		(int)(65536/(6)),		(int)(65536/(10)),		(int)(65536/(17)),		/* 華符「芳華絢爛」用 */
//	(int)(65536/(6*8)), 	(int)(65536/(6*8)), 	(int)(65536/(10*8)),	(int)(65536/(17*8)),	/* 華符「芳華絢爛」用 */
//	// (r39)ボスが中心に拠って来る仕様に変更した為、従来のままでは高密度て避けれない。
	(6),					(6),					(8),					(10),					/*(分割数、黄色)*/	/* 華符「芳華絢爛」用 */	/* (r39-)仕様を少し変えたので簡単にしないとゲームにならない。 */
	(int)(65536/(6)),		(int)(65536/(6)),		(int)(65536/(8)),		(int)(65536/(10)),		/*(分割角、黄色)*/	/* 華符「芳華絢爛」用 */	/* (r39-)仕様を少し変えたので簡単にしないとゲームにならない。 */
	(6*8),					(6*8),					(8*8),					(10*8), 				/*(分割数、紅色)*/	/* 華符「芳華絢爛」用 */	/* (r39-)仕様を少し変えたので簡単にしないとゲームにならない。 */
	(int)(65536/(6*8)), 	(int)(65536/(6*8)), 	(int)(65536/(8*8)), 	(int)(65536/(10*8)),	/*(分割角、紅色)*/	/* 華符「芳華絢爛」用 */	/* (r39-)仕様を少し変えたので簡単にしないとゲームにならない。 */
	VR0b: tama_const_H00_NUMS_HOUGA_YELLOW/*(分割数、黄色)*/
	VR0c: tama_const_H02_DIVS_HOUGA_YELLOW/*(分割角、黄色)*/
	VR0d: tama_const_H01_NUMS_HOUGA_RED/*(分割数、紅色)*/
	VR0e: tama_const_H03_DIVS_HOUGA_RED/*(分割角、紅色)*/
	//[tama_const_10_HOUGA_YELLOW_ROTATE_ANGLE]
	/*tama_const_H07_DIVS_ALICE_RED*/	/* 分割数 */
	#endif
//	PACK_NAN_IDO_CONST((6), (6), (8), (10));/*(-r40)*/
//	PACK_NAN_IDO_CONST((6), (7), (8), (10));/*(r41-)*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	美鈴の通常攻撃っぽいカード
	-------------------------------------------------------
	normal? 紅クナイ	24方向?
	hard	紅クナイ	35方向(36方向では無い)
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	[定数1]雨の速度
	R0a 	[定数2]クナイが曲がる角度(180/360ちょい回転)
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
#define meirin_01_amefuri_callback common_01_amefuri_callback

/*---------------------------------------------------------
	[弾幕レイヤーグループ(3)セクション、レイヤー(3)弾]
	-------------------------------------------------------
	赤青クナイ用青赤
---------------------------------------------------------*/
local TAMA_FUNC(meirin_03_aka_ao_kunai_time256_callback)
{
	// [128] ダメ早い
	/*(発弾から約4[秒]経過した弾は、通常弾へ変身する)*/
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-(256)) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[256]カウント以上経過した弾 */
	{
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}
/*---------------------------------------------------------
	[弾幕レイヤーグループ(2)セクション、レイヤー(2)弾]
	-------------------------------------------------------
	赤青クナイ用青赤
---------------------------------------------------------*/
local TAMA_FUNC(meirin_02_aka_ao_kunai_callback)
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) == src_tama->jyumyou)/* 発弾エフェクト後から64カウント経過した弾 */
	{
		src_tama->TR01_hatudan_speed65536	= t256(1.0);	/* 初速(打ち出し速度) */
		src_tama->TR02_hatudan_tra65536 	= t256(6.0);	/* 調整加速弾 */
	//	src_tama->tmp_angleCCW1024			= (VR0a);		/* [定数2]赤青クナイが曲がる角度 */
	//	src_tama->tmp_angleCCW65536 		= ((VR0a)<<6);/*(r42とりあえず)*/	/* [定数2]赤青クナイが曲がる角度 */
		src_tama->tmp_angleCCW65536 		= ((VR0a) );/*(r42とりあえず)*/ /* [定数2]赤青クナイが曲がる角度 */
		if (src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT)
		{
		//	src_tama->tmp_angleCCW1024		= (-(src_tama->tmp_angleCCW1024));
			src_tama->tmp_angleCCW65536 	= (-(src_tama->tmp_angleCCW65536));
		}
	//	src_tama->rotationCCW1024			+= (src_tama->tmp_angleCCW1024);
		src_tama->rotationCCW65536			+= (src_tama->tmp_angleCCW65536);
	//	mask1024(src_tama->rotationCCW1024);
		mask65536(src_tama->rotationCCW65536);
		/* (赤青クナイ、レイヤー(3)弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_03)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}
//		const int ao_aka_tbl[(2)]	=
//		{
//		//	 (1024/2)+(1024/32), /* 180/360ちょい回転 */	/* 青 */
//		//	-(1024/2)-(1024/32), /* 180/360ちょい回転 */	/* 赤 */
//			 (1024/2)+(1024/24), /* 180/360ちょい回転 */	/* 青 */
//			-(1024/2)-(1024/24), /* 180/360ちょい回転 */	/* 赤 */
//		};
	//	h->rotationCCW1024				+= (1024/2)+(1024/16);/* 180/360ちょい回転 */
	//	h->rotationCCW1024				+= (1024/2)+(1024/32);/* 180/360ちょい回転 */

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
---------------------------------------------------------*/

local SPELL_EXEC(12_meirin_magaru_kunai)
{
//	VR07	 = t256(256);	/*(デバッグ用)*/
	/* 雨 */
	if (0x30>(VR10_BOSS_SPELL_TIMER & 0xff))/* (256回に ??回) */
	{
		spell_execute_common_amefuri(src_boss);
	}
/*
time
f	1111	青1 			[発弾]
e	1110
d	1101			赤1 	[発弾]
c	1100
b	1011	青2 			[変身]
a	1010
9	1001			赤2 	[変身]
8	1000
7
...
0
*/
//	VR0a = (VR10_BOSS_SPELL_TIMER);/*(とりあえず)*/
	/* [発弾] */
	if (0xd0 == (VR10_BOSS_SPELL_TIMER & 0xdf))/* (256回に2回) */
	{
		static /*const*/ u32 codebase_exec[29] =
		{
		// (01) VR03_i = 0;
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R03_i, NAX),
		(0),
	//	loop_i-25:
		//	HATSUDAN_R11_speed256			= (t256(4.0)-(VR03_i << 6));				/* 弾速 */
		// (02) VR11 = (VR03_i << 6);
		MCODE(OP0x1f_ASLM_PD, 0x06, R11, R03_i),/*(ショートメモリアドレッシング)*/
		// (03) VR11 = (VR00 + (0) - VR11);
		MCODE(OP0x05_SUBR_PD, (0x00), R11, R00),/*(ゼロレジスタ使用)*/
		// (04) VR11 = VR11 + (t256(4.0));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(ロングメモリアドレッシング専用命令)*/
		(t256(4.0)),
		// (05) HATSUDAN_R12_speed_offset		= -t256(5); 						/* (-5) (-3)調整減速弾 */	/* この方式になるか検討中 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(-t256(5)),
		// (06) HATSUDAN_R13_angle65536 		= (0/65536);						/* 下向き */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),
		((0/65536)),
		// (07) u8 check_00type 				= ((VR10_BOSS_SPELL_TIMER>>5)&1); /* 赤青クナイ弾 +(0&1)*/
		MCODE(OP0x1d_ANDM_PD, 0x20, R14, R10),/*(1<<5)(ショートメモリアドレッシング)*/
		// (08) if (0 != VR14) {goto loop_i;}/*(6連)*/
		MCODE(OP0x08_BNE_RS, (0), R14, (+5)),//(ccc+5:)
		//----------------赤クナイ弾 (0==check_00type)
		// (09) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|((check_00type)<<8)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_02)|(0x0000)|(TAMA_SPEC_0000_TILT)),
		// (10) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)+(check_00type+check_00type);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)+(0+0)),
		// (11) goto (ddd+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+4)),// (ddd+4)
		//----------------青クナイ弾 (1==check_00type)
	//(ccc+5:)
		// (12) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|((check_00type)<<8)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_02)|(0x0100)|(TAMA_SPEC_0000_TILT)),
		// (13) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)+(check_00type+check_00type);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)+(1+1)),
		//----------------
	//(ddd+4:)
		// (14) HATSUDAN_R16_n_way				= (24);//step_tbl[(difficulty+4)];/*(32)*/
		MCODE(OP0x1c_MOVEM_PD, (24), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (15) HATSUDAN_R17_div_angle65536 	= (65536/24);				/* 分割角度([360/360]度を24分割) */ 	//step_tbl[(difficulty)];/*(32)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
		(65536/24),
		// (16)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (17)VR03_i++;
		MCODE(OP0x01_MOVER_PD, (u8)(+1), R03_i, R03_i), /*(インデックス付)*/
		// (18) if (6 != VR03_i) goto loop_i-25;/*(6連)*/	/*(残り回数があればループ。)*/
		MCODE(OP0x08_BNE_RS, (6), R03_i, (-25)),/*goto loop_i;*/
		// (19)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
		// (20) (eee+22:)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
		};
	//	codebase[1] = (u32)VR04;
		cpu_exec((u32*)&codebase_exec, (20+6*25+10));/*(テキトーに大目)*/
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
	/* 上広タイプ */

local SPELL_INIT(12_meirin_magaru_kunai)
{
	//	cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & ((1<<difficulty)-1) );
	static /*const*/ u32 codebase_init[11] =
	{
		/*(ボス本体の移動範囲を制限する。)*/
		// (01) VR3c_boss_clip_min_x256	= ;
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3c_boss_clip_min_x256, NAX),// 右の範囲を設定する。
		CLIP_BOSS_01_VR3c, // #01狭いタイプ。
		// (02) VR3e_boss_clip_max_x256	= ;
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R3e_boss_clip_max_x256, NAX),// 左の範囲を設定する。
		CLIP_BOSS_01_VR3e, // #01狭いタイプ。
	//----
		//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[定数1]雨の速度
		//	VR09	= (t256(1.5)+((0)<<6));//[定数1]雨の速度
		// (03)VR09 = (t256(1.5)+((0)<<6));//[定数1]雨の速度	/*(とりあえず)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R09, NAX),//
		(t256(1.5)),
		// (04) VR0a = 難易度別定数2
		//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[定数2]赤青クナイが曲がる角度
		//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[定数2]赤青クナイが曲がる角度
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0a, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((0), (10), (12), (16)),/*(r41-)*/
	//	PACK_NAN_IDO_CONST((0), (8), (16), (24)),/*(-r40)*/
		// (05)
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),/*(ロングメモリアドレッシング専用命令)*/
		((1024/2)+(1024/24)),
		// (06) VR0a	= (VR0a << (6));/*(r42とりあえず)*/ 	/* [定数2]赤青クナイが曲がる角度 */
		MCODE(OP0x1f_ASLM_PD, (6), R0a, R0a),/*(ショートメモリアドレッシング)*/
	};
	cpu_exec((u32*)&codebase_init, (6));
	//
}
		//	 (nan_ido);
		// (01) VR0d = 難易度別定数1
	//	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	//	PACK_NAN_IDO_CONST(0x00, 0x1f, 0x3f, 0x5f),
	//	// (02) VR09 = t256(1.0) + VR09;//[定数1]雨の速度
	//	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),/*(ロングメモリアドレッシング専用命令)*/
	//	(t256(1.0)),

//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[定数1]雨の速度
//	/*(とりあえず)*/VR09	= (t256(1.5)+((0)<<6));//[定数1]雨の速度
//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[定数2]赤青クナイが曲がる角度

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	五方向時計回り弾
	-------------------------------------------------------
	真上が基準位置。
	分割角は、5*13/360 ぐらいから始まる。
	だんだん増える。
	分割角は、65536/5/13 == 1008.246153846154 なので、
	1000から始める事にする。
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09
	R0a
	-------------------------------------------------------
	R0b 	分割角。
	R0c 	現在回転角。
	R0d 	。
---------------------------------------------------------*/

local SPELL_EXEC(19_meirin_5_houkou)
{
	/* [発弾] */
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x04))/* ( 回に 回) */
	{
		VR0c += VR0b;
		VR0b += (0xff-(VR10_BOSS_SPELL_TIMER & 0xff));
		HATSUDAN_R11_speed256			= t256(2.0);/* 弾速(0) */
		HATSUDAN_R12_speed_offset		= t256(-1);/* 減速？ */
		HATSUDAN_R13_angle65536 		= (VR0c);	/* 弾源角度65536 */ 	/*下CCW*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA);			/* [赤クナイ弾] */
		HATSUDAN_R16_n_way				= (5);								/* [5way] */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/5);					/* [密着弾]の分割角度(r32) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	}
}

local SPELL_INIT(19_meirin_5_houkou)
{
	VR0b = 1000;
	VR0c = 0;
}
// ==================================== [スペカ境界] ==================================== //

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	幻符「華想夢葛」
	-------------------------------------------------------
	幻符「華想夢葛」は、一見ばらばらに配置している風に見えるが、
	発弾位置をよく見ると、乱数ではなく星型(5方向)に配置している。

---------------------------------------------------------*/
//local SPELL_EXEC(40_meirin_kasou_yume_kazura)
//{
//
//}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	虹符「彩虹の風鈴」(normal)
	-------------------------------------------------------
	分割数が良く解からないが、
	分割数は56分割〜64分割程度らしい。
	根拠は 7 弾密集している部分が、全体の(1/8)未満の領域に収まっている事。
	(1/8)の領域に 7 弾密集しているのだから、最低でも
	7 x 8 で 56分割は、必要である。
	-------------------------------------------------------
	弾幕の分割数が 12で割り切れる場合もある。
	8 x 8 で 64分割なので、これに近い値で、12 で割り切れるものは、60。
	だから、60分割(5x12)の可能性はある。
	-------------------------------------------------------
	ところが実際に調べて見た処、60 分割と64 分割は色の間隔から、どう頑張っても辻褄が合わない。
	-------------------------------------------------------
	64 分割 (8 x 8) 		  (辻褄合わない。蜜弾の間隔が狭すぎる。次の波までの間隔が広すぎる。)
	60 分割 (7 x 4 + 8 x 4)   (辻褄合わない。蜜弾の間隔が狭すぎる。次の波までの間隔が広すぎる。)
	-------------------------------------------------------
	56 分割 (7 x 8) 		  (辻褄合う。)
	-------------------------------------------------------
	回り方向は、模倣風のシステムがCCW(反時計回り)なのでCCWとする。
	-------------------------------------------------------
	始めに美鈴は、時計回りで撃ってくる(途中から反時計回りになったり戻ったりする)
---------------------------------------------------------
[]の部分は撃つ。
  の部分は撃たないが、仮に撃つとしたらその色になる筈。
<>の部分は特殊弾で、角度が一致しない。色も違う。
---------------------------------------------------------
	仮に56分割として色を考えてみる。
位置[00/56][紫色]位置[14/56] 紫色 位置[28/56][紫色]位置[42/56]<特3A>/
位置[01/56][青色]位置[15/56] 青色 位置[29/56] 青色 位置[43/56]<特3B>/
位置[02/56][水色]位置[16/56][水色]位置[30/56][水色]位置[44/56][水色]/
位置[03/56][緑色]位置[17/56] 緑色 位置[31/56][緑色]位置[45/56] 緑色 /
位置[04/56][黄色]位置[18/56][黄色]位置[32/56][黄色]位置[46/56][黄色]/
位置[05/56][橙色]位置[29/56]<特1A>位置[33/56] 橙色 位置[47/56] 橙色 /
位置[06/56][赤色]位置[20/56]<特1B>位置[34/56][赤色]位置[48/56] 赤色 /
---------------------------------------------------------------------
位置[07/56] なし 位置[21/56] なし 位置[35/56] なし 位置[49/56] なし /
位置[08/56] なし 位置[22/56] なし 位置[36/56] なし 位置[50/56] なし /
位置[09/56] なし 位置[23/56] なし 位置[37/56] なし 位置[51/56] なし /
位置[10/56] なし 位置[24/56][橙色]位置[38/56][特２]位置[52/56] なし /
位置[11/56] なし 位置[25/56] なし 位置[39/56] なし 位置[53/56] なし /
位置[12/56] なし 位置[26/56] なし 位置[40/56] なし 位置[54/56] なし /
位置[13/56] なし 位置[27/56] なし 位置[41/56] なし 位置[55/56] なし /
---------------------------------------------------------
<特１>	青色特殊弾A。角度が若干ずれている。<特1A>と<特1B>の中間ぐらい。
[特２]	青色特殊弾B。この弾は角度がずれていない。
<特３>	橙色特殊弾C。角度が若干ずれている。<特3A>と<特3B>の中間ぐらい。
---------------------------------------------------------
特殊弾の角度のずれは、どれくらいずれているのか良く解からない。
ずれが分割数の違い(ずれてる方は64分割とか)からきている可能性もある。
---------------------------------------------------------
ずれを中間位置とした場合に考えてみる。
	7 x 8 x 2 で 112分割。
---------------------------------------------------------
	仮に112分割として色を考えてみる。
位置[000/112][紫色]位置[028/112] 紫色 位置[056/112][紫色]位置[084/112] なし /
位置[001/112] なし 位置[029/112] なし 位置[057/112] なし 位置[085/112]<特3 >/
位置[002/112][青色]位置[030/112] 青色 位置[058/112] 青色 位置[086/112] なし /
位置[003/112] なし 位置[031/112] なし 位置[059/112] なし 位置[087/112] なし /
位置[004/112][水色]位置[032/112][水色]位置[060/112][水色]位置[088/112][水色]/
位置[005/112] なし 位置[033/112] なし 位置[061/112] なし 位置[089/112] なし /
位置[006/112][緑色]位置[034/112] 緑色 位置[062/112][緑色]位置[090/112] 緑色 /
位置[007/112] なし 位置[035/112] なし 位置[063/112] なし 位置[091/112] なし /
位置[008/112][黄色]位置[036/112][黄色]位置[064/112][黄色]位置[092/112][黄色]/
位置[009/112] なし 位置[037/112] なし 位置[065/112] なし 位置[093/112] なし /
位置[010/112][橙色]位置[038/112] なし 位置[066/112] 橙色 位置[094/112] 橙色 /
位置[011/112] なし 位置[039/112]<特1 >位置[067/112] なし 位置[095/112] なし /
位置[012/112][赤色]位置[040/112] なし 位置[068/112][赤色]位置[096/112] 赤色 /
位置[013/112] なし 位置[041/112] なし 位置[069/112] なし 位置[097/112] なし /
---------------------------------------------------------------------
位置[014/112] なし 位置[042/112] なし 位置[070/112] なし 位置[098/112] なし /
位置[015/112] なし 位置[043/112] なし 位置[071/112] なし 位置[099/112] なし /
位置[016/112] なし 位置[044/112] なし 位置[072/112] なし 位置[100/112] なし /
位置[017/112] なし 位置[045/112] なし 位置[073/112] なし 位置[101/112] なし /
位置[018/112] なし 位置[046/112] なし 位置[074/112] なし 位置[102/112] なし /
位置[019/112] なし 位置[047/112] なし 位置[075/112] なし 位置[103/112] なし /
位置[020/112] なし 位置[048/112][橙色]位置[076/112][特２]位置[104/112] なし /
位置[021/112] なし 位置[049/112] なし 位置[077/112] なし 位置[105/112] なし /
位置[022/112] なし 位置[050/112] なし 位置[078/112] なし 位置[106/112] なし /
位置[023/112] なし 位置[051/112] なし 位置[079/112] なし 位置[107/112] なし /
位置[024/112] なし 位置[052/112] なし 位置[080/112] なし 位置[108/112] なし /
位置[025/112] なし 位置[053/112] なし 位置[081/112] なし 位置[109/112] なし /
位置[026/112] なし 位置[054/112] なし 位置[082/112] なし 位置[110/112] なし /
位置[027/112] なし 位置[055/112] なし 位置[083/112] なし 位置[111/112] なし /
---------------------------------------------------------
結局、特殊弾は４つ。で別処理と推測できる。
	<特1 > 弾番号40 (？)
	[橙色] 弾番号49 (始終苦しむから？)
	[特２] 弾番号77 (ラッキ−7から？)
	<特3 > 弾番号86 (pc-98x1のcpu型番i80x86から？ナムコシステム86から？車のレビンAE86から？)
だと思われる。
---------------------------------------------------------*/
