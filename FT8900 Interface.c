/*
 * FT8900_Interface.c
 *
 * Created: 29/08/2015 15:01:42
 *  Author: Tyler
 */ 


#include <avr/io.h>

#include "hardware.h"
#include "peripherals.h"

int main(void)
{
	char ReceivedByte;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);			//enable USB USART
	//UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);		//use 8bit values
	
	UBRR0H = (USART_USB_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR0L = (USART_USB_BAUDRATE_PRESCALE);			//load baudrate lower bits
	
	UDR0 = 'R';										//test UART is working
	
    while(1)
    {
        while ((UCSR0A & (1 << RXC0)) == 0);		// Do nothing until data have been received and is ready to be read from UDR
        ReceivedByte = UDR0;						// Fetch the received byte value into the variable "ByteReceived"

        while ((UCSR0A & (1 << UDRE0)) == 0);		// Do nothing until UDR is ready for more data to be written to it
        UDR0 = ReceivedByte;						// Echo back the received byte back to the computer
    }
}