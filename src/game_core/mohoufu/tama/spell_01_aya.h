
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�˖��� ���̃J�[�h���`���܂��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	��	�ʏ�U��1
	-------------------------------------------------------
		��(12)�e
		��(12)�e
		��(12)�e
	-------------------------------------------------------
	�Ƃ肠�����A�܂��������ĂȂ��B
	�Ƃ������A�܂������Ⴄ�B
	�u�ʏ�U��1�v�͂悭�킩��Ȃ��B�̂ŁA�F�X�ς����Ⴄ�Ǝv���B
	-------------------------------------------------------
	�g�p���W�X�^
	R02 	j	(���[�v�ϐ�)
	R03 	i	(���[�v�ϐ�)
	R06 	�󂯓n�����W�X�^	�e��X���W		���e�ʒu ���Wx
	R07 	�󂯓n�����W�X�^	�e��Y�e��		���e�ʒu ���Wy
	�g�p���W�X�^
	R08 	�J�E���^�B			(16���1��) ���e
	R09 	aaa_angle65536
	R0a 	bbb_angle65536
	R0b 	���񂾂�傫���Ȃ�~�̔��a�B
	R0c 	���p�J�E���^�B(48���1��) �����B
	-------------------------------------------------------
	R0d 	ccc_angle65536		����i���[�v�ł̊�p�x(0, 32768, 65536)
---------------------------------------------------------*/

local SPELL_EXEC(15_aya_misogi1)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 16, R08, NAX),
		NAX
	};
//	if ((0x08)==(VR10_BOSS_SPELL_TIMER & 0x0f))/* (16���1��)(16�񖈂ɔ��e) */
	cpu_exec((u32*)&codebase111, (1));//	/* (16���1��)(16�񖈂ɔ��e) */
	if (1==VR08) /* (16���1��) ���e */
	{
		static const u32 codebase222[4] =
		{
			// (03) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
			// (04) /
			//	const u32 VR0b = (((~(VR10_BOSS_SPELL_TIMER))>>3)&0x1f);/* �e�L�g�[�ɑ傫�����Ă݂�B */
			MCODE(OP0x02_COUNTER, 24, R0b, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (2));//		/*(r34, 32)*/
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* ���(�����12�e) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/NUM_12_OF_CIRCLE_ONE))/* ��� */
		{
			static const u32 codebase444[45] =
			{
				//	VR06 += (sin65536((VR02_j))*(16));			/* �e��x256 */
				//	VR07 += (cos65536((VR02_j))*(16));			/* �e��y256 */
				//	VR06 += ((si n65536((VR02_j))*((16+(VR0b)))));/*fps_factor*/	/* �e��x256 */	/* CCW�̏ꍇ */
				//	VR07 += ((co s65536((VR02_j))*((16+(VR0b)))));/*fps_factor*/	/* �e��y256 */
				//	VR06 += ((si n1024((deg65536to1024(VR02_j)))*((16+(VR0b)))));/*fps_factor*/ 	/* �e��x256 */	/* CCW�̏ꍇ */
				//	VR07 += ((co s1024((deg65536to1024(VR02_j)))*((16+(VR0b)))));/*fps_factor*/ 	/* �e��y256 */
				// HATSUDAN_R11_speed256	= (t256(12 + VR0b)); //= ((12+(VR0b)) << 8);	/*(r34, 16)*/
				// (00) VR11 = VR0b + (12); 	/* �e�� */
				MCODE(OP0x01_MOVER_PD, (u8)(+12), R11, R0b), /*(�C���f�b�N�X�t)*/
				// (00) HATSUDAN_R11_speed256 = (VR11 << (8));
				MCODE(OP0x1f_ASLM_PD, (8), R11, R11),/*(�V���[�g�������A�h���b�V���O)*/
				// (00) HATSUDAN_R13_angle65536 = (VR02_j);
				MCODE(OP0x01_MOVER_PD, NAX, R13, R02_j),
				// (00)
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				// (00) VR07 += VR04;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R07, R04),
				// (00) VR06 += VR05;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R06, R05),
				//	NAX/*(�I��)*/
				//------------------
				//	VR09 -= ( ((VR07)));	/* �e�� */
				//	h->center.y256 = (VR06);/*fps_factor*/
				//------------------
				// (00) VR03_i = 2;
				MCODE(OP0x1c_MOVEM_PD, (0x02), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
				// (00) VR0d = 1; //VR0d = 0;
				MCODE(OP0x1c_MOVEM_PD, (0x01), R0d, NAX),/*(�V���[�g�������A�h���b�V���O)*/
			//	for ( ; VR03_i<(65536); )/* ��� */
			//	for_loop_i: 				;
			// �������
			// �����(��CCW������A�����CCW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= (1);//t256(0);/*(���0)*/ /*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, (0x01), R12, NAX),/*(�V���[�g�������A�h���b�V���O)*/
			//	HATSUDAN_R13_angle65536 		= (((VR09)+VR0d) & (65536-1));			/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR09;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R09),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [�g�t���ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (00) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// ����
			// �t���(��CCW������A�E���CW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.50)),
				// (00) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(1)),
			//	HATSUDAN_R13_angle65536 		= (((VR0a)+VR0d) & (65536-1));			/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);// 	/* [�g�t�� �ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_01_AKA)),
				// (00) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// �t���(��CCW������A�E���CW)
			// ��(�e�L�g�[)
				// (00) if (3 != cg_VR20_game_difficulty) {goto LOOP_contine;}
				MCODE(OP0x08_BNE_RS, (3), R20_PLAYER_DATA_game_difficulty, (u8)(+13)),//(LOOP_contine)
				// (00) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= t256(2);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(2)),
				// (00) VR0a += (int)((65536/2));	/* �p�x(65536[360/360�x]�� 2����) */
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
				((int)(65536/2)),
			//	HATSUDAN_R13_angle65536 		= ((VR0a+VR0d) & (65536-1));			/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI);	/* [�g�t�� �ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI)),
				// (00) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
				// (00) VR0a += (int)((65536/2));	/* �p�x(65536[360/360�x]�� 2����) */
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
				((int)(65536/2)),
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (00) VR0d += (int)(65536/2);
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0d, R0d),
				((int)(65536/2)),
				// (00) VR03_i--;
				MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
				// (00) if (0 != VR03_i) {goto for_loop_i;}
				MCODE(OP0x08_BNE_RS, (0), R03_i, (u8)(-35)),//(LOOP_contine)
				// (00)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
			};
			cpu_exec((u32*)&codebase444, ((23*2)+8));//
		}
		static const u32 codebase333[8] =
		{
			// ��]��
			// (00) VR09 += (int)(	   (65536/(22)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)(    (65536/(22)))),
			// (00) VR0a += (int)(65536-(65536/(15)));/* ROTATE_ANGLE */		/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
			((int)(65536-(65536/(15)))),
			// ���p
			//	if ((0x10)==(VR10_BOSS_SPELL_TIMER & 0x1f))/* (32���1�񔭉�) */
			//	if ((0x40)==(VR10_BOSS_SPELL_TIMER & 0x7f))/* (128���1�񔭉�) */
			//	/* (8���1��) ((16x8)==128���1�񔭉�) */
			MCODE(OP0x02_COUNTER, 3, R0c, NAX), 	/* (2���1��) ((16x3)==48���1�񔭉�) */
		//	NAX
			// (55)if (0 != )goto(ccc+2);if (0==(VR10_BOSS_SPELL_TIMER & 0x07))
			// if (0<VR0c) {goto �������Ȃ�;}// ==if (0==VR0c) {��������B;}// /* (48���1��) ���� */ if (1==VR0c)		{	}
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (u8)(+1)),//	(ccc+1)
			// (56)  (cpu_auto_bullet_play_default);
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	(ccc+1:)
			// (57)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
		};
		cpu_exec((u32*)&codebase333, (8));//
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	��	�ʏ�U��2
	-------------------------------------------------------
	normal
		��(12)�e	CW�e������								�E��45�x����J�n
		��(12)�e	CCW�e���x��(�e��2.5�{���炢�H)		����45�x����J�n
	-------------------------------------------------------
	luna
		��(12)�e	CW�e������								�E��45�x����J�n
		��(12)�e	CCW�e���x��(�e��1.5�{���炢�H)		����45�x����J�n
	-------------------------------------------------------
	(?)�B
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B
	R09 	aaa_angle65536
	R0a 	bbb_angle65536
	R0c 	���p�J�E���^�B(40���1��) �����B
---------------------------------------------------------*/

local SPELL_EXEC(23_aya_misogi2)
{
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 8, R08, NAX),
		NAX
	};

//	if ((0x04)==(VR10_BOSS_SPELL_TIMER & 0x07))/* (8���1�� ���e) */
	cpu_exec((u32*)&codebase111, (1));//	/* (8���1�� ���e) */
	if (1==VR08) /* (8���1��) ���e */
	{
		HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
//
	//	#define NUM_12_OF_CIRCLE_ONE	(12)/* ���(�����12�e) */
		#define NUM_12_OF_CIRCLE_ONE	(9)
		for (VR02_j=0; VR02_j<(65536);	VR02_j+=(65536/NUM_12_OF_CIRCLE_ONE))/* ��� */
		{
			static const u32 codebase555[31/*-1*/] =
			{
				//	VR06 += (sin65536((VR02_j))*(16));			/* �e��x256 */
				//	VR07 += (cos65536((VR02_j))*(16));			/* �e��y256 */
				// (01) HATSUDAN_R11_speed256	= (t256(12)); // = ((12)<<8);	/*(r34, 16)*/	/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(((12)<<8)),
				// (02) HATSUDAN_R13_angle65536 = (VR02_j);
				MCODE(OP0x01_MOVER_PD, NAX, R13, R02_j),
				// (03)
				MCODE(OP0x10_SINCOS256, NAX, R04, R05),
				// (04) VR07 += VR04;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R07, R04),
				// (05) VR06 += VR05;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R06, R05),
				//
			//	VR06 += ((si n1024((deg65536to1024(VR02_j)))*(16)));/*fps_factor*/	/* �e��x256 */	/* CCW�̏ꍇ */
			//	VR07 += ((co s1024((deg65536to1024(VR02_j)))*(16)));/*fps_factor*/	/* �e��y256 */
			//	NAX/*(�I��)*/
				//------------------
			// [�������]
				// �����(��CCW������A�����CCW)
				// (06) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.75)),
				// (07) HATSUDAN_R12_speed_offset		= (1);//t256(0);/*(���0)*/ /*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, (0x01), R12, NAX),/*(�V���[�g�������A�h���b�V���O)*/
				// (08) VR13 = VR09;	HATSUDAN_R13_angle65536 		= ((VR09) & (65536-1)); 		/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
				// (09) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [�g�t���ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (10) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			// [����]
				// �t���(��CCW������A�E���CW)
				// (11) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.50)),
				// (12) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(1)),
				//		HATSUDAN_R13_angle65536 		= ((VR0a) & (65536-1)); 		/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				// (13) VR13 = VR0a;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0a),
				// (14) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_01_AKA);// 	/* [�g�t�� �ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_01_AKA)),
				// (15) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
				// ()
				// ��(�e�L�g�[)
				// (16) if (3 != cg_VR20_game_difficulty) {goto LOOP_contine;}
				MCODE(OP0x08_BNE_RS, (3), R20_PLAYER_DATA_game_difficulty, (u8)(+7)),//(LOOP_contine)
				// �����(��CCW������A�����CCW)
				// (17) HATSUDAN_R11_speed256			= (t256(0.75)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.75)),
				// (18) HATSUDAN_R12_speed_offset		= t256(3);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(3)),
				// (19) VR13 = VR09;	HATSUDAN_R13_angle65536 		= ((VR09) & (65536-1)); 		/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				MCODE(OP0x01_MOVER_PD, NAX, R13, R09),
				// (20) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI);	/* [�g�t�� �ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_02_YUKARI)),
				// (21) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (22)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
			};
			cpu_exec((u32*)&codebase555, (21));
		}
		static const u32 codebase333[8] =
		{
			// ��]��
		//	VR09 += (((int)(	  (65536/(22)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
		//	VR0a += (((int)(65536-(65536/(15)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
		//	VR09 += (((int)(	  (65536/(44)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
		//	VR0a += (((int)(65536-(65536/(30)))+((int)(65536/(2)))));/* ROTATE_ANGLE */ 	/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
			// ��]�ʂ� 22����(�A��������, ����44����)�̏ꍇ.
			// (01) VR09 += ((int)( 	  (65536/(44)) + (65536/(2))   ));		/* �p�x(65536[360/360�x]�� 22�����A�A���������ɕ`�� ==	((65536/44)+(65536/2)) ) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)( 	  (65536/(44)) + (65536/(2))   )),
			// ��]�ʂ� 15����(�A��������, ����30����)�̏ꍇ.
			// (02) VR0a += ((int)(65536-( (65536/(30)) + (65536/(2)) ) )); /* �p�x(65536[360/360�x]�� 15�����A�A���������ɕ`�� == -((65536/30)+(65536/2)) ) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
			((int)(65536-( (65536/(30)) + (65536/(2)) ) )),
			// (03)
			// ���p
			//	if ((0x10)==(VR10_BOSS_SPELL_TIMER & 0x1f))/* (32���1��) */
			//	if ((0x40)==(VR10_BOSS_SPELL_TIMER & 0x7f))/* (128���1��) */
			MCODE(OP0x02_COUNTER, 5, R0c, NAX), 	/* (5���1��) ((8x5)==40���1�񔭉�) */
		//	NAX
			// (04) if (0 != VR0c) {goto �������Ȃ��B;}// if (0<VR0c) {goto �������Ȃ��B;}// ==if (0==VR0c) {��������B;}/* (40���1��) ���� */ if (1==VR0c)		{	}
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (u8)(+1)),//	(ccc+1)
			// (05)  (cpu_auto_bullet_play_default);
			MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	(ccc+1:)
			// (06)
			MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
		};
		cpu_exec((u32*)&codebase333, (5));//
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	��	�򕄁u�V�̔��ˁv
	-------------------------------------------------------
	�U�wx32�����e
	-------------------------------------------------------
	�����W�J���A�������E22.5/360�x[1��/16����]�͈̔͂͒e�����Ȃ��B

         /|X
        / | X
       /  |  X
      /   |   X
     /    |    X
    /     |     X
	22.5  | 22.5
	�e�����Ȃ��͈� == [1��/16����] + [1��/16����]
	����̃X�N�V�����瑪��Ƃ����B
	-------------------------------------------------------
	�����ǁApsp���Ɗp�x���L��������B
	�㉺�؂�Ă���(�Q�[���t�B�[���h��)���L�̉�ʂ�����A�����������񂾂낤�ȁB
	����(�ڂ̍��o):
	�����l���c�Ȃ̕��Ɖ��Ȃ̕��𒅂��ꍇ�A�c�Ȃ̕��̕���(�S�̂�)�ׂ�������B
	�����J�[�h�ł����E�g���~���O���ăJ�b�g����ƁA�ڂ̍��o�ōׂ�������B
	�����J�[�h�ł��㉺�g���~���O���ăJ�b�g����ƁA�ڂ̍��o�ő���������B
	���̏ꍇ(psp)���������ɓ�������A�ڂ̍��o�ŋɒ[�ɑ���������B
	-------------------------------------------------------
	������Ƃ����āA�p�x�����߂���A�S�̂��k�����Ē�������ƁA�]�v�����Q�ɋ߂Â��C������B
	�l�I�ɂ́A�u����(��)���v����Ԃ�肽�������񂾂��Apsp�̉�ʋ�������A����(r32)����(��)���͖����Q���ۂ��B
	����(��)���͖����Q���ۂ����A����(��)���͂ł���B
	-------------------------------------------------------
	����(��)��:���ɒ���t���Ȃ���A���̗̑͂����U���@�B(�U���n�ȊO��z��B�U���n�ȊO�ōU���ł���)
	����(��)��:�P�ɒe���(��)���邾���A�U���ł��Ȃ��B�U���n�Ȃ�U���ł��邩���m��Ȃ����z��O(����̖͕핗�ł͏o���Ȃ�)�B
	���̃J�[�h�͒P�ɒe���(��)���邾���Ȃ�ȒP�B
	-------------------------------------------------------
	����(r32)�ł͍U�����w�b�^������Ȃ��������ɕς��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[callback t01 section: �e�����C���[�O���[�v(1)�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
local TAMA_FUNC(aya_danmaku_01_callback)/* �򕄁u�V�̔��ˁv */
{
	if (((32*18)-HATUDAN_FRAME64)==((VR0a) ))/* ��0.33[�b](==20[frame])��~ */
	{
		/* �����ł͌��ʉ��Ȃ� */
		/*(�e�����C���[�O���[�v(1)��S�e��~�B������ς���B)*/
		src_tama->TR02_hatudan_tra65536 				= t256(0);		/* ���������e */
		src_tama->TR01_hatudan_speed65536				= t256(0);		/* �e�� */
	}
	else
	if (((32*18)-HATUDAN_FRAME64-20)==((VR0a) ))/* �~�܂��Ă���20[frame]�� */ /*(32*17)*/
	{
		/* �ړ��B �ĉ����B */
			/*(�e�����C���[�O���[�v(1)��S�e����������B)
				-------------------------------------------------------
				�����e(���m�ɂ͓������e)�Ȃ̂ɁA�����e�Ɍ����Ȃ��ŁA
				�����e(���m�ɂ͓����x�e�A����==0)�Ɍ������Ⴄ��肪����B
			*/
		{
			#if 1
			/* �[������==���Z�Œ�l(KOTEITI_AYA_1234) */
		//	#define KOTEITI_AYA_1234 (1234<<6)
		//	#define KOTEITI_AYA_1234 (78976)
			#define KOTEITI_AYA_1234 (7777)
			VR09 += (KOTEITI_AYA_1234);
		//	src_tama->rotationCCW1024				= (ra_nd()&((1024)-1)); 	/* ���� */	/* �����͗����łȂ��C������ */
		//	src_tama->rotationCCW1024				= (deg65536to1024(VR09));			/* ���� */
		//	src_tama->rotationCCW1024				= ((((deg65536to1024(VR09))&(512-1))+(256*(4-1)))&(1024-1));		/* ����(��(180/360[�x])�ɂ��������Ȃ�) */
		//	src_tama->rotationCCW1024				= ((((deg65536to1024(VR09))&((256<<6)-1))+((128<<6)*(8-1)))&(65536-1)); 	/* ����(��( 90/360[�x])�ɂ��������Ȃ�) */
			src_tama->rotationCCW65536				= (((((VR09))&((256<<6)-1))+((128<<6)*(8-1)))&(65536-1));		/* ����(��( 90/360[�x])�ɂ��������Ȃ�) */
			#endif
			src_tama->TR02_hatudan_tra65536 		= t256(1);	/* (1) ���������e */
		/* �`���m(�p�[�t�F�N�g�t���[�Y)�̏ꍇ�͐�ɕϐg���邪�A��(�V�̔���)�̏ꍇ�͌�ŕϐg����B */
			src_tama->obj_type_set							= (BULLET_MARU10_BASE + TAMA_IRO_03_AOI);	/* �ےe */
			reflect_sprite_spec(src_tama, OBJ_BANK_SIZE_00_TAMA);	/* �e�O���ƒe�����蔻���ύX����B */
			/* (�ʏ�e�֕ϐg����) */
			src_tama->TR00_hatudan_spec_data		= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
		}
		/* �~�܂����������A�����n�߂鎞�Ɍ��ʉ��炵������������ۂ��B */
		#if (1)
		AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;/* ���ʉ�: ������ */
	//	AUDIO_18_voice_number	= VOICE11_BOSS_KIRARIN;/* ���ʉ�: ������ */
		AUDIO_19_voice_truck	= TRACK03_IVENT_DAN;	CPU_CALL(cpu_voice_play);
		AUDIO_19_voice_truck	= TRACK04_TEKIDAN;		CPU_CALL(cpu_voice_play);
		/* �厖�Ȏ��Ȃ̂łQ�񌾂��܂����B */
		#endif
	}
//	standard_angle_mover_00_callback(src_tama);/*(�p�x�e�ړ�+��ʊO�e����)*/
	hatudan_system_tama_move_angle(src_tama);/*(�p�x�e�ړ�)*/
}

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
	�g�p���W�X�^
//	R08 	�J�E���^�B
//	R09 	add_angle
	R0a 	�{�X�^�C�}�[�l�A�R�[���o�b�N���ɘA���p�B(�Ƃ肠����)
//	R0b 	�ĉ����̑��x�p�Ɉꎞ�g�p�B
---------------------------------------------------------*/
local SPELL_EXEC(22_aya_yatimata)
{
	static const u32 codebase_exec[23] =
	{
	// (01) VR0a = (VR10_BOSS_SPELL_TIMER);/*(�{�X�^�C�}�[�l�A�R�[���o�b�N���ɘA���p�B(�Ƃ肠����))*/
	MCODE(OP0x01_MOVER_PD, NAX, R0a, R10),
	//----
	// (02) VR03_i = (VR10_BOSS_SPELL_TIMER);
	MCODE(OP0x01_MOVER_PD, NAX, R03_i, R10),
	// (03) VR03_i = VR03_i - (((32*20)-1));
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R03_i, R03_i),
	(int)(-(((32*20)-1))),
	// (04) if ((0) != VR03_i)/* ��1.0[�b](==64[frame])�S�e��W�J */	{goto ccc_end+17;}
	MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(+17)),//	(ccc_end+17)
	/* �e���� */
	// (05) HATSUDAN_R11_speed256			= (t256(0.5));			/* �e��(psp�̉�ʂ͋���) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.5)),
	// (06) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT)),
	// (07) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO);		/* ���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	((BULLET_WAKU12_BASE + TAMA_IRO_00_SIRO)),
	//----
	// (08) VR03_i = (6);/* �U�w�B */
	MCODE(OP0x1c_MOVEM_PD, (6), R03_i, NAX),/*(�V���[�g�������A�h���b�V���O)*/
//	bbb_loop-9: 	;
	//		HATSUDAN_R12_speed_offset		= t256(-5); 		/* (-5) (-3)���������e */	/* ���̕����ɂȂ邩������ */
	//		HATSUDAN_R12_speed_offset		= t256(-VR03_i);/*(�e�X�g)*/
	//		HATSUDAN_R12_speed_offset		= t256(VR03_i<<2);/* x4�{ �Ă���*/
	// (09) HATSUDAN_R12_speed_offset		= (VR03_i<<(2+8));/* x4�{ �Ă���*/
	MCODE(OP0x1f_ASLM_PD, (2+8), R12, R03_i),/*(�V���[�g�������A�h���b�V���O)*/
	//		HATSUDAN_R13_angle65536 		= (65536/16);			/* ���� */
	// (10) HATSUDAN_R13_angle65536 		= (65536/2);			/* [�j��] */	/* �^����� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),
	((65536/2)),
	// (11) HATSUDAN_R16_n_way				= (32); 				/* [�j��] */	/* [32way] */	/* 32�����e */
	MCODE(OP0x1c_MOVEM_PD, (32), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (12) HATSUDAN_R17_div_angle65536 	= ((65536-(65536/8))/32);/*(1792)*/ /* [�j��] */	/* �����p�x(�e�����Ȃ��͈͂�����32����) */	/* (ra_nd16>>4) == ����(0-4095) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
	(((65536-(65536/8))/32)),/*(1792)*/
	// (13) (1�e����)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(42-)*/
	// (14) VR03_i--;
	MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i),/*(�C���f�b�N�X�t)*/
	// (15) if (0 != VR03_i) {goto bbb_loop-9;}
	MCODE(OP0x08_BNE_RS, (0x00), R03_i, (u8)(-9)),//	(bbb_loop-9)
	// (16)  (cpu_auto_bullet_play_default);
	MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
//	(ccc_end+17:)
	// (17)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (51));// 51==16+5x7
}

local SPELL_INIT(22_aya_yatimata)
{	// (CLIP_RECT_TYPE_01_UE_YOKO);
	static /*const*/ u32 codebase_init[6] =
	{
	// (01)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1c_bullet_clip_min_x256, NAX),// ��ɍL���^�C�v
	CLIP_RECT_01_VR1c,// ��ɍL���^�C�v
	// (02)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// ��ɍL���^�C�v
	CLIP_RECT_01_VR1d,// ��ɍL���^�C�v
	// (03)
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1e_bullet_clip_max_x256, NAX),// ��ɍL���^�C�v
	CLIP_RECT_01_VR1e,// ��ɍL���^�C�v
	};
	cpu_exec((u32*)&codebase_init, (3));
}
// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�Ǖ��u�R�_�n��v(normal)
	�Ǖ��u�V��V���̏ƚ��v(luna)
	-------------------------------------------------------
	���񂺂����ĂȂ�...
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	bbb �J�E���^�B
	R09 	[���g�p]
	R0a 	�ꎞ�g�ptemp�B
	R0b 	�J�E���^�B
	R0c 	zzz �J�E���^ ��Փx�ʒ萔�B
	-------------------------------------------------------
	R0d 	�e�̎��1	cc_type[(cg_VR20_game_difficulty)]
	R0e 	�e�̎��2	ba_type[(cg_VR20_game_difficulty)]
---------------------------------------------------------*/

// 4096 == 65536/16
// 3855.05882352941176470588235294118 == 65536/17
//	240.941176470588235294117647058824 == ((65536/16)-(16636/17)) ����
local SPELL_EXEC(26_aya_saifu)
{
	static const u32 codebase_exec[40] =
	{
	// (01) //	count_up_limit_NUM(R0b, VR0c);
	MCODE(OP0x02_COUNTER, REGISTER_ADDRESSING/*[���W�X�^�ԐڃA�h���b�V���O]*/, R0b, R0c/*[��Փx�ʒ萔]*/),
	// (02) if (0 != VR0b)	{goto (bbb+18);}
	MCODE(OP0x08_BNE_RS, (0), R0b, (u8)(+18)),// (bbb+18)
	// ---- VR0c -= (cg_VR20_game_difficulty);
	// (03) VR0a = cg_VR20_game_difficulty;
	MCODE(OP0x01_MOVER_PD, NAX, R0a, R20_PLAYER_DATA_game_difficulty),
	// (04) VR0a = (VR00 + (0) - VR0a);
	MCODE(OP0x05_SUBR_PD, (0x00), R0a, R00),/*(�[�����W�X�^�g�p)*/
	// (05) VR0c += VR0a;
	MCODE(OP0x04_ADDR_PD, NAX, R0c, R0a),
//	#define min_24zzz (26)/* (r33) */
//	#define min_24zzz (40)/* (r34)�኱�e�؂ꂷ��B */
	#define min_24zzz (44)/* (r34) */
	// ---- if (min_24zzz > VR0c)	{VR0c = min_24zzz;}
	// (06) if (min_24zzz < VR0c)) {goto qqq+1;}/*(�t���[�����番��B)*/
	MCODE(OP0x09_BFL_RS, (min_24zzz), R0c, (u8)(+1)),// (aaa+1:);	/* �t���[�����番�� */
	// (07) VR0c				= (min_24zzz);
	MCODE(OP0x1c_MOVEM_PD, (min_24zzz), R0c, NAX),/*(�V���[�g�������A�h���b�V���O)*/
//aaa+1:
	#undef min_24zzz
	// (08) HATSUDAN_R11_speed256			= (t256(0.50)); 	/* �e��(t256(1.00)) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.50)),
	// (09) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�gt256(0))*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (10) HATSUDAN_R13_angle65536 		= (0);				/* ���˒��S�p�x / ����@�\(���@�_��/��) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R13, NAX),
	(0),
	// (11) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (12) HATSUDAN_R15_bullet_obj_type	= VR0d; 		/*	�e�̎��1[ �e] */
	MCODE(OP0x01_MOVER_PD, NAX, R15, R0d),
	// (13) HATSUDAN_R16_n_way				= (16*5);		/* [80way] */	/*(6)*/ 	/* ���e�� */
	MCODE(OP0x1c_MOVEM_PD, (16*5), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (14) HATSUDAN_R17_div_angle65536 	= (int)(65536/(16*5));	/* �����p�x(65536[360/360�x]�� 8 ����) */	/* 1����n���������p�x */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(16*5)),
	// (15)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//bbb+18:
	// ---- VR0a = ((VR10_BOSS_SPELL_TIMER+4)&0x07);/* (2���1��)(8�񖈂ɔ��e) */
	// (16) VR0a = VR10_BOSS_SPELL_TIMER + (4); 	/* �e�� */
	MCODE(OP0x01_MOVER_PD, (u8)(+4), R0a, R10), /*(�C���f�b�N�X�t)*/
	// (17) VR0a = ((VR0a)&0x07);
	MCODE(OP0x1d_ANDM_PD, 0x07, R0a, R0a),/*(�V���[�g�������A�h���b�V���O)*/
	// (18) if (0 != VR0a)		{goto ddd+16;}		//	if (0==VR0a)	{	}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+16)),// (ddd+16)
	// (19) VR08 += (77);
	MCODE(OP0x01_MOVER_PD, (u8)(+77), R08, R08), /*(�C���f�b�N�X�t)*/
	//	//	HATSUDAN_R13_angle65536 		= (int)((65536*3/4))+(VR10_BOSS_SPELL_TIMER&0xff);
	//	//	HATSUDAN_R13_angle65536 		= (int)((65536*1/4))+(VR10_BOSS_SPELL_TIMER&0xff);
	// (20) HATSUDAN_R13_angle65536 		= (VR08);	/* ���˒��S�p�x / ����@�\(���@�_��/��) */
	MCODE(OP0x01_MOVER_PD, NAX, R13, R08),
	// (21) VR0a = (VR10_BOSS_SPELL_TIMER & 0x08);
	MCODE(OP0x1d_ANDM_PD, 0x08, R0a, R10),/*(�V���[�g�������A�h���b�V���O)*/
	// (22) if (0 != VR0a)		{goto �������ɂ��Ȃ��B;}
	MCODE(OP0x08_BNE_RS, (0x00), R0a, (u8)(+1)),//	(ccc+1)
	// (23) HATSUDAN_R13_angle65536 			= -(HATSUDAN_R13_angle65536); VR13 = (VR00 + (0x00) - VR13);
	MCODE(OP0x05_SUBR_PD, (0x00), R13, R00),/*(�[�����W�X�^�g�p)*/
//ccc+1:
	// (24) HATSUDAN_R11_speed256				= (t256(0.50)); 	/* �e��(t256(1.00)) */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	(t256(0.50)),
	// (25) HATSUDAN_R12_speed_offset			= t256(1);/*(�e�X�gt256(0))*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(t256(1)),
	// (26) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)),
	// (27) HATSUDAN_R15_bullet_obj_type = VR0e;	/*	�e�̎��2[ �e] */
	MCODE(OP0x01_MOVER_PD, NAX, R15, R0e),
	// (28) HATSUDAN_R16_n_way					= (16); 	/* [16way] */	/* ���e��(17) (8) (6) */
	MCODE(OP0x1c_MOVEM_PD, (16), R16, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// (29) HATSUDAN_R17_div_angle65536 		= (int)(65536/(16));	/* �����p�x(65536[360/360�x]�� 16 ����) */	/* 1����n���������p�x */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),//
	(int)(65536/(16)),
	// (30)
	MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
//ddd+16:
	// (31)
	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (30));
}

local SPELL_INIT(26_aya_saifu)
{
	static const u32 codebase_init[11] =
	{
	//	VR0d = cc_type[(cg_VR20_game_difficulty)];//	�e�̎��1
	// (01) VR0d = hairetu[VR20_game_difficulty];goto (bbb+16);
	MCODE(OP0x0a_BRA_TABLE, R20_PLAYER_DATA_game_difficulty, R0d, (+4)),
	//	const u32 cc_type[4] =
	(BULLET_MINI8_BASE + TAMA_IRO_05_MIDORI),
	(BULLET_MINI8_BASE + TAMA_IRO_00_SIRO), 		// �Ǖ��u�R�_�n��v(normal)
	(BULLET_KOME_BASE  + TAMA_IRO_06_KI_IRO),
	(BULLET_KOME_BASE  + TAMA_IRO_06_KI_IRO),		// �Ǖ��u�V��V���̏ƚ��v(luna)
	//	VR0e = ba_type[(cg_VR20_game_difficulty)];//	�e�̎��2
	// (02) VR0e = hairetu[R20_game_difficulty];goto (bbb+16);
	MCODE(OP0x0a_BRA_TABLE, R20_PLAYER_DATA_game_difficulty, R0e, (+4)),
	//	const u32 ba_type[4] =
	(BULLET_KOME_BASE	 + TAMA_IRO_03_AOI),
	(BULLET_KOME_BASE	 + TAMA_IRO_03_AOI),		// �Ǖ��u�R�_�n��v(normal)
	(BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO),
	(BULLET_UROKO14_BASE + TAMA_IRO_06_KI_IRO), 	// �Ǖ��u�V��V���̏ƚ��v(luna)
	//----
	// (03) VR0c = (64);/* 64����n�߂�B */
	MCODE(OP0x1c_MOVEM_PD, (64), R0c, NAX),/*(�V���[�g�������A�h���b�V���O)*/
	// [�d��]VR0b = 0;
	// (04)
//	MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_init, (3));
}
// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	��	�댯�Ȏ�e�J�[�h
	-------------------------------------------------------
	�e�L�g�[
---------------------------------------------------------*/
//tern OBJ_CALL_FUNC(add_zako_aya_doll);/* ���e */
extern OBJ_CALL_FUNC(add_zako_aya_doll);/* ���l�`�J�[�h */
local SPELL_EXEC(0f_aya_doll)
{
	if (50 == VR10_BOSS_SPELL_TIMER)
	{
		add_zako_aya_doll(src_boss);
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�J�~��e
	-------------------------------------------------------
	R09 	[�萔1]�J�̑��x
	//
	R0a 	[���g�p]�h���ʁB�h���� == (�h���傫��) x cos(�h����]�p�x)�B
	R0b 	�h���ʁB�h���� == (�h���傫��) x sin(�h����]�p�x)�B
	//
	//
	R0d 	work x�B��Փx�ʁB���e��x�ʒu��ێ�����ׂɕK�v�B
	R0e 	�h����]�p�x��ێ��B
---------------------------------------------------------*/

/*---------------------------------------------------------
	[execute section: ���e�Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/

//#define spell_execute_1d_amefuri_test spell_execute_common_amefuri
local SPELL_EXEC(1d_amefuri_test)
{
//	spell_execute_aya_amefuri_oodama(src);
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))	// 16�J�E���g��1����8way�e������
//	if (0 == (VR10_BOSS_SPELL_TIMER & 0x3f))	// 64�J�E���g��1����8way�e������
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x0f))	// 16�J�E���g��1����1�e������
	{
	static const u32 codebase999[14] =
	{
	// �h����]�p�x
	// (01) VR0e += (1234);/*(�e�L�g�[�ɉ��Z)*/
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0e, R0e),
	(1234),/*(�e�L�g�[�ɉ��Z)*/
	//	VR0e &= (0xffff);
	//------------------
	//	[r41]�p�x�e�����̏ꍇ�́A���Ȃ����A�x�N�g���e������ꍇ�A���ʂȑ΍􂪕K�v�B
	//	(r41���_��[���Ԃ�r36���炢����])�x�N�g���e�́A
	//	VR06, VR07 �́A local TAMA_FUNC(common_01_amefuri_callback)�Ŏg�p���Ă���̂Ŕj��ł��Ȃ��B
	//------------------
	// (02) HATSUDAN_R11_speed256	= (t256(33.3));/*(�h���傫��)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	((t256(33.3))),
	// (03) HATSUDAN_R13_angle65536 = (VR0e);/*(�h���p�x)*/
	MCODE(OP0x01_MOVER_PD, NAX, R13, R0e),
	// (04) p[VR0a, VR0b] = sincos256(VR11, VR13);
	MCODE(OP0x10_SINCOS256, NAX, R0a, R0b),
	//VR0b	src->math_vector.x256 = VR07;//sin_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//VR0a	src->math_vector.y256 = VR06;//cos_value_t256 // ��CCW�̏ꍇ(�ECW�̏ꍇ�Ƃ�xy���t)
	//	sincos �j�󃌃W�X�^�����̂ŁA�\�� sincos �� VR0b ���v�Z���Ă���
	//------------------
	//		HATSUDAN_R11_speed256				= t256(0.5)/*VR09*/;// [�萔1]�J�̑��x
	//		HATSUDAN_R11_speed256				= t256(0.45)/*VR09*/;// [�萔1]�J�̑��x
	// (05) HATSUDAN_R11_speed256				= t256(0.33)/*VR09*/;// [�萔1]�J�̑��x
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),
	((t256(33.3))),
	//		HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
	//		HATSUDAN_R12_speed_offset	= ((ra_nd()&0x07)+1);//t256(0.04)/*(�Ƃ肠����)*/
	// (06) HATSUDAN_R12_speed_offset	= ((0)+1);//t256(0.04)/*(�Ƃ肠����)*/
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
	(((0)+1)),
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		//	HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	// (07) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
	((DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT)),
	// (08) HATSUDAN_R15_bullet_obj_type		= BULLET_OODAMA32_00_AOI;/* [��ʒe] */	/* �e�O�� */
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),
	(BULLET_OODAMA32_00_AOI),/* [��ʒe] */
	//------------------
	// (09)
//	NAX/*(�I��)*/
	};
	cpu_exec((u32*)&codebase999, (8));
	//	for (jj=(0); jj<(8); jj++)
		{
			/* �V���b�g */
		//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((0	 )&(0x0fff));
		//	HATSUDAN_R13_angle65536 			= (jj<<(10));
			#if 0
		//	HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(10-4));
		//	VR13 += (65536/4)+(65536/8)+(65536/16);
		//	VR13 += (VR0b);
		//	HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(8-4));
		//	VR13 += (65536/4)+(65536/8)+(65536/16)+(65536/32);
		//	VR13 += (VR0b);
			HATSUDAN_R13_angle65536 			= ((VR10_BOSS_SPELL_TIMER & 0x70)<<(6-4));
			VR13 += (int)((65536/4)+(65536/8)+(65536/16)+(65536/32)+(65536/64)+(65536/128));
			VR13 += (VR0b);
			#endif
			HATSUDAN_R13_angle65536 			= (0);
			VR13 += (int)((65536/2));
		//	VR13 += (VR0b<<4);
			VR13 += (VR0b);
			//
//	//		HATSUDAN_R16_n_way					= (8);
//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
//	spell_execute_aya_amefuri_kodan(src);
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))	// 4�J�E���g��1����8way�e������
	{
			HATSUDAN_R11_speed256				= VR09;// [�萔1]�J�̑��x
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
//			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_01)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);	/* �e�O�� */	/* [���Ēe] */
		int jj;
		jj = (8);/*(x�ʒu)*/
		{
		loop_oodama:
			VR0d -= cg_VR20_game_difficulty;// jj �� x�ʒu�Ȃ̂ŕς���ƈʒu���΂�B�����ŊԈ����B
			if (1 > VR0d)
			{
				VR0d += (3);
				#if 0
				/* �V���b�g */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER>>(2-6))&((0x3f)<<6));
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 				= (int)(65536/64);
				HATSUDAN_R17_VECTOR_leg acy_dan_delta256	= ((ra_nd()&0x03)+2);//t256(0.04)
				bul let_reg ist_leg acy_vec tor_dir ect();
				#else
				/* �V���b�g */
			//	b05_fire_flags &= (~(doll_data->identity_bit));/* off */
			//	HATSUDAN_R12_speed_offset			= ((ra_nd()&0x03)+2);//t256(0.04)
				/*(�Ƃ肠����)*/HATSUDAN_R12_speed_offset			= ((ra_nd()&0x07)+1);//t256(0.04)
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(5+6))+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x3f<<6));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11));//+((VR10_BOSS_SPELL_TIMER<<(6-2))&(0x0fff));
	//	//		HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
			//	HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(5))&(0x0fff));
				HATSUDAN_R13_angle65536 			= (65536/4)+(65536/8)+(jj<<(11))+((VR10_BOSS_SPELL_TIMER<<(4))&(0x0fff));
				//
	//	//		HATSUDAN_R16_n_way					= (8);
	//			HATSUDAN_R17_div_angle65536 		= (int)(65536/64);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
				#endif
			}
			jj--;
			if ((0) < jj) {goto loop_oodama;}
		}
	}
}

