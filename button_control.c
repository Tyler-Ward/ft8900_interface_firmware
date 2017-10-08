/*
 * button_control.c
 *
 * Created: 20/03/2016 13:42:40
 *  Author: Tyler
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "hardware.h"
#include "peripherals.h"
#include "error_codes.h"
#include "head_codes.h"

#include "error_buffer.h"
#include "stream_processor.h"

#include <util/delay.h>

int ButtonControlInit()
{
	return(SUCCESS);
}

int ButtonControlPress(head_button_t button)
{
	StreamProcessorHeadSetData(button.location,button.data);
	StreamProcessorHeadSetMask(button.location,0xFF);
	_delay_ms(100);
	StreamProcessorHeadSetMask(button.location,0);
	StreamProcessorHeadSetData(button.location,HEAD_IDLE[button.location]);
	_delay_ms(100);
	return(SUCCESS);
}

int ButtonControlPress2(head_button_t button,head_button_t button2)
{
	StreamProcessorHeadSetData(button.location,button.data);
	StreamProcessorHeadSetMask(button.location,0xFF);
	StreamProcessorHeadSetData(button2.location,button2.data);
	StreamProcessorHeadSetMask(button2.location,0xFF);
	_delay_ms(100);
	StreamProcessorHeadSetMask(button.location,0);
	StreamProcessorHeadSetData(button.location,HEAD_IDLE[button.location]);
	StreamProcessorHeadSetMask(button2.location,0);
	StreamProcessorHeadSetData(button2.location,HEAD_IDLE[button2.location]);
	_delay_ms(100);
	return(SUCCESS);
}

/*!
 * Locks all front panel controls to unpressed states
 *
 * \retval SUCCESS as cannot fail
 */
int ButtonControlLock()
{
	return(SUCCESS);
}
