
/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	/src/SDL231/video/SDL_blit.c
	date:		2011/02/04
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2FSDL_blit.c
	revision:	441(2366�ȉ��ł͍ŐV)
	-------------------------------------------------------
	powerd by google �|��B
--------------------------------------------------------- */

/*
psp - ���r�W���� 441Subversion ���|�W�g���ꗗ: pspps2ps2wareps3ps3warepspware���r�W����:(root)/trunk/SDL/src/video/SDL_blit.c
���r�W���� 440 - �ڍו\�� - �O�̃��r�W�����Ƃ̍��� - �ŏI�X�V���� - ���O������ -
*/

/*---------------------------------------------------------
	�����͕핗 �` Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	PSPL - PSP customised SDL Layer port.
	SDL Copyright (C) 1997-2004 Sam Lantinga.
---------------------------------------------------------*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: PSPL_blit.c,v 1.13 2005/04/17 10:40:41 icculus Exp $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/PSPL_error.h"			/* ��芸����(��) */
#include "../include/PSPL_video.h"			/* ��芸����(��) */
#include "PSPL_sysvideo.h"
#include "PSPL_blit.h"
#include "PSPL_pixels_c.h"
#include "PSPL_memops.h"

#if (1==USE_RLEACCEL)
	#include "PSPL_RLEaccel_c.h"
#endif

#ifndef SDL_SetError_bbb
	#define SDL_SetError_bbb( ... )
#endif

/*
The general purpose software blit routine.
�ėp�\�t�g�E�F�A��`�}�`�]���`�惋�[�`���B
*/
static int SDL_SoftBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
	int error_flag;
	int src_locked;
	int dst_locked;
	/*
	Everything is okay at the beginning...
	�J�n���̏�����Ԃ� OK �ɐݒ肵�Ă����܂��B
	*/
	error_flag = (0);/*(OK)*/
	/*
	Lock the destination if it's in hardware.
	�n�[�h�E�F�A�̏ꍇ�́A�]��������b�N���܂��B
	*/
	dst_locked = (0);
	if (SDL_MUSTLOCK(dst))
	{
		if (0 > SDL_LockSurface(dst))
				{error_flag = (-1);/*(NG)*/}
		else	{dst_locked = (1);}
	}
	/*
	Lock the source if it's in hardware.
	�n�[�h�E�F�A�̏ꍇ�͓]���������b�N���܂��B
	*/
	src_locked = (0);
	if (SDL_MUSTLOCK(src))
	{
		if (0 > SDL_LockSurface(src))
				{error_flag = (-1);/*(NG)*/}
		else	{src_locked = (1);}
	}
	/*
	Set up source and destination buffer pointers, and BLIT!
	�]�����Ɠ]����o�b�t�@�̃|�C���^�Ƌ�`�}�`�]���`��̐ݒ�����܂��B
	*/
	if ((/*(OK)*/0==error_flag) && (srcrect->w) && (srcrect->h))
	{
		SDL_BlitInfo info;
		SDL_loblit RunBlit;
		/*
		Set up the blit information.
		�`�����ݒ肵�܂��B
		*/
		info.s_pixels	= (u8 *)src->pixels +
			((u16)srcrect->y * src->pitch) +
			((u16)srcrect->x * src->format->BytesPerPixel);
		info.s_width	= srcrect->w;
		info.s_height	= srcrect->h;
		info.s_skip 	= (src->pitch-info.s_width * src->format->BytesPerPixel);
		info.d_pixels	= (u8 *)dst->pixels +
			((u16)dstrect->y * dst->pitch) +
			((u16)dstrect->x * dst->format->BytesPerPixel);
		info.d_width	= dstrect->w;
		info.d_height	= dstrect->h;
		info.d_skip 	= (dst->pitch-info.d_width * dst->format->BytesPerPixel);
		info.aux_data	= src->map->sw_data->aux_data;
		info.src		= src->format;
		info.table		= src->map->table;
		info.dst		= dst->format;
		RunBlit 		= src->map->sw_data->blit;
		/*
		Run the actual software blit.
		���ۂ̃\�t�g�E�F�A�`������s���܂��B
		*/
		RunBlit(&info);
	}
	/*
	We need to unlock the surfaces if they're locked.
	����炪���b�N����Ă���ꍇ
	��X�̓T�[�t�F�X�̃��b�N����������K�v������܂��B
	*/
	if (dst_locked) 	{SDL_UnlockSurface(dst);}
	if (src_locked) 	{SDL_UnlockSurface(src);}
	/*
	Blit is done!
	�`�悪�I�������I
	*/
//	return ((0==error_flag) ? 0 : -1);
	return (error_flag);
}

static void SDL_BlitCopy(SDL_BlitInfo *info)
{
	const int w 	= info->d_width * info->dst->BytesPerPixel;
	int h;	  h 	= info->d_height;
	int srcskip;
	int dstskip;
	srcskip 	= w + info->s_skip;
	dstskip 	= w + info->d_skip;
	u8 *src;
	u8 *dst;
	src 		= info->s_pixels;
	dst 		= info->d_pixels;
	while (h--)
	{
		SDL_memcpy(dst, src, w);/* normal. �ʏ�̏��� */
		src += srcskip;
		dst += dstskip;
	}
}

