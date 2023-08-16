/*
 *              Copyright (c)  2023
 *  File header: 		drv_atcmd.h
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */

#ifndef DRV_ATCMD_H_
#define DRV_ATCMD_H_

#include "main.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f3xx_hal.h"


#define   ATC_CMSIS_OS                            (0)
#define   ATC_TXDMA                               (0) // not supported yet, comming soon
#define   ATC_MAX_ELEMENTS                        (1)
#define   ATC_MAX_URC_SEARCHING_STRING   		  (20)
#define 	ARR_MALLOC							  (0)
#if !ARR_MALLOC
#define 	ATC_MAX_URC_SEARCHING_SIZE			  (20)
#define 	ATC_MAX_ANSWER_SEARCHING_SIZE		  (20)
#define 	ATC_RX_MAX_BUF						  (RX_MAX_BUF)
#endif
#define   ATC_MAX_ANSWER_SEARCHING_STRING         (5)


typedef void (*URC_CallBack)(char*,char*);

typedef enum
{
	ATC_FAIL = -1, 			    // sending fail
	ATC_TIMEOUT,				// Timeout waiting response
	ATC_ERR,  					// reponse ERROR
	ATC_SUCCESS,				// Reponse OK
}
ATC_cmd_status_t;

typedef enum
{
  ATC_Element_Error = -1,
  ATC_Element_0,
  ATC_Element_1,
  ATC_Element_2,
  ATC_Element_3,
  ATC_Element_4
}
ATC_Element_t;


typedef struct
{
  ATC_Element_t	  id;
  peripheral_t    usart;
  char      	  name[10];
  uint64_t        rxTime;
  uint8_t         rxTmp;
  uint16_t        rxIndex;
  uint16_t        rxSize;
  uint16_t        rxTimeout;
  uint8_t         txBusy;
  int8_t          foundAnswer;
  uint16_t        foundAnswerSize;
  char*           foundAnswerString;
  uint8_t		  rxBuffer[ATC_RX_MAX_BUF];
  char            answerSearchingString[ATC_MAX_ANSWER_SEARCHING_STRING][ATC_MAX_ANSWER_SEARCHING_SIZE];
  char            alwaysSearchingString[ATC_MAX_URC_SEARCHING_STRING][ATC_MAX_URC_SEARCHING_SIZE];
  void            (*URC_CallBack)(char*,char*);
}
ATC_t;


typedef enum
{
	AT_RSP=0,
	AT_URC,
	AT_ALL,
	AT_HEX,
}
PROCCESS_TYPE;


void            atc_process(PROCCESS_TYPE _type);
void            atc_callback_devide(ATC_Element_t ATC_Element);
void 			atc_callback(void * arg);
void            atc_callback_txDMA(ATC_Element_t ATC_Element);
bool            atc_init(ATC_Element_t ATC_Element,  uint32_t baudrate,peripheral_t usart, uint16_t rxSize, uint16_t rxTimeout, char* name);
bool 			atc_URCregister(ATC_Element_t ATC_Element, URC_CallBack urcCallback, char *_urcArray[]);
uint8_t         atc_sendAtCommand(ATC_Element_t ATC_Element, char *atCommand, uint32_t wait_ms, char *answerString, uint16_t answerSize, uint8_t searchingItems,...);
uint8_t 		atc_sendDataAtCommand(ATC_Element_t ATC_Element, uint8_t *atCommand,uint16_t sizedata, uint32_t wait_ms, char *answerString, uint16_t answerSize, uint8_t searchingItems,...);
bool            atc_addURCSearchString(ATC_Element_t ATC_Element, char *str);

uint8_t         atc_sendString(ATC_Element_t ATC_Element, char *str, uint32_t timeout);
uint8_t         atc_sendData(ATC_Element_t ATC_Element, uint8_t *data, uint16_t size, uint32_t timeout);
ATC_Element_t   atc_getElementByName(char *name);
ATC_Element_t 	atc_getElementByUart(uint32_t uart);
uint16_t        atc_getSize(ATC_Element_t ATC_Element);

void            atc_userFoundString(ATC_Element_t ATC_Element, char* foundStr, char* startPtr);
uint16_t 		atc_parser(char* _rslt,char* _data,char *_header,char*_end);
bool 			atc_parser_U8(uint8_t* rslt,uint8_t *data,uint16_t size_data,char *header,char* endpoint);
bool 			atc_wait_ms(uint32_t _ms,PROCCESS_TYPE mode);
ATC_t* 			atc_getPoiterElementByID(ATC_Element_t id);
void 			atc_clearElementDataByID(ATC_Element_t id);
int8_t 			atcSendCmd_waitU8_malloc(ATC_Element_t ATC_Element, char *atCommand,uint16_t size_wait,uint32_t _timeout_ms,uint8_t rsp_num,...);


#endif /* DRV_ATCMD_H_ */
