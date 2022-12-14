/*
 * UART_config.h
 *
 *  Created on: Sep 9, 2022
 *      Author: basse
 */

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_

#define DATA_BITS			EIGHT_BITS

#define PARITY_STATUS		NO_PARITY

#define STOP_STATUS			ONE_STOP_BIT

#define BAUD_RATE			9600UL

#define UART_MODE			TRANSCEIVER

#define SYNC_MODE			ASYNCHRONOUS

#define SPEED_MODE			DOUBLE_SPEED

#define MULTI_PROCESSOR		MPCM_OFF

#define CLOCK_POLARITY		TX_RISING_EDGE

#endif /* MCAL_UART_UART_CONFIG_H_ */
