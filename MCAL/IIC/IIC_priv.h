/*
 * IIC_priv.h
 *
 *  Created on: Sep 16, 2022
 *      Author: basse
 */

#ifndef MCAL_IIC_IIC_PRIV_H_
#define MCAL_IIC_IIC_PRIV_H_

#define BIT_MASK			0x01

#define CPU_CLOCK			16000000UL
#define TWBR_VALUE(	SCL_FREQ )		( ( CPU_CLOCK - ( 16ul * SCL_FREQ ) ) / ( 2ul * SCL_FREQ *TWI_PRES ) )

/************************************/
/*	TWI General Call Reply Options	*/
/************************************/
#define GC_OFF					10
#define GC_ON					13

/************************************/
/*		TWI Operation Options		*/
/************************************/
#define TW_WRITE				20
#define TW_READ					23

/************************************/
/*		TWI Prescaler Options		*/
/************************************/
#define	TWI_PRES_1				1
#define	TWI_PRES_4				4
#define	TWI_PRES_16				16
#define	TWI_PRES_64				64

/****************************************************************************************/
/*					TWI STATUS REGISTER VALUE AFTER EACH OPERATION						*/
/****************************************************************************************/
#define TW_START					0x08	/*	start condition transmitted				*/
#define TW_REP_START				0x10	/*	Repeated start condition transmitted	*/
				/********************************************/
				/*			Master Transmitter Mode			*/
				/********************************************/
#define TW_MT_SLA_ACK				0x18	/*	SLA+W transmitted, ACK received			*/
#define TW_MT_SLA_NACK				0x20	/*	SLA+W transmitted, No ACK received		*/
#define TW_MT_DATA_ACK				0x28	/*	data transmitted, ACK received			*/
#define TW_MT_DATA_NACK				0x30	/*	data transmitted, No ACK received		*/
#define TW_MT_ARB_LOST				0x38	/*	arbitration lost in SLA+W or data 		*/
				/********************************************/
				/*			Master Receiver Mode			*/
				/********************************************/
#define TW_MR_ARB_LOST				0x38	/*	Arbitration lost in SLA+R or No ACK	*/
#define TW_MR_SLA_ACK				0x40	/*	SLA+R transmitted, ACK received		*/
#define TW_MR_SLA_NACK				0x48	/*	SLA+R transmitted, No ACK received	*/
#define TW_MR_DATA_ACK				0x50	/*	Data received, ACK returned			*/
#define TW_MR_DATA_NACK				0x58	/*	Data received, No ACK returned		*/
				/********************************************/
				/*			Slave Transmitter Mode			*/
				/********************************************/
#define TW_ST_SLA_ACK				0xA8	/*	SLA+R received, ACK returned		*/
#define TW_ST_ARB_LOST_SLA_ACK		0xB0	/*	Arbitration lost in SLA+RW, SLA+R received, ACK returned	*/
#define TW_ST_DATA_ACK				0xB8	/*	Data transmitted, ACK received 		*/
#define TW_ST_DATA_NACK				0xC0	/*	Data transmitted, NACK received 	*/
#define TW_ST_LAST_DATA				0xC8	/*	Last data byte transmitted, ACK received */
				/********************************************/
				/*			Slave Receiver Mode			*/
				/********************************************/
#define TW_SR_SLA_ACK				0x60	/*	SLA+W received, ACK returned 		*/
#define TW_SR_ARB_LOST_SLA_ACK		0x68	/*	Arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_GCALL_ACK				0x70	/*	General call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK	0x78	/*	Arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_DATA_ACK				0x80	/*	Data received, ACK returned 		*/
#define TW_SR_DATA_NACK				0x88	/*	Data received, NACK returned 		*/
#define TW_SR_GCALL_DATA_ACK		0x90	/*	General call data received, ACK returned */
#define TW_SR_GCALL_DATA_NACK		0x98	/*	General call data received, NACK returned */
#define TW_SR_STOP					0xA0	/*	Stop or repeated start condition received while selected */
				/********************************************/
				/*			Miscellaneous States			*/
				/********************************************/
#define TW_NO_INFO					0xF8	/*	No state information available	*/
#define TW_BUS_ERROR				0x00	/*	Illegal start or stop condition	*/
/****************************************************************************************/
/****************************************************************************************/



/********************************************/
/*			TWI Control Register			*/
/********************************************/
#define TWCR			*( (u8*)0x56 )
#define TWINT				7					/*	TWI Interrupt Flag		*/	//	must be cleared by software by writing Logic One to it
#define TWEA				6					/*	TWI Enable ACK bit		*/	//	1: ACK bit is generated on bus 	0:	device is virtually disconnected
#define TWSTA				5					/*	TWI START Condition bit	*/	//	must be cleared by software after START condition has been transmitted
#define TWSTO				4					/*	TWI STOP Condition bit	*/
#define TWWC				3					/*	TWI Write Collision Flag*/	//	Cleared by writing the TWDR while TWINT is HIGH
#define TWEN				2					/*	TWI Enable Bit			*/
/*....RESERVED BIT......RESERVED BIT......RESERVED BIT......RESERVED BIT....*/
#define TWIE				0					/*	TWI Interrupt Enable	*/

/********************************************/
/*			TWI Bit Rate Register			*/
/********************************************/
#define TWBR			*( (u8*)0x20 )

/********************************************/
/*			TWI Status Register				*/
/********************************************/
#define TWSR			*( (u8*)0x21 )
#define TWS7				7					/***** TWI Status bits ******/
#define TWS6				6					/***** TWI Status bits ******/
#define TWS5				5					/***** TWI Status bits ******/
#define TWS4				4					/***** TWI Status bits ******/
#define TWS3				3					/***** TWI Status bits ******/
/*....RESERVED BIT......RESERVED BIT......RESERVED BIT......RESERVED BIT....*/
#define TWPS1				1					/**** TWI Prescaler bits ****/
#define TWPS0				0					/* 00:1 /01:4 /10:16 /11:64 */

/********************************************/
/*			TWI Address Register			*/
/********************************************/
#define TWAR			*( (u8*)0x22 )
#define TWA6				7					/***** TWI Address bits ******/
#define TWA5				6					/***** TWI Address bits ******/
#define TWA4				5					/***** TWI Address bits ******/
#define TWA3				4					/***** TWI Address bits ******/
#define TWA2				3					/***** TWI Address bits ******/
#define TWA1				2					/***** TWI Address bits ******/
#define TWA0				1					/***** TWI Address bits ******/
#define TWGCE				0					/* TWI General Call Recognition Enable bit	*/

/********************************************/
/*			TWI Data Register				*/
/********************************************/
#define TWDR			*( (u8*)0x23 )


#define TWI_STATUS		(TWSR & 0xF8)

#define TWI_PRES_1_BITS		0x00
#define TWI_PRES_4_BITS		0x01
#define TWI_PRES_16_BITS	0x02
#define TWI_PRES_64_BITS	0x03

#endif /* MCAL_IIC_IIC_PRIV_H_ */
