
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���C�Y���ۂ��J�[�h���`���܂��B
	�Ǝv�������ǁA�S�R������ۂ��Ȃ��B
	-------------------------------------------------------
	�Ƃ肠�����J�[�h��̎����B
	-------------------------------------------------------
	�J�E���^��p���W�X�^�͔p�~���āA�ėp���W�X�^�Ɠ��������B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�ŏI�`�Ԃ��ۂ��z
	-------------------------------------------------------
	���@�_��32���������e�B
	���E�Ɍ��݂Ɍ��B32������1/4���B����͔����e�B
	-------------------------------------------------------
	�V�V�X�e���ŃJ�[�h�ꂪ�g����\��(?)�Ȃ̂ŁA
	�J�[�h����ӎ����ď����Ď���B
	-------------------------------------------------------
	�g�p���W�X�^(�Ă���):
	R08 	�J�E���^�B��{�I��4��Ɉ�񏈗��B
	R09 	32�����e�ɂ���`���ƁB
	R0a 	���E�ŐF��ς��悤�B
	R0b 	�p�x��ێ�����ˁB
	R0c
	R0d
	R0e
	R0f 	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA)
---------------------------------------------------------*/
local SPELL_EXEC(44_ruiz3)
{
	static const u32 codebase_exec[25] =
	{
		MCODE(OP0x02_COUNTER, 4, R08, NAX),// ��{�I��4��Ɉ�񏈗��B
		// (1)	if (0!=(VR08)) {return;}	R8 �� 0 �̏ꍇ�̂ݔ��e�B����ȊO�͔��e���Ȃ��B
		MCODE(OP0x08_BNE_RS, (0x00), R08, (+22)),//(eee+22) /* ���e���Ȃ��ꍇ�A���I���܂ŃW�����v */
		// (2)				// 32�����e�ɂ���`���ƁB
		MCODE(OP0x02_COUNTER, 32, R09, NAX),// 32�����e�ɂ���`���ƁB
		// (3)	if (1==(VR09))	/* �n�߂Ă̏ꍇ[��������] */
		MCODE(OP0x08_BNE_RS, (0x01), R09, (+3)),//(bbb+3)	/* �n�߂Ă̏ꍇ */
		// (4)					// ���E�ŐF��ς��悤�B
		MCODE(OP0x02_COUNTER, 2, R0a, NAX),// ���E�ŐF��ς��悤�B
		// (5)	 (calculate_jiki_nerai);/* ���@�_���p�쐬 */
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),/* ���@�_���p�쐬 */
		// (6)	VR0b = HATSUDAN_R13_angle65536;/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R0b, R13),
		// (7)	(bbb+3:)	/* �n�߂Ă̏ꍇ[�����܂�] */
		MCODE(OP0x08_BNE_RS, (0x00), R0a, (+3)),//(ccc+3)
		// (8)	if (0!=VR0a)	{(VR0b) -= (65536/(4*32));}
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(+(65536/(4*32))),
		// (9)	goto (ddd+2);
		MCODE(OP0x0b_BRA_RS, NAX, NAX, (+2)),
		// (10) (ccc+3:)	if (0==VR0a)	{(VR0b) += (65536/(4*32));}
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R0b, R0b),/*(�����O�������A�h���b�V���O��p����)*/
		(-(65536/(4*32))),
		// (11) (ddd:)	HATSUDAN_R11_speed256 = (t256(1.2) + (VR09 << 3));	/* �e�� */
		// (11) VR11 = (VR09 << 3);
		MCODE(OP0x1f_ASLM_PD, 0x03, R11, R09),/*(�V���[�g�������A�h���b�V���O)*/
		// (12) VR11 = VR11 + (t256(1.2));
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R11, R11),/*(�����O�������A�h���b�V���O��p����)*/
		(t256(1.2)),
		// (13) HATSUDAN_R12_speed_offset			= t256(1);/*(�e�X�g)*/
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R12, NAX),/*(�����O�������A�h���b�V���O)*/
		(t256(1)),
		// (14) HATSUDAN_R13_angle65536 			= (VR0b);/* ���@�_���p */
		MCODE(OP0x01_MOVER_PD, NAX, R13, R0b),
		// (15) HATSUDAN_R14_tama_spec				= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
		MCODE(OP0x1c_MOVEM_PD, LONG_MEMORY_ADDRESSING, R14, NAX),/*(�����O�������A�h���b�V���O)*/
		(DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT),
		// (16) HATSUDAN_R15_bullet_obj_type		= (BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + VR0a;	/* [ �e] */
		MCODE(OP0x1b_ADDM_LONG_PD, LONG_ONLY, R15, R0a),/*(�����O�������A�h���b�V���O��p����)*/
		(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA),
		// (17) 	(1�e����)
		MCODE(OP0x0c_hatudan_system_regist_tama, HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE, NAX, NAX),/*(42-)*/
		// (18) (eee+22:)
		MCODE(OP0x00_EXIT, NAX, NAX, NAX),/*(�I��[�u�����`�n���߂�����ꍇ�A�K���v��])*/
	};
	cpu_exec((u32*)&codebase_exec, (17));
}

#if 0
[ID:supeka3500] 			; //���ʕ�����
����u�J�[�h��̂Ă��Ɓv	; //����

[init]	; //�������Z�N�V����
r0		44		; //�o�^�ԍ�(r0�͏�ɒ萔0�Ȃ̂ŏ������ł��Ȃ��B�����ŁA�������Z�N�V�����ɏ������ꍇ�A�o�^�ԍ��ɂ���B)
r1		5
r8		125
;	�g�p���W�X�^(�Ă���):
;	r1	��芸����4��Ɉ��ł�����B
;	r2	32�����e�ɂ���`���ƁB
;	r3	���E�ŐF��ς��悤�B
;	r4	�p�x��ێ�����ˁB

[spell] 	; //���e�Z�N�V����
{
	; // �J�[�h��͖��߂ƍő�ň���3�܂ŁB
	count_up_limit r1, 4, 0 			; ��芸����4��Ɉ��ł�����B
	if_equal 0, r1						; // if�͈���2�܂ň���3�̓V�X�e�����g��(����3==�s�����̏ꍇ�̃W�����v��̈ʒu)
	{
		count_up_limit r2, 32, 0		; 32�����e�ɂ���`���ƁB
		if_equal 1, r2					; �n�߂Ă̏ꍇ
		{
			count_up_limit r3, 2, 0 	; ���E�ŐF��ς��悤�B
			jiki_nerai r4				; ���@�_���p�쐬  CPUREG_angleCCW65536_jiki_nerai();/*	*/
			set r4, HATSUDAN_R13_angle65536 	; // /* ���@�_���p */
		}
		if_equal 0, r3
		{
			add r4, 512 				; 512 == ((65536/4)/32)
		}
	;	else �̓J�[�h��ł͑��݂��Ȃ��B
		if_equal 1, r3
		{
			add r4, -512				; 512 == ((65536/4)/32)
		}
		set HATSUDAN_R11_speed256,			(t256(1.2)+(r2<<3)) 			; /* �e�� */
		set HATSUDAN_R12_speed_offset,		t256(1) 						; /*(�e�X�g)*/
		set HATSUDAN_R13_angle65536,		(r4)							;
		set HATSUDAN_R14_tama_spec, 		(DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT)			; /* (r33-)�W���e */
		set HATSUDAN_R15_bullet_obj_type,	(BULLET_KUNAI12_BASE + TAMA_IRO_01_AKA) + r3		; /* [ �e] */
		hatudan_system_regist_single												; /* (1�e����) */
	}
	label 123	;
	jump 123	;
}
#endif
