#include "stm32f10x.h"
#include "serial.h"
#include "WIFI.h"
#include "OLED.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>
uint8_t Recieved_String_Size;
char WIFI_temp[500];
static int tried_times=0;
void  Wifi_USART_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate =9600 ;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode =USART_Mode_Tx|USART_Mode_Rx ;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b ;
	
	USART_Init(USART2,&USART_InitStructure);

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2,ENABLE);




}
	

void WIFI_SendByte(uint8_t Byte)
{
USART_SendData(USART2,Byte);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);

}


void WIFI_SendArray(uint8_t *Array,uint16_t Length)

{
	uint16_t i;
for(i=0;i<Length;i++)
	{WIFI_SendByte(Array[i]);}


}

void WIFI_SendString(char *string)
	
{
uint16_t i;
	for(i=0;string[i]!=0;i++)
	{WIFI_SendByte(string[i]);}



}

uint32_t WIFI_Serial_Pow(uint32_t X,uint32_t Y)
{

uint32_t Result=1;
	while(Y--)
	{
	Result *=X;
	}
return Result;
}

void WIFI_SendNumber(uint32_t Number,uint8_t Length)
{
uint16_t i;
for(i=0;i<Length;i++)
	{
	WIFI_SendByte(Number/WIFI_Serial_Pow(10,Length-i-1)%10 +'0');
	
	}


}



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

void USART2_IRQHandler(void)
{
	

		if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        (void)USART2->SR;
        (void)USART2->DR;
        USART_ClearITPendingBit(USART2, USART_IT_IDLE);
			
				Recieved_String_Size= 500-DMA_GetCurrDataCounter(DMA1_Channel6);
				DMA_Cmd(DMA1_Channel6, DISABLE);
        WIFI_temp[Recieved_String_Size]='\0';
			
			
				DMA_SetCurrDataCounter(DMA1_Channel6, 500);
			
			
String_Copy(Recieve_String,WIFI_temp,Recieved_String_Size);
				DMA_Cmd(DMA1_Channel6, ENABLE);
			
     
    }
		
	
		
}



void Show_Recieved_WIFI_Data()

{
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(1, i+1, Recieve_String[i]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(2, i+1, Recieve_String[i+15]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(3, i+1, Recieve_String[i+30]);
	}
	for(int i=0;i<15;i++)
	{
OLED_ShowChar(4, i+1, Recieve_String[i+45]);
	}


}

int Join_AP(){


WIFI_SendString(Join_Ap);
	
	if(tried_times++>=5){
		OLED_ShowString(1,1,"No AP Connection");
		return 0;
	}
Delay_s(3);
	Connect_Server();
	return 1;
}


int Connect_Server()
	
{
	Recieve_String[0] = '\0';
		
		OLED_ShowString(1,1,"Connecting...");
		WIFI_SendString(Check_AT);
	Delay_ms(200);

		WIFI_SendString(Change_CIPMODE);
	Delay_ms(200);
	WIFI_SendString(Connect_To_Server);
	Delay_ms(200);
	
	
	WIFI_SendString(Connection_Status);
	Delay_ms(200);
	
	
	char *p=strstr(Recieve_String,"STATUS:");
	if(!p)
		Connect_Server();
	
	p+=7;
	
	int Status=(int)*p-'0';
	
	switch (Status){
		case 3:
			tried_times=0;
					return 1;
					
		case 5:
			if(Join_AP()==0)
		return 0;
		
	}
	
	}

	
	int check_AP_Connection()
	{
	
	Recieve_String[0] = '\0';
		WIFI_SendString(Check_AT);
	Delay_ms(200);
	WIFI_SendString(Connection_Status);
	Delay_ms(200);
	
	
	char *p=strstr(Recieve_String,"STATUS:");
	if(!p)
		Connect_Server();
	
	p+=7;
	
	int Status=(int)*p-'0';
	
	switch (Status){
		case 1:
					return 0;
		case 5:
		return 0;
		default:
			return 1;
		
	}
	
	
	
	
	}
	

void Send_Http(Data* data)
	
{
	Delay_s(1);
	WIFI_SendString("+++");
	Delay_s(1);
	int statu=Connect_Server();
	if(statu==1)
	{
		
	char json[256];                  
 int json_len = snprintf(
        json, sizeof json,
        "{\"CO2_concentration\": %f,"
        "\"ID\": %d,"
        "\"Light_time\": %f,"
        "\"Soil_humidity\":%f,"
        "\"Soil_temperature\": %f,"
        "\"Air_humidity\":%f,"
        "\"Air_temperature\":%f}",
        data->CO2_concentration,
				data->ID,
				data->Light_time,
				data->Soil_humidity,
				data->Soil_temperature,
				data->Air_humidity,
				data->Air_temperature
				);

char http[512];
    int http_len = snprintf(
        http, sizeof http,
        "POST /postdata HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        "8.208.52.104", json_len, json);
				WIFI_SendString(CIP_Send);
				Delay_ms(500);
				WIFI_SendString(http);
				Delay_ms(1000);
				WIFI_SendString("+++");
				//char *p=strstr(Recieve_String,"success");
				
				
				
				
			}
	
		
	
				
	
}






	














