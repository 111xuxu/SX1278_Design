#include "stm32f10x.h"                  // Device header
#include "delay.h"
uint8_t RxDa;

uint8_t RxFlag;//接收标志位
uint8_t TxPacket[4];//输出数据缓存区
uint8_t RxPacket[4];//输入数据缓存区
extern char Recieve_String[500];
char temp[500];
uint8_t Recieved_String_Size;

void MYUSART_Init()
{	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate =9600 ;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode =USART_Mode_Tx|USART_Mode_Rx ;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b ;
	
	USART_Init(USART1,&USART_InitStructure);
	
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1,ENABLE);
}

void USART_SendByte(uint8_t Byte)
{
USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

}


void USART_SendArray(uint8_t *Array,uint16_t Length)

{
	uint16_t i;
for(i=0;i<Length;i++)
	{USART_SendByte(Array[i]);}


}

void USART_SendString(char *string)
	
{
uint16_t i;
	for(i=0;string[i]!=0;i++)
	{USART_SendByte(string[i]);}



}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{

uint32_t Result=1;
	while(Y--)
	{
	Result *=X;
	}
return Result;
}

void USART_SendNumber(uint32_t Number,uint8_t Length)
{
uint16_t i;
for(i=0;i<Length;i++)
	{
	USART_SendByte(Number/Serial_Pow(10,Length-i-1)%10 +'0');
	
	}


}
uint8_t GetRxFlag(void)
{
if (RxFlag==1)
	{
		RxFlag=0;
		return 1;
	}
	return 0;

}

uint8_t GetRxData(void)
{return RxDa;}


void String_Copy(char *dest,char *src,int length)
{
	uint16_t i=0;
while (*src != '\0'&&i<length)
    {
        if ((*src != 0x0D) && (*src != 0x0A)) 
        {
            *dest++ = *src;
					
        }
        
        src++;
				i++;
    }
    *dest = '\0';




}

void USART1_IRQHandler(void)
{
	

		if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        (void)USART1->SR;
        (void)USART1->DR;
        USART_ClearITPendingBit(USART1, USART_IT_IDLE);
			
				Recieved_String_Size= 500-DMA_GetCurrDataCounter(DMA1_Channel5);
				DMA_Cmd(DMA1_Channel5, DISABLE);
        temp[Recieved_String_Size]='\0';
			
			
				DMA_SetCurrDataCounter(DMA1_Channel5, 500);
			
			
String_Copy(Recieve_String,temp,Recieved_String_Size);
				DMA_Cmd(DMA1_Channel5, ENABLE);
			
     
    }
		
	
		
}


