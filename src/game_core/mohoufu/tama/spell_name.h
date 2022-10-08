
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	スペルシステム==カードの管理システム。(カードシステムとは違うので注意)
	-------------------------------------------------------
	スペルシステム(あらかじめカードの定義をしておくシステム)
	-------------------------------------------------------
	模倣風ではスペルはシステムでサポートしています。
	スペルとして定義(カード)しておくと、どのボスが、どのスペルでも撃てるようになります。
	-------------------------------------------------------
	またスペルはカードシステムに番号を登録しておくと、カードシステムでスペルが取得できます。
	(つまりカードシステム経由でスペルが撃てます)
	-------------------------------------------------------
	(r32)現在、雑魚(模倣風のdatの中-ボス)もスペルを撃てますが、
	この機能は将来なくなるかも知れません。
	雑魚(模倣風のdatの中-ボス)がスペルを撃てる機能は「風神禄」で思いついたのですが、
	こういう機能が無い方がゲームの速度が速く出来る気もするし、
	もしかしたらこういう機能は本家に無いのかもと思うこともあります。良く判りません。
	-------------------------------------------------------
	card.spell_used_number に撃ちたいスペルをセットすると、スペル生成開始。
	スペル生成が終了すると自動的に card.spell_used_number が DANMAKU_00 になる。
	-------------------------------------------------------
	スペル生成中は VR10_BOSS_SPELL_TIMER が勝手に毎フレーム減算され、0 になるとスペル生成終了。
	この時間はスペルごとに違う標準時間が設定されている。
	これはカードの初期化内で自動初期化される。
	-------------------------------------------------------
	カードの初期化。
	カードが変わると毎回行う必要がある。
	-------------------------------------------------------
---------------------------------------------------------*/

#ifndef _SPELL_NAME_VALUE_H_
#define _SPELL_NAME_VALUE_H_

