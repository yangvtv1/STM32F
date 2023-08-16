/*
 *              Copyright (c)  2023
 *  File header: 		drv_atcmd.c
 *  Created on : 		August 14, 2023
 *      Author : 		Luong_Thanh_Hai (Embedded Software Engineer)
 *      Contact:        elvis.luong@gmail.com
 */


#include "drv_atcmd.h"

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

/******************************************************************************/
/******************************************************************************/
/***                                Global Parameters                        **/
/******************************************************************************/
/******************************************************************************/
uint8_t     atc_cnt;
ATC_t       atc_elements[ATC_MAX_ELEMENTS];
ATC_Element_t ATC_Element = ATC_Element_0;
/******************************************************************************/
/******************************************************************************/
/***                            Private functions                            **/
/******************************************************************************/
/******************************************************************************/
void  atc_userFoundString(ATC_Element_t ATC_Element, char* foundStr, char* startPtr)
{
	if(atc_elements[ATC_Element].URC_CallBack != NULL)
	{
		atc_elements[ATC_Element].URC_CallBack(foundStr, startPtr);
	}
}

void atc_callback(void *arg)
{
	if(atc_elements[ATC_Element].rxIndex < atc_elements[ATC_Element].rxSize - 1)
	{
		atc_elements[ATC_Element].rxBuffer[atc_elements[ATC_Element].rxIndex] = *(uint8_t*)arg;
		atc_elements[ATC_Element].rxIndex++;
	}
	atc_elements[ATC_Element].rxTime = DRV_GETTICK();
}

void atc_process(PROCCESS_TYPE _type)
{
  for(uint8_t el = 0; el < atc_cnt ; el++)
  {
    if((atc_elements[el].rxIndex > 0) && (DRV_GETTICK() - atc_elements[el].rxTime > atc_elements[el].rxTimeout))
    {
		LOGA(DRV,"Ele(%d)%s << {%s}\r\n",el,atc_elements[el].name,(char*)atc_elements[el].rxBuffer);
		for(uint8_t ans = 0 ; ans < ATC_MAX_ANSWER_SEARCHING_STRING ; ans++)
		{
			if(atc_elements[el].answerSearchingString[ans] == NULL)
			{
				break;
			}
			char *ansStr = strstr((char*)atc_elements[el].rxBuffer, (char*)atc_elements[el].answerSearchingString[ans]);
			if(ansStr!=NULL)
			{
				if(strlen((char*)atc_elements[el].rxBuffer) <= atc_elements[el].foundAnswerSize)
				{
					strcpy(atc_elements[el].foundAnswerString,(char*)atc_elements[el].rxBuffer);
				}
				else
				{
					strncpy(atc_elements[el].foundAnswerString,(char*)atc_elements[el].rxBuffer,atc_elements[el].foundAnswerSize);
				}
				atc_elements[el].foundAnswer = ans;
				break;
			}
		}

		for(uint8_t au = 0 ; au < ATC_MAX_URC_SEARCHING_STRING ; au++)
		{
			if(atc_elements[el].alwaysSearchingString[au] == NULL)
				continue;

			char *autoStr = strstr((char*)atc_elements[el].rxBuffer, atc_elements[el].alwaysSearchingString[au]);
			if(autoStr != NULL)
			{
				atc_userFoundString((ATC_Element_t)el, atc_elements[el].alwaysSearchingString[au], autoStr);
			}
		}
		atc_elements[el].rxIndex = 0;
		memset(atc_elements[el].rxBuffer, 0, atc_elements[el].rxSize);
    }
  }
}
/******************************************************************************/
/******************************************************************************/
/***                      Processing functions Callback                      **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                            MainRun functions                            **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                            Public functions                             **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                            Library callback                             **/
/******************************************************************************/
/******************************************************************************/





