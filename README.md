# PWM Drawer

A standalone real-time PWM signal analyser built from scratch using bare-metal C and the ATmega32. The system uses Timer1 Input Capture to measure the PWM signal's period, frequency, and duty cycle, then displays the measurements alongside a live waveform on a graphical LCD. Frequency is displayed with 0.1 resolution and duty cycle with 1% resolution. A freeze/hold mode allows the user to pause the display for easier inspection of measurements.

The project follows a layered MCAL/HAL architecture and includes custom drivers for DIO, EXTI, Timer0, Timer1, GLCD, LEDs, and buttons. The complete system was simulated and validated in Proteus.

---
Video demo: https://youtu.be/JcgQYUyIVQY
---

## Hardware Setup

| Peripheral | Pins | Role |
|---|---|---|
| Timer1 ICP1 | PD6 | PWM signal input - the signal being measured |
| Timer0 OC0 | PB3 | Internal demo source: Fast PWM output, duty swept 1–99% in `main()` |
| EXTI INT0 | PD2 | Freeze/hold button |
| GLCD Data Bus | PORTA | 8-bit parallel data bus to both GLCD chip segments |
| GLCD Control | PORTC (CS1, CS2, RS, RW, E, RST) | Chip-select and control lines for a dual-controller 128×64 GLCD |
| Status LED | PC7 | Freeze indicator |

The board doubles as its own signal source: `TIMER0_voidFastPWM()` drives
PB3 as a demo waveform, sweeping the duty cycle from 1% to 99% every 50,000
main-loop iterations, so the analyser has something to read without extra
hardware. To measure a real external signal instead, feed it into PD6
(ICP1) directly.

---

## Measurement Accuracy

| Quantity | Resolution |
|---|---|
| Frequency | 0.1 (auto-scaled Hz / KHz / MHz / GHz) |
| Period | 0.1 (auto-scaled ns / us / ms / s) |
| Duty Cycle | 1% |

> Note: Measurement is limited by the ATmega32 16MHz frequency and timer1 prescaler

---

## Architecture

```
APP/            → Application layer (PWM_ANALYSER, main)
HAL/             → Hardware Abstraction Layer (GLCD, LED, Button)
MCAL/            → Microcontroller Abstraction Layer (DIO, EXTI, GI, Timer0, Timer1)
LIB/             → Shared types & bit-math macros
```

| Module | Responsibility |
|---|---|
| `MCAL/TIMERS/TIMER1` | Input Capture configuration & edge-sense control |
| `MCAL/TIMERS/TIMER0` | Fast PWM generation (demo signal source) |
| `MCAL/EXTI` | External interrupt for the freeze button |
| `MCAL/DIO` | Pin/port level I/O |
| `HAL/GLCD` | Graphical LCD driver (128×64, dual chip-select) |
| `HAL/BTN` / `HAL/LED` | Freeze button input / status LED |
| `APP/PWM_ANALYSER` | Edge-capture state machine, frequency/duty math, GLCD rendering |

---

## Design Decisions

### The 3-State Edge Capture Sequence

A single PWM period requires three edges to fully characterize: rising →
falling → rising. `APP_voidICUISR()` walks a 3-state machine, flipping the
Input Capture edge-sense direction (`RISING`/`FALLING`) after each
timestamp so the *next* interrupt fires on the opposite edge:

| State | On Entry | Captures | Edge-sense set for next IRQ |
|---|---|---|---|
| 0 | Waiting for cycle start | `T1` (rising edge) | `FALLING` |
| 1 | Mid-cycle | `T2` (falling edge) → `Ton = T2 - T1` | `RISING` |
| 2 | Cycle closing | `T3` (next rising edge) → `Ttotal = T3 - T1` | `RISING`, `FLAG = 1` |

If `Ton` comes back as `0` in state 1 (edge-sense misfire or noise), the
state machine resets to state 0 immediately rather than propagating a bad
reading.

### Redraw Only On Change

```c
if (current_Freq != prev_Freq || current_DC != prev_DC) {
    APP_voidWipeSignal();
    APP_voidDrawSignal(current_Freq, current_DC);
    ...
}
```

Every column of the waveform is drawn one GLCD data-write at a time over an
8-bit parallel bus, meaning a steady signal produces a steady, flicker-free display instead of
being redrawn dozens of times a second for no visible difference.

### Auto-Scaled Waveform Rendering

The GLCD is only 128 pixels wide, so a fixed pixels-per-microsecond scale
would either flatten fast signals into a smear or make slow signals overrun
the screen. `APP_voidDrawSignal()` instead buckets the period into a
half-cycle pixel width before drawing:

| Period (`t_period`) | `half_cycle` (pixels) |
|---|---|
| ≥ 1 s | 40 |
| ≥ 1 ms | 20 |
| ≥ 1 µs | 10 |
| < 1 µs | 5 |

The waveform, the "T" period marker, and the bracket above it are all
derived from this single value, so the whole drawing scales consistently
regardless of which bucket the signal falls into.

### Freeze via a Single Toggle

```c
void APP_voidBTNISR(void) {
    FREEZE ^= 1;
    LED_voidLEDToggle(LED1);
}
```

Stops the display from being updated, letting you hold a reading steady for as long as you need to read it.

---

## File Structure

```
PWM_drawer/
└── PWM_drawer/
    ├── APP/
    │   ├── main.c / main.h
    │   └── PWM_ANALYSER/
    │       ├── PWM_ANALYSER.c
    │       └── PWM_ANALYSER.h
    ├── HAL/
    │   ├── BTN/    (BTN_prog.c, BTN_interface.h, BTN_config.h)
    │   ├── GLCD/   (GLCD_prog.c, GLCD_interface.h, GLCD_config.h)
    │   └── LED/    (LED_prog.c, LED_interface.h, LED_config.h)
    ├── MCAL/
    │   ├── DIO/
    │   ├── EXTI/
    │   ├── GI/
    │   └── TIMERS/
    │       ├── TIMER0/
    │       └── TIMER1/
    ├── LIB/        (STD_TYPE.h, BIT_MATH.h, interruptVectorNum.h)
    └── PWM_drawer.cproj
PWM_drawer.atsln
Simulation/
└── PWM_drawer.pdsprj
```

---

## Building

Built with **Atmel Studio** (avr-gcc toolchain, ATmega32 target). Open
`PWM_drawer/PWM_drawer.atsln` and build normally, or invoke the generated
Makefile inside the Debug/Release configuration directly.

## Simulation

Tested and verified in **Proteus** `Simulation/PWM_drawer.pdsprj`. The
external PWM source in simulation can be swapped for the on-board Timer0
demo signal or an external generator wired into PD6.

---

## Limitations

- **No debounce on the freeze button** a noisy switch edge on INT0 can
  double-toggle `FREEZE` faster than intended.

- **Non-atomic capture read**: `T1`/`T2`/`T3` are `volatile u16` written by
  the ICU ISR and read in the main loop without disabling interrupts. A
  16-bit read on AVR isn't atomic, so in rare cases a capture firing
  mid-read could hand `APP_voidProcess()` a torn value.

---

## License

The project is licensed under the MIT License.
See the [LICENSE](./LICENSE) file for license information.

## Author

**Amr Gomaa**
GitHub: [AmrGomaa3](https://github.com/AmrGomaa3)
