/*
 * Fire_System.c
 *
 * Created: 9/23/2023 2:04:46 PM
 *  Author: Right Click
 */ 


# define F_CPU 8000000UL

#include "StdTypes.h"
#include <string.h>
#include <util/delay.h>
#include "ADC_Interface.h"
#include "DIO_Inteface.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Interface.h"
#include "sensors_Interface.h"
#include "Filter.h"
#include "Fire_system.h"
#include "MOTOR_Interface.h"

static Fire_System_Modes_Type sys_Mode=fine; //system mode
static u8 key=NO_KEY; //key pad input
static u8 sys_pass[16]="1111"; // system password
static u16 sys_temprature=0; // system temperature
static u16 sys_smoke=0; // system Smoke level
static u16 sys_smoke_history=0, sys_temprature_history=0; // store the previous data for compare 
/*
transaction flags
1- configuration flag
2- change mode flag
*/
static Fire_System_MSG_Type config_msg_flag=Not_Done, mode_change_flag=Not_Done,alert_msg_flag=Not_Done;
void Fire_System_Init(void)
{
	//initialize the filter
	Filter_Init();
	
	// fill the system vars with the initial values
	Filter_Get_filtered_all_sensor();
	sys_smoke=Filter_Get_filtered_sensor_x(MQ2_filter);
	sys_temprature=Filter_Get_filtered_sensor_x(LM35_filter);
	sys_smoke_history=sys_smoke;
	sys_temprature_history=sys_temprature;
}
void Fire_System_Run(void)
{
	//display the leds system indication  
 	if (mode_change_flag==Not_Done)
 	{
 		//mode_change_flag=Done;
 		Fire_System_Led_color(sys_Mode);
 	}
	 //read system data
	 Fire_System_read();
 	// choose the function based on the system mode
	switch (sys_Mode)
	{
		case config:
		Fire_System_config();
		break;
		case fine:
		Fire_System_fine();
		break;
		case heat:
		Fire_System_heat();
		break;
		case fire:
		Fire_System_fire();
		break;
	}
}
void Fire_System_config(void)
{
	if (config_msg_flag==Not_Done) // display the first configuration MSG for once
	{
		LCD_Clear();
		LCD_WriteString("1-reset");
		LCD_GoTo(1,0);
		LCD_WriteString("2-change pass");
		config_msg_flag=Done;
	}
	
	// get the use choose
	key=KEYPAD_GetKey();
	switch(key)
	{
		// reset the system
		case '1':
		sys_Mode=fine;
		mode_change_flag==Not_Done;
		config_msg_flag=Not_Done;
		break;
		//reset the password
		case '2':
		Config_change_pass();
		config_msg_flag=Not_Done;
		break;
	}
}
void Fire_System_fine(void)
{
	//Fire_System_read();
	//display the new reads
	Fire_System_display();
	//compare temp with threshold temperature
	if (sys_temprature > heat_transation_temp)
	{
		// go to heat mode
		sys_Mode=heat;
		mode_change_flag=Not_Done;
	}
	Is_config();
}
void Fire_System_heat(void)
{
	//Fire_System_read();
	// display alert MSG
	LCD_Clear();
	if (alert_msg_flag==Not_Done)
	{
		LCD_WriteString("Alert");
		LCD_GoTo(1,0);
		LCD_WriteString("High temperature");
		alert_msg_flag=Done;
	}
	else
	{
		alert_msg_flag=Not_Done;
	}
	_delay_ms(300);
	
	// check if there is a smoke more than the threshold
	if (sys_smoke/50 > Smoke_threshold)
	{
		// go to fire mode
		sys_Mode=fire;
		mode_change_flag=Not_Done;
	}
	//compare temp with threshold temperature
	if (sys_temprature < fine_transation_temp)
	{
		// go to fine mode
		sys_Mode=fine;
		mode_change_flag=Not_Done;
	}
	Is_config();
}
void Fire_System_fire(void)
{
	if (mode_change_flag==Not_Done)
	{
		// start the motor
		MOTOR_CW(M1);
		//display fire MSG
		LCD_Clear();
		LCD_GoTo(0,5);
		LCD_WriteString("FIRE!");
		LCD_GoTo(1,0);
		LCD_WriteString("press = to stop");
		mode_change_flag=Done;
	}
	
	key=KEYPAD_GetKey();
	if (key=='=')
	{
		LCD_Clear();
		LCD_WriteString("enter the pass");
		u8 pass_tem[16]="";
		config_get_pass(pass_tem);
		if (strcmp(pass_tem,sys_pass)==0)
		{
			MOTOR_Stop(M1);
			mode_change_flag=Not_Done;
			sys_Mode=config;
		}
	}
}
void Fire_System_Led_color(Fire_System_Modes_Type mode)
{
	// check the indication system type
	#ifdef RGB_led
	switch(mode)
	{
		case config:
		DIO_WritePin(Led_red,LOW);
		DIO_WritePin(Led_green,HIGH);
		DIO_WritePin(Led_blue,HIGH);
		break;
		case fine:
		DIO_WritePin(Led_red,HIGH);
		DIO_WritePin(Led_green,LOW);
		DIO_WritePin(Led_blue,HIGH);
		break;
		case heat:
		DIO_WritePin(Led_red,LOW);
		DIO_WritePin(Led_green,HIGH);
		DIO_WritePin(Led_blue,HIGH);
		break;
		case fire:
		DIO_WritePin(Led_red,LOW);
		DIO_WritePin(Led_green,HIGH);
		DIO_WritePin(Led_blue,HIGH);
		break;
	}
#endif // RGB_led

	#ifdef multi_leds
	switch(mode)
	{
		case config:
		DIO_WritePin(config_led_pin,HIGH);
		DIO_WritePin(fine_led_pin,LOW);
		DIO_WritePin(fire_led_pin,LOW);
		DIO_WritePin(heat_led_pin,LOW);
		break;
		case fine:
		DIO_WritePin(config_led_pin,LOW);
		DIO_WritePin(fine_led_pin,HIGH);
		DIO_WritePin(fire_led_pin,LOW);
		DIO_WritePin(heat_led_pin,LOW);
		break;
		case heat:
		DIO_WritePin(config_led_pin,LOW);
		DIO_WritePin(fine_led_pin,LOW);
		DIO_WritePin(fire_led_pin,LOW);
		DIO_WritePin(heat_led_pin,HIGH);
		break;
		case fire:
		DIO_WritePin(config_led_pin,LOW);
		DIO_WritePin(fine_led_pin,LOW);
		DIO_WritePin(fire_led_pin,HIGH);
		DIO_WritePin(heat_led_pin,LOW);
		break;
	}
	#endif // multi_leds
}

