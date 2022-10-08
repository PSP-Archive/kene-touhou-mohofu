
# /*
# ---------------------------------------------------------
#   �����͕핗 �` Toho Imitation Style.
#   http://code.google.com/p/kene-touhou-mohofu/
# ---------------------------------------------------------
# ����� PSPSDK �� �T���v��
# /pspsdk/psp/sdk/samples/gu/spharm/disablefpu.S
# �ɓ����Ă������C���������̂ł��B
# ---------------------------------------------------------
# ����
# ---------------------------------------------------------
# main();�����ɏ����Ȃ��ƍI�������Ȃ��݂����B
# -------------------------------------------------------
# */

# /*
# FPU��O�̖�����
# -------------------------------------------------------
#   �����FPU��O�𖳌��ɂ��܂��B(FPU��O�𖳌��ɂ��č��������܂�)
#   This disables FPU exceptions.
#
#   ���̊֐���($31==$ra��M��̂�)main()�����ɏ����Ȃ��ƃ_����������Ȃ��B
# */

#include <as_reg_compat.h>

.text
.align  4

.set    push 
.set    noreorder 
.set    nomacro
# /* extern void disable_FPU_exeptions_in_main(void); */
.globl  disable_FPU_exeptions_in_main
.ent    disable_FPU_exeptions_in_main
disable_FPU_exeptions_in_main: 
    cfc1    $2, $ra 
    lui     $8, 0x80        # R8 &= 0x80;

    and     $8, $2, $8      # Mask off all bits except for 23 of FCR 
    ctc1    $8, $ra 

    jr      $ra             # return ();
    nop

.end    disable_FPU_exeptions_in_main
.set    pop
.set    macro