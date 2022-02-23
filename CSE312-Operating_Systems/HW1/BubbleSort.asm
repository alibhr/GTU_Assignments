# void bubble_sort(int arr[], int n){
# 	for(int i=0 ; i<n ; ++i){
# 		for (int j=1 ; j < n-i ; ++j){
# 			if(arr[j-1] > arr[j]){
# 				int temp = arr[j-1];
# 				arr[j-1] = arr[j];
# 				arr[j] = temp;
# 			}
# 		}
# 	}
# }

	.data
ask_size:	.asciiz "Array Size: "
before:		.asciiz "before sort: "
after :		.asciiz "after sort: "
nl:		.asciiz "\n"
spc:		.asciiz " "
msg:		.asciiz ".element: "
warn_msg:	.asciiz "array size should be greater than 0\n"

	.text
	.globl main
main:

	la $a0, ask_size
	addi $v0, $zero, 4
	syscall

	addi $v0, $zero, 5
	syscall
	move $s0, $v0
	
	slt $t1, $zero, $s0
	beq $t1, $zero, warning

	sll $t0, $s0, 2
	move $a0, $t0
	addi $v0, $zero, 9
	syscall
	add $s1, $zero, $v0

	move $a0, $s1
	move $a1, $s0
	jal get_inputs

	la $a0, before
	addi $v0, $zero, 4
	syscall

	move $a0, $s1
	move $a1, $s0
	jal print_the_array

	move $a0, $s1
	move $a1, $s0
	jal bubble_sort

	la $a0, after
	addi $v0, $zero, 4
	syscall

	move $a0, $s1
	move $a1, $s0
	jal print_the_array


	j exit
warning:
	la $a0, warn_msg
	li $v0, 4
	syscall

exit:
	li $v0, 10
	syscall


# fills the array
# a0 first address of the array to be filled
# a1 size of the array
get_inputs:
	move $t0, $a0
	sll $t1, $a1, 2
	add $t2, $a0, $t1
	li $t4, 1

g_i_loop1:
	slt $t3, $t0, $t2
	beq $t3, $zero, g_i_exit

	move $a0, $t4
	addi $v0, $zero, 1
	syscall
	
	la $a0, msg
	addi $v0, $zero, 4
	syscall

	addi $v0, $zero, 5
	syscall

	sw $v0, 0($t0)

	addi $t0, $t0, 4
	
	addi $t4, $t4, 1
	j g_i_loop1

g_i_exit:
	jr $ra


# prints the array
# a0 first address of the array to be printed
# a1 size of the array
print_the_array:
	move $t0, $a0
	sll $t1, $a1, 2
	add $t2, $a0, $t1

p_t_a_loop1:
	slt $t3, $t0, $t2
	beq $t3, $zero, p_t_a_exit1

	lw $a0, 0($t0)
	addi $v0, $zero, 1
	syscall

	la $a0, spc
	addi $v0, $zero, 4
	syscall

	addi $t0, $t0, 4
	j p_t_a_loop1

p_t_a_exit1:
	la $a0, nl
	addi $v0, $zero, 4
	syscall

	jr $ra

#
#
bubble_sort:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)

	move $s0, $a0
	move $s1, $a1

	li $t0, 0
outer_for:
	slt $t2, $t0, $s1
	beq $t2, $zero, exit_outer

	li $t1, 1
inner_for:
	sub $t4, $s1, $t0
	slt $t3, $t1, $t4
	beq $t3, $zero, exit_inner

	sll $t5, $t1 2
	addi $t5, $t5, -4
	add $t6, $s0, $t5


	lw $t2, 0($t6)
	lw $t3, 4($t6)
	slt $t7, $t3, $t2
	beq $t7, $zero, no_swap
	
	#swap
	lw $t8, 4($t6)
	
	lw $t2, 0($t6)
	sw $t2, 4($t6)
	
	sw $t8, 0($t6)

no_swap:
	addi $t1, $t1, 1
	j inner_for
exit_inner:
	addi $t0, $t0, 1
	j outer_for
exit_outer:
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra
