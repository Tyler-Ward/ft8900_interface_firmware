/*
 * string_decoder.h
 *
 * Created: 06/03/2016
 *  Author: Tyler
 */ 

#ifndef STRING_DECODER_H_
#define STRING_DECODER_H_

#include "body_codes.h"

char decode_char(char* data,const lcd_character* letter);
int decode_string(char* data,const lcd_string string,char* output);

#endif /* STRING_DECODER_H_ */