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
	sw $t0,res($0)

	ll $t0,res($0)
        addi $t1,$t0,1
        addi $t2,$t1,1
	sc $t1,res($0)
	sc $t2,res($0)

	lw $t3,res($0)

	li $v0,1  # call print_integer
	move $a0, $t3
	syscall

	li $v0, 10 # end program
	syscall 
