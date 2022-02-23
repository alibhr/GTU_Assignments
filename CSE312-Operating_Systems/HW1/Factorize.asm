# void factorize(int n){
# 	printf("factors of %d is ", n);
# 	for(int i=1 ; i<n ; ++i){
# 		if(n % i == 0) printf("%d, ", i);
# 	}
# 	printf("%d\n", n);
# }

	.data
msg0:	.asciiz "Enter a number: "
msg1:	.asciiz "factors of "
msg2:	.asciiz " is "
msg3:	.asciiz "invalid input !!\n"
comma:	.asciiz ", "
nl:	.asciiz "\n"

	.text
	.globl main
main:

	la $a0, msg0
	li $v0, 4
	syscall

	li $v0, 5
	syscall
	
	move $t0, $v0
	
	slt $t1, $zero, $t0
	beq $t1, $zero, warning

	move $a0, $t0
	jal factorize
	j exit

warning:
	la $a0, msg3
	li $v0, 4
	syscall

exit:
	li $v0, 10
	syscall

#
factorize:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)

	move $s0, $a0
	li $s1, 1

	la $a0, msg1
	li $v0, 4
	syscall

	move $a0, $s0
	li $v0, 1
	syscall

	la $a0, msg2
	li $v0, 4
	syscall

loop:
	slt $t0, $s1, $s0
	beq $t0, $zero, exit_loop

	div $s0, $s1
	mfhi $t0
	bne $t0, $zero, dont_print

	move $a0, $s1
	li $v0, 1
	syscall
	
	la $a0, comma
	li $v0, 4
	syscall
	

dont_print:
	addi $s1, $s1, 1
	j loop

exit_loop:
	move $a0, $s0
	li $v0, 1
	syscall

	la $a0, nl
	li $v0, 4
	syscall

	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra
