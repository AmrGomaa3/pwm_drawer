#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPE.h"
#include "../../../LIB/interruptVectorNum.h"
#include "TIMER0_interface.h"
#include "TIMER0_reg.h"


void (*TIMER0_ptr[2])(void) = {null};


void TIMER0_voidInit(u8 copy_u8mode) {
	if (copy_u8mode == OVF_MODE) {
		TCCR0_REG &= 0xB7;                                        // Set normal mode
	} else if (copy_u8mode == CTC_MODE) {
		TCCR0_REG = (TCCR0_REG & 0xB7) | (0x08);                  // Set CTC mode
		OCR0_REG = CTC_VALUE;                                     // Set compare value
	}
	
	TIMSK_REG = (TIMSK_REG & 0xFC) | (1 << copy_u8mode);          // Enable Timer0 Interrupts
	TCCR0_REG = (TCCR0_REG & 0xF8) | TIMER0_PRESCALER;            // Set prescaler
}


void TIMER0_voidFastPWM(u8 copy_u8duty) {
	TCCR0_REG = (TCCR0_REG & ~0x78) | 0x68;                       // Fast PWM non-inverting mode
	TCCR0_REG = (TCCR0_REG & 0xF8) | TIMER0_PRESCALER;            // Set prescaler
	OCR0_REG = ((u16)copy_u8duty * 255) / 100;                    // Set compare time
}


void TIMER0_voidSetCallback(void(*ptr)(void), u8 copy_u8mode) { TIMER0_ptr[copy_u8mode] = ptr; }


ISR(TIMER0_COMP) {
	if(TIMER0_ptr[1] != null) {
		TIMER0_ptr[1]();
	}
}
	
	
ISR(TIMER0_OVF) {
	if(TIMER0_ptr[0] != null) {
		TIMER0_ptr[0]();
	}	
}
