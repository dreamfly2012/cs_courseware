X		 EQU		1
Y		 EQU		128
		 AREA	LG,CODE,READONLY
		 ENTRY
		 CODE32
START   LDR		SP,=0x40003F00;设置堆栈
		 LDR		R0,=X
		 LDR       R1,=Y
LOOP	 CMP		R0,R1
		 LDRHI	    R0,=X
		 BL		    SUB        ;调用子程序，返回值为R0
		 B		    LOOP

SUB		 STMFD	SP!,{R2-R7,LR}
		 MOV     R0,R0,LSL #1
		 LDMFD  SP!,{R2-R7,PC}
		 END 
