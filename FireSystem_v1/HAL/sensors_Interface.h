/*
 * sensors_Interface.h
 *
 * Created: 7/9/2023 8:37:41 PM
 *  Author: Right Click
 */ 


#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

#include "Sensors_CFG.h"

/*
typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}Sensor_Channel_type;
*/



void Sensors_Init(void);
u16 Sensors_read_sensor(Sensor_type sensor);



#endif /* SENSORS_INTERFACE_H_ */