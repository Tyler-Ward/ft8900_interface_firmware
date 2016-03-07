/*
 * head_codes.h
 *
 * Created: 06/03/2016 16:27
 *  Author: Tyler
 */ 

#ifndef HEAD_CODES_H_
#define HEAD_CODES_H_

/*! Structure of head response packets
 *	
 * names of the fields contained in the head response.
 */
typedef struct
{
	char left_dial;
	char right_dial;
	char mic_sw1;
	char right_squelch;
	char right_volume;
	char unknown;
	char left_volume;
	char left_squelch;
	char mic_sw2;
	char left_keys;
	char right_keys;
	char buttons;
	char hyper_memory;
} headResponse;

/* LEFT DIAL *******************************************************/

#define LEFT_DIAL_IDLE 128
#define LEFT_DIAL_CCW 255
#define LEFT_DIAL_CW 129

/* RIGHT DIAL ******************************************************/

#define RIGHT_DIAL_IDLE 0
#define RIGHT_DIAL_CCW 127
#define RIGHT_DIAL_CW 1

/* button masks ****************************************************/

#define MASK_RIGHT_DIAL 1
#define MASK_LEFT_DIAL 2
#define MASK_SET 4
#define MASK_WIRES 8

#endif /* HEAD_CODES_H_ */