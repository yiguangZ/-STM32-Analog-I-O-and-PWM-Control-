
#include "SysClock.h"

void System_Clock_Init(void) {
	 // Enable MSI clock
    RCC->CR |= RCC_CR_MSION;
    while ((RCC->CR & RCC_CR_MSIRDY) == 0); 

    // Configure MSI range to 8 MHz
    RCC->CR &= ~RCC_CR_MSIRANGE;
    RCC->CR |= RCC_CR_MSIRANGE_6; // 8 MHz range
    RCC->CR |= RCC_CR_MSIRGSEL;   // Select the new range

    // Select MSI as the system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_MSI; // MSI as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI); 
}