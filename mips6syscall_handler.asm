# Primer obradjivaca novih sistemskih poziva myprint_string i myread_string
# koji koriste Keyboard and Display Simulator uredjaj.
# (c) 2016, GPL3
#
# Funkcije myprint_string i myread_string se pozivaju kao i ostali sistemski pozivi u MARS-u
#

	.kdata
saveat:	.word 0		# Sacuvana vrednost $at registra

# Ovo je ulazna tacka za obradjivac sistemskih poziva.
# Umemo da obradimo sistemske pozive 104 (print_string), i 108 (read string).

	.ktext	0x80000180
handler:
	.set noat
	move $k1, $at
	sw $k1, saveat	# Cuvamo $at
	.set at

        mfc0 $k0, $13           # Preuzimamo Cause registar
        srl $k0, $k0, 2         
        andi $k0, $k0, 0xf      # Pomocu maske vadimo informaciju o razlogu dogadjaja.
								# Mozemo da obradimo sistemske pozive(8). 
								# Za sve drugo pozivamo exit()
        beq $k0, 8, syscallhdlr
exit:
        li $v0, 10             	# Ne mozemo da obradimo dogadjaj
        syscall

# Obradjivac sistemskog poziva
syscallhdlr:

	beq $v0, 104, doprint	# print_string sistemski poziv
	beq $v0, 108, doread	# print_string sistemski poziv
	b exit			# Za ostalo, exit()

doprint: jal myprint_string	# Pozivamo funkciju myprint_string()
	b restore				# i zavrsavamo sa obradjivacem
doread: jal myread_string	# Pozivamo funkciju myread_string()

restore:			# obnova registara
        mfc0 $k0, $14           # Uzimamo EPC registar
        addiu $k0, $k0, 4       # Preskacemo instrukciju syscall
                                # Tako sto uvecamo EPC za jednu instrukciju
        mtc0 $k0, $14           # Resetujemo EPC registar

        .set noat
        lw $k1, saveat          # Obnova $at registra
        move $at, $k1           
        .set at

        mtc0 $0, $13            # Brisemo Cause registar
        mfc0 $k0, $12           # 
        ori  $k0, 0x1           # Omogucujemo prekide 
        mtc0 $k0, $12           # u status registru
        eret                    # povratak korisnickom programu na instrukciju sa adesom iz EPC





myprint_string:	subu $sp, $sp, 24	# Pravimo minimalni stek frejm
		sw $ra, 20($sp)		# i sacuvamo registre $ra, $a0, $a1 i $a2
		sw $a0, 0($sp)		# tako da mozemo slobodno da ih menjamo
		sw $a1, 4($sp)
		sw $a2, 8($sp)

print_char:	lb $a1, ($a0)		# Ucitavamo karakter za ispis
		beq $a1, $0, endprint	# Zaustavljamo se ako je vrednost NUL

writeloop:	lw $a2, 0xffff0008	# Mozemo li da saljemo?
		bne $a2, 1, writeloop	# Ne jos
		sb $a1, 0xffff000c	# Da, upisujemo karakter u registar za slanje
		addi $a0, $a0, 1	# Uvecavamo pokazivac $a0
		j print_char		# I vrtimo petlju

endprint:	lw $ra, 20($sp)		# Zavrseno, obnavljamo registre
		lw $a2, 8($sp)			# sa vrednostima sa steka
		lw $a1, 4($sp)
		lw $a0, 0($sp)
		addu $sp, $sp, 24		# Unistavamo stek frejm
		jr $ra			# povratak iz funkcije


# 	myread_string(char* pBuffer, unsigned int charRemain)
#	{ 
#		if(charRemain > 0)
#		{
#			do
#			{
#				if(charRemain == 1)
#				{
#					*pBuffer = NUL;
#				}else
#				{
#					*pBuffer = ReadLoop();
#					if(*pBuffer == '\n')
#					{
#						++pBuffer;
#						*pBuffer = NUL;
#					}
#				}				
#				++pBuffer;
#				--charRemain;
#			}while(*(pBuffer-1) != NUL )
#		}
#		return;
#	}
		
myread_string:

		jr $ra			# povratak iz funkcije
	
