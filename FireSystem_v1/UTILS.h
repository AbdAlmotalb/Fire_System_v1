#ifndef UTILS_H_
#define UTILS_H_


#define  READ_BIT(reg,bit)  ((reg>>bit)&1)
//#define  READ_BIT2(reg,bit)  (reg&(1<<BIT))
#define  SET_BIT(reg,bit)   (reg=reg|(1<<bit))
#define  CLR_BIT(reg,bit)   (reg=reg&(~(1<<bit)))
#define  TOG_BIT(reg,bit)   (reg=reg^(1<<bit))

#define  F_CPU   8000000
#include <util/delay.h>


#endif /* UTILS_H_ */