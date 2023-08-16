/*
 *              Copyright (c)  2023
 *  File header: 		drv_include.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef DRV_INCLUDE_H_
#define DRV_INCLUDE_H_

#include "main.h"
#include "string.h"
#include "stdbool.h"

/******************************************************************************/
/***                        DEFINE FOR APB PERIPHERALS                       **/
/******************************************************************************/

#define RCU_USART1                                              USART1_BASE
#define RCU_USART2                                              USART2_BASE
#define RCU_USART3                                              USART3_BASE
#define RCU_UART4                                               UART4_BASE
#define RCU_UART5                                               UART5_BASE


/******************************************************************************/
/***                   DEFINE SYSTEM FUNCTIONS FOR THE MCU                   **/
/******************************************************************************/
#define getSysTick 												HAL_GetTick
#define DRV_GETTICK												getSysTick
#define	DRV_MILLIS												getSysTick
#define delay_ms(x)                                             HAL_Delay(x)
#define DRV_DELAY_MS(x)										    delay_ms(x)
/******************************************************************************/
/***                   DEFINE TIMER FUNCTIONS FOR THE MCU                    **/
/******************************************************************************/
#define DRV_TIM_PERIOD_ELAPSED_CALLBACK(x)                      HAL_TIM_PeriodElapsedCallback(x)
#define DRV_TIM_BASE_START_IT(x)                                HAL_TIM_Base_Start_IT(x)
/******************************************************************************/
/***                   DEFINE UART FUNCTIONS FOR THE MCU                     **/
/******************************************************************************/
#define DRV_UART_RX_CPLT_CALLBACK(x)                            HAL_UART_RxCpltCallback(x)
#define DRV_UART_RECEIVE_IT(x, y, z)                            HAL_UART_Receive_IT(x, y, z)
#define DRV_UART_TRANSMIT_IT(x, y, z)                           HAL_UART_Transmit_IT(x, y, z)

//#define DRV_UART_RECEIVE 									usart_data_receive
//#define DRV_UART_TRANSMIT 								    usart_data_transmit
//#define DRV_UART_FLAG_TBE_GET(x) 					        usart_flag_get(x,USART_FLAG_TBE)
//#define DRV_UART_FLAG_TC_GET(x) 					        usart_flag_get(x,USART_FLAG_TC)
//#define DRV_UART_FLAG_TC_CLEAR(x)					        usart_flag_clear(x,USART_FLAG_TC)
//#define DRV_UART_FLAG_TBE_CLEAR(x)				            usart_flag_clear(x,USART_FLAG_TBE)


#endif /* DRV_INCLUDE_H_ */
