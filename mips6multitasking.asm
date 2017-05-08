# Primer prekljucenja na MIPS CPU.
# (c) 2016 GPL3
# Imamo dva programa, koja u beskonacnoj petlji, ispisuju vrednost brojaca, a zatim ga uvecaju
# Program main1 broji od 0 i uvecava sa korakom od 1
# Program main2 broji od 10000 i uvecava sa korakom od 2
#
# Svaki otkucaj casovnika ce izazvati prekljucenje procesora izmedju dva programa
#
# Program main vrsi sistemski poziv 100, koji pokrece ova dva programa i 
# nikada se ne vraca iz tog sistemskog poziva.

	.data
m1msg:	 .asciiz "In main1, the counter is "
m2msg:	 .asciiz "In main2, the counter is "
newline: .asciiz "\n"
never:	 .asciiz "We should never get here\n"

	.text
	.globl main
main:	la $a0, main1		# Prosledjujemo pocetne adrese oba programa, kao parametre sistemskog poziva 100
	la $a1, main2		
	li $v0, 100		
	syscall			

	la $a0, never		# syscall 100 nikada se ne zavrsava,
	li $v0 4		  	# tako da se ova pooruka nece nikaa ispisati
	syscall
	li $v0, 10			# Takodje nikada necemo izaci iz programa
	syscall


main1:	li $t0, 0		# Brojac pocinje od 0 
m1loop:	la $a0, m1msg		# Ispis poruke
	li $v0, 4
	syscall
	move $a0, $t0		# Ispis brojaca 
	li $v0, 1
	syscall
	la $a0, newline		# Ispis nove linije
	li $v0, 4
	syscall
	addi $t0, $t0, 1	# Uvecanje brojaca za 1
	b m1loop		# Ponovo na pocetak


main2:	li $t0, 10000		# Brojac pocinje od 10000
m2loop:	la $a0, m2msg		# Ispis poruke
	li $v0, 4
	syscall
	move $a0, $t0		# Ispis brojaca
	li $v0, 1
	syscall
	la $a0, newline		# Ispis nove linije
	li $v0, 4
	syscall
	addi $t0, $t0, 2	# Uvecanje brojaca za 2
	b m2loop		# Ponovo na pocetak
