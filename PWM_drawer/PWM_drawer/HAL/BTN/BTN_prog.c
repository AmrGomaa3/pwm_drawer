#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "BTN_interface.h"
#include "BTN_config.h"


void BTN_voidInit(u8 copy_u8port, u8 copy_u8pin) {
	DIO_voidSetPinDir(copy_u8port, copy_u8pin, INPUT);
}