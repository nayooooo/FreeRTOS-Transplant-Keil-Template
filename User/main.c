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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  // ����ϵͳ�ж����ȼ�����4	 	 
	delay_init();	    				// ��ʱ������ʼ��	  
	uart_init(115200);					// ��ʼ������
	LED_Init();		  					// ��ʼ��LED
}

int main(void)
{
	System_Init();
	 
	// ������ʼ����
    xTaskCreate((TaskFunction_t )Start_Task,            // ������
                (const char*    )"Start_Task",          // ��������
                (uint16_t       )START_STK_SIZE,        // �����ջ��С
                (void*          )NULL,                  // ���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       // �������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   // ������              
    vTaskStartScheduler();          // �����������
}

//��ʼ����������
void Start_Task(void *pvParameters)
{
    taskENTER_CRITICAL();           // �����ٽ���
    // ����LED0����
    xTaskCreate((TaskFunction_t )Led0_Task,
                (const char*    )"Led0_Task",
                (uint16_t       )LED0_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LED0_TASK_PRIO,
                (TaskHandle_t*  )&LED0Task_Handler);
    // �����б�����
    xTaskCreate((TaskFunction_t )List_Task,
                (const char*    )"List_Task",
                (uint16_t       )LIST_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LIST_TASK_PRIO,
                (TaskHandle_t*  )&ListTask_Handler);
    vTaskDelete(NULL);				// ɾ����ʼ��������
    taskEXIT_CRITICAL();			// �˳��ٽ���
}

// LED0������ 
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

// �б�����
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
