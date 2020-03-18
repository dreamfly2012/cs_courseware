  AREA Exp0103,CODE,READONLY
SourceAddr  EQU 0x40003000
DestAddr    EQU 0x40003100

  ENTRY
  CODE32
START   LDR R0,=SourceAddr
        MOV R1,#0
STOREDIGITAL    STRB R1,[R0],#1
                ADD R1,R1,#1              
                CMP  R1,#255
                BLS  STOREDIGITAL
                LDR R0,=SourceAddr
                LDR R1,=DestAddr
                MOV R2,#0                
COPYSTR         LDRB R3,[R0],#1
                STRB R3,[R1],#1    
                ADD  R2,R2,#1
                CMP  R2,#255
                BLS  COPYSTR
STOP    MOV     R0, #0x18     
        LDR     R1, =0x20026  
        SWI     0x123456  
   END  
  