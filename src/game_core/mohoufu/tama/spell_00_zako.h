
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�G���̃J�[�h���`���܂��B
---------------------------------------------------------*/

// ==================================== [�X�y�J���E] ==================================== //


#if 0
/*---------------------------------------------------------
	�A���X(��)	����@�J�[�h
	-------------------------------------------------------
	�e�L�g�[
---------------------------------------------------------*/
#define cg_BOSS_DATA_38_angleCCW1024 cg_BOSS_DATA_38_angleCCW65536
local SPELL_EXEC(09_zako_sentakki)
{
	if (0 == (VR10_BOSS_SPELL_TIMER & 0x03))
	{
		cg_BOSS_DATA_38_angleCCW1024 -= (int)(1024/24);
		mask1024(cg_BOSS_DATA_38_angleCCW1024);
	//
		#if 0
			HATSUDAN_R16_n_way					= (8);										/* [8way] */
			HATSUDAN_R17_div_angle65536 		= (int)(65536/24);							/* �����p�x */
	//
			HATSUDAN_R11_speed256				= (t256(2.0)+((VR10_BOSS_SPELL_TIMER)<<2)); /* �e�� */
		{
			HATSUDAN_R13_angle65536 			= ((cg_BOSS_DATA_38_angleCCW1024)<<6);				/* �p�x */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [�ؒe] */
			bullet_regist_multi_vector_direct();
		//
			HATSUDAN_R13_angle65536 			= ((-((cg_BOSS_DATA_38_angleCCW1024)<<6))&(65536-1));		/* �p�x */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [���ؒe] */
			bullet_regist_multi_vector_direct();
		}
		#endif
		#if 1
			HATSUDAN_R12_speed_offset			= t256(1);		/* ���������e */	/* ���̕����ɂȂ邩������ */
			HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R16_n_way					= (8);										/* [8way] */
			HATSUDAN_R17_div_angle65536 		= (int)(65536/24);							/* �����p�x */
	//
			HATSUDAN_R11_speed256				= (t256(1.0)+((VR10_BOSS_SPELL_TIMER)<<2)); /* �e�� */
		{
			int first_angle65536 = ((cg_BOSS_DATA_38_angleCCW1024)<<6);
			HATSUDAN_R13_angle65536 			= (first_angle65536);						/* �p�x */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_03_AOI);					/* [�ؒe] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r33-) */
		//
			HATSUDAN_R13_angle65536 			= ((-first_angle65536)&(65536-1));			/* �p�x */
			HATSUDAN_R15_bullet_obj_type		= (BULLET_UROKO14_BASE + TAMA_IRO_04_MIZU_IRO); 			/* [���ؒe] */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);/* (r33-) */
		}
		#endif
		#if (1)
		CPU_CALL(cpu_auto_bullet_play_default);
		#endif
	}
}
#endif

// ==================================== [�X�y�J���E] ==================================== //

/*---------------------------------------------------------
	[���̑�] ���ؒe easy�p
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
local SPELL_EXEC(09_test_inuno_fuguri)
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
			// (3) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
			MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),
			((DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT)),
			// (4) /
			//	const u32 VR0b = (((~(VR10_BOSS_SPELL_TIMER))>>3)&0x1f);/* �e�L�g�[�ɑ傫�����Ă݂�B */
			MCODE(OP0x02_COUNTER, 24, R0b, NAX),
			NAX
		};
		cpu_exec((u32*)&codebase222, (2));//		/*(r34, 32)*/
		#define NUM_05_OF_CIRCLE_ONE	(5)/* ���(�����5�e) */
		for (VR02_j=0; VR02_j<(65536); VR02_j+=(65536/NUM_05_OF_CIRCLE_ONE))/* ��� */
		{
			static const u32 codebase444[22] =
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

			// ����
			// �t���(��CCW������A�E���CW)
				// (00) HATSUDAN_R11_speed256			= (t256(0.50)); 				/* �e�� */		/*3.5 2.5 2.0*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R11, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(0.75)),
				// (00) HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
				(t256(1)),
			//	HATSUDAN_R13_angle65536 		= (((VR0a)+VR0d) & (65536-1));			/* ���˒��S�p�x / ����@�\(���@�_��/��) */
				// (00) VR13 = VR0d;
				MCODE(OP0x01_MOVER_PD, NAX, R13, R0d),
				// (00) VR13 += VR0a;/*fps_factor*/
				MCODE(OP0x04_ADDR_PD, NAX, R13, R0a),
				// (00) HATSUDAN_R15_bullet_obj_type	= (BULLET_WAKU12_BASE + TAMA_IRO_03_AOI);// 	/* [�g�t�� �ےe] */
				MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R15, NAX),/*(�����O�������A�h���b�V���O)*/
				((BULLET_WAKU12_BASE + TAMA_IRO_03_AOI)),
				// (00) (1�e����)
				MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
			//	(LOOP_contine:) 	LOOP_contine:	;
				// (00) VR0d += (int)(65536/3);
				MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0d, R0d),
				((int)(65536/3)),
				// (00) VR03_i--;
				MCODE(OP0x01_MOVER_PD, (u8)(-1), R03_i, R03_i), /*(�C���f�b�N�X�t)*/
				// (00) if (0 != VR03_i) {goto for_loop_i;}
				MCODE(OP0x08_BNE_RS, (0), R03_i, (u8)(-13)),//(LOOP_contine)
				// (00)
				MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
			};
			cpu_exec((u32*)&codebase444, ((23*2)+8));//
		}
		static const u32 codebase333[8] =
		{
			// ��]��
			// VR09 += (int)(	   (65536/(22)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
			MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R09, R09),
			((int)(    (65536/(22)))),
			// VR0a += (int)(65536-(65536/(15)));/* ROTATE_ANGLE */ 		/*(65536/(6*8))*/		/* �p�x(65536[360/360�x]�� 48����) */
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
			MCODE(OP0x08_BNE_RS, (0x00), R0c, (+1)),//	(ccc+1)
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

