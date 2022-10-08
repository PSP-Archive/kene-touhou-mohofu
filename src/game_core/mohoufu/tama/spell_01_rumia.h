
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ルーミアのカードを定義します。
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面 道中 雑魚(妖精) 「7方向弾」[Normal]
	-------------------------------------------------------
	1周を10分割し、7方向。(180(5/10)+(1/10))
	7方向に分割。中心が自機狙い弾。
	-------------------------------------------------------
	赤弾のみ。
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面 道中 ルーミア 「16分割3連弾」
	-------------------------------------------------------
	16方向に分割。
	-------------------------------------------------------
	パターンは 3種類 ある。
	case 1: 先弾.枠付緑弾、後弾.枠付黄弾。
	case 2: 先弾.枠付青弾、後弾.なし。
	case 3: 先弾.枠付青弾、後弾.枠付赤弾。
	-------------------------------------------------------
---------------------------------------------------------*/



// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面 道中 ルーミア 「14分割5連弾」
	-------------------------------------------------------
	14方向に分割。
	R08 弾色
---------------------------------------------------------*/
local SPELL_EXEC(03_lumia02_douchuu)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))
	{
		if ((64-14) < VR10_BOSS_SPELL_TIMER)
		{
			HATSUDAN_R13_angle65536 			= ((64+VR10_BOSS_SPELL_TIMER)<<11); /* x 2048 */				/* 弾源角度65536 */
				{
	static /*const*/ u32 codebase_exec[14] =
	{
		// (01) HATSUDAN_R15_bullet_obj_type		= (VR08);			/* [弾] */
		MCODE(OP0x01_MOVER_PD, NAX, R15, R08),
		// (02) HATSUDAN_R15_bullet_obj_type		+= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);			/* [弾] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),/*(ロングメモリアドレッシング専用命令)*/
		(BULLET_MARU10_BASE + TAMA_IRO_03_AOI),
		// (03) HATSUDAN_R11_speed256				= (t256(0.75)); 		/* 偶数は低速弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
		(t256(0.75)),
		// (04) HATSUDAN_R12_speed_offset			= t256(15);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(15)),/*(テスト)*/
		// (05) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (06) HATSUDAN_R16_n_way					= (16); 							/* [16way] */
		MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (07) HATSUDAN_R17_div_angle65536 		= (int)(65536/14);		/* 分割角度(65536[360/360度]を 14 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(14)),
		// (08)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (09)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	};
	cpu_exec((u32*)&codebase_exec, (9));
				}
			VR08++;
		}
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面 道中 中ボス ルーミア 「16分割弾+3連16連弾」
	-------------------------------------------------------
	16方向に枠付青弾。
	自機狙い 3方向に赤米弾 16連弾。間隔狭い。
	-------------------------------------------------------
	R0c 	覚えとく角度。aaa_angle65536
---------------------------------------------------------*/
	#if 0/*(メモ)*/
	if (SPELL_TIME_0064-(2*16) < VR10_BOSS_SPELL_TIMER)
	{
		if ((SPELL_TIME_0064-1)!=VR10_BOSS_SPELL_TIMER) {goto rendan16;}
	//	{
		// hard 18方向(1回)
		// Luna 36方向(2回)
		/* 弾源x256 y256 ボスの中心から発弾。 */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
		VR0c = VR13;/*(自機狙い角度を覚えとく)*/
		//
		HATSUDAN_R11_speed256			= (t256(2.0));				/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [枠付き青丸弾] */
		HATSUDAN_R16_n_way				= (16);// (36);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16));// (int)(65536/(36));	/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		CPU_CALL(cpu_auto_bullet_play_default);
	//	}
	rendan16:
		if (0!=(VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2回に1回)*/
		HATSUDAN_R13_angle65536 		= VR0c;/*(覚えといた自機狙い角度を使う)*/
		HATSUDAN_R11_speed256			= (t256(3.0)) + (VR10_BOSS_SPELL_TIMER<<3); 			/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(1) ;/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [赤米弾] */
		HATSUDAN_R16_n_way				= (3);// (3);/* [nway] */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));// (int)(65536/(36)); /* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
	osimai:
		;
	}
	#endif
local SPELL_EXEC(4d_rumia_3nerai)
{
	// SPELL_TIME_0064
	//
	static /*const*/ u32 codebase_exec[35] =
	{
		// (1)	if (SPELL_TIME_0064-(2*16) < VR10_BOSS_SPELL_TIMER) {goto osimai+32;}else{goto osimai;/*何もしない*/}
		MCODE(OP0x09_BFL_RS, (SPELL_TIME_0064-(2*16)), R10, (+1)),//(start+1) 始め フローしたら分岐
		// (2)	else	{goto osimai;/*何もしない*/}// おしまい
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	//(start+1:)
		// (3)	if ((SPELL_TIME_0064-1) != VR10_BOSS_SPELL_TIMER) {goto rendan16;}
		MCODE(OP0x08_BNE_RS, (SPELL_TIME_0064-1), R10, (u8)(15)),// (rendan16+15)
		// hard 18方向(1回)
		// Luna 36方向(2回)
		/* 弾源x256 y256 ボスの中心から発弾。 */
		// (4)	 (calculate_boss_to_jiki_nerai);/* 1:いちいち作成するっぽい。 */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		// (5)	VR0c = VR13;/*(自機狙い角度を覚えとく)*/
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		// (6) HATSUDAN_R11_speed256			= (t256(2.0));				/* 弾速 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),//
		(t256(2.0)),
		// (7) HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(1)),
		// (8) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (9) HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [枠付き青丸弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_WAKU12_BASE + TAMA_IRO_03_AOI),
		// (10) HATSUDAN_R16_n_way				= (16);/* [nway] */
		MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (11) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16));	/* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(16)),
		// (12)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (13)  (cpu_auto_bullet_play_default);
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//(rendan16+15:)
		//		if (0 != (VR10_BOSS_SPELL_TIMER&1)) {goto osimai;}/*(2回に1回)*/
		// (14) VR11 = VR10 & 0x01;VR11 = (VR10_BOSS_SPELL_TIMER & 0x01);
		MCODE(OP0x1d_ANDM_PD, (0x01), R11, R10),/*(ショートメモリアドレッシング)*/
		// (15) if (0 != VR11) {goto osimai;}/*(2回に1回)*/
		MCODE(OP0x08_BNE_RS, (0x00), R11, (u8)(14)),//	(osimai+14)
		// (16) HATSUDAN_R13_angle65536 		= VR0c;/*(覚えといた自機狙い角度を使う)*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (17) HATSUDAN_R11_speed256 = (VR10_BOSS_SPELL_TIMER << 3);			/* 弾速 */
		MCODE(OP0x1f_ASLM_PD, 0x03, R11, R10),/*(ショートメモリアドレッシング)*/
		// (18) VR11 += t256(3.00);/* 弾速 */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(ロングメモリアドレッシング専用命令)*/
		(t256(3.00)),
		// (19) HATSUDAN_R12_speed_offset		= t256(1) ;/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(1)),
		// (20) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT)),
		// (21) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); 	/* [赤米弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),//
		(BULLET_KOME_BASE + TAMA_IRO_01_AKA),
		// (22) HATSUDAN_R16_n_way				= (3);// (3);/* [nway] */
		MCODE(OP0x1c_MOVEM_PD, (3), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (23) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));// (int)(65536/(36)); /* 分割角度(65536[360/360度]を 64 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(16*5)),
		// (24)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
	//(osimai+14:)//(osimai+32:)// おしまい
		// (25)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (24));
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面ボス ルーミア 夜符「ナイトバード」にちょっとだけ似たカード(予定)
	-------------------------------------------------------
	5弾目が自機狙いの 32分割16方向 弓状弾。
	-------------------------------------------------------
---a aaaa [aaa]
0000 xxxx 16回 撃つ 		青色 (0x00==((time_out)&0x20))
0001 0000 自機狙い角作成	青色 (0x00==((time_out)&0x20))
0010 xxxx 16回 撃つ 		水色
0011 0000 自機狙い角作成	水色
0100 xxxx 16回 撃つ 		青色 (0x00==((time_out)&0x20))
0101 0000 自機狙い角作成	青色 (0x00==((time_out)&0x20))
0110 xxxx 16回 撃つ 		水色
0111 0000 自機狙い角作成	水色
//
1000 0000 start
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ1。
	R09 	カウンタ2。
	R0a 	弾の基準角度。aaa_angle65536
	R0b 	弾番号。0x0fが1弾目、0x0eが2弾目。
	-------------------------------------------------------
---------------------------------------------------------*/
local SPELL_EXEC(08_rumia_night_bird)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 32, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));
//	if (0x10 == (VR10_BOSS_SPELL_TIMER & 0x1f))/* 自機狙い角作成 */
	if (1==(VR08))/* 自機狙い角作成 */
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 2, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));/*(カウンタ2)*/
		#if 1
		/* 弾源x256 y256 ボスの中心から発弾。 */
		CPU_CALL(calculate_boss_to_jiki_nerai);/* 自機狙い角作成 */
		VR0a = HATSUDAN_R13_angle65536;/* 自機狙い角 */
		#endif
		//	2048 == (65536)/(32)		: 1周を32分割した角度。
		//	8192 == (2048) * (4)		: 5弾目(4弾分の幅)。
		// 57344 == (65536) - (8192)	: 開始角度。(加算しないと誤差が出る。)
	//	VR0a += (const int)(65536-(int)((65536*4)/(32)));/* 5弾目が自機狙い */
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
		if (1==(VR09))/*(カウンタ2)*/
				{VR0a += (57344);}/* 5弾目(4弾分の幅)が自機狙い(65536-(4*(65536/32))) */
		else	{VR0a += (8192);}/* 5弾目(4弾分の幅)が自機狙い(65536+(4*(65536/32))) */
		mask65536(VR0a);
		/* 角度(65536[360/360度]を 32分割) */
		VR0b = 0x10;
	}
