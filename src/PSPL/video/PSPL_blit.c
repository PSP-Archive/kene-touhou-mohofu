
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	/src/SDL231/video/SDL_blit.c
	date:		2011/02/04
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2FSDL_blit.c
	revision:	441(2366以下では最新)
	-------------------------------------------------------
	powerd by google 翻訳。
--------------------------------------------------------- */

/*
psp - リビジョン 441Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/video/SDL_blit.c
リビジョン 440 - 詳細表示 - 前のリビジョンとの差分 - 最終更新日時 - ログを見る -
*/

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
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

#include "../include/PSPL_error.h"			/* 取り敢えず(仮) */
#include "../include/PSPL_video.h"			/* 取り敢えず(仮) */
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
汎用ソフトウェア矩形図形転送描画ルーチン。
*/
static int SDL_SoftBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
	int error_flag;
	int src_locked;
	int dst_locked;
	/*
	Everything is okay at the beginning...
	開始時の初期状態は OK に設定しておきます。
	*/
	error_flag = (0);/*(OK)*/
	/*
	Lock the destination if it's in hardware.
	ハードウェアの場合は、転送先をロックします。
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
	ハードウェアの場合は転送元をロックします。
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
	転送元と転送先バッファのポインタと矩形図形転送描画の設定をします。
	*/
	if ((/*(OK)*/0==error_flag) && (srcrect->w) && (srcrect->h))
	{
		SDL_BlitInfo info;
		SDL_loblit RunBlit;
		/*
		Set up the blit information.
		描画情報を設定します。
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
		実際のソフトウェア描画を実行します。
		*/
		RunBlit(&info);
	}
	/*
	We need to unlock the surfaces if they're locked.
	それらがロックされている場合
	我々はサーフェスのロックを解除する必要があります。
	*/
	if (dst_locked) 	{SDL_UnlockSurface(dst);}
	if (src_locked) 	{SDL_UnlockSurface(src);}
	/*
	Blit is done!
	描画が終わったよ！
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
		SDL_memcpy(dst, src, w);/* normal. 通常の処理 */
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
多くの描画ルーチンの中のどれがサーフェス上に設定されているのかを探します。
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
	ハードウェアアクセラレーションで描画が出来るのかどうか判断します。
	*/
	surface->flags &= ~SDL_HWACCEL;
	/*
	Get the blit function index, based on surface mode.
	サーフェスモードに基づいた描画関数インデックスを取得します。
	*/
	/*
	{
		0 = nothing,		0: なし
		1 = colorkey,		1: 抜き色指定
		2 = alpha,			2: アルファ指定
		3 = colorkey+alpha	3: 抜き色+アルファ指定
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
	コピー描画で特別に"同じものが無い"ケースをチェックします。
	*/
	if (surface->map->identity && blit_index == 0)
	{
		surface->map->sw_data->blit = SDL_BlitCopy;
		/*
		Handle overlapping blits on the same surface.
		同じサーフェス上の重複する描画処理をハンドルします。
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
	我々は描画関数を持っていることを確認してください。
	*/
	if (surface->map->sw_data->blit == NULL)
	{
		SDL_InvalidateMap(surface->map);
		SDL_SetError_bbb("Blit combination not supported");
		return (-1);
	}
	/*
	Choose software blitting function.
	ソフトウェア描画する関数を選択します。
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
