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
#include "Led.h"
#include "WIFI.h"
void Menu();
void Parameter_Menu();
void Setting_Menu();
char FIFO_Buffer[256];
extern uint16_t CO2[6];
uint16_t CO2_Concentration=0;
uint8_t temperature;
	uint8_t humi;
uint8_t Cursor_position=1;
uint8_t Cursor_choice=1;
int Server_Status=0;
char Buffer[128]={
0x12, 0x34, 0x56, 0x00, 0x5f, 0x11, 0xed, 0x4b, 0xd2, 0xee, 0x95, 0xe2, 0x24, 0x35, 0x74, 0x79,  
0xe4, 0x82, 0xc1, 0x48, 0x9c, 0x6c, 0x08, 0x2f, 0x3c, 0xa5, 0xfb, 0x73, 0xdf, 0x2e, 0x31, 0xf8,  
0x08, 0xd6, 0x07, 0x9f, 0x5a, 0xd4, 0x5e, 0x4e, 0x72, 0x01, 0x7a, 0x69, 0xd3, 0x12, 0x09, 0xe5,  
0x62, 0x36, 0x39, 0xdb, 0xc2, 0x68, 0x82, 0x27, 0x48, 0x4a, 0x18, 0x6b, 0xb8, 0x31, 0x06, 0xaf,
0x12, 0x34, 0x56, 0x4f, 0x5f, 0x11, 0xed, 0x4b, 0xd2, 0xee, 0x95, 0xe2, 0x24, 0x35, 0x74, 0x79,  
0xe4, 0x82, 0xc1, 0x48, 0x9c, 0x6c, 0x08, 0x2f, 0x3c, 0xa5, 0xfb, 0x73, 0xdf, 0x2e, 0x31, 0xf8,  
0x08, 0xd6, 0x07, 0x9f, 0x5a, 0xd4, 0x5e, 0x4e, 0x72, 0x01, 0x7a, 0x69, 0xd3, 0x12, 0x09, 0xe5,  
0x62, 0x36, 0x39, 0xdb, 0xc2, 0x68, 0x82, 0x27, 0x48, 0x4a, 0x18, 0x6b, 0xb8, 0x31, 0x06, 0xaf  
};





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
char *menu[]={
									"Start",
									"Setting",
									"Test",
									"Mode",
									"Information",
									"Basic setting",
									"Sending Test",
									"WIFI"
};

char *Setting[]={
									"Parameter",
									"back",
	

};
									
char *parameter[]={
									"BandWidth",
									"Header",
									"Power",
									"CR",
									"Back"

};

char *BW[]={
									"7.8KHZ",
									"10.4KHZ",
									"15.6KHZ",
									"20.8KHZ",
									"31.25KHZ",
									"41.7KHZ",
									"62.5KHZ",
									"125KHZ",
									"250KHZ",
									"500KHZ",
									"Back"

};
char *CR[]={
									"4/5",
									"4/6",
									"4/7",
									"4/8",
									"Back"
									

};
char *HEADER[]={
									"ON",
									"OFF",
									"Back"
									
									

};
char *POWER[]={
									"2dBm",
									"3dBm",
									"4dBm",
									"5dBm",
									"6dBm",
									"7dBm",
									"8dBm",
									"9dBm",
									"10dBm",
									"11dBm",
									"12dBm",
									"13dBm",
									"14dBm",
									"15dBm",
									"16dBm",
									"17dBm",
									"Back"
									
									

};



void Set_Cursor(uint8_t	i)
{
	OLED_ShowString(1,1," ");
	OLED_ShowString(2,1," ");
	OLED_ShowString(3,1," ");
	OLED_ShowString(4,1," ");
	OLED_ShowString(i,1,">");


}

void Welcome_menu()
{
	OLED_ShowString(1,1,"  Welcome to    ");
	OLED_ShowString(2,1,"     LoRa       ");
	OLED_ShowString(3,1,"    Press to    ");
	OLED_ShowString(4,1,"    continue    ");
}


void Show_Wifi_Status()
{
	OLED_SetCursor(0, 120); 
	if(Server_Status){
    for (uint8_t i = 0; i < 8; i++) { // 连续 8 列
        OLED_WriteData(0xFF);         // 0xFF = 8 个像素全亮
    }
	}
	else{
	
	for (uint8_t i = 0; i < 8; i++) { // 连续 8 列
        OLED_WriteData(0x00);         // 0xFF = 8 个像素全亮
    }
	}

}

uint8_t Show_Menu(char *Menu[],uint8_t rows)
{
	
uint8_t j=0;
	OLED_Clear();
	Cursor_position=1;
	Cursor_choice=1;
	while(1)
	{
		Show_Wifi_Status();
		OLED_ShowNum(4,14,Cursor_choice,2);
		for(int i=0;i<4&& (i + j) < rows;i++)
	{
	OLED_ShowString(i+1,2,Menu[i+j]);
	}
	
	Set_Cursor(Cursor_position);
	if(Key_GetNum()==2)
		{
			
		Cursor_choice++;
		Cursor_position++;
			
			
			if(Cursor_position==rows+1)
			{
			Cursor_position=1;
			Cursor_choice=1;
			}	
			
		if(Cursor_position==5)
		{
			Cursor_position=4;
		j++;	
			if(j==(rows-3))
			{
			j=0;
			Cursor_position=1;
				Cursor_choice=1;
			}
			
			OLED_Clear();
		}
		
		
		
	}
		
	else 
	{
	
	OLED_Clear();
		OLED_ShowNum(1,1,Cursor_choice,3);
		return Cursor_choice;

	}


}
	


	}

	void HEADER_Menu()
	{
	switch (Show_Menu(HEADER,sizeof(HEADER) / sizeof(HEADER[0])))
	{
		case 1:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xFE)|0x00));
		break;
		case 2:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xFE)|0x01));
		break;
		
			
	}	
	Parameter_Menu();
	//Get_Basic_Setting();
	}
	
	void BW_Menu()

