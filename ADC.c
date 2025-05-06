#include "ADC.h"

#include "stm32l476xx.h"

#include <stdint.h>

void ADC_Wakeup(void) {
    int wait_time;

    // To start ADC operations, the following sequence should be applied
    // DEEPPWD = 0: ADC not in deep-power down
    // DEEPPWD = 1: ADC in deep-power-down (default reset state)
    if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
        ADC1->CR &= ~ADC_CR_DEEPPWD; // Exit deep power down mode if still in that state

    // Enable the ADC internal voltage regulator
    // Before performing any operation such as launching a calibration or enabling the ADC, the ADC
    // voltage regulator must first be enabled and the software must wait for the regulator start-up
    // time.
    ADC1->CR |= ADC_CR_ADVREGEN;

    // Wait for ADC voltage regulator start-up time
    // The software must wait for the startup time of the ADC voltage regulator (T_ADCVREG_STUP)
    // before launching a calibration or enabling the ADC.
    // T_ADCVREG_STUP = 20 us
    wait_time = 20 * (80000000 / 1000000);
    while (wait_time != 0) {
        wait_time--;
    }
}

void ADC_Common_Configuration() {
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN; //enable I/) analog switch
	  ADC123_COMMON->CCR |= ADC_CCR_VREFEN; //enable V
	  ADC123_COMMON->CCR &= ~(15UL<<18); //clock not diveded
	  ADC123_COMMON->CCR |= 1UL<<16; //HCLK/1 mode
	  ADC123_COMMON->CCR &= ~31UL; //independent mode
	  
}

void ADC_Pin_Init(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	  GPIOA->MODER &= ~(3UL<<2);
	  GPIOA->MODER |= 3UL<<2; //Analog mode
	 GPIOA->PUPDR &= ~(3UL << 2); //No PUPD
	 GPIOA->ASCR |= GPIO_ASCR_ASC1; //connects PA1 to ADC input
}

void ADC_Init(void) {
    // [TODO] Enable & Reset ADC Clock
	  RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
    RCC->AHB2RSTR |= RCC_AHB2RSTR_ADCRST;  // Set the reset bit
    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_ADCRST; // Clear the reset bit
    // Other ADC Initialization
    ADC_Pin_Init();
    ADC_Common_Configuration();
    ADC_Wakeup();

    // [TODO] Other Configuration
	  ADC1->CR &= ~ADC_CR_ADEN;
    ADC1->CFGR &= ~ADC_CFGR_RES;          // Clear resolution bits
    ADC1->CFGR &= ~(3UL<<3); // Set resolution to 12-bit (0b00)
    ADC1->CFGR &= ~ADC_CFGR_ALIGN;        // Set right alignment
    ADC1->SQR1 &= ~ADC_SQR1_L;            // Set sequence length to 1 conversion (0b0000)
    ADC1->SQR1 &= ~ADC_SQR1_SQ1; 
	  ADC1->SQR1 |= ADC_SQR1_SQ1_1; 
		ADC1->SQR1 |= ADC_SQR1_SQ1_2; // Set channel 6 as first in the sequence
    ADC1->DIFSEL &= ~(1UL << 6); // Clear bit to set channel 6 as single-ended
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP6); // Clear previous sampling time for channel 6
    ADC1->SMPR1 |= (3UL << 18); // Set sampling time to 24.5 cycles
    ADC1->CFGR &= ~ADC_CFGR_CONT; // Clear continuous mode for single conversion
    ADC1->CFGR &= ~ADC_CFGR_EXTEN; // Disable hardware trigger (EXTEN = 0)
    ADC1->CR |= ADC_CR_ADEN; // Enable the ADC
    while (!(ADC1->ISR & ADC_ISR_ADRDY)); // Wait for ADRDY (ADC ready) flag
}