

//#include "game_main.h"


extern OBJ_CALL_FUNC(chuu_boss_zako_anime_type05)
{
	zako_anime_type05(src);/* アニメーション */
}


/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/
#define GAME_COMMAND_OBJ_CALL_PRIVATE(nnn)	game_command_##nnn(gcmd, gcmd_obj_2nd)

extern void callback_hit_chuu_boss(OBJ/**/ *src, OBJ/**/ *tama);
extern OBJ_CALL_FUNC(move_chuu_boss);


/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/
extern GAME_COMMAND_FUNC(01_regist_chuu_boss)/* [中型敵]中ボス、生成処理 */
{
	//hold_game_mode_on();
	/*(既に実行中の場合戻る。２重登録しない。中ボスはボスの領域を使用しているので、
	ボスの領域が一つしかないから２つ同時には出せない。)*/
	if (chuu_boss_00_mode_off != cg_BOSS_DATA_32_chuu_boss_mode)	{return;}/*(中ボス実行中なので登録できない)*/
	//-----------------
	/* プライオリティー(表示優先順位)があるから、背後に表示させる為に、初めに後ろの魔方陣を確保。 */
	OBJ *gcmd_obj_3rd;		/* 背後の魔方陣 */
	gcmd_obj_3rd	= obj_regist_teki();
	if (NULL == gcmd_obj_3rd)	{return;}/*(obj overで背後の魔方陣が登録できない)*/
	//-----------------
	/* 後ろの魔方陣が確保出来たら本体を確保。 */
	OBJ *gcmd_obj_2nd;	/* 本体 */
	gcmd_obj_2nd	= obj_regist_teki();
	if (NULL == gcmd_obj_2nd)/* 本体(gcmd_obj_2nd)が登録できなかった場合、登録できなかった場合 */
	{
		gcmd_obj_3rd->jyumyou	= JYUMYOU_NASI;/* 背後の魔方陣(gcmd_obj_3rd)の登録もあきらめる。 */
		return;/*(obj overで本体が登録できない)*/
	}
	//-----------------
	/* 中ボスが正常に登録できた場合のみ、中ボス実行中にする。 */
	cg_BOSS_DATA_32_chuu_boss_mode = (chuu_boss_01_mode_stay);/*(実行中)*/
	//-----------------
	{
		/* 0ttd dddd
			'0': force only zero.
			't': yokai type. (0-3)
			'd': dan maku type. (0-31)
		*/
		u32 my_haikei_iro;
	//	my_haikei_iro = (((gcmd->user_255_code)>>5)&(4-1));
		my_haikei_iro = (((gcmd->user_255_code)   )&(4-1));
	//
		/* 魔方陣生成 */
		gcmd_obj_3rd->m_Hit256R 			= ZAKO_ATARI02_PNG;
		gcmd_obj_3rd->obj_type_set			= ZAKO_28_MAHOJIN;
		gcmd_obj_3rd->atari_hantei			= (1/*スコア兼用*/);
		{
			const u32 color_table[4] =
			{	/*	gcmd_obj_3rd->alpha 		= 0x00;*/
				MAKE32RGBA(0xff, 0xff, 0xff, 0x7f), 	/* 灰っぽく */
				MAKE32RGBA(0xff, 0x3f, 0x3f, 0x7f), 	/* 赤っぽく */
				MAKE32RGBA(0x3f, 0x00, 0xff, 0x7f), 	/* 青っぽく */
				MAKE32RGBA(0x5f, 0xff, 0xaf, 0x7f), 	/* 紫っぽく(水色になった) */
			};
			gcmd_obj_3rd->color32				= color_table[my_haikei_iro];
		}
	//
		gcmd_obj_2nd->callback_mover			= move_chuu_boss;
	//
		GAME_COMMAND_OBJ_CALL_PRIVATE(regist_settei_common);/* 中ボスと共用する必要がある。 */
		//	gcmd_obj_2nd->type		 /* 設定ファイルから決める */
		/* easyでも存在感を印象づける為に 200 は必要 */ 	// 50+150*di fficulty;
	//	gcmd_obj_2nd->atari_hantei				= (1/*スコア兼用*/);
	//	gcmd_obj_2nd->m_Hit256R 				= ZAKO_ATARI16_PNG;
	//	gcmd_obj_2nd->ba se_hp					= ((l->us er_h p));		/* 設定ファイルから体力を決める。 */
	//	gcmd_obj_2nd->ba se_score				= ((l->us er_sco re));	/* 設定ファイルから獲得スコアを決める。 */
		//
	//	gcmd_obj_2nd->cen ter.x256				= ((l->us er_loc ate_x)<<(8));
	//	gcmd_obj_2nd->cen ter.y256				= ((l->us er_loc ate_y)<<(8));
		/*(
		(r41-)のシステムではスペカはスペカCPUでしか実行できなくなったので、従来の方式では中ボスはスペカを撃てない。
		一時的な互換対策として、中ボスとボスは同時に出てこないので、中ボスはスペカを撃つ為に、ボスの場所を間借りする。
		一時的にボスの座標を書き換える
		)*/
		#if 1
		/*(登場予定座標)*/
	//	VR06	= /*(スペカCPU外部座標[中ボス用])*/gcmd_o bj_2nd->cen ter.x256;
	//	VR07	= /*(スペカCPU外部座標[中ボス用])*/((gcmd->us er_loc ate_y)<<(8));/* t256(50.0) */		/* (中ボス用、特殊修正) */		// 中ボスの場合、y座標は登場予定座標。
		game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel単位] 設定ファイルから 出現(x, y)座標 を(VR06, VR07)に設定する。 */
		/*(現在座標)*/
		cg_BOSS_DATA_3a_center_x256/*(スペカCPU内部座標[ボス用])*/ = t256(300.0);/*(スペカCPU外部座標[中ボス用])*/
		cg_BOSS_DATA_3b_center_y256/*(スペカCPU内部座標[ボス用])*/ = t256(-30.0);/*(スペカCPU外部座標[中ボス用])*/	/* (中ボス用、特殊修正) */
		/* (背後の魔方陣座標) */ /* (中ボス座標) */
		gcmd_obj_3rd->center.x256				=	gcmd_obj_2nd->center.x256				= cg_BOSS_DATA_3a_center_x256;
		gcmd_obj_3rd->center.y256				=	gcmd_obj_2nd->center.y256				= cg_BOSS_DATA_3b_center_y256;
		boss_set_new_position_void();
		#endif
		//
		gcmd_obj_2nd->callback_hit_teki 		= callback_hit_chuu_boss;	/* コールバック登録 */
	//
		gcmd_obj_2nd->YOKAI1_DATA_s2			= gcmd_obj_3rd;
		#if 1
		//------------ カード関連
		card.spell_used_number		= (SPELL_00);/*(カード実行停止にする)*/
		card.address_temporaly		= ((gcmd->user_kougeki_type)&0x3f);
		gcmd_obj_2nd->jyumyou		= (CHUU_BOSS_JIKAN_04_2048-1);/* 「上から登場」へ設定。 */
		#endif
	}
}
/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

