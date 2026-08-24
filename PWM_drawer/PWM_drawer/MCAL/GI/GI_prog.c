#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "GI_interface.h"
#include "GI_reg.h"


void GI_voidEnable(void) { __asm volatile("SEI"); }


void GI_voidDisable(void) { __asm volatile("CLI"); }

