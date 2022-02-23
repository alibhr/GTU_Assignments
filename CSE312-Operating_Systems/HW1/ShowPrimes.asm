# void show_primes(int f, int l){
# 	for(int i=f ; i<=l ; ++i){
# 		printf("%d ", i);
# 		if(is_prime(i)){
# 			printf("prime");
# 		}
# 		printf("\n");
# 	}
# }

# int is_prime(int n){
# 	if(n <= 1) return 0;
# 	for(int i=2 ; i<n ; ++i){
# 		if (n%i == 0) return 0;
# 	}
# 	return 1;
# }

	.data
new_line:.asciiz "\n"
primeMsg:.asciiz " prime"

	.text
	.globl main
main:
	li $a0, 0
	li $a1, 1000
	jal show_primes

	li $v0, 10
	syscall

#
#
show_primes:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)

	move $s0, $a0
	move $s1, $a1

loop1:
	slt $t0, $s1, $s0
	bne $t0, $zero, exit_loop1

	move $a0, $s0
	li $v0, 1
	syscall

	move $a0, $s0
	jal is_prime

	beq $v0, $zero, not_prime

	la $a0, primeMsg
	li $v0, 4
	syscall

not_prime:
	la $a0, new_line
	li $v0, 4
	syscall

	addi $s0, $s0, 1
	j loop1

exit_loop1:
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra

#
is_prime:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)

	move $s0, $a0

	li $t1, 1
	slt $t0, $t1, $s0
	beq $t0, $zero, return_0

	li $s1, 2

loop2:
	slt $t0, $s1, $s0
	beq $t0, $zero, exit_loop2

	div $s0, $s1
	mfhi $t1

	beq $t1, $zero, return_0

	addi $s1, $s1, 1
	j loop2

exit_loop2:
	li $v0, 1
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra

return_0:
	li $v0, 0
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra
