/*
 * IIC_prog.c
 *
 *  Created on: Sep 16, 2022
 *      Author: basse
 */

#include "..\..\Libraries\stdTypes.h"
#include "..\..\Libraries\errorState.h"


#include "IIC_priv.h"
#include "IIC_config.h"


ES_t IIC_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	/*	Setting TWI Slave Address and General Call Response	*/
	TWAR = 0x00 ;
	TWAR = ( TWI_ADDRESS << TWA0 ) | (u8)( ( ( GENERAL_CALL_REPLY - GC_OFF ) / 3 ) << TWGCE );

	/*	Setting TWI Prescaler & TWI Bit rate 	*/
	TWBR = TWBR_VALUE(	SCL_FREQ ) ;
	TWSR = 0x00 ;
	switch( TWI_PRES )
	{
		case TWI_PRES_1		:	TWSR = ( TWI_PRES_1_BITS << TWPS0 ) ;
			break;
		case TWI_PRES_4		:	TWSR = ( TWI_PRES_4_BITS << TWPS0 ) ;
			break;
		case TWI_PRES_16	:	TWSR = ( TWI_PRES_16_BITS << TWPS0 ) ;
			break;
		case TWI_PRES_64	:	TWSR = ( TWI_PRES_64_BITS << TWPS0 ) ;
			break;
		default :	Local_enuErrorState = ES_OUT_RANGE;
	}

	/*	Setting TWI Control Register	*/
	u8 Local_u8TWCRCopy = 0x00 ;
//	Local_u8TWCRCopy |=	  ( BIT_MASK << TWINT ) ;		/*	Clearing Interrupt Flag		*/
	Local_u8TWCRCopy |=	  ( BIT_MASK << TWEA  ) ;		/*	Enable ACK bit				*/
	Local_u8TWCRCopy |=	  ( BIT_MASK << TWEN  ) ;		/*	Enable TWI Interrupt		*/
	Local_u8TWCRCopy |=	  ( BIT_MASK << TWIE  ) ;		/*	Enable TWI 					*/

	TWCR = Local_u8TWCRCopy ;

	return ( Local_enuErrorState == ES_NOK ? ES_OK : Local_enuErrorState );
}

ES_t IIC_enuStartCondition(void)	// Handles both Start Condition & Repeated Start Condition
{

	ES_t Local_enuErrorState = ES_NOK ;

	u8 Local_u8TWCRCopy = TWCR ;

	Local_u8TWCRCopy |=	  ( BIT_MASK << TWINT ) ;		/*	Clearing Interrupt Flag		*/
	Local_u8TWCRCopy |=	  ( BIT_MASK << TWSTA ) ;		/*	Set Start Condition bit		*/
	Local_u8TWCRCopy &=	  ( BIT_MASK << TWSTO ) ;		/*	Clear Stop Condition Bit	*/
	Local_u8TWCRCopy |=	  ( BIT_MASK << TWEN  ) ;		/*	Enable TWI 					*/

	TWCR = Local_u8TWCRCopy ;

	while( !( (TWCR >> TWINT )& BIT_MASK ) );

	if( TWI_STATUS == TW_START || TWI_STATUS == TW_REP_START )
	{
		Local_enuErrorState = ES_OK ;
	}

	return Local_enuErrorState ;
}

ES_t IIC_enuStopCondition(void)
{
	u8 Local_u8TWCRCopy = TWCR ;

	Local_u8TWCRCopy |= ( BIT_MASK << TWINT );				/*	Clearing Interrupt Flag		*/
	Local_u8TWCRCopy |= ( BIT_MASK << TWSTO ) ;				/*	Set Stop Condition Bit		*/
	Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTA ) ;			/*	Clear Start Condition Bit	*/
	Local_u8TWCRCopy |= ( BIT_MASK << TWEN );				/*	Enable TWI					*/

	TWCR = Local_u8TWCRCopy ;

	return ES_OK ;
}

ES_t IIC_enuWriteSlaveAddress(u8 Copy_u8SlaveAddress , u8 Copy_u8Operation )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_u8Operation == TW_WRITE || Copy_u8Operation == TW_READ )
	{
		u8 Local_u8TWCRCopy = TWCR ;

		TWDR = ( ( Copy_u8SlaveAddress << BIT_MASK) | ( Copy_u8Operation - TW_WRITE ) / 3 ) ;

		Local_u8TWCRCopy |= ( BIT_MASK << TWINT );				/*	Clearing Interrupt Flag		*/
		Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTO ) ;			/*	Clear Stop Condition Bit	*/
		Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTA ) ;			/*	Clear Start Condition Bit	*/
		Local_u8TWCRCopy |= ( BIT_MASK << TWEN );				/*	Enable TWI					*/
		TWCR = Local_u8TWCRCopy ;

		while( !( (TWCR >> TWINT )& BIT_MASK ) );

		if(	( ( TWI_STATUS == TW_MT_SLA_ACK ) && ( Copy_u8Operation == TW_WRITE ) ) ||			/*	Master Transmitter Mode	*/
			( ( TWI_STATUS == TW_MR_SLA_ACK ) && ( Copy_u8Operation == TW_READ  ) ) )			/*	Master Receiver Mode	*/
		{
			Local_enuErrorState = ES_OK ;
		}
		else if( 	( ( TWI_STATUS == TW_MT_SLA_NACK ) && ( Copy_u8Operation == TW_WRITE ) ) ||		/*	Master Transmitter Mode	NOT ACK */
					( ( TWI_STATUS == TW_MR_SLA_NACK ) && ( Copy_u8Operation == TW_READ  ) ) )		/*	Master Receiver Mode NOT ACK	*/
		{
			Local_enuErrorState = ES_NACK ;
		}
		else if( ( ( TWI_STATUS == TW_MR_ARB_LOST ) && ( Copy_u8Operation == TW_READ  ) ) )			/*	Master Receiver Mode ARB LOST	*/
		{
			Local_enuErrorState = ES_ARB_LOST ;
		}
		else if( TWI_STATUS == TW_ST_ARB_LOST_SLA_ACK ) 		/*	Master Transmitter/Receiver Mode ARB LOST & owns SLA+R,ACK returned	*/
		{
			Local_enuErrorState = ES_OWN_SLA_R ;
		}
		else if( ( TWI_STATUS == TW_SR_ARB_LOST_SLA_ACK   ) ||	/*	Master Transmitter/Receiver Mode ARB LOST & owns SLA+W, ACK returned	*/
				 ( TWI_STATUS == TW_SR_ARB_LOST_GCALL_ACK ) )	/*	Master Transmitter/Receiver Mode ARB LOST & General Call ACK returned	*/
		{
			Local_enuErrorState = ES_OWN_SLA_W ;
		}
	}
	else Local_enuErrorState = ES_OUT_RANGE ;

	return Local_enuErrorState ;
}

