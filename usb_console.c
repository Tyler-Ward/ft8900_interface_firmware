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

//command function files
#include "function_debug.h"
#include "function_autotune.h"
#include "button_control.h"


#include <util/delay.h>

/*! Create command table */
static command_t commands[] = {
	{"AT+ERRORS", handler_error},
	{"AT+VOLUME", handler_volume},
	{"AT+READ_DISPLAY",handler_read_display},
		
	{"AT+TUNE",AutotuneFunctionHandler},
		
	//debug functions
	{"AT+DEBUG_TEXT",DebugDisplayCharactersFunctionHandler},
		
	//test functions
	{"AT+TEST_SET_DISPLAY",handler_set_display},
	{"AT+TEST_CLEAR_DISPLAY",handler_clear_display},
	{"AT+TEST_PRESS_SET",handler_press_set},
				
	//null command to end search
	{0x00,0x00}
};

console_status_t console_status;


char ReceivedByte;
char str[64];
int i=0;

/*!
 * Sets up the USB console.
 *
 * \retval #SUCCESS as cannot fail.
 */
int UsbConsoleInit()
{
	console_status.command_list=commands;		//load command list into console struct
	
	console_status.command_length=0;			//no command in buffer
	console_status.command_status=CONSOLE_COMMAND_STATE_NONE;	//no command is currently processing
	
	return(SUCCESS);
}

/*!
 * Checks for incoming commands and starts processing if required.
 *
 * \retval any errors encountered in starting the next command
 */
int UsbConsoleProcess()
{
	//check USB commands
	if (uartRecieveBuffer.enter)			// has a byte been received from the body
	{
		DriverUSBUartPut("\r\n",2);			// print a newline
		
		//copy command into console status buffer
		int i=0;							//value for iterating through provided string
		while(i<uartRecieveBuffer.length)
		{
			char letter=uartRecieveBuffer.buffer[(uartRecieveBuffer.marker+i)%UART_RECIEVE_BUFFER_LENGTH];
			if (letter=='\r' || letter=='\n' || letter=='\0')
			{
				console_status.command_string[i]='\0';	//null terminate command
				break;
			}
			console_status.command_string[i]=letter;	//add letter to string
			i++;										//move to next letter
		}
		DriverUSBUartPutString(console_status.command_string);
		
		console_status.command_length=i;				//save command length
		
		UsbConsoleInterpretCommand(&console_status);
		
		//todo check for multiple commands at once
		uartRecieveBuffer.enter=0;			//command has been completed
		uartRecieveBuffer.length=0;			//no data in buffer
	}
	return(SUCCESS);
}

/*!
 * Produces a debug output of a character string from the body unit
 *
 * \retval errors on command processing or #SUCCESS if command ran successfully
 */
int UsbConsoleInterpretCommand(console_status_t *console_status)
{
	uint8_t i = 0;					//variable to iterate through command list
	
	while(console_status->command_list[i].handler)		//while there are commands in the command list
	{
		if(!strncmp(console_status->command_list[i].commandName,console_status->command_string,strlen(console_status->command_list[i].commandName)))	//if the command matches
		{
			console_status->command_arg_marker=strlen(console_status->command_list[i].commandName);		//store the length of the command
			console_status->command_list[i].handler((void *) console_status);							//call the command
			return(SUCCESS);																			//exit while loop
		}
		i++;	//move ontop the next command
	}
	
	return(ERR_COMMAND_NOT_FOUND);	//report that the command could not be found
}

void handler_volume(void *command)
{
	sprintf(str,"volume= %d %d\r\n",headInput.array[4],headInput.array[6]);
	DriverUSBUartPutString(str);
}

void handler_read_display(void *command)
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

void handler_set_display(void *command)
{
	StreamProcessorBodySetText(&LEFT_NAME,"TESTS");
}

void handler_clear_display(void *command)
{
	StreamProcessorBodyReturnText(&LEFT_NAME);
}

void handler_press_set(void *command)
{
	DriverUSBUartPutString("typing 145350");
	//ButtonControlPress((head_button_t){MIC_SW1_LOC,MIC_SW1_ACC,0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[1][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[1][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[4][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[4][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[5][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[5][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[3][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[3][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[5][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[5][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[0][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[0][0],0});
	DriverUSBUartPutString("typeing done");
}