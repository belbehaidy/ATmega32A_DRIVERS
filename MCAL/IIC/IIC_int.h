/*
 * IIC_int.h
 *
 *  Created on: Sep 16, 2022
 *      Author: basse
 */

#ifndef MCAL_IIC_IIC_INT_H_
#define MCAL_IIC_IIC_INT_H_

/************************************/
/*		TWI Operation Options		*/
/************************************/
#define TW_WRITE				20
#define TW_READ					23

ES_t IIC_enuInit(void);

ES_t IIC_enuStartCondition(void);	// Handles both Start Condition & Repeated Start Condition

ES_t IIC_enuStopCondition(void);

ES_t IIC_enuWriteSlaveAddress(u8 Copy_u8SlaveAddress , u8 Copy_u8Operation);

ES_t IIC_enuWriteData(u8 Copy_u8Data);

ES_t IIC_enuCheckMyAddress(void);

ES_t IIC_enuReadData(u8 * Copy_pu8Data);

#endif /* MCAL_IIC_IIC_INT_H_ */
