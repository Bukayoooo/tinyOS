#ifndef _ASM_OFFSETS_H
#define _ASM_OFFSETS_H

/* trap_regs结构体中每个字段的偏移量 */

#define PT_SIZE 264     /* sizeof(struct sbi_trap_regs) */
#define PT_MEPC 0       /* offset(struct sbi_trap_regs, mepc) */
#define PT_RA 8       /* offset(struct sbi_trap_regs, ra) */
#define PT_SP 16       /* offset(struct sbi_trap_regs, sp) */
#define PT_GP 24       /* offset(struct sbi_trap_regs, gp) */
#define PT_TP 32       /* offset(struct sbi_trap_regs, tp) */
#define PT_T0 40       /* offset(struct sbi_trap_regs, t0) */
#define PT_T1 48       /* offset(struct sbi_trap_regs, t1) */
#define PT_T2 56       /* offset(struct sbi_trap_regs, t2) */
#define PT_T3 64       /* offset(struct sbi_trap_regs, t3) */
#define PT_T4 72       /* offset(struct sbi_trap_regs, t4) */
#define PT_T5 80       /* offset(struct sbi_trap_regs, t5) */
#define PT_T6 88       /* offset(struct sbi_trap_regs, t6) */
#define PT_S0 96       /* offset(struct sbi_trap_regs, s0) */
#define PT_S1 104       /* offset(struct sbi_trap_regs, s1) */
#define PT_S2 112       /* offset(struct sbi_trap_regs, s2) */
#define PT_S3 120       /* offset(struct sbi_trap_regs, s3) */
#define PT_S4 128       /* offset(struct sbi_trap_regs, s4) */
#define PT_S5 136       /* offset(struct sbi_trap_regs, s5) */
#define PT_S6 144       /* offset(struct sbi_trap_regs, s6) */
#define PT_S7 152       /* offset(struct sbi_trap_regs, s7) */
#define PT_S8 160       /* offset(struct sbi_trap_regs, s8) */
#define PT_S9 168       /* offset(struct sbi_trap_regs, s9) */
#define PT_S10 176       /* offset(struct sbi_trap_regs, s10) */
#define PT_S11 184       /* offset(struct sbi_trap_regs, s11) */
#define PT_A0 192       /* offset(struct sbi_trap_regs, a0) */
#define PT_A1 200       /* offset(struct sbi_trap_regs, a1) */
#define PT_A2 208       /* offset(struct sbi_trap_regs, a2) */
#define PT_A3 216       /* offset(struct sbi_trap_regs, a3) */
#define PT_A4 224       /* offset(struct sbi_trap_regs, a4) */
#define PT_A5 232       /* offset(struct sbi_trap_regs, a5) */
#define PT_A6 240       /* offset(struct sbi_trap_regs, a6) */
#define PT_A7 248       /* offset(struct sbi_trap_regs, a7) */
#define PT_MSTATUS 256       /* offset(struct sbi_trap_regs, mstatus) */


#endif /* _ASM_OFFSETS_H */