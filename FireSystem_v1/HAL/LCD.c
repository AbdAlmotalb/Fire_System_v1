/*
 * LCD.c
 *
 * Created: 6/24/2023 12:21:09 PM
 *  Author: Right Click
 */ 
#include "StdTypes.h"
#include "DIO_Inteface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "UTILS.h"
#include "String.h"
#define  F_CPU   8000000
#include <util/delay.h>

#if _8_BIT == LCD_MODE
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);
	WriteIns(0x0c);
	WriteIns(0x01);
	_delay_ms(1);
	WriteIns(0x06);
	
}

#elif _4_BIT == LCD_MODE
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	
	/*write the most significant nibble*/
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	/*write the lest significant nibble*/
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	
	/*write the most significant nibble*/
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	/*write the lest significant nibble*/
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(30);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c);
	WriteIns(0x01);
	_delay_ms(1);
	WriteIns(0x06);
}
#endif

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(2);
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}
/**line 0:1 cell 0:15 **/
void LCD_GoTo(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80+cell);
	}
	else if (line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}

void LCD_WriteString(c8*str)
{
	u8 i=0;
	while(str[i])
	{
		WriteData(str[i]);
		i++;
	}
}
void LCD_WriteNumber(s32 num)
{
	u8 str[16];
	string_intToStr(num,(c8 *)str,16);
	LCD_WriteString((c8 *)str);
}
void LCD_WriteBinary(u8 num)
{
	for(s8 i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}
void LCD_WriteHex(u8 num)
{
	u8 num1=num/16;
	for (u8 i=0;i<2;i++)
	{
		switch(num1)
		{
			case 10:
				LCD_WriteChar('A');
			break;
			case 11:
				LCD_WriteChar('B');
			break;
			case 12:
				LCD_WriteChar('C');
			break;
			case 13:
				LCD_WriteChar('D');
			break;
			case 14:
			LCD_WriteChar('E');
			break;
			case 15:
			LCD_WriteChar('F');
			break;
			default:
				LCD_WriteChar((num1%16)+'0');
		}
		num1=num%16;
	}
}
void LCD_Write_4D(u16 num)
{
	num %=10000;
	LCD_WriteChar((num/1000)+'0');
	num %=1000;
	LCD_WriteChar((num/100)+'0');
	num %=100;
	LCD_WriteChar((num/10)+'0');
	LCD_WriteChar((num%10)+'0');

}
void LCD_CustomChar(u8 address,u8*patten)
{
	WriteIns((address*8)+0x40);
	for(u8 i=0;i<8;i++)
	{
		WriteData(patten[i]);
	}
	LCD_GoTo(0,0);
}

void LCD_WriteStringGoto(u8 line ,u8 cell,c8*str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}
void LCD_ClearPosition(u8 line ,u8 cell,u8 NoCells)
{
	LCD_GoTo(line,cell);
	for(u8 i=0;i<NoCells;i++)
	LCD_WriteChar(' ');
}
