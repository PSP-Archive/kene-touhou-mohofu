
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	�̂̂����ۂ��J�[�h�𐶐����悤�Ǝv�������ǖ����ł����B
---------------------------------------------------------*/

/*---------------------------------------------------------
	�g2�ʒ�-�{�X ��d�� �ʏ�U��1(1/3)
	-------------------------------------------------------
	�΃N�i�C�e
	������n�߂āA���v���A2�i�Â�
	-------------------------------------------------------
	�g�p���W�X�^
	R08 	�J�E���^�B
	R09 	�p�x�����p�B
	R0a 	���x�����p�B
	R0b 	���Z�p(�e�L�g�[)
	R0c 	���Z�p�����l(seed)��ێ��B(�e�L�g�[)
---------------------------------------------------------*/
local SPELL_EXEC(1e_momiji_no_nonoji)
{
//	if (64 == VR10_BOSS_SPELL_TIMER) /* �n�߂ɏ����� */
	static const u32 codebase111[2] =
	{
		MCODE(OP0x02_COUNTER, 192, R08, NAX),
		NAX
	};
	cpu_exec((u32*)&codebase111, (1));//	/*	�J��Ԃ��J�E���^�B */
	if (1==VR08) /* �n�߂ɏ����� */
	{
		VR09 = 0;
		VR0a = 0;
	}
//	if ((64-(48)) < VR10_BOSS_SPELL_TIMER)
	if (48 > VR08) /* 48�ȉ��Ȃ猂�� */
	{
	//	if (0x00 == (VR10_BOSS_SPELL_TIMER & (2-1)))/*(2���1��)*/
		{
				HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
				HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_8000_NON_TILT);/* (r33-)��X���e */
				HATSUDAN_R15_bullet_obj_type	= (BULLET_OODAMA32_00_AOI); 	/* [��ʒe] �����̖������� */
			for (VR03_i=0; VR03_i<(1+cg_VR20_game_difficulty); VR03_i++)/*(2�i�Â�)*/
			{
			//	HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a<<2)+(VR03_i<<6));		/* �e�� */
				HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a	)+(VR03_i<<6)); 		/* �e�� */
				HATSUDAN_R13_angle65536 		= (VR09);
				hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
			}
			VR09 += (65536/48); /* �����猂���n�߂�B */
			VR0a++;
			#if (1)
			CPU_CALL(cpu_auto_bullet_play_default);
			#endif
		}
	}
	if (192 > VR08) /* 192�ȉ��Ȃ猂�� */
	{
		if (96 < VR08) /* 96�ȏ�Ȃ猂�� */
		{
			HATSUDAN_R12_speed_offset		= t256(1);/*(�e�X�g)*/
			HATSUDAN_R14_tama_spec			= (DANMAKU_LAYER_00)|(TAMA_SPEC_0000_TILT);/* (r33-)�W���e */
			HATSUDAN_R15_bullet_obj_type	= (BULLET_KOME_BASE + TAMA_IRO_00_SIRO);			/* [���Ēe] */
			HATSUDAN_R11_speed256			= (t256(0.6)+(VR0a));		/* �e�� */
			HATSUDAN_R13_angle65536 		= (VR09);
			VR0c += VR0b; /* �e�L�g�[? */
			VR0b = VR0c;
			VR0b = (VR0b >> (5));	/*( /=32 ���������J�[�h���߂��K�v�B)*/
		//	/* 1365.333333 == (65536/48) �ő���Z�p�x�������Ă݂�B */
			VR09 -= 1365; /* (192-96)/48 ==2 �łQ����锤�B�e�L�g�[? */
			VR09 -= VR0b; /* �e�L�g�[? */
			hatudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);/*(r42-)*/
		}
	}
}
