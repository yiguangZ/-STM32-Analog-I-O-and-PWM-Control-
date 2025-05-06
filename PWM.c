#include "PWM.h"

#include "stm32l476xx.h"

void LED_Pin_Init(void) {
    // Enable GPIO Clock for PA5 (TIM2_CH1)
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Set PA5 to Alternate Function Mode (AF1 for TIM2_CH1)
    GPIOA->MODER &= ~(3UL << 10);
    GPIOA->MODER |= (2UL << 10); // Alternate Function Mode
    GPIOA->AFR[0] &= ~(15UL << 20);
    GPIOA->AFR[0] |= (1UL << 20); // AF1 (TIM2_CH1)

    // Set Speed to Very High
    GPIOA->OSPEEDR |= (3UL << 10);

    // No Pull-Up or Pull-Down
    GPIOA->PUPDR &= ~(3UL << 10);
}

void TIM2_CH1_Init(void) {
    // Enable TIM2 Clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // Set Timer to Upcounting Mode
    TIM2->CR1 &= ~TIM_CR1_DIR;

    // Set Prescaler and Auto-Reload
    TIM2->PSC = 79;    // Prescaler to get 1 MHz clock (80 MHz / 80 = 1 MHz)
    TIM2->ARR = 999;   // Set PWM period to 1 ms (1 kHz)

    // Configure PWM Mode 1
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M; // Clear mode bits
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM Mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Enable Preload

    // Enable TIM2 Channel 1 Output
    TIM2->CCER |= TIM_CCER_CC1E;

    // Set Initial Duty Cycle to 0%
    TIM2->CCR1 = 0;

    // Enable Counter
    TIM2->CR1 |= TIM_CR1_CEN;
}
