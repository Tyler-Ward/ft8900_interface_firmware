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
#include "stream_processor.h"

#include "head_codes.h"
#include "body_codes.h"


char str[64];
int i=0;

int main(void)
{
	
	ErrorBufferInit();								//setup the error buffer
	
	DriverUSBUartInit();							//initilise the USB uart driver;
	StreamProcessorInit();							//sets up the processor for the 8900 data stream
	
	sei();											//enable global interrupts
	
	DriverUSBUartPut("Booted\r\n",8);
	
	char ReceivedByte;
	
	StreamProcessorBodySet((lcd_segment)APO);
	
    while(1)
    {
		StreamProcessorProcess();

		//check USB commands
		if (uartRecieveBuffer.enter)			// has a byte been received from the body
		{
			DriverUSBUartPut("\r\n",2);
			
			ReceivedByte = uartRecieveBuffer.buffer[uartRecieveBuffer.marker];						// Fetch the received byte value into the variable "ByteReceived"
			uartRecieveBuffer.enter=0;
			uartRecieveBuffer.length=0;
			
			if(ReceivedByte=='v')
			{

				sprintf(str,"volume= %d %d\r\n",headInput.array[4],headInput.array[6]);
				
				DriverUSBUartPutString(str);
			}

			if(ReceivedByte=='c')
			{
				char data6 = decode_char(bodyInput.array,&LEFT_NAME_6);
				char data5 = decode_char(bodyInput.array,&LEFT_NAME_5);
				char data4 = decode_char(bodyInput.array,&LEFT_NAME_4);
				char data3 = decode_char(bodyInput.array,&LEFT_NAME_3);
				char data2 = decode_char(bodyInput.array,&LEFT_NAME_2);
				char data1 = decode_char(bodyInput.array,&LEFT_NAME_1);
				
				sprintf(str,"CHR 6= %d, %d, %d, %d, %d, %d\r\n",data1,data2,data3,data4,data5,data6);
				
				DriverUSBUartPutString(str);
			}
		
			if(ReceivedByte=='s')
			{		
				char datal[12];
				char datar[12];
				char datalm[12];
				char datarm[12];
				
				decode_string(bodyInput.array,LEFT_NAME,datal);
				decode_string(bodyInput.array,RIGHT_NAME,datar);
				decode_string(bodyInput.array,LEFT_MEMORY,datalm);
				decode_string(bodyInput.array,RIGHT_MEMORY,datarm);
				
				sprintf(str,"STR LEFT= %s RIGHT= %s\r\nMEM LEFT= %s RIGHT= %s\r\n",datal,datar,datalm,datarm);
				
				DriverUSBUartPutString(str);
			}
			
			if(ReceivedByte=='p')
			{
				StreamProcessorBodySet((lcd_segment)APO);
				DriverUSBUartPutString("SET APO");
			}
		}

    }
}