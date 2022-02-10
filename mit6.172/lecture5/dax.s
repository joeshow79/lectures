	.text
	.file	"dax.c"
	.globl	dax                     # -- Begin function dax
	.p2align	4, 0x90
	.type	dax,@function
dax:                                    # @dax
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movq	$0, -40(%rbp)
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	-40(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jge	.LBB0_4
# %bb.2:                                # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-16(%rbp), %xmm0        # xmm0 = mem[0],zero
	movq	-24(%rbp), %rax
	movq	-40(%rbp), %rcx
	mulsd	(%rax,%rcx,8), %xmm0
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rcx
	movsd	%xmm0, (%rax,%rcx,8)
# %bb.3:                                # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	-40(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -40(%rbp)
	jmp	.LBB0_1
.LBB0_4:                                # %for.end
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	dax, .Lfunc_end0-dax
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.1 (https://github.com/OpenCilk/opencilk-project 8435006eea5d32f9cf895a666496b89613e2cbc1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
