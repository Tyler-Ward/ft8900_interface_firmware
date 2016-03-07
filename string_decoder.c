
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#include "error_codes.h"
#include "hardware.h"

#include "string_decoder.h"
#include "body_codes.h"
#include "character_map.h"

char decode_char(char* data,const lcd_character* letter)
{
	charmap_t letter_map; 
	
	//simple check to see if it is a T character
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
	
	int i=0;
	
	for(i=0;i<CHARMAP_MAX_CHAR;i++)
	{
		if(charmap[i].map==letter_map.map)
		{
			break;
		}
		//while ((UCSR0A & (1 << UDRE0)) == 0);
		//UART_USB_DATA=i+CHARMAP_OFFSET;
		
	}
	
	if(i==CHARMAP_MAX_CHAR)
	{
		//todo throw error
		return '\0';
	}
	else
	{
		return (char)(i+CHARMAP_OFFSET);
	}
	
	
	
}

int print_segments(charmap_t display)
{
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
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UART_USB_DATA='/';
	return(SUCCESS);
}

int decode_string(char* data,const lcd_string string,char* output)
{
	int i=0;
	
	for(i=0;i<string.length;i++)
	{
		output[i]=decode_char(data,string.characters[i]);
	}
	output[i]='\0';
	
	return SUCCESS;
}