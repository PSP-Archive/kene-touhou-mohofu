
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	このファイルは直接インクルードしません。
	"game_main.h" からのみ間接的にインクルードします。
---------------------------------------------------------*/

#ifndef _CARD_CPU_H_
#define _CARD_CPU_H_
/*---------------------------------------------------------
	カードCPU
---------------------------------------------------------*/

/*---------------------------------------------------------
	カードCPU用のレジスタ(ローカルメモリー)
	-------------------------------------------------------
	将来的に「カード」は、全て「カードスクリプト」で処理する用に移行する(予定)。
	-------------------------------------------------------
	この「カードスクリプト」は、「カードCPU
	(カードスクリプト中央処理ユニット)
	(SPEll-CArd script, Central Prcessing Unit.)」
	が、実際の処理を行う。
	-------------------------------------------------------
	このカードCPUには、レジスタ(Resister)と呼ばれるカードCPUの内部メモリがあり。
	カードCPUを実行させる場合(つまりスペルカードを撃つ場合)に、カードCPUはレジスタ以外アクセスできない。
	-------------------------------------------------------
	仕様:
		ゼロページレジスタ(reg00-reg1f)は、カードスクリプト開始時に必ず(0)で消去される。
		その後、カードスクリプト用の[initialize section: 初期化セクション]で指示された初期化処理が一度だけ行われる。
	-------------------------------------------------------
	難易度レジスタ(r41-)仕様変更:
		難易度レジスタの難易度はいつでも使用できる。
		値を破壊してはダメ。
	-------------------------------------------------------
	(r41-)ボスのコントロールは将来的に、スクリプトから行う必要がある。
	カードCPUはレジスタ以外アクセスできないので、
	ボスの関係の値は、すべてレジスタへ移動した。
	同様に、プレイヤーの値も、スクリプトから行う必要があるので、
	すべてレジスタへ移動した。
	-------------------------------------------------------
	ゼロページ:
		ゼロページだからアクセスが速いなんてことはないよ。
		なんでこんな名前なのかというと、カードスクリプト開始時に
		必ずゼロクリアされるから。
	-------------------------------------------------------
	ToDo:
	カードCPUのI/O ポート(==レジスタ)に、ボスの移動処理もマッピングして、
	ボスのコントロールはすべてカードCPU経由で行う様にする。
	同様にサウンドもすべてI/O ポート(==レジスタ)に、マッピングする。
---------------------------------------------------------*/

/*---------------------------------------------------------
	レジスタ
	-------------------------------------------------------
	'R##' means Register Number, '##' means Hex number(00 ... 2f).
	Always equal 'R##' and '##', but '##' means number and 'R##' means Register Number.
	-------------------------------------------------------
	R## は レジスタ(Register)番号(Number)です。R## == ## です。
	数字(Number)で書くと、数字なのかレジスタなのか判らないのでこうなりました。
	-------------------------------------------------------
	'VR##' means Register Number of Value.
	ex. VR08 = 5; // R08 into value of 5.
	-------------------------------------------------------
	VR## は レジスタ値です。VR## == R##の値 です。
	'V' は Value(意味は値) です。
	C言語では、 VR08 = 5; とやると R08 に数値 5 が入ります。
---------------------------------------------------------*/

