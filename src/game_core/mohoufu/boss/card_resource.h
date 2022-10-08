
/*---------------------------------------------------------
	�J�[�h�ݒ�B
---------------------------------------------------------*/

typedef struct
{
	int spell_life; 							/* �J�[�h�ɓo�^���ꂽ���̗� */
	int spell_limit_time;						/* �J�[�h�̐������ԁB(�J�[�h�ɓo�^���ꂽ��莞��) */
//
	const char *spell_str_name; 				/* �J�[�h���� */
	int spell_set_number;						/* �J�[�h�̎�� */
//	/*(r36, NULL�͓o�^�ł��Ȃ��B�������Ȃ��ꍇ�� NULL_keitai ��o�^����B)*/
//	void (*spell_init_callback)(OBJ *sss);				/* �������ړ����� */
//	int spell_init_callback_flag;				/* �������ړ������ݒ�t���O[�p�~�\��](�����ł���Ă̓_���ŁA�X�y�JCPU���X�y�Jinit�ł��ׂ�) */
//	void (*boss_move_keitai_set_callback)(OBJ *sss);	/*(-r40) �{�X�ړ��`�ԑI������ */
	void (*boss_move_keitai_set_callback_void)(void);	/*(r41-) �{�X�ړ��`�ԑI������ */
	#if 0
	int spell_bonus_score;		/* �J�[�h���擾�����ꍇ�ɓ����链�_�B(20���`80�����x��z��B) */
	int spell_bonus_item;		/* �J�[�h���擾�����ꍇ�ɓ�����ITEM�B(�|����1up�o�����A���Ԑ؂ꂾ�Ɩ����Ƃ���ݒ�B) */
	#endif
} CARD_ADDRESS_RESOURCE;

/* �J�[�h����(==�P��[�t���[��])�́A64�{(==�P��[��1�b])���K�i */
#define s_time(aaa) (((int)(aaa))<<6)

/* �{�X�̗͒P�ʂ́A1024�{��P�ʂɂ��Ă݂�(-r35u1) */
//#define s_hp(aaa) (((int)(aaa))<<10)

/* �{�X�̗͒P�ʂ́A4096�{��P�ʂɂ��Ă݂�(r35u2-) */
#define s_hp(aaa) (((int)(aaa))<<12)

#if 0
	// 32�ŃQ�[�W1�{(r32)
	32768==1024*32==s_hp(32)
//
311296==32768*9.5
294912==32768*9.0
262144==32768*8.0
237568==32768*7.25
229376==32768*7.0
196608==32768*6.0
163840==32768*5.0
147456==32768*4.5
131072==32768*4.0
114688==32768*3.5
98304==32768*3.0
81920==32768*2.5
65536==32768*2.0
49152==32768*1.5
#endif


/* ��: �����̓e�L�g�[�ł��B */
#define void_kaiwa_00_keitai NULL_keitai_void
/*---------------------------------------------------------
	�X���u�A�C�V�N���t�H�[���v�����Ȃ��ŃJ�[�h�����B
---------------------------------------------------------*/

