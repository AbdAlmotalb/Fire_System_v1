/*
 * Filter.c
 *
 * Created: 9/19/2023 9:39:51 PM
 *  Author: Right Click
 */ 

# define F_CPU 8000000UL
#include <util/delay.h>


#include "StdTypes.h"
#include "sensors_Interface.h"
#include "Filter.h"
#include "LCD_Interface.h"

/*
filter array contains all filters
*/
static Filter_Type my_filters [Filter_count];


void Filter_Init(void)
{
	/*
	filling the filter data
	*/
	my_filters[0].Sensor_name= LM35_CH;
	my_filters[0].index=0;
	my_filters[1].Sensor_name= MQ2_CH;
	my_filters[1].index=0;
	/*
	fill all filter array with the first sensor read
	*/
	for (u8 j=0; j<Filter_count;j++)
	{
		u16 tem=Sensors_read_sensor(my_filters[j].Sensor_name);
		for (u8 i=0;i<Filter_size;i++)
		{
			my_filters[j].Filer_array[i]=tem;
		}
	}

}


Error_t Filter_Get_filtered_all_sensor()
{
	/*
	run all sensors and fill the next index with the new data 
	*/
	for (u8 i =0;i<Filter_count;i++)
	{
		my_filters[i].Filer_array[my_filters[i].index]=Sensors_read_sensor(my_filters[i].Sensor_name);
		my_filters[i].index=(my_filters[i].index +1)%Filter_size;
	}
	return OK;
}
u16 Filter_Get_filtered_sensor_x(filter_name_type filter_name)
{
	u32 sum=0;  //to sum all filter array in it
	/*
	sum all filter array in sum var
	*/
	for (u8 i=0;i<Filter_size;i++)
	{
		sum+= (u32) my_filters[filter_name].Filer_array[i];
	}
	/*
	return the sum after dividing by the filter array size
	*/
	return (u16)(sum/Filter_size);
}
/*
void filter_print(void)
{
	for (u8 i=0;i<10;i++)
	{
		LCD_GoTo(1,0);
		LCD_WriteNumber(my_filters[0].Filer_array[i]);
		LCD_WriteChar('-');
		LCD_WriteNumber(i);
		_delay_ms(500);
	}
	/*
	_delay_ms(3000);
	LCD_GoTo(1,0);
	for (u8 i=4;i<8;i++)
	{
		LCD_WriteNumber(my_filters[0].Filer_array[i]);
	}
	*/
	/*
	LCD_GoTo(1,0);
	LCD_WriteNumber(my_filters[0].Filer_array[9]);
	
}
*/