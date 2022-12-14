
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	演出用テキスト
---------------------------------------------------------*/

#include "kanji_system.h"

/* ゲーム中イベントメッセージ表示 */
extern GAME_COMMAND_FUNC(00_kanji_hyouji)
{
	#if (1)/*(r36使ってないので廃止するかも)*/
	if ((255)!=l->user_255_code)
	{
		return; 	/* error!! */
	}
	if (0==l->user_x)
	{
		kanji_window_all_clear();	/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	}
	cg.msg_time = byou60(5);	/* 約 5 秒 */
//
	char *text;
	text = l->user_string;
	strcpy(my_font_text, text);
	kanji_color(7);
	kanji_draw();
	#endif
}

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	隠しボーナスチェック
---------------------------------------------------------*/
static int kakusi_check;

/*---------------------------------------------------------
	隠しボーナスチェック終了。結果表示。
	-------------------------------------------------------
	シークレット区間終了。結果表示。
---------------------------------------------------------*/
extern GAME_COMMAND_FUNC(03_check_secret_bonus)
{
	int secret_bonus;
	if (kakusi_check != cg_player_data_used_bomber)
	{
		/* ボム使用したら、ボーナス無し。 */
		secret_bonus = (0);
	}
	else
	{
		int secret_score_table[4] =
		{
			score( 100000), /*(easy 	10万[pts])*/
			score( 500000), /*(normal	50万[pts])*/
			score(1000000), /*(hard    100万[pts])*/
			score(5000000), /*(lunatic 500万[pts])*/
		};
		secret_bonus = secret_score_table[((cg_VR20_game_difficulty)/*&0x03*/)];
	}
	/* */
	player_dummy_add_score(secret_bonus);
}

/*---------------------------------------------------------
	隠しボーナスチェック開始。
	-------------------------------------------------------
	シークレット区間開始
---------------------------------------------------------*/
extern GAME_COMMAND_FUNC(04_begin_secret_bonus)
{
	kakusi_check = cg_player_data_used_bomber;/* 開始時のボム使用数を覚えておく */
}

