# 🎚️ STM32 Analog I/O and PWM Control (ECE 153B Labs 5A–5B)

This project demonstrates how to use the STM32L476 microcontroller for analog input/output and PWM signal generation. It integrates ADC readings, DAC waveform output, EXTI interrupt-driven control, and LED brightness modulation using PWM, forming a responsive embedded control loop.

## 🔍 Lab Overview

| Lab  | Focus Areas                         | Description                                                                 |
|------|-------------------------------------|-----------------------------------------------------------------------------|
| 5A   | ADC + PWM                           | Reads analog voltage using ADC and adjusts LED brightness via PWM          |
| 5B   | ADC + PWM + DAC + EXTI              | Adds EXTI interrupts to step a DAC value up/down and observe LED PWM effects|

## 🧰 Features

- 🧪 Analog-to-Digital Conversion (ADC) from external voltage source on PA1
- 💡 Pulse Width Modulation (PWM) on PA5 to modulate LED brightness
- 🔊 Digital-to-Analog Conversion (DAC) output via PA4
- 🛎️ External interrupt (EXTI13 / user button) to trigger DAC value adjustments
- ↕️ DAC value ramps up or down in steps with each button press
- 🔁 Real-time feedback loop between input (ADC), output (DAC), and PWM duty cycle

## 📁 File Structure

- `main (1).c`: Lab 5A – ADC input to PWM LED brightness
- `main (2).c`: Lab 5B – ADC + EXTI-driven DAC with PWM output
- `ADC.c`: ADC configuration and initialization
- `DAC.c`: DAC output and step value management
- `EXTI.c`: Button interrupt (EXTI13) handler and DAC update logic
- `PWM.c`: Timer 2 PWM setup on channel 1 (PA5)
- `SysClock.c`: Initializes system clock to 8 MHz MSI

## 📦 Dependencies

- STM32L476 Discovery board
- CMSIS-compliant toolchain (STM32CubeIDE, Keil MDK, etc.)
- Headers: `stm32l476xx.h`, STM32 standard peripheral library

## 🚀 How to Run

1. Flash `main (1).c` to test ADC input controlling PWM brightness.
2. Flash `main (2).c` to test EXTI-driven DAC with real-time ADC-PWM feedback.
3. Connect an analog voltage source to PA1.
4. Monitor PWM output on PA5 (can be scoped).
5. Press the user button (PC13) to modify DAC value.
6. Observe output changes on PA4 (DAC) and PA5 (LED brightness).

## 👤 Author

Yiguang Zhu — ECE 153B, Lab 5A–5B (Winter 2024)
