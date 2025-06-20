#ifndef __Menu_h
#define __Menu_h
             
#include "delay.h"
#include "OLED.h"
const static char *menu[]={
									"Start",
									"Setting",
									"Receive_Test",
									"Mode",
									"Information",
									"Basic setting",
									"Sending Test",
									"WIFI",
									"Sensor_Test",
									"Send_Sensor_data",
									"SD_Test",
									"Get_Time"
};

const static char *Setting[]={
									"Parameter",
									"back",
	

};
									
const static char *parameter[]={
									"BandWidth",
									"Header",
									"Power",
									"CR",
									"Back"

};

const static char *BW[]={
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
const static char *CR[]={
									"4/5",
									"4/6",
									"4/7",
									"4/8",
									"Back"
									

};
const static char *HEADER[]={
									"ON",
									"OFF",
									"Back"
									
									

};
const static char *POWER[]={
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

const static char *Start_Choose_Role[]={


	"Edge Device",
	"Central Device",
	"Back"
	
	
};

const static char *Choose_Device_ID[]={
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13"
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
	
	//if(Get_Time_Stamp());

	OLED_ShowString(1,1,"  Welcome to    ");
	OLED_ShowString(2,1,"     LoRa       ");
	OLED_ShowString(3,1,"   press to     ");
	OLED_ShowString(4,1,"   continue     ");
}


void Show_Wifi_Status(void);

uint8_t Show_Menu(char *Menu[],uint8_t rows);

void HEADER_Menu(void);

void BW_Menu(void);

void CR_Menu(void);
	
void Power_Menu(void);

void INFORMATION_Menu(void);
	
void Parameter_Menu(void);

void Setting_Menu(void);

void Menu(void);

void Receive_Test(void);

void Sending_test(void);

void Menu(void);
#endif



