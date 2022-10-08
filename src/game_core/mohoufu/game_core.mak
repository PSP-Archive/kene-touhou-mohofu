
#------------------------------------------------------------------------------
#  �����͕핗 �` Toho Imitation Style.	Included Makefile for game core
#------------------------------------------------------------------------------
# game core version (r42)

#--- ��{�֐� �֘A�B
OBJS += $(OBJ)/game_core/$(TARGET)/my_math.o

#--- tama �֘A�B
# �G�e������{�V�X�e��(���e�V�X�e��)�B[basic bullet create system]
OBJS += $(OBJ)/game_core/$(TARGET)/tama/hatudan_system.o
OBJS += $(OBJ)/game_core/$(TARGET)/tama/obj_system.o
# �X�N���v�g�V�X�e���B
# �����W�� CPU �V�X�e���B
# �{�X�e�ݒ�B
# �����e�ݒ�B
OBJS += $(OBJ)/game_core/$(TARGET)/tama/spell_system.o

#--- spell/card/boss �֘A�B
# �X�y���V�X�e���B
# �J�[�h�V�X�e���B
# �{�X�ړ� �֘A�B
# �I�v�V�����V�X�e���B
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_card.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_support.o
#; �{�X(�{��)
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_all.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_move.o
#; �{�X�̃I�v�V����
OBJS += $(OBJ)/game_core/$(TARGET)/boss/boss_tukaima.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_41_aya_momiji02.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_40_aya_momiji01.o
#
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_10_alice_zako_doll_type_b.o
OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_11_alice_zako_doll_type_a.o

#--- zako �֘A�B
# �����U�R�ړ� �֘A�B
# �����̒��{�X/�{�X �֘A�B
# �����C�x���g �֘A�B(�����C�x���g==�X�N���[���Ƃ��Q�[���I���Ƃ�)
#; ���{�X���ǂ�
#; �U�R�̃I�v�V����
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/option_00_homing.o
#; �����̓G(�����̃{�X/�����̒��{�X/�����̃U�R)
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/teki.o

#; �G�ȊO�����G����
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/kanji_text.o
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/game_clear.o
OBJS += $(OBJ)/game_core/$(TARGET)/douchu/bakuhatsu.o

#--- jiki �֘A�B
# ���@ �֘A�B
# ���@�I�v�V���� �֘A�B
# ���@�V���b�g/�{�� �֘A�B
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki.o
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_option.o
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_shot_bomber.o

#--- etc/core �֘A�B
# �w�i�R���g���[��
OBJS += $(OBJ)/game_core/$(TARGET)/bg.o
# �A�C�e��
OBJS += $(OBJ)/game_core/$(TARGET)/jiki/bonus_item.o

# �Q�[���{��
OBJS += $(OBJ)/game_core/$(TARGET)/game_core.o
#--- audio �֘A�B
# �a�f�l����ʉ� �R���g���[��
OBJS += $(OBJ)/game_core/$(TARGET)/game_audio.o

#--- draw �֘A�B
# �`�揈���B
OBJS += $(OBJ)/game_core/$(TARGET)/draw/score_panel.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/PSPL_font.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/draw_kanji.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/graphics00.o 
OBJS += $(OBJ)/game_core/$(TARGET)/draw/psp_load_texture.o
OBJS += $(OBJ)/game_core/$(TARGET)/draw/psp_draw_screen.o

#--- menu �֘A�B
# ���_�t�H���g�̃f�[�^�[�B
OBJS += $(OBJ)/font/shinonome16p.o

# �G���[�̏ꍇ�A�����I���B
OBJS += $(OBJ)/game_core/$(TARGET)/menu/fatal_error.o
# �^�C�g����ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/title.o
# �X�e�[�W�I����ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/select_stage.o
# ���@�I����ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/select_jiki.o

# �Q�[���ꎞ��~��ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/pause_menu.o
# �Q�[���I�[�o�[��ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/game_over.o
# ���O���͉�ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/name_entry.o

# �Q�[���I�v�V�����ݒ��ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/option_menu.o
# �L�[�R���t�B�O�ݒ��ʁB
OBJS += $(OBJ)/game_core/$(TARGET)/menu/key_config.o
# �~���[�W�b�N���[���B
OBJS += $(OBJ)/game_core/$(TARGET)/menu/music_room.o
# ��b�V�X�e���B
#/* ��b�V�X�e���͕����\�肠�� */
OBJS += $(OBJ)/game_core/$(TARGET)/menu/kaiwa.o

