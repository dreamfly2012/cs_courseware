   AREA SCopy,CODE,READONLY
    EXPORT strswap
T1 equ 0x40003000

strswap
    ;;;;;;[r0]=a;  r1=b  r2=c r3=d  
   LDRB R4,[R0]  ;A
   LDRB R5,[R1]  ;B
   LDRB R6,[R2]  ;C
   LDRB R7,[R3]  ;D
   
   STRB R5,[R0]  ;B
   STRB R7,[R1]  ;D
   STRB R6,[R2]  ;C
   STRB R4,[R3]  ;A

   MOV PC,LR;
   END 