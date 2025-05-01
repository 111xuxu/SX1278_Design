#include "stm32f10x.h"                  // Device header
#ifndef __My_spi_h
#define __My_spi_h

void MySPI_W_SS(uint8_t Bitvalue);
void MySPI_W_SCK(uint8_t Bitvalue);
void MySPI_W_MOSI(uint8_t Bitvalue);
uint8_t MySPI_R_MISO(void);
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);


#endif