//	else
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x10))/* 16回 撃つ */
	if (15<(VR08))/* (16 ... 31), 16回 撃つ */
	{
		{
			/* 方向 */
			VR0b -= (1);
		//	VR0b = (VR10_BOSS_SPELL_TIMER & 0x0f);
			#if (0)/* デバッグ(自機狙い弾の色を変える) */
			if (0x0b==VR0b)/* 0x0b==5弾目 (0x0fが1弾目だから0x0bが5弾目) */
						{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);}/* 枠つき赤色弾 色変える。 */
			else
			#endif
			#if 1
			{
			//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
				if (1==(VR09))/*(カウンタ2)*/
						{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);}/* 枠つき青色弾 */
				else	{HATSUDAN_R15_bullet_obj_type = (BULLET_WAKU12_BASE + TAMA_IRO_04_MIZU_IRO);}/* 枠つき水色弾 */
			}
			#endif
		//	HATSUDAN_R11_speed256			= (t256(1.5));								/* 弾速 */
			HATSUDAN_R11_speed256			= (t256(0.75))+((16-(VR0b))<<5);	/* 弾速 */
			/* 弾速 0.75 - 2.75 倍 */
			HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
			HATSUDAN_R13_angle65536 		= (VR0a);	/* 発射中心角度 / 特殊機能(自機狙い/他) */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			/* [枠付き青色弾] [枠付き水色弾] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
		/* 次の弾の角度 */
		//	 2048 == (65536)/(32)		: 1周を32分割した角度。
		//	63488 == (65536) - (2048)	: 減算の場合(加算しないと誤差が出る。)
	//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x20))
		if (1==(VR09))/*(カウンタ2)*/
				{VR0a += (2048);}/* 角度(65536[360/360度]を 32分割) (int)(65536/(32)); */
		else	{VR0a += (63488);}/* 角度(65536[360/360度]を 32分割) (65536)-(int)(65536/(32)); */
		mask65536(VR0a);
		//
			static const u32 codebase888[2-1] =
			{
				MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
			//	NAX/*(終了)*/
			};
			cpu_exec((u32*)&codebase888, (1));
	}
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	紅1面ボス ルーミア 闇符「ディマーケイション」にちょっとだけ似たカード(予定)
	-------------------------------------------------------
	ルーミア交差弾:
	交差弾にも良く見ると種類があるような気がしてきた。
	闇符「ディマーケイション」の交差弾は。
		1. 一定距離に飛び出す。(通常減速弾)
		2. 弾停止。
		3. 突然 (弾グラが)90度回転する。(極彩颱風みたいな感じで滑らかではあるが、すばやく回転)
		4.弾グラが傾きながら弾が広がる。
	-------------------------------------------------------
	16
	-------------------------------------------------------
	0010 01--	0x027f == 64*10-1
	0010 00--	0x023f == 64* 9-1
				...
	0000 00--	0x003f == 64* 1-1
	-------------------------------------------------------
