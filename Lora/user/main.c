#include "stm32f10x.h"                
#include "delay.h"	
#include "WIFI.h"
#include <string.h>  
#include "SD_Card.h"
extern uint16_t CO2[6];
uint16_t CO2_Concentration=0;
uint8_t temperature;
uint8_t humi;
extern uint16_t MyRTC_Time[];
uint8_t test[];
uint8_t SD_Recieve_buffer[512];
uint8_t SD_Write_buffer[512];

/*在FIFO中一共有三个指针，分别是发送缓冲区的基地址（0x0E），接受缓冲区的基地址（0x0F），
以及访问0x0D也就是FIFO时开始的地址*/
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
/*                            结合                       */
int Wait_or_Found(uint16_t ms,char *str){
	
for(int i=0;i<ms;i++)
{
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
	NVIC_DisableIRQ(USART2_IRQn);
char *p=strstr(Recieve_String,str);
	NVIC_EnableIRQ(USART2_IRQn);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	if(p) return 1;
	
	Delay_ms(1);
	
}
return 0;
}


uint8_t Get_Tem_Hum()
{
DHT11_Read_Data(&temperature,&humi);
Delay_ms(10);
DHT11_Read_Data(&temperature,&humi);
return 1;
}


uint16_t Get_CO2()
{
CO2_Concentration=CO2[1]*256+CO2[2];
	return CO2_Concentration;
}



int main(void)

{
	
	//GPIO_WriteBit(GPIOA, GPIO_Pin_12, 1);
	OLED_Init();
	
	/*OLED_ShowNum(1,1,23,2);
	Power_Init();
	
	Delay_s(3);
	Power_Stop_Mode();
	ResetSystemClock();
	*/
	
	Key_Init();
	DHT11_Init();
	MYUSART_Init();
	Wifi_USART_Init();
	MYDMA_Init();
	MySPI_Init();
	SX1278_Init();
	SX1278_Basic_Setting(128);
	Light_Init();
	Soil_Humidity_Init();
	
	MyRTC_Init(); 
	OLED_Clear();
	SD_Initialize();
	/*Get_Time_Stamp();
	while (1)
	{
		MyRTC_ReadTime();
		
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);
		OLED_ShowNum(1, 14, MyRTC_Time[2], 2);
		
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}*/
	
	//Delay_ms(500);
	
	//OLED_ShowNum(2,1,SD_Initialize(),3);
	/*MySPI_SD_Start();
	SD_SendCommand(CMD8,0x1AA,0x87);
	MySPI_SD_Stop();*/
	


 
//SD_WriteSector(2,SD_Write_buffer);
 



//SD_ReadSector(2,SD_Recieve_buffer);



	
	//	Delay_ms(500);
	//OLED_ShowNum(2,1,SD_Initialize(),3);

	//Delay_ms(2000);

	/*Data *data= (Data*)malloc(sizeof (Data));
	
	data->CO2_concentration=120;
	data->ID=15;
	data->Light_time=1;
	data->Soil_humidity=15;
	data->Soil_temperature=16;
	data->Air_humidity=17;
	data->Air_temperature=18;
	Send_Http(data);
	data->CO2_concentration=120;
	data->ID=13;
	data->Light_time=0;
	data->Soil_humidity=35;
	data->Soil_temperature=36;
	data->Air_humidity=37;
	data->Air_temperature=38;
	Send_Http(data);
  free(data);
	*/
	
	Welcome_menu();
	while(Key_GetNum()==0);
	OLED_Clear();
	Menu();

}




