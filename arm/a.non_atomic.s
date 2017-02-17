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
#NO_APP
	ldr	w2, [x1]
	add	w0, w2, w0
	str	w0, [x1]
#APP
// 46 "a.c" 1
	@ atomic_add_and_fetch end
// 0 "" 2
#NO_APP
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
#NO_APP
	ldr	w3, [x1]
	add	w2, w3, w0
	str	w2, [x1]
#APP
// 71 "a.c" 1
	@ atomic_fetch_and_add end
// 0 "" 2
#NO_APP
	mov	w0, w3
	ret
	.size	atomic_fetch_and_add, .-atomic_fetch_and_add
	.section	.text.startup,"ax",@progbits
	.align	2
	.p2align 3,,7
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
#APP
// 55 "a.c" 1
	@ atomic_fetch_and_add begin
// 0 "" 2
// 71 "a.c" 1
	@ atomic_fetch_and_add end
// 0 "" 2
// 29 "a.c" 1
	@ atomic_add_and_fetch begin
// 0 "" 2
// 46 "a.c" 1
	@ atomic_add_and_fetch end
// 0 "" 2
#NO_APP
	mov	w3, 7
	mov	w2, 0
	mov	w1, w3
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	main, .-main
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"x:%u y:%u z:%u\n"
	.ident	"GCC: (Linaro GCC 6.2-2016.11) 6.2.1 20161016"
	.section	.note.GNU-stack,"",@progbits
