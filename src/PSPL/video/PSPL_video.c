
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	PSPL - PSP customised SDL Layer port.
	SDL Copyright (C) 1997-2004 Sam Lantinga.
	-------------------------------------------------------
	/src/SDL231/video/SDL_video.c
	date:		2011/02/04
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2FSDL_video.c&peg=2366
	revision:	448(2366以下では最新)
	-------------------------------------------------------
	/src/SDL231/video/SDL_pspvideo.c
	date:		2011/02/04
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2Fpsp%2FSDL_pspvideo.c
	revision:	2366(2366以下では最新)
	-------------------------------------------------------
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2Fpsp%2FSDL_pspvideo.h
	revision:	1444(2366以下では最新)
	source: 	http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fvideo%2FSDL_surface.c
	revision:	440(2366以下では最新)
	-------------------------------------------------------
	PSP port contributed by:
	Marcus R. Brown <mrbrown@ocgnet.org>
	Jim Paris <jim@jtan.com>
	-------------------------------------------------------
	powerd by google 翻訳。
---------------------------------------------------------*/

/*
psp - リビジョン 448Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/video/SDL_video.c @ 2366
リビジョン 441 - 詳細表示 - 前のリビジョンとの差分 - 最終更新日時 - ログを見る -
psp - リビジョン 2366Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/video/psp/SDL_pspvideo.c
リビジョン 1689 - 詳細表示 - 前のリビジョンとの差分 - 最終更新日時 - ログを見る -
psp - リビジョン 1464Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/video/psp/SDL_pspvideo.h
リビジョン 1444 - 詳細表示 - 前のリビジョンとの差分 - 最終更新日時 - ログを見る -
psp - リビジョン 441Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/video/SDL_surface.c
リビジョン 440 - 詳細表示 - 前のリビジョンとの差分 - 最終更新日時 - ログを見る -
*/

#ifdef SAVE_RCSID
static char rcsid  = "@(#) $Id: PSPL_surface.c,v 1.21 2005/04/17 10:40:41 icculus Exp $";
static char rcsid2 = "@(#) $Id: PSPL_nullvideo.h,v 1.4 2004/01/04 16:49:24 slouken Exp $";
#endif

#include <psptypes.h>
#include <pspge.h>

#include <pspkernel.h>
//#include <pspkernel.h>
//#include <psputils.h>
#include <psputils.h>
#include <pspdisplay.h>
#include <pspgu.h>
//#include <pspgu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "./../include/PSPL.h"			/* 取り敢えず(仮) */
#include "./../include/PSPL_error.h"	/* 取り敢えず(仮) */
#include "./../include/PSPL_video.h"	/* 取り敢えず(仮) */

//#include "PSPL_events.h"
//#include "PSPL_mutex.h"
#include "PSPL_sysvideo.h"
//#include "PSPL_cursor_c.h"
//#include "PSPL_sysevents.h"
#include "PSPL_blit.h"

#include "PSPL_pixels_c.h"
#include "PSPL_events_c.h"

#include "PSPL_memops.h"
//#include "PSPL_leaks.h"

#if (1==USE_RLEACCEL)
	#include "PSPL_RLEaccel_c.h"
#endif

#ifndef SDL_OutOfMemory_bbb
	#define SDL_OutOfMemory_bbb(aaa)
#endif

#ifndef SDL_SetError_bbb
	#define SDL_SetError_bbb( ... )
#endif


/* The high-level video driver subsystem */

static	SDL_Surface *pspl_screen;

#define SCREEN_480_WIDTH	(480)
#define SCREEN_272_HEIGHT	(272)



/*---------------------------------------------------------
	サーフェイス基本処理
---------------------------------------------------------*/

/*---------------------------------------------------------
	2つの画像が重なっているか判断する。
	重なっている場合 TRUE 、
	それ以外は FALSE 。
	-------------------------------------------------------
	A function to calculate the intersection of two rectangles:
	2つの四角形の交差部分を計算する関数:
	return TRUE if the rectangles intersect, FALSE otherwise.
	矩形が交差した場合 TRUE を返し、そうでない場合は FALSE 。
---------------------------------------------------------*/

/* psp専用の命令(pspのcpuにしか無いアセンブラ命令)を活用する。(組み込み関数) */
#ifndef psp_min
	#define psp_min __builtin_allegrex_min
#endif
#ifndef psp_max
	#define psp_max __builtin_allegrex_max
#endif

/*---------------------------------------------------------
	-------------------------------------------------------
	Set the clipping rectangle for a blittable surface.
	blit転送可能なサーフェスのクリッピング矩形を設定します。
---------------------------------------------------------*/
#if (0)/*(r42ok?)*/
static SDL_bool SDL_SetClipRect(SDL_Surface *surface, const SDL_Rect *A/*rect*/)
{
	/* Don't do anything if there's no surface to act on */
	if (0==surface) 	{return (SDL_FALSE);}
//
	/* Set up the full surface rectangle */
	SDL_Rect full_rect;
	full_rect.x = 0;
	full_rect.y = 0;
	full_rect.w = surface->w;
	full_rect.h = surface->h;
	/* Set the clipping rectangle */
	if (NULL == A/*rect*/)
	{
		surface->clip_rect = full_rect;
		return (1);
	}
//	return SDL_IntersectRect();
//	static __inline__ SDL_bool SDL_IntersectRect()
//	const SDL_Rect *A		= rect;
	const SDL_Rect *B		= &full_rect;
	SDL_Rect *intersection	= &surface->clip_rect;
	{
	int Amin;
	int Amax;
	int Bmin;
	int Bmax;
	/* Horizontal intersection */
	Amin = A->x;	Amax = Amin + A->w;
	Bmin = B->x;	Bmax = Bmin + B->w;
//	if (Amin < Bmin)	{Amin = Bmin;}
	Amin = psp_max(Amin, Bmin);
	intersection->x = Amin;
//	if (Amax > Bmax)	{Amax = Bmax;}
	Amax = psp_min(Amax, Bmax);
//	intersection->w = ((Amax - Amin) > 0) ? (Amax - Amin) : (0);
	intersection->w = psp_max((Amax - Amin), 0);
	/* Vertical intersection */
	Amin = A->y;	Amax = Amin + A->h;
	Bmin = B->y;	Bmax = Bmin + B->h;
//	if (Amin < Bmin)	{Amin = Bmin;}
	Amin = psp_max(Amin, Bmin);
	intersection->y = Amin;
//	if (Amax > Bmax)	{Amax = Bmax;}
	Amax = psp_min(Amax, Bmax);
//	intersection->h = ((Amax - Amin) > 0) ? (Amax - Amin) : (0);
	intersection->h = psp_max((Amax - Amin), 0);
	return (intersection->w && intersection->h);
	}
}
#else
static __inline__ SDL_bool SDL_IntersectRect(const SDL_Rect *A, const SDL_Rect *B, SDL_Rect *intersection)
{
	int Amin;
	int Amax;
	int Bmin;
	int Bmax;
	/* Horizontal intersection */
	Amin = A->x;	Amax = Amin + A->w;
	Bmin = B->x;	Bmax = Bmin + B->w;
//	if (Amin < Bmin)	{Amin = Bmin;}
	Amin = psp_max(Amin, Bmin);
	intersection->x = Amin;
//	if (Amax > Bmax)	{Amax = Bmax;}
	Amax = psp_min(Amax, Bmax);
//	intersection->w = ((Amax - Amin) > 0) ? (Amax - Amin) : (0);
	intersection->w = psp_max((Amax - Amin), 0);
	/* Vertical intersection */
	Amin = A->y;	Amax = Amin + A->h;
	Bmin = B->y;	Bmax = Bmin + B->h;
//	if (Amin < Bmin)	{Amin = Bmin;}
	Amin = psp_max(Amin, Bmin);
	intersection->y = Amin;
//	if (Amax > Bmax)	{Amax = Bmax;}
	Amax = psp_min(Amax, Bmax);
//	intersection->h = ((Amax - Amin) > 0) ? (Amax - Amin) : (0);
	intersection->h = psp_max((Amax - Amin), 0);
	return (intersection->w && intersection->h);
}
SDL_bool SDL_SetClipRect(SDL_Surface *surface, const SDL_Rect *rect)
{
	SDL_Rect full_rect;
	/* Don't do anything if there's no surface to act on */
	if (0==surface)
	{
		return (SDL_FALSE);
	}
	/* Set up the full surface rectangle */
	full_rect.x = 0;
	full_rect.y = 0;
	full_rect.w = surface->w;
	full_rect.h = surface->h;
	/* Set the clipping rectangle */
	if (0==rect)
	{
		surface->clip_rect = full_rect;
		return (1);
	}
	return SDL_IntersectRect(rect, &full_rect, &surface->clip_rect);
}
#endif//1
//
#if 0
/*"模倣風で未使用"*/void SDL_GetClipRect(SDL_Surface *surface, SDL_Rect *rect)
{
	if (surface && rect)
	{
		*rect = surface->clip_rect;
	}
}
#endif
/*---------------------------------------------------------
	-------------------------------------------------------
	Set up a blit between two surfaces -- split into three parts:
	2つのサーフェスの間の矩形描画を、三つの部分に分けて設定します。
	The upper part, SDL_UpperBlit(), performs clipping and rectangle verification.
	始めに重なる上の部分は、SDL_UpperBlit()を使います。クリッピング処理と長方形の検証を行ないます。
	The lower part is a pointer to a low level accelerated blitting function.
	重なる下の部分は、高速に低水準矩形描画する関数へのポインタです。
	These parts are separated out and each used internally by this
	library in the optimimum places.
	これらの部品は分離し、それぞれが最適な場所で、このライブラリによって内部的に使用されます。
	They are exported so that if you know exactly what you are doing,
	you can optimize your code by calling the one(s) you need.
	それらがエクスポートされるようにあなたがやっているのかを正確に知っていれば、
	あなたが必要なもの（複数可）を呼び出すことによって、コードを最適化することができます。
---------------------------------------------------------*/

