# Primer kako obradjivac otkucaja casovnika izaziva prekljucenje procesora.
# (c) 2016, GPL3


# Definisanje PCB bloka za svaki program
	.kdata
p1pcb:	.space 20	# Prostor za a0, v0, t0, t1 i PC (offset 0, 4, 8, 12, 16)
p2pcb:	.space 20	# Isto

curpcb:	.word 0		# Offset tekuceg PCB bloka. Vrednost 0 ili 20
saveat:	.word 0		# Sacuvana vrednost $at registra

# Ovo je ulazna tacka za obradjivac sistemskih poziva i obradjivac prekida
	.ktext	0x80000180
handler:
	.set noat
	move $k1, $at
	sw $k1, saveat          # Cuvamo $at
	.set at

	mfc0 $k0, $13           # Preuzimamo Cause registar
	srl $k0, $k0, 2         
	andi $k0, $k0, 0xf		# Pomocu maske vadimo informaciju o razlogu dogadjaja.
				# Mozemo da obradimo prekide(0)
				# ili sistemske pozive(8). 
				# Za sve drugo pozivamo exit()
	beqz $k0, inthandler
	beq $k0, 8, syscallhdlr
exit:
	li $v0, 10		# Ne mozemo da obradimo dogadjaj
	syscall

# Obradjivac sistemskog poziva 100
syscallhdlr:
	bne $v0, 100, exit	# Ako nije sistemski poiv 100 onda exit()

	la $k0, p1pcb
	sw $a0, 16($k0)		# Adresa prve instrukcije programa prog1
	sw $0, 12($k0)		# ostala polja PCB-a su inicijalno 0
	sw $0, 8($k0)
	sw $0, 4($k0)
	sw $0, 0($k0)
	la $k0, p2pcb
	sw $a1, 16($k0)		# Adresa prve instrukcije programa prog2
	sw $0, 12($k0)		# ostala polja PCB-a su inicijalno 0
	sw $0, 8($k0)
	sw $0, 4($k0)
	sw $0, 0($k0)

	la $k0, 0xFFFF0013	# Omogucimo otkucaje casovnika od "Digial Lab Sim"
	li $k1, 1
	sb $k1, ($k0)
	b restore		# pocinjemo sa prvim programom


# Obradjivac prekida otkucaja casovnika
inthandler:			# Prvo sacuvamo registre programa
	la $k0, p1pcb
	lw $k1, curpcb
	add $k0, $k0, $k1	# k0 = p1pcb + curpcb, bazna adresa + offset
	sw $a0, 0($k0)		# Sacuvamo registre a0, v0, t0 i t1 
	sw $v0, 4($k0)
	sw $t0, 8($k0)
	sw $t1, 12($k0)
	mfc0 $k1, $14
	sw $k1, 16($k0)		# Sacuvamo stari programski brojac iz EPC registra

				# Kada smo sacuvali stanje prethodnog programa,
				# mozemo promeniti aktuelni program promenom offset-a curpcb.

	lw $k0, curpcb
	li $k1, 20
	sub $k0, $k1, $k0	# k0 = 20 - curpcb, 20 => 0, 0 => 20
	sw $k0, curpcb

				# Sada mozemo da obnovimo stanje drugog programa i pokrenemo ga
		
restore:			# Obnavljamo registre i resetujemo stanje procesora
	la $k0, p1pcb
	lw $k1, curpcb
	add $k0, $k0, $k1	# k0 = p1pcb + curpcb, bazna adresa + offset
	lw $a0, 0($k0)		# obnavljamo registre a0, v0, t0 i t1
	lw $v0, 4($k0)
	lw $t0, 8($k0)
	lw $t1, 12($k0)
	lw $k1, 16($k0)		# Programski brojac smestamo u EPC registar
	mtc0 $k1, $14

	.set noat
	lw $k1, saveat          # Obnavljamo registar $at
	move $at, $k1           
	.set at

	mtc0 $0, $13            # Brisemo Cause registar
	mfc0 $k0, $12           # 
	ori  $k0, 0x1           # Omogucujemo prekide 
	mtc0 $k0, $12			# u status registru
	eret			# povratak korisnickom programu na instrukciju sa adesom iz EPC
