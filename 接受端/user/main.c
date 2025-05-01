#include "stm32f10x.h"                
#include "delay.h"
#include "serial.h"
#include "OLED.h"
#include "SX1278.h"
#include "My_spi.h"
#include "SX1278_Reg_Define_Table.h"
#include <string.h>
#include "Key.h"
#include "stdio.h"
#include "CO2.h"    
#include "Light.h"
#include "Soil_Humidity.h"
#include "WIFI.h"
#include <stdlib.h>


extern uint16_t CO2[6];
uint16_t CO2_Concentration=0;
uint8_t temperature;
uint8_t humi;



/*在FIFO中一共有三个指针，分别是发送缓冲区的基地址（0x0E），接受缓冲区的基地址（0x0F），
以及访问0x0D也就是FIFO时开始的地址*/
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */
/*                            接收端                               */

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
	
	OLED_Init();
	Key_Init();
	DHT11_Init();
	MYUSART_Init();
	Wifi_USART_Init();
	MYDMA_Init();
	SX1278_Init();
	Light_Init();
	Soil_Humidity_Init();
	SX1278_Basic_Setting(128);

	
	Data *data= malloc (sizeof (Data));
	
	data->CO2_concentration=120;
	data->ID=12;
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
	/*while(1)
	{
		OLED_ShowNum(1,5,1111,4);
	OLED_ShowNum(2,5,AD_GetValue(ADC_Channel_0),4);
	OLED_ShowNum(1,1,Get_Light(),2);

	
Get_Tem_Hum();
	OLED_ShowNum(3,1,temperature,2);
		OLED_ShowNum(4,1,humi,2);
	OLED_ShowNum(4,5,Get_CO2(),4);
	}*/
	
	Welcome_menu();
	while(Key_GetNum()==0);
	OLED_Clear();
	Menu();
	
  
	
	

	

	
}

