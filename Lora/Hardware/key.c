#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
void Key_Init()
	
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOB,&GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
	{
	uint8_t KeyNum;
		
		while(1){
		
	if(	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0)
	{	
	Delay_ms(20);
	
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0);
		
		Delay_ms(20);
		KeyNum=1;
	break;
	}
		
	if(	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
	Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		KeyNum=2;
		break;
}
	
}
		
		return KeyNum;
	
	}
	


	