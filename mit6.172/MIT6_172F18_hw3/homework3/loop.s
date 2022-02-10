	.text
	.file	"loop.c"
	.file	1 "/usr/include" "stdlib.h"
	.file	2 "/usr/include" "time.h"
	.file	3 "/usr/include/x86_64-linux-gnu/bits" "types.h"
	.file	4 "/usr/include/x86_64-linux-gnu/bits/types" "struct_timespec.h"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function main
.LCPI0_0:
	.quad	4472406533629990549     # double 1.0000000000000001E-9
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
.Lfunc_begin0:
	.file	5 "/workspace/src/github/joeshow79/pess/MIT6_172F18_hw3/homework3" "loop.c"
	.loc	5 50 0                  # loop.c:50:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: main:argc <- $edi
	#DEBUG_VALUE: main:argv <- $rsi
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	subq	$12328, %rsp            # imm = 0x3028
	.cfi_def_cfa_offset 12368
	.cfi_offset %rbx, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
.Ltmp0:
	#DEBUG_VALUE: main:total <- 0
	#DEBUG_VALUE: main:seed <- 0
	.loc	5 59 18 prologue_end    # loop.c:59:18
	movl	$0, 12(%rsp)
.Ltmp1:
	#DEBUG_VALUE: main:j <- 0
	.loc	5 0 18 is_stmt 0        # loop.c:0:18
	leaq	8224(%rsp), %rdi
.Ltmp2:
	xorl	%ebp, %ebp
.Ltmp3:
	.loc	5 65 14 is_stmt 1       # loop.c:65:14
	movl	$4096, %edx             # imm = 0x1000
	xorl	%esi, %esi
.Ltmp4:
	callq	memset
.Ltmp5:
	.loc	5 0 14 is_stmt 0        # loop.c:0:14
	leaq	4128(%rsp), %rdi
	.loc	5 66 14 is_stmt 1       # loop.c:66:14
	movl	$4096, %edx             # imm = 0x1000
	xorl	%esi, %esi
	callq	memset
.Ltmp6:
	.loc	5 0 14 is_stmt 0        # loop.c:0:14
	leaq	32(%rsp), %rdi
	.loc	5 67 14 is_stmt 1       # loop.c:67:14
	movl	$4096, %edx             # imm = 0x1000
	xorl	%esi, %esi
	callq	memset
.Ltmp7:
	#DEBUG_VALUE: main:j <- undef
	.loc	5 0 14 is_stmt 0        # loop.c:0:14
	leaq	16(%rsp), %rsi
.Ltmp8:
	.file	6 "/workspace/src/github/joeshow79/pess/MIT6_172F18_hw3/homework3" "././fasttime.h"
	.loc	6 72 3 is_stmt 1        # ././fasttime.h:72:3
	movl	$1, %edi
	callq	clock_gettime
.Ltmp9:
	.loc	6 77 3                  # ././fasttime.h:77:3
	movq	16(%rsp), %r15
	movq	24(%rsp), %r14
.Ltmp10:
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 0 64] $r15
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 64 64] $r14
	#DEBUG_VALUE: main:i <- 0
	.p2align	4, 0x90
.LBB0_1:                                # %for.cond8.preheader
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 64 64] $r14
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 0 64] $r15
	#DEBUG_VALUE: main:j <- 0
	#DEBUG_VALUE: main:seed <- 0
	#DEBUG_VALUE: main:total <- 0
	.loc	6 0 3 is_stmt 0         # ././fasttime.h:0:3
	movq	$-8, %rax
.Ltmp11:
	#DEBUG_VALUE: main:i <- $ebp
	#DEBUG_VALUE: main:j <- 0
	.p2align	4, 0x90
