/*
 * ADC.c
 *
 * Created: 7/8/2023 9:25:47 PM
 *  Author: Right Click
 */ 
#include "StdTypes.h"
#include "MemMap.h"

#include "UTILS.h"
#include "ADC_Interface.h"



void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/* vref*/
	switch(vref)
	{
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
	}
	/* prescaller*/
	
	ADCSRA&=0XF8;
	scaler&=0X07;
	ADCSRA=ADCSRA|scaler;
	
	/* enable ADC*/
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type CH)
{
	//u16 result=0;
	/* select channel*/
	ADMUX &= 0xE0;
	ADMUX |= CH;
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait conversion*/
	while(READ_BIT(ADCSRA,ADSC));
	/*get result*/
	//result=ADCL ;
	//result|= (ADCH << 8);
	
	return ADC;
}

/* return mv*/
u16 ADC_VoltRead(ADC_Channel_type CH);
void ADC_StartConversion(ADC_Channel_type CH);
u8 ADC_GetReadPerodic(u16*pdata);
u16 ADC_GetRead(void);
u16 ADC_GetReadNoblock(void);

