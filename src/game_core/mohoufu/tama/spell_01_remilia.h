
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	レミリア っぽいカードを定義します。
---------------------------------------------------------*/
/*---------------------------------------------------------
	ショット発弾サブ。
	-------------------------------------------------------
	C言語の場合は共通サブ。
	スクリプト化した場合は、コピペする。
	-------------------------------------------------------
	使用レジスタ
	cg_BOSS_DATA_38_angleCCW65536; 引渡し、狙い基準角度
---------------------------------------------------------*/
local BOSS_EXEC(remilia_shot00)
{
	// ■  [大玉弾]
//	HATSUDAN_R11_speed256			= (t256(3.5));						/* 弾速 */
//	HATSUDAN_R11_speed256			= (t256(2.25)); 					/* 弾速 */
	HATSUDAN_R11_speed256			= (t256(8.00)); 					/* 弾速 */
//	HATSUDAN_R12_speed_offset		= -t256(1);/* 減速弾？ */
	HATSUDAN_R12_speed_offset		= -t256(4);/* 減速弾？ */
	HATSUDAN_R13_angle65536 		= cg_BOSS_DATA_38_angleCCW65536;/* 引渡し、狙い基準角度 */
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_1000_EFFECT_MIDDLE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	HATSUDAN_R15_bullet_obj_type	= BULLET_OODAMA32_01_AKA;			/* [赤大玉弾] */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		// ■  [中玉弾]
	//	HATSUDAN_R11_speed256			= (t256(6.00)); 					/* 弾速 */
		HATSUDAN_R12_speed_offset		= -t256(2);/* 減速弾？ */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_01_AKA);			/* [赤大中弾] */
	{
		u32 rrr;
		rrr = (ra_nd());
		for (VR03_i=0; VR03_i<(8*3); VR03_i++)
		{
			rrr += 13579;
			rrr &= 0xffffffffu;
			HATSUDAN_R11_speed256		= (t256(5.00)+(rrr&0x1ff)); 					/* 弾速 */
			HATSUDAN_R13_angle65536 	= cg_BOSS_DATA_38_angleCCW65536 + ((rrr) & ((65536/8)-1)) - ((65536/16)-1);/* 自機狙い角 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
		// ■  [小玉弾]
	//	HATSUDAN_R11_speed256			= (t256(4.00)); 					/* 弾速 */
		HATSUDAN_R12_speed_offset		= -t256(1);/* 減速弾？ */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);				/* [赤大中弾] */
		for (VR03_i=0; VR03_i<(16*2); VR03_i++)/*(16)*/
		{
			rrr += 1234567;
			rrr &= 0xffffffffu;
			HATSUDAN_R11_speed256		= (t256(2.00)+(rrr&0x1ff)); 					/* 弾速 */
			HATSUDAN_R13_angle65536 	= cg_BOSS_DATA_38_angleCCW65536 + ((rrr) & ((65536/4)-1)) - ((65536/8)-1);/* 自機狙い角 */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
	#if (1)
	CPU_CALL(cpu_auto_bullet_play_default);
	#endif
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]	レミリア 通常攻撃2 っぽいもの
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。基本的に24回に一回処理。
	R09 	撃つ回数制限。
	R0a 	加算角度。
	R0b 	弾角度(基準位置を保持)。
---------------------------------------------------------*/
//local SPELL_INIT(1f_remilia_kougeki2)
//{
//}
/*---------------------------------------------------------
	レミリア 通常攻撃2 っぽいもの
	-------------------------------------------------------
	1秒撃ったら、3秒休む(移動)。

	REG_0f	難易度
	REG_10	ボスタイマー
---- ---- ---- ----
0000 0011 1111 1111
---------------------------------------------------------*/

local SPELL_EXEC(1f_remilia_kougeki2)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 24, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));// 基本的に24回に一回処理。(撃つ)
	if (0==(VR08))
	{
		static const u32 codebase222[2] =
		{
			MCODE(OP0x02_COUNTER, 16, R09, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (1));// 16, 最大10(10.666==256/24)なので16はダミー値。
		if (1==(VR09))	/* 始めての場合 */
		{
			CPU_CALL(calculate_jiki_nerai);/* 自機狙い角作成 */
			cg_BOSS_DATA_38_angleCCW65536		= HATSUDAN_R13_angle65536;/* 自機狙い角 */
			VR0a	= (int)( ((65536/12)));/*(table3[]加算角度を設定)*/
			if ((cg_BOSS_DATA_3a_center_x256) & 0x100)
			{
				VR0a	= -VR0a;/*(table3[]加算角度を設定)*/
			}
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]加算角度を移動)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]加算角度を移動)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]加算角度を移動)*/
			cg_BOSS_DATA_38_angleCCW65536		-= VR0a;/*(table3[]加算角度を移動)*/
			VR0b = cg_BOSS_DATA_38_angleCCW65536;/*(始めの角度を設定)*/
		}
		if (0<(6-1)+(cg_VR20_game_difficulty)-(VR09))
		{
			// easy 	は 6回 3回 0000
			// normal	は 7回 5回 0001
			// hard 	は 8回 7回 0010
			// lunatic	は 9回 9回 0011
			/*(保持角度を移動)*/
			{
				VR0b	+= VR0a;/*(table2[]保持角度を移動)*/
				/*(基準角度に保持角度を設定)*/
				cg_BOSS_DATA_38_angleCCW65536		= VR0b;/*(基準角度を指定)*/
			}
			remilia_shot00();
		}
	}
}

