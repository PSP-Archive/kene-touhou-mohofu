
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	輝夜のカードを定義します。
---------------------------------------------------------*/

/*---------------------------------------------------------
	輝夜
	-------------------------------------------------------
	無理やり追加
---------------------------------------------------------*/

/*---------------------------------------------------------
	4面専用
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_uroko_dan_seisei)
{
	/* 4面の場合---- */
	const u16 my_ra_nd = ra_nd();
	if (my_ra_nd & 0x8000)		/* 50%の確率で */
	{
		s32 kakudo65536;
	//	kakudo65536 = ((255-32)<<6);
	//	kakudo65536 = ((256-32)<<6);
	//	kakudo65536 = (((1024/4)-(1024/32))<<6);
		kakudo65536 = ((65536/4)-(65536/32));
		kakudo65536 += ((my_ra_nd)&((/*64<<6*/4096)-1));
		HATSUDAN_R12_speed_offset	= t256(0);			/* (-5) (-3)調整減速弾 */	/* この方式になるか検討中 */
		HATSUDAN_R13_angle65536 	= (kakudo65536);
		HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R16_n_way			= (24);
		HATSUDAN_R17_div_angle65536 = (int)(65536/24);	/* 分割角度([360/360]度を24分割) */
//
	static const void *JumpTable[(8)] =
	{
		&&OPKA0x00, &&OPKA0x01, &&OPKA0x02, &&OPKA0x03,
		&&OPKA0x04, &&OPKA0x05, &&OPKA0x06, &&OPKA0x07,
	};
		goto *JumpTable[((src->boss_hp>>13)&(0x07))];
		{
		OPKA0x03:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(0.6);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_05_MIDORI);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(1.4);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x02:/*not_break;*/
		OPKA0x04:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(1.0);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(1.8);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x05:/*not_break;*/
		OPKA0x01:/*not_break;*/
			HATSUDAN_R11_speed256	= t256(1.2);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_02_YUKARI);	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(0.8);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
			HATSUDAN_R11_speed256	= t256(2.0);HATSUDAN_R15_bullet_obj_type = (BULLET_UROKO14_BASE + TAMA_IRO_01_AKA); 	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
		OPKA0x00:
		OPKA0x06:
		OPKA0x07:
			;
		}
	}
}


/*---------------------------------------------------------
	左右ショット
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_hari_shot)
{
	int hari_no_iro;
	hari_no_iro = BULLET_HARI32_00_AOI;
	{	/* 4面の場合---- */
		u16 iro_tbl[8] =
		{
/**/		BULLET_HARI32_01_AKA,
/*1*/		BULLET_HARI32_01_AKA,
/*2*/		BULLET_HARI32_03_DAIDAI,
/*3*/		BULLET_HARI32_02_KIIRO,
/*4*/		BULLET_HARI32_00_AOI,
/*5*/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
/**/		BULLET_HARI32_00_AOI,
		};
		int vvv;
	//	vvv = (((src->boss_hp)&(0x0000e000) )>>(13));/*(-r32)*/
		vvv = (((src->boss_hp)&(0x0001c000) )>>(14));/*(r33-)*/
		hari_no_iro = iro_tbl[vvv];
	//											0x0001c000 == 114688 == 3.5*32*1024
	}
		HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		HATSUDAN_R15_bullet_obj_type	= hari_no_iro;		/* [ 弾] */
	//
	{
		static int hari = 0;
		hari--;
		hari &= 32;
		//
		int spd;/*(弾速)*/
		spd = t256(1.5) + /*(t256(0.0 ... 0.99)の乱数)*/(ra_nd() & 0x00ff);
			//	angle512 += (/*22*/21+hari-difficulty/*cv1024r(20)*/)		/* 23本(360) ← 8本(180) */ /* ((4+1)<<16) 4 difficulty*/
		for (VR03_i=0; VR03_i<((5)<<16); VR03_i += ((/*44*/36<<6)+((hari)<<7)-((cg_VR20_game_difficulty)<<(8)) /*cv1024r(20)*/) ) /* 最低 == 10 == 48本(360) */
		{
			HATSUDAN_R11_speed256			= (int)(spd);	/* 弾速 */	/*6*/	/*t256(2.5)*/
			HATSUDAN_R13_angle65536 		= (VR03_i);
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			spd += (64>>3/*difficulty*/);
		}
	}
	//
	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;
	AUDIO_19_voice_truck	= TRACK04_TEKIDAN;/* テキトー */
	CPU_CALL(cpu_voice_play);
}

