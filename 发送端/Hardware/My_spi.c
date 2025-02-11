#include "stm32f10x.h"                  // Device header
#include "My_spi.h"


void MySPI_W_SS(uint8_t Bitvalue)
{

GPIO_WriteBit(GPIOB,GPIO_Pin_15,(BitAction)Bitvalue);

}


void MySPI_W_SCK(uint8_t Bitvalue)
{

GPIO_WriteBit(GPIOB,GPIO_Pin_13,(BitAction)Bitvalue);

}

void MySPI_W_MOSI(uint8_t Bitvalue)
{

GPIO_WriteBit(GPIOB,GPIO_Pin_12,(BitAction)Bitvalue);

}

uint8_t MySPI_R_MISO(void)
{

return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);

}


void MySPI_Init(void)
	
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	MySPI_W_SS(1);
	MySPI_W_SCK(0);

}

void MySPI_Start(void)
{

MySPI_W_SS(0);

}

void MySPI_Stop(void)
{

MySPI_W_SS(1);

}



uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
uint8_t i,ByteRecieve=0x00;
	
	for(i=0;i<8;i++)
	
	{
	MySPI_W_MOSI(ByteSend & (0x80>>i));
	MySPI_W_SCK(1);
	if(MySPI_R_MISO()==1)
	{
	
	ByteRecieve|=(0x80>>i);
	}
	
	MySPI_W_SCK(0);
	}

	
	
	
	
	
return ByteRecieve;
 

}

