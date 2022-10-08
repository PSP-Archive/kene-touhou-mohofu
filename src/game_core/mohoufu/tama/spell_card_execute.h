
/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	カードインタプリター
	-------------------------------------------------------
	カードCPUの実行部分。
	-------------------------------------------------------
	(r41)現在 CPUの仕様は確定していません。(設計中です)
	命令はともかく、デクリメントはめんどくさいから全部出来る様にしちゃえ、
	と思わなくもないですが、対応しないと CPUのコードが小さくなるというメリットもあります。
	(元々デクリメントは全部できる規格の予定でした。)
	-------------------------------------------------------
	将来的に objのコントロールも CPUに入る予定なので、
	CPUのコードが小さければ小さい方が、良いです。
	-------------------------------------------------------
	CPUのコードが小さければ小さい方が(キャッシュのヒット率が上がるので)、ゲーム全体の速度があがります。
	というかキャッシュに載る大きさにすれば、どんな大きさでも良いです。
	CPUのコードが大きくなりすぎてキャッシュに載らない場合、速度低下してゲームにならないと思います。
	-------------------------------------------------------
	OP_01_MOVER_PD 命令のデクリメントと
	メモリロングショートアドレッシングのショートアドレッシングの場合のデクリメントは
	最低でも残す予定です。
	とりあえず、インクリメント/デクリメントは OP_01_MOVER_PD 命令 でやった方が良い気がします。
	-------------------------------------------------------
	不要な命令は 排除する方針です。
---------------------------------------------------------*/

//#include "spell_micro_code.h"
/*---------------------------------------------------------
	メンバ関数(private:)
	-------------------------------------------------------
	プライベートな関数は外部に出さないので、
	間違えて出したらコンパイルエラーになるよう細工しとく。
---------------------------------------------------------*/


/*---------------------------------------------------------
	(r35)定数等
---------------------------------------------------------*/
//#define MAX_I_COUNT	(8192)/* (1/60)あたりの最大処理命令。 */

global int spell_register[REG_NUM_99_MAX];



#if (0)/*(将来的にカードインタプリタ上で動作する命令に移行する)*/
/*---------------------------------------------------------
	(r35)これらの関数は、レジスタではなく、レジスタ番号を渡すので注意の事。
	間違えてレジスタ渡した場合、間違い無くpspがハングアップする。
	間違いやすいので、関数名にNUMを入れた。
	-------------------------------------------------------
	(r35)これらの関数が、何故レジスタ値を渡さないかというと、
	カードスクリプト用命令に移行した場合、
	カードスクリプトではそもそもレジスタ値を渡せない。
	という仕様のスクリプトを予定している。
	理由はレジスタ値を渡すとスクリプトの実行速度が低下するから。
---------------------------------------------------------*/
#endif


/*てすと*/extern void audio_voice_play(void);
/*てすと*/extern void audio_auto_bullet_play(void);
static CPU_FUNC(cpu_auto_bullet_play_default);
/*---------------------------------------------------------
	カードCPUユニットのカード命令を1命令実行する。
---------------------------------------------------------*/

#define USE_CPU_DEBUG_MODE (0)
#if (1==USE_CPU_DEBUG_MODE)
static u32 opecode_history[4];
static u32 opecode_history_pointer;
static u32 hook_counter = (1);
u32 *codebase_bak;
	#define opcode_fetch()\
	{\
		fetch_data32 = /**/\
		opecode_history[opecode_history_pointer] = (*codebase);\
		codebase++;\
		opecode_history_pointer++;\
		opecode_history_pointer &= 3;\
	}
//	#define OP_NOP_debug OP_NEXT
	#define OP_NOP_debug OP_0b_BRA_RS/*(てすと)*/
#else
	#define opcode_fetch()	{fetch_data32 = (*codebase);codebase++;}
	#define OP_NOP_debug OP_NEXT
#endif

// (基本命令)-------- レジスタアドレッシング。
#define OP0x00		OP_00_EXIT
#define OP0x01		OP_01_MOVER_PD
#define OP0x02		OP_02_COUNTER
#define OP0x03		OP_03_nan_ido
#define OP0x04		OP_04_ADDR_PD
#define OP0x05		OP_05_SUBR_PD/*[符号反転命令]*/
#define OP0x06		OP_06_BRAR_NN	// ジャンプテーブル命令[無条件分岐(レジスタ値)](この命令は必要)
#if 0/*(仮)*/
	#define OP0x07	OP_06_REGIST_PROCESS/*(まだ作ってないけど、この命令は必要。)*/
#else
	#define OP0x07	OP_NOP_debug/*(仮)*/
#endif
// (ブランチ系命令)--------
#define OP0x08		OP_08_BNE_RS		// ブランチ系命令[値が違えば分岐](この命令は必要)
#define OP0x09		OP_09_BFL_RS		// ブランチ系命令[値が即値よりフローしたら分岐](この命令は必要)
#define OP0x0a		OP_0a_BRA_TABLE 	// ブランチ系命令[配列](この命令は必要)
#define OP0x0b		OP_0b_BRA_RS		// ブランチ系命令[無条件分岐(即値)](この命令は必要)
// (基本弾発生命令)--------
#define OP0x0c		OP_0c_hatudan_system_regist_tama/*single*/
#define OP0x0d		OP_0d_AUDIO_VOICE_PLAY
#define OP0x0e		OP_0e_AUDIO_AUTO_BULLET_PLAY_SET_18
#define OP0x0f		OP_0f_CLEAR_ZERO_PAGE
//	(サポート命令)--------
#define OP0x10		OP_10_SINCOS256
#define OP0x11		OP_11_BOSS_TO_JIKI_NERAI
#define OP0x12		OP_12_JIKI_NERAI
#define OP0x13		OP_13_HANYOU_NERAI
#define OP0x14		OP_14_MULTIPREX_RATE_VECTOR
#define OP0x15		OP_15_RAND_VALUE
#define OP0x16		OP_16_RAND_INIT
#define OP0x17		OP_17_DIV65536
//
#if 0
//	(弾(OBJ)制御命令)-------- 弾==(OBJなので、雑魚ボス等も同じ仕組みでスペカCPUから操作出来る)
//	OP_xx_OBJ_REGIST_HEAD	// 操作する弾の先頭アドレスをスペカCPUに登録する。
//	OP_xx_OBJ_LOAD_VALUE	// 弾の設定値をレジスタに読み込む。
//	OP_xx_OBJ_STORE_VALUE	// レジスタ値を弾の設定値へ書き込む。
//	間接操作なので遅い。
#endif
//
//#define OP0x06	OP_NOP_debug/*OP_06_ASRR_PD*/
//#define OP0x07	OP_NOP_debug/*OP_07_ASLR_PD*/
/*OP_03_ANDR_PD*/
/*OP_18_hatudan_system_regist_n_way*/
/*OP_18_hatudan_system_regist_katayori_n_way*/

