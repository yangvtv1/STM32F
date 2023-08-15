/*
 *              Copyright (c)  2023
 *  File header: 		test_callback.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef TEST_CALLBACK_H_
#define TEST_CALLBACK_H_

#include "drv_common.h"
//#include "defines.h"
//#include <variables.h>
#include "string.h"
#include "stdbool.h"

typedef struct
{
	void (*init)(void);
	void (*run)(void);
}
test_callback_t;

extern test_callback_t TEST_CBK;
void init_test_callback(void);

#endif /* TEST_CALLBACK_H_ */
