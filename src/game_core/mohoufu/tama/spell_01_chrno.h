
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	チルノのカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	紅2面ボス チルノ	通常攻撃1(1/3)	自機狙い拡散弾(1-2-3-4-5-6-7-8弾)
	-------------------------------------------------------
	(1-2-3-4-5-6-7弾)かと思ってたけど、原作やり直したら、
	(1-2-3-4-5-6-7-8弾)だったので修正。
うーん
	原作やり直してよく見たら、
//	(1-2-3-4-5-6-7弾)か 			(easyとか)間違い？？？

	チルノはどうも「内部ランク」で違う感じの弾を撃ってくる。ので良く判らない。

	-------------------------------------------------------
	原作やり直してよく見たら、
	(2-3-4-5-6-7弾) 				(easy)
									(normal)
	(3-4-5-6-7-8弾)。				(hard)
	(3-4-5-6-7-8弾)。				(lunatic)
	-------------------------------------------------------
	始めの方の弾が速く、後の弾はゆっくり。

1100 0111 0xc7
0100 0000
--11 0111 0x37

	-------------------------------------------------------
0x38(56) --0
0x30(48) --1
0x28(40) --2 全方位青枠丸弾
0x20(32) --3 全方位青枠丸弾
0x18(24) --4
0x10(16) --5
0x08( 8) --6
0x00( 0) --7
	-------------------------------------------------------
	lunaticとかだと全方位青枠丸弾も同時に撃ってくる。(2回ぐらい)
	-------------------------------------------------------
	使用レジスタ
	R0c 	覚えとく角度。aaa_angle65536
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	---
	R09 	周期カウンタ2。
	R0a 	難易度別定数3(E=0, N=0, H=1, L=1)
//	R0b 	---
	R0c 	覚えとく角度。aaa_angle65536
	R0d 	難易度別定数1
	R0e 	難易度別定数2
---------------------------------------------------------*/
local SPELL_EXEC(10_cirno_misogi)
{
	// SPELL_TIME_0128
	if (SPELL_TIME_0064-(8*8) < VR10_BOSS_SPELL_TIMER)
	{
		if ((SPELL_TIME_0064-1)!=VR10_BOSS_SPELL_TIMER) {goto rendan16;}
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#else
		{
			static /*const*/ u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(終了)*/
			};
			cpu_exec((u32*)&codebase888, (1));
		}
		#endif
		//
		/* 弾源x256 y256 ボスの中心から発弾。 */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
		VR0c = VR13;/*(自機狙い角度を覚えとく)*/
	// --------
	rendan16:
	//	if (0x40==((s rc->boss_sp ell_timer)&0xc7))/* 8回(修正1-2-3-4-5-6-7弾:0wayは撃たないので撃つのは7回) */
	//	if (0x00==((s rc->boss_sp ell_timer)&0x07))/* 8回(修正1-2-3-4-5-6-7弾:0wayは撃たないので撃つのは7回) */
		if (0!=(VR10_BOSS_SPELL_TIMER&7)) {goto easy_ha_nasi;}/*(8回に1回)*/ /* 8回毎に1回 */
		//{
		/*(0 ... 11 : 12回 カウンタ2)*/
		/* --10 -000 == 0011 0111 */
		//	if (0x20==((s rc->boss_sp ell_timer)&0x37))/* 2回 */
		if (SPELL_TIME_0064-(2*8) < VR10_BOSS_SPELL_TIMER){;}else{goto easy_ha_nasi;}/* 2回 */	/* (0) or (1) の場合。 */
		if (0 == VR0d) {goto easy_ha_nasi;}
		//{
		// hard 18方向(1回)
		// Luna 36方向(2回)
		HATSUDAN_R13_angle65536 		= VR0c;/*(覚えといた自機狙い角度を使う)*/
		HATSUDAN_R11_speed256			= (t256(2.0));				/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [枠付き青丸弾] */
		HATSUDAN_R16_n_way				= VR0d;// (36);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(36));	/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		//}
	// --------
	easy_ha_nasi:
		;
		if (0!=(VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2回に1回)*/ /* 8回毎に1回 */
		if (SPELL_TIME_0064-(6*8) < VR10_BOSS_SPELL_TIMER){;}else{goto osimai;}/* 2回 */	/* (0) or (1) の場合。 */
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 12, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));/*(0 ... 11 : カウンタ2)*/
	}
		//if (6 > VR09)/*(0, 1, 2, 3, 4, 5 の場合)*/
	/* 2.50, 2.375, 2.250, 2.125, 2.00, 1.875 :  (8-3)==0.125,	8==1.00, 7==0.50, 6==0.25, 5==0.125 */
	//	HATSUDAN_R11_speed256			= (t256(2.5))-((R09)<<5);				/* 弾速 */
		HATSUDAN_R11_speed256			= (t256(2.5)) + (VR10_BOSS_SPELL_TIMER<<2); 			/* 弾速 */
	//	HATSUDAN_R12_speed_offset		= t256(6);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= t256(6);/*(テスト)*/
		HATSUDAN_R13_angle65536 		= VR0c;/*(覚えといた自機狙い角度を使う)*/ // /* [破壊] */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [青米弾] になってるのは現在 氷弾 のグラが無いから */
		HATSUDAN_R16_n_way				= (2) + (VR09) + (VR0a);/* [nway] */	/* [破壊] */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(64));		/* [破壊] */		/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(80));		/* [破壊] */		/* 分割角度(65536[360/360度]を 80 分割) */	/* 1周をn分割した角度 */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(96));		/* [破壊] */		/* 分割角度(65536[360/360度]を 80 分割) */	/* 1周をn分割した角度 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/

		//}
	osimai:
		;
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
---------------------------------------------------------*/
local SPELL_INIT(10_cirno_misogi)
{
//	if ((64-1)==((s rc->boss_sp ell_timer)))
//	if ((SPELL_TIME_0060-1)==((s rc->boss_sp ell_timer)))	{;}
	//	/*別変数でも良い?*/cg_BOSS_DATA_38_angleCCW65536
	static const u32 codebase_init[5] =
	{
		// (01) VR0a = ((cg_VR20_game_difficulty)>>1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0a, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*()*/
		PACK_NAN_IDO_CONST((0), (0), (1), (1)),/* R0a	難易度別定数3(E=0, N=0, H=1, L=1) */
		// (02) // VR0d = 難易度別定数1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(分割数、黄色)*/
		PACK_NAN_IDO_CONST((0), (0), (18), (36)),/*tama_const_H06_NUMS_ALICE_RED*/	/* 分割数:(r35-) */
		// (03)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e  = 65536 / R0d;/*(分割角、黄色)*/	/* 分割角度:  (r35-) */
	};
	cpu_exec((u32*)&codebase_init, (3));//
}
	#if 0
	// ★ チルノ「」用
	VR0d = [tama_const_H04_NUMS_CIRNO_BLUE];/*(分割数、青色)*/	(0),	(0),	(18),				(36),				/* 註:3より4の方が簡単 */
	VR0e = [tama_const_H05_DIVS_CIRNO_BLUE];/*(分割角、青色)*/	(0),	(0),	(int)(65536/(18)),	(int)(65536/(36)),	/* 註:3より4の方が簡単 */
	#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅2面ボス チルノ	通常攻撃1(2/3)	自機狙い全方位弾
	-------------------------------------------------------
	[easy]10方向枠付き青弾。
	-------------------------------------------------------
	ただの全方位ばらまき。
	-------------------------------------------------------
	紅2面ボス チルノ	通常攻撃1(3/3)	自機狙い収束弾
	-------------------------------------------------------
	[easy]自機狙い収束18方向白米弾は、原作のスクショから
	弾の中心で138x138[pix]ぐらいまで広がるっぽい。
	70[pix]として、pspでは52[pix]ぐらい？(52.5==70*0.75)
	-------------------------------------------------------
	始めはただの全方位ばらまき。speedt256(2.0)ぐらい？
	70[pix]進んだら、全弾自機狙いに変化。
	すごいゆっくりspeedt256(0.5)ぐらい？