// (拡張命令[CPU外部コード(命令)])-------- メモリロングショートアドレッシング。
#define OP0x18		OP_NOP_debug// メモリロングショートアドレッシング。
#define OP0x19		OP_NOP_debug// メモリロングショートアドレッシング。
#define OP0x1a		OP_NOP_debug// メモリロングショートアドレッシング。
#define OP0x1b		OP_MLS// メモリロングショートアドレッシング。
#define OP0x1c		OP_MLS// メモリロングショートアドレッシング。
#define OP0x1d		OP_MLS// メモリロングショートアドレッシング。
#define OP0x1e		OP_MLS// メモリロングショートアドレッシング。
#define OP0x1f		OP_MLS// メモリロングショートアドレッシング。
// (拡張命令[CPU内部コード])-------- メモリロングショートアドレッシング。
/*[未使用]*/#define OB0x20		OP_NOP_debug
/*[未使用]*/#define OB0x21		OP_NOP_debug
/*[未使用]*/#define OB0x22		OP_NOP_debug
/*[OP_MLS]*/#define OB0x23		OB_1b_CALC_ADDM_LONG_PD// ロングメモリアドレッシング専用命令。
// (拡張命令)-------- メモリアドレッシング。
/*[OP_MLS]*/#define OB0x24		OB_1c_CALC_MOVEM_PD// メモリロングショートアドレッシング。
/*[OP_MLS]*/#define OB0x25		OB_1d_CALC_ANDM_PD// メモリロングショートアドレッシング。
/*[OP_MLS]*/#define OB0x26		OB_1e_CALC_ASRM_PD// メモリロングショートアドレッシング。
/*[OP_MLS]*/#define OB0x27		OB_1f_CALC_ASLM_PD// メモリロングショートアドレッシング。
// (拡張命令)--------
/*OB_1d_CALC_SUBM_PD*/	/*(この命令は要らないかも。[用途が無い気がする])*/

#define USE_VFPU_INTEGER_DIVISOR (1)
#if (1==USE_VFPU_INTEGER_DIVISOR)
/*--------------------DSS-------------------------------------
	avoid cpu pipeline breaking, using the vfpu divide.
	vfpuで割り算することにより、cpuのパイプラインブレイクを防ぐ。
	-------------------------------------------------------
	usage: 使い方。
		s32 result_value;
		s32 value000;
		s32 value111;
		value000 = 65536;
		value111 = 7;
		vfpu_div_s32(&result_value, value000, value111);// result_value = value000 / value111;
	result: 結果。
		result_value == 9362; // 9362.285714285714 == 65536 / 7;
	-------------------------------------------------------
	精度に関しては良くわかんない。
---------------------------------------------------------*/
inline static void vfpu_div_s32(int *result_value000, int value000, int value111)
{
	int result_value;
	// result_value = value000 / value111;
	__asm__ volatile (
		"mtv        %1, S000\n" 			/* S000 = (value000); */
		"mtv        %2, S001\n" 			/* S001 = (value111); */
		#if 0/*(means same.同じ)*/
	//	"vi2f.s     S000, S000,    0\n" 	/* S000 = ((float)(S000)/(float)(0.0f)); [from int to → float conversion.変換] */
	//	"vi2f.s     S001, S001,    0\n" 	/* S001 = ((float)(S001)/(float)(0.0f)); [from int to → float conversion.変換] */
		#else
		"vi2f.p     C000, C000,    0\n" 	/* C000.p = ((float)(C000.p)/(float)(0.0f)); [from int to → float conversion.変換] */
		#endif
		"vdiv.s     S002, S000, S001\n" 	// S002 = S000 / S001	// result_value = value000 / value111;
		"vf2iu.s    S002, S002,    0\n" 	/* S000.s = (int)(S000.s * (0.0f));[from float to → int conversion.変換] */
		"mfv        %0, S002\n"
		: "=r"(result_value)				/* %0(result_value) [output.出力]*/
		: "r"(value000), "r"(value111)		/* %1(value000), %2(value111) [input.入力]*/
	);
	(*result_value000) = (s32)(result_value);
}
#endif

