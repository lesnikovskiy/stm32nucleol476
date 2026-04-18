#include "itm.h"

static uint8_t g_itm_debug_enabled = 0;

void ITM_Init(void) {
	// Enable Port B
	RCC->AHB2ENR |= (1 << 1);

	// Configure PB2 as Alternate Function 0 (SYS_JTDO-SWO)
	GPIOB->MODER &= ~(3 << 6);
	GPIOB->MODER |= (2 << 6); // 10 - AF
	GPIOB->AFRL &= ~(0xF << 12); // AF0 for pin 3 (bits 12-15)

	if (!(DEMCR & (1 << 24))) {
		DEMCR |= (1 << 24);
	}

	// Unlock the ITM (Mandatory for some STM32L4 variants)
	ITM->LAR = 0xC5ACCE55;

	// Enable Trace (TCR_ITMENA_Msk | TCR_DWTENA_Msk)
	ITM->TCR |= (1 << 0) | (1 << 16);

	// Enable Stimulus Port 0
	ITM->TER |= (1 << 0);

	g_itm_debug_enabled = 1;
}

void ITM_SendChar(char ch) {
	if (!g_itm_debug_enabled) {
		return;
	}

	// Wait until Port 0 is ready
	while (ITM->PORT[0] == 0);
	// Write character
	ITM->PORT[0] = (uint32_t) ch;
}
