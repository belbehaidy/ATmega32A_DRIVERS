/*
 * UART_prog.c
 *
 *  Created on: Sep 9, 2022
 *      Author: basse
 */

#include "..\..\Libraries\stdTypes.h"
#include "..\..\Libraries\errorState.h"

#include "UART_priv.h"
#include "UART_config.h"

UART_Int_t Global_AstrUART_Pointers[UART_INTERRUPTS] =	{
														{ RXCIE ,	NULL, NULL},
														{ UDRIE ,	NULL, NULL},
														{ TXCIE ,	NULL, NULL}
													};



ES_t UART_enuInit( void )
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8CopyUCSRC = 0x00;
	UCSRB = 0x00 ;
	UCSRA = 0x00 ;

	/************************************************/
	/*	Setting Multi-processor Communication Mode	*/
	/************************************************/
#if MULTI_PROCESSOR == MPCM_ON
	UCSRA |= (BIT_MASK << MPCM_BIT );
#endif

	/****************************************************************/
	/*	Setting Synchronous Mode / Operating Mode / Clock Polarity	*/
	/****************************************************************/
#if SYNC_MODE == ASYNCHRONOUS
	Local_u8CopyUCSRC &= ~(BIT_MASK << UMSEL_BIT );
	Local_u8CopyUCSRC &= ~(BIT_MASK << UCPOL_BIT );

	#if SPEED_MODE == NORMAL_SPEED
	UCSRA &=~(BIT_MASK << U2X_BIT );
	#elif SPEED_MODE == DOUBLE_SPEED
	UCSRA |= (BIT_MASK << U2X_BIT );
	#else
	#warning " UART_enuInit(): Unidentified Operating Mode. Switched to NORMAL_SPEED "
	#endif

#elif SYNC_MODE == SYNCHRONOUS
	UCSRA &=~(BIT_MASK << U2X_BIT );
	Local_u8CopyUCSRC |= (BIT_MASK << UMSEL_BIT );

	#if CLOCK_POLARITY == TX_RISING_EDGE
		Local_u8CopyUCSRC &= ~(BIT_MASK << UCPOL_BIT );
	#elif CLOCK_POLARITY == RX_RISING_EDGE
		Local_u8CopyUCSRC |= (BIT_MASK << UCPOL_BIT );
	#else
	#warning " UART_enuInit(): Unidentified Clock Polarity for Synchronous Operation . Switched to TX_RISING_EDGE Polarity "
	#endif

#else
#error " UART_enuInit(): Unidentified Synchronization Mode. "
#endif

	/************************************************/
	/*			Setting Frame Data bits 			*/
	/************************************************/
#if DATA_BITS >= FIVE_BITS && DATA_BITS <= EIGHT_BITS
	Local_u8CopyUCSRC |= ( ( DATA_BITS - FIVE_BITS )& TWO_BITS_MASK ) << UCSZ0_BIT ;
#elif DATA_BITS == NINE_BITS
	UCSRB |= (BIT_MASK << UCSZ2_BIT );
	Local_u8CopyUCSRC |= (TWO_BITS_MASK << UCSZ0_BIT ) ;
#else
	Local_u8CopyUCSRC |= (TWO_BITS_MASK << UCSZ0_BIT ) ;
#warning " UART_enuInit(): Unidentified Frame Data bits choice. 8-bits Choice is selected "
#endif

	/************************************************/
	/*			Setting Frame Parity bits 			*/
	/************************************************/
#if PARITY_STATUS == NO_PARITY
	Local_u8CopyUCSRC &= ~(BIT_MASK << UPM1_BIT );
	Local_u8CopyUCSRC &= ~(BIT_MASK << UPM0_BIT );
#elif PARITY_STATUS == EVEN_PARITY
	Local_u8CopyUCSRC |= (BIT_MASK << UPM1_BIT );
	Local_u8CopyUCSRC &= ~(BIT_MASK << UPM0_BIT );
#elif PARITY_STATUS == ODD_PARITY
	Local_u8CopyUCSRC |= (BIT_MASK << UPM1_BIT );
	Local_u8CopyUCSRC |= (BIT_MASK << UPM0_BIT );
