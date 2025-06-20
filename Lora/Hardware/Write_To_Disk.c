#include "ff.h"
#include "diskio.h"
#include "string.h"
#include "stm32f10x.h"
#include "Write_To_Disk.h"
#include "delay.h"
#include "SD_Card.h"

 
 
 
 
 
 
 
 FATFS fs;
FIL file;
FRESULT res;
UINT bw;




/*void WriteFileToSD(char *File_Name, char *Content, int Method)
{
    static uint8_t mounted = 0;

    // ? ֻ����һ��
    if (!mounted)
    {
        res = f_mount(&fs, "", 1);
        if (res != FR_OK)
        {
            OLED_ShowString(1, 1, "Mount Fail");
            Delay_ms(1000);
            return;
        }
        mounted = 1;
    }

    // ? ���ļ���׷�ӻ��½���
    if (Method == Append_In_File)
    {
        res = f_open(&file, File_Name, FA_WRITE | FA_OPEN_ALWAYS);
        if (res != FR_OK)
        {
            OLED_ShowString(1, 1, "Open Fail");
            Delay_ms(1000);
            return;
        }
        f_lseek(&file, f_size(&file));  // �ƶ����ļ�ĩβ
    }
    else if (Method == Creat_New_File)
    {
        res = f_open(&file, File_Name, FA_WRITE | FA_CREATE_ALWAYS);
        if (res != FR_OK)
        {
            OLED_ShowString(1, 1, "Open Fail");
            Delay_ms(1000);
            return;
        }
    }

    // ? д������
    res = f_write(&file, Content, strlen(Content), &bw);
    if (res != FR_OK || bw != strlen(Content))
    {
        OLED_ShowString(1, 1, "Write Fail");
        Delay_ms(1000);
        f_close(&file);
        return;
    }

    // ? �ر��ļ�
    f_close(&file);
    OLED_ShowString(1, 1, "Write OK");
}

 */
 
 
 
 
 
 
 
void WriteFileToSD(char *File_Name,char * Content,int Method)
{
//MySPI_SwapByte(0xFF);
	//MySPI_SwapByte(0xFF);
	//MySPI_SwapByte(0xFF);
//	MySPI_SwapByte(0xFF);
	
    res = f_mount(&fs, "", 1);
    if (res != FR_OK) {

        OLED_ShowString(1, 1, "Mount Fail");
			//OLED_ShowNum(4,1,res,4);
			//while(1);
			Delay_ms(1000);
        return;
    }

    if(Method==Append_In_File)
		{
    res = f_open(&file, File_Name, FA_WRITE | FA_OPEN_ALWAYS);
    if (res != FR_OK) {
        OLED_ShowString(1, 1, "Open Fail");
			Delay_ms(1000);
        return;
    }
 f_lseek(&file, f_size(&file));
	}
		if(Method==Creat_New_File)
		{
		
		res = f_open(&file, File_Name, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        OLED_ShowString(1, 1, "Open Fail");
			Delay_ms(1000);
        return;
    }
		}
			
		
    res = f_write(&file, Content, strlen(Content), &bw);
    if (res != FR_OK || bw != strlen(Content)) {
        OLED_ShowString(1, 1, "Write Fail");
			Delay_ms(1000);
        f_close(&file);
        return;
    }

    // 4. �ر��ļ�
    f_close(&file);

    OLED_ShowString(1, 1, "Write OK");
		
	
	
		
		
}