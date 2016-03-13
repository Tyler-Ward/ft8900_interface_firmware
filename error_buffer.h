/*
 * error_buffer.h
 *
 * Created: 30/08/2015 17:14:45
 *  Author: Tyler
 */ 


#ifndef ERROR_BUFFER_H_
#define ERROR_BUFFER_H_

#define ERROR_BUFFER_LENGTH 64		//!< error buffer length

/*! Error storage structure */
typedef struct ErrorBuffer
{
	unsigned int count;
	unsigned int marker;
	unsigned int buffer[ERROR_BUFFER_LENGTH];
} ErrorBuffer;

/* FUNCTIION DECLARATIONS ******************************************/

int ErrorBufferInit();
int ErrorBufferPut(int error);

void handler_error(void *command);

#endif /* ERROR_BUFFER_H_ */