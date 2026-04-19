#include <stdint.h>
#include "delay.h"

const uint32_t SystemCoreClock = 4000000; // 4 MHz

void delay_us(uint32_t us) {
	// Calculate how many ticks are needed for 'us' microseconds
	// Formula: (Frequency in MHz) * microseconds
	// For 4MHz: 4 ticks per 1us
	uint32_t ticks = us * (SystemCoreClock / 1000000);

	SysTick->LOAD = ticks - 1;            // Set reload value
	SysTick->VAL = 0;                     // Reset current value to 0
	SysTick->CTRL = (1 << 2) | (1 << 0);  // Use processor clock and enable counter

	// Wait until the COUNTFLAG(bit 16) is set
	while (!(SysTick->CTRL & (1 << 16)));

	SysTick->CTRL = 0;                    // Disable timer
}

void delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms; i++) {

		delay_us(1000);
	}
}
