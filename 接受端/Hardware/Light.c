#include "stm32f10x.h"  
#include "Light.h"

void Light_Init()
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA,&GPIO_InitStructure);


	
		
	
	
	
}

int Get_Light()
{

return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);

}
