	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	__Z14clock_volatilev
	.p2align	4, 0x90
__Z14clock_volatilev:                   ## @_Z14clock_volatilev
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## volatile int *
	## InlineAsm End
	jmp	LBB0_2
	.p2align	4, 0x90
LBB0_1:                                 ##   in Loop: Header=BB0_2 Depth=1
	movl	$1, _reg(%rip)
	movl	$0, _reg(%rip)
LBB0_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB0_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z9clocksyncv
	.p2align	4, 0x90
__Z9clocksyncv:                         ## @_Z9clocksyncv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## __sync_synchronize
	## InlineAsm End
	jmp	LBB1_2
	.p2align	4, 0x90
LBB1_1:                                 ##   in Loop: Header=BB1_2 Depth=1
	movl	$1, _reg(%rip)
	mfence
	movl	$0, _reg(%rip)
	mfence
LBB1_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB1_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock1v
	.p2align	4, 0x90
__Z6clock1v:                            ## @_Z6clock1v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_release
	## InlineAsm End
	jmp	LBB2_2
	.p2align	4, 0x90
LBB2_1:                                 ##   in Loop: Header=BB2_2 Depth=1
	movl	$1, _clk(%rip)
	mfence
	movl	$0, _clk(%rip)
	mfence
LBB2_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB2_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock2v
	.p2align	4, 0x90
__Z6clock2v:                            ## @_Z6clock2v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_release
	## InlineAsm End
	jmp	LBB3_2
	.p2align	4, 0x90
LBB3_1:                                 ##   in Loop: Header=BB3_2 Depth=1
	movl	$1, _clk(%rip)
	##MEMBARRIER
	movl	$0, _clk(%rip)
	##MEMBARRIER
LBB3_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB3_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock3v
	.p2align	4, 0x90
__Z6clock3v:                            ## @_Z6clock3v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_relaxed
	## InlineAsm End
	jmp	LBB4_2
	.p2align	4, 0x90
LBB4_1:                                 ##   in Loop: Header=BB4_2 Depth=1
	movl	$1, _clk(%rip)
	movl	$0, _clk(%rip)
LBB4_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB4_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock4v
	.p2align	4, 0x90
__Z6clock4v:                            ## @_Z6clock4v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp15:
	.cfi_def_cfa_offset 16
Ltmp16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp17:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_release
	## InlineAsm End
	jmp	LBB5_2
	.p2align	4, 0x90
LBB5_1:                                 ##   in Loop: Header=BB5_2 Depth=1
	movl	$1, _clk(%rip)
	movl	$0, _clk(%rip)
LBB5_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB5_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock5v
	.p2align	4, 0x90
__Z6clock5v:                            ## @_Z6clock5v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp18:
	.cfi_def_cfa_offset 16
Ltmp19:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp20:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_acq_rel
	## InlineAsm End
	jmp	LBB6_2
	.p2align	4, 0x90
LBB6_1:                                 ##   in Loop: Header=BB6_2 Depth=1
	movl	$1, _clk(%rip)
	##MEMBARRIER
	movl	$0, _clk(%rip)
	##MEMBARRIER
LBB6_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB6_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock6v
	.p2align	4, 0x90
__Z6clock6v:                            ## @_Z6clock6v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp21:
	.cfi_def_cfa_offset 16
Ltmp22:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp23:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_seq_cst
	## InlineAsm End
	jmp	LBB7_2
	.p2align	4, 0x90
LBB7_1:                                 ##   in Loop: Header=BB7_2 Depth=1
	movl	$1, %eax
	xchgl	%eax, _clk(%rip)
	mfence
	xorl	%eax, %eax
	xchgl	%eax, _clk(%rip)
	mfence
LBB7_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB7_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock7v
	.p2align	4, 0x90
__Z6clock7v:                            ## @_Z6clock7v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp24:
	.cfi_def_cfa_offset 16
Ltmp25:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp26:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## memory_order_seq_cst
	## InlineAsm End
	jmp	LBB8_2
	.p2align	4, 0x90
LBB8_1:                                 ##   in Loop: Header=BB8_2 Depth=1
	movl	$1, %eax
	xchgl	%eax, _clk(%rip)
	mfence
	xorl	%eax, %eax
	xchgl	%eax, _clk(%rip)
	mfence
LBB8_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB8_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z6clock0v
	.p2align	4, 0x90
__Z6clock0v:                            ## @_Z6clock0v
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp27:
	.cfi_def_cfa_offset 16
Ltmp28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp29:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## atomic default
	## InlineAsm End
	jmp	LBB9_2
	.p2align	4, 0x90
LBB9_1:                                 ##   in Loop: Header=BB9_2 Depth=1
	movl	$1, %eax
	xchgl	%eax, _clk(%rip)
	xorl	%eax, %eax
	xchgl	%eax, _clk(%rip)
LBB9_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_run_flag(%rip), %eax
	testl	%eax, %eax
	jne	LBB9_1
## BB#3:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z4funcv
	.p2align	4, 0x90
__Z4funcv:                              ## @_Z4funcv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp30:
	.cfi_def_cfa_offset 16
Ltmp31:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp32:
	.cfi_def_cfa_register %rbp
	## InlineAsm Start
	## atomic_signal_fence(std::memory_order_seq_cst)
	## InlineAsm End
	##MEMBARRIER
	mfence
	## InlineAsm Start
	## std::atomic_signal_fence(std::memory_order_acquire)
	## InlineAsm End
	##MEMBARRIER
	##MEMBARRIER
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_clk                    ## @clk
.zerofill __DATA,__common,_clk,4,2
	.section	__DATA,__data
	.globl	_run_flag               ## @run_flag
	.p2align	2
_run_flag:
	.long	1                       ## 0x1

	.globl	_reg                    ## @reg
.zerofill __DATA,__common,_reg,4,2

.subsections_via_symbols
