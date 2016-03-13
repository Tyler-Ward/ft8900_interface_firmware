/*
 * usb_console.c
 *
 * Created: 12/03/2016 22:18:47
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

static command_t commands[] = {
	{"AT+ERRORS", handler_error},
	{"AT+VOLUME", handler_volume},
	{"AT+READ_DISPLAY",handler_read_display},
		
	//debug functions
	{"AT+DEBUG_TEXT",handler_display_read_debug},
		
	//test functions
	{"AT+TEST_SET_DISPLAY",handler_set_display},
	{"AT+TEST_CLEAR_DISPLAY",handler_clear_display},
				
	//null command to end search
	{0x00,0x00}
};


char ReceivedByte;
char str[64];
int i=0;

int UsbConsoleProcess()
{
	//check USB commands
	if (uartRecieveBuffer.enter)			// has a byte been received from the body
	{
		DriverUSBUartPut("\r\n",2);
		UsbConsoleInterpretCommand(&(uartRecieveBuffer.buffer[uartRecieveBuffer.marker]),10);
		
		uartRecieveBuffer.enter=0;
		uartRecieveBuffer.length=0;
	}
	return(SUCCESS);
}

int UsbConsoleInterpretCommand(char *command,uint8_t command_length)
{
	uint8_t i = 0;
	
	while(commands[i].handler)
	{
		if(!strncmp(commands[i].commandName,command,strlen(commands[i].commandName)))
		{
			commands[i].handler((void *) command);	//call the command
			return(SUCCESS);						//exit while loop
		}
		i++;	//increment iterable
	}
	

	return(ERR_COMMAND_NOT_FOUND);
}

static void handler_error(void *command)
{
	DriverUSBUartPutString("ERRORS\r\n");
}

static void handler_volume(void *command)
{
	sprintf(str,"volume= %d %d\r\n",headInput.array[4],headInput.array[6]);
	DriverUSBUartPutString(str);
}

static void handler_read_display(void *command)
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

/*!
 * Produces a debug output of a character string from the body unit
 */
static void handler_display_read_debug(void *command)
{
	char* strptr=command;	//create a pointer to the command string
	strptr+=strlen("AT+DEBUG_TEXT");	//advance the string pointer
	
	const lcd_string* string_ref = NULL;		//create a null pointer to the string to process
	
	//work out what string we want to debug
	if(!strncmp(" LEFT_NAME",strptr,strlen(" LEFT_NAME")))
	{
		string_ref = &LEFT_NAME;
	}
	if(!strncmp(" LEFT_MEMORY",strptr,strlen(" LEFT_MEMORY")))
	{
		string_ref = &LEFT_MEMORY;
	}
	if(!strncmp(" RIGHT_NAME",strptr,strlen(" RIGHT_NAME")))
	{
		string_ref = &RIGHT_NAME;
	}
	if(!strncmp(" RIGHT_MEMORY",strptr,strlen(" RIGHT_MEMORY")))
	{
		string_ref = &RIGHT_MEMORY;
	}
	
	
	if (string_ref==NULL)					//if we have not provided a valid string
	{
		DriverUSBUartPutString("Unrecognized string");
		return;		
	}

	sprintf(str,"CHARACTERS = %d[",string_ref->length);	//prepare the start of the display info message
	DriverUSBUartPutString(str);						//send the start of the packet
	
	int i=0;								//create a variable to iterate through the strings characters
	
	for(i=0;i<string_ref->length;i++)		//for each letter in string
	{
		char decoded = decode_char(bodyInput.array,string_ref->characters[i]);	//calculate the character
		
		sprintf(str,"%d,",decoded);			//prepare a string with the character id in decimal
		DriverUSBUartPutString(str);		//send the sting
	}
	
	DriverUSBUartPutString("]\r\n");		//close the array and place a newline

}

static void handler_set_display(void *command)
{
	StreamProcessorBodySetText(&LEFT_NAME,"TESTS");
}

static void handler_clear_display(void *command)
{
	StreamProcessorBodyReturnText(&LEFT_NAME);
}
