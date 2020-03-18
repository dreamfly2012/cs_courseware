 AREA SCopy,CODE,READONLY
    EXPORT strcopy
strcopy
    ;;;;;;r0:目的串   r1:源串
   LDRB r2,[r1]                   ;修改过
   ADD  r1,r1,#1
   STRB r2,[r0]
   ADD  r0,r0,#1
   CMP r2,#0;
   BNE strcopy;
   MOV PC,LR;
   END 