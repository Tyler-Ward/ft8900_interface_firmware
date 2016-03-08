/*
 * FT8900_Interface.c
 *
 * Created: 29/08/2015 15:01:42
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
#include "string_decoder.h"

#include "head_codes.h"
#include "body_codes.h"

unsigned int headPosition=0;
char headarray[16];

unsigned int bodyPosition=0;
char bodyarray[64];



int storeHeaddata(char data)
{
	if(data&0x80)
	{
		headPosition=0;
	}
	
	headarray[headPosition]=data;
	headPosition++;
	
	return(SUCCESS);
}

int storeBodydata(char data)
{
	if(data&0x80)
	{
		bodyPosition=0;
	}
	
	bodyarray[bodyPosition]=data;
	bodyPosition++;
	
	return(SUCCESS);
}


char str[64];
int i=0;

int main(void)
{
	
	ErrorBufferInit();								//setup the error buffer
	
	DriverUSBUartInit();							//initilise the USB uart driver;
	
	sei();											//enable global interrupts
	
	char ReceivedByte;
	
	//HEAD INTERFACE
	
	UCSR2A = (1 << U2X0);
	UCSR2B = (1 << RXEN2) | (1 << TXEN2);			//enable transmission and reception
	
	UBRR2H = (USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR2L = (USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits
	
	//BODY INTERFACE
	
	UCSR1A = (1 << U2X0);
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	
	UBRR1H = (USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
	UBRR1L = (USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits
	
    while(1)
    {
		
		//retransmit head
		if ((UCSR2A & (1 << RXC2)) != 0)			// has a byte been received from the head
		{
			ReceivedByte = UDR2;						// Fetch the received byte value into the variable "ByteReceived"
			
			while ((UCSR1A & (1 << UDRE1)) == 0);		// Do nothing until UDR is ready for more data to be written to it
			UDR1 = ReceivedByte;
			storeHeaddata(ReceivedByte);
		}

		//retransmit body
		if ((UCSR1A & (1 << RXC1)) != 0)			// has a byte been received from the body
		{
			ReceivedByte = UDR1;						// Fetch the received byte value into the variable "ByteReceived"
			
			while ((UCSR2A & (1 << UDRE2)) == 0);		// Do nothing until UDR is ready for more data to be written to it
			UDR2 = ReceivedByte;
			storeBodydata(ReceivedByte);
		}
		
		//check USB commands
		if (uartRecieveBuffer.enter)			// has a byte been received from the body
		{
			DriverUSBUartPut("\r\n",2);
			
			ReceivedByte = uartRecieveBuffer.buffer[uartRecieveBuffer.marker];						// Fetch the received byte value into the variable "ByteReceived"
			uartRecieveBuffer.enter=0;
			uartRecieveBuffer.length=0;
			
			if(ReceivedByte=='v')
			{

				sprintf(str,"volume= %d %d\r\n",headarray[4],headarray[6]);
				
				DriverUSBUartPutString(str);
			}

			if(ReceivedByte=='c')
			{
				char data6 = decode_char(bodyarray,&LEFT_NAME_6);
				char data5 = decode_char(bodyarray,&LEFT_NAME_5);
				char data4 = decode_char(bodyarray,&LEFT_NAME_4);
				char data3 = decode_char(bodyarray,&LEFT_NAME_3);
				char data2 = decode_char(bodyarray,&LEFT_NAME_2);
				char data1 = decode_char(bodyarray,&LEFT_NAME_1);
				
				sprintf(str,"CHR 6= %d, %d, %d, %d, %d, %d\r\n",data1,data2,data3,data4,data5,data6);
				
				DriverUSBUartPutString(str);
			}
		
			if(ReceivedByte=='s')
			{		
				char datal[12];
				char datar[12];
				char datalm[12];
				char datarm[12];
				
				decode_string(bodyarray,LEFT_NAME,datal);
				decode_string(bodyarray,RIGHT_NAME,datar);
				decode_string(bodyarray,LEFT_MEMORY,datalm);
				decode_string(bodyarray,RIGHT_MEMORY,datarm);
				
				sprintf(str,"STR LEFT= %s RIGHT= %s\r\nMEM LEFT= %s RIGHT= %s\r\n",datal,datar,datalm,datarm);
				
				DriverUSBUartPutString(str);
			}
		}

    }
}