{
	SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|((Show_Menu(BW,sizeof(BW) / sizeof(BW[0]))-1)<<4)));

		Parameter_Menu();

//Get_Basic_Setting();
	}

		void CR_Menu()

{
	
	SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(Show_Menu(CR,sizeof(CR) / sizeof(CR[0]))<<1)));

		Parameter_Menu();
		//Get_Basic_Setting();
	}

	
void	Power_Menu()
	
{
	
SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|(Show_Menu(POWER,sizeof(POWER) / sizeof(POWER[0]))-1)));
	Parameter_Menu();
}
	
void	INFORMATION_Menu()
{
OLED_ShowString(1,1,"Version:1.0");
	while(Key_GetNum()==0);


}
	
void Parameter_Menu()
{

switch (Show_Menu(parameter,sizeof(parameter) / sizeof(parameter[0])))
		{
		case 1:
			BW_Menu();
			break;
		case 2:
			HEADER_Menu();
			break;
		case 3:
			Power_Menu();
			break;
		case 4:
			CR_Menu();
			break;
		
		
		
			
}
			Setting_Menu();

}
void Setting_Menu()
{
switch (Show_Menu(Setting,sizeof(Setting) / sizeof(Setting[0])))
		{
		case 1:
			Parameter_Menu();
			break;	
}
Menu();
	}



void Test()
{
long recieved_times=0;
if(SX1278_ReadReg(0x42)!=0x12)
		OLED_ShowString(1,1,"Error");
		Get_Basic_Setting();
OLED_Clear();
while(1)
{
	
	Recieve_Data();
  SX1278_WriteReg(FIFO_Pointer,Recieve_Buffer_Start);
	for (int i=1;i<5;i++)
	{
		for(int j=0;j<5;j++)
			{
			OLED_ShowHexNum(i,1+j*3,SX1278_ReadReg(0x00),2);
		
			}
	}
	
OLED_ShowNum(1,1,recieved_times,3);
	recieved_times++;

		//if(Key_GetNum()!=0)
	//break;
}
	
	OLED_Clear();
	
		
	SX1278_WriteReg(FIFO_Pointer,0x00);
	
	for(int i=0;i<256;i++)
	{
	FIFO_Buffer[i]=SX1278_ReadReg(0x00);
	}
Menu();
}

void Sending_test()
{

unsigned int j;

SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
		while(1){
			SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
			for (int i=0;i<128;i++)
		{
		SX1278_WriteReg(0x00,Buffer[i]);
		}
		
		OLED_ShowString(1,1,"                ");
	OLED_ShowString(1,1,"Sending Data");
			
	OLED_ShowNum(3,13,j,3);
		j++;	
	SX1278_WriteReg(FIFO_Pointer,Send_Buffer_Start);
	OLED_ShowHexNum(3,1,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,4,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,7,SX1278_ReadReg(0x00),2);
	OLED_ShowHexNum(3,10,SX1278_ReadReg(0x00),2);
				if(Send_Data(128)==1)
		OLED_ShowString(4,1,"Send Success");
			
	Buffer[3]++;
}

}


void Menu()	
{
	switch (Show_Menu(menu,sizeof(menu) / sizeof(menu[0])))
		{
		case 1:
			//Start();
			break;
		case 2:Setting_Menu();
			break;
		case 3:
			Test();
		break;
		case 5:
			INFORMATION_Menu();
		Menu();
			break;
		case 6:
			Get_Basic_Setting();
	Menu();
		case 7:
			Sending_test();
		case 8:
			
			if(Connect_Server())
				Server_Status=1;
			else 
				Server_Status=0;
		Menu();
		
		break;
}

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
	


	
	/*while(1)
	{
		OLED_ShowNum(1,5,1111,4);
	OLED_ShowNum(2,5,AD_GetValue(ADC_Channel_0),4);
	OLED_ShowNum(1,1,Get_Light(),2);

	
Get_Tem_Hum();
	OLED_ShowNum(3,1,temp,2);
		OLED_ShowNum(4,1,humi,2);
	OLED_ShowNum(4,5,Get_CO2(),4);
	}
	*/
	
	/*while(1)
	{
	Get_CO2();
Get_Tem_Hum();
	OLED_ShowNum(1,1,temp,2);
		OLED_ShowNum(2,1,humi,2);
		OLED_ShowHexNum(3,1,CO2[0],2);
		OLED_ShowHexNum(3,4,CO2[1],2);
		OLED_ShowHexNum(3,7,CO2[2],2);
		OLED_ShowNum(4,1,CO2_Concentration,4);
	}
	*/

	/*while(1)
	{
		 Get_Tem_Hum();
	OLED_ShowNum(1,1,temp,2);
		OLED_ShowNum(2,1,humi,2);
	
	}*/
	
	Welcome_menu();
	while(Key_GetNum()==0);
	OLED_Clear();
	Menu();
	
  
	
	

	

	
}

