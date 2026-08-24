#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/interruptVectorNum.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"


void (*EXTI_PTR[3])(void) = {null};


void EXTI_voidInit(u8 copy_u8num, u8 copy_u8sense) {
	switch (copy_u8num)
	{
	case INT0:
		if (copy_u8sense == LOW_LEVEL)
		{
			CLR_BIT(MCUCR_REG, 0);
			CLR_BIT(MCUCR_REG, 1);
		} else if (copy_u8sense == ANY_CHANGE)
		{
			CLR_BIT(MCUCR_REG, 1);
			SET_BIT(MCUCR_REG, 0);
		} else if (copy_u8sense == FALLING_EDGE)
		{
			CLR_BIT(MCUCR_REG, 0);
			SET_BIT(MCUCR_REG, 1);
		} else if (copy_u8sense == RISING_EDGE) {
			SET_BIT(MCUCR_REG, 0);
			SET_BIT(MCUCR_REG, 1);
		} break;	
	case INT1:
		if (copy_u8sense == LOW_LEVEL)
		{
			CLR_BIT(MCUCR_REG, 2);
			CLR_BIT(MCUCR_REG, 3);
		} else if (copy_u8sense == ANY_CHANGE)
		{
			CLR_BIT(MCUCR_REG, 3);
			SET_BIT(MCUCR_REG, 2);
		} else if (copy_u8sense == FALLING_EDGE)
		{
			CLR_BIT(MCUCR_REG, 2);
			SET_BIT(MCUCR_REG, 3);
		} else if (copy_u8sense == RISING_EDGE) {
			SET_BIT(MCUCR_REG, 2);
			SET_BIT(MCUCR_REG, 3);
		} break;
	case INT2:
		if (copy_u8sense == FALLING_EDGE)
		{
			CLR_BIT(MCUCSR_REG, 6);
		} else if (copy_u8sense == RISING_EDGE) {
			SET_BIT(MCUCSR_REG, 6);
		} break;
	}
}


void EXTI_voidEnable(u8 copy_u8num) {
	SET_BIT(GICR_REG, copy_u8num);
}

void EXTI_voidDisable(u8 copy_u8num) {
	CLR_BIT(GICR_REG, copy_u8num);
}


void EXTI_voidSetCallback(void (*ptr)(void), u8 copy_u8num) {
	EXTI_PTR[copy_u8num] = ptr;
}


ISR(_INT0) { 
	if (EXTI_PTR[0] != null) {
		EXTI_PTR[0]();
	}
}


ISR(_INT1) {
	if (EXTI_PTR[1] != null) {
		EXTI_PTR[1]();
	}
}


ISR(_INT2) {
	if (EXTI_PTR[2] != null) {
		EXTI_PTR[2]();
	}
}