extern int atan_65536(int y, int x);/*(vfpu/math_atan65536i.c)*/
extern void cpu_exec(u32 *codebase, s32 icount)
{
	/*
	何故か 'const' を 'static const' にすると遅くなる。
	'static const' じゃなくて 'const' の方がコードが大きくなるが速い。
psp-gcc -v
Using built-in specs.
Target: psp
Configured with: ../../gcc-4.3.5/configure --build=i686-pc-mingw32
 --prefix=/pspsdk --target=psp --enable-languages=c,c++,objc,obj-c++,d
 --enable-cxx-flags=-G0 --with-newlib --with-headers --disable-win32-registry
 --disable-nls --disable-libstdcxx-pch --with-libiconv-prefix=/usr/local
 --with-gmp-include=/usr/local/include --with-gmp-lib=/usr/local/lib
 --with-mpfr-include=/usr/local/include --with-mpfr-lib=/usr/local/lib
Thread model: single
gcc version 4.3.5 (GCC)
	*/
	#define OB0x99_MAX	(0x08)/*[CPU内部コードの最大数]*/
	/*static*/ const void *jump_table_basic[(OP0x99_MAX + OB0x99_MAX)] __attribute__((aligned(16))) =/*(基本オペコード[basic opecodes])*/
	{	// 0x30 == (OP0x99_MAX + OB0x99_MAX);
		// [CPU外部命令]
		&&OP0x00, &&OP0x01, &&OP0x02, &&OP0x03, &&OP0x04, &&OP0x05, &&OP0x06, &&OP0x07,// (基本命令)-------- /
		&&OP0x08, &&OP0x09, &&OP0x0a, &&OP0x0b, &&OP0x0c, &&OP0x0d, &&OP0x0e, &&OP0x0f,// (基本命令)-------- /
		&&OP0x10, &&OP0x11, &&OP0x12, &&OP0x13, &&OP0x14, &&OP0x15, &&OP0x16, &&OP0x17,// (サポート命令)-------- /
		&&OP0x18, &&OP0x19, &&OP0x1a, &&OP0x1b, &&OP0x1c, &&OP0x1d, &&OP0x1e, &&OP0x1f,// (拡張命令)-------- メモリロングショートアドレッシング。
		// [CPU内部コード]
		&&OB0x20, &&OB0x21, &&OB0x22, &&OB0x23, &&OB0x24, &&OB0x25, &&OB0x26, &&OB0x27,// [CPU内部コード]-------- メモリロングショートアドレッシング。
	};
//	/*static*/ const void *jump_table_memory_long_short[(8)] __attribute__((aligned(16)));/*(メモリロングショートアドレッシング。[addressing for memory long/short.])*/
//	#define JUMP_TABLE_MEMORY_LONG_SHORT_OFFSET 	(0x28)/*(オフセット)*/
	u32 fetch_data32;/*(32[bit] fetch code. it used opecodes and fetch data or temporary.)*/
loop_start:
	opcode_fetch();/*[fech]*/
	u8 op = ((fetch_data32 >>  0)/*& 0x3f*/);/*(とりあえず)*/
	u8 v0 = ((fetch_data32 >>  8)/*& 0xff*/);
	u8 ra = ((fetch_data32 >> 16)/*& 0xff*/);
	u8 rb = ((fetch_data32 >> 24)/*& 0xff*/);
	#if (1==USE_CPU_DEBUG_MODE)
	if ((u8)0x1f < op)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// 半角40字"最大表示文字数"
			"CPU命令エラー: %08x は意味が判りません。" "\\n"
			"%08x %08x %08x %08x %d" "\\n",
			fetch_data32,
			opecode_history[0],
			opecode_history[1],
			opecode_history[2],
			opecode_history[3],
			opecode_history_pointer
		);
	}
	#else
	if ((u8)0x1f < op)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// 半角40字"最大表示文字数"
			"CPU命令エラー: %08x は意味が判りません。" "\\n",
			fetch_data32
		);
	}//1111022f
	#endif
	#if 0
	0a0a0f0b // MCODE(OP0x1d_ANDM_PD, R0f, R0a, R0a),
	0a0a0f16 // MCODE(OP0x16_RAND_INIT, R0f, R0a, R0a),
	0a0a0f21 // MCODE(OP0x06_BNE_RS, R0f, R0a, R0a),
	0c074678 // MCODE(OP0x78__???
	3
	#endif
MLS_COMMON:
	goto *jump_table_basic[(op)];
/*-------------------------------------------------------*/
OP_MLS:// メモリロングショートアドレッシング。
	if (LONG_MEMORY_ADDRESSING==v0)
			{opcode_fetch();/*[fech]*/}/*(ロングメモリアドレッシング)*/
	else	{fetch_data32 = (s32)(s8)v0;v0 = 0;}/*(ショートメモリアドレッシング)*/ /*([必要]インデックス付/デクリメント付)*/
	// ショートメモリアドレッシングは、デクリメント必須です。でないとあんま意味無いよーな気がする。
//	goto *jump_table_memory_long_short[(op & 0x07)];
//	goto *jump_table_basic[JUMP_TABLE_MEMORY_LONG_SHORT_OFFSET+(op & 0x07)];
//	goto *jump_table_basic[(op+8)];
	op += 8;
	goto MLS_COMMON;
/*-------------------------------------------------------*/
//
/*---------------------------------------------------------
[基本命令]	カウンター命令。
	-------------------------------------------------------
	この命令は、原理的には無くても出来ますが、(実行速度等の観点も踏まえて)
	あった方が便利なので存在します。
	スペカコンパイラの設計も(たぶん)楽になりますし。
	-------------------------------------------------------
	動作: 指定したレジスタの値「カウンタ値」を +1 します。
	これだけだと、 ADD_R REG = REG + #1; や MOVE_R REG = REG + ix(#1); と同じですが、
	この命令の場合「カウンタ上限」が設定できて、「カウンタ上限」を超えると、
	自動的に「カウンタ値」が「0」になります。
	-------------------------------------------------------
	「カウンタ上限」の指定方法は基本的には「即値」で命令の中に含まれますが、
	[レジスタ間接アドレッシング]を使用して「レジスタ値」(カウンタ値ではない)で、指定できます。
	これは、難易度別に弾数や弾の時間間隔等が変化するもので使用します。
---------------------------------------------------------*/
	#if 0/*[メモ]*/
	spell_register[ra]++;
	if (REGISTER_ADDRESSING==v0)/*[レジスタ間接アドレッシング]*/
	{
		if (spell_register[rb] <= (spell_register[ra]))
		{spell_register[ra] = (0);}
	}
	else/*[即値アドレッシング]*/
	{
		if (v0 <= (spell_register[ra]))
		{spell_register[ra] = (0);}
	}
	goto OP_NEXT;
	#endif
OP_02_COUNTER://	(r35)カードスクリプト用命令(カウンター)
	#if 1// [レジスタ間接アドレッシング] == 難易度別に弾数や弾の時間間隔等が変化するもの専用のカウンタ命令。
	if (REGISTER_ADDRESSING == v0)/*[レジスタ間接アドレッシング]*/
	{v0 = spell_register[rb];}
	#endif
//	else/*[即値アドレッシング]*/	{;}
	// [即値アドレッシング]==通常のカウンタ命令。(通常の場合、カウンタ命令は即値以外用途が無い。)
	spell_register[ra]++;
	if (v0 <= (spell_register[ra]))
	{spell_register[ra] = (0);}
	goto OP_NEXT;
/*---------------------------------------------------------
[基本命令]	レジスタ間転送命令。
	-------------------------------------------------------
	この命令は、レジスタの値を他のレジスタにコピーします。
	-------------------------------------------------------
	コピーする際に、インクリメント や デクリメント(加減算)機能があります。
	(正確な名称は プリインクリメント / プリデクリメント)
	-------------------------------------------------------
	「即値」の加減算はこの命令でできますが、
	「レジスタ値」の加減算はこの命令でできないので、ADDR を使用します。
---------------------------------------------------------*/
OP_01_MOVER_PD:
//	spell_register[ra] = ((s32)spell_register[rb]) + (s32)v0;/*([ダメ]簡易インデックスデクリメント無し版)*/
	// インクリメント/デクリメントは、この命令を使う方が良い気がする
	spell_register[ra] = ((s32)spell_register[rb]) + (s32)(s8)v0;/*([必要]インデックス付/デクリメント付)*/
	goto OP_NEXT;
