/*
 * KeyPad.c
 *
 * Created: 6/29/2023 1:03:51 PM
 *  Author: Right Click
 */ 

#define  KEYPAD_PRG  1

#include "StdTypes.h"
#include "DIO_Inteface.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"
#define  F_CPU   8000000
#include <util/delay.h>



void KEYPAD_Init(void)
{
	for (u8 i=0;i<ROWS;i++)
	{
		DIO_WritePin(KeyPad_ROW_Pins[i],KeyPad_initial_value);
	}
}

u8 KEYPAD_GetKey(void)
{
	u8 row,col,key=NO_KEY;
	for (row=0;row<ROWS;row++)
	{
		DIO_WritePin(KeyPad_ROW_Pins[row],KeyPad_check_value);
		for (col=0;col<COLS;col++)
		{
			if (DIO_ReadPin(KeyPad_COL_Pins[col])==KeyPad_check_value)
			{
				_delay_ms(delay_time);
				#ifdef blocking
				while(DIO_ReadPin(KeyPad_COL_Pins[col])==KeyPad_check_value);
 				#endif
				
				_delay_ms(10);
				key=KeysArr[row][col];
			}
		}
		DIO_WritePin(KeyPad_ROW_Pins[row],KeyPad_initial_value);
	}
	return key;
}



