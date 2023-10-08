/*
 * Filter.h
 *
 * Created: 9/19/2023 9:40:15 PM
 *  Author: Right Click
 */ 


#ifndef FILTER_H_
#define FILTER_H_

#define Filter_count 2
#define Filter_size 10 

//#include "sensors_Interface.h"

/*
struct contains filter data
1- the sensor name to use it to access the sensor functions 
2- index as a queue index
3- filter array
*/
typedef struct{
	Sensor_type Sensor_name;
	u8 index;
	u16 Filer_array[Filter_size];
	} Filter_Type;


/*
contains filter used in the system
*/
typedef enum{
	LM35_filter=0,
	MQ2_filter
	
	}filter_name_type;

/*
1- initialize the filter  
*/
void Filter_Init(void);

/*
get all sensors data and put it in its index
*/
Error_t Filter_Get_filtered_all_sensor();

/*
get the required sensor data
*/
u16 Filter_Get_filtered_sensor_x(filter_name_type filter_name);
//void filter_print(void);


#endif /* FILTER_H_ */