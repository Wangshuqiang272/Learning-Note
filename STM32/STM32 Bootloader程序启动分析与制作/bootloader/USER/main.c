/*
 * Project: test_bootloader
 * Module: module_name
 * File: main.c
 * Created Date: 2025-04-05 16:13:50
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sys.h"
#include "usart.h"
#include "timer.h"
/* ======================================================================================
 * macros
 */

/* ======================================================================================
 * types
 */

typedef void (*pFunction)(void);
/* ======================================================================================
 * declaration
 */

/* ======================================================================================
 * globals
 */

/* ======================================================================================
 * helper
 */

/* ======================================================================================
 * private implementation

 */
/* ======================================================================================
 * implementation
 */

/* APP flash address */
#define APP_FLASH_ADDR (0x8010000)
char buf[] = {"running bootloader\r\n"};
int  i     = 0;
int  main(void) {
    uint32_t  JumpAddress;
    pFunction Jump_To_Application;
		//TIM3_Int_Init(9999,7199);
    /* 检查栈顶地址是否合法 */
    if (((*(__IO uint32_t*)APP_FLASH_ADDR) & 0x2FFE0000) == 0x20000000) {
        /* 屏蔽所有中断，防止在跳转过程中，中断干扰出现异常 */
        __disable_irq();
        uart_init(115200);

        for (i = 0; i < sizeof(buf); i++) {
            USART_SendData(USART1, buf[i]);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
        }
		//printf("1111\r\n");
        /* 用户代码区第二个 字 为程序开始地址(复位地址) */
        JumpAddress = *(__IO uint32_t*)(APP_FLASH_ADDR + 4);

        /* Initialize user application's Stack Pointer */
        /* 初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址) */
        __set_MSP(*(__IO uint32_t*)APP_FLASH_ADDR);

        /* 类型转换 */
        Jump_To_Application = (pFunction)JumpAddress;
        // printf("ready jump to main App\r\n");
        /* 跳转到 APP */
        Jump_To_Application();
    }
}
