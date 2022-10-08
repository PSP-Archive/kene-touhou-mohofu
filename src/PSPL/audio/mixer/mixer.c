
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
---------------------------------------------------------*/

/* This function gets the version of the dynamically linked SDL_mixer library.
   it should NOT be used to fill a version structure, instead you should
   use the SDL_MIXER_VERSION() macro.
 */
//extern const SDL_version * /*SD LCALL*/ Mix_Linked_Version(void);


/*
	SDL_mixer:	An audio mixer library based on the SDL library
	Copyright (C) 1997-2004 Sam Lantinga

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	Sam Lantinga
	slouken@libsdl.org
*/

/* $Id: mixer.c,v 1.50 2004/08/21 12:24:02 slouken Exp $ */
#ifdef _SDL_MIXER_H
error! "このプログラムは SDL_mixer.h がインクルードされていると、コンパイルできません。"
#endif
#define _SDL_MIXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "./../../include/PSPL_audio.h"
#include "000SDL_mixer.h"//#define PSPL_MIXER_MAX_VOLUME			128 	/* Volume of a chunk */

//#include "_SD L_types.h"
//#include <SD L/SDL_mutex.h>//#include "SD L_mutex.h"
#include "./../../include/PSPL_endian.h"//#include <SD L/SDL_endian.h>//#include "SD L_endian.h"
//#include <SD L/SDL_timer.h>//#include "SD L_timer.h"

//#include <SD L/SD L_mixer.h>//#include "SD L_mixer.h"

#ifdef USE_WINDOWS_AIFF
	#include "load_aiff.h"
#endif
#ifdef USE_CREATIVE_VOC
	#include "load_voc.h"
#endif
#if defined(OGG_MUSIC)
	#include "load_ogg.h"
#endif

#ifndef SDL_SetError_bbb
	#define SDL_SetError_bbb(aaa)
#endif

#ifndef Mix_SetError_bbb
	#define Mix_SetError_bbb(aaa)
#endif

/* Magic numbers for various audio file formats */
#define RIFF		0x46464952		/* "RIFF" */
#define WAVE		0x45564157		/* "WAVE" */
#define FORM		0x4d524f46		/* "FORM" */
#define OGGS		0x5367674f		/* "OggS" */
#define CREA		0x61657243		/* "Crea" */

static int audio_opened = 0;
static int reserved_channels = 0;
static PSPL_AUDIO_SPEC pspl_mixer;



/* The default mixer has 8 simultaneous mixing channels */

#ifndef MAX_16_MIXING_CHANNELS
	//#define MAX_16_MIXING_CHANNELS	(8)/* SDLmixerは 8チャンネル。 */
	#define MAX_16_MIXING_CHANNELS		(16)/* 模倣風ではSDL互換は切り捨てて16チャンネルにした。 */
#endif

//MAX_16_MIXING_CHANNELS 8 static int MAX_16_MIXING_CHANNELS;
//#define MAX_16_MIXING_CHANNELS MAX_16_MIXING_CHANNELS

#define USE_MIXER_EFFECT (0)


#if (1==USE_MIXER_EFFECT)
	#include "./music_effect.h"/*effect機能*/
	typedef struct mix_effect_info_t
	{
		Mix_EffectFunc_t callback;
		Mix_EffectDone_t done_callback;
		void *udata;
		struct mix_effect_info_t *next;
	} effect_info;
#endif

/* 1:動的確保方式 */
/* 0:固定配列方式 */
#define USE_MIX_CHANNEL_ALLOC (1)
//#define USE_MIX_CHANNEL_ALLOC (0)
//static
typedef struct //mix_channel_t
{
	PSPL_MIX_VOICE_CHUNK	*chunk;			// 効果音の音データ。
	int 		playing;					// 再生中判別フラグ。
//0000	int 		paused;
	u8		*samples;						// 効果音の音データ。
	int 		volume;
//	int 		looping;/*[廃止]効果音ループ機能*/
//	int 		tag;/*模倣風で使用していない*/
//0 u32 	expire;
//	u32 	start_time;/*模倣風で使用していない*/
//	Mix_Fading	fading;/*[廃止]*/
//	int 		fade_volume;/*[廃止]*/
//	u32 	fade_length;/*[廃止]*/
//	u32 	ticks_fade;/*[廃止]*/
	#if (1==USE_MIXER_EFFECT)
	effect_info *effects;
	#endif
} PSPL_MIX_CANNELS; //*mix_channel = NULL;

#if (1==USE_MIX_CHANNEL_ALLOC)
/* 動的確保方式 */
static PSPL_MIX_CANNELS *mix_channel = NULL;
#else
/* 固定配列方式 */
static PSPL_MIX_CANNELS mix_channel[MAX_16_MIXING_CHANNELS] __attribute__((aligned(64))) ;
#endif

	#if (1==USE_MIXER_EFFECT)
static effect_info *posteffects = NULL;
	#endif



#if 00/*模倣風で使用していない*/
/* Support for hooking into the mixer callback system */
static void (*mix_postmix)(void *udata, u8 *stream, int len) = NULL;
static void *mix_postmix_data = NULL;
#endif

#if 00/*模倣風で使用していない*/
/* rcg07062001 callback to alert when channels are done playing. */
static void (*channel_done_callback)(int channel) = NULL;
#endif

/* Music function declarations */
extern int open_music(PSPL_AUDIO_SPEC *mixer);
extern void close_music(void);

/* Support for user defined music functions, plus the default one */
//extern int volatile mixer_only_music_active;/*[廃止]*/
extern void custom_music_mixer(void *udata, u8 *stream, int len);
//static void (*mix_music)(void *udata, u8 *stream, int len) = custom_music_mixer;/*[廃止]フックしない*/
static void *music_data = NULL;

#if 0/*模倣風で使用していない*/
#include <psptypes.h>
#include <psprtc.h>
//------------------------------------------------------------
//	psp_ticker
//------------------------------------------------------------

