/*
 * EXT_EEPROM_config.h
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#ifndef HAL_EXT_EEPROM_EXT_EEPROM_CONFIG_H_
#define HAL_EXT_EEPROM_EXT_EEPROM_CONFIG_H_

#include "EXT_EEPROM_priv.h"

typedef struct
{
	u8 EEPROM_Size;
	u8 A2_Status;
	u8 A1_Status;
	u8 A0_Status;
}EXT_EEPROM_t;

#define EXT_EEPROM_TYPE			EXT_EEPROM_8K

#define EXT_EEPROM_MAX_NUM			4

/********************************************/
/*		EXT_EEPROM_2K Configuration			*/
/********************************************/
#define A2_2K_STATUS	CONNECTED_TO_GROUND
#define A1_2K_STATUS	CONNECTED_TO_GROUND
#define A0_2K_STATUS	CONNECTED_TO_GROUND

/********************************************/
/*		EXT_EEPROM_4K Configuration			*/
/********************************************/
#define A2_4K_STATUS	CONNECTED_TO_GROUND
#define A1_4K_STATUS	CONNECTED_TO_GROUND
#define A0_4K_STATUS	NOT_CONNECTED

/********************************************/
/*		EXT_EEPROM_8K Configuration			*/
/********************************************/
#define A2_8K_STATUS	CONNECTED_TO_GROUND
#define A1_8K_STATUS	NOT_CONNECTED
#define A0_8K_STATUS	NOT_CONNECTED

/********************************************/
/*		EXT_EEPROM_16K Configuration			*/
/********************************************/
#define A2_16K_STATUS	NOT_CONNECTED
#define A1_16K_STATUS	NOT_CONNECTED
#define A0_16K_STATUS	NOT_CONNECTED


#endif /* HAL_EXT_EEPROM_EXT_EEPROM_CONFIG_H_ */
