/*
 * ATM32_Project.c
 *
 * Created: 6/16/2023 10:40:42 AM
 * Author : Right Click
 */ 

# define F_CPU 8000000UL


#include "StdTypes.h"
#include "DIO_Inteface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Interface.h"
#include <util/delay.h>
#include "ADC_Interface.h"
#include "sensors_Interface.h"
#include "Filter.h"
#include "Fire_system.h"



int main(void)
{
	DIO_Init();
	MOTOR_Init();
	LCD_Init();
	KEYPAD_Init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	Sensors_Init();
	Filter_Init();
	Fire_System_Init();
    u8 i=NO_KEY;
	s32 a=0,b='B';
	
	u16 adc_value=0,x=5000000;
	LCD_WriteString("welcome");
	_delay_ms(500);
	while (1) 
    {
		Fire_System_Run();
 		//Fire_System_fine();
		/* Filte_Get_filtered_all_sensor();
		filter_print();
		*/
		/*LCD_GoTo(0,8);
		LCD_WriteNumber(a++);
		*/
		//_delay_ms(1000);
		
		/*
		adc_value=Filte_Get_filtered_sensor_x(LM35_filter);
 		Filte_Get_filtered_all_sensor();
 		if (x!=adc_value)
 		{
 			LCD_Clear();
 			LCD_WriteString("temp=");
 			LCD_WriteNumber(adc_value/10);
 			LCD_WriteChar('.');
			LCD_WriteNumber(adc_value%10);
 			LCD_WriteString(" c ");
 		}
		 filter_print();
 		x=adc_value;
		 _delay_ms(500);
		 */
 		
		
    }
}

