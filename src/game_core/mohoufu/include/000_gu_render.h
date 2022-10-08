
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	���̃t�@�C���͒��ڃC���N���[�h���܂���B
	"game_main.h" ����̂݊ԐړI�ɃC���N���[�h���܂��B
---------------------------------------------------------*/

#ifndef _PSP_GU_RENDER_H_
#define _PSP_GU_RENDER_H_

enum
{
	GU_HAIKEI_00_2D_256 = 0,	/* 256x256�e�N�X�`����~���l�߂�2D�B */
	GU_HAIKEI_01_3D_TEST01, 	/* 3D�̃e�X�g */
	GU_HAIKEI_02_EIENTEI,		/* "�i����"�̗\��B */
	GU_HAIKEI_03_FAKE_3D,		/* �e�N�X�`���ό`�ɂ��[��3D �����I�ɖ����Ȃ�\��B */
	GU_HAIKEI_99_MAX,
};

/*---------------------------------------------------------
	�w�i�w���p�[
---------------------------------------------------------*/

/* �w�i�������F�� 32bit color�Ŏw�肷��B */
extern void gu_set_bg_u32_clear_color(u32 set_u32_clear_color);

/*---------------------------------------------------------
about...
	draw screen:	480x272 SDL surface. this screen can drawing.(for drawing virtual screen)
	temp screen:	480x272 SDL surface. this screen not drawing.(temporary virtual screen)
	-------------------------------------------------------
	draw screen:(�`�扼�z���)
		this screen can drawing. or not drawing, used programmable switch.
		this screen do not directly loading files.
		(���̉�ʂ͕`��p�ł��B�摜�̓ǂݍ��݂͂��܂���B
		SDL�̕\����� �Ǝ��Ă��܂����A�Ⴂ�� SDL�̕\����� �͕\���������Ȃ��̂ł����A
		���̉�ʂ� �v���O�����ŕ\���� on/off �ł��܂��B)
	temp screen:(�ޔ����z���)
		this screen can not drawing.
		this screen can loading files.(gazo.png, gazo.jpg, ... ) and
		psp_move_screen(MODE_01_POP);// image copy, temp screen to draw screen.
		when drawing.
		(���̉�ʂ͑ޔ�p�ł��B�摜�̓ǂݍ��݃v���O�����́A���̉�ʗp�ɂ����v��܂���B
		�摜��ǂݍ��񂾂�A
		psp_move_screen(MODE_01_POP);
		�ŁA�`�扼�z��ʂɓ��e���R�s�[���鎖�ŉ摜��\���ł��܂��B)
	-------------------------------------------------------
---------------------------------------------------------*/
enum
{
	MODE_00_PUSH = 0,/*[saved draw screen to temp screen.](���z�X�N���[����ޔ�)*/
	MODE_01_POP,/*([loaded temp screen to draw screen]���z�X�N���[���𕜊�)*/
};
extern void psp_move_screen(int set_mode);

/*---------------------------------------------------------
	�w�i�̕`��v���O������o�^����B
	�w�i�J�[�h
---------------------------------------------------------*/

/* �J�[�h���ɔw�i�̃v���O������ނ�ݒ� */

/*---------------------------------------------------------
	���j���[�V�X�e��
---------------------------------------------------------*/

extern void psp_pause_filter(void);/*[draw flitering, only draw screen.](�`�扼�z�X�N���[���ɂ������G�t�F�N�g��������)*/
extern void psp_clear_screen(void);/*[image clear, only draw screen.](�`�扼�z�X�N���[�������ŏ���)*/

#endif /* _PSP_GU_RENDER_H_ */
