/*
 * body_codes.h
 *
 * Created: 06/03/2016 16:42
 *  Author: Tyler
 */ 

#ifndef BODY_CODES_H_
#define BODY_CODES_H_

/* struct to define placement of segments in head messages */
typedef struct 
{
	uint8_t byte;	//!< the byte containing the segment
	uint8_t bit;	//!< the bit containing the segment
} lcd_segment;

/* struct to store layout of character segments */
typedef struct
{
	const lcd_segment A;		//!< A element location
	const lcd_segment B;		//!< B element location
	const lcd_segment C;		//!< C element location
	const lcd_segment D;		//!< D element location
	const lcd_segment E;		//!< E element location
	const lcd_segment F;		//!< F element location
	const lcd_segment G1;		//!< G1 element location
	const lcd_segment G2;		//!< G2 element location
	const lcd_segment H;		//!< H element location
	const lcd_segment IL;		//!< I and L elements location
	const lcd_segment J;		//!< J element location
	const lcd_segment K;		//!< K element location
	const lcd_segment M;		//!< M element location
	const lcd_segment DP;		//!< Decimal point element location
} lcd_character;

/*struct to store character grids */
typedef struct
{
	uint8_t length;				//!< length of the string
	lcd_character const * const * const characters;	//pointer to an array of characters in the string
} lcd_string;


#define SEGMENT_LOCATION_NONE {7,7}		//! used to mark a nonexistant segment

/* LEFT NAME 1 *****************************************************/

#define LEFT_NAME_1_A {13,4}
#define LEFT_NAME_1_B {13,2}
#define LEFT_NAME_1_C {13,0}
#define LEFT_NAME_1_D {14,2}
#define LEFT_NAME_1_E {14,6}
#define LEFT_NAME_1_F {15,0}
#define LEFT_NAME_1_G1 {13,5}
#define LEFT_NAME_1_G2 {13,1}
#define LEFT_NAME_1_H {13,6}
#define LEFT_NAME_1_IL {14,3}
#define LEFT_NAME_1_J {13,3}
#define LEFT_NAME_1_K {14,1}
#define LEFT_NAME_1_M {14,5}
#define LEFT_NAME_1_DP SEGMENT_LOCATION_NONE		//!< left name field 4th digit DP element
	
extern const lcd_character LEFT_NAME_1;

/* LEFT NAME 2 *****************************************************/

#define LEFT_NAME_2_A {11,2}
#define LEFT_NAME_2_B {11,0}
#define LEFT_NAME_2_C {10,5}
#define LEFT_NAME_2_D {12,0}
#define LEFT_NAME_2_E {12,4}
#define LEFT_NAME_2_F {12,5}
#define LEFT_NAME_2_G1 {11,3}
#define LEFT_NAME_2_G2 {10,6}
#define LEFT_NAME_2_H {11,4}
#define LEFT_NAME_2_IL {12,1}
#define LEFT_NAME_2_J {11,1}
#define LEFT_NAME_2_K {11,6}
#define LEFT_NAME_2_M {12,3}
#define LEFT_NAME_2_DP SEGMENT_LOCATION_NONE		//!< left name field 4th digit DP element
	
extern const lcd_character LEFT_NAME_2;

/* LEFT NAME 3 *****************************************************/

#define LEFT_NAME_3_A {9,0}
#define LEFT_NAME_3_B {8,5}
#define LEFT_NAME_3_C {8,3}
#define LEFT_NAME_3_D {9,5}
#define LEFT_NAME_3_E {10,2}
#define LEFT_NAME_3_F {10,3}
#define LEFT_NAME_3_G1 {9,1}
#define LEFT_NAME_3_G2 {8,4}
#define LEFT_NAME_3_H {9,2}
#define LEFT_NAME_3_IL {9,6}
#define LEFT_NAME_3_J {8,6}
#define LEFT_NAME_3_K {9,4}
#define LEFT_NAME_3_M {10,1}
#define LEFT_NAME_3_DP {8,0}
	