/*(領域チェックなし描画)*/
static int SDL_LowerBlit(
	SDL_Surface *src, SDL_Rect *srcrect,
	SDL_Surface *dst, SDL_Rect *dstrect)
{
	/* Check to make sure the blit mapping is valid */
	if ((src->map->dst != dst) ||
		 (src->map->dst->format_version != src->map->format_version))
	{
		if (0 > SDL_MapSurface(src, dst))
		{
			return (-1);/*[ng!エラー(描画できません)]*/
		}
	}
	//
	#if 1//(1==USE_RLEACCEL)
	SDL_blit do_blit;
//	SDL_Rect hw_srcrect;
//	SDL_Rect hw_dstrect;
	/* Figure out which blitter to use */
//	if ((src->flags & SDL_HWACCEL) == SDL_HWACCEL)
//	{
//		if (src == (pspl_screen))
//		{
//			hw_srcrect = *srcrect;
//			hw_srcrect.x += current_video->offset_x;
//			hw_srcrect.y += current_video->offset_y;
//			srcrect = &hw_srcrect;
//		}
//		if (dst == (pspl_screen))
//		{
//			hw_dstrect = *dstrect;
//			hw_dstrect.x += current_video->offset_x;
//			hw_dstrect.y += current_video->offset_y;
//			dstrect = &hw_dstrect;
//		}
//		do_blit = src->map->hw _blit;
//	}
//	else
	{
		do_blit = src->map->sw_blit;
	}
	return (do_blit(src, srcrect, dst, dstrect));/*[描画する]*/
	#else
	return (/*do_blit*/SDL_SoftBlit(src, srcrect, dst, dstrect));/*[描画する]*/
	#endif /*(USE_RLEACCEL)*/
}
/*(領域チェックあり描画)*/
extern int SDL_UpperBlit(
	SDL_Surface *src, SDL_Rect *srcrect,
	SDL_Surface *dst, SDL_Rect *dstrect)
{
	/* Make sure the surfaces aren't locked */
	if (
		(NULL==src) ||
		(NULL==dst)
	)
	{
		/*[サーフェイスが無い場合は描画できない]*/
		SDL_SetError_bbb("SDL_UpperBlit: passed a NULL surface");
		return (-1);/*[ng!エラー(描画できません)]*/
	}
	if (
		(0 != src->locked) ||
		(0 != dst->locked)
	)
	{
		/*[ロックされているサーフェイスは描画できない]*/
		SDL_SetError_bbb("Surfaces must not be locked during blit");
		return (-1);/*[ng!エラー(描画できません)]*/
	}
	SDL_Rect fulldst;
	/* If the destination rectangle is NULL, use the entire dest surface */
	if (NULL == dstrect)
	{
		fulldst.x = fulldst.y = 0;
		dstrect = &fulldst;
	}
	int srcx;
	int srcy;
	int w;
	int h;
	/* clip the source rectangle to the source surface */
	if (srcrect)
	{
		int maxw;
		int maxh;
		srcx = srcrect->x;
		w = srcrect->w;
		if (0 > srcx)	{w += srcx; dstrect->x -= srcx; srcx = 0;}
		maxw = src->w - srcx;
	//	if (w > maxw)	{w = maxw;}
		w = psp_min(w, maxw);
		srcy = srcrect->y;
		h = srcrect->h;
		if (0 > srcy)	{h += srcy; dstrect->y -= srcy; srcy = 0;}
		maxh = src->h - srcy;
	//	if (h > maxh)	{h = maxh;}
		h = psp_min(h, maxh);
	}
	else/*[領域が設定されてなければ全領域]*/
	{
		srcx = srcy = 0;
		w = src->w;
		h = src->h;
	}
	/* clip the destination rectangle against the clip rectangle */
	{
		SDL_Rect *clip = &dst->clip_rect;
		int dx;
		int dy;
		dx = clip->x - dstrect->x;					if (0 < dx) 	{w -= dx;dstrect->x += dx;	srcx += dx;}
		dx = dstrect->x + w - clip->x - clip->w;	if (0 < dx) 	{w -= dx;}
		dy = clip->y - dstrect->y;					if (0 < dy) 	{h -= dy;dstrect->y += dy;	srcy += dy;}
		dy = dstrect->y + h - clip->y - clip->h;	if (0 < dy) 	{h -= dy;}
	}
	if ((0 < w) && (0 < h))
	{
		SDL_Rect sr;
		sr.x = srcx;
		sr.y = srcy;
		sr.w = dstrect->w = w;
		sr.h = dstrect->h = h;
		return SDL_LowerBlit(src, &sr, dst, dstrect);/*[描画する]*/
	}
	dstrect->w = dstrect->h = 0;
	return (0);/*[ok正常(描画する必要がなかった)]*/
}

//static int SDL_FillRect1(SDL_Surface *dst, SDL_Rect *dstrect, u32 color)
//{
//	/* FIXME: We have to worry about packing order.. *sigh* */
//	SDL_SetError_bbb("1-bpp rect fill not yet implemented");
//	return (-1);
//}

//static int SDL_FillRect4(SDL_Surface *dst, SDL_Rect *dstrect, u32 color)
//{
//	/* FIXME: We have to worry about packing order.. *sigh* */
//	SDL_SetError_bbb("4-bpp rect fill not yet implemented");
//	return (-1);
//}

/*
 * This function performs a fast fill of the given rectangle with 'color'
 */
#if 0
#define pSDL_memset4(dst, val, len) 	\
do {									\
	unsigned _count = (len);			\
	unsigned _n = (_count + 3) / 4; 	\
	u32 *_p = (u32 *)(dst); 			\
	u32 _val = (val);					\
	switch (_count /*&(4-1)*/% 4)		\
	{									\
	case 0: do {	*_p++ = _val;		\
	case 3:  *_p++ = _val;				\
	case 2:  *_p++ = _val;				\
	case 1:  *_p++ = _val;				\
		} while (--_n); 				\
	}									\
} while (0)
#else

	#if 1/*(てすと)*/
	extern void memset32(int *dest, int c, int count);
	extern void memset32_uncached(int *dest, int c, int count);
	extern void memcpy32(int *dest, int *src, int count); // 32bit word count
	#endif/*(てすと)*/

	#define pSDL_memset4 memset32
#endif

