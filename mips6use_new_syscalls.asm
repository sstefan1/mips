# Primer koriscenja sistemskih poziva myprint_string i myread_string
# koji su definisani u datoteci mips6syscall_handler.asm.
# (c) 2016, GPL3


	.data
prompt:	.asciiz	"Please type something on the keyboard\n"
result:	.asciiz	"Here is what you typed:\n"
buffer:	.space 100

	.text
main:
	li $v0, 104	# Pozivamo myprint_string
	la $a0, prompt	# Ispisujemo string "prompt"
	syscall

	li $v0, 4	# Takodje ispisujemo na konzolu MARS-a
	la $a0, prompt
	syscall

	li $v0, 108	# Pozivamo myread_string
	la $a0, buffer
	li $a1, 100
	syscall

	li $v0, 104	# Ispisujemo string "result"
	la $a0, result	# na displej simulatora i na MARS konzolu
	syscall

	li $v0, 4
	la $a0, result
	syscall

	li $v0, 104	# Ispisujemo string koji je uneo korisnik
	la $a0, buffer	# na displej simulatora i na MARS konzolu
	syscall

	li $v0, 4
	la $a0, buffer
	syscall
			# Izlaz
	li $v0, 10
	syscall