enum
{
	// ゼロページ[ゼロクリアされる。]
	// レジスタ(全ての計算は内部レジスタ0x00-0x0fでしか出来ない)
	R00 = (0),	// ZEROレジスタ。 常に 定数(0) を入れる事で、無い場合に比べCPU命令を削減できる。
	R01,		// [未定]CC1レジスタ。CONDITION_CODE1 IFやLOOP等で暗黙に利用(予定)。// [未使用]。
	R02_j,		// jレジスタ(ループ2用)。// 基本的に内側から2番目のループ用。(若しくは雑変数)
	R03_i,		// iレジスタ(ループ1用)。// 基本的に一番内側のループ用。(若しくは雑変数)
	R04,		// 0受け渡しレジスタ。REG_ _00_SRC_X
	R05,		// 1受け渡しレジスタ。REG_ _01_SRC_Y
	R06,		// 2受け渡しレジスタ。REG_ _02_DEST_X
	R07,		// 3受け渡しレジスタ。REG_ _03_DEST_Y
	//
	R08,		// 汎用レジスタ0。
	R09,		// 汎用レジスタ1。
	R0a,		// 汎用レジスタ2。
	R0b,		// 汎用レジスタ3。
	R0c,		// 汎用レジスタ4。
	R0d,		// 汎用レジスタ5。
	R0e,		// 汎用レジスタ6。
	R0f,		// 汎用レジスタ7。
	// I/Oポート(外部の入出力はI/Oポート0x10-0x1fを経由しないと出来ない)
	R10,		// スペル経過時間用レジスタ。REG_ _10_BOSS_SPELL_TIMER
	R11,		// 発弾用レジスタ1。tama_system に接続。HATSUDAN_R11_speed256
	R12,		// 発弾用レジスタ2。tama_system に接続。HATSUDAN_R12_speed_offset
	R13,		// 発弾用レジスタ3。tama_system に接続。HATSUDAN_R13_angle65536
	R14,		// 発弾用レジスタ4。tama_system に接続。HATSUDAN_R14_tama_spec
	R15,		// 発弾用レジスタ5。tama_system に接続。HATSUDAN_R15_bullet_obj_type
	R16,		// 発弾用レジスタ6。tama_system に接続。HATSUDAN_R16_n_way
	R17,		// 発弾用レジスタ7。tama_system に接続。HATSUDAN_R17_div_angle65536
	// スクリプトから効果音をどう扱うか仕様が確定していない。
	R18,		// REG_NUM_18_ VOICE_NUMBER REG_NUM_18_SOUND_REG0, // 効果音番号保持用レジスタ。
	R19,		// REG_NUM_19_ VOICE_TRACK REG_NUM_19_SOUND_REG1, // 効果音トラック番号保持用レジスタ。
	R1a_,					// R1a_SOUND_REG2,	// [未使用]。
	R1b_,					// R1b_SOUND_REG3,	// [未使用]。
	//=================== ここから上は、ゼロクリアされる。
	R1c_bullet_clip_min_x256,					// POINT256 bullet_clip_min;	/* 弾の範囲(最小値)横方向軸座標限界値 */
	R1d_bullet_clip_min_y256,					// POINT256 bullet_clip_min;	/* 弾の範囲(最小値)縦方向軸座標限界値 */
	R1e_bullet_clip_max_x256,					// POINT256 bullet_clip_max;	/* 弾の範囲(最大値)横方向軸座標限界値 */
	R1f_bullet_clip_max_y256,					// POINT256 bullet_clip_max;	/* 弾の範囲(最大値)縦方向軸座標限界値 */
//===================
	// cg から移動。
	/* R20: 難易度レジスタ。 このレジスタは、難易度が入る。 */
	R20_PLAYER_DATA_game_difficulty,			//	s32 game_difficulty;			/* (pspのmax, min命令を使っているので signed int の必要がある ) */
	R21_PLAYER_DATA_game_score, 				//	u32 game_score; 				/* スコア得点 */
	R22_PLAYER_DATA_graze_point,				//	u32 graze_point;				/* グレイズ得点 */
	R23_PLAYER_DATA_bombs,						//	int bombs;						/* ボム数 */
	R24_PLAYER_DATA_zanki,						//	int zanki;						/* 残りチャンス */
	R25_PLAYER_DATA_game_rank,					//	s32 game_rank;					/* ランク変動システムのゲームランク */
	R26_PLAYER_DATA_jiki_weapon_level,			//	u32 jiki_weapon_level;			/* (r35u2)強さのみ */		//	/*u8*/u32 jiki_weapon_level_offset;/* 装備した武器レベル(番号)の８倍にプレイヤー値を足した値をオフセットとして保持 */
	R27_PLAYER_DATA_weapon_power,				//	int weapon_power;				/* 0x00-0x80  (0-128 の129段階==本家と同じ)   max==128==「129段階」*/
	R28_PLAYER_DATA_bomber_time,				//	s32 bomber_time;				/* Use Gu */  // /* bomb_wait */ /* ボムの有効時間 */
	R29_PLAYER_DATA_chain_point,				//	int chain_point;
	R2a_PLAYER_DATA_state_flag, 				//	u32 state_flag; 				/* 設定フラグ(集) */
	R2b_PLAYER_DATA_player_data_use_continue,	//	int player_data_use_continue;	/* コンティニュー回数 */
	R2c_PLAYER_DATA_player_data_count_misstake, //	int player_data_count_miss; 	/* ミス回数 */
	R2d_PLAYER_DATA_player_data_used_bomber,	//	int player_data_used_bomber;	/* ボム使用回数 */
	R2e_PLAYER_DATA_player_data_use_kurai_bomb, //	int player_data_use_kurai_bomb; /* 喰らいボム成功回数 */
	R2f_PLAYER_DATA_player_data_count_bonus,	//	int player_data_count_bonus;	/* カードボーナス回数 */
	// 集計システム(player_data)				//	/* 集計システム(player_data) */
	R30_BOSS_DATA_target_x256,					// ボス用。 /* 目標x座標 */
	R31_BOSS_DATA_target_y256,					// ボス用。 /* 目標y座標 */
	R32_BOSS_DATA_chuu_boss_mode,				// (中ボス用)。/ [remilia] 発弾数カウンタ。
	R33_BOSS_DATA_kougeki_anime_count,			// ボス用。 /* 攻撃アニメーション用カウンタ / 0以下なら移動アニメーション */
	R34_BOSS_DATA_toutatu_wariai256,			// ボス用。 /* 目標座標への到達割合 */
	R35_BOSS_DATA_move_jyumyou, 	// ボス用。 /* 制限時間 */	/* 制限時間(boss_move_timerと同じ) */
	R36_BOSS_DATA_sakuya_data_move_angle1024,	// ボス用。 /* 咲夜の角度 */
	R37_BOSS_DATA_sakuya_data_common_wait256,	// ボス用。 /* 咲夜の */
	R38_BOSS_DATA_angleCCW65536,				// ボス用。 (旧src->tm p_angleCCW65536)
	R39_BOSS_DATA_tukaima_type, 				// ボス用。使用する使い魔のタイプ。
	R3a_BOSS_DATA_center_x256,					// ボス用。obj 中心x座標(コピー)
	R3b_BOSS_DATA_center_y256,					// ボス用。obj 中心y座標(コピー)
	R3c_boss_clip_min_x256, 					// POINT256 boss_clip_min;	/* ボス移動範囲(最小値)横方向軸座標限界値 */
	R3d_boss_clip_min_y256, 					// POINT256 boss_clip_min;	/* ボス移動範囲(最小値)縦方向軸座標限界値 */
	R3e_boss_clip_max_x256, 					// POINT256 boss_clip_max;	/* ボス移動範囲(最大値)横方向軸座標限界値 */
	R3f_boss_clip_max_y256, 					// POINT256 boss_clip_max;	/* ボス移動範囲(最大値)縦方向軸座標限界値 */
	//
	REG_NUM_99_MAX// = 0x20/*(.align 32)*/
};
// ゼロページのサイズ
#define REG_NUM_0x1c_ZERO_PAGE_MAX (R1b_+1)

// 弾の範囲(alias)
#define VR1c_bullet_clip_min_x256		spell_register[R1c_bullet_clip_min_x256]
#define VR1d_bullet_clip_min_y256		spell_register[R1d_bullet_clip_min_y256]
#define VR1e_bullet_clip_max_x256		spell_register[R1e_bullet_clip_max_x256]
#define VR1f_bullet_clip_max_y256		spell_register[R1f_bullet_clip_max_y256]
// ボス移動範囲(alias)
#define VR3c_boss_clip_min_x256 		spell_register[R3c_boss_clip_min_x256]
#define VR3d_boss_clip_min_y256 		spell_register[R3d_boss_clip_min_y256]
#define VR3e_boss_clip_max_x256 		spell_register[R3e_boss_clip_max_x256]
#define VR3f_boss_clip_max_y256 		spell_register[R3f_boss_clip_max_y256]

