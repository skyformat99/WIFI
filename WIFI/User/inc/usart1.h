#ifndef USART1_H
#define USART1_H
#include "includes.h"
 //�������16���Ĺ�����������ú�
 //�������8���Ĺ��������򲻶���ú�
#define Usart1_OVER8

void Usart1_Init(int boand);
void Usart1_Sendbyte(u8 date);
void Usart1_SendString(char *buf);
u8 Usart1_Receivebyte(void);
void Usart1_Receivestring(char *buf);
void Usart1_Exit_Init(void);

#endif
