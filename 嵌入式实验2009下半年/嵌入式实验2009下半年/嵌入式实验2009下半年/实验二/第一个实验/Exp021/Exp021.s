COUNT		EQU	0x40003100	; 定义一个变量，地址为0x40003100	
			AREA	Example2,CODE,READONLY	; 声明代码段Example2 
			ENTRY				; 标识程序入口
			CODE32				; 声明32位ARM指令
START		LDR		R1,=COUNT	; R1 <= COUNT
			MOV		R0,#0		; R0 <= 0 
			STR		R0,[R1]	; [R1] <= R0，即设置COUNT为0
LOOP   		LDR		R1,=COUNT	
			LDR		R0,[R1]		; R0 <= [R1] 
			ADD		R0,R0,#1	; R0 <= R0 + 1
			CMP		R0,#8	; R0与10比较，影响条件码标志
			MOVHS	R0,#0	; 若R0大于等于8，则此指令执行，R0 <= 0
			STR		R0,[R1]	; [R1] <= R0，即保存COUNT
		;	B		LOOP
		
stop
            MOV     r0, #0x18      ;执行中止
            LDR     r1, =0x20026   ; 
	        SWI     0x123456       ;ARM semihosting SWI
		
		
			END