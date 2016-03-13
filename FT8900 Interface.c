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
	
	sei();											//enable global interrupts
	
	DriverUSBUartPut("Booted\r\n",8);
	
    while(1)
    {
		StreamProcessorProcess();
		UsbConsoleProcess();

    }
}