/*
 * usb_console.h
 *
 * Created: 12/03/2016 22:20:35
 *  Author: Tyler
 */ 


#ifndef USB_CONSOLE_H_
#define USB_CONSOLE_H_

typedef struct
{
	const char *commandName;
	void (*handler) (void*);
} command_t;


int UsbConsoleProcess();
int UsbConsoleInterpretCommand(char *command,uint8_t command_length);

static void handler_error(void *command);
static void handler_volume(void *command);
static void handler_read_display(void *command);
static void handler_display_read_debug(void *command);
static void handler_set_display(void *command);
static void handler_clear_display(void *command);


#endif /* USB_CONSOLE_H_ */