static u64 psp_ticker(void)
{
	u64 current_ticks;
	sceRtcGetCurrentTick(&current_ticks);
	return current_ticks;
}
static /*cycles_t*/unsigned long SDL_GetTicks_bbb/*osd_cycles*/(void)
{
//	return (/*cycles_t*/unsigned long)(psp_ticker()/1000);
	return (/*cycles_t*/unsigned long)(psp_ticker() /*/1000*/);
}
#endif/*模倣風で使用していない*/


//------------------------------------------------------------

#if 00/*未使用*/
/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define SDL_MIXER_MAJOR_VERSION 	1
#define SDL_MIXER_MINOR_VERSION 	2
#define SDL_MIXER_PATCHLEVEL		6

/* This macro can be used to fill a version structure with the compile-time
 * version of the SDL_mixer library.
 */
#define SDL_MIXER_VERSION(X)						\
{													\
	(X)->major = SDL_MIXER_MAJOR_VERSION;			\
	(X)->minor = SDL_MIXER_MINOR_VERSION;			\
	(X)->patch = SDL_MIXER_PATCHLEVEL;				\
}

/* Backwards compatibility */
//#define MIX_MAJOR_VERSION SDL_MIXER_MAJOR_VERSION
//#define MIX_MINOR_VERSION SDL_MIXER_MINOR_VERSION
//#define MIX_PATCHLEVEL		SDL_MIXER_PATCHLEVEL
//#define MIX_VERSION(X)		SDL_MIXER_VERSION(X)

/* rcg06192001 get linked library's version. */
typedef struct SDL_version
{
	u8 major;
	u8 minor;
	u8 patch;
} SDL_version;
const SDL_version *Mix_Linked_Version(void)
{
	static SDL_version linked_version;
	SDL_MIXER_VERSION(&linked_version);
	return (&linked_version);
}
#endif/*未使用*/

//------------------------------------------------------------

	#if (1==USE_MIXER_EFFECT)
/* MAKE SURE you hold the audio lock (PSPL_LockAudio()) before calling this! */
static int s_Mix_remove_all_effects(int channel, effect_info **e)
{
	if (!e)
	{
		Mix_SetError_bbb("Internal error");
		return (0);
	}

	effect_info *cur;
	for (cur = *e; cur != NULL; cur = next)
	{
		effect_info *next;
		next = cur->next;
		if (cur->done_callback != NULL)
		{
			cur->done_callback(channel, cur->udata);
		}
		free(cur);
	}
	*e = NULL;
	return (1);
}
	#endif

#if 000/* レンダリング後のコールバック(模倣風では無し) */
/*
 * rcg06122001 Cleanup effect callbacks.
 *	MAKE SURE PSPL_LockAudio() is called before this (or you're in the
 *	 audio callback).
 */
static void s_Mix_channel_done_playing(int channel)
{
	#if 00/*模倣風で使用していない*/
	if (channel_done_callback)
	{
		channel_done_callback(channel);
	}
	#endif

	#if (1==USE_MIXER_EFFECT)
	/*
	 * Call internal function directly, to avoid locking audio from
	 *	 inside audio callback.
	 */
	s_Mix_remove_all_effects(channel, &mix_channel[channel].effects);
	#endif
}
#else
	#define s_Mix_channel_done_playing(aaa) /**/
#endif/* レンダリング後のコールバック(ここまで) */

#if (1==USE_MIXER_EFFECT)
static void *Mix_DoEffects(int chan, void *snd, int len)
{
#if (1==USE_MIXER_EFFECT)
	int posteffect = (chan == MIX_CHANNEL_POST);
	effect_info *e = ((posteffect) ? posteffects : mix_channel[chan].effects);
#endif
	void *buf = snd;

#if (1==USE_MIXER_EFFECT)
	if (e != NULL)
	{	/* are there any registered effects? */
		/* if this is the postmix, we can just overwrite the original. */
		if (!posteffect)
		{
			buf = malloc(len);
			if (buf == NULL)
			{
				return (snd);
			}
			memcpy(buf, snd, len);
		}

		for (; e != NULL; e = e->next)
		{
			if (e->callback != NULL)
			{
				e->callback(chan, buf, len, e->udata);
			}
		}
	}
#endif
	/* be sure to free() the return value if != snd ... */
	return (buf);
}
#endif

//------------------------------------------------------------

#if 00/*模倣風で使用していない*/
/* Set volume of a particular channel */
static int s_Mix_Volume(int which, int volume)
{
	int prev_volume;
	if (which == -1)
	{
		prev_volume = 0;
		int i;
		for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
		{
			prev_volume += s_Mix_Volume(i, volume);
		}
		#if (16==MAX_16_MIXING_CHANNELS)
		prev_volume >>= 4;
		#else
		prev_volume /= MAX_16_MIXING_CHANNELS;
		#endif
	}
	else
	{
		prev_volume = mix_channel[which].volume;
		if (volume >= 0)
		{
			if (volume > PSPL128_MIX_MAX_VOLUME)
			{
				volume = PSPL128_MIX_MAX_VOLUME;
			}
			mix_channel[which].volume = volume;
		}
	}
	return (prev_volume);
}
#endif/*模倣風で使用していない*/

#if 00/*模倣風で使用していない*/
/* Set volume of a particular chunk */
int Mix_VolumeChunk(PSPL_MIX_VOICE_CHUNK *chunk, int volume)
{
	int prev_volume;
	prev_volume = chunk->volume;
	if (volume >= 0)
	{
		if (volume > PSPL_MIXER_MAX_VOLUME)
		{
			volume = PSPL_MIXER_MAX_VOLUME;
		}
		chunk->volume = volume;
	}
	return (prev_volume);
}
#endif/*模倣風で使用していない*/

//------------------------------------------------------------