#else
#warning " UART_enuInit(): Unidentified Parity bits choice. NO Parity is selected "
#endif

	/************************************************/
	/*			Setting Frame STOP bits 			*/
	/************************************************/
#if STOP_STATUS == ONE_STOP_BIT
	Local_u8CopyUCSRC &= ~(BIT_MASK << USBS_BIT );
#elif STOP_STATUS == TWO_STOP_BIT
	Local_u8CopyUCSRC |= (BIT_MASK << USBS_BIT );
#else
#warning " UART_enuInit(): Unidentified STOP bits choice. 1-STOP bit choice is selected "
#endif

	Local_u8CopyUCSRC |= (BIT_MASK << URSEL_BIT );		/*	Setting URSEL to 1 to access UCSRC register	*/
	UCSRC = Local_u8CopyUCSRC ;

	/************************************************/
	/*				Setting BAUD Rate	 			*/
	/************************************************/
	u16 Local_u16CopyUBRR = UBRR_VALUE( BAUD_RATE );
	UBRRH = ( Local_u16CopyUBRR >> BYTE_SHIFT ) ;
	UBRRL =  (u8)Local_u16CopyUBRR ;

	/************************************************/
	/*				Setting UART Mode	 			*/
	/************************************************/
	#if UART_MODE == TRANSMITTER
	UCSRB |= ( BIT_MASK << TXEN_BIT );
#elif UART_MODE == RECEIVER
	UCSRB |= ( BIT_MASK << RXEN_BIT );
#elif UART_MODE == TRANSCEIVER
	UCSRB |= ( BIT_MASK << TXEN_BIT );
	UCSRB |= ( BIT_MASK << RXEN_BIT );
#else
#warning " UART_enuInit(): Unidentified UART Mode. Disabled UART "
#endif

	return Local_enuErrorState ;
}

