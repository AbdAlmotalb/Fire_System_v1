
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

#include "DIO_Inteface.h"



/*********************PIN CONFIG *************************/
/*M1 */
#define  M1_IN1   PINC4
#define  M1_IN2   PINC3

#define  M2_IN1   PIND1
#define  M2_IN2   PIND2


#define  M3_IN1   PIND3
#define  M3_IN2   PIND4


#define  M4_IN1   PIND5
#define  M4_IN2   PIND6

typedef struct{
	DIO_Pin_type in1;
	DIO_Pin_type in2;
	
}MOTOR_Pin_type;


/*********************************	IN1   IN2*/
extern const MOTOR_Pin_type MotorPinsArr[4];


#define  MOTOR_INIT_STATE


#define MOTOR_MAX_SPEED  90

#endif /* MOTOR_CFG_H_ */