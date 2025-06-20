#include "stm32f10x.h"                  // Device header
#include "SD_Card.h"
#include "My_spi.h"
#include "delay.h"	

uint8_t SD_Initialize(void);

//send command 函数不包含cs的控制，需要外部函数进行控制选择

uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t response;
    uint8_t frame[6] = {
        0x40 | (cmd & 0x3F),//（00100000|（cmd&00111111）
        (uint8_t)(arg >> 24),
        (uint8_t)(arg >> 16),
        (uint8_t)(arg >> 8),
        (uint8_t)arg,
        crc
    };
   
    MySPI_SwapByte(0xFF);         
    for (int i = 0; i < 6; i++)   
        MySPI_SwapByte(frame[i]);
	

		
    for (int i = 0; i < 80; i++)   
    {
        response = MySPI_SwapByte(0xFF);
        if (!(response & 0x80)) break;
    }

    return response;              
}



uint8_t SD_Check(void)
{
    uint8_t ocr[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t r;

    MySPI_LORA_Stop();
    MySPI_SD_Stop();
    MySPI_SwapByte(0xFF);
    MySPI_SD_Start();

    r = SD_SendCommand(CMD58, 0, 0x01);  // Read OCR

    if (r == 0x01 || r == 0x00)  // Only accept 0x01 (idle) or 0x00 (ready)
    {
        for (int i = 0; i < 4; i++)
            ocr[i] = MySPI_SwapByte(0xFF);
    }

    MySPI_SD_Stop();

		if (r == 0x00) {
			if (ocr[0] == 0x00 && ocr[1] == 0x00 && ocr[2] == 0x00 && ocr[3] == 0x00)
			{ 
				OLED_ShowString(1, 1, "No SD Card      ");
			
        return 0;
			}
    }
		
    // === 判断条件修正 ===
    if (r == 0xFF) {
        OLED_ShowString(1, 1, "No Response     ");
			SD_Initialize();
        return 0;
    }
    else if (ocr[0] == 0xFF && ocr[1] == 0xFF && ocr[2] == 0xFF && ocr[3] == 0xFF) {
        OLED_ShowString(1, 1, "OCR Invalid     ");
        return 0;
    }
    else if (r > 0x01) {
        OLED_ShowString(1, 1, "Bad R1 Resp     ");
        return 0;
    }
    else {
        OLED_ShowString(1, 1, "SD Ready        ");
        return 1;
    }
}



uint8_t SD_Initialize(void)
{
    uint8_t i, r;
static int retry=0;
    MySPI_Init();

    MySPI_SD_Stop();
    for(i = 0; i < 10; i++)    
		MySPI_SwapByte(0xFF);

    MySPI_SD_Start();
		r = SD_SendCommand(CMD0, 0, 0x95);//40 00 00 00 00 95
		MySPI_SD_Stop();
	
	
    if (r !=0x01) 
		{ 
			
			OLED_ShowString(1,1,"Check SD        ");
			if (retry<1)
			{
				retry++;
			SD_Initialize();
				return 1;
			}
			retry =0;
			
			return 1;      
		}			
		 MySPI_SD_Start();
    for (i = 0; i < 500; i++)
    {
        r = SD_SendCommand(CMD1, 0, 0x01);  //41 00 00 00 00 01
        if (r == 0x00) 
					break;
        Delay_ms(10);
    }
		 MySPI_SD_Stop();
		
    if (i == 500)
{ 
	OLED_ShowString(1,1,"Init Failed     ");
			Delay_s(1);
			return 2;      
		}	     
	 MySPI_SD_Start();
    r = SD_SendCommand(CMD16, 512, 0x01);  //50 00 00 02 00 01
 MySPI_SD_Stop();
    if (r != 0x00) 
			{
				OLED_ShowString(1,1,"Sector set error");
			Delay_s(1);
			return 3;      
		}

    MySPI_SD_Stop();
    MySPI_SwapByte(0xFF);
		OLED_ShowString(1,1,"SD Init Succeed ");
		if(retry==1)
		{
		SD_Check();
			return 0; 
		}
		Delay_s(1);
    return 0;                              
}



uint8_t SD_WriteSector(uint32_t sectorAddr, uint8_t *data)
{
    uint8_t response;
    uint32_t byteAddr = sectorAddr * 512;
    
    MySPI_SD_Start();
    response = SD_SendCommand(CMD24, byteAddr, 0xFF);
	
    if (response != 0x00)
    {
        MySPI_SD_Stop();
			OLED_ShowString(1,1,"Write failed    ");
			Delay_s(1);
        return 1; // CMD24 faild
    }
		
    MySPI_SwapByte(0xFE);
		 MySPI_SD_Start();
    for (int i = 0; i < 512; i++)
        MySPI_SwapByte(data[i]);

    
    MySPI_SwapByte(0xFF);
    MySPI_SwapByte(0xFF);

    uint8_t dataResp = MySPI_SwapByte(0xFF);
    if ((dataResp & 0x1F) != 0x05)
    {
        MySPI_SD_Stop();
			OLED_ShowString(1,1,"Write Declined  ");
			Delay_s(1);
        return 2; 
    }

    while (MySPI_SwapByte(0xFF) != 0xFF);

    MySPI_SD_Stop();
    MySPI_SwapByte(0xFF);
//OLED_ShowString(1,1,"Write Succeed   ");
			//Delay_s(1);
    return 0; 
}

uint8_t SD_ReadSector(uint32_t sectorAddr, uint8_t *buffer)
{
	uint32_t byteAddr = sectorAddr * 512;
    uint8_t response;

    MySPI_SD_Start();
    

    response = SD_SendCommand(CMD17, byteAddr, 0xFF);
    if (response != 0x00)
    {
        MySPI_SD_Stop();
			OLED_ShowString(1,1,"Read failed     ");
			Delay_s(1);
        return 1; 
    }

    for (int i = 0; i < 100000; i++)
    {
        uint8_t token = MySPI_SwapByte(0xFF);
        if (token == 0xFE)
            break;

        if (i == 99999)
        {
            MySPI_SD_Stop();
					OLED_ShowString(1,1,"Timeout         ");
			Delay_s(1);
            return 2; 
        }
    }

    for (int i = 0; i < 512; i++)
        buffer[i] = MySPI_SwapByte(0xFF);

    MySPI_SwapByte(0xFF);
    MySPI_SwapByte(0xFF);

    MySPI_SD_Stop();
    MySPI_SwapByte(0xFF); 
OLED_ShowString(1,1,"Read Succeed    ");
			//Delay_s(1);
    return 0;
}