---------------------------------------------------------*/
#if 0
#endif

// ==================================== [スペカ境界] ==================================== //


/*---------------------------------------------------------
	紅2面ボス チルノ	氷符「アイシクルフォール」
	-------------------------------------------------------
	上から順番に計11回撃つ。(初ループ目は2回目の位置から始めるので計10回、2ループ目からは計11回撃つ)
	3回目ぐらいが水平(より若干下)。
	10回目ぐらいが45度斜めぐらい(より若干下)。
	-------------------------------------------------------
	このカードではチルノは動かないので、画像解析してみる。
	http://code.google.com/p/kene-touhou-mohofu/htm/lab/20110704.html
	-------------------------------------------------------
	画像解析してみると、角度ムラがかなりある。
	わざとやってるのかもしれない。良く判らない。
	-------------------------------------------------------
	45/360度を8分割した角度らしい。(が近い)
	と言う事は1周を64分割した角度？？？
	-------------------------------------------------------
	1回0.5[秒]くらいかな？
	-------------------------------------------------------
	0.5[秒]が 32[カウント]として 10[回]だから、
	繰り返し1周期 == 320[カウント]？
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。(音専用)
	-------------------------------------------------------
	Windows 7 の関数電卓で tan(theta) が計算できる。
	Deg は Degree で 1周が360度の形式。
	Rad は Radian で 1周が 2.0 x PI(3.14...) の形式。(たぶん)
	-------------------------------------------------------
	[Deg] 45 [tan] で 1 == (y / x)
	-------------------------------------------------------
	チルノの横に出す弾は水平じゃなくて、少し下がってる。
	224[pixel]で10[pixel]ぐらい下がる。
	0.04464285714285714285714285714286 == 10[pixel] / 224[pixel] 。そこで
	0.04464285714285714285714285714286 == tan(theta[Deg]) とする。
	0.04464285714148814522111963147185 == tan(2.5561500785...[Deg])
	-------------------------------------------------------
	arc tanが無いので、適当に入れた数字2.5度で大体同じ。(水平より、 2.5度ぐらい下がってる)
	theta[Deg] == 2.5561500785...[Deg](arc tanが無いので、途中でめんどくさくなったw)
	465.33292095715555555555555555556 == 2.5561500785... x 65536[模倣風での1周] / 360[Degでの1周]
	140.93763440860215053763440860215 == 65536 / 465
	141分割(?)
	464.79432624113475177304964539007 == 65536 / 141
	そーゆー訳で (465) を足す事にする。
---------------------------------------------------------*/
#define CIRNO_SAGARU_BUN465 (465)
/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(cirno_icecle_fall_01_callback)/* 氷符「アイシクルフォール」 */
{
//	if (((32*18)-HATUDAN_FRAME64)==((VR0a) ))/* 約0.33[秒](==20[frame])停止 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-64) == src_tama->jyumyou)/* 発弾エフェクト後から[64]カウントの弾 */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(時計回り)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 -= (1024/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */	/* [左が基準(-r40)] */
		//	src_tama->rotationCCW1024 += (1024/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */	/* [右が基準(r41-)] */
			src_tama->rotationCCW65536 += (65536/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /* [右が基準(r41-)] */
		}
		else
		{	/*CCW(反時計回り)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 += (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 += (1024/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */	/* [左が基準(-r40)] */
		//	src_tama->rotationCCW1024 -= (1024/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */	/* [右が基準(r41-)] */
			src_tama->rotationCCW65536 -= (65536/4);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */ /* [右が基準(r41-)] */
		}
		//	src_tama->TR02_hatudan_tra65536 		= t256(1);		/* (1) 調整加速弾 */
		//	src_tama->TR02_hatudan_tra65536 		= t256(7);		/* (1) 調整加速弾 */
			src_tama->TR02_hatudan_tra65536 		= t256(/*4+*/1+cg_VR20_game_difficulty);		/* (1) 調整加速弾 */
		//	src_tama->TR01_hatudan_speed65536		= t256(128);		/* 弾速 */
			src_tama->TR01_hatudan_speed65536		= t256(256);		/* 弾速 */
			/* (通常弾へ変身する) */
			src_tama->TR00_hatudan_spec_data		= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	VR03_i		一度に5弾撃つ。[n]
	VR0b		int aaa_angle;
	-------------------------------------------------------
	システム使用レジスタ(コンパイラが割り当てる)
	VR03_i	ループ用 i (難易度別に残り回数を設定。)
---------------------------------------------------------*/
local SPELL_EXEC(1b_cirno_icecle_fall)
{
//	if ((64-1)==((s rc->boss_sp ell_timer)))
//	if ((SPELL_TIME_0060-1)==((s rc->boss_sp ell_timer)))
//	{
//		/* 弾源x256 y256 ボスの中心から発弾。 */
//		 (calculate_boss_to_jiki_nerai);/* 自機狙い角作成 */
//		HATSUDAN_R13_angle65536 = HATSUDAN_R13_angle65536;	/* [角度をおぼえとく] */
//	}
//	else
//	if (0x40 == (VR10_BOSS_SPELL_TIMER & 0xc7))/* 8回(修正1-2-3-4-5-6-7弾:0wayは撃たないので撃つのは7回) */
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))/* 8回(修正1-2-3-4-5-6-7弾:0wayは撃たないので撃つのは7回) */
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* 約0.5[秒]として、32回に1回。 */
	{
		static /*const*/ u32 codebase777[22] =
		{
			//	HATSUDAN_R11_speed256				= (t256(0.5));			/* 弾速(pspの画面は狭い) */
			//	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
				//	HATSUDAN_R12_speed_offset			= t256(6);/*(テスト)*/
				//	HATSUDAN_R12_speed_offset			= (jj<<(2+8));/* x4倍 てすと*/
			// (01) HATSUDAN_R12_speed_offset			= (0);/* x4倍 てすと*/
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
			((0)),
			// (02) HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [青米弾] になってるのは現在 氷弾 のグラが無いから */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
			((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
			// (03) VR03_i = 5;/* 一度に5弾撃つ。 */
			MCODE(OP0x1c_MOVEM_PD, (0x05), R03_i, NAX),/*(ショートメモリアドレッシング)*/
		//	{
		//	loop_i:(ddd-15)
			//		HATSUDAN_R11_speed256				= (t256(2.0)-(VR03_i<<5));				/* 弾速(2.5) */
			//		HATSUDAN_R11_speed256				= (t256(1.5)-(VR03_i<<8));				/* 弾速(2.5) */
			//		HATSUDAN_R11_speed256				= (t256(1.25)-(VR03_i<<5)); 		/* 弾速(1.250 1.125 1.000, 0.875 0.750, 0.625 ) */
			//		HATSUDAN_R11_speed256				= (t256(1.25)-(VR03_i<<6)); 		/* 弾速(1.250 1.000 0.750, 0.500 0.250	) */
			// (04) HATSUDAN_R11_speed256				= (VR03_i<<6)); 		/* 弾速(1.250 1.000 0.750, 0.500 0.250	) */
			MCODE(OP0x1f_ASLM_PD, (6), R11, R03_i),/*(ショートメモリアドレッシング)*/
			//		HATSUDAN_R13_angle65536 			= (0);	/* 下向き */	/* [破壊] */
			//		HATSUDAN_R16_n_way					= (1);/* [nway] */		/* [破壊] */
			//		HATSUDAN_R17_div_angle65536 		= (int)(65536/(5))+((VR10_BOSS_SPELL_TIMER)<<7);	/* [破壊] */		/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
			//		VR0b = (65536/2) + (int)(65536/5) + ((VR10_BOSS_SPELL_TIMER)<<(10-5));/*n x 1024, 1024==65536/64[分割]。 */
			//		VR0b = (int)(65536/5) + ((VR10_BOSS_SPELL_TIMER)<<(10-5));/*n x 1024, 1024==65536/64[分割]。 */ /* [左が基準(-r40)] */
			// (05) VR0b = ((VR10_BOSS_SPELL_TIMER)<<(10-5));
			MCODE(OP0x1f_ASLM_PD, (10-5), R0b, R10),/*(ショートメモリアドレッシング)*/
			// (06) VR0b += (int)(65536/8) - (int)(CIRNO_SAGARU_BUN465)/*水平より若干下がっている*/;/*n x 1024, 1024==65536/64[分割]。 */	/* [右が基準(r41-)] */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),
			((int)(65536/8) - (int)(CIRNO_SAGARU_BUN465)), /*水平より若干下がっている*/
			// (07) HATSUDAN_R13_angle65536 = VR0b;
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
			/* HATSUDAN_R13_angle65536 [破壊??] */
			// (08) HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(ロングメモリアドレッシング)*/
			((DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			// (09) (1弾撃つ)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// (10) VR0b = (VR00 + (0) - VR0b); 	HATSUDAN_R13_angle65536 = (65536-VR0b);/*(反対側を狙う)*/
			MCODE(OP0x05_SUBR_PD, (0x00), R0b, R00),/*(ゼロレジスタ使用)*/
			// (11) HATSUDAN_R13_angle65536 = VR0b;
			MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
			// (12) HATSUDAN_R14_tama_spec	= (DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(ロングメモリアドレッシング)*/
			((DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			/* HATSUDAN_R13_angle65536 [破壊??] */
			// (13) (1弾撃つ)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// (14) VR03_i--;/*(残り回数減らす。)*/
			/*(ok!インクリメント/デクリメントは、この命令を使う方が良い気がする)*/
			MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
			// (15) if (0 != (s32)VR03_i) {goto loop_i;}/*(残り回数があればループ。)*/ if (0 < (s32)VR03_i) {goto loop_i;}
			MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-15)),//	(ddd-15)loop_i:;
		//	}
		//(eee:)
			// (16)
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			// (17)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
		};
		cpu_exec((u32*)&codebase777, (3+12*5+1));
	}
	if (0x20 == (VR10_BOSS_SPELL_TIMER & 0x37))/* 2回 */
	{
		if (0 < cg_VR20_game_difficulty)
		{
			/* 弾源x256 y256 ボスの中心から発弾。 */
			CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
			HATSUDAN_R11_speed256			= (t256(1.0));				/* (t256(2.0)) 弾速(2.5) */
			HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
			/* HATSUDAN_R13_angle65536 [破壊] */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_07_DAI_DAI);		/* [枠付き黄丸弾] */
		//	HATSUDAN_R16_n_way				= (5);/* [nway] */	/* [破壊] */
			HATSUDAN_R16_n_way				= (7);/* [nway] */	/* [破壊] */
		//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(36));	/* [破壊] */		/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/(24));	/* [破壊] */		/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
}

local SPELL_INIT(1b_cirno_icecle_fall)
{	// (CLIP_RECT_TYPE_02_UE_ONLY);
	static /*const*/ u32 codebase_init[2] =
	{
		// (01)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上だけ広いタイプ
		CLIP_RECT_02_VR1d,// 上だけ広いタイプ
	};
	cpu_exec((u32*)&codebase_init, (1));
}
// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	パーフェクトフリーズの研究
	-------------------------------------------------------
	原作では弾にどの色を割り当てるかという事には拘りがある。
	チルノは 5種類の色の弾を撃つが、撃つ弾の色の出る確率が均等ではなく偏っている。
	この色の偏りは、プログラムの都合等で偶然偏ったものではなく、作為的な演出である。
	ここではチルノが青(aho)なので、ゲーム的にチルノを目立たせるために青弾を少なくするという演出意図がある。
	(青弾が多いとチルノが何処にいるか判らなくなるというゲーム上の都合がある。)
	この色の偏りが、チルノらしさを演出しているので、ここの再現は実は重要だと思う。
	(ahoとかいう設定は関係なくて)弾の色の偏りが原作と違うと、おそらく「ゲーム的にチルノらしくならない」。
	チルノらしさ: 青 -> あお -> ao -> aho -> アホ -> baka -> baka==⑨(花映塚公式説明書から)
	//
	そこで適当なスクショから弾の数を調べる。
	1(1).赤 27/141個	3/16個 == 3.06382978723404255319148936170213 = 27*16/141	(R+G+Bは白なので青が若干少ないがほぼ同値にする)
	2(3).青 21/141個	2/16個 == 2.38297872340425531914893617021277 = 21*16/141	(R+G+Bは白なので青が若干少ないがほぼ同値にする)
	3(5).緑 26/141個	3/16個 == 2.95035460992907801418439716312057 = 26*16/141	(R+G+Bは白なので青が若干少ないがほぼ同値にする)
	4(6).黄 34/141個	4/16個 == 3.85815602836879432624113475177305 = 34*16/141	黄すなわち(R+G)なので青が少ないという演出。
	5(7).橙 33/141個	4/16個 == 3.74468085106382978723404255319149 = 33*16/141	橙すなわち(R+R+G)なので青が少ないという演出。
	従って、下記の確率テーブルがある。
	-------------------------------------------------------
	const u8 p_tama_tbl[(16)] =
	{
		// 確率を等しくする。
		// 色が散らばるような配置を考える。
		 TAMA_IRO_01_AKA, TAMA_IRO_03_AOI,	  TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI,
		 TAMA_IRO_01_AKA, TAMA_IRO_03_AOI,	  TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI,
		 TAMA_IRO_01_AKA, TAMA_IRO_06_KI_IRO, TAMA_IRO_05_MIDORI, TAMA_IRO_06_KI_IRO, TAMA_IRO_07_DAI_DAI, TAMA_IRO_07_DAI_DAI,
	};
	-------------------------------------------------------
	本当はパーフェクトフリーズに乱数は一つも無いのでは？
	と個人的には考えている。
	-------------------------------------------------------
	とりあえず、自前の乱数生成関数(単に周期の長い関数)が、割と品質の良い乱数を出すので、
	何も小細工しなくても偏らないので特に問題なかった。
	でもどうせなら拘ってみる。
//
	まずチルノは毎フレーム弾をばら撒いているに決まっているので(この前提がおかしい可能性はあまり無いと思われる)。
	チルノがばら撒く弾量から、1秒間に60弾程度、1秒間に120弾程度、1秒間に180弾程度の中では、1秒間に120弾程度が近い。
	従って1フレーム2弾とする。
//
	パット見には判らないが、チルノの乱数弾はぐるぐる回りながら、偏って出てくる。らしいので。
	どれぐらいの速度で回るのなら、回って見えないかを実験してみる。(原作は言われなければ判らない程度)
	(16分割==)約1秒間(64フレーム)に4周(0.25秒で1周)だと、露骨に回っている感じ。なので、これでは明らかにおかしい。
	(8分割==)約1秒間(64フレーム)に8周(0.125秒で1周)だと、言われなければ判らない程度。
	(4分割==)約1秒間(64フレーム)に16周(0.0625秒で1周)だと、分割領域がおおざっぱすぎて、分割する意味がないのではないか？。
	1フレーム2弾と総弾量が決まっている為、周回数を増せばその分、分割領域が広くなり、分割する意味がなくなる。
	(分割数1は分割処理をしないのと同じだから)
	つまり、弾量が1フレーム2弾の場合、8分割に近いものしかありえないという事が判る。
//
	上記の実験から、1フレーム辺りは 8分の1程度の領域に 2弾が確定した。
	ただし、この領域は厳密に 8分の1 ではない。
	なぜなら、この領域が n分の1で割り切れると、回って見えやすい上にゲーム的に安全地帯が出来やすい。
	だから、この領域は厳密に n分の1 ではない。
	65536/8 == 8192。65536/10 == 6553.6。これらに近い値と思われる。
	8分の1(8192) > ? > 10分の1(6554) テキトーに KOTEITI_CHIRNO_7777 にしてみる。
	7777の場合 8.42689983284042689983284042689983分の1。(==65536/7777)
//
	上記実験が 8分割なので、2弾目の角度は、16 分割離れた先の、16 分割程度の乱数値(0-4095)が良いと思われる。
	( 8分割 == 16分割(固定値) + 16分割(乱数値) )
	-------------------------------------------------------
	★ 要修正:
	パーフェクトフリーズの後追い弾(青丸)はやり直したら全然違った。
	普通は止まって避けるから判らなかった。(っていうかワザワザ動く人居ないかと)
	なんか動きながら避けると、構造がわかる。
	ランダムとかじゃなくて、(８方向弾を)「三セット」(同時っぽく)撃って来るみたい。
	(自機狙わない)自機狙い偶数弾。
	初回時に自機狙い角a, b, cを作成(?)。
	aとbとcは独立。
---------------------------------------------------------*/

//#define KOTEITI_CHIRNO_7777	(7777<<6)
//#define KOTEITI_CHIRNO_7777	(497728)
#define KOTEITI_CHIRNO_7777 	(492013)
//#define KOTEITI_CHIRNO_7777	(7777)
/* 擬似乱数==加算固定値(KOTEITI_CHIRNO_7777) */

/*---------------------------------------------------------
	パーフェクトフリーズ
	1周期が約10[秒]とする。
0x280  0000 0010 1000 0000	>>=6  0x000a
	-------------------------------------------------------
64 x  0 	(640==0x0280) a
	ランダム発射
64 x  1 	(576==0x0240) 9
	ランダム発射
64 x  2 	(512==0x0200) 8
	ランダム発射
64 x  3 	(448==0x01c0) 7 減速開始
	//減速
64 x  4 	(384==0x0180) 6 停止
	//停止	// 自機依存による8方向発射
64 x  5 	(320==0x0140) 5 再加速
	//再加速
64 x  6 	(256==0x0100) 4
64 x  7 	(192==0x00c0) 3
64 x  8 	(128==0x0080) 2
64 x  9 	( 64==0x0040) 1
64 x 10 	(  0==0x0000) 0
	-------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
[09sec] 34 33		| -- --
[08sec] 32 31 30 29 | -- -- -- --
[07sec] 28 27 26 25 | AA -- -- -- // [07sec] 減速開始。
[06sec] 24 23 22 21 | -- -- -- --
[05sec] 20 19 18 17 | -- -- -- --
[04sec] 16 15 14 13 | BB -- -- -- // [04sec] 全てストップ。
[03sec] 12 11 10 09 | CC -- -- -- // [03sec] 再加速。
[02sec] 08 07 06 05 | -- -- -- --
[01sec] 04 03 02 01 | -- -- -- --
	-------------------------------------------------------
	[execute section: 発弾セクション]
[09sec] 34 33		| RR RR
[08sec] 32 31 30 29 | RR RR RR RR
[07sec] 28 27 26 25 | RR RR RR RR
[06sec] 24 23 22 21 | -- -- RR RR // [06.50sec]最初のランダム発射。((12*16)192[フレーム]==約3秒)ばら撒く。
[05sec] 20 19 18 17 | ZZ ZZ -- --
[04sec] 16 15 14 13 | -- -- ZZ ZZ // [04.50sec] 後追い弾発射
[03sec] 12 11 10 09 | -- -- -- --
[02sec] 08 07 06 05 | -- -- -- --
[01sec] 04 03 02 01 | -- -- -- --
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	使用レジスタ
//	R08 	カウンタ。
	R09 	add_angle 加算角度を保持。
	R0a 	自機狙い角を一時保持する。(現在の実装では HATSUDAN_R13_angle65536 が破壊される仕様なので要るが、後で要らなくなるかも？)
	R0b 	再加速の速度用に乱数保持。
	R0c 	ra_nd16 乱数 16bit
	R0d 	temp 一時使用 [破壊]。/ ループ変数jj;
	-------------------------------------------------------
	VR10_BOSS_SPELL_TIMER	ボスタイマー値。
	VR11 VR10 の判断で用途外使用。
	-------------------------------------------------------
	システム使用レジスタ(コンパイラが割り当てる)
	VR03_i	ループ用 i (難易度別に残り回数を設定。)
---------------------------------------------------------*/
local TAMA_FUNC(cirno_danmaku_01_callback)/* パーフェクトフリーズ */
{
	VR11 = (VR10 & 0x0f);
	if (0 != VR11)	{goto tugi444;}
	//
	VR11 = (VR10 >> 4);
//	if ((28*16) == VR10_BOSS_SPELL_TIMER) /*[07sec] 減速開始*/
//	if ((28*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi222;} /*[07sec] 減速開始*/
	if (28 != VR11) 	{goto tugi222;} /*[07sec] 減速開始*/
	/*---------------------------------------------------------
		(全弾減速) (枠つき12丸弾を全弾減速させる。)
	---------------------------------------------------------*/
	//{
	//	src_tama->TR02_hatudan_tra65536 	= t256(-6); 	/* (-5.12==98%)調整減速弾 x 1.0 */
	//	src_tama->TR02_hatudan_tra65536 	= t256(-12);	/* (-5.12==98%)調整減速弾 x 2.0 */	/* -12==少し戻る */
		src_tama->TR02_hatudan_tra65536 	= t256(-9); 	/* (-5.12==98%)調整減速弾 x 1.5 */
	//}
	goto tugi444;
tugi222:
//	else
//	if ((24*16) == VR10_BOSS_SPELL_TIMER) /*[06sec] 全てストップ*/
//	if ((20*16) == VR10_BOSS_SPELL_TIMER) /*[05sec] 全てストップ*/
//	if ((16*16) == VR10_BOSS_SPELL_TIMER) /*[04sec] 全てストップ*/
//	if ((16*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi333;}  /*[04sec] 全てストップ*/
	if (16 != VR11) 	{goto tugi333;} /*[04sec] 全てストップ*/
	/*---------------------------------------------------------
		(全弾停止) (枠つき12丸弾を全弾停止。)
		弾の色を白くする。
		向きを変える。
	---------------------------------------------------------*/
	//{
			#if 0
		//	s->rotationCCW1024					= (ra_nd()&((1024)-1)); 	/* 向き */	/* 向きは乱数でない気がする */
			#else
			/* 少なくとも乱数よりは本物に近い。 が、全然違う。 */
			/* 加算固定値(KOTEITI_CHIRNO_7777)以外の要因として、全弾配列のサイズでループする為、全弾配列のサイズを */
			/* 現在の 1024 から、本物と同じ 640 に減らせば、似る可能性はある。 */
			VR09 += (KOTEITI_CHIRNO_7777);
		//	src_tama->rotationCCW1024			= (deg65536to1024(VR09));	/* 向き */	/* 「1周が65536分割」から「1周が1024分割」へ変換する。 */
			src_tama->rotationCCW65536			= ((VR09)); /* 向き */
			#endif
		src_tama->TR02_hatudan_tra65536 	= t256(0.0);		/* 調整加速弾 */
		src_tama->TR01_hatudan_speed65536	= t256(0.0);		/* 弾速 */
		src_tama->obj_type_set					= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* 弾グラと弾あたり判定を変更する。 */
	//}
	goto tugi444;
tugi333:
//	else
//	if ((12*16) == VR10_BOSS_SPELL_TIMER) /*[03sec] 再加速*/
//	if ((12*16) != VR10_BOSS_SPELL_TIMER)	{goto tugi444;} /*[03sec] 再加速*/
	if (12 != VR11) 	{goto tugi444;} /*[03sec] 再加速*/
	/*---------------------------------------------------------
		(全弾加速) (枠つき12丸弾を全弾加速させる。)
		加速弾(正確には等加速弾)なのに、加速弾に見えないで
		等速弾(正確には等速度弾、加速==0)に見えちゃう問題がある。
	---------------------------------------------------------*/
	//{
		//{
			#if 0
			VR0b += 0x0100;
		//	VR0b &= 0x0700; 	// 2 3 4 5	6 7 8 9
			VR0b &= 0x0300; 	// 3 4 5 6
		//	src_tama->TR02_hatudan_tra65536 = t256(6);					/* 調整加速弾 */
		//	src_tama->TR02_hatudan_tra65536 = (jj<<8)+t256(2);			/* (2 ... 9) 調整加速弾 */
	//		src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(3.0);/*(r34)*/	/* (3 ... 6) 調整加速弾 */
			#endif
			/* (1は遅すぎたので除外) 9 だと速過ぎるかも */
			/*
				r35で弾幕システムの仕様を変更して、次の弾幕にかかる事が出来るようになった。(r34のシステムでは出来ない)
				(本物は加速が遅いので次の弾幕にかかる)
				したがって、もっとゆっくり加速する。
				r34のシステムではレイヤー区別が無く、弾の種類で判定している為、前の弾幕と次の弾幕の区別が出来ない。
				この為、遅れる事は許されない為に、弾幕の仕様を変更していた。
				r35のシステムでは弾幕別にレイヤーを分けて管理している。この為r34に比べ若干遅い。
				弾幕のレイヤー管理はr34は計1レイヤー管理する(==レイヤー管理無し)。r35は計4レイヤー管理する。
				r35では前の弾幕(レイヤー0)と次の弾幕(レイヤー1)はレイヤーが違うので同時に出現しても問題無い。
			*/
			#if (0)
			VR0b += (123);
			VR0b &= (0x01ff);/* 0 ... 2 */
			src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(1.0);/*(r35)*/	/* (1 ... 3) 調整加速弾 */
			#else
			VR0b += (97);
			VR0b &= (0xff);/* 0 ... 1 */
			src_tama->TR02_hatudan_tra65536 = (VR0b)+t256(1.0);/*(r35)*/	/* (1 ... 2) 調整加速弾 */
			#endif
		//}
		/* (通常弾へ変身する) */	/*(後追い弾は通常弾)*/
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	//}
//	goto tugi444;
tugi444:
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
#define T_01_AKA		(BULLET_WAKU12_BASE | TAMA_IRO_01_AKA)
#define T_03_AOI		(BULLET_WAKU12_BASE | TAMA_IRO_03_AOI)
#define T_05_MIDORI 	(BULLET_WAKU12_BASE | TAMA_IRO_05_MIDORI)
#define T_06_KI_IRO 	(BULLET_WAKU12_BASE | TAMA_IRO_06_KI_IRO)
#define T_07_DAI_DAI	(BULLET_WAKU12_BASE | TAMA_IRO_07_DAI_DAI)
local SPELL_EXEC(13_perfect_freeze)
{
	static const u32 codebase_exec[68] =/*24+16+21+10*/
	{
		// (01) VR11 = (VR10 >> 4);
		MCODE(OP0x1e_ASRM_PD, (4), R11, R10),/*(ショートメモリアドレッシング)*/
		//	(memo)if (((SPELL_TIME_34x16_544)-(12*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if ((22*16) < VR10_BOSS_SPELL_TIMER) {goto colorful_particle;}/* [06.50sec]最初のランダム発射 ((12*16)192[フレーム]==約3秒)ばら撒く。 */
		// (02) if ((22) < VR11) {goto colorful_particle;}/* [06.50sec]最初のランダム発射 ((12*16)192[フレーム]==約3秒)ばら撒く。 */
		MCODE(OP0x09_BFL_RS, (22), R11, (+26)),// colorful_particle+26/*[カラフル弾]*/ フローしたら分岐
		//	(memo)if (((SPELL_TIME_34x16_544)-(16*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if (((SPELL_TIME_34x16_544)-(16*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)else if ((18*16) < VR10_BOSS_SPELL_TIMER) {return;/*何もしない*/}/*[05.50sec] 何もしない*/
		// (03) else if ((18) < VR11) {goto osimai;/*何もしない*/}/*[05.50sec] 何もしない*/
		MCODE(OP0x09_BFL_RS, (18), R11, (+1)),// osimai+1;/*何もしない*/ フローしたら分岐
		/*[04.50sec] 後追い弾発射 */
		//	(memo)if (((SPELL_TIME_34x16_544)-(20*16)) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)if (((SPELL_TIME_34x16_544)-(19*16)/*(24*16)*/) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		//	(memo)else if ((15*16) < VR10_BOSS_SPELL_TIMER) // 192== (12*16)
		// (04) else if ((15) < VR11) // 192== (12*16)
		MCODE(OP0x09_BFL_RS, (15), R11, (+1)),// ato_oidan_check+1;/*後追い弾チェック*/ フローしたら分岐
//osimai+1://osimai-3:
		// (05) else	{goto osimai;/*何もしない*/}
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
/*[後追い弾チェック]*/
//ato_oidan_check+1:
	//{
		// (06) 	VR11 = VR10 & 0x07;VR11 = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, (0x07), R11, R10),/*(ショートメモリアドレッシング)*/
		//	(memo)if (0 == (VR10_BOSS_SPELL_TIMER & 0x07)) /* 8[frame]に1回 */
	//	if (0x00==VR11) /* 8[frame]に1回 */
	//	{
	//	//(?)	(memo)if ((4+(cg_VR20_game_difficulty))>(VR10_BOSS_SPELL_TIMER & 0x07))//[意味不明]
	//		goto ato_oidan;
	//	}
		// (07) if (0 != VR0a)	{return;}	//if (0==VR0a) goto (aaa+3);
		MCODE(OP0x08_BNE_RS, (0), R11, (-3)),/*何もしない*/
/*[後追い弾]*/
//ato_oidan:
		/*
		Normalで適当にやってみた。
		後追い弾は、速度の違う弾(三種)を同時に出す。のセットを6回だった。
		*/
		/* 弾源x256 y256 ボスの中心から発弾。 */
		// (08)  (calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		// (09) VR0a = (HATSUDAN_R13_angle65536);/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R0a, R13),
		// (10) HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(0)),
		// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
		// (12) HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_MARU10_BASE + TAMA_IRO_03_AOI),
		// (13) VR03_i = 3;
		MCODE(OP0x1c_MOVEM_PD, (0x03), R03_i, NAX),/*(ショートメモリアドレッシング)*/
	//(ddd-11:)loop_i:;
		//	HATSUDAN_R11_speed256			= (t256(2.5));				/* 弾速 */
		//	HATSUDAN_R11_speed256			= (t256(1.75)+(jj<<7)); 	/* 弾速 */
		// (14) HATSUDAN_R11_speed256			= (VR03_i << 8);	/* 弾速 */
		MCODE(OP0x1f_ASLM_PD, 0x08, R11, R03_i),/*(ショートメモリアドレッシング)*/
		// (15) HATSUDAN_R13_angle65536 		= (VR11);	/* [破壊] */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R11),
		// (16) VR11 += t256(2.00);/* 弾速 */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(t256(2.00)),
		// (17) VR13 += (VR0a);/* 自機狙い角 */
		MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
		// (18) HATSUDAN_R16_n_way				= (8);			/* [破壊] */	/* [8way] */
		MCODE(OP0x1c_MOVEM_PD, (8), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (19) HATSUDAN_R17_div_angle65536 	= (65536/16);	/* [破壊] */	/* 分割角度([360/360]度を16分割) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/16),
		// (20)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
		// (21) VR03_i--;/*(残り回数減らす。)*/
		#if 1/*(ok!インクリメント/デクリメントは、この命令を使う方が良い気がする)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
		#endif
		// (22) if (0 != (s32)VR03_i) {goto loop_i;}/*(残り回数があればループ。)*/ if (0 < (s32)VR03_i) {goto loop_i;}
		MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-11)),//	(ddd-11)loop_i:;
	//(eee:)//return;
		// (23)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	//}
/*[カラフル弾]*/
//colorful_particle+6:
		// (24) VR09 += (KOTEITI_CHIRNO_7777);	/* 固定値。8分の1 から 10分の1 程度の値で、n分の1で割り切れない値。 */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
		(u32)(KOTEITI_CHIRNO_7777), /* 分割角度([360/360]度を16分割) */
		// (25) VR0c = (ra_nd());/*&0xffff*/
		MCODE(OP0x15_RAND_VALUE, NAX, R0c, NAX),
		// (26) VR0c = VR0c & (65536-1);	VR0c &= (0xffff);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0c, R0c),
		(0xffff),
		//		HATSUDAN_R11_speed256			= (t256(1.9)+(VR0c>>7));		/* 弾速 */	/* (VR0c>>7) == 乱数(0-511) */
		//		HATSUDAN_R11_speed256			= (t256(1.5)+(VR0c>>7));		/* 弾速 */	/* (VR0c>>7) == 乱数(0-511) */
		// (27) HATSUDAN_R11_speed256 = (VR0c >> 7);
		MCODE(OP0x1e_ASRM_PD, (7), R11, R0c),/*(ショートメモリアドレッシング)*/
		// (28) HATSUDAN_R11_speed256 += (u32)(t256(1.5));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),
		(u32)(t256(1.5)),	/* */
		//		HATSUDAN_R12_speed_offset		= t256(-5); 		/* (-5) (-3)調整減速弾 */	/* この方式になるか検討中 */
		// (29) HATSUDAN_R12_speed_offset	= t256(0);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(0)),
		/*
			ここの弾速調整は、単純に速い方が難しかったり、遅い方が難しかったりという事は無い。
			あんまり速くし過ぎる(倍速ぐらい？)と、ただのエターナルミークになっちゃうのは判ると思うけど。
			//
			速い場合は、始めの弾を避けるのはその分難しくなるが、後半は弾数が減るので酷く簡単になる。
			遅い場合は、始めの弾を避けるのはその分簡単になるが、後半は弾数が増えるのでその分難しくなる。
		*/
		//		HATSUDAN_R13_angle65536 	= (0/65536);					/* 下向き */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((32768)-1)) + ((VR10_BOSS_SPELL_TIMER)<<(8+6)); 	/* 向き */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((32768/32)-1)) + ((VR10_BOSS_SPELL_TIMER)<<(8+4));		/* 向き */
		//		HATSUDAN_R13_angle65536 	= (ra _nd()&((65536)-1)) ;		/* 向き */
		// (30) HATSUDAN_R13_angle65536 	= (VR09)/*8分割(0.125秒で1周)*/;	/* 向き */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
		// (31) HATSUDAN_R14_tama_spec = (DANMAKU_LAYER_01)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_8000_NON_TILT)),
		// (32) VR0d = (VR10_BOSS_SPELL_TIMER & 0x0f);
		MCODE(OP0x1d_ANDM_PD, (0x0f), R0d, R10),/*(ショートメモリアドレッシング)*/
		//	HATSUDAN_R15_bullet_obj_type		= (p_tama_tbl[(VR0d)]);
		// (33) VR15 = hairetu[R0d];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R0d, R15, (+16)),
		// [16]
		T_01_AKA, T_03_AOI,   T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI,
		T_01_AKA, T_03_AOI,   T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI,
		T_01_AKA, T_06_KI_IRO, T_05_MIDORI, T_06_KI_IRO, T_07_DAI_DAI, T_07_DAI_DAI,
//		/* 確率を等しくする。 */
//		/* 色が散らばるような配置を考える。 */
//	(bbb+16:)
		// (...) HATSUDAN_R17_div_angle65536 += (u32)(65536/16);
	//	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
	//	(BULLET_WAKU12_BASE),	/* */
	//	#if 0
	//	HATSUDAN_R16_n_way	= (2);	/* [2way] */	/* 1フレームに2弾 */
	//	#else
	//	HATSUDAN_R16_n_way	= (1 + (cg_VR20_game_difficulty)); /* 模倣風なので、難易度調整 */
	//	#endif
		// (50) VR16 = VR20 + 1;//HATSUDAN_R16_n_way = (1+(cg_VR20_game_difficulty));
		MCODE(OP0x01_MOVER_PD, (u8)(+1), R16, R20_PLAYER_DATA_game_difficulty),/*(インデックス付)*/
		// (51) HATSUDAN_R17_div_angle65536 = (VR0c >> 4); /* (VR0c >> 4) == 乱数(0-4095) */
		MCODE(OP0x1e_ASRM_PD, (4), R17, R0c),/*(ショートメモリアドレッシング)*/
		// (52) HATSUDAN_R17_div_angle65536 += (u32)(65536/16);
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R17, R17),
		(u32)(65536/16),	/* 分割角度([360/360]度を16分割) */
		// (53)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (54) VR0d = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, (0x07), R0d, R10),/*(ショートメモリアドレッシング)*/
		// (55)if (0 != VR0d){goto(ccc+2);}if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
		MCODE(OP0x08_BNE_RS, (0x00), R0d, (+1)),//	(ccc+1)
		// (56)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
//	(ccc+1:)
		// (57)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (30+6/*9*/+8));/*(?テキトーに多め)*/
//	cpu_exec((u32*)&codebase_exec, (17));
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	雪符「ダイアモンドブリザード」
	-------------------------------------------------------
	(r35)巧くいってない。
	-------------------------------------------------------
	チルノの周りで氷弾をばら撒く
	微妙に減速弾っぽい。
		1.チルノの周り離れた位置から発弾。(ランダム?)
		2.ある程度まで広がる。
		3.微減速弾。
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。(音専用)
	R09 	angle_65536
	R0a 	sine   の値用。
	R0b 	cosine の値用。
---------------------------------------------------------*/

local SPELL_EXEC(16_diamond_blizzard)
{
	// VR06;/*(ボスx座標)*/
	// VR07;/*(ボスy座標)*/
	static const u32 codebase_exec[23] =
	{
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x1f))/*(32回に1回)*/
	/*(毎フレーム発弾)*/
	//	{
		// (01) VR13 = (ra _nd()/*&0xffff*/);
		MCODE(OP0x15_RAND_VALUE, NAX, R13, NAX),	//	HATSUDAN_R13_angle65536 		= VR09;
		// (02) VR09 = (ra _nd()/*&0xffff*/);
		MCODE(OP0x15_RAND_VALUE, NAX, R09, NAX),
	//	HATSUDAN_R13_angle65536 		= VR09;
	//	HATSUDAN_R11_speed256			= (VR09&0x7fff);
		// (03) VR11 = VR09;
		MCODE(OP0x01_MOVER_PD, NAX, R11, R09),
		// (04) VR11 &= 0x7fff;
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R11, R11),
		(0x7fff),
		// (05)  (sincos256);/*(破壊レジスタ多いので注意)*/
		MCODE(OP0x10_SINCOS256, NAX, R0b, R0a),// 註記: ここだけ sin と cos が逆.
		// (06) VR07 = (VR07 << 1);VR07 >>= 1;/*(楕円の範囲で発弾)*/
		MCODE(OP0x1e_ASRM_PD, 0x01, R0b, R0b),/*(ショートメモリアドレッシング)*/
		// (07) VR06 += VR0a;/*(ボスx座標へ差分R0aを加算)*/
		MCODE(OP0x04_ADDR_PD, NAX, R06, R0a),//
		// (08) VR07 += VR0b;/*(ボスy座標へ差分R0bを加算)*/
		MCODE(OP0x04_ADDR_PD, NAX, R07, R0b),//
	//	NAX
		// (09) HATSUDAN_R11_speed256			= (t256(0.5));				/* 弾速(2.5) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(0.5)),
		// (10) HATSUDAN_R12_speed_offset		= t256(2);/*(てすと)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(2)),
		// (11) HATSUDAN_R13_angle65536 		= (VR09);/*(何故かダメ(?))*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
		// (12) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
		// (13) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_03_AOI); 	/* [青米弾] になってるのは現在 氷弾 のグラが無いから */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KOME_BASE + TAMA_IRO_03_AOI)),
		// (14) (1弾撃つ)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
	//	}
		//	radius_aaa = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//	src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		// (15)
		MCODE(OP0x02_COUNTER, 32, R08, NAX),	//	/* (32回毎に発音) */
		// (16) if (1 != VR08){goto eee;} /* (32回に1回) 発音 */
		MCODE(OP0x08_BNE_RS, (0x01), R08, (+1)),
		// (17)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE16_BOSS_KYUPIN, NAX, NAX),
//	(eee+19):
		// (18)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (17));
}

/*
	最強「エターナルフォースブリザード」
	(Eternal Force Blizzard, EFB)

	エターナルフォースブリザード
		一瞬で相手の周囲の大気ごと氷結させる
		相手は死ぬ

	2ちゃんねるのニュース速報板のスレッド(通称VIP)で考え出された魔法(必殺技？)
	あまりのクォリティの高さに様々なAAが作られる。
	また、多くの閲覧者に自分も過去に同じような事を考えていたと言うトラウマを呼び覚まさせた。
*/