#--- file �֘A�B
# �t�@�C�����o�͏����B
OBJS += $(OBJ)/game_core/$(TARGET)/my_file.o
# �X�e�[�W�ǂݍ��ݏ���/�X�e�[�W���ߏ����B
OBJS += $(OBJ)/game_core/$(TARGET)/load_stage.o

#--- boot/initialize �֘A�B
# �N�������B
OBJS += $(OBJ)/game_core/$(TARGET)/boot_main.o
# �n�߂Ɉ�x���������������B
OBJS += $(OBJ)/game_core/$(TARGET)/initialize.o

#--- �f�B���N�g���쐬�B
OBJDIRS += $(OBJ)/game_core
OBJDIRS += $(OBJ)/game_core/$(TARGET)
OBJDIRS += $(OBJ)/game_core/$(TARGET)/jiki
OBJDIRS += $(OBJ)/game_core/$(TARGET)/douchu
OBJDIRS += $(OBJ)/game_core/$(TARGET)/boss
OBJDIRS += $(OBJ)/game_core/$(TARGET)/tama
OBJDIRS += $(OBJ)/game_core/$(TARGET)/draw
OBJDIRS += $(OBJ)/game_core/$(TARGET)/menu

#--- �\�[�X���X�g����̓ǂ݂��݃C���N���[�h�D��p�X�ݒ�B
#INCDIR += $(SRC)/game_core/$(TARGET)/.
INCDIR += $(SRC)/game_core/$(TARGET)/include


#--- �p�~�B

#OBJS += $(OBJ)/game_core/$(TARGET)/tama/bullet_vector.o
#OBJS += $(OBJ)/game_core/$(TARGET)/tama/layer_system.o # (core�ɓ���)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_62_sakuya_ryoute.o	#(�X�y�Jfestival_knife�ֈڍs)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_64_sakuya_kurukuru.o	#(�X�y�Jfestival_knife�ֈڍs)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_63_sakuya_linear.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_65_sakuya_360knife.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_66_sakuya_star.o		#(�X�y�J�ֈڍs)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_67_sakuya_laser.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_68_sakuya_tama_oki.o	#(�X�y�J�ֈڍs)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_68_sakuya_hosigata.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_50_pache_laser.o	#(���g�p)
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_51_pache_doll.o
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_60_sakuya_baramaki1_2.o	#�g����boss_tukaima.c�ɗZ��
#OBJS += $(OBJ)/game_core/$(TARGET)/boss/option_20_mima_kaguya.o			#�g����boss_tukaima.c�ɗZ��
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_boss.o#zako.c�ɗZ��
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_03_rumia.o#����
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_02_youkai2.o#����
#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/chuu_01_youkai1.o#����

#OBJS += $(OBJ)/game_core/$(TARGET)/jiki/jiki_bomber.o#jiki_shot_bomber.c�ɗZ��

#OBJS += $(OBJ)/game_core/$(TARGET)/menu/pause.o#����
#OBJS += $(OBJ)/game_core/$(TARGET)/menu/ask_continue.o#����

#OBJS += $(OBJ)/game_core/$(TARGET)/douchu/clouds.o#��U�p�~�B��蒼�������������B
#OBJS += $(OBJ)/game_core/$(TARGET)/particle.o#��U�p�~�B��蒼�������������B
#OBJS += $(OBJ)/game_core/$(TARGET)/fps.o#�p�~�B
#OBJS += $(OBJ)/game_core/$(TARGET)/tiny_strcmp.o#���C�u�����ֈړ��B
#OBJS += $(OBJ)/libpspmath.a#���C�u�����ֈړ��B

#$ make
#Making object tree for kene ...
#psp-gcc $(CFLAGS_OPTIMIZE) -Werror -Isrc/core/. -I. -I/pspdev/psp/sdk/include -G0 -Wall -g 
#-I/usr/local/pspdev/psp/include -I/pspdev/psp/include/SDL	-c src/core/support.c -o
#obj/core/support.o
#cc1: warnings being treated as errors
#src/core/support.c: In function 'blit_scaled':
#src/core/support.c(573) : warning: control may reach end of non-void function 'getpixel' being inlined
#make: *** [obj/core/support.o] Error 1
# ?  �x��: ���䂪�� void �֐��̏I��ɓ��B���܂��� 
#$(OBJ)/core/support.o: $(SRC)/core/support.c
#	psp-gcc $(CFLAGS_OPTIMIZE)	 $(CXXFLAGS) -c $< -o $@
#	//else
#	//{
#		return (0);
#	//}
