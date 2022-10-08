
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ルイズっぽいカードを定義します。
	と思ったけど、全然それっぽくない。
	-------------------------------------------------------
	とりあえずカード語の実験。
	-------------------------------------------------------
	カウンタ専用レジスタは廃止して、汎用レジスタと統合した。
---------------------------------------------------------*/

/*---------------------------------------------------------
	最終形態っぽい奴
	-------------------------------------------------------
	自機狙い32方向減速弾。
	左右に交互に撃つ。32方向で1/4周。原作は白小弾。
	-------------------------------------------------------
	新システムでカード語が使える予定(?)なので、
	カード語を意識して書いて試る。
	-------------------------------------------------------
	使用レジスタ(てすと):
	R08 	カウンタ。基本的に4回に一回処理。
	R09 	32方向弾にしよ～っと。
	R0a 	左右で色を変えよう。
	R0b 	角度を保持するね。
	R0c
	R0d
	R0e
	R0f 	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)
---------------------------------------------------------*/
local SPELL_EXEC(44_ruiz3)
{
	static const u32 codebase_exec[25] =
	{
		MCODE(OP0x02_COUNTER, 4, R08, NAX),// 基本的に4回に一回処理。
		// (1)	if (0!=(VR08)) {return;}	R8 が 0 の場合のみ発弾。それ以外は発弾しない。
		MCODE(OP0x08_BNE_RS, (0x00), R08, (+22)),//(eee+22) /* 発弾しない場合、お終いまでジャンプ */
		// (2)				// 32方向弾にしよ～っと。
		MCODE(OP0x02_COUNTER, 32, R09, NAX),// 32方向弾にしよ～っと。
		// (3)	if (1==(VR09))	/* 始めての場合[ここから] */
		MCODE(OP0x08_BNE_RS, (0x01), R09, (+3)),//(bbb+3)	/* 始めての場合 */
		// (4)					// 左右で色を変えよう。
		MCODE(OP0x02_COUNTER, 2, R0a, NAX),// 左右で色を変えよう。
		// (5)	 (calculate_jiki_nerai);/* 自機狙い角作成 */
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),/* 自機狙い角作成 */
		// (6)	VR0b = HATSUDAN_R13_angle65536;/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R13),
		// (7)	(bbb+3:)	/* 始めての場合[ここまで] */
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (+3)),//(ccc+3)
		// (8)	if (0!=VR0a)	{(VR0b) -= (65536/(4*32));}
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(+(65536/(4*32))),
		// (9)	goto (ddd+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
		// (10) (ccc+3:)	if (0==VR0a)	{(VR0b) += (65536/(4*32));}
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(-(65536/(4*32))),
		// (11) (ddd:)	HATSUDAN_R11_speed256 = (t256(1.2) + (VR09 << 3));	/* 弾速 */
		// (11) VR11 = (VR09 << 3);
		MCODE(OP0x1f_ASLM_PD, 0x03, R11, R09),/*(ショートメモリアドレッシング)*/
		// (12) VR11 = VR11 + (t256(1.2));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(ロングメモリアドレッシング専用命令)*/
		(t256(1.2)),
		// (13) HATSUDAN_R12_speed_offset			= t256(1);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
		(t256(1)),
		// (14) HATSUDAN_R13_angle65536 			= (VR0b);/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (15) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(ロングメモリアドレッシング)*/
		(DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT),
		// (16) HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + VR0a;	/* [ 弾] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R0a),/*(ロングメモリアドレッシング専用命令)*/
		(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA),
		// (17) 	(1弾撃つ)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		// (18) (eee+22:)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (17));
}

#if 0
[ID:supeka3500] 			; //識別文字列
試作「カード語のてすと」	; //譜名

[init]	; //初期化セクション
r0		44		; //登録番号(r0は常に定数0なので初期化できない。そこで、初期化セクションに書いた場合、登録番号にする。)
r1		5
r8		125
;	使用レジスタ(てすと):
;	r1	取り敢えず4回に一回でいいや。
;	r2	32方向弾にしよ～っと。
;	r3	左右で色を変えよう。
;	r4	角度を保持するね。

[spell] 	; //発弾セクション
{
	; // カード語は命令と最大で引数3個まで。
	count_up_limit r1, 4, 0 			; 取り敢えず4回に一回でいいや。
	if_equal 0, r1						; // ifは引数2個まで引数3はシステムが使う(引数3==不成立の場合のジャンプ先の位置)
	{
		count_up_limit r2, 32, 0		; 32方向弾にしよ～っと。
		if_equal 1, r2					; 始めての場合
		{
			count_up_limit r3, 2, 0 	; 左右で色を変えよう。
			jiki_nerai r4				; 自機狙い角作成  CPUREG_angleCCW65536_jiki_nerai();/*	*/
			set r4, HATSUDAN_R13_angle65536 	; // /* 自機狙い角 */
		}
		if_equal 0, r3
		{
			add r4, 512 				; 512 == ((65536/4)/32)
		}
	;	else はカード語では存在しない。
		if_equal 1, r3
		{
			add r4, -512				; 512 == ((65536/4)/32)
		}
		set HATSUDAN_R11_speed256,			(t256(1.2)+(r2<<3)) 			; /* 弾速 */
		set HATSUDAN_R12_speed_offset,		t256(1) 						; /*(テスト)*/
		set HATSUDAN_R13_angle65536,		(r4)							;
		set HATSUDAN_R14_tama_spec, 		(DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)			; /* (r33-)標準弾 */
		set HATSUDAN_R15_bullet_obj_type,	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + r3		; /* [ 弾] */
		hatudan_system_regist_single												; /* (1弾撃つ) */
	}
	label 123	;
	jump 123	;
}
#endif
