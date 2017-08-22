#include "includes.h"

/***************************************

��������W25Q64_Page_Program
����������
��������ֵ����
�������ܣ�ʵ��W25Q64ҳ���
�����������洢����
****************************************/
void W25Q64_Page_Program(u32 addr,u8 date)
{
	//дʹ��
  W25Q64_WriteEnable();
	CS_L;
	//mcu����оƬҲ���ָ��
	SPI_SendDate(0x02);
	//����24λ��ַ
	SPI_SendDate(addr>>16);
	SPI_SendDate(addr>>8);
	SPI_SendDate(addr);
	SPI_SendDate(date);
	CS_H;
	W25Q64_ReadStatus();
}
/***************************************

��������W25Q64_Read_Date
����������
��������ֵ����
�������ܣ�ʵ��W25Q64ҳ���
����������������
****************************************/
u8 W25Q64_Read_Date(u32 addr)
{
	u8 date;
	CS_L;
	//���Ͷ�ָ��
	SPI_SendDate(0x03);
	SPI_SendDate(addr>>16);
	SPI_SendDate(addr>>8);
	SPI_SendDate(addr);
	date=SPI_ReceiveDate();
	CS_H;
	return date;
}
/***************************************

��������W25Q64_Read_DateFromZK
����������
��������ֵ����
�������ܣ�ʵ��W25Q64ҳ���
����������������
****************************************/
void W25Q64_Read_DateFromZK(u32 addr,u16 size,u8 *date)
{
	u16 i;
	CS_L;
	//���Ͷ�ָ��
	SPI_SendDate(0x03);
	SPI_SendDate(addr>>16);
	SPI_SendDate(addr>>8);
	SPI_SendDate(addr);
	for(i=0;i<size;i++)
	{
	*date=SPI_ReceiveDate();
	date++;
	}
	CS_H;

}



/***************************************

��������W25Q64_WriteEnable()
����������
��������ֵ��
�������ܣ�W25Q64дʹ��
����������
 
****************************************/
void W25Q64_WriteEnable()
{

	CS_L;
	//����дʹ��ָ��
	SPI_SendDate(0x06);
	CS_H;

}

/***************************************

��������W25Q64_WriteDisable()
����������
��������ֵ��
�������ܣ�W25Q64д���ݽ���
����������
 
****************************************/
void W25Q64_WriteDisable()
{
	CS_L;
	SPI_SendDate(0x04);
	CS_H;
}

/***************************************

��������W25Q64_Sector_Erase()
����������
u32 addr
��������ֵ��
�������ܣ�W25Q64��ʹ��
����������
 
****************************************/
void W25Q64_Sector_Erase(u32 addr)
{
	W25Q64_WriteEnable();
  CS_L;
	//��MCU������������ָ��
	SPI_SendDate(0x20);
	
	SPI_SendDate(addr>>16);
	SPI_SendDate(addr>>8);
	SPI_SendDate(addr);
	CS_H;
	//�ȴ�ͨ����״̬�Ĵ������ȴ�ָ��ִ�����
	W25Q64_ReadStatus();
	
}

/***************************************

��������W25Q64_Block_Erase()
����������
��������ֵ��
�������ܣ�W25Q64��ʹ��
����������
 
****************************************/
void W25Q64_Block_Erase(u32 addr)
{
	W25Q64_WriteEnable();
  CS_L;
	//��MCU������������ָ��
	SPI_SendDate(0xD8);
	SPI_SendDate(addr>>16);
	SPI_SendDate(addr>>8);
	SPI_SendDate(addr);
	CS_H;
	//�ȴ�ͨ����״̬�Ĵ������ȴ�ָ��ִ�����
	W25Q64_ReadStatus();
	
}
/***************************************

��������W25Q64_Chip_Erase()
����������
��������ֵ��
�������ܣ�W25Q64��ʹ��
����������
 
****************************************/
void W25Q64_Chip_Erase()
{
	W25Q64_WriteEnable();
  CS_L;
	//��MCU������������ָ��
	SPI_SendDate(0xC7);
	CS_H;
	//�ȴ�ͨ����״̬�Ĵ������ȴ�ָ��ִ�����
	W25Q64_ReadStatus();
	
}

/***************************************

��������W25Q64_ReadStatus()
����������
��������ֵ��
�������ܣ�W25Q64��״̬
����������
busy =0 ִ�����
busy =1 ����ִ��
 
****************************************/
void W25Q64_ReadStatus()
{
	u8 status;
	CS_L;
	//����һ����״ָ̬��
	SPI_SendDate(0x05);
	do{
	  status=SPI_ReceiveDate();
	}while((status & (1<<0))==1);
	
   CS_H;
}

