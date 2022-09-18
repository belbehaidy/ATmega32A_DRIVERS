/*
 * errorState.h
 *
 *  Created on: Aug 6, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef ERRORSTATE_H_
#define ERRORSTATE_H_

typedef enum
{
	ES_OK,
	ES_NOK,
	ES_OUT_RANGE,
	ES_NULL_POINTER,
	ES_NACK,
	ES_ARB_LOST,
	ES_OWN_SLA_R,
	ES_OWN_SLA_W,
	ES_NOT_OWN_SLA,
	ES_TW_SR_STOP,
}ES_t;

#endif /* ERRORSTATE_H_ */
