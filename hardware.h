/*
 * hardware.h
 *
 * Created: 29/08/2015 15:02:40
 *  Author: Tyler
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#define F_CPU 16000000UL						//!< 16Mhz Clock

/* USB INTERFACE ***************************************************/

#define UART_USB_PORT PORTE					//!< PORT register for USB serial interface
#define UART_USB_PORT_PIN PINE				//!< PIN register for USB serial interface
#define UART_USB_PORT_DDR DDRE				//!< DDR register for USB serial interface

#define UART_USB_TX_PIN PE1					//!< USART TX pin
#define UART_USB_RX_PIN PE0					//!< USART RX pin

#define UART_USB_DATA UDR0					//!< USART Data register

/* HEAD INTERFACE **************************************************/

#define UART_HEAD_PORT PORTH				//!< PORT register for head serial interface
#define UART_HEAD_PORT_PIN PINH				//!< PIN register for head serial interface
#define UART_HEAD_PORT_DDR DDRH				//!< DDR register for head serial interface

#define UART_HEAD_TX_PIN PH1				//!< USART TX pin
#define UART_HEAD_RX_PIN PH0				//!< USART RX pin

#define UART_HEAD_DATA UDR2					//!< USART Data register

/* BODY INTERFACE **************************************************/

#define UART_BODY_PORT PORTD				//!< PORT register for body serial interface
#define UART_BODY_PORT_PIN PIND				//!< PIN register for body serial interface
#define UART_BODY_PORT_DDR DDRD				//!< PIN register for body serial interface

#define UART_BODY_TX_PIN PD3				//!< USART TX pin
#define UART_BODY_RX_PIN PD2				//!< USART RX pin

#define UART_BODY_DATA UDR1					//!< USART Data register

/* POWER SWITCH ****************************************************/

#define POWERSWITCH_PORT PORTC				//!< PORT register for powerswitch
#define POWERSWITCH_PORT_PIN PINC			//!< PIN register for powerswitch
#define POWERSWITCH_PORT_DDR DDRC			//!< DDR register for powerswitch

#define POWERSWITCH_PIN PC0					//!< powerswitch pin

#endif /* HARDWARE_H_ */