//typedef struct /*_clip_class_*/
//{
//	POINT256 boss_clip_min; 	/* ボス移動範囲(最小値) */
//	POINT256 boss_clip_max; 	/* ボス移動範囲(最大値) */
//
//	POINT256 bullet_clip_min;	/* 弾の範囲(最小値) */
//	POINT256 bullet_clip_max;	/* 弾の範囲(最大値) */
//} RECT_CLIP_CLASS;
//extern RECT_CLIP_CLASS rect_clip;

/*---------------------------------------------------------
	システムレジスタ。規定範囲: R00 ... R07
	-------------------------------------------------------
	規定範囲: R00	使用禁止。0以外を書くとCPU命令自体が正常動作できません。(private)
	規定範囲: R01	CPUの内部動作用なので外部から使用禁止。(private)
	-------------------------------------------------------
	規定範囲: R02 ... R03	ループ変数用です。(public)
	-------------------------------------------------------
	規定範囲: R04 ... R07	受け渡し作業に使用します。(public)
---------------------------------------------------------*/

//#define MAX_FIX_VALUE (REG_NUM_01_FIX_VALUE+1)/*固定値の範囲*/
//カードスクリプト実行中には毎フレーム、ボスの現在座標が更新される。
/*static*/extern int spell_register[REG_NUM_99_MAX];

/* 実際のレジスタ */
// [system registers]システムレジスタ。
//0[固定]#define VR00	spell_register[R00]使用禁止。
// [未定]#define VR01	spell_register[R01]
#define VR02_j	spell_register[R02_j]
#define VR03_i	spell_register[R03_i]
// [delivery registers]受け渡しレジスタ。
#define VR04	spell_register[R04]
#define VR05	spell_register[R05]
#define VR06	spell_register[R06]
#define VR07	spell_register[R07]
//
//
/* 受け渡しレジスタの[alias]エイリアス[別名定義] */
#define VR04_NAN_IDO_DECODE 	VR04
#define VR04_temp				VR04

/*---------------------------------------------------------
	ワークレジスタ。規定範囲: R08 ... R0f
	-------------------------------------------------------
	スペカで使用するレジスタ。
---------------------------------------------------------*/
// [general registers]汎用レジスタ。(汎用==general purpose)
#define VR08	spell_register[R08]
#define VR09	spell_register[R09]
#define VR0a	spell_register[R0a]
#define VR0b	spell_register[R0b]
#define VR0c	spell_register[R0c]
#define VR0d	spell_register[R0d]
#define VR0e	spell_register[R0e]
#define VR0f	spell_register[R0f]
//
#if (1)/*(強引にスペカ化している為、連絡処理にレジスタが一つ要る)*/

// [alias]エイリアス[別名定義]
#define VR0f_SAKUYA_LINK		VR0f/*[咲夜:発弾連絡レジスタ]*/
//#define VR0f_AYA_LINK 		VR0f/*[文:発弾連絡レジスタ]*/
#define VR0f_AYA_LINK			VR09/*[文:発弾連絡レジスタ]*/
enum
{
	SAKUYA_LINK_00_DONE = (0),	/*(終わったよ)*/
	SAKUYA_LINK_01_RYOUTE_KNIFE,/*(attack type 1)*/
	SAKUYA_LINK_02_KURU_KURU,	/*(attack type 2)*/
};
enum
{
	AYA_LINK_00_NONE = (0), 	/*(なし)*/
	AYA_LINK_01_RENDAN, 		/*(attack type 1)*/
	AYA_LINK_02_FUDADAN,		/*(attack type 2)*/
	AYA_LINK_03_OODAMA, 		/*(attack type 3)*/
};
#define AYA_LINK_03_OODAMA_23	AYA_LINK_03_OODAMA
#define AYA_LINK_03_OODAMA_22	AYA_LINK_03_OODAMA
#define AYA_LINK_03_OODAMA_21	AYA_LINK_03_OODAMA

#endif

/*---------------------------------------------------------
	弾システム接続I/Oポート。規定範囲: R10 ... R17
---------------------------------------------------------*/
// [tama registers](発弾システム)
/*
	tama (teki-dan) == enemy bullets, japan language.
	shot (ji-dan)	== player bullets, japan language.
	when tama system, enemy bullets only.
*/
#define VR10	spell_register[R10] 	/* スペル経過時間 */
/*([tama_system に直接接続しているレジスタ])*/
#define VR11	spell_register[R11]
#define VR12	spell_register[R12]
#define VR13	spell_register[R13]
#define VR14	spell_register[R14]
#define VR15	spell_register[R15]
#define VR16	spell_register[R16]
#define VR17	spell_register[R17]
// [alias]エイリアス[別名定義]
#define VR10_BOSS_SPELL_TIMER	VR10	/* スペル経過時間 */

/*---------------------------------------------------------
	効果音システム接続I/Oポート。規定範囲: R18 ... R1f
---------------------------------------------------------*/

#define VR18	spell_register[R18]
#define VR19	spell_register[R19]

/*([audio_system に直接接続しているレジスタ])*/
#define AUDIO_18_voice_number	VR18/*(効果音の固有番号。音の種類)*/
#define AUDIO_19_voice_truck	VR19/*(再生トラック指定)*/