extern GAME_COMMAND_FUNC(02_move_chuu_boss)/* [中型敵]中ボス移動コマンド。(r41-) */
{
	if (chuu_boss_00_mode_off == cg_BOSS_DATA_32_chuu_boss_mode) 	{return;}/*(中ボス実行中以外は何もしない)*/
	//
//	GAME_COMMAND_OBJ_CALL_PRIVATE(regist_settei_common);/* 中ボスと共用する必要がある。 */
	#if 1
	/*(登場予定座標)*/
	game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel単位] 設定ファイルから 出現(x, y)座標 を(VR06, VR07)に設定する。 */
//	VR06	= /*(スペカCPU外部座標[中ボス用])*/((gcmd->us er_loc ate_x)<<(8));
//	VR07	= /*(スペカCPU外部座標[中ボス用])*/((gcmd->us er_loc ate_y)<<(8));	// 中ボスの場合、y座標は登場予定座標。
	/*(現在座標)*/
//	cg_BOSS_DATA_3a_center_x256/*(スペカCPU内部座標[ボス用])*/ = t256(300.0);/*(スペカCPU外部座標[中ボス用])*/
//	cg_BOSS_DATA_3b_center_y256/*(スペカCPU内部座標[ボス用])*/ = t256(-30.0);/*(スペカCPU外部座標[中ボス用])*/	/* (中ボス用、特殊修正) */
	/* (背後の魔方陣座標) */ /* (中ボス座標) */
	boss_set_new_position_void();
	#endif
}

//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	道中のボス
---------------------------------------------------------*/
/* from game_core.c */
//extern OBJ_CALL_FUNC(common_bo ss_put_items);
extern GAME_COMMAND_FUNC(06_kaiwa_start_boss)
{
	//----[BOSS]
	OBJ *gcmd_obj;
	gcmd_obj				= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(ボス本体)*/
	GAME_COMMAND_OBJ_CALL(regist_settei_common);/* 中ボス/(boss)と共用する必要がある。(gcmd_obj->callback_loserが設定される) */
//[強制共通]	/*(再定義の必要あり)*/	gcmd_obj->callback_loser				= common_bo ss_put_items;
	NEXT_SCENE;/*(次の場面へ設定)*/
}