#if 0// [未使用]
/*-------------------------------------------------------*/
// [未使用]	レジスタ間 AND演算命令。
OP_03_ANDR_PD://[未使用]
//	spell_register[ra] = (((s32)spell_register[ra]) & ((s32)spell_register[rb])) + (s32)(s8)v0;//[廃止]
//	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)spell_register[ra])) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
// レジスタ間 加算(減算)命令。
OP_04_ADDR_PD:
//	spell_register[ra] = (((s32)spell_register[ra]) + ((s32)spell_register[rb])) + (s32)(s8)v0;//[廃止]
	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	goto OP_NEXT;
#if 1
/*-------------------------------------------------------*/
// レジスタ間 減算(符号反転)命令。(A = B-A; で B が 0 なら符号反転)
OP_05_SUBR_PD://OP_05_NEGR_PD:://MCAA
	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	goto OP_NEXT;
#endif
#if 0
/*-------------------------------------------------------*/
// レジスタ間 ASR 命令。
OP_06_ASRR_PD://[未使用]
	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	goto OP_NEXT;
#endif
#if 0
/*-------------------------------------------------------*/
// レジスタ間 ASL 命令。
OP_07_ASLR_PD://[未使用]
	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
//	ロングアドレッシング
/*-------------------------------------------------------*/
//	難易度デコード命令。
	#if 0// C言語(-r40)
	VR04_NAN_IDO_DECODE = ((VR04_NAN_IDO_DECODE >> (cg_VR20_game_difficulty<<3)) & 0xff);
	#endif

OP_03_nan_ido:
	{
		// (拡張案.A) (メモリアドレッシング)の従来互換はなくなるが、パック命令として汎用化できる。
		#define USE_EXTRA_OP_NANIDO 	(0)
		if (REGISTER_ADDRESSING==v0)/*(難易度パックはレジスタにある)*/
		{	/*(レジスタアドレッシング)*/
			fetch_data32 = spell_register[rb];
			#if (1==USE_EXTRA_OP_NANIDO)
			// (拡張案.A)[ただし(メモリアドレッシング)のみ指定可]
			rb = R20_PLAYER_DATA_game_difficulty;// (レジスタアドレッシング)の場合、強制的に難易度デコード専用命令。
			#endif
		}
		else/*(難易度パックはメモリにある)*/
	//	if (MEMORY_ADDRESSING==v0)/
		{	/*(メモリアドレッシング)*/
			opcode_fetch();/*[fech]*/
		}
		#if (1==USE_EXTRA_OP_NANIDO)
		// (拡張案.A)[ただし(メモリアドレッシング)のみ指定可]
		spell_register[ra] = ((fetch_data32 >> (spell_register[rb]<<3)) & 0xff);
		#else
		spell_register[ra] = ((fetch_data32 >> (cg_VR20_game_difficulty<<3)) & 0xff);
		#endif
	}
	goto OP_NEXT;
//
/*-------------------------------------------------------*/
//	サポートアドレッシング
/*-------------------------------------------------------*/
// 命令。
	#if (0)/*(旧仕様メモ)*/
	h->math_vector.x256  = si n1024((int_angle1024))*(/*p->speed*/(16*KETM075));/*fps_factor*/		/* CCWの場合 */
	h->math_vector.y256  = co s1024((int_angle1024))*(/*p->speed*/(16*KETM075));/*fps_factor*/
	VR06	= (((int)(co s(de g1024tor ad(REG_10_ANGLE1024))*REG_11_SPEED256)));/*(fps_factor)*/
	VR07	= (((int)(si n(de g1024tor ad(REG_10_ANGLE1024))*REG_11_SPEED256)));/*(fps_factor)*/
	#endif
	#if (0)/* C言語(-r40) */
	{
		int sin_value_t256; 		// sin_value_t256 = 0;
		int cos_value_t256; 		// cos_value_t256 = 0;
	//	int256_sincos1024((deg65536to1024(VR13)), &sin_value_t256, &cos_value_t256);
		int256_sin cos65536((VR13), &sin_value_t256, &cos_value_t256);
		VR06	 = (((cos_value_t256)*(VR11))>>8);/*fps_factor*/
		VR07	 = (((sin_value_t256)*(VR11))>>8);/*fps_factor*/
	}
	#endif
