/*
 * Fire_system.h
 *
 * Created: 9/23/2023 1:56:34 PM
 *  Author: Right Click
 */ 


#ifndef FIRE_SYSTEM_H_
#define FIRE_SYSTEM_H_


/*
led indication pins
*/
#define config_led_pin PINB0
#define fine_led_pin PINB1
#define heat_led_pin PINB2
#define fire_led_pin PINB3

#define Led_red PINB0
#define Led_green PINB1
#define Led_blue PINB2

/*
led indication system
*/
#define multi_leds
//#define RGB_led

/*
transaction temperature
*/
#define heat_transation_temp ((u16)500)
#define fine_transation_temp ((u16)450)

#define Smoke_threshold ((u16)50)

/*
system modes
*/
typedef enum{
	config,
	fine,
	heat,
	fire
	} Fire_System_Modes_Type;

/*
transaction flags status
*/
typedef enum{
	Done,
	Not_Done
	}Fire_System_MSG_Type;
	
/*
initialization the system
*/
void Fire_System_Init(void);

/*
the runnable function
*/
void Fire_System_Run(void);

/*
configuration mode function
*/
void Fire_System_config(void);

/*
normal mode function
*/
void Fire_System_fine(void);

/*
high temperature detection function
*/
void Fire_System_heat(void);


//display function
void Fire_System_display(void);
//read system data
void Fire_System_read(void);
/*
fire detection function
*/
void Fire_System_fire(void);

void Config_change_pass(void);
void config_get_pass(u8 *password);
void Fire_System_Led_color(Fire_System_Modes_Type mode);
u8 Is_config(void);

#endif /* FIRE_SYSTEM_H_ */