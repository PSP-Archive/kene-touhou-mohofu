
#------------------------------------------------------------------------------
#  東方模倣風 ～ Toho Imitation Style.	Included Makefile for game core
#------------------------------------------------------------------------------
# game core version (r42)

#--- 基本関数 関連。
OBJS += $(OBJ)/game_core/$(TARGET)/my_math.o

#--- tama 関連。
# 敵弾発生基本システム(発弾システム)。[basic bullet create system]
OBJS += $(OBJ)/game_core/$(TARGET)/tama/hatudan_system.o
OBJS += $(OBJ)/game_core/$(TARGET)/tama/obj_system.o
# スクリプトシステム。
# 処理集中 CPU システム。
# ボス弾設定。
# 道中弾設定。
OBJS += $(OBJ)/game_core/$(TARGET)/tama/spell_system.o

#--- spell/card/boss 関連。
# スペルシステム。
# カードシステム。
# ボス移動 関連。
# オプションシステム。
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_card.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_support.o
#; ボス(本体)
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_all.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_move.o
#; ボスのオプション
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_tukaima.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_41_aya_momiji02.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_40_aya_momiji01.o
#
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_10_alice_zako_doll_type_b.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_11_alice_zako_doll_type_a.o

#--- zako 関連。
# 道中ザコ移動 関連。
# 道中の中ボス/ボス 関連。
# 道中イベント 関連。(道中イベント==スクロールとかゲーム終了とか)
#; 中ボスもどき
#; ザコのオプション
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/option_00_homing.o
#; 道中の敵(道中のボス/道中の中ボス/道中のザコ)
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/teki.o

#; 敵以外だが敵扱い
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/kanji_text.o
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/game_clear.o
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/bakuhatsu.o

#--- jiki 関連。
# 自機 関連。
# 自機オプション 関連。
# 自機ショット/ボム 関連。
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki.o
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_option.o
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_shot_bomber.o

#--- etc/core 関連。
# 背景コントロール
OBJS += $(OBJ)/game_core/$(TARGET)/bg.o
# アイテム
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/bonus_item.o

# ゲーム本体
OBJS += $(OBJ)/game_core/$(TARGET)/game_core.o
#--- audio 関連。
# ＢＧＭや効果音 コントロール
OBJS += $(OBJ)/game_core/$(TARGET)/game_audio.o

#--- draw 関連。
# 描画処理。
OBJS += $(OBJ)/game_core/$(TARGET)/draw/score_panel.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/PSPL_font.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/draw_kanji.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/graphics00.o 
OBJS += $(OBJ)/game_core/$(TARGET)/draw/psp_load_texture.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/psp_draw_screen.o

#--- menu 関連。
# 東雲フォントのデーター。
OBJS += $(OBJ)/font/shinonome16p.o

# エラーの場合、強制終了。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/fatal_error.o
# タイトル画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/title.o
# ステージ選択画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/select_stage.o
# 自機選択画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/select_jiki.o

# ゲーム一時停止画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/pause_menu.o
# ゲームオーバー画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/game_over.o
# 名前入力画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/name_entry.o

# ゲームオプション設定画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/option_menu.o
# キーコンフィグ設定画面。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/key_config.o
# ミュージックルーム。
OBJS += $(OBJ)/game_core/$(TARGET)/menu/music_room.o
# 会話システム。
#/* 会話システムは分離予定あり */
OBJS += $(OBJ)/game_core/$(TARGET)/menu/kaiwa.o

#--- file 関連。
# ファイル入出力処理。
OBJS += $(OBJ)/game_core/$(TARGET)/my_file.o
# ステージ読み込み処理/ステージ解釈処理。
OBJS += $(OBJ)/game_core/$(TARGET)/load_stage.o

#--- boot/initialize 関連。
# 起動処理。
OBJS += $(OBJ)/game_core/$(TARGET)/boot_main.o
# 始めに一度だけ初期化処理。
OBJS += $(OBJ)/game_core/$(TARGET)/initialize.o

#--- ディレクトリ作成。
OBJDIRS += $(OBJ)/game_core
OBJDIRS += $(OBJ)/game_core/$(TARGET)
OBJDIRS += $(OBJ)/game_core/$(TARGET)/jiki
OBJDIRS += $(OBJ)/game_core/$(TARGET)/douchu
OBJDIRS += $(OBJ)/game_core/$(TARGET)/boss
OBJDIRS += $(OBJ)/game_core/$(TARGET)/tama
OBJDIRS += $(OBJ)/game_core/$(TARGET)/draw
OBJDIRS += $(OBJ)/game_core/$(TARGET)/menu

#--- ソースリストからの読みこみインクルード優先パス設定。
#INCDIR += $(SRC)/game_core/$(TARGET)/.
INCDIR += $(SRC)/game_core/$(TARGET)/include


#--- 廃止。

#OBJS += $(OBJ)/game_core/$(TARGET)/tama/bullet_vector.o
#OBJS += $(OBJ)/game_core/$(TARGET)/tama/layer_system.o # (coreに統合)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_62_sakuya_ryoute.o	#(スペカfestival_knifeへ移行)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_64_sakuya_kurukuru.o	#(スペカfestival_knifeへ移行)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_63_sakuya_linear.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_65_sakuya_360knife.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_66_sakuya_star.o		#(スペカへ移行)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_67_sakuya_laser.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_68_sakuya_tama_oki.o	#(スペカへ移行)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_68_sakuya_hosigata.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_50_pache_laser.o	#(未使用)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_51_pache_doll.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_60_sakuya_baramaki1_2.o	#使い魔boss_tukaima.cに融合
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_20_mima_kaguya.o			#使い魔boss_tukaima.cに融合
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_boss.o#zako.cに融合
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_03_rumia.o#統合
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_02_youkai2.o#統合
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_01_youkai1.o#統合

#OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_bomber.o#jiki_shot_bomber.cに融合

#OBJS += $(OBJ)/game_core/$(TARGET)/menu/pause.o#統合
#OBJS += $(OBJ)/game_core/$(TARGET)/menu/ask_continue.o#統合

#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/clouds.o#一旦廃止。作り直した方が速い。
#OBJS += $(OBJ)/game_core/$(TARGET)/particle.o#一旦廃止。作り直した方が速い。
#OBJS += $(OBJ)/game_core/$(TARGET)/fps.o#廃止。
#OBJS += $(OBJ)/game_core/$(TARGET)/tiny_strcmp.o#ライブラリへ移動。
#OBJS += $(OBJ)/libpspmath.a#ライブラリへ移動。

#$ make
#Making object tree for kene ...
#psp-gcc $(CFLAGS_OPTIMIZE) -Werror -Isrc/core/. -I. -I/pspdev/psp/sdk/include -G0 -Wall -g 
#-I/usr/local/pspdev/psp/include -I/pspdev/psp/include/SDL	-c src/core/support.c -o
#obj/core/support.o
#cc1: warnings being treated as errors
#src/core/support.c: In function 'blit_scaled':
#src/core/support.c(573) : warning: control may reach end of non-void function 'getpixel' being inlined
#make: *** [obj/core/support.o] Error 1
# ?  警告: 制御が非 void 関数の終りに到達しました 
#$(OBJ)/core/support.o: $(SRC)/core/support.c
#	psp-gcc $(CFLAGS_OPTIMIZE)	 $(CXXFLAGS) -c $< -o $@
#	//else
#	//{
#		return (0);
#	//}