// R13: 	HATSUDAN_R13_angle65536
// R11: 	HATSUDAN_R11_speed256
OP_10_SINCOS256:
	{
		/*register*/ int sin_value_t256;		// sin_value_t256 = 0;
		/*register*/ int cos_value_t256;		// cos_value_t256 = 0;
		int256_sincos65536((VR13), &sin_value_t256, &cos_value_t256);
		spell_register[ra]	 = (((cos_value_t256)*(VR11))>>8);/*fps_factor*/
		spell_register[rb]	 = (((sin_value_t256)*(VR11))>>8);/*fps_factor*/
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// ボスから自機狙い命令。(ボス から 自機 を狙う場合の角度を調べます。)
OP_11_BOSS_TO_JIKI_NERAI:
	VR06	= cg_BOSS_DATA_3a_center_x256;/*(弾源x256 ボス中心から発弾。狙い元[source])*/
	VR07	= cg_BOSS_DATA_3b_center_y256;/*(弾源y256 ボス中心から発弾。狙い元[source])*/
	/*(fall_through)*/	//goto OP_NEXT;
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
// 自機狙い命令。(src から 自機 を狙う場合の角度を調べます。)
	// 旧仕様メモ(zzz_player, dest);
	#if (0)/*(旧仕様メモ)*/
	VR06	= (dest->center.x256);			/*(狙い先[distination])*/
	VR07	= (dest->center.y256);			/*(狙い先[distination])*/
	#endif
OP_12_JIKI_NERAI:
	{
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
		VR04	= (zzz_player->center.x256);	/*(狙い先[distination])*/
		VR05	= (zzz_player->center.y256);	/*(狙い先[distination])*/
	}
	/*(fall_through)*/	//goto OP_NEXT;
/*-------------------------------------------------------*/
// 汎用狙い命令。(src から dest を狙う場合の角度を調べます。)
	#if (0)/*(旧仕様メモ)*/
	VR04	= (src->center.x256);		/*(狙い元[source])*/
	VR05	= (src->center.y256);		/*(狙い元[source])*/
	VR06	= (dest->center.x256);		/*(狙い先[distination])*/
	VR07	= (dest->center.y256);		/*(狙い先[distination])*/
	#endif
OP_13_HANYOU_NERAI:
	HATSUDAN_R13_angle65536 = (atan_65536((VR05 - VR07), (VR04 - VR06)));
	goto OP_NEXT;
/*-------------------------------------------------------*/
// ベクトル合成命令。
	#if (0)/*(到達割合を考慮して、合成する。)*/
	VR04	= ((my_menu_resource[i].x_offset[move_mode	])<<8); 	/*(合成位置[A]t256()形式)*/
//	VR05	= ((my_menu_resource[i].y_offset[move_mode	])<<8); 	/*(合成位置[A]t256()形式)*/
	VR06	= ((my_menu_resource[i].x_offset[move_mode+1])<<8); 	/*(合成位置[B]t256()形式)*/
//	VR07	= ((my_menu_resource[i].y_offset[move_mode+1])<<8); 	/*(合成位置[B]t256()形式)*/
	REG_11_TAMA1	= move_rate256;/*(合成割合t256()形式)*/
	multiprex_rate();
	#endif
	//
	#if 0/* C言語(-r40) */
	#if 1/*([X]ベクトル合成)*/
	/*(合成順序は割合[A]と割合[B]で、どちらが先でも構わない。)*/
	int x_sa256;/*(t256()形式)*/
	/*合成位置[A]*/x_sa256	= (((VR04)*(256-REG_11_GOUSEI_WARIAI256))>>8);/*(割合[A]を合成)*/
	/*合成位置[B]*/x_sa256 += (((VR06)*(	REG_11_GOUSEI_WARIAI256))>>8);/*(割合[B]を合成)*/
	VR06	= x_sa256;/*(結果[X])*/
	#endif
	#if 1/*([Y]ベクトル合成)*/
	/*(合成順序は割合[A]と割合[B]で、どちらが先でも構わない。)*/
	int y_sa256;/*(t256()形式)*/
	/*合成位置[A]*/y_sa256	= (((VR05)*(256-REG_11_GOUSEI_WARIAI256))>>8);/*(割合[A]を合成)*/
	/*合成位置[B]*/y_sa256 += (((VR07)*(	REG_11_GOUSEI_WARIAI256))>>8);/*(割合[B]を合成)*/
	VR07	= y_sa256;/*(結果[Y])*/
	#endif
	#endif

OP_14_MULTIPREX_RATE_VECTOR:
	opcode_fetch();/*[fech]*/
	{
	//-----------------
	register int value256;/*(t256()形式)*/
	#if 1/*([X]ベクトル合成)*/
	/*(合成順序は割合[A]と割合[B]で、どちらが先でも構わない。)*/
	/*合成位置[A]*/value256	= (((VR04)*(256-(s32)fetch_data32))>>8);/*(割合[A]を合成)*/
	/*合成位置[B]*/value256 += (((VR06)*(	(s32)fetch_data32))>>8);/*(割合[B]を合成)*/
	spell_register[ra]	= value256;/*(結果[X])*/
	#endif
	#if 1/*([Y]ベクトル合成)*/
	/*(合成順序は割合[A]と割合[B]で、どちらが先でも構わない。)*/
	/*合成位置[A]*/value256	= (((VR05)*(256-(s32)fetch_data32))>>8);/*(割合[A]を合成)*/
	/*合成位置[B]*/value256 += (((VR07)*(	(s32)fetch_data32))>>8);/*(割合[B]を合成)*/
	spell_register[rb]	= value256;/*(結果[Y])*/
	#endif
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// 乱数値取得命令。
OP_15_RAND_VALUE:
	spell_register[ra] = (ra_nd());
	goto OP_NEXT;
/*-------------------------------------------------------*/
// 乱数シード設定命令。
OP_16_RAND_INIT:
	goto OP_NEXT;
/*-------------------------------------------------------*/
// (div65536)割り算命令。
	#if 0// C言語(-r40)
	if (0 != VR0d)
	{
		VR0e	= (int)(65536 / VR0d);/*(div command)*/ 		/* 分割角度:  (r35-) */
	}
	#endif
OP_17_DIV65536:
	if (0 != spell_register[rb])
	{
		#if (1==USE_VFPU_INTEGER_DIVISOR)
		/*(vfpuで割り算することにより、cpuのパイプラインブレイクを防ぐ。)*/
		int a_round_65536;
		a_round_65536 = 65536;
		vfpu_div_s32(&spell_register[ra], a_round_65536, spell_register[rb]);/*(div command)*/	/* 分割角度:  (r35-) */
		#else
		spell_register[ra]	= (int)(65536 / spell_register[rb]);/*(div command)*/			/* 分割角度:  (r35-) */
		#endif
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
// 基本弾発生命令。
OP_0c_hatudan_system_regist_tama:
//OP_18_hatudan_system_regist_single:
//OP_18_hatudan_system_regist_katayori_n_way:
//OP_18_hatudan_system_regist_n_way:
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_SINGLE);
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_KATAYORI_N_WAY);
//	ha tudan_system_regist_tama(HATUDAN_SYSTEM_ADDRESSING_REGIST_N_WAY);
	hatudan_system_regist_tama(v0);
	goto OP_NEXT;
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
// 汎用効果音命令。
OP_0d_AUDIO_VOICE_PLAY:
	audio_voice_play();
	goto OP_NEXT;
/*-------------------------------------------------------*/
// 弾専用効果音命令。
OP_0e_AUDIO_AUTO_BULLET_PLAY_SET_18:
	AUDIO_18_voice_number	= v0;
	audio_auto_bullet_play();
	goto OP_NEXT;
/*-------------------------------------------------------*/
	/* (r35)カードスクリプト用命令(カードレジスタ全初期化) */
OP_0f_CLEAR_ZERO_PAGE:
	{
		int i;
		for (i=0; i<REG_NUM_0x1c_ZERO_PAGE_MAX; i++)
		{
			spell_register[i] = (0);	/* 値(0)で初期化 */
		}
	}
	goto OP_NEXT;
/*-------------------------------------------------------*/
	#if 0/*(仮)*/ // (OP0x1f != OP_NOP_debug)/*(まだ作ってないけど、この命令は必要。)*/
//	プロセス登録。
OP_06_REGIST_PROCESS:
	/*(まだ作ってない)*/
	goto OP_NEXT;
	#endif
/*-------------------------------------------------------*/
// ブランチ NOT 系命令。
/*-------------------------------------------------------*/
// ブランチ BNE 命令。(Branch Not Equal)
OP_08_BNE_RS:
	if (v0 != spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/else{goto OP_NEXT;}/*(分岐しない)*/
// ブランチ BNL 命令。(Branch FLow)
OP_09_BFL_RS:
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/else{goto OP_NEXT;}/*(分岐しない)*/
/*-------------------------------------------------------*/
// ブランチ。
/*-------------------------------------------------------*/
// ブランチ(ジャンプテーブル[補助]命令)。
OP_06_BRAR_NN:
	/*(rb は 即値。レジスタじゃないので注意[負方向にジャンプ対応(s8)(-127 <= rb <= +128)])*/
	// 策定案1. V0+VRA-VRB のアドレスにジャンプ。(必要ない?)
//	rb = (-((s32)spell_register[rb]) + ((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	// 策定案2. V0+VRA のアドレスにジャンプ。(必要ない?)
//	rb = (((s32)spell_register[ra])) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	// 策定案3. VRB の相対アドレスにジャンプ。
	rb = spell_register[rb];
	// 必ず分岐する。
	goto OP_0b_BRA_RS;/*(分岐する)*/
/*-------------------------------------------------------*/
// ブランチ 配列読み込み 命令。
OP_0a_BRA_TABLE:
	{
		u32 *data_base;
		data_base = codebase;
		{data_base += (s32)spell_register[(u32)v0];}/*(レジスタ)*/
		spell_register[ra] = (*data_base);
	}
	// 必ず分岐する。
	//goto OP_0b_BRA_RS;/*(分岐する)*/
/*-------------------------------------------------------*/
// ブランチ。
OP_0b_BRA_RS:
	#if (1==USE_CPU_EXTRA)/*([無くても出来るけど]あった方が便利)*/
	if (CPU_QUIT==rb) {goto OP_00_EXIT;}
	#endif
	//
	#if (1==USE_CPU_DEBUG_MODE)
	codebase_bak = codebase;
	#endif
	// 相対ジャンプです。(スペカCPUの場合、それ以外用途がない。下手に絶対ジャンプされても困る！)
	// +100/-100 を超えるロングジャンプは用途がないのですが、万一巨大なスペカを作って用途が発生した場合は BRA を組み合わせます。
	// あまりに巨大(普通の100倍のサイズとか)なスペカは、キャッシュからあふれてたぶんゲームにならない程遅くなると思うので、実用的ではありません。
//	{codebase += (s32)rb;}/*([ダメ。これでは負方向にジャンプ出来ない(s32)(u8)rbになっちゃう(s32)(u8)rb(0 <= rb <= 255)]即値。レジスタじゃないので注意)*/
	{codebase += (s32)(s8)rb;}/*(rb は 即値。レジスタじゃないので注意[負方向にジャンプ対応(s8)(-127 <= rb <= +128)])*/
	#if (1==USE_CPU_DEBUG_MODE)
	hook_counter--;
	if (0 > hook_counter)
	{	// "c074678"
		psp_fatal_error( (char*)
		//	"0123456789012345678901234567890123456789"	// 半角40字"最大表示文字数"
			"bug %8x %8x %8x %8x" "\\n"
			"%8x %8x %8x %8x %d" "\\n",
			fetch_data32,
			(u32)codebase,
			(u32)codebase_bak,
			(u32)(s32)rb,
			opecode_history[0],
			opecode_history[1],
			opecode_history[2],
			opecode_history[3],
			opecode_history_pointer
			 );
		// "0a0a0f16 0a0a0f21 0c074678 0a0a0f0b 3"
	}
	#endif
	#if 0/*(0==hook_counter[1回目]okっぽい)*/
	// bug
	fetch_data32: 030a0020 // MCODE(OP0x20_BEQ_RS, (0), R0a, (+3)),
	(u32)codebase: 08a040e0
	(u32)codebase_bak: 08a040d4
	(u32)(s32)rb: 3
	opecode_history[0]: 00091001 // MCODE(OP0x01_COUNTER, 16, R09, NAX),
	opecode_history[1]: 00000011 // MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),//CPU_CALL(calculate_boss_to_jiki_nerai);
	opecode_history[2]: 100a200b // MCODE(OP0x1d_ANDM_PD, 0x20, R0a, R10),/*(ショートメモリアドレッシング)*/
	opecode_history[3]: 030a0020 // MCODE(OP0x20_BEQ_RS, (0), R0a, (+3)),
	opecode_history_pointer: 0
	#endif
	goto OP_NEXT;

/*-------------------------------------------------------*/
// メモリ間 加算(減算)命令。(ToDo: この命令のショートアドレッシングは要らない)
OB_1b_CALC_ADDM_LONG_PD:// メモリロングアドレッシング。(ロング専用)
//	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)fetch_data32)) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) + ((s32)fetch_data32)) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
#if 0// [未使用]
/*-------------------------------------------------------*/
// メモリ間 減算(符号反転)命令。(A = B-A; で B が 0 なら符号反転)
OB_1d_CALC_SUBM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)fetch_data32)) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) - ((s32)fetch_data32)) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
#endif
#if 1
/*-------------------------------------------------------*/
// メモリ間 ASL 命令。
OB_1f_CALC_ASLM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)fetch_data32)) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) << ((s32)fetch_data32)) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
#endif
#if 1
/*-------------------------------------------------------*/
// メモリ間 ASR 命令。
OB_1e_CALC_ASRM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)fetch_data32)) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) >> ((s32)fetch_data32)) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
#endif
/*-------------------------------------------------------*/
// メモリ間 AND演算命令。
OB_1d_CALC_ANDM_PD:
//	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)fetch_data32)) + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (((s32)spell_register[rb]) & ((s32)fetch_data32)) + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
	goto OP_NEXT;
