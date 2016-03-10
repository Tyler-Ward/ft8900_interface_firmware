/*
 * driver_usb_uart.h
 *
 * Created: 07/03/2016 23:34:01
 *  Author: Tyler
 */ 


#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#define UART_TRANSMIT_BUFFER_LENGTH 64
#define UART_RECIEVE_BUFFER_LENGTH 64

/* buffer for transmitted data */
typedef struct  
{
	volatile uint8_t marker;						//!< marker to next character to send
	volatile uint8_t length;						//!< length of the uart buffer
	volatile char buffer[UART_TRANSMIT_BUFFER_LENGTH];	//!< buffer for storing data
} uart_transmit_buffer_t;

/* buffer for received data */
typedef struct
{
	volatile uint8_t marker;						//!< marker to next character to send
	volatile uint8_t length;						//!< length of the uart buffer
	volatile uint8_t enter;						//!< marks received enter characters
	volatile char buffer[UART_RECIEVE_BUFFER_LENGTH];	//!< buffer for storing data
} uart_recieve_buffer_t;

/* FUNCTION DECLARATIONS *******************************************/

int DriverUSBUartInit();
int DriverUSBUartPut(char* text,uint8_t length);
int DriverUSBUartPutString(char* text);
int DriverUSBUartLoadCharacter();

extern uart_recieve_buffer_t uartRecieveBuffer;	//!< buffer for incoming data
extern uart_transmit_buffer_t uartTransmitBuffer;	//!< buffer for outgoing data

#endif /* DRIVER_UART_H_ */