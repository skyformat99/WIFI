#include "includes.h"
/**
	1���жϷ���
	2��д��������ռֵ����Ӧֵ
	3���Ѿ������ռֵд�뵽�Ĵ���
	4��ʹ��
**/

/******************************************
��������MY_NVIC_init
����������
u8 group :�жϷ���ֵ  д��Ĳ���Ϊ��7-����
    ���� ��Χ�� 0---4
u8 PreemptVal :�������ռ���ȼ���ֵ
u8 SubVal  : �������Ӧ���ȼ���ֵ
IRQn_Type IRQn : �����ĸ��жϵ��жϺ�
��������ֵ����
�������ܣ�ʵ���Զ����NVIC�жϴ������ú���
*******************************************/
void My_NVIC_Init(u8 group, u8 PreemptVal, u8 SubVal, IRQn_Type IRQn )
{
	u8 priority;//��ʾ��ռ����Ӧ�ĺϳ�ֵ
	//�����жϷ���ֵ
	SCB->AIRCR &=~(((unsigned int)0XFFFF<<16)|(0X7<<8));//����
	SCB->AIRCR |=(0X5FA<<16 | group <<8);
	//���þ������ռ����Ӧ��ֵ
	priority =((PreemptVal & ((1<<(7-group))-1))<<(group-3)) |(SubVal &((1<<(group-3))-1));
	//����ռ����Ӧ�ϳ�ֵд��Ĵ���
	NVIC->IP[(uint32_t)(IRQn)] = (priority << 4);    
  //�жϺ�ʹ��
	NVIC->ISER[(uint32_t)((int32_t)IRQn) >> 5] = (uint32_t)(1 << ((uint32_t)((int32_t)IRQn) & (uint32_t)0x1F)); 

}