/*---------------------------------------------------------
	策定中レジスタ。	規定範囲: R20 ... R2f
	策定中レジスタ。	規定範囲: R30 ... R3f
	-------------------------------------------------------
	ボス共通規格レジスタ。
	自機状態レジスタ。
---------------------------------------------------------*/
enum
{
	chuu_boss_00_mode_off = (0),
	chuu_boss_01_mode_stay,
//	chuu_boss_02_mode_spell,/*(予定)*/
};
/* ボス共通規格 */
#define cg_BOSS_DATA_30_target_x256 					spell_register[R30_BOSS_DATA_target_x256]
#define cg_BOSS_DATA_31_target_y256 					spell_register[R31_BOSS_DATA_target_y256]
#define cg_BOSS_DATA_32_chuu_boss_mode					spell_register[R32_BOSS_DATA_chuu_boss_mode]
#define cg_BOSS_DATA_33_kougeki_anime_count 			spell_register[R33_BOSS_DATA_kougeki_anime_count]
#define cg_BOSS_DATA_34_toutatu_wariai256				spell_register[R34_BOSS_DATA_toutatu_wariai256]
#define cg_BOSS_DATA_35_move_jyumyou					spell_register[R35_BOSS_DATA_move_jyumyou]
// [alias]エイリアス[別名定義]
#define cg_BOSS_DATA_35_boss_base_state777				cg_BOSS_DATA_35_move_jyumyou
/*(咲夜)*/
#define cg_BOSS_DATA_36_sakuya_data_move_angle1024		spell_register[R36_BOSS_DATA_sakuya_data_move_angle1024]
#define cg_BOSS_DATA_37_sakuya_data_common_wait256		spell_register[R37_BOSS_DATA_sakuya_data_common_wait256]
//
#define cg_BOSS_DATA_38_angleCCW65536					spell_register[R38_BOSS_DATA_angleCCW65536]
//
#define cg_BOSS_DATA_3a_center_x256 					spell_register[R3a_BOSS_DATA_center_x256]
#define cg_BOSS_DATA_3b_center_y256 					spell_register[R3b_BOSS_DATA_center_y256]
//
#define cg_BOSS_DATA_39_tukaima_type					spell_register[R39_BOSS_DATA_tukaima_type]

//

#define cg_VR20_game_difficulty 						spell_register[R20_PLAYER_DATA_game_difficulty]
#define cg_game_score									spell_register[R21_PLAYER_DATA_game_score]
#define cg_graze_point									spell_register[R22_PLAYER_DATA_graze_point]
#define cg_bombs										spell_register[R23_PLAYER_DATA_bombs]
#define cg_zanki										spell_register[R24_PLAYER_DATA_zanki]
#define cg_game_rank									spell_register[R25_PLAYER_DATA_game_rank]
#define cg_jiki_weapon_level							spell_register[R26_PLAYER_DATA_jiki_weapon_level]
#define cg_weapon_power 								spell_register[R27_PLAYER_DATA_weapon_power]
#define cg_bomber_time									spell_register[R28_PLAYER_DATA_bomber_time]
#define cg_chain_point									spell_register[R29_PLAYER_DATA_chain_point]
//
#define cg_state_flag									spell_register[R2a_PLAYER_DATA_state_flag]
//
#define cg_player_data_use_continue 					spell_register[R2b_PLAYER_DATA_player_data_use_continue]
#define cg_player_data_count_miss						spell_register[R2c_PLAYER_DATA_player_data_count_misstake]
#define cg_player_data_used_bomber						spell_register[R2d_PLAYER_DATA_player_data_used_bomber]
#define cg_player_data_use_kurai_bomb					spell_register[R2e_PLAYER_DATA_player_data_use_kurai_bomb]
#define cg_player_data_count_bonus						spell_register[R2f_PLAYER_DATA_player_data_count_bonus]


/*---------------------------------------------------------
	ヘルパーマクロ。
	-------------------------------------------------------
---------------------------------------------------------*/

/*([無くても出来るけど]あった方が便利)*/
//#define USE_CPU_EXTRA (1)
#define USE_CPU_EXTRA (0)

/*(マイクロオペコードへ変換[コンパイル])*/
#define MCODE(reg_op,reg_v0,reg_ra,reg_rb) (((reg_op)&0xff)|(((reg_v0)&0xff)<<8)|(((reg_ra)&0xff)<<16)|(((reg_rb)&0xff)<<24))

#define NAX 	(0)/*[未定義値。このシステム上 0 固定]*/

enum
{
	LONG_MEMORY_ADDRESSING = (0),	/*(0==ロングアドレッシング)*/
//	NANIDO_REGISTER_ADDRESSING = (0),		/*(0==難易度レジスタアドレッシング)*/
	REGISTER_ADDRESSING = (0),		/*(0==レジスタアドレッシング)*/
	MEMORY_ADDRESSING,				/*(1==メモリアドレッシング)*/
	#if (1==USE_CPU_EXTRA)/*([無くても出来るけど]あった方が便利)*/
	CPU_QUIT = (0), 				/*(0==quit)*/
	#endif
	#if (1)/*(基本弾発生命令のアドレッシング)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE = (0),		/*(0 == 1弾打つ)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY,	/*(1 == 偏り n way 弾)*/
	HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, 			/*(2 == 方向 n way 弾[通常 n way 弾。通常 n way 弾は、「偏り n way 弾」を内部で2回よぶ事により生成する])*/
	#endif
};
#define LONG_ONLY	(LONG_MEMORY_ADDRESSING)/*(ロングメモリアドレッシング専用命令)*/