.LBB0_2:                                # %for.body10
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: main:i <- $ebp
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 64 64] $r14
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 0 64] $r15
	#DEBUG_VALUE: main:j <- 0
	#DEBUG_VALUE: main:seed <- 0
	#DEBUG_VALUE: main:total <- 0
	#DEBUG_VALUE: main:j <- undef
	.loc	5 76 32 is_stmt 1       # loop.c:76:32
	movl	4160(%rsp,%rax,4), %ecx
	movl	4168(%rsp,%rax,4), %edx
	.loc	5 76 25 is_stmt 0       # loop.c:76:25
	addl	8256(%rsp,%rax,4), %ecx
	addl	8264(%rsp,%rax,4), %edx
	.loc	5 76 18                 # loop.c:76:18
	movl	%ecx, 64(%rsp,%rax,4)
	.loc	5 76 32                 # loop.c:76:32
	movl	4176(%rsp,%rax,4), %ecx
	.loc	5 76 25                 # loop.c:76:25
	addl	8272(%rsp,%rax,4), %ecx
	.loc	5 76 18                 # loop.c:76:18
	movl	%edx, 72(%rsp,%rax,4)
	.loc	5 76 32                 # loop.c:76:32
	movl	4184(%rsp,%rax,4), %edx
	.loc	5 76 25                 # loop.c:76:25
	addl	8280(%rsp,%rax,4), %edx
	.loc	5 76 18                 # loop.c:76:18
	movl	%ecx, 80(%rsp,%rax,4)
	movl	%edx, 88(%rsp,%rax,4)
.Ltmp12:
	#DEBUG_VALUE: main:j <- [DW_OP_plus_uconst 8, DW_OP_stack_value] undef
	.loc	5 75 23 is_stmt 1       # loop.c:75:23
	addq	$8, %rax
	cmpq	$1016, %rax             # imm = 0x3F8
.Ltmp13:
	.loc	5 75 9 is_stmt 0        # loop.c:75:9
	jb	.LBB0_2
.Ltmp14:
# %bb.3:                                # %for.inc20
                                        #   in Loop: Header=BB0_1 Depth=1
	#DEBUG_VALUE: main:i <- $ebp
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 64 64] $r14
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 0 64] $r15
	#DEBUG_VALUE: main:j <- 0
	#DEBUG_VALUE: main:seed <- 0
	#DEBUG_VALUE: main:total <- 0
	.loc	5 72 25 is_stmt 1       # loop.c:72:25
	addl	$1, %ebp
.Ltmp15:
	#DEBUG_VALUE: main:i <- $ebp
	.loc	5 72 19 is_stmt 0       # loop.c:72:19
	cmpl	$100000, %ebp           # imm = 0x186A0
.Ltmp16:
	.loc	5 72 5                  # loop.c:72:5
	jne	.LBB0_1
.Ltmp17:
# %bb.4:                                # %for.end22
	#DEBUG_VALUE: main:i <- $ebp
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 64 64] $r14
	#DEBUG_VALUE: main:time1 <- [DW_OP_LLVM_fragment 0 64] $r15
	#DEBUG_VALUE: main:j <- 0
	#DEBUG_VALUE: main:seed <- 0
	#DEBUG_VALUE: main:total <- 0
	.loc	5 0 5                   # loop.c:0:5
	leaq	16(%rsp), %rsi
.Ltmp18:
	.loc	6 72 3                  # ././fasttime.h:72:3
	movl	$1, %edi
	callq	clock_gettime
.Ltmp19:
	.loc	6 77 3 is_stmt 1        # ././fasttime.h:77:3
	movq	16(%rsp), %rbp
.Ltmp20:
	movq	24(%rsp), %rbx
.Ltmp21:
	#DEBUG_VALUE: main:time2 <- [DW_OP_LLVM_fragment 0 64] $rbp
	#DEBUG_VALUE: main:time2 <- [DW_OP_LLVM_fragment 64 64] $rbx
	#DEBUG_VALUE: main:seed <- [DW_OP_plus_uconst 12, DW_OP_deref] $rsp
	.loc	6 0 3 is_stmt 0         # ././fasttime.h:0:3
	leaq	12(%rsp), %rdi
.Ltmp22:
	.loc	5 84 16 is_stmt 1       # loop.c:84:16
	callq	rand_r
.Ltmp23:
                                        # kill: def $eax killed $eax def $rax
	.loc	5 84 30 is_stmt 0       # loop.c:84:30
	leal	1023(%rax), %ecx
	testl	%eax, %eax
	cmovnsl	%eax, %ecx
	andl	$-1024, %ecx            # imm = 0xFC00
	subl	%ecx, %eax
