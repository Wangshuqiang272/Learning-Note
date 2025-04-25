/*
 * Project: FreeRTOS-port
 * Module: module_name
 * File: main.c
 * Created Date: 2024-09-02 22:32:48
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified
 * -----
 */

 /* ======================================================================================
  * log
  */
#define LOG_ENABLE_DEBUG (1)

  /* ======================================================================================
   * includes
   */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
   /* ======================================================================================
	* macros
	*/

	/* ======================================================================================
	 * types
	 */

	 /* ======================================================================================
	  * declaration
	  */

	  /* ======================================================================================
	   * globals
	   */

TaskHandle_t* taskA_handle = NULL;
TaskHandle_t* taskB_handle = NULL;
/* ======================================================================================
 * helper
 */

 /* ======================================================================================
  * private implementation
  */

static void taskA_handle_callback(void* param)
{
	while (1)
	{
		printf("-----------------------\r\n");
		vTaskDelay(1000);
	}
}

static void taskB_handle_callback(void* param)
{
	while (1)
	{
		printf("++++++++++++++++++++++++\r\n");
		vTaskDelay(1000);
	}
}

static void start_task(void* param)
{

	printf("wangshuqiang start_task\r\n");

	xTaskCreate(taskA_handle_callback, "taskA_handle_callback", 512, NULL, 8, taskA_handle);

	xTaskCreate(taskB_handle_callback, "taskB_handle_callback", 512, NULL, 10, taskB_handle);

	if (taskA_handle && taskB_handle)
	{
		printf("wangshuqiang test task create successed\r\n");
	}

	vTaskDelete(NULL);
}

/* ======================================================================================
 * implementation
 */

int main(void)
{
	//int i = 0;
	uart_init(115200);
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	printf("wangshuqiang test FreeRTOS port project!!!\r\n");
	xTaskCreate(start_task, "start_task", 512, NULL, 8, NULL);

	vTaskStartScheduler();
}
