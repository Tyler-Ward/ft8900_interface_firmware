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
#include "usb_console.h"

#include "head_codes.h"
#include "body_codes.h"

int main(void)
{
	
	ErrorBufferInit();								//setup the error buffer
	
	DriverUSBUartInit();							//initilise the USB uart driver;
	StreamProcessorInit();							//sets up the processor for the 8900 data stream
	
	UsbConsoleInit();								//sets up the USB console environment
	
	sei();											//enable global interrupts
	
	ErrorBufferPut(INF_BOOT);						//log that we have booted
	DriverUSBUartPut("Booted\r\n",8);				//print that we have booted on the USB console
	
    while(1)
    {
		StreamProcessorProcess();					//run the stream processor
		UsbConsoleProcess();						//check for incoming commands

    }
}