static CARD_ADDRESS_RESOURCE my_card_resource[CARD_ADDRESS_MAX] __attribute__((aligned(32))) =
{										// �ő唼�p��30�����B
//----------------------------------------
// (?) �X�e�[�W (�ꏊ�����m��)			"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(32*24),		s_time(1900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(32*24),		s_time(1900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(32*24),		s_time(1900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(32*24),		s_time(1900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
//	0
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* ��01�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* ��01�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* ��01�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* ��01�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
//	0
	{s_hp(16),			s_time(12), 	"�@�@�@�@�@���Áu�g�̖��@Lv.2�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��02�`��: ""*//* "���`��: " */
	{s_hp(18),			s_time(16), 	" �@�@�@�@���Áu�g�̖��@Lv.16�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��02�`��: ""*//* "���`��: " */
	{s_hp(16),			s_time(18), 	"�@�@�@�@���Áu�g�̖��@Lv.256�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��02�`��: ""*//* "���`��: " */
	{s_hp(14),			s_time(16), 	"�@�@�@���Áu�g�̖��@Lv.65536�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��02�`��: ""*//* "���`��: " */
//	0
	{s_hp(14),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��03�`��: ""*//* "��O�`��: " */
	{s_hp(24),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��03�`��: ""*//* "��O�`��: " */
	{s_hp(29),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��03�`��: ""*//* "��O�`��: " */
	{s_hp(34),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��03�`��: ""*//* "��O�`��: " */
//	0
	{s_hp(16),			s_time(40), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��04�`��: ""*//* "��l�`��: " */
	{s_hp(18),			s_time(40), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��04�`��: ""*//* "��l�`��: " */
	{s_hp(18),			s_time(20), 	"�@�@�@�@�@�@�@�O���u�F�O��ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��04�`��: ""*//* "��l�`��: " */
	{s_hp(22),			s_time(15), 	"�@�@�@�@�@�@�@�����u�F�،����v" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��04�`��: ""*//* "��l�`��: " */
//	0
	{s_hp(10),			s_time(60), 	" �@�@�@����u���쐬�J�[�hE05�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},	/* ��05�`��: ""*//* "��܌`��: " */
	{s_hp(12),			s_time(60), 	" �@�@�@����u���쐬�J�[�hN05�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},	/* ��05�`��: ""*//* "��܌`��: " */
	{s_hp(14),			s_time(60), 	" �@�@�@����u���쐬�J�[�hH05�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},	/* ��05�`��: ""*//* "��܌`��: " */
	{s_hp(14),			s_time(60), 	" �@�@�@����u���쐬�J�[�hL05�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},	/* ��05�`��: ""*//* "��܌`��: " */
//	0
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��06�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��06�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��06�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/* ��06�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
//	0
	{s_hp(12),			s_time(99), 	"�@�@�ؕ��u���남�ڂ��F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��07�`��: ""*//* "���`��: " */
	{s_hp(12),			s_time(99), 	"�@�@�@�@�@�@�@�Ǖ��u�R�_�n��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��07�`��: ""*//* "���`��: " */
	{s_hp(64),			s_time(99), 	"�@�@�@�@�Ǖ��u�V��V���̏ƚ��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��07�`��: ""*//* "���`��: " */
	{s_hp(64),			s_time(99), 	"�@�@�@�@�Ǖ��u�B��Ƒ��̏ƚ��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/* ��07�`��: ""*//* "���`��: " */
//	0
	{s_hp(64),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 								},	/* ��08�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��08�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��08�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��08�`��: ""*//* "��O�`��: " */
//	0
	{s_hp(14),			s_time(999),	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},	/* ��09�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},	/* ��09�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},	/* ��09�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},	/* ��09�`��: ""*//* "��l�`��: " */
//	0
	{s_hp(14),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},	/* ��10�`��: ""*//* "��܌`��: " */
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},	/* ��10�`��: ""*//* "��܌`��: " */
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},	/* ��10�`��: ""*//* "��܌`��: " */
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},	/* ��10�`��: ""*//* "��܌`��: " */
//	0
	{s_hp(14),			s_time(30), 	"�@�@�����u���^���t�@�e�B�[�O�v" "\n",	SPELL_32_pache_metal_fatigue,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��11�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�@�����u���^���t�@�e�B�[�O�v" "\n",	SPELL_32_pache_metal_fatigue,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��11�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�V���o�[�h���S���v" "\n",	SPELL_3a_pache_silver_dragon,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��11�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�V���o�[�h���S���v" "\n",	SPELL_3a_pache_silver_dragon,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��11�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
//	0
	{s_hp(14),			s_time(15), 	"�@�@�y���u���C�W�B�g�����g���v" "\n",	SPELL_31_pache_rage_tririton_1, 	spell_boss_move_system_01_taihi_ue_naka,			},	/* ��12�`��: ""*//* "���`��: " */
	{s_hp(20),			s_time(15), 	"�@�@�y���u���C�W�B�g�����g���v" "\n",	SPELL_31_pache_rage_tririton_1, 	spell_boss_move_system_01_taihi_ue_naka,			},	/* ��12�`��: ""*//* "���`��: " */
	{s_hp(20),			s_time(20), 	"�y���u���C�W�B�g�����g���㋉�v" "\n",	SPELL_35_pache_rage_tririton_2, 	spell_boss_move_system_01_taihi_ue_naka,			},	/* ��12�`��: ""*//* "���`��: " */
	{s_hp(20),			s_time(20), 	"�@�@�y���u�g�����g���V�F�C�N�v" "\n",	SPELL_39_pache_tririton_shake,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��12�`��: ""*//* "���`��: " */
//	0
	{s_hp(64),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 								},	/* ��13�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},	/* ��13�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},	/* ��13�`��: ""*//* "��O�`��: " */
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},	/* ��13�`��: ""*//* "��O�`��: " */
//	0
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* ��14�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* ��14�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* ��14�`��: ""*//* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* ��14�`��: ""*//* "��l�`��: " */
//	0
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* ��15�`��: ""*//* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* ��15�`��: ""*//* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* ��15�`��: ""*//* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* ��15�`��: ""*//* "��܌`��: " */
//	0
	{s_hp(14),			s_time(30), 	"�@�@�@�@�Ε��u�A�O�j�V���C���v" "\n",	SPELL_2e_pache_agni_shine_1,		spell_boss_move_system_03_x_douki,					},	/* ��16�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�@�Ε��u�A�O�j�V���C���㋉�v" "\n",	SPELL_33_pache_agni_shine_2,		spell_boss_move_system_02_xy_hidouki,				},	/* ��16�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�Ε��u�A�O�j���C�f�B�A���X�v" "\n",	SPELL_36_pache_agni_radiance,		spell_boss_move_system_02_xy_hidouki,				},	/* ��16�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(30), 	"�@�Ε��u�A�O�j���C�f�B�A���X�v" "\n",	SPELL_36_pache_agni_radiance,		spell_boss_move_system_02_xy_hidouki,				},	/* ��16�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
//	0
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��17�`��: ""*//* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��17�`��: ""*//* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��17�`��: ""*//* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��17�`��: ""*//* "���`��: " */
//	0
	{s_hp(14),			s_time(30), 	"�@�����u�v�����Z�X�E���f�B�l�v" "\n",	SPELL_2f_pache_princess_undine, 	spell_boss_move_system_04_xy_douki_differential32,	},	/* ��18�`��: ""*//* "��O�`��: " */
	{s_hp(20),			s_time(30), 	"�@�����u�v�����Z�X�E���f�B�l�v" "\n",	SPELL_2f_pache_princess_undine, 	spell_boss_move_system_04_xy_douki_differential32,	},	/* ��18�`��: ""*//* "��O�`��: " */
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�x���[�C�����C�N�v" "\n",	SPELL_37_pache_bury_in_lake,		spell_boss_move_system_04_xy_douki_differential32,	},	/* ��18�`��: ""*//* "��O�`��: " */
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�x���[�C�����C�N�v" "\n",	SPELL_37_pache_bury_in_lake,		spell_boss_move_system_02_xy_hidouki,				},	/* ��18�`��: ""*//* "��O�`��: " */
//	0
	{s_hp(12),			s_time(44), 	"���f�u���b�h�c�F�y�����̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* ��19�`��: ""*//* "��l�`��: " */
	{s_hp(15),			s_time(44), 	"���f�u�u���h�c�F�y�V���̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* ��19�`��: ""*//* "��l�`��: " */
	{s_hp(15),			s_time(44), 	"�j�f�u�u���h�c�F�y�V���̏j���v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* ��19�`��: ""*//* "��l�`��: " */
	{s_hp(15),			s_time(44), 	"���f�u�u���h�c�F�y�V���̋����v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* ��19�`��: ""*//* "��l�`��: " */
//	0
	{s_hp(19),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�X�l�[�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* ��20�`��: ""*//* "��܌`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* ��20�`��: ""*//* "��܌`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}���b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* ��20�`��: ""*//* "��܌`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�V�k�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* ��20�`��: ""*//* "��܌`��: " */
//	0
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* ��21�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* ��21�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* ��21�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* ��21�`��: ""*//* "���`��: " */ /* ����̍U����(�蓮�ݒ�)  500 160	*/
//	0
	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��22�`��: ""*//* "���`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��22�`��: ""*//* "���`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��22�`��: ""*//* "���`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��22�`��: ""*//* "���`��: " */
//	0
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* ��23�`��: ""*//* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* ��23�`��: ""*//* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* ��23�`��: ""*//* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* ��23�`��: ""*//* "��O�`��: " */
//	0
	{s_hp(7),			s_time(20), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_2c_sakuya_blue_red,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��24�`��: ""*//* "��l�`��: " */
	{s_hp(8),			s_time(20), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_2c_sakuya_blue_red,			spell_boss_move_system_04_xy_douki_differential32,	},	/* ��24�`��: ""*//* "��l�`��: " */
	{s_hp(6),			s_time(13), 	NULL, /* "�ʏ�U��"�����ԃi�C�t */		SPELL_44_remilia_rasen_knife,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��24�`��: ""*//* "��l�`��: " */
	{s_hp(6),			s_time(13), 	NULL, /* "�ʏ�U��"�����ԃi�C�t */		SPELL_44_remilia_rasen_knife,		spell_boss_move_system_01_taihi_ue_naka,			},	/* ��24�`��: ""*//* "��l�`��: " */
//	0
	{s_hp(12),			s_time(66), 	"�@���z�u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* ��25�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(66), 	"�@�����u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* ��25�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(66), 	"�@���t�u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* ��25�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(66), 	"�@�����u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* ��25�`��: ""*//* "��܌`��: " */
//	0
	{s_hp(12),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_02_xy_hidouki,				},	/* ��26�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_02_xy_hidouki,				},	/* ��26�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_02_xy_hidouki,				},	/* ��26�`��: ""*//* "��܌`��: " */
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_02_xy_hidouki,				},	/* ��26�`��: ""*//* "��܌`��: " */
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//	0.0
//----------------------------------------
// �`���m �G�L�X�g���X�e�[�W			"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*5+32*3.5),	s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
//	3.5
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* "���`��: " */	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* "���`��: " */	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* "���`��: " */	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_10_cirno, 					spell_boss_move_system_02_xy_hidouki,				},	/* "���`��: " */	/* ����̍U����(�蓮�ݒ�)  500 160	*/
//	3.0
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* "���`��: " */
	{s_hp(28),			s_time(60), 	"�@�@�X���u�A�C�V�N���t�H�[���v" "\n",	SPELL_1b_cirno_icecle_fall, 		spell_boss_move_system_01_taihi_ue_naka,			},	/* "���`��: " */
//	2.25
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* "��O�`��: " */
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_4d_rumia_3nerai,				spell_boss_move_system_02_xy_hidouki,				},	/* "��O�`��: " */
//	2.0
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "��l�`��: " */
	{s_hp(20),			s_time(24), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "��l�`��: " */
//	1.5
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(64),			s_time(60), 	"�ᕄ�u�_�C�A�����h�u���U�[�h�v" "\n",	SPELL_12_diamond_blizzard,			spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//	0.0
//----------------------------------------
	// ���easy�͒Z����ɒi�K�����Ȃ��B
// ��� 6�� 							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*12+32*2.0), s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5), s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5), s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5), s_time(900),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 73728==8192*9.0 */
//	9.5
	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_01_sakuya_misogi_normal,		spell_boss_move_system_04_xy_douki_differential32,	},	/* "���`��: �ʏ�U��(���E�ɓ������S�e����)"		*/	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_01_sakuya_misogi_normal,		spell_boss_move_system_04_xy_douki_differential32,	},	/* "���`��: �ʏ�U��(���E�ɓ������S�e����)"		*/	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_01_sakuya_misogi_normal,		spell_boss_move_system_04_xy_douki_differential32,	},	/* "���`��: �ʏ�U��(���E�ɓ������S�e����)"		*/	/* ����̍U����(�蓮�ݒ�)  500 160	*/
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_2d_sakuya_misogi_lunatic, 	spell_boss_move_system_04_xy_douki_differential32,	},	/* "���`��: �ʏ�U��(���E�ɓ������S�e����)"		*/	/* ����̍U����(�蓮�ݒ�)  500 160	*/
//	9.0
	{s_hp(9),			s_time(16), 	"�@�@��p�u�~�X�f�B���N�V�����v" "\n",	SPELL_28_sakuya_miss_direction, 	spell_boss_move_system_28_sakuya_miss_direction,	},	/* "���`��: ��p�u�~�X�f�B���N�V�����v(�S���ʁA���܂�)"	*/
	{s_hp(10),			s_time(16), 	"�@�@��p�u�~�X�f�B���N�V�����v" "\n",	SPELL_28_sakuya_miss_direction, 	spell_boss_move_system_28_sakuya_miss_direction,	},	/* "���`��: ��p�u�~�X�f�B���N�V�����v(�S���ʁA���܂�)"	*/
	{s_hp(11),			s_time(16), 	"��p�u���f�~�X�f�B���N�V�����v" "\n",	SPELL_28_sakuya_miss_direction, 	spell_boss_move_system_28_sakuya_miss_direction,	},	/* "���`��: ��p�u�~�X�f�B���N�V�����v(�S���ʁA���܂�)"	*/
	{s_hp(11),			s_time(16), 	"��p�u���f�~�X�f�B���N�V�����v" "\n",	SPELL_28_sakuya_miss_direction, 	spell_boss_move_system_28_sakuya_miss_direction,	},	/* "���`��: ��p�u�~�X�f�B���N�V�����v(�S���ʁA���܂�)"	*/
//	8.25	// bloody==�����炯�́B staind �X�e�C���h==�X�e���h==(�F��)�Ă��t��(�Ďc��)��B
	{s_hp(7),			s_time(20), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_2c_sakuya_blue_red,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��O�`��: " */
	{s_hp(8),			s_time(20), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_2c_sakuya_blue_red,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��O�`��: " */
	{s_hp(3),			s_time(11),		NULL, /* "�ʏ�U��"�����ԃi�C�t */		SPELL_44_remilia_rasen_knife,		spell_boss_move_system_01_taihi_ue_naka,			},	/* "��O�`��: (�e�X�g)" */
	{s_hp(3),			s_time(11),		NULL, /* "�ʏ�U��"�����ԃi�C�t */		SPELL_44_remilia_rasen_knife,		spell_boss_move_system_01_taihi_ue_naka,			},	/* "��O�`��: (�e�X�g)" */
//	8.0
	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��l�`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��l�`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��l�`��: " */
	{s_hp(13),			s_time(20), 	NULL, /* "�ʏ�U��"���Βe */			SPELL_2a_sakuya_baramaki1,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "��l�`��: " */
//	7.5 	// meek==�f���BVlad Draculea. Vlad Tepes.
	{s_hp(12),			s_time(44), 	"���f�u�u���h�c�F�y�V���̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(15),			s_time(44), 	"���f�u�u���h�c�F�y�V���̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(15),			s_time(44), 	"���f�u�u���h�c�F�y�V���̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	{s_hp(15),			s_time(44), 	"���f�u�u���h�c�F�y�V���̎􂢁v" "\n",	SPELL_42_remilia_vlad_tepes,		spell_boss_move_system_02_xy_hidouki,				},	/* "��܌`��: " */
	//
	{s_hp(19),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* "��Z�`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* "��Z�`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* "��Z�`��: " */
	{s_hp(22),			s_time(66), 	"�@�@�@�@�@�@�u���b�h�}�W�b�N�v" "\n",	SPELL_43_remilia_red_magic, 		spell_boss_move_system_02_xy_hidouki,				},	/* "��Z�`��: " */
//	6.5 	// �W���b�N�E�U�E���b�p�[==Jack the Ripper==�؂�􂫃W���b�N(�E�l�S)19���I(1888�N)�Ɏ���(?)/���ۖ������B���[���h�q�[���[�Y�B ���b�N==�X�v���b�^�[�n�E�X
	{s_hp(16),			s_time(20), 	"�@��u�W���b�N�E�K�[���b�N�v" "\n",	SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* "�掵�`��: (���U�����w)�ǉ��v�撆"	*/
	{s_hp(20),			s_time(20), 	"��p�u�W���b�N�E�U�E���b�p�[�v" "\n",	SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* "�掵�`��: (���U�����w)�ǉ��v�撆"	*/
	{s_hp(20),			s_time(20), 	"��p�u�W���b�N�E�U�E�r�[���Y�v" "\n",	SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* "�掵�`��: (���U�����w)�ǉ��v�撆"	*/
	{s_hp(20),			s_time(20), 	"����u�W���b�N�E�f�E�}���}�L�v" "\n",	SPELL_0c_sakuya_jack32, 			spell_boss_move_system_02_xy_hidouki,				},	/* "�掵�`��: (���U�����w)�ǉ��v�撆"	*/
//
	{s_hp(12),			s_time(20), 	NULL,									SPELL_2b_sakuya_baramaki2,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�攪�`��: �����w����"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_2b_sakuya_baramaki2,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�攪�`��: �����w����"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_2b_sakuya_baramaki2,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�攪�`��: �����w����"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_2b_sakuya_baramaki2,			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�攪�`��: �����w����"	*/
//	4.5
	{s_hp(12),			s_time(66), 	"�@���z�u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* "���`��: �ŏI�`��(����1)"	*/
	{s_hp(16),			s_time(66), 	"�@�����u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* "���`��: �ŏI�`��(����1)"	*/
	{s_hp(16),			s_time(66), 	"�@���t�u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* "���`��: �ŏI�`��(����1)"	*/
	{s_hp(16),			s_time(66), 	"�@�����u�t�F�X�e�B�o���i�C�t�v" "\n",	SPELL_45_sakuya_festival_knife, 	spell_boss_move_system_15_sakuya_festival_knife,	},	/* "���`��: �ŏI�`��(����1)"	*/
//	2.5
	{s_hp(12),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_16_sakuya_nazo_keitai,		},	/* "��10�`��: �ŏI�`��(����2)"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_16_sakuya_nazo_keitai,		},	/* "��10�`��: �ŏI�`��(����2)"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_16_sakuya_nazo_keitai,		},	/* "��10�`��: �ŏI�`��(����2)"	*/
	{s_hp(16),			s_time(20), 	NULL,									SPELL_0e_remilia_00,				spell_boss_move_system_16_sakuya_nazo_keitai,		},	/* "��10�`��: �ŏI�`��(����2)"	*/
//	0.5 	// "�{���u�����Ă��J�����Ȃ�����v"
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},	// (easy�͈�i�K���Ȃ��B�����ŏI������)
	{s_hp(64),			s_time(66), 	"�@�@���C�h�閧�u�c�s�s�׎蓖�v" "\n",	SPELL_0e_remilia_00,				spell_boss_move_system_17_sakuya_bimyou_idou,		},	/* "��11�`��: �ŏI�`��(����3)"	*/
	{s_hp(64),			s_time(66), 	"�@���C�h���u�����Ď��ʂ��v" "\n",	SPELL_0e_remilia_00,				spell_boss_move_system_17_sakuya_bimyou_idou,		},	/* "��11�`��: �ŏI�`��(����3)"	*/
	{s_hp(64),			s_time(66), 	"�@�@���C�h���X�u���������{�X�v" "\n",	SPELL_0e_remilia_00,				spell_boss_move_system_17_sakuya_bimyou_idou,		},	/* "��11�`��: �ŏI�`��(����3)"	*/
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//	0.25

//----------------------------------------
	// �p�`�Feasy�͒Z�����1�i�K���Ȃ��B
// A(�아)
// �p�`�FA 5��							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*2.00), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
//	5.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
//	4.0
	{s_hp(14),			s_time(30), 	"�@�@�@�@�Ε��u�A�O�j�V���C���v" "\n",	SPELL_2e_pache_agni_shine_1,		spell_boss_move_system_03_x_douki,					},
	{s_hp(20),			s_time(30), 	"�@�@�@�@�Ε��u�A�O�j�V���C���v" "\n",	SPELL_2e_pache_agni_shine_1,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�@�Ε��u�A�O�j�V���C���㋉�v" "\n",	SPELL_33_pache_agni_shine_2,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�@�Ε��u�A�O�j�V���C���㋉�v" "\n",	SPELL_33_pache_agni_shine_2,		spell_boss_move_system_02_xy_hidouki,				},
//	3.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
//	2.0
	{s_hp(14),			s_time(15), 	"�@�@�y���u���C�W�B�g�����g���v" "\n",	SPELL_31_pache_rage_tririton_1, 	spell_boss_move_system_01_taihi_ue_naka,			},	/*(�e�X�g)*/
	{s_hp(20),			s_time(15), 	"�y���u���C�W�B�g�����g���㋉�v" "\n",	SPELL_35_pache_rage_tririton_2, 	spell_boss_move_system_01_taihi_ue_naka,			},	/*(�e�X�g)*/
	{s_hp(20),			s_time(20), 	"�@�@�y���u�g�����g���V�F�C�N�v" "\n",	SPELL_39_pache_tririton_shake,		spell_boss_move_system_01_taihi_ue_naka,			},	/*(�e�X�g)*/
	{s_hp(20),			s_time(20), 	"�@�@�y���u�g�����g���V�F�C�N�v" "\n",	SPELL_39_pache_tririton_shake,		spell_boss_move_system_01_taihi_ue_naka,			},	/*(�e�X�g)*/
//	1.0
	{s_hp(14),			s_time(30), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
//	0.0
	{s_hp(14),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
//	0.0
	{s_hp(64),			s_time(60), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},	// (easy�͈�i�K���Ȃ��B�����ŏI������)
	{s_hp(64),			s_time(60), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(64),			s_time(60), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(64),			s_time(60), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//----------------------------------------
// B(����)
// �p�`�FB 5��							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*2.00), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
//	5.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
//	4.0
	{s_hp(14),			s_time(30), 	"�@�����u�v�����Z�X�E���f�B�l�v" "\n",	SPELL_2f_pache_princess_undine, 	spell_boss_move_system_04_xy_douki_differential32,	},
	{s_hp(20),			s_time(30), 	"�@�����u�v�����Z�X�E���f�B�l�v" "\n",	SPELL_2f_pache_princess_undine, 	spell_boss_move_system_04_xy_douki_differential32,	},
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�x���[�C�����C�N�v" "\n",	SPELL_37_pache_bury_in_lake,		spell_boss_move_system_04_xy_douki_differential32,	},
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�x���[�C�����C�N�v" "\n",	SPELL_37_pache_bury_in_lake,		spell_boss_move_system_02_xy_hidouki,				},
//	3.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
//	2.0
	{s_hp(14),			s_time(30), 	"�@�@�ؕ��u�V���t�B�z�����㋉�v" "\n",	SPELL_34_pache_sylphy_horn_2,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�ؕ��u�V���t�B�z�����㋉�v" "\n",	SPELL_34_pache_sylphy_horn_2,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�@�ؕ��u�O���[���X�g�[���v" "\n",	SPELL_38_pache_green_storm, 		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�@�ؕ��u�O���[���X�g�[���v" "\n",	SPELL_38_pache_green_storm, 		spell_boss_move_system_01_taihi_ue_naka,			},
//	1.0
	{s_hp(14),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
//	0.0
	{s_hp(14),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
//	0.0
	{s_hp(64),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},	// (easy�͈�i�K���Ȃ��B�����ŏI������)
	{s_hp(64),			s_time(60), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(64),			s_time(60), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(64),			s_time(60), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//----------------------------------------
// C(����)
// �p�`�FC 5��							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*2.00), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
//	5.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
//	4.0
	{s_hp(14),			s_time(30), 	"�@�@�@�@�ؕ��u�V���t�B�z�����v" "\n",	SPELL_30_pache_sylphy_horn_1,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�@�@�ؕ��u�V���t�B�z�����v" "\n",	SPELL_30_pache_sylphy_horn_1,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�ؕ��u�V���t�B�z�����㋉�v" "\n",	SPELL_34_pache_sylphy_horn_2,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�ؕ��u�V���t�B�z�����㋉�v" "\n",	SPELL_34_pache_sylphy_horn_2,		spell_boss_move_system_01_taihi_ue_naka,			},
//	3.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
//	2.0
	{s_hp(14),			s_time(30), 	"�@�@�@�@�Ε��u�A�O�j�V���C���v" "\n",	SPELL_2e_pache_agni_shine_1,		spell_boss_move_system_03_x_douki,					},
	{s_hp(20),			s_time(30), 	"�@�@�Ε��u�A�O�j�V���C���㋉�v" "\n",	SPELL_33_pache_agni_shine_2,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�Ε��u�A�O�j���C�f�B�A���X�v" "\n",	SPELL_36_pache_agni_radiance,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�Ε��u�A�O�j���C�f�B�A���X�v" "\n",	SPELL_36_pache_agni_radiance,		spell_boss_move_system_02_xy_hidouki,				},
//	1.0
	{s_hp(14),			s_time(30), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�؁��Ε��u�t�H���X�g�u���C�Y�v" "\n",	SPELL_3c_pache_forest_blaze,		spell_boss_move_system_01_taihi_ue_naka,			},
//	0.0
	{s_hp(14),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
//	0.0
	{s_hp(64),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},	// (easy�͈�i�K���Ȃ��B�����ŏI������)
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(64),			s_time(60), 	"�΁��y���u���[���@�N�������N�v" "\n",	SPELL_3b_pache_lava_cromlech,		spell_boss_move_system_02_xy_hidouki,				},
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//----------------------------------------
// D(����)
// �p�`�FD 5��							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*2.00), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75), s_time(800),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 40960==8192*5.0 */
//	5.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_40_PACHE_LASER1,				spell_boss_move_system_02_xy_hidouki,				},
//	4.0
	{s_hp(14),			s_time(15), 	"�@�@�y���u���C�W�B�g�����g���v" "\n",	SPELL_31_pache_rage_tririton_1, 	spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(15), 	"�@�@�y���u���C�W�B�g�����g���v" "\n",	SPELL_31_pache_rage_tririton_1, 	spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(20), 	"�y���u���C�W�B�g�����g���㋉�v" "\n",	SPELL_35_pache_rage_tririton_2, 	spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(20), 	"�y���u���C�W�B�g�����g���㋉�v" "\n",	SPELL_35_pache_rage_tririton_2, 	spell_boss_move_system_01_taihi_ue_naka,			},
//	3.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_41_PACHE_LASER2,				spell_boss_move_system_02_xy_hidouki,				},
//	2.0
	{s_hp(14),			s_time(30), 	"�@�@�����u���^���t�@�e�B�[�O�v" "\n",	SPELL_32_pache_metal_fatigue,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�����u���^���t�@�e�B�[�O�v" "\n",	SPELL_32_pache_metal_fatigue,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�V���o�[�h���S���v" "\n",	SPELL_3a_pache_silver_dragon,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(20),			s_time(30), 	"�@�@�@�����u�V���o�[�h���S���v" "\n",	SPELL_3a_pache_silver_dragon,		spell_boss_move_system_01_taihi_ue_naka,			},
//	1.0
	{s_hp(14),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�y�������u�G�������h���K���X�v" "\n",	SPELL_3f_pache_emerald_megalith,	spell_boss_move_system_02_xy_hidouki,				},
//	0.0
	{s_hp(14),			s_time(999),	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(20),			s_time(30), 	"�@�����ؕ��u�E�H�[�^�[�G���t�v" "\n",	SPELL_3d_pache_water_elf,			spell_boss_move_system_02_xy_hidouki,				},
//	0.0
	{s_hp(64),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},	// (easy�͈�i�K���Ȃ��B�����ŏI������)
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(64),			s_time(60), 	"���������u�}�[�L�����|�C�Y���v" "\n",	SPELL_3e_pache_mercury_poison,		spell_boss_move_system_01_taihi_ue_naka,			},
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},

//----------------------------------------
//	SPELL_15_aya_misogi
//	SPELL_25_houka_kenran			/*aya_02_keitai*/
//	SPELL_23_meirin_magaru_kunai	/*aya_01_keitai*/

// �� 4��								"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	//																												/*�{�X�o��O�̏�����[��b�̑O]*/
	{s_hp(4*7+32*3),	s_time(600),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 32768=32768.0 */
	//	4.0 																										/*�{�X�퓬�O�̏�����[��b�̌�]*/
	{s_hp(16),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_20_aya_misogi1,				spell_boss_move_system_03_x_douki,					},	/*(4)*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_20_aya_misogi1,				spell_boss_move_system_03_x_douki,					},	/*(4)*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_20_aya_misogi1,				spell_boss_move_system_03_x_douki,					},	/*(4)*/
	{s_hp(20),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_20_aya_misogi1,				spell_boss_move_system_03_x_douki,					},	/*(4)*/
	//	3.5
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)*/
	{s_hp(22),			s_time(30), 	"�@�@�@�@�@�@�@�򕄁u�V�̔��ˁv" "\n",	SPELL_22_ame_no_yatimata,			spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)*/
	//	3.0
	{s_hp(14),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_21_aya_misogi2,				spell_boss_move_system_03_x_douki,					},	/*(5)"�򕄁u���쐬�J�[�h001�v"*/
	{s_hp(16),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_21_aya_misogi2,				spell_boss_move_system_03_x_douki,					},	/*(5)"�򕄁u���쐬�J�[�h001�v"*/
	{s_hp(16),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_21_aya_misogi2,				spell_boss_move_system_03_x_douki,					},	/*(5)"�򕄁u���쐬�J�[�h001�v"*/
	{s_hp(16),			s_time(20), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_21_aya_misogi2,				spell_boss_move_system_03_x_douki,					},	/*(5)"�򕄁u���쐬�J�[�h001�v"*/
	//	2.5
	{s_hp(8),			s_time(40), 	"�@�@�@�@�@�@�E���u�n����D�]�v" "\n",	SPELL_24_aya_doll,					spell_boss_move_system_03_x_douki,					},	/*(4)"�򕄁u���쐬�J�[�h002�v"*/
	{s_hp(8),			s_time(40), 	"�@�@�@�@�@�����u�n���卪��Q�v" "\n",	SPELL_24_aya_doll,					spell_boss_move_system_03_x_douki,					},	/*(4)"�򕄁u���쐬�J�[�h002�v"*/
	{s_hp(8),			s_time(30), 	"�@�@�@�@�@�@�ߏ�u�R�����Q�v" "\n",	SPELL_24_aya_doll,					spell_boss_move_system_03_x_douki,					},	/*(4)"�򕄁u���쐬�J�[�h002�v"*/
	{s_hp(8),			s_time(30), 	"�@�@�@�@�@��ʁu�����\\���ۉ߁v" "\n", SPELL_24_aya_doll,					spell_boss_move_system_03_x_douki,					},	/*(4)"�򕄁u���쐬�J�[�h002�v"*/
	//	2.0
	{s_hp(12),			s_time(66), 	"�@�@�@�@�@�@�@�����u�����R�l�v" "\n",	SPELL_4f_aya_taifu, 				spell_boss_move_system_13_aya_taifu,				},	/*(5)"�򕄁u���쐬�J�[�h003�v"*/
	{s_hp(14),			s_time(77), 	"�@�@�@�@�@�@�����u�����R�R�l�v" "\n",	SPELL_4f_aya_taifu, 				spell_boss_move_system_13_aya_taifu,				},	/*(5)"�򕄁u���쐬�J�[�h003�v"*/
	{s_hp(18),			s_time(88), 	"�@�@�@�@�@�@�����u�����X�W�l�v" "\n",	SPELL_4f_aya_taifu, 				spell_boss_move_system_13_aya_taifu,				},	/*(5)"�򕄁u���쐬�J�[�h003�v"*/
	{s_hp(20),			s_time(99), 	"�@�@�@�@�@�@�����u�������蒆�v" "\n",	SPELL_4f_aya_taifu, 				spell_boss_move_system_13_aya_taifu,				},	/*(5)"�򕄁u���쐬�J�[�h003�v"*/
	//	1.5
	{s_hp(20),			s_time(99), 	"�@�@�@�@�@�@�H���u�����̒��ׁv" "\n",	SPELL_1d_amefuri_test,				spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)"�򕄁u���쐬�J�[�h004�v"*/
	{s_hp(20),			s_time(99), 	"�@�@�@�@�@�@�H���u����̒��ׁv" "\n",	SPELL_1d_amefuri_test,				spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)"�򕄁u���쐬�J�[�h004�v"*/
	{s_hp(20),			s_time(99), 	"�@�@�@�@�@�@�H���u�Ӌ|�̒��ׁv" "\n",	SPELL_1d_amefuri_test,				spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)"�򕄁u���쐬�J�[�h004�v"*/
	{s_hp(20),			s_time(99), 	"�@�@�@�@�ǐՁu�R�����{�̒��ׁv" "\n",	SPELL_1d_amefuri_test,				spell_boss_move_system_01_taihi_ue_naka,			},	/*(4)"�򕄁u���쐬�J�[�h004�v"*/
	//	1.0
	{s_hp(12),			s_time(99), 	"�@�@�ؕ��u���남�ڂ��F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},	/*(5)*/
	{s_hp(12),			s_time(99), 	"�@�@�@�@�@�@�@�Ǖ��u�R�_�n��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/*(5)*/
	{s_hp(64),			s_time(99), 	"�@�@�@�@�Ǖ��u�V��V���̏ƚ��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/*(5)*/
	{s_hp(64),			s_time(99), 	"�@�@�@�@�Ǖ��u�V��V���̏ƚ��v" "\n",	SPELL_26_aya_saifu, 				spell_boss_move_system_01_taihi_ue_naka,			},	/*(5)*/
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	//	0.5
	//	0.0

//----------------------------------------
//	SPELL_49_kaguya111		�{�X�s���A�� 1�`��
//	SPELL_4a_kaguya222		�{�X�s���A�� 4�`��
	// 3�ʃ{�X�Aeasy�͂��������ȒP�ɁB���͂���Ȃ�ɁB
// �P�� 3�� 							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*2.0),	s_time(500),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 28672==8192*3.5 */
	{s_hp(4*7+32*3.0),	s_time(500),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 28672==8192*3.5 */
	{s_hp(4*7+32*3.5),	s_time(500),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 28672==8192*3.5 */
	{s_hp(4*7+32*4.0),	s_time(500),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 28672==8192*3.5 */
	// 3.5 �{�X�ʏ�U������1�i�H���R �P��j
//	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_48_kaguya000, 						spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
//	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_48_kaguya000, 						spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
//	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_48_kaguya000, 						spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
//	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_48_kaguya000, 						spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_51_kaguya_tujyou_kougeki_01,			spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_51_kaguya_tujyou_kougeki_01,			spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_51_kaguya_tujyou_kougeki_01,			spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
	{s_hp(12),			s_time(20), 	NULL, /* "�ʏ�U��1" "\n"*/ 			SPELL_51_kaguya_tujyou_kougeki_01,			spell_boss_move_system_11_kaguya_yureru,			}, // ����(5)�҂�e�A�ԁA�B���@�_���A�e(8)��18�Z�b�g(�b)���炢(�n�߂�5�b�͏o���Ȃ�)�B(�P����Ԋu�ňړ��A�I���㒆���ֈړ�)
	// 3.0
	{s_hp(10),			s_time(30), 	" ���u������̋� �ܐF�̒e�ہv" "\n",	SPELL_49_kaguya111, 						spell_boss_move_system_11_kaguya_yureru,			}, // 1.������̋�	(�P�钆���Œ�A�Ԏ��Ή��̊ےe�A�Z���[�U�[)4�Z�b�gx ���u������̋ʁ@�]�ܐF�̒e�ہ]�v�iE/N�j
	{s_hp(12),			s_time(30), 	" ���u������̋� �ܐF�̒e�ہv" "\n",	SPELL_49_kaguya111, 						spell_boss_move_system_11_kaguya_yureru,			}, // 1.������̋�	(�P�钆���Œ�A�Ԏ��Ή��̊ےe�A�Z���[�U�[)4�Z�b�gx ���u������̋ʁ@�]�ܐF�̒e�ہ]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"�@�_��u�u�����A���g�h���S���v" "\n",	SPELL_49_kaguya111, 						spell_boss_move_system_11_kaguya_yureru,			}, // 1.������̋�	(�P�钆���Œ�A�Ԏ��Ή��̊ےe�A�Z���[�U�[)4�Z�b�gx �_��u�u�����A���g�h���S���o���b�^�v�iH/L�j
	{s_hp(12),			s_time(30), 	"�@�_��u�u�����A���g�h���S���v" "\n",	SPELL_49_kaguya111, 						spell_boss_move_system_11_kaguya_yureru,			}, // 1.������̋�	(�P�钆���Œ�A�Ԏ��Ή��̊ےe�A�Z���[�U�[)4�Z�b�gx �_��u�u�����A���g�h���S���o���b�^�v�iH/L�j
	// 1.5
	{s_hp(12),			s_time(40), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������2
	{s_hp(16),			s_time(40), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������2
	{s_hp(16),			s_time(40), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������2
	{s_hp(16),			s_time(40), 	NULL, /* "�ʏ�U��2" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������2
	// 2.5
	{s_hp(10),			s_time(30), 	"���u���̌�΂̔��ӂ��ʈӎu�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 2.���̌�΂̔� ���u���̌�΂̔��@�]�ӂ��ʈӎu�]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"���u���̌�΂̔��ӂ��ʈӎu�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 2.���̌�΂̔� ���u���̌�΂̔��@�]�ӂ��ʈӎu�]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"�_��u�u�f�B�X�g�_�C�A�����h�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 2.���̌�΂̔� �_��u�u�f�B�X�g�_�C�A�����h�v�iH/L�j
	{s_hp(12),			s_time(30), 	"�_��u�u�f�B�X�g�_�C�A�����h�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 2.���̌�΂̔� �_��u�u�f�B�X�g�_�C�A�����h�v�iH/L�j
	// �{�X�ʏ�U������3
	{s_hp(12),			s_time(30), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_57_kaguya_tujyou_kougeki_03,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������3
	{s_hp(16),			s_time(30), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_57_kaguya_tujyou_kougeki_03,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������3
	{s_hp(16),			s_time(30), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_57_kaguya_tujyou_kougeki_03,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������3
	{s_hp(16),			s_time(30), 	NULL, /* "�ʏ�U��3" "\n"*/ 			SPELL_57_kaguya_tujyou_kougeki_03,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������3
	// 2.0
	{s_hp(10),			s_time(30), 	" �@���u�Αl�̔�� �ł�ʐS�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 3.�Αl�̔�� ���u�Αl�̔�߁@�]�ł�ʐS�]�v�iE/N�j
	{s_hp(12),			s_time(30), 	" �@���u�Αl�̔�� �ł�ʐS�v" "\n",	SPELL_4a_kaguya222,/*(r41�_��)*/			spell_boss_move_system_12_kaguya_funya_idou,		}, // 3.�Αl�̔�� ���u�Αl�̔�߁@�]�ł�ʐS�]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"�@�_��u�T���}���_�[�V�[���h�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 3.�Αl�̔�� �_��u�T���}���_�[�V�[���h�v�iH/L�j
	{s_hp(12),			s_time(30), 	"�@�_��u�T���}���_�[�V�[���h�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_12_kaguya_funya_idou,		}, // 3.�Αl�̔�� �_��u�T���}���_�[�V�[���h�v�iH/L�j
	// �{�X�ʏ�U������4
	{s_hp(10),			s_time(30), 	NULL, /* "�ʏ�U��4" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������4
	{s_hp(12),			s_time(30), 	NULL, /* "�ʏ�U��4" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������4
	{s_hp(12),			s_time(30), 	NULL, /* "�ʏ�U��4" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������4
	{s_hp(12),			s_time(30), 	NULL, /* "�ʏ�U��4" "\n"*/ 			SPELL_54_kaguya_tujyou_kougeki_02,			spell_boss_move_system_11_kaguya_yureru,			}, // �{�X�ʏ�U������4
	// 1.5
	{s_hp(10),			s_time(30), 	" �@�@���u���̎q���L �i�����v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_11_kaguya_yureru,			}, // 4.���̎q���L ���u���̎q���L�@�]�i�����]�v�iE/N�j
	{s_hp(12),			s_time(30), 	" �@�@���u���̎q���L �i�����v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_11_kaguya_yureru,			}, // 4.���̎q���L ���u���̎q���L�@�]�i�����]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"�@�_��u���C�t�C���t�B�j�e�B�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_11_kaguya_yureru,			}, // 4.���̎q���L �_��u���C�t�X�v�����O�C���t�B�j�e�B�v�iH/L�j
	{s_hp(12),			s_time(30), 	"�@�_��u���C�t�C���t�B�j�e�B�v" "\n",	SPELL_4a_kaguya222, 						spell_boss_move_system_11_kaguya_yureru,			}, // 4.���̎q���L �_��u���C�t�X�v�����O�C���t�B�j�e�B�v�iH/L�j
	// 1.0
	{s_hp(10),			s_time(30), 	"���u�H���̋ʂ̎}���F�̒e���v" "\n",	SPELL_4b_kakuya333_tamanoe, 				spell_boss_move_system_01_taihi_ue_naka,			}, // 5.�H���̋ʂ̎} ���u�H���̒e�̎}�@�]���F�̒e���]�v�iE/N�j
	{s_hp(12),			s_time(30), 	"���u�H���̋ʂ̎}���F�̒e���v" "\n",	SPELL_4b_kakuya333_tamanoe, 				spell_boss_move_system_01_taihi_ue_naka,			}, // 5.�H���̋ʂ̎} ���u�H���̒e�̎}�@�]���F�̒e���]�v�iE/N�j
	{s_hp(12),			s_time(30), 	" �_��u�H���̋ʂ̎} ���F�̋��v" "\n",	SPELL_4b_kakuya333_tamanoe, 				spell_boss_move_system_01_taihi_ue_naka,			}, // 5.�H���̋ʂ̎} �_��u�H���̋ʂ̎}�@�]���F�̋��]�v�iH/L�j
	{s_hp(12),			s_time(30), 	" �_��u�H���̋ʂ̎} ���F�̋��v" "\n",	SPELL_4b_kakuya333_tamanoe, 				spell_boss_move_system_01_taihi_ue_naka,			}, // 5.�H���̋ʂ̎} �_��u�H���̋ʂ̎}�@�]���F�̋��]�v�iH/L�j
	// 0.5
	{s_hp(32),			s_time(30), 	" �@�@�@�@�@�@�u�i��Ԃ� ���Ɂv" "\n",	SPELL_4c_kakuya_tamanoe_bbb,				spell_boss_move_system_01_taihi_ue_naka,			}, //�u�i��Ԃ��@�]���Ɂ]�v�iE�j
	{s_hp(32),			s_time(30), 	" �@�@�@�@�@�u�i��Ԃ� �閾���v" "\n",	SPELL_4c_kakuya_tamanoe_bbb,				spell_boss_move_system_01_taihi_ue_naka,			}, //�u�i��Ԃ��@�]�閾���]�v�iN�j
	{s_hp(40),			s_time(30), 	" �@�@�@�u�i��Ԃ� �����̖����v" "\n",	SPELL_4c_kakuya_tamanoe_bbb,				spell_boss_move_system_01_taihi_ue_naka,			}, //�u�i��Ԃ��@�]�����̖����]�v�iH�j
	{s_hp(56),			s_time(30), 	" �@�@�@�@�@�u�i��Ԃ� �閾���v" "\n",	SPELL_4c_kakuya_tamanoe_bbb,				spell_boss_move_system_01_taihi_ue_naka,			}, //�u�i��Ԃ��@�]�������]�v�iL�j
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,									void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,									void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,									void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,									void_gekiha_keitai, 	/*[���j]*/					},
//----------------------------------------
	// 2�ʃ{�X�Ȃ̂ŁA�K���ɈՂ����B
// ���� 2�� 							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*1.4),	s_time(400),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+16), s_time(400),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+36), s_time(400),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+46), s_time(400),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,									void_kaiwa_00_keitai,								},	/* 20480==8192*2.5 */
	// 2.000 (12==32*0.375) // easy(3) �₽��Z���͓̂����Ŏ���Ńp���[�_�E����z�肵�Ă���B�p���[�_�E���Ȃ̂Œe�͂��Ȃ����A�̗͂��ɒ[�ɏ��Ȃ��̂Ŏ��̒i�K�ɑ����ڍs�����e�����ɂȂ���B
	{s_hp(7),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_47_mima_toge, 				spell_boss_move_system_10_mima_keitai,				},
	{s_hp(10),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_47_mima_toge, 				spell_boss_move_system_10_mima_keitai,				},
	{s_hp(10),			s_time(30), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_47_mima_toge, 				spell_boss_move_system_10_mima_keitai,				},
	{s_hp(10),			s_time(40), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_47_mima_toge, 				spell_boss_move_system_10_mima_keitai,				},
	// 2.--
	{s_hp(9),			s_time(22), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_27_hosigata_test, 			spell_boss_move_system_10_mima_keitai,				},
	{s_hp(16),			s_time(44), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_27_hosigata_test, 			spell_boss_move_system_10_mima_keitai,				},
	{s_hp(30),			s_time(66), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_27_hosigata_test, 			spell_boss_move_system_10_mima_keitai,				},
	{s_hp(20),			s_time(99), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_27_hosigata_test, 			spell_boss_move_system_10_mima_keitai,				},
	// 1.625
	{s_hp(14),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(24),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(29),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(34),			s_time(40), 	"�@�@�ŕ��u�f�B�}�[�P�C�V�����v" "\n",	SPELL_29_rumia_demarcation, 		spell_boss_move_system_01_taihi_ue_naka,			},
	// 1.00
	{s_hp(26),			s_time(40), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_23_meirin_magaru_kunai,		spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(24),			s_time(40), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_23_meirin_magaru_kunai,		spell_boss_move_system_02_xy_hidouki,			},
	{s_hp(28),			s_time(30), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_23_meirin_magaru_kunai,		spell_boss_move_system_02_xy_hidouki,			},
	{s_hp(44),			s_time(20), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_23_meirin_magaru_kunai,		spell_boss_move_system_02_xy_hidouki,			},
	// 1.--
	{s_hp(16),			s_time(40), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(18),			s_time(40), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(18),			s_time(20), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(22),			s_time(15), 	"�@�@�@�@�@�@�@�ؕ��u�F�؈�ࣁv" "\n",	SPELL_25_houka_kenran,				spell_boss_move_system_01_taihi_ue_naka,			},
	// 1.--
	{s_hp(10),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(12),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(14),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},
	{s_hp(14),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	SPELL_18_hana_test, 				spell_boss_move_system_02_xy_hidouki,				},
	// 1.0
	{s_hp(36),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	/**/SPELL_09_test_inuno_fuguri,		spell_boss_move_system_02_xy_hidouki,				}, // ����B
	{s_hp(36),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	/**/SPELL_19_meirin_5_houkou,		spell_boss_move_system_01_taihi_ue_naka,				}, // ����B
	{s_hp(36),			s_time(60), 	"�@�@�@�@�@����u���쐬�J�[�h�v" "\n",	/**/SPELL_19_meirin_5_houkou,		spell_boss_move_system_01_taihi_ue_naka,				}, // ����B
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					}, // (Lunatic �͈�i�K���Ȃ��B�����ŏI������)
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//----------------------------------------
	// 1�ʃ{�X�Ȃ̂ŁA(���Ȃ��Ƃ� easy�Anormal �������)����o���Ȃ��B
// �A���X 1��							"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
	{s_hp(4*7+32*0.75), s_time(300),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 16384==8192*2 */ /* "�ʏ�U��"�̎���(?)*/ /* "�ʏ�U��"�̃��C�t */
	{s_hp(4*7+32*0.75), s_time(300),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 16384==8192*2 */ /* "�ʏ�U��"�̎���(?)*/ /* "�ʏ�U��"�̃��C�t */
	{s_hp(4*7+32*1.00), s_time(300),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 16384==8192*2 */ /* "�ʏ�U��"�̎���(?)*/ /* "�ʏ�U��"�̃��C�t */
	{s_hp(4*7+32*1.25), s_time(300),	NULL, /* "�`�ԕύX" "\n"*/				SPELL_00,							void_kaiwa_00_keitai,								},	/* 16384==8192*2 */ /* "�ʏ�U��"�̎���(?)*/ /* "�ʏ�U��"�̃��C�t */
	// 1.25 easy(10) ������[F]�o��̂ŁA�p���[�͖��Ȃ��B�܂��n�߂ɒe���͊ȒP�Ƃ������Ɋ���Ă��炤�ׁA���߁B(easy �̓v���C���[�Ɏ���ł�����Ă͍���̂ŁA�{�X�Ɛ�����C�ɂ�����̂����)
	/*(r39, [�A���X�ʏ�U�����ۂ��e�X�g]�����e�Ȃ̂ŁA�b���œ�Փx��������Beasy�͌��邾���Anormal��5�b���炢������B�ȉ������Ȃ�B)*/
	{s_hp(7),			s_time(11), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_09_test_inuno_fuguri, 		spell_boss_move_system_01_taihi_ue_naka,			}, // ���炩�ɊȒP�Ȓe��
	{s_hp(10),			s_time(12), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_14_alice_youmu300,			spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(9),			s_time(12), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_14_alice_youmu300,			spell_boss_move_system_01_taihi_ue_naka,			},
	{s_hp(8),			s_time(12), 	NULL, /* "�ʏ�U��" "\n"*/				SPELL_14_alice_youmu300,			spell_boss_move_system_01_taihi_ue_naka,			},
	// 1.--
	{s_hp(16),			s_time(12), 	"�@�@�@�@�@���Áu�g�̖��@Lv.2�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_01_taihi_ue_naka,			},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(18),			s_time(16), 	" �@�@�@�@���Áu�g�̖��@Lv.16�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_01_taihi_ue_naka,			},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(16),			s_time(18), 	"�@�@�@�@���Áu�g�̖��@Lv.256�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(14),			s_time(16), 	"�@�@�@���Áu�g�̖��@Lv.65536�v" "\n",	SPELL_15_alice_aka_2nd, 			spell_boss_move_system_04_xy_douki_differential32,	},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	// 1.-- easy(4) �u�p�[�t�F�N�g�t���[�Y�v�͈��̎��̗�������ׁA���S�Ҍ����ł͖����B
	{s_hp(8),			s_time(20), 	" �@�@ ����u�J�[�h��̂Ă��Ɓv" "\n",	SPELL_44_ruiz3_test/*SPELL_44_ruiz3_test*/,				spell_boss_move_system_02_xy_hidouki,				},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(10),			s_time(20), 	"�@�����u�p�[�t�F�N�g�t���[�Y�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(12),			s_time(30), 	"�@�����u�p�[�e�B�N���t���[�N�v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	{s_hp(16),			s_time(20), 	"�@�����u�u���U�[�h�t���[�Y���v" "\n",	SPELL_11_perfect_freeze,			spell_boss_move_system_02_xy_hidouki,				},	/* "�����u�M���̕������l�`�v"�̃��C�t */
	// 1.00
	{s_hp(64),			s_time(40), 	"�@�����u�����̃}�g�����[�V�J�v" "\n",	SPELL_16_alice_zako_doll,			spell_boss_move_system_02_xy_hidouki,				},	/* " �@�����u�����̃}�g�����[�V�J�v"�����u�����̉~�J�l�`�v */	// (r33p)boss_move_04_xy_douki_differential
	{s_hp(64),			s_time(60), 	"�@�����u�M���̃}�g�����[�V�J�v" "\n",	SPELL_16_alice_zako_doll,			spell_boss_move_system_02_xy_hidouki,				},	/* " �@�����u�M���̃}�g�����[�V�J�v"�����u�����̉~�J�l�`�v */	// (r33p)boss_move_04_xy_douki_differential
	{s_hp(64),			s_time(120),	"�@�����u�����̃}�g�����[�V�J�v" "\n",	SPELL_16_alice_zako_doll,			spell_boss_move_system_02_xy_hidouki,				},	/* " �@�����u�����̃}�g�����[�V�J�v"�����u�����̉~�J�l�`�v */	// (r33p)boss_move_04_xy_douki_differential
	{s_hp(80),			s_time(77), 	"�@�����u���Q�̃}�g�����[�V�J�v" "\n",	SPELL_16_alice_zako_doll,			spell_boss_move_system_02_xy_hidouki,				},	/* " �@�����u���Q�̃}�g�����[�V�J�v"�����u�����̉~�J�l�`�v */	// (r33p)boss_move_04_xy_douki_differential
// r36 �ԕ�(�������j�B�c��{�XHP����炠���Ă��A�{�X�|���B)
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
	{s_hp(12),			s_time(99), 	NULL,									SPELL_00,							void_gekiha_keitai, 	/*[���j]*/					},
//										"eeddccbbaa99887766554433221100", '\n\0' ���[�N������o�b�t�@�������ꂾ�������p�ӂ��Ȃ��\��Ȃ̂ŁA���ӂꂽ�玚���o�Ȃ��B */
};
	/*
	�}�g�����[�V�J�́A�I�����l�`�ł����̂��ȁH�l�`�Ƃ�������薯�|�i�̎����B
	�ŋ߂͖G���}�g�����[�V�J�̎��v�����{���炠��炵���B
	//
	���{�̋C�ے��͕���17m�ȏ�̕����u�䕗�v�ƒ�`�B
	���ۋC�ۋ@��(WMO)�ł͕���33m�ȏ�̂��̂��utyphoon�v�ƒ�`�B����ȉ��́ustorm�v�B
	*/
