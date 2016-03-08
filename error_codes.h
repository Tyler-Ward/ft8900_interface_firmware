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



#endif /* ERROR_CODES_H_ */