/*-------------------------------------------------------*/
// メモリ間 転送命令。(ZEROレジスタ使うなら OB_1b_CALC_ADDM_LONG_PD で代用できる)
OB_1c_CALC_MOVEM_PD:
//	spell_register[ra] = (s32)fetch_data32 + (s32)(s8)v0;/*(インデックス付/デクリメント付)*/
	spell_register[ra] = (s32)fetch_data32 + (s32)v0;/*(簡易インデックスデクリメント無し版)*/
//	goto OP_NEXT;
/*-------------------------------------------------------*/
OP_NEXT:// 次の命令に進む。
// 残り実行処理。
	icount--;/*[one machine code executed.][残り実行カウント数を一つ減らす]*/
	/*[icount remain, if goto loop.][残り実行カウント数があればループして実行を続ける]*/
	if (0 < icount) goto loop_start;
	/*[no icount when done.][残り実行カウント数がなければ終了]*/
/*---------------------------------------------------------
[基本命令]	スペカフレーム終了命令。
	-------------------------------------------------------
	この命令は、強制的にスペカフレームを終了します。
	-------------------------------------------------------
	残り実行カウント数があっても、強制的にゼロになります。
---------------------------------------------------------*/
OP_00_EXIT:
	;
//	icount = (0);	// [終了なので残り実行カウント数はゼロにする]
//	[スペカフレーム終了フラグ = on;]
//	goto CPU_EXIT;
}

