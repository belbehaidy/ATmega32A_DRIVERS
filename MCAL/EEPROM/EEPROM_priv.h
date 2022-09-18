/*
 * EEPROM_priv.h
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#ifndef MCAL_EEPROM_EEPROM_PRIV_H_
#define MCAL_EEPROM_EEPROM_PRIV_H_

#define	BYTE_SHIFT		8


#define	EEARH			*( ( u8 *)0x3F )
#define	EEARL			*( ( u8 *)0x3E )
#define	EEDR			*( ( u8 *)0x3D )
#define	EECR_MM_ADD		*( ( u8 *)0x3C )
#define EERIE					3			/*	EEPROM Peripheral Interrupt Enable	*/
#define EEMWE					2			/*	EEPROM Master Write Enable			*/
#define EEWE					1			/*	EEPROM Write Enable					*/
#define EERE					0			/*	EEPROM Read Enable					*/

#define	EECR_IO_ADD			0x1C




#endif /* MCAL_EEPROM_EEPROM_PRIV_H_ */
