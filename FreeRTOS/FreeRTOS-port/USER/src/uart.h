/*
 * Project: FreeRTOS-port
 * Module: module_name
 * File: uart.h
 * Created Date: 2025-04-25 14:53:15
 * Author: wangshuqiang
 * Description: description
 * -----
 * todo: modified
 * -----
 */
#ifndef UART_H
#define UART_H

/* ======================================================================================
 * includes
 */

/* ======================================================================================
 * extern
 */

/* ======================================================================================
 * macros
 */
#define UART_REC_MODE      UART_REC_MODE_INT
#define UART_REC_MODE_INT  1
#define UART_REC_MODE_LOOP 2
#define UART_REC_MODE_DMA  3
/* ======================================================================================
 * types
 */

/* ======================================================================================
 * declaration
 */

/**
 * @brief 初始化系统串口
 *
 */
void uart_config_init(void);
/* ======================================================================================
 * extern
 */
#endif  // UART_H