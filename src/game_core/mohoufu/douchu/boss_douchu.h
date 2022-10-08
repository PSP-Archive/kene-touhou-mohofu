

//#include "game_main.h"


extern OBJ_CALL_FUNC(chuu_boss_zako_anime_type05)
{
	zako_anime_type05(src);/* �A�j���[�V���� */
}


/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/
#define GAME_COMMAND_OBJ_CALL_PRIVATE(nnn)	game_command_##nnn(gcmd, gcmd_obj_2nd)

extern void callback_hit_chuu_boss(OBJ/**/ *src, OBJ/**/ *tama);
extern OBJ_CALL_FUNC(move_chuu_boss);


/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/
extern GAME_COMMAND_FUNC(01_regist_chuu_boss)/* [���^�G]���{�X�A�������� */
{
	//hold_game_mode_on();
	/*(���Ɏ��s���̏ꍇ�߂�B�Q�d�o�^���Ȃ��B���{�X�̓{�X�̗̈���g�p���Ă���̂ŁA
	�{�X�̗̈悪������Ȃ�����Q�����ɂ͏o���Ȃ��B)*/
	if (chuu_boss_00_mode_off != cg_BOSS_DATA_32_chuu_boss_mode)	{return;}/*(���{�X���s���Ȃ̂œo�^�ł��Ȃ�)*/
	//-----------------
	/* �v���C�I���e�B�[(�\���D�揇��)�����邩��A�w��ɕ\��������ׂɁA���߂Ɍ��̖����w���m�ہB */
	OBJ *gcmd_obj_3rd;		/* �w��̖����w */
	gcmd_obj_3rd	= obj_regist_teki();
	if (NULL == gcmd_obj_3rd)	{return;}/*(obj over�Ŕw��̖����w���o�^�ł��Ȃ�)*/
	//-----------------
	/* ���̖����w���m�ۏo������{�̂��m�ہB */
	OBJ *gcmd_obj_2nd;	/* �{�� */
	gcmd_obj_2nd	= obj_regist_teki();
	if (NULL == gcmd_obj_2nd)/* �{��(gcmd_obj_2nd)���o�^�ł��Ȃ������ꍇ�A�o�^�ł��Ȃ������ꍇ */
	{
		gcmd_obj_3rd->jyumyou	= JYUMYOU_NASI;/* �w��̖����w(gcmd_obj_3rd)�̓o�^��������߂�B */
		return;/*(obj over�Ŗ{�̂��o�^�ł��Ȃ�)*/
	}
	//-----------------
	/* ���{�X������ɓo�^�ł����ꍇ�̂݁A���{�X���s���ɂ���B */
	cg_BOSS_DATA_32_chuu_boss_mode = (chuu_boss_01_mode_stay);/*(���s��)*/
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
		/* �����w���� */
		gcmd_obj_3rd->m_Hit256R 			= ZAKO_ATARI02_PNG;
		gcmd_obj_3rd->obj_type_set			= ZAKO_28_MAHOJIN;
		gcmd_obj_3rd->atari_hantei			= (1/*�X�R�A���p*/);
		{
			const u32 color_table[4] =
			{	/*	gcmd_obj_3rd->alpha 		= 0x00;*/
				MAKE32RGBA(0xff, 0xff, 0xff, 0x7f), 	/* �D���ۂ� */
				MAKE32RGBA(0xff, 0x3f, 0x3f, 0x7f), 	/* �Ԃ��ۂ� */
				MAKE32RGBA(0x3f, 0x00, 0xff, 0x7f), 	/* ���ۂ� */
				MAKE32RGBA(0x5f, 0xff, 0xaf, 0x7f), 	/* �����ۂ�(���F�ɂȂ���) */
			};
			gcmd_obj_3rd->color32				= color_table[my_haikei_iro];
		}
	//
		gcmd_obj_2nd->callback_mover			= move_chuu_boss;
	//
		GAME_COMMAND_OBJ_CALL_PRIVATE(regist_settei_common);/* ���{�X�Ƌ��p����K�v������B */
		//	gcmd_obj_2nd->type		 /* �ݒ�t�@�C�����猈�߂� */
		/* easy�ł����݊�����ۂÂ���ׂ� 200 �͕K�v */ 	// 50+150*di fficulty;
	//	gcmd_obj_2nd->atari_hantei				= (1/*�X�R�A���p*/);
	//	gcmd_obj_2nd->m_Hit256R 				= ZAKO_ATARI16_PNG;
	//	gcmd_obj_2nd->ba se_hp					= ((l->us er_h p));		/* �ݒ�t�@�C������̗͂����߂�B */
	//	gcmd_obj_2nd->ba se_score				= ((l->us er_sco re));	/* �ݒ�t�@�C������l���X�R�A�����߂�B */
		//
	//	gcmd_obj_2nd->cen ter.x256				= ((l->us er_loc ate_x)<<(8));
	//	gcmd_obj_2nd->cen ter.y256				= ((l->us er_loc ate_y)<<(8));
		/*(
		(r41-)�̃V�X�e���ł̓X�y�J�̓X�y�JCPU�ł������s�ł��Ȃ��Ȃ����̂ŁA�]���̕����ł͒��{�X�̓X�y�J�����ĂȂ��B
		�ꎞ�I�Ȍ݊��΍�Ƃ��āA���{�X�ƃ{�X�͓����ɏo�Ă��Ȃ��̂ŁA���{�X�̓X�y�J�����ׂɁA�{�X�̏ꏊ���Ԏ؂肷��B
		�ꎞ�I�Ƀ{�X�̍��W������������
		)*/
		#if 1
		/*(�o��\����W)*/
	//	VR06	= /*(�X�y�JCPU�O�����W[���{�X�p])*/gcmd_o bj_2nd->cen ter.x256;
	//	VR07	= /*(�X�y�JCPU�O�����W[���{�X�p])*/((gcmd->us er_loc ate_y)<<(8));/* t256(50.0) */		/* (���{�X�p�A����C��) */		// ���{�X�̏ꍇ�Ay���W�͓o��\����W�B
		game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel�P��] �ݒ�t�@�C������ �o��(x, y)���W ��(VR06, VR07)�ɐݒ肷��B */
		/*(���ݍ��W)*/
		cg_BOSS_DATA_3a_center_x256/*(�X�y�JCPU�������W[�{�X�p])*/ = t256(300.0);/*(�X�y�JCPU�O�����W[���{�X�p])*/
		cg_BOSS_DATA_3b_center_y256/*(�X�y�JCPU�������W[�{�X�p])*/ = t256(-30.0);/*(�X�y�JCPU�O�����W[���{�X�p])*/	/* (���{�X�p�A����C��) */
		/* (�w��̖����w���W) */ /* (���{�X���W) */
		gcmd_obj_3rd->center.x256				=	gcmd_obj_2nd->center.x256				= cg_BOSS_DATA_3a_center_x256;
		gcmd_obj_3rd->center.y256				=	gcmd_obj_2nd->center.y256				= cg_BOSS_DATA_3b_center_y256;
		boss_set_new_position_void();
		#endif
		//
		gcmd_obj_2nd->callback_hit_teki 		= callback_hit_chuu_boss;	/* �R�[���o�b�N�o�^ */
	//
		gcmd_obj_2nd->YOKAI1_DATA_s2			= gcmd_obj_3rd;
		#if 1
		//------------ �J�[�h�֘A
		card.spell_used_number		= (SPELL_00);/*(�J�[�h���s��~�ɂ���)*/
		card.address_temporaly		= ((gcmd->user_kougeki_type)&0x3f);
		gcmd_obj_2nd->jyumyou		= (CHUU_BOSS_JIKAN_04_2048-1);/* �u�ォ��o��v�֐ݒ�B */
		#endif
	}
}
/*---------------------------------------------------------
	�G��ǉ�����
---------------------------------------------------------*/