.Ltmp24:
	.loc	6 83 21 is_stmt 1       # ././fasttime.h:83:21
	subq	%r15, %rbp
.Ltmp25:
	.loc	6 83 10 is_stmt 0       # ././fasttime.h:83:10
	vcvtsi2sd	%rbp, %xmm0, %xmm0
.Ltmp26:
	.loc	5 84 14 is_stmt 1       # loop.c:84:14
	cltq
.Ltmp27:
	.loc	6 83 56                 # ././fasttime.h:83:56
	subq	%r14, %rbx
.Ltmp28:
	.loc	6 83 43 is_stmt 0       # ././fasttime.h:83:43
	vcvtsi2sd	%rbx, %xmm1, %xmm1
.Ltmp29:
	.loc	5 84 14 is_stmt 1       # loop.c:84:14
	movl	32(%rsp,%rax,4), %ebx
.Ltmp30:
	#DEBUG_VALUE: tdiff:end <- [DW_OP_LLVM_fragment 0 64] undef
	#DEBUG_VALUE: tdiff:end <- [DW_OP_LLVM_fragment 64 64] undef
	#DEBUG_VALUE: tdiff:start <- [DW_OP_LLVM_fragment 64 64] undef
	#DEBUG_VALUE: tdiff:start <- [DW_OP_LLVM_fragment 0 64] undef
	#DEBUG_VALUE: main:total <- $ebx
	.loc	6 83 42                 # ././fasttime.h:83:42
	vmulsd	.LCPI0_0(%rip), %xmm1, %xmm1
	.loc	6 83 36 is_stmt 0       # ././fasttime.h:83:36
	vaddsd	%xmm0, %xmm1, %xmm0
.Ltmp31:
	#DEBUG_VALUE: main:elapsedf <- $xmm0
	.loc	5 89 5 is_stmt 1        # loop.c:89:5
	movl	$.L.str, %edi
	movl	$.L.str.1, %ecx
	movl	$.L.str.2, %r8d
	movl	$1024, %esi             # imm = 0x400
	movl	$100000, %edx           # imm = 0x186A0
	movb	$1, %al
	callq	printf
.Ltmp32:
	.loc	5 93 5                  # loop.c:93:5
	movl	%ebx, %eax
	addq	$12328, %rsp            # imm = 0x3028
	.cfi_def_cfa_offset 40
	popq	%rbx
.Ltmp33:
	.cfi_def_cfa_offset 32
	popq	%r14
.Ltmp34:
	.cfi_def_cfa_offset 24
	popq	%r15
.Ltmp35:
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Ltmp36:
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Elapsed execution time: %f sec; N: %d, I: %d, __OP__: %s, __TYPE__: %s\n"
	.size	.L.str, 72

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"+"
	.size	.L.str.1, 2

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"uint32_t"
	.size	.L.str.2, 9

	.file	7 "/usr/include/x86_64-linux-gnu/bits" "stdint-uintn.h"
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"clang version 10.0.1 (https://github.com/OpenCilk/opencilk-project 8435006eea5d32f9cf895a666496b89613e2cbc1)" # string offset=0
.Linfo_string1:
	.asciz	"loop.c"                # string offset=109
.Linfo_string2:
	.asciz	"/workspace/src/github/joeshow79/pess/MIT6_172F18_hw3/homework3" # string offset=116
.Linfo_string3:
	.asciz	"rand_r"                # string offset=179
.Linfo_string4:
	.asciz	"int"                   # string offset=186
.Linfo_string5:
	.asciz	"unsigned int"          # string offset=190
.Linfo_string6:
	.asciz	"clock_gettime"         # string offset=203
.Linfo_string7:
	.asciz	"tv_sec"                # string offset=217
.Linfo_string8:
	.asciz	"long int"              # string offset=224
.Linfo_string9:
	.asciz	"__time_t"              # string offset=233
.Linfo_string10:
	.asciz	"tv_nsec"               # string offset=242
.Linfo_string11:
	.asciz	"__syscall_slong_t"     # string offset=250
