/*
 * debug_tools.c
 *
 * Created: 13/03/2016 22:46:12
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
#include "function_debug.h"

#include "head_codes.h"
#include "body_codes.h"

/*!
 * Produces a debug output of a character string from the body unit
 */
void DebugDisplayCharactersFunctionHandler(void *command)
{
	char str[32];		//string for storeing output in
	console_status_t *command_status = (console_status_t*) command;	//convert pointer into structure
	
	char* strptr;
	strptr=command_status->command_string;
	
	//advance to end of command string
	strptr+=command_status->command_arg_marker;	//advance the string pointer
	
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