extern GAME_COMMAND_FUNC(02_move_chuu_boss)/* [���^�G]���{�X�ړ��R�}���h�B(r41-) */
{
	if (chuu_boss_00_mode_off == cg_BOSS_DATA_32_chuu_boss_mode) 	{return;}/*(���{�X���s���ȊO�͉������Ȃ�)*/
	//
//	GAME_COMMAND_OBJ_CALL_PRIVATE(regist_settei_common);/* ���{�X�Ƌ��p����K�v������B */
	#if 1
	/*(�o��\����W)*/
	game_command_set_locate_xy_to_R06_R07(gcmd);/* [pixel�P��] �ݒ�t�@�C������ �o��(x, y)���W ��(VR06, VR07)�ɐݒ肷��B */
//	VR06	= /*(�X�y�JCPU�O�����W[���{�X�p])*/((gcmd->us er_loc ate_x)<<(8));
//	VR07	= /*(�X�y�JCPU�O�����W[���{�X�p])*/((gcmd->us er_loc ate_y)<<(8));	// ���{�X�̏ꍇ�Ay���W�͓o��\����W�B
	/*(���ݍ��W)*/
//	cg_BOSS_DATA_3a_center_x256/*(�X�y�JCPU�������W[�{�X�p])*/ = t256(300.0);/*(�X�y�JCPU�O�����W[���{�X�p])*/
//	cg_BOSS_DATA_3b_center_y256/*(�X�y�JCPU�������W[�{�X�p])*/ = t256(-30.0);/*(�X�y�JCPU�O�����W[���{�X�p])*/	/* (���{�X�p�A����C��) */
	/* (�w��̖����w���W) */ /* (���{�X���W) */
	boss_set_new_position_void();
	#endif
}

//#include "game_main.h"

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�����̃{�X
---------------------------------------------------------*/
/* from game_core.c */
//extern OBJ_CALL_FUNC(common_bo ss_put_items);
extern GAME_COMMAND_FUNC(06_kaiwa_start_boss)
{
	//----[BOSS]
	OBJ *gcmd_obj;
	gcmd_obj				= &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI];/*(�{�X�{��)*/
	GAME_COMMAND_OBJ_CALL(regist_settei_common);/* ���{�X/(boss)�Ƌ��p����K�v������B(gcmd_obj->callback_loser���ݒ肳���) */
//[��������]	/*(�Ē�`�̕K�v����)*/	gcmd_obj->callback_loser				= common_bo ss_put_items;
	NEXT_SCENE;/*(���̏�ʂ֐ݒ�)*/
}
