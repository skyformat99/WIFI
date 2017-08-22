#ifndef W25Q64_H
#define W25Q64_H
#include "includes.h"

              // cs ���� PB14
#define  CS_L   GPIOB->ODR &=~(0x1<<14);
	           // cs ����
#define  CS_H    GPIOB->ODR |=(0x1<<14);


//ҳ���
void W25Q64_Page_Program(u32 addr,u8 date);
u8 W25Q64_Read_Date(u32 addr);

void W25Q64_Read_DateFromZK(u32 addr,u16 size,u8 *date);
//дʹ��
void W25Q64_WriteEnable(void);
void W25Q64_WriteDisable(void);

//����
void W25Q64_Sector_Erase(u32 addr);
void W25Q64_Block_Erase(u32 addr);
void W25Q64_Chip_Erase(void);
//��״̬
void W25Q64_ReadStatus(void);



#endif

