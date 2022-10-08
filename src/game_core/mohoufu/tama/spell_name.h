
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�X�y���V�X�e��==�J�[�h�̊Ǘ��V�X�e���B(�J�[�h�V�X�e���Ƃ͈Ⴄ�̂Œ���)
	-------------------------------------------------------
	�X�y���V�X�e��(���炩���߃J�[�h�̒�`�����Ă����V�X�e��)
	-------------------------------------------------------
	�͕핗�ł̓X�y���̓V�X�e���ŃT�|�[�g���Ă��܂��B
	�X�y���Ƃ��Ē�`(�J�[�h)���Ă����ƁA�ǂ̃{�X���A�ǂ̃X�y���ł����Ă�悤�ɂȂ�܂��B
	-------------------------------------------------------
	�܂��X�y���̓J�[�h�V�X�e���ɔԍ���o�^���Ă����ƁA�J�[�h�V�X�e���ŃX�y�����擾�ł��܂��B
	(�܂�J�[�h�V�X�e���o�R�ŃX�y�������Ă܂�)
	-------------------------------------------------------
	(r32)���݁A�G��(�͕핗��dat�̒�-�{�X)���X�y�������Ă܂����A
	���̋@�\�͏����Ȃ��Ȃ邩���m��܂���B
	�G��(�͕핗��dat�̒�-�{�X)���X�y�������Ă�@�\�́u���_�\�v�Ŏv�������̂ł����A
	���������@�\�����������Q�[���̑��x�������o����C�����邵�A
	�����������炱�������@�\�͖{�Ƃɖ����̂����Ǝv�����Ƃ�����܂��B�ǂ�����܂���B
	-------------------------------------------------------
	card.spell_used_number �Ɍ��������X�y�����Z�b�g����ƁA�X�y�������J�n�B
	�X�y���������I������Ǝ����I�� card.spell_used_number �� DANMAKU_00 �ɂȂ�B
	-------------------------------------------------------
	�X�y���������� VR10_BOSS_SPELL_TIMER ������ɖ��t���[�����Z����A0 �ɂȂ�ƃX�y�������I���B
	���̎��Ԃ̓X�y�����ƂɈႤ�W�����Ԃ��ݒ肳��Ă���B
	����̓J�[�h�̏��������Ŏ��������������B
	-------------------------------------------------------
	�J�[�h�̏������B
	�J�[�h���ς��Ɩ���s���K�v������B
	-------------------------------------------------------
---------------------------------------------------------*/

#ifndef _SPELL_NAME_VALUE_H_
#define _SPELL_NAME_VALUE_H_

/* �J�[�h�ԍ�(�e�X�y������ʂ���ׂ̔ԍ�) */
enum
{
	SPELL_00 = 0,						/* �X�y�������I���t���O�B */
//	/* �G���p */
	SPELL_01_sakuya_misogi_normal,		/* [���] �g5�ʒ�-�{�X �S�J�[�h / �g5�ʒ�-�{�X ��� �u�ʏ�U���v */
	SPELL_02_,							/* [����] */		/* [���] �g5�ʒ�-�{�X 24�J�[�h (��p�u�~�X�f�B���N�V�������ǂ�(1/2)�v) */
	SPELL_03_sakuya_old_test,			/* [���] �g5�ʒ�-�{�X 11�J�[�h (��p�u�~�X�f�B���N�V�������ǂ�(2/2)�v) */
	SPELL_04_sakuya_pink_hearts,		/* [���] �g5�ʃ{�X [���] �u�ʏ�U��1(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_05_sakuya,					/* [���] �g5�ʃ{�X [���] �u�ʏ�U��1/2(2/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_06_sakuya,					/* [���] �g5�ʃ{�X [���] ���ہu���i�N���b�N(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_07_sakuya,					/* [���] �g5�ʃ{�X [���] �u�ʏ�U��3(1/2)�v�ɂ�����Ƃ��������J�[�h(�\��) */
//
	SPELL_08_rumia, 					/* [���[�~�A] �g1�ʃ{�X [���[�~�A] �镄�u�i�C�g�o�[�h�v�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_09_test_inuno_fuguri, 		/* [���̑�] ���ؒe easy�p */
	SPELL_0a_dai_yousei_01, 			/* 10:[��d��] �S�� 48�����A���v���A�΃N�i�C�e */
	SPELL_0b_dai_yousei_02, 			/* 11:[��d��] �S�� 48�����A�����v���A�ԃN�i�C�e */
	SPELL_0c_sakuya_jack32, 			/* [���] ���H�u�W���b�N�E�U�E���h�r���v�ɂȂ邩������Ȃ��e�X�g */
	SPELL_0d_dai_yousei_03, 			/* 13:[��d��] 9�����e + 9����������ƌo�����玩�@�_�����e */
	SPELL_0e_remilia_00,				/* [���~���A] �e�X�g */
	SPELL_0f_tengu, 					/* [���̑�] �������̗d��1(�V��l?)�����J�[�h(�\��) */ 	/*(?)*/
//
	SPELL_10_cirno, 					/* [�`���m] �S�J�[�h */
	SPELL_11_perfect_freeze,			/* [�`���m] �p�[�t�F�N�g�t���[�Y */
	SPELL_12_diamond_blizzard,			/* [�`���m] �ᕄ�u�_�C�A�����h�u���U�[�h�v */
	SPELL_13_alice_suwako,				/* [�A���X] �z�K�q���ۂ�(?)�J�[�h */
	SPELL_14_alice_youmu300,			/* [�A���X] �d3�ʃ{�X  normal�ʏ�U��3(�̈ꕔ) */
	SPELL_15_alice_aka_2nd, 			/* [�A���X] ��EX�ʃ{�X �Ԃ̖��@2�i�K�ڂ��ǂ� */
	SPELL_16_alice_zako_doll,			/* [�A���X] �d3�ʃ{�X [�A���X]�l�`�J�[�h(���ǂ�) */ // 40[sec]
	SPELL_17_alice_tama_doll_02,		/* [�A���X] �쐬�� */
//
	SPELL_18_hana_test, 				/* [����] �ԂĂ��ƃJ�[�h */
	SPELL_19_meirin_5_houkou,			/* SPELL_40_meirin_kasou_yume_kazura 4[����] �����u�ؑz�����v */		//SPELL_40_SONOTA_DEBUG_CW_AO,		/* [���̑�] �f�o�b�O�J�[�hCW�� */
	SPELL_41_meirin_saikou_no_furin,	/* 4[����] �����u�ʓ��̕���v */	//SONOTA_DEBUG_CCW_AKA,		/* [���̑�] �f�o�b�O�J�[�hCCW�� */
	SPELL_1b_cirno_icecle_fall, 		/* [�`���m] �X���u�A�C�V�N���t�H�[���v */
	SPELL_44_ruiz3_test,				/* [���C�Y] �J�[�h��̂Ă��ƁB */
	SPELL_1d_amefuri_test,				/* [] �J�Ă��� */
	SPELL_1e_momiji_no_nonoji,			/* [��] �̂̂��J�[�h */
	SPELL_1f_koakuma,					/* [������] �Ă��Ɨp */
//	/* �{�X�p */
	SPELL_20_aya_misogi1,				/* 1[��] �̒ʏ�e���ۂ��J�[�h�������Ă݂�e�X�g1 */
	SPELL_21_aya_misogi2,				/* 2[��] �̒ʏ�e���ۂ��J�[�h�������Ă݂�e�X�g2 */
	SPELL_22_ame_no_yatimata,			/* 3[��] �򕄁u�V�̔��ˁv */
	SPELL_23_meirin_magaru_kunai,		/* 4[����] �ʏ�U�� */
	SPELL_24_aya_doll,					/* 5[��] �l�`�J�[�h */ //40[sec]
	SPELL_25_houka_kenran,				/* 6[�g����] �ؕ��u�F�؈�ࣁv�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_26_aya_saifu, 				/* 7[��] �Ǖ� */
	SPELL_27_hosigata_test, 			/* 8[���̑�] ���^�e�X�g */
//
	SPELL_28_sakuya_miss_direction,		/* [���] ��p�u�~�X�f�B���N�V�����v */
	SPELL_29_rumia_demarcation, 		/* 10[���[�~�A] �g1�ʃ{�X �ŕ��u�f�B�}�[�P�C�V�����v�ɂ�����Ƃ��������J�[�h(�\��) */
	SPELL_2a_sakuya_baramaki1,			/* 11[���] �g5�ʒ�-�{�X �΂�T��1 �J�[�h () */
	SPELL_2b_sakuya_baramaki2,			/* 12[���] �g5�ʒ�-�{�X �΂�T��2 �J�[�h () */
	SPELL_2c_sakuya_blue_red,			/* 13[���] �g5�ʒ�-�{�X �u�ʏ�U��3�v�ԃi�C�t */
	SPELL_2d_sakuya_misogi_lunatic, 	/* 14[���] �g5�ʒ�-�{�X �S�J�[�h / �g5�ʒ�-�{�X ��� �u�ʏ�U���vlunatic */
	SPELL_2e_pache_agni_shine_1,		/* [�p�`�F] "�@�@�@�@�Ε��u�A�O�j�V���C���v" No.15 */	// agni shine (�A�O�j�̋P��)�A (�A�O�j==�C���h�_�b�̉΂̐_)
	SPELL_2f_pache_princess_undine, 	/* [�p�`�F] "�@�����u�v�����Z�X�E���f�B�l�v" No.16 */	// princess undine (�E���f�B�l�̕P)�A(�E���f�B�l==�B���p�t�p���P���X�X�́u�d���̏��v�ɓo�ꂷ�鐅�̐��̖��O)
//
	SPELL_30_pache_sylphy_horn_1,		/* [�p�`�F] "�@�@�@�@�ؕ��u�V���t�B�z�����v" No.17 */	// sylphy horn (�V���t�B�̃z����)�A(�V���t�B==�����i�鐸��)�A(�z����==�y��==�p�J)
	SPELL_31_pache_rage_tririton_1, 	/* [�p�`�F] "�@�@�y���u���C�W�B�g�����g���v" No.18 */	// rage tririton (�{��g�����g��)�A (�g�����g��==���E��Y�X�g�[���w���W�̎O��)
	SPELL_32_pache_metal_fatigue,		/* [�p�`�F] "�@�@�����u���^���t�@�e�B�[�O�v" No.19 */	// metal fatigue (������J)
	SPELL_33_pache_agni_shine_2,		/* [�p�`�F] "�@�@�Ε��u�A�O�j�V���C���㋉�v" No.20 */
	SPELL_34_pache_sylphy_horn_2,		/* [�p�`�F] "�@�@�ؕ��u�V���t�B�z�����㋉�v" No.21 */
	SPELL_35_pache_rage_tririton_2, 	/* [�p�`�F] "�y���u���C�W�B�g�����g���㋉�v" No.22 */
	SPELL_36_pache_agni_radiance,		/* [�p�`�F] "�@�Ε��u�A�O�j���C�f�B�A���X�v" No.23 */	// agni radiance (�A�O�j�̋P��)�A (�A�O�j==�C���h�_�b�̉΂̐_)
	SPELL_37_pache_bury_in_lake,		/* [�p�`�F] "�@�@�@�����u�x���[�C�����C�N�v" No.24 */	// bury in lake (����)
//
	SPELL_38_pache_green_storm, 		/* [�p�`�F] "�@�@�@�ؕ��u�O���[���X�g�[���v" No.25 */	// green storm (�΂̗�)
	SPELL_39_pache_tririton_shake,		/* [�p�`�F] "�@�@�y���u�g�����g���V�F�C�N�v" No.26 */	// tririton shake (�h���g�����g��)�A (�g�����g��==���E��Y�X�g�[���w���W�̎O��)
	SPELL_3a_pache_silver_dragon,		/* [�p�`�F] "�@�@�@�����u�V���o�[�h���S���v" No.27 */	// silver dragon (�◃��)
	SPELL_3b_pache_lava_cromlech,		/* [�p�`�F] "�΁��y���u���[���@�N�������N�v" No.28 */	// lava cromlech (�n�����)
	SPELL_3c_pache_forest_blaze,		/* [�p�`�F] "�؁��Ε��u�t�H���X�g�u���C�Y�v" No.29 */	// forest blaze (�X�щ΍�)
	SPELL_3d_pache_water_elf,			/* [�p�`�F] "�@�����ؕ��u�E�H�[�^�[�G���t�v" No.30 */	// water (��) / elf (�d��)	(�M���O:���n��==���ɗn�����Ⴄ�d��)
	SPELL_3e_pache_mercury_poison,		/* [�p�`�F] "���������u�}�[�L�����|�C�Y���v" No.31 */	// mercury poison (���⒆��)
	SPELL_3f_pache_emerald_megalith,	/* [�p�`�F] "�y�������u�G�������h���K���X�v" No.32 */	// emerald megalith (����ȃG�������h��)
		//
/*40*/	SPELL_40_PACHE_LASER1,				/* [�p�`�F] �u�ʏ�U��1�v�̃��[�U�[���ǂ� */
/*41*/	SPELL_41_PACHE_LASER2,				/* [�p�`�F] �u�ʏ�U��3�v�̃��[�U�[���ǂ� */
/*4e*/	SPELL_42_remilia_vlad_tepes,		/* 9[���/���~���A] �g6�ʃ{�X ���f�u�u���h�E�c�F�y�V���̎􂢁v*/
/*4f*/	SPELL_43_remilia_red_magic, 		/* 9[���/���~���A] �g6�ʃ{�X �u���b�h�}�W�b�N�v���ۂ�(?)*/
/*4d*/	SPELL_44_remilia_rasen_knife,		/* 9[���/���~���A] �g6�ʃ{�X �ԃi�C�t�����e(�\��) */
/*47*/	SPELL_45_sakuya_festival_knife, 	/* [���] ���z�u�t�F�X�e�B�o���i�C�t�v(?) �ނ���ϊ� */
/*42*/	SPELL_46_mima_sekkin,				/* [����] �ڋ߃J�[�h */
/*43*/	SPELL_47_mima_toge, 				/* [����] �g�Q�Ă��ƃJ�[�h */
		//
/*49*/	SPELL_48_kaguya000, 						/* [�P��] �ނ���ϊ�000 SPELL_49_kaguya111 */
/*44*/	SPELL_49_kaguya111, 						/* [�P��] �ނ���ϊ�111 */
/*45*/	SPELL_4a_kaguya222, 						/* [�P��] �ނ���ϊ�222 */
/*46*/	SPELL_4b_kakuya333_tamanoe, 				/* [�P��] �ނ���ϊ�333  [�P��]�A�H���̋ʂ̎}���ǂ��B�쐬�� */
/*4c*/	SPELL_4c_kakuya_tamanoe_bbb,				/* [�P��] �ނ���ϊ�444 */
/*4a*/	SPELL_4d_rumia_3nerai,						/* [���[�~�A] */
/*4b*/	SPELL_4e_test,								/* [�P��] �Ă��� */
/*48*/	SPELL_4f_aya_taifu, 						/* [��] �啗�`�� */
//
/*50*/	SPELL_50_,
/*51*/	SPELL_51_kaguya_tujyou_kougeki_01,			// �ʏ�U��1
/*52*/	SPELL_52_kaguya_tatu_no_kubi_no_tama,		// ���u������̋ʁ@-�ܐF�̒e��-�v
/*53*/	SPELL_53_kaguya_brilliant_dragon_bullet,	// �_��u�u�����A���g�h���S���o���b�^�v
/*54*/	SPELL_54_kaguya_tujyou_kougeki_02,			// �ʏ�U��2,
/*55*/	SPELL_55_kaguya_hotoke_no_oisi_no_hati, 	// ���u���̌�΂̔��@-�ӂ��ʈӎu-�v,
/*56*/	SPELL_56_kaguya_bdist_diamond,				// �_��u�u�f�B�X�g�_�C�A�����h�v
/*57*/	SPELL_57_kaguya_tujyou_kougeki_03,			// �ʏ�U��3,
		//
/*58*/	SPELL_58_kaguya_hi_nezumi_no_kawa_goromo,	// ���u�Αl�̔�߁@-�ł�ʐS-�v,
/*59*/	SPELL_59_kaguya_salamnder_shiled,			// �_��u�T���}���_�[�V�[���h�v
/*5a*/	SPELL_5a_kaguya_tujyou_kougeki_04,			// �ʏ�U��4,
/*5b*/	SPELL_5b_kaguya_tubame_no_koyasugai,		// ���u���̎q���L�@-�i����-�v
/*5c*/	SPELL_5c_kaguya_life_spring_infinity,		// �_��u���C�t�X�v�����O�C���t�B�j�e�B�v
/*5d*/	SPELL_5d_kaguya_hourai_no_tama_no_eda01,	// ���u�H���̋ʂ̎}�@-���F�̒e��-�v
/*5e*/	SPELL_5e_kaguya_hourai_no_tama_no_eda02,	// �_��u�H���̋ʂ̎}�@-���F�̋�-�v
/*5f*/	SPELL_5f_kaguya_eiya_gaesi_yoake,			// �u�i��Ԃ��@�]�閾���]�v�iN�j
//
	SPELL_MAX,
};
//	SPELL_1f_silent_selena, 			/* [�p�`�F] �T�C�����g�Z���i �� �Ă��Ɨp */

#endif /* _SPELL_NAME_VALUE_H_ */
