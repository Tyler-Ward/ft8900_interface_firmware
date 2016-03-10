/*
 * stream_processor.h
 *
 * Created: 08/03/2016 21:49:21
 *  Author: Tyler
 */ 


#ifndef STREAM_PROCESSOR_H_
#define STREAM_PROCESSOR_H_

#define BODY_STREAM_LENGTH 42
#define HEAD_STREAM_LENGTH 13

/*struct for body data*/
typedef struct  
{
	uint8_t writeposition;
	uint8_t next;
	uint8_t readposition;
	char array[64];
} stream_buffer_t;


int StreamProcessorInit();
int StreamProcessorProcess();

int StreamProcessorBodySet(lcd_segment segment);
int StreamProcessorBodyClear(lcd_segment segment);
int StreamProcessorBodyValue(lcd_segment segment,uint8_t value);
int StreamProcessorBodyReturn(lcd_segment segment);

extern stream_buffer_t headInput;
extern stream_buffer_t bodyInput;


#endif /* STREAM_PROCESSOR_H_ */