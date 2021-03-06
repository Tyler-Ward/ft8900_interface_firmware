/*
 * function_autotune.c
 *
 * Created: 13/03/2016 23:30:53
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
#include "function_autotune.h"
#include "usb_console.h"

#include "head_codes.h"
#include "body_codes.h"

#include "button_control.h"

void AutotuneFunctionHandler (void* command)
{
	console_status_t *command_status = (console_status_t*) command;
	
	char* cmdptr;								//create cmdptr that can pass through the command string
	cmdptr=command_status->command_string;		//point cmdptr at the start of the string
	cmdptr+=command_status->command_arg_marker;	//advance the string pointer to start of arguments
	
	if(*cmdptr==' ')							//check if we have arguments
	{
		cmdptr++;								//advance onwards
	}
	else
	{
		DriverUSBUartPutString("No frequency provided\r\n");
		return;
	}
	
	int Mhz;
	int Khz;
	if(!AutotuneProcessFrequency(cmdptr,&Mhz,&Khz))
	{
		char str[16];
		sprintf(str,"FREQ= %d.%d\r\n",Mhz,Khz);
		DriverUSBUartPutString(str);
	}
	else
	{
		DriverUSBUartPutString("Invalid Frequency Format\r\n");
		return;
	}
	
	char memory[6];		//store memory location
	decode_string(bodyInput.array,LEFT_MEMORY,memory);
	if(!strncmp("   ",memory,3))		//check if in memory mode
	{
		DriverUSBUartPutString("not in memory mode\r\n");
	}
	else
	{
		DriverUSBUartPutString("in memory mode\r\n");
		ButtonControlPress((head_button_t){KEY1_LOC,KEY1_VM,0});	//go to vfo mode
	}
	
	int digit1=(Mhz/100)%10;
	int digit2=(Mhz/10)%10;
	int digit3=(Mhz)%10;
	int digit4=(Khz/100)%10;
	int digit5=(Khz/10)%10;
	int digit6=(Khz)%10;
	
	//type in frequency
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit1][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit1][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit2][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit2][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit3][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit3][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit4][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit4][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit5][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit5][0],0});
	ButtonControlPress2((head_button_t){MIC_48_SW2_LOC,KEYPAD_MAP[digit6][1],0},(head_button_t){MIC_48_SW1_LOC,KEYPAD_MAP[digit6][0],0});
	
}

/*!
 * Extracts a frequency in the form Mhz.Khz from a character string.
 *
 * \param frequency character pointer to the string containing the frequency to be decoded
 * \param Mhz in pointer to store decoded Mhz element of the frequency
 * \param Khz in pointer to store decoded Khz element of the frequency
 * \retval 
 */
int AutotuneProcessFrequency(char* frequency,int* Mhz,int* Khz)
{
	*Mhz =0;	//clear input frequencies
	*Khz =0;
	uint8_t KhzDigits=0;			//need to receive at least 3 digits
	int FrequencyProcessState=0;	//state of processing
	
	while(FrequencyProcessState!=3)						//wait until frequency has been extracted
	{
		switch(FrequencyProcessState)
		{
			//skip initial spaces if provided
			case 0:
				if (*frequency=='\0')					//check if we have a null pointer
				{
					return(ERR_AUTOTUNE_FREQUENCY_NULL_POINTER);	//report that we have a null string
				}
				if (*frequency!=' ')					//check that we have received a character other than space
				{
					FrequencyProcessState=1;			//move to Mhz processing
					continue;							//we still want to remain on this character
				}
				break;
			//decode mhz element
			case 1:
				if (*frequency>='0'&&*frequency<='9')	//if we have been provided a number
				{
					*Mhz *= 10;							//shift the current number up
					*Mhz += *frequency-'0';				//add the new number to the Mhz element
				}
				else if(*frequency=='.' && *Mhz>0)		//mhz separator received and a Mhz value has been provided
				{
					FrequencyProcessState=2;			//move onto Khz processing
				}
				else
				{
					return(ERR_AUTOTUNE_FREQUENCY_INVALID);	//not expecting any other characters here
				}
				
				break;
			case 2:
				if (*frequency>='0'&&*frequency<='9')	//if we have been provided a number
				{
					*Khz *= 10;							//shift the current number up
					*Khz += *frequency-'0';				//add the new number to the Khz element
					KhzDigits+=1;						//increment digit count
					if (KhzDigits==3)					//check if we have received enough digits
					{
						return(SUCCESS);				//we are done
					}
				}
				else if(*frequency==' ' || *frequency=='\0')	//have received and end separator so finished processing
				{
					while(KhzDigits<3)
					{
						*Khz *= 10;	//shift by non provided digits
						KhzDigits++;
					}
					return(SUCCESS);
				}
				else
				{
					return(ERR_AUTOTUNE_FREQUENCY_INVALID);	//not expecting other characters here
				}
				break;
		}
		frequency++;		//advance to next character
	}
	
	//todo might want a better error here
	return(ERR_AUTOTUNE_FREQUENCY_INVALID);		//frequency extraction completed
}