COUNT		EQU	0x40003100	; ����һ����������ַΪ0x40003100	
			AREA	Example2,CODE,READONLY	; ���������Example2 
			ENTRY				; ��ʶ�������
			CODE32				; ����32λARMָ��
START		LDR		R1,=COUNT	; R1 <= COUNT
			MOV		R0,#0		; R0 <= 0 
			STR		R0,[R1]	; [R1] <= R0��������COUNTΪ0
LOOP   		LDR		R1,=COUNT	
			LDR		R0,[R1]		; R0 <= [R1] 
			ADD		R0,R0,#1	; R0 <= R0 + 1
			CMP		R0,#8	; R0��10�Ƚϣ�Ӱ���������־
			MOVHS	R0,#0	; ��R0���ڵ���8�����ָ��ִ�У�R0 <= 0
			STR		R0,[R1]	; [R1] <= R0��������COUNT
		;	B		LOOP
		
stop
            MOV     r0, #0x18      ;ִ����ֹ
            LDR     r1, =0x20026   ; 
	        SWI     0x123456       ;ARM semihosting SWI
		
		
			END