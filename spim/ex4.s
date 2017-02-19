	.data
str1:   .asciiz "Enter the number: "
	.align 2
res:	.space 4
	.text
	.globl main
main:
	li $v0, 4 # code for print_str
	la $a0, str1 # argument
	syscall # executes print_str

	li $v0, 5 #read_int
	syscall

	move $t0, $v0
	add $t1,$t0,$t0
	sw $t1,res($0)

	li $v0,1  # call print_integer
	move $a0, $t1
	syscall

	li $v0, 10 # end program
	syscall 
