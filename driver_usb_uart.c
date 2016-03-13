/*
 * driver_usb_uart.c
 *
 * Created: 07/03/2016 23:33:47
 *  Author: Tyler
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "hardware.h"
#include "peripherals.h"
#include "error_codes.h"

#include "error_buffer.h"
#include "driver_usb_uart.h"

uart_recieve_buffer_t uartRecieveBuffer;	//!< buffer for incoming data
uart_transmit_buffer_t uartTransmitBuffer;	//!< buffer for outgoing data

/*!Setup the USB uart
 *
 * \return #SUCCESS as cannot fail
 */
int DriverUSBUartInit()
{
	UCSR0A = (1 << U2X0);							//set fast clock mode
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1<<RXCIE0) | (1<<UDRIE0);			//enable USB USART with RX and TX interrupts
		
	UBRR0H = (USART_USB_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR0L = (USART_USB_BAUDRATE_PRESCALE);			//load baudrate lower bits
	
	uartTransmitBuffer.length=0;					//no data stored
	uartTransmitBuffer.marker=0;					//start at beginning of buffer
	
	uartRecieveBuffer.length=0;						//no data stored
	uartRecieveBuffer.marker=0;						//start at beginning of buffer
	
	return SUCCESS;
}

/*!Loads a character buffer into the outgoing buffer
 *
 * \return #ERR_USB_UART_TRANSMIT_BUFFER_FULL on buffer full otherwise #SUCCESS
 */
int DriverUSBUartPut(char* text,uint8_t length)
{
	if(length>(UART_TRANSMIT_BUFFER_LENGTH-uartTransmitBuffer.length))
	{
		return(ERR_USB_UART_TRANSMIT_BUFFER_FULL);	//report that the buffer is full
	}
	
	int i=0;	//create iterator
	
	for(i=0;i<length;i++)	//for input character
	{
		uartTransmitBuffer.buffer[(uartTransmitBuffer.marker+uartTransmitBuffer.length+i)%UART_TRANSMIT_BUFFER_LENGTH]=text[i];	//load text into buffer
	}
	uartTransmitBuffer.length+=length;	//increase length of string in store
	
	DriverUSBUartLoadCharacter();	//start transmission if required
	UCSR0B |= (1<<UDRIE0);
	
	return(SUCCESS);	//load complete
}

/*!Loads a string into the outgoing buffer
 *
 * \return #ERR_USB_UART_TRANSMIT_BUFFER_FULL on buffer full otherwise #SUCCESS
 */
int DriverUSBUartPutString(char* text)
{
	return(DriverUSBUartPut(text,strlen(text)));	//call the put function with the generated length
}

/*!Loads a character into the TX FIFO
 *
 * \return #SUCCESS as cannot fail
 */
int DriverUSBUartLoadCharacter()
{
	if(uartTransmitBuffer.length>0)		//if there is more data to send
	{
		if(UCSR0A & (1 << UDRE0))		//check that we can load in data (can be called when data is already in the buffer)
		{
			UART_USB_DATA=uartTransmitBuffer.buffer[uartTransmitBuffer.marker];		//load data into the buffer
			uartTransmitBuffer.marker=(uartTransmitBuffer.marker+1)%UART_TRANSMIT_BUFFER_LENGTH;	//advance the ring buffer marker
			uartTransmitBuffer.length--;	//reduce count of data in buffer
		}
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);			//if no more data to send then disable RX empty interrupts
	}
	return(SUCCESS);					//completed
}

/*!USB Uart receive interrupt
 *
 */
ISR(UART_USB_RX_vect)
{
	char data = UART_USB_DATA;	//collect data from interface

	if(uartRecieveBuffer.length==UART_RECIEVE_BUFFER_LENGTH)	//check for a buffer overflow
	{
		uartRecieveBuffer.length=0;		//clear the buffer
		uartRecieveBuffer.marker=0;		//start at the beginning
		ErrorBufferPut(ERR_USB_UART_RECIEVE_BUFFER_FULL);	//report this error
	}
	
	
	uartRecieveBuffer.buffer[(uartRecieveBuffer.marker+uartRecieveBuffer.length)%UART_RECIEVE_BUFFER_LENGTH]=data;	//load the data into the receive buffer
	uartRecieveBuffer.length++;		//increment receive count
	
	if(data=='\r' || data=='\n')	//look for a newline character
	{
		uartRecieveBuffer.enter++;	//increase the received newline count
	}
}

/*!USB Uart transmit interrupt
 *
 */
ISR(UART_USB_UDRE_vect)
{
	DriverUSBUartLoadCharacter(); //trigger transmission of next byte
}