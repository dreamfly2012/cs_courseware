;------------------------------------- 
;延时100机器周期*参数（1~65535） 
;------------------------------------- 
                    NAME     DELAY 
?PR?_DELAY?DELAY    SEGMENT  CODE 
                    PUBLIC   _DELAY 
                    RSEG     ?PR?_DELAY?DELAY 
_DELAY:             PUSH     ACC               ;2 
		    MOV      A,     R7         ;1 
                    JZ       DELA1             ;2 
	            INC      R6                ;1 
DELA1:              MOV      R5,    #50D       ;2 
                    DJNZ     R5,    $          ;2 
                    DJNZ     R7,    DELA1      ;2 
                    DJNZ     R6,    DELA1      ;2 
                    POP      ACC               ;2 
                    RET                        ;2  
                    END 
