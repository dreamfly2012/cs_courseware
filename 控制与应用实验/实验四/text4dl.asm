ORG    	0000H
LJMP  	STRT
ORG  	 000BH
CJNE  	R0,#0,LP2  ;������0��ת
LJMP 	LP1
ORG  	0040H
STRT:  	MOV 00H,#0 ;��ʼ��Ϊ0����ת	
	MOV TMOD,#01H  
	MOV TH0,#9EH  ;;�ͳ�ֵ��8λ,�ж�ʱ��50ms
	MOV TL0,#57H;�ͳ�ֵ��8λ
	MOV R2,#96   ;��ת����,��Ȧ48*2=96��,ÿ250ms��תһ��
	MOV R3,#00H   ;��ʼ�����ƫ����R3=00H
	MOV R4,#0
                MOV R5,#96   ;ͣ��3s������96�μ���
	SETB EA ;���ж�,EA=1,�ж������־
	SETB ET0;ET0=1,T0�ж�����λ
	SETB TR0;����T0
HALT:	SJMP $;�ȴ��ж�
LP1:	INC R4
	CJNE R4,#5,LP7;R4������5ת��
	MOV R4,#0     ;����5��������0
	SJMP LP8      ;��ת
LP7:	RETI
LP8:	MOV DPTR,#TAB ;��ת
	MOV A,R3
	MOVC A,@A+DPTR
	CJNE A,#00H,LP0  ;û�е���TAB���һ��
	MOV R3,#0     ;�����β,���·���TAB��ʼ
	MOV A,R3      
	MOV P1,A
	SJMP LP5      ;
LP0: 	MOV P1,A   ;����R3ƫ��+1
	INC R3
LP5:	DJNZ R2,LP3;����-1,�Ƿ���ɲ���,δ��ɲ�����ʱ�ж�
	MOV R0,#1      ;��ת����
	MOV R3,#00H    ;���ƫ����0
	MOV TH0,#0C2H  ;31.25ms
	MOV TL0,#0F6H
	RETI
LP3:	MOV TH0,9EH;50ms,�����ͼ�����ֵ,��ת
	MOV TL0,57H
	RETI
LP2:	CJNE R5,#0,AA2	;��ת���������ж��Ƿ�ֹͣ3s��һ��96��
                MOV DPTR,#TAB2;��ת
	MOV A,R3
	MOVC A,@A+DPTR
	CJNE A,#00H,LP4;TAB2û�е����β
	MOV R3,#00H;�������¿�ʼ
	MOV A,R3
	MOV P1,A
	SJMP LP6
LP4:	MOV P1,A
	INC R3
LP6:	MOV TH0,#0C2H;�����ͼ�����ֵ
	MOV TL0,#0F6H
	RETI
AA2:         DEC R5;3sֹͣδ������R5��һ����
	LJMP LP6
TAB:	DB 01H,02H,04H,08H,00H
TAB2:	DB 08H,04H,02H,01H,00H
	END
