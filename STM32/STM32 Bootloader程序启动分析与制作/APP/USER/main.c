#include "sys.h"
#include "delay.h"   //延时驱动文件
#include "server.h"  //舵机驱动文件
#include "usart.h"
#include "delay.h"
#include "timer.h"
/* 主函数 */
int main(void) {
    //SCB->VTOR = FLASH_BASE | 0x10000;
    __enable_irq();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    delay_init();
    uart_init(115200);
    TIM3_Int_Init(9999, 7199);
    while (1) {
        static int count = 0;
        printf("-------->%d\r\n", count++);
        delay_ms(500);
    }
}
