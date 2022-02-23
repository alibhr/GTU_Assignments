	.data
menu		:
	.asciiz "
	1 - Run ShowPrimes.asm
	2 - Run Factorize.asm
	3 - Run BubbleSort.asm
	0 - Exit\n"

primes 		:	.asciiz "ShowPrimes.asm"
factorize 	:	.asciiz "Factorize.asm"
bubble_sort	:	.asciiz "BubbleSort.asm"
ask_input	:	.asciiz "your selection: "
warning		:	.asciiz "invalid input\n"

	.text
	.globl main
main:

loop:
	la $a0, menu
	li $v0, 4
	syscall

	la $a0, ask_input
	li $v0, 4
	syscall

	li $v0, 5
	syscall

	move $s0, $v0

	beq $s0, $zero, exit

	li $t0, 1
	beq $s0, $t0, _primes

	li $t0, 2
	beq $s0, $t0, _factorize

	li $t0, 3
	beq $s0, $t0, _bubble_sort

	la $a0, warning
	li $v0, 4
	syscall

	j loop

_primes:
	la $a0, primes
	li $v0, 18
	syscall
	j _pass

_factorize:
	la $a0, factorize
	li $v0, 18
	syscall
	j _pass


_bubble_sort:
	la $a0, bubble_sort
	li $v0, 18
	syscall
	j _pass

_pass:
	j loop

exit:
	li $a0, 0
	li $v0, 17
	syscall