#if 1
/*---------------------------------------------------------
	サーフェイスクリア専用。
	とりあえず16bit.
	-------------------------------------------------------
---------------------------------------------------------*/

extern int PSPL_FillRect000(SDL_Surface *dst/*, SDL_Rect *dstrect, u32 color*/)
{
	if (SDL_LockSurface(dst) != 0)	{return (-1);}
	//
	/* This function doesn't work on 8 bpp > surfaces. */
//	if (8 > dst->format->BitsPerPixel)
//	{
//		switch (dst->format->BitsPerPixel)
//		{
//		case 1: 	return SDL_FillRect1(dst, dstrect, color);			break;
//		case 4: 	return SDL_FillRect4(dst, dstrect, color);			break;
//	//	default:	SDL_SetError_bbb("Fill rect on unsupported surface format");return (-1);	break;
//		}
//	}
	/* If 'dstrect' == NULL, then fill the whole surface */
//	if (dstrect)
//	{
//		/* Perform clipping */
//		if (!SDL_IntersectRect(dstrect, &dst->clip_rect, dstrect))
//		{
//			return (0);
//		}
//	}
//	else
//	{
//		dstrect = &dst->clip_rect;
//	}
	/* Check for hardware acceleration */
//	if (((dst->flags & SDL_HWSURFACE) == SDL_HWSURFACE) &&
//					video->info.blit_fill)
//	{
//		SDL_Rect hhhdw_rect;
//		if (dst == (pspl_screen))
//		{
//			hhhdw_rect = *dstrect;
//			hhhdw_rect.x += current_video->offset_x;
//			hhhdw_rect.y += current_video->offset_y;
//			dstrect = &hhhdw_rect;
//		}
//		return (video->Fill HW Rect(this, dst, dstrect, color));//廃止済
//	}
	/* Perform software fill */
//	if (dst->format->palette || (/*color*/0 == 0))
	{
		SDL_Rect *dstrect;
			dstrect = &dst->clip_rect;
		u8 *row;
		row = (u8 *)dst->pixels +
			dstrect->y * dst->pitch +
			dstrect->x * dst->format->BytesPerPixel;
		int x;
		int y;
		x = dstrect->w * dst->format->BytesPerPixel;
		/*(アライメントチェック。すべて4byte境界かどうか)*/
		if (// 0==0/*color*/ &&
			!((u32)row & 3) &&	/*(rowが4byte境界か？)*/
			!(x & 3) && 		/*(xが4byte境界か？)*/
			!(dst->pitch & 3)	/*(dst->pitchが4byte境界か？)*/
		)
		{/*(4byteアライメントok。すべて4byte境界。)*/
			x >>= 2;// [4byte単位なので4で割る]
			for (y=dstrect->h; y; y--)
			{
				pSDL_memset4( (void*)row, 0/*color(4つ分)*/, x);/*(4byte境界専用)*/
				row += dst->pitch;
			}
		}
		else
		{/*(4byteアライメントng。4byte境界でない。)*/
			//__PPC__
			{
				for (y=dstrect->h; y; y--)
				{
					memset(row, 0/*color(1つ分)*/, x);/*(境界汎用)*/
					row += dst->pitch;
				}
			}
		}
	}
	SDL_UnlockSurface(dst);
	/* We're done! */
	return (0);
}
#endif//1

#if 0/*(メモ)*/
int SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, u32 color)
{
	int x, y;
	u8 *row;
	/* This function doesn't work on 8 bpp > surfaces. */
//	if (8 > dst->format->BitsPerPixel)
//	{
//		switch (dst->format->BitsPerPixel)
//		{
//		case 1: 	return SDL_FillRect1(dst, dstrect, color);			break;
//		case 4: 	return SDL_FillRect4(dst, dstrect, color);			break;
//	//	default:	SDL_SetError_bbb("Fill rect on unsupported surface format");return (-1);	break;
//		}
//	}
	/* If 'dstrect' == NULL, then fill the whole surface */
	if (dstrect)
	{
		/* Perform clipping */
		if (!SDL_IntersectRect(dstrect, &dst->clip_rect, dstrect))
		{
			return (0);
		}
	}
	else
	{
		dstrect = &dst->clip_rect;
	}
	/* Check for hardware acceleration */
//	if (((dst->flags & SDL_HWSURFACE) == SDL_HWSURFACE) &&
//					video->info.blit_fill)
//	{
//		SDL_Rect hhhdw_rect;
//		if (dst == (pspl_screen))
//		{
//			hhhdw_rect = *dstrect;
//			hhhdw_rect.x += current_video->offset_x;
//			hhhdw_rect.y += current_video->offset_y;
//			dstrect = &hhhdw_rect;
//		}
//		return (video->Fill HW Rect(this, dst, dstrect, color));//廃止済
//	}
	/* Perform software fill */
	if (SDL_LockSurface(dst) != 0)
	{
		return (-1);
	}
	row = (u8 *)dst->pixels+dstrect->y*dst->pitch+
			dstrect->x*dst->format->BytesPerPixel;
	if (dst->format->palette || (color == 0))
	{
		x = dstrect->w*dst->format->BytesPerPixel;
		if (!color && !((u32)row&3) && !(x&3) && !(dst->pitch&3))
		{
			int n = x >> 2;
			for (y=dstrect->h; y; y--)
			{
				pSDL_memset4( (void*)row, 0, n);
				row += dst->pitch;
			}
		}
		else
		{
			//__PPC__
			{
				for (y = dstrect->h; y; y--)
				{
					memset(row, color, x);
					row += dst->pitch;
				}
			}
		}
	}
	else
	{
		switch (dst->format->BytesPerPixel)
		{
		case 2:
			for (y=dstrect->h; y; y--)
			{
				u16 *pixels = (u16 *)row;
				u16 c = color;
				u32 cc = (u32)c << 16 | c;
				int n = dstrect->w;
				if ((u32)pixels & 3)
				{
					*pixels++ = c;
					n--;
				}
				if (n >> 1)
				{	pSDL_memset4( (void*)pixels, cc, n >> 1);
				}
				if (n & 1)
				{	pixels[n - 1] = c;
				}
				row += dst->pitch;
			}
			break;

		case 3:
		//	if (SDL_BYTE ORDER == SDL_BIG_ENDIAN)//not_psp
		//	{color <<= 8;}
			for (y=dstrect->h; y; y--)
			{
				u8 *pixels = row;
				for (x=dstrect->w; x; x--)
				{
					memcpy(pixels, &color, 3);
					pixels += 3;
				}
				row += dst->pitch;
			}
			break;

		case 4:
			for (y = dstrect->h; y; --y)
			{
				pSDL_memset4( (void*)row, color, dstrect->w);
				row += dst->pitch;
			}
			break;
		}
	}
	SDL_UnlockSurface(dst);
	/* We're done! */
	return (0);
}
#endif/*(メモ)*/

/*---------------------------------------------------------
	サーフェイスをロックする。
	-------------------------------------------------------
	Lock a surface to directly access the pixels
	We need to wait for vertical retrace on page flipped displays.
	ピクセルに直接アクセスするためにサーフェスをロック
	我々は、ディスプレイを反転ページ上で垂直帰線を待つ必要がある。
---------------------------------------------------------*/

//	/*static*/extern int SDLVIDEO_PSP_LockHWSurface_aaa(/*_THIS,*/ SDL_Surface *surface);
extern int SDL_LockSurface(SDL_Surface *surface)
{
	if (0==surface->locked)
	{
		/* Perform the lock */
		if (surface->flags & (SDL_HWSURFACE|SDL_ASYNCBLIT))
		{
		//	if (video->LockHWSurface(this, surface) < 0)
		//	if (SDLVIDEO_PSP_LockHWSurface_aaa(/*this,*/ surface) < 0)
		//	if ((0) < 0)
		//	if (/*SDLVIDEO_PSP_LockHWSurface(this, surface)*/(0) < 0)
		//	{
		//		return (-1);
		//	}
		}
		#if (1==USE_RLEACCEL)
		if (surface->flags & SDL_RLEACCEL)
		{
			SDL_UnRLESurface(surface, 1);
			surface->flags |= SDL_RLEACCEL; /* save accel'd state */
		}
		#endif /*(USE_RLEACCEL)*/
		/* This needs to be done here in case pixels changes value */
		surface->pixels = (u8 *)surface->pixels + surface->offset;
	}
	/* Increment the surface lock count, for recursive locks */
	surface->locked++;/*([ロックするとロック参照カウンタが必ず +1])*/
	/* Ready to go.. */
	return (0);/*[okロックできた]*/
}

