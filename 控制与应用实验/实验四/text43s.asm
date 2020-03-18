ORG    0000H
LJMP   STRT
ORG    000BH ;中断T0
LJMP   LP0
ORG    0040H
STRT:  MOV 00H,#01H;初始化为正转
           MOV 01H,#00H
            MOV TMOD,#01H;初始化中断,方式1工作
            MOV TH0,#9EH;送初值高8位,中断时间50ms
            MOV TL0,#58H;送初值低8位
            MOV R2,#60H;正转步数,两圈48*2=96步,每250ms正转一步
            MOV R3,#00H;初始化查表偏移量R3=00H
            MOV R4,#0;正转计数5次
           ; MOV R5,#0
            SETB EA
            SETB ET0
            SETB TR0
HALT:  SJMP $;等待中断
LP0:     ;MOV DPTR,#TAB
           JB 01H,DL3S;if 1 then jmp;延时三秒?
            JNB 00H,LP2;if 0 then jmp;0,反转
            INC R4
            CJNE R4,#5,LP00
            MOV R4,#00H;等于5,重新送0
            SJMP LP1
LP00:   RETI;正转  
LP1:      MOV DPTR,#TAB
            MOV A,R3
            MOVC A,@A+DPTR
            CJNE A,#00H,LPP0;走完四拍返回,重新初始化偏移量R3
            MOV R3,#00H
            LJMP LP0 
LPP0:  MOV P1,A  ;没有到达00H一拍,步进一步
           INC R3 ;拍数目+1,偏移+1
           DJNZ R2,LPP1  ;步数-1,是否完成步数,未完成步数延时中断
           ;MOV 00H,00H
           JNB 00H,AA1;正转结束第一次时延时3s,0 jump 
            MOV 01H,01 ;第一次时延时3s
           LJMP  AA1      
DL3S:  MOV R0,#00H ;完成正转后需要延时3S
           MOV 01H,#01 ;需要延时3s
           INC R0
           CJNE R0,#3CH,LP00;延时3s未完成   
           MOV 01H,00H ;完成3s延时
AA1:    MOV 00,#00H;正转结束,变为反转
           MOV R2,#60H ;每次反转送R2值
           MOV R3,#00H;查表偏移清0    
           MOV TH0,#0C2H  ;31.25ms
           MOV TL0,#0F6H
           RETI	      
LPP1:  JNB 00H,AA2;(00H)为1正转延时;0,反转延时
           MOV TH0,9EH;50ms,重新送计数初值,正转
           MOV TL0,58H
           RETI
AA2:   MOV TH0,0C2H;31.25ms,重新送计数初值,正转
          MOV TL0,0F6H
          RETI	   
LP2:   MOV A,R3;反转   
          ADD A,#05H;偏移量反向控制  
          MOV R3,A
          LJMP LP1
TAB:  DB  01H,02H,04H,08H,00H;正转,00H作为结束
          DB  08H,04H,02H,01H,00H;反转,00H作为结束
END