ES_t IIC_enuWriteData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK ;

	u8 Local_u8TWCRCopy = TWCR ;

	TWDR = Copy_u8Data ;

	Local_u8TWCRCopy |= ( BIT_MASK << TWINT );				/*	Clearing Interrupt Flag		*/
	Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTO ) ;			/*	Clear Stop Condition Bit	*/
	Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTA ) ;			/*	Clear Start Condition Bit	*/
	Local_u8TWCRCopy |= ( BIT_MASK << TWEN );				/*	Enable TWI					*/
	TWCR = Local_u8TWCRCopy ;

	while( !( (TWCR >> TWINT )& BIT_MASK ) );

	if(	( TWI_STATUS == TW_MT_DATA_ACK  ) ||				/*	Master Transmitter Mode,ACK returned	*/
		( TWI_STATUS == TW_ST_DATA_ACK  ) ||				/*	Slave Transmitter Mode,ACK returned		*/
		( TWI_STATUS == TW_ST_DATA_NACK ) ||				/*	Slave Transmitter Mode,NOT ACK			*/
		( TWI_STATUS == TW_ST_LAST_DATA )  )				/*	Slave Transmitter Mode,Last data byte transmitted, ACK received	*/
	{
		Local_enuErrorState = ES_OK ;
	}
	else if( TWI_STATUS == TW_MT_DATA_NACK )				/*	Master Transmitter Mode,NO ACK returned	*/
	{
		Local_enuErrorState = ES_NACK ;
	}
	else if( TWI_STATUS == TW_MR_ARB_LOST )					/*	Master Receiver Mode ARB LOST			*/
	{
		Local_enuErrorState = ES_ARB_LOST ;
	}

	return Local_enuErrorState ;
}

ES_t IIC_enuCheckMyAddress(void)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( (TWCR >> TWINT )& BIT_MASK )
	{
		if( TWI_STATUS == TW_ST_SLA_ACK )					/*	Slave Transmitter Mode, ACK returned	*/
		{
			Local_enuErrorState = ES_OWN_SLA_R ;
		}
		else if( ( TWI_STATUS == TW_SR_SLA_ACK  ) ||		/*	Slave Receiver Mode, SLA+W received, ACK returned		*/
				 ( TWI_STATUS == TW_SR_GCALL_ACK) )			/*	Slave Receiver Mode, General call received,ACK returned	*/
		{
			Local_enuErrorState = ES_OWN_SLA_W ;
		}
	}
	else Local_enuErrorState = ES_NOT_OWN_SLA ;

	return Local_enuErrorState ;
}

ES_t IIC_enuReadData(u8 * Copy_pu8Data)
{
	ES_t Local_enuErrorState = ES_NOK ;

	u8 Local_u8TWCRCopy = TWCR ;

	Local_u8TWCRCopy |= ( BIT_MASK << TWINT );				/*	Clearing Interrupt Flag		*/
	Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTO ) ;			/*	Clear Stop Condition Bit	*/
	Local_u8TWCRCopy &= ~ ( BIT_MASK << TWSTA ) ;			/*	Clear Start Condition Bit	*/
	Local_u8TWCRCopy |= ( BIT_MASK << TWEN );				/*	Enable TWI					*/

	TWCR = Local_u8TWCRCopy ;

	while( !( (TWCR >> TWINT )& BIT_MASK ) );

	if(	( TWI_STATUS == TW_MR_DATA_ACK			)		||				/*	Master Receiver Mode, Data Received , ACK returned			*/
		( TWI_STATUS == TW_MR_DATA_NACK			)		||				/*	Master Receiver Mode, Data Received , NO ACK returned		*/
		( TWI_STATUS == TW_SR_DATA_ACK			)		||				/*	Slave Receiver Mode, Data Received , ACK returned			*/
		( TWI_STATUS == TW_SR_DATA_NACK			)		||				/*	Slave Receiver Mode, Data Received , NO ACK returned		*/
		( TWI_STATUS == TW_SR_GCALL_DATA_ACK	)		||				/*	Slave Receiver Mode, Gen Call Data Received, ACK returned	*/
		( TWI_STATUS == TW_SR_GCALL_DATA_NACK	)  		)				/*	Slave Receiver Mode, Gen Call Data Received, NO ACK returned*/
	{
		*Copy_pu8Data = TWDR ;
		Local_enuErrorState = ES_OK ;
	}
	else if( TWI_STATUS == TW_SR_STOP )									/*	Slave Receiver Mode, Stop/Repeated Start Condition Received	*/
	{
		Local_enuErrorState = ES_TW_SR_STOP ;
	}

	return Local_enuErrorState ;
}
