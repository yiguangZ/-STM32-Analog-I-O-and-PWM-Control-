#include "stm32l476xx.h"

static void DAC_Pin_Init(void) {
    // Enable GPIOA clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Configure PA4 as analog mode
    GPIOA->MODER |= (3UL << 8);  // Set PA4 to analog mode
    GPIOA->PUPDR &= ~(3UL << 8); // no PUPD
}


void DAC_Write_Value(uint32_t value) {
	    value &= 0xFFF; 
    // Write the value to the right-aligned 12-bit data holding register for DAC1 Channel 1
    DAC1->DHR12R1 = value;
}


void DAC_Init(void) {
    DAC_Pin_Init();

    // [TODO] Enable DAC clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
 // Ensure DAC is disabled before modifying settings
    DAC1->CR &= ~DAC_CR_EN1;
    // [TODO] Enable software trigger mode
		DAC1->CR |= DAC_CR_TSEL1; // Select software trigger
    // [TODO] Disable trigger
	DAC1->CR &= ~DAC_CR_TEN1;

    // [TODO] DAC1 connected in normal mode to external pin only with buffer enabled
	DAC1->MCR &= ~DAC_MCR_MODE1;

    // [TODO] Enable DAC channel 1
DAC1->CR |= DAC_CR_EN1;
    DAC_Write_Value(0);
}
