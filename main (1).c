/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 5A
 */


#include "ADC.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>
uint32_t adc_value;

int main(void) {
    // Initialization
    System_Clock_Init(); // Switch System Clock = 16 MHz
   
    ADC_Init();

    // [TODO] Initialize PWM
	  LED_Pin_Init();
    TIM2_CH1_Init();
  uint32_t duty_cycle;    
    while (1) {
        // [TODO] Trigger ADC and get result
				ADC1->CR |= ADC_CR_ADSTART; // Start conversion
			  while (!(ADC1->ISR & ADC_ISR_EOC)); // Wait for End of Conversion (EOC) flag
			  adc_value = ADC1->DR; // Read ADC value (0 to 4095 for 12-bit resolution)
        // Map ADC value to duty cycle (0 to 100%)
        duty_cycle = (adc_value * 100) / 4095;

        // Update LED brightness using PWM
     TIM2->CCR1 = (TIM2->ARR * duty_cycle) / 100;			  
		for(int i = 0; i < 1000; i++);
    }
}