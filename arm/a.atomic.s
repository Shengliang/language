	.arch armv8-a
	.file	"a.c"
	.text
	.align	2
	.p2align 3,,7
	.global	atomic_add_and_fetch
	.type	atomic_add_and_fetch, %function
atomic_add_and_fetch:
#APP
// 29 "a.c" 1
	@ atomic_add_and_fetch begin
// 0 "" 2
// 36 "a.c" 1
	@ atomic code
1:	ldrex	x2, [x1]
	add	x2, x2, x0
	strex	x3, x2, [x1]
	teq	x3, #0
	bne	1b
// 0 "" 2
// 46 "a.c" 1
	@ atomic_add_and_fetch end
// 0 "" 2
#NO_APP
	mov	w0, w2
	ret
	.size	atomic_add_and_fetch, .-atomic_add_and_fetch
	.align	2
	.p2align 3,,7
	.global	atomic_fetch_and_add
	.type	atomic_fetch_and_add, %function
atomic_fetch_and_add:
#APP
// 55 "a.c" 1
	@ atomic_fetch_and_add begin
// 0 "" 2
// 61 "a.c" 1
	@ atomic code
1:	ldrex	x2, [x1]
	add	x3, x2, x0
	strex	x3, x3, [x1]
	teq	x3, #0
	bne	1b
// 0 "" 2
// 71 "a.c" 1
	@ atomic_fetch_and_add end
// 0 "" 2
#NO_APP
	mov	w0, w2
	ret
	.size	atomic_fetch_and_add, .-atomic_fetch_and_add
	.section	.text.startup,"ax",@progbits
	.align	2
	.p2align 3,,7
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	add	x0, x29, 32
	str	wzr, [x0, -8]!
#APP
// 55 "a.c" 1
	@ atomic_fetch_and_add begin
// 0 "" 2
// 61 "a.c" 1
	@ atomic code
1:	ldrex	x2, [x0]
	add	x1, x2, 7
	strex	x1, x1, [x0]
	teq	x1, #0
	bne	1b
// 0 "" 2
// 71 "a.c" 1
	@ atomic_fetch_and_add end
// 0 "" 2
#NO_APP
	str	wzr, [x29, 24]
#APP
// 29 "a.c" 1
	@ atomic_add_and_fetch begin
// 0 "" 2
// 36 "a.c" 1
	@ atomic code
1:	ldrex	x3, [x0]
	add	x3, x3, 7
	strex	x1, x3, [x0]
	teq	x1, #0
	bne	1b
// 0 "" 2
// 46 "a.c" 1
	@ atomic_add_and_fetch end
// 0 "" 2
#NO_APP
	mov	w1, 7
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	main, .-main
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"x:%u y:%u z:%u\n"
	.ident	"GCC: (Linaro GCC 6.2-2016.11) 6.2.1 20161016"
	.section	.note.GNU-stack,"",@progbits
