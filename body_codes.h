/*
 * body_codes.h
 *
 * Created: 06/03/2016 16:42
 *  Author: Tyler
 */ 

#ifndef BODY_CODES_H_
#define BODY_CODES_H_

/* struct to define placement of segments in head mesages */
typedef struct 
{
	uint8_t byte;
	uint8_t bit;
} lcd_segment;

/* struct to store layout of character segments */
typedef struct
{
	const lcd_segment A;
	const lcd_segment B;
	const lcd_segment C;
	const lcd_segment D;
	const lcd_segment E;
	const lcd_segment F;
	const lcd_segment G1;
	const lcd_segment G2;
	const lcd_segment H;
	const lcd_segment IL;
	const lcd_segment J;
	const lcd_segment K;
	const lcd_segment M;
	const lcd_segment DP;
} lcd_character;

/*struct to store character grids */
typedef struct
{
	uint8_t length;
	lcd_character const * const * const characters;
} lcd_string;


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
#define LEFT_NAME_1_DP {7,7}		//!< left name field 4th digit DP element
	
extern const lcd_character LEFT_NAME_1;

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
#define LEFT_NAME_2_DP {7,7}		//!< left name field 4th digit DP element
	
extern const lcd_character LEFT_NAME_2;

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
#define LEFT_NAME_4_DP {7,7}		//!< left name field 4th digit DP element

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
#define LEFT_NAME_5_DP {0,0}		//!< left name field 5th digit DP element

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

extern const lcd_character* LEFT_NAME_CHARACTERS[];
extern const lcd_string LEFT_NAME;


#define LEFT_S9 (lcd_segment){0,4}				//!< left S meter S9 element
	
	
	
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
#define RIGHT_NAME_1_DP {7,7}
	
extern const lcd_character RIGHT_NAME_1;

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
#define RIGHT_NAME_2_DP {7,7}
	
extern const lcd_character RIGHT_NAME_2;

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
#define RIGHT_NAME_4_DP {7,7}
	
extern const lcd_character RIGHT_NAME_4;

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
#define RIGHT_NAME_5_DP {7,7}
	
extern const lcd_character RIGHT_NAME_5;

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
	
extern const lcd_character* RIGHT_NAME_CHARACTERS[];
extern const lcd_string RIGHT_NAME;	
	
	


#endif /* BODY_CODES_H_ */
