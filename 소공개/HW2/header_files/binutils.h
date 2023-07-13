#define bfd_fatal(a, b) fatal(a, b)

#define XNEWVEC(T, N)		((T *) xmalloc (sizeof (T) * (N)))
#define XDELETEVEC(P)       free ((void*) (P))

/* Extracted from archures.c.  */
enum bfd_architecture
{
  bfd_arch_unknown,   /* File arch not known.  */
  bfd_arch_obscure,   /* Arch known, not one of these.  */
  bfd_arch_m68k,      /* Motorola 68xxx */
#define bfd_mach_m68000 1
#define bfd_mach_m68008 2
#define bfd_mach_m68010 3
#define bfd_mach_m68020 4
#define bfd_mach_m68030 5
#define bfd_mach_m68040 6
#define bfd_mach_m68060 7
#define bfd_mach_cpu32  8
#define bfd_mach_fido   9
#define bfd_mach_mcf_isa_a_nodiv 10
#define bfd_mach_mcf_isa_a 11
#define bfd_mach_mcf_isa_a_mac 12
#define bfd_mach_mcf_isa_a_emac 13
#define bfd_mach_mcf_isa_aplus 14
#define bfd_mach_mcf_isa_aplus_mac 15
#define bfd_mach_mcf_isa_aplus_emac 16
#define bfd_mach_mcf_isa_b_nousp 17
#define bfd_mach_mcf_isa_b_nousp_mac 18
#define bfd_mach_mcf_isa_b_nousp_emac 19
#define bfd_mach_mcf_isa_b 20
#define bfd_mach_mcf_isa_b_mac 21
#define bfd_mach_mcf_isa_b_emac 22
#define bfd_mach_mcf_isa_b_float 23
#define bfd_mach_mcf_isa_b_float_mac 24
#define bfd_mach_mcf_isa_b_float_emac 25
#define bfd_mach_mcf_isa_c 26
#define bfd_mach_mcf_isa_c_mac 27
#define bfd_mach_mcf_isa_c_emac 28
#define bfd_mach_mcf_isa_c_nodiv 29
#define bfd_mach_mcf_isa_c_nodiv_mac 30
#define bfd_mach_mcf_isa_c_nodiv_emac 31
  bfd_arch_vax,       /* DEC Vax */
  bfd_arch_i960,      /* Intel 960 */
    /* The order of the following is important.
       lower number indicates a machine type that
       only accepts a subset of the instructions
       available to machines with higher numbers.
       The exception is the "ca", which is
       incompatible with all other machines except
       "core".  */

#define bfd_mach_i960_core      1
#define bfd_mach_i960_ka_sa     2
#define bfd_mach_i960_kb_sb     3
#define bfd_mach_i960_mc        4
#define bfd_mach_i960_xa        5
#define bfd_mach_i960_ca        6
#define bfd_mach_i960_jx        7
#define bfd_mach_i960_hx        8

  bfd_arch_or1k,      /* OpenRISC 1000 */
#define bfd_mach_or1k           1
#define bfd_mach_or1knd         2

