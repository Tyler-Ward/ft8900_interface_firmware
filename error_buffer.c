/*
 * error_buffer.c
 *
 * Created: 30/08/2015 17:19:38
 *  Author: Tyler
 */ 

#include <string.h>
#include <stdio.h>

#include "error_codes.h"
#include "error_buffer.h"

#include "driver_usb_uart.h"

static volatile ErrorBuffer	errorBuffer;	//the buffer to store errors in

/*!
 * Setup the error buffer
 *
 * \return #SUCCESS as cannot fail
 */
int ErrorBufferInit()
{
	errorBuffer.count=0;					//no errors have occurred yet
	errorBuffer.marker=0;					//start at the beginning of the ring buffer
	return(SUCCESS);						//error buffer ready
}


/*!
 * Add an error to the buffer
 *
 * \param error The error code to be stored
 * \return #SUCCESS as cannot fail
 */
int ErrorBufferPut(int error)
{
	errorBuffer.buffer[errorBuffer.marker]=error;	//store the error in the next slot in the buffer
	errorBuffer.marker=(errorBuffer.marker+1)%ERROR_BUFFER_LENGTH;	//increment the marker rolling over at the end of the buffer
	errorBuffer.count++;					//increment the error count
	return(SUCCESS);
}

/*!
 * Add an error to the buffer
 *
 * \param error The error code to be stored
 * \return #SUCCESS as cannot fail
 */
void handler_error(void *command)
{
	char str[32];
	
	sprintf(str,"ERRORS: %d\r\n",errorBuffer.count);
	DriverUSBUartPutString(str);
	
	int i=0;
	int length=(errorBuffer.count<ERROR_BUFFER_LENGTH)?errorBuffer.count:ERROR_BUFFER_LENGTH;
	
	for(i=0;i<length;i++)
	{
		sprintf(str,"%d\r\n",errorBuffer.buffer[(errorBuffer.marker-length+i)%ERROR_BUFFER_LENGTH]);
		DriverUSBUartPutString(str);
	}
	
}
