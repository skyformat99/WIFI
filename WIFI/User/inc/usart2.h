#ifndef USART2_H
#define USART2_H
	#include "includes.h"
	/**
	 ���������Usart2_OVER8��˵�����õ���16���Ĺ�����
	������8���Ĺ�����
	**/

#define Usart2_OVER8

void Usart2_Init(int boand);
void Usart2_Sendbyte(u8 date);
void Usart2_SendString(u8 *buf);
void Usart2_Receivestring(char *str);
u8 Usart2_Receivebyte(void);
void Usart2_Exit_Init(void);




#endif


