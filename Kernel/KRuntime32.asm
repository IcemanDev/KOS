
	SEGMENT .text

	GLOBAL ?KPortOutputB@@YIXIE@Z
?KPortOutputB@@YIXIE@Z:
	MOV AL, DL
	MOV EDX, ECX
	OUT DX, AL
	RET

	GLOBAL ?KPortOutputW@@YIXIG@Z
?KPortOutputW@@YIXIG@Z:
	MOV AX, DX
	MOV EDX, ECX
	OUT DX, AX
	RET
	
	GLOBAL ?KPortOutputD@@YIXII@Z
?KPortOutputD@@YIXII@Z:
	MOV EAX, EDX
	MOV EDX, ECX
	OUT DX, EAX
	RET

	GLOBAL ?KPortInputB@@YIEI@Z
?KPortInputB@@YIEI@Z:
	MOV EDX, ECX
	IN AL, DX
	RET

	GLOBAL ?KPortInputW@@YIGI@Z
?KPortInputW@@YIGI@Z:
	MOV EDX, ECX
	IN AX, DX
	RET

	GLOBAL ?KPortInputD@@YIII@Z
?KPortInputD@@YIII@Z:
	MOV EDX, ECX
	IN EAX, DX
	RET
	