# pwm_drawer
A standalone real-time PWM signal analyser using bare-metal C and the ATmega32. The system uses Timer1 ICU to measure the PWM signal's period, frequency, and duty cycle, then displays the measurement and the waveform on a graphical LCD. Follows a layered MCAL/HAL architecture and includes custom drivers.