/*---------------------------------------------------------
	[initialize section: �������Z�N�V����]
	-------------------------------------------------------
---------------------------------------------------------*/
#if 1
//	#define spell_init_1d_amefuri_test spell_init_12_com mon_amefuri
local SPELL_INIT(1d_amefuri_test)
{
//	in it_00_bullet_clip_type(CLIP_RECT_TYPE_03_UE_WIDE);/*(����)*/
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[�萔1]�J�̑��x
//	/*(�Ƃ肠����)*/VR09	= (t256(1.5)+((0)<<6));//[�萔1]�J�̑��x
//	/*(�Ƃ肠����)*/VR09	= (t256(1.5)+((0)<<6));//[�萔1]�J�̑��x
	//	cg_BOSS_DATA_38_angleCCW65536 += (int)(ra_nd() & ((1<<difficulty)-1) );
	static /*const*/ u32 codebase_init[6] =
	{
	// (01) (CLIP_RECT_TYPE_03_UE_WIDE);
	MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R1d_bullet_clip_min_y256, NAX),// ��ɂ����ƍL���^�C�v
	CLIP_RECT_03_VR1d,// ��ɂ����ƍL���^�C�v
	// ----
	// (02) VR0d = ��Փx�ʒ萔1	(nan_ido);
	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
	PACK_NAN_IDO_CONST(0x00, 0x1f, 0x3f, 0x5f),
	// (03) VR09 = t256(1.0) + VR09;//[�萔1]�J�̑��x
	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
	(t256(1.0)),
//	// (04) VR0a = ��Փx�ʒ萔2
//	//	VR0a	= ((65536/2)+(65536/24)+(cg_VR20_game_difficulty<<(3+6)));//[�萔2]�ԐN�i�C���Ȃ���p�x
//	MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R09, NAX/*R20_PLAYER_DATA_game_difficulty*/),
//	PACK_NAN_IDO_CONST((0), (8), (16), (24)),
//	// (05)
//	MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0a, R0a),
//	((65536/2)+(65536/24)),
	};
	cpu_exec((u32*)&codebase_init, (3));
