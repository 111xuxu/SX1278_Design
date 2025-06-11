#include "ff.h"
#include "diskio.h"
#include "string.h"
#include "stm32f10x.h"
#include "Write_To_Disk.h"
#include "delay.h"
#include "SD_Card.h"

 
void WriteFileToSD(char *File_Name,char * Content,int Method)
{

	
	
    res = f_mount(&fs, "", 1);
    if (res != FR_OK) {

        OLED_ShowString(1, 1, "Mount Fail");
        return;
    }

    if(Method==Append_In_File)
		{
    res = f_open(&file, File_Name, FA_WRITE | FA_OPEN_ALWAYS);
    if (res != FR_OK) {
        OLED_ShowString(1, 1, "Open Fail");
        return;
    }
 f_lseek(&file, f_size(&file));
	}
		if(Method==Creat_New_File)
		{
		
		res = f_open(&file, File_Name, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        OLED_ShowString(1, 1, "Open Fail");
        return;
    }
		}
			
		
    res = f_write(&file, Content, strlen(Content), &bw);
    if (res != FR_OK || bw != strlen(Content)) {
        OLED_ShowString(1, 1, "Write Fail");
        f_close(&file);
        return;
    }

    // 4. ¹Ø±ÕÎÄ¼þ
    f_close(&file);

    OLED_ShowString(1, 1, "Write OK");
		
	
	
		
		
}