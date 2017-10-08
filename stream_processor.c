/*
 * stream_processor.c
 *
 * Created: 08/03/2016 21:49:36
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
#include "character_map.h"

#include "head_codes.h"
#include "body_codes.h"

#include "stream_processor.h"

stream_buffer_t bodyInput;					//!< input stream from the body

stream_buffer_t headInput;					//!< input stream from the head

char bodyStreamMask[BODY_STREAM_LENGTH];	//!< stores the mask for the stream modifications
char bodyStreamData[BODY_STREAM_LENGTH];	//!< stores the data for the modified stream

char headStreamMask[HEAD_STREAM_LENGTH];	//!< stores the mask for the stream modifications
char headStreamData[HEAD_STREAM_LENGTH];	//!< stores the data for the modified stream

/*!
 * Sets up the stream processor and associated UARTS
 *
 * \return #SUCCESS as cannot fail
 */
int StreamProcessorInit()
{
		//HEAD INTERFACE
		
		UCSR2A = (1 << U2X2);
		UCSR2B = (1 << RXEN2) | (1 << TXEN2) | (1 << RXCIE2);// | (1<<UDRIE2);			//enable transmission and reception with RX and TX interrupts
		
		UBRR2H = (USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
		UBRR2L = (USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits
		
		//BODY INTERFACE
		
		UCSR1A = (1 << U2X1);
		UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);// | (1<<UDRIE1);			//enable transmission and reception with RX and TX interrupts
		
		UBRR1H = (USART_FT8900_BAUDRATE_PRESCALE >> 8);	//load baudrate upper bits
		UBRR1L = (USART_FT8900_BAUDRATE_PRESCALE);		//load baudrate lower bits
		
		//clear buffers
		
		bodyInput.readposition=BODY_STREAM_LENGTH;
		bodyInput.writeposition=0;
		
		headInput.readposition=HEAD_STREAM_LENGTH;
		headInput.writeposition=0;
		
		//clear mask
		
		int i=0;
		
		for(i=0;i<BODY_STREAM_LENGTH;i++)
		{
			bodyStreamMask[i]=0;
		}
		
		for(i=0;i<HEAD_STREAM_LENGTH;i++)
		{
			headStreamMask[i]=0;
		}
		
		DriverUSBUartPutString("Stream running\r\n");
		
		return (SUCCESS);
}


/*!
 * Performs processing on any waiting bytes
 *
 * \return #SUCCESS as cannot fail
 */
int StreamProcessorProcess()
{
		return(SUCCESS);
}

/*!
 * sets an LCD segment to be on
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodySet(lcd_segment segment)
{
	if(segment.byte>BODY_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	if(segment.bit>=7)									//check for invalid bit positions
	{
		return(ERR_STREAM_SEGMENT_BIT_OUT_OF_RANGE);	//report this error
	}
	
	bodyStreamMask[segment.byte]|=(1<<segment.bit);		//set mask
	bodyStreamData[segment.byte]|=(1<<segment.bit);		//set data
	return(SUCCESS);									//completed
}

/*!
 * sets an LCD segment to be off
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodyClear(lcd_segment segment)
{
	if(segment.byte>BODY_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	if(segment.bit>=7)									//check for invalid bit positions
	{
		return(ERR_STREAM_SEGMENT_BIT_OUT_OF_RANGE);	//report this error
	}
	
	bodyStreamMask[segment.byte]|=(1<<segment.bit);		//set mask
	bodyStreamData[segment.byte]&=~(1<<segment.bit);	//set data
	return(SUCCESS);									//completed
}

/*!
 * sets an LCD segment based on a provided value
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodyValue(lcd_segment segment,uint8_t value)
{
	if(segment.byte>BODY_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	if(segment.bit>=7)									//check for invalid bit positions
	{
		return(ERR_STREAM_SEGMENT_BIT_OUT_OF_RANGE);	//report this error
	}
	
	value&=0x01;										//ensure only last bit is set
	
	bodyStreamMask[segment.byte]|=(1<<segment.bit);		//set mask
	bodyStreamData[segment.byte]|=(value<<segment.bit);	//set data
	return(SUCCESS);									//completed
}

/*!
 * returns control of an LCD segment to the main unit
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodyReturn(lcd_segment segment)
{
	if(segment.byte>BODY_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	if(segment.bit>=7)									//check for invalid bit positions
	{
		return(ERR_STREAM_SEGMENT_BIT_OUT_OF_RANGE);	//report this error
	}
	
	bodyStreamMask[segment.byte]&=~(1<<segment.bit);	//set mask
	return(SUCCESS);									//completed
}

/*!
 * Sets the string on the display to the sent string
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodySetText(const lcd_string* const string,char* text)
{
	int i=0;						//create an variable for iterating through the characters
	int strptr=0;					//create a variable for moving through the string
	
	for(i=0;i<string->length;i++)	//for each character in the lcd string
	{
		char character=text[strptr];	//load the next characted from the string
		
		if(character=='\0'||character=='\r'||character=='\n')	//if string has ended
		{
			character=' ';	//set character to space instead
		}
		else
		{
			strptr++;		//if there are more characters in the string move onto the next one
		}
		
		StreamProcessorSetCharacter(string->characters[i],character);	//set the character
	}
	return(SUCCESS);		//all done
}

/*!
 * Returns control of the string on the display to the body
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorBodyReturnText(const lcd_string* const string)
{
	int i=0;
	
	for(i=0;i<string->length;i++)
	{
		StreamProcessorReturnCharacter(string->characters[i]);
	}
	return(SUCCESS);
}

/*!
 * Sets a character on the display to a given letter
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorSetCharacter(const lcd_character* const character,char letter)
{
	charmap_t map;									//charmap to load into
	map.map = charmap[letter-CHARMAP_OFFSET].map;	//lookup map in the character map
	
	//set character elements to the valus in the map
	StreamProcessorBodyValue(character->A,map.A);
	StreamProcessorBodyValue(character->B,map.B);
	StreamProcessorBodyValue(character->C,map.C);
	StreamProcessorBodyValue(character->D,map.D);
	StreamProcessorBodyValue(character->E,map.E);
	StreamProcessorBodyValue(character->F,map.F);
	StreamProcessorBodyValue(character->G1,map.G1);
	StreamProcessorBodyValue(character->G2,map.G2);
	StreamProcessorBodyValue(character->H,map.H);
	StreamProcessorBodyValue(character->IL,map.IL);
	StreamProcessorBodyValue(character->J,map.J);
	StreamProcessorBodyValue(character->K,map.K);
	StreamProcessorBodyValue(character->M,map.M);
	StreamProcessorBodyValue(character->DP,0);
	
	return(SUCCESS);	//character has been set
}

/*!
 * Returns control of the character on the display to the body
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorReturnCharacter(const lcd_character* const character)
{
	
	//clear the mask and retuen control to the body
	StreamProcessorBodyReturn(character->A);
	StreamProcessorBodyReturn(character->B);
	StreamProcessorBodyReturn(character->C);
	StreamProcessorBodyReturn(character->D);
	StreamProcessorBodyReturn(character->E);
	StreamProcessorBodyReturn(character->F);
	StreamProcessorBodyReturn(character->G1);
	StreamProcessorBodyReturn(character->G2);
	StreamProcessorBodyReturn(character->H);
	StreamProcessorBodyReturn(character->IL);
	StreamProcessorBodyReturn(character->J);
	StreamProcessorBodyReturn(character->K);
	StreamProcessorBodyReturn(character->M);
	StreamProcessorBodyReturn(character->DP);
	
	return(SUCCESS);	//complete
}

/*!
 * Sets the mask for a given byte.
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorHeadSetMask(uint8_t byte,char mask)
{
	if(byte>HEAD_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	
	headStreamMask[byte]=mask&0x7F;				//set mask (exclude highest bit)
	return(SUCCESS);									//completed
}

/*!
 * Sets the data for a given byte.
 *
 * \return out of ranges errors or #SUCCESS
 */
int StreamProcessorHeadSetData(uint8_t byte,char data)
{
	if(byte>HEAD_STREAM_LENGTH)					//check for bytes out of range
	{
		return(ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE);	//report this error
	}
	
	headStreamData[byte]=data;				//set data
	return(SUCCESS);									//completed
}

/* body receive interrupt */
ISR(UART_BODY_RX_vect)
{
	char received = UART_BODY_DATA;			//read byte from serial port
	
	if(received&0x80)				//is this the first byte in the chain
	{
		bodyInput.writeposition=0;	//if this is the first byte move to start of buffer
	}
	
	if(bodyInput.writeposition>=BODY_STREAM_LENGTH)			//check for unexpected data
	{
		ErrorBufferPut(ERR_STREAM_BODY_STREAM_TOO_LONG);	//report this error
		return;		//exit ISR
	}
	
	bodyInput.array[bodyInput.writeposition]=received;	//store data in the buffer
	
	//perform stream manipulation (and the data with the inverted bitmask then or with the bitmasked data)
	char output = (received & ~bodyStreamMask[bodyInput.writeposition]) | (bodyStreamMask[bodyInput.writeposition] & bodyStreamData[bodyInput.writeposition]);
	
	bodyInput.writeposition++;		//increment write pointer
	
	//todo remove this while loop?
	while ((UCSR2A & (1 << UDRE2)) == 0);		// Do nothing until UDR is ready for more data to be written to it
	UART_HEAD_DATA = output;					//send this data onwards to the head
		
}

/* head receive interrupt */
ISR(UART_HEAD_RX_vect)
{
	char received = UART_HEAD_DATA;			//read byte from serial port
	
	if(received&0x80)				//is this the first byte in the chain
	{
		headInput.writeposition=0;	//if this is the first byte move to start of buffer
	}
	
	if(headInput.writeposition>=HEAD_STREAM_LENGTH)	//check for unexpected data
	{
		ErrorBufferPut(ERR_STREAM_HEAD_STREAM_TOO_LONG);	//report this error
		return;		//exit ISR
	}
	
	headInput.array[headInput.writeposition]=received;	//store data in the buffer
	
	//perform stream manipulation (and the data with the inverted bitmask then or with the bitmasked data)
	char output = (received & ~headStreamMask[headInput.writeposition]) | (headStreamMask[headInput.writeposition] & headStreamData[headInput.writeposition]);
	
	headInput.writeposition++;		//increment write pointer
	
	//todo remove this while loop?
	while ((UCSR1A & (1 << UDRE1)) == 0);		// Do nothing until UDR is ready for more data to be written to it
	UART_BODY_DATA = output;					//send this data onwards to the body
}