/*---------------------------------------------------------
	左右ショット
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_hari_dan_seisei)
{
//	if (CARD_ADDRESS_00_kaguya_000 < sp ell_card_number)
	{
		static int fire_wait1;
		fire_wait1--;
		if (0 > fire_wait1)
		{
			fire_wait1 = (45*4);
			kaguya_hari_shot(src);
		}
	}
}


/*---------------------------------------------------------
	4面の場合跳ねる珠
---------------------------------------------------------*/

local OBJ_CALL_FUNC(kaguya_pong_boll)
{
	/* 4面の場合跳ねる珠 */
	{
		/* 体力ゲージが 3本以下になったら、跳ねる珠を落とし始める。 */
	//	if (src->boss_hp < (3*(8192)))/*(-r32)*/
		if (src->boss_hp < (3*(1024*32)))/*(r33-)*/
		{
			kaguya_data_fire_wait3--;
			if (kaguya_data_fire_wait3 < 0)
			{
			//	kaguya_data_fire_wait3 = ((src->boss_hp)>>(2+3));
			//	kaguya_data_fire_wait3 = ((src->boss_hp)>>(7)); 	/* 3*(8192)>>7 == 192 */
				kaguya_data_fire_wait3 = ((src->boss_hp)>>(7+2));	/* 3*(32768)>>9 == 192 */
				//
				#define LIMIT_LOW50 (/*50*/64)
				if (kaguya_data_fire_wait3 < (LIMIT_LOW50))
				{	kaguya_data_fire_wait3 = (LIMIT_LOW50);}
			//	1 ... 40
					#if 0	/*古い*/
					HATSUDAN_R11_speed256					= t256(0.05)+((cg_VR20_game_difficulty)<<6);	/* 速度 t256(5.0) */
					HATSUDAN_R15_bullet_obj_type			= BULLET_MINI8_BASE + (TAMA_IRO_04_MIZU_IRO +(cg_VR20_game_difficulty));
				//	HATSUDAN_R16_n_way						= (8);
					HATSUDAN_R17_VECTOR_leg acy_dan_delta256 = (t256(0.07));	/*17.92==t256(0.07)*/
			//	kaguya_data_bomb_aaa += 9;
			//	if (448 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 448;}/* 512-448 == 64 == 1024/16...方向 / 最大16方向の場合。 */
			//	if (433 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 433;}/* 512-433 == 79 == 1024/13...方向 / 最大13方向の場合。 */
			//	if (427 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 427;}/* 512-427 == 85 == 1024/12...方向 / 最大12方向の場合。 */
			//	if (419 < kaguya_data_bomb_aaa) {kaguya_data_bomb_aaa = 419;}/* 512-419 == 93 == 1024/11...方向 / 最大11方向の場合。 */
			//	for (VR03_i=0; VR03_i<(1024); VR03_i+=(512-kaguya_data_bomb_aaa))/* 精々最大16方向ぐらい出ないとくぐって避けれない。 */
			//	{
			//		HATSUDAN_R13_angle65536 			= ((VR03_i)<<6);	/* 角度 */
			//		bullet_regist_leg acy_vector_direct();
			//	}
					#else	/*新しい*/
					HATSUDAN_R11_speed256					= t256(0.05)+((cg_VR20_game_difficulty)<<6);	/* 速度 t256(5.0) */
					HATSUDAN_R12_speed_offset				= (t256(0.07)); 								/*17.92==t256(0.07)*/
					HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
					HATSUDAN_R15_bullet_obj_type			= BULLET_MINI8_BASE + (TAMA_IRO_04_MIZU_IRO +(cg_VR20_game_difficulty));
				kaguya_data_bomb_aaa += (9*64);
				if ((419*64) < kaguya_data_bomb_aaa)	{kaguya_data_bomb_aaa = (419*64);}/* 512-419 == 93 == 1024/11...方向 / 最大11方向の場合。 */
				//
				for (VR03_i=0; VR03_i<(65536); VR03_i+=((65536/2)-kaguya_data_bomb_aaa))/* 16方向より増やすと、くぐって避けるのが難しくなりすぎるので最大でも16方向。 */
				{
					HATSUDAN_R13_angle65536 			= (VR03_i);/* 角度 */
					hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				}
					#endif
			}
		}
	}
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

local OBJ_CALL_FUNC(boss_init_kaguya_start000)
{
	kaguya_data_fire_wait3			= 0;
	kaguya_data_bomb_aaa			= 0;
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/
local SPELL_EXEC(48_kaguya000)
{
//	if (50 == VR10_BOSS_SPELL_TIMER)
	if ((64-10) == VR10_BOSS_SPELL_TIMER)
	{
		kaguya_uroko_dan_seisei(src_boss);
	}
	kaguya_hari_dan_seisei(src_boss);
}
local SPELL_EXEC(4a_kaguya222)
{
//	if (50 == VR10_BOSS_SPELL_TIMER)
	if ((64-10) == VR10_BOSS_SPELL_TIMER)
	{
		kaguya_uroko_dan_seisei(src_boss);
	}
	kaguya_hari_dan_seisei(src_boss);
	kaguya_pong_boll(src_boss);
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	「永夜返し　‐夜明け‐」（N）
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	難題「蓬莱の玉の枝　-虹色の弾幕-」
	-------------------------------------------------------
	下部弓状オプション7個から左右に弾が広がり
	画面端で反射してから自機狙い弾になる。
	-------------------------------------------------------
	下部弓状オプションは6方向弾(半周)を撃つ。
	下部弓状オプションの弾色は固定で左から順に、
	赤。紫。青。水。緑。黄。橙。(弾と同じで順序はHSV、色角度順)
---------------------------------------------------------*/

/*---------------------------------------------------------
	輝夜、蓬莱の玉の枝もどき
	神宝「蓬莱の玉の枝 - 夢色の郷 -」
	-------------------------------------------------------
	ぜんぜん作ってない...
//	１．輝夜が直接撃つ弾は16方向弾→17方向弾→16方向弾へジョジョに変化する。
	１．輝夜が直接撃つ弾は8方向弾が2セット。(?)
		セット別に回転方向が違う(?)。
	２．弓状にならんだオプションから始めだけ全方位(48方向)弾発射。
	３．弓状にならんだオプションから画面左右端に反転色米弾発射し、
		画面左右端で通常色米弾のプレイヤー狙い弾に変わる。
	-------------------------------------------------------
	[execute section: 発弾セクション]
	-------------------------------------------------------
	使用レジスタ
	R08 	珠の色(1 ... 7)。
	R09 	角度?
---------------------------------------------------------*/
// 4096 == 65536/16
// 3855.05882352941176470588235294118 == 65536/17
//	240.941176470588235294117647058824 == ((65536/16)-(16636/17)) 差分
local SPELL_EXEC(4b_kaguya333_tamanoe)
{
//	if ((0x02)==(VR10_BOSS_SPELL_TIMER & 0x03))/* (2回に1回)(8回毎に発弾) */
	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (2回に1回)(8回毎に発弾) */
	{
	#if (1)//[-r39]変数化するとスペカ切り替え時にリセットされる。
		static u32 kaguya_VR09;
		static u32 kaguya_VR08;
	#else//[r40]変数化するとスペカ切り替え時にリセットされる。
		#define kaguya_VR09 VR09
		#define kaguya_VR08 VR08
	#endif
		kaguya_VR08++;
		kaguya_VR08 &= (0x07);
		if (0==kaguya_VR08) {	kaguya_VR08++;	};
		//
//		HATSUDAN_R11_speed256			= (t256(1.00)); 			/* 弾速 */
		HATSUDAN_R11_speed256			= (t256(0.50)); 			/* 弾速 */
//		HATSUDAN_R12_speed_offset		= t256(0);/*(テスト)*/
		HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
		HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE) + kaguya_VR08;	/* [中丸弾] */
	//	HATSUDAN_R16_n_way				= (17); 						/* [17way] */	/* 発弾数 */
		HATSUDAN_R16_n_way				= (16/*8*/);					/* [16way] */	/* 発弾数 */
	//	HATSUDAN_R17_div_angle65536 	= (int)(65536/(16))-(((si n1024(( ra_nd() & VR10_BOSS_SPELL_TIMER)))&0xff));	/*(int)(65536/(6))*/	/* 分割角度(65536[360/360度]を 6 分割) */	/* 1周をn分割した角度 */
		HATSUDAN_R17_div_angle65536 	= (int)(65536/(16/*8*/));		/* 1周を16分割した角度 */
//
//		HATSUDAN_R13_angle65536 		= ((65536/2));					/* 発射中心角度 / 特殊機能(自機狙い/他) */
//		HATSUDAN_R13_angle65536 		= (int)((65536*1/4))+(VR10_BOSS_SPELL_TIMER&0xff);				/* 発射中心角度 / 特殊機能(自機狙い/他) */
		kaguya_VR09 += (77);
		HATSUDAN_R13_angle65536 		= ((kaguya_VR09));						/* 発射中心角度 / 特殊機能(自機狙い/他) */
		if (0 == (VR10_BOSS_SPELL_TIMER & 0x08))
		{
//			HATSUDAN_R13_angle65536 	= (int)((65536*3/4))+(VR10_BOSS_SPELL_TIMER&0xff);				/* 発射中心角度 / 特殊機能(自機狙い/他) */
			HATSUDAN_R13_angle65536 	= -(kaguya_VR09);				/* 発射中心角度 / 特殊機能(自機狙い/他) */
		}
		hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r42-) */
	}
	/*(r40てすと)*/
//	if ((64-10) == VR10_BOSS_SPELL_TIMER)
//	{kaguya_hari_dan_seisei(src);}
}



/*---------------------------------------------------------
	蓬莱の玉の枝もどき
	-------------------------------------------------------
	せっかく模倣風で輝夜が出るのだから、
	蓬莱の玉の枝もどきだけ作りたい気がする。
	レーザーも要らないし。
	以下メモ。
//
	赤紫青水緑黄橙の順(つまり順序はHSV、色角度順)で7色繰り返しで出てくる。
	画面中央上部の輝夜からは全方位結構ゆっくり速度丸弾。
	ほぼ等速だか微妙に加速してる気もする。(気のせいかも)
	輝夜は上下に揺れているが、射出位置は揺れないで固定。
	全方位弾(開幕時は16方向全方位弾)だが少しずつ(ランダムっぽい角度で)弾数が増える。
	(つまり分割角度が減る)
	17方向全方位弾迄、増えると今度は16方向全方位弾まで減る(多分)。それの繰り返し。
//
	画面中央下部(というかほぼ画面中心)に魔方陣が半分ずつ重なって7つ。扇状配置。
	開幕時だけ、全方位米弾撃ってくる。
	下部に魔方陣からは左右に反転色、米弾。角魔方陣からは同時に弾が出る。
	弾速は比較的ゆっくりだが、輝夜丸弾より速い。
	こちらもほぼ等速だか微妙に加速してる気もする。(気のせいかも)
	色の順序は左側は上と同じ。右側は逆順。
	サインっぽい感じでうねって射出。7色撃つとしばし休む。
	右はangle=90[度]+(sin(周期++)*微角度定数)。
	左はangle=270[度]+(sin(周期++)*微角度定数)。みたいにすればいいのかも？
	(微角度定数は+-11.25度(360/(2^5))ぐらい？なら>>4とかでいいかな？)
	反転色、米弾は、左右の壁にあたると色が同色で反転し(例えば赤反転色米弾が赤米弾になるという意味)、
	自機狙い弾になる。
	-------------------------------------------------------
	大体こんな感じだと思うけど、間違ってるかもしれない。
	以上を満たせば、かなり細部の動きが違っても、似た感じにならないかなあ？
---------------------------------------------------------*/









// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	難題「燕の子安貝　-永命線-」
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	通常攻撃4
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	難題「火鼠の皮衣　-焦れぬ心-」
---------------------------------------------------------*/


// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	通常攻撃3
	-------------------------------------------------------
	反転青米弾は円状48方向。
	緑大玉弾
	紫大玉弾
	緑中弾
	青中弾
	-------------------------------------------------------
---------------------------------------------------------*/
#if (1)// とりあえず(仮)。
/*---------------------------------------------------------
	(テキトー)五方向時計回り弾
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
	-------------------------------------------------------
	R0b 	分割角。
	R0c 	現在回転角。
	R0d 	。
---------------------------------------------------------*/

local SPELL_EXEC(57_kaguya_tujyou_kougeki_03)
{
	static const u32 codebase_exec[25] =
	{
		// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x04);
		MCODE(OP0x1d_ANDM_PD, 0x04, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (02) if (0 != VR0a) {goto label_ddd+17;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+17)),// (ddd+17)
		// (03) VR0c += VR0b;
		MCODE(OP0x04_ADDR_PD, NAX, R0c, R0b),
		// (04) VR0a = (VR10_BOSS_SPELL_TIMER & 0xff);
		MCODE(OP0x1d_ANDM_PD, 0xff, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (05) VR0a = (VR00 + (0xff) - VR0a);		VR0a = (0xff - VR0a);
		MCODE(OP0x05_SUBR_PD, (0xff), R0a, R00),/*(ゼロレジスタ使用)*/
		// (06) VR0b += VR0a;
		MCODE(OP0x04_ADDR_PD, NAX, R0b, R0a),
		// (07) HATSUDAN_R11_speed256			= t256(2.0);/* 弾速(0) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(2.0)),
		// (08) HATSUDAN_R12_speed_offset		= t256(-1);/* 減速？ */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),//
		(t256(-1)),/* 減速？ */
		// (09) HATSUDAN_R13_angle65536 		= VR0c; /* 弾源角度65536 */ 	/*下CCW*/
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0c),
		// (10) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_00)|(TAMA_SPEC_2000_EFFECT_MINI)|(TAMA_SPEC_0000_TILT)),
		// (11) HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_01_AKA); /* [赤米弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KOME_BASE + TAMA_IRO_01_AKA)), /* [赤米弾] */
		// (12) HATSUDAN_R16_n_way				= (5);		/* [5way] */		/* 発弾数 */
		MCODE(OP0x1c_MOVEM_PD, (5), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (13) HATSUDAN_R17_div_angle65536 	= (int)(512-64);		/* 分割角度(65536[360/360度]を	 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(512-64),	/* (65536/1024)*7 448==(64*7)[密着弾]の分割角度(r32) */
		// (14)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//	label_ddd+17:
		// (15) VR0a = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (16) if (0 != VR0a) {goto label_eee+3;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+3)),//	(eee+3)
		// 効果音.
		// (17) AUDIO_18_voice_number		= VOICE16_BOSS_KYUPIN;/*(ナイフ追加音)*/
		MCODE(OP0x1c_MOVEM_PD, (VOICE16_BOSS_KYUPIN), R18, NAX),/*(ショートメモリアドレッシング)*/
		// (18) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;
		MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(ショートメモリアドレッシング)*/
		// (19)  (cpu_voice_play);
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
//	label_eee+3:
		// (20)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (19));
}

local SPELL_INIT(57_kaguya_tujyou_kougeki_03)
{
	VR0b = 1000;
	VR0c = 0;
}
#endif

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	難題「仏の御石の鉢　-砕けぬ意志-」
	-------------------------------------------------------
	オプション魔方陣内側1 09個	配置増分角度(65536/(9*2))
	オプション魔方陣内側2 11個	配置増分角度(65536/(11*2))
	オプション魔方陣内側3 13個	配置増分角度(65536/(13*2))
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(kaguya_tujyou_kougeki_02_wait_callback)/* 珠跳ね */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-256/*128*/) == src_tama->jyumyou)/* 発弾エフェクト後から[128]カウント の弾 */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* 弾速 */
		/* (通常弾へ変身する) */
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
	}
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
//	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]	通常攻撃2
	-------------------------------------------------------
