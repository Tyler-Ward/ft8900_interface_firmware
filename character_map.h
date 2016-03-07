/*
 * character_map.h
 *
 * Created: 06/03/2016 18:37:03
 *  Author: Tyler
 */ 


#ifndef CHARACTER_MAP_H_
#define CHARACTER_MAP_H_

typedef union
{
	uint16_t map;
	struct 
	{
		unsigned A	:1;
		unsigned B	:1;
		unsigned C	:1;
		unsigned D	:1;
		unsigned E	:1;
		unsigned F	:1;
		unsigned G1	:1;
		unsigned G2	:1;
		unsigned H	:1;
		unsigned IL	:1;
		unsigned J	:1;
		unsigned K	:1;
		unsigned M	:1;
	};	
} charmap_t;

extern const charmap_t charmap[];

#define CHARMAP_MAX_CHAR 64
#define CHARMAP_OFFSET 32




#endif /* CHARACTER_MAP_H_ */