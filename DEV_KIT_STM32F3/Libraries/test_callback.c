/*
 *              Copyright (c)  2023
 *  File header: 		test_callback.c
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */


#include "test_callback.h"

/******************************************************************************/
/******************************************************************************/
/***                           Private definitions                           **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                      Private functions declare                          **/
/******************************************************************************/
/******************************************************************************/
#define RX_TIMEOUT      150
/******************************************************************************/
/******************************************************************************/
/***                                Global Parameters                        **/
/******************************************************************************/
/******************************************************************************/
test_callback_t TEST_CBK;
/******************************************************************************/
/******************************************************************************/
/***                            Private functions                            **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                      Processing functions Callback                      **/
/******************************************************************************/
/******************************************************************************/
void test_cbk(void * arg)                 // callback to period timer
{
	static uint32_t check_counter = 0;
	if(check_counter != 0)
	{
		LOGA(INF, "Call timer: %ld\r\n", DRV_GETTICK() - check_counter);
		check_counter = DRV_GETTICK();
	}
	else
	{
		check_counter = DRV_GETTICK();
	}
}

void test_uart_cbk(void * arg)         // callback to usart interrupt
{
	if(TEST_CBK.usart.rx.idx < sizeof(TEST_CBK.usart.rx.rcv) - 1)
	{
		TEST_CBK.usart.rx.rcv[TEST_CBK.usart.rx.idx++] = *(uint8_t *) arg;
	}
	TEST_CBK.usart.rx.rxtime = DRV_GETTICK();
}
/******************************************************************************/
/******************************************************************************/
/***                            MainRun functions                            **/
/******************************************************************************/
/******************************************************************************/
void run_test_callback(void)
{
	if(TEST_CBK.usart.rx.idx > 1 && abs((int)(DRV_GETTICK() - TEST_CBK.usart.rx.rxtime)) > RX_TIMEOUT)
	{
		LOGA(GPS, "Data: %s\r\n", TEST_CBK.usart.rx.rcv);

		memset(&TEST_CBK.usart.rx.rcv, 0x00, sizeof(TEST_CBK.usart.rx.rcv));
		TEST_CBK.usart.rx.idx = 0;
	}
}
/******************************************************************************/
/******************************************************************************/
/***                            Public functions                             **/
/******************************************************************************/
/******************************************************************************/
void init_test_callback(void)
{
	memset(&TEST_CBK, 0x00, sizeof(TEST_CBK));

	Cblk_parameter_t test_callback;

	TEST_CBK.tim.time_refesh = 6000;

	_Clear_DrvPar(&test_callback);
	test_callback.type = DR_TIMER;
	test_callback.para = &TEST_CBK.tim.time_refesh;
	test_callback.EventCallback_t = &test_cbk;
	Drv_RegisterIRQ_callback(test_callback);




	Cblk_parameter_t test_uart;
	TEST_CBK.usart.peri.uart.rcu_uart = RCU_USART1;

	_Clear_DrvPar(&test_uart);
	test_uart.type = DR_UART;
	test_uart.para = &TEST_CBK.usart.peri.uart.rcu_uart;
	test_uart.EventCallback_t = &test_uart_cbk;
	Drv_RegisterIRQ_callback(test_uart);

	TEST_CBK.init = &init_test_callback;
	TEST_CBK.run = &run_test_callback;
}
/******************************************************************************/
/******************************************************************************/
/***                            Library callback                             **/
/******************************************************************************/
/******************************************************************************/





