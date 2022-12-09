/**
 * @file main.c
 * @brief FreeRTOS for STM32F1 template
 * @details using v6.19 ARM compiler
 * @encoding GB2312
 */

#include "main.h"

List_t Test_List;
ListItem_t ListItem_1;
ListItem_t ListItem_2;
ListItem_t ListItem_3;

void System_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  // 设置系统中断优先级分组4	 	 
	delay_init();	    				// 延时函数初始化	  
	uart_init(115200);					// 初始化串口
	LED_Init();		  					// 初始化LED
}

int main(void)
{
	System_Init();
	 
	// 创建开始任务
    xTaskCreate((TaskFunction_t )Start_Task,            // 任务函数
                (const char*    )"Start_Task",          // 任务名称
                (uint16_t       )START_STK_SIZE,        // 任务堆栈大小
                (void*          )NULL,                  // 传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       // 任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   // 任务句柄              
    vTaskStartScheduler();          // 开启任务调度
}

//开始任务任务函数
void Start_Task(void *pvParameters)
{
    taskENTER_CRITICAL();           // 进入临界区
    // 创建LED0任务
    xTaskCreate((TaskFunction_t )Led0_Task,
                (const char*    )"Led0_Task",
                (uint16_t       )LED0_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LED0_TASK_PRIO,
                (TaskHandle_t*  )&LED0Task_Handler);
    // 创建列表任务
    xTaskCreate((TaskFunction_t )List_Task,
                (const char*    )"List_Task",
                (uint16_t       )LIST_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LIST_TASK_PRIO,
                (TaskHandle_t*  )&ListTask_Handler);
    vTaskDelete(NULL);				// 删除开始任务（自身）
    taskEXIT_CRITICAL();			// 退出临界区
}

// LED0任务函数 
void Led0_Task(void *pvParameters)
{
    while(1)
    {
        LED0_Flip();
        vTaskDelay(200);
        LED0_Flip();
		vTaskSuspend(NULL);
    }
}

// 列表任务
void List_Task(void *pvParameters)
{
	vListInitialise( &Test_List );
	vListInitialiseItem( &ListItem_1 );
	vListInitialiseItem( &ListItem_2 );
	vListInitialiseItem( &ListItem_3 );
	ListItem_1.xItemValue = 40;
	ListItem_2.xItemValue = 50;
	ListItem_3.xItemValue = 60;
	
	printf("/*************** List and list items' addresses ***************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List                           %#X                         \r\n", (int)&Test_List);
	printf("Test_List->pxIndex->                %#X                         \r\n", (int)Test_List.pxIndex);
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->xListEnd                 %#X                         \r\n", (int)(&Test_List.xListEnd));
	printf("ListItem_1                          %#X                         \r\n", (int)&ListItem_1);
	printf("ListItem_2                          %#X                         \r\n", (int)&ListItem_2);
	printf("ListItem_3                          %#X                         \r\n", (int)&ListItem_3);
	printf("/**************************** end *****************************/\r\n");
	
	vListInsert(&Test_List, &ListItem_1);
	printf("/*********************** add ListItem_1 ************************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->ListItem_1->pxNext       %#X                         \r\n", (int)ListItem_1.pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->ListItem_1->pxPrevious   %#X                         \r\n", (int)ListItem_1.pxPrevious);
	printf("/**************************** end *****************************/\r\n");
	
	vListInsert(&Test_List, &ListItem_2);
	printf("/*********************** add ListItem_2 ************************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->ListItem_2->pxNext       %#X                         \r\n", (int)ListItem_2.pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->ListItem_2->pxPrevious   %#X                         \r\n", (int)ListItem_2.pxPrevious);
	printf("/**************************** end *****************************/\r\n");
	
	vListInsert(&Test_List, &ListItem_3);
	printf("/*********************** add ListItem_3 ************************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->ListItem_3->pxNext       %#X                         \r\n", (int)ListItem_3.pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->ListItem_3->pxPrevious   %#X                         \r\n", (int)ListItem_3.pxPrevious);
	printf("/**************************** end *****************************/\r\n");
	
	do{
		UBaseType_t temp = uxListRemove(&ListItem_2);
		printf("be left over %d items...\r\n", (int)temp);
	}while(0);
	printf("/********************* remove ListItem_2 **********************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->ListItem_2->pxNext       %#X                         \r\n", (int)ListItem_2.pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->ListItem_2->pxPrevious   %#X                         \r\n", (int)ListItem_2.pxPrevious);
	printf("/**************************** end *****************************/\r\n");
	
	vListInsertEnd(&Test_List, &ListItem_2);
	printf("/**************** insert ListItem_2 to the end ****************/\r\n");
	printf("name                                address                     \r\n");
	printf("Test_List->pxIndex->pxNext          %#X                         \r\n", (int)Test_List.pxIndex->pxNext);
	printf("Test_List->ListItem_2->pxNext       %#X                         \r\n", (int)ListItem_2.pxNext);
	printf("Test_List->pxIndex->pxPrevious      %#X                         \r\n", (int)Test_List.pxIndex->pxPrevious);
	printf("Test_List->ListItem_2->pxPrevious   %#X                         \r\n", (int)ListItem_2.pxPrevious);
	printf("/**************************** end *****************************/\r\n");
	
	while(1)
	{
		vTaskDelay(3000);
	}
}