/*---------------------------------------------------------
	カード CPU マイクロコード
	-------------------------------------------------------
	この CPU の、1ワード(最小基本単位)は 32[bit]です。
	命令は 可変長 で、多くの命令は、1ワード命令ですが 2ワード命令もあります。
	テーブル命令は テーブルの長さワードあります。(nワード命令)
	1ワード目(32bit)は、レジスタ名Ｂ(u8) + レジスタ名Ａ(u8) + 即値(s8) + オペコード(u8) の構成で 32[bit]。
	2ワード目(32bit)を、オペランド(u32) の構成で 32[bit]。(2ワード目は、必須でなくて2ワード目がある命令は 1/3 ぐらいです)
	3ワード目(32bit)以降があるのはテーブル命令です。
	-------------------------------------------------------
	This CPU own basic wards as 32 bit.(say word == 32bit, word not 16bit, 'word' means 'long word' not short word.)
	The Opecode, valiable length. 1[word=32bit] or 2[word=32bit]==64bit.
	The table opecode 2 words.
	1 [word=32bit==4x8bytes]:
		MSB 4[byte]) name reg B (8[bit]==u8== 0 ... 255)
			3[byte]) name reg A (8[bit]==u8== 0 ... 255)
			2[byte]) immidiate value(8[bit]==s8 == -128 ... 127)
		LSB 1[byte]) opecode  (8[bit]==u8== 0 ... 255)
	2 [word=32bit]:
		(u32) valiable.(s32 valiable)
	3 ...  [word=32bit]:
		(u32) valiable.(s32 valiable)
	-------------------------------------------------------
	レジスタ名が(8bit)なので、この CPU の最大保持レジスタは 256レジスタ。
	この 256レジスタは総て計算で使える訳ではなく、I/Oポート機能(ゲームの全機能が操れる)が 全体の 3/4 ぐらいある為、実質 最大64レジスタぐらい。
	とりあえず[r40]現時点の最大レジスタは レジスタ(12) +I/Oポート(8)で済んでいる。
	-------------------------------------------------------
----:	未定義
OPxx:	マイクロオペコード (L--- ---- L: 0:ショートアドレッシング(32bit), 1:ロングアドレッシング(32bit x 2) )
RA--:	レジスタ名Ａ
RB--:	レジスタ名Ｂ
VAL0:	ショート値 (0 ... 255)
JR++:	マイクロコードひとつ分ジャンプ(1命令分飛ばす)
[M+]:	マイクロコードの次位置のメモリから読む。
L32:	u32 定数。 (32bit)
	-------------------------------------------------------
※	ブランチ(ジャンプ)系命令は、相対ブランチ PC+(s8)VAL; しか要らない。
※	弾の移動処理を新しく定義する場合。ロングアドレスが要るが直接使わない。
※	コードを 共有RAM にコピーして動く構造にすると、弾の移動処理の場合に困らない？
	共有RAMに メインプロセスをコピーして動くけど、弾の移動処理の場合、
	動的にアドレス割付して、弾のプロセスをコピーして動く。
	だったら、初期化セクションで使用弾のプロセスをコピーしておいた方が効率よい。
---------------------------------------------------------*/
#define USE_CPU_BHI_BPL (0)
enum
{
	// コード番号					// 意味 						内部format(32bit)					命令長		動作									PC++;	PC++;	//	対応するC言語版の名称
	// (基本命令)--------
	OP0x00_EXIT = 0,				// スペル終了。 				----, ----, ----, OPxx				(1) 		今回のフレーム終了。					PC++;	PC++;	//	なし。(return;)
	OP0x01_MOVER_PD,				// レジスタ間転送。 			RB--, RA--, VAL0, OPxx				(1) 		RA = (RB) + VAL0;						PC++;	PC++;	//	CPU_CALL(MOVER_PD_NUM);
	OP0x02_COUNTER, 				// カウンター。 				----, RA--, VAL0, OPxx				(1) 		RA++;if (RA > (s32)VAL0) {RA=0;}		PC++;	PC++;	//	CPU_CALL(count_up_limit_NUM);
	OP0x03_NAN_IDO, 				// 難易度をデコードする。		0x00, RA--, ----, OPxx	data32		(2) 		PC++;	R9 = decode[data32];					PC++;	//	CPU_CALL(nan_ido);
	OP0x04_ADDR_PD, 				// レジスタ間 加算(減算)。		RB--, RA--, VAL0, OPxx				(1) 		RA = (RA + RB) + VAL0;					PC++;	PC++;	//	CPU_CALL(ADDR_PD_NUM);
	OP0x05_SUBR_PD, 				// 符号反転/減算
	OP0x06_BRAR_NN, 				// 無条件分岐(レジスタ値)		----, RA--, ----, OPxx				(1) 							PC += RA;							//	なし。	// (この命令は必要) ジャンプテーブル[補助]命令
	/*[未使用r42]*/OP0x07_REGIST_PROCESS,// プロセス登録(この命令はいずれ必要)
	//--------
	// (ブランチ系命令)--------
	OP0x08_BNE_RS,					// 値が違えば分岐				IRB-, RA--, VAL0, OPxx				(1) 		if (VAL0 != RA) 	{PC += IRB;} else {PC++;}			//	なし。	// (この命令は必要)
	OP0x09_BFL_RS,					// 値が未満なら分岐 			IRB-, RA--, VAL0, OPxx				(1) 		if (VAL0 < RA)		{PC += IRB;} else {PC++;}			//	なし。	// (この命令は必要)
	OP0x0a_BRA_TABLE,				// 配列 						IRB-, RA--, VAL0, OPxx				(1) 		RA = PC+1[VAL0];	PC += IRB;							//	なし。	// (この命令は必要)
	OP0x0b_BRA_RS,					// 無条件分岐(即値) 			IRB-, ----, ----, OPxx				(1) 							PC += IRB;							//	なし。	// (この命令は必要)
	// (基本弾発生命令)-------- (そもそも発弾システム側で纏めた方が良いかも)
	OP0x0c_hatudan_system_regist_tama,			// 基本弾発生命令。(single, n_way, katayori_n_way)
	OP0x0d_AUDIO_VOICE_PLAY,
	OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18,
	OP0x0f_CLEAR_ZERO_PAGE, 		/* (r35)カードスクリプト用命令(カードレジスタ全初期化) */
	//	(サポート命令)--------
	OP0x10_SINCOS256,				// サイン & コサイン。			----, ----, ----, OPxx				(1) 		sin();cos();							PC++;	PC++;	//	CPU_CALL(sincos256);
	OP0x11_BOSS_TO_JIKI_NERAI,		// ボスから自機狙い。
	OP0x12_JIKI_NERAI,				// 自機狙い角作成。 			----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(calculate_jiki_nerai);
	OP0x13_HANYOU_NERAI,			// 汎用目標狙い角作成。 		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(atan_65536);
	OP0x14_MULTIPREX_RATE_VECTOR,	// 複合割合合成。				----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(multiprex_rate_vector);
	OP0x15_RAND_VALUE,				// リプレイ対応乱数生成。		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(replay_rand_init);
	OP0x16_RAND_INIT,				// リプレイ対応乱数生成。		----, ----, ----, OPxx				(1) 												PC++;	PC++;	//	CPU_CALL(replay_rand);
	OP0x17_DIV65536,				// 割り算命令。65535 / n		RB--, RA--, ----, OPxx				(1) 		R6 = 65536 / R5;						PC++;	PC++;	//	CPU_CALL(div65536); ([予定] RA = 65536 / RB;)
	//--------
	// (拡張命令[CPU外部コード(命令)])-------- メモリロングショートアドレッシング。
	/*[未使用r42]*/OP0x18_,
	/*[未使用r42]*/OP0x19_,
	/*[未使用r42]*/OP0x1a_,
	OP0x1b_ADDM_LONG_PD,			// u32固定値 加算(減算) 		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA +=	([data32] + VAL0);				PC++;	//	なし。
	//
	OP0x1c_MOVEM_PD,				// u32固定値 即値代入。 		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA =	([data32] + VAL0);				PC++;	//	なし。
	OP0x1d_ANDM_PD, 				// u32固定値 AND演算			0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA &=	([data32] + VAL0);				PC++;	//	なし。
	OP0x1e_ASRM_PD, 				// u32固定値 算術右シフト		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA >>=	([data32] + VAL0);				PC++;	//	なし。(註3:)
	OP0x1f_ASLM_PD, 				// u32固定値 算術左シフト		0x00, RA--, ----, OPxx	data32		(1 or 2)	PC++;	RA <<=	([data32] + VAL0);				PC++;	//	なし。
	//--------
	OP0x99_MAX,/*[CPU外部命令の最大数]*/
};
	#if 0/*(メモ)*/
	(註3:)
	算術シフトなので最上位bitが 1 の場合、論理シフトと結果が違う。
	ショートアドレッシングの場合は 最上位bitは 8 で、
	ロングアドレッシングの場合は 最上位bitは 32 と動作も異なる。
	#endif

	//	/*[未使用r42]*/OP0x0d_SUBM_PD,/*てすと*/
	//--------
