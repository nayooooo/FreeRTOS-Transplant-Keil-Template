#ifndef __BKP_H
#define __BKP_H

#include "sys.h"

void BKP_Init(void);
void BKP_Write_16bit_Data(uint16_t BKP_DR, uint16_t Data);
void BKP_Write_32bit_Data(uint16_t BKP_DR, uint32_t Data);
uint16_t BKP_Read_16bit_Data(uint16_t BKP_DR);
uint32_t BKP_Read_32bit_Data(uint16_t BKP_DR);

#endif
