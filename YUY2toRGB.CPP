//------------------------------------------------------------------------------
void BlitYUY2(void *source,void *dest,int larg,int haut,int pitch)
{
// 	_int64 R1B0 = 0x0198010002140100;
//	_int64 G1G0 = 0x006400D0006400D0;
	_int64 R1B0 = 0x00CC0095010A0095;
//	_int64 G1G0 = 0xFF980032FF980032;
//	_int64 Y1Y0 = 0x0000010000000100;
//	_int64 Y1Y0 = 0x0000009500000095;
	_int64 YU   = 0xFFCE0095FFCE0095;
	_int64 GV0  = 0x0000FF980000FF98;
	_int64 GAND = 0x0000FF000000FF00;
// 	_int64 RBAND = 0x00FF00FF00FF00FF;
	_int64 S128 = 0x0080001000800010;
	_asm
	{
		push	ebx
        push	ecx
        push	edx
        push	esi
        push	edi

		mov		esi,source			;pointe sur source
		mov     edi,dest
		mov     edx,pitch
		sub     edx,larg        	;modulo
		pxor	mm7,mm7
		shl     edx,2           	;en octet
		mov     ebx,haut
bcl:
		mov     ecx,larg
		shr     ecx,4
bcl1:
		prefetchnta	[esi+32]
		movq		mm0,[esi]		;V0,Y1,U0,Y0
		movq		mm4,mm0
		punpcklbw	mm0,mm7			;passe en 16bit
			
		punpckhbw	mm4,mm7
		psubsw		mm0,S128
		psubsw		mm4,S128

		pshufw		mm1,mm0,064h	;U0,Y1,U0,Y0
		pshufw		mm5,mm4,064h
		pshufw		mm2,mm0,0C6h	;V0,Y0,U0,Y1

		pmaddwd		mm0,R1B0		;R1, B0
		pshufw		mm3,mm2,0FFh	;V0,V0,V0,V0
		pmaddwd		mm1,YU			;0,Y1+U0,0,Y0+U0

		pmaddwd		mm5,YU			;0,Y1+U0,0,Y0+U0
		pshufw		mm6,mm4,0C6h	;V0,Y0,U0,Y1
		pmaddwd		mm4,R1B0		;R1, B0

		psrad		mm0,7
		pmaddwd		mm3,GV0
		paddd		mm1,mm3			;G1,G0

		pshufw		mm3,mm6,0FFh	;V0,V0,V0,V0
		pmaddwd		mm2,R1B0		;R0, B1
		psrad		mm4,7

		psrad		mm2,7
		psrad		mm1,7
		pmaddwd		mm3,GV0

		pmaddwd		mm6,R1B0		;R0, B1
		packuswb	mm1,mm1
		paddd		mm5,mm3			;G1,G0

		packuswb	mm0,mm2			;R0,B1,R1,B0
		psrad		mm6,7
		psrad		mm5,7

		punpcklbw	mm1,mm1
		pshufw		mm0,mm0,06Ch	;R1,B1,R0,B0
		packuswb	mm5,mm5

		pand		mm1,GAND
		add			esi,8
		packuswb	mm4,mm6			;R0,B1,R1,B0

		por			mm0,mm1
		punpcklbw	mm5,mm5
		pshufw		mm4,mm4,06Ch	;R1,B1,R0,B0
						
		movntq		[edi],mm0
		pand		mm5,GAND
		por			mm4,mm5

		movntq		[edi+8],mm4
		add         edi,16
;--------------------------------------------------------------------------------------
		movq		mm0,[esi]		;V0,Y1,U0,Y0
		movq		mm4,mm0
		punpcklbw	mm0,mm7			;passe en 16bit
		
		punpckhbw	mm4,mm7
		psubsw		mm0,S128
		psubsw		mm4,S128

		pshufw		mm1,mm0,064h	;U0,Y1,U0,Y0
		pshufw		mm5,mm4,064h
		pshufw		mm2,mm0,0C6h	;V0,Y0,U0,Y1

		pmaddwd		mm0,R1B0		;R1, B0
		pshufw		mm3,mm2,0FFh	;V0,V0,V0,V0
		pmaddwd		mm1,YU			;0,Y1+U0,0,Y0+U0

		pmaddwd		mm5,YU			;0,Y1+U0,0,Y0+U0
		pshufw		mm6,mm4,0C6h	;V0,Y0,U0,Y1
		pmaddwd		mm4,R1B0		;R1, B0

		psrad		mm0,7
		pmaddwd		mm3,GV0
		paddd		mm1,mm3			;G1,G0

		pshufw		mm3,mm6,0FFh	;V0,V0,V0,V0
		pmaddwd		mm2,R1B0		;R0, B1
		psrad		mm4,7

		psrad		mm2,7
		psrad		mm1,7
		pmaddwd		mm3,GV0

		pmaddwd		mm6,R1B0		;R0, B1
		packuswb	mm1,mm1
		paddd		mm5,mm3			;G1,G0

		packuswb	mm0,mm2			;R0,B1,R1,B0
		psrad		mm6,7
		psrad		mm5,7

		punpcklbw	mm1,mm1
		pshufw		mm0,mm0,06Ch	;R1,B1,R0,B0
		packuswb	mm5,mm5

		pand		mm1,GAND
		add			esi,8
		packuswb	mm4,mm6			;R0,B1,R1,B0

		por			mm0,mm1
		punpcklbw	mm5,mm5
		pshufw		mm4,mm4,06Ch	;R1,B1,R0,B0
					
		movntq		[edi],mm0
		pand		mm5,GAND
		por			mm4,mm5

		movntq		[edi+8],mm4
		add         edi,16

;--------------------------------------------------------------------------------------
		movq		mm0,[esi]		;V0,Y1,U0,Y0
		movq		mm4,mm0
		punpcklbw	mm0,mm7			;passe en 16bit
		
		punpckhbw	mm4,mm7
		psubsw		mm0,S128
		psubsw		mm4,S128

		pshufw		mm1,mm0,064h	;U0,Y1,U0,Y0
		pshufw		mm5,mm4,064h
		pshufw		mm2,mm0,0C6h	;V0,Y0,U0,Y1

		pmaddwd		mm0,R1B0		;R1, B0
		pshufw		mm3,mm2,0FFh	;V0,V0,V0,V0
		pmaddwd		mm1,YU			;0,Y1+U0,0,Y0+U0

		pmaddwd		mm5,YU			;0,Y1+U0,0,Y0+U0
		pshufw		mm6,mm4,0C6h	;V0,Y0,U0,Y1
		pmaddwd		mm4,R1B0		;R1, B0

		psrad		mm0,7
		pmaddwd		mm3,GV0
		paddd		mm1,mm3			;G1,G0

		pshufw		mm3,mm6,0FFh	;V0,V0,V0,V0
		pmaddwd		mm2,R1B0		;R0, B1
		psrad		mm4,7

		psrad		mm2,7
		psrad		mm1,7
		pmaddwd		mm3,GV0

		pmaddwd		mm6,R1B0		;R0, B1
		packuswb	mm1,mm1
		paddd		mm5,mm3			;G1,G0

		packuswb	mm0,mm2			;R0,B1,R1,B0
		psrad		mm6,7
		psrad		mm5,7

		punpcklbw	mm1,mm1
		pshufw		mm0,mm0,06Ch	;R1,B1,R0,B0
		packuswb	mm5,mm5

		pand		mm1,GAND
		add			esi,8
		packuswb	mm4,mm6			;R0,B1,R1,B0

		por			mm0,mm1
		punpcklbw	mm5,mm5
		pshufw		mm4,mm4,06Ch	;R1,B1,R0,B0
					
		movntq		[edi],mm0
		pand		mm5,GAND
		por			mm4,mm5

		movntq		[edi+8],mm4
		add         edi,16
;--------------------------------------------------------------------------------------
		movq		mm0,[esi]		;V0,Y1,U0,Y0
		movq		mm4,mm0
		punpcklbw	mm0,mm7			;passe en 16bit
		
		punpckhbw	mm4,mm7
		psubsw		mm0,S128
		psubsw		mm4,S128

		pshufw		mm1,mm0,064h	;U0,Y1,U0,Y0
		pshufw		mm5,mm4,064h
		pshufw		mm2,mm0,0C6h	;V0,Y0,U0,Y1

		pmaddwd		mm0,R1B0		;R1, B0
		pshufw		mm3,mm2,0FFh	;V0,V0,V0,V0
		pmaddwd		mm1,YU			;0,Y1+U0,0,Y0+U0

		pmaddwd		mm5,YU			;0,Y1+U0,0,Y0+U0
		pshufw		mm6,mm4,0C6h	;V0,Y0,U0,Y1
		pmaddwd		mm4,R1B0		;R1, B0

		psrad		mm0,7
		pmaddwd		mm3,GV0
		paddd		mm1,mm3			;G1,G0

		pshufw		mm3,mm6,0FFh	;V0,V0,V0,V0
		pmaddwd		mm2,R1B0		;R0, B1
		psrad		mm4,7

		psrad		mm2,7
		psrad		mm1,7
		pmaddwd		mm3,GV0

		pmaddwd		mm6,R1B0		;R0, B1
		packuswb	mm1,mm1
		paddd		mm5,mm3			;G1,G0

		packuswb	mm0,mm2			;R0,B1,R1,B0
		psrad		mm6,7
		psrad		mm5,7

		punpcklbw	mm1,mm1
		pshufw		mm0,mm0,06Ch	;R1,B1,R0,B0
		packuswb	mm5,mm5

		pand		mm1,GAND
		add			esi,8
		packuswb	mm4,mm6			;R0,B1,R1,B0

		por			mm0,mm1
		punpcklbw	mm5,mm5
		pshufw		mm4,mm4,06Ch	;R1,B1,R0,B0
					
		movntq		[edi],mm0
		pand		mm5,GAND
		por			mm4,mm5

		movntq		[edi+8],mm4
		add         edi,16

            
		dec		ecx
		jne     bcl1
		add     edi,edx
		dec     ebx
		jne     bcl

		emms
		pop		edi
	    pop		esi
	    pop		edx
	    pop		ecx
	    pop		ebx
    }
    return;
}