640==0x280
512==0x200
[15]	32*0		５
[14]	32*1		６
[13]	32*2		３
[12]	32*3		４
[11]	32*4		１
[10]	32*5		２
[09]	32*6		休み
[08]	32*7		休み
[07]	32*8		休み
[06]	32*9			赤弾
[05]	32*10		休み
[04]	32*11			緑弾
[03]	32*12		休み
[02]	32*13			青弾
[01]	32*14		休み
[00]	32*15		休み

---------------------------------------------------------*/


/*---------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
	交差弾。反時計回り。
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
	交差弾。時計回り。
256 ... 	: 8[0x07<<5] RUMIA_normal: 通常弾へ変身する
224 ... 255 : 7[0x08<<5] RUMIA_kousa: 交差弾
192 ... 223 : 6[0x09<<5] RUMIA_kousa: 交差弾
160 ... 191 : 5[0x0a<<5] RUMIA_kousa: 交差弾
128 ... 159 : 4[0x0b<<5] RUMIA_kousa: 交差弾
128 ... 159 : 4[0x0b<<5] RUMIA_kousa: 交差弾
 64 ...  95 : 2[0x0d<<5] RUMIA_kousa: 交差弾
 32 ...  63 : 1[0x0e<<5] RUMIA_rot:   急激に曲がる。
  0 ...  31 : 0[0x0f<<5] RUMIA_nop	  発弾後、すぐは何もしない
x---------------------------------------------------------*/
local TAMA_FUNC(rumia_danmaku_01_callback)
{
	#if (1)/*(ok!)*/
	const void *aaa[8] =
	{
&&RUMIA_nop, // [必要]無いと動作しない。
&&RUMIA_normal, //
&&RUMIA_kousa, //
&&RUMIA_kousa, //

&&RUMIA_kousa, //
&&RUMIA_kousa, //
&&RUMIA_rot, // 急激に曲がる。
&&RUMIA_nop, // 発弾後、すぐは何もしない		;/* 発弾後、すぐは何もしない==直進弾 */
	};
	goto *aaa[(src_tama->jyumyou & (0x07<<5))>>5];
	#endif
RUMIA_normal:
		/* (通常弾へ変身する==画面内では弾は消えない) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		goto RUMIA_nop;
RUMIA_rot:
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			/*(模倣風では下CCWなので、正方向が反時計回り)*/
		//	{src_tama->rotationCCW1024 += (10);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
			{src_tama->rotationCCW65536 += (10<<6);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
		else
			/*(模倣風では下CCWなので、負方向が時計回り)*/
		//	{src_tama->rotationCCW1024 -= (10);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
			{src_tama->rotationCCW65536 -= (10<<6);}/* 90/360 度 曲げる(32カウントかけて曲げる。256==8*32) */
		goto RUMIA_nop;
RUMIA_kousa:
	//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
	//			{src_tama->rotationCCW1024++;}/*(交差弾なので曲げる)*/
	//	else	{src_tama->rotationCCW1024--;}/*(交差弾なので曲げる)*/
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
				{src_tama->rotationCCW65536 += (1<<6);}/*(交差弾なので曲げる)*/
		else	{src_tama->rotationCCW65536 -= (1<<6);}/*(交差弾なので曲げる)*/
RUMIA_nop:
		;
	//
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}


	#if (0)
	/* 発弾後 512 カウント以上は弾を消す。 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-512) > src_tama->jyumyou/*(寿命なので自動で減る)*/)/* 発弾エフェクト後から[512]カウント以上経過した弾 */
	{
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
	#endif


/*---------------------------------------------------------
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
	連弾。自機狙い。
	-------------------------------------------------------
	自機を狙わない場合があるが、原因が良く解からない。
---------------------------------------------------------*/
local TAMA_FUNC(rumia_danmaku_02_callback)/* 連弾 */
{
	/* 32 カウントなら */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-32) == src_tama->jyumyou)/* 発弾エフェクト後から[32]カウント経過した弾 */
	{
		VR06	= (src_tama->center.x256);
		VR07	= (src_tama->center.y256);
		CPU_CALL(calculate_jiki_nerai);/* 自機狙い角作成 */
		#if 0
		/*(ダメ)*/
	//	src_tama->rotationCCW1024 = (0);//描画用角度(deg65536to1024(HATSUDAN_R13_angle65536));/* 自機狙い角 */
		#else
		/*(特別ケース、このまま(見た目)の角度で移動する)*/
	//	src_tama->rotationCCW1024 = (deg65536to1024(HATSUDAN_R13_angle65536));/* 自機狙い角 */
		src_tama->rotationCCW65536 = ( (HATSUDAN_R13_angle65536));/* 自機狙い角 */
		/* ここの描画用角度は後で利用する。 */
		#endif
		//
		src_tama->TR01_hatudan_speed65536	= (t256(2.0)<<8);			/* 弾速 */
		//
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data	= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}


