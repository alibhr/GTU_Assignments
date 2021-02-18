	.data

msg1:	.asciiz "Array Size: "

msg2:	.asciiz "Enter the all elements of the array: \n"

msg3:	.asciiz "Enter Number: "

msg4:	.asciiz "The array is as follows: "

msg5:	.asciiz "Target Number: "

msg6:	.asciiz "The sequence giving the target number: "

msg7:	.asciiz "Number of function calls: "

newline:.asciiz "\n"

space_char:
	.asciiz " "

possible:
	.asciiz "\nPossible!\n"

not_possible:
	.asciiz "Not possible!\n"

check:
	.asciiz "success\n"

recursion_counter:
	.space 4

	.text
	.globl main

# $s0 -> size of the array
# $s1 -> the array
# $s2 -> target number
main:
	
	# recursion_counter = 1
	la $t3, recursion_counter
	lw $t3, 0($t3)
	addi $t3, $t3, 1
	sw $t3, recursion_counter

	# Ask to user what size of the array will be
	# cout<<"Array Size: ";
	la $a0, msg1
	addi $v0, $zero, 4
	syscall

	# get the size of the array and set it to $s0
	# cin>>$s0
	addi $v0, $zero, 5
	syscall
	move $s0, $v0

	# sbrk (allocate heap memory)
	# $a0 number of bytes to allocate
	# $v0 contains address of allocated memory
	# $s1 will be the first address of the array
	# int arr[$s1];
	sll $t0, $s0, 2
	move $a0, $t0
	addi $v0, $zero, 9
	syscall
	add $s1, $zero, $v0

	# cout<<"Target Number: ";
	la $a0, msg5
	addi $v0, $zero, 4
	syscall

	# cin>>$vo
	addi $v0, $zero, 5
	syscall
	
	# $s2 = $v0
	move $s2, $v0

	# fill the array
	move $a0, $s1
	move $a1, $s0
	jal get_inputs

	# cout<<"The array is as follows: ";
	la $a0, msg4
	addi $v0, $zero, 4
	syscall

	# print the array
	move $a0, $s1
	move $a1, $s0
	jal print_the_array

	# cout<<"The sequence giving the target number: ";
	la $a0, msg6
	addi $v0, $zero, 4
	syscall

	# $a0 target number
	# $a1 the array
	# $a2 size of the array
	# v0 contains the result of the function
	move $a0, $s2
	move $a1, $s1
	move $a2, $s0
	jal CheckSumPossibility

	beq $v0, $zero, m_else
	la $a0, possible
	addi $v0, $zero, 4
	syscall
	j m_end_if
m_else :
	la $a0, not_possible
	addi $v0, $zero, 4
	syscall

m_end_if:
	# cout<<"Number of function calls: ";
	la $a0, msg7
	addi $v0, $zero, 4
	syscall
	
	la $t3, recursion_counter
	lw $a0, 0($t3)
	addi $v0, $zero, 1
	syscall
	
	# program will be finished
	addi $v0, $zero, 10
	syscall

# fills the array
# a0 first address of the array to be filled
# a1 size of the array
# no need to return any value
get_inputs:
	move $t0, $a0
	sll $t1, $a1, 2
	add $t2, $a0, $t1

	# Ask input from user
	# cout<<"Enter the all elements of the array: ";
	la $a0, msg2
	addi $v0, $zero, 4
	syscall

g_i_loop1:
	# while($t0 < &array[size])
	slt $t3, $t0, $t2
	beq $t3, $zero, g_i_exit

	# cout<<"Enter number: ";
	la $a0, msg3
	addi $v0, $zero, 4
	syscall

	# cin>>$vo
	addi $v0, $zero, 5
	syscall

	#*arr = $v0
	sw $v0, 0($t0)

	# ++$t0
	addi $t0, $t0, 4
	
	j g_i_loop1

g_i_exit:
	jr $ra

