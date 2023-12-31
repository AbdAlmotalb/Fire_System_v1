/*
 * LCD_Cfg.h
 *
 * Created: 6/24/2023 12:19:29 PM
 *  Author: Right Click
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define  _8_BIT  0
#define  _4_BIT  1

/***********_8_BIT or _4_BIT *********************/
#define  LCD_MODE  _4_BIT




#define  RS    PINA1
#define  EN    PINA2
/**************** 4 BIT mode only *************/
#define D4  PINA3
#define D5  PINA4
#define D6  PINA5
#define D7  PINA6

/**************** 8 BIT mode only *************/
#define  LCD_PORT  PA



#endif /* LCD_CFG_H_ */