  bfd_arch_sparc,     /* SPARC */
#define bfd_mach_sparc                 1
/* The difference between v8plus and v9 is that v9 is a true 64 bit env.  */
#define bfd_mach_sparc_sparclet        2
#define bfd_mach_sparc_sparclite       3
#define bfd_mach_sparc_v8plus          4
#define bfd_mach_sparc_v8plusa         5 /* with ultrasparc add'ns.  */
#define bfd_mach_sparc_sparclite_le    6
#define bfd_mach_sparc_v9              7
#define bfd_mach_sparc_v9a             8 /* with ultrasparc add'ns.  */
#define bfd_mach_sparc_v8plusb         9 /* with cheetah add'ns.  */
#define bfd_mach_sparc_v9b             10 /* with cheetah add'ns.  */
#define bfd_mach_sparc_v8plusc         11 /* with UA2005 and T1 add'ns.  */
#define bfd_mach_sparc_v9c             12 /* with UA2005 and T1 add'ns.  */
#define bfd_mach_sparc_v8plusd         13 /* with UA2007 and T3 add'ns.  */
#define bfd_mach_sparc_v9d             14 /* with UA2007 and T3 add'ns.  */
#define bfd_mach_sparc_v8pluse         15 /* with OSA2001 and T4 add'ns (no IMA).  */
#define bfd_mach_sparc_v9e             16 /* with OSA2001 and T4 add'ns (no IMA).  */
#define bfd_mach_sparc_v8plusv         17 /* with OSA2011 and T4 and IMA and FJMAU add'ns.  */
#define bfd_mach_sparc_v9v             18 /* with OSA2011 and T4 and IMA and FJMAU add'ns.  */
#define bfd_mach_sparc_v8plusm         19 /* with OSA2015 and M7 add'ns.  */
#define bfd_mach_sparc_v9m             20 /* with OSA2015 and M7 add'ns.  */
#define bfd_mach_sparc_v8plusm8        21 /* with OSA2017 and M8 add'ns.  */
#define bfd_mach_sparc_v9m8            22 /* with OSA2017 and M8 add'ns.  */
/* Nonzero if MACH has the v9 instruction set.  */
#define bfd_mach_sparc_v9_p(mach) \
  ((mach) >= bfd_mach_sparc_v8plus && (mach) <= bfd_mach_sparc_v9m8 \
   && (mach) != bfd_mach_sparc_sparclite_le)
/* Nonzero if MACH is a 64 bit sparc architecture.  */
#define bfd_mach_sparc_64bit_p(mach) \
  ((mach) >= bfd_mach_sparc_v9 \
   && (mach) != bfd_mach_sparc_v8plusb \
   && (mach) != bfd_mach_sparc_v8plusc \
   && (mach) != bfd_mach_sparc_v8plusd \
   && (mach) != bfd_mach_sparc_v8pluse \
   && (mach) != bfd_mach_sparc_v8plusv \
   && (mach) != bfd_mach_sparc_v8plusm \
   && (mach) != bfd_mach_sparc_v8plusm8)
  bfd_arch_spu,       /* PowerPC SPU */
#define bfd_mach_spu           256
  bfd_arch_mips,      /* MIPS Rxxxx */
#define bfd_mach_mips3000              3000
#define bfd_mach_mips3900              3900
#define bfd_mach_mips4000              4000
#define bfd_mach_mips4010              4010
#define bfd_mach_mips4100              4100
#define bfd_mach_mips4111              4111
#define bfd_mach_mips4120              4120
#define bfd_mach_mips4300              4300
#define bfd_mach_mips4400              4400
#define bfd_mach_mips4600              4600
#define bfd_mach_mips4650              4650
#define bfd_mach_mips5000              5000
#define bfd_mach_mips5400              5400
#define bfd_mach_mips5500              5500
#define bfd_mach_mips5900              5900
#define bfd_mach_mips6000              6000
#define bfd_mach_mips7000              7000
#define bfd_mach_mips8000              8000
#define bfd_mach_mips9000              9000
#define bfd_mach_mips10000             10000
#define bfd_mach_mips12000             12000
#define bfd_mach_mips14000             14000
#define bfd_mach_mips16000             16000
#define bfd_mach_mips16                16
#define bfd_mach_mips5                 5
#define bfd_mach_mips_loongson_2e      3001
#define bfd_mach_mips_loongson_2f      3002
#define bfd_mach_mips_loongson_3a      3003
#define bfd_mach_mips_sb1              12310201 /* octal 'SB', 01 */
#define bfd_mach_mips_octeon           6501
#define bfd_mach_mips_octeonp          6601
#define bfd_mach_mips_octeon2          6502
#define bfd_mach_mips_octeon3          6503
#define bfd_mach_mips_xlr              887682   /* decimal 'XLR'  */
#define bfd_mach_mips_interaptiv_mr2   736550   /* decimal 'IA2'  */
#define bfd_mach_mipsisa32             32
#define bfd_mach_mipsisa32r2           33
#define bfd_mach_mipsisa32r3           34
#define bfd_mach_mipsisa32r5           36
#define bfd_mach_mipsisa32r6           37
#define bfd_mach_mipsisa64             64
#define bfd_mach_mipsisa64r2           65
#define bfd_mach_mipsisa64r3           66
#define bfd_mach_mipsisa64r5           68
#define bfd_mach_mipsisa64r6           69
#define bfd_mach_mips_micromips        96
  bfd_arch_i386,      /* Intel 386 */
#define bfd_mach_i386_intel_syntax     (1 << 0)
#define bfd_mach_i386_i8086            (1 << 1)
#define bfd_mach_i386_i386             (1 << 2)
#define bfd_mach_x86_64                (1 << 3)
#define bfd_mach_x64_32                (1 << 4)
#define bfd_mach_i386_i386_intel_syntax (bfd_mach_i386_i386 | bfd_mach_i386_intel_syntax)
#define bfd_mach_x86_64_intel_syntax   (bfd_mach_x86_64 | bfd_mach_i386_intel_syntax)
#define bfd_mach_x64_32_intel_syntax   (bfd_mach_x64_32 | bfd_mach_i386_intel_syntax)
  bfd_arch_l1om,   /* Intel L1OM */
#define bfd_mach_l1om                  (1 << 5)
#define bfd_mach_l1om_intel_syntax     (bfd_mach_l1om | bfd_mach_i386_intel_syntax)
  bfd_arch_k1om,   /* Intel K1OM */
#define bfd_mach_k1om                  (1 << 6)
#define bfd_mach_k1om_intel_syntax     (bfd_mach_k1om | bfd_mach_i386_intel_syntax)
#define bfd_mach_i386_nacl             (1 << 7)
#define bfd_mach_i386_i386_nacl        (bfd_mach_i386_i386 | bfd_mach_i386_nacl)
#define bfd_mach_x86_64_nacl           (bfd_mach_x86_64 | bfd_mach_i386_nacl)
#define bfd_mach_x64_32_nacl           (bfd_mach_x64_32 | bfd_mach_i386_nacl)
  bfd_arch_iamcu,   /* Intel MCU */
#define bfd_mach_iamcu                 (1 << 8)
#define bfd_mach_i386_iamcu            (bfd_mach_i386_i386 | bfd_mach_iamcu)
#define bfd_mach_i386_iamcu_intel_syntax (bfd_mach_i386_iamcu | bfd_mach_i386_intel_syntax)
  bfd_arch_we32k,     /* AT&T WE32xxx */
  bfd_arch_tahoe,     /* CCI/Harris Tahoe */
  bfd_arch_i860,      /* Intel 860 */
  bfd_arch_i370,      /* IBM 360/370 Mainframes */
  bfd_arch_romp,      /* IBM ROMP PC/RT */
  bfd_arch_convex,    /* Convex */
  bfd_arch_m88k,      /* Motorola 88xxx */
  bfd_arch_m98k,      /* Motorola 98xxx */
  bfd_arch_pyramid,   /* Pyramid Technology */
  bfd_arch_h8300,     /* Renesas H8/300 (formerly Hitachi H8/300) */
#define bfd_mach_h8300    1
#define bfd_mach_h8300h   2
#define bfd_mach_h8300s   3
#define bfd_mach_h8300hn  4
#define bfd_mach_h8300sn  5
#define bfd_mach_h8300sx  6
#define bfd_mach_h8300sxn 7
  bfd_arch_pdp11,     /* DEC PDP-11 */
  bfd_arch_plugin,
  bfd_arch_powerpc,   /* PowerPC */
#define bfd_mach_ppc           32
#define bfd_mach_ppc64         64
#define bfd_mach_ppc_403       403
#define bfd_mach_ppc_403gc     4030
#define bfd_mach_ppc_405       405
#define bfd_mach_ppc_505       505
#define bfd_mach_ppc_601       601
#define bfd_mach_ppc_602       602
#define bfd_mach_ppc_603       603
#define bfd_mach_ppc_ec603e    6031
#define bfd_mach_ppc_604       604
#define bfd_mach_ppc_620       620
#define bfd_mach_ppc_630       630
#define bfd_mach_ppc_750       750
#define bfd_mach_ppc_860       860
#define bfd_mach_ppc_a35       35
#define bfd_mach_ppc_rs64ii    642
#define bfd_mach_ppc_rs64iii   643
#define bfd_mach_ppc_7400      7400
#define bfd_mach_ppc_e500      500
#define bfd_mach_ppc_e500mc    5001
#define bfd_mach_ppc_e500mc64  5005
#define bfd_mach_ppc_e5500     5006
#define bfd_mach_ppc_e6500     5007
#define bfd_mach_ppc_titan     83
#define bfd_mach_ppc_vle       84
  bfd_arch_rs6000,    /* IBM RS/6000 */
#define bfd_mach_rs6k          6000
#define bfd_mach_rs6k_rs1      6001
#define bfd_mach_rs6k_rsc      6003
#define bfd_mach_rs6k_rs2      6002
  bfd_arch_hppa,      /* HP PA RISC */
#define bfd_mach_hppa10        10
#define bfd_mach_hppa11        11
#define bfd_mach_hppa20        20
#define bfd_mach_hppa20w       25
  bfd_arch_d10v,      /* Mitsubishi D10V */
#define bfd_mach_d10v          1
#define bfd_mach_d10v_ts2      2
#define bfd_mach_d10v_ts3      3
  bfd_arch_d30v,      /* Mitsubishi D30V */
  bfd_arch_dlx,       /* DLX */
  bfd_arch_m68hc11,   /* Motorola 68HC11 */
  bfd_arch_m68hc12,   /* Motorola 68HC12 */
#define bfd_mach_m6812_default 0
#define bfd_mach_m6812         1
#define bfd_mach_m6812s        2
  bfd_arch_m9s12x,   /* Freescale S12X */
  bfd_arch_m9s12xg,  /* Freescale XGATE */
  bfd_arch_z8k,       /* Zilog Z8000 */
#define bfd_mach_z8001         1
#define bfd_mach_z8002         2
  bfd_arch_h8500,     /* Renesas H8/500 (formerly Hitachi H8/500) */
  bfd_arch_sh,        /* Renesas / SuperH SH (formerly Hitachi SH) */
#define bfd_mach_sh            1
#define bfd_mach_sh2        0x20
#define bfd_mach_sh_dsp     0x2d
#define bfd_mach_sh2a       0x2a
#define bfd_mach_sh2a_nofpu 0x2b
#define bfd_mach_sh2a_nofpu_or_sh4_nommu_nofpu 0x2a1
#define bfd_mach_sh2a_nofpu_or_sh3_nommu 0x2a2
#define bfd_mach_sh2a_or_sh4  0x2a3
#define bfd_mach_sh2a_or_sh3e 0x2a4
#define bfd_mach_sh2e       0x2e
#define bfd_mach_sh3        0x30
#define bfd_mach_sh3_nommu  0x31
#define bfd_mach_sh3_dsp    0x3d
#define bfd_mach_sh3e       0x3e
#define bfd_mach_sh4        0x40
#define bfd_mach_sh4_nofpu  0x41
#define bfd_mach_sh4_nommu_nofpu  0x42
#define bfd_mach_sh4a       0x4a
#define bfd_mach_sh4a_nofpu 0x4b
#define bfd_mach_sh4al_dsp  0x4d
#define bfd_mach_sh5        0x50
  bfd_arch_alpha,     /* Dec Alpha */
#define bfd_mach_alpha_ev4  0x10
#define bfd_mach_alpha_ev5  0x20
#define bfd_mach_alpha_ev6  0x30
  bfd_arch_arm,       /* Advanced Risc Machines ARM.  */
#define bfd_mach_arm_unknown   0
#define bfd_mach_arm_2         1
#define bfd_mach_arm_2a        2
#define bfd_mach_arm_3         3
#define bfd_mach_arm_3M        4
#define bfd_mach_arm_4         5
#define bfd_mach_arm_4T        6
#define bfd_mach_arm_5         7
#define bfd_mach_arm_5T        8
#define bfd_mach_arm_5TE       9
#define bfd_mach_arm_XScale    10
#define bfd_mach_arm_ep9312    11
#define bfd_mach_arm_iWMMXt    12
#define bfd_mach_arm_iWMMXt2   13
  bfd_arch_nds32,     /* Andes NDS32 */
#define bfd_mach_n1            1
#define bfd_mach_n1h           2
#define bfd_mach_n1h_v2        3
#define bfd_mach_n1h_v3        4
#define bfd_mach_n1h_v3m       5
  bfd_arch_ns32k,     /* National Semiconductors ns32000 */
  bfd_arch_w65,       /* WDC 65816 */
  bfd_arch_tic30,     /* Texas Instruments TMS320C30 */
  bfd_arch_tic4x,     /* Texas Instruments TMS320C3X/4X */
#define bfd_mach_tic3x         30
#define bfd_mach_tic4x         40
  bfd_arch_tic54x,    /* Texas Instruments TMS320C54X */
  bfd_arch_tic6x,     /* Texas Instruments TMS320C6X */
  bfd_arch_tic80,     /* TI TMS320c80 (MVP) */
  bfd_arch_v850,      /* NEC V850 */
  bfd_arch_v850_rh850,/* NEC V850 (using RH850 ABI) */
#define bfd_mach_v850          1
#define bfd_mach_v850e         'E'
#define bfd_mach_v850e1        '1'
#define bfd_mach_v850e2        0x4532
#define bfd_mach_v850e2v3      0x45325633
#define bfd_mach_v850e3v5      0x45335635 /* ('E'|'3'|'V'|'5') */
  bfd_arch_arc,       /* ARC Cores */
#define bfd_mach_arc_a4        0
#define bfd_mach_arc_a5        1
#define bfd_mach_arc_arc600    2
#define bfd_mach_arc_arc601    4
#define bfd_mach_arc_arc700    3
#define bfd_mach_arc_arcv2     5
 bfd_arch_m32c,     /* Renesas M16C/M32C.  */
#define bfd_mach_m16c        0x75
#define bfd_mach_m32c        0x78
  bfd_arch_m32r,      /* Renesas M32R (formerly Mitsubishi M32R/D) */
#define bfd_mach_m32r          1 /* For backwards compatibility.  */
#define bfd_mach_m32rx         'x'
#define bfd_mach_m32r2         '2'
  bfd_arch_mn10200,   /* Matsushita MN10200 */
  bfd_arch_mn10300,   /* Matsushita MN10300 */
#define bfd_mach_mn10300               300
#define bfd_mach_am33          330
#define bfd_mach_am33_2        332
  bfd_arch_fr30,
#define bfd_mach_fr30          0x46523330
  bfd_arch_frv,
#define bfd_mach_frv           1
#define bfd_mach_frvsimple     2
#define bfd_mach_fr300         300
#define bfd_mach_fr400         400
#define bfd_mach_fr450         450
#define bfd_mach_frvtomcat     499     /* fr500 prototype */
#define bfd_mach_fr500         500
#define bfd_mach_fr550         550
  bfd_arch_moxie,       /* The moxie processor */
#define bfd_mach_moxie         1
  bfd_arch_ft32,       /* The ft32 processor */
#define bfd_mach_ft32          1
#define bfd_mach_ft32b         2
  bfd_arch_mcore,
  bfd_arch_mep,
#define bfd_mach_mep           1
#define bfd_mach_mep_h1        0x6831
#define bfd_mach_mep_c5        0x6335
  bfd_arch_metag,
#define bfd_mach_metag         1
  bfd_arch_ia64,      /* HP/Intel ia64 */
#define bfd_mach_ia64_elf64    64
#define bfd_mach_ia64_elf32    32
  bfd_arch_ip2k,      /* Ubicom IP2K microcontrollers. */
#define bfd_mach_ip2022        1
#define bfd_mach_ip2022ext     2
 bfd_arch_iq2000,     /* Vitesse IQ2000.  */
#define bfd_mach_iq2000        1
#define bfd_mach_iq10          2
  bfd_arch_epiphany,   /* Adapteva EPIPHANY */
#define bfd_mach_epiphany16    1
#define bfd_mach_epiphany32    2
  bfd_arch_mt,
#define bfd_mach_ms1           1
#define bfd_mach_mrisc2        2
#define bfd_mach_ms2           3
  bfd_arch_pj,
  bfd_arch_avr,       /* Atmel AVR microcontrollers.  */
#define bfd_mach_avr1          1
#define bfd_mach_avr2          2
#define bfd_mach_avr25         25
#define bfd_mach_avr3          3
#define bfd_mach_avr31         31
#define bfd_mach_avr35         35
#define bfd_mach_avr4          4
#define bfd_mach_avr5          5
#define bfd_mach_avr51         51
#define bfd_mach_avr6          6
#define bfd_mach_avrtiny   100
#define bfd_mach_avrxmega1 101
#define bfd_mach_avrxmega2 102
#define bfd_mach_avrxmega3 103
#define bfd_mach_avrxmega4 104
#define bfd_mach_avrxmega5 105
#define bfd_mach_avrxmega6 106
#define bfd_mach_avrxmega7 107
  bfd_arch_bfin,        /* ADI Blackfin */
#define bfd_mach_bfin          1
  bfd_arch_cr16,       /* National Semiconductor CompactRISC (ie CR16). */
#define bfd_mach_cr16          1
  bfd_arch_cr16c,       /* National Semiconductor CompactRISC. */
#define bfd_mach_cr16c         1
  bfd_arch_crx,       /*  National Semiconductor CRX.  */
#define bfd_mach_crx           1
  bfd_arch_cris,      /* Axis CRIS */
#define bfd_mach_cris_v0_v10   255
#define bfd_mach_cris_v32      32
#define bfd_mach_cris_v10_v32  1032
  bfd_arch_riscv,
#define bfd_mach_riscv32       132
#define bfd_mach_riscv64       164
  bfd_arch_rl78,
#define bfd_mach_rl78  0x75
  bfd_arch_rx,        /* Renesas RX.  */
#define bfd_mach_rx            0x75
  bfd_arch_s390,      /* IBM s390 */
#define bfd_mach_s390_31       31
#define bfd_mach_s390_64       64
  bfd_arch_score,     /* Sunplus score */
#define bfd_mach_score3         3
#define bfd_mach_score7         7
  bfd_arch_mmix,      /* Donald Knuth's educational processor.  */
  bfd_arch_xstormy16,
#define bfd_mach_xstormy16     1
  bfd_arch_msp430,    /* Texas Instruments MSP430 architecture.  */
#define bfd_mach_msp11          11
#define bfd_mach_msp110         110
#define bfd_mach_msp12          12
#define bfd_mach_msp13          13
#define bfd_mach_msp14          14
#define bfd_mach_msp15          15
#define bfd_mach_msp16          16
#define bfd_mach_msp20          20
#define bfd_mach_msp21          21
#define bfd_mach_msp22          22
#define bfd_mach_msp23          23
#define bfd_mach_msp24          24
#define bfd_mach_msp26          26
#define bfd_mach_msp31          31
#define bfd_mach_msp32          32
#define bfd_mach_msp33          33
#define bfd_mach_msp41          41
#define bfd_mach_msp42          42
#define bfd_mach_msp43          43
#define bfd_mach_msp44          44
#define bfd_mach_msp430x        45
#define bfd_mach_msp46          46
#define bfd_mach_msp47          47
#define bfd_mach_msp54          54
  bfd_arch_xc16x,     /* Infineon's XC16X Series.               */
#define bfd_mach_xc16x         1
#define bfd_mach_xc16xl        2
#define bfd_mach_xc16xs        3
  bfd_arch_xgate,   /* Freescale XGATE */
#define bfd_mach_xgate         1
  bfd_arch_xtensa,    /* Tensilica's Xtensa cores.  */
#define bfd_mach_xtensa        1
  bfd_arch_z80,
#define bfd_mach_z80strict      1 /* No undocumented opcodes.  */
#define bfd_mach_z80            3 /* With ixl, ixh, iyl, and iyh.  */
#define bfd_mach_z80full        7 /* All undocumented instructions.  */
#define bfd_mach_r800           11 /* R800: successor with multiplication.  */
  bfd_arch_lm32,      /* Lattice Mico32 */
#define bfd_mach_lm32      1
  bfd_arch_microblaze,/* Xilinx MicroBlaze. */
  bfd_arch_tilepro,   /* Tilera TILEPro */
  bfd_arch_tilegx, /* Tilera TILE-Gx */
#define bfd_mach_tilepro   1
#define bfd_mach_tilegx    1
#define bfd_mach_tilegx32  2
  bfd_arch_aarch64,   /* AArch64  */
#define bfd_mach_aarch64 0
#define bfd_mach_aarch64_ilp32 32
  bfd_arch_nios2,      /* Nios II */
#define bfd_mach_nios2         0
#define bfd_mach_nios2r1       1
#define bfd_mach_nios2r2       2
  bfd_arch_visium,     /* Visium */
#define bfd_mach_visium        1
  bfd_arch_wasm32,     /* WebAssembly */
#define bfd_mach_wasm32        1
  bfd_arch_pru,        /* PRU */
#define bfd_mach_pru   0
  bfd_arch_last
  };

