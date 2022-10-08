
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	もみじカード
	-------------------------------------------------------
	ボス共通規格使用データー:
---------------------------------------------------------*/

#define MOMIJI_KODOMO_next_angle65536	tmp_angleCCW65536					/* 子供弾、生成角度 */

/*---------------------------------------------------------

---------------------------------------------------------*/
/*static*/extern OBJ_CALL_FUNC(add_zako_aya_5_momiji);
static OBJ_CALL_FUNC(move_aya_momiji_oya)
{
//	jyumyou 		= ((30+15)/*+1*/);
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-(45)) < src->jyumyou)/* 発弾エフェクト後から[(45)]カウント未満の弾 */
	/* 移動処理 */
	{
		src->center.x256 += (src->math_vector.x256);/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);/*fps_factor*/
		//
		/* 親が画面外なら分裂しない */
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	/* おしまい処理 */
	else
	{
		add_zako_aya_5_momiji(src); 	/* 5方向もみじ小弾を生成 */
		src->jyumyou = JYUMYOU_NASI;	/* おしまい */
	}
}


/*---------------------------------------------------------

---------------------------------------------------------*/

#define i_angle65536	VR03_i

/*static*/ OBJ_CALL_FUNC(add_zako_aya_doll)
{
	/* 初期位置 */
	VR05			= src->center.x256;
	VR04			= src->center.y256;
//	int i_angle65536;
//	for (i_angle65536=(int)((65536)-(65536*2/24)); i_angle65536<(int)((65536)+(65536*3/24)); i_angle65536+=(int)(65536*1/24) )
	for (i_angle65536=(0); i_angle65536<(65536); i_angle65536+=(int)(65536*1/24) )
	{
		OBJ *h;
		h							= obj_regist_teki();
		if (NULL != h)/* 登録できた場合のみ */
		{
			h->center.x256						= VR05;/* 発弾位置 座標x */
			h->center.y256						= VR04;/* 発弾位置 座標y */
			//
			h->obj_type_set 					= (TEKI_32_20)+((i_angle65536>>(7+6)) & 0x07);/* 0 ... 8 */
			h->m_Hit256R						= ZAKO_ATARI16_PNG;
			h->atari_hantei 					= (/*ATARI_HANTEI_TAOSENAI*/ATARI_HANTEI_OFF/*スコア兼用*/);/* あたり判定無し */
			h->zako_hp							= (ZAKO_HP_TAOSENAI);/*(倒せない)*/
	//		h->base_score						= score(25*2);/*ダミー*/
			//
			h->callback_mover					= move_aya_momiji_oya;
		//	h->callback_loser					= NULL;
	//		h->callback_hit_teki				= callback_hit_zako;/*(?)*/
			h->rotationCCW65536 				= (i_angle65536);
			//
			h->jyumyou = HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			#if 1/*(?)*/
			h->MOMIJI_KODOMO_next_angle65536	= (i_angle65536);
			#endif
	//		regist_vector(h, speed256, angle512);
		//	const int speed256 = t256(1.00);
		//	h->math_vector.x256 = ((si n1024((angle1024))*(speed256))>>8);	/*fps_factor*/
		//	h->math_vector.y256 = ((co s1024((angle1024))*(speed256))>>8);	/*fps_factor*/
			#if (0)//r42(?)
		//	h->math_vector.x256 = (si n65536((i_angle65536)));	/*fps_factor*/	/* CCWの場合 */
		//	h->math_vector.y256 = (co s65536((i_angle65536)));	/*fps_factor*/
			{
				int sin_value_t256; 		//	sin_value_t256 = 0;
				int cos_value_t256; 		//	cos_value_t256 = 0;
				int256_sin cos65536(i_angle65536, &sin_value_t256, &cos_value_t256);
				h->math_vector.x256 			= (sin_value_t256);/*fps_factor*/
				h->math_vector.y256 			= (cos_value_t256);/*fps_factor*/
			}
			#else
			//------------------
			HATSUDAN_R11_speed256				= (t256(1.0));
			HATSUDAN_R13_angle65536 			= (i_angle65536);
			CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
			h->math_vector.x256 				= VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			h->math_vector.y256 				= VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
			//------------------
			#endif
		}
	}
}
