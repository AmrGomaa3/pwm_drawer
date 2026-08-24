#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


/* TIMER0 prescaler */
#define TIMER0_NO_PRESCALER   1
#define TIMER0_8_PRESCALER    2
#define TIMER0_64_PRESCALER   3
#define TIMER0_256_PRESCALER  4
#define TIMER0_1024_PRESCALER 5

#define TIMER0_PRESCALER TIMER0_64_PRESCALER


/* TIMER0 modes */
#define OVF_MODE 0
#define CTC_MODE 1


/* CTC compare value */
#define CTC_VALUE 250


void TIMER0_voidInit(u8 copy_u8mode);
void TIMER0_voidSetCallback(void(*ptr)(void), u8 copy_u8mode);
void TIMER0_voidFastPWM(u8 copy_u8duty);


#endif /* TIMER0_INTERFACE_H_ */