//	OP0x1a_/*ANDR_PD*/, 			//[未使用] レジスタ間 AND演算。 		RB--, RA--, VAL0, OPxx	dummy32 	(1) 	RA = (RA & RB) + VAL0;					PC++;	PC++;	//	CPU_CALL(ANDR_PD_NUM);
// u32固定値 即値代入。 		----, ----, VAL0, OPxx	data32		(2) 	[VAL0]PC = [data32];					PC++;

//#define OP0x05_NEGR_PD OP0x05_SUBR_PD

// (だめ)/#define MCODE_OP0x05_NEGR_PD(arg_v0, arg_rb) MCODE(OP0x05_SUBR_PD, arg_v0, R00, arg_rb)

	#if 0/*(まだ考えるの早い(?))*/
//	OP0x08_BEQR,					// u8相対	ジャンプ			RB--, RA--, VAL0, OPxx	dummy32 	(1) 	if (RA==RB) goto PC+(s32)VAL0;			PC++;	PC++;	//	なし。 Branch relative Jump, if Equal. for register.
//	OP0x08_BEQS,					// u8相対	ジャンプ			VAL2, RA--, VAL0, OPxx	dummy32 	(1) 	if (RA==(s32)VAL2) goto PC+(s32)VAL0;	PC++;	PC++;	//	なし。 Branch relative Jump, if Equal. for short index.
//	BEQ BNE BLS BHI ...
	#endif


/*
OP0x16_div65536の案

	OP16, ----, RA--, RB--
	RB = 65536 / RA;


ToDo:
	メモリ書き換え命令
*/

extern void cpu_exec(u32 *codebase, s32 icount);

/*(CARD CPU 内部命令)*/
extern CPU_FUNC(sincos256);

#endif /* _CARD_CPU_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _HATSUDAN_SYSTEM_H_
#define _HATSUDAN_SYSTEM_H_
/*---------------------------------------------------------
	発弾システム
	-------------------------------------------------------
	どんな弾でも発弾する場合は必ず「発弾システム」を通らなければならない。
	これは、一ヶ所に無いと極端に速度低下するのが主な理由。
	-------------------------------------------------------
	発弾システムは主に発弾エフェクトの指定をするが、
	発弾エフェクトの無い弾でも当然発弾システムを通らなければならない。
	-------------------------------------------------------
	発弾エフェクトは現状発弾システムが担当しているが、
	将来的にもっと効率的な別システムになる。
	「弾幕」に特化して「弾(個弾)」の(移動)処理が出来なくなる。
	これは「弾幕」シューティングの場合、個弾の移動処理は必要無い為、
	個弾の移動処理は無い。あると遅い。
---------------------------------------------------------*/

/*---------------------------------------------------------
	発弾単位の受け渡し設定(角度弾の場合)
	-------------------------------------------------------
	角度弾の分解能は65536度に決定。
	-------------------------------------------------------
	将来カードスクリプトシステムに移行した場合、
	この構造体は、カードスクリプト用のレジスタ(ローカルメモリー)に
	移動する。(でないとカードスクリプト上から弾をどうこうできないので)
---------------------------------------------------------*/

