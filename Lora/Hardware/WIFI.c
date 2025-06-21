#include "stm32f10x.h"
#include "serial.h"
#include "WIFI.h"
#include "OLED.h"
#include "delay.h"
#include <string.h>
#include <stdbool.h>
uint8_t Recieved_String_Size;
char WIFI_temp[500];
static int tried_times=0;
uint8_t data_ready_flag;

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
       
			
			
				DMA_SetCurrDataCounter(DMA1_Channel6, 500);
			
			
				String_Copy(Recieve_String,WIFI_temp,Recieved_String_Size+1);
			Recieve_String[Recieved_String_Size]='\0';
				DMA_Cmd(DMA1_Channel6, ENABLE);
			data_ready_flag = 1; 
     
    }
		
	
		
}




int Wait_or_Found(uint16_t timeout_ms, const char *target)
{
    char temp_buf[128] = {0};

    for (uint16_t elapsed = 0; elapsed < timeout_ms; elapsed += 5)
    {
        if (data_ready_flag)
        {
            data_ready_flag = 0;

            __disable_irq();
            strncpy(temp_buf, Recieve_String, sizeof(temp_buf) - 1);
            __enable_irq();

            if (strstr(temp_buf, "ERROR")) return 2;
            if (strstr(temp_buf, "busy")) continue;
            if (strstr(temp_buf, target)) return 1;
        }

        Delay_ms(5);
    }

    return 0;
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
	  WIFI_SendString("+++");
    Delay_ms(80); 
    WIFI_SendString("+++");
    Delay_ms(80);
    tried_times++;
    if (tried_times > 5)
    {
        OLED_ShowString(1,1,"Too many retries");
        return 0;
    }

   // OLED_ShowString(1,1,"Connecting...");

    Recieve_String[0] = '\0';
    WIFI_SendString(Check_AT);
    if (!Wait_or_Found(1000, "OK")) return 0;

    WIFI_SendString(Change_CIPMODE);
    if (!Wait_or_Found(1000, "OK")) return 0;

    WIFI_SendString(Connect_To_Server);
    if (!Wait_or_Found(3000, "CONNECT")) return 0;

    WIFI_SendString(Connection_Status);
    if (!Wait_or_Found(1000, "STATUS:")) return 0;

    char *p = strstr(Recieve_String, "STATUS:");
    if (!p) return Connect_Server(); 

    int Status = *(p + 7) - '0';
    if (Status == 3)
    {
        tried_times = 0;
        return 1;
    }
    else if (Status == 5)
    {
        return Join_AP();
    }

    return 0;
}


	
	int check_AP_Connection()
{
   
    WIFI_SendString(Check_AT);
    if (!Wait_or_Found(1000, "OK")) return 0;

    
    WIFI_SendString(Connection_Status);
    if (!Wait_or_Found(1000, "STATUS:")) return Connect_Server();

   
    char *p = strstr(Recieve_String, "STATUS:");
    if (!p) return Connect_Server();

    int Status = *(p + 7) - '0';

    switch (Status)
    {
        case 1:
					 
        case 5:
					
            return 0;
        default:
            return 1; 
    }
}
	
	
	
	
	
	

/*void Send_Http(Data* data)
	
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
			
			}	
	
}

*/




int Send_Http(Data* data)
{

    int statu = Connect_Server();
    if (statu != 1) return 0;

    char json[200];
	
	
   int json_len = snprintf(json, sizeof(json),
    "{\"CO2_concentration\":%d,"
    "\"ID\": %d,"
    "\"Record_Time\": \"%s\","
    "\"Light_time\": %d,"
    "\"Soil_humidity\":  %d,"
    "\"Soil_temperature\":  %d,"
    "\"Air_humidity\": %d,"
    "\"Air_temperature\": %d}",
    data->CO2_concentration,
    data->ID,
    data->Record_Time,
    data->Light_time,
    data->Soil_humidity,
    data->Soil_temperature,
    data->Air_humidity,
    data->Air_temperature);



    char http[512];
    int http_len = snprintf(
        http, sizeof(http),
        "POST /postdata HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        "8.208.52.104", json_len, json
    );

    WIFI_SendString(CIP_Send);
    if (Wait_or_Found(2000, ">") != 1) {
        OLED_ShowString(1, 1, "Send Cmd Fail");
        return 2;
    }

     //清空接收缓冲（避免上次响应影响）
    Recieve_String[0] = '\0';
    data_ready_flag = 0;

    WIFI_SendString(http);

     //等待 服务器返回 "200 OK"
    int result = Wait_or_Found(5000, "200 OK");

    if (result == 1) {
        //OLED_ShowString(1, 1, "HTTP 200 OK     ");
          WIFI_SendString("+++");
    Delay_ms(80); 
    WIFI_SendString("+++");
    Delay_ms(80);
        return 1;
    } else if (result == 2) {
        OLED_ShowString(1, 1, "Server Error    ");
          WIFI_SendString("+++");
    Delay_ms(80); 
    WIFI_SendString("+++");
    Delay_ms(80);
        return 3;
    } else {
        OLED_ShowString(1, 1, "No Response     ");
          WIFI_SendString("+++");
    Delay_ms(80); 
    WIFI_SendString("+++");
    Delay_ms(80);
        return 4;
    }
}

int Get_Time_Stamp()
{
    Recieve_String[0] = '\0';

   
    WIFI_SendString("+++");
    Delay_ms(80); 
    WIFI_SendString("+++");
    Delay_ms(80);

   
    Recieve_String[0] = '\0';
    WIFI_SendString(Disconnect_To_Server);
    if (!Wait_or_Found(1000, "OK"))
    return 2;

   
    Recieve_String[0] = '\0';
    WIFI_SendString(Change_CIPMODE);
    if (!Wait_or_Found(2000, "OK")) return 2;

   
    Recieve_String[0] = '\0';
    WIFI_SendString(Connect_To_Time_Server);
    if (!Wait_or_Found(3000, "CONNECT"))
    {
       
        return 2;
    }

 

 
    Recieve_String[0] = '\0';
    WIFI_SendString(CIP_Send);
    if (!Wait_or_Found(2000, "OK"))
        return 3;

   

   
    Recieve_String[0] = '\0';
    WIFI_SendString(Get_Time_From_Internet);

    if (!Wait_or_Found(3000, "server_time"))
    {
      
			
        return 4;
    }

    
    unsigned long long ms = 0ULL;
    if (sscanf(Recieve_String, "{\"server_time\":%llu}", &ms) != 1)
    {
        
        return 5;
    }

   
    uint32_t cnt = (uint32_t)(ms / 1000ULL) - 7 * 3600; // 东八区偏移
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_EnterConfigMode();
    RTC_SetCounter(cnt);
    RTC_ExitConfigMode();
    RTC_WaitForLastTask();
    PWR_BackupAccessCmd(DISABLE);

    OLED_ShowString(1, 1, "Time OK");
    
    WIFI_SendString("+++");
    Delay_ms(50);
    WIFI_SendString("+++");
    Delay_ms(50);
    WIFI_SendString(Disconnect_To_Server);
    Delay_ms(100);

    return 1; 
}





	