//	VR0c = (0);/*[�[���y�[�W�͕K��0�N���A�����̂ŏȗ��\](���e��x�ʒu��ێ�����ׂɕK�v�B)*/
//	VR0e = (0);/*[�[���y�[�W�͕K��0�N���A�����̂ŏȗ��\](�h����]�p�x��ێ��B)*/
//	VR09	= (t256(1.5)+((cg_VR20_game_difficulty)<<6));//[�萔1]�J�̑��x
}
#endif
// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	�� �䕗�`��
	-------------------------------------------------------
	VR0f_AYA_LINK		�U���^�C�v
	-------------------------------------------------------
	AYA_LINK_00_NONE	�U���^�C�v00: �U�����Ȃ��B;
		�U�����Ȃ��ꍇ(AYA_LINK_00_NONE == VR0f_AYA_LINK)�͈ړ��X�V�����Ȃ��B
		�U�������ꍇ(AYA_LINK_00_NONE != VR0f_AYA_LINK)�́A
		�V���Ȏ��̖ڕW��ݒ肷��B
	-------------------------------------------------------
	AYA_LINK_01_RENDAN	�U���^�C�v01: �ĘA�e;
		���m�ɑ_���Ă���ĘA�e�B���������łn�j�B
		[r42]�P�F�ɕύX�B
	-------------------------------------------------------
	AYA_LINK_02_FUDADAN �U���^�C�v02: ��ǂ��D�e;
		���肰�Ȃ��΂�T���D�e�B���肰�Ȃ����B
	-------------------------------------------------------
	AYA_LINK_03_OODAMA	�U���^�C�v03: ��ʒe;
		���\�_���Ă����ʒe�B���x���Ⴄ�̂Ō��Ȋ����B
