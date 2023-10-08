/*
 * String.c
 *
 * Created: 6/24/2023 2:28:19 PM
 *  Author: Right Click
 */ 

#include "StdTypes.h"
#include "String.h"

void string_intToStr(u32 num,c8* str,u32 size)
{
	u32 i=0,sign=1;
	if(num<0)
	{
		sign=-1;
		num*=-1;
	}
	else if(num==0)
	str[i++]='0';
	while(i<size&&num)
	{
		str[i++]=(num%10)+'0';
		num/=10;
	}
	if(sign==-1)
	str[i++]='-';
	str[i]=0;
	string_reverse(str);
}

s32 string_reverse(c8* str)
{
	s32 i=0,size=string_len(str);
	c8 temp;
	while(i<size/2)
	{
		temp=str[i];
		str[i]=str[size-i-1];
		str[size-i-1]=temp;
		i++;
	}
	return 1;
}

s32 string_len(c8* str)
{
	s32 i=0;
	while(str[i])
	i++;
	return i;
}

// convert string to int
s32 strToInt(c8* str,s32 max_size)
{
	s32 i=0,sum=0,sign=1;
	if(str[i]=='-')
	{
		sign=-1;
		i++;
	}
	while(str[i]&&str[i]>='0'&&str[i]<='9'&&i<max_size)
	{
		sum*=10;
		sum+=(str[i]-'0');
		i++;
	}
	return sum*sign;
}