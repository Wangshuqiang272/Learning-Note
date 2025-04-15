#include "sys.h"
#include "delay.h"   //��ʱ�����ļ�
#include "server.h"  //��������ļ�
#include "usart.h"
#include "delay.h"
#include "timer.h"
/* ������ */
int main(void) {
    //SCB->VTOR = FLASH_BASE | 0x10000;
    __enable_irq();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    delay_init();
    uart_init(115200);
    TIM3_Int_Init(9999, 7199);
    while (1) {
        static int count = 0;
        printf("-------->%d\r\n", count++);
        delay_ms(500);
    }
}
