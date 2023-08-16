/*
 *              Copyright (c)  2023
 *  File header: 		flash_memory.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef FLASH_MEMORY_H_
#define FLASH_MEMORY_H_

#include "main.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f3xx_hal.h"

#define FLASH_STORAGE                       0x08009000
#define page_size                           0x800

typedef struct
{
	void (*init)(void );
	void (*write)(uint8_t * );
	void (*read)(uint8_t* );
}
flash_mem_t;

extern flash_mem_t FLA_MEMORY;
void flash_init(void);

#endif /* FLASH_MEMORY_H_ */
