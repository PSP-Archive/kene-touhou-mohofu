
/*

http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fthread%2FSDL_thread_c.h

psp - リビジョン 440Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/thread/SDL_thread_c.h
詳細表示 - 最終更新日時 - ログを見る -

http://psp.jim.sh/svn/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fthread%2Fpsp%2FSDL_systhread_c.h
http://svn.pspdev.org/filedetails.php?repname=psp&path=%2Ftrunk%2FSDL%2Fsrc%2Fthread%2Fpsp%2FSDL_systhread_c.h

psp - リビジョン 440Subversion リポジトリ一覧: pspps2ps2wareps3ps3warepspwareリビジョン:(root)/trunk/SDL/src/thread/SDL_systhread.h
詳細表示 - 最終更新日時 - ログを見る -
*/

/*
Subversion リポジトリ一覧 psp
(root)/trunk/SDL/src/thread/psp/SDL_systhread_c.h - リビジョン 472
*/

/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	PSPL - PSP customised SDL Layer port.
	SDL Copyright (C) 1997-2004 Sam Lantinga.
---------------------------------------------------------*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: PSPL_thread_c.h,v 1.5 2004/01/04 16:49:18 slouken Exp $";
#endif

#ifndef _PSPL_thread_c_h
#define _PSPL_thread_c_h

#include "./PSPL_error_c.h"
//#include "./PSPL_systhread_c.h"

/* PSP port contributed by Marcus R. Brown <mrbrown@ocgnet.org>. */

#include <pspkerneltypes.h>

typedef SceUID SYS_ThreadHandle;

/* This is the system-independent thread info structure */
struct SDL_Thread
{
	u32 threadid;
	SYS_ThreadHandle handle;
	int status;
	SDL_error errbuf;
	void *data;
};

/* This is the function called to run a thread */
extern void SDL_RunThread(void *data);

/* Routine to get the thread-specific error variable */
extern SDL_error *SDL_GetErrBuf(void);

#endif /* _PSPL_thread_c_h */
