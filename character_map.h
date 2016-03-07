/*
 * character_map.h
 *
 * Created: 06/03/2016 18:37:03
 *  Author: Tyler
 */ 


#ifndef CHARACTER_MAP_H_
#define CHARACTER_MAP_H_

/* A structure to store compressed character maps*/
typedef union
{
	uint16_t map;			//!< compressed map
	struct 
	{
		unsigned A	:1;		//!< A element
		unsigned B	:1;		//!< B element
		unsigned C	:1;		//!< C element
		unsigned D	:1;		//!< D element
		unsigned E	:1;		//!< E element
		unsigned F	:1;		//!< F element
		unsigned G1	:1;		//!< G1 element
		unsigned G2	:1;		//!< G2 element
		unsigned H	:1;		//!< H element
		unsigned IL	:1;		//!< I and L elements
		unsigned J	:1;		//!< J element
		unsigned K	:1;		//!< K element
		unsigned M	:1;		//!< M element
	};	
} charmap_t;

/* ascii table of Character maps */
extern const charmap_t charmap[];

#define CHARMAP_MAX_CHAR 64		//!< length of character map
#define CHARMAP_OFFSET 32		//!< offset to apply when looking up in the map


#endif /* CHARACTER_MAP_H_ */