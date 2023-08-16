/*
 *              Copyright (c)  2023
 *  File header: 		AT_command.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef AT_COMMAND_H_
#define AT_COMMAND_H_

#include "main.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f3xx_hal.h"
#include "drv_atcmd.h"

typedef enum
{
	LTE_IDLE=0,
	LTE_SHUTDOWNED,
	LTE_RESTARTING,
	LTE_ERR,
	LTE_RDY,
	LTE_BOOTING,
	LTE_BUSY, // This is status when the modem is waiting response in the special case (SMS send, Server connect,...)
}
ATcommand_status;


typedef struct
{
	void             (*Run)(void);
	void             (*Init)(void);
	ATcommand_status (*Config)(void);
	void             (*Process)(PROCCESS_TYPE);

	struct
	{
		uint32_t timer_refesh;                           // (base ms)time to refesh database
		uint16_t time_dead; 	                         // (base s)time to count timing devices was stucked
		uint16_t time_busy; 	                         // (base s)time to count timing devices was busy
	}
	work;
}
at_command_t;

extern at_command_t  MODULE;
void module_init(void);

#endif /* AT_COMMAND_H_ */
