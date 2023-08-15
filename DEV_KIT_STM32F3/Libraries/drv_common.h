/*
 *              Copyright (c)  2023
 *  File header: 		drv_common.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef DRV_COMMON_H_
#define DRV_COMMON_H_

#include "main.h"
//#include "defines.h"
//#include <variables.h>
#include "string.h"
#include "stdbool.h"

#define RCU_USART1          USART1_BASE
#define RCU_USART2          USART2_BASE
#define RCU_USART3          USART3_BASE
#define RCU_UART4           UART4_BASE
#define RCU_UART5           UART5_BASE

#define IRQ_MAX  20

 typedef enum
{
	 DR_NULL = 0,
	 DR_UART,
	 DR_I2C,
	 DR_SPI,
	 DR_TIMER_SYS,
	 DR_TIMER,
	 DR_PCMTIMER,
 }
 irq_type_t;

typedef struct
{
	void (*EventCallback_t)(void*);
	irq_type_t type;
	void * para;
	uint64_t private_systick; // use to calculate timeout
	bool active;
}
Cblk_parameter_t;

//extern Cblk_parameter_t IRQ_Arr[IRQ_MAX];

/******************************************************************************/
/***                        TIMER FUNCTION FOR THE DRIVER                    **/
/******************************************************************************/
typedef void(*Callback)(void*);
void Drv_RegisterTIMER(void);
void Drv_TimerCaptureInit(uint32_t *timer,Callback fnc_cbk);
//void Drv_TimerCaptureChannelConfig(uint32_t timer,uint16_t channel,drv_gpio_t _obj);
extern void DRV_RUN(void);
extern void DRV_TIMER_FNC(void *arg);
/******************************************************************************/
/***                 INTERRUPT FUNCTIONS FOR THE DRIVER                      **/
/******************************************************************************/
void _Clear_DrvPar(Cblk_parameter_t *_cblk);
bool Drv_RegisterIRQ_callback(Cblk_parameter_t cbk);
void UART_IRQ(uint32_t _uart);
#endif /* DRV_COMMON_H_ */
