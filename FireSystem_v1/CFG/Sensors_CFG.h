/*
 * Sensors_CFG.h
 *
 * Created: 7/9/2023 8:38:04 PM
 *  Author: Right Click
 */ 


#ifndef SENSORS_CFG_H_
#define SENSORS_CFG_H_

#define VREF 5000
/*
#define LM35_CH CH_0
#define MQ2_CH CH_7
*/

typedef enum{
	LM35_CH =0,
	MQ2_CH=7
}Sensor_type;


#endif /* SENSORS_CFG_H_ */