.Linfo_string12:
	.asciz	"timespec"              # string offset=268
.Linfo_string13:
	.asciz	"gettime"               # string offset=277
.Linfo_string14:
	.asciz	"fasttime_t"            # string offset=285
.Linfo_string15:
	.asciz	"s"                     # string offset=296
.Linfo_string16:
	.asciz	"tdiff"                 # string offset=298
.Linfo_string17:
	.asciz	"double"                # string offset=304
.Linfo_string18:
	.asciz	"start"                 # string offset=311
.Linfo_string19:
	.asciz	"end"                   # string offset=317
.Linfo_string20:
	.asciz	"main"                  # string offset=321
.Linfo_string21:
	.asciz	"A"                     # string offset=326
.Linfo_string22:
	.asciz	"__uint32_t"            # string offset=328
.Linfo_string23:
	.asciz	"uint32_t"              # string offset=339
.Linfo_string24:
	.asciz	"__ARRAY_SIZE_TYPE__"   # string offset=348
.Linfo_string25:
	.asciz	"B"                     # string offset=368
.Linfo_string26:
	.asciz	"C"                     # string offset=370
.Linfo_string27:
	.asciz	"argc"                  # string offset=372
.Linfo_string28:
	.asciz	"argv"                  # string offset=377
.Linfo_string29:
	.asciz	"char"                  # string offset=382
.Linfo_string30:
	.asciz	"total"                 # string offset=387
.Linfo_string31:
	.asciz	"seed"                  # string offset=393
.Linfo_string32:
	.asciz	"j"                     # string offset=398
.Linfo_string33:
	.asciz	"time1"                 # string offset=400
.Linfo_string34:
	.asciz	"i"                     # string offset=406
.Linfo_string35:
	.asciz	"time2"                 # string offset=408
.Linfo_string36:
	.asciz	"elapsedf"              # string offset=414
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
	.quad	.Lfunc_begin0-.Lfunc_begin0
	.quad	.Ltmp2-.Lfunc_begin0
	.short	1                       # Loc expr size
	.byte	85                      # super-register DW_OP_reg5
	.quad	0
	.quad	0
.Ldebug_loc1:
	.quad	.Lfunc_begin0-.Lfunc_begin0
	.quad	.Ltmp4-.Lfunc_begin0
	.short	1                       # Loc expr size
	.byte	84                      # DW_OP_reg4
	.quad	0
	.quad	0
.Ldebug_loc2:
	.quad	.Ltmp0-.Lfunc_begin0
	.quad	.Ltmp30-.Lfunc_begin0
	.short	2                       # Loc expr size
	.byte	48                      # DW_OP_lit0
	.byte	159                     # DW_OP_stack_value
	.quad	.Ltmp30-.Lfunc_begin0
	.quad	.Ltmp33-.Lfunc_begin0
	.short	1                       # Loc expr size
	.byte	83                      # super-register DW_OP_reg3
	.quad	0
	.quad	0
.Ldebug_loc3:
	.quad	.Ltmp0-.Lfunc_begin0
	.quad	.Ltmp21-.Lfunc_begin0
	.short	2                       # Loc expr size
	.byte	48                      # DW_OP_lit0
	.byte	159                     # DW_OP_stack_value
	.quad	.Ltmp21-.Lfunc_begin0
	.quad	.Lfunc_end0-.Lfunc_begin0
	.short	2                       # Loc expr size
	.byte	119                     # DW_OP_breg7
	.byte	12                      # 12
	.quad	0
	.quad	0
.Ldebug_loc4:
	.quad	.Ltmp1-.Lfunc_begin0
	.quad	.Ltmp7-.Lfunc_begin0
	.short	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.quad	.Ltmp10-.Lfunc_begin0
	.quad	.Ltmp11-.Lfunc_begin0
	.short	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.quad	.Ltmp14-.Lfunc_begin0
	.quad	.Lfunc_end0-.Lfunc_begin0
	.short	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.quad	0
	.quad	0
