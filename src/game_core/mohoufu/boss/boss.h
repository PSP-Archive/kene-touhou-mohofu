
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
---------------------------------------------------------*/

#ifndef _BOSS_H_
#define _BOSS_H_

#include "game_main.h"
#include "card_address.h"
#include "./../tama/spell_name.h"
//------------ カード関連
//[重複]#include "boss.h"//#include "card_address.h"
//[重複]#include "boss.h"//#include "./../tama/spell_name.h"
//[重複]#include "./../boss/card_address.h"//#include "spell_address.h"
//[重複]#include "spell_name.h"

/*---------------------------------------------------------
	カード設定。
---------------------------------------------------------*/

/* 目標を設定し、誘導移動 */
extern void boss_set_new_position_void(void);			/*(誘導移動座標を設定)*/
extern void boss_set_new_position_from_target(void);	/*(誘導移動座標をターゲットから設定)*/



extern OBJ_CALL_FUNC(add_zako_sakuya_doll_02_tama_oki);/* 珠置きカード */


/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_01_laser);/* レーザー */

/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_03_star);/* 子供魔方陣(星型を描く) */
/*static*/extern OBJ_CALL_FUNC(add_zako_sakuya_doll_04_360knife);/* 子供魔方陣(360ナイフを撃つ) */
#endif /* _BOSS_H_ */

#ifndef _TUKAIMA_SYSTEM_H_
#define _TUKAIMA_SYSTEM_H_
extern OBJ_CALL_FUNC(tukaima_system_add_dolls);/*(使い魔システム)*/
//
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T01);
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T02);
extern OBJ_CALL_FUNC(init_set_dolls_kaguya_T03);
extern OBJ_CALL_FUNC(init_set_dolls_mima_T04);
extern OBJ_CALL_FUNC(init_set_dolls_sakuya_T05);	/* 咲夜 ばら撒き2弾 オプション */
extern OBJ_CALL_FUNC(init_set_dolls_sakuya_T06);	/* 咲夜 ばら撒き1弾 オプション */
extern OBJ_CALL_FUNC(init_set_dolls_alice_T07); 	/*(通常弾)*/

enum
{
	/*00*/	TUKAIMA_00_OFF = 0,
	/*0a*/	TUKAIMA_01_,/*([未使用])*/
	/*0b*/	TUKAIMA_02_,/*([未使用])*/
	/*0c*/	TUKAIMA_03_,/*([未使用])*/
			//
	/*05*/	TUKAIMA_04_sakuya_T04, /*(sakuya)*/
	/*06*/	TUKAIMA_05_sakuya_T05, /*(sakuya)*/
	/*08*/	TUKAIMA_06_aya_T06, /*(aya)*/
	/*0d*/	TUKAIMA_07_,/*([未使用])*/
			//
	/*01*/	TUKAIMA_08_kaguya_T08, /*(kaguya)*/
	/*02*/	TUKAIMA_09_kaguya_T09, /*(kaguya)*/
	/*0e*/	TUKAIMA_0a_kaguya_sitakara_type04_hiroi,/*(kaguya)*/
	/*0f*/	TUKAIMA_0b_kaguya_sitakara_type05_hiroi,/*(kaguya)*/
			//
	/*03*/	TUKAIMA_0c_kaguya_sitakara_type06, /*(kaguya)*/
	/*09*/	TUKAIMA_0d_kaguya_uekara, /*(kaguya)*/
	/*04*/	TUKAIMA_0e_mima_T0e, /*(mima)*/
	/*07*/	TUKAIMA_0f_alice_T0f, /*(alice通常弾)*/
	//
	TUKAIMA_10_MAX/*(最大数)*/
};
#if 1
/* [使い魔共通規格] */
/*[使用中]*/#define TUKAIMA_KIKAKU_00_target_x256					user_data00 	/* 目標x座標 */
/*[使用中]*/#define TUKAIMA_KIKAKU_01_target_y256					user_data01 	/* 目標y座標 */
//

//
// 未使用。 #define BOSS_tuk aima_DATA_03_kougeki_anime_count			user_data03 	/* 攻撃アニメーション用カウンタ / 0以下なら移動アニメーション */
//
//
//廃止	#define bo ss_spell_timer		user_data04 	/* スペル経過時間 */
// VR10_BOSS_SPELL_TIMER へ移行。
#endif

#endif /* _TUKAIMA_SYSTEM_H_ */


#ifndef _CHUU_BOSS_H_
#define _CHUU_BOSS_H_

#define CHUU_BOSS_JIKAN_01_0256 (256)
#define CHUU_BOSS_JIKAN_02_0272 (272)
#define CHUU_BOSS_JIKAN_03_1792 (256+1024+512+512)
#define CHUU_BOSS_JIKAN_04_2048 (256+1024+512+512+256)

//#define YOKAI1_DATA_repeat			/*廃止*/user_data04 	/* 繰り返し回数 */
//#define YOKAI1_DATA_start_limit_y256	/*廃止*/user_data05 	/* 登場y座標 */
//#define yokai_type					/*廃止*/user_data06 	/* 妖怪の種類(0 ... 3) */
	/* 開始するカード番号 */

//
#define YOKAI1_DATA_s2					target_obj		/* OBJ *s2;*/

//enum /* _yokai_type_ */
//{
//	YOKAI_TYPE_00_RUMIA = 0,	/* 0:00 ルーミア */
//	YOKAI_TYPE_01_YOUKAI02, 	/* 1:32 "妖怪2"(赤) */
//	YOKAI_TYPE_02_YOUKAI01, 	/* 2:64 "妖怪1"(青) */
//	YOKAI_TYPE_03_YOUKAI03		/* 3:96 "妖怪3"(紫) */
//};


#endif /* _CHUU_BOSS_H_ */