extern const lcd_character LEFT_NAME_3;

/* LEFT NAME 4 *****************************************************/

#define LEFT_NAME_4_A {5,6}			//!< left name field 4th digit A element
#define LEFT_NAME_4_B {5,4}			//!< left name field 4th digit B element
#define LEFT_NAME_4_C {5,2}			//!< left name field 4th digit C element
#define LEFT_NAME_4_D {6,4}			//!< left name field 4th digit D element
#define LEFT_NAME_4_E {7,1}			//!< left name field 4th digit E element
#define LEFT_NAME_4_F {7,2}			//!< left name field 4th digit F element
#define LEFT_NAME_4_G1 {6,0}		//!< left name field 4th digit G1 element
#define LEFT_NAME_4_G2 {5,3}		//!< left name field 4th digit G2 element
#define LEFT_NAME_4_H {6,1}			//!< left name field 4th digit H element
#define LEFT_NAME_4_IL {6,5}		//!< left name field 4th digit I and L elements
#define LEFT_NAME_4_J {5,5}			//!< left name field 4th digit J element
#define LEFT_NAME_4_K {6,3}			//!< left name field 4th digit K element
#define LEFT_NAME_4_M {7,0}			//!< left name field 4th digit M element
#define LEFT_NAME_4_DP SEGMENT_LOCATION_NONE		//!< left name field 4th digit DP element

extern const lcd_character LEFT_NAME_4;

/* LEFT NAME 5 *****************************************************/

#define LEFT_NAME_5_A {3,4}			//!< left name field 5th digit A element
#define LEFT_NAME_5_B {3,2}			//!< left name field 5th digit B element
#define LEFT_NAME_5_C {3,0}			//!< left name field 5th digit C element
#define LEFT_NAME_5_D {4,2}			//!< left name field 5th digit D element
#define LEFT_NAME_5_E {4,6}			//!< left name field 5th digit E element
#define LEFT_NAME_5_F {5,0}			//!< left name field 5th digit F element
#define LEFT_NAME_5_G1 {3,5}		//!< left name field 5th digit G1 element
#define LEFT_NAME_5_G2 {3,1}		//!< left name field 5th digit G2 element
#define LEFT_NAME_5_H {3,6}			//!< left name field 5th digit H element
#define LEFT_NAME_5_IL {4,3}		//!< left name field 5th digit I and L elements
#define LEFT_NAME_5_J {3,3}			//!< left name field 5th digit J element
#define LEFT_NAME_5_K {4,1}			//!< left name field 5th digit K element
#define LEFT_NAME_5_M {4,5}			//!< left name field 5th digit M element
#define LEFT_NAME_5_DP SEGMENT_LOCATION_NONE		//!< left name field 5th digit DP element

extern const lcd_character LEFT_NAME_5;

/* LEFT NAME 6 *****************************************************/

#define LEFT_NAME_6_A {1,2}			//!< left name field 6th digit A element
#define LEFT_NAME_6_B {1,0}			//!< left name field 6th digit B element
#define LEFT_NAME_6_C {0,5}			//!< left name field 6th digit C element
#define LEFT_NAME_6_D {2,0}			//!< left name field 6th digit D element
#define LEFT_NAME_6_E {2,4}			//!< left name field 6th digit E element
#define LEFT_NAME_6_F {2,5}			//!< left name field 6th digit F element
#define LEFT_NAME_6_G1 {1,3}		//!< left name field 6th digit G1 element
#define LEFT_NAME_6_G2 {0,6}		//!< left name field 6th digit G2 element
#define LEFT_NAME_6_H {1,4}			//!< left name field 6th digit H element
#define LEFT_NAME_6_IL {2,1}		//!< left name field 6th digit I and L elements
#define LEFT_NAME_6_J {1,1}			//!< left name field 6th digit J element
#define LEFT_NAME_6_K {1,6}			//!< left name field 6th digit K element
#define LEFT_NAME_6_M {2,3}			//!< left name field 6th digit M element
#define LEFT_NAME_6_DP {0,3}		//!< left name field 6th digit DP element
	
