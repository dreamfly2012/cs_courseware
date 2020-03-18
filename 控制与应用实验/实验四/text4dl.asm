ORG    	0000H
LJMP  	STRT
ORG  	 000BH
CJNE  	R0,#0,LP2  ;不等于0反转
LJMP 	LP1
ORG  	0040H
STRT:  	MOV 00H,#0 ;初始化为0，正转	
	MOV TMOD,#01H  
	MOV TH0,#9EH  ;;送初值高8位,中断时间50ms
	MOV TL0,#57H;送初值低8位
	MOV R2,#96   ;正转步数,两圈48*2=96步,每250ms正转一步
	MOV R3,#00H   ;初始化查表偏移量R3=00H
	MOV R4,#0
                MOV R5,#96   ;停顿3s，正好96次记数
	SETB EA ;开中断,EA=1,中断允许标志
	SETB ET0;ET0=1,T0中断允许位
	SETB TR0;启动T0
HALT:	SJMP $;等待中断
LP1:	INC R4
	CJNE R4,#5,LP7;R4不等于5转移
	MOV R4,#0     ;等于5，重新送0
	SJMP LP8      ;正转
LP7:	RETI
LP8:	MOV DPTR,#TAB ;正转
	MOV A,R3
	MOVC A,@A+DPTR
	CJNE A,#00H,LP0  ;没有到达TAB最后一个
	MOV R3,#0     ;到达结尾,重新返回TAB开始
	MOV A,R3      
	MOV P1,A
	SJMP LP5      ;
LP0: 	MOV P1,A   ;则让R3偏移+1
	INC R3
LP5:	DJNZ R2,LP3;步数-1,是否完成步数,未完成步数延时中断
	MOV R0,#1      ;正转结束
	MOV R3,#00H    ;查表偏移清0
	MOV TH0,#0C2H  ;31.25ms
	MOV TL0,#0F6H
	RETI
LP3:	MOV TH0,9EH;50ms,重新送计数初值,正转
	MOV TL0,57H
	RETI
LP2:	CJNE R5,#0,AA2	;正转结束，则判断是否停止3s，一共96步
                MOV DPTR,#TAB2;反转
	MOV A,R3
	MOVC A,@A+DPTR
	CJNE A,#00H,LP4;TAB2没有到达表尾
	MOV R3,#00H;到达重新开始
	MOV A,R3
	MOV P1,A
	SJMP LP6
LP4:	MOV P1,A
	INC R3
LP6:	MOV TH0,#0C2H;重新送计数初值
	MOV TL0,#0F6H
	RETI
AA2:         DEC R5;3s停止未结束，R5减一计数
	LJMP LP6
TAB:	DB 01H,02H,04H,08H,00H
TAB2:	DB 08H,04H,02H,01H,00H
	END