// change the old pass
void Config_change_pass(void)
{
	//ask for the old pass
	LCD_Clear();
	LCD_WriteString("get the old pass");
	LCD_GoTo(1,0);
	LCD_WriteString("if done press =");
	u8 temp_pass[16]="";
	config_get_pass(temp_pass);
	// compare the entered pass with the old pass
	if (!strcmp(temp_pass,sys_pass))
	{
		// if entered a correct old pass
		LCD_Clear();
		// ask for the new pass
		LCD_WriteString("Enter the new pass");
		config_get_pass(sys_pass);
		LCD_Clear();
		LCD_GoTo(0,5);
		LCD_WriteString("Done");
		LCD_GoTo(1,0);
		LCD_WriteString("Press = to continue");
		key=NO_KEY;
		while (key==NO_KEY)
		{
			key=KEYPAD_GetKey();
		}
		sys_Mode=fine;
	}
	else
	{
		// if entered a wrong old pass
		LCD_Clear();
		LCD_WriteString("Error");
		Fire_System_Led_color(fire);
	}
}

//get pass from the user
void config_get_pass(u8 *password)
{
	u8 index=0;
	key=NO_KEY;
	while (key!= '=' && index <16)
	{
		key=KEYPAD_GetKey();
		switch (key)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			password[index++]=key;
			password[index]=0;
			LCD_Clear();
			LCD_WriteString(password);
			break;
			case 'C':
			index--;
			password[index]=0;
			LCD_Clear();
			LCD_WriteString(password);
			
		}
	}
}

void Fire_System_display(void)
{
	if (sys_temprature != sys_temprature_history || sys_smoke != sys_smoke_history || mode_change_flag == Not_Done)
	{
		mode_change_flag=Done;
		LCD_Clear();
		LCD_WriteString("temp= ");
		LCD_WriteNumber((s32)sys_temprature/10);
		LCD_WriteChar('.');
		LCD_WriteNumber((s32)sys_temprature%10);
		LCD_WriteString(" c");
		LCD_GoTo(1,0);
		LCD_WriteString("smoke= ");
		LCD_WriteNumber((s32)sys_smoke/50);
		LCD_WriteString(" %");
		sys_temprature_history=sys_temprature;
		sys_smoke_history=sys_smoke;
	}
}

u8 Is_config(void)
{
	key=KEYPAD_GetKey();
	if (key=='C')
	{
		sys_Mode=config;
		mode_change_flag=Not_Done;
		return 1;
	}
	else
		return 0;
}


void Fire_System_read(void)
{
	//read all sensors and add data to filter array
	Filter_Get_filtered_all_sensor();
	//get the new temp and smoke reads
	sys_temprature=Filter_Get_filtered_sensor_x(LM35_filter);
	sys_smoke=Filter_Get_filtered_sensor_x(MQ2_filter);
}