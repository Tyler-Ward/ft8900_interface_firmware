/*
 * error_codes.h
 *
 * Created: 30/08/2015 17:07:35
 *  Author: Tyler
 */ 


#ifndef ERROR_CODES_H_
#define ERROR_CODES_H_

#define SUCCESS 0		//!< no error has occurred

#define INF_BOOT 1		//!< the board has booted

/* USB UART ********************************************************/

#define ERR_USB_UART_TRANSMIT_BUFFER_FULL 10	//!< USB tranmit buffer full
#define ERR_USB_UART_RECIEVE_BUFFER_FULL 11		//!< USB recieve buffer overflow

/* FT8900 UART *****************************************************/

#define ERR_STREAM_BODY_STREAM_TOO_LONG 20		//!< body data message is too long
#define ERR_STREAM_HEAD_STREAM_TOO_LONG 21		//!< head data message is too long

#define ERR_STREAM_SEGMENT_BYTE_OUT_OF_RANGE 22	//!< byte of the LCD segment is out of range
#define ERR_STREAM_SEGMENT_BIT_OUT_OF_RANGE 23	//!< bit of the LCD segment is out of range

#endif /* ERROR_CODES_H_ */