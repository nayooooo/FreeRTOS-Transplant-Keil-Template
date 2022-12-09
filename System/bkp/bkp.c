#include "bkp.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"

void BKP_Init(void)
{
	// 使能PWR和BKP时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
	
	// 使能访问BKP寄存器
	PWR_BackupAccessCmd(ENABLE);
	
	// 清除侵入检测事件
	BKP_ClearFlag();
}

void BKP_Write_16bit_Data(uint16_t BKP_DR, uint16_t Data)
{
	BKP_ClearFlag();
	BKP_WriteBackupRegister(BKP_DR, Data);
}

void BKP_Write_32bit_Data(uint16_t BKP_DR, uint32_t Data)
{
	BKP_ClearFlag();
	// 小端存储
	BKP_WriteBackupRegister(BKP_DR, (uint16_t)Data);  // 低16位
	BKP_WriteBackupRegister(BKP_DR + 2 * sizeof(uint16_t), (uint16_t)(Data>>16));  // 高16位
}

uint16_t BKP_Read_16bit_Data(uint16_t BKP_DR)
{
	uint16_t data = 0X0000;
	data = BKP_ReadBackupRegister(BKP_DR);
	return data;
}

uint32_t BKP_Read_32bit_Data(uint16_t BKP_DR)
{
	uint32_t data = 0X00000000;
	data = BKP_ReadBackupRegister(BKP_DR);
	data |= BKP_ReadBackupRegister(BKP_DR + 2 * sizeof(uint16_t))<<sizeof(uint16_t);
	return data;
}
