
#include "psp_vfpu.h"

/*---------------------------------------------------------
	sin,cos
	-------------------------------------------------------
	Calculate sine and cosine. ()

	@param angle	 - input in radians. ()
	@param sin_value - pointer to float for sin. ()
	@param cos_value - pointer to float for cos. ()
---------------------------------------------------------*/
#if (0)
void vfpu_sincos(float angle_radian, float *sin_value, float *cos_value)
{
	__asm__ volatile (
		"mtv        %2, S002\n" 			/* S002 = (r); */
		"vcst.s     S003, VFPU_2_PI\n"		/* S003 = (2/PI); */
		"vmul.s     S002, S002, S003\n" 	/* r = r * (2/PI); */
		"vrot.p     C000, S002, [s, c]\n"	/* S000 = sin(r), S001 = cos(r); */
		"mfv        %0, S000\n" 			/* sin_value = S000; */
		"mfv        %1, S001\n" 			/* cos_value = S001; */
		: "=r"(*sin_value), "=r"(*cos_value): "r"(angle_radian));
}
http://cppdiary.blog76.fc2.com/blog-entry-52.html
FPU命令によるサインとコサインの同時取得 2010.05.20 Thu
FPU 命令の１つである fsincos はサインとコサインを同時に計算します。
今回のコードはインラインアセンブラで記述しています。
sin, cos 関数で別々に取得する場合に比べかなり高速です。
void vfpu_sincos(float angle_radian, float *sin_value, float *cos_value)
{
	float cos_tmp;
	float sin_tmp;
	__asm
	{
		fld 	angle_radian
		fsincos
		fstp	cos_tmp
		fstp	sin_tmp
	}
	*sin_value = sin_tmp;
	*cos_value = cos_tmp;
}
#endif
/*---------------------------------------------------------
	sin,cos
	-------------------------------------------------------
	説明:
		一周1024分割の角度を指定して、
		t256形式のsin()とcos()の値を同時に取得します。
	-------------------------------------------------------
	原理:
		sin_value_t256 = sin1024(angle_1024);
		cos_value_t256 = cos1024(angle_1024);
	-------------------------------------------------------
	使用書式:
		vfpu_sincos(angle_1024, &sin_value_t256,&cos_value_t256);
---------------------------------------------------------*/

#if (0)
/*
vfpu内部単位は、[象限]単位。
１[周]は4[象限]だから
1024 == 4[象限] x (1<<8)[倍] x (1.0f[内部harf_float])
となる。
*/
void int256_sincos1024(int angle_1024, int *sin_value_t256, int *cos_value_t256)
{
	__asm__ volatile (
		"mtv        %2, S002\n" 			/* S002 = (angle_1024); */
	//	"vcst.s     S003, VFPU_2_PI\n"		/* S003 = (2/PI); */
	//	"vmul.s     S002, S002, S003\n" 	/* x = x * (2/PI); */
		"vi2f.s     S002, S002,    8\n" 	/* S002 = ((float)(S002)/(float)(256.0f)); [int→float変換](1周が1024分割) */
	//----[memo]----
	//	"vi2f.s     S002, S002,    8\n" 	/* S002 = ((float)(S002)/(float)(256.0f)); (ok)[int→float変換](1周が1024分割) */
	//	"vi2f.s     S002, S002,    7\n" 	/* S002 = ((float)(S002)/(float)(128.0f)); (?) [int→float変換](1周が512分割) */
	//	"vi2f.s     S002, S002,    6\n" 	/* S002 = ((float)(S002)/(float)( 64.0f)); (?) [int→float変換](1周が256分割) */
	//	"vi2f.s     S002, S002,    5\n" 	/* S002 = ((float)(S002)/(float)( 32.0f)); (ok)[int→float変換](1周が128分割) */
	//	"vi2f.s     S002, S002,    4\n" 	/* S002 = ((float)(S002)/(float)( 16.0f)); (?) [int→float変換](1周が 64分割) */
	//----[memo]----
		"vrot.p     C000, S002, [s, c]\n"	/* S000 = sin(r), S001 = cos(r); */
	//	#if (0) 	// 同じ。 */
	//	"vf2iu.s    S000, S000,    8\n" 	// S000 = (int)(S000 * (256.0f)); [float→int変換] */
	//	"vf2iu.s    S001, S001,    8\n" 	// S001 = (int)(S001 * (256.0f)); [float→int変換] */
	//	#else
		"vf2iu.p    C000, C000,    8\n" 	/* C000.p = (int)(C000.p * (256.0f)); [float→int変換] */
	//	#endif
		"mfv        %0, S000\n" 			/* sin_value_t256 = S000; */
		"mfv        %1, S001\n" 			/* cos_value_t256 = S001; */
		: "=r"(*sin_value_t256), "=r"(*cos_value_t256): "r"(angle_1024));
}
#endif


#if (1)
/*
vfpu内部単位は、[象限]単位。
１[周]は4[象限]だから
65536 == 4[象限] x (1<<14)[倍] x (1.0f[内部harf_float])
となる。
*/
void int256_sincos65536(int angle_65536, int *sin_value_t256, int *cos_value_t256)
{
	__asm__ volatile (
		"mtv        %2, S002\n" 			/* S002 = (angle_1024); */
	//	"vcst.s     S003, VFPU_2_PI\n"		/* S003 = (2/PI); */
	//	"vmul.s     S002, S002, S003\n" 	/* x = x * (2/PI); */
	//	"vi2f.s     S002, S002,    8\n" 	/* S002 = ((float)(S002)/(float)(256.0f)); [int→float変換](1周が1024分割) */
		"vi2f.s     S002, S002,   14\n" 	/* S002 = ((float)(S002)/(float)(256.0f)); [int→float変換](1周が65536分割) */
	//----[memo]----
	//	"vi2f.s     S002, S002,    8\n" 	/* S002 = ((float)(S002)/(float)(256.0f)); (ok)[int→float変換](1周が1024分割) */
	//	"vi2f.s     S002, S002,    7\n" 	/* S002 = ((float)(S002)/(float)(128.0f)); (?) [int→float変換](1周が512分割) */
	//	"vi2f.s     S002, S002,    6\n" 	/* S002 = ((float)(S002)/(float)( 64.0f)); (?) [int→float変換](1周が256分割) */
	//	"vi2f.s     S002, S002,    5\n" 	/* S002 = ((float)(S002)/(float)( 32.0f)); (ok)[int→float変換](1周が128分割) */
	//	"vi2f.s     S002, S002,    4\n" 	/* S002 = ((float)(S002)/(float)( 16.0f)); (?) [int→float変換](1周が 64分割) */
	//----[memo]----
		"vrot.p     C000, S002, [s, c]\n"	/* S000 = sin(r), S001 = cos(r); */
	//	#if (0) 	// 同じ。 */
	//	"vf2iu.s    S000, S000,    8\n" 	// S000 = (int)(S000 * (256.0f)); [float→int変換] */
	//	"vf2iu.s    S001, S001,    8\n" 	// S001 = (int)(S001 * (256.0f)); [float→int変換] */
	//	#else
		"vf2iu.p    C000, C000,    8\n" 	/* C000.p = (int)(C000.p * (256.0f)); [float→int変換] */
	//	#endif
		"mfv        %0, S000\n" 			/* sin_value_t256 = S000; */
		"mfv        %1, S001\n" 			/* cos_value_t256 = S001; */
		: "=r"(*sin_value_t256), "=r"(*cos_value_t256): "r"(angle_65536));
}
#endif

