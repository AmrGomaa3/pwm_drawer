#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/* Ports */
#define DIO_PORTA 1
#define DIO_PORTB 2
#define DIO_PORTC 3
#define DIO_PORTD 4


/* Pins */
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7


/* Values */
#define HIGH 1
#define LOW 0


/* Direction */
#define INPUT 0
#define OUTPUT 1


/* Pin Functions */
void DIO_voidSetPinDir(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8dir);
void DIO_voidSetPinVal(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8val);
u8   DIO_voidReadPinVal(u8 copy_u8port, u8 copy_u8pin);
void DIO_voidTogglePinVal(u8 copy_u8port, u8 copy_u8pin);


/* Port Functions */
void DIO_voidSetPortDir(u8 copy_u8port, u8 copy_u8dir);
void DIO_voidSetPortVal(u8 copy_u8port, u8 copy_u8val);


#endif /* DIO_INTERFACE_H_ */