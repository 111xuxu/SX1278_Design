
#include "stm32f10x.h"                  // Device header
extern char WIFI_temp[500];


void MYDMA_Init(){

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
DMA_DeInit(DMA1_Channel6);


DMA_InitTypeDef DMA_InitStructure;
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR); // 外设地址：USART2->DR
DMA_InitStructure.DMA_MemoryBaseAddr    = (uint32_t)WIFI_temp;      // 内存地址：自定义缓冲区
DMA_InitStructure.DMA_DIR               = DMA_DIR_PeripheralSRC;    // 方向：外设->内存
DMA_InitStructure.DMA_BufferSize        = 500;         // 缓冲区大小（单位：传输元素个数）
DMA_InitStructure.DMA_PeripheralInc     = DMA_PeripheralInc_Disable;// 外设地址不自增
DMA_InitStructure.DMA_MemoryInc         = DMA_MemoryInc_Enable;     // 内存地址自增
DMA_InitStructure.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;
DMA_InitStructure.DMA_MemoryDataSize    = DMA_MemoryDataSize_Byte;
DMA_InitStructure.DMA_Mode              = DMA_Mode_Circular;        // 循环模式(环形缓冲)，或 DMA_Mode_Normal
DMA_InitStructure.DMA_Priority          = DMA_Priority_Medium;
DMA_InitStructure.DMA_M2M               = DMA_M2M_Disable;

DMA_Init(DMA1_Channel6, &DMA_InitStructure);

DMA_Cmd(DMA1_Channel6, ENABLE);


USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

}