/* Mixing function */
static void mix_channels(void *udata, u8 *stream, int len)
{
	/* Mix the music (must be done before the channels are added) */
//	if (mixer_only_music_active
//		//	|| (mix_music != custom_music_mixer)
//	)
//	{
	//	mix_music(music_data, stream, len);
		custom_music_mixer(music_data, stream, len);
//	}

	/* Mix any playing channels... */
//000	u32 sdl_ticks = SDL_GetTicks_bbb();
	int i;
	for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
	{
//0000		if (0==mix_channel[i].paused)/* 「一時停止中の状態」以外の場合。 */
		{
			#if 000
			if (mix_channel[i].expire > 0 && (mix_channel[i].expire < sdl_ticks))
			{
				/* Expiration delay for that channel is reached */
				mix_channel[i].playing = 0;
			//	mix_channel[i].fading = MIX_NO_FADING;/*[廃止]*/
				mix_channel[i].expire = 0;
				s_Mix_channel_done_playing(i);
			}
			#endif/*(000)*/
			#if 00/*[廃止]*/
			else if (mix_channel[i].fading != MIX_NO_FADING)
			{
				u32 ticks = sdl_ticks - mix_channel[i].ticks_fade;
				if (ticks > mix_channel[i].fade_length)
				{
					if (mix_channel[i].fading == MIX_FADING_OUT)
					{
						mix_channel[i].playing = 0;
//000						mix_channel[i].expire = 0;
						s_Mix_Volume(i, mix_channel[i].fade_volume); /* Restore the volume */
						s_Mix_channel_done_playing(i);
					}
					mix_channel[i].fading = MIX_NO_FADING;
				}
				else
				{
					if (mix_channel[i].fading == MIX_FADING_OUT)
					{
						s_Mix_Volume(i, (mix_channel[i].fade_volume * (mix_channel[i].fade_length-ticks)) / mix_channel[i].fade_length);
					}
					else
					{
						s_Mix_Volume(i, (mix_channel[i].fade_volume * ticks) / mix_channel[i].fade_length);
					}
				}
			}
			#endif/*[廃止]*/
			if (0 < mix_channel[i].playing)
			{
				u8 *mix_input;
				int index;
				int remaining;
				int set_volume;
				//
				index = 0;
				remaining = len;
			//	set_volume = 0;
				while ((0 < mix_channel[i].playing) && (index < len))
				{
					remaining = len - index;
				//	set_volume = (mix_channel[i].volume * ((int)mix_channel[i].chunk->u8_volume)) / PSPL_MIXER_MAX_VOLUME;
				//	set_volume = (mix_channel[i].volume * ((int)mix_channel[i].chunk->u8_volume)) >> PSPL_MIXER_MAX_VOLUME_SHIFT;//[重複(channel_volumeで設定すれば不要)]u8_volume
				//	set_volume = (mix_channel[i].volume * (PSPL_MIXER_MAX_VOLUME)) / PSPL_MIXER_MAX_VOLUME;//[重複(channel_volumeで設定すれば不要)]u8_volume
					set_volume = (mix_channel[i].volume);//[重複(mix_channel_volumeで設定すれば不要)]u8_volume
					int mixable = mix_channel[i].playing;
					if (mixable > remaining)
					{
						mixable = remaining;
					}
					#if (1==USE_MIXER_EFFECT)
					mix_input = Mix_DoEffects(i, mix_channel[i].samples, mixable);
					#else
					mix_input = (mix_channel[i].samples);/*(?)*/
					#endif
					PSPL_MixAudio((stream+index), mix_input, mixable, set_volume);
					if (mix_input != mix_channel[i].samples)
					{	free(mix_input);}
					mix_channel[i].samples += mixable;
					mix_channel[i].playing -= mixable;
					index += mixable;
					/* rcg06072001 Alert app if channel is done playing. */
					if (0 == mix_channel[i].playing
					//	&&
					// (0 == mix_channel[i].looping)/*[廃止]効果音ループ機能*/
					)
					{
						s_Mix_channel_done_playing(i);
					}
				}
				#if 00/*[廃止]効果音ループ機能*/
				/* If looping the sample and we are at its end, make sure we will still return a full buffer */
				while ((mix_channel[i].looping) && (index < len))
				{
					int alen = mix_channel[i].chunk->alen;
					remaining = len - index;
					if (remaining > alen)
					{
						remaining = alen;
					}
					#if (1==USE_MIXER_EFFECT)
					mix_input = Mix_DoEffects(i, mix_channel[i].chunk->abuf, remaining);
					#else
					mix_input = (mix_channel[i].chunk->abuf);
					#endif
					PSPL_MixAudio(stream+index, mix_input, remaining, set_volume);
					if (mix_input != mix_channel[i].chunk->abuf)
					{
						free(mix_input);
					}
					mix_channel[i].looping--;
					mix_channel[i].samples = mix_channel[i].chunk->abuf + remaining;
					mix_channel[i].playing = mix_channel[i].chunk->alen - remaining;
					index += remaining;
				}
				if (!mix_channel[i].playing && mix_channel[i].looping)
				{
					mix_channel[i].looping--;
					if (mix_channel[i].looping)
					{
						mix_channel[i].samples = mix_channel[i].chunk->abuf;
						mix_channel[i].playing = mix_channel[i].chunk->alen;
					}
				}
				#endif/*[廃止]効果音ループ機能*/
			}
		}
	}
	#if (1==USE_MIXER_EFFECT)
	/* rcg06122001 run posteffects... */
	Mix_DoEffects(MIX_CHANNEL_POST, stream, len);
	#endif/*(USE_MIXER_EFFECT)*/
	//
	#if 00/*模倣風で使用していない*/
	if (mix_postmix)
	{
		mix_postmix(mix_postmix_data, stream, len);
	}
	#endif/*模倣風で使用していない*/
}