/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	-------------------------------------------------------
	R08 	カウンタ。(32回に1回発弾する)
	R09 	カウンタ。(16種類)
	R0a 	x[ワークで一時使用temp]
	R0b 	[一時使用temp]弾角度(交差弾)。	弾角度(連弾)。
	R0c 	自機狙い角度保存用
	R0d 	難易度定数1(分割数、交差弾[32])
	R0e 	難易度定数2(分割角、交差弾[65536/32])
	-------------------------------------------------------
	R15 	弾色(交差弾)。
	-------------------------------------------------------
	VR03_i	ループ用 i (難易度別に残り回数を設定。)
---------------------------------------------------------*/

// カードスクリプト語では「else」は無い。
local SPELL_EXEC(29_rumia_demarcation)
{
	static const u32 codebase_exec[90/*-6*/] =
	{
		// (01) counter(32, VR08);	//if ((0x1f)==(VR10_BOSS_SPELL_TIMER & 0x1f))
		MCODE(OP0x02_COUNTER, 32, R08, NAX),
		// (02) if (0 != VR08)	{goto oyasumi+0;}
		MCODE(OP0x08_BNE_RS, (0), R08, (u8)(+57)),// (oyasumi+38)
		// (03) counter(16, VR09);
		MCODE(OP0x02_COUNTER, 16, R09, NAX),
		/*---- ----*/
		// (04) VR16 = hairetu[VR09];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R09, R16, (+16)),
		(+38), (+38), (+39), (+38),//(oyasumi+38:)		/* お休み */
		(+39), (+38), (+39), (+38),// (kousadan+39:)
		(+38), (+38), (+0), (+0), // 連弾(rendan+0:)
		(+0), (+0), (+0), (+38), /* 最後の方は時間が足りないので、変身処理が間に合わない。 */
		// (05)
		MCODE(OP0x06_BRAR_NN, NAX, NAX, R16),	// 策定案3. VRB の相対アドレスにジャンプ。
		/*---- ----*/
		// (06) if (9 < VR09)	/* [10 ... 14] 自機狙い連弾 */
		//	dimmer_shot_02_rendan();
		/* ★ 自機狙い連弾: 記憶だけで作りがちなので、原作でチェック。normalの場合、飛んでくる連弾は４回だった。 */
	//(rendan+0:)
		// 自機狙い角作成。
		// (06) (calculate_boss_to_jiki_nerai);/* 自機狙い角作成 */ /* 弾源x256 y256 ボスの中心から発弾。 */
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
		//	VR0c = HATSUDAN_R13_angle65536;/* 自機狙い角(一時保存) */
		// (07) VR0c = VR13;/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R0c, R13),
		// (08) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_02)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(ロングメモリアドレッシング)*/
		((DANMAKU_LAYER_02)|(TAMA_SPEC_8000_NON_TILT)),
		// (09) HATSUDAN_R15_bullet_obj_type	= BULLET_WAKU12_BASE + TAMA_IRO_03_AOI; 		/* [枠付き青色弾] [枠付き水色弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(ロングメモリアドレッシング)*/
		(BULLET_WAKU12_BASE + TAMA_IRO_03_AOI),
		// (10) VR02_j = 6;/*(r41-遅すぎるから 6回 に修正。 8 回ループして追加)*/
		MCODE(OP0x1c_MOVEM_PD, (6), R02_j, NAX),/*(ショートメモリアドレッシング)*/
	//	MCODE(OP0x1c_MOVEM_PD, (8), R02_j, NAX),/*(ショートメモリアドレッシング)*/
	//		loop_j:
		//		HATSUDAN_R12_speed_offset			= (VR02_j << 6);//t256(0);/*(テスト)*/
		// (11) HATSUDAN_R12_speed_offset			= (VR02_j << 8);//t256(0);/*(テスト)*/
		MCODE(OP0x1f_ASLM_PD, 0x08, R12, R02_j),/*(ショートメモリアドレッシング)*/
		// (12) VR0b = VR0c;/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R0c),
		// (13) VR0a = ((VR10) & 0x20);
		MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (14) if (0 != VR0a) {goto (aaa+3);}// if (0==VR0a) {goto (aaa+3);}
		MCODE(OP0x08_BNE_RS, (0), R0a, (+3)),//
		// (15) {VR0b += (57344);}/* 角度(65536[360/360度]を 32分割) (int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(57344),
		// (16) goto (bbb+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
//aaa+3:// (17) else {VR0b += (8192);}/* 角度(65536[360/360度]を 32分割) (65536)-(int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(8192),
//bbb+2:// (18) (811aaa8 or bbb9)	mask65536(VR0b);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0b),
		(0xffff),
		// (19) VR03_i = 16;/*(16 回ループして追加)*/
		MCODE(OP0x1c_MOVEM_PD, (16), R03_i, NAX),/*(ショートメモリアドレッシング)*/
		//	loop_i://	(ddd-16)loop_i:;
		//	VR11 = VR03_i;
		//	HATSUDAN_R11_speed256				= (t256(1.5));								/* 弾速 */
		//	HATSUDAN_R11_speed256				= (t256(0.75)) + ((16 - VR0a) << 5);		/* 弾速 */
		//	VR11 = (16 - VR11);
		// (20) VR11 = (VR03_i << 5);
		MCODE(OP0x1f_ASLM_PD, 0x05, R11, R03_i),/*(ショートメモリアドレッシング)*/
		// (21) VR11 = VR11 + (t256(0.75));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(ロングメモリアドレッシング専用命令)*/
		(t256(0.75)),
		// (22) HATSUDAN_R13_angle65536 		= (VR0b);/* 自機狙い角 */	/* 発射中心角度 / 特殊機能(自機狙い/他) */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (23) (1弾撃つ)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		// (24) VR0a = ((VR10) & 0x20);
		MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (25) if (0 != VR0a) {goto (aaa+3);}// if (0==VR0a) {goto (aaa+3);}
		MCODE(OP0x08_BNE_RS, (0), R0a, (+3)),//
		// (26) {VR0b += (2048);}/* 角度(65536[360/360度]を 32分割) (int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(2048),
		// (27) goto (bbb+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
//aaa+3:// (28) else {VR0b += (63488);}/* 角度(65536[360/360度]を 32分割) (65536)-(int)(65536/(32)); */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(ロングメモリアドレッシング専用命令)*/
		(63488),
//bbb+2:// (29) (19aaa8 or bbb9) mask65536(VR0b);
		MCODE(OP0x1d_ANDM_PD, LONG_MEMORY_ADDRESSING, R0b, R0b),
		(0xffff),
		// (30) VR03_i--;/*(残り回数減らす。)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(インデックス付)*/
		// (31) if (0 != (s32)VR03_i) {goto loop_i;}/*(残り回数があればループ。)*/if (0 < (s32)VR03_i) {goto loop_i;}
		MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-16)),//	(ddd-16)loop_i:;
		// (32) VR02_j--;/*(残り回数減らす。)*/
		MCODE(OP0x01_MOVER_PD, (u8)(-1), R02_j, R02_j), /*(インデックス付)*/
		// (33) if (0 != (s32)VR02_j) {goto loop_j;}/*(残り回数があればループ。)*/if (0 < (s32)VR02_j) {goto loop_j;}
		MCODE(OP0x08_BNE_RS, (0x00), R02_j, (u8)(-30)),//	(ddd-16)loop_i:;
		// (34)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE14_SAKUYA_SHOT02, NAX, NAX),
		// (35)
	//oyasumi+38:
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	//	goto oyasumi;
	//	kousadan+39:
		/* ★ 交差弾。 青弾 / 緑弾 / 赤弾 */
		/*---- ----*/
		#if 0// 難易度デコード命令。(拡張案.A)
		// (01) VR15 = (VR09 >> 1);
		MCODE(OP0x1e_ASRM_PD, 0x01, R15, R09),/*(ショートメモリアドレッシング)*/
		// (02) VR15 = [難易度別定数];
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R15, R15(拡張案.A)/*NAX*/),/*(分割数、交差弾)*/
		PACK_NAN_IDO_CONST((0), (TAMA_IRO_03_AOI), (TAMA_IRO_05_MIDORI), (TAMA_IRO_01_AKA)),	/* 分割数(r41-) */
		#else
		// (36) VR15 = hairetu[VR09];goto (bbb+16);
		MCODE(OP0x0a_BRA_TABLE, R09, R15, (+8)),// (+16)
		(0), (0),
		(TAMA_IRO_03_AOI), (0),
		(TAMA_IRO_05_MIDORI),  (0),
		(TAMA_IRO_01_AKA), (0),
	//	(0), (0), (0), (0),// 絶対にこないのでケチる。
	//	(0), (0), (0), (0),// 絶対にこないのでケチる。
		#endif
		/*---- ----*/
		// (37) [40]VR0b = (VR15 & 0x06);
		MCODE(OP0x1d_ANDM_PD, 0x06, R0b, R15),/*(ショートメモリアドレッシング)*/
		//	0x06,
		// (38) VR0b = (VR0b << 8);
		MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(ショートメモリアドレッシング)*/
		//	0x08,
		// (39) HATSUDAN_R15_bullet_obj_type		+= BULLET_KOME_BASE;		/* [枠つき青色弾] [枠つき水色弾] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),/*(ロングメモリアドレッシング専用命令)*/
		BULLET_KOME_BASE,
		// (40) HATSUDAN_R11_speed256		= t256(1.0);/* 弾速 (t256(1.5)) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(ロングメモリアドレッシング)*/
		(t256(1.0)),
		// (41) HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(ロングメモリアドレッシング)*/
		(t256(0)),
		// (42) HATSUDAN_R13_angle65536 		= (VR0b);/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (43) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_01)|(0)|(TAMA_SPEC_0000_TILT),
		// (44) HATSUDAN_R16_n_way = VR0d;	/* [32way] */
		MCODE(OP0x01_MOVER_PD, NAX, R16, R0d),
		// (45) HATSUDAN_R17_div_angle65536 = VR0e; /* 分割角度(65536/32 ) １周を32分割した角度 */
		MCODE(OP0x01_MOVER_PD, NAX, R17, R0e),
		// (46)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (47) HATSUDAN_R13_angle65536 		= (VR0b);/* 自機狙い角 */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (48) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),//
		(DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_0000_TILT),
		// (49)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		// (50)
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
		// (51)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (4096));/*(テキトーだけど大体これくらい。ちょっと負荷高すぎるかな？)*/
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
	/* 上広タイプ */