/*---------------------------------------------------------
[註1]
ブランチ BPL 命令は、
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}
なので、例えば v0==3、spell_register[ra]==3 の場合、
	if ((3) <= (3)) 	{goto OP_0b_BRA_RS;}
となり分岐します。このぎりぎり分岐する境界線は
ブランチ BHI 命令で例えると、
	if ((2) < (3))		{goto OP_0b_BRA_RS;}
で分岐します。
v0 はこの場合破壊しても良いし、必ず整数なのだから、
ブランチ BHI 命令を v0 = v0 + (1); すれば ブランチ BPL 命令 とほぼ同じになります。
両者の違いは、v0 の有効範囲 は singned char 形式(-127 <= v0 <= 128) なので、
有効範囲の境界付近の動作は変わります。(当然ひとつずれる)
---------------------------------------------------------*/
	#if (000)/*([メモ]この辺は、要らない)*/
/*-------------------------------------------------------*/
// ブランチ BEQ 命令。
OP_20_BEQ_RS:
	if (v0 == spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/
	goto OP_NEXT;/*(分岐しない)*/
/*-------------------------------------------------------*/
#if 0
// ブランチ BHI 命令。
OP_22_BHI_RS:
	#if (0)
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/
	goto OP_NEXT;/*(分岐しない)*/
	#else
	v0++;/*(ほぼ同じ[註1])*/
	#endif
/*-------------------------------------------------------*/
// ブランチ BPL 命令。
OP_23_BPL_RS:
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/
	goto OP_NEXT;/*(分岐しない)*/
#else
// ブランチ BPL 命令。
OP_23_BPL_RS:
	#if (0)
	if (v0 <= spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/
	goto OP_NEXT;/*(分岐しない)*/
	#else
	v0--;/*(ほぼ同じ[註1])*/
	#endif
/*-------------------------------------------------------*/
// ブランチ BHI 命令。
OP_22_BHI_RS:
	if (v0 < spell_register[ra])	{goto OP_0b_BRA_RS;}/*(分岐する)*/
	goto OP_NEXT;/*(分岐しない)*/
#endif
	#endif// (000)


/*---------------------------------------------------------
	外部 I/F (インターフェイス)
	-------------------------------------------------------
	スペカCPUにはゲームの全機能が集約されているので、
	ゲームの機能を使う場合にスペカCPUを使う必要があります。
	そこでこれらは、スペカCPUに外部 からアクセスする場合の
	インターフェイスです。
	必要無い物は、将来的に順次廃止する方向で。
---------------------------------------------------------*/
#if 0
extern void cpu_bios(int call_bios_number)
{
	/*static*/ const void *jump_table_bios[(0x10)] __attribute__((aligned(16))) =/*()*/
	{
		// [BIOS]
		&&BIOS0x00, &&BIOS0x01, &&BIOS0x02, &&BIOS0x03, &&BIOS0x04, &&BIOS0x05, &&BIOS0x06, &&BIOS0x07,//
		&&BIOS0x08, &&BIOS0x09, &&BIOS0x0a, &&BIOS0x0b, &&BIOS0x0c, &&BIOS0x0d, &&BIOS0x0e, &&BIOS0x0f,//
		&&BIOS0x10, &&BIOS0x11, &&BIOS0x12, &&BIOS0x13, &&BIOS0x14, &&BIOS0x15, &&BIOS0x16, &&BIOS0x17,//
		&&BIOS0x18, &&BIOS0x19, &&BIOS0x1a, &&BIOS0x1b, &&BIOS0x1c, &&BIOS0x1d, &&BIOS0x1e, &&BIOS0x1f,//
	};
	goto *jump_table_bios[(call_bios_number)];
		BIOS0x00: BIOS0x01: BIOS0x02: BIOS0x03: BIOS0x04: BIOS0x05: BIOS0x06: BIOS0x07:
		BIOS0x08: BIOS0x09: BIOS0x0a: BIOS0x0b: BIOS0x0c: BIOS0x0d: BIOS0x0e: BIOS0x0f:
		BIOS0x10: BIOS0x11: BIOS0x12: BIOS0x13: BIOS0x14: BIOS0x15: BIOS0x16: BIOS0x17:
		BIOS0x18: BIOS0x19: BIOS0x1a: BIOS0x1b: BIOS0x1c: BIOS0x1d: BIOS0x1e: BIOS0x1f:
}
#endif
/*---------------------------------------------------------
	(r36)カードスクリプト用命令(sincos)
	-------------------------------------------------------
	使用レジスタ:
	R11 	REG_11		== HATSUDAN_R11_speed256	入力(速度、半径, t256形式)
	R13 	REG_13		== HATSUDAN_R13_angle65536	入力(角度65536, d65536形式)
	R06 	REG_02: 	出力(cos(angle) x radius, t256形式)
	R07 	REG_03: 	出力(sin(angle) x radius, t256形式)
---------------------------------------------------------*/
extern CPU_FUNC(sincos256)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x10_SINCOS256, NAX, R06, R07),
	//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	ボスから自機狙い角作成
	-------------------------------------------------------
	boss(x, y)の位置から、プレイヤー(x, y)に向けた角度を
	HATSUDAN_R13_angle65536に計算する。
---------------------------------------------------------*/
extern CPU_FUNC(calculate_boss_to_jiki_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x11_BOSS_TO_JIKI_NERAI, NAX, NAX, NAX),
	//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	自機狙い角作成
	-------------------------------------------------------
	dest(x, y)の位置から、プレイヤー(x, y)に向けた角度を
	HATSUDAN_R13_angle65536に計算する。
---------------------------------------------------------*/
extern CPU_FUNC(calculate_jiki_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x12_JIKI_NERAI, NAX, NAX, NAX),
	//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	自機(src)狙い弾(dest)の角度(中心→中心)を
	(カードcpuの内部メモリHATSUDAN_R13_angle65536に)計算。
	-------------------------------------------------------
	元(src)の中心座標から、
	先(dest)の中心座標へ狙う角度を計算し、
	一時角度変数(HATSUDAN_R13_angle65536)に計算する。
	-------------------------------------------------------
	例えば、元(src)==自機、先(dest)==敵弾なら、自機狙い弾。
	-------------------------------------------------------
	(r35)狙い角計算は全て、カードCPUを経由するように変更した。
	狙い角計算がプログラムの複数ヶ所にあると、実行速度が遅すぎて弾幕は無理。
	この変更で問題のある部分も出ているが、
	本家ではこれと似た仕様になっていると思われる。
---------------------------------------------------------*/
extern CPU_FUNC(cpu_VR_angleCCW65536_src_nerai)
{
	static const u32 codebase[2-1] =
	{
		MCODE(OP0x13_HANYOU_NERAI, NAX, NAX, NAX),
	//	NAX/*(終了)*/
	};
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r36)カードスクリプト用命令(multiprex_rate_vector)
	複合割合合成。
	-------------------------------------------------------
	使用レジスタ:
	REG_00: 	入力(x0)
	REG_01: 	入力(y0)
	REG_02: 	入力(x1)/出力(x2)
	REG_03: 	入力(y1)/出力(y2)
	REG_11: 	入力(合成割合, t256形式)
---------------------------------------------------------*/
extern CPU_FUNC(multiprex_rate_vector)
{
	static /*const*/ u32 codebase[2/*-1*/] =
	{
		MCODE(OP0x14_MULTIPREX_RATE_VECTOR, NAX, R06, R07),// メモリアドレッシング。
		NAX,/*(REG_11_GOUSEI_WARIAI256)*/					// メモリ 「入力(合成割合, t256形式)」
	//	NAX/*(終了)*/
	};
	codebase[1] = (u32)REG_11_GOUSEI_WARIAI256;// 合成割合をCPU実行メモリへ書き込む。
	cpu_exec((u32*)&codebase, (1));// CPU実行。
}

/*---------------------------------------------------------
	(r36)カードスクリプト用命令(replay_rand_init)
	リプレイ対応乱数生成。
	-------------------------------------------------------
	使用レジスタ:
	REG_00: 	入力(リプレイ対応乱数シード設定)
---------------------------------------------------------*/

/*---------------------------------------------------------
	(r36)カードスクリプト用命令(replay_rand)
	リプレイ対応乱数生成。
	-------------------------------------------------------
	使用レジスタ:
	REG_03: 	出力(リプレイ対応乱数値)
---------------------------------------------------------*/

/*---------------------------------------------------------
	(r41)カードスクリプト用命令(div65536)割り算命令。
	-------------------------------------------------------
	1周(65536)を 整数で n分割 する。
	-------------------------------------------------------
	使用レジスタ:
	R0d:	入力(割る値)
	R0e:	出力(割った結果の値)
	-------------------------------------------------------
	この命令はCPUキャッシュがフラッシュされて速度低下するので、
	基本的に[initialize section: 初期化セクション]以外では使わない事。
---------------------------------------------------------*/
#if 0/*(廃止)*/
//	/*(廃止)*/extern CPU_FUNC(div65536);/*(スクリプト用)*/
//extern CPU_FUNC(div65536)
//{
//	static const u32 codebase[2] =
//	{
//		MCODE(OP0x17_DIV65536, NAX, R0e, R0d),
//		NAX/*(終了)*/
//	};
//	cpu_exec((u32*)&codebase, (1));
//}
#endif
/*---------------------------------------------------------
	(r41)カードスクリプト用命令(nan_ido)難易度デコード命令。
	-------------------------------------------------------
	難易度をデコードする。
	-------------------------------------------------------
	使用レジスタ:
	R04_NAN_IDO_DECODE: 	入力(全難易度パック値)
	R04_NAN_IDO_DECODE: 	出力(現在の難易度、定数値)
---------------------------------------------------------*/
extern CPU_FUNC(nan_ido)
{
	#if 0//バグ
//	static /*const*/ u32 codebase[2] =
//	{
//	//	MCODE(OP0x03_NAN_IDO, NAX, R04, NAX),//バグ
//		NAX
//	};
//	codebase[1] = (u32)VR04;
//	cpu_exec((u32*)&codebase, (1));
	#endif
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x03_NAN_IDO, REGISTER_ADDRESSING, R04, R04),
	//	NAX,/*(dummy?)*/
	//	NAX/*(終了)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r41)カードスクリプト用
	汎用効果音命令。
---------------------------------------------------------*/
extern CPU_FUNC(cpu_voice_play)
{
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x0d_AUDIO_VOICE_PLAY, NAX, NAX, NAX),
	//	NAX/*(終了)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	(r41)カードスクリプト用命令
	弾専用効果音命令。
---------------------------------------------------------*/
static CPU_FUNC(cpu_auto_bullet_play_default)
{
	static /*const*/ u32 codebase[2-1] =
	{
		MCODE(OP0x0e_AUDIO_AUTO_BULLET_PLAY_SET_18, VOICE15_BOSS_KOUGEKI_01, NAX, NAX),
	//	NAX/*(終了)*/
	};
//	codebase[1] = (u32)VR04;
	cpu_exec((u32*)&codebase, (1));
}

/*---------------------------------------------------------
	スペカが C言語から スクリプトへ完全移行した場合の処理
	-------------------------------------------------------
	まだ作ってないです。
---------------------------------------------------------*/
#define LINK_DUAL_SYSTEM (0)
#if (1==LINK_DUAL_SYSTEM)

#if 0
static u32 compiled_spell[] =
{
	/*[コンパイル済みスペル]*/
}
#endif


static OBJ_CALL_FUNC(ci_run_init_section)
{
	/*[スペル初期化セクション]*/
}

static OBJ_CALL_FUNC(ci_spell_cpu)
{
	/*[スペル実行セクション]*/
}
#endif /*(LINK_DUAL_SYSTEM)*/
