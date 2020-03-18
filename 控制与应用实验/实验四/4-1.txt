	ORG 0000H	;设置程序入口地址
	LJMP START
	ORG 000BH	;设置T0中断程序入口地址
	LJMP T0IN
	ORG 0040H	;设置主程序偏移地址
START: 	MOV TMOD,#01H	;设置计数器0的计数方式为16位初值
	MOV TL0,#0F7H	;设置初值低8位
	MOV TH0,#0C2H	;设置初值高8位
	MOV A,#11H	;设置步进机初值，存A
	MOV R0,#96	;正转两圈共96步
	MOV R1,#8	;一次计数31.25ms，需要8次计数才到250ms
	MOV R2,#96           ;停顿3s，正好96次记数
	
	SETB EA		;开CPU中断
	SETB ET0	;开计数器T0中断
	SETB TR0	;计数器T0开始计数
        	LJMP $		;等待中断

T0IN:   	CJNE R0,#0,AA1	;判断正转96步是否结束
	CJNE R2,#0,AA2	;正转结束，则判断是否停止3s，一共96步
	RR A		;3s停止结束，则循环输出08H,04H,02H,01H，通过循环右移实现
	MOV P1,A		;输出到步进机
	LJMP AA4
AA2:         DEC R2		;3s停止未结束，R2减一计数
	LJMP AA4	
AA1:    	CJNE R1,#0,AA3	;正转未结束，则判断是否满8次计数
	RL A		;是则左移上次输出，形成循环输出01H，02H,04H,08H正转结果
	MOV P1,A		;输出到步进机
	DEC R0		;一次正转，R0减1
	MOV R1,#8	;重新设置8次计数值
	LJMP AA4
AA3:	DEC R1		;未满8次计数则R1进行减1计数
AA4:         MOV TL0,#0F7H	;设置初值低8位
	MOV TH0,#0C2H	;设置初值高8位
	RETI		;中断返回
	END
