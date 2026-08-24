#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_


#define GLCD_LEFT_SIDE  0
#define GLCD_RIGHT_SIDE 1
#define GLCD_BOTH_SIDES 2


void GLCD_voidInit(void);
void GLCD_voidSendCommand(u8 copy_u8Command, u8 copy_u8side);
void GLCD_voidSendData(u8 copy_u8Data);
void GLCD_voidClearDisplay(void);
void GLCD_voidGotoXY(u8 copy_u8X, u8 copy_u8Y);
void GLCD_voidDrawChar(u8 copy_u8char);
void GLCD_voidClearDisplay(void);
void GLCD_voidSendString(const s8* copy_ps8String);
void GLCD_voidSendNum(u32 copy_u32Num);
void GLCD_voidDrawPattern(const u8* pattern, u8 copy_u8size);


#endif /* GLCD_INTERFACE_H_ */