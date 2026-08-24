#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define LOW_LEVEL 0
#define ANY_CHANGE 1
#define FALLING_EDGE 2
#define RISING_EDGE 3


#define ISR_INT0 0
#define ISR_INT1 1
#define ISR_INT2 2


#define INT0 6
#define INT1 7
#define INT2 5


void EXTI_voidInit(u8 copy_u8num, u8 copy_u8sense);
void EXTI_voidEnable(u8 copy_u8num);
void EXTI_voidDisable(u8 copy_u8num);
void EXTI_voidSetCallback(void (*ptr)(void), u8 copy_u8num);


#endif /* EXTI_INTERFACE_H_ */