#define BFD_NO_FLAGS   0x00
#define HAS_RELOC      0x01
#define EXEC_P         0x02
#define HAS_LINENO     0x04
#define HAS_DEBUG      0x08
#define HAS_SYMS       0x10
#define HAS_LOCALS     0x20
#define DYNAMIC        0x40
#define WP_TEXT        0x80
#define D_PAGED        0x100
#define BFD_IS_RELAXABLE 0x200
#define BFD_TRADITIONAL_FORMAT 0x400
#define BFD_IN_MEMORY 0x800
#define BFD_LINKER_CREATED 0x1000
#define BFD_DETERMINISTIC_OUTPUT 0x2000
#define BFD_COMPRESS 0x4000
#define BFD_DECOMPRESS 0x8000
#define BFD_PLUGIN 0x10000
#define BFD_COMPRESS_GABI 0x20000
#define BFD_CONVERT_ELF_COMMON 0x40000
#define BFD_USE_ELF_STT_COMMON 0x80000
#define BFD_FLAGS_SAVED \
  (BFD_IN_MEMORY | BFD_COMPRESS | BFD_DECOMPRESS | BFD_LINKER_CREATED \
   | BFD_PLUGIN | BFD_COMPRESS_GABI | BFD_CONVERT_ELF_COMMON \
   | BFD_USE_ELF_STT_COMMON)