/*---------------------------------------------------------
	サーフェイス、ロック解除
	-------------------------------------------------------
	Unlock a previously locked surface.
	以前にロックされたサーフェスのロックを解除します。
---------------------------------------------------------*/

extern void SDL_UnlockSurface(SDL_Surface *surface)
{
	/* Only perform an unlock if we are locked. */
	#if (0)
	if (0==surface->locked || (--surface->locked > 0))
	/*
	surface->locked: input.
	3:		return;
	2:		return;
	1:		do unlock;
	0:		return;
//	-1: 	do unlock;//un case.(error)
//	-2: 	do unlock;//un case.(error)
	(ロック参照カウンタが異常値の場合、ロック解除する)
	*/
	{
		return;/*(ロック解除しない)*/
	}
	#endif
	/*
	サーフェイスをアンロックする場合、もし正常ならばアンロックしようとする時点で
	ロック参照カウンタが 1 以上の筈です。
	何故ならロックするとロック参照カウンタが必ず +1 される為、
	ロックしてからアンロックする場合、アンロックしようとする時点で最低でも 1 だからです。
	//
	アンロックしようとする時点で 0 以下の場合は、ロックしないのにアンロックする場合です。
	この場合、特別にロック参照カウンタを操作せず戻ります。(念の為 0 を -1 にしないで戻る)
	//
	この特殊ケース以外の場合、ロック参照カウンタを1減らし、
	ロック参照カウンタが 0 の場合のみアンロックします。
	*/
	#if (1)
		#if (0)/*([念の為 0 を -1 にしないで戻る]あまり意味はなく不要。)*/
	if (0 >= (surface->locked))/*(0もしくは負の場合は異常値[正常値の下限が1])*/
	{
		/*(ロック参照カウンタが異常値の場合、ロック解除しない)*/
		return;/*(ロック解除しない)*/
	}
	else
		#endif
	{
		surface->locked--;/*(ロック参照カウンタ)*/
		if (0 != surface->locked)
		{
			return;/*(ロック解除しない)*/
		}
	}
	#endif
	/*(ロック解除する)*/
	/* Perform the unlock */
	surface->pixels = (u8 *)surface->pixels - surface->offset;

	/* Unlock hardware or accelerated surfaces */
	if (surface->flags & (SDL_HWSURFACE|SDL_ASYNCBLIT))
	{
	//	video->UnlockHWSurface(this, surface);
	//	SDLVIDEO_PSP_UnlockHWSurface_aaa(/*this,*/ surface);
		/* Flush video RAM */
		sceKernelDcacheWritebackAll();
	}
	#if (1==USE_RLEACCEL)
	else
	{
		/* Update RLE encoded surface with new data */
		if ((surface->flags & SDL_RLEACCEL) == SDL_RLEACCEL)
		{
			surface->flags &= ~SDL_RLEACCEL; /* stop lying */
			SDL_RLESurface(surface);
		}
	}
	#endif /*(USE_RLEACCEL)*/
}

/* Public routines */



/*---------------------------------------------------------
	サーフェイス抜き色(透明色)設定
	-------------------------------------------------------
	Set the color key in a blittable surface.
	blit転送可能なサーフェスのカラーキーを設定します。
---------------------------------------------------------*/
int SDL_SetColorKey(SDL_Surface *surface, u32 flag, u32 key)
{
	/* Sanity check the flag as it gets passed in */
	if (flag & SDL_SRCCOLORKEY)
	{
		#if (1==USE_RLEACCEL)
		if (flag & (SDL_RLEACCEL|SDL_RLEACCELOK))
		{
			flag = (SDL_SRCCOLORKEY | SDL_RLEACCELOK);
		}
		else
		#endif /*(USE_RLEACCEL)*/
		{
			flag = (SDL_SRCCOLORKEY);
		}
	}
	else
	{
		flag = (0);
	}

	/* Optimize away operations that don't change anything */
	#if (1==USE_RLEACCEL)
	if (flag == (surface->flags & (SDL_SRCCOLORKEY|SDL_RLEACCELOK)))
	{
		if (key == surface->format->colorkey)
		{
			return (0);
		}
	}
	/* UnRLE surfaces before we change the colorkey */
	if (surface->flags & SDL_RLEACCEL)
	{
		SDL_UnRLESurface(surface, 1);
	}
	#endif /*(USE_RLEACCEL)*/
	if (flag)
	{
		surface->flags |= SDL_SRCCOLORKEY;
		surface->format->colorkey = key;
		if (SDL_HWACCEL == (surface->flags & SDL_HWACCEL))
		{
//廃止済				if ((NULL == (video->Set HW ColorKey)) ||
//廃止済					 (0 > (video->Set HW ColorKey(this, surface, key))))
			{
				surface->flags &= ~SDL_HWACCEL;
			}
		}
		#if (1==USE_RLEACCEL)
		if ((flag & SDL_RLEACCELOK))
		{
			surface->flags |= SDL_RLEACCELOK;
		}
		else
		{
			surface->flags &= ~SDL_RLEACCELOK;
		}
		#endif /*(USE_RLEACCEL)*/
	}
	else
	{
		#if (1==USE_RLEACCEL)
		surface->flags &= ~(SDL_SRCCOLORKEY|SDL_RLEACCELOK);
		#else
		surface->flags &= ~(SDL_SRCCOLORKEY/*|SDL_RLEACCELOK*/);
		#endif /*(USE_RLEACCEL)*/
		surface->format->colorkey = 0;
	}
	SDL_InvalidateMap(surface->map);
	return (0);
}

/*---------------------------------------------------------
	サーフェイス、アルファ(透明レイヤー)設定
---------------------------------------------------------*/

/* This function sets the alpha channel of a surface */
int SDL_SetAlpha(SDL_Surface *surface, u32 flag, u8 value)
{
	u32 oldflags = surface->flags;
	u32 oldalpha = surface->format->alpha;

	/* Sanity check the flag as it gets passed in */
	if (flag & SDL_SRCALPHA)
	{
		#if (1==USE_RLEACCEL)
		if (flag & (SDL_RLEACCEL|SDL_RLEACCELOK))
		{
			flag = (SDL_SRCALPHA | SDL_RLEACCELOK);
		}
		else
		#endif /*(USE_RLEACCEL)*/
		{
			flag = (SDL_SRCALPHA);
		}
	}
	else
	{
		flag = (0);
	}

	/* Optimize away operations that don't change anything */
	#if (1==USE_RLEACCEL)
	if (flag == (surface->flags & (SDL_SRCALPHA|SDL_RLEACCELOK)))
	{
		if ((!flag) || (value == oldalpha))
		{
			return (0);
		}
	}
	if (!(flag & SDL_RLEACCELOK) && (surface->flags & SDL_RLEACCEL))
	{
		SDL_UnRLESurface(surface, 1);
	}
	#endif /*(USE_RLEACCEL)*/
	if (flag)
	{
		surface->flags |= SDL_SRCALPHA;
		surface->format->alpha = value;
		if (SDL_HWACCEL == (surface->flags & SDL_HWACCEL))
		{
//廃止済	if ((video->Set HW Alpha == NULL) ||
//廃止済		 (video->Set HW Alpha(this, surface, value) < 0))
			{
				surface->flags &= ~SDL_HWACCEL;
			}
		}
		#if (1==USE_RLEACCEL)
		if (flag & SDL_RLEACCELOK)
		{
			surface->flags |= SDL_RLEACCELOK;
		}
		else
		{
			surface->flags &= ~SDL_RLEACCELOK;
		}
		#endif /*(USE_RLEACCEL)*/
	}
	else
	{
		surface->flags &= ~SDL_SRCALPHA;
		surface->format->alpha = SDL_ALPHA_OPAQUE;
	}
	/*
	The representation for software surfaces is independent of per-surface alpha,
	ソフトウェア面の表現は、サーフェス単位のαとは無関係です。
	so no need to invalidate the blit mapping if just the alpha value was changed.
	これだけのアルファ値が変更された場合、ブリットマッピングを無効にする必要はありません。
	(If either is 255, we still need to invalidate.)
	（どちらかが255の場合は、我々はまだ無効にする必要があります。）
	 */
	if ((SDL_HWACCEL == (surface->flags & SDL_HWACCEL))
	   || (oldflags != surface->flags)
	   || (((oldalpha + 1) ^ (value + 1)) & 0x100))
		SDL_InvalidateMap(surface->map);
	return (0);
}
/*---------------------------------------------------------
	サーフェイス、アルファ(透明レイヤー)設定
---------------------------------------------------------*/
int SDL_SetAlphaChannel(SDL_Surface *surface, u8 value)
{
	int row, col;
	int offset;
	u8 *buf;
	if (
		(0xff000000 != (surface->format->Amask)) &&
		(0x000000ff != (surface->format->Amask))
	)
	{
		SDL_SetError_bbb("Unsupported surface alpha mask format");
		return (-1);
	}
//	#if (SDL_BYTE ORDER == SDL_LIL_ENDIAN)/*(psp)*/
	if (0xff000000 == (surface->format->Amask))
			{offset = 3;}
	else	{offset = 0;}
//	#else//not_psp
//	if (0xff000000 == (surface->format->Amask))
//			{offset = 0;}
//	else	{offset = 3;}
//	#endif /* Byte ordering */

	/*
	Quickly set the alpha channel of an RGBA or ARGB surface.
	すばやくRGBAまたはARGBサーフェスのアルファチャネルを設定します。
	*/
	if (SDL_MUSTLOCK(surface))
	{
		if (0 > SDL_LockSurface(surface))
		{
			return (-1);
		}
	}
	row = surface->h;
	while (row--)
	{
		col = surface->w;
		buf = (u8 *)surface->pixels + row * surface->pitch + offset;
		while (col--)
		{
			*buf = value;
			buf += 4;
		}
	}
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
	return (0);
}


