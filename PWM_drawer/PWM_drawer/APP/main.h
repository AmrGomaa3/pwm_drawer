#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 16000000UL
#include <util/delay.h>
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/GI/GI_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/TIMERS/TIMER0/TIMER0_interface.h"
#include "../MCAL/TIMERS/TIMER1/TIMER1_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/LED/LED_config.h"
#include "../HAL/BTN/BTN_interface.h"
#include "../HAL/BTN/BTN_config.h"
#include "../HAL/GLCD/GLCD_interface.h"
#include "../HAL/GLCD/GLCD_config.h"
#include "./PWM_ANALYSER/PWM_ANALYSER.h"


#endif /* MAIN_H_ */