#define BFD_FLAGS_FOR_BFD_USE_MASK \
  (BFD_IN_MEMORY | BFD_COMPRESS | BFD_DECOMPRESS | BFD_LINKER_CREATED \
   | BFD_PLUGIN | BFD_TRADITIONAL_FORMAT | BFD_DETERMINISTIC_OUTPUT \
   | BFD_COMPRESS_GABI | BFD_CONVERT_ELF_COMMON | BFD_USE_ELF_STT_COMMON)

 
typedef unsigned long long BFD_HOST_U_64_BIT;
typedef long long BFD_HOST_64_BIT;

typedef BFD_HOST_U_64_BIT bfd_vma;
typedef BFD_HOST_64_BIT bfd_signed_vma;
typedef BFD_HOST_U_64_BIT bfd_size_type;
typedef BFD_HOST_U_64_BIT symvalue;
typedef int bfd_boolean;

typedef unsigned int flagword;	/* 32 bits of flags */
typedef unsigned char bfd_byte;

typedef struct bfd bfd;


typedef struct bfd_arch_info
{
  int bits_per_word;
  int bits_per_address;
  int bits_per_byte;
  enum bfd_architecture arch;
  unsigned long mach;
  const char *arch_name;
  const char *printable_name;
  unsigned int section_align_power;
  /* TRUE if this is the default machine for the architecture.
     The default arch should be the first entry for an arch so that
     all the entries for that arch can be accessed via <<next>>.  */
  bfd_boolean the_default;
  const struct bfd_arch_info * (*compatible)
    (const struct bfd_arch_info *a, const struct bfd_arch_info *b);

  bfd_boolean (*scan) (const struct bfd_arch_info *, const char *);

  /* Allocate via bfd_malloc and return a fill buffer of size COUNT.  If
     IS_BIGENDIAN is TRUE, the order of bytes is big endian.  If CODE is
     TRUE, the buffer contains code.  */
  void *(*fill) (bfd_size_type count, bfd_boolean is_bigendian,
                 bfd_boolean code);

  const struct bfd_arch_info *next;
}
bfd_arch_info_type;


typedef enum bfd_error
{
  bfd_error_no_error = 0,
  bfd_error_system_call,
  bfd_error_invalid_target,
  bfd_error_wrong_format,
  bfd_error_wrong_object_format,
  bfd_error_invalid_operation,
  bfd_error_no_memory,
  bfd_error_no_symbols,
  bfd_error_no_armap,
  bfd_error_no_more_archived_files,
  bfd_error_malformed_archive,
  bfd_error_missing_dso,
  bfd_error_file_not_recognized,
  bfd_error_file_ambiguously_recognized,
  bfd_error_no_contents,
  bfd_error_nonrepresentable_section,
  bfd_error_no_debug_section,
  bfd_error_bad_value,
  bfd_error_file_truncated,
  bfd_error_file_too_big,
  bfd_error_on_input,
  bfd_error_invalid_error_code
}
bfd_error_type;

enum bfd_direction
  {
    no_direction = 0,
    read_direction = 1,
    write_direction = 2,
    both_direction = 3
  };

enum bfd_plugin_format
  {
    bfd_plugin_unknown = 0,
    bfd_plugin_yes = 1,
    bfd_plugin_no = 2
  };

struct bfd_build_id
  {
    bfd_size_type size;
    bfd_byte data[1];
  };