/*---------------------------------------------------------
	ｐｓｐビデオメモリ
---------------------------------------------------------*/

/* PSP driver bootstrap functions */
/* vidmem handling from Holger Waechtler's pspgl */
struct vidmem_chunk
{
	void *ptr;
	unsigned int len;
};


static struct vidmem_chunk *vidmem_map = NULL;
static unsigned int vidmem_map_len = 0;


/*---------------------------------------------------------
	ｐｓｐビデオ、リストメモリ開放
---------------------------------------------------------*/

static void  vidmem_free(void * ptr)
{
	unsigned int i;
	for (i=0; i<vidmem_map_len; i++)
	{
		if (vidmem_map[i].ptr == ptr)
		{
			void *tmp;
			vidmem_map_len--;
			memmove(&vidmem_map[i], &vidmem_map[i+1], (vidmem_map_len-i) * sizeof(vidmem_map[0]));
			tmp = realloc(vidmem_map, vidmem_map_len * sizeof(vidmem_map[0]));
			if (tmp)
			{	vidmem_map = tmp;	}
		}
	}
}

#if 1
/*---------------------------------------------------------
	ｐｓｐビデオ、リストメモリ取得
---------------------------------------------------------*/

/* リスト挿入処理 */
static void *vidmem_map_insert_new(unsigned int idx, unsigned int adr, unsigned int size)
{
	void *tmp = realloc(vidmem_map, (vidmem_map_len + 1) * sizeof(vidmem_map[0]));
	if (!tmp)
	{return (NULL);}
	//
	vidmem_map = tmp;
	memmove(&vidmem_map[idx+1], &vidmem_map[idx], (vidmem_map_len-idx) * sizeof(vidmem_map[0]));
	vidmem_map_len++;
	vidmem_map[idx].ptr = (void*) adr;
	vidmem_map[idx].len = size;
	//
	return (vidmem_map[idx].ptr);
}

static void* vidmem_alloc(unsigned int size)
{
	/*(16[bytes]境界へ .align 調整処理.)*/
	unsigned int i;
	/* round the size up to the nearest 16 bytes and
	 all hwsurfaces are safe to use as textures. */
	i = (size & (16-1));//(size % 16)
//	if (0 != i) 	{size += 16 - i;}
	if (0 != i) 	{size += 16; size -= i;}
	/*(リストに挿入処理.)*/
	unsigned int start_addr;
	unsigned int temp_addr;
	start_addr	= ((unsigned int)sceGeEdramGetAddr());
	temp_addr	= start_addr;
	/*(残りvramのある限り調べる)*/
	for (i=0; i<vidmem_map_len; i++)
	{
		if (vidmem_map[i].ptr != NULL)
		{
			unsigned int new_addr;
			new_addr = ((unsigned int)vidmem_map[i].ptr);
			if (size <= new_addr - temp_addr)
			{
				goto my_insert_end;/*(その場所に挿入)*/
			}
			temp_addr = new_addr + vidmem_map[i].len;
		}
	}
	/*(失敗判定)*/
	if (temp_addr + size > start_addr + sceGeEdramGetSize())
	{return (NULL);/*(挿入できない)*/}
	/*(最後に挿入)*/
	i = vidmem_map_len;
my_insert_end:
	return (vidmem_map_insert_new(i, temp_addr, size));/* (挿入処理.) */
}
#endif//1



/*---------------------------------------------------------
	ｐｓｐビデオメモリサーフェイス開放
---------------------------------------------------------*/

	/* Frees a previously allocated video surface */
//	void (*FreeHWSurface)(_THIS, SDL_Surface *surface);
/*static*/static/*extern*/ void SDLVIDEO_PSP_FreeHWSurface_aaa(/*_THIS,*/ SDL_Surface *surface)
{
	vidmem_free(surface->pixels);
	surface->pixels = NULL;
}


#if 1/*(?)*/
/*---------------------------------------------------------
	ｐｓｐビデオメモリサーフェイス新規作成
---------------------------------------------------------*/
/*
Anybody have a routine that will take a number and round it up to the next
power of two?

i.e.:
15 gets rounded up to 16 (2^4).
120 gets rounded up to 128 (2^7).
1000 gets rounded up to 1024 (2^10).

etc...
*/
static /*inline*/ int round_up_to_power_of_2(int x)
{
	#if (1)
	/* alegrex(pspのcpu)対応の組み込み関数を使う */
	return (1 << (32 - __builtin_allegrex_clz(x - 1)));
	#else
	/* alegrex非対応の場合 */
	/* 万一コンパイルできないSDKの場合用 */
	{
		int b = x;
		int n;
		for (n=0; b!=0; n++)	{b >>= 1;}
		b = (1 << n);
		//
		if (b == (2 * x))		{b >>= 1;}
		return (b);
	}
	#endif
}
/* Allocates a surface in video memory */
//	int (*AllocHWSurface)(_THIS, SDL_Surface *surface);
/*static*/static/*extern*/ int SDLVIDEO_PSP_AllocHWSurface_aaa(/*_THIS,*/ SDL_Surface *surface)
{
	int pitch;
	pitch = round_up_to_power_of_2(surface->pitch);
	surface->pixels = vidmem_alloc(pitch * surface->h);/*[VRAMへ確保]*/
	if (!surface->pixels)
	{
		return (-1);/* 失敗 */
	}
	surface->pitch = pitch;
	surface->flags |= SDL_HWSURFACE;/* HW可能 */
	surface->hwdata = (void*)1; /* Hack to make SDL realize it's a HWSURFACE when freeing */
	return (0);/* 成功 */
}
#endif


/*---------------------------------------------------------

---------------------------------------------------------*/