# pirnts the array
# a0 first address of the array to be printed
# a1 size of the array
# no need to return any value
print_the_array:
	move $t0, $a0
	sll $t1, $a1, 2
	add $t2, $a0, $t1

p_t_a_loop1:
	# while($t0 < &array[size])
	slt $t3, $t0, $t2
	beq $t3, $zero, p_t_a_exit1

	# cout<<"*arr ";
	lw $a0, 0($t0)
	addi $v0, $zero, 1
	syscall

	# cout<<" ";
	la $a0, space_char
	addi $v0, $zero, 4
	syscall

	# ++$t0
	addi $t0, $t0, 4
	j p_t_a_loop1

p_t_a_exit1:
	# cout<<"\n";
	la $a0, newline
	addi $v0, $zero, 4
	syscall

	jr $ra

# finds if a subset of array elements can sum up to the target num.
# $a0 target number
# $a1 the array
# $a2 size of the array
# $v0 returns 1 if possible, otherwise 0
CheckSumPossibility:
	# push the parameters and return address to stack
	addi $sp, $sp, -16
	sw $a0, 0($sp)
	sw $a1, 4($sp)
	sw $a2, 8($sp)
	sw $ra, 12($sp)

	# if(num == 0) return 1;
	lw $t1, 0($sp)
	beq $t1, $zero, CheckSum_return_1

	# if(num < 0 || size <= 0) return 0;
	lw $t1, 0($sp)
	slt $t0, $t1, $zero
	bne $t0, $zero, CheckSum_return_0
	lw $t1, 8($sp)
	slt $t0, $zero, $t1
	beq $t0, $zero, CheckSum_return_0

	# if(CheckSumPossibility(num-(*arr), arr+1, size-1)){ cout << *arr << " "; return 1; }
	lw $t0, 4($sp)
	lw $t2, 0($t0)
	lw $t1, 0($sp)
	sub $a0, $t1, $t2
	lw $t1, 4($sp)
	addi $a1, $t1, 4
	lw $t1, 8($sp)
	addi $a2, $t1, -1
	
	# ++recursion_counter;
	la $t3, recursion_counter
	lw $t3, 0($t3)
	addi $t3, $t3, 1
	sw $t3, recursion_counter
	
	jal CheckSumPossibility
	bne $v0, $zero, CheckSum_print_and_return_1

	# return CheckSumPossibility(num, arr+1, size-1);
	lw $a0, 0($sp)
	lw $t1, 4($sp)
	addi $a1, $t1, 4
	lw $t1, 8($sp)
	addi $a2, $t1, -1
	
	# ++recursion_counter;
	la $t3, recursion_counter
	lw $t3, 0($t3)
	addi $t3, $t3, 1
	sw $t3, recursion_counter
	
	jal CheckSumPossibility
	bne $v0, $zero, CheckSum_return_1
	j CheckSum_return_0

CheckSum_print_and_return_1:
	# I need some more stack
	addi $sp, $sp, -8
	sw $a0, 0($sp)
	sw $v0, 4($sp)

	# cout << *arr;
	lw $t0, 12($sp)
	lw $t1, 0($t0)
	move $a0, $t1
	addi $v0, $zero, 1
	syscall

	# cout<<" ";
	la $a0, space_char
	addi $v0, $zero, 4
	syscall

	lw $a0, 0($sp)
	lw $v0, 4($sp)
	addi $sp, $sp, 8

	j CheckSum_return_1

CheckSum_return_1:
	# the values are saved.
	lw $a0, 0($sp)
	lw $a1, 4($sp)
	lw $a2, 8($sp)
	lw $ra, 12($sp)
	addi $sp, $sp, 16
	
	# return 1;
	addi $v0, $zero, 1
	jr $ra

CheckSum_return_0:
	# the values are saved.
	lw $a0, 0($sp)
	lw $a1, 4($sp)
	lw $a2, 8($sp)
	lw $ra, 12($sp)
	addi $sp, $sp, 16
	
	#return 0;
	move $v0, $zero
	jr $ra