extern const lcd_character LEFT_NAME_6;

/* LEFT NAME *******************************************************/

extern const lcd_character* LEFT_NAME_CHARACTERS[];
extern const lcd_string LEFT_NAME;
	
/* RIGHT NAME 1 *****************************************************/
	
#define RIGHT_NAME_1_A {29,4}
#define RIGHT_NAME_1_B {29,2}
#define RIGHT_NAME_1_C {29,0}
#define RIGHT_NAME_1_D {30,2}
#define RIGHT_NAME_1_E {30,6}
#define RIGHT_NAME_1_F {31,0}
#define RIGHT_NAME_1_G1 {29,5}
#define RIGHT_NAME_1_G2 {29,1}
#define RIGHT_NAME_1_H {29,6}
#define RIGHT_NAME_1_IL {30,3}
#define RIGHT_NAME_1_J {29,3}
#define RIGHT_NAME_1_K {30,1}
#define RIGHT_NAME_1_M {30,5}
#define RIGHT_NAME_1_DP SEGMENT_LOCATION_NONE
	
extern const lcd_character RIGHT_NAME_1;

/* RIGHT NAME 2 *****************************************************/

#define RIGHT_NAME_2_A {27,2}
#define RIGHT_NAME_2_B {27,0}
#define RIGHT_NAME_2_C {26,5}
#define RIGHT_NAME_2_D {28,0}
#define RIGHT_NAME_2_E {28,4}
#define RIGHT_NAME_2_F {28,5}
#define RIGHT_NAME_2_G1 {27,3}
#define RIGHT_NAME_2_G2 {26,6}
#define RIGHT_NAME_2_H {27,4}
#define RIGHT_NAME_2_IL {28,1}
#define RIGHT_NAME_2_J {27,1}
#define RIGHT_NAME_2_K {27,6}
#define RIGHT_NAME_2_M {28,3}
#define RIGHT_NAME_2_DP SEGMENT_LOCATION_NONE

extern const lcd_character RIGHT_NAME_2;

/* RIGHT NAME 3 *****************************************************/

#define RIGHT_NAME_3_A {25,0}
#define RIGHT_NAME_3_B {24,5}
#define RIGHT_NAME_3_C {24,3}
#define RIGHT_NAME_3_D {25,5}
#define RIGHT_NAME_3_E {26,2}
#define RIGHT_NAME_3_F {26,3}
#define RIGHT_NAME_3_G1 {25,1}
#define RIGHT_NAME_3_G2 {24,4}
#define RIGHT_NAME_3_H {25,2}
#define RIGHT_NAME_3_IL {25,6}
#define RIGHT_NAME_3_J {24,6}
#define RIGHT_NAME_3_K {25,4}
#define RIGHT_NAME_3_M {26,1}
#define RIGHT_NAME_3_DP {24,0}

extern const lcd_character RIGHT_NAME_3;

/* RIGHT NAME 4 *****************************************************/

#define RIGHT_NAME_4_A {21,6}
#define RIGHT_NAME_4_B {21,4}
#define RIGHT_NAME_4_C {21,2}
#define RIGHT_NAME_4_D {22,4}
#define RIGHT_NAME_4_E {23,1}
#define RIGHT_NAME_4_F {23,2}
#define RIGHT_NAME_4_G1 {22,0}
#define RIGHT_NAME_4_G2 {21,3}
#define RIGHT_NAME_4_H {22,1}
#define RIGHT_NAME_4_IL {22,5}
#define RIGHT_NAME_4_J {21,5}
#define RIGHT_NAME_4_K {22,3}
#define RIGHT_NAME_4_M {23,0}
#define RIGHT_NAME_4_DP SEGMENT_LOCATION_NONE

extern const lcd_character RIGHT_NAME_4;