/*---------------------------------------------------------
	サーフェイス開放
	-------------------------------------------------------
	Free a surface created by the above function.
	上記の関数によって作成されたサーフェスを開放します。
---------------------------------------------------------*/
void SDL_FreeSurface(SDL_Surface *surface)
{
	/* Free anything that's not NULL, and not the screen surface */
	if (
		(surface == NULL)
		 || (surface == (pspl_screen))
	)
	{
		return;
	}
	surface->refcount--;
	if (surface->refcount > 0)
	{
		return;
	}
	while (surface->locked > 0)
	{
		SDL_UnlockSurface(surface);
	}
	#if (1==USE_RLEACCEL)
	if ((surface->flags & SDL_RLEACCEL) == SDL_RLEACCEL)
	{
		SDL_UnRLESurface(surface, 0);
	}
	#endif /*(USE_RLEACCEL)*/
	if (surface->format)
	{
		SDL_FreeFormat(surface->format);
		surface->format = NULL;
	}
	if (surface->map != NULL)
	{
		SDL_FreeBlitMap(surface->map);
		surface->map = NULL;
	}
	if (surface->hwdata)
	{
	//	video->FreeHWSurface(this, surface);
		SDLVIDEO_PSP_FreeHWSurface_aaa(/*this,*/ surface);
	}
	if (surface->pixels &&
		 ((surface->flags & SDL_PREALLOC) != SDL_PREALLOC))
	{
		free(surface->pixels);
	}
	free(surface);
	#ifdef CHECK_LEAKS
	surfaces_allocated--;
	#endif
}

/*---------------------------------------------------------
	サーフェイス新規作成
	-------------------------------------------------------
	Create an empty RGB surface of the appropriate depth.
	適切な色深度の空のRGBサーフェスをを作成します。
---------------------------------------------------------*/
SDL_Surface * SDL_CreateRGBSurface(
	u32 flags,
	int width, int height, int depth,
	u32 Rmask, u32 Gmask, u32 Bmask, u32 Amask)
{
	SDL_Surface *screen;
	SDL_Surface *surface;
	/* Make sure the size requested doesn't overflow our datatypes */
	/* Next time I write a library like SDL, I'll use int for size. :) */
//	if ((16384 <= width) || (65536 <= height))
	if ((512 < width) || (512 < height))
	{
		SDL_SetError_bbb("Width or height is too large");
		return (NULL);
	}
	/* Check to see if we desire the surface in video memory */
	screen = (pspl_screen);
//	if (pspl_screen/*video*/)/*(pspl_screenはある？)*/
//	{
//		/*(PSPL_VideoInit()、SDL_SetVideoMode()以降の場合)*/
//		screen = (pspl_screen);
//	}
//	else
//	{	/*(PSPL_VideoInit()、SDL_SetVideoMode()以前の場合)*/
//		screen = NULL;/*(PSPL_VideoInit()でpspl_screenを新規作成する場合)*/
//	}
	if (
			(NULL!=screen) &&
		(SDL_HWSURFACE == (screen->flags&SDL_HWSURFACE)))
	{
		if (0 != (flags&(SDL_SRCCOLORKEY|SDL_SRCALPHA)))
		{
			flags |= SDL_HWSURFACE;
		}
		if (SDL_SRCCOLORKEY == (flags & SDL_SRCCOLORKEY))
		{
			if (0== 1/*info.blit_hw_CC*/)
			{
				flags &= ~SDL_HWSURFACE;
			}
		}
		if (SDL_SRCALPHA == (flags & SDL_SRCALPHA))
		{
			if (0== 0/*info.blit_hw_A*/)
			{
				flags &= ~SDL_HWSURFACE;
			}
		}
	}
	else
	{
		flags &= ~SDL_HWSURFACE;
	}
	/* Allocate the surface */
//	surface = (SDL_Surface *)mal loc(sizeof(*surface));
	surface = (SDL_Surface *)memalign(16, (sizeof(*surface)));
	if (NULL == surface)
	{
		SDL_OutOfMemory_bbb();
		return (NULL);
	}
	surface->flags = SDL_SWSURFACE;
	if (SDL_HWSURFACE == (flags & SDL_HWSURFACE))
	{
	//	if (0 (Amask) && (display_form_at_alpha_pixel))
	//	{
	//		0 depth = display_form_at_alpha_pixel->BitsPerPixel;
	//		0 Rmask = display_form_at_alpha_pixel->Rmask;
	//		0 Gmask = display_form_at_alpha_pixel->Gmask;
	//		0 Bmask = display_form_at_alpha_pixel->Bmask;
	//		0 Amask = display_form_at_alpha_pixel->Amask;
	//	}
	//	else
		{
			depth = screen->format->BitsPerPixel;
			Rmask = screen->format->Rmask;
			Gmask = screen->format->Gmask;
			Bmask = screen->format->Bmask;
			Amask = screen->format->Amask;
		}
	}
	surface->format = SDL_AllocFormat(depth, Rmask, Gmask, Bmask, Amask);
	if (NULL == surface->format)
	{
		free(surface);
		return (NULL);
	}
	if (Amask)
	{
		surface->flags |= SDL_SRCALPHA;
	}
	surface->w			= width;
	surface->h			= height;
	surface->pitch		= SDL_CalculatePitch(surface);
	surface->pixels 	= NULL;
	surface->offset 	= 0;
	surface->hwdata 	= NULL;
	surface->locked 	= 0;
	surface->map		= NULL;
//	surface->unused1	= 0;
	SDL_SetClipRect(surface, NULL);
	SDL_FormatChanged(surface);

	/* Get the pixels */
	#define R42_TEST (0)
	#if (1==R42_TEST)/*[r42てすと。(指定時以外VRAM確保しない)]*/
	if (SDL_SWSURFACE == (flags & SDL_HWSURFACE))
	{
		if (SDLVIDEO_PSP_AllocHWSurface_aaa(/*this,*/ surface) < 0)/*[VRAMへ確保]*/
		{goto software_mem_alloc;}
	}
	else
	#else
	/*[-r41。まずVRAMへ確保(可能であれば必ずVRAM確保)]*/
	if (
		(SDL_SWSURFACE == (flags & SDL_HWSURFACE)) ||
	//	(video->AllocHWSurface(this, surface) < 0)
		(SDLVIDEO_PSP_AllocHWSurface_aaa(/*this,*/ surface) < 0)/*[VRAMへ確保]*/
	)
	#endif
	{
		#if (1==R42_TEST)
		software_mem_alloc:
		#endif
		if (surface->w && surface->h)
		{
		//	surface->pixels = mal loc(surface->h*surface->pitch);
			surface->pixels = memalign(16, (surface->h*surface->pitch));
			if (NULL == surface->pixels)
			{
				SDL_FreeSurface(surface);
				SDL_OutOfMemory_bbb();
				return (NULL);
			}
			/* This is important for bitmaps */
			memset(surface->pixels, 0, surface->h*surface->pitch);
		}
	}
	/* Allocate an empty mapping */
	surface->map = SDL_AllocBlitMap();
	if (NULL == surface->map)
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	/* The surface is ready to go */
	surface->refcount = 1;
	#if defined(CHECK_LEAKS)
	surfaces_allocated++;
	#endif
	return (surface);
}