#if (0)/*[デバッグ用]*/
static void PrintFormat(char *title, PSPL_AUDIO_SPEC *fmt)
{
	printf("%s: %d bit %s audio (%s) at %u Hz\n", title, (fmt->format&0xff),
			(fmt->format&0x8000) ? "signed" : "unsigned",
			(fmt->channels > 2) ? "surround" :
			(fmt->channels > 1) ? "stereo" : "mono", fmt->freq);
}
#endif/*(0)[デバッグ用]*/


//void s_Mix_InitEffects(void);

/////////////////////////////////////////////////////////////
/* Halt playing of a particular channel */
#if (1)
static int s_Mix_HaltChannel(int which)
{
	if (which == -1)
	{
		unsigned int i;
		for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
		{
			s_Mix_HaltChannel(i);
		}
	}
	else
	{
		PSPL_LockAudio();
		if (mix_channel[which].playing)
		{
			s_Mix_channel_done_playing(which);
			mix_channel[which].playing = 0;
		}
//000		mix_channel[which].expire = 0;
		#if 00/*[廃止]*/
		if (mix_channel[which].fading != MIX_NO_FADING) /* Restore volume */
		{	mix_channel[which].volume = mix_channel[which].fade_volume;}
		mix_channel[which].fading = MIX_NO_FADING;/*[廃止]*/
		#endif/*[廃止]*/
		PSPL_UnlockAudio();
	}
	return (0);
}
#endif/*(1)*/
//
#if 00/*模倣風で使用していない*/
/* Halt playing of a particular group of channels */
int Mix_HaltGroup(int tag)
{
	unsigned int i;
	for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
	{
		if (mix_channel[i].tag == tag)
		{
			s_Mix_HaltChannel(i);
		}
	}
	return (0);
}
#endif/*模倣風で使用していない*/

//------------------------------------------------------------
#if (1==USE_MIXER_EFFECT)
static int s_Mix_UnregisterAllEffects(int channel)
{
	effect_info **e = NULL;
	if (channel == MIX_CHANNEL_POST)
	{
		e = &posteffects;
	}
	else
	{
		if ((channel < 0) || (channel >= MAX_16_MIXING_CHANNELS))
		{
			Mix_SetError_bbb("Invalid channel number");
			return (0);
		}
		e = &mix_channel[channel].effects;
	}
	//
	{
		PSPL_LockAudio();
		int retval;
		retval = s_Mix_remove_all_effects(channel, e);
		PSPL_UnlockAudio();
		return (retval);
	}
}
#endif

/* Close the mixer, halting all playing audio */
void Mix_CloseAudio(void)
{
	if (audio_opened)
	{
		if (1 == audio_opened)
		{
			#if (1==USE_MIXER_EFFECT)
			unsigned int i;
			for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
			{
				s_Mix_UnregisterAllEffects(i);
			}
			s_Mix_UnregisterAllEffects(MIX_CHANNEL_POST);
			#endif
			close_music();
			s_Mix_HaltChannel(-1);
		// ここで開放は禁止 PSPL_CloseAudio();
			#if (1==USE_MIX_CHANNEL_ALLOC)/* []malloc all mix_channel(8) */
			free(mix_channel);
			mix_channel = NULL;
			#endif
		}
		audio_opened--;
	}
}


/////////////////////////////////////////////////
/* Open the mixer with a certain desired audio format */
int Mix_OpenAudio(int frequency_dummy, u16 format_dummy, int nchannels_dummy, int chunksize_dummy)
{
	/* If the mixer is already opened, increment open count */
	if (audio_opened)
	{
		audio_opened++;
		return (0);
	}

	/* Set the desired format and frequency */
	PSPL_AUDIO_SPEC desired;
	desired.freq		= (44100);//frequency;
	desired.format		= (AUDIO_S16);//format;
//	desired.channels	= (2);//nchannels; //(2)pspステレオ再生固定
	desired.samples 	= (1024);//chunksize;
	//
	desired.callback	= mix_channels;
	desired.userdata	= NULL;

	/* Accept nearly any audio format */
	if (PSPL_OpenAudio(&desired, &pspl_mixer) < 0)
	{
		return (-1);
	}
	#if 0
	PrintFormat("Audio device", &pspl_mixer);
	#endif

	/* Initialize the music players */
	if (open_music(&pspl_mixer) < 0)
	{
	// ここで開放は禁止 	PSPL_CloseAudio();
		return (-1);
	}
	#if (000)
	MAX_16_MIXING_CHANNELS = MAX_16_MIXING_CHANNELS;
	#endif
	#if (1==USE_MIX_CHANNEL_ALLOC)/* []malloc all mix_channel(8) */
//	mix_channel = (PSPL_MIX_CANNELS *)malloc(MAX_16_MIXING_CHANNELS * sizeof(PSPL_MIX_CANNELS));
	mix_channel = (PSPL_MIX_CANNELS *)memalign(16, MAX_16_MIXING_CHANNELS * sizeof(PSPL_MIX_CANNELS));
	#endif

	/* Clear out the audio channels */
	int i;
	for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
	{
		mix_channel[i].chunk		= NULL;
		mix_channel[i].playing		= 0;
	//	mix_channel[i].looping		= 0;/*[廃止]効果音ループ機能*/
		mix_channel[i].volume		= PSPL128_MIX_MAX_VOLUME;
	//	mix_channel[i].fade_volume	= PSPL128_MIX_MAX_VOLUME;/*[廃止]*/
	//	mix_channel[i].fading		= MIX_NO_FADING;/*[廃止]*/
//		mix_channel[i].tag			= -1;/*模倣風で使用していない*/
//000		mix_channel[i].expire		= 0;
		#if (1==USE_MIXER_EFFECT)
		mix_channel[i].effects		= NULL;
		#endif
//0000		mix_channel[i].paused		= 0;
	}
	Mix_VolumeMusic(PSPL128_MIX_MAX_VOLUME);

	#if 0
	/* now not used effects. */
	s_Mix_InitEffects();
	#endif

	audio_opened = 1;
	PSPL_PauseAudio(0);
	return (0);
}