ES_t UART_ReceiveFrame( void *Copy_pReceivedData)
{
	ES_t Local_enuErrorState = ES_NOK;

	if( Copy_pReceivedData != NULL )
	{
		while( !( ( UCSRA >> RXC_BIT ) & BIT_MASK ) );		/*	Waiting for RX Complete Flag	*/

		/*	Reading Data From UDR according to Frame Data bits 	*/
#if( DATA_BITS == NINE_BITS )
		{
			u8 Local_u8CopySERG = SREG;
			asm(" CLI ");
			*( (u16 *)Copy_pReceivedData )  = 	0x00;
			*( (u16 *)Copy_pReceivedData )  =	(u16)( ( UCSRB >> RXB8_BIT ) & BIT_MASK ) << BYTE_SHIFT ;
			*( (u16 *)Copy_pReceivedData ) |=	RXB ;
			SREG = Local_u8CopySERG ;
		}
#else
		{
			*( (u8 *)Copy_pReceivedData ) = RXB ;
		}
#endif
		Local_enuErrorState = ES_OK;
	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState ;
}

ES_t UART_SendFrame( void *Copy_pData)
{
	ES_t Local_enuErrorState = ES_NOK;

	while( !( ( UCSRA>> UDRE_BIT ) & BIT_MASK ) );		/*	Waiting for UDR Empty Flag	*/

	/*	Writing Data To UDR according to Frame Data bits 	*/
#if( DATA_BITS == NINE_BITS )
	{
		u8 Local_u8CopySERG = SREG;
		asm(" CLI ");
		UCSRB &= ~(BIT_MASK << TXB8_BIT );
		UCSRB |= ( ( (*( (u16 *)Copy_pData )) >> BYTE_SHIFT ) & BIT_MASK ) << TXB8_BIT ;
		TXB = *( (u16 *)Copy_pData ) ;
		SREG = Local_u8CopySERG ;
	}
#else
	{
		TXB = *( (u8 *)Copy_pData ) ;					/*	Writing Data to UDR			*/
	}
#endif
	Local_enuErrorState = ES_OK ;

	return Local_enuErrorState ;
}


ES_t UART_enuSendString( char *Copy_pcData )
{
	ES_t Local_enuErrorState = ES_NOK;

#if DATA_BITS == EIGHT_BITS

	while( *Copy_pcData != '\0' )
	{
		while( !( ( UCSRA>> UDRE_BIT ) & BIT_MASK ) );		/*	Waiting for UDR Empty Flag			*/
		TXB = *Copy_pcData ;								/*	Writing Data to UDR					*/
		Copy_pcData++ ;										/*	Incrementing Pointer to next Char	*/
	}
	Local_enuErrorState = ES_OK ;
#else
		Local_enuErrorState = ES_OUT_RANGE;
#warning " UART_enuSendString() : Data bits should be EIGHT_BITS , can NOT Send string."
#endif

	return Local_enuErrorState ;
}

ES_t UART_enuReceiveString( char *Copy_pcData)
{
	ES_t Local_enuErrorState = ES_NOK;

	if( Copy_pcData != NULL )
	{

		#if DATA_BITS == EIGHT_BITS

			u8 Local_u8Data;

			while(1)
			{
				while( !( ( UCSRA >> RXC_BIT ) & BIT_MASK ) );									/*	Waiting for RX Complete Flag		*/
				Local_u8Data = RXB ;															/*	Reading Data Byte From UDR 		 	*/
				if( ( Local_u8Data == '\n' ) || ( Local_u8Data == '\r' ) || ( Local_u8Data == '\0' ) )
				{
					*Copy_pcData = '\0';														/*	Terminating String received			*/
					break;
				}
				*Copy_pcData = Local_u8Data ;													/*	Saving Data Byte To Data String  	*/
				Copy_pcData++;																	/*	Incrementing Pointer to next Byte	*/
			}
			Local_enuErrorState = ES_OK;

		#else
			Local_enuErrorState = ES_OUT_RANGE;
			#warning " UART_enuReceiveString() : Data bits should be EIGHT_BITS , can NOT receive string."
		#endif

	}
	else Local_enuErrorState = ES_NULL_POINTER;

	return Local_enuErrorState ;
}


ES_t UART_enuCallBack( u8 Copy_u8InterruptName , void ( *Copy_pAppFun )(void *) , void *Copy_pAppVar )
{
	ES_t Local_enuErrorState = ES_NOK;

	if( Copy_pAppFun != NULL )
	{

		u8 Local_u8Iter = 0 ;
		for( ; Local_u8Iter < UART_INTERRUPTS ; Local_u8Iter++ )
		{
			if( Global_AstrUART_Pointers[Local_u8Iter].InterruptName == Copy_u8InterruptName )
			{
				Global_AstrUART_Pointers[Local_u8Iter].ptrFun = Copy_pAppFun ;
				Global_AstrUART_Pointers[Local_u8Iter].ptrVar = Copy_pAppVar ;
				Local_enuErrorState = ES_OK;
				break;
			}
		}
		if( Local_u8Iter ==  UART_INTERRUPTS )
		{
			Local_enuErrorState = ES_OUT_RANGE;
			#warning " UART_enuCallBack() : Unidentified Interrupt Name, No Action Taken."
		}

	}
	else Local_enuErrorState = ES_NULL_POINTER ;

	return Local_enuErrorState ;
}


void __vector_13( void )__attribute__((signal));
void __vector_14( void )__attribute__((signal));
void __vector_15( void )__attribute__((signal));

void __vector_13( void )	/*	RXCIE : RX Complete Interrupt	*/
{
	if( Global_AstrUART_Pointers[0].ptrFun != NULL)
	{
		( *Global_AstrUART_Pointers[0].ptrFun )( Global_AstrUART_Pointers[0].ptrVar );
	}
}

void __vector_14( void )	/*	UDRE : UDR register Empty Interrupt	*/
{
	if( Global_AstrUART_Pointers[1].ptrFun != NULL)
	{
		( *Global_AstrUART_Pointers[1].ptrFun )( Global_AstrUART_Pointers[1].ptrVar );
	}
}

void __vector_15( void )	/*	TXCIE : TX Complete Interrupt	*/
{
	if( Global_AstrUART_Pointers[2].ptrFun != NULL)
	{
		( *Global_AstrUART_Pointers[2].ptrFun)( Global_AstrUART_Pointers[2].ptrVar );
	}
}
