#include "stm32f10x.h"                
#include "Menu.h"

uint8_t Cursor_position=1;
uint8_t Cursor_choice=1;
extern uint16_t CO2[6];

extern uint8_t temperature;
extern uint8_t humi;
void Setting_Menu(void);
void Menu(void)	;
int Server_Status=0;
void Parameter_Menu(void);

void Sensor_Test(void)
{
while(1)
	{
		OLED_ShowNum(1,5,1111,4);
	OLED_ShowNum(2,5,AD_GetValue(ADC_Channel_0),4);
	OLED_ShowNum(1,1,Get_Light(),2);

	Show_DS18B20_Tempreature(3,8);
Get_Tem_Hum();
	OLED_ShowNum(3,1,temperature,2);
		OLED_ShowNum(4,1,humi,2);
	OLED_ShowNum(4,5,Get_CO2(),4);
	}

}


void Show_Wifi_Status()
{
	OLED_SetCursor(0, 120); 
	if(Server_Status){
    for (uint8_t i = 0; i < 8; i++) { 
        OLED_WriteData(0xFF);        
    }
	}
	else{
	
	for (uint8_t i = 0; i < 8; i++) { 
        OLED_WriteData(0x00);         
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
		//OLED_ShowNum(4,14,Cursor_choice,2);
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
		//OLED_ShowNum(1,1,Cursor_choice,3);
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
	}
	
	void BW_Menu()

{
	const static char BW_Parameter[]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90};
	
	SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0x0F)|BW_Parameter[Show_Menu(BW,sizeof(BW) / sizeof(BW[0]))-1]));

		Parameter_Menu();


	}

void CR_Menu()

{
switch (Show_Menu(CR,sizeof(CR) / sizeof(CR[0])))
		{case 1:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x01<<1)));
			break;
			case 2:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x02<<1)));
			break;
			case 3:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x03<<1)));
			break;
			case 4:
			SX1278_WriteReg(0x1D,((SX1278_SwapByte(0x1D)&0xF1)|(0x04<<1)));
			break;
}
		Parameter_Menu();
	}

	
	
void	Power_Menu()
	
{
	const static char Power_Parameter[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
	
	SX1278_WriteReg(0x09,((SX1278_SwapByte(0x09)&0xF0)|Power_Parameter[Show_Menu(POWER,sizeof(POWER) / sizeof(POWER[0]))-1]));
	
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
			Receive_Test();
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
			
			if(check_AP_Connection())
				Server_Status=1;
			else 
				Server_Status=0;
		Menu();
		
		break;
		case 9:
			Sensor_Test();
}


}
