ORG 0000H
LJMP STRT
ORG 000BH
LJMP T0IN
ORG 0040H
STRT:MOV TMOD,#01H
          MOV TL0,#0FEH
          MOV TH0,#0C2H
          MOV R0,#01
          MOV R1,#0          ; 0:FRONT 1:HALT 2:REVERSE
          MOV R6,#96
          MOV R7,#8 ;INTERUPT COUNT
          SETB EA
          SETB ET0
          SETB TR0
          SJMP $
T0IN:MOV TL0,#0FEH
         MOV TH0,#0C2H
         DJNZ R7,EXIT
         CJNE R1,#0,PAUSE
         CJNE R0,#16,AA1
         MOV R0,#01
AA1:MOV P1,R0
      MOV A,R0
       RL A
       MOV R0,A
       MOV R7,#8
       DJNZ R6,EXIT
       MOV R7,#96
       MOV R1,#1
       AJMP EXIT
PAUSE:MOV R1,#2
         MOV R7,#1
BACK:CJNE R0,#00,AA3
         MOV R0,#08
AA3:MOV P1,R0
      MOV A,R0
      RR A
      MOV R0,A
      MOV R7,#1
EXIT:RETI
END
 