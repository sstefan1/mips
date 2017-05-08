	.data
input: .asciiz "Unesite broj: "
newline: .asciiz "\n"

	.text
main:
	la $a0, input
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	
	move $a0, $v0
	jal factorial
	
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
factorial:
	subu $sp, $sp, 24
	sw $ra, 20($sp)
	sw $a0, 0($sp)
	
	bgt $a0, 1, notbase

base:
	li $v0, 1
	b fact_return
	
notbase:
	subi $a0, $a0, 1
	jal factorial
	
	lw $a0, 0($sp)
	mulo $v0, $a0, $v0
	
fact_return:
	lw $ra, 20($sp)
	addi $sp, $sp, 24
	jr $ra
	
		
			
					