local SPELL_INIT(29_rumia_demarcation)
{
	static const u32 codebase_init[3] =
	{
		// (01) // R0d = 難易度別定数1;(分割数、交差弾[32])
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(分割数、交差弾)*/
		PACK_NAN_IDO_CONST((12), (20), (32), (48)), 	/* 分割数(r41-) */
		// (02) // R0e = 65536 / R0d; = 難易度別定数2;(分割角、交差弾[65536/32])
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、交差弾)*/ 	/* 分割角度 */
	//	NAX/*(初期化終了)*/
	};
	cpu_exec((u32*)&codebase_init, (2));//
}
	//	PACK_NAN_IDO_CONST((24), (28), (32), (32)), 	/* 分割数(-r40) */
	/*
	LUNATIC:
		(48)なら、視点が連弾にあっても大体避けれる。
		(交差弾を)見てれば(64)余裕。(交差弾を)見てないと(視点が連弾にあると)死ぬ。
		まだ 2面ですし、トータルで考えて (48) の方が良いかな？
		(64)だと LUNATIC みたいになっちゃう。いえ LUNATIC なんですが。
	*/

/*
	(r41-)の調整方針(予定):
	EASY:		交差弾は避けられない(と断定)。弾幕シューの基本的な避け方を知らない(と断定)。→ EASY は 弾幕関係なくて、難易度下げて普通のシューティングにする事にしよう。
	NORMAL: 	交差弾は避けかたが判ってない(判ってないがある程度避けれる)。弾幕シューはやった事が無いかも。
	HARD:		交差弾は避けられる(避け方を知ってる)。 弾幕シュー(と東方projyect)の(おやくそく的な)避け方を知ってる。(模倣風では HARD が 実質NORMAL)
	LUNATIC:	交差弾は簡単(だけど珠にミスる)。(見てれば100%避けれるように調整) HARD で 物足りない人向け。(HARD は難しく出来ない)
*/

	//{
	//	#define P0x80		0x80
	//	#define YASUMI000	0x00
	//	const u8 ttt[16] =
	//	{
	//	/*0x0f*/0	YASUMI000,	/* 休み */
	//	/*0x0e*/1	YASUMI000,	/* 休み */
	//	/*0x0d*/2	(BULLET_KOME_03_AOI    - BULLET_KOME_00_SIRO),		/* 青弾 */
	//	/*0x0c*/3	YASUMI000,	/* 休み */
	//	/*0x0b*/4	(BULLET_KOME_05_MIDORI - BULLET_KOME_00_SIRO),		/* 緑弾 */
	//	/*0x0a*/5	YASUMI000,	/* 休み */
	//	/*0x09*/6	(BULLET_KOME_01_AKA    - BULLET_KOME_00_SIRO),		/* 赤弾 */
	//	/*0x08*/7	YASUMI000,	/* 休み */
	//	/*0x07*/8	YASUMI000,	/* 休み */
	//	/*0x06*/9	YASUMI000,	/* 休み */
	//	/*0x05*/10	P0x80,	/* 自機狙い連弾 */
	//	/*0x04*/	P0x80,	/* 自機狙い連弾 */
	//	/*0x03*/	P0x80,	/* 自機狙い連弾 */
	//	/*0x02*/	P0x80,	/* 自機狙い連弾 */
	//	/*0x01*/	P0x80,	/* 自機狙い連弾 */
	//	/*0x00*/	P0x80,	/* 自機狙い連弾 */
	//	};
	//	tama_type = ttt[((VR09/*(VR10_BOSS_SPELL_TIMER)>>5*/)&0x0f)];
	//}

// ==================================== [スペカ境界] ==================================== //
