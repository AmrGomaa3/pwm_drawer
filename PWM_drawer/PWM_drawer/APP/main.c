#include "main.h"


int main(void)
{
	APP_voidInit();
	
	u8 DC = 1;
	u16 update_counter = 0;
	
	TIMER0_voidFastPWM(DC);

	while (1) {
		APP_voidProcess();
		
		update_counter++;
		if (update_counter >= 50000) {
			update_counter = 0;
			
			DC++;
			if (DC >= 100) {
				DC = 1;
			}
			
			TIMER0_voidFastPWM(DC);
		}
	}
}