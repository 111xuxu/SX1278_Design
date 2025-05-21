
#include "stm32f10x.h"                  // Device header
extern char WIFI_temp[500];


void MYDMA_Init(){

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
DMA_DeInit(DMA1_Channel6);


DMA_InitTypeDef DMA_InitStructure;
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR); // �����ַ��USART2->DR
DMA_InitStructure.DMA_MemoryBaseAddr    = (uint32_t)WIFI_temp;      // �ڴ��ַ���Զ��建����
DMA_InitStructure.DMA_DIR               = DMA_DIR_PeripheralSRC;    // ��������->�ڴ�
DMA_InitStructure.DMA_BufferSize        = 500;         // ��������С����λ������Ԫ�ظ�����
DMA_InitStructure.DMA_PeripheralInc     = DMA_PeripheralInc_Disable;// �����ַ������
DMA_InitStructure.DMA_MemoryInc         = DMA_MemoryInc_Enable;     // �ڴ��ַ����
DMA_InitStructure.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;
DMA_InitStructure.DMA_MemoryDataSize    = DMA_MemoryDataSize_Byte;
DMA_InitStructure.DMA_Mode              = DMA_Mode_Circular;        // ѭ��ģʽ(���λ���)���� DMA_Mode_Normal
DMA_InitStructure.DMA_Priority          = DMA_Priority_Medium;
DMA_InitStructure.DMA_M2M               = DMA_M2M_Disable;

DMA_Init(DMA1_Channel6, &DMA_InitStructure);

DMA_Cmd(DMA1_Channel6, ENABLE);


USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

}