/* カード番号(各スペルを区別する為の番号) */
enum
{
	SPELL_00 = 0,						/* スペル生成終了フラグ。 */
//	/* 雑魚用 */
	SPELL_01_sakuya_misogi_normal,		/* [咲夜] 紅5面中-ボス 禊カード / 紅5面中-ボス 咲夜 「通常攻撃」 */
	SPELL_02_,							/* [未定] */		/* [咲夜] 紅5面中-ボス 24カード (奇術「ミスディレクションもどき(1/2)」) */
	SPELL_03_sakuya_old_test,			/* [咲夜] 紅5面中-ボス 11カード (奇術「ミスディレクションもどき(2/2)」) */
	SPELL_04_sakuya_pink_hearts,		/* [咲夜] 紅5面ボス [咲夜] 「通常攻撃1(1/2)」にちょっとだけ似たカード(予定) */
	SPELL_05_sakuya,					/* [咲夜] 紅5面ボス [咲夜] 「通常攻撃1/2(2/2)」にちょっとだけ似たカード(予定) */
	SPELL_06_sakuya,					/* [咲夜] 紅5面ボス [咲夜] 幻象「ルナクロック(1/2)」にちょっとだけ似たカード(予定) */
	SPELL_07_sakuya,					/* [咲夜] 紅5面ボス [咲夜] 「通常攻撃3(1/2)」にちょっとだけ似たカード(予定) */
//
	SPELL_08_rumia, 					/* [ルーミア] 紅1面ボス [ルーミア] 夜符「ナイトバード」にちょっとだけ似たカード(予定) */
	SPELL_09_test_inuno_fuguri, 		/* [その他] 青小華弾 easy用 */
	SPELL_0a_dai_yousei_01, 			/* 10:[大妖精] 全周 48分割、時計回り、緑クナイ弾 */
	SPELL_0b_dai_yousei_02, 			/* 11:[大妖精] 全周 48分割、反時計回り、赤クナイ弾 */
	SPELL_0c_sakuya_jack32, 			/* [咲夜] 幻幽「ジャック・ザ・ルドビレ」になるかもしれないテスト */
	SPELL_0d_dai_yousei_03, 			/* 13:[大妖精] 9方向青弾 + 9方向ちょっと経ったら自機狙い白弾 */
	SPELL_0e_remilia_00,				/* [レミリア] テスト */
	SPELL_0f_tengu, 					/* [その他] 差分氏の妖怪1(天狗様?)が撃つカード(予定) */ 	/*(?)*/
//
	SPELL_10_cirno, 					/* [チルノ] 禊カード */
	SPELL_11_perfect_freeze,			/* [チルノ] パーフェクトフリーズ */
	SPELL_12_diamond_blizzard,			/* [チルノ] 雪符「ダイアモンドブリザード」 */
	SPELL_13_alice_suwako,				/* [アリス] 諏訪子っぽい(?)カード */
	SPELL_14_alice_youmu300,			/* [アリス] 妖3面ボス  normal通常攻撃3(の一部) */
	SPELL_15_alice_aka_2nd, 			/* [アリス] 怪EX面ボス 赤の魔法2段階目もどき */
	SPELL_16_alice_zako_doll,			/* [アリス] 妖3面ボス [アリス]人形カード(もどき) */ // 40[sec]
	SPELL_17_alice_tama_doll_02,		/* [アリス] 作成中 */
//
	SPELL_18_hana_test, 				/* [魅魔] 花てすとカード */
	SPELL_19_meirin_5_houkou,			/* SPELL_40_meirin_kasou_yume_kazura 4[美鈴] 幻符「華想夢葛」 */		//SPELL_40_SONOTA_DEBUG_CW_AO,		/* [その他] デバッグカードCW青 */
	SPELL_41_meirin_saikou_no_furin,	/* 4[美鈴] 虹符「彩虹の風鈴」 */	//SONOTA_DEBUG_CCW_AKA,		/* [その他] デバッグカードCCW赤 */
	SPELL_1b_cirno_icecle_fall, 		/* [チルノ] 氷符「アイシクルフォール」 */
	SPELL_44_ruiz3_test,				/* [ルイズ] カード語のてすと。 */
	SPELL_1d_amefuri_test,				/* [] 雨てすと */
	SPELL_1e_momiji_no_nonoji,			/* [椛] ののじカード */
	SPELL_1f_koakuma,					/* [小悪魔] てすと用 */
//	/* ボス用 */
	SPELL_20_aya_misogi1,				/* 1[文] の通常弾っぽいカード撃たせてみるテスト1 */
	SPELL_21_aya_misogi2,				/* 2[文] の通常弾っぽいカード撃たせてみるテスト2 */
	SPELL_22_ame_no_yatimata,			/* 3[文] 岐符「天の八衢」 */
	SPELL_23_meirin_magaru_kunai,		/* 4[美鈴] 通常攻撃 */
	SPELL_24_aya_doll,					/* 5[文] 人形カード */ //40[sec]
	SPELL_25_houka_kenran,				/* 6[紅美鈴] 華符「芳華絢爛」にちょっとだけ似たカード(予定) */
	SPELL_26_aya_saifu, 				/* 7[文] 塞符 */
	SPELL_27_hosigata_test, 			/* 8[その他] 星型テスト */
//
	SPELL_28_sakuya_miss_direction,		/* [咲夜] 奇術「ミスディレクション」 */
	SPELL_29_rumia_demarcation, 		/* 10[ルーミア] 紅1面ボス 闇符「ディマーケイション」にちょっとだけ似たカード(予定) */
	SPELL_2a_sakuya_baramaki1,			/* 11[咲夜] 紅5面中-ボス ばら撒き1 カード () */
	SPELL_2b_sakuya_baramaki2,			/* 12[咲夜] 紅5面中-ボス ばら撒き2 カード () */
	SPELL_2c_sakuya_blue_red,			/* 13[咲夜] 紅5面中-ボス 「通常攻撃3」青赤ナイフ */
	SPELL_2d_sakuya_misogi_lunatic, 	/* 14[咲夜] 紅5面中-ボス 禊カード / 紅5面中-ボス 咲夜 「通常攻撃」lunatic */
	SPELL_2e_pache_agni_shine_1,		/* [パチェ] "　　　　火符「アグニシャイン」" No.15 */	// agni shine (アグニの輝き)、 (アグニ==インド神話の火の神)
	SPELL_2f_pache_princess_undine, 	/* [パチェ] "　水符「プリンセスウンディネ」" No.16 */	// princess undine (ウンディネの姫)、(ウンディネ==錬金術師パラケルススの「妖精の書」に登場する水の精の名前)
//
	SPELL_30_pache_sylphy_horn_1,		/* [パチェ] "　　　　木符「シルフィホルン」" No.17 */	// sylphy horn (シルフィのホルン)、(シルフィ==風を司る精霊)、(ホルン==楽器==角笛)
	SPELL_31_pache_rage_tririton_1, 	/* [パチェ] "　　土符「レイジィトリリトン」" No.18 */	// rage tririton (怒るトリリトン)、 (トリリトン==世界遺産ストーンヘンジの三つ石)
	SPELL_32_pache_metal_fatigue,		/* [パチェ] "　　金符「メタルファティーグ」" No.19 */	// metal fatigue (金属疲労)
	SPELL_33_pache_agni_shine_2,		/* [パチェ] "　　火符「アグニシャイン上級」" No.20 */
	SPELL_34_pache_sylphy_horn_2,		/* [パチェ] "　　木符「シルフィホルン上級」" No.21 */
	SPELL_35_pache_rage_tririton_2, 	/* [パチェ] "土符「レイジィトリリトン上級」" No.22 */
	SPELL_36_pache_agni_radiance,		/* [パチェ] "　火符「アグニレイディアンス」" No.23 */	// agni radiance (アグニの輝き)、 (アグニ==インド神話の火の神)
	SPELL_37_pache_bury_in_lake,		/* [パチェ] "　　　水符「ベリーインレイク」" No.24 */	// bury in lake (水葬)
//
	SPELL_38_pache_green_storm, 		/* [パチェ] "　　　木符「グリーンストーム」" No.25 */	// green storm (緑の嵐)
	SPELL_39_pache_tririton_shake,		/* [パチェ] "　　土符「トリリトンシェイク」" No.26 */	// tririton shake (揺れるトリリトン)、 (トリリトン==世界遺産ストーンヘンジの三つ石)
	SPELL_3a_pache_silver_dragon,		/* [パチェ] "　　　金符「シルバードラゴン」" No.27 */	// silver dragon (銀翼竜)
	SPELL_3b_pache_lava_cromlech,		/* [パチェ] "火＆土符「ラーヴァクロムレク」" No.28 */	// lava cromlech (溶岩環状列石)
	SPELL_3c_pache_forest_blaze,		/* [パチェ] "木＆火符「フォレストブレイズ」" No.29 */	// forest blaze (森林火災)
	SPELL_3d_pache_water_elf,			/* [パチェ] "　水＆木符「ウォーターエルフ」" No.30 */	// water (水) / elf (妖精)	(ギャグ:水溶性==水に溶けちゃう妖精)
	SPELL_3e_pache_mercury_poison,		/* [パチェ] "金＆水符「マーキュリポイズン」" No.31 */	// mercury poison (水銀中毒)
	SPELL_3f_pache_emerald_megalith,	/* [パチェ] "土＆金符「エメラルドメガリス」" No.32 */	// emerald megalith (巨大なエメラルド石)
		//
/*40*/	SPELL_40_PACHE_LASER1,				/* [パチェ] 「通常攻撃1」のレーザーもどき */
/*41*/	SPELL_41_PACHE_LASER2,				/* [パチェ] 「通常攻撃3」のレーザーもどき */
/*4e*/	SPELL_42_remilia_vlad_tepes,		/* 9[咲夜/レミリア] 紅6面ボス 呪詛「ブラド・ツェペシュの呪い」*/
/*4f*/	SPELL_43_remilia_red_magic, 		/* 9[咲夜/レミリア] 紅6面ボス 「レッドマジック」っぽい(?)*/
/*4d*/	SPELL_44_remilia_rasen_knife,		/* 9[咲夜/レミリア] 紅6面ボス 赤ナイフ螺旋弾(予定) */
/*47*/	SPELL_45_sakuya_festival_knife, 	/* [咲夜] 幻想「フェスティバルナイフ」(?) むりやり変換 */
/*42*/	SPELL_46_mima_sekkin,				/* [魅魔] 接近カード */
/*43*/	SPELL_47_mima_toge, 				/* [魅魔] トゲてすとカード */
		//
/*49*/	SPELL_48_kaguya000, 						/* [輝夜] むりやり変換000 SPELL_49_kaguya111 */
/*44*/	SPELL_49_kaguya111, 						/* [輝夜] むりやり変換111 */
/*45*/	SPELL_4a_kaguya222, 						/* [輝夜] むりやり変換222 */
/*46*/	SPELL_4b_kakuya333_tamanoe, 				/* [輝夜] むりやり変換333  [輝夜]、蓬莱の玉の枝もどき。作成中 */
/*4c*/	SPELL_4c_kakuya_tamanoe_bbb,				/* [輝夜] むりやり変換444 */
/*4a*/	SPELL_4d_rumia_3nerai,						/* [ルーミア] */
/*4b*/	SPELL_4e_test,								/* [輝夜] てすと */
/*48*/	SPELL_4f_aya_taifu, 						/* [文] 大風形態 */
//
/*50*/	SPELL_50_,
/*51*/	SPELL_51_kaguya_tujyou_kougeki_01,			// 通常攻撃1
/*52*/	SPELL_52_kaguya_tatu_no_kubi_no_tama,		// 難題「龍の頸の玉　-五色の弾丸-」
/*53*/	SPELL_53_kaguya_brilliant_dragon_bullet,	// 神宝「ブリリアントドラゴンバレッタ」
/*54*/	SPELL_54_kaguya_tujyou_kougeki_02,			// 通常攻撃2,
/*55*/	SPELL_55_kaguya_hotoke_no_oisi_no_hati, 	// 難題「仏の御石の鉢　-砕けぬ意志-」,
/*56*/	SPELL_56_kaguya_bdist_diamond,				// 神宝「ブディストダイアモンド」
/*57*/	SPELL_57_kaguya_tujyou_kougeki_03,			// 通常攻撃3,
		//
/*58*/	SPELL_58_kaguya_hi_nezumi_no_kawa_goromo,	// 難題「火鼠の皮衣　-焦れぬ心-」,
/*59*/	SPELL_59_kaguya_salamnder_shiled,			// 神宝「サラマンダーシールド」
/*5a*/	SPELL_5a_kaguya_tujyou_kougeki_04,			// 通常攻撃4,
/*5b*/	SPELL_5b_kaguya_tubame_no_koyasugai,		// 難題「燕の子安貝　-永命線-」
/*5c*/	SPELL_5c_kaguya_life_spring_infinity,		// 神宝「ライフスプリングインフィニティ」
/*5d*/	SPELL_5d_kaguya_hourai_no_tama_no_eda01,	// 難題「蓬莱の玉の枝　-虹色の弾幕-」
/*5e*/	SPELL_5e_kaguya_hourai_no_tama_no_eda02,	// 神宝「蓬莱の玉の枝　-夢色の郷-」
/*5f*/	SPELL_5f_kaguya_eiya_gaesi_yoake,			// 「永夜返し　‐夜明け‐」（N）
//
	SPELL_MAX,
};
//	SPELL_1f_silent_selena, 			/* [パチェ] サイレントセレナ の てすと用 */

#endif /* _SPELL_NAME_VALUE_H_ */
