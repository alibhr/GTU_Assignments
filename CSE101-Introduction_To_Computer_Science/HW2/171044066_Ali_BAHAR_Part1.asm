load R0,0
load R1,5		;fakt�riyeli al�nmak istenen sayi.
load R2,4		;fakt�riyeli alinmak istenen sayinin 1 eksigi.
load R3,1		;yaln�zca 1! i�in.
move R0,R1		;yaln�zca 1! i�in.
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
move RF,R9		;sonuc ekranda hexadecimal olarak g�r�nt�leniyor.
load RA,10		;sonu�lar� alt alta g�stereilmek i�in.
move RF,RA		
HALT
