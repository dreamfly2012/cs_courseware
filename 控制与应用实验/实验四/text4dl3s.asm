ORG    0000H
LJMP   STRT
ORG    000BH ;�ж�T0
LJMP   LP0
ORG    0040H
STRT:  MOV 00H,#01H   ;��ʼ��Ϊ��ת
            MOV TMOD,#01H    ;��ʼ���ж�,��ʽ1����
            MOV TH0,#9EH    ;�ͳ�ֵ��8λ,�ж�ʱ��50ms
            MOV TL0,#58H    ;�ͳ�ֵ��8λ
            MOV R2,#60H     ;��ת����,��Ȧ48*2=96��,ÿ250ms��תһ��
            MOV R3,#00H      ;��ʼ�����ƫ����R3=00H
            MOV R4,#0
            MOV R5,#0      ;R5=1ʱ�������,�����ǵ�һ�����ʱ��Ϊ1
            SETB EA         ;���ж�,EA=1,�ж������־
            SETB ET0       ;ET0=1,T0�ж�����λ
            SETB TR0       ;����T0
HALT:  SJMP $     ;�ȴ��ж�
LP0:     MOV DPTR,#TAB  ;ȡTAB���ַ
            JB R5,DL3S    ;R5=1��ʱ����
            JNB 00H,LP2  ;(00H)Ϊ1��ת;0,��ת,����ת�ж�
            INC R4
            CJNE R4,#5,LP00;R4������5ת��
            MOV R4,#00H     ;����5��������0
            SJMP LP1       ;��ת
LP00:   RETI
LP1:     MOV A,R3    ;��ת
            MOVC A,@A+DPTR
            CJNE A,#00H,LPP0;�������ķ���,���³�ʼ��ƫ����R3
            MOV R3,#00H
            LJMP LP0
LPP0:  MOV P1,A  ;û�е���00Hһ��,����һ��
           INC R3 ;����Ŀ+1,ƫ��+1
           DJNZ R2,LPP1  ;����-1,�Ƿ���ɲ���,δ��ɲ�����ʱ�ж�
           JNB 00H,AA1;��ת������һ��ʱ��ʱ3s
DL3S:  MOV R0,#00H ;�����ת����Ҫ��ʱ3S
           MOV R5,#01 ;��Ҫ��ʱ3s
           INC R0
           CJNE R0,#3C,LP00;��ʱ3sδ���
           MOV R5,00H ;���3s��ʱ
AA1:    MOV 00,#00H;��ת����,��Ϊ��ת
           MOV R2,#60H ;ÿ�η�ת��R2ֵ
           MOV R3,#00H;���ƫ����0
           MOV TH0,#0C2H  ;31.25ms
           MOV TL0,#0F6H
           RETI
LPP1:  JNB 00H,AA2;(00H)Ϊ1��ת��ʱ;0,��ת��ʱ
           MOV TH0,9EH;50ms,�����ͼ�����ֵ,��ת
           MOV TL0,58H
           RETI
AA2:   MOV TH0,0C2H;31.25ms,�����ͼ�����ֵ,��ת
          MOV TL0,0F6H
          RETI
LP2:   MOV A,R3;��ת
          ADD A,#05H;ƫ�����������
          MOV R3,A
          LJMP LP1
TAB:  DB  01H,02H,04H,08H,00H;��ת,00H��Ϊ����
          DB  08H,04H,02H,01H,00H;��ת,00H��Ϊ����
END
