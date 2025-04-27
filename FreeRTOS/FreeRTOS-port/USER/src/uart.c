/*
 * Project: FreeRTOS-port
 * Module: module_name
 * File: uart.c
 * Created Date: 2025-04-25 14:53:12
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
#include "uart.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "queue.h"
/* ======================================================================================
 * macros
 */
#define UART_QUEUE_LENGTH 100
#define UART_QUEUE_SIZE   3
/* ======================================================================================
 * types
 */

/* ======================================================================================
 * declaration
 */

/* ======================================================================================
 * globals
 */
static QueueHandle_t uart_rec_queue = NULL;
static uint8_t       usart_rx_buf[UART_QUEUE_LENGTH];
static uint8_t       usart_rx_count;
/* ======================================================================================
 * helper
 */

/* ======================================================================================
 * private implementation
 */

/* ======================================================================================
 * implementation
 */
void uart_config_init(void) {
    // GPIO端口设置
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);  // 使能USART1，GPIOA时钟

    // USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;  // PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化GPIOA.9

    // USART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;            // PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 初始化GPIOA.10
#if (UART_REC_MODE == UART_REC_MODE_INT)
    // 中断模式接收数据
    // Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;       // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;  // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                                 // 根据指定的参数初始化VIC寄存器
#elif (UART_REC_MODE == UART_REC_MODE_LOOP)
    // 轮询接收数据
#elif (UART_REC_MODE == UART_REC_MODE_DMA)
    // DMA 初始化
#else

    // USART 初始化设置

#endif
    // 初始化队列
    uart_rec_queue = xQueueCreate(UART_QUEUE_LENGTH, UART_QUEUE_SIZE);
    if (NULL == uart_rec_queue) {
        // 串口队列创建失败
    }

    USART_InitStructure.USART_BaudRate            = 115200;                          // 串口波特率
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             // 字长为8位数据格式
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;                // 一个停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;                 // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 无硬件数据流控制
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;   // 收发模式

    USART_Init(USART1, &USART_InitStructure);       // 初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  // 开启串口接受中断
    USART_Cmd(USART1, ENABLE);                      // 使能串口1
}

void USART1_IRQHandler(void)  // 串口1中断服务程序
{
    u8 Res;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        Res = USART_ReceiveData(USART1);  // 读取接收到的数据

        usart_rx_buf[usart_rx_count++] = Res;
    }
}
