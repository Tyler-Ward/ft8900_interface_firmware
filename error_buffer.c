/*
 * error_buffer.c
 *
 * Created: 30/08/2015 17:19:38
 *  Author: Tyler
 */ 

#include "error_codes.h"
#include "error_buffer.h"

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