---------------------------------------------------------*/

local void s_aya_kougeki_all_void(void)
{
	// (r35�ŃJ�[�h�̏ꍇ�̂ݏȗ��\)	/* �e��x256 y256 ���S���甭�e�B */
	/* �e��x256 y256 ���S���甭�e�B */
	CPU_CALL(calculate_boss_to_jiki_nerai);
	#if 0/*(r35�̃V�X�e���ł́A�ȗ��\)*/
	HATSUDAN_R13_angle65536 			= (HATSUDAN_R13_angle65536);	/* [�j��] */
	#endif
	//
//	if (AYA_LINK_00_NONE==VR0f_AYA_LINK)	/*[�U���^�C�v00: �U�����Ȃ��B]*/
//	{
//	}
//	else
	if (AYA_LINK_01_RENDAN==VR0f_AYA_LINK)	/*[�U���^�C�v01: �ĘA�e]*/
	{
		/* ���� */
		static const u32 codebase_exec111[16] =
		{
			// (01) AUDIO_18_voice_number		= VOICE11_BOSS_KIRARIN;
			MCODE(OP0x1c_MOVEM_PD, (VOICE11_BOSS_KIRARIN), R18, NAX),/*(�V���[�g�������A�h���b�V���O)*/
			// (02) AUDIO_19_voice_truck		= TRACK04_TEKIDAN;/*�e�L�g�[*/
			MCODE(OP0x1c_MOVEM_PD, (TRACK04_TEKIDAN), R19, NAX),/*(�V���[�g�������A�h���b�V���O)*/
			// (03)  (cpu_voice_play);
			MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
			// (04) HATSUDAN_R12_speed_offset	= t256(1.0);/* �H */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(t256(1.0)),
			// (05) HATSUDAN_R14_tama_spec		= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			//	VR04 = ((cg_game_dif ficulty)<<6)+t256(4.50);/*(aya_speed)*/
			#if 0
			easy	0	  0+1152 1152  t256(4.50) t256(4.50)	// 3.5����easy���������B t256(3.5)
			normal	1	 64+1152 1216  t256(4.75) t256(4.50)
			hard	2	128+1152 1280  t256(5.00) t256(4.75)
			luna	3	192+1152 1344  t256(5.25) t256(4.00)
			#endif
			// (06) VR04 = ([��Փx�ʒ萔]);	VR04 = PACK_NAN_IDO_CONST((u8)(4.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4));
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R04, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(4.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4)), 	// 4==2^2, 6+2==8==t256()
			PACK_NAN_IDO_CONST((u8)(2.50*4), (u8)(4.50*4), (u8)(4.75*4), (u8)(4.00*4)), 	// 4==2^2, 6+2==8==t256()
			// (07) VR04 <<= (6);/*(aya_speed)*/											// 4==2^2, 6+2==8==t256()
			MCODE(OP0x1f_ASLM_PD, (6), R04, R04),/*(�V���[�g�������A�h���b�V���O)*/
			// (08) VR05		= (HATSUDAN_R13_angle65536);	/* [�j��] */
			MCODE(OP0x01_MOVER_PD, NAX, R05, R13),
			// HATSUDAN_R15_bullet_obj_type = (BULLET_KOME_BASE) + (/*ra_nd()*/(HATSUDAN_R13_angle65536>>8) & 0x0f);	/* �e�O�� */
			// (09) VR15 = VR13;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R13),
			// (10) VR15 >>= (8);
			MCODE(OP0x1e_ASRM_PD, (8), R15, R15),/*(�V���[�g�������A�h���b�V���O)*/
			// (11) VR15 &= (0x0f);
			MCODE(OP0x1d_ANDM_PD, (0x0f), R15, R15),/*(�V���[�g�������A�h���b�V���O)*/
			// (12) VR15 += (BULLET_KOME_BASE);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			(BULLET_KOME_BASE), 	/* �e�O�� */
		};
		cpu_exec((u32*)&codebase_exec111, (12));
		//
		for (VR03_i=0; VR03_i<(8+cg_VR20_game_difficulty); VR03_i++)
		{
			VR04 -= (t256(0.125));
			HATSUDAN_R11_speed256			= (VR04);			/* �e�� */
			HATSUDAN_R13_angle65536 		= (VR05);			/* [�j��] */
			HATSUDAN_R16_n_way				= (11-VR03_i);		/* [�j��] */	/* [10way] */
			HATSUDAN_R17_div_angle65536 	= (int)(65536/24);	/* [�j��] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);/*(r42-)*/
		}
	}
	else
	if (AYA_LINK_02_FUDADAN==VR0f_AYA_LINK) /*[�U���^�C�v02:	��ǂ��D�e]*/
	{	/*(�D�e�͈Ӑ}�I�ɒx������)*/
		static const u32 codebase_exec222[14] =
		{
			//	HATSUDAN_R11_speed256			= (t256(2.0)+((cg_VR20_game_difficulty)<<8));	/* �e�� */	/*t256(5.0)*/
			//	HATSUDAN_R11_speed256			= (t256(1.5)+((cg_VR20_game_difficulty)<<4));	/* �e�� */	/*t256(5.0)*/
			#if 0
			easy	0	t256(1.5000==1.50+0.0000) == (24<<4)
			normal	1	t256(1.5625==1.50+0.0625) == (25<<4)
			hard	2	t256(1.6250==1.50+0.1250) == (26<<4)
			luna	3	t256(1.6875==1.50+0.1875) == (27<<4)
			#endif
			// (01) //	VR11 = ([��Փx�ʒ萔]);
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R11, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(1.5000*16), (u8)(1.5625*16), (u8)(1.6250*16), (u8)(1.6875*16)), 	// 16==4^2, 4+4==8==t256()
			PACK_NAN_IDO_CONST((u8)(2.0000*16), (u8)(1.5625*16), (u8)(1.6250*16), (u8)(1.6875*16)), 	// 16==4^2, 4+4==8==t256()
			// (02) VR11 <<= (4);/*(aya_speed)*/														// 16==4^2, 4+4==8==t256()
			MCODE(OP0x1f_ASLM_PD, (4), R11, R11),/*(�V���[�g�������A�h���b�V���O)*/
			// (03) HATSUDAN_R12_speed_offset		= t256(1.0);/* �H */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(t256(1.0)),
			// (04) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_3000_EFFECT_NONE)|(TAMA_SPEC_0000_TILT)),
			//	HATSUDAN_R15_bullet_obj_type	= BULLET_KOME_BASE + (ra_nd()&0x0f);	/* �e�O�� */
			//	HATSUDAN_R15_bullet_obj_type	= (BULLET_OFUDA12_00_AOI) + (VR0a); 	/* �e�O�� */
			// (05) VR15 = VR0a + (BULLET_OFUDA12_00_AOI);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R0a),
			(BULLET_OFUDA12_00_AOI),	/* �e�O�� */
			// (06) HATSUDAN_R16_n_way = ([��Փx�ʒ萔]);		/* [�j��] */	/* [5way] */
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R16, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((5), (5), (7), (7)),
			// (07) HATSUDAN_R17_div_angle65536 	= (65536/12);	/* [�j��] */	/* 12���� == (30/360)[�x] */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R17, NAX),
			((65536/12)),
			// (08)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY, NAX, NAX),/*(r42-)*/
		};
		cpu_exec((u32*)&codebase_exec222, (8));
	}
	else
