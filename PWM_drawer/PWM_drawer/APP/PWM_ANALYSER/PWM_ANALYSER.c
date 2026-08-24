#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/GI/GI_interface.h"
#include "../../MCAL/EXTI/EXTI_interface.h"
#include "../../MCAL/TIMERS/TIMER0/TIMER0_interface.h"
#include "../../MCAL/TIMERS/TIMER1/TIMER1_interface.h"
#include "../../HAL/LED/LED_interface.h"
#include "../../HAL/LED/LED_config.h"
#include "../../HAL/BTN/BTN_interface.h"
#include "../../HAL/BTN/BTN_config.h"
#include "../../HAL/GLCD/GLCD_interface.h"
#include "../../HAL/GLCD/GLCD_config.h"
#include "PWM_ANALYSER.h"


#define F_CPU 16000000UL


static volatile u16 T1  = 0;
static volatile u16 T2  = 0;
static volatile u16 T3  = 0;
static volatile u8 FLAG = 0;
static volatile u8 FREEZE = 0;


void APP_voidICUISR(void) {
	static u8 state = 0;

	if (state == 0) {
		T1 = TIMER1_u16ReadICR();
		TIMER1_voidICRSenseControl(FALLING);
		state = 1;
	} else if (state == 1) {
		T2 = TIMER1_u16ReadICR();
		
		u16 Ton = T2 - T1;
		if (Ton == 0) {
			state = 0;
			TIMER1_voidICRSenseControl(RISING);
			return;
		}
		
		TIMER1_voidICRSenseControl(RISING);
		state = 2;
	} else if (state == 2) {
		T3 = TIMER1_u16ReadICR();
		
		u16 Ton = T2 - T1;
		u16 Ttotal = T3 - T1;

		if (Ttotal > Ton && Ttotal > 0) {
			FLAG = 1;
		}
		
		state = 0;
		TIMER1_voidICRSenseControl(RISING);
	}
}


void APP_voidBTNISR(void) {
	FREEZE ^= 1;
	LED_voidLEDToggle(LED1);
}