/* Dynamically change the number of channels managed by the mixer.
   If decreasing the number of channels, the upper channels are
   stopped.
 */
#if 0/*模倣風で使用していない*/
int Mix_AllocateChannels(int numchans)
{
	if ((numchans<0) || (numchans==MAX_16_MIXING_CHANNELS))
	{return (MAX_16_MIXING_CHANNELS);}

	if (numchans < MAX_16_MIXING_CHANNELS)
	{
		/* Stop the affected channels */
		int i;
		for (i=numchans; i<MAX_16_MIXING_CHANNELS; i++)
		{
			s_Mix_HaltChannel(i);
		}
	}
	PSPL_LockAudio();
	mix_channel = (struct mix_channel_t *) realloc(mix_channel, numchans * sizeof(struct mix_channel_t));
	if (numchans > MAX_16_MIXING_CHANNELS)
	{
		/* Initialize the new channels */
		int i;
		for (i=MAX_16_MIXING_CHANNELS; i < numchans; i++)
		{
			mix_channel[i].chunk		= NULL;
			mix_channel[i].playing		= 0;
		//	mix_channel[i].looping		= 0;/*[廃止]効果音ループ機能*/
			mix_channel[i].volume		= PSPL128_MIX_MAX_VOLUME;
		//	mix_channel[i].fade_volume	= PSPL128_MIX_MAX_VOLUME;/*[廃止]*/
		//	mix_channel[i].fading		= MIX_NO_FADING;/*[廃止]*/
//			mix_channel[i].tag			= -1;/*模倣風で使用していない*/
			mix_channel[i].expire		= 0;
			mix_channel[i].effects		= NULL;
//0000			mix_channel[i].paused		= 0;
		}
	}
	MAX_16_MIXING_CHANNELS = numchans;
	PSPL_UnlockAudio();
	return (MAX_16_MIXING_CHANNELS);
}
#endif/*模倣風で使用していない*/

#if 0/*模倣風で使用していない*/
/* Return the actual mixer parameters */
int Mix_QuerySpec(int *frequency, u16 *format, int *channels)
{
	if (audio_opened)
	{
		if (frequency)		{*frequency = mixer.freq;}
		if (format) 		{*format = mixer.format;}
		if (channels)		{*channels = mixer.channels;}
	}
	return (audio_opened);
}
#endif/*模倣風で使用していない*/
//
#if 1/*模倣風で使用してい*/
/*
 * !!! FIXME: Ideally, we want a Mix_LoadSample_RW(), which will handle the
 *		 generic setup, then call the correct file format loader.
 */

/* Load a wave file */
PSPL_MIX_VOICE_CHUNK *Mix_LoadWAV_RW(SDL_RWops *src, int freesrc)
{
	u32 magic;
	PSPL_MIX_VOICE_CHUNK *chunk;
	PSPL_AUDIO_SPEC wavespec, *loaded;
	PSPL_AUDIO_CONVERT wavecvt;
	int samplesize;

	/* rcg06012001 Make sure src is valid */
	if (NULL == src)
	{
		SDL_SetError_bbb("Mix_LoadWAV_RW with NULL src");
		return (NULL);
	}

	/* Make sure audio has been opened */
	if (0 == audio_opened)
	{
		SDL_SetError_bbb("Audio device hasn't been opened");
		if (freesrc && src)
		{
			SDL_RWclose(src);
		}
		return (NULL);
	}

	/* Allocate the chunk memory */
//	chunk = (PSPL_MIX_VOICE_CHUNK *)malloc(sizeof(PSPL_MIX_VOICE_CHUNK));
	chunk = (PSPL_MIX_VOICE_CHUNK *)memalign(16, sizeof(PSPL_MIX_VOICE_CHUNK));
	if (NULL == chunk)
	{
		SDL_SetError_bbb("Out of memory");
		if (freesrc)
		{
			SDL_RWclose(src);
		}
		return (NULL);
	}

	/* Find out what kind of audio file this is */
	magic = SDL_ReadLE32(src);
	/* Seek backwards for compatibility with older loaders */
	SDL_RWseek(src, -(int)sizeof(u32), SEEK_CUR);

	switch (magic)
	{
	case WAVE:
	case RIFF:
		loaded = PSPL_LoadWAV_RW(src, freesrc, &wavespec, (u8 **)&chunk->www_abuf, &chunk->www_alen);
		break;
	#ifdef USE_WINDOWS_AIFF
	case FORM:
		loaded = Mix_LoadAIFF_RW(src, freesrc, &wavespec, (u8 **)&chunk->www_abuf, &chunk->www_alen);
		break;
	#endif	/* USE_WINDOWS_AIFF */
	#if defined(OGG_MUSIC)
	case OGGS:
		loaded = Mix_LoadOGG_RW(src, freesrc, &wavespec, (u8 **)&chunk->www_abuf, &chunk->www_alen);
		break;
	#endif
	#ifdef USE_CREATIVE_VOC
	case CREA:
		loaded = Mix_LoadVOC_RW(src, freesrc, &wavespec, (u8 **)&chunk->www_abuf, &chunk->www_alen);
		break;
	#endif
	default:
		SDL_SetError_bbb("Unrecognized sound file type");
		return (0);
	}
	if (!loaded)
	{
		free(chunk);
		return (NULL);
	}

#if 0
	PrintFormat("Audio device", &pspl_mixer);
	PrintFormat("-- Wave file", &wavespec);
#endif

	/* Build the audio converter and create conversion buffers */
	if (PSPL_BuildAudioCVT(
			&wavecvt,
			//--変換元
			wavespec.format,
			wavespec.channels_is_load_wave_only,
			wavespec.freq,
			//--変換先
			pspl_mixer.format,
			#ifdef _OLD_SDL_LINK_MODE_/*(旧互換機能)*/
			(2),//	pspl_mixer.channels, //(2)pspステレオ再生固定
			#endif
			pspl_mixer.freq) < 0)
	{
		PSPL_FreeWAV(chunk->www_abuf);
		free(chunk);
		return (NULL);
	}
	samplesize			= ((wavespec.format & 0xff)>>3) * (wavespec.channels_is_load_wave_only);/*/8*/
	wavecvt.len 		= (chunk->www_alen & (~(samplesize-1)));
	wavecvt.buf 		= (u8 *)memalign(16, (wavecvt.len * wavecvt.len_mult));
	if (wavecvt.buf == NULL)
	{
		SDL_SetError_bbb("Out of memory");
		PSPL_FreeWAV(chunk->www_abuf);
		free(chunk);
		return (NULL);
	}
	memcpy(wavecvt.buf, chunk->www_abuf, chunk->www_alen);
	PSPL_FreeWAV(chunk->www_abuf);

	/* Run the audio converter */
	if (0 > PSPL_ConvertAudio(&wavecvt))
	{
		free(wavecvt.buf);
		free(chunk);
		return (NULL);
	}
	chunk->allocated		= (1);/*(有効)*/
	chunk->www_abuf 		= wavecvt.buf;
	chunk->www_alen 		= wavecvt.len_cvt;
//[重複(channel_volumeで設定すれば不要)]	chunk->u8_volume		= PSPL_MIXER_MAX_VOLUME;
	return (chunk);
}
#endif/*模倣風で使用してい*/

