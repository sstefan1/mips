#############################################################
# Ispis koda izuzetka
#
	.kdata
saveat:	.word 0		# Sacuvana vrednost $at registra
poruka: .asciiz "Exception code: "

s1: .word 0
s2: .word 0

	.ktext	0x80000180
handler:
#############################################################
# Save $at, $v0, $a0
#
	.set noat
	move $k1, $at
	sw $k1, saveat			# Save $at
	.set at

	sw $v0, s1				# Save $v0
	sw $a0, s2				# Save $a0

#############################################################
# Print exception code
#	
	li $v0, 4				# syscall (print_str)
	la $a0, poruka
	syscall
	
	li $v0, 1				# syscall (print_int)
	mfc0 $k0, $13			# Get cause register ($13)
	srl $a0, $k0, 2			# Extract ExcCode
	andi $a0, $a0, 0xf
	syscall
	
#############################################################
# Return from (non-interrupt) exception. Skip offending
# instruction at EPC to avoid infinite loop.
#	
	mfc0 $k0 $14            # Get EPC register value
	addiu $k0 $k0 4         # Skip faulting instruction by skipping
	                        # forward by one instruction
                          	# (Need to handle delayed branch case here)
	mtc0 $k0 $14            # Reset the EPC register
	
#############################################################
# Restore registers and reset procesor state
#
	lw $v0, s1               # Restore $v0 and $a0
	lw $a0, s2
	
    .set noat
    lw $k1, saveat          # Restore $at register
    move $at, $k1           
    .set at

    mtc0 $0, $13            # Clear Cause register
    mfc0 $k0, $12           # 
    ori  $k0, 0x1           # Enable interuptions 
    mtc0 $k0, $12           # in status register
    
#############################################################
# Return from exception on MIPS32
#
	eret



