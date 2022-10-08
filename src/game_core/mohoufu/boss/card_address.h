
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	カードアドレス
	-------------------------------------------------------
	カードの絶対位置を示す一意の値（カードアドレス）を定義します。
	-------------------------------------------------------
	絶対位置は、難易度別に異なります。
	また五面の場合は、キャラ別によって絶対位置が異なります。
	-------------------------------------------------------
	カードアドレスはカード番号とは異なります。
	違うカードアドレスに同じカード番号を配置する事が出来ます。
	-------------------------------------------------------
	具体例では、
	パチェ 5面	霊夢 B (夢符)で、8形態目（カードアドレス）が
	土＆金符「エメラルドメガリス」（カード番号）で、
	パチェ 5面	魔理沙 A (魔符)、7形態目（カードアドレス）が
	土＆金符「エメラルドメガリス」（カード番号）と言う事です。
---------------------------------------------------------*/

#ifndef _CARD_ADDRESS_VALUE_H_
#define _CARD_ADDRESS_VALUE_H_

//	CARD_ADDRESS_00_OFF = 0,
enum
{
// ??? ファンタズムステージ
	CARD_ADDRESS_00E_ph_000 = 0, /* "形態変更" */
	CARD_ADDRESS_00N_ph_000,	/* "形態変更" */
	CARD_ADDRESS_00H_ph_000,	/* "形態変更" */
	CARD_ADDRESS_00L_ph_000,	/* "形態変更" */
	//
	CARD_ADDRESS_01E_ph_aaa,	/* 第01形態: ""*/
	CARD_ADDRESS_01N_ph_aaa,	/* 第01形態: ""*/
	CARD_ADDRESS_01H_ph_aaa,	/* 第01形態: ""*/
	CARD_ADDRESS_01L_ph_aaa,	/* 第01形態: ""*/
	//
	CARD_ADDRESS_02E_ph_bbb,	/* 第02形態: ""*/
	CARD_ADDRESS_02N_ph_bbb,	/* 第02形態: ""*/
	CARD_ADDRESS_02H_ph_bbb,	/* 第02形態: ""*/
	CARD_ADDRESS_02L_ph_bbb,	/* 第02形態: ""*/
	//
	CARD_ADDRESS_03E_ph_ccc,	/* 第03形態: ""*/
	CARD_ADDRESS_03N_ph_ccc,	/* 第03形態: ""*/
	CARD_ADDRESS_03H_ph_ccc,	/* 第03形態: ""*/
	CARD_ADDRESS_03L_ph_ccc,	/* 第03形態: ""*/
	//
	CARD_ADDRESS_04E_ph_ddd,	/* 第04形態: ""*/
	CARD_ADDRESS_04N_ph_ddd,	/* 第04形態: ""*/
	CARD_ADDRESS_04H_ph_ddd,	/* 第04形態: ""*/
	CARD_ADDRESS_04L_ph_ddd,	/* 第04形態: ""*/
	//
	CARD_ADDRESS_05E_ph_eee,	/* 第05形態: ""*/
	CARD_ADDRESS_05N_ph_eee,	/* 第05形態: ""*/
	CARD_ADDRESS_05H_ph_eee,	/* 第05形態: ""*/
	CARD_ADDRESS_05L_ph_eee,	/* 第05形態: ""*/
	//
	CARD_ADDRESS_06E_ph_fff,	/* 第06形態: ""*/
	CARD_ADDRESS_06N_ph_fff,	/* 第06形態: ""*/
	CARD_ADDRESS_06H_ph_fff,	/* 第06形態: ""*/
	CARD_ADDRESS_06L_ph_fff,	/* 第06形態: ""*/
	//
	CARD_ADDRESS_07E_ph_ggg,	/* 第07形態: ""*/
	CARD_ADDRESS_07N_ph_ggg,	/* 第07形態: ""*/
	CARD_ADDRESS_07H_ph_ggg,	/* 第07形態: ""*/
	CARD_ADDRESS_07L_ph_ggg,	/* 第07形態: ""*/
	//
	CARD_ADDRESS_08E_ph_hhh,	/* 第08形態: ""*/
	CARD_ADDRESS_08N_ph_hhh,	/* 第08形態: ""*/
	CARD_ADDRESS_08H_ph_hhh,	/* 第08形態: ""*/
	CARD_ADDRESS_08L_ph_hhh,	/* 第08形態: ""*/
	//
	CARD_ADDRESS_09E_ph_iii,	/* 第09形態: ""*/
	CARD_ADDRESS_09N_ph_iii,	/* 第09形態: ""*/
	CARD_ADDRESS_09H_ph_iii,	/* 第09形態: ""*/
	CARD_ADDRESS_09L_ph_iii,	/* 第09形態: ""*/
	//
	CARD_ADDRESS_10E_ph_jjj,	/* 第10形態: ""*/
	CARD_ADDRESS_10N_ph_jjj,	/* 第10形態: ""*/
	CARD_ADDRESS_10H_ph_jjj,	/* 第10形態: ""*/
	CARD_ADDRESS_10L_ph_jjj,	/* 第10形態: ""*/
	//
	CARD_ADDRESS_11E_ph_kkk,	/* 第11形態: ""*/
	CARD_ADDRESS_11N_ph_kkk,	/* 第11形態: ""*/
	CARD_ADDRESS_11H_ph_kkk,	/* 第11形態: ""*/
	CARD_ADDRESS_11L_ph_kkk,	/* 第11形態: ""*/
	//
	CARD_ADDRESS_12E_ph_lll,	/* 第12形態: ""*/
	CARD_ADDRESS_12N_ph_lll,	/* 第12形態: ""*/
	CARD_ADDRESS_12H_ph_lll,	/* 第12形態: ""*/
	CARD_ADDRESS_12L_ph_lll,	/* 第12形態: ""*/
	//
	CARD_ADDRESS_13E_ph_mmm,	/* 第13形態: ""*/
	CARD_ADDRESS_13N_ph_mmm,	/* 第13形態: ""*/
	CARD_ADDRESS_13H_ph_mmm,	/* 第13形態: ""*/
	CARD_ADDRESS_13L_ph_mmm,	/* 第13形態: ""*/
	//
	CARD_ADDRESS_14E_ph_nnn,	/* 第14形態: ""*/
	CARD_ADDRESS_14N_ph_nnn,	/* 第14形態: ""*/
	CARD_ADDRESS_14H_ph_nnn,	/* 第14形態: ""*/
	CARD_ADDRESS_14L_ph_nnn,	/* 第14形態: ""*/
	//
	CARD_ADDRESS_15E_ph_ooo,	/* 第15形態: ""*/
	CARD_ADDRESS_15N_ph_ooo,	/* 第15形態: ""*/
	CARD_ADDRESS_15H_ph_ooo,	/* 第15形態: ""*/
	CARD_ADDRESS_15L_ph_ooo,	/* 第15形態: ""*/
	//
	CARD_ADDRESS_16E_ph_ppp,	/* 第16形態: ""*/
	CARD_ADDRESS_16N_ph_ppp,	/* 第16形態: ""*/
	CARD_ADDRESS_16H_ph_ppp,	/* 第16形態: ""*/
	CARD_ADDRESS_16L_ph_ppp,	/* 第16形態: ""*/
	//
	CARD_ADDRESS_17E_ph_qqq,	/* 第17形態: ""*/
	CARD_ADDRESS_17N_ph_qqq,	/* 第17形態: ""*/
	CARD_ADDRESS_17H_ph_qqq,	/* 第17形態: ""*/
	CARD_ADDRESS_17L_ph_qqq,	/* 第17形態: ""*/
	//
	CARD_ADDRESS_18E_ph_rrr,	/* 第18形態: ""*/
	CARD_ADDRESS_18N_ph_rrr,	/* 第18形態: ""*/
	CARD_ADDRESS_18H_ph_rrr,	/* 第18形態: ""*/
	CARD_ADDRESS_18L_ph_rrr,	/* 第18形態: ""*/
	//
	CARD_ADDRESS_19E_ph_sss,	/* 第19形態: ""*/
	CARD_ADDRESS_19N_ph_sss,	/* 第19形態: ""*/
	CARD_ADDRESS_19H_ph_sss,	/* 第19形態: ""*/
	CARD_ADDRESS_19L_ph_sss,	/* 第19形態: ""*/
	//
	CARD_ADDRESS_20E_ph_tee,	/* 第20形態: ""*/
	CARD_ADDRESS_20N_ph_tee,	/* 第20形態: ""*/
	CARD_ADDRESS_20H_ph_tee,	/* 第20形態: ""*/
	CARD_ADDRESS_20L_ph_tee,	/* 第20形態: ""*/
	//
	CARD_ADDRESS_21E_ph_uaa,	/* 第21形態: ""*/
	CARD_ADDRESS_21N_ph_uaa,	/* 第21形態: ""*/
	CARD_ADDRESS_21H_ph_uaa,	/* 第21形態: ""*/
	CARD_ADDRESS_21L_ph_uaa,	/* 第21形態: ""*/
	//
	CARD_ADDRESS_22E_ph_vbb,	/* 第22形態: ""*/
	CARD_ADDRESS_22N_ph_vbb,	/* 第22形態: ""*/
	CARD_ADDRESS_22H_ph_vbb,	/* 第22形態: ""*/
	CARD_ADDRESS_22L_ph_vbb,	/* 第22形態: ""*/
	//
	CARD_ADDRESS_23E_ph_wcc,	/* 第23形態: ""*/
	CARD_ADDRESS_23N_ph_wcc,	/* 第23形態: ""*/
	CARD_ADDRESS_23H_ph_wcc,	/* 第23形態: ""*/
	CARD_ADDRESS_23L_ph_wcc,	/* 第23形態: ""*/
	//
	CARD_ADDRESS_24E_ph_xdd,	/* 第24形態: ""*/
	CARD_ADDRESS_24N_ph_xdd,	/* 第24形態: ""*/
	CARD_ADDRESS_24H_ph_xdd,	/* 第24形態: ""*/
	CARD_ADDRESS_24L_ph_xdd,	/* 第24形態: ""*/
	//
	CARD_ADDRESS_25E_ph_yee,	/* 第25形態: ""*/
	CARD_ADDRESS_25N_ph_yee,	/* 第25形態: ""*/
	CARD_ADDRESS_25H_ph_yee,	/* 第25形態: ""*/
	CARD_ADDRESS_25L_ph_yee,	/* 第25形態: ""*/
	//
	CARD_ADDRESS_26E_ph_zzz,	/* 第26形態: ""*/
	CARD_ADDRESS_26N_ph_zzz,	/* 第26形態: ""*/
	CARD_ADDRESS_26H_ph_zzz,	/* 第26形態: ""*/
	CARD_ADDRESS_26L_ph_zzz,	/* 第26形態: ""*/
	//
	CARD_ADDRESS_27E_ph_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_27N_ph_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_27H_ph_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_27L_ph_gekiha, /*(r36強制的に撃破)*/
// チルノ エキストラステージ
	CARD_ADDRESS_00E_chrno_000, 	/* "形態変更" */
	CARD_ADDRESS_00N_chrno_000, 	/* "形態変更" */
	CARD_ADDRESS_00H_chrno_000, 	/* "形態変更" */
	CARD_ADDRESS_00L_chrno_000, 	/* "形態変更" */
	CARD_ADDRESS_01E_chrno_aaa, 	/* 第一形態: "通常攻撃1"*/
	CARD_ADDRESS_01N_chrno_aaa, 	/* 第一形態: "通常攻撃1"*/
	CARD_ADDRESS_01H_chrno_aaa, 	/* 第一形態: "通常攻撃1"*/
	CARD_ADDRESS_01L_chrno_aaa, 	/* 第一形態: "通常攻撃1"*/
	CARD_ADDRESS_02E_chrno_bbb, 	/* 第二形態: 氷符「アイシクルフォール」*/
	CARD_ADDRESS_02N_chrno_bbb, 	/* 第二形態: 氷符「アイシクルフォール」*/
	CARD_ADDRESS_02H_chrno_bbb, 	/* 第二形態: 氷符「アイシクルフォール」*/
	CARD_ADDRESS_02L_chrno_bbb, 	/* 第二形態: 氷符「アイシクルフォール」*/
	CARD_ADDRESS_03E_chrno_ccc, 	/* 第三形態:「通常攻撃2」 */
	CARD_ADDRESS_03N_chrno_ccc, 	/* 第三形態:「通常攻撃2」 */
	CARD_ADDRESS_03H_chrno_ccc, 	/* 第三形態:「通常攻撃2」 */
	CARD_ADDRESS_03L_chrno_ccc, 	/* 第三形態:「通常攻撃2」 */
	CARD_ADDRESS_04E_chrno_ddd, 	/* 第四形態: 凍符「パーフェクトフリーズ」*/
	CARD_ADDRESS_04N_chrno_ddd, 	/* 第四形態: 凍符「パーフェクトフリーズ」*/
	CARD_ADDRESS_04H_chrno_ddd, 	/* 第四形態: 凍符「パーフェクトフリーズ」*/
	CARD_ADDRESS_04L_chrno_ddd, 	/* 第四形態: 凍符「パーフェクトフリーズ」*/
	CARD_ADDRESS_05E_chrno_eee, 	/* 第五形態: 雪符「ダイアモンドブリザード」*/
	CARD_ADDRESS_05N_chrno_eee, 	/* 第五形態: 雪符「ダイアモンドブリザード」*/
	CARD_ADDRESS_05H_chrno_eee, 	/* 第五形態: 雪符「ダイアモンドブリザード」*/
	CARD_ADDRESS_05L_chrno_eee, 	/* 第五形態: 雪符「ダイアモンドブリザード」*/
	CARD_ADDRESS_06E_chrno_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_06N_chrno_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_06H_chrno_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_06L_chrno_gekiha,	/*(r36強制的に撃破)*/
// 咲夜 6面
	CARD_ADDRESS_00E_sakuya_000,	/* "形態変更" */
	CARD_ADDRESS_00N_sakuya_000,	/* "形態変更" */
	CARD_ADDRESS_00H_sakuya_000,	/* "形態変更" */
	CARD_ADDRESS_00L_sakuya_000,	/* "形態変更" */
	CARD_ADDRESS_01E_sakuya_aaa,	/* 第一形態: 通常攻撃(左右に動いて禊弾撃ち) */
	CARD_ADDRESS_01N_sakuya_aaa,	/* 第一形態: 通常攻撃(左右に動いて禊弾撃ち) */
	CARD_ADDRESS_01H_sakuya_aaa,	/* 第一形態: 通常攻撃(左右に動いて禊弾撃ち) */
	CARD_ADDRESS_01L_sakuya_aaa,	/* 第一形態: 通常攻撃(左右に動いて禊弾撃ち) */
	CARD_ADDRESS_02E_sakuya_bbb,	/* 第二形態: 奇術「ミスディレクション」(全方位、豆まき) */
	CARD_ADDRESS_02N_sakuya_bbb,	/* 第二形態: 奇術「ミスディレクション」(全方位、豆まき) */
	CARD_ADDRESS_02H_sakuya_bbb,	/* 第二形態: 奇術「ミスディレクション」(全方位、豆まき) */
	CARD_ADDRESS_02L_sakuya_bbb,	/* 第二形態: 奇術「ミスディレクション」(全方位、豆まき) */
	CARD_ADDRESS_03E_sakuya_ccc,	/* 第三形態: 螺旋赤ナイフ  */
	CARD_ADDRESS_03N_sakuya_ccc,	/* 第三形態: 螺旋赤ナイフ  */
	CARD_ADDRESS_03H_sakuya_ccc,	/* 第三形態: 螺旋赤ナイフ  */
	CARD_ADDRESS_03L_sakuya_ccc,	/* 第三形態: 螺旋赤ナイフ  */
	CARD_ADDRESS_04E_sakuya_ddd,	/* 第四形態:  */
	CARD_ADDRESS_04N_sakuya_ddd,	/* 第四形態:  */
	CARD_ADDRESS_04H_sakuya_ddd,	/* 第四形態:  */
	CARD_ADDRESS_04L_sakuya_ddd,	/* 第四形態:  */
	CARD_ADDRESS_05E_sakuya_eee,	/* 第五形態:  */
	CARD_ADDRESS_05N_sakuya_eee,	/* 第五形態:  */
	CARD_ADDRESS_05H_sakuya_eee,	/* 第五形態:  */
	CARD_ADDRESS_05L_sakuya_eee,	/* 第五形態:  */
	CARD_ADDRESS_06E_sakuya_fff,	/* 第六形態:  */
	CARD_ADDRESS_06N_sakuya_fff,	/* 第六形態:  */
	CARD_ADDRESS_06H_sakuya_fff,	/* 第六形態:  */
	CARD_ADDRESS_06L_sakuya_fff,	/* 第六形態:  */
	CARD_ADDRESS_07E_sakuya_ggg,	/* 第七形態: (分散魔方陣)追加計画中 */
	CARD_ADDRESS_07N_sakuya_ggg,	/* 第七形態: (分散魔方陣)追加計画中 */
	CARD_ADDRESS_07H_sakuya_ggg,	/* 第七形態: (分散魔方陣)追加計画中 */
	CARD_ADDRESS_07L_sakuya_ggg,	/* 第七形態: (分散魔方陣)追加計画中 */
	CARD_ADDRESS_08E_sakuya_hhh,	/* 第八形態: (時止めナイフ)追加計画中 */
	CARD_ADDRESS_08N_sakuya_hhh,	/* 第八形態: (時止めナイフ)追加計画中 */
	CARD_ADDRESS_08H_sakuya_hhh,	/* 第八形態: (時止めナイフ)追加計画中 */
	CARD_ADDRESS_08L_sakuya_hhh,	/* 第八形態: (時止めナイフ)追加計画中 */
	CARD_ADDRESS_09E_sakuya_iii,	/* 第九形態: 最終形態(その1) */
	CARD_ADDRESS_09N_sakuya_iii,	/* 第九形態: 最終形態(その1) */
	CARD_ADDRESS_09H_sakuya_iii,	/* 第九形態: 最終形態(その1) */
	CARD_ADDRESS_09L_sakuya_iii,	/* 第九形態: 最終形態(その1) */
	CARD_ADDRESS_10E_sakuya_jjj,	/* 第10形態: 最終形態(その2) */
	CARD_ADDRESS_10N_sakuya_jjj,	/* 第10形態: 最終形態(その2) */
	CARD_ADDRESS_10H_sakuya_jjj,	/* 第10形態: 最終形態(その2) */
	CARD_ADDRESS_10L_sakuya_jjj,	/* 第10形態: 最終形態(その2) */
	CARD_ADDRESS_11E_sakuya_kkk,	/* 第11形態: 最終形態(その3) */
	CARD_ADDRESS_11N_sakuya_kkk,	/* 第11形態: 最終形態(その3) */
	CARD_ADDRESS_11H_sakuya_kkk,	/* 第11形態: 最終形態(その3) */
	CARD_ADDRESS_11L_sakuya_kkk,	/* 第11形態: 最終形態(その3) */
	CARD_ADDRESS_12E_sakuya_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_12N_sakuya_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_12H_sakuya_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_12L_sakuya_gekiha, /*(r36強制的に撃破)*/
// パチェA 5面
	CARD_ADDRESS_00E_pacheA_000,	/* "形態変更" */
	CARD_ADDRESS_00N_pacheA_000,	/* "形態変更" */
	CARD_ADDRESS_00H_pacheA_000,	/* "形態変更" */
	CARD_ADDRESS_00L_pacheA_000,	/* "形態変更" */
	CARD_ADDRESS_01E_pacheA_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01N_pacheA_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01H_pacheA_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01L_pacheA_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_02E_pacheA_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_02N_pacheA_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_02H_pacheA_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_02L_pacheA_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_03E_pacheA_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03N_pacheA_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03H_pacheA_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03L_pacheA_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_04E_pacheA_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_04N_pacheA_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_04H_pacheA_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_04L_pacheA_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_05E_pacheA_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_05N_pacheA_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_05H_pacheA_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_05L_pacheA_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_06E_pacheA_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_06N_pacheA_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_06H_pacheA_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_06L_pacheA_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_07E_pacheA_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_07N_pacheA_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_07H_pacheA_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_07L_pacheA_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_08E_pacheA_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_08N_pacheA_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_08H_pacheA_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_08L_pacheA_gekiha, /*(r36強制的に撃破)*/
// パチェB 5面
	CARD_ADDRESS_10E_pacheB_000,	/* "形態変更" */
	CARD_ADDRESS_10N_pacheB_000,	/* "形態変更" */
	CARD_ADDRESS_10H_pacheB_000,	/* "形態変更" */
	CARD_ADDRESS_10L_pacheB_000,	/* "形態変更" */
	CARD_ADDRESS_11E_pacheB_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_11N_pacheB_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_11H_pacheB_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_11L_pacheB_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_12E_pacheB_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_12N_pacheB_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_12H_pacheB_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_12L_pacheB_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_13E_pacheB_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_13N_pacheB_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_13H_pacheB_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_13L_pacheB_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_14E_pacheB_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_14N_pacheB_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_14H_pacheB_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_14L_pacheB_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_15E_pacheB_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_15N_pacheB_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_15H_pacheB_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_15L_pacheB_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_16E_pacheB_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_16N_pacheB_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_16H_pacheB_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_16L_pacheB_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_17E_pacheB_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_17N_pacheB_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_17H_pacheB_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_17L_pacheB_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_18E_pacheB_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_18N_pacheB_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_18H_pacheB_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_18L_pacheB_gekiha, /*(r36強制的に撃破)*/
// パチェC 5面
	CARD_ADDRESS_20E_pacheC_000,	/* "形態変更" */
	CARD_ADDRESS_20N_pacheC_000,	/* "形態変更" */
	CARD_ADDRESS_20H_pacheC_000,	/* "形態変更" */
	CARD_ADDRESS_20L_pacheC_000,	/* "形態変更" */
	CARD_ADDRESS_21E_pacheC_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_21N_pacheC_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_21H_pacheC_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_21L_pacheC_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_22E_pacheC_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_22N_pacheC_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_22H_pacheC_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_22L_pacheC_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_23E_pacheC_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_23N_pacheC_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_23H_pacheC_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_23L_pacheC_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_24E_pacheC_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_24N_pacheC_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_24H_pacheC_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_24L_pacheC_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_25E_pacheC_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_25N_pacheC_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_25H_pacheC_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_25L_pacheC_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_26E_pacheC_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_26N_pacheC_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_26H_pacheC_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_26L_pacheC_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_27E_pacheC_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_27N_pacheC_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_27H_pacheC_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_27L_pacheC_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_28E_pacheC_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_28N_pacheC_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_28H_pacheC_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_28L_pacheC_gekiha, /*(r36強制的に撃破)*/
// パチェD 5面
	CARD_ADDRESS_30E_pacheD_000,	/* "形態変更" */
	CARD_ADDRESS_30N_pacheD_000,	/* "形態変更" */
	CARD_ADDRESS_30H_pacheD_000,	/* "形態変更" */
	CARD_ADDRESS_30L_pacheD_000,	/* "形態変更" */
	CARD_ADDRESS_31E_pacheD_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_31N_pacheD_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_31H_pacheD_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_31L_pacheD_bbb,	/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_32E_pacheD_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_32N_pacheD_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_32H_pacheD_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_32L_pacheD_ccc,	/* 第二形態: カードⅠ */
	CARD_ADDRESS_33E_pacheD_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_33N_pacheD_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_33H_pacheD_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_33L_pacheD_ddd,	/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_34E_pacheD_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_34N_pacheD_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_34H_pacheD_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_34L_pacheD_eee,	/* 第四形態: カードⅡ */
	CARD_ADDRESS_35E_pacheD_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_35N_pacheD_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_35H_pacheD_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_35L_pacheD_fff,	/* 第五形態: カードⅢ */
	CARD_ADDRESS_36E_pacheD_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_36N_pacheD_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_36H_pacheD_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_36L_pacheD_ggg,	/* 第六形態: カードⅣ */
	CARD_ADDRESS_37E_pacheD_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_37N_pacheD_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_37H_pacheD_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_37L_pacheD_hhh,	/* 第七形態: カードⅤ */
	CARD_ADDRESS_38E_pacheD_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_38N_pacheD_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_38H_pacheD_gekiha, /*(r36強制的に撃破)*/
	CARD_ADDRESS_38L_pacheD_gekiha, /*(r36強制的に撃破)*/
// 文 4面
	CARD_ADDRESS_00E_aya_000,		/* "形態変更" */
	CARD_ADDRESS_00N_aya_000,		/* "形態変更" */
	CARD_ADDRESS_00H_aya_000,		/* "形態変更" */
	CARD_ADDRESS_00L_aya_000,		/* "形態変更" */
	CARD_ADDRESS_01E_aya_bbb,		/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01N_aya_bbb,		/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01H_aya_bbb,		/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_01L_aya_bbb,		/* 第一形態: 通常攻撃1 */
	CARD_ADDRESS_02E_aya_ccc,		/* 第二形態: カードⅠ */
	CARD_ADDRESS_02N_aya_ccc,		/* 第二形態: カードⅠ */
	CARD_ADDRESS_02H_aya_ccc,		/* 第二形態: カードⅠ */
	CARD_ADDRESS_02L_aya_ccc,		/* 第二形態: カードⅠ */
	CARD_ADDRESS_03E_aya_ddd,		/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03N_aya_ddd,		/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03H_aya_ddd,		/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_03L_aya_ddd,		/* 第三形態: 通常攻撃2 */
	CARD_ADDRESS_04E_aya_eee,		/* 第四形態: カードⅡ */
	CARD_ADDRESS_04N_aya_eee,		/* 第四形態: カードⅡ */
	CARD_ADDRESS_04H_aya_eee,		/* 第四形態: カードⅡ */
	CARD_ADDRESS_04L_aya_eee,		/* 第四形態: カードⅡ */
	CARD_ADDRESS_05E_aya_fff,		/* 第五形態: カードⅢ */
	CARD_ADDRESS_05N_aya_fff,		/* 第五形態: カードⅢ */
	CARD_ADDRESS_05H_aya_fff,		/* 第五形態: カードⅢ */
	CARD_ADDRESS_05L_aya_fff,		/* 第五形態: カードⅢ */
	CARD_ADDRESS_06E_aya_ggg,		/* 第六形態: カードⅣ */
	CARD_ADDRESS_06N_aya_ggg,		/* 第六形態: カードⅣ */
	CARD_ADDRESS_06H_aya_ggg,		/* 第六形態: カードⅣ */
	CARD_ADDRESS_06L_aya_ggg,		/* 第六形態: カードⅣ */
	CARD_ADDRESS_07E_aya_hhh,		/* 第七形態: カードⅤ */
	CARD_ADDRESS_07N_aya_hhh,		/* 第七形態: カードⅤ */
	CARD_ADDRESS_07H_aya_hhh,		/* 第七形態: カードⅤ */
	CARD_ADDRESS_07L_aya_hhh,		/* 第七形態: カードⅤ */
	CARD_ADDRESS_08E_aya_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_08N_aya_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_08H_aya_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_08L_aya_gekiha,	/*(r36強制的に撃破)*/
// 輝夜 3面
	CARD_ADDRESS_00E_kaguya_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00N_kaguya_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00H_kaguya_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00L_kaguya_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_51E_kaguya_bbb,/* "通常攻撃1" "\n"*/
	CARD_ADDRESS_51N_kaguya_bbb,/* "通常攻撃1" "\n"*/
	CARD_ADDRESS_51H_kaguya_bbb,/* "通常攻撃1" "\n"*/
	CARD_ADDRESS_51L_kaguya_bbb,/* "通常攻撃1" "\n"*/
	CARD_ADDRESS_52E_kaguya_ccc,// " 難題「龍の頸の玉 五色の弾丸」" "\n",
	CARD_ADDRESS_52N_kaguya_ccc,// " 難題「龍の頸の玉 五色の弾丸」" "\n",
	CARD_ADDRESS_52H_kaguya_ccc,// "　神宝「ブリリアントドラゴン」" "\n",
	CARD_ADDRESS_52L_kaguya_ccc,// "　神宝「ブリリアントドラゴン」" "\n",
	CARD_ADDRESS_53E_kaguya_ddd,/* "通常攻撃2" "\n"*/
	CARD_ADDRESS_53N_kaguya_ddd,/* "通常攻撃2" "\n"*/
	CARD_ADDRESS_53H_kaguya_ddd,/* "通常攻撃2" "\n"*/
	CARD_ADDRESS_53L_kaguya_ddd,/* "通常攻撃2" "\n"*/
	CARD_ADDRESS_54E_kaguya_eee,// "難題「仏の御石の鉢砕けぬ意志」" "\n",
	CARD_ADDRESS_54N_kaguya_eee,// "難題「仏の御石の鉢砕けぬ意志」" "\n",
	CARD_ADDRESS_54H_kaguya_eee,// "神宝「ブディストダイアモンド」" "\n",
	CARD_ADDRESS_54L_kaguya_eee,// "神宝「ブディストダイアモンド」" "\n",
	CARD_ADDRESS_55E_kaguya_fff,/* "通常攻撃3" "\n"*/
	CARD_ADDRESS_55N_kaguya_fff,/* "通常攻撃3" "\n"*/
	CARD_ADDRESS_55H_kaguya_fff,/* "通常攻撃3" "\n"*/
	CARD_ADDRESS_55L_kaguya_fff,/* "通常攻撃3" "\n"*/
	CARD_ADDRESS_56E_kaguya_ggg,// " 　難題「火鼠の皮衣 焦れぬ心」" "\n",
	CARD_ADDRESS_56N_kaguya_ggg,// " 　難題「火鼠の皮衣 焦れぬ心」" "\n",
	CARD_ADDRESS_56H_kaguya_ggg,// "　神宝「サラマンダーシールド」" "\n",
	CARD_ADDRESS_56L_kaguya_ggg,// "　神宝「サラマンダーシールド」" "\n",
	CARD_ADDRESS_57E_kaguya_hhh,/* "通常攻撃4" "\n"*/
	CARD_ADDRESS_57N_kaguya_hhh,/* "通常攻撃4" "\n"*/
	CARD_ADDRESS_57H_kaguya_hhh,/* "通常攻撃4" "\n"*/
	CARD_ADDRESS_57L_kaguya_hhh,/* "通常攻撃4" "\n"*/
	CARD_ADDRESS_58E_kaguya_iii,// " 　　難題「燕の子安貝 永命線」" "\n",
	CARD_ADDRESS_58N_kaguya_iii,// " 　　難題「燕の子安貝 永命線」" "\n",
	CARD_ADDRESS_58H_kaguya_iii,// "　神宝「ライフインフィニティ」" "\n",
	CARD_ADDRESS_58L_kaguya_iii,// "　神宝「ライフインフィニティ」" "\n",
	CARD_ADDRESS_59E_kaguya_jjj,// "難題「蓬莱の玉の枝虹色の弾幕」" "\n",
	CARD_ADDRESS_59N_kaguya_jjj,// "難題「蓬莱の玉の枝虹色の弾幕」" "\n",
	CARD_ADDRESS_59H_kaguya_jjj,// " 神宝「蓬莱の玉の枝 夢色の郷」" "\n",
	CARD_ADDRESS_59L_kaguya_jjj,// " 神宝「蓬莱の玉の枝 夢色の郷」" "\n",
	CARD_ADDRESS_5aE_kaguya_fff,// " 　　　　　　「永夜返し 朝靄」" "\n",
	CARD_ADDRESS_5aN_kaguya_fff,// " 　　　　　「永夜返し 夜明け」" "\n",
	CARD_ADDRESS_5aH_kaguya_fff,// " 　　　「永夜返し 明けの明星」" "\n",
	CARD_ADDRESS_5aL_kaguya_fff,// " 　　　　　「永夜返し 夜明け」" "\n",
	CARD_ADDRESS_5bE_kaguya_gekiha, 	/*(r36強制的に撃破)*/
	CARD_ADDRESS_5bN_kaguya_gekiha, 	/*(r36強制的に撃破)*/
	CARD_ADDRESS_5bH_kaguya_gekiha, 	/*(r36強制的に撃破)*/
	CARD_ADDRESS_5bL_kaguya_gekiha, 	/*(r36強制的に撃破)*/
// 未定 2面
	CARD_ADDRESS_00E_mima_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00N_mima_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00H_mima_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00L_mima_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_61E_mima_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_61N_mima_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_61H_mima_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_61L_mima_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_62E_mima_ccc,// " 　　　未定「未作成カードE01」" "\n",
	CARD_ADDRESS_62N_mima_ccc,// " 　　　未定「未作成カードN01」" "\n",
	CARD_ADDRESS_62H_mima_ccc,// " 　　　未定「未作成カードH01」" "\n",
	CARD_ADDRESS_62L_mima_ccc,// " 　　　未定「未作成カードL01」" "\n",
	CARD_ADDRESS_63E_mima_ddd,// "　　闇符「ディマーケイション」" "\n",
	CARD_ADDRESS_63N_mima_ddd,// "　　闇符「ディマーケイション」" "\n",
	CARD_ADDRESS_63H_mima_ddd,// "　　闇符「ディマーケイション」" "\n",
	CARD_ADDRESS_63L_mima_ddd,// "　　闇符「ディマーケイション」" "\n",
	CARD_ADDRESS_64E_mima_eee,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_64N_mima_eee,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_64H_mima_eee,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_64L_mima_eee,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_65E_mima_fff,// "　　　　　　　華符「芳華絢爛」" "\n",
	CARD_ADDRESS_65N_mima_fff,// "　　　　　　　華符「芳華絢爛」" "\n",
	CARD_ADDRESS_65H_mima_fff,// "　　　　　　　華符「芳華絢爛」" "\n",
	CARD_ADDRESS_65L_mima_fff,// "　　　　　　　華符「芳華絢爛」" "\n",
	CARD_ADDRESS_66E_mima_ggg,// " 　　　未定「未作成カードE05」" "\n",
	CARD_ADDRESS_66N_mima_ggg,// " 　　　未定「未作成カードN05」" "\n",
	CARD_ADDRESS_66H_mima_ggg,// " 　　　未定「未作成カードH05」" "\n",
	CARD_ADDRESS_66L_mima_ggg,// " 　　　未定「未作成カードL05」" "\n",
	CARD_ADDRESS_67E_mima_hhh,// " 　　　未定「てすとカードE06」" "\n",
	CARD_ADDRESS_67N_mima_hhh,// " 　　　未定「てすとカードN06」" "\n",
	CARD_ADDRESS_67H_mima_hhh,// " 　　　未定「てすとカードH06」" "\n",
	CARD_ADDRESS_67L_mima_hhh,// NULL,
	CARD_ADDRESS_68E_mima_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_68N_mima_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_68H_mima_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_68L_mima_gekiha,	/*(r36強制的に撃破)*/
// アリス 1面
	CARD_ADDRESS_00E_alice_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00N_alice_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00H_alice_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_00L_alice_000,/* "形態変更" "\n"*/
	CARD_ADDRESS_71E_alice_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_71N_alice_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_71H_alice_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_71L_alice_bbb,/* "通常攻撃" "\n"*/
	CARD_ADDRESS_72E_alice_ccc,// "　　　　　懐古「紅の魔法Lv.2」" "\n",
	CARD_ADDRESS_72N_alice_ccc,// " 　　　　懐古「紅の魔法Lv.16」" "\n",
	CARD_ADDRESS_72H_alice_ccc,// "　　　　懐古「紅の魔法Lv.256」" "\n",
	CARD_ADDRESS_72L_alice_ccc,// "　　　懐古「紅の魔法Lv.65536」" "\n",
	CARD_ADDRESS_73E_alice_ddd,// " 　　 試作「カード語のてすと」" "\n",
	CARD_ADDRESS_73N_alice_ddd,// "　凍符「パーフェクトフリーズ」" "\n",
	CARD_ADDRESS_73H_alice_ddd,// "　凍符「パーティクルフリーク」" "\n",
	CARD_ADDRESS_73L_alice_ddd,// "　凍符「ブリザードフローズン」" "\n",
	CARD_ADDRESS_74E_alice_eee,// "　蒼符「薄愛のマトリョーシカ」" "\n",
	CARD_ADDRESS_74N_alice_eee,// "　蒼符「溺愛のマトリョーシカ」" "\n",
	CARD_ADDRESS_74H_alice_eee,// "　蒼符「自戒のマトリョーシカ」" "\n",
	CARD_ADDRESS_74L_alice_eee,// "　蒼符「自害のマトリョーシカ」" "\n",
	CARD_ADDRESS_76E_alice_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_76N_alice_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_76H_alice_gekiha,	/*(r36強制的に撃破)*/
	CARD_ADDRESS_76L_alice_gekiha,	/*(r36強制的に撃破)*/
	//
	CARD_ADDRESS_MAX/* 最大数 */
};

#endif /* _CARD_ADDRESS_VALUE_H_ */
