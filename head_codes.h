/*
 * head_codes.h
 *
 * Created: 06/03/2016 16:27
 *  Author: Tyler
 */ 

#ifndef HEAD_CODES_H_
#define HEAD_CODES_H_

typedef struct  
{
	uint8_t location;
	char	data;
	uint8_t type;
} head_button_t;


extern const char HEAD_IDLE[13];

/* BUTTON TYPES ****************************************************/

#define BUTTON_TYPE_ABSOLOUTE 0			//!< button is done as absolute values
#define BUTTON_TYPE_MASK 1				//!< button is a bitwise mask

/* LEFT DIAL *******************************************************/

#define LEFT_DIAL_LOC 0

#define LEFT_DIAL_IDLE 128
#define LEFT_DIAL_CCW 255
#define LEFT_DIAL_CW 129

/* RIGHT DIAL ******************************************************/

#define RIGHT_DIAL_LOC 1

#define RIGHT_DIAL_IDLE 0
#define RIGHT_DIAL_CCW 127
#define RIGHT_DIAL_CW 1

/* MIC SW1 *********************************************************/

#define MIC_SW1_LOC 2
#define MIC_48_PTT_LOC 2

#define MIC_SW1_IDLE 127
#define MIC_SW1_ACC 101
#define MIC_SW1_UP 77
#define MIC_SW1_DOWN 52
#define MIC_SW1_PTT 28

/* MIC SW2 *********************************************************/

#define MIC_SW2_LOC 8
#define MIC_48_SW2_LOC 8

#define MIC_SW2_IDLE 127
#define MIC_SW2_P2 77
#define MIC_SW2_P1 51
#define MIC_SW2_p 28

/* MIC SW1 (48) ****************************************************/

#define MIC_48_SW1_LOC 5

/* KEY1 ************************************************************/

#define KEY1_LOC 9

#define KEY1_IDLE 127
#define KEY1_LOW 98
#define KEY1_VM 64
#define KEY1_HM 31
#define KEY1_SCN 0

/* KEY2 ************************************************************/

#define KEY2_LOC 10

#define KEY2_IDLE 127
#define KEY2_LOW 0
#define KEY2_VM 32
#define KEY2_HM 65
#define KEY2_SCN 98

/* button masks ****************************************************/

#define BUTTON_LOC 11

#define MASK_RIGHT_DIAL 1
#define MASK_LEFT_DIAL 2
#define MASK_SET 4
#define MASK_WIRES 8

#define BUTTON_SET {BUTTON_LOC,MASK_SET,BUTTON_TYPE_MASK}

/* HYPER MEMORY ****************************************************/

#define HYPER_MEMORY_LOC 12


/* MH48 Keypad *****************************************************/

#define KEYPAD_ROW_1 0x00	//!< keypad row 1 (1-A)
#define KEYPAD_ROW_2 0x1A	//!< keypad row 1 (4-B)
#define KEYPAD_ROW_3 0X32	//!< keypad row 1 (7-C)
#define KEYPAD_ROW_4 0x4C	//!< keypad row 1 (*-D)
#define KEYPAD_ROW_5 0x64	//!< keypad row 1 (P1-P4)

#define KEYPAD_COL_1 0x1B	//!< keypad row 1 (1-*)
#define KEYPAD_COL_2 0x33	//!< keypad row 1 (2-0)
#define KEYPAD_COL_3 0X4C	//!< keypad row 1 (3-#)
#define KEYPAD_COL_4 0x67	//!< keypad row 1 (A-D)

extern const char KEYPAD_MAP[10][2];




#endif /* HEAD_CODES_H_ */