/* RIGHT NAME 5 *****************************************************/

#define RIGHT_NAME_5_A {19,4}
#define RIGHT_NAME_5_B {19,2}
#define RIGHT_NAME_5_C {19,0}
#define RIGHT_NAME_5_D {20,2}
#define RIGHT_NAME_5_E {20,6}
#define RIGHT_NAME_5_F {21,0}
#define RIGHT_NAME_5_G1 {19,5}
#define RIGHT_NAME_5_G2 {19,1}
#define RIGHT_NAME_5_H {19,6}
#define RIGHT_NAME_5_IL {20,3}
#define RIGHT_NAME_5_J {19,3}
#define RIGHT_NAME_5_K {20,1}
#define RIGHT_NAME_5_M {20,5}
#define RIGHT_NAME_5_DP SEGMENT_LOCATION_NONE

extern const lcd_character RIGHT_NAME_5;

/* RIGHT NAME 6 *****************************************************/

#define RIGHT_NAME_6_A {17,2}
#define RIGHT_NAME_6_B {17,0}
#define RIGHT_NAME_6_C {16,5}
#define RIGHT_NAME_6_D {18,0}
#define RIGHT_NAME_6_E {18,4}
#define RIGHT_NAME_6_F {18,5}
#define RIGHT_NAME_6_G1 {17,3}
#define RIGHT_NAME_6_G2 {16,6}
#define RIGHT_NAME_6_H {17,4}
#define RIGHT_NAME_6_IL {18,1}
#define RIGHT_NAME_6_J {17,1}
#define RIGHT_NAME_6_K {17,6}
#define RIGHT_NAME_6_M {18,3}
#define RIGHT_NAME_6_DP {16,3}
	
extern const lcd_character RIGHT_NAME_6;

/* RIGHT NAME ******************************************************/

extern const lcd_character* RIGHT_NAME_CHARACTERS[];
extern const lcd_string RIGHT_NAME;

/* LEFT MEMORY prefix **********************************************/

#define LEFT_MEMORY_PREFIX_A {40,5}		//!< left memory prefix A element
#define LEFT_MEMORY_PREFIX_B {40,3}		//!< left memory prefix B element
#define LEFT_MEMORY_PREFIX_C {40,2}		//!< left memory prefix C element
#define LEFT_MEMORY_PREFIX_D {48,3}		//!< left memory prefix D element
#define LEFT_MEMORY_PREFIX_E {40,6}		//!< left memory prefix E element
#define LEFT_MEMORY_PREFIX_F {41,0}		//!< left memory prefix F element
#define LEFT_MEMORY_PREFIX_G {40,4}		//!< left memory prefix G element
	
extern const lcd_character LEFT_MEMORY_PREFIX;
	
/* LEFT MEMORY TENS **********************************************/

#define LEFT_MEMORY_TENS_A {39,4}		//!< left memory TENS A element
#define LEFT_MEMORY_TENS_B {38,5}		//!< left memory TENS B element
#define LEFT_MEMORY_TENS_C {38,4}		//!< left memory TENS C element
#define LEFT_MEMORY_TENS_D {40,0}		//!< left memory TENS D element
#define LEFT_MEMORY_TENS_E {39,5}		//!< left memory TENS E element
#define LEFT_MEMORY_TENS_F {39,6}		//!< left memory TENS F element
#define LEFT_MEMORY_TENS_G {39,3}		//!< left memory TENS G element
	
extern const lcd_character LEFT_MEMORY_TENS;

/* LEFT MEMORY UNITS **********************************************/

#define LEFT_MEMORY_UNITS_A {37,6}		//!< left memory UNITS A element
#define LEFT_MEMORY_UNITS_B {37,4}		//!< left memory UNITS B element
#define LEFT_MEMORY_UNITS_C {37,3}		//!< left memory UNITS C element
#define LEFT_MEMORY_UNITS_D {38,2}		//!< left memory UNITS D element
#define LEFT_MEMORY_UNITS_E {38,0}		//!< left memory UNITS E element
#define LEFT_MEMORY_UNITS_F {38,1}		//!< left memory UNITS F element
#define LEFT_MEMORY_UNITS_G {37,5}		//!< left memory UNITS G element

