#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


/* Prescaler select */
#define TIMER1_1_PRESCALER    1
#define TIMER1_8_PRESCALER    2
#define TIMER1_64_PRESCALER   3
#define TIMER1_256_PRESCALER  4
#define TIMER1_1024_PRESCALER 5

#define TIMER1_PRESCALER TIMER1_8_PRESCALER


#if TIMER1_PRESCALER == TIMER1_1_PRESCALER
	#define TIMER1_PRESCALER_DIV  1
#elif TIMER1_PRESCALER == TIMER1_8_PRESCALER
	#define TIMER1_PRESCALER_DIV  8
#elif TIMER1_PRESCALER == TIMER1_64_PRESCALER
	#define TIMER1_PRESCALER_DIV  64
#elif TIMER1_PRESCALER == TIMER1_256_PRESCALER
	#define TIMER1_PRESCALER_DIV  256
#elif TIMER1_PRESCALER == TIMER1_1024_PRESCALER
	#define TIMER1_PRESCALER_DIV  1024
#endif


#define OC1A 128
#define OC1B 32

#define RISING 1
#define FALLING 0


void TIMER1_voidFastPWMICR(u8 copy_u8pin);
void TIMER1_voidSetOCRVal(u16 copy_u16Val, u8 copy_u8pin);
void TIMER1_voidICRInit(u8 copy_u8sense);
void TIMER1_voidICRSenseControl(u8 copy_u8sense);
void TIMER1_voidResetICR(void);
u16  TIMER1_u16ReadICR(void);
void TIMER1_voidICRSetCallback(void (*ptr)(void));


#endif /* TIMER1_INTERFACE_H_ */