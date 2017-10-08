/*
 * usb_console.h
 *
 * Created: 12/03/2016 22:20:35
 *  Author: Tyler
 */ 


#ifndef USB_CONSOLE_H_
#define USB_CONSOLE_H_

/*! Command storage structure */
typedef struct
{
	const char *commandName;		//command name
	void (*handler) (void*);		//function to call for the command
} command_t;

typedef struct
{
	command_t *command_list;		//pointer to command list
	

	char command_string[32];		//command buffer
	uint8_t command_length;			//!< length of the command
	uint8_t command_arg_marker;		//!< marker to the start of the command arguments
	
	//command status
	uint8_t command_status;			//!< status of the command (used for commands that take time to complete)
} console_status_t;

#define CONSOLE_COMMAND_STATE_NONE 0	//!< no command in progress
#define CONSOLE_COMMAND_STATE_ACTIVE 1	//!< command is still in progress

/* FUNCTIION DECLARATIONS ******************************************/

int UsbConsoleInit();
int UsbConsoleProcess();
int UsbConsoleInterpretCommand(console_status_t *command_status);

void handler_volume(void *command);
void handler_read_display(void *command);
void handler_set_display(void *command);
void handler_clear_display(void *command);
void handler_press_set(void *command);


#endif /* USB_CONSOLE_H_ */