/*
 * EEPROM_prog.c
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#include "..\..\Libraries\stdTypes.h"
#include "..\..\Libraries\errorState.h"

#include "EEPROM_priv.h"

ES_t EEPROM_enuWriteByte( u16 Copy_u16Address , u8 Copy_u8Data )
{
	while( ( ( EECR_MM_ADD >> EEWE ) & BIT_MASK ) );
	while( ( ( SPMCR >> SPMEN ) & BIT_MASK ) );

	u8 Local_u8CopySREG = SREG ;
	asm("CLI");

	EEARH = ( Copy_u16Address >> BYTE_SHIFT );
	EEARL = (u8)Copy_u16Address;
	EEDR = Copy_u8Data ;
	asm( " SBI 0x1C,2 " );
	asm( " SBI 0x1C,1 " );

	SREG = Local_u8CopySREG ;
	return ES_OK;
}

ES_t EEPROM_enuReadByte( u16 Copy_u16Address , u8 *Copy_pu8Data )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_pu8Data != NULL )
	{
		while( ( ( EECR_MM_ADD >> EEWE ) & 1 ) );
		EEARH = ( Copy_u16Address >> BYTE_SHIFT );
		EEARL = (u8)Copy_u16Address;
		asm( " SBI 0x1C,0 " );
		* Copy_pu8Data = EEDR ;
		Local_enuErrorState = ES_OK ;
	}
	else Local_enuErrorState = ES_NULL_POINTER ;

	return Local_enuErrorState ;
}
