
#include "boss.h"//#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	カード
	-------------------------------------------------------
	ボス共通規格使用データー:
---------------------------------------------------------*/

#define MOMIJI_KODOMO_DATA_angle65536			user_data00 	/*union BULLET_ANGLE_DATA*/
#define MOMIJI_KODOMO_DATA_speed256 			user_data01 	/*union BULLET_ANGLE_DATA*/
//
//
#define MOMIJI_KODOMO_DATA_angle222_65536		user_data03
#define MOMIJI_KODOMO_DATA_adjust_speed256		user_data06


/*---------------------------------------------------------
	分裂(last)
---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_aya_doll_last_burrets)
{
//	/*[r35要半分速]*/HATSUDAN_R11_speed256	= (t256(0.75)+(ra_nd()&0xff));					/* 弾速 */
	/*[r35半分速]*/HATSUDAN_R11_speed256	= (t256(0.375)+(ra_nd()&0xff)); 				/* 弾速 */
	HATSUDAN_R12_speed_offset				= (2);/*(とりあえず)*/
	HATSUDAN_R14_tama_spec					= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)標準弾 */
	HATSUDAN_R13_angle65536 				= ((ra_nd()&(65536-1)));						/* src->tmp_angleCCW1024 */
	HATSUDAN_R15_bullet_obj_type			= (BULLET_KOME_BASE + TAMA_IRO_01_AKA) + (((cg_VR20_game_difficulty)&0x02)<<1); /* [赤(0x01)/緑(0x05)米弾] */
	HATSUDAN_R16_n_way						= (1+(cg_VR20_game_difficulty));				/* [7way] [8way] */
	HATSUDAN_R17_div_angle65536 			= (int)(65536/23);								/* 角度 (65536/27) (65536/24) */
	set_REG_DEST_XY(src);	/* 弾源x256 y256 中心から発弾。 */
	hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
//	bullet_regist_multi_vector_direct();
}

/*---------------------------------------------------------

---------------------------------------------------------*/

static OBJ_CALL_FUNC(move_bullet_momiji)
{
	//	jyumyou 		= (50); 	/* 200寿命 */
	if ((HATUDAN_ITI_NO_JIKAN_USE_EFFECT-50) < src->jyumyou)/* 発弾エフェクト後から[50]カウント未満の弾 */
	/* 移動処理 */
	{
		if (src->MOMIJI_KODOMO_DATA_speed256 < t256(0.5) )
		{
			src->MOMIJI_KODOMO_DATA_angle222_65536 += (65536/2);	/* (65536/2) == 半周 == [180/360 度] */
			#if 1
			/* ねんのため */
		//	mask65536(src->MOMIJI_KODOMO_DATA_angle222_65536);
			#endif
			src->MOMIJI_KODOMO_DATA_angle65536	= src->MOMIJI_KODOMO_DATA_angle222_65536;
			src->MOMIJI_KODOMO_DATA_adjust_speed256 = (-(src->MOMIJI_KODOMO_DATA_adjust_speed256));
		}
		src->MOMIJI_KODOMO_DATA_speed256 += src->MOMIJI_KODOMO_DATA_adjust_speed256;
		if (((src->MOMIJI_KODOMO_DATA_angle65536-src->MOMIJI_KODOMO_DATA_angle222_65536)>>6/*r42とりあえず*/) < (int)(1024*1/12) )
		{
			src->MOMIJI_KODOMO_DATA_angle65536 += ((1+1)<<6);/*0.01*/
		}
		#if 1
		/* ねんのため */
	//	mask65536(src->MOMIJI_KODOMO_DATA_angle65536);
		#endif
	//	mono_angle_move(src, (BULLET_ANGLE_DATA *)data);
		#if (0)//r42(?)
	//	src->math_vector.x256			= ((si n65536((src->MOMIJI_KODOMO_DATA_angle65536))*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/	/* CCWの場合 */
	//	src->math_vector.y256			= ((co s65536((src->MOMIJI_KODOMO_DATA_angle65536))*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
		{
			int sin_value_t256; 	//	sin_value_t256 = 0;
			int cos_value_t256; 	//	cos_value_t256 = 0;
			int256_sin cos65536( (src->MOMIJI_KODOMO_DATA_angle65536), &sin_value_t256, &cos_value_t256);
			src->math_vector.x256			= ((sin_value_t256*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
			src->math_vector.y256			= ((cos_value_t256*(src->MOMIJI_KODOMO_DATA_speed256))>>8);/*fps_factor*/
		}
		#else
		//------------------
		HATSUDAN_R11_speed256	= (src->MOMIJI_KODOMO_DATA_speed256);
		HATSUDAN_R13_angle65536 = (src->MOMIJI_KODOMO_DATA_angle65536);
		CPU_CALL(sincos256);/*(破壊レジスタ多いので注意)*/
		src->math_vector.x256 = VR07;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		src->math_vector.y256 = VR06;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
		//------------------
		#endif
		src->center.x256 += (src->math_vector.x256);/*fps_factor*/
		src->center.y256 += (src->math_vector.y256);/*fps_factor*/
	}
	/* おしまい処理 */
	else
	{
		move_aya_doll_last_burrets(src);
		src->jyumyou = JYUMYOU_NASI;	/* おしまい */
	}
}

/*---------------------------------------------------------
	5方向もみじ小弾を生成
---------------------------------------------------------*/
#define MOMIJI_KODOMO_next_angle65536	tmp_angleCCW65536	/* 子供弾、生成角度 */

#define i_angle65536	VR03_i

/*static*/ OBJ_CALL_FUNC(add_zako_aya_5_momiji)
{
	/* 初期位置 */
	VR05			= src->center.x256;
	VR04			= src->center.y256;
//	int i_angle65536;
	i_angle65536 = (src->MOMIJI_KODOMO_next_angle65536)-((int)(65536*1/20));
//
//	int VR02_j;
	for (VR02_j=(0); VR02_j<(5); VR02_j++)
	{
		OBJ *h;
		h							= obj_regist_teki();
		if (NULL != h)/* 登録できた場合のみ */
		{
			h->center.x256							= VR05;/* 発弾位置 座標x */
			h->center.y256							= VR04;/* 発弾位置 座標y */
			//
			h->obj_type_set 						= (TEKI_32_20) + ((i_angle65536>>(7+6)) & 0x07);/* 0 ... 8 */
			h->m_Hit256R							= ZAKO_ATARI16_PNG;
			h->atari_hantei 						= (1/*スコア兼用*/);
		//
			h->callback_mover						= move_bullet_momiji;
			h->jyumyou								= HATUDAN_ITI_NO_JIKAN_USE_EFFECT;
			//
			h->MOMIJI_KODOMO_DATA_angle222_65536	= (i_angle65536);/*r42とりあえず*/
			h->MOMIJI_KODOMO_DATA_angle65536		= (i_angle65536);/*r42とりあえず*/
			h->MOMIJI_KODOMO_DATA_speed256			= t256(3.0);
			h->MOMIJI_KODOMO_DATA_adjust_speed256	= t256(-0.04);
			//
			i_angle65536 += (int)(65536*1/20);/*offset_angle*/
		//	mask65536(i_angle65536);
		}
	}
}
