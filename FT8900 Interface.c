/*
 * FT8900_Interface.c
 *
 * Created: 29/08/2015 15:01:42
 *  Author: Tyler
 */ 


#include <avr/io.h>

#include "hardware.h"
#include "peripherals.h"
#include "error_codes.h"

#include "error_buffer.h"

int main(void)
{
	
	ErrorBufferInit();								//setup the error buffer
	
	char ReceivedByte;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);			//enable USB USART
	
	UBRR0H = (USART_USB_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR0L = (USART_USB_BAUDRATE_PRESCALE);			//load baudrate lower bits
	
	UART_USB_DATA = 'R';
	
	
	//HEAD INTERFACE
	
	UCSR2B = (1 << RXEN2) | (1 << TXEN2);			//enable transmission and reception
	
	UBRR2H = 0x00;//(USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR2L = 51UL;//(USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits
	
	//BODY INTERFACE
	
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	
	UBRR1H = 0x00;//(USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR1L = 51UL;//(USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits	
	
    while(1)
    {
		
		//retransmit head
		if ((UCSR2A & (1 << RXC2)) != 0)			// has a byte been received from the head
		{
			ReceivedByte = UDR2;						// Fetch the received byte value into the variable "ByteReceived"
			
			while ((UCSR1A & (1 << UDRE1)) == 0);		// Do nothing until UDR is ready for more data to be written to it
			UDR1 = ReceivedByte;
			//while ((UCSR0A & (1 << UDRE0)) == 0);		// Do nothing until UDR is ready for more data to be written to it
		}

		//retransmit body
		if ((UCSR1A & (1 << RXC1)) != 0)			// has a byte been received from the body
		{
			ReceivedByte = UDR1;						// Fetch the received byte value into the variable "ByteReceived"
			
			while ((UCSR2A & (1 << UDRE2)) == 0);		// Do nothing until UDR is ready for more data to be written to it
			UDR2 = ReceivedByte;
			//while ((UCSR0A & (1 << UDRE0)) == 0);		// Do nothing until UDR is ready for more data to be written to it
		}
		
		//loopback USB
		if ((UCSR0A & (1 << RXC0)) != 0)			// has a byte been received from the body
		{
			ReceivedByte = UART_USB_DATA;						// Fetch the received byte value into the variable "ByteReceived"
					
			while ((UCSR0A & (1 << UDRE0)) == 0);		// Do nothing until UDR is ready for more data to be written to it
			UART_USB_DATA = ReceivedByte;
			//UART_HEAD_DATA = ReceivedByte;
			//UART_BODY_DATA = ReceivedByte;
		}

    }
}