#if 0
	if (0x80 == (VR10_BOSS_SPELL_TIMER & 0x80))/* 後半 */
	{
	//	if (0xc0 == (VR10_BOSS_SPELL_TIMER & 0xc0))
		if (0xc0 == (VR10_BOSS_SPELL_TIMER & 0xc7))/* ８回に一回 */
		{
			#if 0
			/* 撃つターン 8弾 */
					if (0x0000 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* 自機狙い撃ち */
			else	if (0x0100 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* CW 撃ち */
			else	if (0x0200 == (VR10_BOSS_SPELL_TIMER & 0x30)) {remilia_shot00(src);}	/* CCW 撃ち */
			else/*	if (0x0300 == (VR10_BOSS_SPELL_TIMER & 0x30)) */{remilia_shot00(src);}	/* 自機狙い撃ち */	/* 一気撃ち */
			#endif
		}
	}
#endif


/*---------------------------------------------------------

大弾＆中弾＆小弾乱射
冥符「紅色の冥界」
128way螺旋状高速ナイフ弾
赤針弾ばら撒き→９WAY赤大弾連射→全方位12way炎弾連射（ループ）
紅符「スカーレットシュート」
---------------------------------------------------------*/


/*---------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。(8回に1回発弾する)
	R0a 	保持角度。
	-------------------------------------------------------
128way螺旋状高速ナイフ弾
	拡散型全方位ナイフ弾
	80分割弾 == (8way[hi to 0]+8way[slow to 0]) x 5way(5分割)
	-------------------------------------------------------

---------------------------------------------------------*/
//local SPELL_EXEC(07_80way_dual_five)
local SPELL_EXEC(44_remilia_rasen_knife)/* 鈴仙でなくて螺旋です。 */
{
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x01))
	{
				HATSUDAN_R12_speed_offset		= t256(1/*0*/);/*(テスト)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
				HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI+1;				/* [akaナイフ弾] */
				HATSUDAN_R13_angle65536 		= VR0a; 		/* 角度 */
		{	/* 1周を65536分割した角度 */
			for (VR03_i=0; VR03_i<(4); VR03_i += (1) ) /* [4分割] */	/* 角度(65536[90/360度]を 4 分割) */
			{
				HATSUDAN_R13_angle65536 += (65536/4);			/* 角度 */
				mask65536(HATSUDAN_R13_angle65536);
				//
				HATSUDAN_R11_speed256			= (t256(2.00) );	/* 速弾 t256(3.00) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				//
				HATSUDAN_R11_speed256			= (t256(2.40) );	/* 高速弾 t256(3.14) */
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
		}
				HATSUDAN_R13_angle65536 -= (65536/128); 				/* 次の角度 */
				VR0a		= HATSUDAN_R13_angle65536;			/* 角度を保持 */
	}
		#if (0)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
}

/*---------------------------------------------------------
	呪詛「ブラド・ツェペシュの呪い」
	-------------------------------------------------------
	「レッドマジック」
	-------------------------------------------------------
	珠置き共通サブ
	-------------------------------------------------------
	R08 	カウンタ。弾置き間隔
	R0b 	発弾後、集まるX座標(t256形式)
	R0c 	発弾後、集まるY座標(t256形式)
	-------------------------------------------------------
	C言語の場合は共通サブ。
	スクリプト化した場合は、コピペする。
---------------------------------------------------------*/
local TAMA_FUNC(remilia_common_tama_oki_sub)
{
		src_tama->TR01_hatudan_speed65536	+= (1<<8);			/* 弾速 */
	//
	//	if (0==(src_tama->jyumyou&0x0f))/*16回に1回弾を置く*/
	//	if (0==(src_tama->jyumyou&0x07))/*8回に1回弾を置く*/
		if (0 == VR08)
		{
			//
			VR04	= (VR0b);
			VR05	= (VR0c);
			set_REG_DEST_XY(src_tama);			/* 弾源x256 y256 弾obj中心から発弾。 */
			CPU_CALL(cpu_VR_angleCCW65536_src_nerai);//_bbb(zzz_player, dest);
	//[重複]set_REG_DEST_XY(src_tama);			/* 弾源y256 弾obj中心から発弾。 */
			HATSUDAN_R11_speed256			= t256(0);	/* 弾速 */
			HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
		//	HATSUDAN_R13_angle65536 		= (0);	/* 基準角度 */
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_02)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_01_AKA);		/* [赤弾] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
}

/*---------------------------------------------------------
	呪詛「ブラド・ツェペシュの呪い」
	-------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(brp_tamaoki_danmaku_01_callback)/* 珠置き */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-0) == src_tama->jyumyou)/* 発弾エフェクト後から[0]カウントの弾 */
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* テキトー */
		CPU_CALL(cpu_voice_play);
	}
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* 発弾エフェクト後から[224]カウント未満の弾 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* 発弾エフェクト後から[225]カウント未満の弾 */
	{
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{	/*CW(時計回り)*/
		//	src_tama->rotationCCW1024 -= (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 -= (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 -= (3<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		else
		{	/*CCW(反時計回り)*/
		//	src_tama->rotationCCW1024 += (6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		//	src_tama->rotationCCW1024 += (3);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
			src_tama->rotationCCW65536 += (3<<6);/* 90/360 度 曲げてみるテスト(32カウントかけて曲げる。256==8*32) */
		}
		remilia_common_tama_oki_sub(src_tama);
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
	「レッドマジック」
	-------------------------------------------------------
	[callback t01 section: 弾幕レイヤーグループ(1)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(red_magic_tamaoki_danmaku_01_callback)/* 珠置き */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-0) == src_tama->jyumyou)/* 発弾エフェクト後から[0]カウントの弾 */
	{
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* テキトー */
		CPU_CALL(cpu_voice_play);
	}
	/*(225==1+224==1+7*32)*/
//	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-224) < src_tama->jyumyou)/* 発弾エフェクト後から[224]カウント未満の弾 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-225) < src_tama->jyumyou)/* 発弾エフェクト後から[225]カウント未満の弾 */
	{
		if (0!=(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{
			/*(左右の壁で反射する。)*/
			if (src_tama->center.x256 < t256(32))
			{
				/*(一度しか反射しない)*/
			//	src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			//	src_tama->rotationCCW1024 -= (1024/2);/* 180/360 度 曲げてみるテスト */
				goto red_magic_hansya_syori;
			}
			else
			if (src_tama->center.x256 > t256(32)+t256(320) )
			{
			red_magic_hansya_syori:
				/*(一度しか反射しない)*/
				src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_01)|(0)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
			//	src_tama->rotationCCW1024 -= (1024/2);/* 180/360 度 曲げてみるテスト */
			//	src_tama->rotationCCW1024 = (1024)-(src_tama->rotationCCW1024); /* 反転[※1] */
				src_tama->rotationCCW65536 = (65536)-(src_tama->rotationCCW65536); /* 反転[※1] */
			}
		}
		remilia_common_tama_oki_sub(src_tama);
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
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(remilia_tahane_danmaku_02_callback)/* 珠跳ね */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-128) == src_tama->jyumyou)/* 発弾エフェクト後から[128]カウント の弾 */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* 弾速 */
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

local void tamaoki_kankaku_void(void)
{
	//	#define TAMA_DATA_10_TAMA_OKI_KANKAKU
	VR08--;
	if (0 > VR08)
	{
		VR08 = VR09;//[定数1]n回に一回弾を置く。
	}
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]	呪詛「ブラド・ツェペシュの呪い」
	-------------------------------------------------------
	現在(r35)のスペカシステムの場合、仕様上
	スペカがまたがるレジスタ値を保持できない。
	(スペカが始まるタイミングで強制的にレジスタが0クリアされてしまう為)
	-------------------------------------------------------
	ナイフは13way → 18wayに増える。
	-------------------------------------------------------
	使用レジスタ:
	R09 = 難易度別定数1;
	R0d:	発弾数
	R0e:	分割数
---------------------------------------------------------*/
local SPELL_EXEC(42_remilia_vlad_tepes)
{
	if ((SPELL_TIME_0256-1) == VR10_BOSS_SPELL_TIMER) /*(一番始め)*/
	{
		HATSUDAN_R11_speed256			= t256(1.0);	/* 弾速 */
		HATSUDAN_R12_speed_offset		= t256(5);/*(テスト)*/
		HATSUDAN_R13_angle65536 		= 0;	/* 基準角度 */
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|((ra_nd()) & TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= BULLET_KNIFE20_04_AOI;		/* [青ナイフ弾] */
		#if 0
	//	HATSUDAN_R16_n_way				= (13); 	/* [13way] */		/* 発弾数 */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(13));	/* 分割角度(65536[360/360度]を 13 分割) */
		#else/*(とりあえず)*/
		HATSUDAN_R16_n_way				= (VR0d); 	/* [13way] */		/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= (VR0e);	/* 分割角度(65536[360/360度]を 13 分割) */
		#endif

		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		u32 aaa = ra_nd();
		VR0b = ((aaa	)&0xff00) + t256(((480-128-32-256)/2));
		VR0c = ((aaa<<8 )&0xff00) + t256(((272-256)/2));
		#if (1)
		AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"ボス溜め1",		/* r	うぃーん音 */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
		CPU_CALL(cpu_voice_play);
		#endif
	}
	tamaoki_kankaku_void();
}


/*---------------------------------------------------------
	[execute section: 発弾セクション]	「レッドマジック」
	-------------------------------------------------------
	現在(r35)のスペカシステムの場合、仕様上
	スペカがまたがるレジスタ値を保持できない。
	(スペカが始まるタイミングで強制的にレジスタが0クリアされてしまう為)
	-------------------------------------------------------
	使用レジスタ:
	R0b 	発弾後、集まるX座標(t256形式)
	R0c 	発弾後、集まるY座標(t256形式)
	R0e 	分割角度
---------------------------------------------------------*/
local SPELL_EXEC(43_remilia_red_magic)
{
	/*(呪詛「ブラド・ツェペシュの呪い」に比べて、「レッドマジック」は更新間隔が短い。(だんだん早くなる？))*/
	if ((SPELL_TIME_0192-1) == VR10_BOSS_SPELL_TIMER) /*(一番始め)*/
	{
		/*(呪詛「ブラド・ツェペシュの呪い」に比べて、「レッドマジック」の大玉弾の動きは非常に遅い)*/
		HATSUDAN_R11_speed256			= t256(0.5);	/* 弾速(r40==0.5, r39==1.0) */
		HATSUDAN_R12_speed_offset		= t256(3);/*(テスト)*/
	//	HATSUDAN_R13_angle65536 		= (65536/4);	/* 基準角度(水平に撃つ。左右が基準０度) */
		HATSUDAN_R13_angle65536 		= ((ra_nd()) & 0x1fff);	/* 基準角度(?)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_01_AKA); 	/* [紫大弾] */
		HATSUDAN_R16_n_way				= VR0d;// (10); /* [10way] */		/* 発弾数 */
		HATSUDAN_R17_div_angle65536 	= VR0e;// (int)(65536/(10)); /* 分割角度(65536[360/360度]を 10 分割) */
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
		u32 aaa = ra_nd();
		VR0b = ((aaa	)&0xff00) + t256(((480-128-32-256)/2));
		VR0c = ((aaa<<8 )&0xff00) + t256(((272-256)/2));
		#if (1)
		AUDIO_18_voice_number	= VOICE17_BOSS_TAME01;	//	"ボス溜め1",		/* r	うぃーん音 */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;
		CPU_CALL(cpu_voice_play);
		#endif
	}
	tamaoki_kankaku_void();
}
/*---------------------------------------------------------
	[initialize section: 初期化セクション]	呪詛「ブラド・ツェペシュの呪い」
	-------------------------------------------------------
	R09[定数1]n回に一回弾を置く。
---------------------------------------------------------*/
//	TAMA_DATA_10_TAMA_OKI_KANKAKU	= (0);// カウンタ
//	VR04_NAN_IDO_DECODE = ((16)-((cg_VR20_game_difficulty)<<2));//[定数1]n回に一回弾を置く。
//	VR04_NAN_IDO_DECODE = NAN_IDO_DECODE((16), (12), (8), (4));//[定数1]n回に一回弾を置く。
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((16), (12), (8), (4));//[定数1]n回に一回弾を置く。
//	VR04_NAN_IDO_DECODE = PACK_NAN_IDO_CONST((16), (10), (8), (4));//[定数1]n回に一回弾を置く。
//	 (nan_ido);
//	VR09	= VR04_NAN_IDO_DECODE;
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[定数1]雨の速度
//	VR0a	= ((1024/2)+(1024/24)+(cg_VR20_game_difficulty<<3));//[定数2]赤青クナイが曲がる角度

local SPELL_INIT(42_remilia_vlad_tepes)
{
	//
	#define R32 R32_BOSS_DATA_chuu_boss_mode
	static const u32 codebase_init[7] =
	{
		// (1) VR0d = cg_BOSS_DATA_32_chuu_boss_mode;
		MCODE(OP0x01_MOVER_PD, NAX, R0d, R32),
		// (2)	// R09 = 難易度別定数1;
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(分割数、交差弾)*/
		PACK_NAN_IDO_CONST((16), (10), (8), (4)), 	/* 分割数(r41-) */
		// (3)	// R0e = 65536 / R0d; = 難易度別定数2;(分割角、交差弾[65536/32])
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e = 65536 / R0d;/*(分割角、交差弾)*/ 	/* 分割角度 */
		// (4) if (17 < (s32)VR32) {goto end;}/*[最大18way]*/
		MCODE(OP0x09_BFL_RS, (17), R32, (u8)(+1)),//	(end+1); フローしたら分岐
		// (5) cg_BOSS_DATA_32_chuu_boss_mode++;
		MCODE(OP0x01_MOVER_PD, (u8)(+1), R32, R32), /*(インデックス付)*/
		// (6) //	(end+1:);
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_init, (5));//
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]	「レッドマジック」
	-------------------------------------------------------
	R09[定数1]n回に一回弾を置く。
	R0d 	難易度別定数1
---------------------------------------------------------*/

local SPELL_INIT(43_remilia_red_magic)
{
	static const u32 codebase_init[5] =
	{
		// (1)	// VR09 = [定数1]n回に一回弾を置く。
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	//	PACK_NAN_IDO_CONST((32), (24), (16), (8)),//[定数1]n回に一回弾を置く。
		PACK_NAN_IDO_CONST((32), (20), (16), (13)),//[定数1]n回に一回弾を置く。
		// (2)	// VR0d = 難易度別定数1
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0d, NAX/*R20_PLAYER_DATA_game_difficulty*/),/*(分割数、紅色)*/
	//	PACK_NAN_IDO_CONST((10), (10), (13), (18)),/*tama_const_H06_NUMS_ALICE_RED*/	/*(分割数、紅色)*/
		PACK_NAN_IDO_CONST((10), (13), (20), (24)),/*tama_const_H06_NUMS_ALICE_RED*/	/*(分割数、紅色)*/
		// (3)
		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),// R0e  = 65536 / R0d;/*(分割角、紅色)*/	/*(分割角度、紅色)*/
	};
	cpu_exec((u32*)&codebase_init, (3));//
	//
}
//	TAMA_DATA_10_TAMA_OKI_KANKAKU	= (0);// カウンタ
//	VR09	= ((16)-((cg_VR20_game_difficulty)<<2));//[定数1]n回に一回弾を置く。
//	VR09	= ((32)-((cg_VR20_game_difficulty)<<3));//[定数1]n回に一回弾を置く。
	//
	#if 0
	// ★ 「レッドマジック」もどき用
	VR0d	= [tama_const_H09_NUMS_REMI_MAGIC];  /*(分割数、紅色)*/ (10),					(10),					(13),					(18),
	VR0e	= [tama_const_H10_DIVS_REMI_MAGIC];  /*(分割角、紅色)*/ (int)(65536/(10)),		(int)(65536/(10)),		(int)(65536/(13)),		(int)(65536/(18)),
	#endif
