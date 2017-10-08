/*
 * head_codes.c
 *
 * Created: 20/03/2016 15:17:23
 *  Author: Tyler
 */ 

#include <stdio.h>
#include "head_codes.h"

const char HEAD_IDLE[13] =
{
	LEFT_DIAL_IDLE,
	RIGHT_DIAL_IDLE,
	MIC_SW1_IDLE,
	0,	//right sql
	0,	//right volume
	127, //unknown line
	0,	//left volume
	0,	//left sql
	MIC_SW2_IDLE,
	KEY1_IDLE,
	KEY2_IDLE,
	0,	//button mask
	0,	//hyper memory
};

/*! Map of keypad position to digits */
const char KEYPAD_MAP[10][2] =
{
	{KEYPAD_ROW_4,KEYPAD_COL_2},	//0
	{KEYPAD_ROW_1,KEYPAD_COL_1},	//1
	{KEYPAD_ROW_1,KEYPAD_COL_2},	//2
	{KEYPAD_ROW_1,KEYPAD_COL_3},	//3
	{KEYPAD_ROW_2,KEYPAD_COL_1},	//4
	{KEYPAD_ROW_2,KEYPAD_COL_2},	//5
	{KEYPAD_ROW_2,KEYPAD_COL_3},	//6
	{KEYPAD_ROW_3,KEYPAD_COL_1},	//7
	{KEYPAD_ROW_3,KEYPAD_COL_2},	//8
	{KEYPAD_ROW_3,KEYPAD_COL_3}		//9
};