#ifndef DIO_REG_H_
#define DIO_REG_H_


/* Port A */
#define PORTA_REG *((volatile u8*) 0x3B)
#define DDRA_REG  *((volatile u8*) 0x3A)
#define PINA_REG  *((volatile u8*) 0x39)

/* Port B */
#define PORTB_REG *((volatile u8*) 0x38)
#define DDRB_REG  *((volatile u8*) 0x37)
#define PINB_REG  *((volatile u8*) 0x36)

/* Port C */
#define PORTC_REG *((volatile u8*) 0x35)
#define DDRC_REG  *((volatile u8*) 0x34)
#define PINC_REG  *((volatile u8*) 0x33)

/* Port D */
#define PORTD_REG *((volatile u8*) 0x32)
#define DDRD_REG  *((volatile u8*) 0x31)
#define PIND_REG  *((volatile u8*) 0x30)


#endif /* DIO_REG_H_ */