#if 1

	/*([tama_system に直接接続しているレジスタ])*/
	// 以下は、 弾の設定。
	#define HATSUDAN_R11_speed256			VR11 /* 速度 */
	#define HATSUDAN_R12_speed_offset		VR12 /* 加速度 */
	#define HATSUDAN_R13_angle65536 		VR13 /* 角度 */ 				/* <分解能65536度に決定> */
	#define HATSUDAN_R14_tama_spec			VR14 /* 弾の能力属性 */
	#define HATSUDAN_R15_bullet_obj_type	VR15 /* 弾グラフィックの種類 */
	// 以下は、 n_way弾の場合に必要な要素。
	#define HATSUDAN_R16_n_way				VR16 /* n way 弾の弾数 */
	#define HATSUDAN_R17_div_angle65536 	VR17 /* n way 弾の分割角度 */	/* <分解能65536度に決定> */
	// 別名定義。(alias)
	/* 同じ物だけど、 65536分割なのか 1024 分割なのか明示する為に必要。 */
	//[廃止済みr42]#define HATSUDAN_R13_angle1024			VR13	/* 描画用角度 */	/* <描画用の分解能1024度に落としてある事を明示する。> */
	/* 同じ物だけど、  。 */
	#define REG_11_GOUSEI_WARIAI256 		VR11
#endif

#if 1
	/*([tukaima_system に直接接続しているレジスタ])*/
	/*
		使い魔に関しては、直接スクリプトからコントロールできないと話にならないので、
		直接接続しているレジスタがある。
	*/
#endif

#if 1
	/*([audio_systemに直接接続しているレジスタ])*/
	/*
		効果音、BGMもレジスタ経由でないとスクリプト化出来ない。
	*/
#endif

/*---------------------------------------------------------
	登録種類
---------------------------------------------------------*/

//extern void hatudan_system_regist_single(void);			/* 単発 */
//extern void hatudan_system_regist_katayori_n_way(void);	/* 偏り n way弾 */
//extern void hatudan_system_regist_n_way(void);				/* 通常 n way弾 */
extern void hatudan_system_regist_tama(int set_addressing);

/*---------------------------------------------------------
	発弾登録規格
---------------------------------------------------------*/
	#define TR00_hatudan_spec_data				system_data00	/* 画面外消去判定や反射機能 */
	//
	#define TR01_hatudan_speed65536 			user_data00 	/* 加減速 */
	#define TR02_hatudan_tra65536				user_data01 	/* 加減速調整 */
	#define TR03_hatudan_frame_counter			user_data02 	/* 発弾フレームカウンタ(正値で発弾) */
	//
//	#define hatudan_system_bbb					user_data04 	/* 拡張予定(?) (r33現在未使用) / */
//	#define hatudan_system_ccc					user_data05 	/* 拡張予定(?) (r33現在未使用) / */

/*---------------------------------------------------------
	弾スペック
	弾の能力、状態をあらわす。
	描画する場合のグラフィック、傾き弾。非傾き弾。の区別。
	弾幕システムのどのレイヤーに所属する弾かの区別。
---------------------------------------------------------*/

#if 1
	#define TAMA_SPEC_0000_TILT 				(0x0000)/* 傾き弾(通常弾) */
	#define TAMA_SPEC_8000_NON_TILT 			(0x8000)/* 非傾き弾 */		/* 傾かない弾(大玉弾、チルノ弾、等用) */
	#define TAMA_SPEC_4000_GRAZE				(0x4000)/* グレイズ済みかとうかのフラグ */
	#define TAMA_SPEC_3000_EFFECT_MASK			(0x3000)/* エフェクト選択 */
	#define TAMA_SPEC_3000_EFFECT_NONE			(0x3000)/* エフェクトなし */
	#define TAMA_SPEC_2000_EFFECT_MINI			(0x2000)/* エフェクト小 */
	#define TAMA_SPEC_1000_EFFECT_MIDDLE		(0x1000)/* エフェクト中 */
	#define TAMA_SPEC_0000_EFFECT_LARGE 		(0x0000)/* エフェクト大(旧r34互換) */
#endif
	/*(CCW)*/
	#define TAMA_SPEC_0x0100_CCW_BIT 			(0x0100)
	/*(咲夜チルノ左右の壁で1度だけ反射)*/
	#define TAMA_SPEC_KABE_SAYUU_HANSYA_BIT 	(TAMA_SPEC_0x0100_CCW_BIT)
	/*(美鈴の曲がるクナイ連弾、回転方向フラグ)*/
	/*(パチェのマキュリーポイズン、回転方向フラグ)*/
	/*(レミリア、呪詛「ブラド・ツェペシュの呪い」、回転方向フラグ)*/
	/*(ルーミア、闇符「ディマーケイション」、回転方向フラグ)*/
	#define TAMA_SPEC_KAITEN_HOUKOU_BIT 		(TAMA_SPEC_0x0100_CCW_BIT)
//	#define TAMA_SPEC_KAITEN_HOUKOU_0x0000_CW	(0x0000)
//	#define TAMA_SPEC_KAITEN_HOUKOU_0x1000_CCW	(TAMA_SPEC_0x0100_CCW_BIT)

#endif /* _HATSUDAN_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*---------------------------------------------------------
	レーザーシステム
---------------------------------------------------------*/

#ifndef _LASER_SYSTEM_H_
#define _LASER_SYSTEM_H_

