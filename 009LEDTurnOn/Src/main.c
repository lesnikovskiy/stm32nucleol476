#include <stdint.h>

int main(void) {
	volatile uint32_t *const AHB2_ENR = (volatile uint32_t*) 0x4002104C;
	volatile uint32_t *const GPIOA_MODER = (volatile uint32_t*) 0x48000000;
	volatile uint32_t *const GPIOA_ODR = (volatile uint32_t*) 0x48000014;
//	volatile uint32_t *const GPIOA_BSRR = (volatile uint32_t*) 0x48000018;

	// 1. Enable clock for GPIOA Peripheral
	*AHB2_ENR |= (1 << 0);

	// 2. Configure a mode of PA5 as Output
	*GPIOA_MODER &= ~(3 << 10);
	*GPIOA_MODER |= (1 << 10);

	// 3. Put data to data register
	*GPIOA_ODR &= ~(1 << 5);
	*GPIOA_ODR |= (1 << 5);
//	*GPIOA_BSRR |= (1 << 5);

	/* Loop forever */
	for (;;) {
		*GPIOA_ODR ^= (1 << 5);
		for (volatile uint32_t i = 0; i < 400000; i++);
	}
}
