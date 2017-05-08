	.text
	
main:
	li $a0, 5
	li $a1, 3
	jal pow
	
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
pow:
	subi $sp, $sp, 24
	sw $ra, 20($sp)
	
	bgt $a1, 0, notbase

base:
	li $v0, 1
	b return
	
notbase:
	subi $a1, $a1, 1
	jal pow
	
	mulo $v0, $a0, $v0
return:
	lw $ra, 20($sp)
	addi $sp, $sp, 24
	jr $ra