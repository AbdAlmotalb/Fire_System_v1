/*
 * String.h
 *
 * Created: 6/24/2023 2:27:59 PM
 *  Author: Right Click
 */ 


#ifndef STRING_H_
#define STRING_H_

void string_intToStr(u32 num,c8* str,u32 size);
s32 string_reverse(c8* str);
s32 string_len(c8* str);
s32 strToInt(c8* str,s32 max_size);

#endif /* STRING_H_ */