/*
 *              Copyright (c)  2023
 *  File header: 		drv_common.c
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */


#include "drv_common.h"

#define DRV_TIMER_PERIOD 1000 // 100 ms

Cblk_parameter_t IRQ_Arr[IRQ_MAX];

/*
[1]	I2C_HandleTypeDef hi2c1;
[2]	RTC_HandleTypeDef hrtc;
[3]	SPI_HandleTypeDef hspi1;
[4]	TIM_HandleTypeDef htim2;
[5]	UART_HandleTypeDef huart4;
*/
/******************************************************************************/
/***                        TIMER FUNCTION FOR THE DRIVER                    **/
/******************************************************************************/
void _Clear_DrvPar(Cblk_parameter_t *_cblk)
{
	memset(_cblk,0,sizeof(Cblk_parameter_t));
	_cblk->type = DR_NULL;
	_cblk->active = false;
	_cblk->para = 0;
	_cblk->private_systick = 0;
	_cblk->EventCallback_t = 0;
}
void Drv_RegisterTIMER(void)
{
	Cblk_parameter_t cbkirq;
	_Clear_DrvPar(&cbkirq);
	cbkirq.type = DR_TIMER_SYS;
	Drv_RegisterIRQ_callback(cbkirq);
}
void DRV_TIMER_FNC(void *arg)
{
	for(uint8_t i=0; i<IRQ_MAX; i++)
	{
		if(IRQ_Arr[i].type == DR_NULL) return;

		if((IRQ_Arr[i].type) == DR_TIMER)
		{
			if(*(uint32_t*)IRQ_Arr[i].para != 0 && IRQ_Arr[i].para != 0)
			{
				if(++IRQ_Arr[i].private_systick >= (*(uint32_t*)IRQ_Arr[i].para) / DRV_TIMER_PERIOD)
				{
					if(IRQ_Arr[i].active == false)
					{
						IRQ_Arr[i].active = true;
					}
					IRQ_Arr[i].private_systick = 0;
				}
			}
			else if(!(*(uint32_t*)IRQ_Arr[i].para))
			{
				IRQ_Arr[i].private_systick = 0;
			}
		}
	}
}

void DRV_RUN(void)
{
	for(uint8_t i = 0; i<IRQ_MAX; i++)
	{
		if(IRQ_Arr[i].type == DR_NULL) return;
		if(IRQ_Arr[i].active && IRQ_Arr[i].type == DR_TIMER)
		{
			IRQ_Arr[i].EventCallback_t(0);
			IRQ_Arr[i].active=false;
		}
	}
}
/******************************************************************************/
/***                 INTERRUPT FUNCTIONS FOR THE DRIVER                      **/
/******************************************************************************/
bool Drv_RegisterIRQ_callback(Cblk_parameter_t cbk)
{
	uint8_t i;
	for(i=0;i<IRQ_MAX;i++)
	{
		if(IRQ_Arr[i].type == DR_NULL)
		{
			_Clear_DrvPar(&IRQ_Arr[i]);
			IRQ_Arr[i] = cbk;
			return true;
		}
	}
	return false;
}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UART_IRQ(uint32_t _uart)
{
	for(uint8_t i=0; i<IRQ_MAX; i++)
	{
		if(IRQ_Arr[i].type == DR_NULL)
		{
			return;
		}

		if(IRQ_Arr[i].type == DR_UART)
		{
			if(_uart == *(uint32_t*)IRQ_Arr[i].para)
			{
				IRQ_Arr[i].EventCallback_t(IRQ_Arr[i].para);
			}
		}
	}
}
