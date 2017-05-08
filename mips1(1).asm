# Zadatak 4

# proci kroz string i za svako malo 


	.data
poruka1: .asciiz "Please enter a sentence: "
poruka2: .asciiz "Number of "
buffer: .space 27
ponavljanja: .space 52
newline: .asciiz "\n"
colon: .asciiz "'s: "


	.text
	
main:
	la $a0, poruka1		# ispis poruke
	li $v0, 4
	syscall
	
	li $v0, 8		# Unos stringa
	la $a0, buffer		# Unos sacuvati na adresu n akojoj se nalazi buffer
	li $a1, 27		# Max duzina unosa
	syscall
	
	move $t0, $a0		# Sacuvati string u $t0  BUFFER
	
	li $t1, 0		#brojac
	li $t2, 0		
	
	
inicijalizacija_ponavljanja:
	sb $t2, ponavljanja($t1)
	
	addi $t1, $t1, 1
	blt $t1, 52, inicijalizacija_ponavljanja
	
	li $t1, 0		# vratiti brojac na 0 | brojac kroz buffer
	li $t3, 0		# brojac kroz ponavljanja
	li $t4, 1		# brojac ponavljanja pojedinacnih slova
	
	# $t2 ce se koristiti za preuzimanje slova
	
slovo_po_slovo:
	lb $t2, buffer($t1)
	move $t5, $t1			# da bi $t1 sacuvao vrednost, a $t5 ce se koristiti za prolazak kroz ostatak buffera
	bge $t2, 97, manje_od_122	# provera 1: ako je >= 97 -> skok na proveru 2
	b sledece_slovo			# U slucaju da je < 97, prelazi se na sledeci karakter
	
manje_od_122:				# provera 2: ako je <= 122 -> skok na prebrojavanje
	ble $t2, 122, vrati_brojac	# Ako je slovo u zeljenom opsegu, prelazi se na prebrojavanje
	b sledece_slovo				# ako nije, provera sledeceg karaktera
	
sledece_slovo:
	add $t1, $t1, 1
	li $t4, 1		# vrati brojac na 1
	bge $t1,27, ispis	# ako smo prosli kroz sva slova, prelazimo na ispis
	b slovo_po_slovo

vrati_brojac:
	li $t3, 0
	
proveri_ponavljanja:
	# $t7 ce biti korisceno za privremeno cuvanje vrednosti
	lb $t6, ponavljanja($t3)
	beq $t2, $t6, sledece_slovo	# Ako se slova podudaraju, prelazimo na sledece slovo
	move $t7, $t1
	move $t1, $t6 
	move $t1, $t7
	beqz $t1, prebroj_ponavljanja
	add $t3, $t3, 1
	#move $t1, $t7
	lb $t6, ponavljanja($t3)
	move $t7, $t1			# $t1 = $t7
	move $t1, $t6
	beqz $t1, prebroj_ponavljanja	# Ako je smo naisli na 0, znaci da slovo nije pronadjeno
	add $t3, $t3, 1
	move $t1, $t7			# # $t7 = $t1
	bgt $t3, 52, ispis		# Ako je niz popunjen, idemo na ispis (slucaj da su sva slova napisana jednom)
	
prebroj_ponavljanja:
	#move $t1, $t7
	add $t5, $t5, 1			# $t5 se povecava zato sto inicijalno cuva poziciju slova koje se prebrojava
	add $t3, $t3, 1
	lb $t7, buffer($t5)
	beq $t2, $t7, povecaj_ponavljanja
	bge $t5, 26, smesti_u_ponavljanja	# ako smo proverili sva slova, prelazimo na smestanje rezultata
	b prebroj_ponavljanja
	
povecaj_ponavljanja:
	add $t4, $t4, 1			# Uvecaj broj ponavljanja
	b prebroj_ponavljanja		# povratak na prebrojavanje
	
smesti_u_ponavljanja:
	la $t7, ponavljanja
	add $t7, $t7, $t3
	sb $t2, ($t7)			# stavljamo na $t7 jer je to prvi nulti clan
	add $t3, $t3, 1			# na sledece mesto stavljamo broj ponavljanja ascii vrednost = $t4 + 48
	add $t4, $t4, 48
	sb $t4, ponavljanja($t3)
	add $t3, $t3, 1			# Pomeramo se za 2 bajta, jer je pored slova zapisan broj njegovih ponavljanja
	b sledece_slovo
		
ispis:
	li $t1, 0	
	
ispis_petlja:
	
	la $a0, poruka2
	li $v0, 4
	syscall
	
	lb $a0, ponavljanja($t1)		# Stampanje slova
	add $t1, $t1, 1
	#li $a1, 2
	li $v0, 11
	syscall
	
	la $a0, colon
	li $v0, 4
	syscall
	
	lb $a0, ponavljanja($t1)		# stampanje broja ponavljanja
	add $t1, $t1, 1
	#li $a1, 1		
	li $v0, 11
	syscall
	
	la $a0, newline
	li $v0, 4
	syscall
	
	
	move $t3, $t1			# $t7 = $t1
	lb $t1, ponavljanja($t3)
	beqz $t1, kraj			# ako su u $a0 nalazi nula, dosli smo do kraja
	move $t1, $t3			# $t1 = $t7	
	b ispis_petlja
	
	
	
	
	
	
kraj:	
 	li $v0, 10
 	syscall			#end of program
