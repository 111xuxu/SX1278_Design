#include "stm32f10x.h"                
#include "delay.h"
#include "Menu.h"

uint8_t Cursor_position=1;
uint8_t Cursor_choice=1;
void Setting_Menu();
void Menu()	;
int Server_Status=0;
void Parameter_Menu();

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