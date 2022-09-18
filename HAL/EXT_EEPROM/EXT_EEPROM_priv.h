/*
 * EXT_EEPROM_priv.h
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#ifndef HAL_EXT_EEPROM_EXT_EEPROM_PRIV_H_
#define HAL_EXT_EEPROM_EXT_EEPROM_PRIV_H_

#define BYTE_SHIFT				0x08
#define BIT_MASK				0x01
#define TWO_BIT_MASK			0x03
#define THREE_BIT_MASK			0x07

#define SLAVE_ADDRESS_PREFIX	0x50		//	01010xxx where x are saved as Zeros in prefix

#define EXT_EEPROM_2K			20
#define EXT_EEPROM_4K			23
#define EXT_EEPROM_8K			26
#define EXT_EEPROM_16K			29

#define CONNECTED_TO_GROUND		0x00
#define	CONNECTED_TO_VCC		0x01
#define	NOT_CONNECTED			45

#define A2_BIT					2
#define A1_BIT					1
#define A0_BIT					0

#endif /* HAL_EXT_EEPROM_EXT_EEPROM_PRIV_H_ */
