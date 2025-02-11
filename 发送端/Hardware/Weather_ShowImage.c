#include "stm32f10x.h"                  // Device header
#include "TFT_Driver.h"
#include "GUI.h"
    #include "OLED.h"

extern unsigned char temp[256];
extern uint8_t PictureTemp[4096];
extern uint8_t Picture[11000];
extern int i,p;

void Refresh (uint8_t x,uint8_t y,uint8_t z,uint8_t w)
{
Lcd_SetRegion(x,y,x+z,y+w);	
		    for(i=0;i<z*w;i++)
			 {	
			 
LCD_WriteData_16Bit(0xff<<8|0xff);  					 
	}		


}
void Show_Sunny(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
	W25Q64_ReadData(0x000000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x001000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x002000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,79);

}

void Show_Windy(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x003000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x004000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x005000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,52);

}
void Show_Cloudy_Day(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x006000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x007000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x008000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,53);

}

void Show_Rainbow(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x009000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x00A000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x00B000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,47);

}

void Show_Cloudy_Night(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x00C000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x00D000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x00E000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,47);

}


void Show_Rain_Day(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x010000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x011000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x012000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,55);

}
void Show_Clear_Night(uint8_t x,uint8_t y)
{
	Refresh (x,y,76,80);
W25Q64_ReadData(0x013000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x014000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x015000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,76,80);

}
void Show_Rain_Night(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
W25Q64_ReadData(0x016000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x017000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x018000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}

	showimage(Picture,x,y,77,60);

}


void Show_Waiting()
{
Lcd_Clear(WHITE);
	 W25Q64_ReadData(0x019000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x01A000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	};
	
	
	showimage(Picture,0,0,128,32);
	
	W25Q64_ReadData(0x01B000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x01C000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,32,128,32);
	
	
	W25Q64_ReadData(0x01D000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x01E000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,64,128,32);
	W25Q64_ReadData(0x01F000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x020000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,96,128,32);
	W25Q64_ReadData(0x021000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x022000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,128,128,32);



}

void Show_Internet_Failed()
{
Lcd_Clear(WHITE);
	 W25Q64_ReadData(0x023000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x024000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	};
	
	
	showimage(Picture,0,0,128,32);
	
	W25Q64_ReadData(0x025000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x026000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,32,128,32);
	
	
	W25Q64_ReadData(0x027000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x028000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,64,128,32);
	W25Q64_ReadData(0x029000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x02A000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,96,128,32);
	W25Q64_ReadData(0x02B000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x02C000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,128,128,32);



}
void Show_connect_successful()
	
{
Lcd_Clear(WHITE);
	 W25Q64_ReadData(0x02D000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x02E000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	};
	
	
	showimage(Picture,0,0,128,32);
	
	W25Q64_ReadData(0x02F000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x030000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,32,128,32);
	
	
	W25Q64_ReadData(0x031000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x032000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,64,128,32);
	W25Q64_ReadData(0x033000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x034000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,96,128,32);
	W25Q64_ReadData(0x035000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x036000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,128,128,32);



}

void Show_press_to_continue()
{
Lcd_Clear(WHITE);
	 W25Q64_ReadData(0x037000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x038000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	};
	
	
	showimage(Picture,0,0,128,32);
	
	W25Q64_ReadData(0x039000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x03A000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,32,128,32);
	
	
	W25Q64_ReadData(0x03B000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x03C000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,64,128,32);
	W25Q64_ReadData(0x03D000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x03E000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,96,128,32);
	W25Q64_ReadData(0x03F000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x040000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096*1]=PictureTemp[i];
	
	}
	showimage(Picture,0,128,128,32);



}

void Show_Temperature_Image(uint8_t x,uint8_t y)
{
	Refresh (x,y,38,60);
	W25Q64_ReadData(0x041000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x042000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	

	showimage(Picture,x,y,38,60);

}

void Show_yintian(uint8_t x,uint8_t y)
{
	Refresh (x,y,77,80);
	W25Q64_ReadData(0x043000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x044000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x045000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}
	

	showimage(Picture,x,y,74,80);

}
	void Show_Snowy(uint8_t x,uint8_t y)
		{
	Refresh (x,y,77,80);
	W25Q64_ReadData(0x046000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x047000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x048000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+8192]=PictureTemp[i];
	
	}
	

	showimage(Picture,x,y,74,80);

}
	void Show_Umbrella(uint8_t x,uint8_t y)
{
	Refresh (x,y,45,48);
	W25Q64_ReadData(0x049000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x04A000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	
	

	showimage(Picture,x,y,45,48);

}

void Show_Sleep(uint8_t x,uint8_t y)
	
{
	Refresh (x,y,45,48);
	W25Q64_ReadData(0x04B000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x04C000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	
	

	showimage(Picture,x,y,45,48);

}
void Show_Sunglass(uint8_t x,uint8_t y)
	{
	Refresh (x,y,45,48);
	W25Q64_ReadData(0x04D000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	
	

	showimage(Picture,x,y,45,23);

}
	
void Show_Cloth(uint8_t x,uint8_t y)
	{
	Refresh (x,y,45,48);
	W25Q64_ReadData(0x04E000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	W25Q64_ReadData(0x04F000,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	}
	
	

	showimage(Picture,x,y,45,48);

}
	
void Show_Wrong(uint8_t x,uint8_t y)
{
Lcd_Clear(WHITE);
int o;
	for(o=0;o<5;o++)
	{
	 W25Q64_ReadData(0x050000+0x002000*o,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i]=PictureTemp[i];
	
	}
	
	W25Q64_ReadData(0x051000+0x002000*o,PictureTemp,4096);
	for(i=0;i<4096;i++)
	{
	Picture[i+4096]=PictureTemp[i];
	
	};
	
	
	showimage(Picture,0,32*o,128,32);
	

}
	

}