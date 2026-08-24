#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"


void LED_voidInit(u8 copy_u8port, u8 copy_u8pin) {
	DIO_voidSetPinDir(copy_u8port, copy_u8pin, OUTPUT);
}


void LED_voidLEDOn(u8 copy_u8port, u8 copy_u8pin) {
	DIO_voidSetPinVal(copy_u8port, copy_u8pin, HIGH);
}



void LED_voidLEDOff(u8 copy_u8port, u8 copy_u8pin) {
	DIO_voidSetPinVal(copy_u8port, copy_u8pin, LOW);
}


void LED_voidLEDToggle(u8 copy_u8port, u8 copy_u8pin) {
	DIO_voidTogglePinVal(copy_u8port, copy_u8pin);
}