void APP_voidPrintFrequency(u32 copy_u32frequency) {
	/* clear previous reading */
	GLCD_voidGotoXY(12, 0);
	GLCD_voidSendString("        ");
						
	GLCD_voidGotoXY(12, 0);
						
	if (copy_u32frequency <= 999) {
		GLCD_voidSendNum(copy_u32frequency);
		GLCD_voidSendString("Hz");
	} else if (copy_u32frequency <= 999999) {
		GLCD_voidSendNum(copy_u32frequency/1000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((copy_u32frequency/100)%10);
		GLCD_voidSendString("KHz");
	} else if (copy_u32frequency <= 999999999) {
		GLCD_voidSendNum(copy_u32frequency/1000000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((copy_u32frequency/100000)%10);
		GLCD_voidSendString("MHz");
	} else if (copy_u32frequency <= 4294967295) {
		GLCD_voidSendNum(copy_u32frequency/1000000000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((copy_u32frequency/100000000)%10);
		GLCD_voidSendString("GHz");
	}
}


void APP_voidPrintDuty(u8 copy_u8duty) {
	GLCD_voidGotoXY(104, 0);
	GLCD_voidSendString("    ");
	GLCD_voidGotoXY(104, 0);
	GLCD_voidSendNum(copy_u8duty);
	GLCD_voidDrawChar('%');
}


void APP_voidInit(void) {
	LED_voidInit(LED1);
	LED_voidLEDOn(LED1);
		
	GLCD_voidInit();
	DIO_voidSetPinDir(DIO_PORTB, DIO_PIN3, OUTPUT);
	DIO_voidSetPinDir(DIO_PORTD, DIO_PIN6, INPUT);

	TIMER1_voidICRSetCallback(APP_voidICUISR);
	TIMER1_voidICRInit(RISING);

	/* Configure External Interrupt for Button */
	EXTI_voidEnable(INT0);
	BTN_voidInit(BTN1);
	EXTI_voidSetCallback(APP_voidBTNISR, ISR_INT0);
	EXTI_voidInit(INT0, FALLING_EDGE);

	GI_voidEnable();

	/* Draw Static UI */
	GLCD_voidGotoXY(0, 0);
	GLCD_voidSendString("F:???");

	GLCD_voidGotoXY(74, 0);
	GLCD_voidSendString("DUTY:???");
	
	GLCD_voidGotoXY(74, 2);
	GLCD_voidSendString("T:???");
}


void APP_voidDrawSignal(u32 copy_u32frequency, u8 copy_u8duty) {
	u8 half_cycle = 0;
	u32 t_period = 1000000000ULL/copy_u32frequency;             // periodic time in nanoseconds
	
	if (t_period >= 1000000000ULL) half_cycle = 40;
	else if (t_period >= 1000000UL) half_cycle = 20;
	else if (t_period >= 1000UL) half_cycle = 10;
	else half_cycle = 5;
	
	u8 waveform = ((u16)copy_u8duty * half_cycle * 2) / 100;
	
	u8 x = 0;
	
	for (u8 i = 0; i < (128 / (half_cycle * 2 + 2)); i++) {
		/* high Line */
		GLCD_voidGotoXY(x, 5);
		for (u8 j = 0; j < waveform; j++) {
			GLCD_voidSendData(0x01);
			x++;
		}
		
		/* falling Edge */
		GLCD_voidGotoXY(x, 5);
		GLCD_voidSendData(0xFF);
		GLCD_voidGotoXY(x, 6);
		GLCD_voidSendData(0xFF);
		x++;

		/* low Line */
		for (u8 j = 0; j < (half_cycle * 2 - waveform); j++) {
			GLCD_voidSendData(0x80);
			x++;
		}

		/* rising Edge */
		GLCD_voidGotoXY(x, 6);
		GLCD_voidSendData(0xFF);
		GLCD_voidGotoXY(x, 5);
		GLCD_voidSendData(0xFF);
		x++;
	}
	
	GLCD_voidGotoXY(x, 5);
	for (; x < 128; x++) GLCD_voidSendData(0x01);
	
	/* draw periodic time */
	x = waveform;
	GLCD_voidGotoXY(x, 3);
	GLCD_voidSendData(0xFC);
	GLCD_voidGotoXY(x, 4);
	GLCD_voidSendData(0x3F);
	
	for (u8 i = 0; i < (half_cycle*2) +1; i++) {
		GLCD_voidSendData(0x02);
		x++;
	}
	
	x++;
	GLCD_voidGotoXY(x, 4);
	GLCD_voidSendData(0x3F);
	GLCD_voidGotoXY(x, 3);
	GLCD_voidSendData(0xFC);
	GLCD_voidGotoXY(waveform + half_cycle - 2, 3);
	GLCD_voidDrawChar('T');

	GLCD_voidGotoXY(86, 2);
	GLCD_voidSendString("       ");
	GLCD_voidGotoXY(86, 2);
	
	if (t_period <= 999) {
		GLCD_voidSendNum(t_period);
		GLCD_voidSendString("ns");
	} else if (t_period <= 999999) {
		GLCD_voidSendNum(t_period/1000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((t_period/100)%10);
		GLCD_voidSendString("us");
	} else if (t_period <= 999999999) {
		GLCD_voidSendNum(t_period/1000000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((t_period/100000)%10);
		GLCD_voidSendString("ms");
	} else if (t_period <= 4294967295) {
		GLCD_voidSendNum(t_period/1000000000);
		GLCD_voidDrawChar('.');
		GLCD_voidSendNum((t_period/100000000)%10);
		GLCD_voidSendString("s");
	}
}


void APP_voidWipeSignal(void) {
	GLCD_voidGotoXY(0, 3);
	
	for (u16 i = 0; i < 512; i++) GLCD_voidSendData(0x00);
	
	GLCD_voidGotoXY(0, 0);
}


void APP_voidProcess(void) {
	static u8 prev_DC = 0xFF;
	static u32 prev_Freq = 0xFFFFFFFF;
	
	if (FLAG == 1) {
		/* Process and update ONLY if FREEZE is 0 */
		if (!FREEZE) {
			u16 Ton = T2 - T1;
			u16 Ttotal = T3 - T1;

			if (Ttotal > 0 && Ton <= Ttotal) {
				u8 current_DC = (((u32)Ton * 100) + (Ttotal / 2)) / Ttotal;
				u32 current_Freq = (F_CPU / TIMER1_PRESCALER_DIV) / Ttotal;

				if (current_Freq != prev_Freq || current_DC != prev_DC) {
					APP_voidWipeSignal();
					APP_voidDrawSignal(current_Freq, current_DC);
				
					/* Update Frequency ONLY if changed */
					if (current_Freq != prev_Freq) {
						APP_voidPrintFrequency(current_Freq);
						prev_Freq = current_Freq;
					}

					/* Update Duty Cycle ONLY if changed */
					if (current_DC != prev_DC) {
						APP_voidPrintDuty(current_DC);
						prev_DC = current_DC;
					}
				}
			}
		}

		FLAG = 0; // Clear capture flag for next cycle
	}
}