//------------------------------------------------------------

#if 00/*模倣風で使用していない*/
/* Load a wave file of the mixer format from a memory buffer */
PSPL_MIX_VOICE_CHUNK *Mix_QuickLoad_WAV(u8 *mem)
{
	PSPL_MIX_VOICE_CHUNK *chunk;
	u8 magic[4];

	/* Make sure audio has been opened */
	if (0==audio_opened)
	{
		SDL_SetError_bbb("Audio device hasn't been opened");
		return (NULL);
	}

	/* Allocate the chunk memory */
	chunk = (PSPL_MIX_VOICE_CHUNK *)malloc(sizeof(PSPL_MIX_VOICE_CHUNK));
	if (chunk == NULL)
	{
		SDL_SetError_bbb("Out of memory");
		return (NULL);
	}

	/* Essentially just skip to the audio data (no error checking - fast) */
	chunk->allocated = (0);/*(無効)*/
	mem += 12; /* WAV header */
	do
	{
		memcpy(magic, mem, 4);
		mem 			+= 4;
		chunk->alen 	= ((mem[3]<<24)|(mem[2]<<16)|(mem[1]<<8)|(mem[0]));
		mem 			+= 4;
		chunk->abuf 	= mem;
		mem 			+= chunk->alen;
	} while (memcmp(magic, "data", 4) != 0);
	chunk->volume = PSPL_MIXER_MAX_VOLUME;

	return (chunk);
}
#endif/*模倣風で使用していない*/
//
#if 00/*模倣風で使用していない*/
/* Load raw audio data of the mixer format from a memory buffer */
PSPL_MIX_VOICE_CHUNK *Mix_QuickLoad_RAW(u8 *mem, u32 len)
{
	PSPL_MIX_VOICE_CHUNK *chunk;

	/* Make sure audio has been opened */
	if (0==audio_opened)
	{
		SDL_SetError_bbb("Audio device hasn't been opened");
		return (NULL);
	}

	/* Allocate the chunk memory */
	chunk = (PSPL_MIX_VOICE_CHUNK *)malloc(sizeof(PSPL_MIX_VOICE_CHUNK));
	if (chunk == NULL)
	{
		SDL_SetError_bbb("Out of memory");
		return (NULL);
	}

	/* Essentially just point at the audio data (no error checking - fast) */
	chunk->allocated	= (0);/*(無効)*/
	chunk->www_alen 		= len;
	chunk->www_abuf 		= mem;
	chunk->volume		= PSPL_MIXER_MAX_VOLUME;

	return (chunk);
}
#endif/*模倣風で使用していない*/
//
/* Free an audio chunk previously loaded */
void Mix_FreeChunk(PSPL_MIX_VOICE_CHUNK *chunk)
{
	/* Caution -- if the chunk is playing, the mixer will crash */
	if (chunk)
	{
		/* Guarantee that this chunk isn't playing */
		PSPL_LockAudio();
		#if (1==USE_MIX_CHANNEL_ALLOC)/* []malloc all mix_channel(8) */
		if (mix_channel)
		#endif
		{
			int i;
			for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
			{
				if (chunk == mix_channel[i].chunk)
				{
					mix_channel[i].playing = 0;
				}
			}
		}
		PSPL_UnlockAudio();
		/* Actually free the chunk */
		if (chunk->allocated)/*(有効なら開放)*/
		{
			free(chunk->www_abuf);
		}
		free(chunk);
	}
}


#if 00/*模倣風で使用していない*/
/* Set a function that is called after all mixing is performed.
   This can be used to provide real-time visual display of the audio stream
   or add a custom mixer filter for the stream data.
*/
void Mix_SetPostMix(void (*mix_func)(void *udata, u8 *stream, int len), void *arg)
{
	PSPL_LockAudio();
	mix_postmix_data	= arg;
	mix_postmix 		= mix_func;
	PSPL_UnlockAudio();
}
#endif/*模倣風で使用していない*/
//
#if 00/*[廃止]フックしない*/
/* Add your own music player or mixer function.
   If 'mix_func' is NULL, the default music player is re-enabled.
 */
void Mix_HookMusic(void (*mix_func)(void *udata, u8 *stream, int len), void *arg)
{
	PSPL_LockAudio();
	if (mix_func != NULL)
	{
		music_data	= arg;
		mix_music	= mix_func;
	}
	else
	{
		music_data	= NULL;
		mix_music	= custom_music_mixer;
	}
	PSPL_UnlockAudio();
}

