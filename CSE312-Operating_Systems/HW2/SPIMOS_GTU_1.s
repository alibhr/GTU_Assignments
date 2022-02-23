# https://www.geeksforgeeks.org/merge-sort-using-multi-threading/

	.data
ask_size:	.asciiz "Array Size: "
before:		.asciiz "before sort: "
after :		.asciiz "after sort: "
nl:		.asciiz "\n"
spc:		.asciiz " "
msg:		.asciiz ".element: "
warn_msg:	.asciiz "array size should be greater than 0\n"
debug_msg:	.asciiz "HERE\n"
thread_name: .asciiz "thread_name"

# s7: int *a;
# s6: part=0;
# s5: size of the array

	.text
	.globl main
main:
	# create the main thread
	li $v0, 18
	syscall

	la $a0, ask_size
	addi $v0, $zero, 4
	syscall

	addi $v0, $zero, 5
	syscall
	move $s5, $v0
	
	slt $t1, $zero, $s5
	beq $t1, $zero, warning

	sll $t0, $s5, 2
	move $a0, $t0
	addi $v0, $zero, 9
	syscall
	add $s7, $zero, $v0

	move $a0, $s7
	move $a1, $s5
	jal get_inputs

	la $a0, before
	addi $v0, $zero, 4
	syscall

	move $a0, $s7
	move $a1, $s5
	jal print_the_array

	# create a new thread
	la $a0, thread_name
	la $a1, merge_sort_thread
	li $v0, 19
	syscall

	# thread_join_all
	li $v0, 21
	syscall

	la $a0, after
	addi $v0, $zero, 4
	syscall

	move $a0, $s7
	move $a1, $s5
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


merge_sort_thread:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $a0, 0
	addi $t0, $s5, -1
	move $a1, $t0
	jal merge_sort

	lw $ra, 0($sp)
	addi $sp, $sp, 4

	# thread_exit
	li $v0, 20
	syscall


# a0 low
# a1 high
# s0 mid
# returns void
merge_sort:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	sw $s0, 12($sp)

	# (high - low)
	sub $t0, $a1, $a0
	
	# (high - low) / 2;
	sra $t0, $t0, 1

	# mid = low + (high - low) / 2;
	add $s0, $a0, $t0

	slt $t0, $a0, $a1
	beq $t0, $zero, no_more_call
		lw $a0, 4($sp)
		move $a1, $s0
		jal merge_sort
		
		addi $a0, $s0, 1
		lw $a1, 8($sp)
		jal merge_sort
		
		lw $a0, 4($sp)
		move $a1, $s0
		lw $a2, 8($sp)
		jal merge
	no_more_call:

	lw $s0, 12($sp)
	lw $a1, 8($sp)
	lw $a0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 16
	jr $ra


# a0 low
# a1 mid
# a2 high
# s0 left array
# s1 right array
# s2 n1
# s3 n2
# s7 the array to be sorted
# returns void
merge:
	addi $sp, $sp, -32
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	sw $a2, 12($sp)
	sw $s0, 16($sp)
	sw $s1, 20($sp)
	sw $s2, 24($sp)
	sw $s3, 28($sp)

	# int* left = new int[mid - low + 1];
	lw $a1, 8($sp)
	lw $a0, 4($sp)
	sub $t0, $a1, $a0
	addi $s2, $t0, 1
	sll $t0, $s2, 2
	move $a0, $t0
	addi $v0, $zero, 9
	syscall
	add $s0, $zero, $v0

	# int* right = new int[high - mid];
	lw $a2, 12($sp)
	lw $a1, 8($sp)
	sub $s3, $a2, $a1
	sll $t0, $s3, 2
	move $a0, $t0
	addi $v0, $zero, 9
	syscall
	add $s1, $zero, $v0
	
	#  $t5: i
	#  $t6: j
	#  $t7: k
	
	# for (i = 0; i < n1; i++)
	# 	left[i] = a[i + low];
	lw $a0, 4($sp)
	li $t5, 0
for_loop_1:
	slt $t0, $t5, $s2
	beq $t0, $zero, exit_for_loop_1

	add $t0, $t5, $a0
	sll $t0, $t0, 2
	add $t1, $t0, $s7
	lw $t3, 0($t1)
	
	sll $t0, $t5, 2
	add $t2, $t0, $s0
	sw $t3, 0($t2)
	
	addi $t5, $t5, 1
	j for_loop_1
exit_for_loop_1:

	# for (i = 0; i < n2; i++)
	# 	right[i] = a[i + mid + 1];
	lw $a1, 8($sp)
	li $t5, 0
for_loop_2:
	slt $t0, $t5, $s3
	beq $t0, $zero, exit_for_loop_2

	add $t0, $t5, $a1
	addi $t0, $t0, 1
	sll $t0, $t0, 2
	add $t1, $t0, $s7
	lw $t3, 0($t1)
	
	sll $t0, $t5, 2
	add $t2, $t0, $s1
	sw $t3, 0($t2)
	
	addi $t5, $t5, 1
	j for_loop_2
exit_for_loop_2:
	
	
	# int k = low;
	# i = j = 0;
	lw $t7, 4($sp)
	li $t5, 0
	li $t6, 0

while_1:
	slt $t0, $t5, $s2
	beq $t0, $zero, exit_while_1
	
	slt, $t0, $t6, $s3
	beq $t0, $zero, exit_while_1
	
	sll $t0, $t5, 2
	add $t0, $t0, $s0
	lw $t2, 0($t0) # left[i]
	
	sll $t1, $t6, 2
	add $t1, $t1, $s1
	lw $t3, 0($t1) # right[j]
	
	slt $t0, $t3, $t2
	beq $t0, $zero, case_true
	
	# a[k] = right[j];
	sll $t0, $t7, 2
	add $t0, $t0, $s7 # a[k]
	
	sll $t1, $t6, 2
	add $t1, $t1, $s1 # right[j]
	lw $t1, 0($t1)
	
	sw $t1, 0($t0)
	
	addi $t7, $t7, 1
	addi $t6, $t6, 1
	j while_1

case_true:
	# a[k] = left[i];
	sll $t0, $t7, 2
	add $t0, $t0, $s7 # a[k]
	
	sll $t1, $t5, 2
	add $t1, $t1, $s0 # left[i]
	lw $t1, 0($t1)
	
	sw $t1, 0($t0)
	
	addi $t7, $t7, 1
	addi $t5, $t5, 1
	j while_1

exit_while_1:

while_2:
	slt $t0, $t5, $s2
	beq $t0, $zero, exit_while_2
	
	sll $t0, $t7, 2
	add $t0, $t0, $s7 # a[k]
	
	sll $t1, $t5, 2
	add $t1, $t1, $s0 # left[i]
	lw $t1, 0($t1)
	
	sw $t1, 0($t0)
	
	addi $t7, $t7, 1
	addi $t5, $t5, 1
	
	j while_2
	
exit_while_2:

while_3:
	slt $t0, $t6, $s3
	beq $t0, $zero, exit_while_3

	sll $t0, $t7, 2
	add $t0, $t0, $s7 # a[k]
	
	sll $t1, $t6, 2
	add $t1, $t1, $s1 # right[j]
	lw $t1, 0($t1)
	
	sw $t1, 0($t0)
	
	addi $t7, $t7, 1
	addi $t6, $t6, 1
	
	j while_3
exit_while_3:

	lw $s3, 28($sp)
	lw $s2, 24($sp)
	lw $s1, 20($sp)
	lw $s0, 16($sp)
	lw $a2, 12($sp)
	lw $a1, 8($sp)
	lw $a0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 32
	jr $ra