extern const lcd_character LEFT_MEMORY_UNITS;

/* LEFT MEMORY *****************************************************/

extern const lcd_character* LEFT_MEMORY_CHARACTERS[];
extern const lcd_string LEFT_MEMORY;

/* RIGHT MEMORY prefix *********************************************/

#define RIGHT_MEMORY_PREFIX_A {35,6}		//!< RIGHT memory prefix A element
#define RIGHT_MEMORY_PREFIX_B {35,4}		//!< RIGHT memory prefix B element
#define RIGHT_MEMORY_PREFIX_C {35,3}		//!< RIGHT memory prefix C element
#define RIGHT_MEMORY_PREFIX_D {34,1}		//!< RIGHT memory prefix D element
#define RIGHT_MEMORY_PREFIX_E {36,0}		//!< RIGHT memory prefix E element
#define RIGHT_MEMORY_PREFIX_F {36,1}		//!< RIGHT memory prefix F element
#define RIGHT_MEMORY_PREFIX_G {35,5}		//!< RIGHT memory prefix G element

extern const lcd_character RIGHT_MEMORY_PREFIX;
	
/* RIGHT MEMORY TENS **********************************************/

#define RIGHT_MEMORY_TENS_A {34,5}		//!< RIGHT memory TENS A element
#define RIGHT_MEMORY_TENS_B {34,3}		//!< RIGHT memory TENS B element
#define RIGHT_MEMORY_TENS_C {34,2}		//!< RIGHT memory TENS C element
#define RIGHT_MEMORY_TENS_D {35,1}		//!< RIGHT memory TENS D element
#define RIGHT_MEMORY_TENS_E {34,6}		//!< RIGHT memory TENS E element
#define RIGHT_MEMORY_TENS_F {35,0}		//!< RIGHT memory TENS F element
#define RIGHT_MEMORY_TENS_G {34,4}		//!< RIGHT memory TENS G element
	
extern const lcd_character RIGHT_MEMORY_TENS;
	
/* RIGHT MEMORY UNITS **********************************************/

#define RIGHT_MEMORY_UNITS_A {33,4}		//!< RIGHT memory UNITS A element
#define RIGHT_MEMORY_UNITS_B {33,2}		//!< RIGHT memory UNITS B element
#define RIGHT_MEMORY_UNITS_C {33,1}		//!< RIGHT memory UNITS C element
#define RIGHT_MEMORY_UNITS_D {34,0}		//!< RIGHT memory UNITS D element
#define RIGHT_MEMORY_UNITS_E {33,5}		//!< RIGHT memory UNITS E element
#define RIGHT_MEMORY_UNITS_F {33,6}		//!< RIGHT memory UNITS F element
#define RIGHT_MEMORY_UNITS_G {33,3}		//!< RIGHT memory UNITS G element

extern const lcd_character RIGHT_MEMORY_UNITS;

/* RIGHT MEMORY ****************************************************/

extern const lcd_character* RIGHT_MEMORY_CHARACTERS[];
extern const lcd_string RIGHT_MEMORY;

/* LEFT S-METER ****************************************************/

#define LEFT_BUSY {12,2}			//!< left S meter BUSY element
#define LEFT_S1 {10,4}				//!< left S meter S1 element
#define LEFT_S2 {10,0}				//!< left S meter S2 element
#define LEFT_S3 {8,2}				//!< left S meter S3 element
#define LEFT_S4 {6,6}				//!< left S meter S4 element
#define LEFT_S5 {5,1}				//!< left S meter S5 element
#define LEFT_S6 {4,4}				//!< left S meter S6 element
#define LEFT_S7 {2,6}				//!< left S meter S7 element
#define LEFT_S8 {2,2}				//!< left S meter S8 element
#define LEFT_S9 {0,4}				//!< left S meter S9 element