/*
	パチェ「通常攻撃」
	フラン禁忌「レーヴァテイン」
	フラン禁弾「過去を刻む時計」
	これらのカードを作るかどうかは別問題として、これらのレーザー弾に
	システムで対応できるように設計しとく必要がある。
*/
enum
{
	LASER_TYPE_00_OFF		= 0, // LASER_TYPE_00_1_PACHE	= 0,	// 0==off, lz[0]==offの場合、特殊機能で全部off。
	LASER_TYPE_01_4_PACHE,	/* 4本、外側タイプ(パチェ「通常攻撃」用) */
	LASER_TYPE_02_1_FRAN,	/* 1本、タイプ	  (フラン禁忌「レーヴァテイン」用) */
	LASER_TYPE_03_4_FRAN,	/* 4本、内側タイプ(フラン禁弾「過去を刻む時計」用) */
	MAX_99_LASER_TYPE
};
enum
{
	LASER_00_ = 0,
	LASER_01_,
	MAX_99_LASER
	/*	2弾？==禁忌「レーヴァテイン」(「始め」と「最後か真中あたり」のみ判定があれば、残像全部に判定がなくても大して変わらない気がする)
		8弾？==禁忌「レーヴァテイン」
		最後でなくて、真中あたりにするのは難易度を調整する為。(最後の方が若干難しい)
		物が剣なので、実際は「ぎりぎりで当たってる」のだけど、その場合あたってない事にした方が「ぎりぎりで当たらなかった」という奴。
		２本要る理由は、高速移動キャラで、1本目ですり抜けても、２本目に当たる。
	 */
};
typedef struct _laser_
{
	int laser_type; 		/* レーザーの種類 / 又はoff指定. LASER_TYPE */
	int laser_angle65536;	/* レーザーの角度 */
} LASER;
extern LASER lz[MAX_99_LASER];
/* lz[0]==0;の場合、すべてoff。(レーザーモード 0:off, 1:on) */

#endif /* _LASER_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _SPELL_SYSTEM_H_
#define _SPELL_SYSTEM_H_
/*
	スペルシステム==カードの管理システム。(カードシステムとは違うので注意)
*/

/*---------------------------------------------------------
	スペル生成システム(カードを生成)
---------------------------------------------------------*/

	/* 弾源x256 弾源y256 ボス中心から発弾。 */
//#define set_REG_DEST_XY(aaa) {REG_02_SEND1_BOSS_X_LOCATE = (aaa->center.x256);	REG_03_SEND1_BOSS_Y_LOCATE = (aaa->center.y256); }
extern void set_REG_DEST_BOSS_XY(void);
extern OBJ_CALL_FUNC(set_REG_DEST_XY);
#if 0/*あとで有効にする*/
extern OBJ_CALL_FUNC(card_maikai_init);
extern OBJ_CALL_FUNC(card_generate);
#endif

/* HATSUDAN_R13_angle65536 に 自機狙い弾の角度を計算 */
extern CPU_FUNC(cpu_VR_angleCCW65536_src_nerai);

/* HATSUDAN_R13_angle65536 に 自機狙い弾の角度を計算 */
extern CPU_FUNC(calculate_boss_to_jiki_nerai);
extern CPU_FUNC(calculate_jiki_nerai);

/*---------------------------------------------------------
	(r36)カードスクリプト用命令(multiprex_rate_vector)
	複合割合合成。
---------------------------------------------------------*/
extern CPU_FUNC(multiprex_rate_vector);

/* スペルをCPU実行し、カードを１フレーム生成する。 */
extern OBJ_CALL_FUNC(card_generate);

#endif /* _SPELL_SYSTEM_H_ */

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#ifndef _CARD_SYSTEM_H_
#define _CARD_SYSTEM_H_

//------------ カード関連

extern void create_card(OBJ/**/ *src, int card_number);

//extern OBJ_CALL_FUNC(ch eck_regist_card);/* カードの更新チェック */
extern OBJ_CALL_FUNC(card_boss_move_generate_check_regist); /* カード登録可能なら登録 / カード生成 */

// extern OBJ_CALL_FUNC(card_state_check_holding);/* カードが終わるまで待つ。 */

enum
{
	DANMAKU_LAYER_00 = 0,	// (0)/* 弾幕コントロールしない通常弾(画面外で弾消し) */
	DANMAKU_LAYER_01,		// (1)/* 弾幕コントロールグループ(1)弾 */
	DANMAKU_LAYER_02,		// (2)/* 弾幕コントロールグループ(2)弾 */
	DANMAKU_LAYER_03,		// (3)/* 弾幕コントロールグループ(3)弾 */
	DANMAKU_LAYER_04_MAX/* 弾幕コントロールグループ最大数 */
};

typedef struct /*_card_global_class_*/
{
	void (*boss_spell_callback)(OBJ/**/ *sss);				/* ボスspell system内「発弾処理」処理(実行言語(カードインタプリタ / C言語)が別れるので一時的に要る。C言語を全て廃止できれば、不要になる) */
//	void (*boss_move_card_callback)(OBJ/**/ *sss);			/* ボスcard内「移動」処理(-r40) */
	void (*boss_move_card_callback_void)(void); 			/* ボスcard内「移動」処理(r41-) */
	int limit_health;		/* 規定値以下になれば カードモード解除 */
	int card_timer; 		/* [共用]スペカの制限時間 */
	//
	int address_set;		/* [共用]カードアドレス番号 */
	int address_temporaly;	/* [一時使用]カードアドレス番号 */
	int spell_used_number;	/* [使用中のスペル番号] */
	int boss_hp_dec_by_frame;/* ボス攻撃減少値、フレーム単位 */
	//
	void (*layer_callback[(DANMAKU_LAYER_04_MAX)])(OBJ/**/ *sss); /* 弾幕レイヤー、コールバックシステム(スペル変身処理) */
	int tukaima_used_type;/*(使い魔システム、使う種類)*/
//	int tukaima_now_counts;/*(使い魔システム、)*/
//	int tukaima_add_interval;/*(使い魔システム)*/

} CARD_SYSTEM_GLOBAL_CLASS;
extern CARD_SYSTEM_GLOBAL_CLASS card;
//	/* 負値になればボスがカードモードに入らない */
//	void (*boss_sel ect_action_callback)(OBJ/**/ *sss); 	/* ボスcard内「行動選択」処理 */

/* とりあえず */

//------------ "回"みたいなマークのエフェクト
/* 「"回"みたいなマーク」は、ボスが持ってるカードだそうです。 */
/*static*/extern OBJ_CALL_FUNC(move_card_square_effect);
/*static*/extern void boss_effect_kotei_obj_r36_taihi(void);

extern void game_core_danmaku_system_callback(void);
#endif /* _CARD_SYSTEM_H_ */
