/*
 * EXT_EEPROM_int.h
 *
 *  Created on: Sep 17, 2022
 *      Author: basse
 */

#ifndef HAL_EXT_EEPROM_EXT_EEPROM_INT_H_
#define HAL_EXT_EEPROM_EXT_EEPROM_INT_H_


ES_t EXT_EEPROM_enuInit( void );

ES_t EXT_EEPROM_enuWriteData( u16 Copy_u16Address , u8 Copy_u8Data );

ES_t EXT_EEPROM_enuReadData( u16 Copy_u16Address , u8 *Copy_pu8Data );

#endif /* HAL_EXT_EEPROM_EXT_EEPROM_INT_H_ */
