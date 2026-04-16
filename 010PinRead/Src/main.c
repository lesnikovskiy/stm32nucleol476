#include <stdint.h>

int main(void) {
	volatile uint32_t *const AHB2_ENR = (volatile uint32_t*) 0x4002104C;
	volatile uint32_t *const GPIOA_MODER = (volatile uint32_t*) 0x48000000;
	volatile uint32_t *const GPIOA_PUPDR = (volatile uint32_t*) 0x4800000C;
	volatile uint32_t *const GPIOA_IDR = (volatile uint32_t*) 0x48000010;
	volatile uint32_t *const GPIOA_ODR = (volatile uint32_t*) 0x48000014;

	// 1. Enable clock for GPIOA Peripheral
	*AHB2_ENR |= (1 << 0);

	// 2. Configure PA0 as INPUT
	*GPIOA_MODER &= ~(3 << 0);

	// 3. Enable pull down register so it won't act like floating pin
	*GPIOA_PUPDR &= ~(3 << 0);
	*GPIOA_PUPDR |= (2 << 0); // 10 pull down

	// 3. Configure a mode of PA5 as Output
	*GPIOA_MODER &= ~(3 << 10);
	*GPIOA_MODER |= (1 << 10);

	/* Loop forever */
	for (;;) {
		uint8_t pa0Status = (uint8_t) (*GPIOA_IDR & 0x1);

		if (pa0Status) {
			*GPIOA_ODR |= (1 << 5);
		} else {
			*GPIOA_ODR &= ~(1 << 5);
		}
	}
}
