		load	R1,Name
		load	R2,1			;sonraki karakter i�in ama ekrana yazd�rmad�m.
		load	R0,0
		load	R4,-1		;�ceki karakter.
		load	R3,0			;name k�sm�ndaki karakter say�s�.
HarfAtla:
		addi	R1,R1,R2
		jmpEQ	R1=R0,devam
		addi	R3,R3,R2
		jmp		HarfAtla
devam:	load	R0,10		;geri d�nerken 10'u g�rd���nde durmas� i�in kulland�m.
		load	RF,[R3]
		addi	R3,R3,R4	;�nceki karaktere ge�i�.
		jmpEQ	RF=R0,Ready
		jmp		devam


Ready:	halt

Text:	db		10,"Ali BAHAR"
		db		0