static void SDL_BlitCopyOverlap(SDL_BlitInfo *info)
{
	const int w 	= info->d_width * info->dst->BytesPerPixel;
	int h;	  h 	= info->d_height;
	int srcskip;
	int dstskip;
	srcskip 	= w + info->s_skip;
	dstskip 	= w + info->d_skip;
	u8 *src;
	u8 *dst;
	src 		= info->s_pixels;
	dst 		= info->d_pixels;
	if (dst < src)
	{
		while (h--)
		{
			SDL_memcpy(dst, src, w);
			src += srcskip;
			dst += dstskip;
		}
	}
	else
	{
		src += ((h-1) * srcskip);
		dst += ((h-1) * dstskip);
		while (h--)
		{
			SDL_revcpy(dst, src, w);
			src -= srcskip;
			dst -= dstskip;
		}
	}
}

/*
Figure out which of many blit routines to set up on a surface.
�����̕`�惋�[�`���̒��̂ǂꂪ�T�[�t�F�X��ɐݒ肳��Ă���̂���T���܂��B
*/
int SDL_CalculateBlit(SDL_Surface *surface)
{
	int blit_index;
	/* Clean everything out to start */
	#if (1==USE_RLEACCEL)
	if ((surface->flags & SDL_RLEACCEL) == SDL_RLEACCEL)
	{
		SDL_UnRLESurface(surface, 1);
	}
	#endif /*(USE_RLEACCEL)*/
	surface->map->sw_blit = NULL;
	/*
	Figure out if an accelerated hardware blit is possible.
	�n�[�h�E�F�A�A�N�Z�����[�V�����ŕ`�悪�o����̂��ǂ������f���܂��B
	*/
	surface->flags &= ~SDL_HWACCEL;
	/*
	Get the blit function index, based on surface mode.
	�T�[�t�F�X���[�h�Ɋ�Â����`��֐��C���f�b�N�X���擾���܂��B
	*/
	/*
	{
		0 = nothing,		0: �Ȃ�
		1 = colorkey,		1: �����F�w��
		2 = alpha,			2: �A���t�@�w��
		3 = colorkey+alpha	3: �����F+�A���t�@�w��
	}
	*/
	blit_index = 0;
	blit_index |= (!!(surface->flags & SDL_SRCCOLORKEY))	  << 0;
	if (surface->flags & SDL_SRCALPHA
		 && (surface->format->alpha != SDL_ALPHA_OPAQUE
		 || surface->format->Amask) )
	{
		blit_index |= 2;
	}
	/*
	Check for special "identity" case -- copy blit.
	�R�s�[�`��œ��ʂ�"�������̂�����"�P�[�X���`�F�b�N���܂��B
	*/
	if (surface->map->identity && blit_index == 0)
	{
		surface->map->sw_data->blit = SDL_BlitCopy;
		/*
		Handle overlapping blits on the same surface.
		�����T�[�t�F�X��̏d������`�揈�����n���h�����܂��B
		*/
		if (surface == surface->map->dst)
		{
			surface->map->sw_data->blit = SDL_BlitCopyOverlap;
		}
	}
	else
	{
		if (surface->format->BitsPerPixel < 8)
		{
			surface->map->sw_data->blit = SDL_CalculateBlit0(surface, blit_index);
		}
		else
		{
			switch (surface->format->BytesPerPixel)
			{
			case 1: 	surface->map->sw_data->blit = SDL_CalculateBlit1(surface, blit_index);	break;
			case 2: 	/*fall_through*/
			case 3: 	/*fall_through*/
			case 4: 	surface->map->sw_data->blit = SDL_CalculateBlitN(surface, blit_index);	break;
			default:	surface->map->sw_data->blit = NULL; 	break;
			}
		}
	}
	/*
	Make sure we have a blit function.
	��X�͕`��֐��������Ă��邱�Ƃ��m�F���Ă��������B
	*/
	if (surface->map->sw_data->blit == NULL)
	{
		SDL_InvalidateMap(surface->map);
		SDL_SetError_bbb("Blit combination not supported");
		return (-1);
	}
	/*
	Choose software blitting function.
	�\�t�g�E�F�A�`�悷��֐���I�����܂��B
	*/
	#if (1==USE_RLEACCEL)
	if ((surface->flags & SDL_RLEACCELOK)
	   && (surface->flags & SDL_HWACCEL) != SDL_HWACCEL)
	{
		if (surface->map->identity
		   && (blit_index == 1
			   || (blit_index == 3 && !surface->format->Amask)))
		{
			if (SDL_RLESurface(surface) == 0)
			{
				surface->map->sw_blit = SDL_RLEBlit;
			}
		}
		else
		if (blit_index == 2 && surface->format->Amask)
		{
			if (SDL_RLESurface(surface) == 0)
			{
				surface->map->sw_blit = SDL_RLEAlphaBlit;
			}
		}
	}
	#endif /*(USE_RLEACCEL)*/
	if (surface->map->sw_blit == NULL)
	{
		surface->map->sw_blit = SDL_SoftBlit;
	}
	return (0);
}