SPELL_4e_kaguya_tujyou_kougeki_02


lt == 32[pixel]
stat == 128[pixel]
game == 160[pixel]

|lt|---game--|stat|
|32|32|256|32|128| == |480[pixel] psp 横幅|
|-64--|128+---------kaguya x(center)

32 + 32 + 256 + 32 + 128 == 480 [pixel] == psp width.
	-------------------------------------------------------
4 + 4 + 32 + 4 + 16 == 60, 60*8 == 480 [pixel] == psp width.
2 + 2 + 16 + 2 + 8 == 30, 30*16 == 480 [pixel] == psp width.

---------------------------------------------------------*/

local SPELL_EXEC(54_kaguya_tujyou_kougeki_02)
{
	HATSUDAN_R11_speed256			= (t256(0.5));				/* 弾速(2.5) */
	HATSUDAN_R12_speed_offset		= t256(2);/*(てすと)*/
	HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
//	HATSUDAN_R15_bullet_obj_type	= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);	/* [青丸弾] */
//	HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);	/* [青枠弾] */
	HATSUDAN_R15_bullet_obj_type	= (BULLET_MINI8_BASE + TAMA_IRO_03_AOI);	/* [青ミニ弾] */
	//
//	VR03_i = 0;
	//
	not_tama:
		;
//	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (2回に1回)(8回毎に発弾) */
	//	int boss_x256;cg_BOSS_DATA_3a_center_x256
	//	int boss_y256;cg_BOSS_DATA_3b_center_y256
	//VR06	int tama_x256;
	//VR07	int tama_y256;
		//
		int dr; 	/* 半径(==radius) */
		int dx; 	/* x差分(微小x距離, delta x) */
		int dy; 	/* y差分(微小y距離, delta x) */
		//
	//	VR06 = cg_BOSS_DATA_3a_center_x256 - (128<<8) + ((ra_nd()&0xff)<<8);
	//	VR07 = cg_BOSS_DATA_3b_center_y256 + ((ra_nd()&0xff)<<8);
	//	VR06 = ((ra_nd() & 0xffff)) + t256(64);/* (0 ... 255)[pixel], 64[pixel] == lt:32[pixel] + game_lt:32[pixel] */
	//	VR07 = ((ra_nd() & 0x7fff));/* (0 ... 127)[pixel] */
		VR06 = ((ra_nd() & 0xff)) +  (64);/* (0 ... 255)[pixel], 64[pixel] == lt:32[pixel] + game_lt:32[pixel] */
		VR07 = ((ra_nd() & 0xff));/* (0 ... 255)[pixel] */
	//	VR07 = ((ra_nd() & 0x7f));/* (0 ... 127)[pixel] */
		//
	//	dr = (/*obj2->m_Hit256R*/ /*+*/t256(80) /*boss_m_Hit256R*/);
	//	dr = (/*obj2->m_Hit256R*/ /*+*/t256(100) /*boss_m_Hit256R*/);
		dr = (VR0b);
		/* 中心同士で差。つまり軸ごとの距離を求める。 */
	//	dx = ((VR06) - (cg_BOSS_DATA_3a_center_x256));/* 中心同士で差を求める。 */
	//	dy = ((VR07) - (cg_BOSS_DATA_3b_center_y256));/* 中心同士で差を求める。 */
	//	dx = ((VR06) - (t256(32+32+128)));/* 中心同士で差を求める。 */
	//	dy = ((VR07) - (t256(0)));/* 中心同士で差を求める。 */
		dx = ((VR06) - ( (32+32+128)));/* 中心同士で差を求める。 */
		dy = ((VR07) - ( (0)));/* 中心同士で差を求める。 */

		/* check collision, delta x position. 矩形判定（Ｘ軸） */
		if (dx < 0) 	{dx = (-dx);}	/* dx = abs(dx); */
	//	if (dx > dr)	{goto not_tama;/*(FALSE)*/ }	/* not hit, because not near the dx. Ｘの差分が大きいので、当たってない */
	//
		/* check collision, delta y position. 矩形判定（Ｙ軸） */
		if (dy < 0) 	{dy = (-dy);}	/* dy = abs(dy); */
		if (dy > dr)	{goto not_tama;/*(FALSE)*/ }	/*	not hit, because not near the dy. Ｙの差分が大きいので、当たってない */

		/* check collision, circle delta round distance.  円の半径で判定 */
		dr *= dr;
	//	dr = t256(80*80);
		dx *= dx;
		dy *= dy;
		dx += dy;
		/* 当たり判定外なら */
		if (dr < dx)/* if ((dr^2) < ( (dx^2) + (dy^2) )) */
		{
			goto not_tama;/*(FALSE)*/	/*(not hit. 当たってない)*/
		}
	//	return (1);/*(TRUE)*/	/*(hit! 当たった)*/
//	VR06 &= 0x00fff000;
//	VR07 &= 0x00fff000;
//	VR06 &= 0x00fff0;
//	VR07 &= 0x00fff0;
	VR06 &= 0x00fff8;
	VR07 &= 0x00fff8;
	VR06 <<= 8;
	VR07 <<= 8;

//	VR06 = VR06;
//	VR07 = VR07;
	HATSUDAN_R13_angle65536 		= (ra_nd());/*( )*/
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
	//
//	VR03_i++;
//	if (2 > VR03_i) goto not_tama;
//	if (1 > VR03_i) goto not_tama;

	// 効果音.
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x07))
	{
		AUDIO_18_voice_number	= VOICE16_BOSS_KYUPIN;/*(ナイフ追加音)*/
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;
		CPU_CALL(cpu_voice_play);
	}
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
	VR0b	t256(難易度別定数1);
