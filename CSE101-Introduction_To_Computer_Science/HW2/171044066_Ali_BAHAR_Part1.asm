load R0,0
load R1,5		;faktöriyeli alýnmak istenen sayi.
load R2,4		;faktöriyeli alinmak istenen sayinin 1 eksigi.
load R3,1		;yalnýzca 1! için.
move R0,R1		;yalnýzca 1! için.
jmpEQ R3=R0,son
load R4,-1
load R5,0
load R6,0


sonraki:addi R5,R5,R1
addi R6,R6,R3
move R0,R2
jmpEQ R6=R0,sonr
jmp sonraki

sonr: addi R2,R2,R4
jmpEQ R3=R0,son
move R1,R5
load R6,0
load R5,0
jmp sonraki

son:load R7,00001111b
ror R1,4
load R8,48d
and R9,R1,R7
addi R9,R9,R8
move RF,R9
ror R1,4
and R9,R1,R7
addi R9,R9,R8
move RF,R9		;sonuc ekranda hexadecimal olarak görüntüleniyor.
load RA,10		;sonuçlarý alt alta göstereilmek için.
move RF,RA		
HALT
