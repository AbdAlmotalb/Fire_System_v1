/*
 * KeyPad_Cfg.h
 *
 * Created: 6/29/2023 12:55:10 PM
 *  Author: Right Click
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_


#define  ROWS   4
#define  COLS   4

#define ROW0 PINB4
#define ROW1 PINB5
#define ROW2 PINB6
#define ROW3 PINB7
#define COL0 PIND2
#define COL1 PIND3
#define COL2 PIND4
#define COL3 PIND5


#define KeyPad_initial_value HIGH
#define KeyPad_check_value LOW

#define NO_KEY  'T'

#define FIRST_OUTPUT   PINB4
#define FIRST_INPUT    PIND0

#define delay  /* blocking  delay */
#define delay_time 200

#if KEYPAD_PRG

const DIO_Pin_type KeyPad_ROW_Pins[ROWS]={ROW0,ROW1,ROW2,ROW3};
const DIO_Pin_type KeyPad_COL_Pins[COLS]={COL0,COL1,COL2,COL3};

const u8 KeysArr[ROWS][COLS]={ {'7','8','9','/'}
,{'4','5','6','*'}
,{'1','2','3','-'}
,{'C','0','=','+'}};
#endif



#endif /* KEYPAD_CFG_H_ */