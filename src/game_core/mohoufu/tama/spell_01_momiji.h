
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ののじっぽいカードを生成しようと思ったけど無理でした。
---------------------------------------------------------*/

/*---------------------------------------------------------
	紅2面中-ボス 大妖精 通常攻撃1(1/3)
	-------------------------------------------------------
	緑クナイ弾
	下から始めて、時計回り、2段づつ
	-------------------------------------------------------
	使用レジスタ
	R08 	カウンタ。
	R09 	角度調整用。
	R0a 	速度調整用。
	R0b 	加算角(テキトー)
	R0c 	加算角調整値(seed)を保持。(テキトー)
---------------------------------------------------------*/
local SPELL_EXEC(1e_momiji_no_nonoji)
{
//	if (64 == VR10_BOSS_SPELL_TIMER) /* 始めに初期化 */
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 192, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));//	/*	繰り返しカウンタ。 */
	if (1==VR08) /* 始めに初期化 */
	{
		VR09 = 0;
		VR0a = 0;
	}
//	if ((64-(48)) < VR10_BOSS_SPELL_TIMER)
	if (48 > VR08) /* 48以下なら撃つ */
	{
	//	if (0x00 == (VR10_BOSS_SPELL_TIMER & (2-1)))/*(2回に1回)*/
		{
				HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)非傾き弾 */
				HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI); 	/* [青大玉弾] 白いの無いから */
			for (VR03_i=0; VR03_i<(1+cg_VR20_game_difficulty); VR03_i++)/*(2段づつ)*/
			{
			//	HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a<<2)+(VR03_i<<6));		/* 弾速 */
				HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a	)+(VR03_i<<6)); 		/* 弾速 */
				HATSUDAN_R13_angle65536 		= (VR09);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
			VR09 += (65536/48); /* 下から撃ち始める。 */
			VR0a++;
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
	if (192 > VR08) /* 192以下なら撃つ */
	{
		if (96 < VR08) /* 96以上なら撃つ */
		{
			HATSUDAN_R12_speed_offset		= t256(1);/*(テスト)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);			/* [白米弾] */
			HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a));		/* 弾速 */
			HATSUDAN_R13_angle65536 		= (VR09);
			VR0c += VR0b; /* テキトー? */
			VR0b = VR0c;
			VR0b = (VR0b >> (5));	/*( /=32 こういうカード命令が必要。)*/
		//	/* 1365.333333 == (65536/48) 最大加算角度制限してみる。 */
			VR09 -= 1365; /* (192-96)/48 ==2 で２周回る筈。テキトー? */
			VR09 -= VR0b; /* テキトー? */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}
