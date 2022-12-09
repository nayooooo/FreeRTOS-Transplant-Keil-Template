#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
#include "stdbool.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.7
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
#define NOP1()		__NOP()
#define NOP2()		NOP1();__NOP()
#define NOP3()		NOP2();__NOP()
#define NOP4()		NOP3();__NOP()
#define NOP5()		NOP4();__NOP()
#define NOP6()		NOP5();__NOP()
#define NOP7()		NOP6();__NOP()
#define NOP8()		NOP7();__NOP()
#define NOP9()		NOP8();__NOP()
#define NOP10()		NOP9();__NOP()
#define NOP11()		NOP10();__NOP()
#define NOP12()		NOP11();__NOP()
#define NOP13()		NOP12();__NOP()
#define NOP14()		NOP13();__NOP()
#define NOP15()		NOP14();__NOP()
#define NOP16()		NOP15();__NOP()
#define NOP17()		NOP16();__NOP()
#define NOP18()		NOP17();__NOP()
#define NOP19()		NOP18();__NOP()
#define NOP20()		NOP19();__NOP()
#define NOP21()		NOP20();__NOP()
#define NOP22()		NOP21();__NOP()
#define NOP23()		NOP22();__NOP()
#define NOP24()		NOP23();__NOP()
#define NOP25()		NOP24();__NOP()
#define NOP26()		NOP25();__NOP()
#define NOP27()		NOP26();__NOP()
#define NOP28()		NOP27();__NOP()
#define NOP29()		NOP28();__NOP()
#define NOP30()		NOP29();__NOP()
#define NOP31()		NOP30();__NOP()
#define NOP32()		NOP31();__NOP()
#define NOP33()		NOP32();__NOP()
#define NOP34()		NOP33();__NOP()
#define NOP35()		NOP34();__NOP()
#define NOP36()		NOP35();__NOP()
#define NOP37()		NOP36();__NOP()
#define NOP38()		NOP37();__NOP()
#define NOP39()		NOP38();__NOP()
#define NOP40()		NOP39();__NOP()
#define NOP(x)		NOP##x()

//0,不支持os
//1,支持os
#define SYSTEM_SUPPORT_OS		1		//定义系统文件夹是否支持OS

#define PI (3.1415926)														    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

#endif
