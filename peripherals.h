/*
 * peripherals.h
 *
 * Created: 29/08/2015 15:22:53
 *  Author: Tyler
 */ 


#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

/* USB UART SETTINGS ***********************************************/

#define USART_USB_BAUDRATE 115200			//!< Baudrate for USB Connection
#define USART_USB_BAUDRATE_PRESCALE (((F_CPU / (USART_USB_BAUDRATE * 8UL))) - 1)	//!< Calculation for USB USART Prescaler (+1 added to offset rounding error)

/* FT8900 UART SETTINGS ********************************************/

#define USART_FT8900_BAUDRATE 19200			//!< Baudrate for FT8900 Interface
#define USART_FT8900_BAUDRATE_PRESCALE (((F_CPU / (USART_FT8900_BAUDRATE *8UL))) - 1)	//!< Calculation for FT8900 USART Prescaler

#endif /* PERIPHERALS_H_ */