void *Mix_GetMusicHookData(void)
{
	return (music_data);
}
#endif/*[廃止]フックしない*/
//
#if 00/*模倣風で使用していない*/
void Mix_ChannelFinished(void (*channel_finished)(int channel))
{
	PSPL_LockAudio();
	channel_done_callback = channel_finished;
	PSPL_UnlockAudio();
}
#endif/*模倣風で使用していない*/
//
#if 00/*模倣風で使用していない*/
/* Reserve the first channels (0 -> n-1) for the application, i.e. don't allocate
   them dynamically to the next sample if requested with a -1 value below.
   Returns the number of reserved channels.
 */
int Mix_ReserveChannels(int num)
{
	if (num > MAX_16_MIXING_CHANNELS)
	{	num = MAX_16_MIXING_CHANNELS;}
	reserved_channels = num;
	return (num);
}
#endif/*模倣風で使用していない*/
//
#if 0//000//[release]
//
/*("psp devkit r15, r16"には GCC_VERSION を定義したファイル自体が無い。)*/
#include <./../../i686-pc-mingw32/psp/include/ansidecl.h>
#ifndef GCC_VERSION
	error(
		"not support! gcc 4.1.0 or higher version.\n"
		"gcc 4.1.0未満はアンサポートです。");
#endif

#if (GCC_VERSION < 4400)
	/*[GCC435では、よくわかんないけど有効にしとく(取るとプチノイズが出る)]*/
	#define LINK_CHECK_CHUNK	(1)
#else
	/*[GCC462では、ハングアップするので無効にする。ただしプチノイズが出る。]*/
	#define LINK_CHECK_CHUNK	(0)
#endif
//
#else//[debug]
	/*[GCC435では、よくわかんないけど有効にしとく(取るとプチノイズが出る)]*/
	/*[GCC462では、ハングアップするので無効にする。ただしプチノイズが出る。]*/
	#define LINK_CHECK_CHUNK	(0)/*[ただしプチノイズが出る。]*/
