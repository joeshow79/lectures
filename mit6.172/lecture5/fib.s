	.text
	.file	"fib.c"
	.globl	fib                     # -- Begin function fib
	.p2align	4, 0x90
	.type	fib,@function
fib:                                    # @fib
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	cmpq	$2, -16(%rbp)
	jge	.LBB0_2
# %bb.1:                                # %if.then
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.end
	movq	-16(%rbp), %rax
	subq	$1, %rax
	movq	%rax, %rdi
	callq	fib
	movq	-16(%rbp), %rcx
	subq	$2, %rcx
	movq	%rcx, %rdi
	movq	%rax, -24(%rbp)         # 8-byte Spill
	callq	fib
	movq	-24(%rbp), %rcx         # 8-byte Reload
	addq	%rax, %rcx
	movq	%rcx, -8(%rbp)
.LBB0_3:                                # %return
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	fib, .Lfunc_end0-fib
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.1 (https://github.com/OpenCilk/opencilk-project 8435006eea5d32f9cf895a666496b89613e2cbc1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym fib
