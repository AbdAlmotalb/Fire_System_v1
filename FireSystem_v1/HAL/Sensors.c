/*
 * Sensors.c
 *
 * Created: 7/9/2023 8:37:16 PM
 *  Author: Right Click
 */ 

#include "StdTypes.h"
#include "Sensors_CFG.h"
#include "sensors_Interface.h"
#include "ADC_Interface.h"

void Sensors_Init(void)
{
	
}
u16 Sensors_read_sensor(Sensor_type sensor)
{
	u16 out=ADC_Read((ADC_Channel_type)sensor);
	out=(u32)out*5000/1024;
	return out;
}


