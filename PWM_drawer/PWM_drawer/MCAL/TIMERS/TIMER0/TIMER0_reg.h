#ifndef TIMER0_REG_H_
#define TIMER0_REG_H_


#define TCCR0_REG *((volatile u8*) 0x53)
#define TCNT0_REG *((volatile u8*) 0x52)
#define OCR0_REG  *((volatile u8*) 0x5C)
#define TIMSK_REG *((volatile u8*) 0x59)
#define TIFR_REG  *((volatile u8*) 0x58)


#endif /* TIMER0_REG_H_ */