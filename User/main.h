/**
 * @file main.h
 * @brief FreeRTOS for STM32F1 template
 * @details using v6.19 ARM compiler
 * @encoding GB2312
 */

#ifndef __MAIN_H
#define __MAIN_H

#include <stdlib.h>
#include "misc.h"

#include "sys.h"
#include "delay.h"

#include "led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "list.h"

// 开始任务
#define START_TASK_PRIO		1
#define START_STK_SIZE 		128  
TaskHandle_t StartTask_Handler;
void Start_Task(void *pvParameters);

// LED0任务
#define LED0_TASK_PRIO		1
#define LED0_STK_SIZE 		50
TaskHandle_t LED0Task_Handler;
void Led0_Task(void *pvParameters);

// 列表任务
#define LIST_TASK_PRIO		1
#define LIST_STK_SIZE 		128  
TaskHandle_t ListTask_Handler;
void List_Task(void *pvParameters);

#endif /* __MAIN_H */
