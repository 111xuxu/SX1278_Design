
#include "stm32f10x.h"                  // Device header
void LED_Init(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_4);
	}
	
	void Led1_on(void)
	{
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	}
	
	void Led1_off(void)
	{
	
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	}
	void Led2_on(void)
	{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	
	void Led2_off(void)
	{
	
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	
	void Led1_Turn(void)
		
	{
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
		
		{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)
		{GPIO_ResetBits(GPIOA,GPIO_Pin_1);}
	}
	
		void Led2_Turn(void)
		
	{
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
		
		{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==1)
		{GPIO_ResetBits(GPIOA,GPIO_Pin_2);}
	}