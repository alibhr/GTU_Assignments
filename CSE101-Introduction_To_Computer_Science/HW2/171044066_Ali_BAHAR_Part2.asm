		load	R1,Name
		load	R2,1			;sonraki karakter için ama ekrana yazdýrmadým.
		load	R0,0
		load	R4,-1		;öceki karakter.
		load	R3,0			;name kýsmýndaki karakter sayýsý.
HarfAtla:
		addi	R1,R1,R2
		jmpEQ	R1=R0,devam
		addi	R3,R3,R2
		jmp		HarfAtla
devam:	load	R0,10		;geri dönerken 10'u gördüðünde durmasý için kullandým.
		load	RF,[R3]
		addi	R3,R3,R4	;önceki karaktere geçiþ.
		jmpEQ	RF=R0,Ready
		jmp		devam


Ready:	halt

Text:	db		10,"Ali BAHAR"
		db		0
