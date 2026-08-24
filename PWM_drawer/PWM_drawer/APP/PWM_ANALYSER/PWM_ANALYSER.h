#ifndef PWM_ANALYSER_H_
#define PWM_ANALYSER_H_


void APP_voidICUISR(void);
void APP_voidBTNISR(void);
void APP_voidPrintFrequency(u32 copy_u32frequency);
void APP_voidPrintDuty(u8 copy_u8duty);
void APP_voidInit(void);
void APP_voidDrawSignal(u32 copy_u32frequency, u8 copy_u8duty);
void APP_voidWipeSignal(void);
void APP_voidProcess(void);


#endif /* PWM_ANALYSER_H_ */