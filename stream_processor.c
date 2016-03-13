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

stream_buffer_t bodyInput;
stream_buffer_t bodyOutput;

stream_buffer_t headInput;
stream_buffer_t headOutput;

char bodyStreamMask[BODY_STREAM_LENGTH];
char bodyStreamData[BODY_STREAM_LENGTH];

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
		
	/*
	//retransmit head
	if(headInput.readposition>=HEAD_STREAM_LENGTH&&headInput.next)	//check for new buffer loads
	{
		headInput.readposition=0;
		headInput.next=0;
	}
		
	if ((headInput.writeposition>headInput.readposition)||(headInput.next && headInput.readposition<HEAD_STREAM_LENGTH))			// has a byte been received from the head
	{
		char byte = headInput.array[headInput.readposition];	// Fetch the received byte value from the input buffer
		headInput.readposition++;
				
		while ((UCSR1A & (1 << UDRE1)) == 0);		// Do nothing until UDR is ready for more data to be written to it
		UDR1 = byte;
	}

	//retransmit body
	if(bodyInput.readposition>=BODY_STREAM_LENGTH&&bodyInput.next)	//check for new buffer loads
	{
		bodyInput.readposition=0;
		bodyInput.next=0;
	}
		
	if ((bodyInput.writeposition>bodyInput.readposition)||(bodyInput.next && bodyInput.readposition<BODY_STREAM_LENGTH))			// has a byte been received from the head
	{
		char byte = bodyInput.array[bodyInput.readposition];	// Fetch the received byte value from the input buffer
		bodyInput.readposition++;
				
		while ((UCSR2A & (1 << UDRE2)) == 0);		// Do nothing until UDR is ready for more data to be written to it
		UDR2 = byte;
	}
	*/
		
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
	int i=0;
	int strptr=0;
	
	for(i=0;i<string->length;i++)
	{
		char character=text[strptr];
		
		if(character=='\0'||character=='\r'||character=='\n')	//if string has ended
		{
			character=' ';	//set character to space instead
		}
		else
		{
			strptr++;
		}
		
		StreamProcessorSetCharacter(string->characters[i],character);
	}
	return(SUCCESS);
}

int StreamProcessorBodyReturnText(const lcd_string* const string)
{
	int i=0;
	
	for(i=0;i<string->length;i++)
	{
		StreamProcessorReturnCharacter(string->characters[i]);
	}
	return(SUCCESS);
}

int StreamProcessorSetCharacter(const lcd_character* const character,char letter)
{
	charmap_t map;
	map.map = charmap[letter-CHARMAP_OFFSET].map;
	
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
	
	return(SUCCESS);
}

int StreamProcessorReturnCharacter(const lcd_character* const character)
{
	
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
	
	return(SUCCESS);
}

/* body receive interrupt */
ISR(USART1_RX_vect)
{
	//DriverUSBUartPut("B",1);
	char received = UDR1;			//read byte from serial port
	
	if(received&0x80)				//is this the first byte in the chain
	{
		bodyInput.writeposition=0;	
	}
	
	if(bodyInput.writeposition>=BODY_STREAM_LENGTH)	//check for unexpected data
	{
		ErrorBufferPut(ERR_STREAM_BODY_STREAM_TOO_LONG);	//report this error
		return;		//exit ISR
	}
	
	bodyInput.array[bodyInput.writeposition]=received;	//store data in the buffer
	
	//perform stream manipulation
	char output = (received & ~bodyStreamMask[bodyInput.writeposition]) | (bodyStreamMask[bodyInput.writeposition] & bodyStreamData[bodyInput.writeposition]);
	
	bodyInput.writeposition++;		//increment write pointer
	
	//todo remove this while loop?
	while ((UCSR2A & (1 << UDRE2)) == 0);		// Do nothing until UDR is ready for more data to be written to it
	UDR2 = output;
		
}

/* head receive interrupt */
ISR(USART2_RX_vect)
{
	//DriverUSBUartPut("H",1);
	char received = UDR2;			//read byte from serial port
	
	if(received&0x80)				//is this the first byte in the chain
	{
		headInput.writeposition=0;
	}
	
	if(headInput.writeposition>=HEAD_STREAM_LENGTH)	//check for unexpected data
	{
		ErrorBufferPut(ERR_STREAM_HEAD_STREAM_TOO_LONG);	//report this error
		return;		//exit ISR
	}
	
	headInput.array[headInput.writeposition]=received;	//store data in the buffer
	headInput.writeposition++;		//increment write pointer
	
	//todo remove this while loop?
	while ((UCSR1A & (1 << UDRE1)) == 0);		// Do nothing until UDR is ready for more data to be written to it
	UDR1 = received;
}

/* body transmit interrupt */
ISR(USART1_UDRE_vect)
{
	
}

/* head transmit interrupt */
ISR(USART2_UDRE_vect)
{
	
}