/* RIGHT S-METER ***************************************************/

#define RIGHT_BUSY {28,2}			//!< right S meter BUSY element
#define RIGHT_S1 {26,4}				//!< RIGHT S meter S1 element
#define RIGHT_S2 {26,1}				//!< RIGHT S meter S2 element
#define RIGHT_S3 {24,2}				//!< RIGHT S meter S3 element
#define RIGHT_S4 {22,6}				//!< RIGHT S meter S4 element
#define RIGHT_S5 {21,1}				//!< RIGHT S meter S5 element
#define RIGHT_S6 {20,4}				//!< RIGHT S meter S6 element
#define RIGHT_S7 {18,6}				//!< RIGHT S meter S7 element
#define RIGHT_S8 {18,2}				//!< RIGHT S meter S8 element
#define RIGHT_S9 {16,4}				//!< RIGHT S meter S9 element

/* INDICATORS ******************************************************/

#define LEFT_MT {12,6}				//!< left MT indicator
#define LEFT_MUTE {11,5}			//!< left MUTE indicator
#define LEFT_DCS {9,3}				//!< left DCS indicator
#define LEFT_AM {6,2}				//!< left AM indicator
#define LEFT_9600 {4,0}				//!< left 9600 indicator
#define LEFT_L {1,5}				//!< left L power indicator
#define LEFT_M {0,2}				//!< left M power indicator

#define RIGHT_MT {27,5}				//!< right MT indicator
#define RIGHT_MUTE {25,3}			//!< right MUTE indicator
#define RIGHT_DCS {22,2}			//!< right DCS indicator
#define RIGHT_9600 {20,0}			//!< right 9600 indicator
#define RIGHT_L {17,5}				//!< right L power indicator
#define RIGHT_M {16,2}				//!< right M power indicator
	
#define KEY2 {28,6}					//!< key2 indicator
#define LOCK {30,4}					//!< lock indicator
#define APO {0,1}					//!< auto power off indicator
#define SET {30,0}					//!< set indicator
	
#define LEFT_MEMORY_DASH {40,1}		//!< left memory dash indicator
#define LEFT_SKIP {37,2}			//!< left skip indicator
#define LEFT_SKIP_ARROW {37,1}		//!< left skip arrow indicator 
#define LEFT_ENC {36,6}				//!< left ENC indicator
#define LEFT_DEC {37,0}				//!< left DEC indicator
#define LEFT_MINUS {36,5}			//!< left MINUS indicator
#define LEFT_PLUS {36,4}			//!< left PLUS indicator
#define LEFT_TX {36,3}				//!< left TX indicator
#define LEFT_MAIN {36,2}			//!< left MAIN indicator

#define RIGHT_MEMORY_DASH {35,2}	//!< RIGHT memory dash indicator
#define RIGHT_SKIP {33,0}			//!< RIGHT skip indicator
#define RIGHT_SKIP_ARROW {32,6}		//!< RIGHT skip arrow indicator
#define RIGHT_ENC {32,4}			//!< RIGHT ENC indicator
#define RIGHT_DEC {32,5}			//!< RIGHT DEC indicator
#define RIGHT_MINUS {32,3}			//!< RIGHT MINUS indicator
#define RIGHT_PLUS {32,2}			//!< RIGHT PLUS indicator
#define RIGHT_TX {32,1}				//!< RIGHT TX indicator
#define RIGHT_MAIN {32,0}			//!< RIGHT MAIN indicator
	
/* BACKLIGHT *******************************************************/
	
#define BACKLIGHT_1 {41,3}			//!< backlight control 1
#define BACKLIGHT_2 {41,2}			//!< backlight control 2
#define BACKLIGHT_3 {41,1}			//!< backlight control 3
	
#endif /* BODY_CODES_H_ */
