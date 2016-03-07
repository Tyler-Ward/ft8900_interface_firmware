/*
 * string_decoder.h
 *
 * Created: 06/03/2016
 *  Author: Tyler
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#include "error_codes.h"
#include "hardware.h"

#include "string_decoder.h"
#include "body_codes.h"
#include "character_map.h"

/*! decodes a character from the LCD feed
 *
 * \param data The data from the body to the head unit
 * \param letter the letter location to be decoded 
 * \retval character ASCII character displayed on the screen
 */
char decode_char(char* data,const lcd_character* letter)
{
	charmap_t letter_map; 
	
	//Populate the letter map from the LCD feed
	letter_map.A = (data[letter->A.byte]&(1<<letter->A.bit))?1:0;
	letter_map.B = (data[letter->B.byte]&(1<<letter->B.bit))?1:0;
	letter_map.C = (data[letter->C.byte]&(1<<letter->C.bit))?1:0;
	letter_map.D = (data[letter->D.byte]&(1<<letter->D.bit))?1:0;
	letter_map.E = (data[letter->E.byte]&(1<<letter->E.bit))?1:0;
	letter_map.F = (data[letter->F.byte]&(1<<letter->F.bit))?1:0;
	letter_map.G1 = (data[letter->G1.byte]&(1<<letter->G1.bit))?1:0;
	letter_map.G2 = (data[letter->G2.byte]&(1<<letter->G2.bit))?1:0;
	letter_map.H = (data[letter->H.byte]&(1<<letter->H.bit))?1:0;
	letter_map.IL = (data[letter->IL.byte]&(1<<letter->IL.bit))?1:0;
	letter_map.J = (data[letter->J.byte]&(1<<letter->J.bit))?1:0;
	letter_map.K = (data[letter->K.byte]&(1<<letter->K.bit))?1:0;
	letter_map.M = (data[letter->M.byte]&(1<<letter->M.bit))?1:0;
	
	//print_segments(letter_map);
	
	int i=0;								//create itterable character
	
	for(i=0;i<CHARMAP_MAX_CHAR;i++)			//iterate through the character map
	{
		if(charmap[i].map==letter_map.map)	//if character map matches
		{
			break;							//exit for loop
		}	
	}
	
	if(i==CHARMAP_MAX_CHAR)					//check if we reached the end of the charmap
	{
		//todo throw error
		return '\0';						//return a null character
	}
	else
	{
		return (char)(i+CHARMAP_OFFSET);	//return the character with the required offset
	}
	
	
	
}

/*! Prints the segments activated for a character to the USB uart
 *
 * \param display a charmap of the character
 * \retval #SUCCESS
 */
int print_segments(charmap_t display)
{
	//todo use a better print function
	if(display.A)
	{
			while ((UCSR0A & (1 << UDRE0)) == 0);
			UART_USB_DATA='A';
	}
	if(display.B)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='B';
	}
	if(display.C)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='C';
	}
	if(display.D)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='D';
	}
	if(display.E)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='E';
	}
	if(display.F)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='F';
	}
	if(display.G1)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='G';
	}
	if(display.G2)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='g';
	}
	if(display.H)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='H';
	}
	if(display.IL)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='I';
	}
	if(display.J)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='J';
	}
	if(display.K)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='K';
	}
	if(display.M)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UART_USB_DATA='M';
	}
	
	//print trailing slash
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UART_USB_DATA='/';
	return(SUCCESS);	//return success
}

/*! decodes a string from the LCD feed
 *
 * \param data The data from the body to the head unit
 * \param string the lcd_string object for the location to be decoded 
 * \param output location so save decoded string
 * \retval #SUCCESS
 */
int decode_string(char* data,const lcd_string string,char* output)
{
	int i=0;						//create string iterator
	
	for(i=0;i<string.length;i++)	//for each character in string
	{
		output[i]=decode_char(data,string.characters[i]);	//run the decoder
	}
	output[i]='\0';					//add a null terminator to the string
	
	return SUCCESS;					//return success
}