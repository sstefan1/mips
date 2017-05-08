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
	jal fib
	
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
fib:
	subi $sp, $sp, 28
	sw $ra, 20($sp)
	
	beqz $a0, casezero
	bgt $a0, 1, notbase

base:
	li $v0, 1
	b return
casezero:
	li $v0, 0
	b return

notbase:
	sw $a0, 0($sp)
	subi $a0, $a0, 1
	jal fib 	#fib(n-1)
	
	sw $v0, 24($sp)
	lw $a0, 0($sp)
	
	subi $a0, $a0, 2
	jal fib
	
	lw $t0, 24($sp)
	add $v0, $v0, $t0
return:
	lw $ra, 20($sp)
	addi $sp, $sp, 28
	jr $ra	