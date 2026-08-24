#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPE.h"
#include "../../../LIB/interruptVectorNum.h"
#include "TIMER1_interface.h"
#include "TIMER1_reg.h"


void (*ICR_PTR)(void) = null;


void TIMER1_voidFastPWMICR(u8 copy_u8pin) {
	/* Mode 14: fast PWM */
	CLR_BIT(TCCR1A_REG, 0);
	SET_BIT(TCCR1A_REG, 1);
	SET_BIT(TCCR1B_REG, 3);
	SET_BIT(TCCR1B_REG, 4);
	
	/* Choose compare unit */
	TCCR1A_REG = (TCCR1A_REG & 0x0F) | copy_u8pin;
	
	ICR1_REG = 40000;
	
	TCCR1B_REG = (TCCR1B_REG & 0xF8) | TIMER1_PRESCALER;
}


void TIMER1_voidSetOCRVal(u16 copy_u16Val, u8 copy_u8pin) {
	if (copy_u8pin == OC1A) OCR1A_REG = copy_u16Val;
	else if (copy_u8pin == OC1B) OCR1B_REG = copy_u16Val;
}


void TIMER1_voidICRInit(u8 copy_u8sense) {
	TCCR1B_REG = (TCCR1B_REG & 0xF8) | TIMER1_PRESCALER;
	
	switch (copy_u8sense)
	{
		case RISING:
		SET_BIT(TCCR1B_REG, 6);
		break;
		case FALLING:
		CLR_BIT(TCCR1B_REG, 6);
		break;
	}
		
	SET_BIT(TIMSK_REG, 5);
}


void TIMER1_voidICRSenseControl(u8 copy_u8sense) {
	switch (copy_u8sense)
	{
		case RISING:
		SET_BIT(TCCR1B_REG, 6);
		break;
		case FALLING:
		CLR_BIT(TCCR1B_REG, 6);
		break;
	}
}


void TIMER1_voidResetICR(void) { TCNT1_REG = 0x0000; }


u16 TIMER1_u16ReadICR(void) { return ICR1_REG; }
	

void TIMER1_voidICRSetCallback(void (*ptr)(void)) { ICR_PTR = ptr; }


ISR(TIMER1_CAPT) {
	if (ICR_PTR != null) ICR_PTR();
}