/*---------------------------------------------------------
	サーフェイス新規作成
	-------------------------------------------------------
	Create an RGB surface from an existing memory buffer.
	既存のメモリバッファからRGBサーフェスをを作成します。
---------------------------------------------------------*/
SDL_Surface *SDL_CreateRGBSurfaceFrom(
	void *pixels,
	int width, int height,
	int depth, int pitch,
	u32 Rmask, u32 Gmask, u32 Bmask, u32 Amask)
{
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(
		SDL_SWSURFACE, 0, 0,
		depth,
		Rmask, Gmask, Bmask, Amask);
	if (NULL != surface)
	{
		surface->flags |= SDL_PREALLOC;
		surface->pixels = pixels;
		surface->w = width;
		surface->h = height;
		surface->pitch = pitch;
		SDL_SetClipRect(surface, NULL);
	}
	return (surface);
}
/*---------------------------------------------------------
	サーフェイス新規作成
	-------------------------------------------------------
---------------------------------------------------------*/
SDL_Surface *SDL_CreateSurface(
	u32 flags,
	int width, int height)
{
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(
		flags, width, height,
	//	((pspl_screen)->format->BytesPerPixel*8),
		(pspl_screen)->format->BitsPerPixel,
		(pspl_screen)->format->Rmask,
		(pspl_screen)->format->Gmask,
		(pspl_screen)->format->Bmask,
		(pspl_screen)->format->Amask);
	return (surface);
}
/*---------------------------------------------------------
	サーフェイス、画像データーフォーマット、変換処理
	-------------------------------------------------------
	Convert a surface into the specified pixel format.
	指定されたピクセルフォーマットにサーフェスを変換します。
---------------------------------------------------------*/
SDL_Surface *SDL_ConvertSurface(SDL_Surface *surface, SDL_PixelFormat *format, u32 flags)
{
	SDL_Surface *convert;
	u32 colorkey = 0;
	u8 alpha = 0;
	u32 surface_flags;
	SDL_Rect bounds;

	/*
	Check for empty destination palette! (results in empty image.)
	転送先のパレットが、空で無いかチェックして下さい！（でないと、空の画像になっても知りませんよ。）
	*/
	if (NULL != format->palette)
	{
		int i;
		for (i=0; i<(format->palette->ncolors); i++)
		{
			if (
				(format->palette->colors[i].r != 0) ||
				(format->palette->colors[i].g != 0) ||
				(format->palette->colors[i].b != 0)
			)
			{	break;	}
		}
		if (i == format->palette->ncolors)
		{
			SDL_SetError_bbb("Empty destination palette");
			return (NULL);
		}
	}
	/*
	Only create hardware surfaces with alpha channel if hardware alpha blits are supported.
	ハードウェアアルファブリットがサポートされている場合のみ、
	アルファチャンネルを使用してハードウェアサーフェスを作成します。
	*/
	if (format->Amask != 0 && (flags & SDL_HWSURFACE))
	{
		if (//(0==) ||
			0==0/*info.blit_hw_A*/)
		{	flags &= ~SDL_HWSURFACE;
		}
	}
	/*
	Create a new surface with the desired format.
	指定された形式を使用して新しいサーフェスを作成します。
	*/
	convert = SDL_CreateRGBSurface(flags,
		surface->w, surface->h, format->BitsPerPixel,
		format->Rmask, format->Gmask, format->Bmask, format->Amask);
	if (NULL == convert)
	{
		return (NULL);
	}

	/*
	Copy the palette if any.
	パレットがある場合はコピーをします。
	*/
	if (format->palette && convert->format->palette)
	{
		memcpy(convert->format->palette->colors,
			format->palette->colors,
			format->palette->ncolors*sizeof(SDL_Color));
		convert->format->palette->ncolors = format->palette->ncolors;
	}

	/*
	Save the original surface color key and alpha.
	元のサーフェスのカラーキーとアルファを保存します。
	*/
	surface_flags = surface->flags;
	if ((surface_flags & SDL_SRCCOLORKEY) == SDL_SRCCOLORKEY)
	{
		/*
		Convert colourkeyed surfaces to RGBA if requested.
		必要ならばのRGBAに抜き色指定されたサーフェスに変換します。
		*/
		if ((flags & SDL_SRCCOLORKEY) != SDL_SRCCOLORKEY
		   && format->Amask)
		{
			surface_flags &= ~SDL_SRCCOLORKEY;
		}
		else
		{
			colorkey = surface->format->colorkey;
			SDL_SetColorKey(surface, 0, 0);
		}
	}
	if ((surface_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
	{
		/*
		Copy over the alpha channel to RGBA if requested.
		必要ならば、RGBAにアルファチャネルを介してコピーします。
		*/
		if (format->Amask)
		{
			surface->flags &= ~SDL_SRCALPHA;
		}
		else
		{
			alpha = surface->format->alpha;
			SDL_SetAlpha(surface, 0, 0);
		}
	}

	/*
	Copy over the image data.
	画像データをコピーします。
	*/
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = surface->w;
	bounds.h = surface->h;
	SDL_LowerBlit(surface, &bounds, convert, &bounds);

	/*
	Clean up the original surface, and update converted surface.
	オリジナルのサーフェスをクリーンアップし、変換されたサーフェスを更新します。
	*/
	if (convert != NULL)
	{
		SDL_SetClipRect(convert, &surface->clip_rect);
	}
	if ((surface_flags & SDL_SRCCOLORKEY) == SDL_SRCCOLORKEY)
	{
		#if (1==USE_RLEACCEL)
		u32 cflags = surface_flags & (SDL_SRCCOLORKEY | SDL_RLEACCELOK);
		#else
		u32 cflags = surface_flags & (SDL_SRCCOLORKEY/* | SDL_RLEACCELOK*/);
		#endif /*(USE_RLEACCEL)*/
		if (convert != NULL)
		{
			u8 keyR, keyG, keyB;
			SDL_GetRGB(colorkey, surface->format, &keyR, &keyG, &keyB);
			#if (1==USE_RLEACCEL)
			SDL_SetColorKey(convert, cflags | (flags & SDL_RLEACCELOK), SDL_MapRGB(convert->format, keyR, keyG, keyB));
			#else
			SDL_SetColorKey(convert, cflags/* | (flags & SDL_RLEACCELOK)*/, SDL_MapRGB(convert->format, keyR, keyG, keyB));
			#endif /*(USE_RLEACCEL)*/
		}
		SDL_SetColorKey(surface, cflags, colorkey);
	}
	if ((surface_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
	{
		#if (1==USE_RLEACCEL)
		u32 aflags = surface_flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
		#else
		u32 aflags = surface_flags & (SDL_SRCALPHA/* | SDL_RLEACCELOK*/);
		#endif /*(USE_RLEACCEL)*/
		if (convert != NULL)
		{
			#if (1==USE_RLEACCEL)
			SDL_SetAlpha(convert, aflags | (flags & SDL_RLEACCELOK), alpha);
			#else
			SDL_SetAlpha(convert, aflags/* | (flags & SDL_RLEACCELOK)*/, alpha);
			#endif /*(USE_RLEACCEL)*/
		}
		if (format->Amask)
		{
			surface->flags |= SDL_SRCALPHA;
		}
		else
		{
			SDL_SetAlpha(surface, aflags, alpha);
		}
	}
	/*
	We're ready to go!
	変換できました！
	*/
	return (convert);
}









/*---------------------------------------------------------

---------------------------------------------------------*/


#if (1)/* call from src/core/menu/scenario_script.c */
/*
 * Convert a surface into the video pixel format.
 */
/*global*/ SDL_Surface *SDL_DisplayFormat(SDL_Surface *surface)
{
	u32 flags;
//	#if (000)/* NOT support check. */
//	if (0==(pspl_screen) )
//	{
//		// SDLのビデオモードが一度もセットされてないよ。
//		SDL_SetError_bbb("No video mode has been set");
//		return (NULL);
//	}
//	#endif
//	#if (000)/* NOT support get SDL_HWSURFACE. */
//	/* Set the flags appropriate for copying to display surface */
//	if ((((pspl_screen)->flags&SDL_HWSURFACE) == SDL_HWSURFACE) && current_video->info.blit_hw)
//	{	flags = SDL_HWSURFACE;}
//	else
//	#endif
	{	flags = SDL_SWSURFACE;}
//	#ifdef AUTORLE_DISPLAYFORMAT
//	flags |= (surface->flags & (SDL_SRCCOLORKEY|SDL_SRCALPHA));
//	flags |= SDL_RLEACCELOK;
//	#else
	#if (1==USE_RLEACCEL)
		flags |= surface->flags & (SDL_SRCCOLORKEY|SDL_SRCALPHA|SDL_RLEACCELOK);
	#else
		flags |= surface->flags & (SDL_SRCCOLORKEY|SDL_SRCALPHA/*|SDL_RLEACCELOK*/);
	#endif /*(USE_RLEACCEL)*/
//	#endif
	return (SDL_ConvertSurface(surface, (pspl_screen)->format, flags));
}
#endif

	/* * * */
static void *psp_vram_base;
/*---------------------------------------------------------
	Clean up the video subsystem.
	Note:	If we are terminated, this could be called in the middle of
			another SDL video routine -- notably UpdateRects.
--------------------------------------------------------- */
/* Reverse the effects VideoInit() -- called if VideoInit() fails
   or if the application is shutting down the video subsystem. */
void PSPL_VideoQuit(void)/*only exit once*/
{
	/* Clean up allocated window manager items */
//	if ((pspl_screen) )
//	{
//		(pspl_screen) = NULL;
//	}
	/* Just in case... */
	/* Clean up the system video */
//	sceGuTerm();/*(?)*/
	vidmem_free(psp_vram_base);
	/* Free any lingering surfaces */
	if ((pspl_screen) != NULL )
	{
		SDL_Surface *ready_to_go;
		ready_to_go 		= (pspl_screen);
		(pspl_screen)	= NULL;
		SDL_FreeSurface(ready_to_go);
	}
	(pspl_screen) = NULL;
	/* Clean up miscellaneous memory */
	/* Finish cleaning up video subsystem */
//	video->free(this);
}


/*---------------------------------------------------------
	void PSPL_VideoInit(void)
	Initialize the video and event subsystems -- determine native pixel format.
	SDL_SetVideoMode
--------------------------------------------------------- */

//SDL_Surface * SDL_SetVideoMode(int dummy_width, int dummy_height, int video_bpp, u32 dummy_flags)
SDL_Surface * PSPL_video_init(
	int video_bpp_sdl,	/*sdl depth(15 or 16 or 32)*/
	int video_depth16,	/*psp depth(16 or 32)*/
	u32 Amask,
	u32 Bmask,
	u32 Gmask,
	u32 Rmask
)/*only boot once*/
// /*static*/extern int SDLVIDEO_PSP_VideoInit(_THIS, SDL_PixelFormat *vformat);
{
	/* Select the proper video driver */
	/* Initialize all variables that we clean on shutdown */
	memset(&pspl_screen, 0, (sizeof(pspl_screen)));

	/* Do some basic variable initialization */
	pspl_screen 						= NULL; 	/* Until SDL_SetVideoMode() */

	/* Initialize the video subsystem */

	//	video->VideoInit(video, &vformat);
	//	SDLVIDEO_PSP_VideoInit(video, &vformat);
		/* Initialize the native video subsystem, filling 'vformat' with the
		   "best" display pixel format, returning 0 or -1 if there's an error.
		 */
	// /*static*/extern int SDLVIDEO_PSP_VideoInit(_THIS, SDL_PixelFormat *vformat)
	#if (1)
	{
		SDL_PixelFormat vformat;
		memset(&vformat, 0, sizeof(vformat));
		vformat.BytesPerPixel		= 4;	/* Default for pspsdk is 8888 ABGR */
		vformat.BitsPerPixel		= /*video_depth16*/16/*32*/;	/* Default for pspsdk is 8888 ABGR */
	//	vformat.Amask= /*Amask*/0/*0*/;
	//	vformat.Bmask= /*Bmask*/0/*0*/;
	//	vformat.Gmask= /*Gmask*/0/*0*/;
	//	vformat.Rmask= /*Rmask*/0/*0*/;
		/* Create a zero sized video surface of the appropriate format */
		pspl_screen =
			SDL_CreateRGBSurface
			(
				/*video_flags =*/(SDL_SWSURFACE),
				(0)/*width*/,
				(0)/*height*/
			,
				vformat.BitsPerPixel,
				vformat.Rmask,
				vformat.Gmask,
				vformat.Bmask,
				0
			);
	}
	#endif
	#if (0)/*(ダメ)*/
	{
	//	SDL_PixelFormat vformat;
	//	memset(&vformat, 0, sizeof(vformat));
	//unused	vformat.BytesPerPixel		= 4;	/* Default for pspsdk is 8888 ABGR */
		/*vformat.*/(pspl_screen)->format->BitsPerPixel 	= /*video_depth16*/16/*32*/;	/* Default for pspsdk is 8888 ABGR */
		/*vformat.*/(pspl_screen)->format->Amask= /*Amask*/0/*0*/;
		/*vformat.*/(pspl_screen)->format->Bmask= /*Bmask*/0/*0*/;
		/*vformat.*/(pspl_screen)->format->Gmask= /*Gmask*/0/*0*/;
		/*vformat.*/(pspl_screen)->format->Rmask= /*Rmask*/0/*0*/;
		/* Create a zero sized video surface of the appropriate format */
		pspl_screen =
		//	SDL_CreateRGBSurface
			SDL_CreateSurface
			(
				/*video_flags =*/(SDL_SWSURFACE),
				(0)/*width*/,
				(0)/*height*/
			//,
			//	vformat.BitsPerPixel,
			//	vformat.Rmask,
			//	vformat.Gmask,
			//	vformat.Bmask,
			//	0
			);
	}
	#endif
//	info_vfmt = (pspl_screen)->format;

	/* Clean up any previous video mode */
//	if ((pspl_screen) != NULL )
//	{
//		(pspl_screen) = NULL;
//	}
	/* Try to set the video mode, along with offset and clipping */
//	SDL_Surface *mode;
//	mode = (pspl_screen);
	//
	int disp_pitch;
	int pixel_format;
	disp_pitch = (512*2);
	{
	//	u32 Amask;
	//	u32 Bmask;
	//	u32 Gmask;
	//	u32 Rmask;
		if (15==video_bpp_sdl)//case 15: /* 5-5-5-1 */
		{
		//	Amask = 0x00008000;
		//	Bmask = 0x00007c00;
		//	Gmask = 0x000003e0;
		//	Rmask = 0x0000001f;
			pixel_format = PSP_DISPLAY_PIXEL_FORMAT_5551;
		}
		else
		if (16==video_bpp_sdl)//case 16: /* 5-6-5 */
		{
		//	Amask = 0;
		//	Bmask = 0x0000f800;
		//	Gmask = 0x000007e0;
		//	Rmask = 0x0000001f;
			pixel_format = PSP_DISPLAY_PIXEL_FORMAT_565;
		}
		else
	//	if (32==video_bpp_sdl)//case 32: /* 8-8-8-8 */
		{
			disp_pitch += disp_pitch;
		//	Amask = 0xff000000;
		//	Bmask = 0x00ff0000;
		//	Gmask = 0x0000ff00;
		//	Rmask = 0x000000ff;
			pixel_format = PSP_DISPLAY_PIXEL_FORMAT_8888;
		}
	}
	/* Now adjust the offsets to match the desired mode */
	//廃止		video->offset_x 		= (0);
	//廃止		video->offset_y 		= (0);
	SDL_ReallocFormat(pspl_screen, video_bpp_sdl, Rmask, Gmask, Bmask, 0/*Amask*/);
	pspl_screen->offset 	= (0);//(video->offset_y * pspl_screen->pitch) + (video->offset_x * pspl_screen->format->BytesPerPixel);
	pspl_screen->w			= SCREEN_480_WIDTH;/*width*/
	pspl_screen->h			= SCREEN_272_HEIGHT;/*height*/
	pspl_screen->pitch		= (disp_pitch);
	/* allocate display buffer */
	{
		u32 	psp_frame_offset;	/* Byte offset of the start of the second frame. */
		psp_frame_offset		= (disp_pitch * SCREEN_272_HEIGHT);/*height*/
		psp_vram_base			= vidmem_alloc((psp_frame_offset+psp_frame_offset));/*[VRAMへ確保]*/	/* allocate dispbuffer + drawbuffer */
		pspl_screen->pixels 	= (void *) ((u32)psp_vram_base + psp_frame_offset);
	}
	sceDisplaySetMode(0, SCREEN_480_WIDTH, SCREEN_272_HEIGHT);
	sceDisplaySetFrameBuf(psp_vram_base, 512, pixel_format, PSP_DISPLAY_SETBUF_NEXTFRAME);
	{
	//	u32 flags;
		pspl_screen->flags	= /*flags =(u32)*/ (SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_PREALLOC);
		/* SDL_PREALLOC: so SDL doesn't free ->pixels */
	}
	/* Clear the surface to black */
//	SDL_SetClipRect(pspl_screen, NULL);
	#if 0/*(とりあえず)*/
	SDL_ClearSurface(pspl_screen);// 本来、起動時(画面モード切り替え時)に画面消す機能。
	#endif
//	info_vfmt = (pspl_screen)->format;
	return (pspl_screen);
}
//#include "not_use_PSPL_video.c" // 使用しない部分が多いので分割
