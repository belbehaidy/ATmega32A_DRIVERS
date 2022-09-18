/*
 * EXT_EEPROM_prog.c
 *
 *  Created on: Sep 17, 2022
 *      Author: Bassem El-behaidy
 */

#include "..\..\Libraries\stdTypes.h"
#include "..\..\Libraries\errorState.h"

#include "..\..\MCAL\IIC\IIC_int.h"

#include "EXT_EEPROM_priv.h"
#include "EXT_EEPROM_config.h"

extern u8 EXT_EEPROM_Size ;
extern u8 EXT_EEPROM_MaxNum ;
extern EXT_EEPROM_t EXT_EEPROM[] ;


ES_t EXT_EEPROM_enuInit( void )			/*	Wrapper Function	*/
{
	return ( IIC_enuInit() ) ;
}

ES_t EXT_EEPROM_enuWriteData( u16 Copy_u16Address , u8 Copy_u8Data )
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 SlaveAddress , ByteAddress = (u8)Copy_u16Address ;

	for( u8 Local_u8Iter = 0 ; Local_u8Iter < EXT_EEPROM_MaxNum ; Local_u8Iter++)
	{
		if( EXT_EEPROM[Local_u8Iter].EEPROM_Size == EXT_EEPROM_Size)
		{
			if( EXT_EEPROM[Local_u8Iter].A2_Status == NOT_CONNECTED )					/*	16K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( ( Copy_u16Address >> BYTE_SHIFT ) & THREE_BIT_MASK ) ) ;
			}
			else if( EXT_EEPROM[Local_u8Iter].A1_Status == NOT_CONNECTED )				/*	8K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( ( Copy_u16Address >> BYTE_SHIFT ) & TWO_BIT_MASK ) ) ;
			}
			else if( EXT_EEPROM[Local_u8Iter].A0_Status == NOT_CONNECTED )				/*	4K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A1_Status << A1_BIT )
														| ( ( Copy_u16Address >> BYTE_SHIFT ) & BIT_MASK ) ) ;
			}
			else																		/*	2K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A1_Status << A1_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A0_Status << A0_BIT ) ) ;
			}
		}
	}

	if( IIC_enuStartCondition() == ES_OK )
	{
		if( IIC_enuWriteSlaveAddress( SlaveAddress , TW_WRITE ) == ES_OK )
		{
			if( IIC_enuWriteData( ByteAddress ) == ES_OK )
			{
				if( IIC_enuWriteData( Copy_u8Data ) == ES_OK )
				{
					Local_enuErrorState = IIC_enuStopCondition() ;
				}
			}
		}
	}

	return Local_enuErrorState ;
}



ES_t EXT_EEPROM_enuReadData( u16 Copy_u16Address , u8 *Copy_pu8Data )
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 SlaveAddress , ByteAddress = (u8)Copy_u16Address ;

	for( u8 Local_u8Iter = 0 ; Local_u8Iter < EXT_EEPROM_MaxNum ; Local_u8Iter++)
	{
		if( EXT_EEPROM[Local_u8Iter].EEPROM_Size == EXT_EEPROM_Size)
		{
			if( EXT_EEPROM[Local_u8Iter].A2_Status == NOT_CONNECTED )					/*	16K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( ( Copy_u16Address >> BYTE_SHIFT ) & THREE_BIT_MASK ) ) ;
			}
			else if( EXT_EEPROM[Local_u8Iter].A1_Status == NOT_CONNECTED )				/*	8K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( ( Copy_u16Address >> BYTE_SHIFT ) & TWO_BIT_MASK ) ) ;
			}
			else if( EXT_EEPROM[Local_u8Iter].A0_Status == NOT_CONNECTED )				/*	4K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A1_Status << A1_BIT )
														| ( ( Copy_u16Address >> BYTE_SHIFT ) & BIT_MASK ) ) ;
			}
			else																		/*	2K Configuration	*/
			{
				SlaveAddress = (   SLAVE_ADDRESS_PREFIX | ( EXT_EEPROM[Local_u8Iter].A2_Status << A2_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A1_Status << A1_BIT )
														| ( EXT_EEPROM[Local_u8Iter].A0_Status << A0_BIT ) ) ;
			}
		}
	}

	if( IIC_enuStartCondition() == ES_OK )
	{
		if( IIC_enuWriteSlaveAddress( SlaveAddress , TW_WRITE ) == ES_OK )
		{
			if( IIC_enuWriteData( ByteAddress ) == ES_OK )
			{
				if( IIC_enuStartCondition() == ES_OK )
				{
					if( IIC_enuWriteSlaveAddress( SlaveAddress , TW_READ ) == ES_OK )
					{
						if( IIC_enuReadData( Copy_pu8Data ) == ES_OK )
						{
							Local_enuErrorState = IIC_enuStopCondition() ;
						}
					}
				}
			}
		}
	}

	return Local_enuErrorState ;
}
