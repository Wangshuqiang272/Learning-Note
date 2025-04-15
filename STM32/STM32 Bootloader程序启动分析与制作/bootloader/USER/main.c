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
    /* ���ջ����ַ�Ƿ�Ϸ� */
    if (((*(__IO uint32_t*)APP_FLASH_ADDR) & 0x2FFE0000) == 0x20000000) {
        /* ���������жϣ���ֹ����ת�����У��жϸ��ų����쳣 */
        __disable_irq();
        uart_init(115200);

        for (i = 0; i < sizeof(buf); i++) {
            USART_SendData(USART1, buf[i]);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
        }
		//printf("1111\r\n");
        /* �û��������ڶ��� �� Ϊ����ʼ��ַ(��λ��ַ) */
        JumpAddress = *(__IO uint32_t*)(APP_FLASH_ADDR + 4);

        /* Initialize user application's Stack Pointer */
        /* ��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ) */
        __set_MSP(*(__IO uint32_t*)APP_FLASH_ADDR);

        /* ����ת�� */
        Jump_To_Application = (pFunction)JumpAddress;
        // printf("ready jump to main App\r\n");
        /* ��ת�� APP */
        Jump_To_Application();
    }
}
