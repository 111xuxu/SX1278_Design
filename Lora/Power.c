#include "stm32f10x.h"                  // Device header
#define MAGIC_WORD  0xA5A5
#define BKP_MAGIC   BKP->DR1
#define BKP_CNT_L   BKP->DR2
#define BKP_CNT_H   BKP->DR3
void Power_Init()
{
 RCC->APB2ENR = RCC_APB2Periph_AFIO;  
    RCC->APB2ENR = 0;

    /* 2) 把所有 GPIO（A~E）都设成模拟输入，断开上下拉，降低漏电 */
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA 
                 | RCC_APB2Periph_GPIOB
                 | RCC_APB2Periph_GPIOC
                 | RCC_APB2Periph_GPIOD
                 | RCC_APB2Periph_GPIOE;
    GPIO_InitTypeDef gpio = {
        .GPIO_Pin   = GPIO_Pin_All,
        .GPIO_Mode  = GPIO_Mode_AIN,
    };
    GPIO_Init(GPIOA, &gpio);
    GPIO_Init(GPIOB, &gpio);
    GPIO_Init(GPIOC, &gpio);
    GPIO_Init(GPIOD, &gpio);
    GPIO_Init(GPIOE, &gpio);

RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

/*RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);


GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPD;
GPIO_Init(GPIOB, &GPIO_InitStruct);


GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);


EXTI_InitTypeDef EXTI_InitStruct;
EXTI_InitStruct.EXTI_Line    = EXTI_Line5;
EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发
EXTI_InitStruct.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStruct);


NVIC_InitTypeDef NVIC_InitStruct;
NVIC_InitStruct.NVIC_IRQChannel                   = EXTI9_5_IRQn;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0;
NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
NVIC_Init(&NVIC_InitStruct);
*/



}

void Power_Stop_Mode()
	
{
PWR->CR &= ~(PWR_CR_PDDS);
PWR->CR |= PWR_CR_LPDS;


SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
__WFI();

}



void Power_Stand_By_Mode()
	
{
PWR->CR |= PWR_CR_CSBF;   
PWR->CR |= PWR_CR_CWUF;   


PWR->CR |= PWR_CR_PDDS;

SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;


__WFI();
}



void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
}


void ResetSystemClock(void)
{
    
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

   
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);
 
    SystemCoreClockUpdate();

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1) { }
    }
}


int Check_Power_Off()
{
    return (RCC->BDCR & RCC_BDCR_RTCEN) ? 0 : 1;
}


