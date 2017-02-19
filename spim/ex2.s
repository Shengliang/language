	.data
str: .asciiz "Hello World"
	.text
	.globl main
main:
	li $v0, 4 # code for print_str
	la $a0, str # argument
	syscall # executes print_str

	li $v0, 10 # end program
	syscall 
