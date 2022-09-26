/*
 * SevSeg1_prog.c
 *
 *  Created on: Aug 9, 2022
 *      Author: basse
 */

#include <util/delay.h>

#include "../../Libraries/stdTypes.h"
#include "../../Libraries/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "SevSeg_priv.h"
#include "SevSeg_config.h"

extern u8 SevSeg_u8MaxModules;
extern u8 ModuleValuePins;
extern u8 ModuleControlPins;
extern SSegModule_t SSegModule[];

ES_t SevSeg_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	for( u8 Local_u8Counter = 0 ; Local_u8Counter <= SevSeg_u8MaxModules ; Local_u8Counter++)
	{
		for( u8 Local_u8PinNum = 0 ; Local_u8PinNum < ModuleValuePins ; Local_u8PinNum++ )
		{
			Local_enuErrorState = DIO_enuSetPinDirection(	SSegModule[Local_u8Counter].Value_Conf[Local_u8PinNum].InputGrp ,
															SSegModule[Local_u8Counter].Value_Conf[Local_u8PinNum].InputPin , DIO_u8OUTPUT);
			if( Local_enuErrorState != ES_OK) break;
		}
#if DIP_STATUS == DIP_ENABLED
		if( Local_enuErrorState == ES_OK)
		{
			Local_enuErrorState = DIO_enuSetPinDirection(	SSegModule[Local_u8Counter].DIP_Conf.InputGrp ,
															SSegModule[Local_u8Counter].DIP_Conf.InputPin , DIO_u8OUTPUT);
		}
#endif
		if( Local_enuErrorState == ES_OK)
		{
			Local_enuErrorState = DIO_enuSetPinDirection(	SSegModule[Local_u8Counter].Enable_Conf.InputGrp ,
															SSegModule[Local_u8Counter].Enable_Conf.InputPin , DIO_u8OUTPUT);
		}
		if( Local_enuErrorState != ES_OK) break;
	}

	return Local_enuErrorState ;//DONE
}
ES_t SevSeg_enuSetDigitValue(u8 Copy_u8ModuleNum , u8 Copy_u8SevSegDigitValue)
{
	ES_t Local_enuErrorState=ES_NOK ;
	
	if( ( (Copy_u8ModuleNum -= MODULE_1) < SevSeg_u8MaxModules ) &&	( Copy_u8SevSegDigitValue < DIGIT_BASE ) )
	{
		for( u8 Local_u8Counter = 0 ; Local_u8Counter < ModuleValuePins ; Local_u8Counter++ )
		{
			Local_enuErrorState = DIO_enuSetPinValue(	SSegModule[Copy_u8ModuleNum].Value_Conf[Local_u8Counter].InputGrp ,
														SSegModule[Copy_u8ModuleNum].Value_Conf[Local_u8Counter].InputPin ,
														( Copy_u8SevSegDigitValue >> Local_u8Counter ) & SevSeg_u8BIT_MASK );
			if( Local_enuErrorState != ES_OK) break;
		}
	}
	else Local_enuErrorState = ES_OUT_RANGE;


	return Local_enuErrorState ;//DONE
}

#if DIP_STATUS == DIP_ENABLED
ES_t SevSeg_enuSetDIPValue(u8 Copy_u8ModuleNum ,u8 Copy_u8SevSegDIPValue)
{
	ES_t Local_enuErrorState=ES_NOK;

	if( ( (Copy_u8ModuleNum -= MODULE_1) < SevSeg_u8MaxModules ) &&
		( Copy_u8SevSegDIPValue == DIP_ON ||Copy_u8SevSegDIPValue == DIP_OFF ) )
	{
		Local_enuErrorState = DIO_enuSetPinValue(	SSegModule[Copy_u8ModuleNum].DIP_Conf.InputGrp ,
													SSegModule[Copy_u8ModuleNum].DIP_Conf.InputPin  , Copy_u8SevSegDIPValue );
	}
	else Local_enuErrorState = ES_OUT_RANGE;

	return Local_enuErrorState ;//DONE
}
#endif

ES_t SevSeg_enuFrameDelay(u8 Copy_u8SevSegTotalModules, u8 *Copy_pu8SevSegModuleDelay)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8SevSegTotalModules <= SevSeg_u8MaxModules)
	{
		*Copy_pu8SevSegModuleDelay = SevSeg_u8MODULE_DELAY( Copy_u8SevSegTotalModules );

		Local_enuErrorState=ES_OK;
	}
	else Local_enuErrorState = ES_OUT_RANGE;

	return Local_enuErrorState ;//DONE
}

ES_t SevSeg_enuModuleControl(u8 Copy_u8SevSegModuleNum , u8 Copy_u8SevSegModuleStatus)
{
	ES_t Local_enuErrorState=ES_NOK;
	u8 Local_u8Output;

	if( ( Copy_u8SevSegModuleStatus == MODULE_DISABLE || Copy_u8SevSegModuleStatus == MODULE_ENABLE ) &&
		( Copy_u8SevSegModuleNum -= MODULE_1 < SevSeg_u8MaxModules ) )
	{
		Local_enuErrorState = DIO_enuSetPinValue(	SSegModule[Copy_u8SevSegModuleNum].Enable_Conf.InputGrp ,
													SSegModule[Copy_u8SevSegModuleNum].Enable_Conf.InputPin ,
													( Copy_u8SevSegModuleStatus - MODULE_DISABLE ) );	
	}
	else	Local_enuErrorState = ES_OUT_RANGE;

	return Local_enuErrorState ;//DONE
}