//	if (AYA_LINK_03_OODAMA==VR0f_AYA_LINK)	/*[�U���^�C�v03:	��ʒe]*/
	{	/*(�A�e���኱�x������)*/
		static const u32 codebase_exec333[16] =
		{
			//	HATSUDAN_R11_speed256			= speed256; 			/* �e�� */
			//	HATSUDAN_R11_speed256			= (t256(4.0)-((cg_VR20_game_difficulty)<<7));	/* �e�� */
			//	HATSUDAN_R11_speed256			= (t256(3.5)-((cg_VR20_game_difficulty)<<6));	/* �e�� */
			#if 0
			easy	0	t256(3.50)
			normal	1	t256(3.25)
			hard	2	t256(3.00)
			luna	3	t256(2.75)
			#endif
			// (01) //	VR11 = ([��Փx�ʒ萔]);
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R11, NAX/*R20_PLAYER_DATA_game_difficulty*/),
		//	PACK_NAN_IDO_CONST((u8)(3.50*4), (u8)(3.25*4), (u8)(3.00*4), (u8)(2.75*4)), 	// 4==2^2, 6+2==8==t256()
			PACK_NAN_IDO_CONST((u8)(3.00*4), (u8)(3.25*4), (u8)(3.00*4), (u8)(2.75*4)), 	// 4==2^2, 6+2==8==t256()
			// (02) VR11 <<= (6);/*(aya_speed)*/											// 4==2^2, 6+2==8==t256()
			MCODE(OP0x1f_ASLM_PD, (6), R11, R11),/*(�V���[�g�������A�h���b�V���O)*/
			// (03) HATSUDAN_R12_speed_offset		= t256(-2);/* �����e�H */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),
			(-(t256(2.0))),
			// (04) HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(0)|(TAMA_SPEC_8000_NON_TILT)),
			// HATSUDAN_R15_bullet_obj_type = (BULLET_OODAMA32_00_AOI) + ((HATSUDAN_R13_angle65536>>8) & 0x03); 	/* �e�O�� */
			// (05) VR15 = VR13;
			MCODE(OP0x01_MOVER_PD, NAX, R15, R13),
			// (06) VR15 >>= (8);
			MCODE(OP0x1e_ASRM_PD, (8), R15, R15),/*(�V���[�g�������A�h���b�V���O)*/
			// (07) VR15 &= (0x03);
			MCODE(OP0x1d_ANDM_PD, (0x03), R15, R15),/*(�V���[�g�������A�h���b�V���O)*/
			// (08) VR15 += (BULLET_OODAMA32_00_AOI);
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R15),
			(BULLET_OODAMA32_00_AOI),	/* �e�O�� */
			// (09) HATSUDAN_R16_n_way = PACK_NAN_IDO_CONST((12), (14), (16), (20));	/* [12way] */
			MCODE(OP0x03_NAN_IDO, MEMORY_ADDRESSING, R16, NAX/*R20_PLAYER_DATA_game_difficulty*/),
			PACK_NAN_IDO_CONST((12), (14), (16), (20)),
			// (10)  (div65536);/*[�������Z�N�V�����ȊO�ł͑��x�ቺ�̉\������]*/	(65536/12); 	/* 12���� == (30/360)[�x] */
			MCODE(OP0x17_DIV65536, NAX, R17, R16),// HATSUDAN_R17_div_angle65536  = 65536 / VR04_NAN_IDO_DECODE;
			// (11)
			MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY, NAX, NAX),/*(r42-)*/
		};
		cpu_exec((u32*)&codebase_exec333, (11));
	}
}
local SPELL_EXEC(48_aya_taifu)
{
	if (AYA_LINK_00_NONE != VR0f_AYA_LINK)
	{
		s_aya_kougeki_all_void();
		VR0f_AYA_LINK = AYA_LINK_00_NONE;
		/* �ړ����W�����߂� */
		boss_set_new_position_from_target();/*(�U���ړ����W���^�[�Q�b�g����ݒ�)*/
	}
}
