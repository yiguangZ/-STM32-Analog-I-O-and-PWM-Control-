#include "EXTI.h"

#include "DAC.h"

void EXTI_Init(void) {
	// Initialize User Button
	// [TODO]
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~(3UL<<26);
	GPIOC->PUPDR &= ~(3UL<<26);
	GPIOC->PUPDR |= 2UL<<26;
	
	// Configure SYSCFG EXTI
	// [TODO]
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	
	// Configure EXTI Trigger
	// [TODO]
	EXTI->FTSR1 |= EXTI_FTSR1_FT13;
	// Enable EXTI
	// [TODO]
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	
	// Configure and Enable in NVIC
	// [TODO]
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn,0);
	
}
#define DAC_MIN 0
#define DAC_MAX 4095
#define DAC_INCREMENT 256

static uint32_t dac_value = 0;
static enum {
    DOWN,
    UP,
} direction = UP;

// [TODO] Interrupt handler
void EXTI15_10_IRQHandler(void) {
    // Check if EXTI13 triggered the interrupt
    if ((EXTI->PR1 & EXTI_PR1_PIF13) != 0){

        // Update DAC value 
        if (direction == UP) {
            if (dac_value + DAC_INCREMENT <= DAC_MAX) {
                dac_value += DAC_INCREMENT; // Increment DAC value
            } else {
                dac_value = DAC_MAX; // Cap at maximum
                direction = DOWN;    // Switch direction
            }
        } else { 
            if (dac_value >= DAC_INCREMENT) {
                dac_value -= DAC_INCREMENT; // Decrement DAC value
            } else {
                dac_value = DAC_MIN; // Cap at minimum
                direction = UP;      // Switch direction
            }
        }

        // Write the updated value to the DAC
        DAC_Write_Value(dac_value);
				 // Clear the interrupt pending flag
        EXTI->PR1 |= EXTI_PR1_PIF13;
    }
}