#endif//000
// 1074556
/* Play an audio chunk on a specific channel.
   If the specified channel is -1, play on the first free channel.
   'ticks' is the number of milliseconds at most to play the sample, or -1
   if there is no limit.
   Returns which channel was used to play the sound.
*/
#if 0//(1==LINK_CHECK_CHUNK)/*[原版のメモ]*/ // 1074652
static int checkchunkintegral(PSPL_MIX_VOICE_CHUNK *chunk)
{
	int frame_width = 1;
	if ((pspl_mixer.format & 0xff) == 16)	{frame_width = 2;}
	frame_width *= pspl_mixer.channels_is_load_wave_only;
	/*[GCC462では、ここの割り算(%)でハングアップする]*/while (chunk->www_alen % frame_width)	{chunk->www_alen--;}
	return (chunk->www_alen);
}
#endif/*[原版のメモ]*/
//
#if (1==LINK_CHECK_CHUNK)/*模倣風で使用している*/
static int checkchunkintegral(PSPL_MIX_VOICE_CHUNK *chunk)
{
	int frame_width;
	frame_width = (pspl_mixer.channels_is_load_wave_only);
	#if 1/*[追加]*/
	if (0==frame_width) {return (0);}
	#endif
	//
	if ((pspl_mixer.format & 0xff) == 16)
			{frame_width += (frame_width);}
	//
	#if 0/*[追加]*/
	if (0==frame_width) {return (0);}
	#endif
	{
		my_loop:
			;
		int new_length;
		/*[GCC462では、ここの割り算(%)でハングアップする]*/new_length = ((unsigned)chunk->www_alen % (unsigned)frame_width);
		if (new_length)
		{
			chunk->www_alen--;
			if (0 >= chunk->www_alen) return (0);
			goto my_loop;
		}
	}
	//
	return (chunk->www_alen);
}
#endif/*模倣風で使用している*/
//
#if 1/*模倣風で使用している*/
/* Check the status of a specific channel.
   If the specified mix_channel is -1, check all mix channels.
*/
static int s_Mix_Playing(int which)
{
	int status;
	status = 0;
	if (-1 == which)
	{
		int i;
		for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
		{
			if ((0 < mix_channel[i].playing)
		//	 || (0 < mix_channel[i].looping)/*[廃止]効果音ループ機能*/
			)
			{status++;}
		}
	}
	else
	{
		if ((0 < mix_channel[which].playing)
	//	 || (0 < mix_channel[which].looping)/*[廃止]効果音ループ機能*/
		)
		{status++;}
	}
	return (status);
}
//int Mix_PlayChannelTimed(int which, PSPL_MIX_VOICE_CHUNK *chunk, int loops, int ticks)
//int Mix_PlayChannel(int which, PSPL_MIX_VOICE_CHUNK *chunk)//, int loops)//, int ticks)
/*int*/void sdl_mixer_play_channel(int play_track_number, PSPL_MIX_VOICE_CHUNK *chunk/*, int dummy1, int dummy2*/)//, 0==int loops, -1==int ticks)
{
	/* Don't play null pointers :-) */
	if (chunk == NULL)
	{
		Mix_SetError_bbb("Tried to play a NULL chunk");
		return /*(-1)*/;
	}
	#if (1==LINK_CHECK_CHUNK)/*(よくわかんない)*/
	if (0 == checkchunkintegral(chunk))
	{
		Mix_SetError_bbb("Tried to play a chunk with a bad frame");
		return /*(-1)*/;
	}
	#endif /*(よくわかんない)*/
	/* Lock the mixer while modifying the playing channels */
	PSPL_LockAudio();
	{
		/* If play_track_number is -1, play on the first free channel */
		if (play_track_number == -1)
		{
			int i;
			for (i=reserved_channels; i<MAX_16_MIXING_CHANNELS; i++)
			{
				if (mix_channel[i].playing <= 0)
				{	break;}
			}
			if (i == MAX_16_MIXING_CHANNELS)
			{
				Mix_SetError_bbb("No free channels available");
				play_track_number = -1;
			}
			else
			{
				play_track_number = i;
			}
		}

		/* Queue up the audio data for this channel */
		if (play_track_number >= 0)
		{
//			u32 sdl_ticks = SDL_GetTicks_bbb();/*模倣風で使用していない*/
			if (s_Mix_Playing(play_track_number))
			{	s_Mix_channel_done_playing(play_track_number);}
			mix_channel[play_track_number].samples		= chunk->www_abuf;
			mix_channel[play_track_number].playing		= chunk->www_alen;
		//	mix_channel[play_track_number].looping		= 0;//loops;/*[廃止]効果音ループ機能*/
			mix_channel[play_track_number].chunk		= chunk;
//0000		mix_channel[play_track_number].paused		= 0;
		//	mix_channel[play_track_number].fading		= MIX_NO_FADING;/*[廃止]*/
//			mix_channel[play_track_number].start_time	= sdl_ticks;/*模倣風で使用していない*/
//000		mix_channel[play_track_number].expire		= 0;//(ticks>0) ? (sdl_ticks + ticks) : 0;
		}
	}
	PSPL_UnlockAudio();
	/* Return the channel on play_track_number the sound is being played */
	return /*(play_track_number)*/;
}
#endif/*模倣風で使用している*/
//
#if 00/*模倣風で使用していない*/
/* Change the expiration delay for a channel */
int Mix_ExpireChannel(int which, int ticks)
{
	int status = 0;
	if (which == -1)
	{
		int i;
		for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
		{
			status += Mix_ExpireChannel(i, ticks);
		}
	}
	else
	if (which < MAX_16_MIXING_CHANNELS)
	{
		PSPL_LockAudio();
		mix_channel[which].expire = (ticks>0) ? (SDL_GetTicks_bbb() + ticks) : 0;
		PSPL_UnlockAudio();
		status++;
	}
	return (status);
}
#endif/*模倣風で使用していない*/
//
#if 00/*模倣風で使用していない*/
/* Fade in a sound on a channel, over ms milliseconds */
int Mix_FadeInChannelTimed(int which, PSPL_MIX_VOICE_CHUNK *chunk, int loops, int ms, int ticks)
{
	/* Don't play null pointers :-) */
	if (chunk == NULL)
	{
		return (-1);
	}
	#if (0)/*(よくわかんない)*/
	if (0 == checkchunkintegral(chunk))
	{
		Mix_SetError_bbb("Tried to play a chunk with a bad frame");
		return (-1);
	}
	#endif /*(よくわかんない)*/
	/* Lock the mixer while modifying the playing channels */
	PSPL_LockAudio();
	{
		/* If which is -1, play on the first free channel */
		if (which == -1)
		{
			int i;
			for (i=reserved_channels; i<MAX_16_MIXING_CHANNELS; i++)
			{
				if (mix_channel[i].playing <= 0)
				{	break;}
			}
			if (i == MAX_16_MIXING_CHANNELS)
			{
				which = -1;
			}
			else
			{
				which = i;
			}
		}

		/* Queue up the audio data for this channel */
		if (which >= 0)
		{
			u32 sdl_ticks = SDL_GetTicks_bbb();
			if (s_Mix_Playing(which))
			{	s_Mix_channel_done_playing(which);}
			mix_channel[which].samples		= chunk->abuf;
			mix_channel[which].playing		= chunk->alen;
			mix_channel[which].looping		= loops;
			mix_channel[which].chunk		= chunk;
//0000		mix_channel[which].paused		= 0;
			mix_channel[which].fading		= MIX_FADING_IN;
			mix_channel[which].fade_volume	= mix_channel[which].volume;
			mix_channel[which].volume		= 0;
			mix_channel[which].fade_length	= (u32)ms;
//			mix_channel[which].start_time	= /*模倣風で使用していない*/
			mix_channel[which].ticks_fade 	= sdl_ticks;
			mix_channel[which].expire		= (ticks > 0) ? (sdl_ticks+ticks) : (0);
		}
	}
	PSPL_UnlockAudio();

	/* Return the channel on which the sound is being played */
	return (which);
}
#endif/*模倣風で使用していない*/
//
#if 00/*模倣風で使用していない*/
/* Fade out a channel and then stop it automatically */
int Mix_FadeOutChannel(int which, int ms)
{
	int status;
	status = 0;
	if (audio_opened)
	{
		if (which == -1)
		{
			int i;
			for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
			{
				status += Mix_FadeOutChannel(i, ms);
			}
		}
		else
		{
			PSPL_LockAudio();
			if (mix_channel[which].playing &&
				(mix_channel[which].volume > 0) &&
				(mix_channel[which].fading != MIX_FADING_OUT)
			)
			{
				mix_channel[which].fading = MIX_FADING_OUT;
				mix_channel[which].fade_volume = mix_channel[which].volume;
				mix_channel[which].fade_length = ms;
				mix_channel[which].ticks_fade = SDL_GetTicks_bbb();
				status++;
			}
			PSPL_UnlockAudio();
		}
	}
	return (status);
}
#endif/*模倣風で使用していない*/
//
#if 00/*模倣風で使用していない*/
/* Halt playing of a particular group of channels */
int Mix_FadeOutGroup(int tag, int ms)
{
	int status = 0;
	int i;
	for (i=0; i<MAX_16_MIXING_CHANNELS; i++)
	{
		if (mix_channel[i].tag == tag)
		{
			status += Mix_FadeOutChannel(i, ms);
		}
	}
	return (status);
}
Mix_Fading Mix_FadingChannel(int which)
{
	return mix_channel[which].fading;
}
#endif/*模倣風で使用していない*/