---------------------------------------------------------*/

local SPELL_INIT(54_kaguya_tujyou_kougeki_02)
{
	static const u32 codebase_init[3-1] =
	{
		// (1)	VR0b = t256(難易度別定数1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((50), (90), (120), (150)),/*(半径[pixel])*/
		// (2)	VR0b = VR0b * (256);/*(t256形式に変換する)*/
		// (2)	VR0b = (VR0b << 8);/*(t256形式に変換する)*/
	//	MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(ショートメモリアドレッシング)*/
	//	NAX/*(初期化終了)*/
	};
	cpu_exec((u32*)&codebase_init, (2-1));//
}

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	難題「龍の頸の玉　-五色の弾丸-」
---------------------------------------------------------*/

// ==================================== [スペカ境界] ==================================== //

/*---------------------------------------------------------
	通常攻撃1
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t02 section: 弾幕レイヤーグループ(2)セクション]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(kaguya_tujyou_kougeki_01_wait_callback)/* 珠跳ね */
{
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT+16/*128*/) == src_tama->jyumyou)/* 発弾エフェクト後から[128]カウント の弾 */
	{
		src_tama->TR01_hatudan_speed65536 = (1<<16);		/* 弾速 */
		/* (通常弾へ変身する) */
	//	src_tama->obj_type_set				= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);
		if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
		{
		//	src_tama->rotationCCW1024 += ((int)((1024/2)+(1024/12)));
			src_tama->rotationCCW65536 += ((int)((65536/2)+(65536/12)));
			src_tama->obj_type_set			= (BULLET_KOME_BASE + TAMA_IRO_01_AKA);//minus[負]
		}
		else
		{
		//	src_tama->rotationCCW1024 += ((int)((1024/2)-(1024/12)));
			src_tama->rotationCCW65536 += ((int)((65536/2)-(65536/12)));
			src_tama->obj_type_set			= (BULLET_KOME_BASE + TAMA_IRO_03_AOI);//plus[正]
		}
		src_tama->TR00_hatudan_spec_data = (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
		reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* 弾グラと弾あたり判定を変更する。 */
	}
	// 減速。 弾速(2.5)  ->  弾速(0.5)
	src_tama->TR01_hatudan_speed65536 -= t256((2.0/32));
	// 回転。
//	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
//			{src_tama->rotationCCW1024 += (1024-1);}//minus[負]
//	else	{src_tama->rotationCCW1024 += (1);}//plus[正]
	if (0==(src_tama->TR00_hatudan_spec_data & TAMA_SPEC_KAITEN_HOUKOU_BIT))
			{src_tama->rotationCCW65536 += (65536-(1<<6));}//minus[負]
	else	{src_tama->rotationCCW65536 += (1<<6);}//plus[正]
	//
//	standard_angle_mover_00_callback(src_tama);/*(角度弾移動+画面外弾消し)*/
	hatudan_system_tama_move_angle(src_tama);/*(角度弾移動)*/
}

