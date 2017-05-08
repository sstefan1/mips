#################################
# Ispis koda izuzetka
#
	.kdata
saveat:	.word 0		# Sacuvana vrednost $at registra
poruka: .asciiz "Exception code: "

s1: .word 0
s2: .word 0

	.ktext	0x80000180
handler:
	.set noat
	move $k1, $at
	sw $k1, saveat	# Cuvamo $at
	.set at

	sw $v0, s1
	sw $a0, s2
	
	li $v0, 4
	la $a0, poruka
	syscall
	
	li $v0, 1
	mfc0 $k0, $13
	srl $a0, $k0, 2
	andi $a0, $a0, 0xf
	syscall
	
	mfc0 $k0 $14            # Get EPC register value
	addiu $k0 $k0 4         # Skip faulting instruction by skipping
	                        # forward by one instruction
                          # (Need to handle delayed branch case here)
	mtc0 $k0 $14            # Reset the EPC register
	
	
	lw $v0, s1               # Restore $v0 and $a0
	lw $a0, s2
	
    .set noat
    lw $k1, saveat          # Obnova $at registra
    move $at, $k1           
    .set at

    mtc0 $0, $13            # Brisemo Cause registar
    mfc0 $k0, $12           # 
    ori  $k0, 0x1           # Omogucujemo prekide 
    mtc0 $k0, $12           # u status registru
    eret                    # povratak korisnickom programu na instrukciju sa adesom iz EPC



