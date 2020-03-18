;------------------------------------- 
;超声发生子程序（12M晶振38.5KHz） 
;------------------------------------- 
                    NAME     CS_T 
?PR?CS_T?CS_T       SEGMENT  CODE 
                    PUBLIC   CS_T 
                    RSEG     ?PR?CS_T?CS_T 
CS_T:               PUSH     ACC 
                    MOV      TH0,   #00H 
                    MOV      TL0,   #00H 
                    MOV      A,     #4D 
                    SETB     TR0 
CS_T1:              CPL      P1.0 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    NOP 
                    DJNZ     ACC,  CS_T1 
                    POP      ACC 
                    RET 
                    END 