/*---------------------------------------------------------
	[execute section: 発弾セクション]	通常攻撃2
	-------------------------------------------------------
SPELL_4e_kaguya_tujyou_kougeki_02


lt == 32[pixel]
stat == 128[pixel]
game == 160[pixel]

|lt|---game--|stat|
|32|32|256|32|128| == |480[pixel] psp 横幅|
|-64--|128+---------kaguya x(center)

32 + 32 + 256 + 32 + 128 == 480 [pixel] == psp width.
	-------------------------------------------------------
4 + 4 + 32 + 4 + 16 == 60, 60*8 == 480 [pixel] == psp width.
2 + 2 + 16 + 2 + 8 == 30, 30*16 == 480 [pixel] == psp width.

	-------------------------------------------------------
	使用レジスタ
	R0a		一時使用。
---------------------------------------------------------*/

local SPELL_EXEC(51_kaguya_tujyou_kougeki_01)
{
	static const u32 codebase_exec[28] =
	{
		// (01) VR0a = (VR10_BOSS_SPELL_TIMER & 0x01);
		MCODE(OP0x1d_ANDM_PD, 0x01, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (02) if (0 != VR0a) {goto label_ddd+20;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+20)),//	(ddd+20)
		// (03) VR0a = (VR10_BOSS_SPELL_TIMER & 0x10);
		MCODE(OP0x1d_ANDM_PD, 0x10, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (04) if (0 != VR0a) {goto label_bbb+5;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+5)),//	(bbb+5)
		// (05) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(TAMA_SPEC_KAITEN_HOUKOU_BIT)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
		// (06) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI);	/* [青クナイ弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_03_AOI)),	/* [青クナイ弾] */
		// (07) goto label_ccc+4;
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (u8)(+4)),
//	label_bbb+5:
		// (08) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(0x0000)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
		((DANMAKU_LAYER_01)|(0x0000)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
		// (09) HATSUDAN_R15_bullet_obj_type	= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA);	/* [赤クナイ弾] */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
		((BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)),	/* [赤クナイ弾] */
//	label_ccc+4:
		// (10) HATSUDAN_R13_angle65536 		= (ra _nd());/*( )*/
		MCODE(OP0x15_RAND_VALUE, NAX, R13, NAX),
		// (11) HATSUDAN_R16_n_way				= (5);		/* [5way] */		/* 発弾数 */
		MCODE(OP0x1c_MOVEM_PD, (5), R16, NAX),/*(ショートメモリアドレッシング)*/
		// (12) HATSUDAN_R11_speed256			= (t256(2.5));/* 弾速(2.5) */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
		(t256(2.5)),
		// (13) HATSUDAN_R12_speed_offset		= t256(2);/*(てすと)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
		(t256(2)),
		// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/(32*5));		/* 分割角度(65536[360/360度]を 32 分割) */	/* 1周をn分割した角度 */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
		(int)(65536/(32*5)),
		// (15)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//	label_ddd+20:
		// (16) VR0a = (VR10_BOSS_SPELL_TIMER & 0x07);
		MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R10),/*(ショートメモリアドレッシング)*/
		// (17) if (0 != VR0a) {goto label_eee+3;}
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+3)),//	(eee+3)
		// 効果音.
		// (18) AUDIO_18_voice_number		= VOICE16_BOSS_KYUPIN;/*(ナイフ追加音)*/
		MCODE(OP0x1c_MOVEM_PD, (VOICE16_BOSS_KYUPIN), R18, NAX),/*(ショートメモリアドレッシング)*/
		// (19) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;
		MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(ショートメモリアドレッシング)*/
		// (20)	 (cpu_voice_play);
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
//	label_eee+3:
		// (21)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(終了[ブランチ系命令がある場合、必ず要る])*/
	};
	cpu_exec((u32*)&codebase_exec, (20));
}

/*---------------------------------------------------------
	[initialize section: 初期化セクション]
	-------------------------------------------------------
	VR0b	t256(難易度別定数1);
---------------------------------------------------------*/

local SPELL_INIT(51_kaguya_tujyou_kougeki_01)
{
	static const u32 codebase_init[4] =
	{	//	 (CLIP_RECT_TYPE_03_UE_WIDE);/*(特殊)*/
		// (01)
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// 上にもっと広いタイプ
		CLIP_RECT_03_VR1d,// 上にもっと広いタイプ
		// ----
		// (02)	VR0b = t256(難易度別定数1);
		MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R0b, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		PACK_NAN_IDO_CONST((50), (90), (120), (150)),/*(半径[pixel])*/
		// (03)	VR0b = VR0b * (256);/*(t256形式に変換する)*/
		// (04)	VR0b = (VR0b << 8);/*(t256形式に変換する)*/
	//	MCODE(OP0x1f_ASLM_PD, 0x08, R0b, R0b),/*(ショートメモリアドレッシング)*/
	//	NAX/*(初期化終了)*/
	};
	cpu_exec((u32*)&codebase_init, (2));//
}

// ==================================== [スペカ境界] ==================================== //
