/*
 * EXT_EEPROM_config.c
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#include "..\..\Libraries\stdTypes.h"
#include "..\..\Libraries\errorState.h"

#include "EXT_EEPROM_priv.h"
#include "EXT_EEPROM_config.h"


u8 EXT_EEPROM_Size = EXT_EEPROM_TYPE ;
u8 EXT_EEPROM_MaxNum = EXT_EEPROM_MAX_NUM ;

EXT_EEPROM_t EXT_EEPROM[EXT_EEPROM_MAX_NUM] =	{
													{ EXT_EEPROM_2K	,	A2_2K_STATUS ,	A1_2K_STATUS ,	A0_2K_STATUS },
													{ EXT_EEPROM_4K ,	A2_4K_STATUS ,	A1_4K_STATUS ,	A0_4K_STATUS },
													{ EXT_EEPROM_8K ,	A2_8K_STATUS ,	A1_8K_STATUS ,	A0_8K_STATUS },
													{ EXT_EEPROM_16K ,	A2_16K_STATUS ,	A1_16K_STATUS ,	A0_16K_STATUS }
												};