.Ldebug_loc5:
	.quad	.Ltmp10-.Lfunc_begin0
	.quad	.Ltmp34-.Lfunc_begin0
	.short	6                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.byte	94                      # DW_OP_reg14
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.quad	.Ltmp34-.Lfunc_begin0
	.quad	.Ltmp35-.Lfunc_begin0
	.short	3                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.quad	0
	.quad	0
.Ldebug_loc6:
	.quad	.Ltmp11-.Lfunc_begin0
	.quad	.Ltmp20-.Lfunc_begin0
	.short	1                       # Loc expr size
	.byte	86                      # super-register DW_OP_reg6
	.quad	0
	.quad	0
.Ldebug_loc7:
	.quad	.Ltmp21-.Lfunc_begin0
	.quad	.Ltmp25-.Lfunc_begin0
	.short	6                       # Loc expr size
	.byte	86                      # DW_OP_reg6
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.byte	83                      # DW_OP_reg3
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.quad	.Ltmp25-.Lfunc_begin0
	.quad	.Ltmp28-.Lfunc_begin0
	.short	5                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.byte	83                      # DW_OP_reg3
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.quad	0
	.quad	0
.Ldebug_loc8:
	.quad	.Ltmp31-.Lfunc_begin0
	.quad	.Ltmp32-.Lfunc_begin0
	.short	1                       # Loc expr size
	.byte	97                      # DW_OP_reg17
	.quad	0
	.quad	0
	.section	.debug_abbrev,"",@progbits
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	16                      # DW_AT_stmt_list
	.byte	23                      # DW_FORM_sec_offset
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	32                      # DW_AT_inline
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	64                      # DW_AT_frame_base
	.byte	24                      # DW_FORM_exprloc
	.ascii	"\227B"                 # DW_AT_GNU_all_call_sites
	.byte	25                      # DW_FORM_flag_present
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	14                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	15                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	24                      # DW_FORM_exprloc
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	16                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	17                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	87                      # DW_AT_call_column
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	18                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	24                      # DW_FORM_exprloc
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	19                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	85                      # DW_AT_ranges
	.byte	23                      # DW_FORM_sec_offset
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	87                      # DW_AT_call_column
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	20                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	21                      # Abbreviation Code
	.ascii	"\211\202\001"          # DW_TAG_GNU_call_site
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	22                      # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	23                      # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	55                      # DW_AT_count
	.byte	5                       # DW_FORM_data2
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	24                      # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.long	.Ldebug_info_end0-.Ldebug_info_start0 # Length of Unit
.Ldebug_info_start0:
	.short	4                       # DWARF version number
	.long	.debug_abbrev           # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x26c DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string1          # DW_AT_name
	.long	.Lline_table_start0     # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0-.Lfunc_begin0 # DW_AT_high_pc
	.byte	2                       # Abbrev [2] 0x2a:0x12 DW_TAG_subprogram
	.long	.Linfo_string3          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.short	459                     # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	60                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x36:0x5 DW_TAG_formal_parameter
	.long	67                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x3c:0x7 DW_TAG_base_type
	.long	.Linfo_string4          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x43:0x5 DW_TAG_pointer_type
	.long	72                      # DW_AT_type
	.byte	4                       # Abbrev [4] 0x48:0x7 DW_TAG_base_type
	.long	.Linfo_string5          # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0x4f:0x16 DW_TAG_subprogram
	.long	.Linfo_string6          # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	219                     # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	60                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x5a:0x5 DW_TAG_formal_parameter
	.long	60                      # DW_AT_type
	.byte	3                       # Abbrev [3] 0x5f:0x5 DW_TAG_formal_parameter
	.long	101                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x65:0x5 DW_TAG_pointer_type
	.long	106                     # DW_AT_type
	.byte	7                       # Abbrev [7] 0x6a:0x21 DW_TAG_structure_type
	.long	.Linfo_string12         # DW_AT_name
	.byte	16                      # DW_AT_byte_size
	.byte	4                       # DW_AT_decl_file
	.byte	9                       # DW_AT_decl_line
	.byte	8                       # Abbrev [8] 0x72:0xc DW_TAG_member
	.long	.Linfo_string7          # DW_AT_name
	.long	139                     # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	11                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	8                       # Abbrev [8] 0x7e:0xc DW_TAG_member
	.long	.Linfo_string10         # DW_AT_name
	.long	157                     # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	12                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x8b:0xb DW_TAG_typedef
	.long	150                     # DW_AT_type
	.long	.Linfo_string9          # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	148                     # DW_AT_decl_line
	.byte	4                       # Abbrev [4] 0x96:0x7 DW_TAG_base_type
	.long	.Linfo_string8          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x9d:0xb DW_TAG_typedef
	.long	150                     # DW_AT_type
	.long	.Linfo_string11         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	184                     # DW_AT_decl_line
	.byte	10                      # Abbrev [10] 0xa8:0x18 DW_TAG_subprogram
	.long	.Linfo_string13         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	192                     # DW_AT_type
	.byte	1                       # DW_AT_inline
	.byte	11                      # Abbrev [11] 0xb4:0xb DW_TAG_variable
	.long	.Linfo_string15         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	70                      # DW_AT_decl_line
	.long	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0xc0:0xb DW_TAG_typedef
	.long	106                     # DW_AT_type
	.long	.Linfo_string14         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.byte	10                      # Abbrev [10] 0xcb:0x23 DW_TAG_subprogram
	.long	.Linfo_string16         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	82                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	238                     # DW_AT_type
	.byte	1                       # DW_AT_inline
	.byte	12                      # Abbrev [12] 0xd7:0xb DW_TAG_formal_parameter
	.long	.Linfo_string18         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	82                      # DW_AT_decl_line
	.long	192                     # DW_AT_type
	.byte	12                      # Abbrev [12] 0xe2:0xb DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	82                      # DW_AT_decl_line
	.long	192                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0xee:0x7 DW_TAG_base_type
	.long	.Linfo_string17         # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	13                      # Abbrev [13] 0xf5:0x146 DW_TAG_subprogram
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.long	.Lfunc_end0-.Lfunc_begin0 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_GNU_all_call_sites
	.long	.Linfo_string20         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	60                      # DW_AT_type
                                        # DW_AT_external
	.byte	14                      # Abbrev [14] 0x10e:0xf DW_TAG_formal_parameter
	.long	.Ldebug_loc0            # DW_AT_location
	.long	.Linfo_string27         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	60                      # DW_AT_type
	.byte	14                      # Abbrev [14] 0x11d:0xf DW_TAG_formal_parameter
	.long	.Ldebug_loc1            # DW_AT_location
	.long	.Linfo_string28         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.long	613                     # DW_AT_type
	.byte	15                      # Abbrev [15] 0x12c:0x10 DW_TAG_variable
	.byte	4                       # DW_AT_location
	.byte	145
	.asciz	"\240\300"
	.long	.Linfo_string21         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.long	571                     # DW_AT_type
	.byte	15                      # Abbrev [15] 0x13c:0xf DW_TAG_variable
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\240 "
	.long	.Linfo_string25         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.long	571                     # DW_AT_type
	.byte	15                      # Abbrev [15] 0x14b:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	32
	.long	.Linfo_string26         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.long	571                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x159:0xf DW_TAG_variable
	.long	.Ldebug_loc2            # DW_AT_location
	.long	.Linfo_string30         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	584                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x168:0xf DW_TAG_variable
	.long	.Ldebug_loc3            # DW_AT_location
	.long	.Linfo_string31         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	59                      # DW_AT_decl_line
	.long	72                      # DW_AT_type
	.byte	16                      # Abbrev [16] 0x177:0xf DW_TAG_variable
	.long	.Ldebug_loc4            # DW_AT_location
	.long	.Linfo_string32         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.long	60                      # DW_AT_type
	.byte	16                      # Abbrev [16] 0x186:0xf DW_TAG_variable
	.long	.Ldebug_loc5            # DW_AT_location
	.long	.Linfo_string33         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	70                      # DW_AT_decl_line
	.long	192                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x195:0xf DW_TAG_variable
	.long	.Ldebug_loc6            # DW_AT_location
	.long	.Linfo_string34         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.long	60                      # DW_AT_type
	.byte	16                      # Abbrev [16] 0x1a4:0xf DW_TAG_variable
	.long	.Ldebug_loc7            # DW_AT_location
	.long	.Linfo_string35         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	81                      # DW_AT_decl_line
	.long	192                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x1b3:0xf DW_TAG_variable
	.long	.Ldebug_loc8            # DW_AT_location
	.long	.Linfo_string36         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.long	238                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x1c2:0x1d DW_TAG_inlined_subroutine
	.long	168                     # DW_AT_abstract_origin
	.quad	.Ltmp8                  # DW_AT_low_pc
	.long	.Ltmp10-.Ltmp8          # DW_AT_high_pc
	.byte	5                       # DW_AT_call_file
	.byte	70                      # DW_AT_call_line
	.byte	24                      # DW_AT_call_column
	.byte	18                      # Abbrev [18] 0x1d6:0x8 DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.long	180                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	17                      # Abbrev [17] 0x1df:0x1d DW_TAG_inlined_subroutine
	.long	168                     # DW_AT_abstract_origin
	.quad	.Ltmp18                 # DW_AT_low_pc
	.long	.Ltmp22-.Ltmp18         # DW_AT_high_pc
	.byte	5                       # DW_AT_call_file
	.byte	81                      # DW_AT_call_line
	.byte	24                      # DW_AT_call_column
	.byte	18                      # Abbrev [18] 0x1f3:0x8 DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	16
	.long	180                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x1fc:0x17 DW_TAG_inlined_subroutine
	.long	203                     # DW_AT_abstract_origin
	.long	.Ldebug_ranges0         # DW_AT_ranges
	.byte	5                       # DW_AT_call_file
	.byte	86                      # DW_AT_call_line
	.byte	23                      # DW_AT_call_column
	.byte	20                      # Abbrev [20] 0x208:0x5 DW_TAG_formal_parameter
	.long	215                     # DW_AT_abstract_origin
	.byte	20                      # Abbrev [20] 0x20d:0x5 DW_TAG_formal_parameter
	.long	226                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x213:0xd DW_TAG_GNU_call_site
	.long	79                      # DW_AT_abstract_origin
	.quad	.Ltmp9                  # DW_AT_low_pc
	.byte	21                      # Abbrev [21] 0x220:0xd DW_TAG_GNU_call_site
	.long	79                      # DW_AT_abstract_origin
	.quad	.Ltmp19                 # DW_AT_low_pc
	.byte	21                      # Abbrev [21] 0x22d:0xd DW_TAG_GNU_call_site
	.long	42                      # DW_AT_abstract_origin
	.quad	.Ltmp23                 # DW_AT_low_pc
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0x23b:0xd DW_TAG_array_type
	.long	584                     # DW_AT_type
	.byte	23                      # Abbrev [23] 0x240:0x7 DW_TAG_subrange_type
	.long	606                     # DW_AT_type
	.short	1024                    # DW_AT_count
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x248:0xb DW_TAG_typedef
	.long	595                     # DW_AT_type
	.long	.Linfo_string23         # DW_AT_name
	.byte	7                       # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x253:0xb DW_TAG_typedef
	.long	72                      # DW_AT_type
	.long	.Linfo_string22         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.byte	24                      # Abbrev [24] 0x25e:0x7 DW_TAG_base_type
	.long	.Linfo_string24         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	7                       # DW_AT_encoding
	.byte	5                       # Abbrev [5] 0x265:0x5 DW_TAG_pointer_type
	.long	618                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x26a:0x5 DW_TAG_pointer_type
	.long	623                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x26f:0x7 DW_TAG_base_type
	.long	.Linfo_string29         # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	0                       # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.Ltmp24-.Lfunc_begin0
	.quad	.Ltmp26-.Lfunc_begin0
	.quad	.Ltmp27-.Lfunc_begin0
	.quad	.Ltmp29-.Lfunc_begin0
	.quad	.Ltmp30-.Lfunc_begin0
	.quad	.Ltmp31-.Lfunc_begin0
	.quad	0
	.quad	0
	.ident	"clang version 10.0.1 (https://github.com/OpenCilk/opencilk-project 8435006eea5d32f9cf895a666496b89613e2cbc1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.section	.debug_line,"",@progbits
.Lline_table_start0:
